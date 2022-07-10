.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

.global lbl_8014E4F0
lbl_8014E4F0:
/* 8014E4F0 0014B0D0  7C 08 02 A6 */	mflr r0
/* 8014E4F4 0014B0D4  90 01 00 04 */	stw r0, 4(r1)
/* 8014E4F8 0014B0D8  94 21 FF 98 */	stwu r1, -0x68(r1)
/* 8014E4FC 0014B0DC  93 E1 00 64 */	stw r31, 0x64(r1)
/* 8014E500 0014B0E0  93 C1 00 60 */	stw r30, 0x60(r1)
/* 8014E504 0014B0E4  7C 7E 1B 78 */	mr r30, r3
/* 8014E508 0014B0E8  93 A1 00 5C */	stw r29, 0x5c(r1)
/* 8014E50C 0014B0EC  93 81 00 58 */	stw r28, 0x58(r1)
/* 8014E510 0014B0F0  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8014E514 0014B0F4  80 1F 22 00 */	lwz r0, 0x2200(r31)
/* 8014E518 0014B0F8  80 BF 02 D4 */	lwz r5, 0x2d4(r31)
/* 8014E51C 0014B0FC  28 00 00 00 */	cmplwi r0, 0
/* 8014E520 0014B100  41 82 01 04 */	beq lbl_8014E624
/* 8014E524 0014B104  3B 80 00 00 */	li r28, 0
/* 8014E528 0014B108  93 9F 22 00 */	stw r28, 0x2200(r31)
/* 8014E52C 0014B10C  3C 00 43 30 */	lis r0, 0x4330
/* 8014E530 0014B110  80 9F 23 44 */	lwz r4, 0x2344(r31)
/* 8014E534 0014B114  C8 42 A4 68 */	lfd f2, lbl_804D9E48@sda21(r2)
/* 8014E538 0014B118  6C 83 80 00 */	xoris r3, r4, 0x8000
/* 8014E53C 0014B11C  C0 05 00 1C */	lfs f0, 0x1c(r5)
/* 8014E540 0014B120  90 61 00 54 */	stw r3, 0x54(r1)
/* 8014E544 0014B124  90 01 00 50 */	stw r0, 0x50(r1)
/* 8014E548 0014B128  C8 21 00 50 */	lfd f1, 0x50(r1)
/* 8014E54C 0014B12C  EC 21 10 28 */	fsubs f1, f1, f2
/* 8014E550 0014B130  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8014E554 0014B134  40 80 00 C8 */	bge lbl_8014E61C
/* 8014E558 0014B138  38 04 00 01 */	addi r0, r4, 1
/* 8014E55C 0014B13C  90 1F 23 44 */	stw r0, 0x2344(r31)
/* 8014E560 0014B140  38 7F 00 00 */	addi r3, r31, 0
/* 8014E564 0014B144  38 80 00 1F */	li r4, 0x1f
/* 8014E568 0014B148  C0 02 A4 58 */	lfs f0, lbl_804D9E38@sda21(r2)
/* 8014E56C 0014B14C  C0 22 A4 5C */	lfs f1, lbl_804D9E3C@sda21(r2)
/* 8014E570 0014B150  D0 01 00 38 */	stfs f0, 0x38(r1)
/* 8014E574 0014B154  C0 02 A4 60 */	lfs f0, lbl_804D9E40@sda21(r2)
/* 8014E578 0014B158  D0 21 00 3C */	stfs f1, 0x3c(r1)
/* 8014E57C 0014B15C  D0 01 00 40 */	stfs f0, 0x40(r1)
/* 8014E580 0014B160  4B F2 6A 8D */	bl func_8007500C
/* 8014E584 0014B164  80 BF 05 E8 */	lwz r5, 0x5e8(r31)
/* 8014E588 0014B168  54 60 20 36 */	slwi r0, r3, 4
/* 8014E58C 0014B16C  38 81 00 38 */	addi r4, r1, 0x38
/* 8014E590 0014B170  7C 65 00 2E */	lwzx r3, r5, r0
/* 8014E594 0014B174  38 A1 00 44 */	addi r5, r1, 0x44
/* 8014E598 0014B178  4B EB CC 35 */	bl func_8000B1CC
/* 8014E59C 0014B17C  38 60 00 00 */	li r3, 0
/* 8014E5A0 0014B180  83 BE 00 2C */	lwz r29, 0x2c(r30)
/* 8014E5A4 0014B184  20 03 00 05 */	subfic r0, r3, 5
/* 8014E5A8 0014B188  2C 03 00 05 */	cmpwi r3, 5
/* 8014E5AC 0014B18C  7C 09 03 A6 */	mtctr r0
/* 8014E5B0 0014B190  38 81 00 1C */	addi r4, r1, 0x1c
/* 8014E5B4 0014B194  40 80 00 30 */	bge lbl_8014E5E4
lbl_8014E5B8:
/* 8014E5B8 0014B198  80 1D 22 40 */	lwz r0, 0x2240(r29)
/* 8014E5BC 0014B19C  7C 03 00 00 */	cmpw r3, r0
/* 8014E5C0 0014B1A0  41 82 00 1C */	beq lbl_8014E5DC
/* 8014E5C4 0014B1A4  80 1D 22 44 */	lwz r0, 0x2244(r29)
/* 8014E5C8 0014B1A8  7C 03 00 00 */	cmpw r3, r0
/* 8014E5CC 0014B1AC  41 82 00 10 */	beq lbl_8014E5DC
/* 8014E5D0 0014B1B0  90 64 00 00 */	stw r3, 0(r4)
/* 8014E5D4 0014B1B4  38 84 00 04 */	addi r4, r4, 4
/* 8014E5D8 0014B1B8  3B 9C 00 01 */	addi r28, r28, 1
lbl_8014E5DC:
/* 8014E5DC 0014B1BC  38 63 00 01 */	addi r3, r3, 1
/* 8014E5E0 0014B1C0  42 00 FF D8 */	bdnz lbl_8014E5B8
lbl_8014E5E4:
/* 8014E5E4 0014B1C4  7F 83 E3 78 */	mr r3, r28
/* 8014E5E8 0014B1C8  48 23 1F 99 */	bl HSD_Randi
/* 8014E5EC 0014B1CC  54 64 10 3A */	slwi r4, r3, 2
/* 8014E5F0 0014B1D0  80 1D 22 40 */	lwz r0, 0x2240(r29)
/* 8014E5F4 0014B1D4  38 61 00 1C */	addi r3, r1, 0x1c
/* 8014E5F8 0014B1D8  7C A3 20 2E */	lwzx r5, r3, r4
/* 8014E5FC 0014B1DC  38 7E 00 00 */	addi r3, r30, 0
/* 8014E600 0014B1E0  38 81 00 44 */	addi r4, r1, 0x44
/* 8014E604 0014B1E4  90 1D 22 44 */	stw r0, 0x2244(r29)
/* 8014E608 0014B1E8  7C A6 2B 78 */	mr r6, r5
/* 8014E60C 0014B1EC  90 BD 22 40 */	stw r5, 0x2240(r29)
/* 8014E610 0014B1F0  38 A0 00 7A */	li r5, 0x7a
/* 8014E614 0014B1F4  C0 3F 00 2C */	lfs f1, 0x2c(r31)
/* 8014E618 0014B1F8  48 17 9D 65 */	bl func_802C837C
lbl_8014E61C:
/* 8014E61C 0014B1FC  38 00 00 00 */	li r0, 0
/* 8014E620 0014B200  90 1F 21 BC */	stw r0, 0x21bc(r31)
lbl_8014E624:
/* 8014E624 0014B204  80 01 00 6C */	lwz r0, 0x6c(r1)
/* 8014E628 0014B208  83 E1 00 64 */	lwz r31, 0x64(r1)
/* 8014E62C 0014B20C  83 C1 00 60 */	lwz r30, 0x60(r1)
/* 8014E630 0014B210  83 A1 00 5C */	lwz r29, 0x5c(r1)
/* 8014E634 0014B214  83 81 00 58 */	lwz r28, 0x58(r1)
/* 8014E638 0014B218  38 21 00 68 */	addi r1, r1, 0x68
/* 8014E63C 0014B21C  7C 08 03 A6 */	mtlr r0
/* 8014E640 0014B220  4E 80 00 20 */	blr 

