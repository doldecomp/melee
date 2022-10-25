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

#pragma push
asm unk_t DCStoreRange()
{ // clang-format off
    nofralloc
/* 80344840 00341420  28 04 00 00 */	cmplwi r4, 0
/* 80344844 00341424  4C 81 00 20 */	blelr 
/* 80344848 00341428  54 65 06 FF */	clrlwi. r5, r3, 0x1b
/* 8034484C 0034142C  41 82 00 08 */	beq lbl_80344854
/* 80344850 00341430  38 84 00 20 */	addi r4, r4, 0x20
lbl_80344854:
/* 80344854 00341434  38 84 00 1F */	addi r4, r4, 0x1f
/* 80344858 00341438  54 84 D9 7E */	srwi r4, r4, 5
/* 8034485C 0034143C  7C 89 03 A6 */	mtctr r4
lbl_80344860:
/* 80344860 00341440  7C 00 18 6C */	dcbst 0, r3
/* 80344864 00341444  38 63 00 20 */	addi r3, r3, 0x20
/* 80344868 00341448  42 00 FF F8 */	bdnz lbl_80344860
/* 8034486C 0034144C  44 00 00 02 */	sc 
/* 80344870 00341450  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t DCFlushRangeNoSync()
{ // clang-format off
    nofralloc
/* 80344874 00341454  28 04 00 00 */	cmplwi r4, 0
/* 80344878 00341458  4C 81 00 20 */	blelr 
/* 8034487C 0034145C  54 65 06 FF */	clrlwi. r5, r3, 0x1b
/* 80344880 00341460  41 82 00 08 */	beq lbl_80344888
/* 80344884 00341464  38 84 00 20 */	addi r4, r4, 0x20
lbl_80344888:
/* 80344888 00341468  38 84 00 1F */	addi r4, r4, 0x1f
/* 8034488C 0034146C  54 84 D9 7E */	srwi r4, r4, 5
/* 80344890 00341470  7C 89 03 A6 */	mtctr r4
lbl_80344894:
/* 80344894 00341474  7C 00 18 AC */	dcbf 0, r3
/* 80344898 00341478  38 63 00 20 */	addi r3, r3, 0x20
/* 8034489C 0034147C  42 00 FF F8 */	bdnz lbl_80344894
/* 803448A0 00341480  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t DCZeroRange()
{ // clang-format off
    nofralloc
/* 803448A4 00341484  28 04 00 00 */	cmplwi r4, 0
/* 803448A8 00341488  4C 81 00 20 */	blelr 
/* 803448AC 0034148C  54 65 06 FF */	clrlwi. r5, r3, 0x1b
/* 803448B0 00341490  41 82 00 08 */	beq lbl_803448B8
/* 803448B4 00341494  38 84 00 20 */	addi r4, r4, 0x20
lbl_803448B8:
/* 803448B8 00341498  38 84 00 1F */	addi r4, r4, 0x1f
/* 803448BC 0034149C  54 84 D9 7E */	srwi r4, r4, 5
/* 803448C0 003414A0  7C 89 03 A6 */	mtctr r4
lbl_803448C4:
/* 803448C4 003414A4  7C 00 1F EC */	dcbz 0, r3
/* 803448C8 003414A8  38 63 00 20 */	addi r3, r3, 0x20
/* 803448CC 003414AC  42 00 FF F8 */	bdnz lbl_803448C4
/* 803448D0 003414B0  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t ICInvalidateRange()
{ // clang-format off
    nofralloc
/* 803448D4 003414B4  28 04 00 00 */	cmplwi r4, 0
/* 803448D8 003414B8  4C 81 00 20 */	blelr 
/* 803448DC 003414BC  54 65 06 FF */	clrlwi. r5, r3, 0x1b
/* 803448E0 003414C0  41 82 00 08 */	beq lbl_803448E8
/* 803448E4 003414C4  38 84 00 20 */	addi r4, r4, 0x20
lbl_803448E8:
/* 803448E8 003414C8  38 84 00 1F */	addi r4, r4, 0x1f
/* 803448EC 003414CC  54 84 D9 7E */	srwi r4, r4, 5
/* 803448F0 003414D0  7C 89 03 A6 */	mtctr r4
lbl_803448F4:
/* 803448F4 003414D4  7C 00 1F AC */	icbi 0, r3
/* 803448F8 003414D8  38 63 00 20 */	addi r3, r3, 0x20
/* 803448FC 003414DC  42 00 FF F8 */	bdnz lbl_803448F4
/* 80344900 003414E0  7C 00 04 AC */	sync
/* 80344904 003414E4  4C 00 01 2C */	isync 
/* 80344908 003414E8  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t ICFlashInvalidate()
{ // clang-format off
    nofralloc
/* 8034490C 003414EC  7C 70 FA A6 */	mfspr r3, 0x3f0
/* 80344910 003414F0  60 63 08 00 */	ori r3, r3, 0x800
/* 80344914 003414F4  7C 70 FB A6 */	mtspr 0x3f0, r3
/* 80344918 003414F8  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t ICEnable()
{ // clang-format off
    nofralloc
/* 8034491C 003414FC  4C 00 01 2C */	isync 
/* 80344920 00341500  7C 70 FA A6 */	mfspr r3, 0x3f0
/* 80344924 00341504  60 63 80 00 */	ori r3, r3, 0x8000
/* 80344928 00341508  7C 70 FB A6 */	mtspr 0x3f0, r3
/* 8034492C 0034150C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t __LCEnable()
{ // clang-format off
    nofralloc
/* 80344930 00341510  7C A0 00 A6 */	mfmsr r5
/* 80344934 00341514  60 A5 10 00 */	ori r5, r5, 0x1000
/* 80344938 00341518  7C A0 01 24 */	mtmsr r5
/* 8034493C 0034151C  3C 60 80 00 */	lis r3, 0x80000020@ha
/* 80344940 00341520  38 80 04 00 */	li r4, 0x400
/* 80344944 00341524  7C 89 03 A6 */	mtctr r4
lbl_80344948:
/* 80344948 00341528  7C 00 1A 2C */	dcbt 0, r3
/* 8034494C 0034152C  7C 00 18 6C */	dcbst 0, r3
/* 80344950 00341530  38 63 00 20 */	addi r3, r3, 0x80000020@l
/* 80344954 00341534  42 00 FF F4 */	bdnz lbl_80344948
/* 80344958 00341538  7C 98 E2 A6 */	mfspr r4, 0x398
/* 8034495C 0034153C  64 84 10 0F */	oris r4, r4, 0x100f
/* 80344960 00341540  7C 98 E3 A6 */	mtspr 0x398, r4
/* 80344964 00341544  60 00 00 00 */	nop 
/* 80344968 00341548  60 00 00 00 */	nop 
/* 8034496C 0034154C  60 00 00 00 */	nop 
/* 80344970 00341550  60 00 00 00 */	nop 
/* 80344974 00341554  60 00 00 00 */	nop 
/* 80344978 00341558  60 00 00 00 */	nop 
/* 8034497C 0034155C  60 00 00 00 */	nop 
/* 80344980 00341560  60 00 00 00 */	nop 
/* 80344984 00341564  60 00 00 00 */	nop 
/* 80344988 00341568  60 00 00 00 */	nop 
/* 8034498C 0034156C  60 00 00 00 */	nop 
/* 80344990 00341570  60 00 00 00 */	nop 
/* 80344994 00341574  3C 60 E0 00 */	lis r3, 0xE0000002@h
/* 80344998 00341578  60 63 00 02 */	ori r3, r3, 0xE0000002@l
/* 8034499C 0034157C  7C 7F 83 A6 */	mtdbatl 3, r3
/* 803449A0 00341580  60 63 01 FE */	ori r3, r3, 0x1fe
/* 803449A4 00341584  7C 7E 83 A6 */	mtdbatu 3, r3
/* 803449A8 00341588  4C 00 01 2C */	isync 
/* 803449AC 0034158C  3C 60 E0 00 */	lis r3, 0xE0000020@ha
/* 803449B0 00341590  38 C0 02 00 */	li r6, 0x200
/* 803449B4 00341594  7C C9 03 A6 */	mtctr r6
/* 803449B8 00341598  38 C0 00 00 */	li r6, 0
lbl_803449BC:
/* 803449BC 0034159C  10 06 1F EC */	dcbz_l r6, r3
/* 803449C0 003415A0  38 63 00 20 */	addi r3, r3, 0xE0000020@l
/* 803449C4 003415A4  42 00 FF F8 */	bdnz lbl_803449BC
/* 803449C8 003415A8  60 00 00 00 */	nop 
/* 803449CC 003415AC  60 00 00 00 */	nop 
/* 803449D0 003415B0  60 00 00 00 */	nop 
/* 803449D4 003415B4  60 00 00 00 */	nop 
/* 803449D8 003415B8  60 00 00 00 */	nop 
/* 803449DC 003415BC  60 00 00 00 */	nop 
/* 803449E0 003415C0  60 00 00 00 */	nop 
/* 803449E4 003415C4  60 00 00 00 */	nop 
/* 803449E8 003415C8  60 00 00 00 */	nop 
/* 803449EC 003415CC  60 00 00 00 */	nop 
/* 803449F0 003415D0  60 00 00 00 */	nop 
/* 803449F4 003415D4  60 00 00 00 */	nop 
/* 803449F8 003415D8  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop


