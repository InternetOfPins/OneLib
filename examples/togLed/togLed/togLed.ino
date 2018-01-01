#include <OneArduino.h>
#include <OneLib/Button.h>

// using namespace OneLib;
using namespace OneLib::Arduino;
#include <OneLib/ClickButton.h>

void rise() {Serial.println("button pressed");}
void fall() {Serial.println("button released");}

void ledOn() {Serial.println("led id on");}
void ledOff() {Serial.println("led id off");}

//default led output with rise/fall associated functions
typedef OneLib::Arduino::PinCap<OneLib::Arduino::OnRise<OneLib::Arduino::OnFall<OutputPin<LED_BUILTIN>,ledOff>,ledOn>> Led;

#define BUTTON_PIN 4
//pulled-up input pin with 10ms software debounce
//with rise/fall associated fuctions
typedef OneLib::Arduino::PinCap<OneLib::Arduino::OnRise<OneLib::Arduino::OnFall<Debouncer<InputPin<-BUTTON_PIN>,10>,fall>,rise>> Btn;

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
