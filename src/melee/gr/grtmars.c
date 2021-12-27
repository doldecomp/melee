#include "grtmars.h"

extern int* stage_info;
extern int* lbl_803E8EB0;

void GrTMars_80221EF4(void)
{
    return;
}

asm void GrTMars_80221EF8(void)
{
    nofralloc
/* 80221EF8 0021EAD8  7C 08 02 A6 */	mflr r0
/* 80221EFC 0021EADC  3C 60 80 4A */	lis r3, stage_info@ha
/* 80221F00 0021EAE0  90 01 00 04 */	stw r0, 4(r1)
/* 80221F04 0021EAE4  38 63 E6 C8 */	addi r3, r3, stage_info@l
/* 80221F08 0021EAE8  38 A3 00 8C */	addi r5, r3, 0x8c
/* 80221F0C 0021EAEC  94 21 FF F8 */	stwu r1, -8(r1)
/* 80221F10 0021EAF0  38 80 00 01 */	li r4, 1
/* 80221F14 0021EAF4  88 03 00 8C */	lbz r0, 0x8c(r3)
/* 80221F18 0021EAF8  38 60 00 00 */	li r3, 0
/* 80221F1C 0021EAFC  50 60 1F 38 */	rlwimi r0, r3, 3, 0x1c, 0x1c
/* 80221F20 0021EB00  98 05 00 00 */	stb r0, 0(r5)
/* 80221F24 0021EB04  38 60 00 00 */	li r3, 0
/* 80221F28 0021EB08  88 05 00 00 */	lbz r0, 0(r5)
/* 80221F2C 0021EB0C  50 80 17 7A */	rlwimi r0, r4, 2, 0x1d, 0x1d
/* 80221F30 0021EB10  98 05 00 00 */	stb r0, 0(r5)
/* 80221F34 0021EB14  48 00 00 65 */	bl GrTMars_80221F98
/* 80221F38 0021EB18  38 60 00 01 */	li r3, 1
/* 80221F3C 0021EB1C  48 00 00 5D */	bl GrTMars_80221F98
/* 80221F40 0021EB20  38 60 00 02 */	li r3, 2
/* 80221F44 0021EB24  48 00 00 55 */	bl GrTMars_80221F98
/* 80221F48 0021EB28  4B FA 1A 79 */	bl func_801C39C0
/* 80221F4C 0021EB2C  4B FA 1C 69 */	bl func_801C3BB4
/* 80221F50 0021EB30  4B FA 22 C1 */	bl func_801C4210
/* 80221F54 0021EB34  4B FA 23 59 */	bl func_801C42AC
/* 80221F58 0021EB38  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80221F5C 0021EB3C  38 21 00 08 */	addi r1, r1, 8
/* 80221F60 0021EB40  7C 08 03 A6 */	mtlr r0
/* 80221F64 0021EB44  4E 80 00 20 */	blr 
}

void GrTMars_80221F68(void)
{
    return;
}

#pragma push
#pragma peephole on
void GrTMars_80221F6C(void)
{
    func_801CAE04(0);
}
#pragma pop

int GrTMars_80221F90(void)
{
    return 0;
}