.global ftGameWatch_SpecialN_StartAction
ftGameWatch_SpecialN_StartAction:
/* 8014E644 0014B224  7C 08 02 A6 */	mflr r0
/* 8014E648 0014B228  38 80 01 61 */	li r4, 0x161
/* 8014E64C 0014B22C  90 01 00 04 */	stw r0, 4(r1)
/* 8014E650 0014B230  38 C0 00 00 */	li r6, 0
/* 8014E654 0014B234  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8014E658 0014B238  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8014E65C 0014B23C  7C 7F 1B 78 */	mr r31, r3
/* 8014E660 0014B240  C0 22 A4 60 */	lfs f1, lbl_804D9E40@sda21(r2)
/* 8014E664 0014B244  80 A3 00 2C */	lwz r5, 0x2c(r3)
/* 8014E668 0014B248  FC 60 08 90 */	fmr f3, f1
/* 8014E66C 0014B24C  D0 25 00 84 */	stfs f1, 0x84(r5)
/* 8014E670 0014B250  38 A0 00 00 */	li r5, 0
/* 8014E674 0014B254  C0 42 A4 70 */	lfs f2, lbl_804D9E50@sda21(r2)
/* 8014E678 0014B258  4B F1 AD 35 */	bl Fighter_ActionStateChange_800693AC
/* 8014E67C 0014B25C  7F E3 FB 78 */	mr r3, r31
/* 8014E680 0014B260  4B F2 05 25 */	bl func_8006EBA4
/* 8014E684 0014B264  80 BF 00 2C */	lwz r5, 0x2c(r31)
/* 8014E688 0014B268  38 80 00 00 */	li r4, 0
/* 8014E68C 0014B26C  3C 60 80 15 */	lis r3, lbl_8014E4F0@ha
/* 8014E690 0014B270  90 85 22 00 */	stw r4, 0x2200(r5)
/* 8014E694 0014B274  38 03 E4 F0 */	addi r0, r3, lbl_8014E4F0@l
/* 8014E698 0014B278  90 85 22 04 */	stw r4, 0x2204(r5)
/* 8014E69C 0014B27C  90 85 22 08 */	stw r4, 0x2208(r5)
/* 8014E6A0 0014B280  90 85 23 40 */	stw r4, 0x2340(r5)
/* 8014E6A4 0014B284  90 85 23 44 */	stw r4, 0x2344(r5)
/* 8014E6A8 0014B288  90 05 21 BC */	stw r0, 0x21bc(r5)
/* 8014E6AC 0014B28C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8014E6B0 0014B290  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8014E6B4 0014B294  38 21 00 20 */	addi r1, r1, 0x20
/* 8014E6B8 0014B298  7C 08 03 A6 */	mtlr r0
/* 8014E6BC 0014B29C  4E 80 00 20 */	blr 

