.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240


.global func_80127DE4
func_80127DE4:
/* 80127DE4 001249C4  7C 08 02 A6 */	mflr r0
/* 80127DE8 001249C8  90 01 00 04 */	stw r0, 4(r1)
/* 80127DEC 001249CC  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 80127DF0 001249D0  93 E1 00 24 */	stw r31, 0x24(r1)
/* 80127DF4 001249D4  93 C1 00 20 */	stw r30, 0x20(r1)
/* 80127DF8 001249D8  7C 7E 1B 78 */	mr r30, r3
/* 80127DFC 001249DC  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 80127E00 001249E0  80 03 23 44 */	lwz r0, 0x2344(r3)
/* 80127E04 001249E4  2C 00 00 03 */	cmpwi r0, 3
/* 80127E08 001249E8  41 82 00 10 */	beq lbl_80127E18
/* 80127E0C 001249EC  80 03 22 00 */	lwz r0, 0x2200(r3)
/* 80127E10 001249F0  28 00 00 00 */	cmplwi r0, 0
/* 80127E14 001249F4  41 82 00 30 */	beq lbl_80127E44
lbl_80127E18:
/* 80127E18 001249F8  38 00 00 00 */	li r0, 0
/* 80127E1C 001249FC  90 03 21 DC */	stw r0, 0x21dc(r3)
/* 80127E20 00124A00  38 7E 00 00 */	addi r3, r30, 0
/* 80127E24 00124A04  38 80 01 6A */	li r4, 0x16a
/* 80127E28 00124A08  C0 22 9F A0 */	lfs f1, lbl_804D9980@sda21(r2)
/* 80127E2C 00124A0C  38 A0 00 00 */	li r5, 0
/* 80127E30 00124A10  C0 42 9F A4 */	lfs f2, lbl_804D9984@sda21(r2)
/* 80127E34 00124A14  38 C0 00 00 */	li r6, 0
/* 80127E38 00124A18  FC 60 08 90 */	fmr f3, f1
/* 80127E3C 00124A1C  4B F4 15 71 */	bl Fighter_ActionStateChange_800693AC
/* 80127E40 00124A20  48 00 00 68 */	b lbl_80127EA8
lbl_80127E44:
/* 80127E44 00124A24  7F C3 F3 78 */	mr r3, r30
/* 80127E48 00124A28  4B FF F8 15 */	bl func_8012765C
/* 80127E4C 00124A2C  2C 03 00 00 */	cmpwi r3, 0
/* 80127E50 00124A30  41 82 00 58 */	beq lbl_80127EA8
/* 80127E54 00124A34  C0 22 9F A0 */	lfs f1, lbl_804D9980@sda21(r2)
/* 80127E58 00124A38  7F C3 F3 78 */	mr r3, r30
/* 80127E5C 00124A3C  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 80127E60 00124A40  38 80 01 69 */	li r4, 0x169
/* 80127E64 00124A44  FC 60 08 90 */	fmr f3, f1
/* 80127E68 00124A48  C0 42 9F A4 */	lfs f2, lbl_804D9984@sda21(r2)
/* 80127E6C 00124A4C  38 A0 00 00 */	li r5, 0
/* 80127E70 00124A50  38 C0 00 00 */	li r6, 0
/* 80127E74 00124A54  4B F4 15 39 */	bl Fighter_ActionStateChange_800693AC
/* 80127E78 00124A58  38 00 00 00 */	li r0, 0
/* 80127E7C 00124A5C  4C C6 31 82 */	crclr 6
/* 80127E80 00124A60  90 1F 22 00 */	stw r0, 0x2200(r31)
/* 80127E84 00124A64  38 7E 00 00 */	addi r3, r30, 0
/* 80127E88 00124A68  38 A0 00 00 */	li r5, 0
/* 80127E8C 00124A6C  90 1F 21 DC */	stw r0, 0x21dc(r31)
/* 80127E90 00124A70  38 C0 04 C0 */	li r6, 0x4c0
/* 80127E94 00124A74  80 9F 05 E8 */	lwz r4, 0x5e8(r31)
/* 80127E98 00124A78  81 1E 00 2C */	lwz r8, 0x2c(r30)
/* 80127E9C 00124A7C  80 E4 00 00 */	lwz r7, 0(r4)
/* 80127EA0 00124A80  38 88 06 0C */	addi r4, r8, 0x60c
/* 80127EA4 00124A84  4B F3 F8 4D */	bl efAsync_Spawn
lbl_80127EA8:
/* 80127EA8 00124A88  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 80127EAC 00124A8C  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 80127EB0 00124A90  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 80127EB4 00124A94  38 21 00 28 */	addi r1, r1, 0x28
/* 80127EB8 00124A98  7C 08 03 A6 */	mtlr r0
/* 80127EBC 00124A9C  4E 80 00 20 */	blr 


