// Possible UART commands
typedef enum {
  /* 0  */ COM_TEST,
  /* 1  */ COM_PROBE,
  /* 2  */ COM_PROBE_RESPONSE,
  /* 3  */ COM_ENABLE_PROPAGATION,
  /* 4  */ COM_LENGTH_INQUIRY,
  /* 5  */ COM_LENGTH_RESPONSE,
  /* 6  */ COM_INFORM_CHAIN_LENGTH,
  /* 7  */ COM_SET_BACKLIGHT_COLOR,
  /* 8  */ COM_SET_FRAME_BLENDING,
  /* 9  */ COM_SET_BRIGHTNESS,
  /* 10 */ COM_SHOW,
  /* 11 */ COM_SET_TRANSITION_TYPE,
  /* 12 */ COM_SET_TRANSITION_DURATION_MS,
  /* 13 */ COM_SET_CHARACTER,
  /* 14 */ COM_START_BUS_MODE,
  /* 15 */ COM_END_BUS_MODE,
  /* 16 */ COM_BUS_READY,
  /* 17 */ COM_SET_DEBUG_OVERLAY_OPACITY,
  /* 18 */ COM_SET_DISPLAY_COLORS,
  /* 19 */ COM_SET_GRADIENT_TYPE,
  /* 20 */ COM_GET_FPS,
  /* 21 */ COM_SET_STRING,
  /* 22 */ COM_TRANSITION_COMPLETE,
  /* 23 */ COM_GET_VERSION,
  /* 24 */ COM_TOUCH_EVENT,
  /* 25 */ COM_VERSION_RESPONSE,
  /* 26 */ COM_SET_TRANSITION_INTERPOLATION,
  /* 27 */ COM_SET_TOUCH_GLOW_POSITION,
  /* 28 */ COM_SET_TOUCH_GLOW_COLOR,
  /* 29 */ COM_READ_TOUCH,
  /* 30 */ COM_CALIBRATE_TOUCH,
  /* 31 */ COM_READ_TOUCH_RESPONSE,
  /* 32 */ COM_SET_TOUCH_THRESHOLD,
  /* 33 */ COM_SAVE_STORAGE,
  
  NUM_COMMANDS
} command_t;