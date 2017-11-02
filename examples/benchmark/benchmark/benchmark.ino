#include <OneAVR.h>
#include <OneArduino.h>

using namespace OneLib;

#define ENCBTN_PIN -4

typedef Avr::Pin<AtMega328p::portB,5> Led;//pin 13 on arduino
Led led;
typedef Debouncer<Avr::Pin<AtMega328p::portB,5>,30> Deb13;//pin 13 on arduino
Deb13 deb13;
typedef Arduino::Pin<13> Pin13;
Pin13 pin13;

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
  Serial.print("|Arduino pin mode:|");
  Serial.print(test([](){pinMode(13,INPUT);}));
  Serial.println("|");
  Serial.print("|OneLib Arduino pin mode:|");
  Serial.print(test([](){Pin13::modeIn();}));
  Serial.println("|");
  Serial.print("|OneLib pin mode:|");
  Serial.print(test([](){Led::modeIn();}));
  Serial.println("|");

  Serial.print("|Arduino pin input:|");
  Serial.print(test([](){digitalRead(13);}));
  Serial.println("|");
  Serial.print("|OneLib Arduino pin input:|");
  Serial.print(test([](){pin13.in();}));
  Serial.println("|");
  Serial.print("|OnePin pin input:|");
  Serial.print(test([](){led.in();}));
  Serial.println("|");
  Serial.print("|Debounced input:|");
  Serial.print(test([](){deb13.in();}));
  Serial.println("|");
}

void setup() {
  Serial.begin(115200);
  while(!Serial);
}

void loop() {
  test();
}