.global func_80127EC0
func_80127EC0:
/* 80127EC0 00124AA0  7C 08 02 A6 */	mflr r0
/* 80127EC4 00124AA4  90 01 00 04 */	stw r0, 4(r1)
/* 80127EC8 00124AA8  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 80127ECC 00124AAC  93 E1 00 3C */	stw r31, 0x3c(r1)
/* 80127ED0 00124AB0  93 C1 00 38 */	stw r30, 0x38(r1)
/* 80127ED4 00124AB4  93 A1 00 34 */	stw r29, 0x34(r1)
/* 80127ED8 00124AB8  7C 7D 1B 78 */	mr r29, r3
/* 80127EDC 00124ABC  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 80127EE0 00124AC0  80 03 23 44 */	lwz r0, 0x2344(r3)
/* 80127EE4 00124AC4  2C 00 00 03 */	cmpwi r0, 3
/* 80127EE8 00124AC8  41 82 00 10 */	beq lbl_80127EF8
/* 80127EEC 00124ACC  80 03 22 00 */	lwz r0, 0x2200(r3)
/* 80127EF0 00124AD0  28 00 00 00 */	cmplwi r0, 0
/* 80127EF4 00124AD4  41 82 00 30 */	beq lbl_80127F24
lbl_80127EF8:
/* 80127EF8 00124AD8  38 00 00 00 */	li r0, 0
/* 80127EFC 00124ADC  90 03 21 DC */	stw r0, 0x21dc(r3)
/* 80127F00 00124AE0  38 7D 00 00 */	addi r3, r29, 0
/* 80127F04 00124AE4  38 80 01 6E */	li r4, 0x16e
/* 80127F08 00124AE8  C0 22 9F A0 */	lfs f1, lbl_804D9980@sda21(r2)
/* 80127F0C 00124AEC  38 A0 00 00 */	li r5, 0
/* 80127F10 00124AF0  C0 42 9F A4 */	lfs f2, lbl_804D9984@sda21(r2)
/* 80127F14 00124AF4  38 C0 00 00 */	li r6, 0
/* 80127F18 00124AF8  FC 60 08 90 */	fmr f3, f1
/* 80127F1C 00124AFC  4B F4 14 91 */	bl Fighter_ActionStateChange_800693AC
/* 80127F20 00124B00  48 00 00 74 */	b lbl_80127F94
lbl_80127F24:
/* 80127F24 00124B04  7F A3 EB 78 */	mr r3, r29
/* 80127F28 00124B08  4B FF F7 35 */	bl func_8012765C
/* 80127F2C 00124B0C  2C 03 00 00 */	cmpwi r3, 0
/* 80127F30 00124B10  41 82 00 64 */	beq lbl_80127F94
/* 80127F34 00124B14  C0 22 9F A0 */	lfs f1, lbl_804D9980@sda21(r2)
/* 80127F38 00124B18  7F A3 EB 78 */	mr r3, r29
/* 80127F3C 00124B1C  83 FD 00 2C */	lwz r31, 0x2c(r29)
/* 80127F40 00124B20  38 80 01 6D */	li r4, 0x16d
/* 80127F44 00124B24  FC 60 08 90 */	fmr f3, f1
/* 80127F48 00124B28  83 DF 02 D4 */	lwz r30, 0x2d4(r31)
/* 80127F4C 00124B2C  38 A0 00 00 */	li r5, 0
/* 80127F50 00124B30  C0 42 9F A4 */	lfs f2, lbl_804D9984@sda21(r2)
/* 80127F54 00124B34  38 C0 00 00 */	li r6, 0
/* 80127F58 00124B38  4B F4 14 55 */	bl Fighter_ActionStateChange_800693AC
/* 80127F5C 00124B3C  38 00 00 00 */	li r0, 0
/* 80127F60 00124B40  4C C6 31 82 */	crclr 6
/* 80127F64 00124B44  90 1F 22 00 */	stw r0, 0x2200(r31)
/* 80127F68 00124B48  38 7D 00 00 */	addi r3, r29, 0
/* 80127F6C 00124B4C  38 A0 00 00 */	li r5, 0
/* 80127F70 00124B50  90 1F 21 DC */	stw r0, 0x21dc(r31)
/* 80127F74 00124B54  38 C0 04 C0 */	li r6, 0x4c0
/* 80127F78 00124B58  C0 1E 00 B4 */	lfs f0, 0xb4(r30)
/* 80127F7C 00124B5C  D0 1F 00 84 */	stfs f0, 0x84(r31)
/* 80127F80 00124B60  80 9F 05 E8 */	lwz r4, 0x5e8(r31)
/* 80127F84 00124B64  81 1D 00 2C */	lwz r8, 0x2c(r29)
/* 80127F88 00124B68  80 E4 00 00 */	lwz r7, 0(r4)
/* 80127F8C 00124B6C  38 88 06 0C */	addi r4, r8, 0x60c
/* 80127F90 00124B70  4B F3 F7 61 */	bl efAsync_Spawn
lbl_80127F94:
/* 80127F94 00124B74  80 01 00 44 */	lwz r0, 0x44(r1)
/* 80127F98 00124B78  83 E1 00 3C */	lwz r31, 0x3c(r1)
/* 80127F9C 00124B7C  83 C1 00 38 */	lwz r30, 0x38(r1)
/* 80127FA0 00124B80  83 A1 00 34 */	lwz r29, 0x34(r1)
/* 80127FA4 00124B84  38 21 00 40 */	addi r1, r1, 0x40
/* 80127FA8 00124B88  7C 08 03 A6 */	mtlr r0
/* 80127FAC 00124B8C  4E 80 00 20 */	blr 
.global lbl_80127FB0
lbl_80127FB0:
/* 80127FB0 00124B90  7C 08 02 A6 */	mflr r0
/* 80127FB4 00124B94  90 01 00 04 */	stw r0, 4(r1)
/* 80127FB8 00124B98  94 21 FF F8 */	stwu r1, -8(r1)
/* 80127FBC 00124B9C  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 80127FC0 00124BA0  80 04 22 00 */	lwz r0, 0x2200(r4)
/* 80127FC4 00124BA4  28 00 00 00 */	cmplwi r0, 0
/* 80127FC8 00124BA8  41 82 00 28 */	beq lbl_80127FF0
/* 80127FCC 00124BAC  38 00 00 00 */	li r0, 0
/* 80127FD0 00124BB0  90 04 21 DC */	stw r0, 0x21dc(r4)
/* 80127FD4 00124BB4  38 80 01 6A */	li r4, 0x16a
/* 80127FD8 00124BB8  38 A0 00 00 */	li r5, 0
/* 80127FDC 00124BBC  C0 22 9F A0 */	lfs f1, lbl_804D9980@sda21(r2)
/* 80127FE0 00124BC0  38 C0 00 00 */	li r6, 0
/* 80127FE4 00124BC4  C0 42 9F A4 */	lfs f2, lbl_804D9984@sda21(r2)
/* 80127FE8 00124BC8  FC 60 08 90 */	fmr f3, f1
/* 80127FEC 00124BCC  4B F4 13 C1 */	bl Fighter_ActionStateChange_800693AC
lbl_80127FF0:
/* 80127FF0 00124BD0  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80127FF4 00124BD4  38 21 00 08 */	addi r1, r1, 8
/* 80127FF8 00124BD8  7C 08 03 A6 */	mtlr r0
/* 80127FFC 00124BDC  4E 80 00 20 */	blr 
.global lbl_80128000
lbl_80128000:
/* 80128000 00124BE0  7C 08 02 A6 */	mflr r0
/* 80128004 00124BE4  90 01 00 04 */	stw r0, 4(r1)
/* 80128008 00124BE8  94 21 FF F8 */	stwu r1, -8(r1)
/* 8012800C 00124BEC  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 80128010 00124BF0  80 04 22 00 */	lwz r0, 0x2200(r4)
/* 80128014 00124BF4  28 00 00 00 */	cmplwi r0, 0
/* 80128018 00124BF8  41 82 00 28 */	beq lbl_80128040
/* 8012801C 00124BFC  38 00 00 00 */	li r0, 0
/* 80128020 00124C00  90 04 21 DC */	stw r0, 0x21dc(r4)
/* 80128024 00124C04  38 80 01 6E */	li r4, 0x16e
/* 80128028 00124C08  38 A0 00 00 */	li r5, 0
/* 8012802C 00124C0C  C0 22 9F A0 */	lfs f1, lbl_804D9980@sda21(r2)
/* 80128030 00124C10  38 C0 00 00 */	li r6, 0
/* 80128034 00124C14  C0 42 9F A4 */	lfs f2, lbl_804D9984@sda21(r2)
/* 80128038 00124C18  FC 60 08 90 */	fmr f3, f1
/* 8012803C 00124C1C  4B F4 13 71 */	bl Fighter_ActionStateChange_800693AC
lbl_80128040:
/* 80128040 00124C20  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80128044 00124C24  38 21 00 08 */	addi r1, r1, 8
/* 80128048 00124C28  7C 08 03 A6 */	mtlr r0
/* 8012804C 00124C2C  4E 80 00 20 */	blr 
.global lbl_80128050
lbl_80128050:
/* 80128050 00124C30  7C 08 02 A6 */	mflr r0
/* 80128054 00124C34  90 01 00 04 */	stw r0, 4(r1)
/* 80128058 00124C38  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8012805C 00124C3C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80128060 00124C40  7C 7F 1B 78 */	mr r31, r3
/* 80128064 00124C44  4B F4 71 D5 */	bl func_8006F238
/* 80128068 00124C48  2C 03 00 00 */	cmpwi r3, 0
/* 8012806C 00124C4C  40 82 00 0C */	bne lbl_80128078
/* 80128070 00124C50  7F E3 FB 78 */	mr r3, r31
/* 80128074 00124C54  4B F6 22 49 */	bl func_8008A2BC
lbl_80128078:
/* 80128078 00124C58  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8012807C 00124C5C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80128080 00124C60  38 21 00 18 */	addi r1, r1, 0x18
/* 80128084 00124C64  7C 08 03 A6 */	mtlr r0
/* 80128088 00124C68  4E 80 00 20 */	blr 
.global lbl_8012808C
lbl_8012808C:
/* 8012808C 00124C6C  7C 08 02 A6 */	mflr r0
/* 80128090 00124C70  90 01 00 04 */	stw r0, 4(r1)
/* 80128094 00124C74  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80128098 00124C78  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8012809C 00124C7C  7C 7F 1B 78 */	mr r31, r3
/* 801280A0 00124C80  4B F4 71 99 */	bl func_8006F238
/* 801280A4 00124C84  2C 03 00 00 */	cmpwi r3, 0
/* 801280A8 00124C88  40 82 00 0C */	bne lbl_801280B4
/* 801280AC 00124C8C  7F E3 FB 78 */	mr r3, r31
/* 801280B0 00124C90  4B FA 46 81 */	bl func_800CC730
lbl_801280B4:
/* 801280B4 00124C94  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 801280B8 00124C98  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 801280BC 00124C9C  38 21 00 18 */	addi r1, r1, 0x18
/* 801280C0 00124CA0  7C 08 03 A6 */	mtlr r0
/* 801280C4 00124CA4  4E 80 00 20 */	blr 
.global lbl_801280C8
lbl_801280C8:
/* 801280C8 00124CA8  7C 08 02 A6 */	mflr r0
/* 801280CC 00124CAC  90 01 00 04 */	stw r0, 4(r1)
/* 801280D0 00124CB0  94 21 FF F8 */	stwu r1, -8(r1)
/* 801280D4 00124CB4  4B F5 CE 69 */	bl func_80084F3C
/* 801280D8 00124CB8  80 01 00 0C */	lwz r0, 0xc(r1)
/* 801280DC 00124CBC  38 21 00 08 */	addi r1, r1, 8
/* 801280E0 00124CC0  7C 08 03 A6 */	mtlr r0
/* 801280E4 00124CC4  4E 80 00 20 */	blr 
.global lbl_801280E8
lbl_801280E8:
/* 801280E8 00124CC8  7C 08 02 A6 */	mflr r0
/* 801280EC 00124CCC  90 01 00 04 */	stw r0, 4(r1)
/* 801280F0 00124CD0  94 21 FF F8 */	stwu r1, -8(r1)
/* 801280F4 00124CD4  4B F5 CD F9 */	bl func_80084EEC
/* 801280F8 00124CD8  80 01 00 0C */	lwz r0, 0xc(r1)
/* 801280FC 00124CDC  38 21 00 08 */	addi r1, r1, 8
/* 80128100 00124CE0  7C 08 03 A6 */	mtlr r0
/* 80128104 00124CE4  4E 80 00 20 */	blr 
.global lbl_80128108
lbl_80128108:
/* 80128108 00124CE8  7C 08 02 A6 */	mflr r0
/* 8012810C 00124CEC  90 01 00 04 */	stw r0, 4(r1)
/* 80128110 00124CF0  94 21 FF F8 */	stwu r1, -8(r1)
/* 80128114 00124CF4  4B F5 CE 29 */	bl func_80084F3C
/* 80128118 00124CF8  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8012811C 00124CFC  38 21 00 08 */	addi r1, r1, 8
/* 80128120 00124D00  7C 08 03 A6 */	mtlr r0
/* 80128124 00124D04  4E 80 00 20 */	blr 
.global lbl_80128128
lbl_80128128:
/* 80128128 00124D08  7C 08 02 A6 */	mflr r0
/* 8012812C 00124D0C  90 01 00 04 */	stw r0, 4(r1)
/* 80128130 00124D10  94 21 FF F8 */	stwu r1, -8(r1)
/* 80128134 00124D14  4B F5 CD B9 */	bl func_80084EEC
/* 80128138 00124D18  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8012813C 00124D1C  38 21 00 08 */	addi r1, r1, 8
/* 80128140 00124D20  7C 08 03 A6 */	mtlr r0
/* 80128144 00124D24  4E 80 00 20 */	blr 
.global lbl_80128148
lbl_80128148:
/* 80128148 00124D28  7C 08 02 A6 */	mflr r0
/* 8012814C 00124D2C  90 01 00 04 */	stw r0, 4(r1)
/* 80128150 00124D30  94 21 FF F8 */	stwu r1, -8(r1)
/* 80128154 00124D34  4B F5 CD E9 */	bl func_80084F3C
/* 80128158 00124D38  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8012815C 00124D3C  38 21 00 08 */	addi r1, r1, 8
/* 80128160 00124D40  7C 08 03 A6 */	mtlr r0
/* 80128164 00124D44  4E 80 00 20 */	blr 
.global lbl_80128168
lbl_80128168:
/* 80128168 00124D48  7C 08 02 A6 */	mflr r0
/* 8012816C 00124D4C  90 01 00 04 */	stw r0, 4(r1)
/* 80128170 00124D50  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80128174 00124D54  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80128178 00124D58  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8012817C 00124D5C  80 9F 02 D4 */	lwz r4, 0x2d4(r31)
/* 80128180 00124D60  7F E3 FB 78 */	mr r3, r31
/* 80128184 00124D64  C0 5F 01 70 */	lfs f2, 0x170(r31)
/* 80128188 00124D68  C0 24 00 B8 */	lfs f1, 0xb8(r4)
/* 8012818C 00124D6C  4B F5 53 09 */	bl func_8007D494
/* 80128190 00124D70  7F E3 FB 78 */	mr r3, r31
/* 80128194 00124D74  4B F5 4D C5 */	bl func_8007CF58
/* 80128198 00124D78  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8012819C 00124D7C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 801281A0 00124D80  38 21 00 20 */	addi r1, r1, 0x20
/* 801281A4 00124D84  7C 08 03 A6 */	mtlr r0
/* 801281A8 00124D88  4E 80 00 20 */	blr 
.global lbl_801281AC
lbl_801281AC:
/* 801281AC 00124D8C  7C 08 02 A6 */	mflr r0
/* 801281B0 00124D90  90 01 00 04 */	stw r0, 4(r1)
/* 801281B4 00124D94  94 21 FF F8 */	stwu r1, -8(r1)
/* 801281B8 00124D98  4B F5 CD 85 */	bl func_80084F3C
/* 801281BC 00124D9C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 801281C0 00124DA0  38 21 00 08 */	addi r1, r1, 8
/* 801281C4 00124DA4  7C 08 03 A6 */	mtlr r0
/* 801281C8 00124DA8  4E 80 00 20 */	blr 
.global lbl_801281CC
lbl_801281CC:
/* 801281CC 00124DAC  7C 08 02 A6 */	mflr r0
/* 801281D0 00124DB0  90 01 00 04 */	stw r0, 4(r1)
/* 801281D4 00124DB4  94 21 FF F8 */	stwu r1, -8(r1)
/* 801281D8 00124DB8  4B F5 CD 15 */	bl func_80084EEC
/* 801281DC 00124DBC  80 01 00 0C */	lwz r0, 0xc(r1)
/* 801281E0 00124DC0  38 21 00 08 */	addi r1, r1, 8
/* 801281E4 00124DC4  7C 08 03 A6 */	mtlr r0
/* 801281E8 00124DC8  4E 80 00 20 */	blr 
.global lbl_801281EC
lbl_801281EC:
/* 801281EC 00124DCC  7C 08 02 A6 */	mflr r0
/* 801281F0 00124DD0  3C 80 80 12 */	lis r4, func_801279EC@ha
/* 801281F4 00124DD4  90 01 00 04 */	stw r0, 4(r1)
/* 801281F8 00124DD8  38 84 79 EC */	addi r4, r4, func_801279EC@l
/* 801281FC 00124DDC  94 21 FF F8 */	stwu r1, -8(r1)
/* 80128200 00124DE0  4B F5 BE 3D */	bl func_8008403C
/* 80128204 00124DE4  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80128208 00124DE8  38 21 00 08 */	addi r1, r1, 8
/* 8012820C 00124DEC  7C 08 03 A6 */	mtlr r0
/* 80128210 00124DF0  4E 80 00 20 */	blr 
.global lbl_80128214
lbl_80128214:
/* 80128214 00124DF4  7C 08 02 A6 */	mflr r0
/* 80128218 00124DF8  3C 80 80 12 */	lis r4, func_8012798C@ha
/* 8012821C 00124DFC  90 01 00 04 */	stw r0, 4(r1)
/* 80128220 00124E00  38 84 79 8C */	addi r4, r4, func_8012798C@l
/* 80128224 00124E04  94 21 FF F8 */	stwu r1, -8(r1)
/* 80128228 00124E08  4B F5 AA 4D */	bl func_80082C74
/* 8012822C 00124E0C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80128230 00124E10  38 21 00 08 */	addi r1, r1, 8
/* 80128234 00124E14  7C 08 03 A6 */	mtlr r0
/* 80128238 00124E18  4E 80 00 20 */	blr 
.global lbl_8012823C
lbl_8012823C:
/* 8012823C 00124E1C  7C 08 02 A6 */	mflr r0
/* 80128240 00124E20  3C 80 80 12 */	lis r4, func_80127ACC@ha
/* 80128244 00124E24  90 01 00 04 */	stw r0, 4(r1)
/* 80128248 00124E28  38 84 7A CC */	addi r4, r4, func_80127ACC@l
/* 8012824C 00124E2C  94 21 FF F8 */	stwu r1, -8(r1)
/* 80128250 00124E30  4B F5 BD ED */	bl func_8008403C
/* 80128254 00124E34  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80128258 00124E38  38 21 00 08 */	addi r1, r1, 8
/* 8012825C 00124E3C  7C 08 03 A6 */	mtlr r0
/* 80128260 00124E40  4E 80 00 20 */	blr 
.global lbl_80128264
lbl_80128264:
/* 80128264 00124E44  7C 08 02 A6 */	mflr r0
/* 80128268 00124E48  3C 80 80 12 */	lis r4, func_80127A54@ha
/* 8012826C 00124E4C  90 01 00 04 */	stw r0, 4(r1)
/* 80128270 00124E50  38 84 7A 54 */	addi r4, r4, func_80127A54@l
/* 80128274 00124E54  94 21 FF F8 */	stwu r1, -8(r1)
/* 80128278 00124E58  4B F5 A9 FD */	bl func_80082C74
/* 8012827C 00124E5C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80128280 00124E60  38 21 00 08 */	addi r1, r1, 8
/* 80128284 00124E64  7C 08 03 A6 */	mtlr r0
/* 80128288 00124E68  4E 80 00 20 */	blr 
.global lbl_8012828C
lbl_8012828C:
/* 8012828C 00124E6C  7C 08 02 A6 */	mflr r0
/* 80128290 00124E70  3C 80 80 12 */	lis r4, func_80127BAC@ha
/* 80128294 00124E74  90 01 00 04 */	stw r0, 4(r1)
/* 80128298 00124E78  38 84 7B AC */	addi r4, r4, func_80127BAC@l
/* 8012829C 00124E7C  94 21 FF F8 */	stwu r1, -8(r1)
/* 801282A0 00124E80  4B F5 BD 9D */	bl func_8008403C
/* 801282A4 00124E84  80 01 00 0C */	lwz r0, 0xc(r1)
/* 801282A8 00124E88  38 21 00 08 */	addi r1, r1, 8
/* 801282AC 00124E8C  7C 08 03 A6 */	mtlr r0
/* 801282B0 00124E90  4E 80 00 20 */	blr 
.global lbl_801282B4
lbl_801282B4:
/* 801282B4 00124E94  7C 08 02 A6 */	mflr r0
/* 801282B8 00124E98  3C 80 80 12 */	lis r4, func_80127B4C@ha
/* 801282BC 00124E9C  90 01 00 04 */	stw r0, 4(r1)
/* 801282C0 00124EA0  38 84 7B 4C */	addi r4, r4, func_80127B4C@l
/* 801282C4 00124EA4  94 21 FF F8 */	stwu r1, -8(r1)
/* 801282C8 00124EA8  4B F5 A9 AD */	bl func_80082C74
/* 801282CC 00124EAC  80 01 00 0C */	lwz r0, 0xc(r1)
/* 801282D0 00124EB0  38 21 00 08 */	addi r1, r1, 8
/* 801282D4 00124EB4  7C 08 03 A6 */	mtlr r0
/* 801282D8 00124EB8  4E 80 00 20 */	blr 
.global lbl_801282DC
lbl_801282DC:
/* 801282DC 00124EBC  7C 08 02 A6 */	mflr r0
/* 801282E0 00124EC0  3C 80 80 12 */	lis r4, func_80127C74@ha
/* 801282E4 00124EC4  90 01 00 04 */	stw r0, 4(r1)
/* 801282E8 00124EC8  38 84 7C 74 */	addi r4, r4, func_80127C74@l
/* 801282EC 00124ECC  94 21 FF F8 */	stwu r1, -8(r1)
/* 801282F0 00124ED0  4B F5 BD 4D */	bl func_8008403C
/* 801282F4 00124ED4  80 01 00 0C */	lwz r0, 0xc(r1)
/* 801282F8 00124ED8  38 21 00 08 */	addi r1, r1, 8
/* 801282FC 00124EDC  7C 08 03 A6 */	mtlr r0
/* 80128300 00124EE0  4E 80 00 20 */	blr 
.global lbl_80128304
lbl_80128304:
/* 80128304 00124EE4  7C 08 02 A6 */	mflr r0
/* 80128308 00124EE8  3C 80 80 12 */	lis r4, func_80127C14@ha
/* 8012830C 00124EEC  90 01 00 04 */	stw r0, 4(r1)
/* 80128310 00124EF0  38 84 7C 14 */	addi r4, r4, func_80127C14@l
/* 80128314 00124EF4  94 21 FF F8 */	stwu r1, -8(r1)
/* 80128318 00124EF8  4B F5 A9 5D */	bl func_80082C74
/* 8012831C 00124EFC  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80128320 00124F00  38 21 00 08 */	addi r1, r1, 8
/* 80128324 00124F04  7C 08 03 A6 */	mtlr r0
/* 80128328 00124F08  4E 80 00 20 */	blr 


