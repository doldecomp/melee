.include "macros.inc"

.section .text  # 0x0 - 0x1c

.global test
test:
/* 00000000 00000000  38 00 00 01 */	li r0, 1
.L00000004:
/* 00000004 00000004  80 60 00 00 */	lwz r3, x@sda21(r2)
/* 00000008 00000008  2C 03 00 02 */	cmpwi r3, 2
/* 0000000C 0000000C  4D 82 00 20 */	beqlr 
/* 00000010 00000010  90 00 00 00 */	stw r0, x@sda21(r2)
/* 00000014 00000014  4B FF FF F0 */	b .L00000004
/* 00000018 00000018  4E 80 00 20 */	blr 

.section .sbss  # 0x0 - 0x4

.global x
x:
	.word 0x00000000

