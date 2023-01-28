.include "macros.inc"

.section .text  # 0x0 - 0x28

.global test
test:
/* 00000000 00000000  C0 40 00 00 */	lfs f2, $$22@sda21(r13)
/* 00000004 00000004  3C 60 00 00 */	lis r3, $$25@ha
/* 00000008 00000008  C8 20 00 00 */	lfd f1, $$23@sda21(r13)
/* 0000000C 0000000C  38 03 00 00 */	addi r0, r3, $$25@l
/* 00000010 00000010  C8 00 00 00 */	lfd f0, $$24@sda21(r13)
/* 00000014 00000014  D0 40 00 00 */	stfs f2, a@sda21(r2)
/* 00000018 00000018  D8 20 00 00 */	stfd f1, b@sda21(r2)
/* 0000001C 0000001C  D8 00 00 00 */	stfd f0, c@sda21(r2)
/* 00000020 00000020  90 00 00 00 */	stw r0, d@sda21(r2)
/* 00000024 00000024  4E 80 00 20 */	blr 

.section .data  # 0x0 - 0xa

.global $$25
$$25:
	.word 0x2268656c
	.word 0x6c6f220a
	.bytes 0x1, 0x0

.section .sbss  # 0x0 - 0x1c

.global d
d:
	.word 0x00000000
	.word 0x00000000

.global c
c:
	.word 0x00000000
	.word 0x00000000

.global b
b:
	.word 0x00000000
	.word 0x00000000

.global a
a:
	.word 0x00000000

.section .sdata2  # 0x0 - 0x18

.global $$22
$$22:
	.word 0x3f99999a
	.word 0x00000000

.global $$23
$$23:
	.word 0x402a0000
	.word 0x00000000

.global $$24
$$24:
	.word 0x420a13b8
	.word 0x60000000

