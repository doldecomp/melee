.include "macros.inc"

.section .text  # 0x0 - 0x20

.global test
test:
/* 00000000 00000000  7C 08 02 A6 */	mflr r0
/* 00000004 00000004  90 01 00 04 */	stw r0, 4(r1)
/* 00000008 00000008  94 21 FF F8 */	stwu r1, -8(r1)
.L0000000C:
/* 0000000C 0000000C  2C 03 00 02 */	cmpwi r3, 2
/* 00000010 00000010  40 81 FF FC */	ble .L0000000C
/* 00000014 00000014  48 00 00 01 */	bl foo
/* 00000018 00000018  4B FF FF F4 */	b .L0000000C

.global foo
foo:
/* 0000001C 0000001C  4E 80 00 20 */	blr 

