.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

.global HSD_FogSet
HSD_FogSet:
/* 8037D970 0037A550  7C 08 02 A6 */	mflr r0
/* 8037D974 0037A554  90 01 00 04 */	stw r0, 4(r1)
/* 8037D978 0037A558  94 21 FF 38 */	stwu r1, -0xc8(r1)
/* 8037D97C 0037A55C  DB E1 00 C0 */	stfd f31, 0xc0(r1)
/* 8037D980 0037A560  93 E1 00 BC */	stw r31, 0xbc(r1)
/* 8037D984 0037A564  93 C1 00 B8 */	stw r30, 0xb8(r1)
/* 8037D988 0037A568  93 A1 00 B4 */	stw r29, 0xb4(r1)
/* 8037D98C 0037A56C  7C 7D 1B 79 */	or. r29, r3, r3
/* 8037D990 0037A570  40 82 00 2C */	bne lbl_8037D9BC
/* 8037D994 0037A574  C0 22 ED 14 */	lfs f1, lbl_804DE6F4@sda21(r2)
/* 8037D998 0037A578  38 81 00 10 */	addi r4, r1, 0x10
/* 8037D99C 0037A57C  80 02 ED 10 */	lwz r0, lbl_804DE6F0@sda21(r2)
/* 8037D9A0 0037A580  38 60 00 00 */	li r3, 0
/* 8037D9A4 0037A584  FC 40 08 90 */	fmr f2, f1
/* 8037D9A8 0037A588  FC 60 08 90 */	fmr f3, f1
/* 8037D9AC 0037A58C  90 01 00 10 */	stw r0, 0x10(r1)
/* 8037D9B0 0037A590  FC 80 08 90 */	fmr f4, f1
/* 8037D9B4 0037A594  4B FC 2E 11 */	bl func_803407C4
/* 8037D9B8 0037A598  48 00 02 60 */	b lbl_8037DC18
lbl_8037D9BC:
/* 8037D9BC 0037A59C  4B FE C8 CD */	bl func_8036A288
/* 8037D9C0 0037A5A0  7C 7E 1B 79 */	or. r30, r3, r3
/* 8037D9C4 0037A5A4  40 82 00 18 */	bne lbl_8037D9DC
/* 8037D9C8 0037A5A8  3C 60 80 40 */	lis r3, lbl_804070F0@ha
/* 8037D9CC 0037A5AC  38 A3 70 F0 */	addi r5, r3, lbl_804070F0@l
/* 8037D9D0 0037A5B0  38 6D A8 80 */	addi r3, r13, lbl_804D5F20@sda21
/* 8037D9D4 0037A5B4  38 80 00 4D */	li r4, 0x4d
/* 8037D9D8 0037A5B8  48 00 A8 A1 */	bl HSD_Panic
lbl_8037D9DC:
/* 8037D9DC 0037A5BC  80 1D 00 18 */	lwz r0, 0x18(r29)
/* 8037D9E0 0037A5C0  38 7E 00 00 */	addi r3, r30, 0
/* 8037D9E4 0037A5C4  3B E1 00 0C */	addi r31, r1, 0xc
/* 8037D9E8 0037A5C8  90 01 00 0C */	stw r0, 0xc(r1)
/* 8037D9EC 0037A5CC  4B FE C5 C5 */	bl HSD_CObjGetFar
/* 8037D9F0 0037A5D0  FF E0 08 90 */	fmr f31, f1
/* 8037D9F4 0037A5D4  7F C3 F3 78 */	mr r3, r30
/* 8037D9F8 0037A5D8  4B FE C5 91 */	bl HSD_CObjGetNear
/* 8037D9FC 0037A5DC  FC 60 08 90 */	fmr f3, f1
/* 8037DA00 0037A5E0  80 7D 00 08 */	lwz r3, 8(r29)
/* 8037DA04 0037A5E4  FC 80 F8 90 */	fmr f4, f31
/* 8037DA08 0037A5E8  C0 3D 00 10 */	lfs f1, 0x10(r29)
/* 8037DA0C 0037A5EC  C0 5D 00 14 */	lfs f2, 0x14(r29)
/* 8037DA10 0037A5F0  7F E4 FB 78 */	mr r4, r31
/* 8037DA14 0037A5F4  4B FC 2D B1 */	bl func_803407C4
/* 8037DA18 0037A5F8  80 1D 00 0C */	lwz r0, 0xc(r29)
/* 8037DA1C 0037A5FC  28 00 00 00 */	cmplwi r0, 0
/* 8037DA20 0037A600  41 82 01 E8 */	beq lbl_8037DC08
/* 8037DA24 0037A604  38 61 00 70 */	addi r3, r1, 0x70
/* 8037DA28 0037A608  4B FC 3C E9 */	bl func_80341710
/* 8037DA2C 0037A60C  80 BD 00 0C */	lwz r5, 0xc(r29)
/* 8037DA30 0037A610  3C 00 43 30 */	lis r0, 0x4330
/* 8037DA34 0037A614  C8 42 ED 28 */	lfd f2, lbl_804DE708@sda21(r2)
/* 8037DA38 0037A618  A8 65 00 08 */	lha r3, 8(r5)
/* 8037DA3C 0037A61C  C0 61 00 78 */	lfs f3, 0x78(r1)
/* 8037DA40 0037A620  38 63 01 40 */	addi r3, r3, 0x140
/* 8037DA44 0037A624  C0 02 ED 18 */	lfs f0, lbl_804DE6F8@sda21(r2)
/* 8037DA48 0037A628  6C 63 80 00 */	xoris r3, r3, 0x8000
/* 8037DA4C 0037A62C  C0 81 00 70 */	lfs f4, 0x70(r1)
/* 8037DA50 0037A630  90 61 00 AC */	stw r3, 0xac(r1)
/* 8037DA54 0037A634  90 01 00 A8 */	stw r0, 0xa8(r1)
/* 8037DA58 0037A638  C8 21 00 A8 */	lfd f1, 0xa8(r1)
/* 8037DA5C 0037A63C  EC 21 10 28 */	fsubs f1, f1, f2
/* 8037DA60 0037A640  EC 23 00 72 */	fmuls f1, f3, f1
/* 8037DA64 0037A644  EC 01 00 24 */	fdivs f0, f1, f0
/* 8037DA68 0037A648  EC 04 00 2A */	fadds f0, f4, f0
/* 8037DA6C 0037A64C  FC 00 00 1E */	fctiwz f0, f0
/* 8037DA70 0037A650  D8 01 00 A0 */	stfd f0, 0xa0(r1)
/* 8037DA74 0037A654  83 E1 00 A4 */	lwz r31, 0xa4(r1)
/* 8037DA78 0037A658  2C 1F 00 00 */	cmpwi r31, 0
/* 8037DA7C 0037A65C  40 80 00 08 */	bge lbl_8037DA84
/* 8037DA80 0037A660  3B E0 00 00 */	li r31, 0
lbl_8037DA84:
/* 8037DA84 0037A664  2C 1F 02 80 */	cmpwi r31, 0x280
/* 8037DA88 0037A668  40 81 00 08 */	ble lbl_8037DA90
/* 8037DA8C 0037A66C  3B E0 02 80 */	li r31, 0x280
lbl_8037DA90:
/* 8037DA90 0037A670  A0 85 00 0A */	lhz r4, 0xa(r5)
/* 8037DA94 0037A674  28 04 00 00 */	cmplwi r4, 0
/* 8037DA98 0037A678  41 82 00 14 */	beq lbl_8037DAAC
/* 8037DA9C 0037A67C  38 61 00 88 */	addi r3, r1, 0x88
/* 8037DAA0 0037A680  38 A5 00 0C */	addi r5, r5, 0xc
/* 8037DAA4 0037A684  4B FC 2E D1 */	bl func_80340974
/* 8037DAA8 0037A688  48 00 01 4C */	b lbl_8037DBF4
lbl_8037DAAC:
/* 8037DAAC 0037A68C  3C 60 80 3C */	lis r3, lbl_803B95A8@ha
/* 8037DAB0 0037A690  38 A3 95 A8 */	addi r5, r3, lbl_803B95A8@l
/* 8037DAB4 0037A694  80 85 00 00 */	lwz r4, 0(r5)
/* 8037DAB8 0037A698  38 61 00 54 */	addi r3, r1, 0x54
/* 8037DABC 0037A69C  80 05 00 04 */	lwz r0, 4(r5)
/* 8037DAC0 0037A6A0  90 81 00 14 */	stw r4, 0x14(r1)
/* 8037DAC4 0037A6A4  90 01 00 18 */	stw r0, 0x18(r1)
/* 8037DAC8 0037A6A8  80 85 00 08 */	lwz r4, 8(r5)
/* 8037DACC 0037A6AC  80 05 00 0C */	lwz r0, 0xc(r5)
/* 8037DAD0 0037A6B0  90 81 00 1C */	stw r4, 0x1c(r1)
/* 8037DAD4 0037A6B4  90 01 00 20 */	stw r0, 0x20(r1)
/* 8037DAD8 0037A6B8  80 85 00 10 */	lwz r4, 0x10(r5)
/* 8037DADC 0037A6BC  80 05 00 14 */	lwz r0, 0x14(r5)
/* 8037DAE0 0037A6C0  90 81 00 24 */	stw r4, 0x24(r1)
/* 8037DAE4 0037A6C4  90 01 00 28 */	stw r0, 0x28(r1)
/* 8037DAE8 0037A6C8  80 85 00 18 */	lwz r4, 0x18(r5)
/* 8037DAEC 0037A6CC  80 05 00 1C */	lwz r0, 0x1c(r5)
/* 8037DAF0 0037A6D0  90 81 00 2C */	stw r4, 0x2c(r1)
/* 8037DAF4 0037A6D4  90 01 00 30 */	stw r0, 0x30(r1)
/* 8037DAF8 0037A6D8  80 85 00 20 */	lwz r4, 0x20(r5)
/* 8037DAFC 0037A6DC  80 05 00 24 */	lwz r0, 0x24(r5)
/* 8037DB00 0037A6E0  90 81 00 34 */	stw r4, 0x34(r1)
/* 8037DB04 0037A6E4  90 01 00 38 */	stw r0, 0x38(r1)
/* 8037DB08 0037A6E8  80 85 00 28 */	lwz r4, 0x28(r5)
/* 8037DB0C 0037A6EC  80 05 00 2C */	lwz r0, 0x2c(r5)
/* 8037DB10 0037A6F0  90 81 00 3C */	stw r4, 0x3c(r1)
/* 8037DB14 0037A6F4  90 01 00 40 */	stw r0, 0x40(r1)
/* 8037DB18 0037A6F8  80 85 00 30 */	lwz r4, 0x30(r5)
/* 8037DB1C 0037A6FC  80 05 00 34 */	lwz r0, 0x34(r5)
/* 8037DB20 0037A700  90 81 00 44 */	stw r4, 0x44(r1)
/* 8037DB24 0037A704  90 01 00 48 */	stw r0, 0x48(r1)
/* 8037DB28 0037A708  80 85 00 38 */	lwz r4, 0x38(r5)
/* 8037DB2C 0037A70C  80 05 00 3C */	lwz r0, 0x3c(r5)
/* 8037DB30 0037A710  90 81 00 4C */	stw r4, 0x4c(r1)
/* 8037DB34 0037A714  90 01 00 50 */	stw r0, 0x50(r1)
/* 8037DB38 0037A718  4B FC 38 59 */	bl func_80341390
/* 8037DB3C 0037A71C  C0 01 00 54 */	lfs f0, 0x54(r1)
/* 8037DB40 0037A720  FC 00 00 1E */	fctiwz f0, f0
/* 8037DB44 0037A724  D8 01 00 A0 */	stfd f0, 0xa0(r1)
/* 8037DB48 0037A728  80 01 00 A4 */	lwz r0, 0xa4(r1)
/* 8037DB4C 0037A72C  2C 00 00 01 */	cmpwi r0, 1
/* 8037DB50 0037A730  41 82 00 50 */	beq lbl_8037DBA0
/* 8037DB54 0037A734  40 80 00 84 */	bge lbl_8037DBD8
/* 8037DB58 0037A738  2C 00 00 00 */	cmpwi r0, 0
/* 8037DB5C 0037A73C  40 80 00 08 */	bge lbl_8037DB64
/* 8037DB60 0037A740  48 00 00 78 */	b lbl_8037DBD8
lbl_8037DB64:
/* 8037DB64 0037A744  C0 01 00 58 */	lfs f0, 0x58(r1)
/* 8037DB68 0037A748  C0 21 00 5C */	lfs f1, 0x5c(r1)
/* 8037DB6C 0037A74C  D0 01 00 14 */	stfs f0, 0x14(r1)
/* 8037DB70 0037A750  C0 01 00 60 */	lfs f0, 0x60(r1)
/* 8037DB74 0037A754  D0 21 00 1C */	stfs f1, 0x1c(r1)
/* 8037DB78 0037A758  C0 21 00 64 */	lfs f1, 0x64(r1)
/* 8037DB7C 0037A75C  D0 01 00 28 */	stfs f0, 0x28(r1)
/* 8037DB80 0037A760  C0 01 00 68 */	lfs f0, 0x68(r1)
/* 8037DB84 0037A764  D0 21 00 2C */	stfs f1, 0x2c(r1)
/* 8037DB88 0037A768  C0 21 00 6C */	lfs f1, 0x6c(r1)
/* 8037DB8C 0037A76C  D0 01 00 3C */	stfs f0, 0x3c(r1)
/* 8037DB90 0037A770  C0 02 ED 1C */	lfs f0, lbl_804DE6FC@sda21(r2)
/* 8037DB94 0037A774  D0 21 00 40 */	stfs f1, 0x40(r1)
/* 8037DB98 0037A778  D0 01 00 4C */	stfs f0, 0x4c(r1)
/* 8037DB9C 0037A77C  48 00 00 3C */	b lbl_8037DBD8
lbl_8037DBA0:
/* 8037DBA0 0037A780  C0 01 00 58 */	lfs f0, 0x58(r1)
/* 8037DBA4 0037A784  C0 21 00 5C */	lfs f1, 0x5c(r1)
/* 8037DBA8 0037A788  D0 01 00 14 */	stfs f0, 0x14(r1)
/* 8037DBAC 0037A78C  C0 01 00 60 */	lfs f0, 0x60(r1)
/* 8037DBB0 0037A790  D0 21 00 20 */	stfs f1, 0x20(r1)
/* 8037DBB4 0037A794  C0 21 00 64 */	lfs f1, 0x64(r1)
/* 8037DBB8 0037A798  D0 01 00 28 */	stfs f0, 0x28(r1)
/* 8037DBBC 0037A79C  C0 01 00 68 */	lfs f0, 0x68(r1)
/* 8037DBC0 0037A7A0  D0 21 00 30 */	stfs f1, 0x30(r1)
/* 8037DBC4 0037A7A4  C0 21 00 6C */	lfs f1, 0x6c(r1)
/* 8037DBC8 0037A7A8  D0 01 00 3C */	stfs f0, 0x3c(r1)
/* 8037DBCC 0037A7AC  C0 02 ED 20 */	lfs f0, lbl_804DE700@sda21(r2)
/* 8037DBD0 0037A7B0  D0 21 00 40 */	stfs f1, 0x40(r1)
/* 8037DBD4 0037A7B4  D0 01 00 50 */	stfs f0, 0x50(r1)
lbl_8037DBD8:
/* 8037DBD8 0037A7B8  C0 01 00 78 */	lfs f0, 0x78(r1)
/* 8037DBDC 0037A7BC  38 61 00 88 */	addi r3, r1, 0x88
/* 8037DBE0 0037A7C0  38 A1 00 14 */	addi r5, r1, 0x14
/* 8037DBE4 0037A7C4  FC 00 00 1E */	fctiwz f0, f0
/* 8037DBE8 0037A7C8  D8 01 00 A0 */	stfd f0, 0xa0(r1)
/* 8037DBEC 0037A7CC  80 81 00 A4 */	lwz r4, 0xa4(r1)
/* 8037DBF0 0037A7D0  4B FC 2D 85 */	bl func_80340974
lbl_8037DBF4:
/* 8037DBF4 0037A7D4  57 E4 04 3E */	clrlwi r4, r31, 0x10
/* 8037DBF8 0037A7D8  38 A1 00 88 */	addi r5, r1, 0x88
/* 8037DBFC 0037A7DC  38 60 00 01 */	li r3, 1
/* 8037DC00 0037A7E0  4B FC 2F 3D */	bl func_80340B3C
/* 8037DC04 0037A7E4  48 00 00 14 */	b lbl_8037DC18
lbl_8037DC08:
/* 8037DC08 0037A7E8  38 60 00 00 */	li r3, 0
/* 8037DC0C 0037A7EC  38 80 00 00 */	li r4, 0
/* 8037DC10 0037A7F0  38 A0 00 00 */	li r5, 0
/* 8037DC14 0037A7F4  4B FC 2F 29 */	bl func_80340B3C
lbl_8037DC18:
/* 8037DC18 0037A7F8  80 01 00 CC */	lwz r0, 0xcc(r1)
/* 8037DC1C 0037A7FC  CB E1 00 C0 */	lfd f31, 0xc0(r1)
/* 8037DC20 0037A800  83 E1 00 BC */	lwz r31, 0xbc(r1)
/* 8037DC24 0037A804  83 C1 00 B8 */	lwz r30, 0xb8(r1)
/* 8037DC28 0037A808  83 A1 00 B4 */	lwz r29, 0xb4(r1)
/* 8037DC2C 0037A80C  38 21 00 C8 */	addi r1, r1, 0xc8
/* 8037DC30 0037A810  7C 08 03 A6 */	mtlr r0
/* 8037DC34 0037A814  4E 80 00 20 */	blr 

