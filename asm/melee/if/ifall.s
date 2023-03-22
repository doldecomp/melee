.include "macros.inc"

.section .text  # 0x802F3394 - 0x8032261C

.global ifAll_802F3394
ifAll_802F3394:
/* 802F3394 002EFF74  7C 08 02 A6 */	mflr r0
/* 802F3398 002EFF78  90 01 00 04 */	stw r0, 4(r1)
/* 802F339C 002EFF7C  94 21 FF F8 */	stwu r1, -8(r1)
/* 802F33A0 002EFF80  48 00 34 F9 */	bl func_802F6898
/* 802F33A4 002EFF84  48 00 0C B9 */	bl ifTime_802F405C
/* 802F33A8 002EFF88  48 00 A0 A9 */	bl un_802FD450
/* 802F33AC 002EFF8C  48 00 95 3D */	bl func_802FC8E8
/* 802F33B0 002EFF90  48 00 A2 B9 */	bl un_802FD668
/* 802F33B4 002EFF94  48 00 A5 5D */	bl un_802FD910
/* 802F33B8 002EFF98  48 00 C1 B9 */	bl un_802FF570
/* 802F33BC 002EFF9C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802F33C0 002EFFA0  38 21 00 08 */	addi r1, r1, 8
/* 802F33C4 002EFFA4  7C 08 03 A6 */	mtlr r0
/* 802F33C8 002EFFA8  4E 80 00 20 */	blr

.global ifAll_802F33CC
ifAll_802F33CC:
/* 802F33CC 002EFFAC  7C 08 02 A6 */	mflr r0
/* 802F33D0 002EFFB0  90 01 00 04 */	stw r0, 4(r1)
/* 802F33D4 002EFFB4  94 21 FF F8 */	stwu r1, -8(r1)
/* 802F33D8 002EFFB8  48 00 35 19 */	bl func_802F68F0
/* 802F33DC 002EFFBC  48 00 0C DD */	bl ifTime_802F40B8
/* 802F33E0 002EFFC0  48 00 A0 7D */	bl un_802FD45C
/* 802F33E4 002EFFC4  48 00 95 5D */	bl func_802FC940
/* 802F33E8 002EFFC8  48 00 A2 8D */	bl un_802FD674
/* 802F33EC 002EFFCC  48 00 A5 31 */	bl un_802FD91C
/* 802F33F0 002EFFD0  48 00 C2 31 */	bl un_802FF620
/* 802F33F4 002EFFD4  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802F33F8 002EFFD8  38 21 00 08 */	addi r1, r1, 8
/* 802F33FC 002EFFDC  7C 08 03 A6 */	mtlr r0
/* 802F3400 002EFFE0  4E 80 00 20 */	blr

.global ifAll_802F3404
ifAll_802F3404:
/* 802F3404 002EFFE4  3C 60 80 4A */	lis r3, lbl_804A0FD8@ha
/* 802F3408 002EFFE8  38 63 0F D8 */	addi r3, r3, lbl_804A0FD8@l
/* 802F340C 002EFFEC  80 63 00 00 */	lwz r3, 0(r3)
/* 802F3410 002EFFF0  4E 80 00 20 */	blr

.global ifAll_802F3414
ifAll_802F3414:
/* 802F3414 002EFFF4  3C 60 80 4A */	lis r3, lbl_804A0FD8@ha
/* 802F3418 002EFFF8  38 63 0F D8 */	addi r3, r3, lbl_804A0FD8@l
/* 802F341C 002EFFFC  38 63 00 0C */	addi r3, r3, 0xc
/* 802F3420 002F0000  4E 80 00 20 */	blr

.global ifAll_802F3424
ifAll_802F3424:
/* 802F3424 002F0004  1C 83 00 0C */	mulli r4, r3, 0xc
/* 802F3428 002F0008  3C 60 80 4A */	lis r3, lbl_804A0FD8@ha
/* 802F342C 002F000C  38 03 0F D8 */	addi r0, r3, lbl_804A0FD8@l
/* 802F3430 002F0010  7C 60 22 14 */	add r3, r0, r4
/* 802F3434 002F0014  38 63 00 18 */	addi r3, r3, 0x18
/* 802F3438 002F0018  4E 80 00 20 */	blr

