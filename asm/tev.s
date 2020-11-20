.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

.global func_80362400
func_80362400:
/* 80362400 0035EFE0  7C 08 02 A6 */	mflr r0
/* 80362404 0035EFE4  90 01 00 04 */	stw r0, 4(r1)
/* 80362408 0035EFE8  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8036240C 0035EFEC  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80362410 0035EFF0  3B E0 00 00 */	li r31, 0
/* 80362414 0035EFF4  93 C1 00 10 */	stw r30, 0x10(r1)
/* 80362418 0035EFF8  3B C3 00 00 */	addi r30, r3, 0
/* 8036241C 0035EFFC  48 00 00 24 */	b lbl_80362440
lbl_80362420:
/* 80362420 0035F000  80 7E 00 04 */	lwz r3, 4(r30)
/* 80362424 0035F004  48 00 02 95 */	bl func_803626B8
/* 80362428 0035F008  7C 03 F8 00 */	cmpw r3, r31
/* 8036242C 0035F00C  40 81 00 08 */	ble lbl_80362434
/* 80362430 0035F010  7C 7F 1B 78 */	mr r31, r3
lbl_80362434:
/* 80362434 0035F014  7F C3 F3 78 */	mr r3, r30
/* 80362438 0035F018  4B FF FC 6D */	bl HSD_SetupChannel
/* 8036243C 0035F01C  83 DE 00 00 */	lwz r30, 0(r30)
lbl_80362440:
/* 80362440 0035F020  28 1E 00 00 */	cmplwi r30, 0
/* 80362444 0035F024  40 82 FF DC */	bne lbl_80362420
/* 80362448 0035F028  80 6D BF 60 */	lwz r3, lbl_804D7600-_SDA_BASE_(r13)
/* 8036244C 0035F02C  57 E0 06 3E */	clrlwi r0, r31, 0x18
/* 80362450 0035F030  7C 03 00 00 */	cmpw r3, r0
/* 80362454 0035F034  41 82 00 0C */	beq lbl_80362460
/* 80362458 0035F038  54 03 06 3E */	clrlwi r3, r0, 0x18
/* 8036245C 0035F03C  4B FD C1 01 */	bl GXSetNumChans
lbl_80362460:
/* 80362460 0035F040  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80362464 0035F044  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80362468 0035F048  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8036246C 0035F04C  38 21 00 18 */	addi r1, r1, 0x18
/* 80362470 0035F050  7C 08 03 A6 */	mtlr r0
/* 80362474 0035F054  4E 80 00 20 */	blr 

.global func_80362478
func_80362478:
/* 80362478 0035F058  7C 08 02 A6 */	mflr r0
/* 8036247C 0035F05C  90 01 00 04 */	stw r0, 4(r1)
/* 80362480 0035F060  94 21 FF F8 */	stwu r1, -8(r1)
/* 80362484 0035F064  48 00 06 21 */	bl func_80362AA4
/* 80362488 0035F068  80 0D BF 5C */	lwz r0, lbl_804D75FC-_SDA_BASE_(r13)
/* 8036248C 0035F06C  7C 03 00 00 */	cmpw r3, r0
/* 80362490 0035F070  40 81 00 08 */	ble lbl_80362498
/* 80362494 0035F074  90 6D BF 5C */	stw r3, lbl_804D75FC-_SDA_BASE_(r13)
lbl_80362498:
/* 80362498 0035F078  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8036249C 0035F07C  38 21 00 08 */	addi r1, r1, 8
/* 803624A0 0035F080  7C 08 03 A6 */	mtlr r0
/* 803624A4 0035F084  4E 80 00 20 */	blr 

.global func_803624A8
func_803624A8:
/* 803624A8 0035F088  7C 08 02 A6 */	mflr r0
/* 803624AC 0035F08C  90 01 00 04 */	stw r0, 4(r1)
/* 803624B0 0035F090  94 21 FF F8 */	stwu r1, -8(r1)
/* 803624B4 0035F094  80 0D BF 5C */	lwz r0, lbl_804D75FC-_SDA_BASE_(r13)
/* 803624B8 0035F098  54 03 06 3E */	clrlwi r3, r0, 0x18
/* 803624BC 0035F09C  4B FD A6 BD */	bl func_8033CB78
/* 803624C0 0035F0A0  38 00 00 00 */	li r0, 0
/* 803624C4 0035F0A4  90 0D BF 5C */	stw r0, lbl_804D75FC-_SDA_BASE_(r13)
/* 803624C8 0035F0A8  80 01 00 0C */	lwz r0, 0xc(r1)
/* 803624CC 0035F0AC  38 21 00 08 */	addi r1, r1, 8
/* 803624D0 0035F0B0  7C 08 03 A6 */	mtlr r0
/* 803624D4 0035F0B4  4E 80 00 20 */	blr 

.global func_803624D8
func_803624D8:
/* 803624D8 0035F0B8  38 00 00 00 */	li r0, 0
/* 803624DC 0035F0BC  90 0D BF 58 */	stw r0, lbl_804D75F8-_SDA_BASE_(r13)
/* 803624E0 0035F0C0  4E 80 00 20 */	blr 

.global func_803624E4
func_803624E4:
/* 803624E4 0035F0C4  80 6D BF 58 */	lwz r3, lbl_804D75F8-_SDA_BASE_(r13)
/* 803624E8 0035F0C8  4E 80 00 20 */	blr 

.global func_803624EC
func_803624EC:
/* 803624EC 0035F0CC  7C 08 02 A6 */	mflr r0
/* 803624F0 0035F0D0  90 01 00 04 */	stw r0, 4(r1)
/* 803624F4 0035F0D4  94 21 FF F8 */	stwu r1, -8(r1)
/* 803624F8 0035F0D8  80 6D BF 58 */	lwz r3, lbl_804D75F8-_SDA_BASE_(r13)
/* 803624FC 0035F0DC  38 03 00 01 */	addi r0, r3, 1
/* 80362500 0035F0E0  90 0D BF 58 */	stw r0, lbl_804D75F8-_SDA_BASE_(r13)
/* 80362504 0035F0E4  48 00 02 65 */	bl func_80362768
/* 80362508 0035F0E8  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8036250C 0035F0EC  38 21 00 08 */	addi r1, r1, 8
/* 80362510 0035F0F0  7C 08 03 A6 */	mtlr r0
/* 80362514 0035F0F4  4E 80 00 20 */	blr 

