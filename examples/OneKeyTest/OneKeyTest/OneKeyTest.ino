#include "OnePin/Arduino.h"

//negative pin, OnePin will wire reverse logic
#define ENCBTN_PIN -4

const OnePin<ArduinoPin,13> led;

void setup() {
  led.modeOut();
}

void loop() {
  led.on();
  delay(1000);
  led.off();
  delay(1000);
}
