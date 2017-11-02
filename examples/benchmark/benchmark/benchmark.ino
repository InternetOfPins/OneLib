#include <OneLib.h>

#define ENCBTN_PIN -4

//static hardware description
struct AtMega328p {
  typedef Avr::Port<0x23> portB;
  typedef Avr::Port<0x26> portC;
  typedef Avr::Port<0x29> portD;
} mcu;

typedef Avr::Pin<AtMega328p::portB,5> Led;//pin 13 on arduino

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
  Serial.print("Arduino pin mode:");
  Serial.println(test([](){pinMode(13,INPUT);}));
  Serial.print("OneLib pin mode:");
  Serial.println(test([](){Led::modeIn();}));

  Serial.print("Arduino pin input:");
  Serial.println(test([](){digitalRead(13);}));
  Serial.print("OnePin pin input:");
  Serial.println(test([](){Led::in();}));
  // Serial.print("Debounced input:");
  // Serial.println(test([](){pin4.get();}));
}

void setup() {
  Serial.begin(115200);
  while(!Serial);
}

void loop() {
  test();
}