.global func_80362518
func_80362518:
/* 80362518 0035F0F8  7C 08 02 A6 */	mflr r0
/* 8036251C 0035F0FC  90 01 00 04 */	stw r0, 4(r1)
/* 80362520 0035F100  94 21 FF F8 */	stwu r1, -8(r1)
/* 80362524 0035F104  80 0D BF 58 */	lwz r0, lbl_804D75F8-_SDA_BASE_(r13)
/* 80362528 0035F108  54 03 06 3E */	clrlwi r3, r0, 0x18
/* 8036252C 0035F10C  4B FD E2 65 */	bl func_80340790
/* 80362530 0035F110  38 00 00 00 */	li r0, 0
/* 80362534 0035F114  90 0D BF 58 */	stw r0, lbl_804D75F8-_SDA_BASE_(r13)
/* 80362538 0035F118  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8036253C 0035F11C  38 21 00 08 */	addi r1, r1, 8
/* 80362540 0035F120  7C 08 03 A6 */	mtlr r0
/* 80362544 0035F124  4E 80 00 20 */	blr 

.global func_80362548
func_80362548:
/* 80362548 0035F128  7C 08 02 A6 */	mflr r0
/* 8036254C 0035F12C  90 01 00 04 */	stw r0, 4(r1)
/* 80362550 0035F130  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80362554 0035F134  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80362558 0035F138  7C 7F 1B 78 */	mr r31, r3
/* 8036255C 0035F13C  80 63 00 08 */	lwz r3, 8(r3)
/* 80362560 0035F140  80 9F 00 0C */	lwz r4, 0xc(r31)
/* 80362564 0035F144  80 BF 00 10 */	lwz r5, 0x10(r31)
/* 80362568 0035F148  80 DF 00 14 */	lwz r6, 0x14(r31)
/* 8036256C 0035F14C  4B FD E0 85 */	bl func_803405F0
/* 80362570 0035F150  80 1F 00 04 */	lwz r0, 4(r31)
/* 80362574 0035F154  28 00 00 00 */	cmplwi r0, 0
/* 80362578 0035F158  40 82 00 24 */	bne lbl_8036259C
/* 8036257C 0035F15C  80 7F 00 08 */	lwz r3, 8(r31)
/* 80362580 0035F160  80 9F 00 18 */	lwz r4, 0x18(r31)
/* 80362584 0035F164  4B FD D8 41 */	bl func_8033FDC4
/* 80362588 0035F168  80 7F 00 08 */	lwz r3, 8(r31)
/* 8036258C 0035F16C  38 80 00 00 */	li r4, 0
/* 80362590 0035F170  38 A0 00 00 */	li r5, 0
/* 80362594 0035F174  4B FD DE 8D */	bl func_80340420
/* 80362598 0035F178  48 00 00 94 */	b lbl_8036262C
lbl_8036259C:
/* 8036259C 0035F17C  80 7F 00 08 */	lwz r3, 8(r31)
/* 803625A0 0035F180  80 9F 00 18 */	lwz r4, 0x18(r31)
/* 803625A4 0035F184  80 BF 00 30 */	lwz r5, 0x30(r31)
/* 803625A8 0035F188  80 DF 00 2C */	lwz r6, 0x2c(r31)
/* 803625AC 0035F18C  88 FF 00 34 */	lbz r7, 0x34(r31)
/* 803625B0 0035F190  81 1F 00 38 */	lwz r8, 0x38(r31)
/* 803625B4 0035F194  4B FD DA B9 */	bl func_8034006C
/* 803625B8 0035F198  80 7F 00 08 */	lwz r3, 8(r31)
/* 803625BC 0035F19C  80 9F 00 1C */	lwz r4, 0x1c(r31)
/* 803625C0 0035F1A0  80 BF 00 20 */	lwz r5, 0x20(r31)
/* 803625C4 0035F1A4  80 DF 00 24 */	lwz r6, 0x24(r31)
/* 803625C8 0035F1A8  80 FF 00 28 */	lwz r7, 0x28(r31)
/* 803625CC 0035F1AC  4B FD D9 9D */	bl func_8033FF68
/* 803625D0 0035F1B0  80 7F 00 08 */	lwz r3, 8(r31)
/* 803625D4 0035F1B4  80 9F 00 3C */	lwz r4, 0x3c(r31)
/* 803625D8 0035F1B8  80 BF 00 54 */	lwz r5, 0x54(r31)
/* 803625DC 0035F1BC  80 DF 00 50 */	lwz r6, 0x50(r31)
/* 803625E0 0035F1C0  88 FF 00 58 */	lbz r7, 0x58(r31)
/* 803625E4 0035F1C4  81 1F 00 5C */	lwz r8, 0x5c(r31)
/* 803625E8 0035F1C8  4B FD DB 45 */	bl func_8034012C
/* 803625EC 0035F1CC  80 7F 00 08 */	lwz r3, 8(r31)
/* 803625F0 0035F1D0  80 9F 00 40 */	lwz r4, 0x40(r31)
/* 803625F4 0035F1D4  80 BF 00 44 */	lwz r5, 0x44(r31)
/* 803625F8 0035F1D8  80 DF 00 48 */	lwz r6, 0x48(r31)
/* 803625FC 0035F1DC  80 FF 00 4C */	lwz r7, 0x4c(r31)
/* 80362600 0035F1E0  4B FD D9 E9 */	bl func_8033FFE8
/* 80362604 0035F1E4  80 7F 00 08 */	lwz r3, 8(r31)
/* 80362608 0035F1E8  80 9F 00 64 */	lwz r4, 0x64(r31)
/* 8036260C 0035F1EC  80 BF 00 68 */	lwz r5, 0x68(r31)
/* 80362610 0035F1F0  4B FD DE 11 */	bl func_80340420
/* 80362614 0035F1F4  80 7F 00 08 */	lwz r3, 8(r31)
/* 80362618 0035F1F8  80 9F 00 6C */	lwz r4, 0x6c(r31)
/* 8036261C 0035F1FC  4B FD DD 2D */	bl func_80340348
/* 80362620 0035F200  80 7F 00 08 */	lwz r3, 8(r31)
/* 80362624 0035F204  80 9F 00 70 */	lwz r4, 0x70(r31)
/* 80362628 0035F208  4B FD DD 8D */	bl func_803403B4
lbl_8036262C:
/* 8036262C 0035F20C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80362630 0035F210  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80362634 0035F214  38 21 00 20 */	addi r1, r1, 0x20
/* 80362638 0035F218  7C 08 03 A6 */	mtlr r0
/* 8036263C 0035F21C  4E 80 00 20 */	blr 

