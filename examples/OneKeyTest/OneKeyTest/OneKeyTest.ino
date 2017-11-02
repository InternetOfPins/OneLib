
#ifdef DEBUG
  #include <streamFlow.h>
#endif
#include <OneLib/OnePort.h>

// consuming an objects with another
template<class Pin>
struct RevLogic:protected Pin {
  static inline void on() {Pin::off();}
  static inline void off() {Pin::on();}
  static inline bool in() {return !Pin::in();}
};

//consuming the object a function
template<class Pin>
inline void blink(int t) {
  Pin::on();
  delay(t);
  Pin::off();
}

struct AtMega328p {
  typedef Avr::Port<0x23> portB;
  typedef Avr::Port<0x26> portC;
  typedef Avr::Port<0x29> portD;
} mcu;

typedef Avr::Pin<AtMega328p::portB,5> led;//pin 13 on arduino
typedef Avr::Pin<AtMega328p::portD,-4> encBtn;//with reverse logic included

void setup() {
  Serial.begin(115200);
  while(!Serial);
  led::modeOut();
  encBtn::modeInUp();
}

void loop() {
  blink<led>(10);
  if (encBtn::in()) delay(90);
  else delay(990);
}
