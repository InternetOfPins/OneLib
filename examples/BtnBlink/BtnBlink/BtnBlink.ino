#ifdef DEBUG
  #include <streamFlow.h>
#endif

#include <OneAVR.h>

using namespace OneLib;
using namespace OneLib::Avr;
using namespace OneLib::Avr::AtMega328p;

//static hardware description
typedef Pin<PortB,5> Led;//pin 13 on arduino
typedef Pin<PortD,-4> EncBtn;//with reverse logic included

void setup() {
  Led::modeOut();
  EncBtn::modeInUp();
}

//toggles on/off as specified in ms
inline bool tog(unsigned int on,unsigned int off) {return (millis()%(on+off))<on;}

//blink with no delay
void loop() {
  if (EncBtn()) Led::set(tog(10,90));
  else Led::set(tog(100,100));
}