.global ifAll_802F343C
ifAll_802F343C:
/* 802F343C 002F001C  7C 08 02 A6 */	mflr r0
/* 802F3440 002F0020  90 01 00 04 */	stw r0, 4(r1)
/* 802F3444 002F0024  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 802F3448 002F0028  DB E1 00 20 */	stfd f31, 0x20(r1)
/* 802F344C 002F002C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 802F3450 002F0030  93 C1 00 18 */	stw r30, 0x18(r1)
/* 802F3454 002F0034  3B C3 00 00 */	addi r30, r3, 0
/* 802F3458 002F0038  3C 60 80 4A */	lis r3, lbl_804A0FD8@ha
/* 802F345C 002F003C  93 A1 00 14 */	stw r29, 0x14(r1)
/* 802F3460 002F0040  3B E3 0F D8 */	addi r31, r3, lbl_804A0FD8@l
/* 802F3464 002F0044  2C 1E 00 03 */	cmpwi r30, 3
/* 802F3468 002F0048  93 81 00 10 */	stw r28, 0x10(r1)
/* 802F346C 002F004C  83 9F 00 08 */	lwz r28, 8(r31)
/* 802F3470 002F0050  41 82 00 A4 */	beq ifAll_802F3514
/* 802F3474 002F0054  40 80 00 14 */	bge ifAll_802F3488
/* 802F3478 002F0058  2C 1E 00 01 */	cmpwi r30, 1
/* 802F347C 002F005C  41 82 00 20 */	beq ifAll_802F349C
/* 802F3480 002F0060  40 80 00 48 */	bge ifAll_802F34C8
/* 802F3484 002F0064  48 00 01 E8 */	b ifAll_802F366C
ifAll_802F3488:
/* 802F3488 002F0068  2C 1E 00 07 */	cmpwi r30, 7
/* 802F348C 002F006C  40 80 01 E0 */	bge ifAll_802F366C
/* 802F3490 002F0070  2C 1E 00 05 */	cmpwi r30, 5
/* 802F3494 002F0074  40 80 01 18 */	bge ifAll_802F35AC
/* 802F3498 002F0078  48 00 00 C8 */	b ifAll_802F3560
ifAll_802F349C:
/* 802F349C 002F007C  38 7C 00 00 */	addi r3, r28, 0
/* 802F34A0 002F0080  4C C6 31 82 */	crclr 6
/* 802F34A4 002F0084  38 81 00 0C */	addi r4, r1, 0xc
/* 802F34A8 002F0088  38 A0 00 09 */	li r5, 9
/* 802F34AC 002F008C  38 C0 FF FF */	li r6, -1
/* 802F34B0 002F0090  4B D1 E9 75 */	bl lb_80011E24
/* 802F34B4 002F0094  80 61 00 0C */	lwz r3, 0xc(r1)
/* 802F34B8 002F0098  38 BF 00 18 */	addi r5, r31, 0x18
/* 802F34BC 002F009C  38 80 00 00 */	li r4, 0
/* 802F34C0 002F00A0  4B D1 7D 0D */	bl lb_8000B1CC
/* 802F34C4 002F00A4  48 00 01 A8 */	b ifAll_802F366C
ifAll_802F34C8:
/* 802F34C8 002F00A8  3B A0 00 00 */	li r29, 0
/* 802F34CC 002F00AC  1C 1D 00 0C */	mulli r0, r29, 0xc
/* 802F34D0 002F00B0  7F FF 02 14 */	add r31, r31, r0
/* 802F34D4 002F00B4  48 00 00 34 */	b ifAll_802F3508
ifAll_802F34D8:
/* 802F34D8 002F00B8  38 7C 00 00 */	addi r3, r28, 0
/* 802F34DC 002F00BC  4C C6 31 82 */	crclr 6
/* 802F34E0 002F00C0  38 81 00 0C */	addi r4, r1, 0xc
/* 802F34E4 002F00C4  38 BD 00 0B */	addi r5, r29, 0xb
/* 802F34E8 002F00C8  38 C0 FF FF */	li r6, -1
/* 802F34EC 002F00CC  4B D1 E9 39 */	bl lb_80011E24
/* 802F34F0 002F00D0  80 61 00 0C */	lwz r3, 0xc(r1)
/* 802F34F4 002F00D4  38 BF 00 18 */	addi r5, r31, 0x18
/* 802F34F8 002F00D8  38 80 00 00 */	li r4, 0
/* 802F34FC 002F00DC  4B D1 7C D1 */	bl lb_8000B1CC
/* 802F3500 002F00E0  3B FF 00 0C */	addi r31, r31, 0xc
/* 802F3504 002F00E4  3B BD 00 01 */	addi r29, r29, 1
ifAll_802F3508:
/* 802F3508 002F00E8  7C 1D F0 00 */	cmpw r29, r30
/* 802F350C 002F00EC  41 80 FF CC */	blt ifAll_802F34D8
/* 802F3510 002F00F0  48 00 01 5C */	b ifAll_802F366C
ifAll_802F3514:
/* 802F3514 002F00F4  3B A0 00 00 */	li r29, 0
/* 802F3518 002F00F8  1C 1D 00 0C */	mulli r0, r29, 0xc
/* 802F351C 002F00FC  7F FF 02 14 */	add r31, r31, r0
/* 802F3520 002F0100  48 00 00 34 */	b ifAll_802F3554
ifAll_802F3524:
/* 802F3524 002F0104  38 7C 00 00 */	addi r3, r28, 0
/* 802F3528 002F0108  4C C6 31 82 */	crclr 6
/* 802F352C 002F010C  38 81 00 0C */	addi r4, r1, 0xc
/* 802F3530 002F0110  38 BD 00 08 */	addi r5, r29, 8
/* 802F3534 002F0114  38 C0 FF FF */	li r6, -1
/* 802F3538 002F0118  4B D1 E8 ED */	bl lb_80011E24
/* 802F353C 002F011C  80 61 00 0C */	lwz r3, 0xc(r1)
/* 802F3540 002F0120  38 BF 00 18 */	addi r5, r31, 0x18
/* 802F3544 002F0124  38 80 00 00 */	li r4, 0
/* 802F3548 002F0128  4B D1 7C 85 */	bl lb_8000B1CC
/* 802F354C 002F012C  3B FF 00 0C */	addi r31, r31, 0xc
/* 802F3550 002F0130  3B BD 00 01 */	addi r29, r29, 1
ifAll_802F3554:
/* 802F3554 002F0134  7C 1D F0 00 */	cmpw r29, r30
/* 802F3558 002F0138  41 80 FF CC */	blt ifAll_802F3524
/* 802F355C 002F013C  48 00 01 10 */	b ifAll_802F366C
ifAll_802F3560:
/* 802F3560 002F0140  3B A0 00 00 */	li r29, 0
/* 802F3564 002F0144  1C 1D 00 0C */	mulli r0, r29, 0xc
/* 802F3568 002F0148  7F FF 02 14 */	add r31, r31, r0
/* 802F356C 002F014C  48 00 00 34 */	b ifAll_802F35A0
ifAll_802F3570:
/* 802F3570 002F0150  38 7C 00 00 */	addi r3, r28, 0
/* 802F3574 002F0154  4C C6 31 82 */	crclr 6
/* 802F3578 002F0158  38 81 00 0C */	addi r4, r1, 0xc
/* 802F357C 002F015C  38 BD 00 02 */	addi r5, r29, 2
/* 802F3580 002F0160  38 C0 FF FF */	li r6, -1
/* 802F3584 002F0164  4B D1 E8 A1 */	bl lb_80011E24
/* 802F3588 002F0168  80 61 00 0C */	lwz r3, 0xc(r1)
/* 802F358C 002F016C  38 BF 00 18 */	addi r5, r31, 0x18
/* 802F3590 002F0170  38 80 00 00 */	li r4, 0
/* 802F3594 002F0174  4B D1 7C 39 */	bl lb_8000B1CC
/* 802F3598 002F0178  3B FF 00 0C */	addi r31, r31, 0xc
/* 802F359C 002F017C  3B BD 00 01 */	addi r29, r29, 1
ifAll_802F35A0:
/* 802F35A0 002F0180  7C 1D F0 00 */	cmpw r29, r30
/* 802F35A4 002F0184  41 80 FF CC */	blt ifAll_802F3570
/* 802F35A8 002F0188  48 00 00 C4 */	b ifAll_802F366C
ifAll_802F35AC:
/* 802F35AC 002F018C  38 7C 00 00 */	addi r3, r28, 0
/* 802F35B0 002F0190  4C C6 31 82 */	crclr 6
/* 802F35B4 002F0194  38 81 00 0C */	addi r4, r1, 0xc
/* 802F35B8 002F0198  38 A0 00 06 */	li r5, 6
/* 802F35BC 002F019C  38 C0 FF FF */	li r6, -1
/* 802F35C0 002F01A0  4B D1 E8 65 */	bl lb_80011E24
/* 802F35C4 002F01A4  80 61 00 0C */	lwz r3, 0xc(r1)
/* 802F35C8 002F01A8  38 BF 00 18 */	addi r5, r31, 0x18
/* 802F35CC 002F01AC  38 80 00 00 */	li r4, 0
/* 802F35D0 002F01B0  4B D1 7B FD */	bl lb_8000B1CC
/* 802F35D4 002F01B4  C0 3F 00 18 */	lfs f1, 0x18(r31)
/* 802F35D8 002F01B8  7F 83 E3 78 */	mr r3, r28
/* 802F35DC 002F01BC  C0 02 E0 50 */	lfs f0, lbl_804DDA30@sda21(r2)
/* 802F35E0 002F01C0  38 81 00 0C */	addi r4, r1, 0xc
/* 802F35E4 002F01C4  4C C6 31 82 */	crclr 6
/* 802F35E8 002F01C8  EC 01 00 32 */	fmuls f0, f1, f0
/* 802F35EC 002F01CC  38 A0 00 07 */	li r5, 7
/* 802F35F0 002F01D0  38 C0 FF FF */	li r6, -1
/* 802F35F4 002F01D4  D0 1F 00 18 */	stfs f0, 0x18(r31)
/* 802F35F8 002F01D8  4B D1 E8 2D */	bl lb_80011E24
/* 802F35FC 002F01DC  80 61 00 0C */	lwz r3, 0xc(r1)
/* 802F3600 002F01E0  38 BF 00 54 */	addi r5, r31, 0x54
/* 802F3604 002F01E4  38 80 00 00 */	li r4, 0
/* 802F3608 002F01E8  4B D1 7B C5 */	bl lb_8000B1CC
/* 802F360C 002F01EC  C0 1F 00 54 */	lfs f0, 0x54(r31)
/* 802F3610 002F01F0  3B A0 00 01 */	li r29, 1
/* 802F3614 002F01F4  C3 E2 E0 50 */	lfs f31, lbl_804DDA30@sda21(r2)
/* 802F3618 002F01F8  1C 1D 00 0C */	mulli r0, r29, 0xc
/* 802F361C 002F01FC  EC 00 07 F2 */	fmuls f0, f0, f31
/* 802F3620 002F0200  7F DF 02 14 */	add r30, r31, r0
/* 802F3624 002F0204  D0 1F 00 54 */	stfs f0, 0x54(r31)
ifAll_802F3628:
/* 802F3628 002F0208  38 7C 00 00 */	addi r3, r28, 0
/* 802F362C 002F020C  4C C6 31 82 */	crclr 6
/* 802F3630 002F0210  38 81 00 0C */	addi r4, r1, 0xc
/* 802F3634 002F0214  38 BD 00 01 */	addi r5, r29, 1
/* 802F3638 002F0218  38 C0 FF FF */	li r6, -1
/* 802F363C 002F021C  4B D1 E7 E9 */	bl lb_80011E24
/* 802F3640 002F0220  80 61 00 0C */	lwz r3, 0xc(r1)
/* 802F3644 002F0224  38 BE 00 18 */	addi r5, r30, 0x18
/* 802F3648 002F0228  38 80 00 00 */	li r4, 0
/* 802F364C 002F022C  4B D1 7B 81 */	bl lb_8000B1CC
/* 802F3650 002F0230  C0 1E 00 18 */	lfs f0, 0x18(r30)
/* 802F3654 002F0234  3B BD 00 01 */	addi r29, r29, 1
/* 802F3658 002F0238  2C 1D 00 05 */	cmpwi r29, 5
/* 802F365C 002F023C  EC 00 07 F2 */	fmuls f0, f0, f31
/* 802F3660 002F0240  D0 1E 00 18 */	stfs f0, 0x18(r30)
/* 802F3664 002F0244  3B DE 00 0C */	addi r30, r30, 0xc
/* 802F3668 002F0248  41 80 FF C0 */	blt ifAll_802F3628
ifAll_802F366C:
/* 802F366C 002F024C  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 802F3670 002F0250  CB E1 00 20 */	lfd f31, 0x20(r1)
/* 802F3674 002F0254  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 802F3678 002F0258  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 802F367C 002F025C  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 802F3680 002F0260  83 81 00 10 */	lwz r28, 0x10(r1)
/* 802F3684 002F0264  38 21 00 28 */	addi r1, r1, 0x28
/* 802F3688 002F0268  7C 08 03 A6 */	mtlr r0
/* 802F368C 002F026C  4E 80 00 20 */	blr