.global ftGameWatch_SpecialAirN_StartAction
ftGameWatch_SpecialAirN_StartAction:
/* 8014E6C0 0014B2A0  7C 08 02 A6 */	mflr r0
/* 8014E6C4 0014B2A4  38 80 01 62 */	li r4, 0x162
/* 8014E6C8 0014B2A8  90 01 00 04 */	stw r0, 4(r1)
/* 8014E6CC 0014B2AC  38 C0 00 00 */	li r6, 0
/* 8014E6D0 0014B2B0  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8014E6D4 0014B2B4  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8014E6D8 0014B2B8  7C 7F 1B 78 */	mr r31, r3
/* 8014E6DC 0014B2BC  C0 22 A4 60 */	lfs f1, lbl_804D9E40@sda21(r2)
/* 8014E6E0 0014B2C0  80 A3 00 2C */	lwz r5, 0x2c(r3)
/* 8014E6E4 0014B2C4  FC 60 08 90 */	fmr f3, f1
/* 8014E6E8 0014B2C8  D0 25 00 84 */	stfs f1, 0x84(r5)
/* 8014E6EC 0014B2CC  38 A0 00 00 */	li r5, 0
/* 8014E6F0 0014B2D0  C0 42 A4 70 */	lfs f2, lbl_804D9E50@sda21(r2)
/* 8014E6F4 0014B2D4  4B F1 AC B9 */	bl Fighter_ActionStateChange_800693AC
/* 8014E6F8 0014B2D8  7F E3 FB 78 */	mr r3, r31
/* 8014E6FC 0014B2DC  4B F2 04 A9 */	bl func_8006EBA4
/* 8014E700 0014B2E0  80 BF 00 2C */	lwz r5, 0x2c(r31)
/* 8014E704 0014B2E4  38 80 00 00 */	li r4, 0
/* 8014E708 0014B2E8  3C 60 80 15 */	lis r3, lbl_8014E4F0@ha
/* 8014E70C 0014B2EC  90 85 22 00 */	stw r4, 0x2200(r5)
/* 8014E710 0014B2F0  38 03 E4 F0 */	addi r0, r3, lbl_8014E4F0@l
/* 8014E714 0014B2F4  90 85 22 04 */	stw r4, 0x2204(r5)
/* 8014E718 0014B2F8  90 85 22 08 */	stw r4, 0x2208(r5)
/* 8014E71C 0014B2FC  90 85 23 40 */	stw r4, 0x2340(r5)
/* 8014E720 0014B300  90 85 23 44 */	stw r4, 0x2344(r5)
/* 8014E724 0014B304  90 05 21 BC */	stw r0, 0x21bc(r5)
/* 8014E728 0014B308  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8014E72C 0014B30C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8014E730 0014B310  38 21 00 20 */	addi r1, r1, 0x20
/* 8014E734 0014B314  7C 08 03 A6 */	mtlr r0
/* 8014E738 0014B318  4E 80 00 20 */	blr 
.global lbl_8014E73C
lbl_8014E73C:
/* 8014E73C 0014B31C  7C 08 02 A6 */	mflr r0
/* 8014E740 0014B320  90 01 00 04 */	stw r0, 4(r1)
/* 8014E744 0014B324  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 8014E748 0014B328  93 E1 00 3C */	stw r31, 0x3c(r1)
/* 8014E74C 0014B32C  7C 7F 1B 78 */	mr r31, r3
/* 8014E750 0014B330  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 8014E754 0014B334  80 04 22 08 */	lwz r0, 0x2208(r4)
/* 8014E758 0014B338  80 A4 02 D4 */	lwz r5, 0x2d4(r4)
/* 8014E75C 0014B33C  28 00 00 00 */	cmplwi r0, 0
/* 8014E760 0014B340  41 82 00 50 */	beq lbl_8014E7B0
/* 8014E764 0014B344  38 00 00 00 */	li r0, 0
/* 8014E768 0014B348  90 04 22 08 */	stw r0, 0x2208(r4)
/* 8014E76C 0014B34C  3C 00 43 30 */	lis r0, 0x4330
/* 8014E770 0014B350  80 64 23 44 */	lwz r3, 0x2344(r4)
/* 8014E774 0014B354  C8 42 A4 68 */	lfd f2, lbl_804D9E48@sda21(r2)
/* 8014E778 0014B358  6C 63 80 00 */	xoris r3, r3, 0x8000
/* 8014E77C 0014B35C  C0 05 00 1C */	lfs f0, 0x1c(r5)
/* 8014E780 0014B360  90 61 00 34 */	stw r3, 0x34(r1)
/* 8014E784 0014B364  90 01 00 30 */	stw r0, 0x30(r1)
/* 8014E788 0014B368  C8 21 00 30 */	lfd f1, 0x30(r1)
/* 8014E78C 0014B36C  EC 21 10 28 */	fsubs f1, f1, f2
/* 8014E790 0014B370  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8014E794 0014B374  40 80 00 1C */	bge lbl_8014E7B0
/* 8014E798 0014B378  80 04 23 40 */	lwz r0, 0x2340(r4)
/* 8014E79C 0014B37C  2C 00 00 00 */	cmpwi r0, 0
/* 8014E7A0 0014B380  40 82 00 10 */	bne lbl_8014E7B0
/* 8014E7A4 0014B384  7F E3 FB 78 */	mr r3, r31
/* 8014E7A8 0014B388  C0 25 00 18 */	lfs f1, 0x18(r5)
/* 8014E7AC 0014B38C  48 00 03 71 */	bl func_8014EB1C
lbl_8014E7B0:
/* 8014E7B0 0014B390  7F E3 FB 78 */	mr r3, r31
/* 8014E7B4 0014B394  4B F2 0A 85 */	bl ftAnim_IsFramesRemaining
/* 8014E7B8 0014B398  2C 03 00 00 */	cmpwi r3, 0
/* 8014E7BC 0014B39C  40 82 00 0C */	bne lbl_8014E7C8
/* 8014E7C0 0014B3A0  7F E3 FB 78 */	mr r3, r31
/* 8014E7C4 0014B3A4  4B F3 BA F9 */	bl func_8008A2BC
lbl_8014E7C8:
/* 8014E7C8 0014B3A8  80 01 00 44 */	lwz r0, 0x44(r1)
/* 8014E7CC 0014B3AC  83 E1 00 3C */	lwz r31, 0x3c(r1)
/* 8014E7D0 0014B3B0  38 21 00 40 */	addi r1, r1, 0x40
/* 8014E7D4 0014B3B4  7C 08 03 A6 */	mtlr r0
/* 8014E7D8 0014B3B8  4E 80 00 20 */	blr 
.global lbl_8014E7DC
lbl_8014E7DC:
/* 8014E7DC 0014B3BC  7C 08 02 A6 */	mflr r0
/* 8014E7E0 0014B3C0  90 01 00 04 */	stw r0, 4(r1)
/* 8014E7E4 0014B3C4  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 8014E7E8 0014B3C8  93 E1 00 3C */	stw r31, 0x3c(r1)
/* 8014E7EC 0014B3CC  7C 7F 1B 78 */	mr r31, r3
/* 8014E7F0 0014B3D0  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8014E7F4 0014B3D4  80 03 22 08 */	lwz r0, 0x2208(r3)
/* 8014E7F8 0014B3D8  80 83 02 D4 */	lwz r4, 0x2d4(r3)
/* 8014E7FC 0014B3DC  28 00 00 00 */	cmplwi r0, 0
/* 8014E800 0014B3E0  41 82 00 50 */	beq lbl_8014E850
/* 8014E804 0014B3E4  38 00 00 00 */	li r0, 0
/* 8014E808 0014B3E8  90 03 22 08 */	stw r0, 0x2208(r3)
/* 8014E80C 0014B3EC  80 03 23 40 */	lwz r0, 0x2340(r3)
/* 8014E810 0014B3F0  2C 00 00 00 */	cmpwi r0, 0
/* 8014E814 0014B3F4  40 82 00 3C */	bne lbl_8014E850
/* 8014E818 0014B3F8  80 63 23 44 */	lwz r3, 0x2344(r3)
/* 8014E81C 0014B3FC  3C 00 43 30 */	lis r0, 0x4330
/* 8014E820 0014B400  C8 42 A4 68 */	lfd f2, lbl_804D9E48@sda21(r2)
/* 8014E824 0014B404  6C 63 80 00 */	xoris r3, r3, 0x8000
/* 8014E828 0014B408  C0 04 00 1C */	lfs f0, 0x1c(r4)
/* 8014E82C 0014B40C  90 61 00 34 */	stw r3, 0x34(r1)
/* 8014E830 0014B410  90 01 00 30 */	stw r0, 0x30(r1)
/* 8014E834 0014B414  C8 21 00 30 */	lfd f1, 0x30(r1)
/* 8014E838 0014B418  EC 21 10 28 */	fsubs f1, f1, f2
/* 8014E83C 0014B41C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8014E840 0014B420  40 80 00 10 */	bge lbl_8014E850
/* 8014E844 0014B424  7F E3 FB 78 */	mr r3, r31
/* 8014E848 0014B428  C0 24 00 18 */	lfs f1, 0x18(r4)
/* 8014E84C 0014B42C  48 00 03 41 */	bl func_8014EB8C
lbl_8014E850:
/* 8014E850 0014B430  7F E3 FB 78 */	mr r3, r31
/* 8014E854 0014B434  4B F2 09 E5 */	bl ftAnim_IsFramesRemaining
/* 8014E858 0014B438  2C 03 00 00 */	cmpwi r3, 0
/* 8014E85C 0014B43C  40 82 00 0C */	bne lbl_8014E868
/* 8014E860 0014B440  7F E3 FB 78 */	mr r3, r31
/* 8014E864 0014B444  4B F7 DE CD */	bl func_800CC730
lbl_8014E868:
/* 8014E868 0014B448  80 01 00 44 */	lwz r0, 0x44(r1)
/* 8014E86C 0014B44C  83 E1 00 3C */	lwz r31, 0x3c(r1)
/* 8014E870 0014B450  38 21 00 40 */	addi r1, r1, 0x40
/* 8014E874 0014B454  7C 08 03 A6 */	mtlr r0
/* 8014E878 0014B458  4E 80 00 20 */	blr 
.global lbl_8014E87C
lbl_8014E87C:
/* 8014E87C 0014B45C  7C 08 02 A6 */	mflr r0
/* 8014E880 0014B460  90 01 00 04 */	stw r0, 4(r1)
/* 8014E884 0014B464  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8014E888 0014B468  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 8014E88C 0014B46C  80 04 06 5C */	lwz r0, 0x65c(r4)
/* 8014E890 0014B470  80 A4 02 D4 */	lwz r5, 0x2d4(r4)
/* 8014E894 0014B474  54 00 05 AD */	rlwinm. r0, r0, 0, 0x16, 0x16
/* 8014E898 0014B478  40 82 00 0C */	bne lbl_8014E8A4
/* 8014E89C 0014B47C  38 00 00 01 */	li r0, 1
/* 8014E8A0 0014B480  90 04 23 40 */	stw r0, 0x2340(r4)
lbl_8014E8A4:
/* 8014E8A4 0014B484  80 04 22 04 */	lwz r0, 0x2204(r4)
/* 8014E8A8 0014B488  28 00 00 00 */	cmplwi r0, 0
/* 8014E8AC 0014B48C  41 82 00 44 */	beq lbl_8014E8F0
/* 8014E8B0 0014B490  80 04 06 68 */	lwz r0, 0x668(r4)
/* 8014E8B4 0014B494  54 00 05 AD */	rlwinm. r0, r0, 0, 0x16, 0x16
/* 8014E8B8 0014B498  41 82 00 38 */	beq lbl_8014E8F0
/* 8014E8BC 0014B49C  80 84 23 44 */	lwz r4, 0x2344(r4)
/* 8014E8C0 0014B4A0  3C 00 43 30 */	lis r0, 0x4330
/* 8014E8C4 0014B4A4  C8 42 A4 68 */	lfd f2, lbl_804D9E48@sda21(r2)
/* 8014E8C8 0014B4A8  6C 84 80 00 */	xoris r4, r4, 0x8000
/* 8014E8CC 0014B4AC  C0 05 00 1C */	lfs f0, 0x1c(r5)
/* 8014E8D0 0014B4B0  90 81 00 1C */	stw r4, 0x1c(r1)
/* 8014E8D4 0014B4B4  90 01 00 18 */	stw r0, 0x18(r1)
/* 8014E8D8 0014B4B8  C8 21 00 18 */	lfd f1, 0x18(r1)
/* 8014E8DC 0014B4BC  EC 21 10 28 */	fsubs f1, f1, f2
/* 8014E8E0 0014B4C0  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8014E8E4 0014B4C4  40 80 00 0C */	bge lbl_8014E8F0
/* 8014E8E8 0014B4C8  C0 25 00 18 */	lfs f1, 0x18(r5)
/* 8014E8EC 0014B4CC  48 00 02 31 */	bl func_8014EB1C
lbl_8014E8F0:
/* 8014E8F0 0014B4D0  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8014E8F4 0014B4D4  38 21 00 20 */	addi r1, r1, 0x20
/* 8014E8F8 0014B4D8  7C 08 03 A6 */	mtlr r0
/* 8014E8FC 0014B4DC  4E 80 00 20 */	blr 
.global lbl_8014E900
lbl_8014E900:
/* 8014E900 0014B4E0  7C 08 02 A6 */	mflr r0
/* 8014E904 0014B4E4  90 01 00 04 */	stw r0, 4(r1)
/* 8014E908 0014B4E8  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8014E90C 0014B4EC  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 8014E910 0014B4F0  80 04 06 5C */	lwz r0, 0x65c(r4)
/* 8014E914 0014B4F4  80 A4 02 D4 */	lwz r5, 0x2d4(r4)
/* 8014E918 0014B4F8  54 00 05 AD */	rlwinm. r0, r0, 0, 0x16, 0x16
/* 8014E91C 0014B4FC  40 82 00 0C */	bne lbl_8014E928
/* 8014E920 0014B500  38 00 00 01 */	li r0, 1
/* 8014E924 0014B504  90 04 23 40 */	stw r0, 0x2340(r4)
lbl_8014E928:
/* 8014E928 0014B508  80 04 22 04 */	lwz r0, 0x2204(r4)
/* 8014E92C 0014B50C  28 00 00 00 */	cmplwi r0, 0
/* 8014E930 0014B510  41 82 00 44 */	beq lbl_8014E974
/* 8014E934 0014B514  80 04 06 68 */	lwz r0, 0x668(r4)
/* 8014E938 0014B518  54 00 05 AD */	rlwinm. r0, r0, 0, 0x16, 0x16
/* 8014E93C 0014B51C  41 82 00 38 */	beq lbl_8014E974
/* 8014E940 0014B520  80 84 23 44 */	lwz r4, 0x2344(r4)
/* 8014E944 0014B524  3C 00 43 30 */	lis r0, 0x4330
/* 8014E948 0014B528  C8 42 A4 68 */	lfd f2, lbl_804D9E48@sda21(r2)
/* 8014E94C 0014B52C  6C 84 80 00 */	xoris r4, r4, 0x8000
/* 8014E950 0014B530  C0 05 00 1C */	lfs f0, 0x1c(r5)
/* 8014E954 0014B534  90 81 00 1C */	stw r4, 0x1c(r1)
/* 8014E958 0014B538  90 01 00 18 */	stw r0, 0x18(r1)
/* 8014E95C 0014B53C  C8 21 00 18 */	lfd f1, 0x18(r1)
/* 8014E960 0014B540  EC 21 10 28 */	fsubs f1, f1, f2
/* 8014E964 0014B544  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8014E968 0014B548  40 80 00 0C */	bge lbl_8014E974
/* 8014E96C 0014B54C  C0 25 00 18 */	lfs f1, 0x18(r5)
/* 8014E970 0014B550  48 00 02 1D */	bl func_8014EB8C
lbl_8014E974:
/* 8014E974 0014B554  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8014E978 0014B558  38 21 00 20 */	addi r1, r1, 0x20
/* 8014E97C 0014B55C  7C 08 03 A6 */	mtlr r0
/* 8014E980 0014B560  4E 80 00 20 */	blr 
.global lbl_8014E984
lbl_8014E984:
/* 8014E984 0014B564  7C 08 02 A6 */	mflr r0
/* 8014E988 0014B568  90 01 00 04 */	stw r0, 4(r1)
/* 8014E98C 0014B56C  94 21 FF F8 */	stwu r1, -8(r1)
/* 8014E990 0014B570  4B F3 65 AD */	bl func_80084F3C
/* 8014E994 0014B574  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8014E998 0014B578  38 21 00 08 */	addi r1, r1, 8
/* 8014E99C 0014B57C  7C 08 03 A6 */	mtlr r0
/* 8014E9A0 0014B580  4E 80 00 20 */	blr 
.global lbl_8014E9A4
lbl_8014E9A4:
/* 8014E9A4 0014B584  7C 08 02 A6 */	mflr r0
/* 8014E9A8 0014B588  90 01 00 04 */	stw r0, 4(r1)
/* 8014E9AC 0014B58C  94 21 FF F8 */	stwu r1, -8(r1)
/* 8014E9B0 0014B590  4B F3 65 3D */	bl func_80084EEC
/* 8014E9B4 0014B594  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8014E9B8 0014B598  38 21 00 08 */	addi r1, r1, 8
/* 8014E9BC 0014B59C  7C 08 03 A6 */	mtlr r0
/* 8014E9C0 0014B5A0  4E 80 00 20 */	blr 
.global lbl_8014E9C4
lbl_8014E9C4:
/* 8014E9C4 0014B5A4  7C 08 02 A6 */	mflr r0
/* 8014E9C8 0014B5A8  90 01 00 04 */	stw r0, 4(r1)
/* 8014E9CC 0014B5AC  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8014E9D0 0014B5B0  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8014E9D4 0014B5B4  7C 7F 1B 78 */	mr r31, r3
/* 8014E9D8 0014B5B8  4B F3 3D C9 */	bl func_800827A0
/* 8014E9DC 0014B5BC  2C 03 00 00 */	cmpwi r3, 0
/* 8014E9E0 0014B5C0  40 82 00 0C */	bne lbl_8014E9EC
/* 8014E9E4 0014B5C4  7F E3 FB 78 */	mr r3, r31
/* 8014E9E8 0014B5C8  48 00 00 55 */	bl func_8014EA3C
lbl_8014E9EC:
/* 8014E9EC 0014B5CC  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8014E9F0 0014B5D0  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8014E9F4 0014B5D4  38 21 00 18 */	addi r1, r1, 0x18
/* 8014E9F8 0014B5D8  7C 08 03 A6 */	mtlr r0
/* 8014E9FC 0014B5DC  4E 80 00 20 */	blr 
.global lbl_8014EA00
lbl_8014EA00:
/* 8014EA00 0014B5E0  7C 08 02 A6 */	mflr r0
/* 8014EA04 0014B5E4  90 01 00 04 */	stw r0, 4(r1)
/* 8014EA08 0014B5E8  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8014EA0C 0014B5EC  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8014EA10 0014B5F0  7C 7F 1B 78 */	mr r31, r3
/* 8014EA14 0014B5F4  4B F3 32 F9 */	bl func_80081D0C
/* 8014EA18 0014B5F8  2C 03 00 00 */	cmpwi r3, 0
/* 8014EA1C 0014B5FC  41 82 00 0C */	beq lbl_8014EA28
/* 8014EA20 0014B600  7F E3 FB 78 */	mr r3, r31
/* 8014EA24 0014B604  48 00 00 89 */	bl func_8014EAAC
lbl_8014EA28:
/* 8014EA28 0014B608  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8014EA2C 0014B60C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8014EA30 0014B610  38 21 00 18 */	addi r1, r1, 0x18
/* 8014EA34 0014B614  7C 08 03 A6 */	mtlr r0
/* 8014EA38 0014B618  4E 80 00 20 */	blr 

