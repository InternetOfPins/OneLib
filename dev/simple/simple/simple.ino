#include <OneArduino.h>

using namespace OneLib;
using namespace OneLib::Arduino;

unsigned long start;
int duration=10000;
unsigned long test() {
  unsigned long cnt1=0;
  unsigned long cnt2=0;
  start=millis();
  while(millis()-start<duration) {
    pinMode(13,OUTPUT);//arduino mode
    cnt1++;
  }
  start=millis();
  while(millis()-start<duration) {
    Pin<13>::modeOut();//OneArduino mode
    cnt2++;
  }
  Serial.println(cnt1);
  Serial.println(cnt2);
}



void setup() {
  Serial.begin(115200);
  while(!Serial);
  test();
}

void loop() {}
