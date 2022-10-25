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
