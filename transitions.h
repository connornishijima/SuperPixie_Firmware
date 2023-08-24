extern int16_t get_sine_float_index(float index);

void run_transition(uint32_t t_now) {
  // Simple, instant transition
  if (CONFIG.TRANSITION_TYPE == TRANSITION_INSTANT) {
    DEVICE.CURRENT_CHARACTER.character = DEVICE.NEW_CHARACTER.character;
    DEVICE.CURRENT_CHARACTER.opacity = 1.0;
    transition_complete = true;
  }
  
  // Fancy transitions
  else {
    DEVICE.MASTER_OPACITY = 1.0;
    DEVICE.CURRENT_CHARACTER.opacity = 1.0;
    DEVICE.NEW_CHARACTER.opacity = 0.0;

    uint32_t time_elapsed = t_now - transition_start;
    uint32_t transition_duration = transition_end - transition_start;
    float transition_progress = float(time_elapsed) / float(transition_duration);

    // Handle potential time errors
    if (transition_progress < 0.0) {
      transition_progress = 0.0;
    }
    
    // Transition is complete, clean up
    else if (transition_progress >= 1.0) {
      DEVICE.CURRENT_CHARACTER.opacity = 1.0;
      DEVICE.NEW_CHARACTER.opacity = 0.0;

      DEVICE.CURRENT_CHARACTER.character = DEVICE.NEW_CHARACTER.character;
      transition_progress = 1.0;
      transition_complete = true;

      DEVICE.CURRENT_CHARACTER.pos_x = 0.0;
      DEVICE.CURRENT_CHARACTER.pos_y = 0.0;
      DEVICE.CURRENT_CHARACTER.scale_x = 1.0;
      DEVICE.CURRENT_CHARACTER.scale_y = 1.0;
      DEVICE.CURRENT_CHARACTER.rotation = 0.0;

      DEVICE.NEW_CHARACTER.pos_x = 0.0;
      DEVICE.NEW_CHARACTER.pos_y = 0.0;
      DEVICE.NEW_CHARACTER.scale_x = 1.0;
      DEVICE.NEW_CHARACTER.scale_y = 1.0;
      DEVICE.NEW_CHARACTER.rotation = 0.0;
    }
    
    // Transition is running
    else {
      if (CONFIG.TRANSITION_TYPE == TRANSITION_FLIP_HORIZONTAL) {
        if (transition_progress >= 0.5) {
          DEVICE.CURRENT_CHARACTER.character = DEVICE.NEW_CHARACTER.character;
        }
        DEVICE.CURRENT_CHARACTER.scale_x = (get_sine_float_index(transition_progress + 0.25) / 32768.0) * 0.5 + 0.5;
        DEVICE.NEW_CHARACTER.scale_x = DEVICE.CURRENT_CHARACTER.scale_x;
      } else if (CONFIG.TRANSITION_TYPE == TRANSITION_FLIP_VERTICAL) {
        if (transition_progress >= 0.5) {
          DEVICE.CURRENT_CHARACTER.character = DEVICE.NEW_CHARACTER.character;
        }
        DEVICE.CURRENT_CHARACTER.scale_y = (get_sine_float_index(transition_progress + 0.25) / 32768.0) * 0.5 + 0.5;
        DEVICE.NEW_CHARACTER.scale_y = DEVICE.CURRENT_CHARACTER.scale_y;
      } else if (CONFIG.TRANSITION_TYPE == TRANSITION_FADE) {
        DEVICE.CURRENT_CHARACTER.opacity = 1.0 - transition_progress;
        DEVICE.NEW_CHARACTER.opacity = transition_progress;
      } else if (CONFIG.TRANSITION_TYPE == TRANSITION_FADE_OUT) {
        if (transition_progress >= 0.5) {
          DEVICE.CURRENT_CHARACTER.character = DEVICE.NEW_CHARACTER.character;
        }
        DEVICE.MASTER_OPACITY = (get_sine_float_index(transition_progress + 0.25) / 32768.0) * 0.5 + 0.5;
      } else if (CONFIG.TRANSITION_TYPE == TRANSITION_SPIN_LEFT) {
        DEVICE.CURRENT_CHARACTER.rotation = ((1.0 - ((get_sine_float_index((transition_progress * 0.5) + 0.25) / 32768.0) * 0.5 + 0.5)) * 360.0) * -1.0;
        DEVICE.NEW_CHARACTER.rotation = DEVICE.CURRENT_CHARACTER.rotation;
        DEVICE.CURRENT_CHARACTER.opacity = 1.0 - transition_progress;
        DEVICE.NEW_CHARACTER.opacity = transition_progress;
      } else if (CONFIG.TRANSITION_TYPE == TRANSITION_SPIN_RIGHT) {
        DEVICE.CURRENT_CHARACTER.rotation = (1.0 - ((get_sine_float_index((transition_progress * 0.5) + 0.25) / 32768.0) * 0.5 + 0.5)) * 360.0;
        DEVICE.NEW_CHARACTER.rotation = DEVICE.CURRENT_CHARACTER.rotation;
        DEVICE.CURRENT_CHARACTER.opacity = 1.0 - transition_progress;
        DEVICE.NEW_CHARACTER.opacity = transition_progress;
      } else if (CONFIG.TRANSITION_TYPE == TRANSITION_SPIN_HALF_LEFT) {
        DEVICE.CURRENT_CHARACTER.rotation = ((1.0 - ((get_sine_float_index((transition_progress * 0.5) + 0.25) / 32768.0) * 0.5 + 0.5)) * 180.0) * -1.0;
        DEVICE.NEW_CHARACTER.rotation = DEVICE.CURRENT_CHARACTER.rotation - 180.0;
        DEVICE.CURRENT_CHARACTER.opacity = 1.0 - transition_progress;
        DEVICE.NEW_CHARACTER.opacity = transition_progress;
      } else if (CONFIG.TRANSITION_TYPE == TRANSITION_SPIN_HALF_RIGHT) {
        DEVICE.CURRENT_CHARACTER.rotation = (1.0 - ((get_sine_float_index((transition_progress * 0.5) + 0.25) / 32768.0) * 0.5 + 0.5)) * 180.0;
        DEVICE.NEW_CHARACTER.rotation = DEVICE.CURRENT_CHARACTER.rotation + 180.0;
        DEVICE.CURRENT_CHARACTER.opacity = 1.0 - transition_progress;
        DEVICE.NEW_CHARACTER.opacity = transition_progress;
      }

      else if (CONFIG.TRANSITION_TYPE == TRANSITION_SHRINK) {
        if (transition_progress >= 0.5) {
          DEVICE.CURRENT_CHARACTER.character = DEVICE.NEW_CHARACTER.character;
        }
        DEVICE.CURRENT_CHARACTER.scale_x = (get_sine_float_index(transition_progress + 0.25) / 32768.0) * 0.5 + 0.5;
        DEVICE.CURRENT_CHARACTER.scale_y = DEVICE.CURRENT_CHARACTER.scale_x;
        DEVICE.NEW_CHARACTER.scale_x = DEVICE.CURRENT_CHARACTER.scale_x;
        DEVICE.NEW_CHARACTER.scale_y = DEVICE.CURRENT_CHARACTER.scale_y;
      }

      else if (CONFIG.TRANSITION_TYPE == TRANSITION_PUSH_DOWN) {
        float push = 1.0 - ((get_sine_float_index(transition_progress * 0.5 + 0.25) / 32768.0) * 0.5 + 0.5);
        DEVICE.CURRENT_CHARACTER.pos_y = -22.0 * push;
        DEVICE.NEW_CHARACTER.pos_y = DEVICE.CURRENT_CHARACTER.pos_y + 22.0;

        DEVICE.CURRENT_CHARACTER.opacity = 1.0 - push;
        DEVICE.NEW_CHARACTER.opacity = 1.0;
      } else if (CONFIG.TRANSITION_TYPE == TRANSITION_PUSH_UP) {
        float push = 1.0 - ((get_sine_float_index(transition_progress * 0.5 + 0.25) / 32768.0) * 0.5 + 0.5);
        DEVICE.CURRENT_CHARACTER.pos_y = 22.0 * push;
        DEVICE.NEW_CHARACTER.pos_y = DEVICE.CURRENT_CHARACTER.pos_y - 22.0;

        DEVICE.CURRENT_CHARACTER.opacity = 1.0 - push;
        DEVICE.NEW_CHARACTER.opacity = 1.0;
      } else if (CONFIG.TRANSITION_TYPE == TRANSITION_PUSH_LEFT) {
        float push = 1.0 - ((get_sine_float_index(transition_progress * 0.5 + 0.25) / 32768.0) * 0.5 + 0.5);
        DEVICE.CURRENT_CHARACTER.pos_x = -15.0 * push;
        DEVICE.NEW_CHARACTER.pos_x = DEVICE.CURRENT_CHARACTER.pos_x + 15.0;

        DEVICE.CURRENT_CHARACTER.opacity = 1.0;  //-push;
        DEVICE.NEW_CHARACTER.opacity = 1.0;
      } else if (CONFIG.TRANSITION_TYPE == TRANSITION_PUSH_RIGHT) {
        float push = 1.0 - ((get_sine_float_index(transition_progress * 0.5 + 0.25) / 32768.0) * 0.5 + 0.5);
        DEVICE.CURRENT_CHARACTER.pos_x = 15.0 * push;
        DEVICE.NEW_CHARACTER.pos_x = DEVICE.CURRENT_CHARACTER.pos_x - 15.0;

        DEVICE.CURRENT_CHARACTER.opacity = 1.0 - push;
        DEVICE.NEW_CHARACTER.opacity = 1.0;
      }
    }
  }
}