#include <OnePin/Arduino.h>

#define ENCBTN_PIN -4

//pin types
//attach software debouncer to a pin
ArduinoPin Pin;
typedef Debouncer<ArduinoPin,30> SoftDebouncedPin;

//specific pins
OnePin<SoftDebouncedPin,ENCBTN_PIN> pin4;
OnePin<ArduinoPin,13> led;

unsigned long cnt;
unsigned long start;
int duration=2000;
unsigned long test(auto f) {
  cnt=0;
  start=millis();
  while(millis()-start<duration) {
    f();
    cnt++;
  }
  return cnt;
}

void test() {
  Serial.print("Raw mode:");
  Serial.println(test([](){pinMode(4,INPUT);}));
  Serial.print("OnePin mode:");
  Serial.println(test([](){Pin.modeIn(4);}));

  Serial.print("Raw input:");
  Serial.println(test([](){digitalRead(4);}));
  Serial.print("OnePin input:");
  Serial.println(test([](){Pin.get(4);}));
  Serial.print("Debounced input:");
  Serial.println(test([](){pin4.get();}));
}

void setup() {
  Serial.begin(115200);
  while(!Serial);
}

void loop() {
  test();
}
