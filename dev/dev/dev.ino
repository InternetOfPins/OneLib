#ifdef DEBUG
  #include <streamFlow.h>
#endif
// #include <Extras.h>
// #include <OneAVR.h>
#include <OneArduino.h>

// #define pinMode(p,m) Arduino::Pin<p>::mode(m)
// #define digitalRead(p) Arduino::Pin<p>().in()
// #define digitalWrite(p,d) Arduino::Pin<p>().set(o)

#include <Arduino.h>
#include <Print.h>
#include <SPI.h>
#include <Wire.h>
#include <U8g2lib.h>

using namespace OneLib;
using namespace OneLib::Arduino;
// using namespace OneLib::AtMega328p;
// using namespace OneLib::AtMega328p::ArduinoPins;*----------


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
typedef RecState<OnRise<Debouncer<LastState<Pin<-4>>,30>,ok>> Btn;//encoder button with pullup (reverse logic)
Btn btn;

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
  Led::set(btn.in()?tog(10,90):tog(100,100));
  // Led::set(tog(500,500));
  u8g2.firstPage();
  do u8g2.drawStr(0,8,"OneLib!");
  while ( u8g2.nextPage() );
}
