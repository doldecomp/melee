#include <dolphin/types.h>

extern unk_t BootInfo;

#pragma push
asm unk_t OSGetConsoleType()
{ // clang-format off
    nofralloc
/* 80342E94 0033FA74  80 6D BC 98 */	lwz r3, BootInfo(r13)
/* 80342E98 0033FA78  28 03 00 00 */	cmplwi r3, 0
/* 80342E9C 0033FA7C  41 82 00 10 */	beq lbl_80342EAC
/* 80342EA0 0033FA80  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 80342EA4 0033FA84  28 03 00 00 */	cmplwi r3, 0
/* 80342EA8 0033FA88  40 82 00 10 */	bne lbl_80342EB8
lbl_80342EAC:
/* 80342EAC 0033FA8C  3C 60 10 00 */	lis r3, 0x10000002@ha
/* 80342EB0 0033FA90  38 63 00 02 */	addi r3, r3, 0x10000002@l
/* 80342EB4 0033FA94  48 00 00 04 */	b lbl_80342EB8
lbl_80342EB8:
/* 80342EB8 0033FA98  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop
