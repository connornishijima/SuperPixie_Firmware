// Save configuration to LittleFS
void save_config() {
  debug("LITTLEFS: ");
  File file = LittleFS.open("/CONFIG.BIN", FILE_WRITE);
  if (!file) {
    debugln("Failed to open CONFIG.BIN for writing!");
    return;

  } else {
    file.seek(0);
    uint8_t config_buffer[256];
    memcpy(config_buffer, &CONFIG, sizeof(CONFIG));

    for (uint16_t i = 0; i < 256; i++) {
      file.write(config_buffer[i]);
    }
    debugln("WROTE CONFIG.BIN SUCCESSFULLY");
  }
  file.close();
}


// Save configuration to LittleFS 3 seconds from now
// This prevents rapid requests to save from rapidly writing to flash
void save_config_delayed() {
  debugln("CONFIG SAVE QUEUED");
  next_save_time = millis()+3000;
  settings_updated = true;
}


// Load configuration from LittleFS
void load_config() {
  debug("LITTLEFS: ");

  File file = LittleFS.open("/CONFIG.BIN", FILE_READ);
  if (!file) {
    debugln("Failed to open CONFIG.BIN for reading!");
    return;

  } else {
    file.seek(0);
    uint8_t config_buffer[256];
    for (uint16_t i = 0; i < sizeof(CONFIG); i++) {
      config_buffer[i] = file.read();
    }

    memcpy(&CONFIG, config_buffer, sizeof(CONFIG));

    debugln("READ CONFIG SUCCESSFULLY");
  }
  file.close();
}


// Initialize LittleFS
void init_fs() {
  debug("INIT FILESYSTEM: ");
  debugln(LittleFS.begin(true) == true ? PASS : FAIL);

  load_config();
}


// Restore only configuration defaults
void restore_defaults() {
  debug("Deleting CONFIG.BIN: ");

  if (LittleFS.remove("/CONFIG.BIN")) {
    debugln("file deleted");
  } else {
    debugln("delete failed");
  }
}


// This is to prevent overuse of internal flash writes!
// Instead of writing every single setting change to
// LittleFS, we wait until no settings have been altered
// for more than 3 seconds before attempting to update
// the flash with changes. This helps in scenarios where
// you're rapidly cycling through modes for example.
void check_settings(uint32_t t_now_ms) {
  if (settings_updated) {
    if (t_now_ms >= next_save_time) {
      debugln("QUEUED CONFIG SAVE TRIGGERED");
      save_config();
      settings_updated = false;
    }
  }
}