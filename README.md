# OneLib

**Zero cost meta-framework for IOT**

Zero-cost abstractions for pin frameworks

## Purpose

Provide a set of common small libraries packed into one.
Serve as an example of [OnePin](https://github.com/InternetOfPins/OnePin) library usage.

## Utilities

- **Button** simple button state provider with states Open⁺ | Pressed | Hold⁺ | Released
  ⁺ Open and Hold states can repeat
  Pressed and Released states are unique and must be consumed
- **ClickButton** Button variant with extra unique states DoubleClicked | Clicked 
- **Encoder** simple quad-encoder driver
- **AccelEncoder** Encoder variant with acceleration

## Example

```c++
#include <OneArduino.h>
#include <OneLib/Button.h>

using namespace OneLib;
using namespace OneLib::Arduino;
#include <OneLib/ClickButton.h>

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
```
