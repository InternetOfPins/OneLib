000002c0 <main>:
 2c0:	78 94       	sei
 2c2:	84 b5       	in	r24, 0x24	; 36
 2c4:	82 60       	ori	r24, 0x02	; 2
 2c6:	84 bd       	out	0x24, r24	; 36
 2c8:	84 b5       	in	r24, 0x24	; 36
 2ca:	81 60       	ori	r24, 0x01	; 1
 2cc:	84 bd       	out	0x24, r24	; 36
 2ce:	85 b5       	in	r24, 0x25	; 37
 2d0:	82 60       	ori	r24, 0x02	; 2
 2d2:	85 bd       	out	0x25, r24	; 37
 2d4:	85 b5       	in	r24, 0x25	; 37
 2d6:	81 60       	ori	r24, 0x01	; 1
 2d8:	85 bd       	out	0x25, r24	; 37
 2da:	80 91 6e 00 	lds	r24, 0x006E	; 0x80006e <__TEXT_REGION_LENGTH__+0x7e006e>
 2de:	81 60       	ori	r24, 0x01	; 1
 2e0:	80 93 6e 00 	sts	0x006E, r24	; 0x80006e <__TEXT_REGION_LENGTH__+0x7e006e>
 2e4:	10 92 81 00 	sts	0x0081, r1	; 0x800081 <__TEXT_REGION_LENGTH__+0x7e0081>
 2e8:	80 91 81 00 	lds	r24, 0x0081	; 0x800081 <__TEXT_REGION_LENGTH__+0x7e0081>
 2ec:	82 60       	ori	r24, 0x02	; 2
 2ee:	80 93 81 00 	sts	0x0081, r24	; 0x800081 <__TEXT_REGION_LENGTH__+0x7e0081>
 2f2:	80 91 81 00 	lds	r24, 0x0081	; 0x800081 <__TEXT_REGION_LENGTH__+0x7e0081>
 2f6:	81 60       	ori	r24, 0x01	; 1
 2f8:	80 93 81 00 	sts	0x0081, r24	; 0x800081 <__TEXT_REGION_LENGTH__+0x7e0081>
 2fc:	80 91 80 00 	lds	r24, 0x0080	; 0x800080 <__TEXT_REGION_LENGTH__+0x7e0080>
 300:	81 60       	ori	r24, 0x01	; 1
 302:	80 93 80 00 	sts	0x0080, r24	; 0x800080 <__TEXT_REGION_LENGTH__+0x7e0080>
 306:	80 91 b1 00 	lds	r24, 0x00B1	; 0x8000b1 <__TEXT_REGION_LENGTH__+0x7e00b1>
 30a:	84 60       	ori	r24, 0x04	; 4
 30c:	80 93 b1 00 	sts	0x00B1, r24	; 0x8000b1 <__TEXT_REGION_LENGTH__+0x7e00b1>
 310:	80 91 b0 00 	lds	r24, 0x00B0	; 0x8000b0 <__TEXT_REGION_LENGTH__+0x7e00b0>
 314:	81 60       	ori	r24, 0x01	; 1
 316:	80 93 b0 00 	sts	0x00B0, r24	; 0x8000b0 <__TEXT_REGION_LENGTH__+0x7e00b0>
 31a:	80 91 7a 00 	lds	r24, 0x007A	; 0x80007a <__TEXT_REGION_LENGTH__+0x7e007a>
 31e:	84 60       	ori	r24, 0x04	; 4
 320:	80 93 7a 00 	sts	0x007A, r24	; 0x80007a <__TEXT_REGION_LENGTH__+0x7e007a>
 324:	80 91 7a 00 	lds	r24, 0x007A	; 0x80007a <__TEXT_REGION_LENGTH__+0x7e007a>
 328:	82 60       	ori	r24, 0x02	; 2
 32a:	80 93 7a 00 	sts	0x007A, r24	; 0x80007a <__TEXT_REGION_LENGTH__+0x7e007a>
 32e:	80 91 7a 00 	lds	r24, 0x007A	; 0x80007a <__TEXT_REGION_LENGTH__+0x7e007a>
 332:	81 60       	ori	r24, 0x01	; 1
 334:	80 93 7a 00 	sts	0x007A, r24	; 0x80007a <__TEXT_REGION_LENGTH__+0x7e007a>
 338:	80 91 7a 00 	lds	r24, 0x007A	; 0x80007a <__TEXT_REGION_LENGTH__+0x7e007a>
 33c:	80 68       	ori	r24, 0x80	; 128
 33e:	80 93 7a 00 	sts	0x007A, r24	; 0x80007a <__TEXT_REGION_LENGTH__+0x7e007a>
 342:	10 92 c1 00 	sts	0x00C1, r1	; 0x8000c1 <__TEXT_REGION_LENGTH__+0x7e00c1>
 346:	ed e9       	ldi	r30, 0x9D	; 157
 348:	f0 e0       	ldi	r31, 0x00	; 0
 34a:	24 91       	lpm	r18, Z
 34c:	e9 e8       	ldi	r30, 0x89	; 137
 34e:	f0 e0       	ldi	r31, 0x00	; 0
 350:	84 91       	lpm	r24, Z
 352:	88 23       	and	r24, r24
 354:	99 f0       	breq	.+38     	; 0x37c <main+0xbc>
 356:	90 e0       	ldi	r25, 0x00	; 0
 358:	88 0f       	add	r24, r24
 35a:	99 1f       	adc	r25, r25
 35c:	fc 01       	movw	r30, r24
 35e:	e8 59       	subi	r30, 0x98	; 152
 360:	ff 4f       	sbci	r31, 0xFF	; 255
 362:	a5 91       	lpm	r26, Z+
 364:	b4 91       	lpm	r27, Z
 368:	ee 58       	subi	r30, 0x8E	; 142
 366:	fc 01       	movw	r30, r24
 36a:	ff 4f       	sbci	r31, 0xFF	; 255
 36c:	85 91       	lpm	r24, Z+
 36e:	94 91       	lpm	r25, Z
 370:	8f b7       	in	r24, 0x3f	; 63
 372:	f8 94       	cli
 374:	ec 91       	ld	r30, X
 376:	e2 2b       	or	r30, r18
 378:	ec 93       	st	X, r30
 37a:	8f bf       	out	0x3f, r24	; 63
 37c:	c0 e0       	ldi	r28, 0x00	; 0
 37e:	d0 e0       	ldi	r29, 0x00	; 0
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
