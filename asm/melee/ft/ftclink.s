.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

.global func_80148B78
func_80148B78:
/* 80148B78 00145758  7C 08 02 A6 */	mflr r0
/* 80148B7C 0014575C  90 01 00 04 */	stw r0, 4(r1)
/* 80148B80 00145760  94 21 FF A8 */	stwu r1, -0x58(r1)
/* 80148B84 00145764  93 E1 00 54 */	stw r31, 0x54(r1)
/* 80148B88 00145768  93 C1 00 50 */	stw r30, 0x50(r1)
/* 80148B8C 0014576C  93 A1 00 4C */	stw r29, 0x4c(r1)
/* 80148B90 00145770  7C 7D 1B 78 */	mr r29, r3
/* 80148B94 00145774  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 80148B98 00145778  80 1E 00 04 */	lwz r0, 4(r30)
/* 80148B9C 0014577C  2C 00 00 10 */	cmpwi r0, 0x10
/* 80148BA0 00145780  40 82 00 A8 */	bne lbl_80148C48
/* 80148BA4 00145784  80 1E 22 0C */	lwz r0, 0x220c(r30)
/* 80148BA8 00145788  83 FE 02 D4 */	lwz r31, 0x2d4(r30)
/* 80148BAC 0014578C  28 00 00 01 */	cmplwi r0, 1
/* 80148BB0 00145790  40 82 00 98 */	bne lbl_80148C48
/* 80148BB4 00145794  38 00 00 00 */	li r0, 0
/* 80148BB8 00145798  90 1E 22 0C */	stw r0, 0x220c(r30)
/* 80148BBC 0014579C  38 A1 00 20 */	addi r5, r1, 0x20
/* 80148BC0 001457A0  38 80 00 00 */	li r4, 0
/* 80148BC4 001457A4  80 7E 05 E8 */	lwz r3, 0x5e8(r30)
/* 80148BC8 001457A8  80 63 02 30 */	lwz r3, 0x230(r3)
/* 80148BCC 001457AC  4B EC 26 01 */	bl func_8000B1CC
/* 80148BD0 001457B0  80 7E 05 E8 */	lwz r3, 0x5e8(r30)
/* 80148BD4 001457B4  38 A1 00 2C */	addi r5, r1, 0x2c
/* 80148BD8 001457B8  38 80 00 00 */	li r4, 0
/* 80148BDC 001457BC  80 63 02 00 */	lwz r3, 0x200(r3)
/* 80148BE0 001457C0  4B EC 25 ED */	bl func_8000B1CC
/* 80148BE4 001457C4  C0 02 A3 8C */	lfs f0, lbl_804D9D6C@sda21(r2)
/* 80148BE8 001457C8  D0 01 00 34 */	stfs f0, 0x34(r1)
/* 80148BEC 001457CC  D0 01 00 28 */	stfs f0, 0x28(r1)
/* 80148BF0 001457D0  C0 21 00 30 */	lfs f1, 0x30(r1)
/* 80148BF4 001457D4  C0 61 00 24 */	lfs f3, 0x24(r1)
/* 80148BF8 001457D8  C0 41 00 20 */	lfs f2, 0x20(r1)
/* 80148BFC 001457DC  C0 01 00 2C */	lfs f0, 0x2c(r1)
/* 80148C00 001457E0  EC 23 08 28 */	fsubs f1, f3, f1
/* 80148C04 001457E4  EC 42 00 28 */	fsubs f2, f2, f0
/* 80148C08 001457E8  4B ED A0 29 */	bl func_80022C30
/* 80148C0C 001457EC  C0 1F 00 00 */	lfs f0, 0(r31)
/* 80148C10 001457F0  7F A3 EB 78 */	mr r3, r29
/* 80148C14 001457F4  C0 5E 00 2C */	lfs f2, 0x2c(r30)
/* 80148C18 001457F8  38 81 00 20 */	addi r4, r1, 0x20
/* 80148C1C 001457FC  FC 00 00 1E */	fctiwz f0, f0
/* 80148C20 00145800  38 A0 00 70 */	li r5, 0x70
/* 80148C24 00145804  D8 01 00 40 */	stfd f0, 0x40(r1)
/* 80148C28 00145808  80 C1 00 44 */	lwz r6, 0x44(r1)
/* 80148C2C 0014580C  48 17 C5 71 */	bl func_802C519C
/* 80148C30 00145810  3C 80 00 03 */	lis r4, 0x00030DB3@ha
/* 80148C34 00145814  38 7E 00 00 */	addi r3, r30, 0
/* 80148C38 00145818  38 84 0D B3 */	addi r4, r4, 0x00030DB3@l
/* 80148C3C 0014581C  38 A0 00 7F */	li r5, 0x7f
/* 80148C40 00145820  38 C0 00 40 */	li r6, 0x40
/* 80148C44 00145824  4B F3 F5 05 */	bl func_80088148
lbl_80148C48:
/* 80148C48 00145828  80 01 00 5C */	lwz r0, 0x5c(r1)
/* 80148C4C 0014582C  83 E1 00 54 */	lwz r31, 0x54(r1)
/* 80148C50 00145830  83 C1 00 50 */	lwz r30, 0x50(r1)
/* 80148C54 00145834  83 A1 00 4C */	lwz r29, 0x4c(r1)
/* 80148C58 00145838  38 21 00 58 */	addi r1, r1, 0x58
/* 80148C5C 0014583C  7C 08 03 A6 */	mtlr r0
/* 80148C60 00145840  4E 80 00 20 */	blr 

