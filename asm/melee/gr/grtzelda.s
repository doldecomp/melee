.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

.global grTZelda_80223E2C
grTZelda_80223E2C:
/* 80223E2C 00220A0C  4E 80 00 20 */	blr
.global grTZelda_80223E30
grTZelda_80223E30:
/* 80223E30 00220A10  7C 08 02 A6 */	mflr r0
/* 80223E34 00220A14  3C 60 80 4A */	lis r3, stage_info@ha
/* 80223E38 00220A18  90 01 00 04 */	stw r0, 4(r1)
/* 80223E3C 00220A1C  38 63 E6 C8 */	addi r3, r3, stage_info@l
/* 80223E40 00220A20  38 A3 00 8C */	addi r5, r3, 0x8c
/* 80223E44 00220A24  94 21 FF F8 */	stwu r1, -8(r1)
/* 80223E48 00220A28  38 80 00 01 */	li r4, 1
/* 80223E4C 00220A2C  88 03 00 8C */	lbz r0, 0x8c(r3)
/* 80223E50 00220A30  38 60 00 00 */	li r3, 0
/* 80223E54 00220A34  50 60 1F 38 */	rlwimi r0, r3, 3, 0x1c, 0x1c
/* 80223E58 00220A38  98 05 00 00 */	stb r0, 0(r5)
/* 80223E5C 00220A3C  38 60 00 00 */	li r3, 0
/* 80223E60 00220A40  88 05 00 00 */	lbz r0, 0(r5)
/* 80223E64 00220A44  50 80 17 7A */	rlwimi r0, r4, 2, 0x1d, 0x1d
/* 80223E68 00220A48  98 05 00 00 */	stb r0, 0(r5)
/* 80223E6C 00220A4C  48 00 00 65 */	bl grTZelda_80223ED0
/* 80223E70 00220A50  38 60 00 01 */	li r3, 1
/* 80223E74 00220A54  48 00 00 5D */	bl grTZelda_80223ED0
/* 80223E78 00220A58  38 60 00 02 */	li r3, 2
/* 80223E7C 00220A5C  48 00 00 55 */	bl grTZelda_80223ED0
/* 80223E80 00220A60  4B F9 FB 41 */	bl Ground_801C39C0
/* 80223E84 00220A64  4B F9 FD 31 */	bl Ground_801C3BB4
/* 80223E88 00220A68  4B FA 03 89 */	bl Ground_801C4210
/* 80223E8C 00220A6C  4B FA 04 21 */	bl Ground_801C42AC
/* 80223E90 00220A70  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80223E94 00220A74  38 21 00 08 */	addi r1, r1, 8
/* 80223E98 00220A78  7C 08 03 A6 */	mtlr r0
/* 80223E9C 00220A7C  4E 80 00 20 */	blr
.global grTZelda_80223EA0
grTZelda_80223EA0:
/* 80223EA0 00220A80  4E 80 00 20 */	blr
.global grTZelda_80223EA4
grTZelda_80223EA4:
/* 80223EA4 00220A84  7C 08 02 A6 */	mflr r0
/* 80223EA8 00220A88  38 60 00 00 */	li r3, 0
/* 80223EAC 00220A8C  90 01 00 04 */	stw r0, 4(r1)
/* 80223EB0 00220A90  94 21 FF F8 */	stwu r1, -8(r1)
/* 80223EB4 00220A94  4B FA 6F 51 */	bl grZakoGenerator_801CAE04
/* 80223EB8 00220A98  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80223EBC 00220A9C  38 21 00 08 */	addi r1, r1, 8
/* 80223EC0 00220AA0  7C 08 03 A6 */	mtlr r0
/* 80223EC4 00220AA4  4E 80 00 20 */	blr
.global grTZelda_80223EC8
grTZelda_80223EC8:
/* 80223EC8 00220AA8  38 60 00 00 */	li r3, 0
/* 80223ECC 00220AAC  4E 80 00 20 */	blr