.global func_80362640
func_80362640:
/* 80362640 0035F220  7C 08 02 A6 */	mflr r0
/* 80362644 0035F224  90 01 00 04 */	stw r0, 4(r1)
/* 80362648 0035F228  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8036264C 0035F22C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80362650 0035F230  3B E0 00 00 */	li r31, 0
/* 80362654 0035F234  93 C1 00 10 */	stw r30, 0x10(r1)
/* 80362658 0035F238  3B C3 00 00 */	addi r30, r3, 0
/* 8036265C 0035F23C  48 00 00 24 */	b lbl_80362680
lbl_80362660:
/* 80362660 0035F240  80 7E 00 08 */	lwz r3, 8(r30)
/* 80362664 0035F244  48 00 02 A5 */	bl func_80362908
/* 80362668 0035F248  7C 03 F8 00 */	cmpw r3, r31
/* 8036266C 0035F24C  40 81 00 08 */	ble lbl_80362674
/* 80362670 0035F250  7C 7F 1B 78 */	mr r31, r3
lbl_80362674:
/* 80362674 0035F254  7F C3 F3 78 */	mr r3, r30
/* 80362678 0035F258  4B FF FE D1 */	bl func_80362548
/* 8036267C 0035F25C  83 DE 00 00 */	lwz r30, 0(r30)
lbl_80362680:
/* 80362680 0035F260  28 1E 00 00 */	cmplwi r30, 0
/* 80362684 0035F264  40 82 FF DC */	bne lbl_80362660
/* 80362688 0035F268  93 ED BF 58 */	stw r31, lbl_804D75F8-_SDA_BASE_(r13)
/* 8036268C 0035F26C  80 0D BF 58 */	lwz r0, lbl_804D75F8-_SDA_BASE_(r13)
/* 80362690 0035F270  54 03 06 3E */	clrlwi r3, r0, 0x18
/* 80362694 0035F274  4B FD E0 FD */	bl func_80340790
/* 80362698 0035F278  38 00 00 00 */	li r0, 0
/* 8036269C 0035F27C  90 0D BF 58 */	stw r0, lbl_804D75F8-_SDA_BASE_(r13)
/* 803626A0 0035F280  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 803626A4 0035F284  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 803626A8 0035F288  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 803626AC 0035F28C  38 21 00 18 */	addi r1, r1, 0x18
/* 803626B0 0035F290  7C 08 03 A6 */	mtlr r0
/* 803626B4 0035F294  4E 80 00 20 */	blr 

.global func_803626B8
func_803626B8:
/* 803626B8 0035F298  7C 08 02 A6 */	mflr r0
/* 803626BC 0035F29C  2C 03 00 04 */	cmpwi r3, 4
/* 803626C0 0035F2A0  90 01 00 04 */	stw r0, 4(r1)
/* 803626C4 0035F2A4  94 21 FF F8 */	stwu r1, -8(r1)
/* 803626C8 0035F2A8  41 82 00 64 */	beq lbl_8036272C
/* 803626CC 0035F2AC  40 80 00 28 */	bge lbl_803626F4
/* 803626D0 0035F2B0  2C 03 00 01 */	cmpwi r3, 1
/* 803626D4 0035F2B4  41 82 00 40 */	beq lbl_80362714
/* 803626D8 0035F2B8  40 80 00 10 */	bge lbl_803626E8
/* 803626DC 0035F2BC  2C 03 00 00 */	cmpwi r3, 0
/* 803626E0 0035F2C0  40 80 00 2C */	bge lbl_8036270C
/* 803626E4 0035F2C4  48 00 00 60 */	b lbl_80362744
lbl_803626E8:
/* 803626E8 0035F2C8  2C 03 00 03 */	cmpwi r3, 3
/* 803626EC 0035F2CC  40 80 00 38 */	bge lbl_80362724
/* 803626F0 0035F2D0  48 00 00 2C */	b lbl_8036271C
lbl_803626F4:
/* 803626F4 0035F2D4  2C 03 00 FF */	cmpwi r3, 0xff
/* 803626F8 0035F2D8  41 82 00 44 */	beq lbl_8036273C
/* 803626FC 0035F2DC  40 80 00 48 */	bge lbl_80362744
/* 80362700 0035F2E0  2C 03 00 06 */	cmpwi r3, 6
/* 80362704 0035F2E4  40 80 00 40 */	bge lbl_80362744
/* 80362708 0035F2E8  48 00 00 2C */	b lbl_80362734
lbl_8036270C:
/* 8036270C 0035F2EC  38 60 00 01 */	li r3, 1
/* 80362710 0035F2F0  48 00 00 48 */	b lbl_80362758
lbl_80362714:
/* 80362714 0035F2F4  38 60 00 02 */	li r3, 2
/* 80362718 0035F2F8  48 00 00 40 */	b lbl_80362758
lbl_8036271C:
/* 8036271C 0035F2FC  38 60 00 01 */	li r3, 1
/* 80362720 0035F300  48 00 00 38 */	b lbl_80362758
lbl_80362724:
/* 80362724 0035F304  38 60 00 02 */	li r3, 2
/* 80362728 0035F308  48 00 00 30 */	b lbl_80362758
lbl_8036272C:
/* 8036272C 0035F30C  38 60 00 01 */	li r3, 1
/* 80362730 0035F310  48 00 00 28 */	b lbl_80362758
lbl_80362734:
/* 80362734 0035F314  38 60 00 02 */	li r3, 2
/* 80362738 0035F318  48 00 00 20 */	b lbl_80362758
lbl_8036273C:
/* 8036273C 0035F31C  38 60 00 00 */	li r3, 0
/* 80362740 0035F320  48 00 00 18 */	b lbl_80362758
lbl_80362744:
/* 80362744 0035F324  38 6D A6 30 */	addi r3, r13, lbl_804D5CD0-_SDA_BASE_
/* 80362748 0035F328  38 80 02 90 */	li r4, 0x290
/* 8036274C 0035F32C  38 AD A6 38 */	addi r5, r13, lbl_804D5CD8-_SDA_BASE_
/* 80362750 0035F330  48 02 5A D1 */	bl func_80388220
/* 80362754 0035F334  38 60 00 00 */	li r3, 0
lbl_80362758:
/* 80362758 0035F338  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8036275C 0035F33C  38 21 00 08 */	addi r1, r1, 8
/* 80362760 0035F340  7C 08 03 A6 */	mtlr r0
/* 80362764 0035F344  4E 80 00 20 */	blr 

