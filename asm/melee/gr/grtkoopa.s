.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

.global func_80221648
func_80221648:
/* 80221648 0021E228  4E 80 00 20 */	blr 
.global lbl_8022164C
lbl_8022164C:
/* 8022164C 0021E22C  7C 08 02 A6 */	mflr r0
/* 80221650 0021E230  3C 60 80 4A */	lis r3, stage_info@ha
/* 80221654 0021E234  90 01 00 04 */	stw r0, 4(r1)
/* 80221658 0021E238  38 63 E6 C8 */	addi r3, r3, stage_info@l
/* 8022165C 0021E23C  38 A3 00 8C */	addi r5, r3, 0x8c
/* 80221660 0021E240  94 21 FF F8 */	stwu r1, -8(r1)
/* 80221664 0021E244  38 80 00 01 */	li r4, 1
/* 80221668 0021E248  88 03 00 8C */	lbz r0, 0x8c(r3)
/* 8022166C 0021E24C  38 60 00 00 */	li r3, 0
/* 80221670 0021E250  50 60 1F 38 */	rlwimi r0, r3, 3, 0x1c, 0x1c
/* 80221674 0021E254  98 05 00 00 */	stb r0, 0(r5)
/* 80221678 0021E258  38 60 00 00 */	li r3, 0
/* 8022167C 0021E25C  88 05 00 00 */	lbz r0, 0(r5)
/* 80221680 0021E260  50 80 17 7A */	rlwimi r0, r4, 2, 0x1d, 0x1d
/* 80221684 0021E264  98 05 00 00 */	stb r0, 0(r5)
/* 80221688 0021E268  48 00 00 65 */	bl func_802216EC
/* 8022168C 0021E26C  38 60 00 01 */	li r3, 1
/* 80221690 0021E270  48 00 00 5D */	bl func_802216EC
/* 80221694 0021E274  38 60 00 02 */	li r3, 2
/* 80221698 0021E278  48 00 00 55 */	bl func_802216EC
/* 8022169C 0021E27C  4B FA 23 25 */	bl func_801C39C0
/* 802216A0 0021E280  4B FA 25 15 */	bl func_801C3BB4
/* 802216A4 0021E284  4B FA 2B 6D */	bl func_801C4210
/* 802216A8 0021E288  4B FA 2C 05 */	bl func_801C42AC
/* 802216AC 0021E28C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802216B0 0021E290  38 21 00 08 */	addi r1, r1, 8
/* 802216B4 0021E294  7C 08 03 A6 */	mtlr r0
/* 802216B8 0021E298  4E 80 00 20 */	blr 
.global lbl_802216BC
lbl_802216BC:
/* 802216BC 0021E29C  4E 80 00 20 */	blr 
.global lbl_802216C0
lbl_802216C0:
/* 802216C0 0021E2A0  7C 08 02 A6 */	mflr r0
/* 802216C4 0021E2A4  38 60 00 00 */	li r3, 0
/* 802216C8 0021E2A8  90 01 00 04 */	stw r0, 4(r1)
/* 802216CC 0021E2AC  94 21 FF F8 */	stwu r1, -8(r1)
/* 802216D0 0021E2B0  4B FA 97 35 */	bl func_801CAE04
/* 802216D4 0021E2B4  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802216D8 0021E2B8  38 21 00 08 */	addi r1, r1, 8
/* 802216DC 0021E2BC  7C 08 03 A6 */	mtlr r0
/* 802216E0 0021E2C0  4E 80 00 20 */	blr 
.global lbl_802216E4
lbl_802216E4:
/* 802216E4 0021E2C4  38 60 00 00 */	li r3, 0
/* 802216E8 0021E2C8  4E 80 00 20 */	blr 