.global func_80148C64
func_80148C64:
/* 80148C64 00145844  7C 08 02 A6 */	mflr r0
/* 80148C68 00145848  38 80 00 00 */	li r4, 0
/* 80148C6C 0014584C  90 01 00 04 */	stw r0, 4(r1)
/* 80148C70 00145850  38 A0 00 00 */	li r5, 0
/* 80148C74 00145854  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80148C78 00145858  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80148C7C 0014585C  93 C1 00 10 */	stw r30, 0x10(r1)
/* 80148C80 00145860  7C 7E 1B 78 */	mr r30, r3
/* 80148C84 00145864  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80148C88 00145868  4B F2 BD C5 */	bl func_80074A4C
/* 80148C8C 0014586C  38 7E 00 00 */	addi r3, r30, 0
/* 80148C90 00145870  38 80 00 01 */	li r4, 1
/* 80148C94 00145874  38 A0 00 00 */	li r5, 0
/* 80148C98 00145878  4B F2 BD B5 */	bl func_80074A4C
/* 80148C9C 0014587C  38 7E 00 00 */	addi r3, r30, 0
/* 80148CA0 00145880  38 80 00 02 */	li r4, 2
/* 80148CA4 00145884  38 A0 00 00 */	li r5, 0
/* 80148CA8 00145888  4B F2 BD A5 */	bl func_80074A4C
/* 80148CAC 0014588C  38 00 00 00 */	li r0, 0
/* 80148CB0 00145890  90 1F 22 2C */	stw r0, 0x222c(r31)
/* 80148CB4 00145894  90 1F 22 34 */	stw r0, 0x2234(r31)
/* 80148CB8 00145898  90 1F 22 38 */	stw r0, 0x2238(r31)
/* 80148CBC 0014589C  90 1F 22 3C */	stw r0, 0x223c(r31)
/* 80148CC0 001458A0  90 1F 22 40 */	stw r0, 0x2240(r31)
/* 80148CC4 001458A4  90 1F 22 38 */	stw r0, 0x2238(r31)
/* 80148CC8 001458A8  90 1F 22 44 */	stw r0, 0x2244(r31)
/* 80148CCC 001458AC  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80148CD0 001458B0  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80148CD4 001458B4  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 80148CD8 001458B8  38 21 00 18 */	addi r1, r1, 0x18
/* 80148CDC 001458BC  7C 08 03 A6 */	mtlr r0
/* 80148CE0 001458C0  4E 80 00 20 */	blr 

.global func_80148CE4
func_80148CE4:
/* 80148CE4 001458C4  7C 08 02 A6 */	mflr r0
/* 80148CE8 001458C8  38 A0 00 01 */	li r5, 1
/* 80148CEC 001458CC  90 01 00 04 */	stw r0, 4(r1)
/* 80148CF0 001458D0  38 80 00 48 */	li r4, 0x48
/* 80148CF4 001458D4  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 80148CF8 001458D8  93 E1 00 24 */	stw r31, 0x24(r1)
/* 80148CFC 001458DC  93 C1 00 20 */	stw r30, 0x20(r1)
/* 80148D00 001458E0  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 80148D04 001458E4  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 80148D08 001458E8  80 DE 01 0C */	lwz r6, 0x10c(r30)
/* 80148D0C 001458EC  7F C3 F3 78 */	mr r3, r30
/* 80148D10 001458F0  88 1E 22 24 */	lbz r0, 0x2224(r30)
/* 80148D14 001458F4  50 A0 07 FE */	rlwimi r0, r5, 0, 0x1f, 0x1f
/* 80148D18 001458F8  83 E6 00 04 */	lwz r31, 4(r6)
/* 80148D1C 001458FC  83 A6 00 48 */	lwz r29, 0x48(r6)
/* 80148D20 00145900  98 1E 22 24 */	stb r0, 0x2224(r30)
/* 80148D24 00145904  4B F3 D1 2D */	bl func_80085E50
/* 80148D28 00145908  4B ED 5B D1 */	bl func_8001E8F8
/* 80148D2C 0014590C  D0 3F 00 54 */	stfs f1, 0x54(r31)
/* 80148D30 00145910  7F C3 F3 78 */	mr r3, r30
/* 80148D34 00145914  4B FA 20 D1 */	bl func_800EAE04
/* 80148D38 00145918  83 FE 02 D4 */	lwz r31, 0x2d4(r30)
/* 80148D3C 0014591C  80 7D 00 00 */	lwz r3, 0(r29)
/* 80148D40 00145920  80 9F 00 48 */	lwz r4, 0x48(r31)
/* 80148D44 00145924  48 12 26 B5 */	bl func_8026B3F8
/* 80148D48 00145928  80 7D 00 04 */	lwz r3, 4(r29)
/* 80148D4C 0014592C  80 9F 00 2C */	lwz r4, 0x2c(r31)
/* 80148D50 00145930  48 12 26 A9 */	bl func_8026B3F8
/* 80148D54 00145934  80 7D 00 08 */	lwz r3, 8(r29)
/* 80148D58 00145938  80 9F 00 BC */	lwz r4, 0xbc(r31)
/* 80148D5C 0014593C  48 12 26 9D */	bl func_8026B3F8
/* 80148D60 00145940  80 7D 00 0C */	lwz r3, 0xc(r29)
/* 80148D64 00145944  80 9F 00 0C */	lwz r4, 0xc(r31)
/* 80148D68 00145948  48 12 26 91 */	bl func_8026B3F8
/* 80148D6C 0014594C  80 7D 00 10 */	lwz r3, 0x10(r29)
/* 80148D70 00145950  80 9F 00 10 */	lwz r4, 0x10(r31)
/* 80148D74 00145954  48 12 26 85 */	bl func_8026B3F8
/* 80148D78 00145958  80 7D 00 14 */	lwz r3, 0x14(r29)
/* 80148D7C 0014595C  38 80 00 7B */	li r4, 0x7b
/* 80148D80 00145960  48 12 26 79 */	bl func_8026B3F8
/* 80148D84 00145964  80 1E 00 04 */	lwz r0, 4(r30)
/* 80148D88 00145968  7F C3 F3 78 */	mr r3, r30
/* 80148D8C 0014596C  80 8D AE A0 */	lwz r4, lbl_804D6540@sda21(r13)
/* 80148D90 00145970  54 00 10 3A */	slwi r0, r0, 2
/* 80148D94 00145974  80 BD 00 18 */	lwz r5, 0x18(r29)
/* 80148D98 00145978  7C 84 00 2E */	lwzx r4, r4, r0
/* 80148D9C 0014597C  80 84 00 00 */	lwz r4, 0(r4)
/* 80148DA0 00145980  4B F2 C6 35 */	bl func_800753D4
/* 80148DA4 00145984  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 80148DA8 00145988  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 80148DAC 0014598C  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 80148DB0 00145990  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 80148DB4 00145994  38 21 00 28 */	addi r1, r1, 0x28
/* 80148DB8 00145998  7C 08 03 A6 */	mtlr r0
/* 80148DBC 0014599C  4E 80 00 20 */	blr 

