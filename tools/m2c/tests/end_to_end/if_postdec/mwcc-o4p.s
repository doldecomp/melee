.include "macros.inc"

.section .text  # 0x0 - 0x24

.global test
test:
/* 00000000 00000000  80 60 00 00 */	lwz r3, glob@sda21(r2)
/* 00000004 00000004  38 03 FF FF */	addi r0, r3, -1
/* 00000008 00000008  2C 03 00 01 */	cmpwi r3, 1
/* 0000000C 0000000C  90 00 00 00 */	stw r0, glob@sda21(r2)
/* 00000010 00000010  40 80 00 0C */	bge .L0000001C
/* 00000014 00000014  38 60 00 04 */	li r3, 4
/* 00000018 00000018  4E 80 00 20 */	blr 
.L0000001C:
/* 0000001C 0000001C  38 60 00 06 */	li r3, 6
/* 00000020 00000020  4E 80 00 20 */	blr 

.section .sbss  # 0x0 - 0x4

.global glob
glob:
	.word 0x00000000

