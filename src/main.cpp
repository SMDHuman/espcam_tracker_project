#include <Arduino.h>
#include <freertos/task.h>
#include "serial_handler.h"
#include "io_handler.h"
#include "espnet.h"
// #include "tracker.h"

// ----------------------------------------------------------------------------
void setup() {
  //... 
  io_init();
  serial_init();
  espnet_init();
  // tracker_init();
  // config_reload();
  //... 
  xTaskCreatePinnedToCore(espnet_task, "ESP-NET", 8192, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(serial_task, "Serial", 8192, NULL, 1, NULL, 0);
}

// ----------------------------------------------------------------------------
void loop() {
  io_task(0);
}