.global func_80148DC0
func_80148DC0:
/* 80148DC0 001459A0  7C 08 02 A6 */	mflr r0
/* 80148DC4 001459A4  90 01 00 04 */	stw r0, 4(r1)
/* 80148DC8 001459A8  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80148DCC 001459AC  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80148DD0 001459B0  7C 9F 23 78 */	mr r31, r4
/* 80148DD4 001459B4  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80148DD8 001459B8  7C 7E 1B 78 */	mr r30, r3
/* 80148DDC 001459BC  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 80148DE0 001459C0  80 63 19 74 */	lwz r3, 0x1974(r3)
/* 80148DE4 001459C4  48 12 24 D1 */	bl func_8026B2B4
/* 80148DE8 001459C8  2C 03 00 01 */	cmpwi r3, 1
/* 80148DEC 001459CC  40 82 00 14 */	bne lbl_80148E00
/* 80148DF0 001459D0  38 7E 00 00 */	addi r3, r30, 0
/* 80148DF4 001459D4  38 80 00 01 */	li r4, 1
/* 80148DF8 001459D8  38 A0 00 01 */	li r5, 1
/* 80148DFC 001459DC  4B F2 BC 51 */	bl func_80074A4C
lbl_80148E00:
/* 80148E00 001459E0  38 7E 00 00 */	addi r3, r30, 0
/* 80148E04 001459E4  38 80 00 02 */	li r4, 2
/* 80148E08 001459E8  38 A0 00 01 */	li r5, 1
/* 80148E0C 001459EC  4B F2 BC 41 */	bl func_80074A4C
/* 80148E10 001459F0  38 7E 00 00 */	addi r3, r30, 0
/* 80148E14 001459F4  38 9F 00 00 */	addi r4, r31, 0
/* 80148E18 001459F8  48 00 01 21 */	bl func_80148F38
/* 80148E1C 001459FC  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80148E20 00145A00  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80148E24 00145A04  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80148E28 00145A08  38 21 00 20 */	addi r1, r1, 0x20
/* 80148E2C 00145A0C  7C 08 03 A6 */	mtlr r0
/* 80148E30 00145A10  4E 80 00 20 */	blr 

.global func_80148E34
func_80148E34:
/* 80148E34 00145A14  7C 08 02 A6 */	mflr r0
/* 80148E38 00145A18  90 01 00 04 */	stw r0, 4(r1)
/* 80148E3C 00145A1C  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80148E40 00145A20  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80148E44 00145A24  7C 7F 1B 78 */	mr r31, r3
/* 80148E48 00145A28  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 80148E4C 00145A2C  80 63 19 74 */	lwz r3, 0x1974(r3)
/* 80148E50 00145A30  48 12 24 65 */	bl func_8026B2B4
/* 80148E54 00145A34  2C 03 00 00 */	cmpwi r3, 0
/* 80148E58 00145A38  40 82 00 10 */	bne lbl_80148E68
/* 80148E5C 00145A3C  38 7F 00 00 */	addi r3, r31, 0
/* 80148E60 00145A40  38 80 00 01 */	li r4, 1
/* 80148E64 00145A44  4B F2 7E 61 */	bl func_80070CC4
lbl_80148E68:
/* 80148E68 00145A48  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80148E6C 00145A4C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80148E70 00145A50  38 21 00 18 */	addi r1, r1, 0x18
/* 80148E74 00145A54  7C 08 03 A6 */	mtlr r0
/* 80148E78 00145A58  4E 80 00 20 */	blr 

.global func_80148E7C
func_80148E7C:
/* 80148E7C 00145A5C  7C 08 02 A6 */	mflr r0
/* 80148E80 00145A60  90 01 00 04 */	stw r0, 4(r1)
/* 80148E84 00145A64  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80148E88 00145A68  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80148E8C 00145A6C  7C 7F 1B 78 */	mr r31, r3
/* 80148E90 00145A70  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 80148E94 00145A74  80 63 19 74 */	lwz r3, 0x1974(r3)
/* 80148E98 00145A78  48 12 24 1D */	bl func_8026B2B4
/* 80148E9C 00145A7C  2C 03 00 00 */	cmpwi r3, 0
/* 80148EA0 00145A80  40 82 00 10 */	bne lbl_80148EB0
/* 80148EA4 00145A84  38 7F 00 00 */	addi r3, r31, 0
/* 80148EA8 00145A88  38 80 00 01 */	li r4, 1
/* 80148EAC 00145A8C  4B F2 7D 9D */	bl func_80070C48
lbl_80148EB0:
/* 80148EB0 00145A90  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80148EB4 00145A94  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80148EB8 00145A98  38 21 00 18 */	addi r1, r1, 0x18
/* 80148EBC 00145A9C  7C 08 03 A6 */	mtlr r0
/* 80148EC0 00145AA0  4E 80 00 20 */	blr 

