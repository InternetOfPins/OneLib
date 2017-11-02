000002e8 <main>:
 2e8:	78 94       	sei
 2ea:	84 b5       	in	r24, 0x24	; 36
 2ec:	82 60       	ori	r24, 0x02	; 2
 2ee:	84 bd       	out	0x24, r24	; 36
 2f0:	84 b5       	in	r24, 0x24	; 36
 2f2:	81 60       	ori	r24, 0x01	; 1
 2f4:	84 bd       	out	0x24, r24	; 36
 2f6:	85 b5       	in	r24, 0x25	; 37
 2f8:	82 60       	ori	r24, 0x02	; 2
 2fa:	85 bd       	out	0x25, r24	; 37
 2fc:	85 b5       	in	r24, 0x25	; 37
 2fe:	81 60       	ori	r24, 0x01	; 1
 300:	85 bd       	out	0x25, r24	; 37
 302:	80 91 6e 00 	lds	r24, 0x006E	; 0x80006e <__stack+0x7ff76f>
 306:	81 60       	ori	r24, 0x01	; 1
 308:	80 93 6e 00 	sts	0x006E, r24	; 0x80006e <__stack+0x7ff76f>
 30c:	10 92 81 00 	sts	0x0081, r1	; 0x800081 <__stack+0x7ff782>
 310:	80 91 81 00 	lds	r24, 0x0081	; 0x800081 <__stack+0x7ff782>
 314:	82 60       	ori	r24, 0x02	; 2
 316:	80 93 81 00 	sts	0x0081, r24	; 0x800081 <__stack+0x7ff782>
 31a:	80 91 81 00 	lds	r24, 0x0081	; 0x800081 <__stack+0x7ff782>
 31e:	81 60       	ori	r24, 0x01	; 1
 320:	80 93 81 00 	sts	0x0081, r24	; 0x800081 <__stack+0x7ff782>
 324:	80 91 80 00 	lds	r24, 0x0080	; 0x800080 <__stack+0x7ff781>
 328:	81 60       	ori	r24, 0x01	; 1
 32a:	80 93 80 00 	sts	0x0080, r24	; 0x800080 <__stack+0x7ff781>
 32e:	80 91 b1 00 	lds	r24, 0x00B1	; 0x8000b1 <__stack+0x7ff7b2>
 332:	84 60       	ori	r24, 0x04	; 4
 334:	80 93 b1 00 	sts	0x00B1, r24	; 0x8000b1 <__stack+0x7ff7b2>
 338:	80 91 b0 00 	lds	r24, 0x00B0	; 0x8000b0 <__stack+0x7ff7b1>
 33c:	81 60       	ori	r24, 0x01	; 1
 33e:	80 93 b0 00 	sts	0x00B0, r24	; 0x8000b0 <__stack+0x7ff7b1>
 342:	80 91 7a 00 	lds	r24, 0x007A	; 0x80007a <__stack+0x7ff77b>
 346:	84 60       	ori	r24, 0x04	; 4
 348:	80 93 7a 00 	sts	0x007A, r24	; 0x80007a <__stack+0x7ff77b>
 34c:	80 91 7a 00 	lds	r24, 0x007A	; 0x80007a <__stack+0x7ff77b>
 350:	82 60       	ori	r24, 0x02	; 2
 352:	80 93 7a 00 	sts	0x007A, r24	; 0x80007a <__stack+0x7ff77b>
 356:	80 91 7a 00 	lds	r24, 0x007A	; 0x80007a <__stack+0x7ff77b>
 35a:	81 60       	ori	r24, 0x01	; 1
 35c:	80 93 7a 00 	sts	0x007A, r24	; 0x80007a <__stack+0x7ff77b>
 360:	80 91 7a 00 	lds	r24, 0x007A	; 0x80007a <__stack+0x7ff77b>
 364:	80 68       	ori	r24, 0x80	; 128
 366:	80 93 7a 00 	sts	0x007A, r24	; 0x80007a <__stack+0x7ff77b>
 36a:	10 92 c1 00 	sts	0x00C1, r1	; 0x8000c1 <__stack+0x7ff7c2>
 36e:	e7 ea       	ldi	r30, 0xA7	; 167
 370:	f0 e0       	ldi	r31, 0x00	; 0
 372:	24 91       	lpm	r18, Z
 374:	e3 e9       	ldi	r30, 0x93	; 147
 376:	f0 e0       	ldi	r31, 0x00	; 0
 378:	84 91       	lpm	r24, Z
 37a:	88 23       	and	r24, r24
 37c:	99 f0       	breq	.+38     	; 0x3a4 <main+0xbc>
 37e:	90 e0       	ldi	r25, 0x00	; 0
 380:	88 0f       	add	r24, r24
 382:	99 1f       	adc	r25, r25
 384:	fc 01       	movw	r30, r24
 386:	e8 59       	subi	r30, 0x98	; 152
 388:	ff 4f       	sbci	r31, 0xFF	; 255
 38a:	a5 91       	lpm	r26, Z+
 38c:	b4 91       	lpm	r27, Z
 38e:	fc 01       	movw	r30, r24
 390:	e4 58       	subi	r30, 0x84	; 132
 392:	ff 4f       	sbci	r31, 0xFF	; 255
 394:	85 91       	lpm	r24, Z+
 396:	94 91       	lpm	r25, Z
 398:	8f b7       	in	r24, 0x3f	; 63
 39a:	f8 94       	cli
 39c:	ec 91       	ld	r30, X
 39e:	e2 2b       	or	r30, r18
 3a0:	ec 93       	st	X, r30
 3a2:	8f bf       	out	0x3f, r24	; 63
 3a4:	ce e9       	ldi	r28, 0x9E	; 158
 3a6:	d0 e0       	ldi	r29, 0x00	; 0
 3a8:	fe 01       	movw	r30, r28
 3aa:	24 91       	lpm	r18, Z
 3ac:	0a e8       	ldi	r16, 0x8A	; 138
 3ae:	10 e0       	ldi	r17, 0x00	; 0
 3b0:	f8 01       	movw	r30, r16
 3b2:	84 91       	lpm	r24, Z
 3b4:	88 23       	and	r24, r24
 3b6:	c9 f0       	breq	.+50     	; 0x3ea <main+0x102>
 3b8:	90 e0       	ldi	r25, 0x00	; 0
 3ba:	88 0f       	add	r24, r24
 3bc:	99 1f       	adc	r25, r25
 3be:	fc 01       	movw	r30, r24
 3c0:	e8 59       	subi	r30, 0x98	; 152
 3c2:	ff 4f       	sbci	r31, 0xFF	; 255
 3c4:	a5 91       	lpm	r26, Z+
 3c6:	b4 91       	lpm	r27, Z
 3c8:	84 58       	subi	r24, 0x84	; 132
 3ca:	9f 4f       	sbci	r25, 0xFF	; 255
 3cc:	fc 01       	movw	r30, r24
 3ce:	45 91       	lpm	r20, Z+
 3d0:	54 91       	lpm	r21, Z
 3d2:	9f b7       	in	r25, 0x3f	; 63
 3d4:	f8 94       	cli
 3d6:	3c 91       	ld	r19, X
 3d8:	82 2f       	mov	r24, r18
 3da:	80 95       	com	r24
 3dc:	83 23       	and	r24, r19
 3de:	8c 93       	st	X, r24
 3e0:	fa 01       	movw	r30, r20
 3e2:	80 81       	ld	r24, Z
 3e4:	28 2b       	or	r18, r24
 3e6:	20 83       	st	Z, r18
 3e8:	9f bf       	out	0x3f, r25	; 63
 3ea:	92 eb       	ldi	r25, 0xB2	; 178
 3ec:	e9 2e       	mov	r14, r25
 3ee:	90 e0       	ldi	r25, 0x00	; 0
 3f0:	f9 2e       	mov	r15, r25
 3f2:	20 e0       	ldi	r18, 0x00	; 0
 3f4:	c2 2e       	mov	r12, r18
 3f6:	20 e0       	ldi	r18, 0x00	; 0
 3f8:	d2 2e       	mov	r13, r18
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
