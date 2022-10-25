#include <dolphin/os/OSInterrupt.h>

void lbl_80347374(void);

#pragma push
asm BOOL OSDisableInterrupts(void)
{ // clang-format off
    nofralloc
/* 80347364 00343F44  7C 60 00 A6 */	mfmsr r3
/* 80347368 00343F48  54 64 04 5E */	rlwinm r4, r3, 0, 0x11, 0xf
/* 8034736C 00343F4C  7C 80 01 24 */	mtmsr r4
/* 80347370 00343F50  54 63 8F FE */	rlwinm r3, r3, 0x11, 0x1f, 0x1f
entry lbl_80347374
/* 80347374 00343F54  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm BOOL OSEnableInterrupts(void)
{ // clang-format off
    nofralloc
/* 80347378 00343F58  7C 60 00 A6 */	mfmsr r3
/* 8034737C 00343F5C  60 64 80 00 */	ori r4, r3, 0x8000
/* 80347380 00343F60  7C 80 01 24 */	mtmsr r4
/* 80347384 00343F64  54 63 8F FE */	rlwinm r3, r3, 0x11, 0x1f, 0x1f
/* 80347388 00343F68  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm BOOL OSRestoreInterrupts(BOOL)
{ // clang-format off
    nofralloc
/* 8034738C 00343F6C  2C 03 00 00 */	cmpwi r3, 0
/* 80347390 00343F70  7C 80 00 A6 */	mfmsr r4
/* 80347394 00343F74  41 82 00 0C */	beq lbl_803473A0
/* 80347398 00343F78  60 85 80 00 */	ori r5, r4, 0x8000
/* 8034739C 00343F7C  48 00 00 08 */	b lbl_803473A4
lbl_803473A0:
/* 803473A0 00343F80  54 85 04 5E */	rlwinm r5, r4, 0, 0x11, 0xf
lbl_803473A4:
/* 803473A4 00343F84  7C A0 01 24 */	mtmsr r5
/* 803473A8 00343F88  54 84 8F FE */	rlwinm r4, r4, 0x11, 0x1f, 0x1f
/* 803473AC 00343F8C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t lbl_804D7378;

#pragma push
asm OSInterruptHandler __OSSetInterruptHandler(OSInterruptType, OSInterruptHandler)
{ // clang-format off
    nofralloc
/* 803473B0 00343F90  7C 60 07 34 */	extsh r0, r3
/* 803473B4 00343F94  80 6D BC D8 */	lwz r3, lbl_804D7378(r13)
/* 803473B8 00343F98  54 00 10 3A */	slwi r0, r0, 2
/* 803473BC 00343F9C  7C A3 02 14 */	add r5, r3, r0
/* 803473C0 00343FA0  80 65 00 00 */	lwz r3, 0(r5)
/* 803473C4 00343FA4  90 85 00 00 */	stw r4, 0(r5)
/* 803473C8 00343FA8  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop



#pragma push
asm OSInterruptHandler __OSGetInterruptHandler(OSInterruptType)
{ // clang-format off
    nofralloc
/* 803473CC 00343FAC  7C 60 07 34 */	extsh r0, r3
/* 803473D0 00343FB0  80 6D BC D8 */	lwz r3, lbl_804D7378(r13)
/* 803473D4 00343FB4  54 00 10 3A */	slwi r0, r0, 2
/* 803473D8 00343FB8  7C 63 00 2E */	lwzx r3, r3, r0
/* 803473DC 00343FBC  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop


