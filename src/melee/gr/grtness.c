#include "grtness.h"

extern int* stage_info;
extern int* lbl_803E9030;

void GrTNess_802225D0(void)
{
    return;
}

asm void GrTNess_802225D4(void)
{
    nofralloc
/* 802225D4 0021F1B4  7C 08 02 A6 */	mflr r0
/* 802225D8 0021F1B8  3C 60 80 4A */	lis r3, stage_info@ha
/* 802225DC 0021F1BC  90 01 00 04 */	stw r0, 4(r1)
/* 802225E0 0021F1C0  38 63 E6 C8 */	addi r3, r3, stage_info@l
/* 802225E4 0021F1C4  38 A3 00 8C */	addi r5, r3, 0x8c
/* 802225E8 0021F1C8  94 21 FF F8 */	stwu r1, -8(r1)
/* 802225EC 0021F1CC  38 80 00 01 */	li r4, 1
/* 802225F0 0021F1D0  88 03 00 8C */	lbz r0, 0x8c(r3)
/* 802225F4 0021F1D4  38 60 00 00 */	li r3, 0
/* 802225F8 0021F1D8  50 60 1F 38 */	rlwimi r0, r3, 3, 0x1c, 0x1c
/* 802225FC 0021F1DC  98 05 00 00 */	stb r0, 0(r5)
/* 80222600 0021F1E0  38 60 00 00 */	li r3, 0
/* 80222604 0021F1E4  88 05 00 00 */	lbz r0, 0(r5)
/* 80222608 0021F1E8  50 80 17 7A */	rlwimi r0, r4, 2, 0x1d, 0x1d
/* 8022260C 0021F1EC  98 05 00 00 */	stb r0, 0(r5)
/* 80222610 0021F1F0  48 00 00 65 */	bl GrTNess_80222674
/* 80222614 0021F1F4  38 60 00 01 */	li r3, 1
/* 80222618 0021F1F8  48 00 00 5D */	bl GrTNess_80222674
/* 8022261C 0021F1FC  38 60 00 02 */	li r3, 2
/* 80222620 0021F200  48 00 00 55 */	bl GrTNess_80222674
/* 80222624 0021F204  4B FA 13 9D */	bl func_801C39C0
/* 80222628 0021F208  4B FA 15 8D */	bl func_801C3BB4
/* 8022262C 0021F20C  4B FA 1B E5 */	bl func_801C4210
/* 80222630 0021F210  4B FA 1C 7D */	bl func_801C42AC
/* 80222634 0021F214  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80222638 0021F218  38 21 00 08 */	addi r1, r1, 8
/* 8022263C 0021F21C  7C 08 03 A6 */	mtlr r0
/* 80222640 0021F220  4E 80 00 20 */	blr 
}

void GrTNess_80222644(void)
{
    return;
}

#pragma push
#pragma peephole on
void GrTNess_80222648(void)
{
    func_801CAE04(0);
}
#pragma pop

int GrTNess_8022266C(void)
{
    return 0;
}

