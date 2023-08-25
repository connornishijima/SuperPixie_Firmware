//----------------------------------------------------------------------+
//   _____                    _____ _     _        _____       _        |
//  |   __|_ _ ___ ___ ___   |  _  |_|_ _|_|___   |   | |___ _| |___    |
//  |__   | | | . | -_|  _|  |   __| |_'_| | -_|  | | | | . | . | -_|   |
//  |_____|___|  _|___|_|    |__|  |_|_,_|_|___|  |_|___|___|___|___|   |
//            |_|                                                       |
//----------------------------------------------------------------------+ 

// TODO: Get firmware to fully compile with all warnings treated as errors

// TODO: Learn how to use AUnit or write your own unit tests for node firmware

// TODO: Make firmware version available via COM_GET_VERSION packet
#define FIRMWARE_VERSION 10000

// External dependencies
#include <FastLED.h>
#include <FixedPoints.h>
#include <FixedPointsCommon.h>
#include <FS.h>        
#include <LittleFS.h> 
#include <WiFi.h>
#include <Ticker.h>

// Internal dependencies
#include "constants.h"
#include "globals.h"
#include "utilities.h"
#include "transitions.h"
#include "commands.h"
#include "node_fs.h"
#include "packets.h"
#include "system.h"
#include "sine.h"
#include "leds.h"
#include "ascii.h"
#include "vector_drawing.h"

void setup() {
  init_system();

  xTaskCreatePinnedToCore(
    loop_leds,      // Function representing the task
    "Loop (LEDs)",  // Task name (optional)
    10000,          // Stack size (bytes)
    NULL,           // Task parameter (can be NULL)
    1,              // Priority (higher value means higher priority)
    NULL,           // Task handle (optional)
    1               // Core to run the task on (0 or 1)
  );

  xTaskCreatePinnedToCore(
    loop_node,      // Function representing the task
    "Loop (Node)",  // Task name (optional)
    10000,          // Stack size (bytes)
    NULL,           // Task parameter (can be NULL)
    1,              // Priority (higher value means higher priority)
    NULL,           // Task handle (optional)
    0               // Core to run the task on (0 or 1)
  );
}


void loop() {
  yield();
}

// TODO: Move run_leds() to leds.h instead of main .ino
void run_leds(uint32_t t_now) {
  static uint8_t iter = 0;
  iter++;

  if(iter >= 10){
    iter = 0;
    if(FastLED.getBrightness() != CONFIG.BRIGHTNESS){
      FastLED.setBrightness(CONFIG.BRIGHTNESS);
    }
  }

  if (transition_complete == false) {
    run_transition(t_now);

    clear_display();
    debug_polygon();

    memcpy(mask_output, mask, sizeof(float) * (LEDS_X * LEDS_Y));

    if (CONFIG.FX_OPACITY > 0.0) {
      memcpy(mask_output_fx, mask, sizeof(float) * (LEDS_X * LEDS_Y));

      blur_mask(mask_output_fx, CONFIG.FX_BLUR);
      darken_mask(mask_output_fx, CONFIG.FX_OPACITY);
    }
  }

  update_leds();
  yield();
}

// TODO: Document all function definition locations that aren't in the current file
// For example, calls to `run_node();` should always have a "// (system.h)" comment after them to aid with navigation.
void loop_node(void *parameter) {
  debugln("NODE LOOP START");
  while (1) {
    static uint32_t iter = 0;

    uint32_t t_now = micros();
    uint32_t t_now_ms = t_now/1000;
    run_node(t_now, t_now_ms);
    run_touch();
    check_settings(t_now_ms);

    iter++;
    if(iter == 10000){
      iter = 0;
      DEVICE.FPS = 1000000 / float(current_frame_duration_us);
      //print_lookup_table();
      //debug("FPS: ");
      //debugln(CONFIG.FPS);
      //print_debug_hits();
    }
    
    yield();
  }
}

void loop_leds(void *parameter) {
  debugln("LEDS LOOP START");
  init_leds();
  
  while (1) {
    if(freeze_led_image == false){
      uint32_t t_now_led = micros();
      run_leds(t_now_led);
      run_fps(t_now_led);
    }
    else{
      yield();
    }
  }
}

// TODO: Replace stupid debug_polygon() function with better name and structure
void debug_polygon() {
  memset(temp_mask, 0, sizeof(float)*LEDS_X*LEDS_Y);

  draw_character(DEVICE.CURRENT_CHARACTER, 1.0);
  draw_character(DEVICE.NEW_CHARACTER, 1.0);

  memcpy(mask, temp_mask, sizeof(float)*LEDS_X*LEDS_Y);
}
