.include "macros.inc"

.section .text  # 0x0 - 0x2c

.global bar
bar:
/* 00000000 00000000  4E 80 00 20 */	blr 

.global test
test:
/* 00000004 00000004  7C 08 02 A6 */	mflr r0
/* 00000008 00000008  90 01 00 04 */	stw r0, 4(r1)
/* 0000000C 0000000C  94 21 FF F8 */	stwu r1, -8(r1)
/* 00000010 00000010  48 00 00 01 */	bl bar
/* 00000014 00000014  38 00 00 04 */	li r0, 4
/* 00000018 00000018  90 00 00 00 */	stw r0, foo@sda21(r2)
/* 0000001C 0000001C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 00000020 00000020  38 21 00 08 */	addi r1, r1, 8
/* 00000024 00000024  7C 08 03 A6 */	mtlr r0
/* 00000028 00000028  4E 80 00 20 */	blr 

.section .sbss  # 0x0 - 0x4

.global foo
foo:
	.word 0x00000000

