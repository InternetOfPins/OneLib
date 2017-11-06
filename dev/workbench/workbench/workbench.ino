#ifdef DEBUG
  #include <streamFlow.h>
#endif
#include <Extras.h>
#include <OneAVR.h>
#include <OneArduino.h>

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

void ok() {Serial<<"ok"<<endl;}

//static hardware description
typedef RecState<OnRise<Debouncer<InputPin<-4>,30>,ok>> Btn;//encoder button with pullup (reverse logic)
Btn btn;
OnePin<Btn> vbtn(btn);

typedef OutputPin<A3> Led;//pin A3 on arduino
Led led;
OnePin<Led> vled(led);

class Encoder {
  public:
    Encoder(VPinBase& a,VPinBase& b):a(a),b(b) {}
    void begin() {
      a.begin();
      b.begin();
    }
    inline int getPosition() {return pos;}
    void updateA() {
      if (a.logicIn()^b.logicIn()) pos--;
      else pos++;
    }
    void updateB() {
      if (a.logicIn()^b.logicIn()) pos++;
      else pos--;
    }

    template<Encoder *enc>
    using UpdateA = MFunc<Encoder>::With<enc,&Encoder::updateA>;

    template<Encoder *enc>
    using UpdateB = MFunc<Encoder>::With<enc,&Encoder::updateB>;

    template<Encoder *enc,class O,uint8_t deb=1>
    using PinA=RecState<OnChange<O,UpdateA<enc>::caller>>;

    template<Encoder *enc,class O,uint8_t deb=1>
    using PinB=RecState<OnChange<O,UpdateB<enc>::caller>>;

  protected:
    VPinBase& a;
    VPinBase& b;
    volatile int pos=0;
};

#define mkEncoder(q,pina,pinb)\
  extern Encoder q;\
  typedef Encoder::PinA<&q,Debouncer<InputPin<pina>,1>> q##_EncA;\
  typedef Encoder::PinB<&q,Debouncer<InputPin<pinb>,1>> q##_EncB;\
  q##_EncA q##_a_;\
  q##_EncB q##_b_;\
  OnePin<q##_EncA> q##_a(q##_a_);\
  OnePin<q##_EncB> q##_b(q##_b_);\
  Encoder q(q##_a,q##_b);

mkEncoder(qenc,-2,-3);

void setup() {
  Serial.begin(115200);
  while(!Serial);
  Serial<<"Testing OneLib!"<<endl;
  SPI.begin();
  u8g2.begin();
  u8g2.setFont(fontName);
  u8g2.setColorIndex(1);
  vled.begin();
  vbtn.begin();
  qenc.begin();
  PCattachInterrupt<2>(Encoder::UpdateA<&qenc>::caller,CHANGE);
  PCattachInterrupt<3>(Encoder::UpdateB<&qenc>::caller,CHANGE);
}

void loop() {
  Serial<<qenc.getPosition()<<endl;
  led.set(vbtn.in()?tog(10,90):tog(100,100));
  u8g2.firstPage();
  do u8g2.drawStr(0,8,"OneLib!");
  while ( u8g2.nextPage() );
}
