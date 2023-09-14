extern system_state SYSTEM_STATE_INTERNAL[2];
extern system_state SYSTEM_STATE;
extern uint8_t current_system_state;
extern bool system_state_changed;

// The array is only 15 LEDs tall, but column 4 has a 16th LED: the backlight!
// Because of how the LEDs are addressed, this means that every other column (1-3, 5-7)
// has a virtual 16th LED in memory that doesn't exist IRL
#define NUM_LEDS_PER_STRIP 16

// Array size, not counting the 16th row used for the backlight
#define LEDS_X 7
#define LEDS_Y 15

// The image is arranged in memory in the same shape it's arranged in real life
CRGBF leds[LEDS_X][NUM_LEDS_PER_STRIP];   // Floating point version  [7][16]
CRGB leds_8[LEDS_X][NUM_LEDS_PER_STRIP];  // Quantized 8-bit version [7][16]

CRGBF leds_blended[LEDS_X][NUM_LEDS_PER_STRIP];  // Output of frame blending
CRGBF leds_last[LEDS_X][NUM_LEDS_PER_STRIP];     // Stores the last frame, used for frame blending

CLEDController *controller[LEDS_X]; // One CLEDController object per lane

// These are the 7 GPIO pins of the LED highway
const uint8_t led_pins[LEDS_X] = { 12, 14, 27, 26, 25, 33, 32 };

// This is the monochrome drawing mask for the current and
// alternate vector characters, with both used during transitions
float character_mask[2][LEDS_X][LEDS_Y];

// #############################################################################################
void init_leds() {
  // -------------------------------------------------------------------------------------------
  // Open all 7 seven lanes of the LED highway, allowing us to update each column of the
  // display in parallel. By having an exceptionally short chain of WS2812B-compatible
  // LEDs (16) split across seven GPIO at once, the frame update time becomes 6.625x faster
  // than if all 106 LEDs were updated using only a single GPIO. This boost in speed gets
  // your SuperPixie running at over 850 FPS, and the LEDs even get their own CPU core. This
  // absurdly high frame rate allows for temporal dithering, a technique that tricks your eye
  // into seeing extra levels of color resolution than is normally posssible with 8-bit LEDs
  // like these, helping to preserve color resolution when the display is dimmed.

  controller[0] = &FastLED.addLeds<WS2812B, 12, GRB>(leds_8[0], NUM_LEDS_PER_STRIP);
  controller[1] = &FastLED.addLeds<WS2812B, 14, GRB>(leds_8[1], NUM_LEDS_PER_STRIP);
  controller[2] = &FastLED.addLeds<WS2812B, 27, GRB>(leds_8[2], NUM_LEDS_PER_STRIP);
  controller[3] = &FastLED.addLeds<WS2812B, 26, GRB>(leds_8[3], NUM_LEDS_PER_STRIP);
  controller[4] = &FastLED.addLeds<WS2812B, 25, GRB>(leds_8[4], NUM_LEDS_PER_STRIP);
  controller[5] = &FastLED.addLeds<WS2812B, 33, GRB>(leds_8[5], NUM_LEDS_PER_STRIP);
  controller[6] = &FastLED.addLeds<WS2812B, 32, GRB>(leds_8[6], NUM_LEDS_PER_STRIP);

  // -------------------------------------------------------------------------------------------
  // Don't worry FastLED, we'll do our own dithering

  FastLED.setBrightness(255);
  FastLED.setDither(DISABLE_DITHER);
  // -------------------------------------------------------------------------------------------
}
// #############################################################################################


// #############################################################################################
// ---------------------------------------------------------------------------------------------
// Desaturate an input CRGBF color by a floating point amount (0.0 - 1.0)
struct CRGBF desaturate(struct CRGBF input_color, float amount) {
  float luminance = 0.2126 * input_color.r + 0.7152 * input_color.g + 0.0722 * input_color.b;
  float amount_inv = 1.0 - amount;

  struct CRGBF output;
  output.r = input_color.r * amount_inv + luminance * amount;
  output.g = input_color.g * amount_inv + luminance * amount;
  output.b = input_color.b * amount_inv + luminance * amount;

  return output;
}
// #############################################################################################