.global grTZelda_80223ED0
grTZelda_80223ED0:
/* 80223ED0 00220AB0  7C 08 02 A6 */	mflr r0
/* 80223ED4 00220AB4  90 01 00 04 */	stw r0, 4(r1)
/* 80223ED8 00220AB8  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80223EDC 00220ABC  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80223EE0 00220AC0  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80223EE4 00220AC4  93 A1 00 14 */	stw r29, 0x14(r1)
/* 80223EE8 00220AC8  93 81 00 10 */	stw r28, 0x10(r1)
/* 80223EEC 00220ACC  3B 83 00 00 */	addi r28, r3, 0
/* 80223EF0 00220AD0  1C 1C 00 14 */	mulli r0, r28, 0x14
/* 80223EF4 00220AD4  3C 60 80 3F */	lis r3, lbl_803E9638@ha
/* 80223EF8 00220AD8  3B E3 96 38 */	addi r31, r3, lbl_803E9638@l
/* 80223EFC 00220ADC  38 7C 00 00 */	addi r3, r28, 0
/* 80223F00 00220AE0  7F BF 02 14 */	add r29, r31, r0
/* 80223F04 00220AE4  4B F9 D5 CD */	bl Ground_801C14D0
/* 80223F08 00220AE8  7C 7E 1B 79 */	or. r30, r3, r3
/* 80223F0C 00220AEC  41 82 00 70 */	beq grTZelda_80223F7C
/* 80223F10 00220AF0  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 80223F14 00220AF4  38 00 00 00 */	li r0, 0
/* 80223F18 00220AF8  3C 60 80 1C */	lis r3, grDisplay_801C5DB0@ha
/* 80223F1C 00220AFC  90 1F 00 08 */	stw r0, 8(r31)
/* 80223F20 00220B00  38 83 5D B0 */	addi r4, r3, grDisplay_801C5DB0@l
/* 80223F24 00220B04  38 7E 00 00 */	addi r3, r30, 0
/* 80223F28 00220B08  90 1F 00 0C */	stw r0, 0xc(r31)
/* 80223F2C 00220B0C  38 A0 00 03 */	li r5, 3
/* 80223F30 00220B10  38 C0 00 00 */	li r6, 0
/* 80223F34 00220B14  48 16 C7 69 */	bl GObj_SetupGXLink
/* 80223F38 00220B18  80 1D 00 0C */	lwz r0, 0xc(r29)
/* 80223F3C 00220B1C  28 00 00 00 */	cmplwi r0, 0
/* 80223F40 00220B20  41 82 00 08 */	beq grTZelda_80223F48
/* 80223F44 00220B24  90 1F 00 1C */	stw r0, 0x1c(r31)
grTZelda_80223F48:
/* 80223F48 00220B28  81 9D 00 00 */	lwz r12, 0(r29)
/* 80223F4C 00220B2C  28 0C 00 00 */	cmplwi r12, 0
/* 80223F50 00220B30  41 82 00 10 */	beq grTZelda_80223F60
/* 80223F54 00220B34  7D 88 03 A6 */	mtlr r12
/* 80223F58 00220B38  38 7E 00 00 */	addi r3, r30, 0
/* 80223F5C 00220B3C  4E 80 00 21 */	blrl
grTZelda_80223F60:
/* 80223F60 00220B40  80 9D 00 08 */	lwz r4, 8(r29)
/* 80223F64 00220B44  28 04 00 00 */	cmplwi r4, 0
/* 80223F68 00220B48  41 82 00 2C */	beq grTZelda_80223F94
/* 80223F6C 00220B4C  38 7E 00 00 */	addi r3, r30, 0
/* 80223F70 00220B50  38 A0 00 04 */	li r5, 4
/* 80223F74 00220B54  48 16 BD E1 */	bl func_8038FD54
/* 80223F78 00220B58  48 00 00 1C */	b grTZelda_80223F94
grTZelda_80223F7C:
/* 80223F7C 00220B5C  38 DC 00 00 */	addi r6, r28, 0
/* 80223F80 00220B60  4C C6 31 82 */	crclr 6
/* 80223F84 00220B64  38 7F 00 90 */	addi r3, r31, 0x90
/* 80223F88 00220B68  38 9F 00 B4 */	addi r4, r31, 0xb4
/* 80223F8C 00220B6C  38 A0 00 C3 */	li r5, 0xc3
/* 80223F90 00220B70  48 12 17 19 */	bl OSReport
grTZelda_80223F94:
/* 80223F94 00220B74  7F C3 F3 78 */	mr r3, r30
/* 80223F98 00220B78  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80223F9C 00220B7C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80223FA0 00220B80  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80223FA4 00220B84  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 80223FA8 00220B88  83 81 00 10 */	lwz r28, 0x10(r1)
/* 80223FAC 00220B8C  38 21 00 20 */	addi r1, r1, 0x20
/* 80223FB0 00220B90  7C 08 03 A6 */	mtlr r0
/* 80223FB4 00220B94  4E 80 00 20 */	blr
.global grTZelda_80223FB8
grTZelda_80223FB8:
/* 80223FB8 00220B98  7C 08 02 A6 */	mflr r0
/* 80223FBC 00220B9C  38 A0 00 00 */	li r5, 0
/* 80223FC0 00220BA0  90 01 00 04 */	stw r0, 4(r1)
/* 80223FC4 00220BA4  94 21 FF F8 */	stwu r1, -8(r1)
/* 80223FC8 00220BA8  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 80223FCC 00220BAC  80 84 00 14 */	lwz r4, 0x14(r4)
/* 80223FD0 00220BB0  4B FA 41 69 */	bl grAnime_801C8138
/* 80223FD4 00220BB4  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80223FD8 00220BB8  38 21 00 08 */	addi r1, r1, 8
/* 80223FDC 00220BBC  7C 08 03 A6 */	mtlr r0
/* 80223FE0 00220BC0  4E 80 00 20 */	blr
.global grTZelda_80223FE4
grTZelda_80223FE4:
/* 80223FE4 00220BC4  38 60 00 00 */	li r3, 0
/* 80223FE8 00220BC8  4E 80 00 20 */	blr
.global grTZelda_80223FEC
grTZelda_80223FEC:
/* 80223FEC 00220BCC  4E 80 00 20 */	blr
.global grTZelda_80223FF0
grTZelda_80223FF0:
/* 80223FF0 00220BD0  4E 80 00 20 */	blr
.global grTZelda_80223FF4
grTZelda_80223FF4:
/* 80223FF4 00220BD4  7C 08 02 A6 */	mflr r0
/* 80223FF8 00220BD8  90 01 00 04 */	stw r0, 4(r1)
/* 80223FFC 00220BDC  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80224000 00220BE0  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80224004 00220BE4  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80224008 00220BE8  7C 7E 1B 78 */	mr r30, r3
/* 8022400C 00220BEC  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80224010 00220BF0  80 63 00 28 */	lwz r3, 0x28(r3)
/* 80224014 00220BF4  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80224018 00220BF8  4B F9 EE B9 */	bl Ground_801C2ED0
/* 8022401C 00220BFC  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80224020 00220C00  38 7E 00 00 */	addi r3, r30, 0
/* 80224024 00220C04  38 A0 00 00 */	li r5, 0
/* 80224028 00220C08  4B FA 41 11 */	bl grAnime_801C8138
/* 8022402C 00220C0C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80224030 00220C10  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80224034 00220C14  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80224038 00220C18  38 21 00 20 */	addi r1, r1, 0x20
/* 8022403C 00220C1C  7C 08 03 A6 */	mtlr r0
/* 80224040 00220C20  4E 80 00 20 */	blr
.global grTZelda_80224044
grTZelda_80224044:
/* 80224044 00220C24  38 60 00 00 */	li r3, 0
/* 80224048 00220C28  4E 80 00 20 */	blr
.global grTZelda_8022404C
grTZelda_8022404C:
/* 8022404C 00220C2C  7C 08 02 A6 */	mflr r0
/* 80224050 00220C30  90 01 00 04 */	stw r0, 4(r1)
/* 80224054 00220C34  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80224058 00220C38  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8022405C 00220C3C  7C 7F 1B 78 */	mr r31, r3
/* 80224060 00220C40  4B DE D5 95 */	bl lb_800115F4
/* 80224064 00220C44  7F E3 FB 78 */	mr r3, r31
/* 80224068 00220C48  4B F9 EF 79 */	bl Ground_801C2FE0
/* 8022406C 00220C4C  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80224070 00220C50  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80224074 00220C54  38 21 00 18 */	addi r1, r1, 0x18
/* 80224078 00220C58  7C 08 03 A6 */	mtlr r0
/* 8022407C 00220C5C  4E 80 00 20 */	blr
.global grTZelda_80224080
grTZelda_80224080:
/* 80224080 00220C60  4E 80 00 20 */	blr
.global grTZelda_80224084
grTZelda_80224084:
/* 80224084 00220C64  7C 08 02 A6 */	mflr r0
/* 80224088 00220C68  90 01 00 04 */	stw r0, 4(r1)
/* 8022408C 00220C6C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80224090 00220C70  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80224094 00220C74  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80224098 00220C78  7C 7E 1B 78 */	mr r30, r3
/* 8022409C 00220C7C  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 802240A0 00220C80  80 63 00 28 */	lwz r3, 0x28(r3)
/* 802240A4 00220C84  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 802240A8 00220C88  4B F9 EE 29 */	bl Ground_801C2ED0
/* 802240AC 00220C8C  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 802240B0 00220C90  38 7E 00 00 */	addi r3, r30, 0
/* 802240B4 00220C94  38 A0 00 00 */	li r5, 0
/* 802240B8 00220C98  4B FA 40 81 */	bl grAnime_801C8138
/* 802240BC 00220C9C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 802240C0 00220CA0  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 802240C4 00220CA4  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 802240C8 00220CA8  38 21 00 20 */	addi r1, r1, 0x20
/* 802240CC 00220CAC  7C 08 03 A6 */	mtlr r0
/* 802240D0 00220CB0  4E 80 00 20 */	blr
.global grTZelda_802240D4
grTZelda_802240D4:
/* 802240D4 00220CB4  38 60 00 00 */	li r3, 0
/* 802240D8 00220CB8  4E 80 00 20 */	blr
.global grTZelda_802240DC
grTZelda_802240DC:
/* 802240DC 00220CBC  7C 08 02 A6 */	mflr r0
/* 802240E0 00220CC0  90 01 00 04 */	stw r0, 4(r1)
/* 802240E4 00220CC4  94 21 FF F8 */	stwu r1, -8(r1)
/* 802240E8 00220CC8  4B F9 EE F9 */	bl Ground_801C2FE0
/* 802240EC 00220CCC  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802240F0 00220CD0  38 21 00 08 */	addi r1, r1, 8
/* 802240F4 00220CD4  7C 08 03 A6 */	mtlr r0
/* 802240F8 00220CD8  4E 80 00 20 */	blr
.global grTZelda_802240FC
grTZelda_802240FC:
/* 802240FC 00220CDC  4E 80 00 20 */	blr
.global grTZelda_80224100
grTZelda_80224100:
/* 80224100 00220CE0  38 60 00 00 */	li r3, 0
/* 80224104 00220CE4  4E 80 00 20 */	blr
.global grTZelda_80224108
grTZelda_80224108:
/* 80224108 00220CE8  38 60 00 01 */	li r3, 1
/* 8022410C 00220CEC  4E 80 00 20 */	blr


