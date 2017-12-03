#ifdef DEBUG
  #include <streamFlow.h>
#endif
// #include <Extras.h>
#include <OneAvr.h>
#include <OneArduino.h>
// #include <OneEncoder.h>
#include <OneLib/Button.h>

// #include <Arduino.h>
// #include <Print.h>
// #include <SPI.h>
// #include <Wire.h>
// #include <U8g2lib.h>
#include <pcint.h>

using namespace OneLib;
using namespace OneLib::Arduino;
// using namespace OneLib::Avr;
// using namespace OneLib::Avr::AtMega328p;
// using namespace OneLib::Avr::AtMega328p::ArduinoPins;

// #define USE_HWSPI
// #define U8_DC 9
// #define U8_CS 8
// #define U8_RST 7
// #define fontName u8g2_font_5x7_tf
// U8G2_PCD8544_84X48_1_4W_HW_SPI u8g2(U8G2_R0, U8_CS, U8_DC , U8_RST);

//soft simple PWM like signal function
//the result of this function will toggle
inline bool tog(unsigned int on,unsigned int off) {return (millis()%(on+off))<on;}

// const uint8_t encAccel=6;
// mkEncoder(Encoder<encAccel>,qenc,-2,-3);

typedef RecState<Debouncer<InputPin<-4>,10>> Key4Pin;
Key4Pin key4Pin;
OnePinHook<Key4Pin> key4(key4Pin);
ClickButton<> btn4(key4);

OnePin* pinMap[]={};

// typedef LogicPinBase<ErrorPin<1>,0> test;
// test t;

void setup() {
  Serial.begin(115200);
  while(!Serial);
  Serial<<"Testing OneLib!"<<endl;
  // SPI.begin();
  // u8g2.begin();
  // u8g2.setFont(fontName);
  // u8g2.setColorIndex(1);
  key4.begin();
  // qenc.begin();
  // PCattachInterrupt<2>(Encoder<encAccel>::UpdateA<&qenc>::caller,CHANGE);
  // PCattachInterrupt<3>(Encoder<encAccel>::UpdateB<&qenc>::caller,CHANGE);
  // PCattachInterrupt<4>((void(*)())MFunc<Key4,bool>::With<&key4, &Key4::in >::caller,CHANGE);
}

Stream& operator<<(Stream& o,BtnState s) {
  switch(s) {
    case BtnState::Open: o<<"Open";break;
    case BtnState::Pressed: o<<"Pressed";break;
    case BtnState::Held: o<<"Held";break;
    case BtnState::Released: o<<"Released";break;
    case BtnState::Clicked: o<<"Clicked";break;
    case BtnState::DoubleClicked: o<<"DoubleClicked";break;
    case BtnState::Escape: o<<"Escape";break;
    default: o<<"what?["<<s<<"]";
  }
  return  o;
};

BtnState oldKey=BtnState::Open;
int oldPos=0;
void loop() {
  // int pos=qenc.getPosition();
  // if (pos!=oldPos) {
  //   Serial<<pos<<" "<<endl;
  //   oldPos=pos;
  // }
  // key4.in();
  BtnState key=btn4.get();
  if (oldKey!=key) {
    Serial<<getMillis()<<" key:"<<key<<endl;
    oldKey=key;
  }
  // u8g2.firstPage();
  // do u8g2.drawStr(0,8,"OneLib!");
  // while ( u8g2.nextPage() );
  delay(10);
}
