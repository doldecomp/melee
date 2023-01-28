.include "macros.inc"

.section .text  # 0x0 - 0x10

.global test
test:
/* 00000000 00000000  3C 63 00 01 */	addis r3, r3, 1
/* 00000004 00000004  84 03 23 48 */	lwzu r0, 0x2348(r3)
/* 00000008 00000008  90 00 00 00 */	stw r0, glob@sda21(r2)
/* 0000000C 0000000C  4E 80 00 20 */	blr 

.section .sbss  # 0x0 - 0x4

.global glob
glob:
	.word 0x00000000