.global ifAll_802F3690
ifAll_802F3690:
/* 802F3690 002F0270  38 6D B6 BC */	addi r3, r13, lbl_804D6D5C@sda21
/* 802F3694 002F0274  4E 80 00 20 */	blr

.global ifAll_802F3698
ifAll_802F3698:
/* 802F3698 002F0278  38 00 00 01 */	li r0, 1
/* 802F369C 002F027C  98 0D B6 B8 */	stb r0, lbl_804D6D58@sda21(r13)
/* 802F36A0 002F0280  4E 80 00 20 */	blr

.global ifAll_802F36A4
ifAll_802F36A4:
/* 802F36A4 002F0284  38 00 00 00 */	li r0, 0
/* 802F36A8 002F0288  98 0D B6 B8 */	stb r0, lbl_804D6D58@sda21(r13)
/* 802F36AC 002F028C  4E 80 00 20 */	blr

.global ifAll_802F36B0
ifAll_802F36B0:
/* 802F36B0 002F0290  88 6D B6 B8 */	lbz r3, lbl_804D6D58@sda21(r13)
/* 802F36B4 002F0294  4E 80 00 20 */	blr
ifAll_802F36B8:
/* 802F36B8 002F0298  7C 08 02 A6 */	mflr r0
/* 802F36BC 002F029C  90 01 00 04 */	stw r0, 4(r1)
/* 802F36C0 002F02A0  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 802F36C4 002F02A4  93 E1 00 14 */	stw r31, 0x14(r1)
/* 802F36C8 002F02A8  3B E3 00 00 */	addi r31, r3, 0
/* 802F36CC 002F02AC  88 0D B6 B8 */	lbz r0, lbl_804D6D58@sda21(r13)
/* 802F36D0 002F02B0  2C 00 00 00 */	cmpwi r0, 0
/* 802F36D4 002F02B4  40 82 00 24 */	bne ifAll_802F36F8
/* 802F36D8 002F02B8  80 7F 00 28 */	lwz r3, 0x28(r31)
/* 802F36DC 002F02BC  48 07 4D 7D */	bl HSD_CObjSetCurrent
/* 802F36E0 002F02C0  2C 03 00 00 */	cmpwi r3, 0
/* 802F36E4 002F02C4  41 82 00 14 */	beq ifAll_802F36F8
/* 802F36E8 002F02C8  38 7F 00 00 */	addi r3, r31, 0
/* 802F36EC 002F02CC  38 80 00 07 */	li r4, 7
/* 802F36F0 002F02D0  48 09 D7 E1 */	bl func_80390ED0
/* 802F36F4 002F02D4  48 07 4F 15 */	bl HSD_CObjEndCurrent
ifAll_802F36F8:
/* 802F36F8 002F02D8  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 802F36FC 002F02DC  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 802F3700 002F02E0  38 21 00 18 */	addi r1, r1, 0x18
/* 802F3704 002F02E4  7C 08 03 A6 */	mtlr r0
/* 802F3708 002F02E8  4E 80 00 20 */	blr