.global func_80362768
func_80362768:
/* 80362768 0035F348  7C 08 02 A6 */	mflr r0
/* 8036276C 0035F34C  28 03 00 0F */	cmplwi r3, 0xf
/* 80362770 0035F350  90 01 00 04 */	stw r0, 4(r1)
/* 80362774 0035F354  94 21 FF F8 */	stwu r1, -8(r1)
/* 80362778 0035F358  41 81 00 9C */	bgt lbl_80362814
/* 8036277C 0035F35C  3C 80 80 40 */	lis r4, jtbl_80405C88@ha
/* 80362780 0035F360  38 84 5C 88 */	addi r4, r4, jtbl_80405C88@l
/* 80362784 0035F364  54 60 10 3A */	slwi r0, r3, 2
/* 80362788 0035F368  7C 04 00 2E */	lwzx r0, r4, r0
/* 8036278C 0035F36C  7C 09 03 A6 */	mtctr r0
/* 80362790 0035F370  4E 80 04 20 */	bctr 
/* 80362794 0035F374  38 60 00 00 */	li r3, 0
/* 80362798 0035F378  48 00 00 90 */	b lbl_80362828
/* 8036279C 0035F37C  38 60 00 01 */	li r3, 1
/* 803627A0 0035F380  48 00 00 88 */	b lbl_80362828
/* 803627A4 0035F384  38 60 00 02 */	li r3, 2
/* 803627A8 0035F388  48 00 00 80 */	b lbl_80362828
/* 803627AC 0035F38C  38 60 00 03 */	li r3, 3
/* 803627B0 0035F390  48 00 00 78 */	b lbl_80362828
/* 803627B4 0035F394  38 60 00 04 */	li r3, 4
/* 803627B8 0035F398  48 00 00 70 */	b lbl_80362828
/* 803627BC 0035F39C  38 60 00 05 */	li r3, 5
/* 803627C0 0035F3A0  48 00 00 68 */	b lbl_80362828
/* 803627C4 0035F3A4  38 60 00 06 */	li r3, 6
/* 803627C8 0035F3A8  48 00 00 60 */	b lbl_80362828
/* 803627CC 0035F3AC  38 60 00 07 */	li r3, 7
/* 803627D0 0035F3B0  48 00 00 58 */	b lbl_80362828
/* 803627D4 0035F3B4  38 60 00 08 */	li r3, 8
/* 803627D8 0035F3B8  48 00 00 50 */	b lbl_80362828
/* 803627DC 0035F3BC  38 60 00 09 */	li r3, 9
/* 803627E0 0035F3C0  48 00 00 48 */	b lbl_80362828
/* 803627E4 0035F3C4  38 60 00 0A */	li r3, 0xa
/* 803627E8 0035F3C8  48 00 00 40 */	b lbl_80362828
/* 803627EC 0035F3CC  38 60 00 0B */	li r3, 0xb
/* 803627F0 0035F3D0  48 00 00 38 */	b lbl_80362828
/* 803627F4 0035F3D4  38 60 00 0C */	li r3, 0xc
/* 803627F8 0035F3D8  48 00 00 30 */	b lbl_80362828
/* 803627FC 0035F3DC  38 60 00 0D */	li r3, 0xd
/* 80362800 0035F3E0  48 00 00 28 */	b lbl_80362828
/* 80362804 0035F3E4  38 60 00 0E */	li r3, 0xe
/* 80362808 0035F3E8  48 00 00 20 */	b lbl_80362828
/* 8036280C 0035F3EC  38 60 00 0F */	li r3, 0xf
/* 80362810 0035F3F0  48 00 00 18 */	b lbl_80362828
lbl_80362814:
/* 80362814 0035F3F4  38 6D A6 30 */	addi r3, r13, lbl_804D5CD0-_SDA_BASE_
/* 80362818 0035F3F8  38 80 02 C5 */	li r4, 0x2c5
/* 8036281C 0035F3FC  38 AD A6 38 */	addi r5, r13, lbl_804D5CD8-_SDA_BASE_
/* 80362820 0035F400  48 02 5A 01 */	bl func_80388220
/* 80362824 0035F404  38 60 00 0F */	li r3, 0xf
lbl_80362828:
/* 80362828 0035F408  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8036282C 0035F40C  38 21 00 08 */	addi r1, r1, 8
/* 80362830 0035F410  7C 08 03 A6 */	mtlr r0
/* 80362834 0035F414  4E 80 00 20 */	blr 
/* 80362838 0035F418  7C 08 02 A6 */	mflr r0
/* 8036283C 0035F41C  28 03 00 0F */	cmplwi r3, 0xf
/* 80362840 0035F420  90 01 00 04 */	stw r0, 4(r1)
/* 80362844 0035F424  94 21 FF F8 */	stwu r1, -8(r1)
/* 80362848 0035F428  41 81 00 9C */	bgt lbl_803628E4
/* 8036284C 0035F42C  3C 80 80 40 */	lis r4, jtbl_80405CC8@ha
/* 80362850 0035F430  38 84 5C C8 */	addi r4, r4, jtbl_80405CC8@l
/* 80362854 0035F434  54 60 10 3A */	slwi r0, r3, 2
/* 80362858 0035F438  7C 04 00 2E */	lwzx r0, r4, r0
/* 8036285C 0035F43C  7C 09 03 A6 */	mtctr r0
/* 80362860 0035F440  4E 80 04 20 */	bctr 
/* 80362864 0035F444  38 60 00 00 */	li r3, 0
/* 80362868 0035F448  48 00 00 90 */	b lbl_803628F8
/* 8036286C 0035F44C  38 60 00 01 */	li r3, 1
/* 80362870 0035F450  48 00 00 88 */	b lbl_803628F8
/* 80362874 0035F454  38 60 00 02 */	li r3, 2
/* 80362878 0035F458  48 00 00 80 */	b lbl_803628F8
/* 8036287C 0035F45C  38 60 00 03 */	li r3, 3
/* 80362880 0035F460  48 00 00 78 */	b lbl_803628F8
/* 80362884 0035F464  38 60 00 04 */	li r3, 4
/* 80362888 0035F468  48 00 00 70 */	b lbl_803628F8
/* 8036288C 0035F46C  38 60 00 05 */	li r3, 5
/* 80362890 0035F470  48 00 00 68 */	b lbl_803628F8
/* 80362894 0035F474  38 60 00 06 */	li r3, 6
/* 80362898 0035F478  48 00 00 60 */	b lbl_803628F8
/* 8036289C 0035F47C  38 60 00 07 */	li r3, 7
/* 803628A0 0035F480  48 00 00 58 */	b lbl_803628F8
/* 803628A4 0035F484  38 60 00 08 */	li r3, 8
/* 803628A8 0035F488  48 00 00 50 */	b lbl_803628F8
/* 803628AC 0035F48C  38 60 00 09 */	li r3, 9
/* 803628B0 0035F490  48 00 00 48 */	b lbl_803628F8
/* 803628B4 0035F494  38 60 00 0A */	li r3, 0xa
/* 803628B8 0035F498  48 00 00 40 */	b lbl_803628F8
/* 803628BC 0035F49C  38 60 00 0B */	li r3, 0xb
/* 803628C0 0035F4A0  48 00 00 38 */	b lbl_803628F8
/* 803628C4 0035F4A4  38 60 00 0C */	li r3, 0xc
/* 803628C8 0035F4A8  48 00 00 30 */	b lbl_803628F8
/* 803628CC 0035F4AC  38 60 00 0D */	li r3, 0xd
/* 803628D0 0035F4B0  48 00 00 28 */	b lbl_803628F8
/* 803628D4 0035F4B4  38 60 00 0E */	li r3, 0xe
/* 803628D8 0035F4B8  48 00 00 20 */	b lbl_803628F8
/* 803628DC 0035F4BC  38 60 00 0F */	li r3, 0xf
/* 803628E0 0035F4C0  48 00 00 18 */	b lbl_803628F8
lbl_803628E4:
/* 803628E4 0035F4C4  38 6D A6 30 */	addi r3, r13, lbl_804D5CD0-_SDA_BASE_
/* 803628E8 0035F4C8  38 80 02 FA */	li r4, 0x2fa
/* 803628EC 0035F4CC  38 AD A6 38 */	addi r5, r13, lbl_804D5CD8-_SDA_BASE_
/* 803628F0 0035F4D0  48 02 59 31 */	bl func_80388220
/* 803628F4 0035F4D4  38 60 00 00 */	li r3, 0
lbl_803628F8:
/* 803628F8 0035F4D8  80 01 00 0C */	lwz r0, 0xc(r1)
/* 803628FC 0035F4DC  38 21 00 08 */	addi r1, r1, 8
/* 80362900 0035F4E0  7C 08 03 A6 */	mtlr r0
/* 80362904 0035F4E4  4E 80 00 20 */	blr 