.global func_8037DC38
func_8037DC38:
/* 8037DC38 0037A818  7C 08 02 A6 */	mflr r0
/* 8037DC3C 0037A81C  3C 80 80 40 */	lis r4, lbl_80407078@ha
/* 8037DC40 0037A820  90 01 00 04 */	stw r0, 4(r1)
/* 8037DC44 0037A824  38 04 70 78 */	addi r0, r4, lbl_80407078@l
/* 8037DC48 0037A828  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8037DC4C 0037A82C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8037DC50 0037A830  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8037DC54 0037A834  3B C3 00 00 */	addi r30, r3, 0
/* 8037DC58 0037A838  7C 03 03 78 */	mr r3, r0
/* 8037DC5C 0037A83C  48 00 46 E9 */	bl hsdNew
/* 8037DC60 0037A840  7C 7F 1B 79 */	or. r31, r3, r3
/* 8037DC64 0037A844  40 82 00 14 */	bne lbl_8037DC78
/* 8037DC68 0037A848  38 6D A8 80 */	addi r3, r13, lbl_804D5F20@sda21
/* 8037DC6C 0037A84C  38 80 00 8C */	li r4, 0x8c
/* 8037DC70 0037A850  38 AD A8 88 */	addi r5, r13, lbl_804D5F28@sda21
/* 8037DC74 0037A854  48 00 A5 AD */	bl __assert
lbl_8037DC78:
/* 8037DC78 0037A858  28 1F 00 00 */	cmplwi r31, 0
/* 8037DC7C 0037A85C  40 82 00 14 */	bne lbl_8037DC90
/* 8037DC80 0037A860  38 6D A8 80 */	addi r3, r13, lbl_804D5F20@sda21
/* 8037DC84 0037A864  38 80 00 99 */	li r4, 0x99
/* 8037DC88 0037A868  38 AD A8 88 */	addi r5, r13, lbl_804D5F28@sda21
/* 8037DC8C 0037A86C  48 00 A5 95 */	bl __assert
lbl_8037DC90:
/* 8037DC90 0037A870  38 7F 00 00 */	addi r3, r31, 0
/* 8037DC94 0037A874  38 9E 00 00 */	addi r4, r30, 0
/* 8037DC98 0037A878  48 00 00 35 */	bl func_8037DCCC
/* 8037DC9C 0037A87C  80 7E 00 04 */	lwz r3, 4(r30)
/* 8037DCA0 0037A880  28 03 00 00 */	cmplwi r3, 0
/* 8037DCA4 0037A884  41 82 00 0C */	beq lbl_8037DCB0
/* 8037DCA8 0037A888  48 00 00 B1 */	bl func_8037DD58
/* 8037DCAC 0037A88C  90 7F 00 0C */	stw r3, 0xc(r31)
lbl_8037DCB0:
/* 8037DCB0 0037A890  7F E3 FB 78 */	mr r3, r31
/* 8037DCB4 0037A894  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8037DCB8 0037A898  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8037DCBC 0037A89C  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8037DCC0 0037A8A0  38 21 00 20 */	addi r1, r1, 0x20
/* 8037DCC4 0037A8A4  7C 08 03 A6 */	mtlr r0
/* 8037DCC8 0037A8A8  4E 80 00 20 */	blr 

