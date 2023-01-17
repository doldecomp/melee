.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

.global lbl_80221C14
lbl_80221C14:
/* 80221C14 0021E7F4  7C 08 02 A6 */	mflr r0
/* 80221C18 0021E7F8  3C 60 80 4A */	lis r3, stage_info@ha
/* 80221C1C 0021E7FC  90 01 00 04 */	stw r0, 4(r1)
/* 80221C20 0021E800  38 63 E6 C8 */	addi r3, r3, stage_info@l
/* 80221C24 0021E804  38 A3 00 8C */	addi r5, r3, 0x8c
/* 80221C28 0021E808  94 21 FF F8 */	stwu r1, -8(r1)
/* 80221C2C 0021E80C  38 80 00 01 */	li r4, 1
/* 80221C30 0021E810  88 03 00 8C */	lbz r0, 0x8c(r3)
/* 80221C34 0021E814  38 60 00 00 */	li r3, 0
/* 80221C38 0021E818  50 60 1F 38 */	rlwimi r0, r3, 3, 0x1c, 0x1c
/* 80221C3C 0021E81C  98 05 00 00 */	stb r0, 0(r5)
/* 80221C40 0021E820  38 60 00 00 */	li r3, 0
/* 80221C44 0021E824  88 05 00 00 */	lbz r0, 0(r5)
/* 80221C48 0021E828  50 80 17 7A */	rlwimi r0, r4, 2, 0x1d, 0x1d
/* 80221C4C 0021E82C  98 05 00 00 */	stb r0, 0(r5)
/* 80221C50 0021E830  48 00 00 65 */	bl func_80221CB4
/* 80221C54 0021E834  38 60 00 01 */	li r3, 1
/* 80221C58 0021E838  48 00 00 5D */	bl func_80221CB4
/* 80221C5C 0021E83C  38 60 00 02 */	li r3, 2
/* 80221C60 0021E840  48 00 00 55 */	bl func_80221CB4
/* 80221C64 0021E844  4B FA 1D 5D */	bl func_801C39C0
/* 80221C68 0021E848  4B FA 1F 4D */	bl func_801C3BB4
/* 80221C6C 0021E84C  4B FA 25 A5 */	bl func_801C4210
/* 80221C70 0021E850  4B FA 26 3D */	bl func_801C42AC
/* 80221C74 0021E854  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80221C78 0021E858  38 21 00 08 */	addi r1, r1, 8
/* 80221C7C 0021E85C  7C 08 03 A6 */	mtlr r0
/* 80221C80 0021E860  4E 80 00 20 */	blr
.global lbl_80221C84
lbl_80221C84:
/* 80221C84 0021E864  4E 80 00 20 */	blr
.global lbl_80221C88
lbl_80221C88:
/* 80221C88 0021E868  7C 08 02 A6 */	mflr r0
/* 80221C8C 0021E86C  38 60 00 00 */	li r3, 0
/* 80221C90 0021E870  90 01 00 04 */	stw r0, 4(r1)
/* 80221C94 0021E874  94 21 FF F8 */	stwu r1, -8(r1)
/* 80221C98 0021E878  4B FA 91 6D */	bl func_801CAE04
/* 80221C9C 0021E87C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80221CA0 0021E880  38 21 00 08 */	addi r1, r1, 8
/* 80221CA4 0021E884  7C 08 03 A6 */	mtlr r0
/* 80221CA8 0021E888  4E 80 00 20 */	blr

.global lbl_80221CAC
lbl_80221CAC:
/* 80221CAC 0021E88C  38 60 00 00 */	li r3, 0
/* 80221CB0 0021E890  4E 80 00 20 */	blr

