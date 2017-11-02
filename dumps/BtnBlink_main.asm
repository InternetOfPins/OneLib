000001e2 <main>:
 1e2:	78 94       	sei
 1e4:	84 b5       	in	r24, 0x24	; 36
 1e6:	82 60       	ori	r24, 0x02	; 2
 1e8:	84 bd       	out	0x24, r24	; 36
 1ea:	84 b5       	in	r24, 0x24	; 36
 1ec:	81 60       	ori	r24, 0x01	; 1
 1ee:	84 bd       	out	0x24, r24	; 36
 1f0:	85 b5       	in	r24, 0x25	; 37
 1f2:	82 60       	ori	r24, 0x02	; 2
 1f4:	85 bd       	out	0x25, r24	; 37
 1f6:	85 b5       	in	r24, 0x25	; 37
 1f8:	81 60       	ori	r24, 0x01	; 1
 1fa:	85 bd       	out	0x25, r24	; 37
 1fc:	80 91 6e 00 	lds	r24, 0x006E	; 0x80006e <__stack+0x7ff76f>
 200:	81 60       	ori	r24, 0x01	; 1
 202:	80 93 6e 00 	sts	0x006E, r24	; 0x80006e <__stack+0x7ff76f>
 206:	10 92 81 00 	sts	0x0081, r1	; 0x800081 <__stack+0x7ff782>
 20a:	80 91 81 00 	lds	r24, 0x0081	; 0x800081 <__stack+0x7ff782>
 20e:	82 60       	ori	r24, 0x02	; 2
 210:	80 93 81 00 	sts	0x0081, r24	; 0x800081 <__stack+0x7ff782>
 214:	80 91 81 00 	lds	r24, 0x0081	; 0x800081 <__stack+0x7ff782>
 218:	81 60       	ori	r24, 0x01	; 1
 21a:	80 93 81 00 	sts	0x0081, r24	; 0x800081 <__stack+0x7ff782>
 21e:	80 91 80 00 	lds	r24, 0x0080	; 0x800080 <__stack+0x7ff781>
 222:	81 60       	ori	r24, 0x01	; 1
 224:	80 93 80 00 	sts	0x0080, r24	; 0x800080 <__stack+0x7ff781>
 228:	80 91 b1 00 	lds	r24, 0x00B1	; 0x8000b1 <__stack+0x7ff7b2>
 22c:	84 60       	ori	r24, 0x04	; 4
 22e:	80 93 b1 00 	sts	0x00B1, r24	; 0x8000b1 <__stack+0x7ff7b2>
 232:	80 91 b0 00 	lds	r24, 0x00B0	; 0x8000b0 <__stack+0x7ff7b1>
 236:	81 60       	ori	r24, 0x01	; 1
 238:	80 93 b0 00 	sts	0x00B0, r24	; 0x8000b0 <__stack+0x7ff7b1>
 23c:	80 91 7a 00 	lds	r24, 0x007A	; 0x80007a <__stack+0x7ff77b>
 240:	84 60       	ori	r24, 0x04	; 4
 242:	80 93 7a 00 	sts	0x007A, r24	; 0x80007a <__stack+0x7ff77b>
 246:	80 91 7a 00 	lds	r24, 0x007A	; 0x80007a <__stack+0x7ff77b>
 24a:	82 60       	ori	r24, 0x02	; 2
 24c:	80 93 7a 00 	sts	0x007A, r24	; 0x80007a <__stack+0x7ff77b>
 250:	80 91 7a 00 	lds	r24, 0x007A	; 0x80007a <__stack+0x7ff77b>
 254:	81 60       	ori	r24, 0x01	; 1
 256:	80 93 7a 00 	sts	0x007A, r24	; 0x80007a <__stack+0x7ff77b>
 25a:	80 91 7a 00 	lds	r24, 0x007A	; 0x80007a <__stack+0x7ff77b>
 25e:	80 68       	ori	r24, 0x80	; 128
 260:	80 93 7a 00 	sts	0x007A, r24	; 0x80007a <__stack+0x7ff77b>
 264:	10 92 c1 00 	sts	0x00C1, r1	; 0x8000c1 <__stack+0x7ff7c2>
 268:	25 9a       	sbi	0x04, 5	; 4
 26a:	54 98       	cbi	0x0a, 4	; 10
 26c:	5c 9a       	sbi	0x0b, 4	; 11
 26e:	c0 e0       	ldi	r28, 0x00	; 0
 270:	d0 e0       	ldi	r29, 0x00	; 0
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
