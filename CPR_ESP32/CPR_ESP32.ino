#include "WiFiUtils.h"
#include "irUtils.h"

void setup() {
  Serial.begin (115200);
  irReceiver_init();
  irTransmitter_init();
  WiFi_init();
}

void loop() {
  irReceiver_handler();
  WiFiClient_handler();
}
