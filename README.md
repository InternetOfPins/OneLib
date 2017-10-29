# OneLib

Zero-cost abstractions for pin frameworks

## Purpose
Experiment with C++ (0x11) to abstract over pin based frameworks (_**ie**: Wiring, Arduino_).

Using meta-programming to provide function mappings, resulting in direct calls.

Open this experiment to consideration and improvement.

## Example

```c++
//use Arduino framework pin function mappings
#include "OnePin/Arduino.h"

//negative pin, OnePin will wire reverse logic
#define ENCBTN_PIN -4

//pin types
//attach software debouncer to a pin
typedef Debouncer<ArduinoPin,30> SoftDebouncedPin;

//specific pins
OnePin<SoftDebouncedPin,ENCBTN_PIN> pin4;
OnePin<ArduinoPin,13> led;

void setup() {
  pin4.modeInUp();
  led.modeOut();
}

void loop() {
  if (pin4.get()) {
    led.on();
    delay(10);
  }
  led.off();
  delay(90);
}
```


## Composability
Experiment with abstractions to provide composable pin behavior

**ex: adding software debounce to a pin**

This is also a zero cost abstraction, meaning that the composition is code equivalent to doing that software debounce on the client function.

**advantages:** software debounce can be added outside a library

ex: **reverse logic**

IOPin check for negative pin number and overlays a reverse logic.

Apply to inputs with pull-up, also removing this consideration from the libraries.

## Current state

### API

#### Layer 1 - base pin functions adapter

**InputPin**

```c++
bool get(PinNr p) // get pin state
```

**OutputPin**

```c++
void set(PinNr p,bool o) // set pin state
void on(PinNr p) // turn pin on
void off(PinNr p) // turn pin off
```

**IOPinNoDown**
```c++
inline void modeOff(PinNr p) // tristate the pin
inline void modeOut(PinNr p) // set output pin
inline void modeIn(PinNr p) // set input pin
inline void modeInUp(PinNr p) // set input pin with pull-up
```

**IOPin**
provides all functionalities of: InputPin, OutputPin, IOPinNoDown
plus an additional input mode with pull-down

#### Layer 2 - Pin behavior overlays

```c++
typedef Debouncer<ArduinoPin,30> SoftDebouncedPin;
```

#### Layer 3 - Provide unique pin attached to meta-objects

```c++
OnePin<SoftDebouncedPin,ENCBTN_PIN> pin4;
OnePin<ArduinoPin,13> led;
```

## TODO

provide a layer of translation from other frameworks (ie: wiring)
this can import code written on other frameworks to be compiled with OneLib instead

## Disassembly compare

#### blinking with OnePin
```assembly
386:	61 e0       	ldi	r22, 0x01	; 1
388:	8d e0       	ldi	r24, 0x0D	; 13
38a:	0e 94 70 00 	call	0xe0	; 0xe0 <digitalWrite>
38e:	0e 94 e1 00 	call	0x1c2	; 0x1c2 <delay.constprop.0>
392:	60 e0       	ldi	r22, 0x00	; 0
394:	8d e0       	ldi	r24, 0x0D	; 13
396:	0e 94 70 00 	call	0xe0	; 0xe0 <digitalWrite>
39a:	0e 94 e1 00 	call	0x1c2	; 0x1c2 <delay.constprop.0>
39e:	20 97       	sbiw	r28, 0x00	; 0
3a0:	91 f3       	breq	.-28     	; 0x386 <main+0xc0>
```

#### blinking with Arduino framework
```assembly
380:	81 e0       	ldi	r24, 0x01	; 1
382:	0e 94 ce 00 	call	0x19c	; 0x19c <digitalWrite.constprop.0>
386:	0e 94 96 00 	call	0x12c	; 0x12c <delay.constprop.2>
38a:	80 e0       	ldi	r24, 0x00	; 0
38c:	0e 94 ce 00 	call	0x19c	; 0x19c <digitalWrite.constprop.0>
390:	0e 94 96 00 	call	0x12c	; 0x12c <delay.constprop.2>
394:	20 97       	sbiw	r28, 0x00	; 0
396:	a1 f3       	breq	.-24     	; 0x380 <main+0xc0>
398:	0e 94 00 00 	call	0	; 0x0 <__vectors>
39c:	f1 cf       	rjmp	.-30     	; 0x380 <main+0xc0>
```
