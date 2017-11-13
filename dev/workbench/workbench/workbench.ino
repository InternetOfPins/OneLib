#ifdef DEBUG
  #include <streamFlow.h>
#endif
#include <Extras.h>
#include <OneAVR.h>
#include <OneArduino.h>
// #include <OneEncoder.h>

#include <Arduino.h>
#include <Print.h>
#include <SPI.h>
#include <Wire.h>
#include <U8g2lib.h>
#include <pcint.h>

using namespace OneLib;
using namespace OneLib::Arduino;
// using namespace OneLib::Avr;
// using namespace OneLib::Avr::AtMega328p;
// using namespace OneLib::Avr::AtMega328p::ArduinoPins;

#define USE_HWSPI
#define U8_DC 9
#define U8_CS 8
#define U8_RST 7
#define fontName u8g2_font_5x7_tf
U8G2_PCD8544_84X48_1_4W_HW_SPI u8g2(U8G2_R0, U8_CS, U8_DC , U8_RST);

//soft simple PWM like signal function
//the result of this function will toggle
inline bool tog(unsigned int on,unsigned int off) {return (millis()%(on+off))<on;}

// const uint8_t encAccel=6;
// mkEncoder(Encoder<encAccel>,qenc,-2,-3);

enum State:uint8_t {Open = 0,Pressed,Held,Released,Clicked,DoubleClicked,Escape};

template<class O>
class KeyData {
protected:
  bool consume=false;
  State state=Open;
  unsigned long lastCheck=0;
};

template<class O>
class ClickEscapeKey:public O, public virtual KeyData<O>, public virtual LastState {
public:
  unsigned long escape=800;
  static inline void begin() {O::begin();}
  inline State get() {
    Serial<<hex(this)<<" "<<KeyData<O>::state<<endl;
    // Serial<<"get"<<endl;
    // O::in();//updates the state <- NOT! state hooks had to be made external to this in order to have function and object pointers
    if (KeyData<O>::state==Pressed&&millis()-KeyData<O>::lastCheck>escape) {
      Serial<<"get from "<<KeyData<O>::state;
      KeyData<O>::state=Escape;
      Serial<<" to "<<KeyData<O>::state<<endl;
    } else if (!(KeyData<O>::consume||KeyData<O>::state==Open)) {
      Serial<<"get from "<<KeyData<O>::state;
      KeyData<O>::state=Open;
      Serial<<" to "<<KeyData<O>::state<<endl;
    } else KeyData<O>::consume=false;
    return KeyData<O>::state;
  }
  inline void onFall() {
    Serial<<hex(this)<<" onFall from "<<KeyData<O>::state;
    if (KeyData<O>::state==Pressed) KeyData<O>::state=millis()-KeyData<O>::lastCheck>escape?Escape:Clicked;
    KeyData<O>::consume=true;
    Serial<<" to "<<KeyData<O>::state<<endl;
  }
  inline void onRise() {
    Serial<<hex(this)<<" onRise from "<<KeyData<O>::state;
    KeyData<O>::lastCheck=millis();
    KeyData<O>::state=Pressed;
    KeyData<O>::consume=true;
    Serial<<" to "<<KeyData<O>::state<<endl;
  };
  // template<typename res,typename... types>
  // ClickEscapeKey<O> mkFunc(res(ClickEscapeKey<O>::*f)(types...),types... args) {
  //   return MFunc<ClickEscapeKey<O>,res,types...>::template With<ClickEscapeKey<O>,this,args...>::caller;
  // }
};

typedef ClickEscapeKey<Debouncer<InputPin<-4>,30>> Btn;

template<class Btn>
struct Key {
  template<Btn* btn>
  struct With:public RecState<
    OnFall<
      OnRise<Btn,&Btn::onRise>,
      &Btn::onFall
    >
  > {};
};

Btn btn;
typedef Key<Btn>::template With<&btn> Key4;
Key4 key4;

OFunc<Btn,&btn,&Btn::onRise> rise4;

typedef OutputPin<A3> Led;//pin A3 on arduino
Led led;
OnePin<Led> vled(led);

// typedef MFunc<Key4,bool>::template With<&key4,&Key4::in> BtnCall;

void setup() {
  Serial.begin(115200);
  while(!Serial);
  Serial<<"Testing OneLib!"<<endl;
  SPI.begin();
  u8g2.begin();
  u8g2.setFont(fontName);
  u8g2.setColorIndex(1);
  vled.begin();
  key4.begin();
  // qenc.begin();
  // PCattachInterrupt<2>(Encoder<encAccel>::UpdateA<&qenc>::caller,CHANGE);
  // PCattachInterrupt<3>(Encoder<encAccel>::UpdateB<&qenc>::caller,CHANGE);
  // PCattachInterrupt<4>((void(*)())MFunc<Key4,bool>::With<&key4, &Key4::in >::caller,CHANGE);
}

Stream& operator<<(Stream& o,State s) {
  switch(s) {
    case State::Open: o<<"Open";break;
    case State::Pressed: o<<"Pressed";break;
    case State::Held: o<<"Held";break;
    case State::Released: o<<"Released";break;
    case State::Clicked: o<<"Clicked";break;
    case State::DoubleClicked: o<<"DoubleClicked";break;
    case State::Escape: o<<"Escape";break;
    default: o<<"what?["<<s<<"]";
  }
  return  o;
};

State oldKey=State::Open;
int oldPos=0;
void loop() {
  // int pos=qenc.getPosition();
  // if (pos!=oldPos) {
  //   Serial<<pos<<" "<<endl;
  //   oldPos=pos;
  // }
  key4.in();
  State key=key4.get();
  if (oldKey!=key) {
    Serial<<"key:"<<key<<endl;
    oldKey=key;
  }
  // u8g2.firstPage();
  // do u8g2.drawStr(0,8,"OneLib!");
  // while ( u8g2.nextPage() );
  delay(100);
}