.global func_80221CB4
func_80221CB4:
/* 80221CB4 0021E894  7C 08 02 A6 */	mflr r0
/* 80221CB8 0021E898  90 01 00 04 */	stw r0, 4(r1)
/* 80221CBC 0021E89C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80221CC0 0021E8A0  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80221CC4 0021E8A4  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80221CC8 0021E8A8  93 A1 00 14 */	stw r29, 0x14(r1)
/* 80221CCC 0021E8AC  93 81 00 10 */	stw r28, 0x10(r1)
/* 80221CD0 0021E8B0  3B 83 00 00 */	addi r28, r3, 0
/* 80221CD4 0021E8B4  1C 1C 00 14 */	mulli r0, r28, 0x14
/* 80221CD8 0021E8B8  3C 60 80 3F */	lis r3, lbl_803E8DF0@ha
/* 80221CDC 0021E8BC  3B E3 8D F0 */	addi r31, r3, lbl_803E8DF0@l
/* 80221CE0 0021E8C0  38 7C 00 00 */	addi r3, r28, 0
/* 80221CE4 0021E8C4  7F BF 02 14 */	add r29, r31, r0
/* 80221CE8 0021E8C8  4B F9 F7 E9 */	bl func_801C14D0
/* 80221CEC 0021E8CC  7C 7E 1B 79 */	or. r30, r3, r3
/* 80221CF0 0021E8D0  41 82 00 70 */	beq lbl_80221D60
/* 80221CF4 0021E8D4  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 80221CF8 0021E8D8  38 00 00 00 */	li r0, 0
/* 80221CFC 0021E8DC  3C 60 80 1C */	lis r3, func_801C5DB0@ha
/* 80221D00 0021E8E0  90 1F 00 08 */	stw r0, 8(r31)
/* 80221D04 0021E8E4  38 83 5D B0 */	addi r4, r3, func_801C5DB0@l
/* 80221D08 0021E8E8  38 7E 00 00 */	addi r3, r30, 0
/* 80221D0C 0021E8EC  90 1F 00 0C */	stw r0, 0xc(r31)
/* 80221D10 0021E8F0  38 A0 00 03 */	li r5, 3
/* 80221D14 0021E8F4  38 C0 00 00 */	li r6, 0
/* 80221D18 0021E8F8  48 16 E9 85 */	bl GObj_SetupGXLink
/* 80221D1C 0021E8FC  80 1D 00 0C */	lwz r0, 0xc(r29)
/* 80221D20 0021E900  28 00 00 00 */	cmplwi r0, 0
/* 80221D24 0021E904  41 82 00 08 */	beq lbl_80221D2C
/* 80221D28 0021E908  90 1F 00 1C */	stw r0, 0x1c(r31)
lbl_80221D2C:
/* 80221D2C 0021E90C  81 9D 00 00 */	lwz r12, 0(r29)
/* 80221D30 0021E910  28 0C 00 00 */	cmplwi r12, 0
/* 80221D34 0021E914  41 82 00 10 */	beq lbl_80221D44
/* 80221D38 0021E918  7D 88 03 A6 */	mtlr r12
/* 80221D3C 0021E91C  38 7E 00 00 */	addi r3, r30, 0
/* 80221D40 0021E920  4E 80 00 21 */	blrl
lbl_80221D44:
/* 80221D44 0021E924  80 9D 00 08 */	lwz r4, 8(r29)
/* 80221D48 0021E928  28 04 00 00 */	cmplwi r4, 0
/* 80221D4C 0021E92C  41 82 00 2C */	beq lbl_80221D78
/* 80221D50 0021E930  38 7E 00 00 */	addi r3, r30, 0
/* 80221D54 0021E934  38 A0 00 04 */	li r5, 4
/* 80221D58 0021E938  48 16 DF FD */	bl func_8038FD54
/* 80221D5C 0021E93C  48 00 00 1C */	b lbl_80221D78
lbl_80221D60:
/* 80221D60 0021E940  38 DC 00 00 */	addi r6, r28, 0
/* 80221D64 0021E944  4C C6 31 82 */	crclr 6
/* 80221D68 0021E948  38 7F 00 90 */	addi r3, r31, 0x90
/* 80221D6C 0021E94C  38 9F 00 B4 */	addi r4, r31, 0xb4
/* 80221D70 0021E950  38 A0 00 C3 */	li r5, 0xc3
/* 80221D74 0021E954  48 12 39 35 */	bl OSReport
lbl_80221D78:
/* 80221D78 0021E958  7F C3 F3 78 */	mr r3, r30
/* 80221D7C 0021E95C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80221D80 0021E960  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80221D84 0021E964  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80221D88 0021E968  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 80221D8C 0021E96C  83 81 00 10 */	lwz r28, 0x10(r1)
/* 80221D90 0021E970  38 21 00 20 */	addi r1, r1, 0x20
/* 80221D94 0021E974  7C 08 03 A6 */	mtlr r0
/* 80221D98 0021E978  4E 80 00 20 */	blr