asm HSD_GObj* GrTNess_80222674(int param_1)
{
    nofralloc
/* 80222674 0021F254  7C 08 02 A6 */	mflr r0
/* 80222678 0021F258  90 01 00 04 */	stw r0, 4(r1)
/* 8022267C 0021F25C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80222680 0021F260  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80222684 0021F264  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80222688 0021F268  93 A1 00 14 */	stw r29, 0x14(r1)
/* 8022268C 0021F26C  93 81 00 10 */	stw r28, 0x10(r1)
/* 80222690 0021F270  3B 83 00 00 */	addi r28, r3, 0
/* 80222694 0021F274  1C 1C 00 14 */	mulli r0, r28, 0x14
/* 80222698 0021F278  3C 60 80 3F */	lis r3, lbl_803E9030@ha
/* 8022269C 0021F27C  3B E3 90 30 */	addi r31, r3, lbl_803E9030@l
/* 802226A0 0021F280  38 7C 00 00 */	addi r3, r28, 0
/* 802226A4 0021F284  7F BF 02 14 */	add r29, r31, r0
/* 802226A8 0021F288  4B F9 EE 29 */	bl func_801C14D0
/* 802226AC 0021F28C  7C 7E 1B 79 */	or. r30, r3, r3
/* 802226B0 0021F290  41 82 00 70 */	beq lbl_80222720
/* 802226B4 0021F294  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 802226B8 0021F298  38 00 00 00 */	li r0, 0
/* 802226BC 0021F29C  3C 60 80 1C */	lis r3, func_801C5DB0@ha
/* 802226C0 0021F2A0  90 1F 00 08 */	stw r0, 8(r31)
/* 802226C4 0021F2A4  38 83 5D B0 */	addi r4, r3, func_801C5DB0@l
/* 802226C8 0021F2A8  38 7E 00 00 */	addi r3, r30, 0
/* 802226CC 0021F2AC  90 1F 00 0C */	stw r0, 0xc(r31)
/* 802226D0 0021F2B0  38 A0 00 03 */	li r5, 3
/* 802226D4 0021F2B4  38 C0 00 00 */	li r6, 0
/* 802226D8 0021F2B8  48 16 DF C5 */	bl GObj_SetupGXLink
/* 802226DC 0021F2BC  80 1D 00 0C */	lwz r0, 0xc(r29)
/* 802226E0 0021F2C0  28 00 00 00 */	cmplwi r0, 0
/* 802226E4 0021F2C4  41 82 00 08 */	beq lbl_802226EC
/* 802226E8 0021F2C8  90 1F 00 1C */	stw r0, 0x1c(r31)
lbl_802226EC:
/* 802226EC 0021F2CC  81 9D 00 00 */	lwz r12, 0(r29)
/* 802226F0 0021F2D0  28 0C 00 00 */	cmplwi r12, 0
/* 802226F4 0021F2D4  41 82 00 10 */	beq lbl_80222704
/* 802226F8 0021F2D8  7D 88 03 A6 */	mtlr r12
/* 802226FC 0021F2DC  38 7E 00 00 */	addi r3, r30, 0
/* 80222700 0021F2E0  4E 80 00 21 */	blrl 
lbl_80222704:
/* 80222704 0021F2E4  80 9D 00 08 */	lwz r4, 8(r29)
/* 80222708 0021F2E8  28 04 00 00 */	cmplwi r4, 0
/* 8022270C 0021F2EC  41 82 00 2C */	beq lbl_80222738
/* 80222710 0021F2F0  38 7E 00 00 */	addi r3, r30, 0
/* 80222714 0021F2F4  38 A0 00 04 */	li r5, 4
/* 80222718 0021F2F8  48 16 D6 3D */	bl func_8038FD54
/* 8022271C 0021F2FC  48 00 00 1C */	b lbl_80222738
lbl_80222720:
/* 80222720 0021F300  38 DC 00 00 */	addi r6, r28, 0
/* 80222724 0021F304  4C C6 31 82 */	crclr 6
/* 80222728 0021F308  38 7F 00 90 */	addi r3, r31, 0x90
/* 8022272C 0021F30C  38 9F 00 B4 */	addi r4, r31, 0xb4
/* 80222730 0021F310  38 A0 00 C3 */	li r5, 0xc3
/* 80222734 0021F314  48 12 2F 75 */	bl OSReport
lbl_80222738:
/* 80222738 0021F318  7F C3 F3 78 */	mr r3, r30
/* 8022273C 0021F31C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80222740 0021F320  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80222744 0021F324  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80222748 0021F328  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 8022274C 0021F32C  83 81 00 10 */	lwz r28, 0x10(r1)
/* 80222750 0021F330  38 21 00 20 */	addi r1, r1, 0x20
/* 80222754 0021F334  7C 08 03 A6 */	mtlr r0
/* 80222758 0021F338  4E 80 00 20 */	blr 
}

