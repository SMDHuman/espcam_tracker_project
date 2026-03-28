#include <Arduino.h>
#include <freertos/task.h>
#include "serial_handler.h"
#include "io_handler.h"
#include "espnet.h"
#include "tracker.h"

// ----------------------------------------------------------------------------
void setup() {
  // Initialize Serial
  Serial.begin(115200);
  // Initialize builtin led
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, !LOW);
  //... 
  serial_init();
  io_init();
  espnet_init();
  //... 
  xTaskCreatePinnedToCore(espnet_task, "ESP-NET", 8192, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(serial_task, "Serial", 8192, NULL, 1, NULL, 0);
}

// ----------------------------------------------------------------------------
void loop() {
  io_task(0);
}
