#include <OneAVR.h>

using namespace OneLib;

template<unsigned int on,unsigned int off>
inline bool tog() {return (millis()%(on+off))<on;}

//static hardware description
typedef Avr::Pin<AtMega328p::portB,5> Led1;//pin 13 on arduino
typedef Avr::Pin<AtMega328p::portC,3> Led2;//pin A3 on arduino

void setup() {
  Led1::modeOut();
  Led2::modeOut();
}

void loop() {
  Led1::set(tog<10,90>());
  Led2::set(tog<500,500>());
}