.global func_8037DCCC
func_8037DCCC:
/* 8037DCCC 0037A8AC  7C 08 02 A6 */	mflr r0
/* 8037DCD0 0037A8B0  90 01 00 04 */	stw r0, 4(r1)
/* 8037DCD4 0037A8B4  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8037DCD8 0037A8B8  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 8037DCDC 0037A8BC  7C 7F 1B 79 */	or. r31, r3, r3
/* 8037DCE0 0037A8C0  41 82 00 64 */	beq lbl_8037DD44
/* 8037DCE4 0037A8C4  28 04 00 00 */	cmplwi r4, 0
/* 8037DCE8 0037A8C8  41 82 00 28 */	beq lbl_8037DD10
/* 8037DCEC 0037A8CC  80 04 00 00 */	lwz r0, 0(r4)
/* 8037DCF0 0037A8D0  90 1F 00 08 */	stw r0, 8(r31)
/* 8037DCF4 0037A8D4  C0 04 00 08 */	lfs f0, 8(r4)
/* 8037DCF8 0037A8D8  D0 1F 00 10 */	stfs f0, 0x10(r31)
/* 8037DCFC 0037A8DC  C0 04 00 0C */	lfs f0, 0xc(r4)
/* 8037DD00 0037A8E0  D0 1F 00 14 */	stfs f0, 0x14(r31)
/* 8037DD04 0037A8E4  80 04 00 10 */	lwz r0, 0x10(r4)
/* 8037DD08 0037A8E8  90 1F 00 18 */	stw r0, 0x18(r31)
/* 8037DD0C 0037A8EC  48 00 00 38 */	b lbl_8037DD44
lbl_8037DD10:
/* 8037DD10 0037A8F0  38 61 00 10 */	addi r3, r1, 0x10
/* 8037DD14 0037A8F4  4B FC 39 FD */	bl func_80341710
/* 8037DD18 0037A8F8  38 00 00 02 */	li r0, 2
/* 8037DD1C 0037A8FC  90 1F 00 08 */	stw r0, 8(r31)
/* 8037DD20 0037A900  38 00 00 FF */	li r0, 0xff
/* 8037DD24 0037A904  C0 01 00 20 */	lfs f0, 0x20(r1)
/* 8037DD28 0037A908  D0 1F 00 10 */	stfs f0, 0x10(r31)
/* 8037DD2C 0037A90C  C0 01 00 24 */	lfs f0, 0x24(r1)
/* 8037DD30 0037A910  D0 1F 00 14 */	stfs f0, 0x14(r31)
/* 8037DD34 0037A914  98 1F 00 18 */	stb r0, 0x18(r31)
/* 8037DD38 0037A918  98 1F 00 19 */	stb r0, 0x19(r31)
/* 8037DD3C 0037A91C  98 1F 00 1A */	stb r0, 0x1a(r31)
/* 8037DD40 0037A920  98 1F 00 1B */	stb r0, 0x1b(r31)
lbl_8037DD44:
/* 8037DD44 0037A924  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8037DD48 0037A928  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 8037DD4C 0037A92C  38 21 00 30 */	addi r1, r1, 0x30
/* 8037DD50 0037A930  7C 08 03 A6 */	mtlr r0
/* 8037DD54 0037A934  4E 80 00 20 */	blr 

