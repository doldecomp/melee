.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

.global func_80223580
func_80223580:
/* 80223580 00220160  4E 80 00 20 */	blr
.global lbl_80223584
lbl_80223584:
/* 80223584 00220164  7C 08 02 A6 */	mflr r0
/* 80223588 00220168  3C 60 80 4A */	lis r3, stage_info@ha
/* 8022358C 0022016C  90 01 00 04 */	stw r0, 4(r1)
/* 80223590 00220170  38 63 E6 C8 */	addi r3, r3, stage_info@l
/* 80223594 00220174  38 A3 00 8C */	addi r5, r3, 0x8c
/* 80223598 00220178  94 21 FF F8 */	stwu r1, -8(r1)
/* 8022359C 0022017C  38 80 00 01 */	li r4, 1
/* 802235A0 00220180  88 03 00 8C */	lbz r0, 0x8c(r3)
/* 802235A4 00220184  38 60 00 00 */	li r3, 0
/* 802235A8 00220188  50 60 1F 38 */	rlwimi r0, r3, 3, 0x1c, 0x1c
/* 802235AC 0022018C  98 05 00 00 */	stb r0, 0(r5)
/* 802235B0 00220190  38 60 00 00 */	li r3, 0
/* 802235B4 00220194  88 05 00 00 */	lbz r0, 0(r5)
/* 802235B8 00220198  50 80 17 7A */	rlwimi r0, r4, 2, 0x1d, 0x1d
/* 802235BC 0022019C  98 05 00 00 */	stb r0, 0(r5)
/* 802235C0 002201A0  48 00 00 65 */	bl func_80223624
/* 802235C4 002201A4  38 60 00 01 */	li r3, 1
/* 802235C8 002201A8  48 00 00 5D */	bl func_80223624
/* 802235CC 002201AC  38 60 00 02 */	li r3, 2
/* 802235D0 002201B0  48 00 00 55 */	bl func_80223624
/* 802235D4 002201B4  4B FA 03 ED */	bl Ground_801C39C0
/* 802235D8 002201B8  4B FA 05 DD */	bl Ground_801C3BB4
/* 802235DC 002201BC  4B FA 0C 35 */	bl Ground_801C4210
/* 802235E0 002201C0  4B FA 0C CD */	bl Ground_801C42AC
/* 802235E4 002201C4  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802235E8 002201C8  38 21 00 08 */	addi r1, r1, 8
/* 802235EC 002201CC  7C 08 03 A6 */	mtlr r0
/* 802235F0 002201D0  4E 80 00 20 */	blr
.global lbl_802235F4
lbl_802235F4:
/* 802235F4 002201D4  4E 80 00 20 */	blr
.global lbl_802235F8
lbl_802235F8:
/* 802235F8 002201D8  7C 08 02 A6 */	mflr r0
/* 802235FC 002201DC  38 60 00 00 */	li r3, 0
/* 80223600 002201E0  90 01 00 04 */	stw r0, 4(r1)
/* 80223604 002201E4  94 21 FF F8 */	stwu r1, -8(r1)
/* 80223608 002201E8  4B FA 77 FD */	bl func_801CAE04
/* 8022360C 002201EC  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80223610 002201F0  38 21 00 08 */	addi r1, r1, 8
/* 80223614 002201F4  7C 08 03 A6 */	mtlr r0
/* 80223618 002201F8  4E 80 00 20 */	blr
.global lbl_8022361C
lbl_8022361C:
/* 8022361C 002201FC  38 60 00 00 */	li r3, 0
/* 80223620 00220200  4E 80 00 20 */	blr