// #############################################################################################
// ---------------------------------------------------------------------------------------------
// Return a CRGBF color that represents a fully bright and saturated hue from the color wheel,
// with an input range of 0.0-1.0 instead of 0 - 360deg
struct CRGBF interpolate_hue(float hue) {
  // Scale hue to [0, 63]
  float hue_scaled = hue * 63.0f;

  // Calculate index1, avoiding expensive floor() call by using typecast to int
  int index1 = (int)hue_scaled;

  // If index1 < 0, make it 0. If index1 > 63, make it 63
  index1 = (index1 < 0 ? 0 : (index1 > 63 ? 63 : index1));

  // Calculate index2, minimizing the range to [index1, index1+1]
  int index2 = index1 + 1;

  // If index2 > 63, make it 63
  index2 = (index2 > 63 ? 63 : index2);

  // Compute interpolation factor
  float t = hue_scaled - index1;

  // Linearly interpolate
  struct CRGBF output;
  output.r = (1.0f - t) * hue_lookup[index1][0] + t * hue_lookup[index2][0];
  output.g = (1.0f - t) * hue_lookup[index1][1] + t * hue_lookup[index2][1];
  output.b = (1.0f - t) * hue_lookup[index1][2] + t * hue_lookup[index2][2];

  return output;
}
// #############################################################################################


// #############################################################################################
// ---------------------------------------------------------------------------------------------
// Return a CRGBF color that represents an input HSV color in a float range of 0.0-1.0
struct CRGBF hsv(float h, float s, float v) {
  h = fmod(h, 1.0);

  struct CRGBF col = interpolate_hue(h);
  col = desaturate(col, 1.0 - s);
  col.r *= v;
  col.g *= v;
  col.b *= v;

  return col;
}
// #############################################################################################


// #############################################################################################
// ---------------------------------------------------------------------------------------------
// Allows for blending of frames to simulate motion blur or phosphor decay
inline void apply_frame_blending() {
  float blend_val = 0;//.7;  //9;

  if (blend_val > 0.0) {
    // -------------------------------------------------------------------------------------------
    // Iterate over entire matrix
    for (uint8_t y = 0; y < LEDS_Y + 1; y++) {  // Extra row for backlight
      for (uint8_t x = 0; x < LEDS_X; x++) {
        float decayed_r = leds_last[x][y].r * blend_val;
        float decayed_g = leds_last[x][y].g * blend_val;
        float decayed_b = leds_last[x][y].b * blend_val;

        leds_blended[x][y].r = leds[x][y].r;
        leds_blended[x][y].g = leds[x][y].g;
        leds_blended[x][y].b = leds[x][y].b;

        if (decayed_r > leds[x][y].r) { leds_blended[x][y].r = decayed_r; }
        if (decayed_g > leds[x][y].g) { leds_blended[x][y].g = decayed_g; }
        if (decayed_b > leds[x][y].b) { leds_blended[x][y].b = decayed_b; }
      }
    }
    // -------------------------------------------------------------------------------------------
  } else {
    memcpy(leds_blended, leds, sizeof(CRGBF) * LEDS_X * NUM_LEDS_PER_STRIP);
  }

  memcpy(leds_last, leds_blended, sizeof(CRGBF) * LEDS_X * NUM_LEDS_PER_STRIP);
}
// #############################################################################################


// #############################################################################################
// Dims the input image by the global brightness level
inline void apply_brightness() {
  // -------------------------------------------------------------------------------------------
  // Iterate over entire matrix
  for (uint8_t y = 0; y < LEDS_Y; y++) {
    for (uint8_t x = 0; x < LEDS_X; x++) {
      leds[x][y].r *= SYSTEM_STATE.BRIGHTNESS;
      leds[x][y].g *= SYSTEM_STATE.BRIGHTNESS;
      leds[x][y].b *= SYSTEM_STATE.BRIGHTNESS;
    }
  }
}
// #############################################################################################


