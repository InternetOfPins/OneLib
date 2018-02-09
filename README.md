# OneLib

**Using Zero cost meta-framework for IOT**

Zero-cost abstractions for pin frameworks

**This project is in early development and should only be used by contributing developers. Expect substantial changes to the library API as it evolves. Contributions, ideas and PRs are very welcome.**

## Current state

Right now I'm facing this problem:

After all the trouble to make pin operations to be grouped in atomic groups of arbitrary size, i need **OneLib** to be a non-template. Otherwise all libraries would have to be made templates also.

Previous implicit type was working but didn't allow mixing frameworks.

Now **OnePin** is using explicit type for atomic operations.

Making it implicit at platform level, makes 8 bit MCU's to read 16 bits SPI ports using two read operations (redundant).

So, the problem remains, how to pass this without making everyone a template, and without making it implicit and platform dependent...

**solutions:**

1 - Revert to a common value (bool), would not allow pin grouping, libs requiring atomic groups have to be on the other side (templates)... right now i do not want this.

2 - Use a common base... will we make 8 bit MCU's use multi-bytes or the reverse... still not satisfactory.

3 - explore the possibility of making the library specify its pin group size. <-- this looks promising.

4 - what else? anyone?

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
