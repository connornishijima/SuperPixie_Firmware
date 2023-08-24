extern void blink();
extern void show(uint32_t t_now);
extern void enable_fast_mode();
extern void disable_fast_mode();
extern void set_config_defaults();
extern void set_new_baud_rate(uint32_t new_baud);
extern void serial_delay(uint16_t del_ms);

void set_new_character(uint8_t c) {
  if (transition_complete == true) {
    if (c != DEVICE.CURRENT_CHARACTER.character || CONFIG.FORCE_TRANSITION == true) {
      DEVICE.NEW_CHARACTER.character = c;
      debug("NEW CHAR: ");
      debugln(DEVICE.NEW_CHARACTER.character);
    }
  } else {
    debugln("NOT DONE TRANSITIONING");
  }
}

// Send command packet to broadcast or a specific address
void send_packet(uint8_t dest_address, uint32_t packet_id, uint16_t packet_type, uint8_t* data, uint8_t data_length_in_bytes) {
  uint8_t packet_temp[256] = { 0 };

  // Packet header
  packet_temp[0] = SYNC_PATTERN_1;
  packet_temp[1] = SYNC_PATTERN_2;
  packet_temp[2] = SYNC_PATTERN_3;
  packet_temp[3] = SYNC_PATTERN_4;

  // 16-bit Packet ID as 2 bytes
  packet_temp[4] = get_byte_from_uint16(packet_id, 1);
  packet_temp[5] = get_byte_from_uint16(packet_id, 0);

  // Origin address
  packet_temp[6] = DEVICE.LOCAL_ADDRESS;

  // Destination node, unless ADDRESS_BROADCAST
  packet_temp[7] = dest_address;

  // First hop address, starts as ADDRESS_NULL
  packet_temp[8] = ADDRESS_NULL;

  // Flags
  packet_temp[9] = 0;

  // 16-bit Packet command type as 2 bytes
  packet_temp[10] = get_byte_from_uint16(packet_type, 1);
  packet_temp[11] = get_byte_from_uint16(packet_type, 0);

  // How many bytes of extra data does this command have?
  packet_temp[12] = data_length_in_bytes;

  // The extra data content, if any
  for (uint16_t i = 0; i < data_length_in_bytes; i++) {
    packet_temp[13 + i] = data[i];
  }

  chain_left.write(packet_temp, 13 + data_length_in_bytes);
  chain_left.flush();
}

// Sends an ACK back for a specific packet ID
void send_ack(uint16_t packet_id) {
  debug("Sending ACK for Packet ID ");
  debugln(packet_id);
  send_packet(ADDRESS_COMMANDER, packet_id, COM_ACK, NULL_DATA, 0);
}

// Sends an ACK back for a specific packet ID
void send_touch_event() {
  uint8_t touch_data[1] = { DEVICE.TOUCH_ACTIVE };
  send_packet(ADDRESS_COMMANDER, 0, COM_TOUCH_EVENT, touch_data, 1);

  debug("SENDING TOUCH EVENT: ");
  debugln(touch_data[0]);
}

