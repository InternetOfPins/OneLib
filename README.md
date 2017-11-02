# OneLib

Aiming Zero-cost abstractions for pin frameworks

CC-BY-NC-SA

## Purpose
Experiment with C++ (0x11) to abstract over pin based frameworks (_**ie**: Wiring, Arduino_).

Open this experiment to consideration and improvement.

## Example

```c++
using namespace OneLib;

//consuming the object with a function
template<class Pin>
inline void blink(int t) {
  Pin::on();
  delay(t);
  Pin::off();
}

//static hardware description
typedef Avr::Pin<AtMega328p::portB,5> Led;//pin 13 on arduino
typedef Avr::Pin<AtMega328p::portD,-4> EncBtn;//with reverse logic included
EncBtn encBtn;//and object of type EncBtn (can use operators)

void setup() {
  Led::modeOut();
  EncBtn::modeInUp();
}

void loop() {
  if (encBtn) {//converts to bool => reads the pin!
    blink<Led>(10);
    delay(90);
  } else {
    blink<Led>(100);
    delay(100);
  }
}
```

## Generated code

**Arduino BtnBlink**

Program:    1154 bytes (3.5% Full)

Data:          9 bytes (0.4% Full)

**OneLib BtnBlink**

Program:     702 bytes (2.1% Full)

Data:          9 bytes (0.4% Full)

## Composability
Experiment with abstractions to provide composable pin behavior

**ex: adding software debounce to a pin**

This is also a zero cost abstraction, meaning that the composition is code equivalent to doing that software debounce on the client function.

**advantages:** software debounce can be added outside a library

ex: **reverse logic**

Check for negative pin number and overlays a reverse logic.

This behavior can also be composed into a pin.

### Examples

```c++
typedef Debouncer<Avr::Pin<AtMega328p::portB,5>,30> Deb13;//soft debounced AVR pin
typedef Debouncer<Arduino::Pin<13>> Pin13;//soft debounced Arduino pin
```

## Benchmarks

Comparative number of operations in 2 sec. (higher is better).
Using Arduino framework and OnePin targeting raw AVR mcu.

| Mode            |  \# Ops |
|-----------------|---------|
|Arduino pin mode:|274281|
|OneLib Arduino pin mode:|274074|
|OneLib pin mode:|496787|
|Arduino pin input:|324428|
|OneLib Arduino pin input:|324412|
|OnePin pin input:|588780|
|Debounced input:|341875|

## Disassembly compare

comparing part of the main function from the example above with the equivalent arduino code.

Target: AtMega328P (current is not a fair compare because OneLib is targeting the raw AVR)

#### blinking with OnePin
```assembly
272:	85 b1       	in	r24, 0x05	; 5
274:	80 62       	ori	r24, 0x20	; 32
276:	4c 99       	sbic	0x09, 4	; 9
278:	0d c0       	rjmp	.+26     	; 0x294 <main+0xb2>
27a:	85 b9       	out	0x05, r24	; 5
27c:	6a e0       	ldi	r22, 0x0A	; 10
27e:	70 e0       	ldi	r23, 0x00	; 0
280:	80 e0       	ldi	r24, 0x00	; 0
282:	90 e0       	ldi	r25, 0x00	; 0
284:	0e 94 6d 00 	call	0xda	; 0xda <delay>
288:	2d 98       	cbi	0x05, 5	; 5
28a:	6a e5       	ldi	r22, 0x5A	; 90
28c:	70 e0       	ldi	r23, 0x00	; 0
28e:	80 e0       	ldi	r24, 0x00	; 0
290:	90 e0       	ldi	r25, 0x00	; 0
292:	0c c0       	rjmp	.+24     	; 0x2ac <main+0xca>
294:	85 b9       	out	0x05, r24	; 5
296:	64 e6       	ldi	r22, 0x64	; 100
298:	70 e0       	ldi	r23, 0x00	; 0
29a:	80 e0       	ldi	r24, 0x00	; 0
29c:	90 e0       	ldi	r25, 0x00	; 0
29e:	0e 94 6d 00 	call	0xda	; 0xda <delay>
2a2:	2d 98       	cbi	0x05, 5	; 5
2a4:	64 e6       	ldi	r22, 0x64	; 100
2a6:	70 e0       	ldi	r23, 0x00	; 0
2a8:	80 e0       	ldi	r24, 0x00	; 0
2aa:	90 e0       	ldi	r25, 0x00	; 0
2ac:	0e 94 6d 00 	call	0xda	; 0xda <delay>
2b0:	20 97       	sbiw	r28, 0x00	; 0
2b2:	f9 f2       	breq	.-66     	; 0x272 <main+0x90>
2b4:	0e 94 00 00 	call	0	; 0x0 <__vectors>
2b8:	dc cf       	rjmp	.-72     	; 0x272 <main+0x90>
```

