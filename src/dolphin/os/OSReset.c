#include <dolphin/os/OSInterrupt.h>
#include <dolphin/os/OSReset.h>

/* 0034502C */ extern void OSResetSystem(BOOL reset, u32 resetCode, BOOL forceMenu);

extern unk_t ResetFunctionQueue;

#pragma push
asm unk_t OSRegisterResetFunction()
{ // clang-format off
    nofralloc
/* 80348310 00344EF0  80 AD BD 00 */	lwz r5, ResetFunctionQueue(r13)
/* 80348314 00344EF4  48 00 00 08 */	b lbl_8034831C
lbl_80348318:
/* 80348318 00344EF8  80 A5 00 08 */	lwz r5, 8(r5)
lbl_8034831C:
/* 8034831C 00344EFC  28 05 00 00 */	cmplwi r5, 0
/* 80348320 00344F00  41 82 00 14 */	beq lbl_80348334
/* 80348324 00344F04  80 85 00 04 */	lwz r4, 4(r5)
/* 80348328 00344F08  80 03 00 04 */	lwz r0, 4(r3)
/* 8034832C 00344F0C  7C 04 00 40 */	cmplw r4, r0
/* 80348330 00344F10  40 81 FF E8 */	ble lbl_80348318
lbl_80348334:
/* 80348334 00344F14  28 05 00 00 */	cmplwi r5, 0
/* 80348338 00344F18  40 82 00 34 */	bne lbl_8034836C
/* 8034833C 00344F1C  38 AD BD 00 */	addi r5, r13, ResetFunctionQueue
/* 80348340 00344F20  84 85 00 04 */	lwzu r4, 4(r5)
/* 80348344 00344F24  28 04 00 00 */	cmplwi r4, 0
/* 80348348 00344F28  40 82 00 0C */	bne lbl_80348354
/* 8034834C 00344F2C  90 6D BD 00 */	stw r3, ResetFunctionQueue(r13)
/* 80348350 00344F30  48 00 00 08 */	b lbl_80348358
lbl_80348354:
/* 80348354 00344F34  90 64 00 08 */	stw r3, 8(r4)
lbl_80348358:
/* 80348358 00344F38  90 83 00 0C */	stw r4, 0xc(r3)
/* 8034835C 00344F3C  38 00 00 00 */	li r0, 0
/* 80348360 00344F40  90 03 00 08 */	stw r0, 8(r3)
/* 80348364 00344F44  90 65 00 00 */	stw r3, 0(r5)
/* 80348368 00344F48  4E 80 00 20 */	blr 
lbl_8034836C:
/* 8034836C 00344F4C  90 A3 00 08 */	stw r5, 8(r3)
/* 80348370 00344F50  80 85 00 0C */	lwz r4, 0xc(r5)
/* 80348374 00344F54  90 65 00 0C */	stw r3, 0xc(r5)
/* 80348378 00344F58  28 04 00 00 */	cmplwi r4, 0
/* 8034837C 00344F5C  90 83 00 0C */	stw r4, 0xc(r3)
/* 80348380 00344F60  40 82 00 0C */	bne lbl_8034838C
/* 80348384 00344F64  90 6D BD 00 */	stw r3, ResetFunctionQueue(r13)
/* 80348388 00344F68  4E 80 00 20 */	blr 
lbl_8034838C:
/* 8034838C 00344F6C  90 64 00 08 */	stw r3, 8(r4)
/* 80348390 00344F70  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t Reset()
{ // clang-format off
    nofralloc
/* 80348394 00344F74  48 00 00 20 */	b lbl_803483B4
lbl_80348398:
/* 80348398 00344F78  7D 10 FA A6 */	mfspr r8, 0x3f0
/* 8034839C 00344F7C  61 08 00 08 */	ori r8, r8, 8
/* 803483A0 00344F80  7D 10 FB A6 */	mtspr 0x3f0, r8
/* 803483A4 00344F84  4C 00 01 2C */	isync 
/* 803483A8 00344F88  7C 00 04 AC */	sync
/* 803483AC 00344F8C  60 00 00 00 */	nop 
/* 803483B0 00344F90  48 00 00 08 */	b lbl_803483B8
lbl_803483B4:
/* 803483B4 00344F94  48 00 00 20 */	b lbl_803483D4
lbl_803483B8:
/* 803483B8 00344F98  7C AC 42 E6 */	mftb r5, 0x10c
lbl_803483BC:
/* 803483BC 00344F9C  7C CC 42 E6 */	mftb r6, 0x10c
/* 803483C0 00344FA0  7C E5 30 50 */	subf r7, r5, r6
/* 803483C4 00344FA4  28 07 11 24 */	cmplwi r7, 0x1124
/* 803483C8 00344FA8  41 80 FF F4 */	blt lbl_803483BC
/* 803483CC 00344FAC  60 00 00 00 */	nop 
/* 803483D0 00344FB0  48 00 00 08 */	b lbl_803483D8
lbl_803483D4:
/* 803483D4 00344FB4  48 00 00 20 */	b lbl_803483F4
lbl_803483D8:
/* 803483D8 00344FB8  3D 00 CC 00 */	lis r8, 0xCC003000@h
/* 803483DC 00344FBC  61 08 30 00 */	ori r8, r8, 0xCC003000@l
/* 803483E0 00344FC0  38 80 00 03 */	li r4, 3
/* 803483E4 00344FC4  90 88 00 24 */	stw r4, 0x24(r8)
/* 803483E8 00344FC8  90 68 00 24 */	stw r3, 0x24(r8)
/* 803483EC 00344FCC  60 00 00 00 */	nop 
/* 803483F0 00344FD0  48 00 00 08 */	b lbl_803483F8
lbl_803483F4:
/* 803483F4 00344FD4  48 00 00 0C */	b lbl_80348400
lbl_803483F8:
/* 803483F8 00344FD8  60 00 00 00 */	nop 
/* 803483FC 00344FDC  4B FF FF FC */	b lbl_803483F8
lbl_80348400:
/* 80348400 00344FE0  4B FF FF 98 */	b lbl_80348398
} // clang-format on
#pragma pop

extern unk_t ICFlashInvalidate();

#pragma push
asm unk_t __OSDoHotReset()
{ // clang-format off
    nofralloc
/* 80348404 00344FE4  7C 08 02 A6 */	mflr r0
/* 80348408 00344FE8  90 01 00 04 */	stw r0, 4(r1)
/* 8034840C 00344FEC  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80348410 00344FF0  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80348414 00344FF4  7C 7F 1B 78 */	mr r31, r3
/* 80348418 00344FF8  4B FF EF 4D */	bl OSDisableInterrupts
/* 8034841C 00344FFC  3C 60 CC 00 */	lis r3, 0xCC002000@ha
/* 80348420 00345000  38 63 20 00 */	addi r3, r3, 0xCC002000@l
/* 80348424 00345004  38 00 00 00 */	li r0, 0
/* 80348428 00345008  B0 03 00 02 */	sth r0, 2(r3)
/* 8034842C 0034500C  4B FF C4 E1 */	bl ICFlashInvalidate
/* 80348430 00345010  57 E3 18 38 */	slwi r3, r31, 3
/* 80348434 00345014  4B FF FF 61 */	bl Reset
/* 80348438 00345018  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8034843C 0034501C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80348440 00345020  38 21 00 18 */	addi r1, r1, 0x18
/* 80348444 00345024  7C 08 03 A6 */	mtlr r0
/* 80348448 00345028  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop
