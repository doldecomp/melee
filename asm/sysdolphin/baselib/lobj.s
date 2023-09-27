.include "macros.inc"

.section .text

.global LObjInfoInit
LObjInfoInit:
/* 80367688 00364268  7C 08 02 A6 */	mflr r0
/* 8036768C 0036426C  3C 60 80 40 */	lis r3, hsdLObj@ha
/* 80367690 00364270  90 01 00 04 */	stw r0, 4(r1)
/* 80367694 00364274  38 E0 00 40 */	li r7, 0x40
/* 80367698 00364278  39 00 00 D4 */	li r8, 0xd4
/* 8036769C 0036427C  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 803676A0 00364280  93 E1 00 0C */	stw r31, 0xc(r1)
/* 803676A4 00364284  3B E3 60 C0 */	addi r31, r3, hsdLObj@l
/* 803676A8 00364288  3C 60 80 40 */	lis r3, hsdObj@ha
/* 803676AC 0036428C  38 83 72 A8 */	addi r4, r3, hsdObj@l
/* 803676B0 00364290  38 7F 00 00 */	addi r3, r31, 0
/* 803676B4 00364294  38 BF 01 38 */	addi r5, r31, 0x138
/* 803676B8 00364298  38 DF 01 50 */	addi r6, r31, 0x150
/* 803676BC 0036429C  48 01 A5 5D */	bl hsdInitClassInfo
/* 803676C0 003642A0  3C 60 80 36 */	lis r3, LObjRelease@ha
/* 803676C4 003642A4  38 03 74 B4 */	addi r0, r3, LObjRelease@l
/* 803676C8 003642A8  3C 60 80 36 */	lis r3, LObjAmnesia@ha
/* 803676CC 003642AC  90 1F 00 30 */	stw r0, 0x30(r31)
/* 803676D0 003642B0  38 03 76 28 */	addi r0, r3, LObjAmnesia@l
/* 803676D4 003642B4  3C 60 80 36 */	lis r3, LObjLoad@ha
/* 803676D8 003642B8  90 1F 00 38 */	stw r0, 0x38(r31)
/* 803676DC 003642BC  38 03 6E A8 */	addi r0, r3, LObjLoad@l
/* 803676E0 003642C0  90 1F 00 3C */	stw r0, 0x3c(r31)
/* 803676E4 003642C4  80 01 00 14 */	lwz r0, 0x14(r1)
/* 803676E8 003642C8  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 803676EC 003642CC  38 21 00 10 */	addi r1, r1, 0x10
/* 803676F0 003642D0  7C 08 03 A6 */	mtlr r0
/* 803676F4 003642D4  4E 80 00 20 */	blr
