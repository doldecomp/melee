#include <dolphin/types.h>

void lbl_80347374(void);

#pragma push
asm unk_t OSDisableInterrupts()
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