.global func_802216EC
func_802216EC:
/* 802216EC 0021E2CC  7C 08 02 A6 */	mflr r0
/* 802216F0 0021E2D0  90 01 00 04 */	stw r0, 4(r1)
/* 802216F4 0021E2D4  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 802216F8 0021E2D8  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 802216FC 0021E2DC  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80221700 0021E2E0  93 A1 00 14 */	stw r29, 0x14(r1)
/* 80221704 0021E2E4  93 81 00 10 */	stw r28, 0x10(r1)
/* 80221708 0021E2E8  3B 83 00 00 */	addi r28, r3, 0
/* 8022170C 0021E2EC  1C 1C 00 14 */	mulli r0, r28, 0x14
/* 80221710 0021E2F0  3C 60 80 3F */	lis r3, lbl_803E8C70@ha
/* 80221714 0021E2F4  3B E3 8C 70 */	addi r31, r3, lbl_803E8C70@l
/* 80221718 0021E2F8  38 7C 00 00 */	addi r3, r28, 0
/* 8022171C 0021E2FC  7F BF 02 14 */	add r29, r31, r0
/* 80221720 0021E300  4B F9 FD B1 */	bl func_801C14D0
/* 80221724 0021E304  7C 7E 1B 79 */	or. r30, r3, r3
/* 80221728 0021E308  41 82 00 70 */	beq lbl_80221798
/* 8022172C 0021E30C  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 80221730 0021E310  38 00 00 00 */	li r0, 0
/* 80221734 0021E314  3C 60 80 1C */	lis r3, func_801C5DB0@ha
/* 80221738 0021E318  90 1F 00 08 */	stw r0, 8(r31)
/* 8022173C 0021E31C  38 83 5D B0 */	addi r4, r3, func_801C5DB0@l
/* 80221740 0021E320  38 7E 00 00 */	addi r3, r30, 0
/* 80221744 0021E324  90 1F 00 0C */	stw r0, 0xc(r31)
/* 80221748 0021E328  38 A0 00 03 */	li r5, 3
/* 8022174C 0021E32C  38 C0 00 00 */	li r6, 0
/* 80221750 0021E330  48 16 EF 4D */	bl func_8039069C
/* 80221754 0021E334  80 1D 00 0C */	lwz r0, 0xc(r29)
/* 80221758 0021E338  28 00 00 00 */	cmplwi r0, 0
/* 8022175C 0021E33C  41 82 00 08 */	beq lbl_80221764
/* 80221760 0021E340  90 1F 00 1C */	stw r0, 0x1c(r31)
lbl_80221764:
/* 80221764 0021E344  81 9D 00 00 */	lwz r12, 0(r29)
/* 80221768 0021E348  28 0C 00 00 */	cmplwi r12, 0
/* 8022176C 0021E34C  41 82 00 10 */	beq lbl_8022177C
/* 80221770 0021E350  7D 88 03 A6 */	mtlr r12
/* 80221774 0021E354  38 7E 00 00 */	addi r3, r30, 0
/* 80221778 0021E358  4E 80 00 21 */	blrl 
lbl_8022177C:
/* 8022177C 0021E35C  80 9D 00 08 */	lwz r4, 8(r29)
/* 80221780 0021E360  28 04 00 00 */	cmplwi r4, 0
/* 80221784 0021E364  41 82 00 2C */	beq lbl_802217B0
/* 80221788 0021E368  38 7E 00 00 */	addi r3, r30, 0
/* 8022178C 0021E36C  38 A0 00 04 */	li r5, 4
/* 80221790 0021E370  48 16 E5 C5 */	bl func_8038FD54
/* 80221794 0021E374  48 00 00 1C */	b lbl_802217B0
lbl_80221798:
/* 80221798 0021E378  38 DC 00 00 */	addi r6, r28, 0
/* 8022179C 0021E37C  4C C6 31 82 */	crclr 6
/* 802217A0 0021E380  38 7F 00 90 */	addi r3, r31, 0x90
/* 802217A4 0021E384  38 9F 00 B4 */	addi r4, r31, 0xb4
/* 802217A8 0021E388  38 A0 00 C3 */	li r5, 0xc3
/* 802217AC 0021E38C  48 12 3E FD */	bl OSReport
lbl_802217B0:
/* 802217B0 0021E390  7F C3 F3 78 */	mr r3, r30
/* 802217B4 0021E394  80 01 00 24 */	lwz r0, 0x24(r1)
/* 802217B8 0021E398  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 802217BC 0021E39C  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 802217C0 0021E3A0  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 802217C4 0021E3A4  83 81 00 10 */	lwz r28, 0x10(r1)
/* 802217C8 0021E3A8  38 21 00 20 */	addi r1, r1, 0x20
/* 802217CC 0021E3AC  7C 08 03 A6 */	mtlr r0
/* 802217D0 0021E3B0  4E 80 00 20 */	blr 
.global lbl_802217D4
lbl_802217D4:
/* 802217D4 0021E3B4  7C 08 02 A6 */	mflr r0
/* 802217D8 0021E3B8  38 A0 00 00 */	li r5, 0
/* 802217DC 0021E3BC  90 01 00 04 */	stw r0, 4(r1)
/* 802217E0 0021E3C0  94 21 FF F8 */	stwu r1, -8(r1)
/* 802217E4 0021E3C4  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 802217E8 0021E3C8  80 84 00 14 */	lwz r4, 0x14(r4)
/* 802217EC 0021E3CC  4B FA 69 4D */	bl func_801C8138
/* 802217F0 0021E3D0  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802217F4 0021E3D4  38 21 00 08 */	addi r1, r1, 8
/* 802217F8 0021E3D8  7C 08 03 A6 */	mtlr r0
/* 802217FC 0021E3DC  4E 80 00 20 */	blr 
.global lbl_80221800
lbl_80221800:
/* 80221800 0021E3E0  38 60 00 00 */	li r3, 0
/* 80221804 0021E3E4  4E 80 00 20 */	blr 
.global lbl_80221808
lbl_80221808:
/* 80221808 0021E3E8  4E 80 00 20 */	blr 
.global lbl_8022180C
lbl_8022180C:
/* 8022180C 0021E3EC  4E 80 00 20 */	blr 
.global lbl_80221810
lbl_80221810:
/* 80221810 0021E3F0  7C 08 02 A6 */	mflr r0
/* 80221814 0021E3F4  90 01 00 04 */	stw r0, 4(r1)
/* 80221818 0021E3F8  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8022181C 0021E3FC  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80221820 0021E400  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80221824 0021E404  7C 7E 1B 78 */	mr r30, r3
/* 80221828 0021E408  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8022182C 0021E40C  80 63 00 28 */	lwz r3, 0x28(r3)
/* 80221830 0021E410  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80221834 0021E414  4B FA 16 9D */	bl func_801C2ED0
/* 80221838 0021E418  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 8022183C 0021E41C  38 7E 00 00 */	addi r3, r30, 0
/* 80221840 0021E420  38 A0 00 00 */	li r5, 0
/* 80221844 0021E424  4B FA 68 F5 */	bl func_801C8138
/* 80221848 0021E428  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8022184C 0021E42C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80221850 0021E430  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80221854 0021E434  38 21 00 20 */	addi r1, r1, 0x20
/* 80221858 0021E438  7C 08 03 A6 */	mtlr r0
/* 8022185C 0021E43C  4E 80 00 20 */	blr 
.global lbl_80221860
lbl_80221860:
/* 80221860 0021E440  38 60 00 00 */	li r3, 0
/* 80221864 0021E444  4E 80 00 20 */	blr 
.global lbl_80221868
lbl_80221868:
/* 80221868 0021E448  7C 08 02 A6 */	mflr r0
/* 8022186C 0021E44C  90 01 00 04 */	stw r0, 4(r1)
/* 80221870 0021E450  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80221874 0021E454  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80221878 0021E458  7C 7F 1B 78 */	mr r31, r3
/* 8022187C 0021E45C  4B DE FD 79 */	bl func_800115F4
/* 80221880 0021E460  7F E3 FB 78 */	mr r3, r31
/* 80221884 0021E464  4B FA 17 5D */	bl func_801C2FE0
/* 80221888 0021E468  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8022188C 0021E46C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80221890 0021E470  38 21 00 18 */	addi r1, r1, 0x18
/* 80221894 0021E474  7C 08 03 A6 */	mtlr r0
/* 80221898 0021E478  4E 80 00 20 */	blr 
.global lbl_8022189C
lbl_8022189C:
/* 8022189C 0021E47C  4E 80 00 20 */	blr 
.global lbl_802218A0
lbl_802218A0:
/* 802218A0 0021E480  7C 08 02 A6 */	mflr r0
/* 802218A4 0021E484  90 01 00 04 */	stw r0, 4(r1)
/* 802218A8 0021E488  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 802218AC 0021E48C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 802218B0 0021E490  93 C1 00 18 */	stw r30, 0x18(r1)
/* 802218B4 0021E494  7C 7E 1B 78 */	mr r30, r3
/* 802218B8 0021E498  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 802218BC 0021E49C  80 63 00 28 */	lwz r3, 0x28(r3)
/* 802218C0 0021E4A0  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 802218C4 0021E4A4  4B FA 16 0D */	bl func_801C2ED0
/* 802218C8 0021E4A8  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 802218CC 0021E4AC  38 7E 00 00 */	addi r3, r30, 0
/* 802218D0 0021E4B0  38 A0 00 00 */	li r5, 0
/* 802218D4 0021E4B4  4B FA 68 65 */	bl func_801C8138
/* 802218D8 0021E4B8  80 01 00 24 */	lwz r0, 0x24(r1)
/* 802218DC 0021E4BC  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 802218E0 0021E4C0  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 802218E4 0021E4C4  38 21 00 20 */	addi r1, r1, 0x20
/* 802218E8 0021E4C8  7C 08 03 A6 */	mtlr r0
/* 802218EC 0021E4CC  4E 80 00 20 */	blr 
.global lbl_802218F0
lbl_802218F0:
/* 802218F0 0021E4D0  38 60 00 00 */	li r3, 0
/* 802218F4 0021E4D4  4E 80 00 20 */	blr 
.global lbl_802218F8
lbl_802218F8:
/* 802218F8 0021E4D8  7C 08 02 A6 */	mflr r0
/* 802218FC 0021E4DC  90 01 00 04 */	stw r0, 4(r1)
/* 80221900 0021E4E0  94 21 FF F8 */	stwu r1, -8(r1)
/* 80221904 0021E4E4  4B FA 16 DD */	bl func_801C2FE0
/* 80221908 0021E4E8  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8022190C 0021E4EC  38 21 00 08 */	addi r1, r1, 8
/* 80221910 0021E4F0  7C 08 03 A6 */	mtlr r0
/* 80221914 0021E4F4  4E 80 00 20 */	blr 
.global lbl_80221918
lbl_80221918:
/* 80221918 0021E4F8  4E 80 00 20 */	blr 
.global lbl_8022191C
lbl_8022191C:
/* 8022191C 0021E4FC  38 60 00 00 */	li r3, 0
/* 80221920 0021E500  4E 80 00 20 */	blr 
.global lbl_80221924
lbl_80221924:
/* 80221924 0021E504  38 60 00 01 */	li r3, 1
/* 80221928 0021E508  4E 80 00 20 */	blr 