.global lbl_80221D9C
lbl_80221D9C:
/* 80221D9C 0021E97C  7C 08 02 A6 */	mflr r0
/* 80221DA0 0021E980  38 A0 00 00 */	li r5, 0
/* 80221DA4 0021E984  90 01 00 04 */	stw r0, 4(r1)
/* 80221DA8 0021E988  94 21 FF F8 */	stwu r1, -8(r1)
/* 80221DAC 0021E98C  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 80221DB0 0021E990  80 84 00 14 */	lwz r4, 0x14(r4)
/* 80221DB4 0021E994  4B FA 63 85 */	bl func_801C8138
/* 80221DB8 0021E998  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80221DBC 0021E99C  38 21 00 08 */	addi r1, r1, 8
/* 80221DC0 0021E9A0  7C 08 03 A6 */	mtlr r0
/* 80221DC4 0021E9A4  4E 80 00 20 */	blr

.global lbl_80221DC8
lbl_80221DC8:
/* 80221DC8 0021E9A8  38 60 00 00 */	li r3, 0
/* 80221DCC 0021E9AC  4E 80 00 20 */	blr

.global lbl_80221DD0
lbl_80221DD0:
/* 80221DD0 0021E9B0  4E 80 00 20 */	blr

.global lbl_80221DD4
lbl_80221DD4:
/* 80221DD4 0021E9B4  4E 80 00 20 */	blr

.global lbl_80221DD8
lbl_80221DD8:
/* 80221DD8 0021E9B8  7C 08 02 A6 */	mflr r0
/* 80221DDC 0021E9BC  90 01 00 04 */	stw r0, 4(r1)
/* 80221DE0 0021E9C0  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80221DE4 0021E9C4  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80221DE8 0021E9C8  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80221DEC 0021E9CC  7C 7E 1B 78 */	mr r30, r3
/* 80221DF0 0021E9D0  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80221DF4 0021E9D4  80 63 00 28 */	lwz r3, 0x28(r3)
/* 80221DF8 0021E9D8  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80221DFC 0021E9DC  4B FA 10 D5 */	bl func_801C2ED0
/* 80221E00 0021E9E0  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80221E04 0021E9E4  38 7E 00 00 */	addi r3, r30, 0
/* 80221E08 0021E9E8  38 A0 00 00 */	li r5, 0
/* 80221E0C 0021E9EC  4B FA 63 2D */	bl func_801C8138
/* 80221E10 0021E9F0  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80221E14 0021E9F4  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80221E18 0021E9F8  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80221E1C 0021E9FC  38 21 00 20 */	addi r1, r1, 0x20
/* 80221E20 0021EA00  7C 08 03 A6 */	mtlr r0
/* 80221E24 0021EA04  4E 80 00 20 */	blr

.global lbl_80221E28
lbl_80221E28:
/* 80221E28 0021EA08  38 60 00 00 */	li r3, 0
/* 80221E2C 0021EA0C  4E 80 00 20 */	blr

.global lbl_80221E30
lbl_80221E30:
/* 80221E30 0021EA10  7C 08 02 A6 */	mflr r0
/* 80221E34 0021EA14  90 01 00 04 */	stw r0, 4(r1)
/* 80221E38 0021EA18  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80221E3C 0021EA1C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80221E40 0021EA20  7C 7F 1B 78 */	mr r31, r3
/* 80221E44 0021EA24  4B DE F7 B1 */	bl func_800115F4
/* 80221E48 0021EA28  7F E3 FB 78 */	mr r3, r31
/* 80221E4C 0021EA2C  4B FA 11 95 */	bl func_801C2FE0
/* 80221E50 0021EA30  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80221E54 0021EA34  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80221E58 0021EA38  38 21 00 18 */	addi r1, r1, 0x18
/* 80221E5C 0021EA3C  7C 08 03 A6 */	mtlr r0
/* 80221E60 0021EA40  4E 80 00 20 */	blr