.global func_80223624
func_80223624:
/* 80223624 00220204  7C 08 02 A6 */	mflr r0
/* 80223628 00220208  90 01 00 04 */	stw r0, 4(r1)
/* 8022362C 0022020C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80223630 00220210  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80223634 00220214  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80223638 00220218  93 A1 00 14 */	stw r29, 0x14(r1)
/* 8022363C 0022021C  93 81 00 10 */	stw r28, 0x10(r1)
/* 80223640 00220220  3B 83 00 00 */	addi r28, r3, 0
/* 80223644 00220224  1C 1C 00 14 */	mulli r0, r28, 0x14
/* 80223648 00220228  3C 60 80 3F */	lis r3, lbl_803E93F8@ha
/* 8022364C 0022022C  3B E3 93 F8 */	addi r31, r3, lbl_803E93F8@l
/* 80223650 00220230  38 7C 00 00 */	addi r3, r28, 0
/* 80223654 00220234  7F BF 02 14 */	add r29, r31, r0
/* 80223658 00220238  4B F9 DE 79 */	bl Ground_801C14D0
/* 8022365C 0022023C  7C 7E 1B 79 */	or. r30, r3, r3
/* 80223660 00220240  41 82 00 70 */	beq lbl_802236D0
/* 80223664 00220244  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 80223668 00220248  38 00 00 00 */	li r0, 0
/* 8022366C 0022024C  3C 60 80 1C */	lis r3, grDisplay_801C5DB0@ha
/* 80223670 00220250  90 1F 00 08 */	stw r0, 8(r31)
/* 80223674 00220254  38 83 5D B0 */	addi r4, r3, grDisplay_801C5DB0@l
/* 80223678 00220258  38 7E 00 00 */	addi r3, r30, 0
/* 8022367C 0022025C  90 1F 00 0C */	stw r0, 0xc(r31)
/* 80223680 00220260  38 A0 00 03 */	li r5, 3
/* 80223684 00220264  38 C0 00 00 */	li r6, 0
/* 80223688 00220268  48 16 D0 15 */	bl GObj_SetupGXLink
/* 8022368C 0022026C  80 1D 00 0C */	lwz r0, 0xc(r29)
/* 80223690 00220270  28 00 00 00 */	cmplwi r0, 0
/* 80223694 00220274  41 82 00 08 */	beq lbl_8022369C
/* 80223698 00220278  90 1F 00 1C */	stw r0, 0x1c(r31)
lbl_8022369C:
/* 8022369C 0022027C  81 9D 00 00 */	lwz r12, 0(r29)
/* 802236A0 00220280  28 0C 00 00 */	cmplwi r12, 0
/* 802236A4 00220284  41 82 00 10 */	beq lbl_802236B4
/* 802236A8 00220288  7D 88 03 A6 */	mtlr r12
/* 802236AC 0022028C  38 7E 00 00 */	addi r3, r30, 0
/* 802236B0 00220290  4E 80 00 21 */	blrl
lbl_802236B4:
/* 802236B4 00220294  80 9D 00 08 */	lwz r4, 8(r29)
/* 802236B8 00220298  28 04 00 00 */	cmplwi r4, 0
/* 802236BC 0022029C  41 82 00 2C */	beq lbl_802236E8
/* 802236C0 002202A0  38 7E 00 00 */	addi r3, r30, 0
/* 802236C4 002202A4  38 A0 00 04 */	li r5, 4
/* 802236C8 002202A8  48 16 C6 8D */	bl func_8038FD54
/* 802236CC 002202AC  48 00 00 1C */	b lbl_802236E8
lbl_802236D0:
/* 802236D0 002202B0  38 DC 00 00 */	addi r6, r28, 0
/* 802236D4 002202B4  4C C6 31 82 */	crclr 6
/* 802236D8 002202B8  38 7F 00 90 */	addi r3, r31, 0x90
/* 802236DC 002202BC  38 9F 00 B4 */	addi r4, r31, 0xb4
/* 802236E0 002202C0  38 A0 00 C3 */	li r5, 0xc3
/* 802236E4 002202C4  48 12 1F C5 */	bl OSReport
lbl_802236E8:
/* 802236E8 002202C8  7F C3 F3 78 */	mr r3, r30
/* 802236EC 002202CC  80 01 00 24 */	lwz r0, 0x24(r1)
/* 802236F0 002202D0  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 802236F4 002202D4  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 802236F8 002202D8  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 802236FC 002202DC  83 81 00 10 */	lwz r28, 0x10(r1)
/* 80223700 002202E0  38 21 00 20 */	addi r1, r1, 0x20
/* 80223704 002202E4  7C 08 03 A6 */	mtlr r0
/* 80223708 002202E8  4E 80 00 20 */	blr
.global lbl_8022370C
lbl_8022370C:
/* 8022370C 002202EC  7C 08 02 A6 */	mflr r0
/* 80223710 002202F0  38 A0 00 00 */	li r5, 0
/* 80223714 002202F4  90 01 00 04 */	stw r0, 4(r1)
/* 80223718 002202F8  94 21 FF F8 */	stwu r1, -8(r1)
/* 8022371C 002202FC  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 80223720 00220300  80 84 00 14 */	lwz r4, 0x14(r4)
/* 80223724 00220304  4B FA 4A 15 */	bl grAnime_801C8138
/* 80223728 00220308  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8022372C 0022030C  38 21 00 08 */	addi r1, r1, 8
/* 80223730 00220310  7C 08 03 A6 */	mtlr r0
/* 80223734 00220314  4E 80 00 20 */	blr
.global lbl_80223738
lbl_80223738:
/* 80223738 00220318  38 60 00 00 */	li r3, 0
/* 8022373C 0022031C  4E 80 00 20 */	blr
.global lbl_80223740
lbl_80223740:
/* 80223740 00220320  4E 80 00 20 */	blr
.global lbl_80223744
lbl_80223744:
/* 80223744 00220324  4E 80 00 20 */	blr
.global lbl_80223748
lbl_80223748:
/* 80223748 00220328  7C 08 02 A6 */	mflr r0
/* 8022374C 0022032C  90 01 00 04 */	stw r0, 4(r1)
/* 80223750 00220330  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80223754 00220334  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80223758 00220338  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8022375C 0022033C  7C 7E 1B 78 */	mr r30, r3
/* 80223760 00220340  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80223764 00220344  80 63 00 28 */	lwz r3, 0x28(r3)
/* 80223768 00220348  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 8022376C 0022034C  4B F9 F7 65 */	bl Ground_801C2ED0
/* 80223770 00220350  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80223774 00220354  38 7E 00 00 */	addi r3, r30, 0
/* 80223778 00220358  38 A0 00 00 */	li r5, 0
/* 8022377C 0022035C  4B FA 49 BD */	bl grAnime_801C8138
/* 80223780 00220360  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80223784 00220364  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80223788 00220368  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8022378C 0022036C  38 21 00 20 */	addi r1, r1, 0x20
/* 80223790 00220370  7C 08 03 A6 */	mtlr r0
/* 80223794 00220374  4E 80 00 20 */	blr
.global lbl_80223798
lbl_80223798:
/* 80223798 00220378  38 60 00 00 */	li r3, 0
/* 8022379C 0022037C  4E 80 00 20 */	blr
.global lbl_802237A0
lbl_802237A0:
/* 802237A0 00220380  7C 08 02 A6 */	mflr r0
/* 802237A4 00220384  90 01 00 04 */	stw r0, 4(r1)
/* 802237A8 00220388  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 802237AC 0022038C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 802237B0 00220390  7C 7F 1B 78 */	mr r31, r3
/* 802237B4 00220394  4B DE DE 41 */	bl func_800115F4
/* 802237B8 00220398  7F E3 FB 78 */	mr r3, r31
/* 802237BC 0022039C  4B F9 F8 25 */	bl Ground_801C2FE0
/* 802237C0 002203A0  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 802237C4 002203A4  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 802237C8 002203A8  38 21 00 18 */	addi r1, r1, 0x18
/* 802237CC 002203AC  7C 08 03 A6 */	mtlr r0
/* 802237D0 002203B0  4E 80 00 20 */	blr
.global lbl_802237D4
lbl_802237D4:
/* 802237D4 002203B4  4E 80 00 20 */	blr
.global lbl_802237D8
lbl_802237D8:
/* 802237D8 002203B8  7C 08 02 A6 */	mflr r0
/* 802237DC 002203BC  90 01 00 04 */	stw r0, 4(r1)
/* 802237E0 002203C0  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 802237E4 002203C4  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 802237E8 002203C8  93 C1 00 18 */	stw r30, 0x18(r1)
/* 802237EC 002203CC  7C 7E 1B 78 */	mr r30, r3
/* 802237F0 002203D0  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 802237F4 002203D4  80 63 00 28 */	lwz r3, 0x28(r3)
/* 802237F8 002203D8  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 802237FC 002203DC  4B F9 F6 D5 */	bl Ground_801C2ED0
/* 80223800 002203E0  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80223804 002203E4  38 7E 00 00 */	addi r3, r30, 0
/* 80223808 002203E8  38 A0 00 00 */	li r5, 0
/* 8022380C 002203EC  4B FA 49 2D */	bl grAnime_801C8138
/* 80223810 002203F0  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80223814 002203F4  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80223818 002203F8  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8022381C 002203FC  38 21 00 20 */	addi r1, r1, 0x20
/* 80223820 00220400  7C 08 03 A6 */	mtlr r0
/* 80223824 00220404  4E 80 00 20 */	blr
.global lbl_80223828
lbl_80223828:
/* 80223828 00220408  38 60 00 00 */	li r3, 0
/* 8022382C 0022040C  4E 80 00 20 */	blr
.global lbl_80223830
lbl_80223830:
/* 80223830 00220410  7C 08 02 A6 */	mflr r0
/* 80223834 00220414  90 01 00 04 */	stw r0, 4(r1)
/* 80223838 00220418  94 21 FF F8 */	stwu r1, -8(r1)
/* 8022383C 0022041C  4B F9 F7 A5 */	bl Ground_801C2FE0
/* 80223840 00220420  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80223844 00220424  38 21 00 08 */	addi r1, r1, 8
/* 80223848 00220428  7C 08 03 A6 */	mtlr r0
/* 8022384C 0022042C  4E 80 00 20 */	blr
.global lbl_80223850
lbl_80223850:
/* 80223850 00220430  4E 80 00 20 */	blr
.global lbl_80223854
lbl_80223854:
/* 80223854 00220434  38 60 00 00 */	li r3, 0
/* 80223858 00220438  4E 80 00 20 */	blr
.global lbl_8022385C
lbl_8022385C:
/* 8022385C 0022043C  38 60 00 01 */	li r3, 1
/* 80223860 00220440  4E 80 00 20 */	blr


.section .data
    .balign 8
.global lbl_803E93F8
lbl_803E93F8:
    .4byte lbl_8022370C
    .4byte lbl_80223738
    .4byte lbl_80223740
    .4byte lbl_80223744
    .4byte NULL
    .4byte lbl_802237D8
    .4byte lbl_80223828
    .4byte lbl_80223830
    .4byte lbl_80223850
    .4byte NULL
    .4byte lbl_80223748
    .4byte lbl_80223798
    .4byte lbl_802237A0
    .4byte lbl_802237D4
    .4byte 0xC0000000
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
.global lbl_803E9448
lbl_803E9448:
    .asciz "/GrTSs.dat"
    .balign 4
.global lbl_803E9454
lbl_803E9454:
    .4byte 0x0000003B
    .4byte lbl_803E93F8
    .4byte lbl_803E9448
    .4byte lbl_80223584
    .4byte func_80223580
    .4byte lbl_802235F4
    .4byte lbl_802235F8
    .4byte lbl_8022361C
    .4byte lbl_80223854
    .4byte lbl_8022385C
    .4byte 0x00000001
    .4byte NULL
    .4byte NULL
    .asciz "%s:%d: couldn t get gobj(id=%d)\n"
    .balign 4
    .asciz "grtsamus.c"
