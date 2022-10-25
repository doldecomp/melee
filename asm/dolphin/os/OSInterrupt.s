.include "macros.inc"

.section .text  # 0x80347364 - 0x80347BC8

.global __OSInterruptInit
__OSInterruptInit:
/* 803473E0 00343FC0  7C 08 02 A6 */	mflr r0
/* 803473E4 00343FC4  90 01 00 04 */	stw r0, 4(r1)
/* 803473E8 00343FC8  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 803473EC 00343FCC  93 E1 00 0C */	stw r31, 0xc(r1)
/* 803473F0 00343FD0  3F E0 80 00 */	lis r31, 0x80003040@ha
/* 803473F4 00343FD4  38 1F 30 40 */	addi r0, r31, 0x80003040@l
/* 803473F8 00343FD8  90 0D BC D8 */	stw r0, lbl_804D7378@sda21(r13)
/* 803473FC 00343FDC  38 80 00 00 */	li r4, 0
/* 80347400 00343FE0  38 A0 00 80 */	li r5, 0x80
/* 80347404 00343FE4  80 6D BC D8 */	lwz r3, lbl_804D7378@sda21(r13)
/* 80347408 00343FE8  4B CB BC F9 */	bl memset
/* 8034740C 00343FEC  38 00 00 00 */	li r0, 0
/* 80347410 00343FF0  90 1F 00 C4 */	stw r0, 0xc4(r31)
/* 80347414 00343FF4  3C 60 CC 00 */	lis r3, 0xCC003000@ha
/* 80347418 00343FF8  38 83 30 00 */	addi r4, r3, 0xCC003000@l
/* 8034741C 00343FFC  90 1F 00 C8 */	stw r0, 0xc8(r31)
/* 80347420 00344000  38 00 00 F0 */	li r0, 0xf0
/* 80347424 00344004  38 60 FF E0 */	li r3, -32
/* 80347428 00344008  90 04 00 04 */	stw r0, 4(r4)
/* 8034742C 0034400C  48 00 03 01 */	bl __OSMaskInterrupts
/* 80347430 00344010  3C 60 80 34 */	lis r3, lbl_80347B80@ha
/* 80347434 00344014  38 83 7B 80 */	addi r4, r3, lbl_80347B80@l
/* 80347438 00344018  38 60 00 04 */	li r3, 4
/* 8034743C 0034401C  4B FF C1 79 */	bl __OSSetExceptionHandler
/* 80347440 00344020  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80347444 00344024  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80347448 00344028  38 21 00 10 */	addi r1, r1, 0x10
/* 8034744C 0034402C  7C 08 03 A6 */	mtlr r0
/* 80347450 00344030  4E 80 00 20 */	blr 

.global SetInterruptMask
SetInterruptMask:
/* 80347454 00344034  7C 60 00 34 */	cntlzw r0, r3
/* 80347458 00344038  2C 00 00 0C */	cmpwi r0, 0xc
/* 8034745C 0034403C  40 80 00 24 */	bge lbl_80347480
/* 80347460 00344040  2C 00 00 08 */	cmpwi r0, 8
/* 80347464 00344044  41 82 00 FC */	beq lbl_80347560
/* 80347468 00344048  40 80 01 28 */	bge lbl_80347590
/* 8034746C 0034404C  2C 00 00 05 */	cmpwi r0, 5
/* 80347470 00344050  40 80 00 9C */	bge lbl_8034750C
/* 80347474 00344054  2C 00 00 00 */	cmpwi r0, 0
/* 80347478 00344058  40 80 00 28 */	bge lbl_803474A0
/* 8034747C 0034405C  48 00 02 AC */	b lbl_80347728
lbl_80347480:
/* 80347480 00344060  2C 00 00 11 */	cmpwi r0, 0x11
/* 80347484 00344064  40 80 00 10 */	bge lbl_80347494
/* 80347488 00344068  2C 00 00 0F */	cmpwi r0, 0xf
/* 8034748C 0034406C  40 80 01 A8 */	bge lbl_80347634
/* 80347490 00344070  48 00 01 50 */	b lbl_803475E0
lbl_80347494:
/* 80347494 00344074  2C 00 00 1B */	cmpwi r0, 0x1b
/* 80347498 00344078  40 80 02 90 */	bge lbl_80347728
/* 8034749C 0034407C  48 00 01 D8 */	b lbl_80347674
lbl_803474A0:
/* 803474A0 00344080  54 80 00 00 */	rlwinm r0, r4, 0, 0, 0
/* 803474A4 00344084  28 00 00 00 */	cmplwi r0, 0
/* 803474A8 00344088  38 A0 00 00 */	li r5, 0
/* 803474AC 0034408C  40 82 00 08 */	bne lbl_803474B4
/* 803474B0 00344090  60 A5 00 01 */	ori r5, r5, 1
lbl_803474B4:
/* 803474B4 00344094  54 80 00 42 */	rlwinm r0, r4, 0, 1, 1
/* 803474B8 00344098  28 00 00 00 */	cmplwi r0, 0
/* 803474BC 0034409C  40 82 00 08 */	bne lbl_803474C4
/* 803474C0 003440A0  60 A5 00 02 */	ori r5, r5, 2
lbl_803474C4:
/* 803474C4 003440A4  54 80 00 84 */	rlwinm r0, r4, 0, 2, 2
/* 803474C8 003440A8  28 00 00 00 */	cmplwi r0, 0
/* 803474CC 003440AC  40 82 00 08 */	bne lbl_803474D4
/* 803474D0 003440B0  60 A5 00 04 */	ori r5, r5, 4
lbl_803474D4:
/* 803474D4 003440B4  54 80 00 C6 */	rlwinm r0, r4, 0, 3, 3
/* 803474D8 003440B8  28 00 00 00 */	cmplwi r0, 0
/* 803474DC 003440BC  40 82 00 08 */	bne lbl_803474E4
/* 803474E0 003440C0  60 A5 00 08 */	ori r5, r5, 8
lbl_803474E4:
/* 803474E4 003440C4  54 80 01 08 */	rlwinm r0, r4, 0, 4, 4
/* 803474E8 003440C8  28 00 00 00 */	cmplwi r0, 0
/* 803474EC 003440CC  40 82 00 08 */	bne lbl_803474F4
/* 803474F0 003440D0  60 A5 00 10 */	ori r5, r5, 0x10
lbl_803474F4:
/* 803474F4 003440D4  3C 80 CC 00 */	lis r4, 0xCC004000@ha
/* 803474F8 003440D8  54 A0 04 3E */	clrlwi r0, r5, 0x10
/* 803474FC 003440DC  38 84 40 00 */	addi r4, r4, 0xCC004000@l
/* 80347500 003440E0  B0 04 00 1C */	sth r0, 0x1c(r4)
/* 80347504 003440E4  54 63 01 7E */	clrlwi r3, r3, 5
/* 80347508 003440E8  48 00 02 20 */	b lbl_80347728
lbl_8034750C:
/* 8034750C 003440EC  3C A0 CC 00 */	lis r5, 0xCC005000@ha
/* 80347510 003440F0  38 A5 50 00 */	addi r5, r5, 0xCC005000@l
/* 80347514 003440F4  38 A5 00 0A */	addi r5, r5, 0xa
/* 80347518 003440F8  54 80 01 4A */	rlwinm r0, r4, 0, 5, 5
/* 8034751C 003440FC  A0 C5 00 00 */	lhz r6, 0(r5)
/* 80347520 00344100  28 00 00 00 */	cmplwi r0, 0
/* 80347524 00344104  54 C6 07 6C */	rlwinm r6, r6, 0, 0x1d, 0x16
/* 80347528 00344108  40 82 00 08 */	bne lbl_80347530
/* 8034752C 0034410C  60 C6 00 10 */	ori r6, r6, 0x10
lbl_80347530:
/* 80347530 00344110  54 80 01 8C */	rlwinm r0, r4, 0, 6, 6
/* 80347534 00344114  28 00 00 00 */	cmplwi r0, 0
/* 80347538 00344118  40 82 00 08 */	bne lbl_80347540
/* 8034753C 0034411C  60 C6 00 40 */	ori r6, r6, 0x40
lbl_80347540:
/* 80347540 00344120  54 80 01 CE */	rlwinm r0, r4, 0, 7, 7
/* 80347544 00344124  28 00 00 00 */	cmplwi r0, 0
/* 80347548 00344128  40 82 00 08 */	bne lbl_80347550
/* 8034754C 0034412C  60 C6 01 00 */	ori r6, r6, 0x100
lbl_80347550:
/* 80347550 00344130  54 C0 04 3E */	clrlwi r0, r6, 0x10
/* 80347554 00344134  B0 05 00 00 */	sth r0, 0(r5)
/* 80347558 00344138  54 63 02 08 */	rlwinm r3, r3, 0, 8, 4
/* 8034755C 0034413C  48 00 01 CC */	b lbl_80347728
lbl_80347560:
/* 80347560 00344140  54 80 02 10 */	rlwinm r0, r4, 0, 8, 8
/* 80347564 00344144  3C 80 CC 00 */	lis r4, 0xCC006C00@ha
/* 80347568 00344148  28 00 00 00 */	cmplwi r0, 0
/* 8034756C 0034414C  80 A4 6C 00 */	lwz r5, 0xCC006C00@l(r4)
/* 80347570 00344150  38 00 FF D3 */	li r0, -45
/* 80347574 00344154  7C A5 00 38 */	and r5, r5, r0
/* 80347578 00344158  40 82 00 08 */	bne lbl_80347580
/* 8034757C 0034415C  60 A5 00 04 */	ori r5, r5, 4
lbl_80347580:
/* 80347580 00344160  3C 80 CC 00 */	lis r4, 0xCC006C00@ha
/* 80347584 00344164  90 A4 6C 00 */	stw r5, 0xCC006C00@l(r4)
/* 80347588 00344168  54 63 02 4E */	rlwinm r3, r3, 0, 9, 7
/* 8034758C 0034416C  48 00 01 9C */	b lbl_80347728
lbl_80347590:
/* 80347590 00344170  54 80 02 52 */	rlwinm r0, r4, 0, 9, 9
/* 80347594 00344174  3C A0 CC 00 */	lis r5, 0xCC006800@ha
/* 80347598 00344178  28 00 00 00 */	cmplwi r0, 0
/* 8034759C 0034417C  80 A5 68 00 */	lwz r5, 0xCC006800@l(r5)
/* 803475A0 00344180  38 00 D3 F0 */	li r0, -11280
/* 803475A4 00344184  7C A5 00 38 */	and r5, r5, r0
/* 803475A8 00344188  40 82 00 08 */	bne lbl_803475B0
/* 803475AC 0034418C  60 A5 00 01 */	ori r5, r5, 1
lbl_803475B0:
/* 803475B0 00344190  54 80 02 94 */	rlwinm r0, r4, 0, 0xa, 0xa
/* 803475B4 00344194  28 00 00 00 */	cmplwi r0, 0
/* 803475B8 00344198  40 82 00 08 */	bne lbl_803475C0
/* 803475BC 0034419C  60 A5 00 04 */	ori r5, r5, 4
lbl_803475C0:
/* 803475C0 003441A0  54 80 02 D6 */	rlwinm r0, r4, 0, 0xb, 0xb
/* 803475C4 003441A4  28 00 00 00 */	cmplwi r0, 0
/* 803475C8 003441A8  40 82 00 08 */	bne lbl_803475D0
/* 803475CC 003441AC  60 A5 04 00 */	ori r5, r5, 0x400
lbl_803475D0:
/* 803475D0 003441B0  3C 80 CC 00 */	lis r4, 0xCC006800@ha
/* 803475D4 003441B4  90 A4 68 00 */	stw r5, 0xCC006800@l(r4)
/* 803475D8 003441B8  54 63 03 10 */	rlwinm r3, r3, 0, 0xc, 8
/* 803475DC 003441BC  48 00 01 4C */	b lbl_80347728
lbl_803475E0:
/* 803475E0 003441C0  3C A0 CC 00 */	lis r5, 0xCC006800@ha
/* 803475E4 003441C4  38 C5 68 00 */	addi r6, r5, 0xCC006800@l
/* 803475E8 003441C8  38 C6 00 14 */	addi r6, r6, 0x14
/* 803475EC 003441CC  54 80 03 18 */	rlwinm r0, r4, 0, 0xc, 0xc
/* 803475F0 003441D0  80 E6 00 00 */	lwz r7, 0(r6)
/* 803475F4 003441D4  38 A0 F3 F0 */	li r5, -3088
/* 803475F8 003441D8  28 00 00 00 */	cmplwi r0, 0
/* 803475FC 003441DC  7C E7 28 38 */	and r7, r7, r5
/* 80347600 003441E0  40 82 00 08 */	bne lbl_80347608
/* 80347604 003441E4  60 E7 00 01 */	ori r7, r7, 1
lbl_80347608:
/* 80347608 003441E8  54 80 03 5A */	rlwinm r0, r4, 0, 0xd, 0xd
/* 8034760C 003441EC  28 00 00 00 */	cmplwi r0, 0
/* 80347610 003441F0  40 82 00 08 */	bne lbl_80347618
/* 80347614 003441F4  60 E7 00 04 */	ori r7, r7, 4
lbl_80347618:
/* 80347618 003441F8  54 80 03 9C */	rlwinm r0, r4, 0, 0xe, 0xe
/* 8034761C 003441FC  28 00 00 00 */	cmplwi r0, 0
/* 80347620 00344200  40 82 00 08 */	bne lbl_80347628
/* 80347624 00344204  60 E7 04 00 */	ori r7, r7, 0x400
lbl_80347628:
/* 80347628 00344208  90 E6 00 00 */	stw r7, 0(r6)
/* 8034762C 0034420C  54 63 03 D6 */	rlwinm r3, r3, 0, 0xf, 0xb
/* 80347630 00344210  48 00 00 F8 */	b lbl_80347728
lbl_80347634:
/* 80347634 00344214  3C A0 CC 00 */	lis r5, 0xCC006800@ha
/* 80347638 00344218  38 A5 68 00 */	addi r5, r5, 0xCC006800@l
/* 8034763C 0034421C  38 A5 00 28 */	addi r5, r5, 0x28
/* 80347640 00344220  54 80 03 DE */	rlwinm r0, r4, 0, 0xf, 0xf
/* 80347644 00344224  80 C5 00 00 */	lwz r6, 0(r5)
/* 80347648 00344228  28 00 00 00 */	cmplwi r0, 0
/* 8034764C 0034422C  54 C6 00 36 */	rlwinm r6, r6, 0, 0, 0x1b
/* 80347650 00344230  40 82 00 08 */	bne lbl_80347658
/* 80347654 00344234  60 C6 00 01 */	ori r6, r6, 1
lbl_80347658:
/* 80347658 00344238  54 80 04 20 */	rlwinm r0, r4, 0, 0x10, 0x10
/* 8034765C 0034423C  28 00 00 00 */	cmplwi r0, 0
/* 80347660 00344240  40 82 00 08 */	bne lbl_80347668
/* 80347664 00344244  60 C6 00 04 */	ori r6, r6, 4
lbl_80347668:
/* 80347668 00344248  90 C5 00 00 */	stw r6, 0(r5)
/* 8034766C 0034424C  54 63 04 5C */	rlwinm r3, r3, 0, 0x11, 0xe
/* 80347670 00344250  48 00 00 B8 */	b lbl_80347728
lbl_80347674:
/* 80347674 00344254  54 80 04 62 */	rlwinm r0, r4, 0, 0x11, 0x11
/* 80347678 00344258  28 00 00 00 */	cmplwi r0, 0
/* 8034767C 0034425C  38 A0 00 F0 */	li r5, 0xf0
/* 80347680 00344260  40 82 00 08 */	bne lbl_80347688
/* 80347684 00344264  60 A5 08 00 */	ori r5, r5, 0x800
lbl_80347688:
/* 80347688 00344268  54 80 05 28 */	rlwinm r0, r4, 0, 0x14, 0x14
/* 8034768C 0034426C  28 00 00 00 */	cmplwi r0, 0
/* 80347690 00344270  40 82 00 08 */	bne lbl_80347698
/* 80347694 00344274  60 A5 00 08 */	ori r5, r5, 8
lbl_80347698:
/* 80347698 00344278  54 80 05 6A */	rlwinm r0, r4, 0, 0x15, 0x15
/* 8034769C 0034427C  28 00 00 00 */	cmplwi r0, 0
/* 803476A0 00344280  40 82 00 08 */	bne lbl_803476A8
/* 803476A4 00344284  60 A5 00 04 */	ori r5, r5, 4
lbl_803476A8:
/* 803476A8 00344288  54 80 05 AC */	rlwinm r0, r4, 0, 0x16, 0x16
/* 803476AC 0034428C  28 00 00 00 */	cmplwi r0, 0
/* 803476B0 00344290  40 82 00 08 */	bne lbl_803476B8
/* 803476B4 00344294  60 A5 00 02 */	ori r5, r5, 2
lbl_803476B8:
/* 803476B8 00344298  54 80 05 EE */	rlwinm r0, r4, 0, 0x17, 0x17
/* 803476BC 0034429C  28 00 00 00 */	cmplwi r0, 0
/* 803476C0 003442A0  40 82 00 08 */	bne lbl_803476C8
/* 803476C4 003442A4  60 A5 00 01 */	ori r5, r5, 1
lbl_803476C8:
/* 803476C8 003442A8  54 80 06 30 */	rlwinm r0, r4, 0, 0x18, 0x18
/* 803476CC 003442AC  28 00 00 00 */	cmplwi r0, 0
/* 803476D0 003442B0  40 82 00 08 */	bne lbl_803476D8
/* 803476D4 003442B4  60 A5 01 00 */	ori r5, r5, 0x100
lbl_803476D8:
/* 803476D8 003442B8  54 80 06 72 */	rlwinm r0, r4, 0, 0x19, 0x19
/* 803476DC 003442BC  28 00 00 00 */	cmplwi r0, 0
/* 803476E0 003442C0  40 82 00 08 */	bne lbl_803476E8
/* 803476E4 003442C4  60 A5 10 00 */	ori r5, r5, 0x1000
lbl_803476E8:
/* 803476E8 003442C8  54 80 04 A4 */	rlwinm r0, r4, 0, 0x12, 0x12
/* 803476EC 003442CC  28 00 00 00 */	cmplwi r0, 0
/* 803476F0 003442D0  40 82 00 08 */	bne lbl_803476F8
/* 803476F4 003442D4  60 A5 02 00 */	ori r5, r5, 0x200
lbl_803476F8:
/* 803476F8 003442D8  54 80 04 E6 */	rlwinm r0, r4, 0, 0x13, 0x13
/* 803476FC 003442DC  28 00 00 00 */	cmplwi r0, 0
/* 80347700 003442E0  40 82 00 08 */	bne lbl_80347708
/* 80347704 003442E4  60 A5 04 00 */	ori r5, r5, 0x400
lbl_80347708:
/* 80347708 003442E8  54 80 06 B4 */	rlwinm r0, r4, 0, 0x1a, 0x1a
/* 8034770C 003442EC  28 00 00 00 */	cmplwi r0, 0
/* 80347710 003442F0  40 82 00 08 */	bne lbl_80347718
/* 80347714 003442F4  60 A5 20 00 */	ori r5, r5, 0x2000
lbl_80347718:
/* 80347718 003442F8  3C 80 CC 00 */	lis r4, 0xCC003000@ha
/* 8034771C 003442FC  38 84 30 00 */	addi r4, r4, 0xCC003000@l
/* 80347720 00344300  90 A4 00 04 */	stw r5, 4(r4)
/* 80347724 00344304  54 63 06 E0 */	rlwinm r3, r3, 0, 0x1b, 0x10
lbl_80347728:
/* 80347728 00344308  4E 80 00 20 */	blr 

