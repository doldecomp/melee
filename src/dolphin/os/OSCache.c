#include <dolphin/types.h>

#pragma push
asm unk_t DCEnable()
{ // clang-format off
    nofralloc
/* 803447C8 003413A8  7C 00 04 AC */	sync
/* 803447CC 003413AC  7C 70 FA A6 */	mfspr r3, 0x3f0
/* 803447D0 003413B0  60 63 40 00 */	ori r3, r3, 0x4000
/* 803447D4 003413B4  7C 70 FB A6 */	mtspr 0x3f0, r3
/* 803447D8 003413B8  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t DCInvalidateRange()
{ // clang-format off
    nofralloc
/* 803447DC 003413BC  28 04 00 00 */	cmplwi r4, 0
/* 803447E0 003413C0  4C 81 00 20 */	blelr 
/* 803447E4 003413C4  54 65 06 FF */	clrlwi. r5, r3, 0x1b
/* 803447E8 003413C8  41 82 00 08 */	beq lbl_803447F0
/* 803447EC 003413CC  38 84 00 20 */	addi r4, r4, 0x20
lbl_803447F0:
/* 803447F0 003413D0  38 84 00 1F */	addi r4, r4, 0x1f
/* 803447F4 003413D4  54 84 D9 7E */	srwi r4, r4, 5
/* 803447F8 003413D8  7C 89 03 A6 */	mtctr r4
lbl_803447FC:
/* 803447FC 003413DC  7C 00 1B AC */	dcbi 0, r3
/* 80344800 003413E0  38 63 00 20 */	addi r3, r3, 0x20
/* 80344804 003413E4  42 00 FF F8 */	bdnz lbl_803447FC
/* 80344808 003413E8  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

// https://decomp.me/scratch/y3hWw
#pragma push
asm unk_t DCFlushRange()
{ // clang-format off
    nofralloc
/* 8034480C 003413EC  28 04 00 00 */	cmplwi r4, 0
/* 80344810 003413F0  4C 81 00 20 */	blelr 
/* 80344814 003413F4  54 65 06 FF */	clrlwi. r5, r3, 0x1b
/* 80344818 003413F8  41 82 00 08 */	beq lbl_80344820
/* 8034481C 003413FC  38 84 00 20 */	addi r4, r4, 0x20
lbl_80344820:
/* 80344820 00341400  38 84 00 1F */	addi r4, r4, 0x1f
/* 80344824 00341404  54 84 D9 7E */	srwi r4, r4, 5
/* 80344828 00341408  7C 89 03 A6 */	mtctr r4
lbl_8034482C:
/* 8034482C 0034140C  7C 00 18 AC */	dcbf 0, r3
/* 80344830 00341410  38 63 00 20 */	addi r3, r3, 0x20
/* 80344834 00341414  42 00 FF F8 */	bdnz lbl_8034482C
/* 80344838 00341418  44 00 00 02 */	sc 
/* 8034483C 0034141C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop
