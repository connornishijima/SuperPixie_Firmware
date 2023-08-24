void draw_character_to_temp_mask(float opacity){
  for(uint8_t x = 0; x < LEDS_X; x++){
    for(uint8_t y = 0; y < LEDS_Y; y++){
      temp_mask[y][x] += character_mask[y][x] * opacity;
      if(temp_mask[y][x] > 1.0){
        temp_mask[y][x] = 1.0;
      }
    }
  }
}

void draw_line(float vertices[][2], float x_offset, float y_offset, float x_scale, float y_scale, float angle_deg) {
  uint16_t num_vertices = 2;

  if (x_offset >= -7.0 && x_offset <= 7.0) {
    if (y_offset >= -15.0 && y_offset <= 15.0) {
      y_scale *= -1.0;
      y_offset *= -1.0;

      // Line thickness
      float stroke_width = 1.0;                     // Alter this
      float stroke_width_inv = 1.0 / stroke_width;  // Don't alter this

      angle_deg = fmod(angle_deg, 360.0);

      // How wide of a neighborhood each checked position should have
      int16_t search_width = 1;

      // Used to store bounding box of final shape
      float min_x = LEDS_X;  // Will shrink to polygon bounds later in this function
      float min_y = LEDS_Y;
      float max_x = -LEDS_X;
      float max_y = -LEDS_Y;

      // Iterate over all vertices of the polygon
      for (uint16_t vert = 0; vert < num_vertices - 1; vert++) {
        float vert_x1 = vertices[vert][0] * x_scale;
        float vert_y1 = vertices[vert][1] * y_scale;
        float vert_x2 = vertices[vert + 1][0] * x_scale;
        float vert_y2 = vertices[vert + 1][1] * y_scale;

        float rotated_x1, rotated_y1, rotated_x2, rotated_y2;
        if (angle_deg == 0.0000) {
          // Preserve verts if no rotation needed
          rotated_x1 = vert_x1;
          rotated_y1 = vert_y1;
          rotated_x2 = vert_x2;
          rotated_y2 = vert_y2;
        } else {
          // Convert angle from degrees to radians
          float angle_rad = angle_deg * M_PI / 180.0;
          //angle_rad *= -1.0;

          // Rotate verts (More computationally expensive)
          rotated_x1 = vert_x1 * cos(angle_rad) - vert_y1 * sin(angle_rad);
          rotated_y1 = vert_x1 * sin(angle_rad) + vert_y1 * cos(angle_rad);
          rotated_x2 = vert_x2 * cos(angle_rad) - vert_y2 * sin(angle_rad);
          rotated_y2 = vert_x2 * sin(angle_rad) + vert_y2 * cos(angle_rad);
        }

        // Line start coord
        float x_start = rotated_x1 + x_offset + 3;
        float y_start = rotated_y1 + y_offset + 7;

        // Line end coord
        float x_end = rotated_x2 + x_offset + 3;
        float y_end = rotated_y2 + y_offset + 7;

        /*
        if (x_start < 0) { x_start = 0; }
        if (y_start < 0) { y_start = 0; }
        if (x_end < 0) { x_end = 0; }
        if (y_end < 0) { y_end = 0; }

        if (x_start > LEDS_X - 1) { x_start = LEDS_X - 1; }
        if (y_start > LEDS_Y - 1) { y_start = LEDS_Y - 1; }
        if (x_end > LEDS_X - 1) { x_end = LEDS_X - 1; }
        if (y_end > LEDS_Y - 1) { y_end = LEDS_Y - 1; }
        */

        // Get exact length of line segment
        float vert_x_diff = x_end - x_start;
        float vert_y_diff = y_end - y_start;
        float line_segment_length = sqrt((vert_x_diff * vert_x_diff) + (vert_y_diff * vert_y_diff));

        // Convert line length to integer number of iterations drawing will take, with at least one step per line
        // This way, a line that stretches 7 pixels in the x or y axis will never have less than 8 drawing steps to avoid gaps while avoiding redundant work
        uint16_t num_steps = line_segment_length + 1;
        if (num_steps < 1) {
          num_steps = 1;
        }

        // Amount to increment along the line on each step
        float step_size = 1.0 / num_steps;

        // Iterate over length of line segment for num_steps
        float progress = 0.0;
        for (uint16_t step = 0; step <= num_steps; step++) {
          float brightness = 1.0;

          if (line_segment_length <= 1.0) {
            brightness = line_segment_length;
          }

          // Get exact intermediate position along line
          float x_step_pos = x_start * (1.0 - progress) + x_end * progress;
          float y_step_pos = y_start * (1.0 - progress) + y_end * progress;

          for (int16_t y_led = y_step_pos - 1; y_led < y_step_pos + 1; y_led++) {
            for (int16_t x_led = x_step_pos - 1; x_led < x_step_pos + 1; x_led++) {
              if (x_led >= 0 && x_led < LEDS_X) {
                if (y_led >= 0 && y_led < LEDS_Y) {

                  // Calculate distance between currently searched pixel and exact position of line step point
                  float x_diff = fabs(x_led - x_step_pos);
                  float y_diff = fabs(y_led - y_step_pos);
                  float distance_to_line = sqrt((x_diff * x_diff) + (y_diff * y_diff));

                  if (distance_to_line <= 1.0) {
                    float output = (1.0 - distance_to_line) * brightness;
                    output = (output * 0.5) + (output * output * 0.5);
                    character_mask[y_led][x_led] += output;
                    if (character_mask[y_led][x_led] > 1.0) {
                      character_mask[y_led][x_led] = 1.0;
                    }
                  }
                }
              }
            }
          }

          // Move one step forward along the line
          progress += step_size;
        }
      }
    }
  }
}