.section .data
    .balign 8
.global lbl_803CDD78
lbl_803CDD78:
    .4byte 0x00000127
    .4byte 0x00340111
    .4byte 0x12000000
    .4byte func_80124908
    .4byte func_80124B6C
    .4byte func_80124B74
    .4byte func_80124BB4
    .4byte func_800761C8
    .4byte 0x00000128
    .4byte 0x00340511
    .4byte 0x12000000
    .4byte func_80124A20
    .4byte func_80124B70
    .4byte func_80124B94
    .4byte func_80124C20
    .4byte func_800761C8
    .4byte 0x00000129
    .4byte 0x00340212
    .4byte 0x13000000
    .4byte func_80124F64
    .4byte func_80124FDC
    .4byte func_80124FE4
    .4byte func_80125084
    .4byte func_800761C8
    .4byte 0x0000012A
    .4byte 0x00340212
    .4byte 0x13000000
    .4byte func_801251BC
    .4byte func_801252FC
    .4byte func_8012535C
    .4byte func_8012539C
    .4byte func_800761C8
    .4byte 0x0000012C
    .4byte 0x00340212
    .4byte 0x13000000
    .4byte func_8012590C
    .4byte func_8012594C
    .4byte func_80125954
    .4byte func_801259D4
    .4byte func_800761C8
    .4byte 0x0000012D
    .4byte 0x00340212
    .4byte 0x13000000
    .4byte func_80125B34
    .4byte func_80125BAC
    .4byte func_80125BB4
    .4byte func_80125C44
    .4byte func_800761C8
    .4byte 0x0000012B
    .4byte 0x00340212
    .4byte 0x13000000
    .4byte func_8012557C
    .4byte func_801256B4
    .4byte func_801256BC
    .4byte func_801256FC
    .4byte func_800761C8
    .4byte 0x0000012E
    .4byte 0x00340612
    .4byte 0x13000000
    .4byte func_80124FA0
    .4byte func_80124FE0
    .4byte func_80125024
    .4byte func_801250C0
    .4byte func_800761C8
    .4byte 0x0000012F
    .4byte 0x00340612
    .4byte 0x13000000
    .4byte func_8012525C
    .4byte func_8012532C
    .4byte func_8012537C
    .4byte func_801253D8
    .4byte func_800761C8
    .4byte 0x0000012C
    .4byte 0x00340612
    .4byte 0x13000000
    .4byte func_80125910
    .4byte func_80125950
    .4byte func_80125958
    .4byte func_801259D8
    .4byte func_800761C8
    .4byte 0x00000131
    .4byte 0x00340612
    .4byte 0x13000000
    .4byte func_80125B70
    .4byte func_80125BB0
    .4byte func_80125BF4
    .4byte func_80125C80
    .4byte func_800761C8
    .4byte 0x00000130
    .4byte 0x00340612
    .4byte 0x13000000
    .4byte func_8012561C
    .4byte func_801256B8
    .4byte func_801256DC
    .4byte func_80125738
    .4byte func_800761C8
    .4byte 0x00000132
    .4byte 0x00340113
    .4byte 0x14000000
    .4byte func_80125ED8
    .4byte func_80125F50
    .4byte func_80125F58
    .4byte func_80125FD8
    .4byte func_800761C8
    .4byte 0x00000133
    .4byte 0x00340113
    .4byte 0x14000000
    .4byte func_80126144
    .4byte func_80126424
    .4byte func_801265D4
    .4byte func_80126614
    .4byte func_800761C8
    .4byte 0x00000134
    .4byte 0x00340113
    .4byte 0x14000000
    .4byte func_80127198
    .4byte func_801272D8
    .4byte func_801272E0
    .4byte func_8012738C
    .4byte func_800761C8
    .4byte 0x00000135
    .4byte 0x00340513
    .4byte 0x14000000
    .4byte func_80125F14
    .4byte func_80125F54
    .4byte func_80125F78
    .4byte func_80126014
    .4byte func_800761C8
    .4byte 0x00000136
    .4byte 0x00340513
    .4byte 0x14000000
    .4byte func_801262B4
    .4byte func_80126428
    .4byte func_801265F4
    .4byte func_801267C8
    .4byte func_800761C8
    .4byte 0x00000137
    .4byte 0x00340513
    .4byte 0x14000000
    .4byte func_80127228
    .4byte func_801272DC
    .4byte func_80127310
    .4byte func_801273D4
    .4byte func_800761C8
    .4byte 0x00000138
    .4byte 0x00340014
    .4byte 0x15000000
    .4byte func_80127CDC
    .4byte NULL
    .4byte lbl_801280C8
    .4byte lbl_801281EC
    .4byte func_800761C8
    .4byte 0x00000139
    .4byte 0x00340014
    .4byte 0x15000000
    .4byte func_80127DE4
    .4byte NULL
    .4byte lbl_80128108
    .4byte lbl_8012823C
    .4byte func_800761C8
    .4byte 0x0000013A
    .4byte 0x00340014
    .4byte 0x15000000
    .4byte lbl_80127FB0
    .4byte NULL
    .4byte lbl_80128148
    .4byte lbl_8012828C
    .4byte func_800761C8
    .4byte 0x0000013B
    .4byte 0x00340014
    .4byte 0x15000000
    .4byte lbl_80128050
    .4byte NULL
    .4byte lbl_801281AC
    .4byte lbl_801282DC
    .4byte func_800761C8
    .4byte 0x0000013C
    .4byte 0x00340414
    .4byte 0x15000000
    .4byte func_80127D60
    .4byte NULL
    .4byte lbl_801280E8
    .4byte lbl_80128214
    .4byte func_800761C8
    .4byte 0x0000013D
    .4byte 0x00340414
    .4byte 0x15000000
    .4byte func_80127EC0
    .4byte NULL
    .4byte lbl_80128128
    .4byte lbl_80128264
    .4byte func_800761C8
    .4byte 0x0000013E
    .4byte 0x00340414
    .4byte 0x15000000
    .4byte lbl_80128000
    .4byte NULL
    .4byte lbl_80128168
    .4byte lbl_801282B4
    .4byte func_800761C8
    .4byte 0x0000013F
    .4byte 0x00340414
    .4byte 0x15000000
    .4byte lbl_8012808C
    .4byte NULL
    .4byte lbl_801281CC
    .4byte lbl_80128304
    .4byte func_800761C8
