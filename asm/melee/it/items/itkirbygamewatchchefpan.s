.include "macros.inc"

.section .text

.global it_802C74D8
it_802C74D8:
/* 802C74D8 002C40B8  7C 08 02 A6 */	mflr r0
/* 802C74DC 002C40BC  38 E0 00 00 */	li r7, 0
/* 802C74E0 002C40C0  90 01 00 04 */	stw r0, 4(r1)
/* 802C74E4 002C40C4  38 00 00 9C */	li r0, 0x9c
/* 802C74E8 002C40C8  38 C0 00 01 */	li r6, 1
/* 802C74EC 002C40CC  94 21 FF 80 */	stwu r1, -0x80(r1)
/* 802C74F0 002C40D0  93 E1 00 7C */	stw r31, 0x7c(r1)
/* 802C74F4 002C40D4  93 C1 00 78 */	stw r30, 0x78(r1)
/* 802C74F8 002C40D8  7C BE 2B 78 */	mr r30, r5
/* 802C74FC 002C40DC  93 A1 00 74 */	stw r29, 0x74(r1)
/* 802C7500 002C40E0  3B A3 00 00 */	addi r29, r3, 0
/* 802C7504 002C40E4  90 01 00 28 */	stw r0, 0x28(r1)
/* 802C7508 002C40E8  80 64 00 00 */	lwz r3, 0(r4)
/* 802C750C 002C40EC  80 04 00 04 */	lwz r0, 4(r4)
/* 802C7510 002C40F0  90 61 00 40 */	stw r3, 0x40(r1)
/* 802C7514 002C40F4  38 61 00 20 */	addi r3, r1, 0x20
/* 802C7518 002C40F8  90 01 00 44 */	stw r0, 0x44(r1)
/* 802C751C 002C40FC  80 04 00 08 */	lwz r0, 8(r4)
/* 802C7520 002C4100  90 01 00 48 */	stw r0, 0x48(r1)
/* 802C7524 002C4104  80 81 00 40 */	lwz r4, 0x40(r1)
/* 802C7528 002C4108  80 01 00 44 */	lwz r0, 0x44(r1)
/* 802C752C 002C410C  C0 02 D8 F0 */	lfs f0, it_804DD2D0@sda21(r2)
/* 802C7530 002C4110  90 81 00 34 */	stw r4, 0x34(r1)
/* 802C7534 002C4114  90 01 00 38 */	stw r0, 0x38(r1)
/* 802C7538 002C4118  80 01 00 48 */	lwz r0, 0x48(r1)
/* 802C753C 002C411C  90 01 00 3C */	stw r0, 0x3c(r1)
/* 802C7540 002C4120  D0 21 00 58 */	stfs f1, 0x58(r1)
/* 802C7544 002C4124  B0 E1 00 5C */	sth r7, 0x5c(r1)
/* 802C7548 002C4128  D0 01 00 54 */	stfs f0, 0x54(r1)
/* 802C754C 002C412C  D0 01 00 50 */	stfs f0, 0x50(r1)
/* 802C7550 002C4130  D0 01 00 4C */	stfs f0, 0x4c(r1)
/* 802C7554 002C4134  93 A1 00 20 */	stw r29, 0x20(r1)
/* 802C7558 002C4138  80 01 00 20 */	lwz r0, 0x20(r1)
/* 802C755C 002C413C  90 01 00 24 */	stw r0, 0x24(r1)
/* 802C7560 002C4140  88 01 00 64 */	lbz r0, 0x64(r1)
/* 802C7564 002C4144  50 C0 3E 30 */	rlwimi r0, r6, 7, 0x18, 0x18
/* 802C7568 002C4148  98 01 00 64 */	stb r0, 0x64(r1)
/* 802C756C 002C414C  90 E1 00 60 */	stw r7, 0x60(r1)
/* 802C7570 002C4150  4B FA 15 A9 */	bl Item_80268B18
/* 802C7574 002C4154  7C 7F 1B 79 */	or. r31, r3, r3
/* 802C7578 002C4158  41 82 00 44 */	beq .L_802C75BC
/* 802C757C 002C415C  80 BF 00 2C */	lwz r5, 0x2c(r31)
/* 802C7580 002C4160  38 7F 00 00 */	addi r3, r31, 0
/* 802C7584 002C4164  38 9D 00 00 */	addi r4, r29, 0
/* 802C7588 002C4168  80 C5 00 C4 */	lwz r6, 0xc4(r5)
/* 802C758C 002C416C  7F C5 F3 78 */	mr r5, r30
/* 802C7590 002C4170  83 C6 00 04 */	lwz r30, 4(r6)
/* 802C7594 002C4174  4B FA 35 C1 */	bl Item_8026AB54
/* 802C7598 002C4178  38 7F 00 00 */	addi r3, r31, 0
/* 802C759C 002C417C  38 9D 00 00 */	addi r4, r29, 0
/* 802C75A0 002C4180  4B F5 E8 39 */	bl db_80225DD8
/* 802C75A4 002C4184  80 BE 00 00 */	lwz r5, 0(r30)
/* 802C75A8 002C4188  38 7F 00 00 */	addi r3, r31, 0
/* 802C75AC 002C418C  38 9D 00 00 */	addi r4, r29, 0
/* 802C75B0 002C4190  4B FB 58 B5 */	bl it_8027CE64
/* 802C75B4 002C4194  7F E3 FB 78 */	mr r3, r31
/* 802C75B8 002C4198  48 00 00 08 */	b .L_802C75C0
.L_802C75BC:
/* 802C75BC 002C419C  38 60 00 00 */	li r3, 0
.L_802C75C0:
/* 802C75C0 002C41A0  80 01 00 84 */	lwz r0, 0x84(r1)
/* 802C75C4 002C41A4  83 E1 00 7C */	lwz r31, 0x7c(r1)
/* 802C75C8 002C41A8  83 C1 00 78 */	lwz r30, 0x78(r1)
/* 802C75CC 002C41AC  83 A1 00 74 */	lwz r29, 0x74(r1)
/* 802C75D0 002C41B0  38 21 00 80 */	addi r1, r1, 0x80
/* 802C75D4 002C41B4  7C 08 03 A6 */	mtlr r0
/* 802C75D8 002C41B8  4E 80 00 20 */	blr

.global it_802C75DC
it_802C75DC:
/* 802C75DC 002C41BC  7C 08 02 A6 */	mflr r0
/* 802C75E0 002C41C0  90 01 00 04 */	stw r0, 4(r1)
/* 802C75E4 002C41C4  94 21 FF F8 */	stwu r1, -8(r1)
/* 802C75E8 002C41C8  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 802C75EC 002C41CC  80 63 05 18 */	lwz r3, 0x518(r3)
/* 802C75F0 002C41D0  28 03 00 00 */	cmplwi r3, 0
/* 802C75F4 002C41D4  41 82 00 08 */	beq .L_802C75FC
/* 802C75F8 002C41D8  4B E4 5A 7D */	bl ftKb_SpecialNGw_8010D074
.L_802C75FC:
/* 802C75FC 002C41DC  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802C7600 002C41E0  38 21 00 08 */	addi r1, r1, 8
/* 802C7604 002C41E4  7C 08 03 A6 */	mtlr r0
/* 802C7608 002C41E8  4E 80 00 20 */	blr

.global it_802C760C
it_802C760C:
/* 802C760C 002C41EC  7C 08 02 A6 */	mflr r0
/* 802C7610 002C41F0  90 01 00 04 */	stw r0, 4(r1)
/* 802C7614 002C41F4  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 802C7618 002C41F8  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 802C761C 002C41FC  7C 7F 1B 78 */	mr r31, r3
/* 802C7620 002C4200  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 802C7624 002C4204  28 03 00 00 */	cmplwi r3, 0
/* 802C7628 002C4208  41 82 00 1C */	beq .L_802C7644
/* 802C762C 002C420C  80 63 05 18 */	lwz r3, 0x518(r3)
/* 802C7630 002C4210  28 03 00 00 */	cmplwi r3, 0
/* 802C7634 002C4214  41 82 00 08 */	beq .L_802C763C
/* 802C7638 002C4218  4B E4 5A 3D */	bl ftKb_SpecialNGw_8010D074
.L_802C763C:
/* 802C763C 002C421C  7F E3 FB 78 */	mr r3, r31
/* 802C7640 002C4220  4B FA 32 AD */	bl Item_8026A8EC
.L_802C7644:
/* 802C7644 002C4224  80 01 00 24 */	lwz r0, 0x24(r1)
/* 802C7648 002C4228  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 802C764C 002C422C  38 21 00 20 */	addi r1, r1, 0x20
/* 802C7650 002C4230  7C 08 03 A6 */	mtlr r0
/* 802C7654 002C4234  4E 80 00 20 */	blr

.global it_802C7658
it_802C7658:
/* 802C7658 002C4238  7C 08 02 A6 */	mflr r0
/* 802C765C 002C423C  90 01 00 04 */	stw r0, 4(r1)
/* 802C7660 002C4240  94 21 FF F8 */	stwu r1, -8(r1)
/* 802C7664 002C4244  4B FA 40 C1 */	bl it_8026B724
/* 802C7668 002C4248  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802C766C 002C424C  38 21 00 08 */	addi r1, r1, 8
/* 802C7670 002C4250  7C 08 03 A6 */	mtlr r0
/* 802C7674 002C4254  4E 80 00 20 */	blr

.global it_802C7678
it_802C7678:
/* 802C7678 002C4258  7C 08 02 A6 */	mflr r0
/* 802C767C 002C425C  90 01 00 04 */	stw r0, 4(r1)
/* 802C7680 002C4260  94 21 FF F8 */	stwu r1, -8(r1)
/* 802C7684 002C4264  4B FA 40 B9 */	bl it_8026B73C
/* 802C7688 002C4268  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802C768C 002C426C  38 21 00 08 */	addi r1, r1, 8
/* 802C7690 002C4270  7C 08 03 A6 */	mtlr r0
/* 802C7694 002C4274  4E 80 00 20 */	blr

