000002c6 <main>:
 2c6:	78 94       	sei
 2c8:	84 b5       	in	r24, 0x24	; 36
 2ca:	82 60       	ori	r24, 0x02	; 2
 2cc:	84 bd       	out	0x24, r24	; 36
 2ce:	84 b5       	in	r24, 0x24	; 36
 2d0:	81 60       	ori	r24, 0x01	; 1
 2d2:	84 bd       	out	0x24, r24	; 36
 2d4:	85 b5       	in	r24, 0x25	; 37
 2d6:	82 60       	ori	r24, 0x02	; 2
 2d8:	85 bd       	out	0x25, r24	; 37
 2da:	85 b5       	in	r24, 0x25	; 37
 2dc:	81 60       	ori	r24, 0x01	; 1
 2de:	85 bd       	out	0x25, r24	; 37
 2e0:	80 91 6e 00 	lds	r24, 0x006E	; 0x80006e <__stack+0x7ff76f>
 2e4:	81 60       	ori	r24, 0x01	; 1
 2e6:	80 93 6e 00 	sts	0x006E, r24	; 0x80006e <__stack+0x7ff76f>
 2ea:	10 92 81 00 	sts	0x0081, r1	; 0x800081 <__stack+0x7ff782>
 2ee:	80 91 81 00 	lds	r24, 0x0081	; 0x800081 <__stack+0x7ff782>
 2f2:	82 60       	ori	r24, 0x02	; 2
 2f4:	80 93 81 00 	sts	0x0081, r24	; 0x800081 <__stack+0x7ff782>
 2f8:	80 91 81 00 	lds	r24, 0x0081	; 0x800081 <__stack+0x7ff782>
 2fc:	81 60       	ori	r24, 0x01	; 1
 2fe:	80 93 81 00 	sts	0x0081, r24	; 0x800081 <__stack+0x7ff782>
 302:	80 91 80 00 	lds	r24, 0x0080	; 0x800080 <__stack+0x7ff781>
 306:	81 60       	ori	r24, 0x01	; 1
 308:	80 93 80 00 	sts	0x0080, r24	; 0x800080 <__stack+0x7ff781>
 30c:	80 91 b1 00 	lds	r24, 0x00B1	; 0x8000b1 <__stack+0x7ff7b2>
 310:	84 60       	ori	r24, 0x04	; 4
 312:	80 93 b1 00 	sts	0x00B1, r24	; 0x8000b1 <__stack+0x7ff7b2>
 316:	80 91 b0 00 	lds	r24, 0x00B0	; 0x8000b0 <__stack+0x7ff7b1>
 31a:	81 60       	ori	r24, 0x01	; 1
 31c:	80 93 b0 00 	sts	0x00B0, r24	; 0x8000b0 <__stack+0x7ff7b1>
 320:	80 91 7a 00 	lds	r24, 0x007A	; 0x80007a <__stack+0x7ff77b>
 324:	84 60       	ori	r24, 0x04	; 4
 326:	80 93 7a 00 	sts	0x007A, r24	; 0x80007a <__stack+0x7ff77b>
 32a:	80 91 7a 00 	lds	r24, 0x007A	; 0x80007a <__stack+0x7ff77b>
 32e:	82 60       	ori	r24, 0x02	; 2
 330:	80 93 7a 00 	sts	0x007A, r24	; 0x80007a <__stack+0x7ff77b>
 334:	80 91 7a 00 	lds	r24, 0x007A	; 0x80007a <__stack+0x7ff77b>
 338:	81 60       	ori	r24, 0x01	; 1
 33a:	80 93 7a 00 	sts	0x007A, r24	; 0x80007a <__stack+0x7ff77b>
 33e:	80 91 7a 00 	lds	r24, 0x007A	; 0x80007a <__stack+0x7ff77b>
 342:	80 68       	ori	r24, 0x80	; 128
 344:	80 93 7a 00 	sts	0x007A, r24	; 0x80007a <__stack+0x7ff77b>
 348:	10 92 c1 00 	sts	0x00C1, r1	; 0x8000c1 <__stack+0x7ff7c2>
 34c:	ed e9       	ldi	r30, 0x9D	; 157
 34e:	f0 e0       	ldi	r31, 0x00	; 0
 350:	24 91       	lpm	r18, Z
 352:	e9 e8       	ldi	r30, 0x89	; 137
 354:	f0 e0       	ldi	r31, 0x00	; 0
 356:	84 91       	lpm	r24, Z
 358:	88 23       	and	r24, r24
 35a:	99 f0       	breq	.+38     	; 0x382 <main+0xbc>
 35c:	90 e0       	ldi	r25, 0x00	; 0
 35e:	88 0f       	add	r24, r24
 360:	99 1f       	adc	r25, r25
 362:	fc 01       	movw	r30, r24
 364:	e8 59       	subi	r30, 0x98	; 152
 366:	ff 4f       	sbci	r31, 0xFF	; 255
 368:	a5 91       	lpm	r26, Z+
 36a:	b4 91       	lpm	r27, Z
 36c:	fc 01       	movw	r30, r24
 36e:	ee 58       	subi	r30, 0x8E	; 142
 370:	ff 4f       	sbci	r31, 0xFF	; 255
 372:	85 91       	lpm	r24, Z+
 374:	94 91       	lpm	r25, Z
 376:	8f b7       	in	r24, 0x3f	; 63
 378:	f8 94       	cli
 37a:	ec 91       	ld	r30, X
 37c:	e2 2b       	or	r30, r18
 37e:	ec 93       	st	X, r30
 380:	8f bf       	out	0x3f, r24	; 63
 382:	c0 e0       	ldi	r28, 0x00	; 0
 384:	d0 e0       	ldi	r29, 0x00	; 0
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
 3a2:	0e 94 00 00 	call	0	; 0x0 <__vectors>
 3a6:	ef cf       	rjmp	.-34     	; 0x386 <main+0xc0>