.global func_80148EC4
func_80148EC4:
/* 80148EC4 00145AA4  7C 08 02 A6 */	mflr r0
/* 80148EC8 00145AA8  90 01 00 04 */	stw r0, 4(r1)
/* 80148ECC 00145AAC  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80148ED0 00145AB0  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80148ED4 00145AB4  7C 9F 23 78 */	mr r31, r4
/* 80148ED8 00145AB8  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80148EDC 00145ABC  7C 7E 1B 78 */	mr r30, r3
/* 80148EE0 00145AC0  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 80148EE4 00145AC4  80 63 19 74 */	lwz r3, 0x1974(r3)
/* 80148EE8 00145AC8  48 12 23 CD */	bl func_8026B2B4
/* 80148EEC 00145ACC  2C 03 00 01 */	cmpwi r3, 1
/* 80148EF0 00145AD0  40 82 00 14 */	bne lbl_80148F04
/* 80148EF4 00145AD4  38 7E 00 00 */	addi r3, r30, 0
/* 80148EF8 00145AD8  38 80 00 01 */	li r4, 1
/* 80148EFC 00145ADC  38 A0 00 00 */	li r5, 0
/* 80148F00 00145AE0  4B F2 BB 4D */	bl func_80074A4C
lbl_80148F04:
/* 80148F04 00145AE4  38 7E 00 00 */	addi r3, r30, 0
/* 80148F08 00145AE8  38 80 00 02 */	li r4, 2
/* 80148F0C 00145AEC  38 A0 00 00 */	li r5, 0
/* 80148F10 00145AF0  4B F2 BB 3D */	bl func_80074A4C
/* 80148F14 00145AF4  38 7E 00 00 */	addi r3, r30, 0
/* 80148F18 00145AF8  38 9F 00 00 */	addi r4, r31, 0
/* 80148F1C 00145AFC  48 00 00 FD */	bl func_80149018
/* 80148F20 00145B00  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80148F24 00145B04  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80148F28 00145B08  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80148F2C 00145B0C  38 21 00 20 */	addi r1, r1, 0x20
/* 80148F30 00145B10  7C 08 03 A6 */	mtlr r0
/* 80148F34 00145B14  4E 80 00 20 */	blr 

.global func_80148F38
func_80148F38:
/* 80148F38 00145B18  7C 08 02 A6 */	mflr r0
/* 80148F3C 00145B1C  90 01 00 04 */	stw r0, 4(r1)
/* 80148F40 00145B20  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 80148F44 00145B24  93 E1 00 24 */	stw r31, 0x24(r1)
/* 80148F48 00145B28  93 C1 00 20 */	stw r30, 0x20(r1)
/* 80148F4C 00145B2C  7C 9E 23 78 */	mr r30, r4
/* 80148F50 00145B30  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 80148F54 00145B34  7C 7D 1B 78 */	mr r29, r3
/* 80148F58 00145B38  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80148F5C 00145B3C  80 7F 19 74 */	lwz r3, 0x1974(r31)
/* 80148F60 00145B40  48 12 23 55 */	bl func_8026B2B4
/* 80148F64 00145B44  2C 03 00 00 */	cmpwi r3, 0
/* 80148F68 00145B48  40 82 00 94 */	bne lbl_80148FFC
/* 80148F6C 00145B4C  80 7F 19 74 */	lwz r3, 0x1974(r31)
/* 80148F70 00145B50  48 12 23 B1 */	bl func_8026B320
/* 80148F74 00145B54  2C 03 00 03 */	cmpwi r3, 3
/* 80148F78 00145B58  41 82 00 4C */	beq lbl_80148FC4
/* 80148F7C 00145B5C  40 80 00 14 */	bge lbl_80148F90
/* 80148F80 00145B60  2C 03 00 01 */	cmpwi r3, 1
/* 80148F84 00145B64  41 82 00 18 */	beq lbl_80148F9C
/* 80148F88 00145B68  40 80 00 28 */	bge lbl_80148FB0
/* 80148F8C 00145B6C  48 00 00 5C */	b lbl_80148FE8
lbl_80148F90:
/* 80148F90 00145B70  2C 03 00 05 */	cmpwi r3, 5
/* 80148F94 00145B74  40 80 00 54 */	bge lbl_80148FE8
/* 80148F98 00145B78  48 00 00 40 */	b lbl_80148FD8
lbl_80148F9C:
/* 80148F9C 00145B7C  38 7D 00 00 */	addi r3, r29, 0
/* 80148FA0 00145B80  38 80 00 01 */	li r4, 1
/* 80148FA4 00145B84  38 A0 00 01 */	li r5, 1
/* 80148FA8 00145B88  4B F2 80 0D */	bl func_80070FB4
/* 80148FAC 00145B8C  48 00 00 3C */	b lbl_80148FE8
lbl_80148FB0:
/* 80148FB0 00145B90  38 7D 00 00 */	addi r3, r29, 0
/* 80148FB4 00145B94  38 80 00 01 */	li r4, 1
/* 80148FB8 00145B98  38 A0 00 00 */	li r5, 0
/* 80148FBC 00145B9C  4B F2 7F F9 */	bl func_80070FB4
/* 80148FC0 00145BA0  48 00 00 28 */	b lbl_80148FE8
lbl_80148FC4:
/* 80148FC4 00145BA4  38 7D 00 00 */	addi r3, r29, 0
/* 80148FC8 00145BA8  38 80 00 01 */	li r4, 1
/* 80148FCC 00145BAC  38 A0 00 02 */	li r5, 2
/* 80148FD0 00145BB0  4B F2 7F E5 */	bl func_80070FB4
/* 80148FD4 00145BB4  48 00 00 14 */	b lbl_80148FE8
lbl_80148FD8:
/* 80148FD8 00145BB8  38 7D 00 00 */	addi r3, r29, 0
/* 80148FDC 00145BBC  38 80 00 01 */	li r4, 1
/* 80148FE0 00145BC0  38 A0 00 03 */	li r5, 3
/* 80148FE4 00145BC4  4B F2 7F D1 */	bl func_80070FB4
lbl_80148FE8:
/* 80148FE8 00145BC8  2C 1E 00 00 */	cmpwi r30, 0
/* 80148FEC 00145BCC  41 82 00 10 */	beq lbl_80148FFC
/* 80148FF0 00145BD0  38 7D 00 00 */	addi r3, r29, 0
/* 80148FF4 00145BD4  38 80 00 01 */	li r4, 1
/* 80148FF8 00145BD8  4B F2 7C 51 */	bl func_80070C48
lbl_80148FFC:
/* 80148FFC 00145BDC  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 80149000 00145BE0  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 80149004 00145BE4  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 80149008 00145BE8  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 8014900C 00145BEC  38 21 00 28 */	addi r1, r1, 0x28
/* 80149010 00145BF0  7C 08 03 A6 */	mtlr r0
/* 80149014 00145BF4  4E 80 00 20 */	blr 