.global func_80362908
func_80362908:
/* 80362908 0035F4E8  7C 08 02 A6 */	mflr r0
/* 8036290C 0035F4EC  28 03 00 0F */	cmplwi r3, 0xf
/* 80362910 0035F4F0  90 01 00 04 */	stw r0, 4(r1)
/* 80362914 0035F4F4  94 21 FF F8 */	stwu r1, -8(r1)
/* 80362918 0035F4F8  41 81 00 9C */	bgt lbl_803629B4
/* 8036291C 0035F4FC  3C 80 80 40 */	lis r4, jtbl_80405D08@ha
/* 80362920 0035F500  38 84 5D 08 */	addi r4, r4, jtbl_80405D08@l
/* 80362924 0035F504  54 60 10 3A */	slwi r0, r3, 2
/* 80362928 0035F508  7C 04 00 2E */	lwzx r0, r4, r0
/* 8036292C 0035F50C  7C 09 03 A6 */	mtctr r0
/* 80362930 0035F510  4E 80 04 20 */	bctr 
/* 80362934 0035F514  38 60 00 01 */	li r3, 1
/* 80362938 0035F518  48 00 00 90 */	b lbl_803629C8
/* 8036293C 0035F51C  38 60 00 02 */	li r3, 2
/* 80362940 0035F520  48 00 00 88 */	b lbl_803629C8
/* 80362944 0035F524  38 60 00 03 */	li r3, 3
/* 80362948 0035F528  48 00 00 80 */	b lbl_803629C8
/* 8036294C 0035F52C  38 60 00 04 */	li r3, 4
/* 80362950 0035F530  48 00 00 78 */	b lbl_803629C8
/* 80362954 0035F534  38 60 00 05 */	li r3, 5
/* 80362958 0035F538  48 00 00 70 */	b lbl_803629C8
/* 8036295C 0035F53C  38 60 00 06 */	li r3, 6
/* 80362960 0035F540  48 00 00 68 */	b lbl_803629C8
/* 80362964 0035F544  38 60 00 07 */	li r3, 7
/* 80362968 0035F548  48 00 00 60 */	b lbl_803629C8
/* 8036296C 0035F54C  38 60 00 08 */	li r3, 8
/* 80362970 0035F550  48 00 00 58 */	b lbl_803629C8
/* 80362974 0035F554  38 60 00 09 */	li r3, 9
/* 80362978 0035F558  48 00 00 50 */	b lbl_803629C8
/* 8036297C 0035F55C  38 60 00 0A */	li r3, 0xa
/* 80362980 0035F560  48 00 00 48 */	b lbl_803629C8
/* 80362984 0035F564  38 60 00 0B */	li r3, 0xb
/* 80362988 0035F568  48 00 00 40 */	b lbl_803629C8
/* 8036298C 0035F56C  38 60 00 0C */	li r3, 0xc
/* 80362990 0035F570  48 00 00 38 */	b lbl_803629C8
/* 80362994 0035F574  38 60 00 0D */	li r3, 0xd
/* 80362998 0035F578  48 00 00 30 */	b lbl_803629C8
/* 8036299C 0035F57C  38 60 00 0E */	li r3, 0xe
/* 803629A0 0035F580  48 00 00 28 */	b lbl_803629C8
/* 803629A4 0035F584  38 60 00 0F */	li r3, 0xf
/* 803629A8 0035F588  48 00 00 20 */	b lbl_803629C8
/* 803629AC 0035F58C  38 60 00 10 */	li r3, 0x10
/* 803629B0 0035F590  48 00 00 18 */	b lbl_803629C8
lbl_803629B4:
/* 803629B4 0035F594  38 6D A6 30 */	addi r3, r13, lbl_804D5CD0-_SDA_BASE_
/* 803629B8 0035F598  38 80 03 19 */	li r4, 0x319
/* 803629BC 0035F59C  38 AD A6 38 */	addi r5, r13, lbl_804D5CD8-_SDA_BASE_
/* 803629C0 0035F5A0  48 02 58 61 */	bl func_80388220
/* 803629C4 0035F5A4  38 60 00 00 */	li r3, 0
lbl_803629C8:
/* 803629C8 0035F5A8  80 01 00 0C */	lwz r0, 0xc(r1)
/* 803629CC 0035F5AC  38 21 00 08 */	addi r1, r1, 8
/* 803629D0 0035F5B0  7C 08 03 A6 */	mtlr r0
/* 803629D4 0035F5B4  4E 80 00 20 */	blr 