#### blinking with Arduino framework
```assembly
3fa:	f7 01       	movw	r30, r14
3fc:	84 91       	lpm	r24, Z
3fe:	fe 01       	movw	r30, r28
400:	a4 90       	lpm	r10, Z
402:	f8 01       	movw	r30, r16
404:	b4 90       	lpm	r11, Z
406:	bb 20       	and	r11, r11
408:	09 f1       	breq	.+66     	; 0x44c <main+0x164>
40a:	81 11       	cpse	r24, r1
40c:	0e 94 75 00 	call	0xea	; 0xea <turnOffPWM>
410:	eb 2d       	mov	r30, r11
412:	f0 e0       	ldi	r31, 0x00	; 0
414:	ee 0f       	add	r30, r30
416:	ff 1f       	adc	r31, r31
418:	cf 01       	movw	r24, r30
41a:	8e 58       	subi	r24, 0x8E	; 142
41c:	9f 4f       	sbci	r25, 0xFF	; 255
41e:	fc 01       	movw	r30, r24
420:	a5 91       	lpm	r26, Z+
422:	b4 91       	lpm	r27, Z
424:	8c 91       	ld	r24, X
426:	a8 22       	and	r10, r24
428:	89 f0       	breq	.+34     	; 0x44c <main+0x164>
42a:	81 e0       	ldi	r24, 0x01	; 1
42c:	0e 94 9e 00 	call	0x13c	; 0x13c <digitalWrite.constprop.1>
430:	64 e6       	ldi	r22, 0x64	; 100
432:	70 e0       	ldi	r23, 0x00	; 0
434:	80 e0       	ldi	r24, 0x00	; 0
436:	90 e0       	ldi	r25, 0x00	; 0
438:	0e 94 f0 00 	call	0x1e0	; 0x1e0 <delay>
43c:	80 e0       	ldi	r24, 0x00	; 0
43e:	0e 94 9e 00 	call	0x13c	; 0x13c <digitalWrite.constprop.1>
442:	64 e6       	ldi	r22, 0x64	; 100
444:	70 e0       	ldi	r23, 0x00	; 0
446:	80 e0       	ldi	r24, 0x00	; 0
448:	90 e0       	ldi	r25, 0x00	; 0
44a:	10 c0       	rjmp	.+32     	; 0x46c <main+0x184>
44c:	81 e0       	ldi	r24, 0x01	; 1
44e:	0e 94 9e 00 	call	0x13c	; 0x13c <digitalWrite.constprop.1>
452:	6a e0       	ldi	r22, 0x0A	; 10
454:	70 e0       	ldi	r23, 0x00	; 0
456:	80 e0       	ldi	r24, 0x00	; 0
458:	90 e0       	ldi	r25, 0x00	; 0
45a:	0e 94 f0 00 	call	0x1e0	; 0x1e0 <delay>
45e:	80 e0       	ldi	r24, 0x00	; 0
460:	0e 94 9e 00 	call	0x13c	; 0x13c <digitalWrite.constprop.1>
464:	6a e5       	ldi	r22, 0x5A	; 90
466:	70 e0       	ldi	r23, 0x00	; 0
468:	80 e0       	ldi	r24, 0x00	; 0
46a:	90 e0       	ldi	r25, 0x00	; 0
46c:	0e 94 f0 00 	call	0x1e0	; 0x1e0 <delay>
470:	c1 14       	cp	r12, r1
472:	d1 04       	cpc	r13, r1
474:	09 f4       	brne	.+2      	; 0x478 <main+0x190>
476:	c1 cf       	rjmp	.-126    	; 0x3fa <main+0x112>
478:	0e 94 00 00 	call	0	; 0x0 <__vectors>
47c:	be cf       	rjmp	.-132    	; 0x3fa <main+0x112>
```