.global func_8014EA3C
func_8014EA3C:
/* 8014EA3C 0014B61C  7C 08 02 A6 */	mflr r0
/* 8014EA40 0014B620  90 01 00 04 */	stw r0, 4(r1)
/* 8014EA44 0014B624  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8014EA48 0014B628  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8014EA4C 0014B62C  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8014EA50 0014B630  7C 7E 1B 78 */	mr r30, r3
/* 8014EA54 0014B634  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8014EA58 0014B638  7F E3 FB 78 */	mr r3, r31
/* 8014EA5C 0014B63C  4B F2 EB 79 */	bl func_8007D5D4
/* 8014EA60 0014B640  3C 80 0C 4C */	lis r4, 0x0C4C509C@ha
/* 8014EA64 0014B644  C0 3F 08 94 */	lfs f1, 0x894(r31)
/* 8014EA68 0014B648  C0 42 A4 70 */	lfs f2, lbl_804D9E50@sda21(r2)
/* 8014EA6C 0014B64C  7F C3 F3 78 */	mr r3, r30
/* 8014EA70 0014B650  C0 62 A4 60 */	lfs f3, lbl_804D9E40@sda21(r2)
/* 8014EA74 0014B654  38 A4 50 9C */	addi r5, r4, 0x0C4C509C@l
/* 8014EA78 0014B658  38 80 01 62 */	li r4, 0x162
/* 8014EA7C 0014B65C  38 C0 00 00 */	li r6, 0
/* 8014EA80 0014B660  4B F1 A9 2D */	bl Fighter_ActionStateChange_800693AC
/* 8014EA84 0014B664  3C 80 80 15 */	lis r4, lbl_8014E4F0@ha
/* 8014EA88 0014B668  80 7E 00 2C */	lwz r3, 0x2c(r30)
/* 8014EA8C 0014B66C  38 04 E4 F0 */	addi r0, r4, lbl_8014E4F0@l
/* 8014EA90 0014B670  90 03 21 BC */	stw r0, 0x21bc(r3)
/* 8014EA94 0014B674  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8014EA98 0014B678  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8014EA9C 0014B67C  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8014EAA0 0014B680  38 21 00 20 */	addi r1, r1, 0x20
/* 8014EAA4 0014B684  7C 08 03 A6 */	mtlr r0
/* 8014EAA8 0014B688  4E 80 00 20 */	blr 

