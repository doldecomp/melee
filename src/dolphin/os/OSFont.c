#include <placeholder.h>
#include <dolphin/os/OSFont.h>

#ifdef MWERKS_GEKKO

static s16 OSFont_804D5C20[] = { -1, 0, 0, 0 };

#pragma push
asm u16 OSGetFontEncode(void)
{ // clang-format off
    nofralloc
/* 8034730C 00343EEC  A0 6D A5 80 */	lhz r3, OSFont_804D5C20(r13)
/* 80347310 00343EF0  28 03 00 01 */	cmplwi r3, 1
/* 80347314 00343EF4  4C 81 00 20 */	blelr
/* 80347318 00343EF8  3C 60 80 00 */	lis r3, 0x800000CC@ha
/* 8034731C 00343EFC  80 03 00 CC */	lwz r0, 0x800000CC@l(r3)
/* 80347320 00343F00  2C 00 00 00 */	cmpwi r0, 0
/* 80347324 00343F04  41 82 00 0C */	beq lbl_80347330
/* 80347328 00343F08  41 80 00 2C */	blt lbl_80347354
/* 8034732C 00343F0C  48 00 00 28 */	b lbl_80347354
lbl_80347330:
/* 80347330 00343F10  3C 60 CC 00 */	lis r3, 0xCC00206E@ha
/* 80347334 00343F14  A0 03 20 6E */	lhz r0, 0xCC00206E@l(r3)
/* 80347338 00343F18  54 00 07 BD */	rlwinm. r0, r0, 0, 0x1e, 0x1e
/* 8034733C 00343F1C  41 82 00 0C */	beq lbl_80347348
/* 80347340 00343F20  38 00 00 01 */	li r0, 1
/* 80347344 00343F24  48 00 00 08 */	b lbl_8034734C
lbl_80347348:
/* 80347348 00343F28  38 00 00 00 */	li r0, 0
lbl_8034734C:
/* 8034734C 00343F2C  B0 0D A5 80 */	sth r0, OSFont_804D5C20(r13)
/* 80347350 00343F30  48 00 00 0C */	b lbl_8034735C
lbl_80347354:
/* 80347354 00343F34  38 00 00 00 */	li r0, 0
/* 80347358 00343F38  B0 0D A5 80 */	sth r0, OSFont_804D5C20(r13)
lbl_8034735C:
/* 8034735C 00343F3C  A0 6D A5 80 */	lhz r3, OSFont_804D5C20(r13)
/* 80347360 00343F40  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#else

u16 OSGetFontEncode(void)
{
    NOT_IMPLEMENTED;
}

#endif
