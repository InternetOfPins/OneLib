# OneLib

**Zero cost meta-framework for IOT**

Zero-cost abstractions for pin frameworks

Licence: CC-BY-NC-SA

## Purpose
Experiment with C++ (0x11) to abstract over pin based frameworks (_**ie**: Wiring, Arduino_).

Open this experiment to consideration and improvement.

## Technique

This meta-framework can overlay existing frameworks or bare-metal MCU's.
Working with the C++ compiler at type level.

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
