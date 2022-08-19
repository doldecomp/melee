.include "macros.inc"

.section .text  # 0x0 - 0x24

.global test
test:
/* 00000000 00000000  C8 20 00 00 */	lfd f1, y@sda21(r2)
/* 00000004 00000004  C8 00 00 00 */	lfd f0, $$23@sda21(r13)
/* 00000008 00000008  C0 60 00 00 */	lfs f3, x@sda21(r2)
/* 0000000C 0000000C  C0 40 00 00 */	lfs f2, $$22@sda21(r13)
/* 00000010 00000010  FC 01 00 32 */	fmul f0, f1, f0
/* 00000014 00000014  EC 23 00 B2 */	fmuls f1, f3, f2
/* 00000018 00000018  D8 00 00 00 */	stfd f0, y@sda21(r2)
/* 0000001C 0000001C  D0 20 00 00 */	stfs f1, x@sda21(r2)
/* 00000020 00000020  4E 80 00 20 */	blr 

.section .sbss  # 0x0 - 0xc

.global y
y:
	.word 0x00000000
	.word 0x00000000

.global x
x:
	.word 0x00000000

.section .sdata2  # 0x0 - 0x10

.global $$22
$$22:
	.word 0x40000000
	.word 0x00000000

.global $$23
$$23:
	.word 0x40000000
	.word 0x00000000