void parse_vector_from_bytes(uint8_t *input_data, int16_t offset, float pos_x, float pos_y, float scale_x, float scale_y, float rotation) {
  const uint8_t header_length = 6;

  int16_t num_bytes = (input_data[offset + 0] << 8) + input_data[offset + 1];
  int16_t num_verts = (input_data[offset + 2] << 8) + input_data[offset + 3];
  int16_t num_lines = (input_data[offset + 4] << 8) + input_data[offset + 5];

  /*
  Serial.print("NUM_BYTES: ");
  Serial.println(num_bytes);

  Serial.print("NUM_VERTS: ");
  Serial.println(num_verts);

  Serial.print("NUM_LINES: ");
  Serial.println(num_lines);
  */

  uint16_t lines_start_offset = header_length + num_verts * 4;

  for (int16_t i = lines_start_offset; i < num_bytes; i += 4) {
    int16_t line_start = (input_data[offset + i + 0] << 8) + input_data[offset + i + 1];
    int16_t line_end = (input_data[offset + i + 2] << 8) + input_data[offset + i + 3];

    int16_t line_start_vertex_offset = header_length + (4 * line_start);
    int16_t start_coord_x_int = (input_data[offset + line_start_vertex_offset + 0] << 8) + input_data[offset + line_start_vertex_offset + 1];
    int16_t start_coord_y_int = (input_data[offset + line_start_vertex_offset + 2] << 8) + input_data[offset + line_start_vertex_offset + 3];

    int16_t line_end_vertex_offset = header_length + (4 * line_end);
    int16_t end_coord_x_int = (input_data[offset + line_end_vertex_offset + 0] << 8) + input_data[offset + line_end_vertex_offset + 1];
    int16_t end_coord_y_int = (input_data[offset + line_end_vertex_offset + 2] << 8) + input_data[offset + line_end_vertex_offset + 3];

    float start_coord_x = start_coord_x_int / 100.0;
    float start_coord_y = start_coord_y_int / 100.0;

    float end_coord_x = end_coord_x_int / 100.0;
    float end_coord_y = end_coord_y_int / 100.0;

    float verts[2][2] = {
      { start_coord_x, start_coord_y },
      { end_coord_x, end_coord_y },
    };

    //draw_poly_stroke(verts, 2, pos_x, pos_y, scale_x, scale_y, rotation, opacity);
    draw_line(verts, pos_x, pos_y, scale_x, scale_y, rotation);
  }
}

void draw_character(character CHAR, float character_opacity) {
  float pos_x = CHAR.pos_x;
  float pos_y = CHAR.pos_y;
  float scale_x = CHAR.scale_x * DEVICE.CHARACTER_SCALE;
  float scale_y = CHAR.scale_y * DEVICE.CHARACTER_SCALE;
  float rotation = CHAR.rotation;
  float opacity = CHAR.opacity * DEVICE.MASTER_OPACITY * character_opacity;

  char c = CHAR.character;
  int32_t address = lookup_ascii_address(c);

  memset(character_mask, 0, sizeof(float)*LEDS_X*LEDS_Y);

  if (address == -1) { 
    // Fall back to ' ' character if bad ascii address
    parse_vector_from_bytes(ascii_font, 0, 0, 0, 1.0, 1.0, 0.0);
    opacity = 0.0000001;
  } else {
    parse_vector_from_bytes(ascii_font, address, pos_x, pos_y, scale_x, scale_y, rotation);
  }

  draw_character_to_temp_mask(opacity);
}