.global func_80149018
func_80149018:
/* 80149018 00145BF8  7C 08 02 A6 */	mflr r0
/* 8014901C 00145BFC  38 A0 FF FF */	li r5, -1
/* 80149020 00145C00  90 01 00 04 */	stw r0, 4(r1)
/* 80149024 00145C04  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80149028 00145C08  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8014902C 00145C0C  3B E4 00 00 */	addi r31, r4, 0
/* 80149030 00145C10  38 80 00 01 */	li r4, 1
/* 80149034 00145C14  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80149038 00145C18  3B C3 00 00 */	addi r30, r3, 0
/* 8014903C 00145C1C  4B F2 7F 79 */	bl func_80070FB4
/* 80149040 00145C20  2C 1F 00 00 */	cmpwi r31, 0
/* 80149044 00145C24  41 82 00 10 */	beq lbl_80149054
/* 80149048 00145C28  38 7E 00 00 */	addi r3, r30, 0
/* 8014904C 00145C2C  38 80 00 01 */	li r4, 1
/* 80149050 00145C30  4B F2 7C 75 */	bl func_80070CC4
lbl_80149054:
/* 80149054 00145C34  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80149058 00145C38  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8014905C 00145C3C  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80149060 00145C40  38 21 00 20 */	addi r1, r1, 0x20
/* 80149064 00145C44  7C 08 03 A6 */	mtlr r0
/* 80149068 00145C48  4E 80 00 20 */	blr 

.global func_8014906C
func_8014906C:
/* 8014906C 00145C4C  7C 08 02 A6 */	mflr r0
/* 80149070 00145C50  90 01 00 04 */	stw r0, 4(r1)
/* 80149074 00145C54  94 21 FF F8 */	stwu r1, -8(r1)
/* 80149078 00145C58  4B FA 21 D9 */	bl func_800EB250
/* 8014907C 00145C5C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80149080 00145C60  38 21 00 08 */	addi r1, r1, 8
/* 80149084 00145C64  7C 08 03 A6 */	mtlr r0
/* 80149088 00145C68  4E 80 00 20 */	blr 

.global func_8014908C
func_8014908C:
/* 8014908C 00145C6C  7C 08 02 A6 */	mflr r0
/* 80149090 00145C70  38 80 00 01 */	li r4, 1
/* 80149094 00145C74  90 01 00 04 */	stw r0, 4(r1)
/* 80149098 00145C78  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8014909C 00145C7C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 801490A0 00145C80  7C 7F 1B 78 */	mr r31, r3
/* 801490A4 00145C84  C0 22 A3 C0 */	lfs f1, lbl_804D9DA0@sda21(r2)
/* 801490A8 00145C88  4B F2 74 49 */	bl func_800704F0
/* 801490AC 00145C8C  C0 22 A3 C0 */	lfs f1, lbl_804D9DA0@sda21(r2)
/* 801490B0 00145C90  38 7F 00 00 */	addi r3, r31, 0
/* 801490B4 00145C94  38 80 00 00 */	li r4, 0
/* 801490B8 00145C98  4B F2 74 39 */	bl func_800704F0
/* 801490BC 00145C9C  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 801490C0 00145CA0  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 801490C4 00145CA4  38 21 00 18 */	addi r1, r1, 0x18
/* 801490C8 00145CA8  7C 08 03 A6 */	mtlr r0
/* 801490CC 00145CAC  4E 80 00 20 */	blr 

