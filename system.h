#include <driver/uart.h>
#include "soc/rtc_cntl_reg.h"

// Functions not in scope yet
extern void init_leds();
extern void show(uint32_t t_now);

// Check to see in the left-hand RX line has been pulled LOW
// for more than RESET_PULSE_DURATION_MS (constants.h) and
// resetting the node to its default state
void check_reset(uint32_t t_now_ms) {
  // Read the RX GPIO
  uint8_t state_now = digitalRead(SERIAL_2_RX_GPIO);

  // Voltage falling now, mark the time
  if (state_now == LOW && rx_low == false) {
    rx_drop_start = t_now_ms;
    rx_low = true;
  }

  // Voltage rising now
  else if (state_now == HIGH && rx_low == true) {
    rx_low = false;
  }

  // If RX is LOW:
  if (rx_low == true) {
    // Measure time since voltage fell
    rx_drop_duration = (int32_t)(t_now_ms - rx_drop_start);

    // if >= half second since boot
    if (t_now_ms >= 500) {
      if (rx_drop_duration >= RESET_PULSE_DURATION_MS) {
        // Reset node to default state
        freeze_led_image = true;
        digitalWrite(2, HIGH);

        // Propagate reset pulse
        digitalWrite(SERIAL_0_TX_GPIO, LOW);
        delay(RESET_PULSE_DURATION_MS + 10);
        digitalWrite(SERIAL_0_TX_GPIO, HIGH);

        // RESET AS FAST AS POSSIBLE VIA REGISTER WRITE
        REG_WRITE(RTC_CNTL_OPTIONS0_REG, RTC_CNTL_SW_SYS_RST);
      }
    }
  }
}

// Set pin modes
void init_gpio() {
  debugln("---- init_gpio()");
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
}

// Used to switch UART baud rates on the fly
void set_new_baud_rate(uint32_t new_baud) {
  chain_left.flush();                                // wait for last transmitted data to be sent
  chain_left.begin(new_baud);                        // Start new baud rate
  while (chain_left.available()) chain_left.read();  // empty out possible garbage from input buffer

  if (DEVICE.PROPAGATION == true) {
    chain_right.flush();                                 // wait for last transmitted data to be sent
    chain_right.begin(new_baud);                         // Start new baud rate
    while (chain_right.available()) chain_right.read();  // empty out possible garbage from input buffer
  }

  // Save updated baud rate
  DEVICE.BAUD = new_baud;
}

// Set up UART communication
void init_uart() {
  debugln("---- init_uart()");
  chain_left.begin(DEFAULT_CHAIN_BAUD, SERIAL_8N1, SERIAL_2_RX_GPIO, SERIAL_2_TX_GPIO);
}

// Reset config struct to default values
void set_config_defaults() {
  debugln("---- set_config_defaults()");

  character empty_char;
  empty_char.character = ' ';
  empty_char.pos_x = 0.0;
  empty_char.pos_y = 0.0;
  empty_char.scale_x = 1.0;
  empty_char.scale_y = 1.0;
  empty_char.rotation = 0.0;
  empty_char.opacity = 0.0;

  DEVICE.LOCAL_ADDRESS = ADDRESS_NULL;
  DEVICE.PROPAGATION = false;
  DEVICE.BAUD = DEFAULT_CHAIN_BAUD;
  DEVICE.DEBUG_LED = 0;

  CONFIG.BRIGHTNESS = 255;

  CONFIG.DISPLAY_COLOR_A = CRGB(255, 0, 0);
  CONFIG.DISPLAY_COLOR_B = CRGB(255, 0, 0);

  CONFIG.GRADIENT_TYPE = GRADIENT_NONE;

  CONFIG.FX_COLOR = CRGB(0, 0, 0);
  CONFIG.FX_OPACITY = 0.0;
  CONFIG.FX_BLUR = 0.0;

  DEVICE.CHARACTER_SCALE = 1.0;

  CONFIG.TRANSITION_TYPE = TRANSITION_INSTANT;
  CONFIG.TRANSITION_DURATION_MS = 0;

  DEVICE.CURRENT_CHARACTER = empty_char;
  DEVICE.NEW_CHARACTER = empty_char;

  DEVICE.MASTER_OPACITY = 1.0;

  CONFIG.FRAME_BLENDING = 0.0;

  DEVICE.TOUCH_VAL = 255;
  CONFIG.TOUCH_THRESHOLD = 50;
  DEVICE.TOUCH_ACTIVE = false;

  CONFIG.FORCE_TRANSITION = true;

  CONFIG.CHAIN_LENGTH = 0;

  CONFIG.SCROLL_TIME_MS = 150;
  CONFIG.SCROLL_HOLD_TIME_MS = 250;

  DEVICE.READY = true;

  DEVICE.FAST_MODE = false;
}

