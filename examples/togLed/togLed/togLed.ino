#include <OneArduino.h>
#include <OneLib/Button.h>

using namespace OneLib;
using namespace OneLib::Arduino;
#include <OneLib/ClickButton.h>

void rise() {Serial.println("rise");}
void fall() {Serial.println("fall");}

//default led
typedef OutputPin<LED_BUILTIN> Led;

#define BUTTON_PIN 4
//pulled-up input pin with 10ms software debounce
typedef OnRise<OnFall<Debouncer<InputPin<-BUTTON_PIN>,10>,fall>,rise> Btn;

//button driver, emits Clicked events +
ClickButton<> oneBtn(Hook<Btn>::pin());

void setup() {
  Serial.begin(115200);
  while(!Serial);
  Serial.println("OneLib - togLed example");
  Serial.println("toggle led state on button press");
  // Btn::begin();//static pin init
  oneBtn.begin();//dynamic pin init
  Led::begin();
  // Btn::what();
}

//toggle led when button clicked
void loop() {
  if(oneBtn.get()==BtnState::Clicked) Led::tog();
}