void execute_packet(uint32_t t_now, uint8_t* buffer, uint16_t packet_id, uint16_t packet_type, bool needs_ack, uint8_t data_length_in_bytes, uint8_t data_start_position) {
  if (packet_type == COM_PROBE) {
    send_ack(packet_id);
  }

  else if (packet_type == COM_BLINK) {
    debugln("GOT BLINK PACKET");
    blink();
  }

  else if (packet_type == COM_RESET_CHAIN) {
    debugln("GOT COM_RESET_CHAIN");
    set_config_defaults();
    disable_fast_mode();
  }

  else if (packet_type == COM_ENABLE_PROPAGATION) {
    chain_right.begin(DEFAULT_CHAIN_BAUD, SERIAL_8N1, SERIAL_0_RX_GPIO, SERIAL_0_TX_GPIO);
    
    if(debug_mode == false){
      DEVICE.PROPAGATION = true;
      enable_fast_mode();
    }

    send_ack(packet_id);

    debugln("GOT COM_ENABLE_PROPAGATION");
  }

  else if (packet_type == COM_ASSIGN_ADDRESS) {
    DEVICE.LOCAL_ADDRESS = buffer[data_start_position + 0];
    panic = false;
    send_ack(packet_id);

    debug("GOT COM_ASSIGN_ADDRESS (");
    debug(DEVICE.LOCAL_ADDRESS);
    debugln(")");
  }

  else if (packet_type == COM_SET_BAUD) {
    uint32_t new_baud = 0;
    new_baud = (new_baud << 8) + buffer[data_start_position + 0];
    new_baud = (new_baud << 8) + buffer[data_start_position + 1];
    new_baud = (new_baud << 8) + buffer[data_start_position + 2];
    new_baud = (new_baud << 8) + buffer[data_start_position + 3];

    debug("| ");
    debugln( buffer[data_start_position + 0] );
    debug("| ");
    debugln( buffer[data_start_position + 1] );
    debug("| ");
    debugln( buffer[data_start_position + 2] );
    debug("| ");
    debugln( buffer[data_start_position + 3] );

    debug("GOT COM_SET_BAUD (");
    debug(new_baud);
    debugln(")");

    set_new_baud_rate(new_baud);

    delay(100);

    debug("NEW BAUD ENABLED: ");
    debugln(chain_left.baudRate());
  }

  else if (packet_type == COM_SET_DEBUG_LED) {
    DEVICE.DEBUG_LED = buffer[data_start_position + 0];

    debug("GOT COM_SET_DEBUG_LED (");
    debug(DEVICE.DEBUG_LED);
    debugln(")");
  }

  else if (packet_type == COM_SET_DEBUG_DIGIT) {
    char new_char = buffer[data_start_position + 0];
    set_new_character(new_char);

    debug("GOT COM_SET_DEBUG_DIGIT (");
    debug(new_char);
    debugln(")");
  }

  else if (packet_type == COM_SET_BRIGHTNESS) {
    CONFIG.BRIGHTNESS = buffer[data_start_position + 0];
    FastLED.setBrightness(CONFIG.BRIGHTNESS);

    save_config_delayed();

    debug("GOT COM_SET_BRIGHTNESS (");
    debug(CONFIG.BRIGHTNESS);
    debugln(")");
  }

  else if (packet_type == COM_SET_COLORS) {
    CONFIG.DISPLAY_COLOR_A.r = buffer[data_start_position + 0];
    CONFIG.DISPLAY_COLOR_A.g = buffer[data_start_position + 1];
    CONFIG.DISPLAY_COLOR_A.b = buffer[data_start_position + 2];

    CONFIG.DISPLAY_COLOR_B.r = buffer[data_start_position + 3];
    CONFIG.DISPLAY_COLOR_B.g = buffer[data_start_position + 4];
    CONFIG.DISPLAY_COLOR_B.b = buffer[data_start_position + 5];

    save_config_delayed();

    debug("GOT COM_SET_COLORS (");
    debug(CONFIG.DISPLAY_COLOR_A.r);
    debug(", ");
    debug(CONFIG.DISPLAY_COLOR_A.g);
    debug(", ");
    debug(CONFIG.DISPLAY_COLOR_A.b);
    debug(", ");
    debug(CONFIG.DISPLAY_COLOR_B.r);
    debug(", ");
    debug(CONFIG.DISPLAY_COLOR_B.g);
    debug(", ");
    debug(CONFIG.DISPLAY_COLOR_B.b);
    debugln(")");
  }

  else if (packet_type == COM_SHOW) {
    show(t_now);

    debugln("GOT COM_SHOW");
  }

  else if (packet_type == COM_SEND_STRING) {
    char new_char = buffer[data_start_position + DEVICE.LOCAL_ADDRESS];
    set_new_character(new_char);

    debug("GOT COM_SEND_STRING (");
    debug(new_char);
    debugln(")");
  }

  else if (packet_type == COM_SET_TRANSITION_TYPE) {
    uint8_t new_type = buffer[data_start_position + 0];
    CONFIG.TRANSITION_TYPE = new_type;

    save_config_delayed();

    debug("GOT COM_SET_TRANSITION_TYPE (");
    debug(new_type);
    debugln(")");
  }

  else if (packet_type == COM_SET_TRANSITION_DURATION_MS) {
    uint8_t new_duration_high = buffer[data_start_position + 0];
    uint8_t new_duration_low = buffer[data_start_position + 1];
    uint16_t new_duration = (new_duration_high << 8) + new_duration_low;
    CONFIG.TRANSITION_DURATION_MS = new_duration;

    save_config_delayed();

    debug("GOT COM_SET_TRANSITION_DURATION_MS (");
    debug(new_duration);
    debugln(")");
  }

  else if (packet_type == COM_SET_FRAME_BLENDING) {
    float blend_val = buffer[data_start_position + 0] / 255.0;  // 8-bit to float
    CONFIG.FRAME_BLENDING = blend_val;

    save_config_delayed();

    debug("GOT COM_SET_FRAME_BLENDING (");
    debug(blend_val);
    debugln(")");
  }

  else if (packet_type == COM_SET_FX_COLOR) {
    CONFIG.FX_COLOR.r = buffer[data_start_position + 0];
    CONFIG.FX_COLOR.g = buffer[data_start_position + 1];
    CONFIG.FX_COLOR.b = buffer[data_start_position + 2];

    save_config_delayed();

    debug("GOT COM_SET_FX_COLOR (");
    debug(CONFIG.FX_COLOR.r);
    debug(", ");
    debug(CONFIG.FX_COLOR.g);
    debug(", ");
    debug(CONFIG.FX_COLOR.b);
    debugln(")");
  }

  else if (packet_type == COM_SET_FX_OPACITY) {
    float opacity_val = buffer[data_start_position + 0] / 255.0;  // 8-bit to float
    CONFIG.FX_OPACITY = opacity_val;

    save_config_delayed();

    debug("GOT COM_SET_FX_OPACITY (");
    debug(opacity_val);
    debugln(")");
  }

  else if (packet_type == COM_SET_FX_BLUR) {
    float blur_val = buffer[data_start_position + 0] / 25.5;  // 8-bit to float range of 0.0 - 10.0
    CONFIG.FX_BLUR = blur_val;

    save_config_delayed();

    debug("GOT COM_SET_FX_BLUR (");
    debug(blur_val);
    debugln(")");
  }

  else if (packet_type == COM_SET_GRADIENT_TYPE) {
    uint8_t gradient_type = buffer[data_start_position + 0];
    CONFIG.GRADIENT_TYPE = gradient_type;

    save_config_delayed();

    debug("GOT COM_SET_GRADIENT_TYPE (");
    debug(gradient_type);
    debugln(")");
  }

  else if (packet_type == COM_FORCE_TRANSITION) {
    bool state = buffer[data_start_position + 0];
    CONFIG.FORCE_TRANSITION = state;

    save_config_delayed();

    debug("GOT COM_FORCE_TRANSITION (");
    debug(state);
    debugln(")");
  }

  else if (packet_type == COM_SCROLL_STRING) {
    uint8_t TRANSITION_TYPE_TEMP = CONFIG.TRANSITION_TYPE;
    uint8_t TRANSITION_DURATION_MS_TEMP = CONFIG.TRANSITION_DURATION_MS;

    CONFIG.TRANSITION_TYPE = TRANSITION_PUSH_LEFT;
    CONFIG.TRANSITION_DURATION_MS = CONFIG.SCROLL_TIME_MS;

    uint32_t del_time = CONFIG.SCROLL_TIME_MS + CONFIG.SCROLL_HOLD_TIME_MS;

    for(uint8_t i = 0; i < (CONFIG.CHAIN_LENGTH-1) - DEVICE.LOCAL_ADDRESS; i++){
      set_new_character(' ');
      show(micros());
      serial_delay(del_time);
    }

    for(uint8_t i = 0; i < data_length_in_bytes; i++){
      set_new_character(buffer[data_start_position + i]);
      show(micros());
      serial_delay(del_time);
    }

    for(uint8_t i = 0; i < DEVICE.LOCAL_ADDRESS; i++){
      set_new_character(' ');
      show(micros());
      serial_delay(del_time);
    }

    set_new_character(' ');
    show(micros());
    serial_delay(CONFIG.TRANSITION_DURATION_MS);
    
    CONFIG.TRANSITION_TYPE = TRANSITION_TYPE_TEMP;
    CONFIG.TRANSITION_DURATION_MS = TRANSITION_DURATION_MS_TEMP;
  }

  else if (packet_type == COM_SET_CHAIN_LENGTH) {
    CONFIG.CHAIN_LENGTH = buffer[data_start_position + 0];

    save_config_delayed();

    debug("GOT COM_SET_CHAIN_LENGTH (");
    debug(CONFIG.CHAIN_LENGTH);
    debugln(")");
  }

  else if (packet_type == COM_SET_SCROLL_SPEED) {
    uint8_t SCROLL_TIME_MS_HIGH = buffer[data_start_position + 0];
    uint8_t SCROLL_TIME_MS_LOW = buffer[data_start_position + 1];

    uint8_t SCROLL_HOLD_TIME_MS_HIGH = buffer[data_start_position + 2];
    uint8_t SCROLL_HOLD_TIME_MS_LOW = buffer[data_start_position + 3];

    CONFIG.SCROLL_TIME_MS = (SCROLL_TIME_MS_HIGH << 8) + SCROLL_TIME_MS_LOW;
    CONFIG.SCROLL_HOLD_TIME_MS = (SCROLL_HOLD_TIME_MS_HIGH << 8) + SCROLL_HOLD_TIME_MS_LOW;

    save_config_delayed();

    debug("GOT COM_SET_SCROLL_SPEED (");
    debug(CONFIG.SCROLL_TIME_MS);
    debug(", ");
    debug(CONFIG.SCROLL_HOLD_TIME_MS);
    debugln(")");
  }

  else if (packet_type == COM_GET_READY_STATUS) {
    debug("GOT COM_GET_READY_STATUS (");
    debug(DEVICE.READY);
    debugln(")");

    uint8_t data[1] = { DEVICE.READY };

    send_packet(ADDRESS_COMMANDER, packet_id, COM_READY_STATUS, data, 1);
  }

  else if (packet_type == COM_HOLD_IMAGE) {
    freeze_led_image = true;
  }

  else if (packet_type == COM_GET_TOUCH_STATE) {
    DEVICE.TOUCH_VAL = touchRead(TOUCH_PIN);

    bool touching = false;
    if (DEVICE.TOUCH_VAL <= CONFIG.TOUCH_THRESHOLD) {
      touching = true;
    }

    uint8_t touch_data[1] = {touching};

    send_packet(ADDRESS_COMMANDER, -1, COM_TOUCH_STATE, touch_data, 1);
  }

  else if (packet_type == COM_ENABLE_FAST_MODE) {
    //chain_left.flush();
    //chain_right.flush();
    //chain_right.end();

    //delay(25);

    //enable_fast_mode();
  }
}