.global func_8037DD58
func_8037DD58:
/* 8037DD58 0037A938  7C 08 02 A6 */	mflr r0
/* 8037DD5C 0037A93C  3C 80 80 40 */	lis r4, lbl_804070B4@ha
/* 8037DD60 0037A940  90 01 00 04 */	stw r0, 4(r1)
/* 8037DD64 0037A944  38 04 70 B4 */	addi r0, r4, lbl_804070B4@l
/* 8037DD68 0037A948  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8037DD6C 0037A94C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8037DD70 0037A950  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8037DD74 0037A954  3B C3 00 00 */	addi r30, r3, 0
/* 8037DD78 0037A958  7C 03 03 78 */	mr r3, r0
/* 8037DD7C 0037A95C  48 00 45 C9 */	bl hsdNew
/* 8037DD80 0037A960  7C 7F 1B 79 */	or. r31, r3, r3
/* 8037DD84 0037A964  40 82 00 14 */	bne lbl_8037DD98
/* 8037DD88 0037A968  38 6D A8 80 */	addi r3, r13, lbl_804D5F20@sda21
/* 8037DD8C 0037A96C  38 80 00 D6 */	li r4, 0xd6
/* 8037DD90 0037A970  38 AD A8 8C */	addi r5, r13, lbl_804D5F2C@sda21
/* 8037DD94 0037A974  48 00 A4 8D */	bl __assert
lbl_8037DD98:
/* 8037DD98 0037A978  28 1F 00 00 */	cmplwi r31, 0
/* 8037DD9C 0037A97C  40 82 00 14 */	bne lbl_8037DDB0
/* 8037DDA0 0037A980  38 6D A8 80 */	addi r3, r13, lbl_804D5F20@sda21
/* 8037DDA4 0037A984  38 80 00 E6 */	li r4, 0xe6
/* 8037DDA8 0037A988  38 AD A8 8C */	addi r5, r13, lbl_804D5F2C@sda21
/* 8037DDAC 0037A98C  48 00 A4 75 */	bl __assert
lbl_8037DDB0:
/* 8037DDB0 0037A990  38 7F 00 00 */	addi r3, r31, 0
/* 8037DDB4 0037A994  38 9E 00 00 */	addi r4, r30, 0
/* 8037DDB8 0037A998  48 00 00 21 */	bl func_8037DDD8
/* 8037DDBC 0037A99C  7F E3 FB 78 */	mr r3, r31
/* 8037DDC0 0037A9A0  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8037DDC4 0037A9A4  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8037DDC8 0037A9A8  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8037DDCC 0037A9AC  38 21 00 20 */	addi r1, r1, 0x20
/* 8037DDD0 0037A9B0  7C 08 03 A6 */	mtlr r0
/* 8037DDD4 0037A9B4  4E 80 00 20 */	blr 

