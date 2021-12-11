.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

.global func_80222B98
func_80222B98:
/* 80222B98 0021F778  4E 80 00 20 */	blr 
.global lbl_80222B9C
lbl_80222B9C:
/* 80222B9C 0021F77C  7C 08 02 A6 */	mflr r0
/* 80222BA0 0021F780  3C 60 80 4A */	lis r3, stage_info@ha
/* 80222BA4 0021F784  90 01 00 04 */	stw r0, 4(r1)
/* 80222BA8 0021F788  38 63 E6 C8 */	addi r3, r3, stage_info@l
/* 80222BAC 0021F78C  38 A3 00 8C */	addi r5, r3, 0x8c
/* 80222BB0 0021F790  94 21 FF F8 */	stwu r1, -8(r1)
/* 80222BB4 0021F794  38 80 00 01 */	li r4, 1
/* 80222BB8 0021F798  88 03 00 8C */	lbz r0, 0x8c(r3)
/* 80222BBC 0021F79C  38 60 00 00 */	li r3, 0
/* 80222BC0 0021F7A0  50 60 1F 38 */	rlwimi r0, r3, 3, 0x1c, 0x1c
/* 80222BC4 0021F7A4  98 05 00 00 */	stb r0, 0(r5)
/* 80222BC8 0021F7A8  38 60 00 00 */	li r3, 0
/* 80222BCC 0021F7AC  88 05 00 00 */	lbz r0, 0(r5)
/* 80222BD0 0021F7B0  50 80 17 7A */	rlwimi r0, r4, 2, 0x1d, 0x1d
/* 80222BD4 0021F7B4  98 05 00 00 */	stb r0, 0(r5)
/* 80222BD8 0021F7B8  48 00 00 65 */	bl func_80222C3C
/* 80222BDC 0021F7BC  38 60 00 01 */	li r3, 1
/* 80222BE0 0021F7C0  48 00 00 5D */	bl func_80222C3C
/* 80222BE4 0021F7C4  38 60 00 02 */	li r3, 2
/* 80222BE8 0021F7C8  48 00 00 55 */	bl func_80222C3C
/* 80222BEC 0021F7CC  4B FA 0D D5 */	bl func_801C39C0
/* 80222BF0 0021F7D0  4B FA 0F C5 */	bl func_801C3BB4
/* 80222BF4 0021F7D4  4B FA 16 1D */	bl func_801C4210
/* 80222BF8 0021F7D8  4B FA 16 B5 */	bl func_801C42AC
/* 80222BFC 0021F7DC  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80222C00 0021F7E0  38 21 00 08 */	addi r1, r1, 8
/* 80222C04 0021F7E4  7C 08 03 A6 */	mtlr r0
/* 80222C08 0021F7E8  4E 80 00 20 */	blr 
.global lbl_80222C0C
lbl_80222C0C:
/* 80222C0C 0021F7EC  4E 80 00 20 */	blr 
.global lbl_80222C10
lbl_80222C10:
/* 80222C10 0021F7F0  7C 08 02 A6 */	mflr r0
/* 80222C14 0021F7F4  38 60 00 00 */	li r3, 0
/* 80222C18 0021F7F8  90 01 00 04 */	stw r0, 4(r1)
/* 80222C1C 0021F7FC  94 21 FF F8 */	stwu r1, -8(r1)
/* 80222C20 0021F800  4B FA 81 E5 */	bl func_801CAE04
/* 80222C24 0021F804  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80222C28 0021F808  38 21 00 08 */	addi r1, r1, 8
/* 80222C2C 0021F80C  7C 08 03 A6 */	mtlr r0
/* 80222C30 0021F810  4E 80 00 20 */	blr 
.global lbl_80222C34
lbl_80222C34:
/* 80222C34 0021F814  38 60 00 00 */	li r3, 0
/* 80222C38 0021F818  4E 80 00 20 */	blr 