.global func_801490D0
func_801490D0:
/* 801490D0 00145CB0  7C 08 02 A6 */	mflr r0
/* 801490D4 00145CB4  38 80 00 01 */	li r4, 1
/* 801490D8 00145CB8  90 01 00 04 */	stw r0, 4(r1)
/* 801490DC 00145CBC  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 801490E0 00145CC0  93 E1 00 14 */	stw r31, 0x14(r1)
/* 801490E4 00145CC4  7C 7F 1B 78 */	mr r31, r3
/* 801490E8 00145CC8  C0 22 A3 C4 */	lfs f1, lbl_804D9DA4@sda21(r2)
/* 801490EC 00145CCC  4B F2 74 05 */	bl func_800704F0
/* 801490F0 00145CD0  C0 22 A3 C4 */	lfs f1, lbl_804D9DA4@sda21(r2)
/* 801490F4 00145CD4  38 7F 00 00 */	addi r3, r31, 0
/* 801490F8 00145CD8  38 80 00 00 */	li r4, 0
/* 801490FC 00145CDC  4B F2 73 F5 */	bl func_800704F0
/* 80149100 00145CE0  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80149104 00145CE4  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80149108 00145CE8  38 21 00 18 */	addi r1, r1, 0x18
/* 8014910C 00145CEC  7C 08 03 A6 */	mtlr r0
/* 80149110 00145CF0  4E 80 00 20 */	blr 
lbl_80149114:
/* 80149114 00145CF4  7C 08 02 A6 */	mflr r0
/* 80149118 00145CF8  90 01 00 04 */	stw r0, 4(r1)
/* 8014911C 00145CFC  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80149120 00145D00  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80149124 00145D04  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80149128 00145D08  80 9F 01 0C */	lwz r4, 0x10c(r31)
/* 8014912C 00145D0C  80 7F 19 A4 */	lwz r3, 0x19a4(r31)
/* 80149130 00145D10  80 84 00 04 */	lwz r4, 4(r4)
/* 80149134 00145D14  C0 24 00 D8 */	lfs f1, 0xd8(r4)
/* 80149138 00145D18  4B F4 9D A1 */	bl func_80092ED8
/* 8014913C 00145D1C  80 6D AE B4 */	lwz r3, lbl_804D6554@sda21(r13)
/* 80149140 00145D20  C0 03 02 94 */	lfs f0, 0x294(r3)
/* 80149144 00145D24  EC 01 00 32 */	fmuls f0, f1, f0
/* 80149148 00145D28  D0 1F 00 EC */	stfs f0, 0xec(r31)
/* 8014914C 00145D2C  C0 3F 19 AC */	lfs f1, 0x19ac(r31)
/* 80149150 00145D30  C0 02 A3 C4 */	lfs f0, lbl_804D9DA4@sda21(r2)
/* 80149154 00145D34  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80149158 00145D38  40 80 00 0C */	bge lbl_80149164
/* 8014915C 00145D3C  C0 1F 00 EC */	lfs f0, 0xec(r31)
/* 80149160 00145D40  48 00 00 0C */	b lbl_8014916C
lbl_80149164:
/* 80149164 00145D44  C0 1F 00 EC */	lfs f0, 0xec(r31)
/* 80149168 00145D48  FC 00 00 50 */	fneg f0, f0
lbl_8014916C:
/* 8014916C 00145D4C  3C 80 00 01 */	lis r4, 0x000111DA@ha
/* 80149170 00145D50  D0 1F 00 EC */	stfs f0, 0xec(r31)
/* 80149174 00145D54  38 7F 00 00 */	addi r3, r31, 0
/* 80149178 00145D58  38 84 11 DA */	addi r4, r4, 0x000111DA@l
/* 8014917C 00145D5C  38 A0 00 7F */	li r5, 0x7f
/* 80149180 00145D60  38 C0 00 40 */	li r6, 0x40
/* 80149184 00145D64  4B F3 EF C5 */	bl func_80088148
/* 80149188 00145D68  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8014918C 00145D6C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80149190 00145D70  38 21 00 18 */	addi r1, r1, 0x18
/* 80149194 00145D74  7C 08 03 A6 */	mtlr r0
/* 80149198 00145D78  4E 80 00 20 */	blr 

.global func_8014919C
func_8014919C:
/* 8014919C 00145D7C  7C 08 02 A6 */	mflr r0
/* 801491A0 00145D80  90 01 00 04 */	stw r0, 4(r1)
/* 801491A4 00145D84  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 801491A8 00145D88  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 801491AC 00145D8C  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 801491B0 00145D90  88 1F 05 F8 */	lbz r0, 0x5f8(r31)
/* 801491B4 00145D94  7C 00 07 75 */	extsb. r0, r0
/* 801491B8 00145D98  40 82 00 40 */	bne lbl_801491F8
/* 801491BC 00145D9C  80 DF 02 D4 */	lwz r6, 0x2d4(r31)
/* 801491C0 00145DA0  3C 80 80 15 */	lis r4, lbl_80149114@ha
/* 801491C4 00145DA4  38 A4 91 14 */	addi r5, r4, lbl_80149114@l
/* 801491C8 00145DA8  38 86 00 C4 */	addi r4, r6, 0xc4
/* 801491CC 00145DAC  4B F3 1F ED */	bl func_8007B1B8
/* 801491D0 00145DB0  88 1F 22 1B */	lbz r0, 0x221b(r31)
/* 801491D4 00145DB4  38 60 00 01 */	li r3, 1
/* 801491D8 00145DB8  50 60 26 F6 */	rlwimi r0, r3, 4, 0x1b, 0x1b
/* 801491DC 00145DBC  98 1F 22 1B */	stb r0, 0x221b(r31)
/* 801491E0 00145DC0  88 1F 22 1B */	lbz r0, 0x221b(r31)
/* 801491E4 00145DC4  50 60 1F 38 */	rlwimi r0, r3, 3, 0x1c, 0x1c
/* 801491E8 00145DC8  98 1F 22 1B */	stb r0, 0x221b(r31)
/* 801491EC 00145DCC  88 1F 22 1B */	lbz r0, 0x221b(r31)
/* 801491F0 00145DD0  50 60 2E B4 */	rlwimi r0, r3, 5, 0x1a, 0x1a
/* 801491F4 00145DD4  98 1F 22 1B */	stb r0, 0x221b(r31)
lbl_801491F8:
/* 801491F8 00145DD8  80 01 00 24 */	lwz r0, 0x24(r1)
/* 801491FC 00145DDC  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80149200 00145DE0  38 21 00 20 */	addi r1, r1, 0x20
/* 80149204 00145DE4  7C 08 03 A6 */	mtlr r0
/* 80149208 00145DE8  4E 80 00 20 */	blr 

.global func_8014920C
func_8014920C:
/* 8014920C 00145DEC  28 03 00 00 */	cmplwi r3, 0
/* 80149210 00145DF0  40 82 00 0C */	bne lbl_8014921C
/* 80149214 00145DF4  38 60 00 01 */	li r3, 1
/* 80149218 00145DF8  4E 80 00 20 */	blr 
lbl_8014921C:
/* 8014921C 00145DFC  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 80149220 00145E00  28 03 00 00 */	cmplwi r3, 0
/* 80149224 00145E04  40 82 00 0C */	bne lbl_80149230
/* 80149228 00145E08  38 60 00 01 */	li r3, 1
/* 8014922C 00145E0C  4E 80 00 20 */	blr 
lbl_80149230:
/* 80149230 00145E10  80 03 00 10 */	lwz r0, 0x10(r3)
/* 80149234 00145E14  2C 00 01 56 */	cmpwi r0, 0x156
/* 80149238 00145E18  41 82 00 14 */	beq lbl_8014924C
/* 8014923C 00145E1C  2C 00 01 57 */	cmpwi r0, 0x157
/* 80149240 00145E20  41 82 00 0C */	beq lbl_8014924C
/* 80149244 00145E24  38 60 00 01 */	li r3, 1
/* 80149248 00145E28  4E 80 00 20 */	blr 
lbl_8014924C:
/* 8014924C 00145E2C  80 03 22 44 */	lwz r0, 0x2244(r3)
/* 80149250 00145E30  28 00 00 00 */	cmplwi r0, 0
/* 80149254 00145E34  40 82 00 0C */	bne lbl_80149260
/* 80149258 00145E38  38 60 00 01 */	li r3, 1
/* 8014925C 00145E3C  4E 80 00 20 */	blr 
lbl_80149260:
/* 80149260 00145E40  38 60 00 00 */	li r3, 0
/* 80149264 00145E44  4E 80 00 20 */	blr 