.global func_8037DDD8
func_8037DDD8:
/* 8037DDD8 0037A9B8  7C 08 02 A6 */	mflr r0
/* 8037DDDC 0037A9BC  90 01 00 04 */	stw r0, 4(r1)
/* 8037DDE0 0037A9C0  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 8037DDE4 0037A9C4  93 E1 00 34 */	stw r31, 0x34(r1)
/* 8037DDE8 0037A9C8  7C 7F 1B 79 */	or. r31, r3, r3
/* 8037DDEC 0037A9CC  41 82 00 7C */	beq lbl_8037DE68
/* 8037DDF0 0037A9D0  28 04 00 00 */	cmplwi r4, 0
/* 8037DDF4 0037A9D4  41 82 00 24 */	beq lbl_8037DE18
/* 8037DDF8 0037A9D8  A0 04 00 02 */	lhz r0, 2(r4)
/* 8037DDFC 0037A9DC  38 64 00 04 */	addi r3, r4, 4
/* 8037DE00 0037A9E0  B0 1F 00 0A */	sth r0, 0xa(r31)
/* 8037DE04 0037A9E4  A8 04 00 00 */	lha r0, 0(r4)
/* 8037DE08 0037A9E8  38 9F 00 0C */	addi r4, r31, 0xc
/* 8037DE0C 0037A9EC  B0 1F 00 08 */	sth r0, 8(r31)
/* 8037DE10 0037A9F0  4B FC 43 C1 */	bl PSMTXCopy
/* 8037DE14 0037A9F4  48 00 00 54 */	b lbl_8037DE68
lbl_8037DE18:
/* 8037DE18 0037A9F8  38 61 00 10 */	addi r3, r1, 0x10
/* 8037DE1C 0037A9FC  4B FC 38 F5 */	bl func_80341710
/* 8037DE20 0037AA00  C0 01 00 18 */	lfs f0, 0x18(r1)
/* 8037DE24 0037AA04  38 7F 00 0C */	addi r3, r31, 0xc
/* 8037DE28 0037AA08  FC 00 00 1E */	fctiwz f0, f0
/* 8037DE2C 0037AA0C  D8 01 00 28 */	stfd f0, 0x28(r1)
/* 8037DE30 0037AA10  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8037DE34 0037AA14  B0 1F 00 0A */	sth r0, 0xa(r31)
/* 8037DE38 0037AA18  A0 1F 00 0A */	lhz r0, 0xa(r31)
/* 8037DE3C 0037AA1C  7C 00 0E 70 */	srawi r0, r0, 1
/* 8037DE40 0037AA20  7C 00 01 94 */	addze r0, r0
/* 8037DE44 0037AA24  7C 00 07 34 */	extsh r0, r0
/* 8037DE48 0037AA28  B0 1F 00 08 */	sth r0, 8(r31)
/* 8037DE4C 0037AA2C  4B FC 43 59 */	bl PSMTXIdentity
/* 8037DE50 0037AA30  C0 02 ED 14 */	lfs f0, lbl_804DE6F4@sda21(r2)
/* 8037DE54 0037AA34  D0 1F 00 3C */	stfs f0, 0x3c(r31)
/* 8037DE58 0037AA38  D0 1F 00 40 */	stfs f0, 0x40(r31)
/* 8037DE5C 0037AA3C  D0 1F 00 44 */	stfs f0, 0x44(r31)
/* 8037DE60 0037AA40  C0 02 ED 20 */	lfs f0, lbl_804DE700@sda21(r2)
/* 8037DE64 0037AA44  D0 1F 00 48 */	stfs f0, 0x48(r31)
lbl_8037DE68:
/* 8037DE68 0037AA48  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 8037DE6C 0037AA4C  83 E1 00 34 */	lwz r31, 0x34(r1)
/* 8037DE70 0037AA50  38 21 00 38 */	addi r1, r1, 0x38
/* 8037DE74 0037AA54  7C 08 03 A6 */	mtlr r0
/* 8037DE78 0037AA58  4E 80 00 20 */	blr 

.global func_8037DE7C
func_8037DE7C:
/* 8037DE7C 0037AA5C  7C 08 02 A6 */	mflr r0
/* 8037DE80 0037AA60  90 01 00 04 */	stw r0, 4(r1)
/* 8037DE84 0037AA64  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8037DE88 0037AA68  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8037DE8C 0037AA6C  3B E4 00 00 */	addi r31, r4, 0
/* 8037DE90 0037AA70  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8037DE94 0037AA74  7C 7E 1B 79 */	or. r30, r3, r3
/* 8037DE98 0037AA78  41 82 00 20 */	beq lbl_8037DEB8
/* 8037DE9C 0037AA7C  80 7E 00 1C */	lwz r3, 0x1c(r30)
/* 8037DEA0 0037AA80  28 03 00 00 */	cmplwi r3, 0
/* 8037DEA4 0037AA84  41 82 00 08 */	beq lbl_8037DEAC
/* 8037DEA8 0037AA88  4B FE 66 25 */	bl HSD_AObjRemove
lbl_8037DEAC:
/* 8037DEAC 0037AA8C  7F E3 FB 78 */	mr r3, r31
/* 8037DEB0 0037AA90  4B FE 64 ED */	bl HSD_AObjLoadDesc
/* 8037DEB4 0037AA94  90 7E 00 1C */	stw r3, 0x1c(r30)
lbl_8037DEB8:
/* 8037DEB8 0037AA98  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8037DEBC 0037AA9C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8037DEC0 0037AAA0  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8037DEC4 0037AAA4  38 21 00 18 */	addi r1, r1, 0x18
/* 8037DEC8 0037AAA8  7C 08 03 A6 */	mtlr r0
/* 8037DECC 0037AAAC  4E 80 00 20 */	blr 

.global func_8037DED0
func_8037DED0:
/* 8037DED0 0037AAB0  7C 08 02 A6 */	mflr r0
/* 8037DED4 0037AAB4  38 80 07 FF */	li r4, 0x7ff
/* 8037DED8 0037AAB8  90 01 00 04 */	stw r0, 4(r1)
/* 8037DEDC 0037AABC  94 21 FF F8 */	stwu r1, -8(r1)
/* 8037DEE0 0037AAC0  48 00 00 15 */	bl func_8037DEF4
/* 8037DEE4 0037AAC4  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8037DEE8 0037AAC8  38 21 00 08 */	addi r1, r1, 8
/* 8037DEEC 0037AACC  7C 08 03 A6 */	mtlr r0
/* 8037DEF0 0037AAD0  4E 80 00 20 */	blr 