// #############################################################################################
// Run temporal dithering to quantize CRGBF values to 8-bit CRGBs, before sending the image to
// the LEDs via the LED highway pins
inline void update_leds() {
  // -------------------------------------------------------------------------------------------
  // Set up timekeeping
  static uint32_t iter = 0;
  iter++;

  // -------------------------------------------------------------------------------------------
  // Increment the dither_index, which decides how the pixels are strategically flickered
  // There are two fields in a checkerboard pattern, with two different indexes 180deg apart
  dither_index += 1;
  if (dither_index >= 8) {
    dither_index = 0;
  }
  uint8_t dither_index_b = dither_index + 4;
  if (dither_index_b >= 8) {
    dither_index_b -= 8;
  }
  // -------------------------------------------------------------------------------------------

  // -------------------------------------------------------------------------------------------
  // Iterate over entire matrix
  for (uint8_t y = 0; y < LEDS_Y + 1; y++) {  // Extra row for backlight
    for (uint8_t x = 0; x < LEDS_X; x++) {
      float gamma_r = leds_blended[x][y].r * leds_blended[x][y].r;  // Cheap gamma correction
      float gamma_g = leds_blended[x][y].g * leds_blended[x][y].g;
      float gamma_b = leds_blended[x][y].b * leds_blended[x][y].b;

      uint16_t color_r_16 = gamma_r * 65535;  // Scale from floating point to 16-bit
      uint16_t color_g_16 = gamma_g * 65535;
      uint16_t color_b_16 = gamma_b * 65535;

      uint8_t color_r_8 = color_r_16 >> 8;  // Upper 8 bits of color
      uint8_t color_g_8 = color_g_16 >> 8;
      uint8_t color_b_8 = color_b_16 >> 8;

      uint8_t color_r_dither = (color_r_16 << 8) >> 8;  // Lower 8 bits of color
      uint8_t color_g_dither = (color_g_16 << 8) >> 8;
      uint8_t color_b_dither = (color_b_16 << 8) >> 8;

      if (color_r_8 > 254) { color_r_8 = 254; }  // Leave room for added dither bit without overflow
      if (color_g_8 > 254) { color_g_8 = 254; }
      if (color_b_8 > 254) { color_b_8 = 254; }

      uint8_t dither_bit = bitRead(dither_pattern[iter % 2][y], x);  // Get the checkerboard pattern
      uint8_t dither_step_now = dither_index;
      if (dither_bit == 1) {  // Decide which of the two dither indices to use based on the pattern
        dither_step_now = dither_index_b;
      }

      // Set the dither bit according to the index vs. the lower 8 bits of the color
      uint8_t dither_bit_r = 0;
      uint8_t dither_bit_g = 0;
      uint8_t dither_bit_b = 0;
      if (color_r_dither > dither_steps[dither_step_now]) { dither_bit_r = 1; }
      if (color_g_dither > dither_steps[dither_step_now]) { dither_bit_g = 1; }
      if (color_b_dither > dither_steps[dither_step_now]) { dither_bit_b = 1; }

      // Assign quantized 8-bit data to the LED
      leds_8[x][y] = CRGB(color_r_8 + dither_bit_r, color_g_8 + dither_bit_g, color_b_8 + dither_bit_b);
    }
  }
  // -------------------------------------------------------------------------------------------

  // Send final dithered 8-bit image to LEDs
  controller[0]->showLeds();
  controller[1]->showLeds();
  controller[2]->showLeds();
  controller[3]->showLeds();
  controller[4]->showLeds();
  controller[5]->showLeds();
  controller[6]->showLeds();
}
// #############################################################################################


// #############################################################################################
// memset() the entire CRGBF "leds" matrix to 0
void clear_leds() {  
  memset(leds, 0, sizeof(CRGBF) * LEDS_X * NUM_LEDS_PER_STRIP);
  // --------------------------------------------------------
}
// #############################################################################################


// #############################################################################################
// Mark the CPU cycles elapsed between now and the last
// call to this function, to calculate the current FPS
void watch_fps() {
  static uint8_t iter = 0;
  static uint32_t cycles_last = 0;
  uint32_t cycles_now = ESP.getCycleCount();

  uint32_t cycles_elapsed = cycles_now - cycles_last;

  iter++;
  if (iter % 10 == 0) {  // Every time that uint8_t wraps to zero
    float FPS = float(F_CPU) / cycles_elapsed;
    Serial.println(FPS, 3);
  }

  cycles_last = cycles_now;
  // -------------------------------------------------------------------------------------------
}
// #############################################################################################