.global func_8014EAAC
func_8014EAAC:
/* 8014EAAC 0014B68C  7C 08 02 A6 */	mflr r0
/* 8014EAB0 0014B690  90 01 00 04 */	stw r0, 4(r1)
/* 8014EAB4 0014B694  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8014EAB8 0014B698  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8014EABC 0014B69C  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8014EAC0 0014B6A0  7C 7E 1B 78 */	mr r30, r3
/* 8014EAC4 0014B6A4  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8014EAC8 0014B6A8  7F E3 FB 78 */	mr r3, r31
/* 8014EACC 0014B6AC  4B F2 ED 31 */	bl func_8007D7FC
/* 8014EAD0 0014B6B0  3C 80 0C 4C */	lis r4, 0x0C4C509C@ha
/* 8014EAD4 0014B6B4  C0 3F 08 94 */	lfs f1, 0x894(r31)
/* 8014EAD8 0014B6B8  C0 42 A4 70 */	lfs f2, lbl_804D9E50@sda21(r2)
/* 8014EADC 0014B6BC  7F C3 F3 78 */	mr r3, r30
/* 8014EAE0 0014B6C0  C0 62 A4 60 */	lfs f3, lbl_804D9E40@sda21(r2)
/* 8014EAE4 0014B6C4  38 A4 50 9C */	addi r5, r4, 0x0C4C509C@l
/* 8014EAE8 0014B6C8  38 80 01 61 */	li r4, 0x161
/* 8014EAEC 0014B6CC  38 C0 00 00 */	li r6, 0
/* 8014EAF0 0014B6D0  4B F1 A8 BD */	bl Fighter_ActionStateChange_800693AC
/* 8014EAF4 0014B6D4  3C 80 80 15 */	lis r4, lbl_8014E4F0@ha
/* 8014EAF8 0014B6D8  80 7E 00 2C */	lwz r3, 0x2c(r30)
/* 8014EAFC 0014B6DC  38 04 E4 F0 */	addi r0, r4, lbl_8014E4F0@l
/* 8014EB00 0014B6E0  90 03 21 BC */	stw r0, 0x21bc(r3)
/* 8014EB04 0014B6E4  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8014EB08 0014B6E8  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8014EB0C 0014B6EC  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8014EB10 0014B6F0  38 21 00 20 */	addi r1, r1, 0x20
/* 8014EB14 0014B6F4  7C 08 03 A6 */	mtlr r0
/* 8014EB18 0014B6F8  4E 80 00 20 */	blr 