void enable_fast_mode() {
  pinMode(SERIAL_2_RX_GPIO, INPUT);
  pinMode(SERIAL_0_TX_GPIO, OUTPUT);

  gpio_matrix_in(SERIAL_2_RX_GPIO, SIG_IN_FUNC224_IDX, false);          // chain_left RX pin
                                                                        // connected directly to...
  gpio_matrix_out(SERIAL_0_TX_GPIO, SIG_IN_FUNC224_IDX, false, false);  // chain_right TX pin
                                                                        // for instant propagation
                                                                        // of data down the chain

  DEVICE.FAST_MODE = true;  // Outgoing commands are instant, returning ACKs are still propagated manually
}

void disable_fast_mode() {
  gpio_matrix_in(SERIAL_2_RX_GPIO, 0x100, false);          // Restore GPIO 23 to its original function
  gpio_matrix_out(SERIAL_0_TX_GPIO, 0x100, false, false);  // Restore GPIO 1 to its original function

  DEVICE.FAST_MODE = false;
}

// Blink debug LED
void blink() {
  digitalWrite(2, HIGH);
  delay(10);
  digitalWrite(2, LOW);
}

// Parse/propagate chain data
void run_node(uint32_t t_now, uint32_t t_now_ms) {
  check_reset(t_now_ms);

  static uint32_t next_announcement = 0;

  if (DEVICE.LOCAL_ADDRESS == ADDRESS_NULL) {
    // Check if enough time has elapsed by looking at the sign of the subtraction
    if ((int32_t)(t_now - next_announcement) >= 0) {
      next_announcement = t_now + (ANOUNCEMENT_INTERVAL_MS * 1000UL);
      //announce_to_chain();
    }
  }

  while (chain_left.available() > 0 || chain_right.available() > 0) {
    // Data coming from chain commander
    if (chain_left.available() > 0) {
      uint8_t byte = chain_left.read();

      if (DEVICE.PROPAGATION == true && debug_mode == false && DEVICE.FAST_MODE == false) {
        chain_right.write(byte);
      }

      //debug("RX: ");
      //debugln(byte);

      feed_byte_into_sync_buffer(byte);

      // Packet started
      if (sync_buffer[0] == SYNC_PATTERN_1) {
        if (sync_buffer[1] == SYNC_PATTERN_2) {
          if (sync_buffer[2] == SYNC_PATTERN_3) {
            if (sync_buffer[3] == SYNC_PATTERN_4) {
              digitalWrite(2, HIGH);
              //debugln("GOT SYNC");
              init_packet();
            }
          }
        }
      } else if (packet_started) {
        bool got_data = false;

        feed_byte_into_packet_buffer(byte);
        packet_read_counter--;
        //debug("packet_read_counter = ");
        //debugln(packet_read_counter);

        if (packet_read_counter == 4) {  // Alter first Hop Address byte
          if (byte == ADDRESS_NULL) {
            byte = DEVICE.LOCAL_ADDRESS;
          }
        }

        if (packet_read_counter == 0) {
          if (packet_got_header == false) {
            packet_got_header = true;
            //debugln("GOT HEADER");
            packet_read_counter = byte;  // Currently reading DATA_LENGTH_IN_BYTES byte
            if (packet_read_counter == 0) {
              got_data = true;
            }
          } else if (packet_got_header == true) {
            got_data = true;
          }
        }

        if (got_data == true) {
          //debugln("GOT DATA, PARSING PACKET");
          parse_packet(t_now);
          digitalWrite(2, LOW);
          packet_started = false;
        }
      }
    }

    // -----------------------------------------------------------------
    // Data returning to chain commander
    if (chain_right.available() > 0) {
      uint8_t byte = chain_right.read();

      feed_byte_into_return_sync_buffer(byte);

      // Packet started
      if (return_sync_buffer[0] == SYNC_PATTERN_1) {
        if (return_sync_buffer[1] == SYNC_PATTERN_2) {
          if (return_sync_buffer[2] == SYNC_PATTERN_3) {
            if (return_sync_buffer[3] == SYNC_PATTERN_4) {
              //digitalWrite(2, HIGH);
              debugln("GOT RETURNING SYNC");
              init_return_packet();
            }
          }
        }
      } else if (return_packet_started) {
        bool return_got_data = false;

        feed_byte_into_return_packet_buffer(byte);
        return_packet_read_counter--;
        debug("return_packet_read_counter = ");
        debugln(return_packet_read_counter);

        if (return_packet_read_counter == 4) {  // Alter first Hop Address byte
          if (byte == ADDRESS_NULL) {
            //digitalWrite(2, HIGH);
            debug("ASSIGNED FIRST HOP TO ");
            debugln(DEVICE.LOCAL_ADDRESS);
            byte = DEVICE.LOCAL_ADDRESS;
          }

          //digitalWrite(2, LOW);
        }

        if (return_packet_read_counter == 0) {
          if (return_packet_got_header == false) {
            return_packet_got_header = true;
            debugln("GOT HEADER");
            return_packet_read_counter = byte;  // Currently reading DATA_LENGTH_IN_BYTES byte
            if (return_packet_read_counter == 0) {
              return_got_data = true;
            }
          } else if (return_packet_got_header == true) {
            return_got_data = true;
          }
        }

        if (return_got_data == true) {
          debugln("GOT DATA, PARSING RETURN PACKET");
          parse_return_packet(t_now);
          return_packet_started = false;
          //digitalWrite(2, LOW);
        }
      }

      chain_left.write(byte);
    }
  }
}

