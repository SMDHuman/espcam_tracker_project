#include <Arduino.h>

void serial_init();
void serial_task(void * pvParameters);
void serial_send_slip(uint8_t data);
void serial_send_slip(uint8_t* buf, size_t len);
void serial_send_slip(uint data);
void serial_send_slip(int data);
void serial_send_slip(char data);
void serial_send_slip(String data);
void serial_end_slip();
