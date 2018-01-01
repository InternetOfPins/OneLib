# OneLib

**Using Zero cost meta-framework for IOT**

Zero-cost abstractions for pin frameworks

## Purpose

Provide a set of common small libraries packed into one.

Serve as an example of [OnePin](https://github.com/InternetOfPins/OnePin) library usage.

## Utilities

- **Button** simple button state provider with states:
  + Open⁺
  + Pressed
  + Hold⁺
  + Released


  _⁺ Open and Hold states can repeat_

  _Pressed and Released states are unique and must be consumed_

- **ClickButton** Button variant with extra unique states:
  + DoubleClicked
  + Clicked


- **Encoder** simple quad-encoder driver

- **AccelEncoder** Encoder variant with acceleration

## Example

```c++
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
```
