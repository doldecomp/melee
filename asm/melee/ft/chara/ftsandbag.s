.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

.global func_8014F9CC
func_8014F9CC:
/* 8014F9CC 0014C5AC  4E 80 00 20 */	blr 

.global ftSandbag_OnLoad
ftSandbag_OnLoad:
/* 8014F9D0 0014C5B0  7C 08 02 A6 */	mflr r0
/* 8014F9D4 0014C5B4  38 80 00 01 */	li r4, 1
/* 8014F9D8 0014C5B8  90 01 00 04 */	stw r0, 4(r1)
/* 8014F9DC 0014C5BC  94 21 FF F8 */	stwu r1, -8(r1)
/* 8014F9E0 0014C5C0  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8014F9E4 0014C5C4  80 A3 01 0C */	lwz r5, 0x10c(r3)
/* 8014F9E8 0014C5C8  80 E3 02 D8 */	lwz r7, 0x2d8(r3)
/* 8014F9EC 0014C5CC  80 C5 00 04 */	lwz r6, 4(r5)
/* 8014F9F0 0014C5D0  80 A6 00 00 */	lwz r5, 0(r6)
/* 8014F9F4 0014C5D4  80 06 00 04 */	lwz r0, 4(r6)
/* 8014F9F8 0014C5D8  90 A7 00 00 */	stw r5, 0(r7)
/* 8014F9FC 0014C5DC  90 07 00 04 */	stw r0, 4(r7)
/* 8014FA00 0014C5E0  90 E3 02 D4 */	stw r7, 0x2d4(r3)
/* 8014FA04 0014C5E4  88 03 22 28 */	lbz r0, 0x2228(r3)
/* 8014FA08 0014C5E8  50 80 2E B4 */	rlwimi r0, r4, 5, 0x1a, 0x1a
/* 8014FA0C 0014C5EC  98 03 22 28 */	stb r0, 0x2228(r3)
/* 8014FA10 0014C5F0  88 03 22 26 */	lbz r0, 0x2226(r3)
/* 8014FA14 0014C5F4  50 80 3E 30 */	rlwimi r0, r4, 7, 0x18, 0x18
/* 8014FA18 0014C5F8  98 03 22 26 */	stb r0, 0x2226(r3)
/* 8014FA1C 0014C5FC  48 00 00 15 */	bl func_8014FA30
/* 8014FA20 0014C600  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8014FA24 0014C604  38 21 00 08 */	addi r1, r1, 8
/* 8014FA28 0014C608  7C 08 03 A6 */	mtlr r0
/* 8014FA2C 0014C60C  4E 80 00 20 */	blr 