.global ifAll_802F370C
ifAll_802F370C:
/* 802F370C 002F02EC  7C 08 02 A6 */	mflr r0
/* 802F3710 002F02F0  3C 80 80 4A */	lis r4, lbl_804A0FD8@ha
/* 802F3714 002F02F4  90 01 00 04 */	stw r0, 4(r1)
/* 802F3718 002F02F8  38 A0 00 00 */	li r5, 0
/* 802F371C 002F02FC  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 802F3720 002F0300  BF 61 00 14 */	stmw r27, 0x14(r1)
/* 802F3724 002F0304  3B 63 00 00 */	addi r27, r3, 0
/* 802F3728 002F0308  3B E4 0F D8 */	addi r31, r4, lbl_804A0FD8@l
/* 802F372C 002F030C  38 60 00 0E */	li r3, 0xe
/* 802F3730 002F0310  38 80 00 0F */	li r4, 0xf
/* 802F3734 002F0314  48 09 CA BD */	bl GObj_Create
/* 802F3738 002F0318  80 9B 00 00 */	lwz r4, 0(r27)
/* 802F373C 002F031C  7C 7C 1B 78 */	mr r28, r3
/* 802F3740 002F0320  80 64 00 00 */	lwz r3, 0(r4)
/* 802F3744 002F0324  80 63 00 00 */	lwz r3, 0(r3)
/* 802F3748 002F0328  48 07 D6 FD */	bl HSD_JObjLoadJoint
/* 802F374C 002F032C  3B 63 00 00 */	addi r27, r3, 0
/* 802F3750 002F0330  4C C6 31 82 */	crclr 6
/* 802F3754 002F0334  93 7F 00 08 */	stw r27, 8(r31)
/* 802F3758 002F0338  38 81 00 0C */	addi r4, r1, 0xc
/* 802F375C 002F033C  38 A0 00 0D */	li r5, 0xd
/* 802F3760 002F0340  38 C0 FF FF */	li r6, -1
/* 802F3764 002F0344  4B D1 E6 C1 */	bl lb_80011E24
/* 802F3768 002F0348  80 61 00 0C */	lwz r3, 0xc(r1)
/* 802F376C 002F034C  38 BF 00 0C */	addi r5, r31, 0xc
/* 802F3770 002F0350  38 80 00 00 */	li r4, 0
/* 802F3774 002F0354  4B D1 7A 59 */	bl lb_8000B1CC
/* 802F3778 002F0358  38 7B 00 00 */	addi r3, r27, 0
/* 802F377C 002F035C  4C C6 31 82 */	crclr 6
/* 802F3780 002F0360  38 81 00 0C */	addi r4, r1, 0xc
/* 802F3784 002F0364  38 A0 00 02 */	li r5, 2
/* 802F3788 002F0368  38 C0 FF FF */	li r6, -1
/* 802F378C 002F036C  4B D1 E6 99 */	bl lb_80011E24
/* 802F3790 002F0370  80 61 00 0C */	lwz r3, 0xc(r1)
/* 802F3794 002F0374  38 BF 00 18 */	addi r5, r31, 0x18
/* 802F3798 002F0378  38 80 00 00 */	li r4, 0
/* 802F379C 002F037C  4B D1 7A 31 */	bl lb_8000B1CC
/* 802F37A0 002F0380  38 7B 00 00 */	addi r3, r27, 0
/* 802F37A4 002F0384  4C C6 31 82 */	crclr 6
/* 802F37A8 002F0388  38 81 00 0C */	addi r4, r1, 0xc
/* 802F37AC 002F038C  38 A0 00 03 */	li r5, 3
/* 802F37B0 002F0390  38 C0 FF FF */	li r6, -1
/* 802F37B4 002F0394  4B D1 E6 71 */	bl lb_80011E24
/* 802F37B8 002F0398  80 61 00 0C */	lwz r3, 0xc(r1)
/* 802F37BC 002F039C  38 BF 00 24 */	addi r5, r31, 0x24
/* 802F37C0 002F03A0  38 80 00 00 */	li r4, 0
/* 802F37C4 002F03A4  4B D1 7A 09 */	bl lb_8000B1CC
/* 802F37C8 002F03A8  38 7B 00 00 */	addi r3, r27, 0
/* 802F37CC 002F03AC  4C C6 31 82 */	crclr 6
/* 802F37D0 002F03B0  38 81 00 0C */	addi r4, r1, 0xc
/* 802F37D4 002F03B4  38 A0 00 04 */	li r5, 4
/* 802F37D8 002F03B8  38 C0 FF FF */	li r6, -1
/* 802F37DC 002F03BC  4B D1 E6 49 */	bl lb_80011E24
/* 802F37E0 002F03C0  80 61 00 0C */	lwz r3, 0xc(r1)
/* 802F37E4 002F03C4  38 BF 00 30 */	addi r5, r31, 0x30
/* 802F37E8 002F03C8  38 80 00 00 */	li r4, 0
/* 802F37EC 002F03CC  4B D1 79 E1 */	bl lb_8000B1CC
/* 802F37F0 002F03D0  38 7B 00 00 */	addi r3, r27, 0
/* 802F37F4 002F03D4  4C C6 31 82 */	crclr 6
/* 802F37F8 002F03D8  38 81 00 0C */	addi r4, r1, 0xc
/* 802F37FC 002F03DC  38 A0 00 05 */	li r5, 5
/* 802F3800 002F03E0  38 C0 FF FF */	li r6, -1
/* 802F3804 002F03E4  4B D1 E6 21 */	bl lb_80011E24
/* 802F3808 002F03E8  80 61 00 0C */	lwz r3, 0xc(r1)
/* 802F380C 002F03EC  38 BF 00 3C */	addi r5, r31, 0x3c
/* 802F3810 002F03F0  38 80 00 00 */	li r4, 0
/* 802F3814 002F03F4  4B D1 79 B9 */	bl lb_8000B1CC
/* 802F3818 002F03F8  38 7B 00 00 */	addi r3, r27, 0
/* 802F381C 002F03FC  4C C6 31 82 */	crclr 6
/* 802F3820 002F0400  38 81 00 0C */	addi r4, r1, 0xc
/* 802F3824 002F0404  38 A0 00 06 */	li r5, 6
/* 802F3828 002F0408  38 C0 FF FF */	li r6, -1
/* 802F382C 002F040C  4B D1 E5 F9 */	bl lb_80011E24
/* 802F3830 002F0410  80 61 00 0C */	lwz r3, 0xc(r1)
/* 802F3834 002F0414  38 BF 00 48 */	addi r5, r31, 0x48
/* 802F3838 002F0418  38 80 00 00 */	li r4, 0
/* 802F383C 002F041C  4B D1 79 91 */	bl lb_8000B1CC
/* 802F3840 002F0420  38 7B 00 00 */	addi r3, r27, 0
/* 802F3844 002F0424  4C C6 31 82 */	crclr 6
/* 802F3848 002F0428  38 81 00 0C */	addi r4, r1, 0xc
/* 802F384C 002F042C  38 A0 00 07 */	li r5, 7
/* 802F3850 002F0430  38 C0 FF FF */	li r6, -1
/* 802F3854 002F0434  4B D1 E5 D1 */	bl lb_80011E24
/* 802F3858 002F0438  80 61 00 0C */	lwz r3, 0xc(r1)
/* 802F385C 002F043C  38 BF 00 54 */	addi r5, r31, 0x54
/* 802F3860 002F0440  38 80 00 00 */	li r4, 0
/* 802F3864 002F0444  4B D1 79 69 */	bl lb_8000B1CC
/* 802F3868 002F0448  3B A0 00 00 */	li r29, 0
/* 802F386C 002F044C  1C 1D 00 0C */	mulli r0, r29, 0xc
/* 802F3870 002F0450  7F DF 02 14 */	add r30, r31, r0
ifAll_802F3874:
/* 802F3874 002F0454  38 7B 00 00 */	addi r3, r27, 0
/* 802F3878 002F0458  4C C6 31 82 */	crclr 6
/* 802F387C 002F045C  38 81 00 0C */	addi r4, r1, 0xc
/* 802F3880 002F0460  38 BD 00 08 */	addi r5, r29, 8
/* 802F3884 002F0464  38 C0 FF FF */	li r6, -1
/* 802F3888 002F0468  4B D1 E5 9D */	bl lb_80011E24
/* 802F388C 002F046C  80 61 00 0C */	lwz r3, 0xc(r1)
/* 802F3890 002F0470  38 BE 00 60 */	addi r5, r30, 0x60
/* 802F3894 002F0474  38 80 00 00 */	li r4, 0
/* 802F3898 002F0478  4B D1 79 35 */	bl lb_8000B1CC
/* 802F389C 002F047C  3B BD 00 01 */	addi r29, r29, 1
/* 802F38A0 002F0480  2C 1D 00 03 */	cmpwi r29, 3
/* 802F38A4 002F0484  3B DE 00 0C */	addi r30, r30, 0xc
/* 802F38A8 002F0488  41 80 FF CC */	blt ifAll_802F3874
/* 802F38AC 002F048C  3B A0 00 00 */	li r29, 0
/* 802F38B0 002F0490  1C 1D 00 0C */	mulli r0, r29, 0xc
/* 802F38B4 002F0494  7F DF 02 14 */	add r30, r31, r0
ifAll_802F38B8:
/* 802F38B8 002F0498  38 7B 00 00 */	addi r3, r27, 0
/* 802F38BC 002F049C  4C C6 31 82 */	crclr 6
/* 802F38C0 002F04A0  38 81 00 0C */	addi r4, r1, 0xc
/* 802F38C4 002F04A4  38 BD 00 0B */	addi r5, r29, 0xb
/* 802F38C8 002F04A8  38 C0 FF FF */	li r6, -1
/* 802F38CC 002F04AC  4B D1 E5 59 */	bl lb_80011E24
/* 802F38D0 002F04B0  80 61 00 0C */	lwz r3, 0xc(r1)
/* 802F38D4 002F04B4  38 BE 00 84 */	addi r5, r30, 0x84
/* 802F38D8 002F04B8  38 80 00 00 */	li r4, 0
/* 802F38DC 002F04BC  4B D1 78 F1 */	bl lb_8000B1CC
/* 802F38E0 002F04C0  3B BD 00 01 */	addi r29, r29, 1
/* 802F38E4 002F04C4  2C 1D 00 02 */	cmpwi r29, 2
/* 802F38E8 002F04C8  3B DE 00 0C */	addi r30, r30, 0xc
/* 802F38EC 002F04CC  41 80 FF CC */	blt ifAll_802F38B8
/* 802F38F0 002F04D0  7F 83 E3 78 */	mr r3, r28
/* 802F38F4 002F04D4  48 09 C9 35 */	bl func_80390228
/* 802F38F8 002F04D8  BB 61 00 14 */	lmw r27, 0x14(r1)
/* 802F38FC 002F04DC  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 802F3900 002F04E0  38 21 00 28 */	addi r1, r1, 0x28
/* 802F3904 002F04E4  7C 08 03 A6 */	mtlr r0
/* 802F3908 002F04E8  4E 80 00 20 */	blr