.global func_8014EB1C
func_8014EB1C:
/* 8014EB1C 0014B6FC  7C 08 02 A6 */	mflr r0
/* 8014EB20 0014B700  3C 80 0C 4C */	lis r4, 0x0C4C509C@ha
/* 8014EB24 0014B704  90 01 00 04 */	stw r0, 4(r1)
/* 8014EB28 0014B708  38 A4 50 9C */	addi r5, r4, 0x0C4C509C@l
/* 8014EB2C 0014B70C  38 80 01 61 */	li r4, 0x161
/* 8014EB30 0014B710  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8014EB34 0014B714  38 C0 00 00 */	li r6, 0
/* 8014EB38 0014B718  93 E1 00 24 */	stw r31, 0x24(r1)
/* 8014EB3C 0014B71C  7C 7F 1B 78 */	mr r31, r3
/* 8014EB40 0014B720  C0 42 A4 70 */	lfs f2, lbl_804D9E50@sda21(r2)
/* 8014EB44 0014B724  C0 62 A4 60 */	lfs f3, lbl_804D9E40@sda21(r2)
/* 8014EB48 0014B728  EC 21 10 28 */	fsubs f1, f1, f2
/* 8014EB4C 0014B72C  4B F1 A8 61 */	bl Fighter_ActionStateChange_800693AC
/* 8014EB50 0014B730  7F E3 FB 78 */	mr r3, r31
/* 8014EB54 0014B734  4B F2 00 51 */	bl func_8006EBA4
/* 8014EB58 0014B738  80 BF 00 2C */	lwz r5, 0x2c(r31)
/* 8014EB5C 0014B73C  38 80 00 00 */	li r4, 0
/* 8014EB60 0014B740  3C 60 80 15 */	lis r3, lbl_8014E4F0@ha
/* 8014EB64 0014B744  90 85 22 04 */	stw r4, 0x2204(r5)
/* 8014EB68 0014B748  38 03 E4 F0 */	addi r0, r3, lbl_8014E4F0@l
/* 8014EB6C 0014B74C  90 85 22 08 */	stw r4, 0x2208(r5)
/* 8014EB70 0014B750  90 85 23 40 */	stw r4, 0x2340(r5)
/* 8014EB74 0014B754  90 05 21 BC */	stw r0, 0x21bc(r5)
/* 8014EB78 0014B758  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8014EB7C 0014B75C  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 8014EB80 0014B760  38 21 00 28 */	addi r1, r1, 0x28
/* 8014EB84 0014B764  7C 08 03 A6 */	mtlr r0
/* 8014EB88 0014B768  4E 80 00 20 */	blr 

.global func_8014EB8C
func_8014EB8C:
/* 8014EB8C 0014B76C  7C 08 02 A6 */	mflr r0
/* 8014EB90 0014B770  3C 80 0C 4C */	lis r4, 0x0C4C509C@ha
/* 8014EB94 0014B774  90 01 00 04 */	stw r0, 4(r1)
/* 8014EB98 0014B778  38 A4 50 9C */	addi r5, r4, 0x0C4C509C@l
/* 8014EB9C 0014B77C  38 80 01 62 */	li r4, 0x162
/* 8014EBA0 0014B780  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8014EBA4 0014B784  38 C0 00 00 */	li r6, 0
/* 8014EBA8 0014B788  93 E1 00 24 */	stw r31, 0x24(r1)
/* 8014EBAC 0014B78C  7C 7F 1B 78 */	mr r31, r3
/* 8014EBB0 0014B790  C0 42 A4 70 */	lfs f2, lbl_804D9E50@sda21(r2)
/* 8014EBB4 0014B794  C0 62 A4 60 */	lfs f3, lbl_804D9E40@sda21(r2)
/* 8014EBB8 0014B798  EC 21 10 28 */	fsubs f1, f1, f2
/* 8014EBBC 0014B79C  4B F1 A7 F1 */	bl Fighter_ActionStateChange_800693AC
/* 8014EBC0 0014B7A0  7F E3 FB 78 */	mr r3, r31
/* 8014EBC4 0014B7A4  4B F1 FF E1 */	bl func_8006EBA4
/* 8014EBC8 0014B7A8  80 BF 00 2C */	lwz r5, 0x2c(r31)
/* 8014EBCC 0014B7AC  38 80 00 00 */	li r4, 0
/* 8014EBD0 0014B7B0  3C 60 80 15 */	lis r3, lbl_8014E4F0@ha
/* 8014EBD4 0014B7B4  90 85 22 04 */	stw r4, 0x2204(r5)
/* 8014EBD8 0014B7B8  38 03 E4 F0 */	addi r0, r3, lbl_8014E4F0@l
/* 8014EBDC 0014B7BC  90 85 22 08 */	stw r4, 0x2208(r5)
/* 8014EBE0 0014B7C0  90 85 23 40 */	stw r4, 0x2340(r5)
/* 8014EBE4 0014B7C4  90 05 21 BC */	stw r0, 0x21bc(r5)
/* 8014EBE8 0014B7C8  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8014EBEC 0014B7CC  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 8014EBF0 0014B7D0  38 21 00 28 */	addi r1, r1, 0x28
/* 8014EBF4 0014B7D4  7C 08 03 A6 */	mtlr r0
/* 8014EBF8 0014B7D8  4E 80 00 20 */	blr 


.section .data
    .balign 8