// #############################################################################################
// Converts a monochromatic character mask to an RGB image using solid colors or gradients
void draw_mask_to_leds(float draw_mask[LEDS_X][LEDS_Y]) {
  for (uint8_t x = 0; x < LEDS_X; x++) {
    for (uint8_t y = 0; y < LEDS_Y; y++) {
      leds[x][y].r = add_clipped_float(leds[x][y].r, draw_mask[x][y] * SYSTEM_STATE.DISPLAY_COLOR_A.r);
      leds[x][y].g = add_clipped_float(leds[x][y].g, draw_mask[x][y] * SYSTEM_STATE.DISPLAY_COLOR_A.g);
      leds[x][y].b = add_clipped_float(leds[x][y].b, draw_mask[x][y] * SYSTEM_STATE.DISPLAY_COLOR_A.b);
    }
  }
}
// #############################################################################################


// #############################################################################################
// Set the color of text/icons on the screen
void set_display_color(CRGBF color_a, CRGBF color_b) {
  SYSTEM_STATE_INTERNAL[!current_system_state].DISPLAY_COLOR_A = color_a;
  SYSTEM_STATE_INTERNAL[!current_system_state].DISPLAY_COLOR_B = color_b;
  system_state_changed = true;
}

void set_display_color(CRGBF color) {
  set_display_color(color, color);
}
// #############################################################################################


// #############################################################################################
// Set the color of the background
void set_display_background_color(CRGBF color_a, CRGBF color_b) {
  SYSTEM_STATE_INTERNAL[!current_system_state].DISPLAY_BACKGROUND_COLOR_A = color_a;
  SYSTEM_STATE_INTERNAL[!current_system_state].DISPLAY_BACKGROUND_COLOR_B = color_b;
  system_state_changed = true;
}

void set_display_background_color(CRGBF color) {
  set_display_background_color(color, color);
}
// #############################################################################################


// #############################################################################################
// Set the color of the backlight
void set_backlight_color(CRGBF color) {
  SYSTEM_STATE_INTERNAL[!current_system_state].BACKLIGHT_COLOR = color;
  system_state_changed = true;
}
// #############################################################################################

// #############################################################################################
// Sets the backlight brightness independently of the display
void set_backlight_brightness(float brightness_value) {
  SYSTEM_STATE_INTERNAL[!current_system_state].BACKLIGHT_BRIGHTNESS = brightness_value;
  system_state_changed = true;
}
// #############################################################################################


// #############################################################################################
// Set the brightness of the screen
void set_brightness(float brightness_value) {
  SYSTEM_STATE_INTERNAL[!current_system_state].BRIGHTNESS = brightness_value;
  system_state_changed = true;
}
// #############################################################################################


// #############################################################################################
// Update the backlight color during frame updates
void draw_backlight() {
  leds[3][15].r = SYSTEM_STATE.BACKLIGHT_COLOR.r * SYSTEM_STATE.BACKLIGHT_BRIGHTNESS;
  leds[3][15].g = SYSTEM_STATE.BACKLIGHT_COLOR.g * SYSTEM_STATE.BACKLIGHT_BRIGHTNESS;
  leds[3][15].b = SYSTEM_STATE.BACKLIGHT_COLOR.b * SYSTEM_STATE.BACKLIGHT_BRIGHTNESS;
}
// #############################################################################################


// #############################################################################################
// Draws the background color/gradient to the LED image during frame updates
void draw_background_gradient(){
  for(uint8_t y = 0; y < LEDS_Y; y++){

    float blend_val = (y/float(LEDS_Y - 1));

    CRGBF row_color = interpolate_CRGBF( SYSTEM_STATE.DISPLAY_BACKGROUND_COLOR_A, SYSTEM_STATE.DISPLAY_BACKGROUND_COLOR_B, blend_val );

    if(y == 0 || y == LEDS_Y-1){
      leds[0][y].r = row_color.r * 0.5;
      leds[0][y].g = row_color.g * 0.5;
      leds[0][y].b = row_color.b * 0.5;
    }
    else{
      leds[0][y] = row_color;
    }

    leds[1][y] = row_color;
    leds[2][y] = row_color;
    leds[3][y] = row_color;
    leds[4][y] = row_color;
    leds[5][y] = row_color;
    
    if(y == 0 || y == LEDS_Y-1){
      leds[6][y].r = row_color.r * 0.5;
      leds[6][y].g = row_color.g * 0.5;
      leds[6][y].b = row_color.b * 0.5;
    }
    else{
      leds[6][y] = row_color;
    }
  }
}
// #############################################################################################