#include <OneArduino.h>
#include <OneLib/Button.h>

using namespace OneLib;
using namespace OneLib::Arduino;
#include <OneLib/ClickButton.h>

//default led
typedef OutputPin<LED_BUILTIN> Led;

#define BUTTON_PIN 4
//pulled-up input pin with 10ms software debounce
typedef RecState<
  Debounce<
    InputPin<-BUTTON_PIN>
    ,10
  >
> Btn;

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
}

//toggle led when button clicked
void loop() {
  if(oneBtn.get()==BtnState::Clicked) Led::tog();
}