.global __OSMaskInterrupts
__OSMaskInterrupts:
/* 8034772C 0034430C  7C 08 02 A6 */	mflr r0
/* 80347730 00344310  90 01 00 04 */	stw r0, 4(r1)
/* 80347734 00344314  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80347738 00344318  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8034773C 0034431C  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80347740 00344320  93 A1 00 14 */	stw r29, 0x14(r1)
/* 80347744 00344324  7C 7F 1B 78 */	mr r31, r3
/* 80347748 00344328  4B FF FC 1D */	bl OSDisableInterrupts
/* 8034774C 0034432C  3C 80 80 00 */	lis r4, 0x800000C4@ha
/* 80347750 00344330  83 A4 00 C4 */	lwz r29, 0x800000C4@l(r4)
/* 80347754 00344334  7C 7E 1B 78 */	mr r30, r3
/* 80347758 00344338  80 A4 00 C8 */	lwz r5, 0xc8(r4)
/* 8034775C 0034433C  7F A0 2B 78 */	or r0, r29, r5
/* 80347760 00344340  7F E3 00 78 */	andc r3, r31, r0
/* 80347764 00344344  7F FF EB 78 */	or r31, r31, r29
/* 80347768 00344348  93 E4 00 C4 */	stw r31, 0xc4(r4)
/* 8034776C 0034434C  7F FF 2B 78 */	or r31, r31, r5
/* 80347770 00344350  48 00 00 04 */	b lbl_80347774
lbl_80347774:
/* 80347774 00344354  48 00 00 04 */	b lbl_80347778
lbl_80347778:
/* 80347778 00344358  48 00 00 0C */	b lbl_80347784
lbl_8034777C:
/* 8034777C 0034435C  7F E4 FB 78 */	mr r4, r31
/* 80347780 00344360  4B FF FC D5 */	bl SetInterruptMask
lbl_80347784:
/* 80347784 00344364  28 03 00 00 */	cmplwi r3, 0
/* 80347788 00344368  40 82 FF F4 */	bne lbl_8034777C
/* 8034778C 0034436C  7F C3 F3 78 */	mr r3, r30
/* 80347790 00344370  4B FF FB FD */	bl OSRestoreInterrupts
/* 80347794 00344374  7F A3 EB 78 */	mr r3, r29
/* 80347798 00344378  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8034779C 0034437C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 803477A0 00344380  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 803477A4 00344384  7C 08 03 A6 */	mtlr r0
/* 803477A8 00344388  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 803477AC 0034438C  38 21 00 20 */	addi r1, r1, 0x20
/* 803477B0 00344390  4E 80 00 20 */	blr 