.global func_803629D8
func_803629D8:
/* 803629D8 0035F5B8  7C 08 02 A6 */	mflr r0
/* 803629DC 0035F5BC  3C 60 80 40 */	lis r3, lbl_80405B98@ha
/* 803629E0 0035F5C0  90 01 00 04 */	stw r0, 4(r1)
/* 803629E4 0035F5C4  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 803629E8 0035F5C8  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 803629EC 0035F5CC  3B E1 00 08 */	addi r31, r1, 8
/* 803629F0 0035F5D0  93 C1 00 18 */	stw r30, 0x18(r1)
/* 803629F4 0035F5D4  3B C3 5B 98 */	addi r30, r3, lbl_80405B98@l
/* 803629F8 0035F5D8  93 A1 00 14 */	stw r29, 0x14(r1)
/* 803629FC 0035F5DC  3B A0 00 00 */	li r29, 0
lbl_80362A00:
/* 80362A00 0035F5E0  80 1E 00 08 */	lwz r0, 8(r30)
/* 80362A04 0035F5E4  2C 00 00 00 */	cmpwi r0, 0
/* 80362A08 0035F5E8  41 82 00 70 */	beq lbl_80362A78
/* 80362A0C 0035F5EC  2C 1D 00 02 */	cmpwi r29, 2
/* 80362A10 0035F5F0  41 82 00 34 */	beq lbl_80362A44
/* 80362A14 0035F5F4  40 80 00 14 */	bge lbl_80362A28
/* 80362A18 0035F5F8  2C 1D 00 00 */	cmpwi r29, 0
/* 80362A1C 0035F5FC  41 82 00 18 */	beq lbl_80362A34
/* 80362A20 0035F600  40 80 00 1C */	bge lbl_80362A3C
/* 80362A24 0035F604  48 00 00 30 */	b lbl_80362A54
lbl_80362A28:
/* 80362A28 0035F608  2C 1D 00 04 */	cmpwi r29, 4
/* 80362A2C 0035F60C  40 80 00 28 */	bge lbl_80362A54
/* 80362A30 0035F610  48 00 00 1C */	b lbl_80362A4C
lbl_80362A34:
/* 80362A34 0035F614  38 60 00 01 */	li r3, 1
/* 80362A38 0035F618  48 00 00 20 */	b lbl_80362A58
lbl_80362A3C:
/* 80362A3C 0035F61C  38 60 00 02 */	li r3, 2
/* 80362A40 0035F620  48 00 00 18 */	b lbl_80362A58
lbl_80362A44:
/* 80362A44 0035F624  38 60 00 03 */	li r3, 3
/* 80362A48 0035F628  48 00 00 10 */	b lbl_80362A58
lbl_80362A4C:
/* 80362A4C 0035F62C  38 60 00 00 */	li r3, 0
/* 80362A50 0035F630  48 00 00 08 */	b lbl_80362A58
lbl_80362A54:
/* 80362A54 0035F634  38 60 00 01 */	li r3, 1
lbl_80362A58:
/* 80362A58 0035F638  80 BE 00 00 */	lwz r5, 0(r30)
/* 80362A5C 0035F63C  7F E4 FB 78 */	mr r4, r31
/* 80362A60 0035F640  80 1E 00 04 */	lwz r0, 4(r30)
/* 80362A64 0035F644  90 A1 00 08 */	stw r5, 8(r1)
/* 80362A68 0035F648  90 01 00 0C */	stw r0, 0xc(r1)
/* 80362A6C 0035F64C  4B FD D7 F5 */	bl func_80340260
/* 80362A70 0035F650  38 00 00 00 */	li r0, 0
/* 80362A74 0035F654  90 1E 00 08 */	stw r0, 8(r30)
lbl_80362A78:
/* 80362A78 0035F658  3B BD 00 01 */	addi r29, r29, 1
/* 80362A7C 0035F65C  28 1D 00 04 */	cmplwi r29, 4
/* 80362A80 0035F660  3B DE 00 0C */	addi r30, r30, 0xc
/* 80362A84 0035F664  41 80 FF 7C */	blt lbl_80362A00
/* 80362A88 0035F668  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80362A8C 0035F66C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80362A90 0035F670  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80362A94 0035F674  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 80362A98 0035F678  38 21 00 20 */	addi r1, r1, 0x20
/* 80362A9C 0035F67C  7C 08 03 A6 */	mtlr r0
/* 80362AA0 0035F680  4E 80 00 20 */	blr 