.global func_80149268
func_80149268:
/* 80149268 00145E48  7C 08 02 A6 */	mflr r0
/* 8014926C 00145E4C  90 01 00 04 */	stw r0, 4(r1)
/* 80149270 00145E50  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80149274 00145E54  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80149278 00145E58  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8014927C 00145E5C  7C 7E 1B 79 */	or. r30, r3, r3
/* 80149280 00145E60  41 82 00 2C */	beq lbl_801492AC
/* 80149284 00145E64  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 80149288 00145E68  28 1F 00 00 */	cmplwi r31, 0
/* 8014928C 00145E6C  41 82 00 1C */	beq lbl_801492A8
/* 80149290 00145E70  80 7F 22 44 */	lwz r3, 0x2244(r31)
/* 80149294 00145E74  28 03 00 00 */	cmplwi r3, 0
/* 80149298 00145E78  41 82 00 10 */	beq lbl_801492A8
/* 8014929C 00145E7C  48 17 F9 99 */	bl func_802C8C34
/* 801492A0 00145E80  38 00 00 00 */	li r0, 0
/* 801492A4 00145E84  90 1F 22 44 */	stw r0, 0x2244(r31)
lbl_801492A8:
/* 801492A8 00145E88  28 1E 00 00 */	cmplwi r30, 0
lbl_801492AC:
/* 801492AC 00145E8C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 801492B0 00145E90  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 801492B4 00145E94  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 801492B8 00145E98  38 21 00 20 */	addi r1, r1, 0x20
/* 801492BC 00145E9C  7C 08 03 A6 */	mtlr r0
/* 801492C0 00145EA0  4E 80 00 20 */	blr 

.global func_801492C4
func_801492C4:
/* 801492C4 00145EA4  28 03 00 00 */	cmplwi r3, 0
/* 801492C8 00145EA8  4D 82 00 20 */	beqlr 
/* 801492CC 00145EAC  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 801492D0 00145EB0  28 04 00 00 */	cmplwi r4, 0
/* 801492D4 00145EB4  41 82 00 18 */	beq lbl_801492EC
/* 801492D8 00145EB8  80 04 22 44 */	lwz r0, 0x2244(r4)
/* 801492DC 00145EBC  28 00 00 00 */	cmplwi r0, 0
/* 801492E0 00145EC0  41 82 00 0C */	beq lbl_801492EC
/* 801492E4 00145EC4  38 00 00 00 */	li r0, 0
/* 801492E8 00145EC8  90 04 22 44 */	stw r0, 0x2244(r4)
lbl_801492EC:
/* 801492EC 00145ECC  28 03 00 00 */	cmplwi r3, 0
/* 801492F0 00145ED0  4E 80 00 20 */	blr 

.global func_801492F4
func_801492F4:
/* 801492F4 00145ED4  28 03 00 00 */	cmplwi r3, 0
/* 801492F8 00145ED8  41 82 00 18 */	beq lbl_80149310
/* 801492FC 00145EDC  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 80149300 00145EE0  28 03 00 00 */	cmplwi r3, 0
/* 80149304 00145EE4  41 82 00 0C */	beq lbl_80149310
/* 80149308 00145EE8  80 63 22 04 */	lwz r3, 0x2204(r3)
/* 8014930C 00145EEC  4E 80 00 20 */	blr 
lbl_80149310:
/* 80149310 00145EF0  38 60 00 00 */	li r3, 0
/* 80149314 00145EF4  4E 80 00 20 */	blr 

.global func_80149318
func_80149318:
/* 80149318 00145EF8  7C 08 02 A6 */	mflr r0
/* 8014931C 00145EFC  38 80 01 56 */	li r4, 0x156
/* 80149320 00145F00  90 01 00 04 */	stw r0, 4(r1)
/* 80149324 00145F04  38 A0 01 57 */	li r5, 0x157
/* 80149328 00145F08  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8014932C 00145F0C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80149330 00145F10  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80149334 00145F14  4B F9 57 B5 */	bl func_800DEAE8
/* 80149338 00145F18  38 00 00 00 */	li r0, 0
/* 8014933C 00145F1C  90 1F 22 04 */	stw r0, 0x2204(r31)
/* 80149340 00145F20  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80149344 00145F24  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80149348 00145F28  38 21 00 18 */	addi r1, r1, 0x18
/* 8014934C 00145F2C  7C 08 03 A6 */	mtlr r0
/* 80149350 00145F30  4E 80 00 20 */	blr 

