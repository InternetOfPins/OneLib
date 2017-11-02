#include <OneLib.h>

//consuming the object with a function
template<class Pin>
inline void blink(int t) {
  Pin::on();
  delay(t);
  Pin::off();
}

//static hardware description
struct AtMega328p {
  typedef Avr::Port<0x23> portB;
  typedef Avr::Port<0x26> portC;
  typedef Avr::Port<0x29> portD;
} mcu;

typedef Avr::Pin<AtMega328p::portB,5> Led;//pin 13 on arduino
typedef Avr::Pin<AtMega328p::portD,-4> EncBtn;//with reverse logic included

EncBtn encBtn;//and object of type EncBtn (can use operators)

void setup() {
  Led::modeOut();
  EncBtn::modeInUp();
}

void loop() {
  if (encBtn) {//converts to bool => reads the pin!
    blink<Led>(10);
    delay(90);
  } else {
    blink<Led>(100);
    delay(100);
  }
}
