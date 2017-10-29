#include <OneKey.h>
#include <Arduino.h>

// using namespace RU;

#define ENCBTN_PIN -4

// OneKey<ENCBTN_PIN> btn;

ArduinoPin apin;
Debouncer<ArduinoPin,30> bpin;

void setup() {
  Serial.begin(115200);
  while(!Serial);
  // Serial.print("OneKey test Sz:");
  // Serial.println(sizeof btn);
  // btn.begin();
  apin.modeOut(13);
  //pinMode(4,INPUT_PULLUP);
  bpin.modeInUp(4);
}

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

void loop() {
  Serial.print("Raw mode:");
  Serial.println(test([](){pinMode(2,INPUT);}));
  Serial.print("OnePin mode:");
  Serial.println(test([](){apin.modeIn(2);}));

  Serial.print("Raw input:");
  Serial.println(test([](){digitalRead(2);}));
  Serial.print("OnePin input:");
  Serial.println(test([](){apin.get(2);}));
  Serial.print("Debounced input:");
  Serial.println(test([](){bpin.get(2);}));
}
