#ifdef DEBUG
  #include <streamFlow.h>
#endif
// #include <Extras.h>
// #include <OneAVR.h>
#include <OneArduino.h>

#include <Arduino.h>
#include <Print.h>
#include <SPI.h>
#include <Wire.h>
#include <U8g2lib.h>

using namespace OneLib;
using namespace OneLib::Arduino;
// using namespace OneLib::AtMega328p;
// using namespace OneLib::AtMega328p::ArduinoPins;*----------

// inline void pinMode(const VPinBase& p,uint8_t mode) {p.mode(mode);}
// inline int digitalRead(const VPinBase& p) {return p.in();}
// inline void digitalWrite(const VPinBase& p,uint8_t v) {return p.set(v);}
// inline void pinMode(VPinBase& p,uint8_t mode) {p.mode(mode);}
// inline int digitalRead(VPinBase& p) {return p.in();}
// inline void digitalWrite(VPinBase& p,uint8_t v) {return p.set(v);}

#define USE_HWSPI
#define U8_DC 9
#define U8_CS 8
#define U8_RST 7
#define fontName u8g2_font_5x7_tf
U8G2_PCD8544_84X48_1_4W_HW_SPI u8g2(U8G2_R0, U8_CS, U8_DC , U8_RST);

//soft simple PWM like signal function
//the result of this function will toggle
inline bool tog(unsigned int on,unsigned int off) {return (millis()%(on+off))<on;}

void ok() {Serial<<"Ok";}

//static hardware description
typedef Pin<A3> Led;//pin A3 on arduino
typedef RecState<OnRise<Debouncer<Pin<-4>,30>,ok>> Btn;//encoder button with pullup (reverse logic)
Btn btn;
VPin<Btn> vbtn(btn);
Led led;
VPin<Led> vled(led);

// template<class A,class B>
// class Encoder {
//   public:
//     inline int getPosition() {return pos;}
//     static void encoderInUpdateA() {
//       if (A()::in()^B()::in()) pos--;
//       else pos++;
//     }
//     static void encoderInUpdateB() {
//       if (A()::in()^B()::in()) pos++;
//       else pos--;
//     }
//   protected:
//     volatile int pos=0;
// };

void setup() {
  Serial.begin(115200);
  while(!Serial);
  Serial<<"Testing OneLib!"<<endl;
  SPI.begin();
  u8g2.begin();
  u8g2.setFont(fontName);
  u8g2.setColorIndex(1);
  Led::modeOut();
  Btn::modeInUp();
}

void loop() {
  // digitalWrite(led,btn.in()?tog(10,90):tog(100,100));
  vled.set(vbtn.in()?tog(10,90):tog(100,100));
  // Led::set(tog(500,500));
  u8g2.firstPage();
  do u8g2.drawStr(0,8,"OneLib!");
  while ( u8g2.nextPage() );
}
