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

**Zero-cost** meta-programming with static inline functions.

**Composition** using c++ mixins.

**OnePin** top level pin class with virtual functions to cover low level mixins.
This class allows delivering a generic pin, breaking the template/mixin chain.

## Example

```c++
#include <OneAvr.h>

using namespace OneLib;
using namespace OneLib::Avr;
using namespace OneLib::Avr::AtMega328p;

//static hardware description
typedef Pin<PortB,5> Led;//pin 13 on arduino
typedef Pin<PortD,-4> EncBtn;//with reverse logic included

void setup() {
  Led::modeOut();
  EncBtn::modeInUp();
}

//toggles on/off as specified in ms
inline bool tog(unsigned int on,unsigned int off) {return (millis()%(on+off))<on;}

//blink with no delay
void loop() {
  if (EncBtn()) Led::set(tog(10,90));
  else Led::set(tog(100,100));
}
```

## Generated code

_this data can be outdated_

**Arduino BtnBlink**

>Program:    1154 bytes (3.5% Full)

>Data:          9 bytes (0.4% Full)

**OneLib BtnBlink**

>Program:     702 bytes (2.1% Full)

>Data:          9 bytes (0.4% Full)
