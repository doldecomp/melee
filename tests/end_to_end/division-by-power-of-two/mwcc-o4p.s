.include "macros.inc"

.section .text  # 0x0 - 0x14

.global test
test:
/* 00000000 00000000  80 03 00 00 */	lwz r0, 0(r3)
/* 00000004 00000004  7C 00 0E 70 */	srawi r0, r0, 1
/* 00000008 00000008  7C 00 01 94 */	addze r0, r0
/* 0000000C 0000000C  90 03 00 00 */	stw r0, 0(r3)
/* 00000010 00000010  4E 80 00 20 */	blr 