.global func_8014FA30
func_8014FA30:
/* 8014FA30 0014C610  7C 08 02 A6 */	mflr r0
/* 8014FA34 0014C614  90 01 00 04 */	stw r0, 4(r1)
/* 8014FA38 0014C618  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8014FA3C 0014C61C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8014FA40 0014C620  7C 7F 1B 78 */	mr r31, r3
/* 8014FA44 0014C624  80 83 05 E8 */	lwz r4, 0x5e8(r3)
/* 8014FA48 0014C628  80 64 00 50 */	lwz r3, 0x50(r4)
/* 8014FA4C 0014C62C  80 84 00 C0 */	lwz r4, 0xc0(r4)
/* 8014FA50 0014C630  4B EB C7 71 */	bl func_8000C1C0
/* 8014FA54 0014C634  80 9F 05 E8 */	lwz r4, 0x5e8(r31)
/* 8014FA58 0014C638  80 64 00 54 */	lwz r3, 0x54(r4)
/* 8014FA5C 0014C63C  80 84 00 C4 */	lwz r4, 0xc4(r4)
/* 8014FA60 0014C640  4B EB C7 61 */	bl func_8000C1C0
/* 8014FA64 0014C644  80 9F 05 E8 */	lwz r4, 0x5e8(r31)
/* 8014FA68 0014C648  80 64 00 50 */	lwz r3, 0x50(r4)
/* 8014FA6C 0014C64C  80 84 01 10 */	lwz r4, 0x110(r4)
/* 8014FA70 0014C650  4B EB C7 51 */	bl func_8000C1C0
/* 8014FA74 0014C654  80 9F 05 E8 */	lwz r4, 0x5e8(r31)
/* 8014FA78 0014C658  80 64 00 54 */	lwz r3, 0x54(r4)
/* 8014FA7C 0014C65C  80 84 01 14 */	lwz r4, 0x114(r4)
/* 8014FA80 0014C660  4B EB C7 41 */	bl func_8000C1C0
/* 8014FA84 0014C664  80 9F 05 E8 */	lwz r4, 0x5e8(r31)
/* 8014FA88 0014C668  80 64 00 70 */	lwz r3, 0x70(r4)
/* 8014FA8C 0014C66C  80 84 02 50 */	lwz r4, 0x250(r4)
/* 8014FA90 0014C670  4B EB C7 99 */	bl func_8000C228
/* 8014FA94 0014C674  80 9F 05 E8 */	lwz r4, 0x5e8(r31)
/* 8014FA98 0014C678  80 64 00 74 */	lwz r3, 0x74(r4)
/* 8014FA9C 0014C67C  80 84 02 54 */	lwz r4, 0x254(r4)
/* 8014FAA0 0014C680  4B EB C7 89 */	bl func_8000C228
/* 8014FAA4 0014C684  80 7F 05 E8 */	lwz r3, 0x5e8(r31)
/* 8014FAA8 0014C688  38 80 00 01 */	li r4, 1
/* 8014FAAC 0014C68C  C0 22 A4 90 */	lfs f1, lbl_804D9E70@sda21(r2)
/* 8014FAB0 0014C690  80 63 00 70 */	lwz r3, 0x70(r3)
/* 8014FAB4 0014C694  4B EB C9 6D */	bl func_8000C420
/* 8014FAB8 0014C698  80 7F 05 E8 */	lwz r3, 0x5e8(r31)
/* 8014FABC 0014C69C  38 80 00 02 */	li r4, 2
/* 8014FAC0 0014C6A0  C0 22 A4 90 */	lfs f1, lbl_804D9E70@sda21(r2)
/* 8014FAC4 0014C6A4  80 63 00 70 */	lwz r3, 0x70(r3)
/* 8014FAC8 0014C6A8  4B EB C9 59 */	bl func_8000C420
/* 8014FACC 0014C6AC  80 7F 05 E8 */	lwz r3, 0x5e8(r31)
/* 8014FAD0 0014C6B0  38 80 00 01 */	li r4, 1
/* 8014FAD4 0014C6B4  C0 22 A4 90 */	lfs f1, lbl_804D9E70@sda21(r2)
/* 8014FAD8 0014C6B8  80 63 00 74 */	lwz r3, 0x74(r3)
/* 8014FADC 0014C6BC  4B EB C9 45 */	bl func_8000C420
/* 8014FAE0 0014C6C0  80 7F 05 E8 */	lwz r3, 0x5e8(r31)
/* 8014FAE4 0014C6C4  38 80 00 02 */	li r4, 2
/* 8014FAE8 0014C6C8  C0 22 A4 90 */	lfs f1, lbl_804D9E70@sda21(r2)
/* 8014FAEC 0014C6CC  80 63 00 74 */	lwz r3, 0x74(r3)
/* 8014FAF0 0014C6D0  4B EB C9 31 */	bl func_8000C420
/* 8014FAF4 0014C6D4  80 9F 05 E8 */	lwz r4, 0x5e8(r31)
/* 8014FAF8 0014C6D8  80 64 00 60 */	lwz r3, 0x60(r4)
/* 8014FAFC 0014C6DC  80 84 00 50 */	lwz r4, 0x50(r4)
/* 8014FB00 0014C6E0  4B EB C7 29 */	bl func_8000C228
/* 8014FB04 0014C6E4  80 9F 05 E8 */	lwz r4, 0x5e8(r31)
/* 8014FB08 0014C6E8  80 64 00 64 */	lwz r3, 0x64(r4)
/* 8014FB0C 0014C6EC  80 84 00 54 */	lwz r4, 0x54(r4)
/* 8014FB10 0014C6F0  4B EB C7 19 */	bl func_8000C228
/* 8014FB14 0014C6F4  80 7F 05 E8 */	lwz r3, 0x5e8(r31)
/* 8014FB18 0014C6F8  38 80 00 01 */	li r4, 1
/* 8014FB1C 0014C6FC  C0 22 A4 94 */	lfs f1, lbl_804D9E74@sda21(r2)
/* 8014FB20 0014C700  80 63 00 60 */	lwz r3, 0x60(r3)
/* 8014FB24 0014C704  4B EB C8 FD */	bl func_8000C420
/* 8014FB28 0014C708  80 7F 05 E8 */	lwz r3, 0x5e8(r31)
/* 8014FB2C 0014C70C  38 80 00 02 */	li r4, 2
/* 8014FB30 0014C710  C0 22 A4 94 */	lfs f1, lbl_804D9E74@sda21(r2)
/* 8014FB34 0014C714  80 63 00 60 */	lwz r3, 0x60(r3)
/* 8014FB38 0014C718  4B EB C8 E9 */	bl func_8000C420
/* 8014FB3C 0014C71C  80 7F 05 E8 */	lwz r3, 0x5e8(r31)
/* 8014FB40 0014C720  38 80 00 01 */	li r4, 1
/* 8014FB44 0014C724  C0 22 A4 94 */	lfs f1, lbl_804D9E74@sda21(r2)
/* 8014FB48 0014C728  80 63 00 64 */	lwz r3, 0x64(r3)
/* 8014FB4C 0014C72C  4B EB C8 D5 */	bl func_8000C420
/* 8014FB50 0014C730  80 7F 05 E8 */	lwz r3, 0x5e8(r31)
/* 8014FB54 0014C734  38 80 00 02 */	li r4, 2
/* 8014FB58 0014C738  C0 22 A4 94 */	lfs f1, lbl_804D9E74@sda21(r2)
/* 8014FB5C 0014C73C  80 63 00 64 */	lwz r3, 0x64(r3)
/* 8014FB60 0014C740  4B EB C8 C1 */	bl func_8000C420
/* 8014FB64 0014C744  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8014FB68 0014C748  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8014FB6C 0014C74C  38 21 00 18 */	addi r1, r1, 0x18
/* 8014FB70 0014C750  7C 08 03 A6 */	mtlr r0
/* 8014FB74 0014C754  4E 80 00 20 */	blr 

