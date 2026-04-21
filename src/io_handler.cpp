//-----------------------------------------------------------------------------
#include <Arduino.h>
#include "io_handler.h"
#include "tracker.h"
#include "espnet.h"

//-----------------------------------------------------------------------------
uint32_t camera_width;
uint32_t camera_height;

//-----------------------------------------------------------------------------
void io_init(){
  // Initialize builtin led
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, !LOW);
  // Initialize camera
  esp_err_t err = esp_camera_init(&camera_config);
  if(err != ESP_OK){
    Serial.println("Failed to initialize camera!!");
    return;
  }
  // camera_load_default_configs();
  // Get one frame buffer for some information
  camera_fb_t *fb = nullptr;
  while(!fb){
    fb = esp_camera_fb_get();
    delay(10);
  }
  camera_width = fb->width;
  camera_height = fb->height;
  // ???? This line might cause problems
  //esp_camera_fb_return(fb);
}

//-----------------------------------------------------------------------------
void io_task(void * pvParameters){
  while(1) {
    uint64_t task_start = millis();
    camera_fb_t *fb = esp_camera_fb_get(); // get fresh image
    if(!fb){
      vTaskDelay(100);
      continue;
    }
    if(espnet_config.mode == MODE_CLIENT){
      digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    }
    tracker_push_camera_buffer(fb);
    tracker_process();

    esp_camera_fb_return(fb);
    vTaskDelay(1);
  }
}

//-----------------------------------------------------------------------------
// Load configs for camera sensor
// void camera_load_default_configs(){
//   sensor_t *s = esp_camera_sensor_get();
//   s->set_brightness(s, TODO); // -2 to 2
//   s->set_contrast(s, TODO); // -2 to 2
//   s->set_saturation(s, TODO); // -2 to 2
//   s->set_special_effect(s, TODO); // 0 to 7
//   s->set_whitebal(s, TODO); // 0 to 1
//   s->set_awb_gain(s, TODO); // 0 to 1
//   s->set_wb_mode(s, TODO); // 0 to 5
//   s->set_exposure_ctrl(s, TODO); // 0 to 1
//   s->set_aec2(s, TODO); // 0 to 1
//   s->set_ae_level(s, TODO); // -2 to 2
// }
