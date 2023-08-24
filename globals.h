// Stored configuration
conf CONFIG;

// Runtime configuration
device DEVICE;

// Debug mode forces information out the righthand A/B pins at DEFAULT CHAIN BAUD,
// Which makes it impossible to use nodes after this one in the chain!
bool debug_mode = false;
uint8_t debug_step = 0;
uint32_t debug_hits[16] = { 0 };

// Holds incoming data
uint8_t packet_buffer[256] = { 0 };
uint8_t packet_buffer_index = 0;
bool packet_started = false;
bool packet_got_header = false;
int16_t packet_read_counter = 0;

// Holds incoming data
uint8_t return_packet_buffer[256] = { 0 };
uint8_t return_packet_buffer_index = 0;
bool return_packet_started = false;
bool return_packet_got_header = false;
int16_t return_packet_read_counter = 0;

uint8_t sync_buffer[4] = { 0 };
uint8_t return_sync_buffer[4] = { 0 };

bool mask_needs_update = false;

bool transition_complete = true;
float transition_progress = 0.0;
uint32_t transition_start = 0;
uint32_t transition_end = 0;

uint32_t current_frame_duration_us;

bool touch_active = false;

bool freeze_led_image = false;

char character_queue[256] = { 0 };
uint8_t charcter_queue_index = 0;

uint32_t rx_drop_start = 0;
uint32_t rx_drop_end = 0;
int32_t rx_drop_duration = 0;
bool rx_low = false;

uint32_t next_save_time = 0;
bool     settings_updated = false;

bool panic = false;

void debug(uint8_t val){
  if(debug_mode == true){
    Serial.print(val);
  }
}

void debug(uint16_t val){
  if(debug_mode == true){
    Serial.print(val);
  }
}

void debug(uint32_t val){
  if(debug_mode == true){
    Serial.print(val);
  }
}

void debug(int8_t val){
  if(debug_mode == true){
    Serial.print(val);
  }
}

void debug(int16_t val){
  if(debug_mode == true){
    Serial.print(val);
  }
}

void debug(int32_t val){
  if(debug_mode == true){
    Serial.print(val);
  }
}

void debug(float val){
  if(debug_mode == true){
    Serial.print(val);
  }
}

void debug(char val){
  if(debug_mode == true){
    Serial.print(val);
  }
}

void debug(char* val){
  if(debug_mode == true){
    Serial.print(val);
  }
}

void debug(const char* val){
  if(debug_mode == true){
    Serial.print(val);
  }
}

void debugln(uint8_t val){
  if(debug_mode == true){
    Serial.println(val);
  }
}

void debugln(uint16_t val){
  if(debug_mode == true){
    Serial.println(val);
  }
}

void debugln(uint32_t val){
  if(debug_mode == true){
    Serial.println(val);
  }
}

void debugln(int8_t val){
  if(debug_mode == true){
    Serial.println(val);
  }
}

void debugln(int16_t val){
  if(debug_mode == true){
    Serial.println(val);
  }
}

void debugln(int32_t val){
  if(debug_mode == true){
    Serial.println(val);
  }
}

void debugln(float val){
  if(debug_mode == true){
    Serial.println(val);
  }
}

void debugln(char val){
  if(debug_mode == true){
    Serial.println(val);
  }
}

void debugln(char* val){
  if(debug_mode == true){
    Serial.println(val);
  }
}

void debugln(const char* val){
  if(debug_mode == true){
    Serial.println(val);
  }
}
