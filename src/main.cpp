#include <Arduino.h>
#include <freertos/task.h>
#include "serial_handler.h"
#include "io_handler.h"
#include "espnet.h"
#include "tracker.h"

// ----------------------------------------------------------------------------
void setup() {
  // Initialize all components
  serial_init();
  io_init();
  espnet_init();
  // Start tasks for each component
  xTaskCreatePinnedToCore(espnet_task, "ESP-NET", 8192, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(serial_task, "Serial", 8192, NULL, 1, NULL, 0);
}

// ----------------------------------------------------------------------------
void loop() {
  // The main loop is reserved for the IO task, which handles camera input and processing
  io_task(0);
}