.section .data
    .balign 8
.global lbl_803E9638
lbl_803E9638:
    .4byte grTZelda_80223FB8
    .4byte grTZelda_80223FE4
    .4byte grTZelda_80223FEC
    .4byte grTZelda_80223FF0
    .4byte NULL
    .4byte grTZelda_80224084
    .4byte grTZelda_802240D4
    .4byte grTZelda_802240DC
    .4byte grTZelda_802240FC
    .4byte NULL
    .4byte grTZelda_80223FF4
    .4byte grTZelda_80224044
    .4byte grTZelda_8022404C
    .4byte grTZelda_80224080
    .4byte 0xC0000000
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
.global lbl_803E9688
lbl_803E9688:
    .asciz "/GrTZd.dat"
    .balign 4
.global lbl_803E9694
lbl_803E9694:
    .4byte 0x0000003E
    .4byte lbl_803E9638
    .4byte lbl_803E9688
    .4byte grTZelda_80223E30
    .4byte grTZelda_80223E2C
    .4byte grTZelda_80223EA0
    .4byte grTZelda_80223EA4
    .4byte grTZelda_80223EC8
    .4byte grTZelda_80224100
    .4byte grTZelda_80224108
    .4byte 0x00000001
    .4byte NULL
    .4byte NULL
    .asciz "%s:%d: couldn t get gobj(id=%d)\n"
    .balign 4
    .asciz "grtzelda.c"
