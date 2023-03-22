.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

.global func_80222E7C
func_80222E7C:
/* 80222E7C 0021FA5C  4E 80 00 20 */	blr
.global lbl_80222E80
lbl_80222E80:
/* 80222E80 0021FA60  7C 08 02 A6 */	mflr r0
/* 80222E84 0021FA64  3C 60 80 4A */	lis r3, stage_info@ha
/* 80222E88 0021FA68  90 01 00 04 */	stw r0, 4(r1)
/* 80222E8C 0021FA6C  38 63 E6 C8 */	addi r3, r3, stage_info@l
/* 80222E90 0021FA70  38 A3 00 8C */	addi r5, r3, 0x8c
/* 80222E94 0021FA74  94 21 FF F8 */	stwu r1, -8(r1)
/* 80222E98 0021FA78  38 80 00 01 */	li r4, 1
/* 80222E9C 0021FA7C  88 03 00 8C */	lbz r0, 0x8c(r3)
/* 80222EA0 0021FA80  38 60 00 00 */	li r3, 0
/* 80222EA4 0021FA84  50 60 1F 38 */	rlwimi r0, r3, 3, 0x1c, 0x1c
/* 80222EA8 0021FA88  98 05 00 00 */	stb r0, 0(r5)
/* 80222EAC 0021FA8C  38 60 00 00 */	li r3, 0
/* 80222EB0 0021FA90  88 05 00 00 */	lbz r0, 0(r5)
/* 80222EB4 0021FA94  50 80 17 7A */	rlwimi r0, r4, 2, 0x1d, 0x1d
/* 80222EB8 0021FA98  98 05 00 00 */	stb r0, 0(r5)
/* 80222EBC 0021FA9C  48 00 00 65 */	bl func_80222F20
/* 80222EC0 0021FAA0  38 60 00 01 */	li r3, 1
/* 80222EC4 0021FAA4  48 00 00 5D */	bl func_80222F20
/* 80222EC8 0021FAA8  38 60 00 02 */	li r3, 2
/* 80222ECC 0021FAAC  48 00 00 55 */	bl func_80222F20
/* 80222ED0 0021FAB0  4B FA 0A F1 */	bl Ground_801C39C0
/* 80222ED4 0021FAB4  4B FA 0C E1 */	bl Ground_801C3BB4
/* 80222ED8 0021FAB8  4B FA 13 39 */	bl Ground_801C4210
/* 80222EDC 0021FABC  4B FA 13 D1 */	bl Ground_801C42AC
/* 80222EE0 0021FAC0  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80222EE4 0021FAC4  38 21 00 08 */	addi r1, r1, 8
/* 80222EE8 0021FAC8  7C 08 03 A6 */	mtlr r0
/* 80222EEC 0021FACC  4E 80 00 20 */	blr
.global lbl_80222EF0
lbl_80222EF0:
/* 80222EF0 0021FAD0  4E 80 00 20 */	blr
.global lbl_80222EF4
lbl_80222EF4:
/* 80222EF4 0021FAD4  7C 08 02 A6 */	mflr r0
/* 80222EF8 0021FAD8  38 60 00 00 */	li r3, 0
/* 80222EFC 0021FADC  90 01 00 04 */	stw r0, 4(r1)
/* 80222F00 0021FAE0  94 21 FF F8 */	stwu r1, -8(r1)
/* 80222F04 0021FAE4  4B FA 7F 01 */	bl grZakoGenerator_801CAE04
/* 80222F08 0021FAE8  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80222F0C 0021FAEC  38 21 00 08 */	addi r1, r1, 8
/* 80222F10 0021FAF0  7C 08 03 A6 */	mtlr r0
/* 80222F14 0021FAF4  4E 80 00 20 */	blr
.global lbl_80222F18
lbl_80222F18:
/* 80222F18 0021FAF8  38 60 00 00 */	li r3, 0
/* 80222F1C 0021FAFC  4E 80 00 20 */	blr