asm HSD_GObj* GrTMars_80221F98(int param_1)
{
    nofralloc
/* 80221F98 0021EB78  7C 08 02 A6 */	mflr r0
/* 80221F9C 0021EB7C  90 01 00 04 */	stw r0, 4(r1)
/* 80221FA0 0021EB80  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80221FA4 0021EB84  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80221FA8 0021EB88  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80221FAC 0021EB8C  93 A1 00 14 */	stw r29, 0x14(r1)
/* 80221FB0 0021EB90  93 81 00 10 */	stw r28, 0x10(r1)
/* 80221FB4 0021EB94  3B 83 00 00 */	addi r28, r3, 0
/* 80221FB8 0021EB98  1C 1C 00 14 */	mulli r0, r28, 0x14
/* 80221FBC 0021EB9C  3C 60 80 3F */	lis r3, lbl_803E8EB0@ha
/* 80221FC0 0021EBA0  3B E3 8E B0 */	addi r31, r3, lbl_803E8EB0@l
/* 80221FC4 0021EBA4  38 7C 00 00 */	addi r3, r28, 0
/* 80221FC8 0021EBA8  7F BF 02 14 */	add r29, r31, r0
/* 80221FCC 0021EBAC  4B F9 F5 05 */	bl func_801C14D0
/* 80221FD0 0021EBB0  7C 7E 1B 79 */	or. r30, r3, r3
/* 80221FD4 0021EBB4  41 82 00 70 */	beq lbl_80222044
/* 80221FD8 0021EBB8  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 80221FDC 0021EBBC  38 00 00 00 */	li r0, 0
/* 80221FE0 0021EBC0  3C 60 80 1C */	lis r3, func_801C5DB0@ha
/* 80221FE4 0021EBC4  90 1F 00 08 */	stw r0, 8(r31)
/* 80221FE8 0021EBC8  38 83 5D B0 */	addi r4, r3, func_801C5DB0@l
/* 80221FEC 0021EBCC  38 7E 00 00 */	addi r3, r30, 0
/* 80221FF0 0021EBD0  90 1F 00 0C */	stw r0, 0xc(r31)
/* 80221FF4 0021EBD4  38 A0 00 03 */	li r5, 3
/* 80221FF8 0021EBD8  38 C0 00 00 */	li r6, 0
/* 80221FFC 0021EBDC  48 16 E6 A1 */	bl GObj_SetupGXLink
/* 80222000 0021EBE0  80 1D 00 0C */	lwz r0, 0xc(r29)
/* 80222004 0021EBE4  28 00 00 00 */	cmplwi r0, 0
/* 80222008 0021EBE8  41 82 00 08 */	beq lbl_80222010
/* 8022200C 0021EBEC  90 1F 00 1C */	stw r0, 0x1c(r31)
lbl_80222010:
/* 80222010 0021EBF0  81 9D 00 00 */	lwz r12, 0(r29)
/* 80222014 0021EBF4  28 0C 00 00 */	cmplwi r12, 0
/* 80222018 0021EBF8  41 82 00 10 */	beq lbl_80222028
/* 8022201C 0021EBFC  7D 88 03 A6 */	mtlr r12
/* 80222020 0021EC00  38 7E 00 00 */	addi r3, r30, 0
/* 80222024 0021EC04  4E 80 00 21 */	blrl 
lbl_80222028:
/* 80222028 0021EC08  80 9D 00 08 */	lwz r4, 8(r29)
/* 8022202C 0021EC0C  28 04 00 00 */	cmplwi r4, 0
/* 80222030 0021EC10  41 82 00 2C */	beq lbl_8022205C
/* 80222034 0021EC14  38 7E 00 00 */	addi r3, r30, 0
/* 80222038 0021EC18  38 A0 00 04 */	li r5, 4
/* 8022203C 0021EC1C  48 16 DD 19 */	bl func_8038FD54
/* 80222040 0021EC20  48 00 00 1C */	b lbl_8022205C
lbl_80222044:
/* 80222044 0021EC24  38 DC 00 00 */	addi r6, r28, 0
/* 80222048 0021EC28  4C C6 31 82 */	crclr 6
/* 8022204C 0021EC2C  38 7F 00 90 */	addi r3, r31, 0x90
/* 80222050 0021EC30  38 9F 00 B4 */	addi r4, r31, 0xb4
/* 80222054 0021EC34  38 A0 00 C3 */	li r5, 0xc3
/* 80222058 0021EC38  48 12 36 51 */	bl OSReport
lbl_8022205C:
/* 8022205C 0021EC3C  7F C3 F3 78 */	mr r3, r30
/* 80222060 0021EC40  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80222064 0021EC44  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80222068 0021EC48  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8022206C 0021EC4C  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 80222070 0021EC50  83 81 00 10 */	lwz r28, 0x10(r1)
/* 80222074 0021EC54  38 21 00 20 */	addi r1, r1, 0x20
/* 80222078 0021EC58  7C 08 03 A6 */	mtlr r0
/* 8022207C 0021EC5C  4E 80 00 20 */	blr 
}