.global func_80149354
func_80149354:
/* 80149354 00145F34  7C 08 02 A6 */	mflr r0
/* 80149358 00145F38  90 01 00 04 */	stw r0, 4(r1)
/* 8014935C 00145F3C  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 80149360 00145F40  93 E1 00 24 */	stw r31, 0x24(r1)
/* 80149364 00145F44  93 C1 00 20 */	stw r30, 0x20(r1)
/* 80149368 00145F48  7C 7E 1B 78 */	mr r30, r3
/* 8014936C 00145F4C  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80149370 00145F50  80 1F 22 04 */	lwz r0, 0x2204(r31)
/* 80149374 00145F54  28 00 00 01 */	cmplwi r0, 1
/* 80149378 00145F58  40 82 00 50 */	bne lbl_801493C8
/* 8014937C 00145F5C  80 1F 22 44 */	lwz r0, 0x2244(r31)
/* 80149380 00145F60  28 00 00 00 */	cmplwi r0, 0
/* 80149384 00145F64  40 82 00 44 */	bne lbl_801493C8
/* 80149388 00145F68  38 7F 00 00 */	addi r3, r31, 0
/* 8014938C 00145F6C  38 80 00 1F */	li r4, 0x1f
/* 80149390 00145F70  4B F2 BC 7D */	bl func_8007500C
/* 80149394 00145F74  C0 3F 00 2C */	lfs f1, 0x2c(r31)
/* 80149398 00145F78  7C 65 1B 78 */	mr r5, r3
/* 8014939C 00145F7C  38 7E 00 00 */	addi r3, r30, 0
/* 801493A0 00145F80  38 9F 00 B0 */	addi r4, r31, 0xb0
/* 801493A4 00145F84  48 17 F7 85 */	bl func_802C8B28
/* 801493A8 00145F88  28 03 00 00 */	cmplwi r3, 0
/* 801493AC 00145F8C  90 7F 22 44 */	stw r3, 0x2244(r31)
/* 801493B0 00145F90  41 82 00 2C */	beq lbl_801493DC
/* 801493B4 00145F94  3C 60 80 0F */	lis r3, func_800EAF58@ha
/* 801493B8 00145F98  38 03 AF 58 */	addi r0, r3, func_800EAF58@l
/* 801493BC 00145F9C  90 1F 21 E4 */	stw r0, 0x21e4(r31)
/* 801493C0 00145FA0  90 1F 21 DC */	stw r0, 0x21dc(r31)
/* 801493C4 00145FA4  48 00 00 18 */	b lbl_801493DC
lbl_801493C8:
/* 801493C8 00145FA8  80 1F 22 04 */	lwz r0, 0x2204(r31)
/* 801493CC 00145FAC  28 00 00 02 */	cmplwi r0, 2
/* 801493D0 00145FB0  40 82 00 0C */	bne lbl_801493DC
/* 801493D4 00145FB4  7F C3 F3 78 */	mr r3, r30
/* 801493D8 00145FB8  4B FF FE 91 */	bl func_80149268
lbl_801493DC:
/* 801493DC 00145FBC  7F C3 F3 78 */	mr r3, r30
/* 801493E0 00145FC0  4B F2 5E 59 */	bl func_8006F238
/* 801493E4 00145FC4  2C 03 00 00 */	cmpwi r3, 0
/* 801493E8 00145FC8  40 82 00 3C */	bne lbl_80149424
/* 801493EC 00145FCC  28 1E 00 00 */	cmplwi r30, 0
/* 801493F0 00145FD0  41 82 00 2C */	beq lbl_8014941C
/* 801493F4 00145FD4  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 801493F8 00145FD8  28 1F 00 00 */	cmplwi r31, 0
/* 801493FC 00145FDC  41 82 00 1C */	beq lbl_80149418
/* 80149400 00145FE0  80 7F 22 44 */	lwz r3, 0x2244(r31)
/* 80149404 00145FE4  28 03 00 00 */	cmplwi r3, 0
/* 80149408 00145FE8  41 82 00 10 */	beq lbl_80149418
/* 8014940C 00145FEC  48 17 F8 29 */	bl func_802C8C34
/* 80149410 00145FF0  38 00 00 00 */	li r0, 0
/* 80149414 00145FF4  90 1F 22 44 */	stw r0, 0x2244(r31)
lbl_80149418:
/* 80149418 00145FF8  28 1E 00 00 */	cmplwi r30, 0
lbl_8014941C:
/* 8014941C 00145FFC  7F C3 F3 78 */	mr r3, r30
/* 80149420 00146000  4B F4 0E 9D */	bl func_8008A2BC
lbl_80149424:
/* 80149424 00146004  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 80149428 00146008  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 8014942C 0014600C  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 80149430 00146010  38 21 00 28 */	addi r1, r1, 0x28
/* 80149434 00146014  7C 08 03 A6 */	mtlr r0
/* 80149438 00146018  4E 80 00 20 */	blr 

.global func_8014943C
func_8014943C:
/* 8014943C 0014601C  7C 08 02 A6 */	mflr r0
/* 80149440 00146020  90 01 00 04 */	stw r0, 4(r1)
/* 80149444 00146024  94 21 FF F8 */	stwu r1, -8(r1)
/* 80149448 00146028  4B F9 58 E9 */	bl func_800DED30
/* 8014944C 0014602C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80149450 00146030  38 21 00 08 */	addi r1, r1, 8
/* 80149454 00146034  7C 08 03 A6 */	mtlr r0
/* 80149458 00146038  4E 80 00 20 */	blr 

.global func_8014945C
func_8014945C:
/* 8014945C 0014603C  7C 08 02 A6 */	mflr r0
/* 80149460 00146040  90 01 00 04 */	stw r0, 4(r1)
/* 80149464 00146044  94 21 FF F8 */	stwu r1, -8(r1)
/* 80149468 00146048  4B F3 BA D5 */	bl func_80084F3C
/* 8014946C 0014604C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80149470 00146050  38 21 00 08 */	addi r1, r1, 8
/* 80149474 00146054  7C 08 03 A6 */	mtlr r0
/* 80149478 00146058  4E 80 00 20 */	blr 

.global func_8014947C
func_8014947C:
/* 8014947C 0014605C  7C 08 02 A6 */	mflr r0
/* 80149480 00146060  90 01 00 04 */	stw r0, 4(r1)
/* 80149484 00146064  94 21 FF F8 */	stwu r1, -8(r1)
/* 80149488 00146068  4B F3 AD F9 */	bl func_80084280
/* 8014948C 0014606C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80149490 00146070  38 21 00 08 */	addi r1, r1, 8
/* 80149494 00146074  7C 08 03 A6 */	mtlr r0
/* 80149498 00146078  4E 80 00 20 */	blr 
