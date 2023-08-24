// Used to signify start and end of packets
#define SYNC_PATTERN_1 0b11001100
#define SYNC_PATTERN_2 0b00110011
#define SYNC_PATTERN_3 0b10101010
#define SYNC_PATTERN_4 0b01010101

// Reserved addresses
#define ADDRESS_BROADCAST 255
#define ADDRESS_NULL      254
#define ADDRESS_COMMANDER 253

// UART objects
#define chain_left  Serial2
#define chain_right Serial

#define DEFAULT_CHAIN_BAUD (38400)

#define SERIAL_0_RX_GPIO (3)
#define SERIAL_0_TX_GPIO (1)

#define SERIAL_2_RX_GPIO (23)
#define SERIAL_2_TX_GPIO (22)

#define RESET_PULSE_DURATION_MS (10)

#define ANOUNCEMENT_INTERVAL_MS (50) // 20Hz

// LED Count
#define NUM_LEDS 70*2
#define LED_DATA_PIN 18

#define TOUCH_PIN 13

uint8_t NULL_DATA[1] = {0};

#define PASS "PASS"
#define FAIL "FAIL ###################"

enum transitions {
  TRANSITION_INSTANT,
  TRANSITION_FADE,
  TRANSITION_FADE_OUT,
  TRANSITION_FLIP_HORIZONTAL,
  TRANSITION_FLIP_VERTICAL,
  TRANSITION_SPIN_LEFT,
  TRANSITION_SPIN_RIGHT,
  TRANSITION_SPIN_HALF_LEFT,
  TRANSITION_SPIN_HALF_RIGHT,
  TRANSITION_SHRINK,
  TRANSITION_PUSH_UP,
  TRANSITION_PUSH_DOWN,
  TRANSITION_PUSH_LEFT,
  TRANSITION_PUSH_RIGHT,

  NUM_TRANSITIONS
};


enum gradient_directions {
  GRADIENT_NONE,
  GRADIENT_HORIZONTAL,
  GRADIENT_VERTICAL,
  GRADIENT_BRIGHTNESS,
};


struct character {
  char     character;

  float    pos_x;
  float    pos_y;

  float    scale_x;
  float    scale_y;

  float    rotation;

  float    opacity;
};


struct conf {
  uint8_t  BRIGHTNESS;

  CRGB     DISPLAY_COLOR_A;
  CRGB     DISPLAY_COLOR_B;
  
  uint8_t  GRADIENT_TYPE;
  
  uint8_t  TRANSITION_TYPE;
  uint16_t TRANSITION_DURATION_MS;
  
  float    FRAME_BLENDING;
  bool     FORCE_TRANSITION;
  uint8_t  CHAIN_LENGTH;

  uint16_t TOUCH_THRESHOLD;
  
  CRGB     FX_COLOR;
  float    FX_OPACITY;
  float    FX_BLUR;

  uint16_t SCROLL_TIME_MS;
  uint16_t SCROLL_HOLD_TIME_MS;
};


struct device {
  uint8_t   LOCAL_ADDRESS;
  bool      PROPAGATION;
  uint32_t  BAUD;
  uint8_t   DEBUG_LED;
  float     CHARACTER_SCALE;
  uint16_t  TOUCH_VAL;
  bool      TOUCH_ACTIVE;
  float     FPS;
  character CURRENT_CHARACTER;
  character NEW_CHARACTER;
  bool      READY;
  float     MASTER_OPACITY;
  bool      FAST_MODE;
};


Ticker debug_checker;