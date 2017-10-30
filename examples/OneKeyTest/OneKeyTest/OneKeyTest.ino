#include <OnePin/Arduino.h>

//negative pin, OnePin will wire reverse logic
#define ENCBTN_PIN -4

OnePin<PinOutput,ArduinoPin,LED_BUILTIN> led;
OnePin<PinInputUp,Debouncer<ArduinoPin,30>, ENCBTN_PIN> btn;

void setup() {
  Serial.begin(115200);
  while(!Serial);
  led.begin();
  btn.begin();
}

void loop() {
  if (btn.in()) {
    led.on();
    delay(10);
    led.off();
    delay(90);
  } else {
    led.set(!led.in());
    delay(100);
  }
}