.global func_8037DEF4
func_8037DEF4:
/* 8037DEF4 0037AAD4  7C 08 02 A6 */	mflr r0
/* 8037DEF8 0037AAD8  28 03 00 00 */	cmplwi r3, 0
/* 8037DEFC 0037AADC  90 01 00 04 */	stw r0, 4(r1)
/* 8037DF00 0037AAE0  94 21 FF F8 */	stwu r1, -8(r1)
/* 8037DF04 0037AAE4  41 82 00 18 */	beq lbl_8037DF1C
/* 8037DF08 0037AAE8  54 80 05 AD */	rlwinm. r0, r4, 0, 0x16, 0x16
/* 8037DF0C 0037AAEC  40 82 00 08 */	bne lbl_8037DF14
/* 8037DF10 0037AAF0  48 00 00 0C */	b lbl_8037DF1C
lbl_8037DF14:
/* 8037DF14 0037AAF4  80 63 00 1C */	lwz r3, 0x1c(r3)
/* 8037DF18 0037AAF8  4B FE 61 F5 */	bl HSD_AObjReqAnim
lbl_8037DF1C:
/* 8037DF1C 0037AAFC  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8037DF20 0037AB00  38 21 00 08 */	addi r1, r1, 8
/* 8037DF24 0037AB04  7C 08 03 A6 */	mtlr r0
/* 8037DF28 0037AB08  4E 80 00 20 */	blr 

