.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

.global TRKInitializeDispatcher
TRKInitializeDispatcher:
/* 803276A8 00324288  3C 60 80 4A */	lis r3, gTRKDispatchTableSize@ha
/* 803276AC 0032428C  38 00 00 20 */	li r0, 0x20
/* 803276B0 00324290  90 03 4B 40 */	stw r0, gTRKDispatchTableSize@l(r3)
/* 803276B4 00324294  38 60 00 00 */	li r3, 0
/* 803276B8 00324298  4E 80 00 20 */	blr

.global TRKDispatchMessage
TRKDispatchMessage:
/* 803276BC 0032429C  7C 08 02 A6 */	mflr r0
/* 803276C0 003242A0  38 80 00 00 */	li r4, 0
/* 803276C4 003242A4  90 01 00 04 */	stw r0, 4(r1)
/* 803276C8 003242A8  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 803276CC 003242AC  93 E1 00 14 */	stw r31, 0x14(r1)
/* 803276D0 003242B0  3B E0 05 00 */	li r31, 0x500
/* 803276D4 003242B4  93 C1 00 10 */	stw r30, 0x10(r1)
/* 803276D8 003242B8  3B C3 00 00 */	addi r30, r3, 0
/* 803276DC 003242BC  4B FF F7 A9 */	bl TRKSetBufferPosition
/* 803276E0 003242C0  38 7E 00 00 */	addi r3, r30, 0
/* 803276E4 003242C4  38 81 00 08 */	addi r4, r1, 8
/* 803276E8 003242C8  4B FF FB 21 */	bl TRKReadBuffer1_ui8
/* 803276EC 003242CC  3C 60 80 4A */	lis r3, gTRKDispatchTableSize@ha
/* 803276F0 003242D0  88 81 00 08 */	lbz r4, 8(r1)
/* 803276F4 003242D4  80 03 4B 40 */	lwz r0, gTRKDispatchTableSize@l(r3)
/* 803276F8 003242D8  7C 04 00 40 */	cmplw r4, r0
/* 803276FC 003242DC  40 80 00 28 */	bge .L_80327724
/* 80327700 003242E0  3C 60 80 40 */	lis r3, gTRKDispatchTable@ha
/* 80327704 003242E4  54 84 10 3A */	slwi r4, r4, 2
/* 80327708 003242E8  38 03 07 88 */	addi r0, r3, gTRKDispatchTable@l
/* 8032770C 003242EC  7C 60 22 14 */	add r3, r0, r4
/* 80327710 003242F0  81 83 00 00 */	lwz r12, 0(r3)
/* 80327714 003242F4  38 7E 00 00 */	addi r3, r30, 0
/* 80327718 003242F8  7D 88 03 A6 */	mtlr r12
/* 8032771C 003242FC  4E 80 00 21 */	blrl
/* 80327720 00324300  7C 7F 1B 78 */	mr r31, r3
.L_80327724:
/* 80327724 00324304  7F E3 FB 78 */	mr r3, r31
/* 80327728 00324308  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8032772C 0032430C  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 80327730 00324310  38 21 00 18 */	addi r1, r1, 0x18
/* 80327734 00324314  80 01 00 04 */	lwz r0, 4(r1)
/* 80327738 00324318  7C 08 03 A6 */	mtlr r0
/* 8032773C 0032431C  4E 80 00 20 */	blr


.section .data
    .balign 8
.global gTRKDispatchTableSize
gTRKDispatchTableSize:
    .4byte TRKDoUnsupported
    .4byte TRKDoConnect
    .4byte TRKDoDisconnect
    .4byte TRKDoReset
    .4byte TRKDoVersions
    .4byte TRKDoSupportMask
    .4byte TRKDoCPUType
    .4byte TRKDoUnsupported
    .4byte TRKDoUnsupported
    .4byte TRKDoUnsupported
    .4byte TRKDoUnsupported
    .4byte TRKDoUnsupported
    .4byte TRKDoUnsupported
    .4byte TRKDoUnsupported
    .4byte TRKDoUnsupported
    .4byte TRKDoUnsupported
    .4byte TRKDoReadMemory
    .4byte TRKDoWriteMemory
    .4byte TRKDoReadRegisters
    .4byte TRKDoWriteRegisters
    .4byte TRKDoUnsupported
    .4byte TRKDoUnsupported
    .4byte TRKDoFlushCache
    .4byte TRKDoUnsupported
    .4byte TRKDoContinue
    .4byte TRKDoStep
    .4byte TRKDoStop
    .4byte TRKDoUnsupported
    .4byte TRKDoUnsupported
    .4byte TRKDoUnsupported
    .4byte TRKDoUnsupported
    .4byte TRKDoUnsupported
    .4byte NULL
    .4byte NULL


.section .bss, "wa"
.global gTRKDispatchTableSize
gTRKDispatchTableSize:
    .skip 0x8