void run_touch() {
  DEVICE.TOUCH_VAL = touchRead(TOUCH_PIN);

  /*
  debug("TOUCH: ");
  debug(DEVICE.TOUCH_VAL);
  debug(" / ");
  debugln(CONFIG.TOUCH_THRESHOLD);
  */

  bool touching = false;
  if (DEVICE.TOUCH_VAL <= CONFIG.TOUCH_THRESHOLD) {
    touching = true;
  }

  if (touching != DEVICE.TOUCH_ACTIVE) {
    /*
    if(touching == true){
      debugln("---------- TOUCH START");
    }
    else{
      debugln("------------ TOUCH END");
    }
    */

    DEVICE.TOUCH_ACTIVE = touching;
    send_touch_event();
  }
}

void debug_check() {
  debug_hits[debug_step] += 1;
}

// Bootup sequence
void init_system() {
  set_config_defaults();

  init_fs();

  init_gpio();
  init_uart();

  // Disable Wi-Fi
  debugln("DISABLING WIFI");
  WiFi.mode(WIFI_OFF);

  //CONFIG.TOUCH_THRESHOLD = 50;
  //save_config();

  //uint32_t t_now = micros();
  //set_new_character(t_now, '?');
  //show(t_now);
}

void run_fps(uint32_t t_now) {
  static uint32_t last_frame_us = 0;

  if (t_now < last_frame_us) {
    // Handle rollover
    current_frame_duration_us = (0xFFFFFFFF - last_frame_us) + t_now + 1;
  } else {
    current_frame_duration_us = t_now - last_frame_us;
  }

  last_frame_us = t_now;
}

void serial_delay(uint16_t del_ms) {
  uint32_t start_time = millis();
  uint32_t t_now;

  while ((int32_t)(millis() - start_time) < del_ms) {
    t_now = micros();
    uint32_t t_now_ms = t_now / 1000;
    yield();
    run_node(t_now, t_now_ms);
  }
}