.global func_8014FB9C
func_8014FB9C:
/* 8014FB9C 0014C77C  4E 80 00 20 */	blr 

.global func_8014FBA0
func_8014FBA0:
/* 8014FBA0 0014C780  4E 80 00 20 */	blr 

.global func_8014FBA4
func_8014FBA4:
/* 8014FBA4 0014C784  7C 08 02 A6 */	mflr r0
/* 8014FBA8 0014C788  90 01 00 04 */	stw r0, 4(r1)
/* 8014FBAC 0014C78C  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8014FBB0 0014C790  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8014FBB4 0014C794  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8014FBB8 0014C798  7C 7E 1B 78 */	mr r30, r3
/* 8014FBBC 0014C79C  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8014FBC0 0014C7A0  80 03 00 E0 */	lwz r0, 0xe0(r3)
/* 8014FBC4 0014C7A4  3B E3 00 00 */	addi r31, r3, 0
/* 8014FBC8 0014C7A8  2C 00 00 01 */	cmpwi r0, 1
/* 8014FBCC 0014C7AC  40 82 00 0C */	bne lbl_8014FBD8
/* 8014FBD0 0014C7B0  7F E3 FB 78 */	mr r3, r31
/* 8014FBD4 0014C7B4  4B F2 DC 29 */	bl func_8007D7FC
lbl_8014FBD8:
/* 8014FBD8 0014C7B8  C0 22 A4 98 */	lfs f1, lbl_804D9E78@sda21(r2)
/* 8014FBDC 0014C7BC  7F C3 F3 78 */	mr r3, r30
/* 8014FBE0 0014C7C0  C0 42 A4 9C */	lfs f2, lbl_804D9E7C@sda21(r2)
/* 8014FBE4 0014C7C4  38 80 01 55 */	li r4, 0x155
/* 8014FBE8 0014C7C8  FC 60 08 90 */	fmr f3, f1
/* 8014FBEC 0014C7CC  38 A0 00 00 */	li r5, 0
/* 8014FBF0 0014C7D0  38 C0 00 00 */	li r6, 0
/* 8014FBF4 0014C7D4  4B F1 97 B9 */	bl func_800693AC
/* 8014FBF8 0014C7D8  80 8D AE B4 */	lwz r4, lbl_804D6554@sda21(r13)
/* 8014FBFC 0014C7DC  7F E3 FB 78 */	mr r3, r31
/* 8014FC00 0014C7E0  80 84 05 F0 */	lwz r4, 0x5f0(r4)
/* 8014FC04 0014C7E4  4B F2 F3 BD */	bl func_8007EFC0
/* 8014FC08 0014C7E8  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8014FC0C 0014C7EC  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8014FC10 0014C7F0  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8014FC14 0014C7F4  38 21 00 18 */	addi r1, r1, 0x18
/* 8014FC18 0014C7F8  7C 08 03 A6 */	mtlr r0
/* 8014FC1C 0014C7FC  4E 80 00 20 */	blr 

