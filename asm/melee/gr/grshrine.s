.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

.global func_80201C60
func_80201C60:
/* 80201C60 001FE840  4E 80 00 20 */	blr 

.global func_80201C64
func_80201C64:
/* 80201C64 001FE844  7C 08 02 A6 */	mflr r0
/* 80201C68 001FE848  90 01 00 04 */	stw r0, 4(r1)
/* 80201C6C 001FE84C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80201C70 001FE850  4B FC 2D 89 */	bl func_801C49F8
/* 80201C74 001FE854  90 6D B3 78 */	stw r3, lbl_804D6A18@sda21(r13)
/* 80201C78 001FE858  38 60 00 00 */	li r3, 0
/* 80201C7C 001FE85C  48 00 00 A5 */	bl func_80201D20
/* 80201C80 001FE860  38 60 00 01 */	li r3, 1
/* 80201C84 001FE864  48 00 00 9D */	bl func_80201D20
/* 80201C88 001FE868  38 60 00 02 */	li r3, 2
/* 80201C8C 001FE86C  48 00 00 95 */	bl func_80201D20
/* 80201C90 001FE870  4B FC 1D 31 */	bl func_801C39C0
/* 80201C94 001FE874  4B FC 1F 21 */	bl func_801C3BB4
/* 80201C98 001FE878  3C 60 80 3C */	lis r3, lbl_803B8298@ha
/* 80201C9C 001FE87C  C0 82 BD 04 */	lfs f4, lbl_804DB6E4@sda21(r2)
/* 80201CA0 001FE880  38 A3 82 98 */	addi r5, r3, lbl_803B8298@l
/* 80201CA4 001FE884  C0 A2 BD 08 */	lfs f5, lbl_804DB6E8@sda21(r2)
/* 80201CA8 001FE888  80 65 00 00 */	lwz r3, 0(r5)
/* 80201CAC 001FE88C  FC E0 20 90 */	fmr f7, f4
/* 80201CB0 001FE890  80 05 00 04 */	lwz r0, 4(r5)
/* 80201CB4 001FE894  FC C0 28 90 */	fmr f6, f5
/* 80201CB8 001FE898  C0 22 BC F8 */	lfs f1, lbl_804DB6D8@sda21(r2)
/* 80201CBC 001FE89C  90 61 00 0C */	stw r3, 0xc(r1)
/* 80201CC0 001FE8A0  C0 42 BC FC */	lfs f2, lbl_804DB6DC@sda21(r2)
/* 80201CC4 001FE8A4  38 61 00 0C */	addi r3, r1, 0xc
/* 80201CC8 001FE8A8  90 01 00 10 */	stw r0, 0x10(r1)
/* 80201CCC 001FE8AC  38 80 FF FF */	li r4, -1
/* 80201CD0 001FE8B0  C0 62 BD 00 */	lfs f3, lbl_804DB6E0@sda21(r2)
/* 80201CD4 001FE8B4  80 05 00 08 */	lwz r0, 8(r5)
/* 80201CD8 001FE8B8  90 01 00 14 */	stw r0, 0x14(r1)
/* 80201CDC 001FE8BC  4B E0 FD 75 */	bl func_80011A50
/* 80201CE0 001FE8C0  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80201CE4 001FE8C4  38 21 00 20 */	addi r1, r1, 0x20
/* 80201CE8 001FE8C8  7C 08 03 A6 */	mtlr r0
/* 80201CEC 001FE8CC  4E 80 00 20 */	blr 
.global lbl_80201CF0
lbl_80201CF0:
/* 80201CF0 001FE8D0  4E 80 00 20 */	blr 
.global lbl_80201CF4
lbl_80201CF4:
/* 80201CF4 001FE8D4  7C 08 02 A6 */	mflr r0
/* 80201CF8 001FE8D8  38 60 00 00 */	li r3, 0
/* 80201CFC 001FE8DC  90 01 00 04 */	stw r0, 4(r1)
/* 80201D00 001FE8E0  94 21 FF F8 */	stwu r1, -8(r1)
/* 80201D04 001FE8E4  4B FC 91 01 */	bl func_801CAE04
/* 80201D08 001FE8E8  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80201D0C 001FE8EC  38 21 00 08 */	addi r1, r1, 8
/* 80201D10 001FE8F0  7C 08 03 A6 */	mtlr r0
/* 80201D14 001FE8F4  4E 80 00 20 */	blr 
.global lbl_80201D18
lbl_80201D18:
/* 80201D18 001FE8F8  38 60 00 00 */	li r3, 0
/* 80201D1C 001FE8FC  4E 80 00 20 */	blr 