.global func_80222C3C
func_80222C3C:
/* 80222C3C 0021F81C  7C 08 02 A6 */	mflr r0
/* 80222C40 0021F820  90 01 00 04 */	stw r0, 4(r1)
/* 80222C44 0021F824  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80222C48 0021F828  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80222C4C 0021F82C  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80222C50 0021F830  93 A1 00 14 */	stw r29, 0x14(r1)
/* 80222C54 0021F834  93 81 00 10 */	stw r28, 0x10(r1)
/* 80222C58 0021F838  3B 83 00 00 */	addi r28, r3, 0
/* 80222C5C 0021F83C  1C 1C 00 14 */	mulli r0, r28, 0x14
/* 80222C60 0021F840  3C 60 80 3F */	lis r3, lbl_803E91B0@ha
/* 80222C64 0021F844  3B E3 91 B0 */	addi r31, r3, lbl_803E91B0@l
/* 80222C68 0021F848  38 7C 00 00 */	addi r3, r28, 0
/* 80222C6C 0021F84C  7F BF 02 14 */	add r29, r31, r0
/* 80222C70 0021F850  4B F9 E8 61 */	bl func_801C14D0
/* 80222C74 0021F854  7C 7E 1B 79 */	or. r30, r3, r3
/* 80222C78 0021F858  41 82 00 70 */	beq lbl_80222CE8
/* 80222C7C 0021F85C  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 80222C80 0021F860  38 00 00 00 */	li r0, 0
/* 80222C84 0021F864  3C 60 80 1C */	lis r3, func_801C5DB0@ha
/* 80222C88 0021F868  90 1F 00 08 */	stw r0, 8(r31)
/* 80222C8C 0021F86C  38 83 5D B0 */	addi r4, r3, func_801C5DB0@l
/* 80222C90 0021F870  38 7E 00 00 */	addi r3, r30, 0
/* 80222C94 0021F874  90 1F 00 0C */	stw r0, 0xc(r31)
/* 80222C98 0021F878  38 A0 00 03 */	li r5, 3
/* 80222C9C 0021F87C  38 C0 00 00 */	li r6, 0
/* 80222CA0 0021F880  48 16 D9 FD */	bl func_8039069C
/* 80222CA4 0021F884  80 1D 00 0C */	lwz r0, 0xc(r29)
/* 80222CA8 0021F888  28 00 00 00 */	cmplwi r0, 0
/* 80222CAC 0021F88C  41 82 00 08 */	beq lbl_80222CB4
/* 80222CB0 0021F890  90 1F 00 1C */	stw r0, 0x1c(r31)
lbl_80222CB4:
/* 80222CB4 0021F894  81 9D 00 00 */	lwz r12, 0(r29)
/* 80222CB8 0021F898  28 0C 00 00 */	cmplwi r12, 0
/* 80222CBC 0021F89C  41 82 00 10 */	beq lbl_80222CCC
/* 80222CC0 0021F8A0  7D 88 03 A6 */	mtlr r12
/* 80222CC4 0021F8A4  38 7E 00 00 */	addi r3, r30, 0
/* 80222CC8 0021F8A8  4E 80 00 21 */	blrl 
lbl_80222CCC:
/* 80222CCC 0021F8AC  80 9D 00 08 */	lwz r4, 8(r29)
/* 80222CD0 0021F8B0  28 04 00 00 */	cmplwi r4, 0
/* 80222CD4 0021F8B4  41 82 00 2C */	beq lbl_80222D00
/* 80222CD8 0021F8B8  38 7E 00 00 */	addi r3, r30, 0
/* 80222CDC 0021F8BC  38 A0 00 04 */	li r5, 4
/* 80222CE0 0021F8C0  48 16 D0 75 */	bl func_8038FD54
/* 80222CE4 0021F8C4  48 00 00 1C */	b lbl_80222D00
lbl_80222CE8:
/* 80222CE8 0021F8C8  38 DC 00 00 */	addi r6, r28, 0
/* 80222CEC 0021F8CC  4C C6 31 82 */	crclr 6
/* 80222CF0 0021F8D0  38 7F 00 90 */	addi r3, r31, 0x90
/* 80222CF4 0021F8D4  38 9F 00 B4 */	addi r4, r31, 0xb4
/* 80222CF8 0021F8D8  38 A0 00 C2 */	li r5, 0xc2
/* 80222CFC 0021F8DC  48 12 29 AD */	bl OSReport
lbl_80222D00:
/* 80222D00 0021F8E0  7F C3 F3 78 */	mr r3, r30
/* 80222D04 0021F8E4  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80222D08 0021F8E8  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80222D0C 0021F8EC  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80222D10 0021F8F0  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 80222D14 0021F8F4  83 81 00 10 */	lwz r28, 0x10(r1)
/* 80222D18 0021F8F8  38 21 00 20 */	addi r1, r1, 0x20
/* 80222D1C 0021F8FC  7C 08 03 A6 */	mtlr r0
/* 80222D20 0021F900  4E 80 00 20 */	blr 
.global lbl_80222D24
lbl_80222D24:
/* 80222D24 0021F904  7C 08 02 A6 */	mflr r0
/* 80222D28 0021F908  38 A0 00 00 */	li r5, 0
/* 80222D2C 0021F90C  90 01 00 04 */	stw r0, 4(r1)
/* 80222D30 0021F910  94 21 FF F8 */	stwu r1, -8(r1)
/* 80222D34 0021F914  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 80222D38 0021F918  80 84 00 14 */	lwz r4, 0x14(r4)
/* 80222D3C 0021F91C  4B FA 53 FD */	bl func_801C8138
/* 80222D40 0021F920  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80222D44 0021F924  38 21 00 08 */	addi r1, r1, 8
/* 80222D48 0021F928  7C 08 03 A6 */	mtlr r0
/* 80222D4C 0021F92C  4E 80 00 20 */	blr 
.global lbl_80222D50
lbl_80222D50:
/* 80222D50 0021F930  38 60 00 00 */	li r3, 0
/* 80222D54 0021F934  4E 80 00 20 */	blr 
.global lbl_80222D58
lbl_80222D58:
/* 80222D58 0021F938  4E 80 00 20 */	blr 
.global lbl_80222D5C
lbl_80222D5C:
/* 80222D5C 0021F93C  4E 80 00 20 */	blr 
.global lbl_80222D60
lbl_80222D60:
/* 80222D60 0021F940  7C 08 02 A6 */	mflr r0
/* 80222D64 0021F944  90 01 00 04 */	stw r0, 4(r1)
/* 80222D68 0021F948  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80222D6C 0021F94C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80222D70 0021F950  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80222D74 0021F954  7C 7E 1B 78 */	mr r30, r3
/* 80222D78 0021F958  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80222D7C 0021F95C  80 63 00 28 */	lwz r3, 0x28(r3)
/* 80222D80 0021F960  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80222D84 0021F964  4B FA 01 4D */	bl func_801C2ED0
/* 80222D88 0021F968  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80222D8C 0021F96C  38 7E 00 00 */	addi r3, r30, 0
/* 80222D90 0021F970  38 A0 00 00 */	li r5, 0
/* 80222D94 0021F974  4B FA 53 A5 */	bl func_801C8138
/* 80222D98 0021F978  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80222D9C 0021F97C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80222DA0 0021F980  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80222DA4 0021F984  38 21 00 20 */	addi r1, r1, 0x20
/* 80222DA8 0021F988  7C 08 03 A6 */	mtlr r0
/* 80222DAC 0021F98C  4E 80 00 20 */	blr 
.global lbl_80222DB0
lbl_80222DB0:
/* 80222DB0 0021F990  38 60 00 00 */	li r3, 0
/* 80222DB4 0021F994  4E 80 00 20 */	blr 
.global lbl_80222DB8
lbl_80222DB8:
/* 80222DB8 0021F998  7C 08 02 A6 */	mflr r0
/* 80222DBC 0021F99C  90 01 00 04 */	stw r0, 4(r1)
/* 80222DC0 0021F9A0  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80222DC4 0021F9A4  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80222DC8 0021F9A8  7C 7F 1B 78 */	mr r31, r3
/* 80222DCC 0021F9AC  4B DE E8 29 */	bl func_800115F4
/* 80222DD0 0021F9B0  7F E3 FB 78 */	mr r3, r31
/* 80222DD4 0021F9B4  4B FA 02 0D */	bl func_801C2FE0
/* 80222DD8 0021F9B8  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80222DDC 0021F9BC  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80222DE0 0021F9C0  38 21 00 18 */	addi r1, r1, 0x18
/* 80222DE4 0021F9C4  7C 08 03 A6 */	mtlr r0
/* 80222DE8 0021F9C8  4E 80 00 20 */	blr 
.global lbl_80222DEC
lbl_80222DEC:
/* 80222DEC 0021F9CC  4E 80 00 20 */	blr 
.global lbl_80222DF0
lbl_80222DF0:
/* 80222DF0 0021F9D0  7C 08 02 A6 */	mflr r0
/* 80222DF4 0021F9D4  90 01 00 04 */	stw r0, 4(r1)
/* 80222DF8 0021F9D8  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80222DFC 0021F9DC  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80222E00 0021F9E0  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80222E04 0021F9E4  7C 7E 1B 78 */	mr r30, r3
/* 80222E08 0021F9E8  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80222E0C 0021F9EC  80 63 00 28 */	lwz r3, 0x28(r3)
/* 80222E10 0021F9F0  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80222E14 0021F9F4  4B FA 00 BD */	bl func_801C2ED0
/* 80222E18 0021F9F8  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80222E1C 0021F9FC  38 7E 00 00 */	addi r3, r30, 0
/* 80222E20 0021FA00  38 A0 00 00 */	li r5, 0
/* 80222E24 0021FA04  4B FA 53 15 */	bl func_801C8138
/* 80222E28 0021FA08  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80222E2C 0021FA0C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80222E30 0021FA10  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80222E34 0021FA14  38 21 00 20 */	addi r1, r1, 0x20
/* 80222E38 0021FA18  7C 08 03 A6 */	mtlr r0
/* 80222E3C 0021FA1C  4E 80 00 20 */	blr 
.global lbl_80222E40
lbl_80222E40:
/* 80222E40 0021FA20  38 60 00 00 */	li r3, 0
/* 80222E44 0021FA24  4E 80 00 20 */	blr 
.global lbl_80222E48
lbl_80222E48:
/* 80222E48 0021FA28  7C 08 02 A6 */	mflr r0
/* 80222E4C 0021FA2C  90 01 00 04 */	stw r0, 4(r1)
/* 80222E50 0021FA30  94 21 FF F8 */	stwu r1, -8(r1)
/* 80222E54 0021FA34  4B FA 01 8D */	bl func_801C2FE0
/* 80222E58 0021FA38  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80222E5C 0021FA3C  38 21 00 08 */	addi r1, r1, 8
/* 80222E60 0021FA40  7C 08 03 A6 */	mtlr r0
/* 80222E64 0021FA44  4E 80 00 20 */	blr 
.global lbl_80222E68
lbl_80222E68:
/* 80222E68 0021FA48  4E 80 00 20 */	blr 
.global lbl_80222E6C
lbl_80222E6C:
/* 80222E6C 0021FA4C  38 60 00 00 */	li r3, 0
/* 80222E70 0021FA50  4E 80 00 20 */	blr 
.global lbl_80222E74
lbl_80222E74:
/* 80222E74 0021FA54  38 60 00 01 */	li r3, 1
/* 80222E78 0021FA58  4E 80 00 20 */	blr 