.global ifAll_802F390C
ifAll_802F390C:
/* 802F390C 002F04EC  7C 08 02 A6 */	mflr r0
/* 802F3910 002F04F0  38 8D A0 E0 */	addi r4, r13, lbl_804D5780@sda21
/* 802F3914 002F04F4  90 01 00 04 */	stw r0, 4(r1)
/* 802F3918 002F04F8  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 802F391C 002F04FC  93 E1 00 24 */	stw r31, 0x24(r1)
/* 802F3920 002F0500  3B ED B6 BC */	addi r31, r13, lbl_804D6D5C@sda21
/* 802F3924 002F0504  38 7F 00 00 */	addi r3, r31, 0
/* 802F3928 002F0508  93 C1 00 20 */	stw r30, 0x20(r1)
/* 802F392C 002F050C  3B C0 00 00 */	li r30, 0
/* 802F3930 002F0510  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 802F3934 002F0514  9B CD B6 B8 */	stb r30, lbl_804D6D58@sda21(r13)
/* 802F3938 002F0518  4B D2 36 49 */	bl lbArchive_80016F80
/* 802F393C 002F051C  3C 80 80 40 */	lis r4, lbl_803F94D0@ha
/* 802F3940 002F0520  80 7F 00 00 */	lwz r3, 0(r31)
/* 802F3944 002F0524  38 A4 94 D0 */	addi r5, r4, lbl_803F94D0@l
/* 802F3948 002F0528  4C C6 31 82 */	crclr 6
/* 802F394C 002F052C  38 81 00 14 */	addi r4, r1, 0x14
/* 802F3950 002F0530  38 C0 00 00 */	li r6, 0
/* 802F3954 002F0534  4B D2 31 9D */	bl lbArchive_80016AF0
/* 802F3958 002F0538  80 61 00 14 */	lwz r3, 0x14(r1)
/* 802F395C 002F053C  4B FF FD B1 */	bl ifAll_802F370C
/* 802F3960 002F0540  80 A1 00 14 */	lwz r5, 0x14(r1)
/* 802F3964 002F0544  38 60 00 13 */	li r3, 0x13
/* 802F3968 002F0548  38 80 00 14 */	li r4, 0x14
/* 802F396C 002F054C  80 C5 00 04 */	lwz r6, 4(r5)
/* 802F3970 002F0550  38 A0 00 00 */	li r5, 0
/* 802F3974 002F0554  83 E6 00 00 */	lwz r31, 0(r6)
/* 802F3978 002F0558  48 09 C8 79 */	bl GObj_Create
/* 802F397C 002F055C  3B A3 00 00 */	addi r29, r3, 0
/* 802F3980 002F0560  38 7F 00 00 */	addi r3, r31, 0
/* 802F3984 002F0564  4B D2 01 91 */	bl lb_80013B14
/* 802F3988 002F0568  88 8D C1 AB */	lbz r4, lbl_804D784B@sda21(r13)
/* 802F398C 002F056C  38 A3 00 00 */	addi r5, r3, 0
/* 802F3990 002F0570  38 7D 00 00 */	addi r3, r29, 0
/* 802F3994 002F0574  48 09 D0 DD */	bl func_80390A70
/* 802F3998 002F0578  3C 60 80 2F */	lis r3, ifAll_802F36B8@ha
/* 802F399C 002F057C  38 83 36 B8 */	addi r4, r3, ifAll_802F36B8@l
/* 802F39A0 002F0580  38 7D 00 00 */	addi r3, r29, 0
/* 802F39A4 002F0584  38 A0 00 08 */	li r5, 8
/* 802F39A8 002F0588  48 09 CD B5 */	bl GObj_SetupGXLinkMax
/* 802F39AC 002F058C  38 00 0D 00 */	li r0, 0xd00
/* 802F39B0 002F0590  90 1D 00 24 */	stw r0, 0x24(r29)
/* 802F39B4 002F0594  3C 60 80 4A */	lis r3, lbl_804A0FD8@ha
/* 802F39B8 002F0598  3B E3 0F D8 */	addi r31, r3, lbl_804A0FD8@l
/* 802F39BC 002F059C  93 DD 00 20 */	stw r30, 0x20(r29)
/* 802F39C0 002F05A0  38 60 00 0E */	li r3, 0xe
/* 802F39C4 002F05A4  38 80 00 03 */	li r4, 3
/* 802F39C8 002F05A8  93 BF 00 00 */	stw r29, 0(r31)
/* 802F39CC 002F05AC  38 A0 00 00 */	li r5, 0
/* 802F39D0 002F05B0  80 C1 00 14 */	lwz r6, 0x14(r1)
/* 802F39D4 002F05B4  80 C6 00 08 */	lwz r6, 8(r6)
/* 802F39D8 002F05B8  80 C6 00 00 */	lwz r6, 0(r6)
/* 802F39DC 002F05BC  83 C6 00 00 */	lwz r30, 0(r6)
/* 802F39E0 002F05C0  48 09 C8 11 */	bl GObj_Create
/* 802F39E4 002F05C4  3B A3 00 00 */	addi r29, r3, 0
/* 802F39E8 002F05C8  38 7E 00 00 */	addi r3, r30, 0
/* 802F39EC 002F05CC  48 07 38 F1 */	bl HSD_LObjLoadDesc
/* 802F39F0 002F05D0  88 8D C1 AA */	lbz r4, lbl_804D784A@sda21(r13)
/* 802F39F4 002F05D4  38 A3 00 00 */	addi r5, r3, 0
/* 802F39F8 002F05D8  38 7D 00 00 */	addi r3, r29, 0
/* 802F39FC 002F05DC  48 09 D0 75 */	bl func_80390A70
/* 802F3A00 002F05E0  3C 60 80 39 */	lis r3, lbl_80391044@ha
/* 802F3A04 002F05E4  38 83 10 44 */	addi r4, r3, lbl_80391044@l
/* 802F3A08 002F05E8  38 7D 00 00 */	addi r3, r29, 0
/* 802F3A0C 002F05EC  38 A0 00 0A */	li r5, 0xa
/* 802F3A10 002F05F0  38 C0 00 00 */	li r6, 0
/* 802F3A14 002F05F4  48 09 CC 89 */	bl GObj_SetupGXLink
/* 802F3A18 002F05F8  93 BF 00 04 */	stw r29, 4(r31)
/* 802F3A1C 002F05FC  48 00 37 19 */	bl func_802F7134
/* 802F3A20 002F0600  48 00 2C 85 */	bl func_802F66A4
/* 802F3A24 002F0604  48 00 74 A1 */	bl func_802FAEC4
/* 802F3A28 002F0608  48 00 0D E5 */	bl ifTime_802F480C
/* 802F3A2C 002F060C  48 00 43 F9 */	bl func_802F7E24
/* 802F3A30 002F0610  48 00 8E 41 */	bl func_802FC870
/* 802F3A34 002F0614  48 00 A8 2D */	bl un_802FE260
/* 802F3A38 002F0618  48 00 9C CD */	bl un_802FD704
/* 802F3A3C 002F061C  48 00 9A 8D */	bl un_802FD4C8
/* 802F3A40 002F0620  48 00 B7 75 */	bl un_802FF1B4
/* 802F3A44 002F0624  48 00 BA 55 */	bl un_802FF498
/* 802F3A48 002F0628  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 802F3A4C 002F062C  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 802F3A50 002F0630  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 802F3A54 002F0634  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 802F3A58 002F0638  38 21 00 28 */	addi r1, r1, 0x28
/* 802F3A5C 002F063C  7C 08 03 A6 */	mtlr r0
/* 802F3A60 002F0640  4E 80 00 20 */	blr

