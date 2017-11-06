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

class AccelEncoder:public Encoder {
  public:
    AccelEncoder(VPinBase& a,VPinBase& b):Encoder(a,b),lastUpdate(millis()) {}
    static const uint16_t accelTop=512;
    static const uint16_t accelUp=8;
    static const uint16_t accelDown=2;
    void updateA() {
      unsigned int m=millis();
      accel-=(m-lastUpdate)*accelDown;
      lastUpdate=m;
      if (accel<1) accel=1;
      if (a.logicIn()^b.logicIn()) pos-=accel;
      else pos+=accel;
      if (accel<accelTop) accel+=accelUp;
    }
    void updateB() {
      unsigned int m=millis();
      accel-=m-lastUpdate;
      lastUpdate=m;
      if (accel<0) accel=0;
      if (a.logicIn()^b.logicIn()) pos+=accel;
      else pos-=accel;
      if (accel<accelTop) accel+=accelUp;
    }

    template<AccelEncoder *enc>
    using UpdateA = MFunc<AccelEncoder>::With<enc,&AccelEncoder::updateA>;

    template<AccelEncoder *enc>
    using UpdateB = MFunc<AccelEncoder>::With<enc,&AccelEncoder::updateB>;

    template<AccelEncoder *enc,class O,uint8_t deb=1>
    using PinA=RecState<OnChange<O,UpdateA<enc>::caller>>;

    template<AccelEncoder *enc,class O,uint8_t deb=1>
    using PinB=RecState<OnChange<O,UpdateB<enc>::caller>>;

    inline int16_t getAccel() const {return accel;}
  protected:
    int16_t accel=0;
    unsigned long lastUpdate;
};

// class IncrEncoder:public Encoder {
//   public:
//     IncrEncoder(VPinBase& a,VPinBase& b):Encoder(a,b) {}
//     void updateA() {
//       bool dir=a.logicIn()^b.logicIn();
//       if (dir!=lastDir) step=step>>1;
//       step++;
//       lastDir=dir;
//       pos+=dir?-(step>>1):step>>1;
//     }
//     void updateB() {
//       bool dir=a.logicIn()^b.logicIn();
//       if (dir!=lastDir) step=(step>>1);
//       step++;
//       lastDir=dir;
//       pos+=dir?step>>1:-(step>>1);
//     }
//
//     template<IncrEncoder *enc>
//     using UpdateA = MFunc<IncrEncoder>::With<enc,&IncrEncoder::updateA>;
//
//     template<IncrEncoder *enc>
//     using UpdateB = MFunc<IncrEncoder>::With<enc,&IncrEncoder::updateB>;
//
//     template<IncrEncoder *enc,class O,uint8_t deb=1>
//     using PinA=RecState<OnChange<O,UpdateA<enc>::caller>>;
//
//     template<IncrEncoder *enc,class O,uint8_t deb=1>
//     using PinB=RecState<OnChange<O,UpdateB<enc>::caller>>;
//
//     inline int16_t getStep() const {return step;}
//   protected:
//     bool lastDir=false;
//     uint16_t step=0;
// };
//
#define mkEncoder(EncoderType,enc,pina,pinb)\
  extern EncoderType enc;\
  typedef EncoderType::PinA<&enc,Debouncer<InputPin<pina>,1>> enc##_EncA;\
  typedef EncoderType::PinB<&enc,Debouncer<InputPin<pinb>,1>> enc##_EncB;\
  enc##_EncA enc##_a_;\
  enc##_EncB enc##_b_;\
  OnePin<enc##_EncA> enc##_a(enc##_a_);\
  OnePin<enc##_EncB> enc##_b(enc##_b_);\
  EncoderType enc(enc##_a,enc##_b);

mkEncoder(IncrEncoder,qenc,-2,-3);

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
  PCattachInterrupt<2>(IncrEncoder::UpdateA<&qenc>::caller,CHANGE);
  PCattachInterrupt<3>(IncrEncoder::UpdateB<&qenc>::caller,CHANGE);
}

int oldPos=0;
void loop() {
  int pos=qenc.getPosition();
  if (pos!=oldPos) {
    Serial<<pos<<" "<<qenc.getStep()<<endl;
    oldPos=pos;
  }
  led.set(vbtn.in()?tog(10,90):tog(100,100));
  u8g2.firstPage();
  do u8g2.drawStr(0,8,"OneLib!");
  while ( u8g2.nextPage() );
}