.global func_8037DF2C
func_8037DF2C:
/* 8037DF2C 0037AB0C  7C 08 02 A6 */	mflr r0
/* 8037DF30 0037AB10  7C 64 1B 79 */	or. r4, r3, r3
/* 8037DF34 0037AB14  90 01 00 04 */	stw r0, 4(r1)
/* 8037DF38 0037AB18  94 21 FF F8 */	stwu r1, -8(r1)
/* 8037DF3C 0037AB1C  41 82 00 14 */	beq lbl_8037DF50
/* 8037DF40 0037AB20  3C A0 80 38 */	lis r5, lbl_8037DF60@ha
/* 8037DF44 0037AB24  80 64 00 1C */	lwz r3, 0x1c(r4)
/* 8037DF48 0037AB28  38 A5 DF 60 */	addi r5, r5, lbl_8037DF60@l
/* 8037DF4C 0037AB2C  4B FE 62 45 */	bl HSD_AObjInterpretAnim
lbl_8037DF50:
/* 8037DF50 0037AB30  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8037DF54 0037AB34  38 21 00 08 */	addi r1, r1, 8
/* 8037DF58 0037AB38  7C 08 03 A6 */	mtlr r0
/* 8037DF5C 0037AB3C  4E 80 00 20 */	blr 
lbl_8037DF60:
/* 8037DF60 0037AB40  28 03 00 00 */	cmplwi r3, 0
/* 8037DF64 0037AB44  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8037DF68 0037AB48  41 82 00 DC */	beq lbl_8037E044
/* 8037DF6C 0037AB4C  28 04 00 14 */	cmplwi r4, 0x14
/* 8037DF70 0037AB50  41 81 00 D4 */	bgt lbl_8037E044
/* 8037DF74 0037AB54  3C C0 80 40 */	lis r6, jtbl_80407110@ha
/* 8037DF78 0037AB58  38 C6 71 10 */	addi r6, r6, jtbl_80407110@l
/* 8037DF7C 0037AB5C  54 80 10 3A */	slwi r0, r4, 2
/* 8037DF80 0037AB60  7C 06 00 2E */	lwzx r0, r6, r0
/* 8037DF84 0037AB64  7C 09 03 A6 */	mtctr r0
/* 8037DF88 0037AB68  4E 80 04 20 */	bctr 
.global lbl_8037DF8C
lbl_8037DF8C:
/* 8037DF8C 0037AB6C  C0 05 00 00 */	lfs f0, 0(r5)
/* 8037DF90 0037AB70  D0 03 00 10 */	stfs f0, 0x10(r3)
/* 8037DF94 0037AB74  48 00 00 B0 */	b lbl_8037E044
.global lbl_8037DF98
lbl_8037DF98:
/* 8037DF98 0037AB78  C0 05 00 00 */	lfs f0, 0(r5)
/* 8037DF9C 0037AB7C  D0 03 00 14 */	stfs f0, 0x14(r3)
/* 8037DFA0 0037AB80  48 00 00 A4 */	b lbl_8037E044
.global lbl_8037DFA4
lbl_8037DFA4:
/* 8037DFA4 0037AB84  C0 22 ED 30 */	lfs f1, lbl_804DE710@sda21(r2)
/* 8037DFA8 0037AB88  C0 05 00 00 */	lfs f0, 0(r5)
/* 8037DFAC 0037AB8C  EC 01 00 32 */	fmuls f0, f1, f0
/* 8037DFB0 0037AB90  FC 00 00 1E */	fctiwz f0, f0
/* 8037DFB4 0037AB94  D8 01 00 18 */	stfd f0, 0x18(r1)
/* 8037DFB8 0037AB98  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8037DFBC 0037AB9C  98 03 00 18 */	stb r0, 0x18(r3)
/* 8037DFC0 0037ABA0  48 00 00 84 */	b lbl_8037E044
.global lbl_8037DFC4
lbl_8037DFC4:
/* 8037DFC4 0037ABA4  C0 22 ED 30 */	lfs f1, lbl_804DE710@sda21(r2)
/* 8037DFC8 0037ABA8  C0 05 00 00 */	lfs f0, 0(r5)
/* 8037DFCC 0037ABAC  EC 01 00 32 */	fmuls f0, f1, f0
/* 8037DFD0 0037ABB0  FC 00 00 1E */	fctiwz f0, f0
/* 8037DFD4 0037ABB4  D8 01 00 18 */	stfd f0, 0x18(r1)
/* 8037DFD8 0037ABB8  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8037DFDC 0037ABBC  98 03 00 19 */	stb r0, 0x19(r3)
/* 8037DFE0 0037ABC0  48 00 00 64 */	b lbl_8037E044
.global lbl_8037DFE4
lbl_8037DFE4:
/* 8037DFE4 0037ABC4  C0 22 ED 30 */	lfs f1, lbl_804DE710@sda21(r2)
/* 8037DFE8 0037ABC8  C0 05 00 00 */	lfs f0, 0(r5)
/* 8037DFEC 0037ABCC  EC 01 00 32 */	fmuls f0, f1, f0
/* 8037DFF0 0037ABD0  FC 00 00 1E */	fctiwz f0, f0
/* 8037DFF4 0037ABD4  D8 01 00 18 */	stfd f0, 0x18(r1)
/* 8037DFF8 0037ABD8  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8037DFFC 0037ABDC  98 03 00 1A */	stb r0, 0x1a(r3)
/* 8037E000 0037ABE0  48 00 00 44 */	b lbl_8037E044
.global lbl_8037E004
lbl_8037E004:
/* 8037E004 0037ABE4  C0 22 ED 30 */	lfs f1, lbl_804DE710@sda21(r2)
/* 8037E008 0037ABE8  C0 05 00 00 */	lfs f0, 0(r5)
/* 8037E00C 0037ABEC  EC 01 00 32 */	fmuls f0, f1, f0
/* 8037E010 0037ABF0  FC 00 00 1E */	fctiwz f0, f0
/* 8037E014 0037ABF4  D8 01 00 18 */	stfd f0, 0x18(r1)
/* 8037E018 0037ABF8  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8037E01C 0037ABFC  98 03 00 1B */	stb r0, 0x1b(r3)
/* 8037E020 0037AC00  48 00 00 24 */	b lbl_8037E044
.global lbl_8037E024
lbl_8037E024:
/* 8037E024 0037AC04  80 63 00 0C */	lwz r3, 0xc(r3)
/* 8037E028 0037AC08  28 03 00 00 */	cmplwi r3, 0
/* 8037E02C 0037AC0C  41 82 00 18 */	beq lbl_8037E044
/* 8037E030 0037AC10  C0 05 00 00 */	lfs f0, 0(r5)
/* 8037E034 0037AC14  FC 00 00 1E */	fctiwz f0, f0
/* 8037E038 0037AC18  D8 01 00 18 */	stfd f0, 0x18(r1)
/* 8037E03C 0037AC1C  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8037E040 0037AC20  B0 03 00 08 */	sth r0, 8(r3)
.global lbl_8037E044
lbl_8037E044:
/* 8037E044 0037AC24  38 21 00 20 */	addi r1, r1, 0x20
/* 8037E048 0037AC28  4E 80 00 20 */	blr 
lbl_8037E04C:
/* 8037E04C 0037AC2C  7C 08 02 A6 */	mflr r0
/* 8037E050 0037AC30  90 01 00 04 */	stw r0, 4(r1)
/* 8037E054 0037AC34  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8037E058 0037AC38  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8037E05C 0037AC3C  7C 7F 1B 78 */	mr r31, r3
/* 8037E060 0037AC40  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8037E064 0037AC44  83 C3 00 0C */	lwz r30, 0xc(r3)
/* 8037E068 0037AC48  28 1E 00 00 */	cmplwi r30, 0
/* 8037E06C 0037AC4C  41 82 00 78 */	beq lbl_8037E0E4
/* 8037E070 0037AC50  3C 60 00 01 */	lis r3, 0x0000FFFF@ha
/* 8037E074 0037AC54  A0 9E 00 04 */	lhz r4, 4(r30)
/* 8037E078 0037AC58  38 03 FF FF */	addi r0, r3, 0x0000FFFF@l
/* 8037E07C 0037AC5C  54 00 04 3E */	clrlwi r0, r0, 0x10
/* 8037E080 0037AC60  7C 04 00 50 */	subf r0, r4, r0
/* 8037E084 0037AC64  7C 00 00 34 */	cntlzw r0, r0
/* 8037E088 0037AC68  54 00 D9 7F */	rlwinm. r0, r0, 0x1b, 5, 0x1f
/* 8037E08C 0037AC6C  38 BE 00 04 */	addi r5, r30, 4
/* 8037E090 0037AC70  41 82 00 08 */	beq lbl_8037E098
/* 8037E094 0037AC74  48 00 00 18 */	b lbl_8037E0AC
lbl_8037E098:
/* 8037E098 0037AC78  38 64 FF FF */	addi r3, r4, -1
/* 8037E09C 0037AC7C  7C 04 00 D0 */	neg r0, r4
/* 8037E0A0 0037AC80  B0 65 00 00 */	sth r3, 0(r5)
/* 8037E0A4 0037AC84  7C 00 00 34 */	cntlzw r0, r0
/* 8037E0A8 0037AC88  54 00 D9 7E */	srwi r0, r0, 5
lbl_8037E0AC:
/* 8037E0AC 0037AC8C  2C 00 00 00 */	cmpwi r0, 0
/* 8037E0B0 0037AC90  41 82 00 34 */	beq lbl_8037E0E4
/* 8037E0B4 0037AC94  28 1E 00 00 */	cmplwi r30, 0
/* 8037E0B8 0037AC98  41 82 00 2C */	beq lbl_8037E0E4
/* 8037E0BC 0037AC9C  80 9E 00 00 */	lwz r4, 0(r30)
/* 8037E0C0 0037ACA0  7F C3 F3 78 */	mr r3, r30
/* 8037E0C4 0037ACA4  81 84 00 30 */	lwz r12, 0x30(r4)
/* 8037E0C8 0037ACA8  7D 88 03 A6 */	mtlr r12
/* 8037E0CC 0037ACAC  4E 80 00 21 */	blrl 
/* 8037E0D0 0037ACB0  80 9E 00 00 */	lwz r4, 0(r30)
/* 8037E0D4 0037ACB4  7F C3 F3 78 */	mr r3, r30
/* 8037E0D8 0037ACB8  81 84 00 34 */	lwz r12, 0x34(r4)
/* 8037E0DC 0037ACBC  7D 88 03 A6 */	mtlr r12
/* 8037E0E0 0037ACC0  4E 80 00 21 */	blrl 
lbl_8037E0E4:
/* 8037E0E4 0037ACC4  80 7F 00 1C */	lwz r3, 0x1c(r31)
/* 8037E0E8 0037ACC8  4B FE 63 E5 */	bl HSD_AObjRemove
/* 8037E0EC 0037ACCC  3C 60 80 40 */	lis r3, lbl_80407078@ha
/* 8037E0F0 0037ACD0  38 63 70 78 */	addi r3, r3, lbl_80407078@l
/* 8037E0F4 0037ACD4  80 83 00 14 */	lwz r4, 0x14(r3)
/* 8037E0F8 0037ACD8  7F E3 FB 78 */	mr r3, r31
/* 8037E0FC 0037ACDC  81 84 00 30 */	lwz r12, 0x30(r4)
/* 8037E100 0037ACE0  7D 88 03 A6 */	mtlr r12
/* 8037E104 0037ACE4  4E 80 00 21 */	blrl 
/* 8037E108 0037ACE8  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8037E10C 0037ACEC  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8037E110 0037ACF0  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8037E114 0037ACF4  38 21 00 18 */	addi r1, r1, 0x18
/* 8037E118 0037ACF8  7C 08 03 A6 */	mtlr r0
/* 8037E11C 0037ACFC  4E 80 00 20 */	blr 