.global func_80362AA4
func_80362AA4:
/* 80362AA4 0035F684  7C 08 02 A6 */	mflr r0
/* 80362AA8 0035F688  2C 03 00 05 */	cmpwi r3, 5
/* 80362AAC 0035F68C  90 01 00 04 */	stw r0, 4(r1)
/* 80362AB0 0035F690  94 21 FF F8 */	stwu r1, -8(r1)
/* 80362AB4 0035F694  41 82 00 74 */	beq lbl_80362B28
/* 80362AB8 0035F698  40 80 00 2C */	bge lbl_80362AE4
/* 80362ABC 0035F69C  2C 03 00 02 */	cmpwi r3, 2
/* 80362AC0 0035F6A0  41 82 00 50 */	beq lbl_80362B10
/* 80362AC4 0035F6A4  40 80 00 14 */	bge lbl_80362AD8
/* 80362AC8 0035F6A8  2C 03 00 00 */	cmpwi r3, 0
/* 80362ACC 0035F6AC  41 82 00 34 */	beq lbl_80362B00
/* 80362AD0 0035F6B0  40 80 00 38 */	bge lbl_80362B08
/* 80362AD4 0035F6B4  48 00 00 74 */	b lbl_80362B48
lbl_80362AD8:
/* 80362AD8 0035F6B8  2C 03 00 04 */	cmpwi r3, 4
/* 80362ADC 0035F6BC  40 80 00 44 */	bge lbl_80362B20
/* 80362AE0 0035F6C0  48 00 00 38 */	b lbl_80362B18
lbl_80362AE4:
/* 80362AE4 0035F6C4  2C 03 00 FF */	cmpwi r3, 0xff
/* 80362AE8 0035F6C8  41 82 00 58 */	beq lbl_80362B40
/* 80362AEC 0035F6CC  40 80 00 5C */	bge lbl_80362B48
/* 80362AF0 0035F6D0  2C 03 00 07 */	cmpwi r3, 7
/* 80362AF4 0035F6D4  41 82 00 44 */	beq lbl_80362B38
/* 80362AF8 0035F6D8  40 80 00 50 */	bge lbl_80362B48
/* 80362AFC 0035F6DC  48 00 00 34 */	b lbl_80362B30
lbl_80362B00:
/* 80362B00 0035F6E0  38 60 00 01 */	li r3, 1
/* 80362B04 0035F6E4  48 00 00 58 */	b lbl_80362B5C
lbl_80362B08:
/* 80362B08 0035F6E8  38 60 00 02 */	li r3, 2
/* 80362B0C 0035F6EC  48 00 00 50 */	b lbl_80362B5C
lbl_80362B10:
/* 80362B10 0035F6F0  38 60 00 03 */	li r3, 3
/* 80362B14 0035F6F4  48 00 00 48 */	b lbl_80362B5C
lbl_80362B18:
/* 80362B18 0035F6F8  38 60 00 04 */	li r3, 4
/* 80362B1C 0035F6FC  48 00 00 40 */	b lbl_80362B5C
lbl_80362B20:
/* 80362B20 0035F700  38 60 00 05 */	li r3, 5
/* 80362B24 0035F704  48 00 00 38 */	b lbl_80362B5C
lbl_80362B28:
/* 80362B28 0035F708  38 60 00 06 */	li r3, 6
/* 80362B2C 0035F70C  48 00 00 30 */	b lbl_80362B5C
lbl_80362B30:
/* 80362B30 0035F710  38 60 00 07 */	li r3, 7
/* 80362B34 0035F714  48 00 00 28 */	b lbl_80362B5C
lbl_80362B38:
/* 80362B38 0035F718  38 60 00 08 */	li r3, 8
/* 80362B3C 0035F71C  48 00 00 20 */	b lbl_80362B5C
lbl_80362B40:
/* 80362B40 0035F720  38 60 00 00 */	li r3, 0
/* 80362B44 0035F724  48 00 00 18 */	b lbl_80362B5C
lbl_80362B48:
/* 80362B48 0035F728  38 6D A6 30 */	addi r3, r13, lbl_804D5CD0-_SDA_BASE_
/* 80362B4C 0035F72C  38 80 03 F2 */	li r4, 0x3f2
/* 80362B50 0035F730  38 AD A6 38 */	addi r5, r13, lbl_804D5CD8-_SDA_BASE_
/* 80362B54 0035F734  48 02 56 CD */	bl func_80388220
/* 80362B58 0035F738  38 60 00 00 */	li r3, 0
lbl_80362B5C:
/* 80362B5C 0035F73C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80362B60 0035F740  38 21 00 08 */	addi r1, r1, 8
/* 80362B64 0035F744  7C 08 03 A6 */	mtlr r0
/* 80362B68 0035F748  4E 80 00 20 */	blr 