asm void GrTNess_8022275C(HSD_GObj* gobj)
{
    nofralloc
/* 8022275C 0021F33C  7C 08 02 A6 */	mflr r0
/* 80222760 0021F340  38 A0 00 00 */	li r5, 0
/* 80222764 0021F344  90 01 00 04 */	stw r0, 4(r1)
/* 80222768 0021F348  94 21 FF F8 */	stwu r1, -8(r1)
/* 8022276C 0021F34C  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 80222770 0021F350  80 84 00 14 */	lwz r4, 0x14(r4)
/* 80222774 0021F354  4B FA 59 C5 */	bl func_801C8138
/* 80222778 0021F358  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8022277C 0021F35C  38 21 00 08 */	addi r1, r1, 8
/* 80222780 0021F360  7C 08 03 A6 */	mtlr r0
/* 80222784 0021F364  4E 80 00 20 */	blr 
}


int GrTNess_80222788(void)
{
    return 0;
}

void GrTNess_80222790(void)
{
    return;
}

void GrTNess_80222794(void)
{
    return;
}

asm void GrTNess_80222798(HSD_GObj* gobj)
{
    nofralloc
/* 80222798 0021F378  7C 08 02 A6 */	mflr r0
/* 8022279C 0021F37C  90 01 00 04 */	stw r0, 4(r1)
/* 802227A0 0021F380  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 802227A4 0021F384  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 802227A8 0021F388  93 C1 00 18 */	stw r30, 0x18(r1)
/* 802227AC 0021F38C  7C 7E 1B 78 */	mr r30, r3
/* 802227B0 0021F390  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 802227B4 0021F394  80 63 00 28 */	lwz r3, 0x28(r3)
/* 802227B8 0021F398  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 802227BC 0021F39C  4B FA 07 15 */	bl func_801C2ED0
/* 802227C0 0021F3A0  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 802227C4 0021F3A4  38 7E 00 00 */	addi r3, r30, 0
/* 802227C8 0021F3A8  38 A0 00 00 */	li r5, 0
/* 802227CC 0021F3AC  4B FA 59 6D */	bl func_801C8138
/* 802227D0 0021F3B0  80 01 00 24 */	lwz r0, 0x24(r1)
/* 802227D4 0021F3B4  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 802227D8 0021F3B8  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 802227DC 0021F3BC  38 21 00 20 */	addi r1, r1, 0x20
/* 802227E0 0021F3C0  7C 08 03 A6 */	mtlr r0
/* 802227E4 0021F3C4  4E 80 00 20 */	blr 
}

int GrTNess_802227E8(void)
{
    return 0;
}

#pragma push
#pragma peephole on
void GrTNess_802227F0(HSD_GObj* gobj)
{
    func_800115F4();
    func_801C2FE0(gobj);
}
#pragma pop

void GrTNess_80222824(void)
{
    return;
}

asm void GrTNess_80222828(HSD_GObj* gobj)
{
    nofralloc
/* 80222828 0021F408  7C 08 02 A6 */	mflr r0
/* 8022282C 0021F40C  90 01 00 04 */	stw r0, 4(r1)
/* 80222830 0021F410  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80222834 0021F414  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80222838 0021F418  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8022283C 0021F41C  7C 7E 1B 78 */	mr r30, r3
/* 80222840 0021F420  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80222844 0021F424  80 63 00 28 */	lwz r3, 0x28(r3)
/* 80222848 0021F428  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 8022284C 0021F42C  4B FA 06 85 */	bl func_801C2ED0
/* 80222850 0021F430  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80222854 0021F434  38 7E 00 00 */	addi r3, r30, 0
/* 80222858 0021F438  38 A0 00 00 */	li r5, 0
/* 8022285C 0021F43C  4B FA 58 DD */	bl func_801C8138
/* 80222860 0021F440  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80222864 0021F444  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80222868 0021F448  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8022286C 0021F44C  38 21 00 20 */	addi r1, r1, 0x20
/* 80222870 0021F450  7C 08 03 A6 */	mtlr r0
/* 80222874 0021F454  4E 80 00 20 */	blr 
}

int GrTNess_80222878(void)
{
    return 0;
}

#pragma push
#pragma peephole on
void GrTNess_80222880(HSD_GObj* gobj)
{
    func_801C2FE0(gobj);
}
#pragma pop

void GrTNess_802228A0(void)
{
    return;
}

int GrTNess_802228A4(void)
{
    return 0;
}

int GrTNess_802228AC(void)
{
    return 1;
}
