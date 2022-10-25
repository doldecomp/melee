#include <dolphin/types.h>

extern unk_t OSExceptionTable;

#pragma push
asm unk_t __OSSetExceptionHandler()
{ // clang-format off
    nofralloc
/* 803435B4 00340194  54 60 06 3E */	clrlwi r0, r3, 0x18
/* 803435B8 00340198  80 6D BC A8 */	lwz r3, OSExceptionTable(r13)
/* 803435BC 0034019C  54 00 10 3A */	slwi r0, r0, 2
/* 803435C0 003401A0  7C A3 02 14 */	add r5, r3, r0
/* 803435C4 003401A4  80 65 00 00 */	lwz r3, 0(r5)
/* 803435C8 003401A8  90 85 00 00 */	stw r4, 0(r5)
/* 803435CC 003401AC  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop
