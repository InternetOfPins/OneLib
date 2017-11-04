#include <OneAVR.h>
#include <OneArduino.h>

using namespace OneLib;
using namespace OneLib::AtMega328p;
using namespace OneLib::Arduino;

#define ENCBTN_PIN -4

typedef Avr::Pin<PortB,5> Led;//pin 13 on arduino
// Led led;
typedef RecState<Debouncer< LastState<Led>,30>> Deb13;//pin 13 on arduino
// Deb13 deb13;
typedef Pin<13> Pin13;
// Pin13 pin13;

unsigned long cnt;
unsigned long start;
int duration=200;
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
  Serial.println("testing pinMode -------------------");
  Serial.print("|Arduino pin mode:\t\t|");
  Serial.print(test([](){pinMode(13,INPUT);}));
  Serial.print("\t|");
  Serial.println("|");
  Serial.print("|OneLib Arduino mode:\t\t|");
  Serial.print(test([](){Pin13::modeIn();}));
  Serial.print("\t|");
  Serial.print(test([](){RecState<Debouncer<LastState<Pin13>,30>>::modeIn();}));
  Serial.println("|");
  Serial.print("|OneLib AVR pin mode:\t\t|");
  Serial.print(test([](){Led::modeIn();}));
  Serial.print("\t|");
  Serial.print(test([](){RecState<Debouncer<LastState<Led>,30>>::modeIn();}));
  Serial.println("|");
  Serial.print("|OneLib VoidPin mode:\t\t|");
  Serial.print(test([](){VoidPin::modeIn();}));
  Serial.print("\t|");
  Serial.print(test([](){RecState<Debouncer<LastState<VoidPin>,30>>::modeIn();}));
  Serial.println("|");

  Serial.println("testing digitalRead -------------------");
  Serial.print("|Arduino pin input:\t\t|");
  Serial.print(test([](){digitalRead(13);}));
  Serial.print("\t|");
  Serial.println("|");
  Serial.print("|OneLib Arduino input:\t\t|");
  Serial.print(test([](){Pin13().in();}));
  Serial.print("\t|");
  Serial.print(test([](){RecState<Debouncer<LastState<Pin13>,30>>().in();}));
  Serial.println("|");
  Serial.print("|OnePin pin input:\t\t|");
  Serial.print(test([](){Led().in();}));
  Serial.print("\t|");
  Serial.print(test([](){RecState<Debouncer<LastState<Led>,30>>().in();}));
  Serial.println("|");
  Serial.print("|OneLib VoidPin input:\t\t|");
  Serial.print(test([](){VoidPin().in();}));
  Serial.print("\t|");
  Serial.print(test([](){RecState<Debouncer<LastState<VoidPin>,30>>().in();}));
  Serial.println("|");

  Serial.println("testing digitalWrite -------------------");
  Serial.print("|Arduino pin output:\t\t|");
  Serial.print(test([](){digitalWrite(13,0);}));
  Serial.print("\t|");
  Serial.println("|");
  Serial.print("|OneLib Arduino output:\t\t|");
  Serial.print(test([](){Pin13::off();}));
  Serial.print("\t|");
  Serial.print(test([](){RecState<Debouncer<LastState<Pin13>,30>>::off();}));
  Serial.println("|");
  Serial.print("|OnePin pin output:\t\t|");
  Serial.print(test([](){Led::off();}));
  Serial.print("\t|");
  Serial.print(test([](){RecState<Debouncer<LastState<Led>,30>>::off();}));
  Serial.println("|");
  Serial.print("|OneLib VoidPin output:\t\t|");
  Serial.print(test([](){VoidPin::off();}));
  Serial.print("\t|");
  Serial.print(test([](){RecState<Debouncer<LastState<VoidPin>,30>>::off();}));
  Serial.println("|");
}

void setup() {
  Serial.begin(115200);
  while(!Serial);
  test();
}

void loop() {
}
