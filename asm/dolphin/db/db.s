.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

.global DBInit
DBInit:
/* 80335EC0 00332AA0  3C 80 80 00 */	lis r4, 0x80000040@ha
/* 80335EC4 00332AA4  38 04 00 40 */	addi r0, r4, 0x80000040@l
/* 80335EC8 00332AA8  3C 60 80 33 */	lis r3, lbl_80335F4C@ha
/* 80335ECC 00332AAC  90 0D BB 68 */	stw r0, __DBInterface@sda21(r13)
/* 80335ED0 00332AB0  38 63 5F 4C */	addi r3, r3, lbl_80335F4C@l
/* 80335ED4 00332AB4  3C 03 80 00 */	addis r0, r3, 0x8000
/* 80335ED8 00332AB8  90 04 00 48 */	stw r0, 0x48(r4)
/* 80335EDC 00332ABC  38 00 00 01 */	li r0, 1
/* 80335EE0 00332AC0  90 0D BB 6C */	stw r0, DBVerbose@sda21(r13)
/* 80335EE4 00332AC4  4E 80 00 20 */	blr 

.global DBIsDebuggerPresent
DBIsDebuggerPresent:
/* 80335EE8 00332AC8  80 6D BB 68 */	lwz r3, __DBInterface@sda21(r13)
/* 80335EEC 00332ACC  28 03 00 00 */	cmplwi r3, 0
/* 80335EF0 00332AD0  40 82 00 0C */	bne lbl_80335EFC
/* 80335EF4 00332AD4  38 60 00 00 */	li r3, 0
/* 80335EF8 00332AD8  4E 80 00 20 */	blr 
lbl_80335EFC:
/* 80335EFC 00332ADC  80 63 00 00 */	lwz r3, 0(r3)
/* 80335F00 00332AE0  4E 80 00 20 */	blr 
lbl_80335F04:
/* 80335F04 00332AE4  7C 08 02 A6 */	mflr r0
/* 80335F08 00332AE8  3C 60 80 40 */	lis r3, lbl_80400BF0@ha
/* 80335F0C 00332AEC  90 01 00 04 */	stw r0, 4(r1)
/* 80335F10 00332AF0  38 63 0B F0 */	addi r3, r3, lbl_80400BF0@l
/* 80335F14 00332AF4  4C C6 31 82 */	crclr 6
/* 80335F18 00332AF8  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80335F1C 00332AFC  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80335F20 00332B00  80 80 00 C0 */	lwz r4, 0xc0(0)
/* 80335F24 00332B04  3F E4 80 00 */	addis r31, r4, 0x8000
/* 80335F28 00332B08  48 00 F7 81 */	bl OSReport
/* 80335F2C 00332B0C  7F E3 FB 78 */	mr r3, r31
/* 80335F30 00332B10  48 00 F4 05 */	bl OSDumpContext
/* 80335F34 00332B14  4B FF FF 61 */	bl PPCHalt
/* 80335F38 00332B18  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80335F3C 00332B1C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80335F40 00332B20  38 21 00 18 */	addi r1, r1, 0x18
/* 80335F44 00332B24  7C 08 03 A6 */	mtlr r0
/* 80335F48 00332B28  4E 80 00 20 */	blr 
lbl_80335F4C:
/* 80335F4C 00332B2C  7C 60 00 A6 */	mfmsr r3
/* 80335F50 00332B30  60 63 00 30 */	ori r3, r3, 0x30
/* 80335F54 00332B34  7C 60 01 24 */	mtmsr r3
/* 80335F58 00332B38  4B FF FF AC */	b lbl_80335F04

.global __DBIsExceptionMarked
__DBIsExceptionMarked:
/* 80335F5C 00332B3C  80 8D BB 68 */	lwz r4, __DBInterface@sda21(r13)
/* 80335F60 00332B40  54 60 06 3E */	clrlwi r0, r3, 0x18
/* 80335F64 00332B44  38 60 00 01 */	li r3, 1
/* 80335F68 00332B48  80 84 00 04 */	lwz r4, 4(r4)
/* 80335F6C 00332B4C  7C 60 00 30 */	slw r0, r3, r0
/* 80335F70 00332B50  7C 83 00 38 */	and r3, r4, r0
/* 80335F74 00332B54  4E 80 00 20 */	blr 

.global DBPrintf
DBPrintf:
/* 80335F78 00332B58  94 21 FF 90 */	stwu r1, -0x70(r1)
/* 80335F7C 00332B5C  40 86 00 24 */	bne cr1, lbl_80335FA0
/* 80335F80 00332B60  D8 21 00 28 */	stfd f1, 0x28(r1)
/* 80335F84 00332B64  D8 41 00 30 */	stfd f2, 0x30(r1)
/* 80335F88 00332B68  D8 61 00 38 */	stfd f3, 0x38(r1)
/* 80335F8C 00332B6C  D8 81 00 40 */	stfd f4, 0x40(r1)
/* 80335F90 00332B70  D8 A1 00 48 */	stfd f5, 0x48(r1)
/* 80335F94 00332B74  D8 C1 00 50 */	stfd f6, 0x50(r1)
/* 80335F98 00332B78  D8 E1 00 58 */	stfd f7, 0x58(r1)
/* 80335F9C 00332B7C  D9 01 00 60 */	stfd f8, 0x60(r1)
lbl_80335FA0:
/* 80335FA0 00332B80  90 61 00 08 */	stw r3, 8(r1)
/* 80335FA4 00332B84  90 81 00 0C */	stw r4, 0xc(r1)
/* 80335FA8 00332B88  90 A1 00 10 */	stw r5, 0x10(r1)
/* 80335FAC 00332B8C  90 C1 00 14 */	stw r6, 0x14(r1)
/* 80335FB0 00332B90  90 E1 00 18 */	stw r7, 0x18(r1)
/* 80335FB4 00332B94  91 01 00 1C */	stw r8, 0x1c(r1)
/* 80335FB8 00332B98  91 21 00 20 */	stw r9, 0x20(r1)
/* 80335FBC 00332B9C  91 41 00 24 */	stw r10, 0x24(r1)
/* 80335FC0 00332BA0  38 21 00 70 */	addi r1, r1, 0x70
/* 80335FC4 00332BA4  4E 80 00 20 */	blr 


.section .data
    .balign 8
.global lbl_80400BF0
lbl_80400BF0:
    .asciz "DBExceptionDestination\n"
    .balign 4


.section .sbss
    .balign 8
.global __DBInterface
__DBInterface:
	.skip 0x4
.global DBVerbose
DBVerbose:
	.skip 0x4
