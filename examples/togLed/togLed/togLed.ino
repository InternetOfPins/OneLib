// this code is broiken at this moment!

#include <OneArduino.h>
using namespace OneLib::Arduino;

#include <OneLib/Button.h>
#include <OneLib/ClickButton.h>

void rise() {Serial.println("button pressed");}
void fall() {Serial.println("button released");}

void ledOn() {Serial.println("led is on");}
void ledOff() {Serial.println("led is off");}

void ledChanged();

//default led output with rise/fall associated functions
typedef
  PinCap<
    OnChange<
      OnRise<
        OnFall<
          OutputPin<LED_BUILTIN>
          ,ledOff
        >
        ,ledOn
      >
      ,ledChanged
    >
  > Led;

void ledChanged() {
  Serial.print("led changed, state:");
  Serial.println(Led::rawIn());
}

#define BUTTON_PIN 4
//pulled-up input pin with 10ms software debounce
//with rise/fall associated fuctions
typedef PinCap<OnRise<OnFall<Debouncer<InputPin<-BUTTON_PIN>,10>,fall>,rise>> Btn;

//button driver, emits Clicked events +
ClickButton<Arduino::API> oneBtn(Hook<Btn,API::Value>::pin());

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
  if(oneBtn.get()==BtnState::Clicked) {
    Serial.println("Clicked, toggle led...");
    Led::tog();
  }
}