.section .data

.global lbl_803E8C70
lbl_803E8C70:
	.4byte lbl_802217D4
	.4byte lbl_80221800
	.4byte lbl_80221808
	.4byte lbl_8022180C
    .4byte NULL
	.4byte lbl_802218A0
	.4byte lbl_802218F0
	.4byte lbl_802218F8
	.4byte lbl_80221918
    .4byte NULL
	.4byte lbl_80221810
	.4byte lbl_80221860
	.4byte lbl_80221868
	.4byte lbl_8022189C
    .4byte 0xC0000000
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
.global lbl_803E8CC0
lbl_803E8CC0:
    .4byte 0x2F477254
    .4byte 0x4B702E64
    .4byte 0x61740000
.global lbl_803E8CCC
lbl_803E8CCC:
    .4byte 0x00000031
    .4byte lbl_803E8C70
    .4byte lbl_803E8CC0
	.4byte lbl_8022164C
	.4byte func_80221648
	.4byte lbl_802216BC
	.4byte lbl_802216C0
	.4byte lbl_802216E4
	.4byte lbl_8022191C
	.4byte lbl_80221924
    .4byte 0x00000001
    .4byte NULL
    .4byte NULL
    .4byte 0x25733A25
    .4byte 0x643A2063
    .4byte 0x6F756C64
    .4byte 0x6E207420
    .4byte 0x67657420
    .4byte 0x676F626A
    .4byte 0x2869643D
    .4byte 0x2564290A
    .4byte NULL
    .4byte 0x6772746B
    .4byte 0x6F6F7061
    .4byte 0x2E630000
