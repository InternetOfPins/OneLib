#include "OnePin/Arduino.h"

//negative pin, OnePin will wire reverse logic
#define ENCBTN_PIN -4

//pin types
//attach software debouncer to a pin
typedef Debouncer<ArduinoPin,30> SoftDebouncedPin;

//specific pins
OnePin<SoftDebouncedPin,ENCBTN_PIN> pin4;
OnePin<ArduinoPin,13> led;

void setup() {
  pin4.modeInUp();
  led.modeOut();
}

void loop() {
  if (pin4.get()) {
    led.on();
    delay(10);
  }
  led.off();
  delay(90);
}