.global it_802C7698
it_802C7698:
/* 802C7698 002C4278  7C 08 02 A6 */	mflr r0
/* 802C769C 002C427C  90 01 00 04 */	stw r0, 4(r1)
/* 802C76A0 002C4280  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 802C76A4 002C4284  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 802C76A8 002C4288  7C 7F 1B 78 */	mr r31, r3
/* 802C76AC 002C428C  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 802C76B0 002C4290  80 03 05 18 */	lwz r0, 0x518(r3)
/* 802C76B4 002C4294  28 00 00 00 */	cmplwi r0, 0
/* 802C76B8 002C4298  41 82 00 1C */	beq .L_802C76D4
/* 802C76BC 002C429C  38 7F 00 00 */	addi r3, r31, 0
/* 802C76C0 002C42A0  38 80 00 00 */	li r4, 0
/* 802C76C4 002C42A4  38 A0 00 02 */	li r5, 2
/* 802C76C8 002C42A8  4B FA 17 95 */	bl Item_80268E5C
/* 802C76CC 002C42AC  7F E3 FB 78 */	mr r3, r31
/* 802C76D0 002C42B0  4B FA 1D FD */	bl Item_802694CC
.L_802C76D4:
/* 802C76D4 002C42B4  80 01 00 24 */	lwz r0, 0x24(r1)
/* 802C76D8 002C42B8  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 802C76DC 002C42BC  38 21 00 20 */	addi r1, r1, 0x20
/* 802C76E0 002C42C0  7C 08 03 A6 */	mtlr r0
/* 802C76E4 002C42C4  4E 80 00 20 */	blr

.global it_802C76E8
it_802C76E8:
/* 802C76E8 002C42C8  7C 08 02 A6 */	mflr r0
/* 802C76EC 002C42CC  90 01 00 04 */	stw r0, 4(r1)
/* 802C76F0 002C42D0  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 802C76F4 002C42D4  93 E1 00 24 */	stw r31, 0x24(r1)
/* 802C76F8 002C42D8  7C 7F 1B 78 */	mr r31, r3
/* 802C76FC 002C42DC  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 802C7700 002C42E0  80 63 05 18 */	lwz r3, 0x518(r3)
/* 802C7704 002C42E4  28 03 00 00 */	cmplwi r3, 0
/* 802C7708 002C42E8  41 82 00 0C */	beq .L_802C7714
/* 802C770C 002C42EC  4B E4 5A 55 */	bl ftKb_SpecialNGw_8010D160
/* 802C7710 002C42F0  48 00 00 08 */	b .L_802C7718
.L_802C7714:
/* 802C7714 002C42F4  38 60 00 01 */	li r3, 1
.L_802C7718:
/* 802C7718 002C42F8  2C 03 00 00 */	cmpwi r3, 0
/* 802C771C 002C42FC  41 82 00 20 */	beq .L_802C773C
/* 802C7720 002C4300  80 7F 00 2C */	lwz r3, 0x2c(r31)
/* 802C7724 002C4304  80 63 05 18 */	lwz r3, 0x518(r3)
/* 802C7728 002C4308  28 03 00 00 */	cmplwi r3, 0
/* 802C772C 002C430C  41 82 00 08 */	beq .L_802C7734
/* 802C7730 002C4310  4B E4 59 45 */	bl ftKb_SpecialNGw_8010D074
.L_802C7734:
/* 802C7734 002C4314  38 60 00 01 */	li r3, 1
/* 802C7738 002C4318  48 00 00 08 */	b .L_802C7740
.L_802C773C:
/* 802C773C 002C431C  38 60 00 00 */	li r3, 0
.L_802C7740:
/* 802C7740 002C4320  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 802C7744 002C4324  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 802C7748 002C4328  38 21 00 28 */	addi r1, r1, 0x28
/* 802C774C 002C432C  7C 08 03 A6 */	mtlr r0
/* 802C7750 002C4330  4E 80 00 20 */	blr

.global it_802C7754
it_802C7754:
/* 802C7754 002C4334  7C 08 02 A6 */	mflr r0
/* 802C7758 002C4338  90 01 00 04 */	stw r0, 4(r1)
/* 802C775C 002C433C  94 21 FF F8 */	stwu r1, -8(r1)
/* 802C7760 002C4340  4B FA 41 35 */	bl it_8026B894
/* 802C7764 002C4344  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802C7768 002C4348  38 21 00 08 */	addi r1, r1, 8
/* 802C776C 002C434C  7C 08 03 A6 */	mtlr r0
/* 802C7770 002C4350  4E 80 00 20 */	blr


.section .data
    .balign 8
.global it_803F7958
it_803F7958:
    .4byte -1
    .4byte it_802C76E8
    .4byte NULL
    .4byte NULL


.section .sdata2
    .balign 8
.global it_804DD2D0
it_804DD2D0:
    .4byte 0x00000000