.global lbl_8014FC20
lbl_8014FC20:
/* 8014FC20 0014C800  4E 80 00 20 */	blr 

.global lbl_8014FC24
lbl_8014FC24:
/* 8014FC24 0014C804  4E 80 00 20 */	blr 

.global lbl_8014FC28
lbl_8014FC28:
/* 8014FC28 0014C808  7C 08 02 A6 */	mflr r0
/* 8014FC2C 0014C80C  90 01 00 04 */	stw r0, 4(r1)
/* 8014FC30 0014C810  94 21 FF F8 */	stwu r1, -8(r1)
/* 8014FC34 0014C814  4B F3 53 09 */	bl func_80084F3C
/* 8014FC38 0014C818  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8014FC3C 0014C81C  38 21 00 08 */	addi r1, r1, 8
/* 8014FC40 0014C820  7C 08 03 A6 */	mtlr r0
/* 8014FC44 0014C824  4E 80 00 20 */	blr 

.global lbl_8014FC48
lbl_8014FC48:
/* 8014FC48 0014C828  7C 08 02 A6 */	mflr r0
/* 8014FC4C 0014C82C  90 01 00 04 */	stw r0, 4(r1)
/* 8014FC50 0014C830  94 21 FF F8 */	stwu r1, -8(r1)
/* 8014FC54 0014C834  4B F3 43 35 */	bl func_80083F88
/* 8014FC58 0014C838  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8014FC5C 0014C83C  38 21 00 08 */	addi r1, r1, 8
/* 8014FC60 0014C840  7C 08 03 A6 */	mtlr r0
/* 8014FC64 0014C844  4E 80 00 20 */	blr 


.section .sdata2

.global lbl_804D9E70
lbl_804D9E70:
	.4byte 0xBFC90FDB
.global lbl_804D9E74
lbl_804D9E74:
	.4byte 0xBFC02037
.global lbl_804D9E78
lbl_804D9E78:
	.4byte 0x00000000
.global lbl_804D9E7C
lbl_804D9E7C:
	.4byte 0x3F800000
