#include <dolphin/types.h>

extern unk_t lbl_80402358;

#pragma push
asm unk_t SIBusy()
{ // clang-format off
    nofralloc
/* 803494BC 0034609C  3C 60 80 40 */	lis r3, lbl_80402358@ha
/* 803494C0 003460A0  80 03 23 58 */	lwz r0, lbl_80402358@l(r3)
/* 803494C4 003460A4  2C 00 FF FF */	cmpwi r0, -1
/* 803494C8 003460A8  41 82 00 0C */	beq lbl_803494D4
/* 803494CC 003460AC  38 60 00 01 */	li r3, 1
/* 803494D0 003460B0  4E 80 00 20 */	blr 
lbl_803494D4:
/* 803494D4 003460B4  38 60 00 00 */	li r3, 0
/* 803494D8 003460B8  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop
