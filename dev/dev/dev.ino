#include <OneAVR.h>
// #include <Extras.h>

using namespace OneLib;
using namespace OneLib::AtMega328p;
using namespace OneLib::AtMega328p::ArduinoPins;

inline bool tog(int on,int off) {return (millis()%(on+off))<on;}

//static hardware description
typedef Pin<13> Led1;//pin 13 on arduino
typedef Pin<A3> Led2;//pin A3 on arduino
typedef Pin<-4> Btn;//encoder button with pullup (reverse logic)

void setup() {
  // Serial.begin(115200);
  // while(!Serial);
  Led1::modeOut();
  Led2::modeOut();
  Btn::modeInUp();
}

void loop() {
  Led1::set(Btn()?tog(10,90):tog(100,100));
  Led2::set(tog(500,500));
}