.global ifAll_802F3A64
ifAll_802F3A64:
/* 802F3A64 002F0644  7C 08 02 A6 */	mflr r0
/* 802F3A68 002F0648  90 01 00 04 */	stw r0, 4(r1)
/* 802F3A6C 002F064C  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 802F3A70 002F0650  93 E1 00 0C */	stw r31, 0xc(r1)
/* 802F3A74 002F0654  48 00 A9 1D */	bl un_802FE390
/* 802F3A78 002F0658  48 00 79 19 */	bl func_802FB390
/* 802F3A7C 002F065C  48 00 79 A1 */	bl func_802FB41C
/* 802F3A80 002F0660  48 00 7A 05 */	bl func_802FB484
/* 802F3A84 002F0664  48 00 8C CD */	bl func_802FC750
/* 802F3A88 002F0668  48 00 43 F5 */	bl func_802F7E7C
/* 802F3A8C 002F066C  48 00 0D B1 */	bl ifTime_802F483C
/* 802F3A90 002F0670  48 00 2D 75 */	bl func_802F6804
/* 802F3A94 002F0674  48 00 37 8D */	bl func_802F7220
/* 802F3A98 002F0678  3C 60 80 4A */	lis r3, lbl_804A0FD8@ha
/* 802F3A9C 002F067C  3B E3 0F D8 */	addi r31, r3, lbl_804A0FD8@l
/* 802F3AA0 002F0680  80 7F 00 00 */	lwz r3, 0(r31)
/* 802F3AA4 002F0684  28 03 00 00 */	cmplwi r3, 0
/* 802F3AA8 002F0688  41 82 00 08 */	beq ifAll_802F3AB0
/* 802F3AAC 002F068C  48 09 C7 7D */	bl func_80390228
ifAll_802F3AB0:
/* 802F3AB0 002F0690  80 7F 00 04 */	lwz r3, 4(r31)
/* 802F3AB4 002F0694  28 03 00 00 */	cmplwi r3, 0
/* 802F3AB8 002F0698  41 82 00 08 */	beq ifAll_802F3AC0
/* 802F3ABC 002F069C  48 09 C7 6D */	bl func_80390228
ifAll_802F3AC0:
/* 802F3AC0 002F06A0  48 00 99 A9 */	bl un_802FD468
/* 802F3AC4 002F06A4  48 00 9E 49 */	bl un_802FD90C
/* 802F3AC8 002F06A8  48 00 A8 C9 */	bl un_802FE390
/* 802F3ACC 002F06AC  48 00 B6 C5 */	bl un_802FF190
/* 802F3AD0 002F06B0  48 00 BA 2D */	bl un_802FF4FC
/* 802F3AD4 002F06B4  80 01 00 14 */	lwz r0, 0x14(r1)
/* 802F3AD8 002F06B8  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 802F3ADC 002F06BC  38 21 00 10 */	addi r1, r1, 0x10
/* 802F3AE0 002F06C0  7C 08 03 A6 */	mtlr r0
/* 802F3AE4 002F06C4  4E 80 00 20 */	blr


.section .data
    .balign 8
.global lbl_803F94D0
lbl_803F94D0:
    .asciz "ScInfDmg_scene_data"
    .balign 4


.section .bss, "wa"
    .balign 8
.global lbl_804A0FD8
lbl_804A0FD8:
    .skip 0xA0


.section .sdata
    .balign 8
.global lbl_804D5780
lbl_804D5780:
    .asciz "IfAll"
    .balign 4


.section .sbss
    .balign 8
.global lbl_804D6D58
lbl_804D6D58:
    .skip 0x4
.global lbl_804D6D5C
lbl_804D6D5C:
    .skip 0x4


.section .sdata2
    .balign 8
.global lbl_804DDA30
lbl_804DDA30:
    .4byte 0x3F266666
    .4byte 0x00000000