void feed_byte_into_packet_buffer(uint8_t incoming_byte) {
  packet_buffer[packet_buffer_index] = incoming_byte;
  //debug("packet_buffer[");
  //debug(packet_buffer_index);
  //debug("] = ");
  //debugln(incoming_byte);

  packet_buffer_index++;
}

void feed_byte_into_return_packet_buffer(uint8_t incoming_byte) {
  return_packet_buffer[return_packet_buffer_index] = incoming_byte;
  debug("return_packet_buffer[");
  debug(return_packet_buffer_index);
  debug("] = ");
  debugln(incoming_byte);

  return_packet_buffer_index++;
}

// Quickly shifts sync buffer left using memmove,
// Adds newest byte at end
void feed_byte_into_sync_buffer(uint8_t incoming_byte) {
  memmove(sync_buffer, sync_buffer + 1, (4 - 1) * sizeof(uint8_t));
  sync_buffer[3] = incoming_byte;
}

// Quickly shifts return_sync_buffer left using memmove,
// Adds newest byte at end
void feed_byte_into_return_sync_buffer(uint8_t incoming_byte) {
  memmove(return_sync_buffer, return_sync_buffer + 1, (4 - 1) * sizeof(uint8_t));
  return_sync_buffer[3] = incoming_byte;
}

