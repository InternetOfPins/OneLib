#include "OnePin/Arduino.h"

//negative pin, OnePin will wire reverse logic
#define ENCBTN_PIN -4

ArduinoPin Pin;

void setup() {
  Pin.modeOut(13);
}

void loop() {
  Pin.on(13);
  delay(1000);
  Pin.off(13);
  delay(1000);
}
