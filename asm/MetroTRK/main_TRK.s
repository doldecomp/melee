.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

.fn TRKTargetCPUMinorType, global
/* 8032ABD8 003277B8  38 60 00 54 */	li r3, 0x54
/* 8032ABDC 003277BC  4E 80 00 20 */	blr
.endfn TRKTargetCPUMinorType

.global TRK_main
TRK_main:
/* 8032ABE0 003277C0  7C 08 02 A6 */	mflr r0
/* 8032ABE4 003277C4  90 01 00 04 */	stw r0, 4(r1)
/* 8032ABE8 003277C8  94 21 FF F8 */	stwu r1, -8(r1)
/* 8032ABEC 003277CC  4B FF BE ED */	bl TRKInitializeNub
/* 8032ABF0 003277D0  3C 80 80 4A */	lis r4, TRK_mainError@ha
/* 8032ABF4 003277D4  94 64 50 D0 */	stwu r3, TRK_mainError@l(r4)
/* 8032ABF8 003277D8  80 04 00 00 */	lwz r0, 0(r4)
/* 8032ABFC 003277DC  2C 00 00 00 */	cmpwi r0, 0
/* 8032AC00 003277E0  40 82 00 0C */	bne .L_8032AC0C
/* 8032AC04 003277E4  4B FF BF CD */	bl TRKNubWelcome
/* 8032AC08 003277E8  4B FF BB 81 */	bl TRKNubMainLoop
.L_8032AC0C:
/* 8032AC0C 003277EC  4B FF BF A1 */	bl TRKTerminateNub
/* 8032AC10 003277F0  3C 80 80 4A */	lis r4, TRK_mainError@ha
/* 8032AC14 003277F4  90 64 50 D0 */	stw r3, TRK_mainError@l(r4)
/* 8032AC18 003277F8  38 21 00 08 */	addi r1, r1, 8
/* 8032AC1C 003277FC  80 01 00 04 */	lwz r0, 4(r1)
/* 8032AC20 00327800  7C 08 03 A6 */	mtlr r0
/* 8032AC24 00327804  4E 80 00 20 */	blr


.section .bss, "wa"
.global TRK_mainError
TRK_mainError:
    .skip 0x10
