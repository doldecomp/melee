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

#pragma push
asm unk_t __OSGetExceptionHandler()
{ // clang-format off
    nofralloc
/* 803435D0 003401B0  54 60 06 3E */	clrlwi r0, r3, 0x18
/* 803435D4 003401B4  80 6D BC A8 */	lwz r3, OSExceptionTable(r13)
/* 803435D8 003401B8  54 00 10 3A */	slwi r0, r0, 2
/* 803435DC 003401BC  7C 63 00 2E */	lwzx r3, r3, r0
/* 803435E0 003401C0  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t OSExceptionVector()
{ // clang-format off
    nofralloc
/* 803435E4 003401C4  7C 90 43 A6 */	mtspr 0x110, r4
/* 803435E8 003401C8  80 80 00 C0 */	lwz r4, 0xc0(r0)
/* 803435EC 003401CC  90 64 00 0C */	stw r3, 0xc(r4)
/* 803435F0 003401D0  7C 70 42 A6 */	mfspr r3, 0x110
/* 803435F4 003401D4  90 64 00 10 */	stw r3, 0x10(r4)
/* 803435F8 003401D8  90 A4 00 14 */	stw r5, 0x14(r4)
/* 803435FC 003401DC  A0 64 01 A2 */	lhz r3, 0x1a2(r4)
/* 80343600 003401E0  60 63 00 02 */	ori r3, r3, 2
/* 80343604 003401E4  B0 64 01 A2 */	sth r3, 0x1a2(r4)
/* 80343608 003401E8  7C 60 00 26 */	mfcr r3
/* 8034360C 003401EC  90 64 00 80 */	stw r3, 0x80(r4)
/* 80343610 003401F0  7C 68 02 A6 */	mflr r3
/* 80343614 003401F4  90 64 00 84 */	stw r3, 0x84(r4)
/* 80343618 003401F8  7C 69 02 A6 */	mfctr r3
/* 8034361C 003401FC  90 64 00 88 */	stw r3, 0x88(r4)
/* 80343620 00340200  7C 61 02 A6 */	mfxer r3
/* 80343624 00340204  90 64 00 8C */	stw r3, 0x8c(r4)
/* 80343628 00340208  7C 7A 02 A6 */	mfspr r3, 0x1a
/* 8034362C 0034020C  90 64 01 98 */	stw r3, 0x198(r4)
/* 80343630 00340210  7C 7B 02 A6 */	mfspr r3, 0x1b
/* 80343634 00340214  90 64 01 9C */	stw r3, 0x19c(r4)
/* 80343638 00340218  7C 65 1B 78 */	mr r5, r3
} // clang-format on
#pragma pop
