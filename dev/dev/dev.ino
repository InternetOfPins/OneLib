#ifdef DEBUG
  #include <streamFlow.h>
#endif
#include <Extras.h>
// #include <OneAVR.h>
#include <OneArduino.h>

#include <Arduino.h>
#include <Print.h>
#include <SPI.h>
#include <Wire.h>
#include <U8g2lib.h>
#include <pcint.h>

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

class Encoder {
  public:
    Encoder(VPinBase& a,VPinBase& b):a(a),b(b) {}
    inline int getPosition() {return pos;}
    void updateA() {
      if (a.logicIn()^b.logicIn()) pos--;
      else pos++;
    }
    void updateB() {
      if (a.logicIn()^b.logicIn()) pos++;
      else pos--;
    }
  protected:
    VPinBase& a;
    VPinBase& b;
    volatile int pos=0;
};

extern Encoder q;
typedef MFunc<Encoder>::With<&q,&Encoder::updateA> EncAUpdate;
typedef MFunc<Encoder>::With<&q,&Encoder::updateB> EncBUpdate;

// void (*updateEncA)()=MFunc<Encoder,void>::With<q,encoderInUpdate>caller;
typedef RecState<OnChange<Debouncer<Pin<2>,1>,EncAUpdate::caller>> EncA;
typedef RecState<OnChange<Debouncer<Pin<3>,1>,EncBUpdate::caller>> EncB;
EncA a_;
EncB b_;
VPin<EncA> a(a_);
VPin<EncB> b(b_);
Encoder q(a,b);

void fx() {Serial<<"got it!"<<endl;};
void (*x)()=Func<void>::With<fx>::caller;

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
  EncA::modeInUp();
  EncB::modeInUp();
  PCattachInterrupt<2>(EncAUpdate::caller,CHANGE);
  PCattachInterrupt<3>(EncBUpdate::caller,CHANGE);
  //auto f=MFunc<Encoder>::With<&q,&Encoder::updateA>::caller;
}

void loop() {
  // a.in();
  // b.in();
  Serial<<q.getPosition()<<endl;
  // digitalWrite(led,btn.in()?tog(10,90):tog(100,100));
  vled.set(vbtn.in()?tog(10,90):tog(100,100));
  // Led::set(tog(500,500));
  u8g2.firstPage();
  do u8g2.drawStr(0,8,"OneLib!");
  while ( u8g2.nextPage() );
}
