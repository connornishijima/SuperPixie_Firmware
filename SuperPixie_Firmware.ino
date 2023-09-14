// #############################################################################################
//----------------------------------------------------------------------+
//   _____                    _____ _     _        _____       _        |
//  |   __|_ _ ___ ___ ___   |  _  |_|_ _|_|___   |   | |___ _| |___    |
//  |__   | | | . | -_|  _|  |   __| |_'_| | -_|  | | | | . | . | -_|   |
//  |_____|___|  _|___|_|    |__|  |_|_,_|_|___|  |_|___|___|___|___|   |
//            |_|                                                       |
//----------------------------------------------------------------------+
// #############################################################################################

// TODO: Document all function definition locations that aren't in the current file 

// TODO: Learn how to use AUnit or write your own unit tests for node firmware

// TODO: Make firmware version available via COM_GET_VERSION packet
#define FIRMWARE_VERSION 10000

// External dependencies
#include <FastLED.h>

// Internal dependencies
#include "constants.h"
#include "math_utilities.h"
#include "ascii.h"
#include "dithering.h"
#include "leds.h"
#include "system.h"
#include "transitions.h"
#include "vector_drawing.h"
#include "test_code.h"


// #############################################################################################
// Runs only once at startup
void setup() {
  // -----------------------------------
  // Init UART at 230400 for development
  Serial.begin(230400);
  // -----------------------------------

  // -------------------------------
  // Init LEDs, UARTs, memory, cores
  init_system();
  // -------------------------------
}
// #############################################################################################


// #############################################################################################
// Unused main Arduino loop()
void loop() {
  yield(); // Keep watchdog timer happy
}
// #############################################################################################


// #############################################################################################
// Core 0: "GPU CORE" handles vector rasterization, transitions, dithering, and LED updating
void loop_gpu(void *parameter) {
  while (1) {
    // -----------------------------------------------------------------
    // Note the current time in milliseconds and microcseconds this loop
    time_us_now = micros();
    time_ms_now = millis();
    // -----------------------------------------------------------------

    // ---------------------------
    // Reset output image to black
    clear_leds();
    // ---------------------------

    // -------------------------------------------------------------
    // Draw the background gradient to the display after clearing it
    draw_background_gradient();
    // -------------------------------------------------------------

    // ----------------------------------------------
    // Run transitions and system state interpolation
    run_system_transition();
    // ----------------------------------------------

    // ------------------------------------------------
    // Draw characters to the screen via the rasterizer
    draw_characters();
    // ------------------------------------------------

    // --------------------------
    // Update the backlight color
    draw_backlight();
    // --------------------------

    // ------------------------------------------------------------------------
    // Apply global brightness level
    apply_brightness();
    // ------------------------------------------------------------------------

    // ------------------------------------------------------------------------
    // Apply frame blending algorithm to simulate motion blur or phosphor decay
    apply_frame_blending();
    // ------------------------------------------------------------------------

    // --------------------------------------------------------------
    // Send the updated LED image down all 7 lanes of the LED highway
    update_leds();
    // --------------------------------------------------------------

    // -----------------------
    // Measure the current FPS
    watch_fps();
    // -----------------------
  }
}


// #############################################################################################
// Core 1: "CPU CORE" handles UART chain communication, touch sensing and system configuration
void loop_cpu(void *parameter) {
  while (1) {
    static uint32_t next_flip_ms = 0;
    static uint8_t current_character = 33;

    if(time_ms_now >= next_flip_ms){
      static float modulation = 0.0;
      modulation += 0.05;
      modulation = fmod(modulation, 1.0);

      set_transition_time_ms( 75 );
      set_transition_type( TRANSITION_FLIP_VERTICAL );
      set_display_color( hsv( modulation, 1.0, 1.0 ) );
      //set_display_background_color( hsv( modulation+0.33, 1.0, 0.15 ), hsv( modulation+0.66, 1.0, 0.0 ) );
      set_backlight_color( hsv( modulation+0.33, 1.0, 1.0 ) );
      set_brightness( 1.0 );
      set_backlight_brightness( 1.0 );
      
      set_new_character(current_character);
      current_character += 1;
      if(current_character >= 127){
        current_character = 33;
      }

      trigger_transition();

      next_flip_ms += 150;
    }

    yield(); // Keep watchdog timer happy since I haven't written the CPU core yet
  }
}
// #############################################################################################