.global func_80222F20
func_80222F20:
/* 80222F20 0021FB00  7C 08 02 A6 */	mflr r0
/* 80222F24 0021FB04  90 01 00 04 */	stw r0, 4(r1)
/* 80222F28 0021FB08  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80222F2C 0021FB0C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80222F30 0021FB10  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80222F34 0021FB14  93 A1 00 14 */	stw r29, 0x14(r1)
/* 80222F38 0021FB18  93 81 00 10 */	stw r28, 0x10(r1)
/* 80222F3C 0021FB1C  3B 83 00 00 */	addi r28, r3, 0
/* 80222F40 0021FB20  1C 1C 00 14 */	mulli r0, r28, 0x14
/* 80222F44 0021FB24  3C 60 80 3F */	lis r3, lbl_803E9270@ha
/* 80222F48 0021FB28  3B E3 92 70 */	addi r31, r3, lbl_803E9270@l
/* 80222F4C 0021FB2C  38 7C 00 00 */	addi r3, r28, 0
/* 80222F50 0021FB30  7F BF 02 14 */	add r29, r31, r0
/* 80222F54 0021FB34  4B F9 E5 7D */	bl Ground_801C14D0
/* 80222F58 0021FB38  7C 7E 1B 79 */	or. r30, r3, r3
/* 80222F5C 0021FB3C  41 82 00 70 */	beq lbl_80222FCC
/* 80222F60 0021FB40  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 80222F64 0021FB44  38 00 00 00 */	li r0, 0
/* 80222F68 0021FB48  3C 60 80 1C */	lis r3, grDisplay_801C5DB0@ha
/* 80222F6C 0021FB4C  90 1F 00 08 */	stw r0, 8(r31)
/* 80222F70 0021FB50  38 83 5D B0 */	addi r4, r3, grDisplay_801C5DB0@l
/* 80222F74 0021FB54  38 7E 00 00 */	addi r3, r30, 0
/* 80222F78 0021FB58  90 1F 00 0C */	stw r0, 0xc(r31)
/* 80222F7C 0021FB5C  38 A0 00 03 */	li r5, 3
/* 80222F80 0021FB60  38 C0 00 00 */	li r6, 0
/* 80222F84 0021FB64  48 16 D7 19 */	bl GObj_SetupGXLink
/* 80222F88 0021FB68  80 1D 00 0C */	lwz r0, 0xc(r29)
/* 80222F8C 0021FB6C  28 00 00 00 */	cmplwi r0, 0
/* 80222F90 0021FB70  41 82 00 08 */	beq lbl_80222F98
/* 80222F94 0021FB74  90 1F 00 1C */	stw r0, 0x1c(r31)
lbl_80222F98:
/* 80222F98 0021FB78  81 9D 00 00 */	lwz r12, 0(r29)
/* 80222F9C 0021FB7C  28 0C 00 00 */	cmplwi r12, 0
/* 80222FA0 0021FB80  41 82 00 10 */	beq lbl_80222FB0
/* 80222FA4 0021FB84  7D 88 03 A6 */	mtlr r12
/* 80222FA8 0021FB88  38 7E 00 00 */	addi r3, r30, 0
/* 80222FAC 0021FB8C  4E 80 00 21 */	blrl
lbl_80222FB0:
/* 80222FB0 0021FB90  80 9D 00 08 */	lwz r4, 8(r29)
/* 80222FB4 0021FB94  28 04 00 00 */	cmplwi r4, 0
/* 80222FB8 0021FB98  41 82 00 2C */	beq lbl_80222FE4
/* 80222FBC 0021FB9C  38 7E 00 00 */	addi r3, r30, 0
/* 80222FC0 0021FBA0  38 A0 00 04 */	li r5, 4
/* 80222FC4 0021FBA4  48 16 CD 91 */	bl func_8038FD54
/* 80222FC8 0021FBA8  48 00 00 1C */	b lbl_80222FE4
lbl_80222FCC:
/* 80222FCC 0021FBAC  38 DC 00 00 */	addi r6, r28, 0
/* 80222FD0 0021FBB0  4C C6 31 82 */	crclr 6
/* 80222FD4 0021FBB4  38 7F 00 90 */	addi r3, r31, 0x90
/* 80222FD8 0021FBB8  38 9F 00 B4 */	addi r4, r31, 0xb4
/* 80222FDC 0021FBBC  38 A0 00 C3 */	li r5, 0xc3
/* 80222FE0 0021FBC0  48 12 26 C9 */	bl OSReport
lbl_80222FE4:
/* 80222FE4 0021FBC4  7F C3 F3 78 */	mr r3, r30
/* 80222FE8 0021FBC8  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80222FEC 0021FBCC  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80222FF0 0021FBD0  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80222FF4 0021FBD4  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 80222FF8 0021FBD8  83 81 00 10 */	lwz r28, 0x10(r1)
/* 80222FFC 0021FBDC  38 21 00 20 */	addi r1, r1, 0x20
/* 80223000 0021FBE0  7C 08 03 A6 */	mtlr r0
/* 80223004 0021FBE4  4E 80 00 20 */	blr
.global lbl_80223008
lbl_80223008:
/* 80223008 0021FBE8  7C 08 02 A6 */	mflr r0
/* 8022300C 0021FBEC  38 A0 00 00 */	li r5, 0
/* 80223010 0021FBF0  90 01 00 04 */	stw r0, 4(r1)
/* 80223014 0021FBF4  94 21 FF F8 */	stwu r1, -8(r1)
/* 80223018 0021FBF8  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 8022301C 0021FBFC  80 84 00 14 */	lwz r4, 0x14(r4)
/* 80223020 0021FC00  4B FA 51 19 */	bl grAnime_801C8138
/* 80223024 0021FC04  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80223028 0021FC08  38 21 00 08 */	addi r1, r1, 8
/* 8022302C 0021FC0C  7C 08 03 A6 */	mtlr r0
/* 80223030 0021FC10  4E 80 00 20 */	blr
.global lbl_80223034
lbl_80223034:
/* 80223034 0021FC14  38 60 00 00 */	li r3, 0
/* 80223038 0021FC18  4E 80 00 20 */	blr
.global lbl_8022303C
lbl_8022303C:
/* 8022303C 0021FC1C  4E 80 00 20 */	blr
.global lbl_80223040
lbl_80223040:
/* 80223040 0021FC20  4E 80 00 20 */	blr
.global lbl_80223044
lbl_80223044:
/* 80223044 0021FC24  7C 08 02 A6 */	mflr r0
/* 80223048 0021FC28  90 01 00 04 */	stw r0, 4(r1)
/* 8022304C 0021FC2C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80223050 0021FC30  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80223054 0021FC34  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80223058 0021FC38  7C 7E 1B 78 */	mr r30, r3
/* 8022305C 0021FC3C  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80223060 0021FC40  80 63 00 28 */	lwz r3, 0x28(r3)
/* 80223064 0021FC44  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80223068 0021FC48  4B F9 FE 69 */	bl Ground_801C2ED0
/* 8022306C 0021FC4C  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80223070 0021FC50  38 7E 00 00 */	addi r3, r30, 0
/* 80223074 0021FC54  38 A0 00 00 */	li r5, 0
/* 80223078 0021FC58  4B FA 50 C1 */	bl grAnime_801C8138
/* 8022307C 0021FC5C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80223080 0021FC60  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80223084 0021FC64  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80223088 0021FC68  38 21 00 20 */	addi r1, r1, 0x20
/* 8022308C 0021FC6C  7C 08 03 A6 */	mtlr r0
/* 80223090 0021FC70  4E 80 00 20 */	blr
.global lbl_80223094
lbl_80223094:
/* 80223094 0021FC74  38 60 00 00 */	li r3, 0
/* 80223098 0021FC78  4E 80 00 20 */	blr
.global lbl_8022309C
lbl_8022309C:
/* 8022309C 0021FC7C  7C 08 02 A6 */	mflr r0
/* 802230A0 0021FC80  90 01 00 04 */	stw r0, 4(r1)
/* 802230A4 0021FC84  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 802230A8 0021FC88  93 E1 00 14 */	stw r31, 0x14(r1)
/* 802230AC 0021FC8C  7C 7F 1B 78 */	mr r31, r3
/* 802230B0 0021FC90  4B DE E5 45 */	bl lb_800115F4
/* 802230B4 0021FC94  7F E3 FB 78 */	mr r3, r31
/* 802230B8 0021FC98  4B F9 FF 29 */	bl Ground_801C2FE0
/* 802230BC 0021FC9C  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 802230C0 0021FCA0  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 802230C4 0021FCA4  38 21 00 18 */	addi r1, r1, 0x18
/* 802230C8 0021FCA8  7C 08 03 A6 */	mtlr r0
/* 802230CC 0021FCAC  4E 80 00 20 */	blr
.global lbl_802230D0
lbl_802230D0:
/* 802230D0 0021FCB0  4E 80 00 20 */	blr
.global lbl_802230D4
lbl_802230D4:
/* 802230D4 0021FCB4  7C 08 02 A6 */	mflr r0
/* 802230D8 0021FCB8  90 01 00 04 */	stw r0, 4(r1)
/* 802230DC 0021FCBC  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 802230E0 0021FCC0  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 802230E4 0021FCC4  93 C1 00 18 */	stw r30, 0x18(r1)
/* 802230E8 0021FCC8  7C 7E 1B 78 */	mr r30, r3
/* 802230EC 0021FCCC  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 802230F0 0021FCD0  80 63 00 28 */	lwz r3, 0x28(r3)
/* 802230F4 0021FCD4  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 802230F8 0021FCD8  4B F9 FD D9 */	bl Ground_801C2ED0
/* 802230FC 0021FCDC  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80223100 0021FCE0  38 7E 00 00 */	addi r3, r30, 0
/* 80223104 0021FCE4  38 A0 00 00 */	li r5, 0
/* 80223108 0021FCE8  4B FA 50 31 */	bl grAnime_801C8138
/* 8022310C 0021FCEC  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80223110 0021FCF0  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80223114 0021FCF4  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80223118 0021FCF8  38 21 00 20 */	addi r1, r1, 0x20
/* 8022311C 0021FCFC  7C 08 03 A6 */	mtlr r0
/* 80223120 0021FD00  4E 80 00 20 */	blr
.global lbl_80223124
lbl_80223124:
/* 80223124 0021FD04  38 60 00 00 */	li r3, 0
/* 80223128 0021FD08  4E 80 00 20 */	blr
.global lbl_8022312C
lbl_8022312C:
/* 8022312C 0021FD0C  7C 08 02 A6 */	mflr r0
/* 80223130 0021FD10  90 01 00 04 */	stw r0, 4(r1)
/* 80223134 0021FD14  94 21 FF F8 */	stwu r1, -8(r1)
/* 80223138 0021FD18  4B F9 FE A9 */	bl Ground_801C2FE0
/* 8022313C 0021FD1C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80223140 0021FD20  38 21 00 08 */	addi r1, r1, 8
/* 80223144 0021FD24  7C 08 03 A6 */	mtlr r0
/* 80223148 0021FD28  4E 80 00 20 */	blr
.global lbl_8022314C
lbl_8022314C:
/* 8022314C 0021FD2C  4E 80 00 20 */	blr
.global lbl_80223150
lbl_80223150:
/* 80223150 0021FD30  38 60 00 00 */	li r3, 0
/* 80223154 0021FD34  4E 80 00 20 */	blr
.global lbl_80223158
lbl_80223158:
/* 80223158 0021FD38  38 60 00 01 */	li r3, 1
/* 8022315C 0021FD3C  4E 80 00 20 */	blr


