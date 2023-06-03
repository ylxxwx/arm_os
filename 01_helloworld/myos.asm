
myos.elf:     file format elf64-littleaarch64


Disassembly of section .startup:

0000000040000000 <entry>:
    40000000:	5800009e 	ldr	x30, 40000010 <entry+0x10>
    40000004:	910003df 	mov	sp, x30
    40000008:	940000bd 	bl	400002fc <main>
    4000000c:	14000000 	b	4000000c <entry+0xc>
    40000010:	40001490 	.inst	0x40001490 ; undefined
    40000014:	00000000 	udf	#0

Disassembly of section .text:

0000000040000018 <sleep>:
    40000018:	d10043ff 	sub	sp, sp, #0x10
    4000001c:	b9000fe0 	str	w0, [sp, #12]
    40000020:	d503201f 	nop
    40000024:	b9400fe0 	ldr	w0, [sp, #12]
    40000028:	51000401 	sub	w1, w0, #0x1
    4000002c:	b9000fe1 	str	w1, [sp, #12]
    40000030:	7100001f 	cmp	w0, #0x0
    40000034:	54ffff81 	b.ne	40000024 <sleep+0xc>  // b.any
    40000038:	d503201f 	nop
    4000003c:	d503201f 	nop
    40000040:	910043ff 	add	sp, sp, #0x10
    40000044:	d65f03c0 	ret

0000000040000048 <pull_up>:
    40000048:	a9be7bfd 	stp	x29, x30, [sp, #-32]!
    4000004c:	910003fd 	mov	x29, sp
    40000050:	b9001fe0 	str	w0, [sp, #28]
    40000054:	90000000 	adrp	x0, 40000000 <entry>
    40000058:	f9423400 	ldr	x0, [x0, #1128]
    4000005c:	f9400000 	ldr	x0, [x0]
    40000060:	91025000 	add	x0, x0, #0x94
    40000064:	52800041 	mov	w1, #0x2                   	// #2
    40000068:	b9000001 	str	w1, [x0]
    4000006c:	528012c0 	mov	w0, #0x96                  	// #150
    40000070:	97ffffea 	bl	40000018 <sleep>
    40000074:	b9401fe0 	ldr	w0, [sp, #28]
    40000078:	52800021 	mov	w1, #0x1                   	// #1
    4000007c:	1ac02021 	lsl	w1, w1, w0
    40000080:	90000000 	adrp	x0, 40000000 <entry>
    40000084:	f9423400 	ldr	x0, [x0, #1128]
    40000088:	f9400000 	ldr	x0, [x0]
    4000008c:	91026000 	add	x0, x0, #0x98
    40000090:	b9000001 	str	w1, [x0]
    40000094:	528012c0 	mov	w0, #0x96                  	// #150
    40000098:	97ffffe0 	bl	40000018 <sleep>
    4000009c:	90000000 	adrp	x0, 40000000 <entry>
    400000a0:	f9423400 	ldr	x0, [x0, #1128]
    400000a4:	f9400000 	ldr	x0, [x0]
    400000a8:	91025000 	add	x0, x0, #0x94
    400000ac:	b900001f 	str	wzr, [x0]
    400000b0:	90000000 	adrp	x0, 40000000 <entry>
    400000b4:	f9423400 	ldr	x0, [x0, #1128]
    400000b8:	f9400000 	ldr	x0, [x0]
    400000bc:	91026000 	add	x0, x0, #0x98
    400000c0:	b900001f 	str	wzr, [x0]
    400000c4:	d503201f 	nop
    400000c8:	a8c27bfd 	ldp	x29, x30, [sp], #32
    400000cc:	d65f03c0 	ret

00000000400000d0 <pull_down>:
    400000d0:	a9be7bfd 	stp	x29, x30, [sp, #-32]!
    400000d4:	910003fd 	mov	x29, sp
    400000d8:	b9001fe0 	str	w0, [sp, #28]
    400000dc:	90000000 	adrp	x0, 40000000 <entry>
    400000e0:	f9423400 	ldr	x0, [x0, #1128]
    400000e4:	f9400000 	ldr	x0, [x0]
    400000e8:	91025000 	add	x0, x0, #0x94
    400000ec:	52800021 	mov	w1, #0x1                   	// #1
    400000f0:	b9000001 	str	w1, [x0]
    400000f4:	528012c0 	mov	w0, #0x96                  	// #150
    400000f8:	97ffffc8 	bl	40000018 <sleep>
    400000fc:	b9401fe0 	ldr	w0, [sp, #28]
    40000100:	52800021 	mov	w1, #0x1                   	// #1
    40000104:	1ac02021 	lsl	w1, w1, w0
    40000108:	90000000 	adrp	x0, 40000000 <entry>
    4000010c:	f9423400 	ldr	x0, [x0, #1128]
    40000110:	f9400000 	ldr	x0, [x0]
    40000114:	91026000 	add	x0, x0, #0x98
    40000118:	b9000001 	str	w1, [x0]
    4000011c:	528012c0 	mov	w0, #0x96                  	// #150
    40000120:	97ffffbe 	bl	40000018 <sleep>
    40000124:	90000000 	adrp	x0, 40000000 <entry>
    40000128:	f9423400 	ldr	x0, [x0, #1128]
    4000012c:	f9400000 	ldr	x0, [x0]
    40000130:	91025000 	add	x0, x0, #0x94
    40000134:	b900001f 	str	wzr, [x0]
    40000138:	90000000 	adrp	x0, 40000000 <entry>
    4000013c:	f9423400 	ldr	x0, [x0, #1128]
    40000140:	f9400000 	ldr	x0, [x0]
    40000144:	91026000 	add	x0, x0, #0x98
    40000148:	b900001f 	str	wzr, [x0]
    4000014c:	d503201f 	nop
    40000150:	a8c27bfd 	ldp	x29, x30, [sp], #32
    40000154:	d65f03c0 	ret

0000000040000158 <pull_disable>:
    40000158:	a9be7bfd 	stp	x29, x30, [sp, #-32]!
    4000015c:	910003fd 	mov	x29, sp
    40000160:	b9001fe0 	str	w0, [sp, #28]
    40000164:	90000000 	adrp	x0, 40000000 <entry>
    40000168:	f9423400 	ldr	x0, [x0, #1128]
    4000016c:	f9400000 	ldr	x0, [x0]
    40000170:	91025000 	add	x0, x0, #0x94
    40000174:	b900001f 	str	wzr, [x0]
    40000178:	528012c0 	mov	w0, #0x96                  	// #150
    4000017c:	97ffffa7 	bl	40000018 <sleep>
    40000180:	b9401fe0 	ldr	w0, [sp, #28]
    40000184:	52800021 	mov	w1, #0x1                   	// #1
    40000188:	1ac02021 	lsl	w1, w1, w0
    4000018c:	90000000 	adrp	x0, 40000000 <entry>
    40000190:	f9423400 	ldr	x0, [x0, #1128]
    40000194:	f9400000 	ldr	x0, [x0]
    40000198:	91026000 	add	x0, x0, #0x98
    4000019c:	b9000001 	str	w1, [x0]
    400001a0:	528012c0 	mov	w0, #0x96                  	// #150
    400001a4:	97ffff9d 	bl	40000018 <sleep>
    400001a8:	90000000 	adrp	x0, 40000000 <entry>
    400001ac:	f9423400 	ldr	x0, [x0, #1128]
    400001b0:	f9400000 	ldr	x0, [x0]
    400001b4:	91025000 	add	x0, x0, #0x94
    400001b8:	b900001f 	str	wzr, [x0]
    400001bc:	90000000 	adrp	x0, 40000000 <entry>
    400001c0:	f9423400 	ldr	x0, [x0, #1128]
    400001c4:	f9400000 	ldr	x0, [x0]
    400001c8:	91026000 	add	x0, x0, #0x98
    400001cc:	b900001f 	str	wzr, [x0]
    400001d0:	d503201f 	nop
    400001d4:	a8c27bfd 	ldp	x29, x30, [sp], #32
    400001d8:	d65f03c0 	ret

00000000400001dc <led_init>:
    400001dc:	a9bf7bfd 	stp	x29, x30, [sp, #-16]!
    400001e0:	910003fd 	mov	x29, sp
    400001e4:	90000000 	adrp	x0, 40000000 <entry>
    400001e8:	f9423400 	ldr	x0, [x0, #1128]
    400001ec:	d2a7e401 	mov	x1, #0x3f200000            	// #1059061760
    400001f0:	f9000001 	str	x1, [x0]
    400001f4:	90000000 	adrp	x0, 40000000 <entry>
    400001f8:	f9423400 	ldr	x0, [x0, #1128]
    400001fc:	f9400000 	ldr	x0, [x0]
    40000200:	91002000 	add	x0, x0, #0x8
    40000204:	b9400001 	ldr	w1, [x0]
    40000208:	90000000 	adrp	x0, 40000000 <entry>
    4000020c:	f9423400 	ldr	x0, [x0, #1128]
    40000210:	f9400000 	ldr	x0, [x0]
    40000214:	91002000 	add	x0, x0, #0x8
    40000218:	121d7021 	and	w1, w1, #0xfffffff8
    4000021c:	b9000001 	str	w1, [x0]
    40000220:	90000000 	adrp	x0, 40000000 <entry>
    40000224:	f9423400 	ldr	x0, [x0, #1128]
    40000228:	f9400000 	ldr	x0, [x0]
    4000022c:	91002000 	add	x0, x0, #0x8
    40000230:	b9400001 	ldr	w1, [x0]
    40000234:	90000000 	adrp	x0, 40000000 <entry>
    40000238:	f9423400 	ldr	x0, [x0, #1128]
    4000023c:	f9400000 	ldr	x0, [x0]
    40000240:	91002000 	add	x0, x0, #0x8
    40000244:	321d0021 	orr	w1, w1, #0x8
    40000248:	b9000001 	str	w1, [x0]
    4000024c:	52800280 	mov	w0, #0x14                  	// #20
    40000250:	97ffffa0 	bl	400000d0 <pull_down>
    40000254:	d503201f 	nop
    40000258:	a8c17bfd 	ldp	x29, x30, [sp], #16
    4000025c:	d65f03c0 	ret

0000000040000260 <gpio_pin_on>:
    40000260:	d10043ff 	sub	sp, sp, #0x10
    40000264:	b9000fe0 	str	w0, [sp, #12]
    40000268:	b9400fe0 	ldr	w0, [sp, #12]
    4000026c:	52800021 	mov	w1, #0x1                   	// #1
    40000270:	1ac02021 	lsl	w1, w1, w0
    40000274:	90000000 	adrp	x0, 40000000 <entry>
    40000278:	f9423400 	ldr	x0, [x0, #1128]
    4000027c:	f9400000 	ldr	x0, [x0]
    40000280:	91007000 	add	x0, x0, #0x1c
    40000284:	b9000001 	str	w1, [x0]
    40000288:	d503201f 	nop
    4000028c:	910043ff 	add	sp, sp, #0x10
    40000290:	d65f03c0 	ret

0000000040000294 <gpio_pin_off>:
    40000294:	d10043ff 	sub	sp, sp, #0x10
    40000298:	b9000fe0 	str	w0, [sp, #12]
    4000029c:	b9400fe0 	ldr	w0, [sp, #12]
    400002a0:	52800021 	mov	w1, #0x1                   	// #1
    400002a4:	1ac02021 	lsl	w1, w1, w0
    400002a8:	90000000 	adrp	x0, 40000000 <entry>
    400002ac:	f9423400 	ldr	x0, [x0, #1128]
    400002b0:	f9400000 	ldr	x0, [x0]
    400002b4:	9100a000 	add	x0, x0, #0x28
    400002b8:	b9000001 	str	w1, [x0]
    400002bc:	d503201f 	nop
    400002c0:	910043ff 	add	sp, sp, #0x10
    400002c4:	d65f03c0 	ret

00000000400002c8 <gpio_pin_read>:
    400002c8:	d10043ff 	sub	sp, sp, #0x10
    400002cc:	b9000fe0 	str	w0, [sp, #12]
    400002d0:	90000000 	adrp	x0, 40000000 <entry>
    400002d4:	f9423400 	ldr	x0, [x0, #1128]
    400002d8:	f9400000 	ldr	x0, [x0]
    400002dc:	9100d000 	add	x0, x0, #0x34
    400002e0:	b9400000 	ldr	w0, [x0]
    400002e4:	b9400fe1 	ldr	w1, [sp, #12]
    400002e8:	52800022 	mov	w2, #0x1                   	// #1
    400002ec:	1ac12041 	lsl	w1, w2, w1
    400002f0:	0a010000 	and	w0, w0, w1
    400002f4:	910043ff 	add	sp, sp, #0x10
    400002f8:	d65f03c0 	ret

00000000400002fc <main>:
    400002fc:	a9be7bfd 	stp	x29, x30, [sp, #-32]!
    40000300:	910003fd 	mov	x29, sp
    40000304:	b9001bff 	str	wzr, [sp, #24]
    40000308:	97ffffb5 	bl	400001dc <led_init>
    4000030c:	b9401be0 	ldr	w0, [sp, #24]
    40000310:	b9001fe0 	str	w0, [sp, #28]
    40000314:	b9401fe0 	ldr	w0, [sp, #28]
    40000318:	7100001f 	cmp	w0, #0x0
    4000031c:	540000a0 	b.eq	40000330 <main+0x34>  // b.none
    40000320:	528002a0 	mov	w0, #0x15                  	// #21
    40000324:	97ffffcf 	bl	40000260 <gpio_pin_on>
    40000328:	b9001bff 	str	wzr, [sp, #24]
    4000032c:	14000005 	b	40000340 <main+0x44>
    40000330:	528002a0 	mov	w0, #0x15                  	// #21
    40000334:	97ffffd8 	bl	40000294 <gpio_pin_off>
    40000338:	52800020 	mov	w0, #0x1                   	// #1
    4000033c:	b9001be0 	str	w0, [sp, #24]
    40000340:	52942400 	mov	w0, #0xa120                	// #41248
    40000344:	72a000e0 	movk	w0, #0x7, lsl #16
    40000348:	97ffff34 	bl	40000018 <sleep>
    4000034c:	17fffff0 	b	4000030c <main+0x10>

Disassembly of section .eh_frame:

0000000040000350 <.eh_frame>:
    40000350:	00000010 	udf	#16
    40000354:	00000000 	udf	#0
    40000358:	00527a01 	.inst	0x00527a01 ; undefined
    4000035c:	011e7804 	.inst	0x011e7804 ; undefined
    40000360:	001f0c1b 	.inst	0x001f0c1b ; undefined
    40000364:	00000014 	udf	#20
    40000368:	00000018 	udf	#24
    4000036c:	fffffcac 	.inst	0xfffffcac ; undefined
    40000370:	00000030 	udf	#48
    40000374:	100e4100 	adr	x0, 4001cb94 <stack_top+0x1b704>
    40000378:	00000e4a 	udf	#3658
    4000037c:	0000001c 	udf	#28
    40000380:	00000030 	udf	#48
    40000384:	fffffcc4 	.inst	0xfffffcc4 ; undefined
    40000388:	00000088 	udf	#136
    4000038c:	200e4100 	.inst	0x200e4100 ; undefined
    40000390:	039e049d 	.inst	0x039e049d ; undefined
    40000394:	0eddde60 	.inst	0x0eddde60 ; undefined
    40000398:	00000000 	udf	#0
    4000039c:	0000001c 	udf	#28
    400003a0:	00000050 	udf	#80
    400003a4:	fffffd2c 	.inst	0xfffffd2c ; undefined
    400003a8:	00000088 	udf	#136
    400003ac:	200e4100 	.inst	0x200e4100 ; undefined
    400003b0:	039e049d 	.inst	0x039e049d ; undefined
    400003b4:	0eddde60 	.inst	0x0eddde60 ; undefined
    400003b8:	00000000 	udf	#0
    400003bc:	0000001c 	udf	#28
    400003c0:	00000070 	udf	#112
    400003c4:	fffffd94 	.inst	0xfffffd94 ; undefined
    400003c8:	00000084 	udf	#132
    400003cc:	200e4100 	.inst	0x200e4100 ; undefined
    400003d0:	039e049d 	.inst	0x039e049d ; undefined
    400003d4:	0eddde5f 	.inst	0x0eddde5f ; undefined
    400003d8:	00000000 	udf	#0
    400003dc:	0000001c 	udf	#28
    400003e0:	00000090 	udf	#144
    400003e4:	fffffdf8 	.inst	0xfffffdf8 ; undefined
    400003e8:	00000084 	udf	#132
    400003ec:	100e4100 	adr	x0, 4001cc0c <stack_top+0x1b77c>
    400003f0:	019e029d 	.inst	0x019e029d ; undefined
    400003f4:	0eddde5f 	.inst	0x0eddde5f ; undefined
    400003f8:	00000000 	udf	#0
    400003fc:	00000014 	udf	#20
    40000400:	000000b0 	udf	#176
    40000404:	fffffe5c 	.inst	0xfffffe5c ; undefined
    40000408:	00000034 	udf	#52
    4000040c:	100e4100 	adr	x0, 4001cc2c <stack_top+0x1b79c>
    40000410:	00000e4b 	udf	#3659
    40000414:	00000014 	udf	#20
    40000418:	000000c8 	udf	#200
    4000041c:	fffffe78 	.inst	0xfffffe78 ; undefined
    40000420:	00000034 	udf	#52
    40000424:	100e4100 	adr	x0, 4001cc44 <stack_top+0x1b7b4>
    40000428:	00000e4b 	udf	#3659
    4000042c:	00000014 	udf	#20
    40000430:	000000e0 	udf	#224
    40000434:	fffffe94 	.inst	0xfffffe94 ; undefined
    40000438:	00000034 	udf	#52
    4000043c:	100e4100 	adr	x0, 4001cc5c <stack_top+0x1b7cc>
    40000440:	00000e4b 	udf	#3659
    40000444:	00000014 	udf	#20
    40000448:	000000f8 	udf	#248
    4000044c:	fffffeb0 	.inst	0xfffffeb0 ; undefined
    40000450:	00000054 	udf	#84
    40000454:	200e4100 	.inst	0x200e4100 ; undefined
    40000458:	039e049d 	.inst	0x039e049d ; undefined

Disassembly of section .got:

0000000040000460 <_GLOBAL_OFFSET_TABLE_>:
	...
    40000468:	40000488 	.inst	0x40000488 ; undefined
    4000046c:	00000000 	udf	#0

Disassembly of section .got.plt:

0000000040000470 <.got.plt>:
	...

Disassembly of section .bss:

0000000040000488 <gpio>:
	...

Disassembly of section .debug_line:

0000000000000000 <.debug_line>:
   0:	00000046 	udf	#70
   4:	00080005 	.inst	0x00080005 ; undefined
   8:	0000002a 	udf	#42
   c:	fb010104 	.inst	0xfb010104 ; undefined
  10:	01000d0e 	.inst	0x01000d0e ; undefined
  14:	00010101 	.inst	0x00010101 ; undefined
  18:	00010000 	.inst	0x00010000 ; undefined
  1c:	01010100 	.inst	0x01010100 ; undefined
  20:	0000011f 	udf	#287
  24:	01020000 	.inst	0x01020000 ; undefined
  28:	020f021f 	.inst	0x020f021f ; undefined
  2c:	00000026 	udf	#38
  30:	00002600 	udf	#9728
  34:	09000000 	.inst	0x09000000 ; undefined
  38:	00000002 	udf	#2
  3c:	00000040 	udf	#64
  40:	21211600 	.inst	0x21211600 ; undefined
  44:	00030221 	.inst	0x00030221 ; undefined
  48:	Address 0x0000000000000048 is out of bounds.


Disassembly of section .debug_line_str:

0000000000000000 <.debug_line_str>:
   0:	6d6f682f 	ldp	d15, d26, [x1, #-272]
   4:	6d6b2f65 	ldp	d5, d11, [x27, #-336]
   8:	30332f74 	adr	x20, 665f5 <entry-0x3ff99a0b>
   c:	4d52415f 	.inst	0x4d52415f ; undefined
  10:	6d72612f 	ldp	d15, d24, [x9, #-224]
  14:	2f736f5f 	.inst	0x2f736f5f ; undefined
  18:	685f3130 	.inst	0x685f3130 ; undefined
  1c:	6f6c6c65 	.inst	0x6f6c6c65 ; undefined
  20:	6c726f77 	ldnp	d23, d27, [x27, #-224]
  24:	74730064 	.inst	0x74730064 ; undefined
  28:	2e747261 	uabdl	v1.4s, v19.4h, v20.4h
  2c:	Address 0x000000000000002c is out of bounds.


Disassembly of section .debug_info:

0000000000000000 <.debug_info>:
   0:	00000024 	udf	#36
   4:	08010005 	stxrb	w1, w5, [x0]
   8:	00000000 	udf	#0
   c:	00000001 	udf	#1
  10:	00000000 	udf	#0
  14:	00000040 	udf	#64
  18:	00001800 	udf	#6144
  1c:	00080000 	.inst	0x00080000 ; undefined
  20:	002e0000 	.inst	0x002e0000 ; NYI
  24:	80010000 	.inst	0x80010000 ; undefined

Disassembly of section .debug_abbrev:

0000000000000000 <.debug_abbrev>:
   0:	10001101 	adr	x1, 220 <entry-0x3ffffde0>
   4:	12011117 	and	w23, w8, #0x8000000f
   8:	1b0e030f 	madd	w15, w24, w14, w0
   c:	130e250e 	sbfiz	w14, w8, #18, #10
  10:	00000005 	udf	#5

Disassembly of section .debug_aranges:

0000000000000000 <.debug_aranges>:
   0:	0000002c 	udf	#44
   4:	00000002 	udf	#2
   8:	00080000 	.inst	0x00080000 ; undefined
   c:	00000000 	udf	#0
  10:	40000000 	.inst	0x40000000 ; undefined
  14:	00000000 	udf	#0
  18:	00000018 	udf	#24
	...

Disassembly of section .debug_str:

0000000000000000 <.debug_str>:
   0:	72617473 	.inst	0x72617473 ; undefined
   4:	00532e74 	.inst	0x00532e74 ; undefined
   8:	6d6f682f 	ldp	d15, d26, [x1, #-272]
   c:	6d6b2f65 	ldp	d5, d11, [x27, #-336]
  10:	30332f74 	adr	x20, 665fd <entry-0x3ff99a03>
  14:	4d52415f 	.inst	0x4d52415f ; undefined
  18:	6d72612f 	ldp	d15, d24, [x9, #-224]
  1c:	2f736f5f 	.inst	0x2f736f5f ; undefined
  20:	685f3130 	.inst	0x685f3130 ; undefined
  24:	6f6c6c65 	.inst	0x6f6c6c65 ; undefined
  28:	6c726f77 	ldnp	d23, d27, [x27, #-224]
  2c:	4e470064 	.inst	0x4e470064 ; undefined
  30:	53412055 	.inst	0x53412055 ; undefined
  34:	332e3220 	.inst	0x332e3220 ; undefined
  38:	Address 0x0000000000000038 is out of bounds.


Disassembly of section .comment:

0000000000000000 <.comment>:
   0:	3a434347 	ccmn	w26, w3, #0x7, mi	// mi = first
   4:	62552820 	.inst	0x62552820 ; undefined
   8:	75746e75 	.inst	0x75746e75 ; undefined
   c:	2e323120 	usubw	v0.8h, v9.8h, v18.8b
  10:	2d302e32 	stp	s18, s11, [x17, #-128]
  14:	75627533 	.inst	0x75627533 ; undefined
  18:	3175746e 	adds	w14, w3, #0xd5d, lsl #12
  1c:	32312029 	orr	w9, w1, #0xff8000
  20:	302e322e 	adr	x14, 5c665 <entry-0x3ffa399b>
	...