.global func_80362B6C
func_80362B6C:
/* 80362B6C 0035F74C  28 03 00 00 */	cmplwi r3, 0
/* 80362B70 0035F750  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80362B74 0035F754  41 82 01 24 */	beq lbl_80362C98
/* 80362B78 0035F758  38 04 FF FB */	addi r0, r4, -5
/* 80362B7C 0035F75C  28 00 00 07 */	cmplwi r0, 7
/* 80362B80 0035F760  41 81 01 18 */	bgt lbl_80362C98
/* 80362B84 0035F764  3C 80 80 40 */	lis r4, jtbl_80405D48@ha
/* 80362B88 0035F768  38 84 5D 48 */	addi r4, r4, jtbl_80405D48@l
/* 80362B8C 0035F76C  54 00 10 3A */	slwi r0, r0, 2
/* 80362B90 0035F770  7C 04 00 2E */	lwzx r0, r4, r0
/* 80362B94 0035F774  7C 09 03 A6 */	mtctr r0
/* 80362B98 0035F778  4E 80 04 20 */	bctr 
/* 80362B9C 0035F77C  C8 22 EA 40 */	lfd f1, lbl_804DE420-_SDA2_BASE_(r2)
/* 80362BA0 0035F780  C0 05 00 00 */	lfs f0, 0(r5)
/* 80362BA4 0035F784  FC 01 00 32 */	fmul f0, f1, f0
/* 80362BA8 0035F788  FC 00 00 1E */	fctiwz f0, f0
/* 80362BAC 0035F78C  D8 01 00 18 */	stfd f0, 0x18(r1)
/* 80362BB0 0035F790  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80362BB4 0035F794  98 03 00 10 */	stb r0, 0x10(r3)
/* 80362BB8 0035F798  48 00 00 E0 */	b lbl_80362C98
/* 80362BBC 0035F79C  C8 22 EA 40 */	lfd f1, lbl_804DE420-_SDA2_BASE_(r2)
/* 80362BC0 0035F7A0  C0 05 00 00 */	lfs f0, 0(r5)
/* 80362BC4 0035F7A4  FC 01 00 32 */	fmul f0, f1, f0
/* 80362BC8 0035F7A8  FC 00 00 1E */	fctiwz f0, f0
/* 80362BCC 0035F7AC  D8 01 00 18 */	stfd f0, 0x18(r1)
/* 80362BD0 0035F7B0  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80362BD4 0035F7B4  98 03 00 11 */	stb r0, 0x11(r3)
/* 80362BD8 0035F7B8  48 00 00 C0 */	b lbl_80362C98
/* 80362BDC 0035F7BC  C8 22 EA 40 */	lfd f1, lbl_804DE420-_SDA2_BASE_(r2)
/* 80362BE0 0035F7C0  C0 05 00 00 */	lfs f0, 0(r5)
/* 80362BE4 0035F7C4  FC 01 00 32 */	fmul f0, f1, f0
/* 80362BE8 0035F7C8  FC 00 00 1E */	fctiwz f0, f0
/* 80362BEC 0035F7CC  D8 01 00 18 */	stfd f0, 0x18(r1)
/* 80362BF0 0035F7D0  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80362BF4 0035F7D4  98 03 00 12 */	stb r0, 0x12(r3)
/* 80362BF8 0035F7D8  48 00 00 A0 */	b lbl_80362C98
/* 80362BFC 0035F7DC  C8 22 EA 40 */	lfd f1, lbl_804DE420-_SDA2_BASE_(r2)
/* 80362C00 0035F7E0  C0 05 00 00 */	lfs f0, 0(r5)
/* 80362C04 0035F7E4  FC 01 00 32 */	fmul f0, f1, f0
/* 80362C08 0035F7E8  FC 00 00 1E */	fctiwz f0, f0
/* 80362C0C 0035F7EC  D8 01 00 18 */	stfd f0, 0x18(r1)
/* 80362C10 0035F7F0  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80362C14 0035F7F4  98 03 00 13 */	stb r0, 0x13(r3)
/* 80362C18 0035F7F8  48 00 00 80 */	b lbl_80362C98
/* 80362C1C 0035F7FC  C8 22 EA 40 */	lfd f1, lbl_804DE420-_SDA2_BASE_(r2)
/* 80362C20 0035F800  C0 05 00 00 */	lfs f0, 0(r5)
/* 80362C24 0035F804  FC 01 00 32 */	fmul f0, f1, f0
/* 80362C28 0035F808  FC 00 00 1E */	fctiwz f0, f0
/* 80362C2C 0035F80C  D8 01 00 18 */	stfd f0, 0x18(r1)
/* 80362C30 0035F810  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80362C34 0035F814  98 03 00 0C */	stb r0, 0xc(r3)
/* 80362C38 0035F818  48 00 00 60 */	b lbl_80362C98
/* 80362C3C 0035F81C  C8 22 EA 40 */	lfd f1, lbl_804DE420-_SDA2_BASE_(r2)
/* 80362C40 0035F820  C0 05 00 00 */	lfs f0, 0(r5)
/* 80362C44 0035F824  FC 01 00 32 */	fmul f0, f1, f0
/* 80362C48 0035F828  FC 00 00 1E */	fctiwz f0, f0
/* 80362C4C 0035F82C  D8 01 00 18 */	stfd f0, 0x18(r1)
/* 80362C50 0035F830  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80362C54 0035F834  98 03 00 0D */	stb r0, 0xd(r3)
/* 80362C58 0035F838  48 00 00 40 */	b lbl_80362C98
/* 80362C5C 0035F83C  C8 22 EA 40 */	lfd f1, lbl_804DE420-_SDA2_BASE_(r2)
/* 80362C60 0035F840  C0 05 00 00 */	lfs f0, 0(r5)
/* 80362C64 0035F844  FC 01 00 32 */	fmul f0, f1, f0
/* 80362C68 0035F848  FC 00 00 1E */	fctiwz f0, f0
/* 80362C6C 0035F84C  D8 01 00 18 */	stfd f0, 0x18(r1)
/* 80362C70 0035F850  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80362C74 0035F854  98 03 00 0E */	stb r0, 0xe(r3)
/* 80362C78 0035F858  48 00 00 20 */	b lbl_80362C98
/* 80362C7C 0035F85C  C8 22 EA 40 */	lfd f1, lbl_804DE420-_SDA2_BASE_(r2)
/* 80362C80 0035F860  C0 05 00 00 */	lfs f0, 0(r5)
/* 80362C84 0035F864  FC 01 00 32 */	fmul f0, f1, f0
/* 80362C88 0035F868  FC 00 00 1E */	fctiwz f0, f0
/* 80362C8C 0035F86C  D8 01 00 18 */	stfd f0, 0x18(r1)
/* 80362C90 0035F870  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80362C94 0035F874  98 03 00 0F */	stb r0, 0xf(r3)
lbl_80362C98:
/* 80362C98 0035F878  38 21 00 20 */	addi r1, r1, 0x20
/* 80362C9C 0035F87C  4E 80 00 20 */	blr 
/* 80362CA0 0035F880  7C 08 02 A6 */	mflr r0
/* 80362CA4 0035F884  3C 60 80 40 */	lis r3, lbl_80405BC8@ha
/* 80362CA8 0035F888  90 01 00 04 */	stw r0, 4(r1)
/* 80362CAC 0035F88C  3C 80 80 40 */	lis r4, lbl_80405D68@ha
/* 80362CB0 0035F890  38 63 5B C8 */	addi r3, r3, lbl_80405BC8@l
/* 80362CB4 0035F894  94 21 FF F8 */	stwu r1, -8(r1)
/* 80362CB8 0035F898  38 84 5D 68 */	addi r4, r4, lbl_80405D68@l
/* 80362CBC 0035F89C  38 A0 00 C0 */	li r5, 0xc0
/* 80362CC0 0035F8A0  4B CA 05 35 */	bl func_800031F4
/* 80362CC4 0035F8A4  38 A0 00 01 */	li r5, 1
/* 80362CC8 0035F8A8  90 AD BF 64 */	stw r5, lbl_804D7604-_SDA_BASE_(r13)
/* 80362CCC 0035F8AC  38 8D BF 64 */	addi r4, r13, lbl_804D7604-_SDA_BASE_
/* 80362CD0 0035F8B0  38 6D BF 6C */	addi r3, r13, lbl_804D760C-_SDA_BASE_
/* 80362CD4 0035F8B4  90 A4 00 04 */	stw r5, 4(r4)
/* 80362CD8 0035F8B8  38 00 FF FF */	li r0, -1
/* 80362CDC 0035F8BC  90 AD BF 6C */	stw r5, lbl_804D760C-_SDA_BASE_(r13)
/* 80362CE0 0035F8C0  90 A3 00 04 */	stw r5, 4(r3)
/* 80362CE4 0035F8C4  90 0D BF 60 */	stw r0, lbl_804D7600-_SDA_BASE_(r13)
/* 80362CE8 0035F8C8  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80362CEC 0035F8CC  38 21 00 08 */	addi r1, r1, 8
/* 80362CF0 0035F8D0  7C 08 03 A6 */	mtlr r0
/* 80362CF4 0035F8D4  4E 80 00 20 */	blr 
/* 80362CF8 0035F8D8  38 00 00 00 */	li r0, 0
/* 80362CFC 0035F8DC  90 0D BF 58 */	stw r0, lbl_804D75F8-_SDA_BASE_(r13)
/* 80362D00 0035F8E0  4E 80 00 20 */	blr 
/* 80362D04 0035F8E4  3C 60 80 40 */	lis r3, lbl_80405B98@ha
/* 80362D08 0035F8E8  38 63 5B 98 */	addi r3, r3, lbl_80405B98@l
/* 80362D0C 0035F8EC  38 00 00 00 */	li r0, 0
/* 80362D10 0035F8F0  90 03 00 08 */	stw r0, 8(r3)
/* 80362D14 0035F8F4  90 03 00 14 */	stw r0, 0x14(r3)
/* 80362D18 0035F8F8  90 03 00 20 */	stw r0, 0x20(r3)
/* 80362D1C 0035F8FC  90 03 00 2C */	stw r0, 0x2c(r3)
/* 80362D20 0035F900  4E 80 00 20 */	blr 
/* 80362D24 0035F904  38 00 00 00 */	li r0, 0
/* 80362D28 0035F908  90 0D BF 5C */	stw r0, lbl_804D75FC-_SDA_BASE_(r13)
/* 80362D2C 0035F90C  4E 80 00 20 */	blr 
