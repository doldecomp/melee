.include "macros.inc"

.section .text  # 0x0 - 0x3c

.global test
test:
/* 00000000 00000000  88 00 00 00 */	lbz r0, a@sda21(r2)
/* 00000004 00000004  3C 60 00 00 */	lis r3, ar@ha
/* 00000008 00000008  7C 00 07 74 */	extsb r0, r0
/* 0000000C 0000000C  94 03 00 00 */	stwu r0, ar@l(r3)
/* 00000010 00000010  88 00 00 00 */	lbz r0, b@sda21(r2)
/* 00000014 00000014  90 03 00 04 */	stw r0, 4(r3)
/* 00000018 00000018  A8 00 00 00 */	lha r0, c@sda21(r2)
/* 0000001C 0000001C  90 03 00 08 */	stw r0, 8(r3)
/* 00000020 00000020  A0 00 00 00 */	lhz r0, d@sda21(r2)
/* 00000024 00000024  90 03 00 0C */	stw r0, 0xc(r3)
/* 00000028 00000028  80 00 00 00 */	lwz r0, e@sda21(r2)
/* 0000002C 0000002C  90 03 00 10 */	stw r0, 0x10(r3)
/* 00000030 00000030  80 00 00 00 */	lwz r0, f@sda21(r2)
/* 00000034 00000034  90 03 00 14 */	stw r0, 0x14(r3)
/* 00000038 00000038  4E 80 00 20 */	blr 

.section .bss  # 0x0 - 0x18

.global ar
ar:
	.word 0x00000000
	.word 0x00000000
	.word 0x00000000
	.word 0x00000000
	.word 0x00000000
	.word 0x00000000

.section .sbss  # 0x0 - 0xe

.global f
f:
	.word 0x00000000

.global e
e:
	.word 0x00000000

.global d
d:
	.bytes 0x0, 0x0

.global c
c:
	.bytes 0x0, 0x0

.global b
b:
	.bytes 0x0

.global a
a:
	.bytes 0x0