.global func_80201D20
func_80201D20:
/* 80201D20 001FE900  7C 08 02 A6 */	mflr r0
/* 80201D24 001FE904  90 01 00 04 */	stw r0, 4(r1)
/* 80201D28 001FE908  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80201D2C 001FE90C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80201D30 001FE910  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80201D34 001FE914  93 A1 00 14 */	stw r29, 0x14(r1)
/* 80201D38 001FE918  93 81 00 10 */	stw r28, 0x10(r1)
/* 80201D3C 001FE91C  3B 83 00 00 */	addi r28, r3, 0
/* 80201D40 001FE920  1C 1C 00 14 */	mulli r0, r28, 0x14
/* 80201D44 001FE924  3C 60 80 3E */	lis r3, lbl_803E50E8@ha
/* 80201D48 001FE928  3B E3 50 E8 */	addi r31, r3, lbl_803E50E8@l
/* 80201D4C 001FE92C  38 7C 00 00 */	addi r3, r28, 0
/* 80201D50 001FE930  7F BF 02 14 */	add r29, r31, r0
/* 80201D54 001FE934  4B FB F7 7D */	bl func_801C14D0
/* 80201D58 001FE938  7C 7E 1B 79 */	or. r30, r3, r3
/* 80201D5C 001FE93C  41 82 00 70 */	beq lbl_80201DCC
/* 80201D60 001FE940  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 80201D64 001FE944  38 00 00 00 */	li r0, 0
/* 80201D68 001FE948  3C 60 80 1C */	lis r3, func_801C5DB0@ha
/* 80201D6C 001FE94C  90 1F 00 08 */	stw r0, 8(r31)
/* 80201D70 001FE950  38 83 5D B0 */	addi r4, r3, func_801C5DB0@l
/* 80201D74 001FE954  38 7E 00 00 */	addi r3, r30, 0
/* 80201D78 001FE958  90 1F 00 0C */	stw r0, 0xc(r31)
/* 80201D7C 001FE95C  38 A0 00 03 */	li r5, 3
/* 80201D80 001FE960  38 C0 00 00 */	li r6, 0
/* 80201D84 001FE964  48 18 E9 19 */	bl func_8039069C
/* 80201D88 001FE968  80 1D 00 0C */	lwz r0, 0xc(r29)
/* 80201D8C 001FE96C  28 00 00 00 */	cmplwi r0, 0
/* 80201D90 001FE970  41 82 00 08 */	beq lbl_80201D98
/* 80201D94 001FE974  90 1F 00 1C */	stw r0, 0x1c(r31)
lbl_80201D98:
/* 80201D98 001FE978  81 9D 00 00 */	lwz r12, 0(r29)
/* 80201D9C 001FE97C  28 0C 00 00 */	cmplwi r12, 0
/* 80201DA0 001FE980  41 82 00 10 */	beq lbl_80201DB0
/* 80201DA4 001FE984  7D 88 03 A6 */	mtlr r12
/* 80201DA8 001FE988  38 7E 00 00 */	addi r3, r30, 0
/* 80201DAC 001FE98C  4E 80 00 21 */	blrl 
lbl_80201DB0:
/* 80201DB0 001FE990  80 9D 00 08 */	lwz r4, 8(r29)
/* 80201DB4 001FE994  28 04 00 00 */	cmplwi r4, 0
/* 80201DB8 001FE998  41 82 00 2C */	beq lbl_80201DE4
/* 80201DBC 001FE99C  38 7E 00 00 */	addi r3, r30, 0
/* 80201DC0 001FE9A0  38 A0 00 04 */	li r5, 4
/* 80201DC4 001FE9A4  48 18 DF 91 */	bl func_8038FD54
/* 80201DC8 001FE9A8  48 00 00 1C */	b lbl_80201DE4
lbl_80201DCC:
/* 80201DCC 001FE9AC  38 DC 00 00 */	addi r6, r28, 0
/* 80201DD0 001FE9B0  4C C6 31 82 */	crclr 6
/* 80201DD4 001FE9B4  38 7F 00 7C */	addi r3, r31, 0x7c
/* 80201DD8 001FE9B8  38 9F 00 A0 */	addi r4, r31, 0xa0
/* 80201DDC 001FE9BC  38 A0 00 CD */	li r5, 0xcd
/* 80201DE0 001FE9C0  48 14 38 C9 */	bl OSReport
lbl_80201DE4:
/* 80201DE4 001FE9C4  7F C3 F3 78 */	mr r3, r30
/* 80201DE8 001FE9C8  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80201DEC 001FE9CC  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80201DF0 001FE9D0  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80201DF4 001FE9D4  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 80201DF8 001FE9D8  83 81 00 10 */	lwz r28, 0x10(r1)
/* 80201DFC 001FE9DC  38 21 00 20 */	addi r1, r1, 0x20
/* 80201E00 001FE9E0  7C 08 03 A6 */	mtlr r0
/* 80201E04 001FE9E4  4E 80 00 20 */	blr 
.global lbl_80201E08
lbl_80201E08:
/* 80201E08 001FE9E8  7C 08 02 A6 */	mflr r0
/* 80201E0C 001FE9EC  38 A0 00 00 */	li r5, 0
/* 80201E10 001FE9F0  90 01 00 04 */	stw r0, 4(r1)
/* 80201E14 001FE9F4  94 21 FF F8 */	stwu r1, -8(r1)
/* 80201E18 001FE9F8  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 80201E1C 001FE9FC  80 84 00 14 */	lwz r4, 0x14(r4)
/* 80201E20 001FEA00  4B FC 63 19 */	bl func_801C8138
/* 80201E24 001FEA04  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80201E28 001FEA08  38 21 00 08 */	addi r1, r1, 8
/* 80201E2C 001FEA0C  7C 08 03 A6 */	mtlr r0
/* 80201E30 001FEA10  4E 80 00 20 */	blr 
.global lbl_80201E34
lbl_80201E34:
/* 80201E34 001FEA14  38 60 00 00 */	li r3, 0
/* 80201E38 001FEA18  4E 80 00 20 */	blr 
.global lbl_80201E3C
lbl_80201E3C:
/* 80201E3C 001FEA1C  4E 80 00 20 */	blr 
.global lbl_80201E40
lbl_80201E40:
/* 80201E40 001FEA20  4E 80 00 20 */	blr 
.global lbl_80201E44
lbl_80201E44:
/* 80201E44 001FEA24  7C 08 02 A6 */	mflr r0
/* 80201E48 001FEA28  38 A0 00 00 */	li r5, 0
/* 80201E4C 001FEA2C  90 01 00 04 */	stw r0, 4(r1)
/* 80201E50 001FEA30  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80201E54 001FEA34  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80201E58 001FEA38  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80201E5C 001FEA3C  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80201E60 001FEA40  4B FC 62 D9 */	bl func_801C8138
/* 80201E64 001FEA44  88 1F 00 11 */	lbz r0, 0x11(r31)
/* 80201E68 001FEA48  38 60 00 02 */	li r3, 2
/* 80201E6C 001FEA4C  50 60 2E 34 */	rlwimi r0, r3, 5, 0x18, 0x1a
/* 80201E70 001FEA50  98 1F 00 11 */	stb r0, 0x11(r31)
/* 80201E74 001FEA54  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80201E78 001FEA58  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80201E7C 001FEA5C  38 21 00 18 */	addi r1, r1, 0x18
/* 80201E80 001FEA60  7C 08 03 A6 */	mtlr r0
/* 80201E84 001FEA64  4E 80 00 20 */	blr 
.global lbl_80201E88
lbl_80201E88:
/* 80201E88 001FEA68  38 60 00 00 */	li r3, 0
/* 80201E8C 001FEA6C  4E 80 00 20 */	blr 
.global lbl_80201E90
lbl_80201E90:
/* 80201E90 001FEA70  4E 80 00 20 */	blr 
.global lbl_80201E94
lbl_80201E94:
/* 80201E94 001FEA74  4E 80 00 20 */	blr 
lbl_80201E98:
/* 80201E98 001FEA78  4E 80 00 20 */	blr 
.global lbl_80201E9C
lbl_80201E9C:
/* 80201E9C 001FEA7C  7C 08 02 A6 */	mflr r0
/* 80201EA0 001FEA80  90 01 00 04 */	stw r0, 4(r1)
/* 80201EA4 001FEA84  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80201EA8 001FEA88  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80201EAC 001FEA8C  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80201EB0 001FEA90  7C 7E 1B 78 */	mr r30, r3
/* 80201EB4 001FEA94  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80201EB8 001FEA98  80 63 00 28 */	lwz r3, 0x28(r3)
/* 80201EBC 001FEA9C  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80201EC0 001FEAA0  4B FC 10 11 */	bl func_801C2ED0
/* 80201EC4 001FEAA4  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80201EC8 001FEAA8  38 7E 00 00 */	addi r3, r30, 0
/* 80201ECC 001FEAAC  38 A0 00 00 */	li r5, 0
/* 80201ED0 001FEAB0  4B FC 62 69 */	bl func_801C8138
/* 80201ED4 001FEAB4  3C 60 80 20 */	lis r3, lbl_80201E98@ha
/* 80201ED8 001FEAB8  38 83 1E 98 */	addi r4, r3, lbl_80201E98@l
/* 80201EDC 001FEABC  38 7E 00 00 */	addi r3, r30, 0
/* 80201EE0 001FEAC0  4B FB F1 D9 */	bl func_801C10B8
/* 80201EE4 001FEAC4  7F C3 F3 78 */	mr r3, r30
/* 80201EE8 001FEAC8  4B FC 10 F9 */	bl func_801C2FE0
/* 80201EEC 001FEACC  88 1F 00 10 */	lbz r0, 0x10(r31)
/* 80201EF0 001FEAD0  38 60 00 01 */	li r3, 1
/* 80201EF4 001FEAD4  50 60 17 7A */	rlwimi r0, r3, 2, 0x1d, 0x1d
/* 80201EF8 001FEAD8  98 1F 00 10 */	stb r0, 0x10(r31)
/* 80201EFC 001FEADC  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80201F00 001FEAE0  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80201F04 001FEAE4  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80201F08 001FEAE8  38 21 00 20 */	addi r1, r1, 0x20
/* 80201F0C 001FEAEC  7C 08 03 A6 */	mtlr r0
/* 80201F10 001FEAF0  4E 80 00 20 */	blr 
.global lbl_80201F14
lbl_80201F14:
/* 80201F14 001FEAF4  38 60 00 00 */	li r3, 0
/* 80201F18 001FEAF8  4E 80 00 20 */	blr 
.global lbl_80201F1C
lbl_80201F1C:
/* 80201F1C 001FEAFC  7C 08 02 A6 */	mflr r0
/* 80201F20 001FEB00  90 01 00 04 */	stw r0, 4(r1)
/* 80201F24 001FEB04  94 21 FF F8 */	stwu r1, -8(r1)
/* 80201F28 001FEB08  4B FC 10 B9 */	bl func_801C2FE0
/* 80201F2C 001FEB0C  4B E0 F6 C9 */	bl func_800115F4
/* 80201F30 001FEB10  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80201F34 001FEB14  38 21 00 08 */	addi r1, r1, 8
/* 80201F38 001FEB18  7C 08 03 A6 */	mtlr r0
/* 80201F3C 001FEB1C  4E 80 00 20 */	blr 
.global lbl_80201F40
lbl_80201F40:
/* 80201F40 001FEB20  4E 80 00 20 */	blr 
.global lbl_80201F44
lbl_80201F44:
/* 80201F44 001FEB24  38 60 00 00 */	li r3, 0
/* 80201F48 001FEB28  4E 80 00 20 */	blr 
.global lbl_80201F4C
lbl_80201F4C:
/* 80201F4C 001FEB2C  7C 08 02 A6 */	mflr r0
/* 80201F50 001FEB30  38 80 00 00 */	li r4, 0
/* 80201F54 001FEB34  90 01 00 04 */	stw r0, 4(r1)
/* 80201F58 001FEB38  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 80201F5C 001FEB3C  93 E1 00 24 */	stw r31, 0x24(r1)
/* 80201F60 001FEB40  3B E3 00 00 */	addi r31, r3, 0
/* 80201F64 001FEB44  38 65 00 00 */	addi r3, r5, 0
/* 80201F68 001FEB48  38 A1 00 14 */	addi r5, r1, 0x14
/* 80201F6C 001FEB4C  4B E0 92 61 */	bl func_8000B1CC
/* 80201F70 001FEB50  C0 3F 00 04 */	lfs f1, 4(r31)
/* 80201F74 001FEB54  C0 01 00 18 */	lfs f0, 0x18(r1)
/* 80201F78 001FEB58  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80201F7C 001FEB5C  40 81 00 0C */	ble lbl_80201F88
/* 80201F80 001FEB60  38 60 00 01 */	li r3, 1
/* 80201F84 001FEB64  48 00 00 08 */	b lbl_80201F8C
lbl_80201F88:
/* 80201F88 001FEB68  38 60 00 00 */	li r3, 0
lbl_80201F8C:
/* 80201F8C 001FEB6C  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 80201F90 001FEB70  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 80201F94 001FEB74  38 21 00 28 */	addi r1, r1, 0x28
/* 80201F98 001FEB78  7C 08 03 A6 */	mtlr r0
/* 80201F9C 001FEB7C  4E 80 00 20 */	blr 


.section .data

.global lbl_803E50E8
lbl_803E50E8:
	.4byte lbl_80201E08
	.4byte lbl_80201E34
	.4byte lbl_80201E3C
	.4byte lbl_80201E40
    .4byte NULL
	.4byte lbl_80201E44
	.4byte lbl_80201E88
	.4byte lbl_80201E90
	.4byte lbl_80201E94
    .4byte NULL
	.4byte lbl_80201E9C
	.4byte lbl_80201F14
	.4byte lbl_80201F1C
	.4byte lbl_80201F40
    .4byte 0xC0000000
.global lbl_803E5124
lbl_803E5124:
    .4byte 0x2F477253
    .4byte 0x682E6461
    .4byte 0x74000000
.global lbl_803E5130
lbl_803E5130:
    .4byte 0x00000007
    .4byte lbl_803E50E8
    .4byte lbl_803E5124
	.4byte func_80201C64
	.4byte func_80201C60
	.4byte lbl_80201CF0
	.4byte lbl_80201CF4
	.4byte lbl_80201D18
	.4byte lbl_80201F44
	.4byte lbl_80201F4C
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
    .4byte 0x67727368
    .4byte 0x72696E65
    .4byte 0x2E630000
    .4byte NULL