.global func_8037E120
func_8037E120:
/* 8037E120 0037AD00  7C 08 02 A6 */	mflr r0
/* 8037E124 0037AD04  3C 60 80 40 */	lis r3, lbl_80407078@ha
/* 8037E128 0037AD08  90 01 00 04 */	stw r0, 4(r1)
/* 8037E12C 0037AD0C  38 CD A8 90 */	addi r6, r13, lbl_804D5F30@sda21
/* 8037E130 0037AD10  38 E0 00 3C */	li r7, 0x3c
/* 8037E134 0037AD14  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8037E138 0037AD18  39 00 00 20 */	li r8, 0x20
/* 8037E13C 0037AD1C  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8037E140 0037AD20  3B E3 70 78 */	addi r31, r3, lbl_80407078@l
/* 8037E144 0037AD24  3C 60 80 40 */	lis r3, hsdObj@ha
/* 8037E148 0037AD28  38 83 72 A8 */	addi r4, r3, hsdObj@l
/* 8037E14C 0037AD2C  38 7F 00 00 */	addi r3, r31, 0
/* 8037E150 0037AD30  38 BF 00 EC */	addi r5, r31, 0xec
/* 8037E154 0037AD34  48 00 3A C5 */	bl hsdInitClassInfo
/* 8037E158 0037AD38  3C 60 80 38 */	lis r3, lbl_8037E04C@ha
/* 8037E15C 0037AD3C  38 03 E0 4C */	addi r0, r3, lbl_8037E04C@l
/* 8037E160 0037AD40  90 1F 00 30 */	stw r0, 0x30(r31)
/* 8037E164 0037AD44  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8037E168 0037AD48  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8037E16C 0037AD4C  38 21 00 10 */	addi r1, r1, 0x10
/* 8037E170 0037AD50  7C 08 03 A6 */	mtlr r0
/* 8037E174 0037AD54  4E 80 00 20 */	blr 

.global func_8037E178
func_8037E178:
/* 8037E178 0037AD58  7C 08 02 A6 */	mflr r0
/* 8037E17C 0037AD5C  3C 60 80 40 */	lis r3, lbl_80407078@ha
/* 8037E180 0037AD60  90 01 00 04 */	stw r0, 4(r1)
/* 8037E184 0037AD64  38 C3 70 78 */	addi r6, r3, lbl_80407078@l
/* 8037E188 0037AD68  3C 60 80 40 */	lis r3, hsdObj@ha
/* 8037E18C 0037AD6C  94 21 FF F8 */	stwu r1, -8(r1)
/* 8037E190 0037AD70  38 83 72 A8 */	addi r4, r3, hsdObj@l
/* 8037E194 0037AD74  38 66 00 3C */	addi r3, r6, 0x3c
/* 8037E198 0037AD78  38 A6 00 EC */	addi r5, r6, 0xec
/* 8037E19C 0037AD7C  38 C6 01 04 */	addi r6, r6, 0x104
/* 8037E1A0 0037AD80  38 E0 00 3C */	li r7, 0x3c
/* 8037E1A4 0037AD84  39 00 00 50 */	li r8, 0x50
/* 8037E1A8 0037AD88  48 00 3A 71 */	bl hsdInitClassInfo
/* 8037E1AC 0037AD8C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8037E1B0 0037AD90  38 21 00 08 */	addi r1, r1, 8
/* 8037E1B4 0037AD94  7C 08 03 A6 */	mtlr r0
/* 8037E1B8 0037AD98  4E 80 00 20 */	blr 


.section .rodata
    .balign 8
.global lbl_803B95A8
lbl_803B95A8:
    .4byte 0x00000000
    .4byte 0x00000000
    .4byte 0x00000000
    .4byte 0x00000000
    .4byte 0x00000000
    .4byte 0x00000000
    .4byte 0x00000000
    .4byte 0x00000000
    .4byte 0x00000000
    .4byte 0x00000000
    .4byte 0x00000000
    .4byte 0x00000000
    .4byte 0x00000000
    .4byte 0x00000000
    .4byte 0x00000000
    .4byte 0x00000000


.section .data
    .balign 8
.global lbl_80407078
lbl_80407078:
    .4byte func_8037E120
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
.global lbl_804070B4
lbl_804070B4:
    .4byte func_8037E178
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
.global lbl_804070F0
lbl_804070F0:
    .asciz "You must specify CObj first.\n"
    .balign 4
.global jtbl_80407110
jtbl_80407110:
	.4byte lbl_8037E044
	.4byte lbl_8037DF8C
	.4byte lbl_8037DF98
	.4byte lbl_8037E044
	.4byte lbl_8037E044
	.4byte lbl_8037DFA4
	.4byte lbl_8037DFC4
	.4byte lbl_8037DFE4
	.4byte lbl_8037E004
	.4byte lbl_8037E044
	.4byte lbl_8037E044
	.4byte lbl_8037E044
	.4byte lbl_8037E044
	.4byte lbl_8037E044
	.4byte lbl_8037E044
	.4byte lbl_8037E044
	.4byte lbl_8037E044
	.4byte lbl_8037E044
	.4byte lbl_8037E044
	.4byte lbl_8037E044
	.4byte lbl_8037E024
    .4byte 0x73797364
    .4byte 0x6F6C7068
    .4byte 0x696E5F62
    .4byte 0x6173655F
    .4byte 0x6C696272
    .4byte 0x61727900
    .4byte 0x6873645F
    .4byte 0x666F6761
    .4byte 0x646A0000


.section .sdata
    .balign 8
.global lbl_804D5F20
lbl_804D5F20:
    .asciz "fog.c"
    .balign 4
.global lbl_804D5F28
lbl_804D5F28:
    .asciz "fog"
    .balign 4
.global lbl_804D5F2C
lbl_804D5F2C:
    .asciz "adj"
    .balign 4
.global lbl_804D5F30
lbl_804D5F30:
    .asciz "hsd_fog"
    .balign 4


.section .sdata2
    .balign 8
.global lbl_804DE6F0
lbl_804DE6F0:
	.4byte 0x00000000
.global lbl_804DE6F4
lbl_804DE6F4:
	.4byte 0x00000000
.global lbl_804DE6F8
lbl_804DE6F8:
	.4byte 0x44200000
.global lbl_804DE6FC
lbl_804DE6FC:
	.4byte 0xBF800000
.global lbl_804DE700
lbl_804DE700:
	.4byte 0x3F800000
	.4byte 0x00000000
.global lbl_804DE708
lbl_804DE708:
	.4byte 0x43300000
	.4byte 0x80000000
.global lbl_804DE710
lbl_804DE710:
	.4byte 0x437F0000
	.4byte 0x00000000
