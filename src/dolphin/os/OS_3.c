#include <dolphin/types.h>
#include <dolphin/base/PPCArch.h>

#pragma push
asm unk_t __OSDBIntegrator()
{ // clang-format off
    nofralloc
/* 8034358C 0034016C  38 A0 00 40 */	li r5, 0x40
/* 80343590 00340170  7C 68 02 A6 */	mflr r3
/* 80343594 00340174  90 65 00 0C */	stw r3, 0xc(r5)
/* 80343598 00340178  80 65 00 08 */	lwz r3, 8(r5)
/* 8034359C 0034017C  64 63 80 00 */	oris r3, r3, 0x8000
/* 803435A0 00340180  7C 68 03 A6 */	mtlr r3
/* 803435A4 00340184  38 60 00 30 */	li r3, 0x30
/* 803435A8 00340188  7C 60 01 24 */	mtmsr r3
/* 803435AC 0034018C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t __OSDBJump()
{ // clang-format off
    nofralloc
/* 803435B0 00340190  48 00 00 63 */	bla 0x60
} // clang-format on
#pragma pop

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

#pragma push
asm unk_t __DBVECTOR()
{ // clang-format off
    nofralloc
/* 8034363C 0034021C  60 00 00 00 */	nop 
/* 80343640 00340220  7C 60 00 A6 */	mfmsr r3
/* 80343644 00340224  60 63 00 30 */	ori r3, r3, 0x30
/* 80343648 00340228  7C 7B 03 A6 */	mtspr 0x1b, r3
} // clang-format on
#pragma pop

extern unk_t OSDefaultExceptionHandler();

#pragma push
asm unk_t __OSEVSetNumber()
{ // clang-format off
    nofralloc
/* 8034364C 0034022C  38 60 00 00 */	li r3, 0
/* 80343650 00340230  80 80 00 D4 */	lwz r4, 0xd4(r0)
/* 80343654 00340234  54 A5 07 BD */	rlwinm. r5, r5, 0, 0x1e, 0x1e
/* 80343658 00340238  40 82 00 14 */	bne lbl_8034366C
/* 8034365C 0034023C  3C A0 80 34 */	lis r5, OSDefaultExceptionHandler@ha
/* 80343660 00340240  38 A5 36 80 */	addi r5, r5, OSDefaultExceptionHandler@l
/* 80343664 00340244  7C BA 03 A6 */	mtspr 0x1a, r5
/* 80343668 00340248  4C 00 00 64 */	rfi 
lbl_8034366C:
/* 8034366C 0034024C  54 65 15 BA */	rlwinm r5, r3, 2, 0x16, 0x1d
/* 80343670 00340250  80 A5 30 00 */	lwz r5, 0x3000(r5)
/* 80343674 00340254  7C BA 03 A6 */	mtspr 0x1a, r5
/* 80343678 00340258  4C 00 00 64 */	rfi 
} // clang-format on
#pragma pop

#pragma push
asm unk_t __OSEVEnd()
{ // clang-format off
    nofralloc
/* 8034367C 0034025C  60 00 00 00 */	nop 
} // clang-format on
#pragma pop

extern unk_t __OSUnhandledException();

#pragma push
asm unk_t OSDefaultExceptionHandler()
{ // clang-format off
    nofralloc
/* 80343680 00340260  90 04 00 00 */	stw r0, 0(r4)
/* 80343684 00340264  90 24 00 04 */	stw r1, 4(r4)
/* 80343688 00340268  90 44 00 08 */	stw r2, 8(r4)
/* 8034368C 0034026C  BC C4 00 18 */	stmw r6, 0x18(r4)
/* 80343690 00340270  7C 11 E2 A6 */	mfspr r0, 0x391
/* 80343694 00340274  90 04 01 A8 */	stw r0, 0x1a8(r4)
/* 80343698 00340278  7C 12 E2 A6 */	mfspr r0, 0x392
/* 8034369C 0034027C  90 04 01 AC */	stw r0, 0x1ac(r4)
/* 803436A0 00340280  7C 13 E2 A6 */	mfspr r0, 0x393
/* 803436A4 00340284  90 04 01 B0 */	stw r0, 0x1b0(r4)
/* 803436A8 00340288  7C 14 E2 A6 */	mfspr r0, 0x394
/* 803436AC 0034028C  90 04 01 B4 */	stw r0, 0x1b4(r4)
/* 803436B0 00340290  7C 15 E2 A6 */	mfspr r0, 0x395
/* 803436B4 00340294  90 04 01 B8 */	stw r0, 0x1b8(r4)
/* 803436B8 00340298  7C 16 E2 A6 */	mfspr r0, 0x396
/* 803436BC 0034029C  90 04 01 BC */	stw r0, 0x1bc(r4)
/* 803436C0 003402A0  7C 17 E2 A6 */	mfspr r0, 0x397
/* 803436C4 003402A4  90 04 01 C0 */	stw r0, 0x1c0(r4)
/* 803436C8 003402A8  7C B2 02 A6 */	mfdsisr r5
/* 803436CC 003402AC  7C D3 02 A6 */	mfdar r6
/* 803436D0 003402B0  48 00 21 A0 */	b __OSUnhandledException
} // clang-format on
#pragma pop

extern unk_t ICFlashInvalidate();

#pragma push
asm unk_t __OSPSInit()
{ // clang-format off
    nofralloc
/* 803436D4 003402B4  7C 08 02 A6 */	mflr r0
/* 803436D8 003402B8  90 01 00 04 */	stw r0, 4(r1)
/* 803436DC 003402BC  94 21 FF F8 */	stwu r1, -8(r1)
/* 803436E0 003402C0  4B FF 27 C9 */	bl PPCMfhid2
/* 803436E4 003402C4  64 63 A0 00 */	oris r3, r3, 0xa000
/* 803436E8 003402C8  4B FF 27 C9 */	bl PPCMthid2
/* 803436EC 003402CC  48 00 12 21 */	bl ICFlashInvalidate
/* 803436F0 003402D0  7C 00 04 AC */	sync
/* 803436F4 003402D4  38 60 00 00 */	li r3, 0
/* 803436F8 003402D8  7C 70 E3 A6 */	mtspr 0x390, r3
/* 803436FC 003402DC  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80343700 003402E0  38 21 00 08 */	addi r1, r1, 8
/* 80343704 003402E4  7C 08 03 A6 */	mtlr r0
/* 80343708 003402E8  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t __OSGetDIConfig()
{ // clang-format off
    nofralloc
/* 8034370C 003402EC  3C 60 CC 00 */	lis r3, 0xCC006000@ha
/* 80343710 003402F0  38 63 60 00 */	addi r3, r3, 0xCC006000@l
/* 80343714 003402F4  80 03 00 24 */	lwz r0, 0x24(r3)
/* 80343718 003402F8  54 03 06 3E */	clrlwi r3, r0, 0x18
/* 8034371C 003402FC  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop
