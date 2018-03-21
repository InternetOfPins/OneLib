#include <OneArduino.h>
#include <HAL/Func.h>

using namespace OneLib::Arduino;

// #include <OneLib/Encoder.h>
// #include <OneLib/ClickButton.h>

constexpr uint8_t encAPin=2;
constexpr uint8_t encBPin=2;
constexpr uint8_t encBtnPin=4;

// template<typename API,int16_t accelUp=6>
// struct A {
//   void tst() {}
// };
//
// A<API,0> a;
//
// template<A<API,0>* aa>
// using tst=MFunc<A<API,0>>::With<aa,&A<API,0>::tst>;

// typedef PinCap<OnRise<OnFall<Debouncer<InputPin<-BUTTON_PIN>,10>,fall>,rise>> Btn;
// ClickButton<Arduino::API> oneBtn(Hook<Btn,API::Value>::pin());

void setup() {
  Serial.begin(115200);
  while(!Serial);
  Serial.println("OneLib - atomic accel. encoder example");
  Serial.println("essay about atomic pin spec.");
}

void loop() {

}