// Once packet bounds within the buffer are known,
// it can be parsed and executed
void decode_packet(uint32_t t_now, uint8_t* buffer, uint8_t start_index) {
  // 16-bit ID of this packet for ACK use
  uint8_t id_a = buffer[start_index + 0];
  uint8_t id_b = buffer[start_index + 1];

  // Parse 2 bytes into 16-bit
  uint16_t packet_id = 0;
  packet_id = (packet_id << 8) + id_a;
  packet_id = (packet_id << 8) + id_b;

  // Address this packet came from
  uint8_t origin_address = buffer[start_index + 2];

  // Address this packet is intended for
  uint8_t dest_address = buffer[start_index + 3];

  // Address this packet is intended for
  uint8_t first_hop_address = buffer[start_index + 4];

  // Boolean flags
  uint8_t packet_flags = buffer[start_index + 5];

  // Command type of packet
  uint8_t packet_type_high = buffer[start_index + 6];
  uint8_t packet_type_low = buffer[start_index + 7];
  uint16_t packet_type = (packet_type_high << 8) + packet_type_low;

  // Was an ACK requested?
  bool needs_ack = bitRead(packet_flags, 7);

  // How many bytes of extra data does this command have?
  uint8_t data_length_in_bytes = buffer[start_index + 8];

  // This is where that extra data begins:
  uint8_t data_start_position = start_index + 9;

  /*
  debug("ID: ");
  debug(packet_id);
  debug("\t SIZE: ");
  debug(packet_size);
  debug("\t DEST ADDRESS: ");
  debug(dest_address);
  debug("\t PACKET TYPE: ");
  debug(packet_type);
  debug("\t DATA_LENGTH: ");
  debug(data_length_in_bytes);
  */

  bool send_panic = false;

  if (dest_address == ADDRESS_BROADCAST){
    if(DEVICE.LOCAL_ADDRESS != ADDRESS_NULL){
      //debugln("BROADCAST PACKET");
      execute_packet(t_now, buffer, packet_id, packet_type, needs_ack, data_length_in_bytes, data_start_position);
    }
    else{
      send_panic = true;
    }
  }
  else if (dest_address == DEVICE.LOCAL_ADDRESS){
    //debugln("LOCAL PACKET");
    execute_packet(t_now, buffer, packet_id, packet_type, needs_ack, data_length_in_bytes, data_start_position);
  }
  else{ // If not addressed to us at all
    //debugln("PACKET NOT FOR ME!");
    if(DEVICE.LOCAL_ADDRESS == ADDRESS_NULL){
      send_panic = true;
      // If we have ADDRESS_NULL and a packet arrives not addressed to ADDRESS_NULL,
      // this node must have de-synced from the chain and is now orphaned.
      // Send a panic signal up the chain to initiate recovery      
    }
  }

  if(DEVICE.LOCAL_ADDRESS != ADDRESS_NULL && DEVICE.PROPAGATION == false){
    if(debug_mode == false){
      DEVICE.PROPAGATION = true;
      enable_fast_mode();
    }
  }

  if(send_panic == true && panic == false){
    panic = true;
    send_packet(ADDRESS_COMMANDER, -1, COM_PANIC, NULL_DATA, 0);
    debugln("NODE PANIC!");
  }

  //digitalWrite(2, LOW);    
}

void init_packet() {
  memset(packet_buffer, 0, sizeof(uint8_t) * 256);
  packet_buffer_index = 0;
  packet_started = true;
  packet_got_header = false;
  packet_read_counter = 9;
}

void init_return_packet() {
  memset(return_packet_buffer, 0, sizeof(uint8_t) * 256);
  return_packet_buffer_index = 0;
  return_packet_started = true;
  return_packet_got_header = false;
  return_packet_read_counter = 9;
}

void parse_packet(uint32_t t_now) {
  decode_packet(t_now, packet_buffer, 0);
}

void parse_return_packet(uint32_t t_now) {
  decode_packet(t_now, return_packet_buffer, 0);
}

void announce_to_chain() {
  send_packet(ADDRESS_COMMANDER, -1, COM_ANNOUNCE, NULL_DATA, 0);
}
