.include "macros.inc"

.section .text  # 0x0 - 0x2c

.global foo
foo:
/* 00000000 00000000  4E 80 00 20 */	blr 

.global test
test:
/* 00000004 00000004  7C 08 02 A6 */	mflr r0
/* 00000008 00000008  90 01 00 04 */	stw r0, 4(r1)
/* 0000000C 0000000C  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 00000010 00000010  38 61 00 0C */	addi r3, r1, 0xc
/* 00000014 00000014  38 81 00 08 */	addi r4, r1, 8
/* 00000018 00000018  48 00 00 01 */	bl foo
/* 0000001C 0000001C  80 01 00 14 */	lwz r0, 0x14(r1)
/* 00000020 00000020  38 21 00 10 */	addi r1, r1, 0x10
/* 00000024 00000024  7C 08 03 A6 */	mtlr r0
/* 00000028 00000028  4E 80 00 20 */	blr 