.global __OSUnmaskInterrupts
__OSUnmaskInterrupts:
/* 803477B4 00344394  7C 08 02 A6 */	mflr r0
/* 803477B8 00344398  90 01 00 04 */	stw r0, 4(r1)
/* 803477BC 0034439C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 803477C0 003443A0  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 803477C4 003443A4  93 C1 00 18 */	stw r30, 0x18(r1)
/* 803477C8 003443A8  93 A1 00 14 */	stw r29, 0x14(r1)
/* 803477CC 003443AC  7C 7F 1B 78 */	mr r31, r3
/* 803477D0 003443B0  4B FF FB 95 */	bl OSDisableInterrupts
/* 803477D4 003443B4  3C 80 80 00 */	lis r4, 0x800000C4@ha
/* 803477D8 003443B8  83 A4 00 C4 */	lwz r29, 0x800000C4@l(r4)
/* 803477DC 003443BC  7C 7E 1B 78 */	mr r30, r3
/* 803477E0 003443C0  80 A4 00 C8 */	lwz r5, 0xc8(r4)
/* 803477E4 003443C4  7F A0 2B 78 */	or r0, r29, r5
/* 803477E8 003443C8  7F E3 00 38 */	and r3, r31, r0
/* 803477EC 003443CC  7F BF F8 78 */	andc r31, r29, r31
/* 803477F0 003443D0  93 E4 00 C4 */	stw r31, 0xc4(r4)
/* 803477F4 003443D4  7F FF 2B 78 */	or r31, r31, r5
/* 803477F8 003443D8  48 00 00 04 */	b lbl_803477FC
lbl_803477FC:
/* 803477FC 003443DC  48 00 00 04 */	b lbl_80347800
lbl_80347800:
/* 80347800 003443E0  48 00 00 0C */	b lbl_8034780C
lbl_80347804:
/* 80347804 003443E4  7F E4 FB 78 */	mr r4, r31
/* 80347808 003443E8  4B FF FC 4D */	bl SetInterruptMask
lbl_8034780C:
/* 8034780C 003443EC  28 03 00 00 */	cmplwi r3, 0
/* 80347810 003443F0  40 82 FF F4 */	bne lbl_80347804
/* 80347814 003443F4  7F C3 F3 78 */	mr r3, r30
/* 80347818 003443F8  4B FF FB 75 */	bl OSRestoreInterrupts
/* 8034781C 003443FC  7F A3 EB 78 */	mr r3, r29
/* 80347820 00344400  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80347824 00344404  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80347828 00344408  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8034782C 0034440C  7C 08 03 A6 */	mtlr r0
/* 80347830 00344410  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 80347834 00344414  38 21 00 20 */	addi r1, r1, 0x20
/* 80347838 00344418  4E 80 00 20 */	blr 
lbl_8034783C:
/* 8034783C 0034441C  7C 08 02 A6 */	mflr r0
/* 80347840 00344420  90 01 00 04 */	stw r0, 4(r1)
/* 80347844 00344424  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 80347848 00344428  93 E1 00 24 */	stw r31, 0x24(r1)
/* 8034784C 0034442C  93 C1 00 20 */	stw r30, 0x20(r1)
/* 80347850 00344430  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 80347854 00344434  7C 9E 23 78 */	mr r30, r4
/* 80347858 00344438  3C 60 CC 00 */	lis r3, 0xCC003000@ha
/* 8034785C 0034443C  83 E3 30 00 */	lwz r31, 0xCC003000@l(r3)
/* 80347860 00344440  57 FF 04 1C */	rlwinm r31, r31, 0, 0x10, 0xe
/* 80347864 00344444  28 1F 00 00 */	cmplwi r31, 0
/* 80347868 00344448  41 82 00 18 */	beq lbl_80347880
/* 8034786C 0034444C  38 63 30 00 */	addi r3, r3, 0x3000
/* 80347870 00344450  80 03 00 04 */	lwz r0, 4(r3)
/* 80347874 00344454  7F E0 00 38 */	and r0, r31, r0
/* 80347878 00344458  28 00 00 00 */	cmplwi r0, 0
/* 8034787C 0034445C  40 82 00 0C */	bne lbl_80347888
lbl_80347880:
/* 80347880 00344460  7F C3 F3 78 */	mr r3, r30
/* 80347884 00344464  4B FF D8 F1 */	bl OSLoadContext
lbl_80347888:
/* 80347888 00344468  57 E0 06 30 */	rlwinm r0, r31, 0, 0x18, 0x18
/* 8034788C 0034446C  28 00 00 00 */	cmplwi r0, 0
/* 80347890 00344470  38 00 00 00 */	li r0, 0
/* 80347894 00344474  41 82 00 60 */	beq lbl_803478F4
/* 80347898 00344478  3C 60 CC 00 */	lis r3, 0xCC004000@ha
/* 8034789C 0034447C  38 63 40 00 */	addi r3, r3, 0xCC004000@l
/* 803478A0 00344480  A0 83 00 1E */	lhz r4, 0x1e(r3)
/* 803478A4 00344484  54 83 07 FE */	clrlwi r3, r4, 0x1f
/* 803478A8 00344488  28 03 00 00 */	cmplwi r3, 0
/* 803478AC 0034448C  41 82 00 08 */	beq lbl_803478B4
/* 803478B0 00344490  64 00 80 00 */	oris r0, r0, 0x8000
lbl_803478B4:
/* 803478B4 00344494  54 83 07 BC */	rlwinm r3, r4, 0, 0x1e, 0x1e
/* 803478B8 00344498  28 03 00 00 */	cmplwi r3, 0
/* 803478BC 0034449C  41 82 00 08 */	beq lbl_803478C4
/* 803478C0 003444A0  64 00 40 00 */	oris r0, r0, 0x4000
lbl_803478C4:
/* 803478C4 003444A4  54 83 07 7A */	rlwinm r3, r4, 0, 0x1d, 0x1d
/* 803478C8 003444A8  28 03 00 00 */	cmplwi r3, 0
/* 803478CC 003444AC  41 82 00 08 */	beq lbl_803478D4
/* 803478D0 003444B0  64 00 20 00 */	oris r0, r0, 0x2000
lbl_803478D4:
/* 803478D4 003444B4  54 83 07 38 */	rlwinm r3, r4, 0, 0x1c, 0x1c
/* 803478D8 003444B8  28 03 00 00 */	cmplwi r3, 0
/* 803478DC 003444BC  41 82 00 08 */	beq lbl_803478E4
/* 803478E0 003444C0  64 00 10 00 */	oris r0, r0, 0x1000
lbl_803478E4:
/* 803478E4 003444C4  54 83 06 F6 */	rlwinm r3, r4, 0, 0x1b, 0x1b
/* 803478E8 003444C8  28 03 00 00 */	cmplwi r3, 0
/* 803478EC 003444CC  41 82 00 08 */	beq lbl_803478F4
/* 803478F0 003444D0  64 00 08 00 */	oris r0, r0, 0x800
lbl_803478F4:
/* 803478F4 003444D4  57 E3 06 72 */	rlwinm r3, r31, 0, 0x19, 0x19
/* 803478F8 003444D8  28 03 00 00 */	cmplwi r3, 0
/* 803478FC 003444DC  41 82 00 40 */	beq lbl_8034793C
/* 80347900 003444E0  3C 60 CC 00 */	lis r3, 0xCC005000@ha
/* 80347904 003444E4  38 63 50 00 */	addi r3, r3, 0xCC005000@l
/* 80347908 003444E8  A0 83 00 0A */	lhz r4, 0xa(r3)
/* 8034790C 003444EC  54 83 07 38 */	rlwinm r3, r4, 0, 0x1c, 0x1c
/* 80347910 003444F0  28 03 00 00 */	cmplwi r3, 0
/* 80347914 003444F4  41 82 00 08 */	beq lbl_8034791C
/* 80347918 003444F8  64 00 04 00 */	oris r0, r0, 0x400
lbl_8034791C:
/* 8034791C 003444FC  54 83 06 B4 */	rlwinm r3, r4, 0, 0x1a, 0x1a
/* 80347920 00344500  28 03 00 00 */	cmplwi r3, 0
/* 80347924 00344504  41 82 00 08 */	beq lbl_8034792C
/* 80347928 00344508  64 00 02 00 */	oris r0, r0, 0x200
lbl_8034792C:
/* 8034792C 0034450C  54 83 06 30 */	rlwinm r3, r4, 0, 0x18, 0x18
/* 80347930 00344510  28 03 00 00 */	cmplwi r3, 0
/* 80347934 00344514  41 82 00 08 */	beq lbl_8034793C
/* 80347938 00344518  64 00 01 00 */	oris r0, r0, 0x100
lbl_8034793C:
/* 8034793C 0034451C  57 E3 06 B4 */	rlwinm r3, r31, 0, 0x1a, 0x1a
/* 80347940 00344520  28 03 00 00 */	cmplwi r3, 0
/* 80347944 00344524  41 82 00 1C */	beq lbl_80347960
/* 80347948 00344528  3C 60 CC 00 */	lis r3, 0xCC006C00@ha
/* 8034794C 0034452C  80 63 6C 00 */	lwz r3, 0xCC006C00@l(r3)
/* 80347950 00344530  54 63 07 38 */	rlwinm r3, r3, 0, 0x1c, 0x1c
/* 80347954 00344534  28 03 00 00 */	cmplwi r3, 0
/* 80347958 00344538  41 82 00 08 */	beq lbl_80347960
/* 8034795C 0034453C  64 00 00 80 */	oris r0, r0, 0x80
lbl_80347960:
/* 80347960 00344540  57 E3 06 F6 */	rlwinm r3, r31, 0, 0x1b, 0x1b
/* 80347964 00344544  28 03 00 00 */	cmplwi r3, 0
/* 80347968 00344548  41 82 00 A4 */	beq lbl_80347A0C
/* 8034796C 0034454C  3C 60 CC 00 */	lis r3, 0xCC006800@ha
/* 80347970 00344550  80 83 68 00 */	lwz r4, 0xCC006800@l(r3)
/* 80347974 00344554  54 83 07 BC */	rlwinm r3, r4, 0, 0x1e, 0x1e
/* 80347978 00344558  28 03 00 00 */	cmplwi r3, 0
/* 8034797C 0034455C  41 82 00 08 */	beq lbl_80347984
/* 80347980 00344560  64 00 00 40 */	oris r0, r0, 0x40
lbl_80347984:
/* 80347984 00344564  54 83 07 38 */	rlwinm r3, r4, 0, 0x1c, 0x1c
/* 80347988 00344568  28 03 00 00 */	cmplwi r3, 0
/* 8034798C 0034456C  41 82 00 08 */	beq lbl_80347994
/* 80347990 00344570  64 00 00 20 */	oris r0, r0, 0x20
lbl_80347994:
/* 80347994 00344574  54 83 05 28 */	rlwinm r3, r4, 0, 0x14, 0x14
/* 80347998 00344578  28 03 00 00 */	cmplwi r3, 0
/* 8034799C 0034457C  41 82 00 08 */	beq lbl_803479A4
/* 803479A0 00344580  64 00 00 10 */	oris r0, r0, 0x10
lbl_803479A4:
/* 803479A4 00344584  3C 60 CC 00 */	lis r3, 0xCC006800@ha
/* 803479A8 00344588  38 63 68 00 */	addi r3, r3, 0xCC006800@l
/* 803479AC 0034458C  80 83 00 14 */	lwz r4, 0x14(r3)
/* 803479B0 00344590  54 83 07 BC */	rlwinm r3, r4, 0, 0x1e, 0x1e
/* 803479B4 00344594  28 03 00 00 */	cmplwi r3, 0
/* 803479B8 00344598  41 82 00 08 */	beq lbl_803479C0
/* 803479BC 0034459C  64 00 00 08 */	oris r0, r0, 8
lbl_803479C0:
/* 803479C0 003445A0  54 83 07 38 */	rlwinm r3, r4, 0, 0x1c, 0x1c
/* 803479C4 003445A4  28 03 00 00 */	cmplwi r3, 0
/* 803479C8 003445A8  41 82 00 08 */	beq lbl_803479D0
/* 803479CC 003445AC  64 00 00 04 */	oris r0, r0, 4
lbl_803479D0:
/* 803479D0 003445B0  54 83 05 28 */	rlwinm r3, r4, 0, 0x14, 0x14
/* 803479D4 003445B4  28 03 00 00 */	cmplwi r3, 0
/* 803479D8 003445B8  41 82 00 08 */	beq lbl_803479E0
/* 803479DC 003445BC  64 00 00 02 */	oris r0, r0, 2
lbl_803479E0:
/* 803479E0 003445C0  3C 60 CC 00 */	lis r3, 0xCC006800@ha
/* 803479E4 003445C4  38 63 68 00 */	addi r3, r3, 0xCC006800@l
/* 803479E8 003445C8  80 83 00 28 */	lwz r4, 0x28(r3)
/* 803479EC 003445CC  54 83 07 BC */	rlwinm r3, r4, 0, 0x1e, 0x1e
/* 803479F0 003445D0  28 03 00 00 */	cmplwi r3, 0
/* 803479F4 003445D4  41 82 00 08 */	beq lbl_803479FC
/* 803479F8 003445D8  64 00 00 01 */	oris r0, r0, 1
lbl_803479FC:
/* 803479FC 003445DC  54 83 07 38 */	rlwinm r3, r4, 0, 0x1c, 0x1c
/* 80347A00 003445E0  28 03 00 00 */	cmplwi r3, 0
/* 80347A04 003445E4  41 82 00 08 */	beq lbl_80347A0C
/* 80347A08 003445E8  60 00 80 00 */	ori r0, r0, 0x8000
lbl_80347A0C:
/* 80347A0C 003445EC  57 E3 04 A4 */	rlwinm r3, r31, 0, 0x12, 0x12
/* 80347A10 003445F0  28 03 00 00 */	cmplwi r3, 0
/* 80347A14 003445F4  41 82 00 08 */	beq lbl_80347A1C
/* 80347A18 003445F8  60 00 00 20 */	ori r0, r0, 0x20
lbl_80347A1C:
/* 80347A1C 003445FC  57 E3 04 E6 */	rlwinm r3, r31, 0, 0x13, 0x13
/* 80347A20 00344600  28 03 00 00 */	cmplwi r3, 0
/* 80347A24 00344604  41 82 00 08 */	beq lbl_80347A2C
/* 80347A28 00344608  60 00 00 40 */	ori r0, r0, 0x40
lbl_80347A2C:
/* 80347A2C 0034460C  57 E3 05 6A */	rlwinm r3, r31, 0, 0x15, 0x15
/* 80347A30 00344610  28 03 00 00 */	cmplwi r3, 0
/* 80347A34 00344614  41 82 00 08 */	beq lbl_80347A3C
/* 80347A38 00344618  60 00 10 00 */	ori r0, r0, 0x1000
lbl_80347A3C:
/* 80347A3C 0034461C  57 E3 05 AC */	rlwinm r3, r31, 0, 0x16, 0x16
/* 80347A40 00344620  28 03 00 00 */	cmplwi r3, 0
/* 80347A44 00344624  41 82 00 08 */	beq lbl_80347A4C
/* 80347A48 00344628  60 00 20 00 */	ori r0, r0, 0x2000
lbl_80347A4C:
/* 80347A4C 0034462C  57 E3 05 EE */	rlwinm r3, r31, 0, 0x17, 0x17
/* 80347A50 00344630  28 03 00 00 */	cmplwi r3, 0
/* 80347A54 00344634  41 82 00 08 */	beq lbl_80347A5C
/* 80347A58 00344638  60 00 00 80 */	ori r0, r0, 0x80
lbl_80347A5C:
/* 80347A5C 0034463C  57 E3 07 38 */	rlwinm r3, r31, 0, 0x1c, 0x1c
/* 80347A60 00344640  28 03 00 00 */	cmplwi r3, 0
/* 80347A64 00344644  41 82 00 08 */	beq lbl_80347A6C
/* 80347A68 00344648  60 00 08 00 */	ori r0, r0, 0x800
lbl_80347A6C:
/* 80347A6C 0034464C  57 E3 07 7A */	rlwinm r3, r31, 0, 0x1d, 0x1d
/* 80347A70 00344650  28 03 00 00 */	cmplwi r3, 0
/* 80347A74 00344654  41 82 00 08 */	beq lbl_80347A7C
/* 80347A78 00344658  60 00 04 00 */	ori r0, r0, 0x400
lbl_80347A7C:
/* 80347A7C 0034465C  57 E3 07 BC */	rlwinm r3, r31, 0, 0x1e, 0x1e
/* 80347A80 00344660  28 03 00 00 */	cmplwi r3, 0
/* 80347A84 00344664  41 82 00 08 */	beq lbl_80347A8C
/* 80347A88 00344668  60 00 02 00 */	ori r0, r0, 0x200
lbl_80347A8C:
/* 80347A8C 0034466C  57 E3 05 28 */	rlwinm r3, r31, 0, 0x14, 0x14
/* 80347A90 00344670  28 03 00 00 */	cmplwi r3, 0
/* 80347A94 00344674  41 82 00 08 */	beq lbl_80347A9C
/* 80347A98 00344678  60 00 40 00 */	ori r0, r0, 0x4000
lbl_80347A9C:
/* 80347A9C 0034467C  57 E3 07 FE */	clrlwi r3, r31, 0x1f
/* 80347AA0 00344680  28 03 00 00 */	cmplwi r3, 0
/* 80347AA4 00344684  41 82 00 08 */	beq lbl_80347AAC
/* 80347AA8 00344688  60 00 01 00 */	ori r0, r0, 0x100
lbl_80347AAC:
/* 80347AAC 0034468C  3C 60 80 00 */	lis r3, 0x800000C4@ha
/* 80347AB0 00344690  80 83 00 C4 */	lwz r4, 0x800000C4@l(r3)
/* 80347AB4 00344694  80 63 00 C8 */	lwz r3, 0xc8(r3)
/* 80347AB8 00344698  7C 83 1B 78 */	or r3, r4, r3
/* 80347ABC 0034469C  7C 04 18 78 */	andc r4, r0, r3
/* 80347AC0 003446A0  28 04 00 00 */	cmplwi r4, 0
/* 80347AC4 003446A4  41 82 00 98 */	beq lbl_80347B5C
/* 80347AC8 003446A8  3C 60 80 40 */	lis r3, lbl_80402318@ha
/* 80347ACC 003446AC  38 03 23 18 */	addi r0, r3, lbl_80402318@l
/* 80347AD0 003446B0  7C 03 03 78 */	mr r3, r0
/* 80347AD4 003446B4  48 00 00 04 */	b lbl_80347AD8
lbl_80347AD8:
/* 80347AD8 003446B8  48 00 00 04 */	b lbl_80347ADC
lbl_80347ADC:
/* 80347ADC 003446BC  80 03 00 00 */	lwz r0, 0(r3)
/* 80347AE0 003446C0  7C 80 00 38 */	and r0, r4, r0
/* 80347AE4 003446C4  28 00 00 00 */	cmplwi r0, 0
/* 80347AE8 003446C8  41 82 00 10 */	beq lbl_80347AF8
/* 80347AEC 003446CC  7C 00 00 34 */	cntlzw r0, r0
/* 80347AF0 003446D0  7C 1D 07 34 */	extsh r29, r0
/* 80347AF4 003446D4  48 00 00 0C */	b lbl_80347B00
lbl_80347AF8:
/* 80347AF8 003446D8  38 63 00 04 */	addi r3, r3, 4
/* 80347AFC 003446DC  4B FF FF E0 */	b lbl_80347ADC
lbl_80347B00:
/* 80347B00 003446E0  80 6D BC D8 */	lwz r3, lbl_804D7378@sda21(r13)
/* 80347B04 003446E4  57 A0 10 3A */	slwi r0, r29, 2
/* 80347B08 003446E8  7F E3 00 2E */	lwzx r31, r3, r0
/* 80347B0C 003446EC  28 1F 00 00 */	cmplwi r31, 0
/* 80347B10 003446F0  41 82 00 4C */	beq lbl_80347B5C
/* 80347B14 003446F4  2C 1D 00 04 */	cmpwi r29, 4
/* 80347B18 003446F8  40 81 00 1C */	ble lbl_80347B34
/* 80347B1C 003446FC  B3 AD BC E0 */	sth r29, __OSLastInterrupt@sda21(r13)
/* 80347B20 00344700  48 00 48 D1 */	bl OSGetTime
/* 80347B24 00344704  90 8D BC EC */	stw r4, lbl_804D738C@sda21(r13)
/* 80347B28 00344708  90 6D BC E8 */	stw r3, __OSLastInterruptTime@sda21(r13)
/* 80347B2C 0034470C  80 1E 01 98 */	lwz r0, 0x198(r30)
/* 80347B30 00344710  90 0D BC DC */	stw r0, __OSLastInterruptSrr0@sda21(r13)
lbl_80347B34:
/* 80347B34 00344714  48 00 32 15 */	bl OSDisableScheduler
/* 80347B38 00344718  7F A3 EB 78 */	mr r3, r29
/* 80347B3C 0034471C  7F C4 F3 78 */	mr r4, r30
/* 80347B40 00344720  7F EC FB 78 */	mr r12, r31
/* 80347B44 00344724  7D 88 03 A6 */	mtlr r12
/* 80347B48 00344728  4E 80 00 21 */	blrl 
/* 80347B4C 0034472C  48 00 32 3D */	bl OSEnableScheduler
/* 80347B50 00344730  48 00 36 DD */	bl __OSReschedule
/* 80347B54 00344734  7F C3 F3 78 */	mr r3, r30
/* 80347B58 00344738  4B FF D6 1D */	bl OSLoadContext
lbl_80347B5C:
/* 80347B5C 0034473C  7F C3 F3 78 */	mr r3, r30
/* 80347B60 00344740  4B FF D6 15 */	bl OSLoadContext
/* 80347B64 00344744  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 80347B68 00344748  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 80347B6C 0034474C  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 80347B70 00344750  7C 08 03 A6 */	mtlr r0
/* 80347B74 00344754  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 80347B78 00344758  38 21 00 28 */	addi r1, r1, 0x28
/* 80347B7C 0034475C  4E 80 00 20 */	blr 
lbl_80347B80:
/* 80347B80 00344760  90 04 00 00 */	stw r0, 0(r4)
/* 80347B84 00344764  90 24 00 04 */	stw r1, 4(r4)
/* 80347B88 00344768  90 44 00 08 */	stw r2, 8(r4)
/* 80347B8C 0034476C  BC C4 00 18 */	stmw r6, 0x18(r4)
/* 80347B90 00344770  7C 11 E2 A6 */	mfspr r0, 0x391
/* 80347B94 00344774  90 04 01 A8 */	stw r0, 0x1a8(r4)
/* 80347B98 00344778  7C 12 E2 A6 */	mfspr r0, 0x392
/* 80347B9C 0034477C  90 04 01 AC */	stw r0, 0x1ac(r4)
/* 80347BA0 00344780  7C 13 E2 A6 */	mfspr r0, 0x393
/* 80347BA4 00344784  90 04 01 B0 */	stw r0, 0x1b0(r4)
/* 80347BA8 00344788  7C 14 E2 A6 */	mfspr r0, 0x394
/* 80347BAC 0034478C  90 04 01 B4 */	stw r0, 0x1b4(r4)
/* 80347BB0 00344790  7C 15 E2 A6 */	mfspr r0, 0x395
/* 80347BB4 00344794  90 04 01 B8 */	stw r0, 0x1b8(r4)
/* 80347BB8 00344798  7C 16 E2 A6 */	mfspr r0, 0x396
/* 80347BBC 0034479C  90 04 01 BC */	stw r0, 0x1bc(r4)
/* 80347BC0 003447A0  7C 17 E2 A6 */	mfspr r0, 0x397
/* 80347BC4 003447A4  90 04 01 C0 */	stw r0, 0x1c0(r4)
/* 80347BC8 003447A8  4B FF FC 74 */	b lbl_8034783C


.section .data
    .balign 8
.global lbl_80402318
lbl_80402318:
    .4byte 0x00000100
    .4byte 0x00000040
    .4byte 0xF8000000
    .4byte 0x00000200
    .4byte 0x00000080
    .4byte 0x00003000
    .4byte 0x00000020
    .4byte 0x03FF8C00
    .4byte 0x04000000
    .4byte 0x00004000
    .4byte 0xFFFFFFFF
    .4byte NULL


.section .sbss
    .4byte NULL
.global lbl_804D7378
lbl_804D7378:
	.skip 0x4
.global __OSLastInterruptSrr0
__OSLastInterruptSrr0:
	.skip 0x4
.global __OSLastInterrupt
__OSLastInterrupt:
	.skip 0x8
.global __OSLastInterruptTime
__OSLastInterruptTime:
	.skip 0x4
.global lbl_804D738C
lbl_804D738C:
	.skip 0x4
