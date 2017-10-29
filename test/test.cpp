#include "test.h"

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