asm void GrTMars_80222080(HSD_GObj* gobj)
{
    nofralloc
/* 80222080 0021EC60  7C 08 02 A6 */	mflr r0
/* 80222084 0021EC64  38 A0 00 00 */	li r5, 0
/* 80222088 0021EC68  90 01 00 04 */	stw r0, 4(r1)
/* 8022208C 0021EC6C  94 21 FF F8 */	stwu r1, -8(r1)
/* 80222090 0021EC70  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 80222094 0021EC74  80 84 00 14 */	lwz r4, 0x14(r4)
/* 80222098 0021EC78  4B FA 60 A1 */	bl func_801C8138
/* 8022209C 0021EC7C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802220A0 0021EC80  38 21 00 08 */	addi r1, r1, 8
/* 802220A4 0021EC84  7C 08 03 A6 */	mtlr r0
/* 802220A8 0021EC88  4E 80 00 20 */	blr 
}

int GrTMars_802220AC(void)
{
    return 0;
}

void GrTMars_802220B4(void)
{
    return;
}

void GrTMars_802220B8(void)
{
    return;
}

asm void GrTMars_802220BC(HSD_GObj* gobj)
{
    nofralloc
/* 802220BC 0021EC9C  7C 08 02 A6 */	mflr r0
/* 802220C0 0021ECA0  90 01 00 04 */	stw r0, 4(r1)
/* 802220C4 0021ECA4  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 802220C8 0021ECA8  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 802220CC 0021ECAC  93 C1 00 18 */	stw r30, 0x18(r1)
/* 802220D0 0021ECB0  7C 7E 1B 78 */	mr r30, r3
/* 802220D4 0021ECB4  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 802220D8 0021ECB8  80 63 00 28 */	lwz r3, 0x28(r3)
/* 802220DC 0021ECBC  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 802220E0 0021ECC0  4B FA 0D F1 */	bl func_801C2ED0
/* 802220E4 0021ECC4  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 802220E8 0021ECC8  38 7E 00 00 */	addi r3, r30, 0
/* 802220EC 0021ECCC  38 A0 00 00 */	li r5, 0
/* 802220F0 0021ECD0  4B FA 60 49 */	bl func_801C8138
/* 802220F4 0021ECD4  80 01 00 24 */	lwz r0, 0x24(r1)
/* 802220F8 0021ECD8  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 802220FC 0021ECDC  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80222100 0021ECE0  38 21 00 20 */	addi r1, r1, 0x20
/* 80222104 0021ECE4  7C 08 03 A6 */	mtlr r0
/* 80222108 0021ECE8  4E 80 00 20 */	blr 
}

int GrTMars_8022210C(void)
{
    return 0;
}

#pragma push
#pragma peephole on
void GrTMars_80222114(HSD_GObj* gobj)
{
    func_800115F4();
    func_801C2FE0(gobj);
}
#pragma pop

void GrTMars_80222148(void)
{
    return;
}

asm void GrTMars_8022214C(HSD_GObj* gobj)
{
    nofralloc
/* 8022214C 0021ED2C  7C 08 02 A6 */	mflr r0
/* 80222150 0021ED30  90 01 00 04 */	stw r0, 4(r1)
/* 80222154 0021ED34  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80222158 0021ED38  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8022215C 0021ED3C  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80222160 0021ED40  7C 7E 1B 78 */	mr r30, r3
/* 80222164 0021ED44  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80222168 0021ED48  80 63 00 28 */	lwz r3, 0x28(r3)
/* 8022216C 0021ED4C  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80222170 0021ED50  4B FA 0D 61 */	bl func_801C2ED0
/* 80222174 0021ED54  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80222178 0021ED58  38 7E 00 00 */	addi r3, r30, 0
/* 8022217C 0021ED5C  38 A0 00 00 */	li r5, 0
/* 80222180 0021ED60  4B FA 5F B9 */	bl func_801C8138
/* 80222184 0021ED64  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80222188 0021ED68  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8022218C 0021ED6C  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80222190 0021ED70  38 21 00 20 */	addi r1, r1, 0x20
/* 80222194 0021ED74  7C 08 03 A6 */	mtlr r0
/* 80222198 0021ED78  4E 80 00 20 */	blr 
}

int GrTMars_8022219C(void)
{
    return 0;
}

#pragma push
#pragma peephole on
void GrTMars_802221A4(HSD_GObj* gobj)
{
    func_801C2FE0(gobj);
}
#pragma pop

void GrTMars_802221C4(void)
{
    return;
}

int GrTMars_802221C8(void)
{
    return 0;
}

int GrTMars_802221D0(void)
{
    return 1;
}