.global as_table_gamewatch
as_table_gamewatch:
    .4byte 0x0000002E
    .4byte 0x002C0201
    .4byte 0x02800000
    .4byte ftGameWatch_Attack11_Anim
    .4byte ftGameWatch_Attack11_IASA
    .4byte ftGameWatch_Attack11_Phys
    .4byte ftGameWatch_Attack11_Coll
    .4byte func_800761C8
    .4byte 0x00000031
    .4byte 0x002C0204
    .4byte 0x05800000
    .4byte ftGameWatch_Attack100Start_Anim
    .4byte ftGameWatch_Attack100Start_IASA
    .4byte ftGameWatch_Attack100Start_Phys
    .4byte ftGameWatch_Attack100Start_Coll
    .4byte func_800761C8
    .4byte 0x00000032
    .4byte 0x002C0204
    .4byte 0x05800000
    .4byte ftGameWatch_Attack100Loop_Anim
    .4byte ftGameWatch_Attack100Loop_IASA
    .4byte ftGameWatch_Attack100Loop_Phys
    .4byte ftGameWatch_Attack100Loop_Coll
    .4byte func_800761C8
    .4byte 0x00000033
    .4byte 0x002C0204
    .4byte 0x05800000
    .4byte ftGameWatch_Attack100End_Anim
    .4byte ftGameWatch_Attack100End_IASA
    .4byte ftGameWatch_Attack100End_Phys
    .4byte ftGameWatch_Attack100End_Coll
    .4byte func_800761C8
    .4byte 0x0000003B
    .4byte 0x00240208
    .4byte 0x09800000
    .4byte ftGameWatch_AttackLw3_Anim
    .4byte ftGameWatch_AttackLw3_IASA
    .4byte ftGameWatch_AttackLw3_Phys
    .4byte ftGameWatch_AttackLw3_Coll
    .4byte func_800761C8
    .4byte 0x0000003E
    .4byte 0x00240A09
    .4byte 0x0A800000
    .4byte ftGameWatch_AttackS4_Anim
    .4byte ftGameWatch_AttackS4_IASA
    .4byte ftGameWatch_AttackS4_Phys
    .4byte ftGameWatch_AttackS4_Coll
    .4byte func_800761C8
    .4byte 0x00000044
    .4byte 0x0024060C
    .4byte 0x0D800000
    .4byte ftGameWatch_AttackAirN_Anim
    .4byte ftGameWatch_AttackAirN_IASA
    .4byte ftGameWatch_AttackAirN_Phys
    .4byte ftGameWatch_AttackAirN_Coll
    .4byte func_800761C8
    .4byte 0x00000046
    .4byte 0x0024060E
    .4byte 0x0F800000
    .4byte ftGameWatch_AttackAirB_Anim
    .4byte ftGameWatch_AttackAirB_IASA
    .4byte ftGameWatch_AttackAirB_Phys
    .4byte ftGameWatch_AttackAirB_Coll
    .4byte func_800761C8
    .4byte 0x00000047
    .4byte 0x0024060F
    .4byte 0x10800000
    .4byte ftGameWatch_AttackAirHi_Anim
    .4byte ftGameWatch_AttackAirHi_IASA
    .4byte ftGameWatch_AttackAirHi_Phys
    .4byte ftGameWatch_AttackAirHi_Coll
    .4byte func_800761C8
    .4byte 0x00000049
    .4byte 0x0000060C
    .4byte 0x0DC00000
    .4byte ftGameWatch_LandingAirN_Anim
    .4byte ftGameWatch_LandingAirN_IASA
    .4byte ftGameWatch_LandingAirN_Phys
    .4byte ftGameWatch_LandingAirN_Coll
    .4byte func_800761C8
    .4byte 0x0000004B
    .4byte 0x0000060E
    .4byte 0x0FC00000
    .4byte ftGameWatch_LandingAirB_Anim
    .4byte ftGameWatch_LandingAirB_IASA
    .4byte ftGameWatch_LandingAirB_Phys
    .4byte ftGameWatch_LandingAirB_Coll
    .4byte func_800761C8
    .4byte 0x0000004C
    .4byte 0x0000060F
    .4byte 0x10C00000
    .4byte ftGameWatch_LandingAirHi_Anim
    .4byte ftGameWatch_LandingAirHi_IASA
    .4byte ftGameWatch_LandingAirHi_Phys
    .4byte ftGameWatch_LandingAirHi_Coll
    .4byte func_800761C8
    .4byte 0x00000127
    .4byte 0x00340111
    .4byte 0x12000000
    .4byte lbl_8014E73C
    .4byte lbl_8014E87C
    .4byte lbl_8014E984
    .4byte lbl_8014E9C4
    .4byte func_800761C8
    .4byte 0x00000128
    .4byte 0x00340511
    .4byte 0x12000000
    .4byte lbl_8014E7DC
    .4byte lbl_8014E900
    .4byte lbl_8014E9A4
    .4byte lbl_8014EA00
    .4byte func_800761C8
    .4byte 0x00000129
    .4byte 0x00340012
    .4byte 0x13000000
    .4byte ftGameWatch_SpecialS_Anim
    .4byte ftGameWatch_SpecialS_IASA
    .4byte ftGameWatch_SpecialS_Phys
    .4byte ftGameWatch_SpecialS_Coll
    .4byte func_800761C8
    .4byte 0x0000012A
    .4byte 0x00340012
    .4byte 0x13000000
    .4byte ftGameWatch_SpecialS_Anim
    .4byte ftGameWatch_SpecialS_IASA
    .4byte ftGameWatch_SpecialS_Phys
    .4byte ftGameWatch_SpecialS_Coll
    .4byte func_800761C8
    .4byte 0x0000012B
    .4byte 0x00340012
    .4byte 0x13000000
    .4byte ftGameWatch_SpecialS_Anim
    .4byte ftGameWatch_SpecialS_IASA
    .4byte ftGameWatch_SpecialS_Phys
    .4byte ftGameWatch_SpecialS_Coll
    .4byte func_800761C8
    .4byte 0x0000012C
    .4byte 0x00340012
    .4byte 0x13000000
    .4byte ftGameWatch_SpecialS_Anim
    .4byte ftGameWatch_SpecialS_IASA
    .4byte ftGameWatch_SpecialS_Phys
    .4byte ftGameWatch_SpecialS_Coll
    .4byte func_800761C8
    .4byte 0x0000012D
    .4byte 0x00340012
    .4byte 0x13000000
    .4byte ftGameWatch_SpecialS_Anim
    .4byte ftGameWatch_SpecialS_IASA
    .4byte ftGameWatch_SpecialS_Phys
    .4byte ftGameWatch_SpecialS_Coll
    .4byte func_800761C8
    .4byte 0x0000012E
    .4byte 0x00340012
    .4byte 0x13000000
    .4byte ftGameWatch_SpecialS_Anim
    .4byte ftGameWatch_SpecialS_IASA
    .4byte ftGameWatch_SpecialS_Phys
    .4byte ftGameWatch_SpecialS_Coll
    .4byte func_800761C8
    .4byte 0x0000012F
    .4byte 0x00340012
    .4byte 0x13000000
    .4byte ftGameWatch_SpecialS_Anim
    .4byte ftGameWatch_SpecialS_IASA
    .4byte ftGameWatch_SpecialS_Phys
    .4byte ftGameWatch_SpecialS_Coll
    .4byte func_800761C8
    .4byte 0x00000130
    .4byte 0x00340012
    .4byte 0x13000000
    .4byte ftGameWatch_SpecialS_Anim
    .4byte ftGameWatch_SpecialS_IASA
    .4byte ftGameWatch_SpecialS_Phys
    .4byte ftGameWatch_SpecialS_Coll
    .4byte func_800761C8
    .4byte 0x00000131
    .4byte 0x00340012
    .4byte 0x13000000
    .4byte ftGameWatch_SpecialS_Anim
    .4byte ftGameWatch_SpecialS_IASA
    .4byte ftGameWatch_SpecialS_Phys
    .4byte ftGameWatch_SpecialS_Coll
    .4byte func_800761C8
    .4byte 0x00000132
    .4byte 0x00340412
    .4byte 0x13000000
    .4byte ftGameWatch_SpecialAirS_Anim
    .4byte ftGameWatch_SpecialAirS_IASA
    .4byte ftGameWatch_SpecialAirS_Phys
    .4byte ftGameWatch_SpecialAirS_Coll
    .4byte func_800761C8
    .4byte 0x00000133
    .4byte 0x00340412
    .4byte 0x13000000
    .4byte ftGameWatch_SpecialAirS_Anim
    .4byte ftGameWatch_SpecialAirS_IASA
    .4byte ftGameWatch_SpecialAirS_Phys
    .4byte ftGameWatch_SpecialAirS_Coll
    .4byte func_800761C8
    .4byte 0x00000134
    .4byte 0x00340412
    .4byte 0x13000000
    .4byte ftGameWatch_SpecialAirS_Anim
    .4byte ftGameWatch_SpecialAirS_IASA
    .4byte ftGameWatch_SpecialAirS_Phys
    .4byte ftGameWatch_SpecialAirS_Coll
    .4byte func_800761C8
    .4byte 0x00000135
    .4byte 0x00340412
    .4byte 0x13000000
    .4byte ftGameWatch_SpecialAirS_Anim
    .4byte ftGameWatch_SpecialAirS_IASA
    .4byte ftGameWatch_SpecialAirS_Phys
    .4byte ftGameWatch_SpecialAirS_Coll
    .4byte func_800761C8
    .4byte 0x00000136
    .4byte 0x00340412
    .4byte 0x13000000
    .4byte ftGameWatch_SpecialAirS_Anim
    .4byte ftGameWatch_SpecialAirS_IASA
    .4byte ftGameWatch_SpecialAirS_Phys
    .4byte ftGameWatch_SpecialAirS_Coll
    .4byte func_800761C8
    .4byte 0x00000137
    .4byte 0x00340412
    .4byte 0x13000000
    .4byte ftGameWatch_SpecialAirS_Anim
    .4byte ftGameWatch_SpecialAirS_IASA
    .4byte ftGameWatch_SpecialAirS_Phys
    .4byte ftGameWatch_SpecialAirS_Coll
    .4byte func_800761C8
    .4byte 0x00000138
    .4byte 0x00340412
    .4byte 0x13000000
    .4byte ftGameWatch_SpecialAirS_Anim
    .4byte ftGameWatch_SpecialAirS_IASA
    .4byte ftGameWatch_SpecialAirS_Phys
    .4byte ftGameWatch_SpecialAirS_Coll
    .4byte func_800761C8
    .4byte 0x00000139
    .4byte 0x00340412
    .4byte 0x13000000
    .4byte ftGameWatch_SpecialAirS_Anim
    .4byte ftGameWatch_SpecialAirS_IASA
    .4byte ftGameWatch_SpecialAirS_Phys
    .4byte ftGameWatch_SpecialAirS_Coll
    .4byte func_800761C8
    .4byte 0x0000013A
    .4byte 0x00340412
    .4byte 0x13000000
    .4byte ftGameWatch_SpecialAirS_Anim
    .4byte ftGameWatch_SpecialAirS_IASA
    .4byte ftGameWatch_SpecialAirS_Phys
    .4byte ftGameWatch_SpecialAirS_Coll
    .4byte func_800761C8
    .4byte 0x0000013B
    .4byte 0x00340013
    .4byte 0x14000000
    .4byte ftGameWatch_SpecialHi_Anim
    .4byte ftGameWatch_SpecialHi_IASA
    .4byte ftGameWatch_SpecialHi_Phys
    .4byte ftGameWatch_SpecialHi_Coll
    .4byte func_800761C8
    .4byte 0x0000013C
    .4byte 0x00340413
    .4byte 0x14000000
    .4byte ftGameWatch_SpecialAirHi_Anim
    .4byte ftGameWatch_SpecialAirHi_IASA
    .4byte ftGameWatch_SpecialAirHi_Phys
    .4byte ftGameWatch_SpecialAirHi_Coll
    .4byte func_800761C8
    .4byte 0x0000013D
    .4byte 0x003C0014
    .4byte 0x15000000
    .4byte ftGameWatch_SpecialLw_Anim
    .4byte ftGameWatch_SpecialLw_IASA
    .4byte ftGameWatch_SpecialLw_Phys
    .4byte ftGameWatch_SpecialLw_Coll
    .4byte func_800761C8
    .4byte 0x0000013E
    .4byte 0x00340014
    .4byte 0x15000000
    .4byte ftGameWatch_SpecialLwCatch_Anim
    .4byte ftGameWatch_SpecialLwCatch_IASA
    .4byte ftGameWatch_SpecialLwCatch_Phys
    .4byte ftGameWatch_SpecialLwCatch_Coll
    .4byte func_800761C8
    .4byte 0x0000013F
    .4byte 0x00340014
    .4byte 0x15000000
    .4byte ftGameWatch_SpecialLwShoot_Anim
    .4byte ftGameWatch_SpecialLwShoot_IASA
    .4byte ftGameWatch_SpecialLwShoot_Phys
    .4byte ftGameWatch_SpecialLwShoot_Coll
    .4byte func_800761C8
    .4byte 0x00000140
    .4byte 0x003C0414
    .4byte 0x15000000
    .4byte ftGameWatch_SpecialAirLw_Anim
    .4byte ftGameWatch_SpecialAirLw_IASA
    .4byte ftGameWatch_SpecialAirLw_Phys
    .4byte ftGameWatch_SpecialAirLw_Coll
    .4byte func_800761C8
    .4byte 0x00000141
    .4byte 0x00340414
    .4byte 0x15000000
    .4byte ftGameWatch_SpecialAirLwCatch_Anim
    .4byte ftGameWatch_SpecialAirLwCatch_IASA
    .4byte ftGameWatch_SpecialAirLwCatch_Phys
    .4byte ftGameWatch_SpecialAirLwCatch_Coll
    .4byte func_800761C8
    .4byte 0x00000142
    .4byte 0x00340414
    .4byte 0x15000000
    .4byte ftGameWatch_SpecialAirLwShoot_Anim
    .4byte ftGameWatch_SpecialAirLwShoot_IASA
    .4byte ftGameWatch_SpecialAirLwShoot_Phys
    .4byte ftGameWatch_SpecialAirLwShoot_Coll
    .4byte func_800761C8