.global lbl_80221E64
lbl_80221E64:
/* 80221E64 0021EA44  4E 80 00 20 */	blr

.global lbl_80221E68
lbl_80221E68:
/* 80221E68 0021EA48  7C 08 02 A6 */	mflr r0
/* 80221E6C 0021EA4C  90 01 00 04 */	stw r0, 4(r1)
/* 80221E70 0021EA50  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80221E74 0021EA54  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80221E78 0021EA58  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80221E7C 0021EA5C  7C 7E 1B 78 */	mr r30, r3
/* 80221E80 0021EA60  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80221E84 0021EA64  80 63 00 28 */	lwz r3, 0x28(r3)
/* 80221E88 0021EA68  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80221E8C 0021EA6C  4B FA 10 45 */	bl func_801C2ED0
/* 80221E90 0021EA70  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80221E94 0021EA74  38 7E 00 00 */	addi r3, r30, 0
/* 80221E98 0021EA78  38 A0 00 00 */	li r5, 0
/* 80221E9C 0021EA7C  4B FA 62 9D */	bl func_801C8138
/* 80221EA0 0021EA80  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80221EA4 0021EA84  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80221EA8 0021EA88  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80221EAC 0021EA8C  38 21 00 20 */	addi r1, r1, 0x20
/* 80221EB0 0021EA90  7C 08 03 A6 */	mtlr r0
/* 80221EB4 0021EA94  4E 80 00 20 */	blr

.global lbl_80221EB8
lbl_80221EB8:
/* 80221EB8 0021EA98  38 60 00 00 */	li r3, 0
/* 80221EBC 0021EA9C  4E 80 00 20 */	blr

.global lbl_80221EC0
lbl_80221EC0:
/* 80221EC0 0021EAA0  7C 08 02 A6 */	mflr r0
/* 80221EC4 0021EAA4  90 01 00 04 */	stw r0, 4(r1)
/* 80221EC8 0021EAA8  94 21 FF F8 */	stwu r1, -8(r1)
/* 80221ECC 0021EAAC  4B FA 11 15 */	bl func_801C2FE0
/* 80221ED0 0021EAB0  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80221ED4 0021EAB4  38 21 00 08 */	addi r1, r1, 8
/* 80221ED8 0021EAB8  7C 08 03 A6 */	mtlr r0
/* 80221EDC 0021EABC  4E 80 00 20 */	blr

.global lbl_80221EE0
lbl_80221EE0:
/* 80221EE0 0021EAC0  4E 80 00 20 */	blr

.global lbl_80221EE4
lbl_80221EE4:
/* 80221EE4 0021EAC4  38 60 00 00 */	li r3, 0
/* 80221EE8 0021EAC8  4E 80 00 20 */	blr

.global lbl_80221EEC
lbl_80221EEC:
/* 80221EEC 0021EACC  38 60 00 01 */	li r3, 1
/* 80221EF0 0021EAD0  4E 80 00 20 */	blr


.section .data
    .balign 4
# .global lbl_803E8E40
# lbl_803E8E40:
#     .4byte 0x2F477254
#     .4byte 0x4C672E64
#     .4byte 0x61740000
.global lbl_803E8E4C
lbl_803E8E4C:
    .4byte 0x00000033
    .4byte lbl_803E8DF0
    .4byte lbl_803E8E40
    .4byte lbl_80221C14
    .4byte func_80221C10
    .4byte lbl_80221C84
    .4byte lbl_80221C88
    .4byte lbl_80221CAC
    .4byte lbl_80221EE4
    .4byte lbl_80221EEC
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
    .4byte 0x6772746C
    .4byte 0x75696769
    .4byte 0x2E630000
