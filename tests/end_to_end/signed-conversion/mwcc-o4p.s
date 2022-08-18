.include "macros.inc"

.section .text  # 0x0 - 0x3c

.global test
test:
/* 00000000 00000000  7C 60 07 74 */	extsb r0, r3
/* 00000004 00000004  54 65 08 3C */	slwi r5, r3, 1
/* 00000008 00000008  90 00 00 00 */	stw r0, glob@sda21(r2)
/* 0000000C 0000000C  1C C3 00 03 */	mulli r6, r3, 3
/* 00000010 00000010  7C A0 07 74 */	extsb r0, r5
/* 00000014 00000014  90 00 00 00 */	stw r0, glob@sda21(r2)
/* 00000018 00000018  7C C0 07 74 */	extsb r0, r6
/* 0000001C 0000001C  7C 64 07 34 */	extsh r4, r3
/* 00000020 00000020  90 00 00 00 */	stw r0, glob@sda21(r2)
/* 00000024 00000024  7C A3 07 34 */	extsh r3, r5
/* 00000028 00000028  7C C0 07 34 */	extsh r0, r6
/* 0000002C 0000002C  90 80 00 00 */	stw r4, glob@sda21(r2)
/* 00000030 00000030  90 60 00 00 */	stw r3, glob@sda21(r2)
/* 00000034 00000034  90 00 00 00 */	stw r0, glob@sda21(r2)
/* 00000038 00000038  4E 80 00 20 */	blr 

.section .sbss  # 0x0 - 0x4

.global glob
glob:
	.word 0x00000000