.global lbl_803D28E8
lbl_803D28E8:
    .asciz "PlGw.dat"
    .balign 4
.global lbl_803D28F4
lbl_803D28F4:
    .asciz "ftDataGamewatch"
    .balign 4
.global lbl_803D2904
lbl_803D2904:
    .asciz "PlGwNr.dat"
    .balign 4
.global lbl_803D2910
lbl_803D2910:
    .asciz "PlyGamewatch5K_Share_joint"
    .balign 4
.global lbl_803D292C
lbl_803D292C:
    .asciz "PlGwAJ.dat"
    .balign 4
.global lbl_803D2938
lbl_803D2938:
    .asciz "ftDemoResultMotionFileGamewatch"
    .balign 4
.global lbl_803D2958
lbl_803D2958:
    .asciz "ftDemoIntroMotionFileGamewatch"
    .balign 4
.global lbl_803D2978
lbl_803D2978:
    .asciz "ftDemoEndingMotionFileGamewatch"
    .balign 4
.global lbl_803D2998
lbl_803D2998:
    .asciz "ftDemoViWaitMotionFileGamewatch"
    .balign 4
.global lbl_803D29B8
lbl_803D29B8:
    .4byte lbl_803D2938
    .4byte lbl_803D2958
    .4byte lbl_803D2978
    .4byte lbl_803D2998
.global lbl_803D29C8
lbl_803D29C8:
    .4byte lbl_803D2904
    .4byte lbl_803D2910
    .4byte NULL
    .4byte lbl_803D2904
    .4byte lbl_803D2910
    .4byte NULL
    .4byte lbl_803D2904
    .4byte lbl_803D2910
    .4byte NULL
    .4byte lbl_803D2904
    .4byte lbl_803D2910
    .4byte NULL


.section .sdata2
    .balign 8
.global lbl_804D9E38
lbl_804D9E38:
	.4byte 0x40200000
.global lbl_804D9E3C
lbl_804D9E3C:
	.4byte 0x40D00000
.global lbl_804D9E40
lbl_804D9E40:
	.4byte 0x00000000
	.4byte 0x00000000
.global lbl_804D9E48
lbl_804D9E48:
	.4byte 0x43300000
	.4byte 0x80000000
.global lbl_804D9E50
lbl_804D9E50:
	.4byte 0x3F800000
	.4byte 0x00000000
