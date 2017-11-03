#ifdef DEBUG
  #include <streamFlow.h>
#endif
// #include <Extras.h>
// #include <OneAVR.h>
#include <OneArduino.h>

using namespace OneLib;
using namespace OneLib::Arduino;
// using namespace OneLib::AtMega328p;
// using namespace OneLib::AtMega328p::ArduinoPins;

//soft simple PWM like signal function
//the result of this function will toggle
inline bool tog(int on,int off) {return (millis()%(on+off))<on;}

//static hardware description
typedef Pin<13> Led1;//pin 13 on arduino
typedef Pin<A3> Led2;//pin A3 on arduino
typedef Debouncer<Pin<-4>,30> Btn;//encoder button with pullup (reverse logic)

void setup() {
  Serial.begin(115200);
  while(!Serial);
  Led1::modeOut();
  Led2::modeOut();
  Btn::modeInUp();
}

void loop() {
  Led1::set(Btn()?tog(10,90):tog(100,100));
  Led2::set(tog(500,500));
}