.section .data
    .balign 8
.global lbl_803E9270
lbl_803E9270:
    .4byte lbl_80223008
    .4byte lbl_80223034
    .4byte lbl_8022303C
    .4byte lbl_80223040
    .4byte NULL
    .4byte lbl_802230D4
    .4byte lbl_80223124
    .4byte lbl_8022312C
    .4byte lbl_8022314C
    .4byte NULL
    .4byte lbl_80223044
    .4byte lbl_80223094
    .4byte lbl_8022309C
    .4byte lbl_802230D0
    .4byte 0xC0000000
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
.global lbl_803E92C0
lbl_803E92C0:
    .asciz "/GrTPk.dat"
    .balign 4
.global lbl_803E92CC
lbl_803E92CC:
    .4byte 0x00000039
    .4byte lbl_803E9270
    .4byte lbl_803E92C0
    .4byte lbl_80222E80
    .4byte func_80222E7C
    .4byte lbl_80222EF0
    .4byte lbl_80222EF4
    .4byte lbl_80222F18
    .4byte lbl_80223150
    .4byte lbl_80223158
    .4byte 0x00000001
    .4byte NULL
    .4byte NULL
    .asciz "%s:%d: couldn t get gobj(id=%d)\n"
    .balign 4
    .asciz "grtpikachu.c"