.global lbl_803CE0B8
lbl_803CE0B8:
    .asciz "PlPk.dat"
    .balign 4
.global lbl_803CE0C4
lbl_803CE0C4:
    .asciz "ftDataPikachu"
    .balign 4
.global lbl_803CE0D4
lbl_803CE0D4:
    .asciz "PlPkNr.dat"
    .balign 4
.global lbl_803CE0E0
lbl_803CE0E0:
    .asciz "PlyPikachu5K_Share_joint"
    .balign 4
.global lbl_803CE0FC
lbl_803CE0FC:
    .asciz "PlyPikachu5K_Share_matanim_joint"
    .balign 4
.global lbl_803CE120
lbl_803CE120:
    .asciz "PlPkRe.dat"
    .balign 4
.global lbl_803CE12C
lbl_803CE12C:
    .asciz "PlyPikachu5KRe_Share_joint"
    .balign 4
.global lbl_803CE148
lbl_803CE148:
    .asciz "PlyPikachu5KRe_Share_matanim_joint"
    .balign 4
.global lbl_803CE16C
lbl_803CE16C:
    .asciz "PlPkBu.dat"
    .balign 4
.global lbl_803CE178
lbl_803CE178:
    .asciz "PlyPikachu5KBu_Share_joint"
    .balign 4
