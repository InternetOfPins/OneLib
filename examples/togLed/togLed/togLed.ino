#include <OneArduino.h>

using namespace OneLib;
using namespace OneLib::Arduino;

//default led
typedef OutputPin<LED_BUILTIN> Led;

#define BUTTON_PIN 4
//pulled-up input pin with 10ms software debounce
typedef RecState<Debounce<InputPin<-BUTTON_PIN>,10>> Btn;

Btn btn;//HAL
OnePinHook<Btn> btnHook(btn);//pin driver
ClickButton<> oneBtn(btnHook);//button driver

void setup() {
  Serial.begin(115200);
  while(!Serial);
  Serial.println("OneLib - togLed example");
  Serial.println("toggle led state on button press");
  Btn::begin();
  Led::begin();
}

void loop() {
  if(oneBtn.get()==BtnState::Clicked) Led::tog();
}