.global lbl_803CE194
lbl_803CE194:
    .asciz "PlyPikachu5KBu_Share_matanim_joint"
    .balign 4
.global lbl_803CE1B8
lbl_803CE1B8:
    .asciz "PlPkGr.dat"
    .balign 4
.global lbl_803CE1C4
lbl_803CE1C4:
    .asciz "PlyPikachu5KGr_Share_joint"
    .balign 4
.global lbl_803CE1E0
lbl_803CE1E0:
    .asciz "PlyPikachu5KGr_Share_matanim_joint"
    .balign 4
.global lbl_803CE204
lbl_803CE204:
    .asciz "PlPkAJ.dat"
    .balign 4
.global lbl_803CE210
lbl_803CE210:
    .asciz "ftDemoResultMotionFilePikachu"
    .balign 4
.global lbl_803CE230
lbl_803CE230:
    .asciz "ftDemoIntroMotionFilePikachu"
    .balign 4
.global lbl_803CE250
lbl_803CE250:
    .asciz "ftDemoEndingMotionFilePikachu"
    .balign 4
.global lbl_803CE270
lbl_803CE270:
    .asciz "ftDemoViWaitMotionFilePikachu"
    .balign 4
.global lbl_803CE290
lbl_803CE290:
    .4byte lbl_803CE210
    .4byte lbl_803CE230
    .4byte lbl_803CE250
    .4byte lbl_803CE270
.global lbl_803CE2A0
lbl_803CE2A0:
    .4byte lbl_803CE0D4
    .4byte lbl_803CE0E0
    .4byte lbl_803CE0FC
    .4byte lbl_803CE120
    .4byte lbl_803CE12C
    .4byte lbl_803CE148
    .4byte lbl_803CE16C
    .4byte lbl_803CE178
    .4byte lbl_803CE194
    .4byte lbl_803CE1B8
    .4byte lbl_803CE1C4
    .4byte lbl_803CE1E0

.section .sdata2
    .balign 8

.global lbl_804D9980
lbl_804D9980:
	.4byte 0x00000000
.global lbl_804D9984
lbl_804D9984:
	.4byte 0x3F800000
