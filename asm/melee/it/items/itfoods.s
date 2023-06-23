.include "macros.inc"

.section .text

.global it_8028F9D8
it_8028F9D8:
/* 8028F9D8 0028C5B8  7C 08 02 A6 */	mflr r0
/* 8028F9DC 0028C5BC  90 01 00 04 */	stw r0, 4(r1)
/* 8028F9E0 0028C5C0  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8028F9E4 0028C5C4  93 E1 00 24 */	stw r31, 0x24(r1)
/* 8028F9E8 0028C5C8  93 C1 00 20 */	stw r30, 0x20(r1)
/* 8028F9EC 0028C5CC  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 8028F9F0 0028C5D0  C0 04 00 00 */	lfs f0, 0(r4)
/* 8028F9F4 0028C5D4  80 BE 00 C4 */	lwz r5, 0xc4(r30)
/* 8028F9F8 0028C5D8  80 1E 0D D4 */	lwz r0, 0xdd4(r30)
/* 8028F9FC 0028C5DC  80 C5 00 04 */	lwz r6, 4(r5)
/* 8028FA00 0028C5E0  54 00 20 36 */	slwi r0, r0, 4
/* 8028FA04 0028C5E4  7C A6 02 14 */	add r5, r6, r0
/* 8028FA08 0028C5E8  C0 45 00 0C */	lfs f2, 0xc(r5)
/* 8028FA0C 0028C5EC  EC 01 00 BA */	fmadds f0, f1, f2, f0
/* 8028FA10 0028C5F0  D0 1E 00 4C */	stfs f0, 0x4c(r30)
/* 8028FA14 0028C5F4  80 1E 0D D4 */	lwz r0, 0xdd4(r30)
/* 8028FA18 0028C5F8  C0 04 00 04 */	lfs f0, 4(r4)
/* 8028FA1C 0028C5FC  54 00 20 36 */	slwi r0, r0, 4
/* 8028FA20 0028C600  7C A6 02 14 */	add r5, r6, r0
/* 8028FA24 0028C604  C0 25 00 10 */	lfs f1, 0x10(r5)
/* 8028FA28 0028C608  EC 01 00 2A */	fadds f0, f1, f0
/* 8028FA2C 0028C60C  D0 1E 00 50 */	stfs f0, 0x50(r30)
/* 8028FA30 0028C610  C0 04 00 08 */	lfs f0, 8(r4)
/* 8028FA34 0028C614  D0 1E 00 54 */	stfs f0, 0x54(r30)
/* 8028FA38 0028C618  83 E3 00 28 */	lwz r31, 0x28(r3)
/* 8028FA3C 0028C61C  28 1F 00 00 */	cmplwi r31, 0
/* 8028FA40 0028C620  40 82 00 14 */	bne .L_8028FA54
/* 8028FA44 0028C624  38 6D 9C 00 */	addi r3, r13, it_804D52A0@sda21
/* 8028FA48 0028C628  38 80 03 94 */	li r4, 0x394
/* 8028FA4C 0028C62C  38 AD 9C 08 */	addi r5, r13, it_804D52A8@sda21
/* 8028FA50 0028C630  48 0F 87 D1 */	bl __assert
.L_8028FA54:
/* 8028FA54 0028C634  34 1E 00 4C */	addic. r0, r30, 0x4c
/* 8028FA58 0028C638  40 82 00 18 */	bne .L_8028FA70
/* 8028FA5C 0028C63C  3C 60 80 3F */	lis r3, it_803F5DF0@ha
/* 8028FA60 0028C640  38 A3 5D F0 */	addi r5, r3, it_803F5DF0@l
/* 8028FA64 0028C644  38 6D 9C 00 */	addi r3, r13, it_804D52A0@sda21
/* 8028FA68 0028C648  38 80 03 95 */	li r4, 0x395
/* 8028FA6C 0028C64C  48 0F 87 B5 */	bl __assert
.L_8028FA70:
/* 8028FA70 0028C650  80 7E 00 4C */	lwz r3, 0x4c(r30)
/* 8028FA74 0028C654  80 1E 00 50 */	lwz r0, 0x50(r30)
/* 8028FA78 0028C658  90 7F 00 38 */	stw r3, 0x38(r31)
/* 8028FA7C 0028C65C  90 1F 00 3C */	stw r0, 0x3c(r31)
/* 8028FA80 0028C660  80 1E 00 54 */	lwz r0, 0x54(r30)
/* 8028FA84 0028C664  90 1F 00 40 */	stw r0, 0x40(r31)
/* 8028FA88 0028C668  80 1F 00 14 */	lwz r0, 0x14(r31)
/* 8028FA8C 0028C66C  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 8028FA90 0028C670  40 82 00 4C */	bne .L_8028FADC
/* 8028FA94 0028C674  28 1F 00 00 */	cmplwi r31, 0
/* 8028FA98 0028C678  41 82 00 44 */	beq .L_8028FADC
/* 8028FA9C 0028C67C  40 82 00 14 */	bne .L_8028FAB0
/* 8028FAA0 0028C680  38 6D 9C 00 */	addi r3, r13, it_804D52A0@sda21
/* 8028FAA4 0028C684  38 80 02 34 */	li r4, 0x234
/* 8028FAA8 0028C688  38 AD 9C 08 */	addi r5, r13, it_804D52A8@sda21
/* 8028FAAC 0028C68C  48 0F 87 75 */	bl __assert
.L_8028FAB0:
/* 8028FAB0 0028C690  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 8028FAB4 0028C694  38 60 00 00 */	li r3, 0
/* 8028FAB8 0028C698  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 8028FABC 0028C69C  40 82 00 10 */	bne .L_8028FACC
/* 8028FAC0 0028C6A0  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 8028FAC4 0028C6A4  41 82 00 08 */	beq .L_8028FACC
/* 8028FAC8 0028C6A8  38 60 00 01 */	li r3, 1
.L_8028FACC:
/* 8028FACC 0028C6AC  2C 03 00 00 */	cmpwi r3, 0
/* 8028FAD0 0028C6B0  40 82 00 0C */	bne .L_8028FADC
/* 8028FAD4 0028C6B4  7F E3 FB 78 */	mr r3, r31
/* 8028FAD8 0028C6B8  48 0E 38 11 */	bl HSD_JObjSetMtxDirtySub
.L_8028FADC:
/* 8028FADC 0028C6BC  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8028FAE0 0028C6C0  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 8028FAE4 0028C6C4  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 8028FAE8 0028C6C8  38 21 00 28 */	addi r1, r1, 0x28
/* 8028FAEC 0028C6CC  7C 08 03 A6 */	mtlr r0
/* 8028FAF0 0028C6D0  4E 80 00 20 */	blr

.global it_8028FAF4
it_8028FAF4:
/* 8028FAF4 0028C6D4  7C 08 02 A6 */	mflr r0
/* 8028FAF8 0028C6D8  90 01 00 04 */	stw r0, 4(r1)
/* 8028FAFC 0028C6DC  94 21 FF 98 */	stwu r1, -0x68(r1)
/* 8028FB00 0028C6E0  93 E1 00 64 */	stw r31, 0x64(r1)
/* 8028FB04 0028C6E4  3B E4 00 00 */	addi r31, r4, 0
/* 8028FB08 0028C6E8  93 C1 00 60 */	stw r30, 0x60(r1)
/* 8028FB0C 0028C6EC  3B C3 00 00 */	addi r30, r3, 0
/* 8028FB10 0028C6F0  38 60 00 12 */	li r3, 0x12
/* 8028FB14 0028C6F4  4B FD D8 11 */	bl it_8026D324
/* 8028FB18 0028C6F8  2C 03 00 00 */	cmpwi r3, 0
/* 8028FB1C 0028C6FC  40 82 00 0C */	bne .L_8028FB28
/* 8028FB20 0028C700  38 60 00 00 */	li r3, 0
/* 8028FB24 0028C704  48 00 00 A8 */	b .L_8028FBCC
.L_8028FB28:
/* 8028FB28 0028C708  38 00 00 12 */	li r0, 0x12
/* 8028FB2C 0028C70C  90 01 00 18 */	stw r0, 0x18(r1)
/* 8028FB30 0028C710  28 1E 00 00 */	cmplwi r30, 0
/* 8028FB34 0028C714  80 7F 00 00 */	lwz r3, 0(r31)
/* 8028FB38 0028C718  80 1F 00 04 */	lwz r0, 4(r31)
/* 8028FB3C 0028C71C  90 61 00 30 */	stw r3, 0x30(r1)
/* 8028FB40 0028C720  90 01 00 34 */	stw r0, 0x34(r1)
/* 8028FB44 0028C724  80 1F 00 08 */	lwz r0, 8(r31)
/* 8028FB48 0028C728  90 01 00 38 */	stw r0, 0x38(r1)
/* 8028FB4C 0028C72C  41 82 00 14 */	beq .L_8028FB60
/* 8028FB50 0028C730  38 7E 00 00 */	addi r3, r30, 0
/* 8028FB54 0028C734  38 81 00 24 */	addi r4, r1, 0x24
/* 8028FB58 0028C738  4B FD C0 11 */	bl it_8026BB68
/* 8028FB5C 0028C73C  48 00 00 1C */	b .L_8028FB78
.L_8028FB60:
/* 8028FB60 0028C740  80 61 00 30 */	lwz r3, 0x30(r1)
/* 8028FB64 0028C744  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8028FB68 0028C748  90 61 00 24 */	stw r3, 0x24(r1)
/* 8028FB6C 0028C74C  90 01 00 28 */	stw r0, 0x28(r1)
/* 8028FB70 0028C750  80 01 00 38 */	lwz r0, 0x38(r1)
/* 8028FB74 0028C754  90 01 00 2C */	stw r0, 0x2c(r1)
.L_8028FB78:
/* 8028FB78 0028C758  C0 22 D0 B0 */	lfs f1, it_804DCA90@sda21(r2)
/* 8028FB7C 0028C75C  38 A0 00 00 */	li r5, 0
/* 8028FB80 0028C760  C0 02 D0 B4 */	lfs f0, it_804DCA94@sda21(r2)
/* 8028FB84 0028C764  38 80 00 01 */	li r4, 1
/* 8028FB88 0028C768  D0 21 00 48 */	stfs f1, 0x48(r1)
/* 8028FB8C 0028C76C  38 61 00 10 */	addi r3, r1, 0x10
/* 8028FB90 0028C770  D0 01 00 44 */	stfs f0, 0x44(r1)
/* 8028FB94 0028C774  D0 01 00 40 */	stfs f0, 0x40(r1)
/* 8028FB98 0028C778  D0 01 00 3C */	stfs f0, 0x3c(r1)
/* 8028FB9C 0028C77C  B0 A1 00 4C */	sth r5, 0x4c(r1)
/* 8028FBA0 0028C780  90 A1 00 10 */	stw r5, 0x10(r1)
/* 8028FBA4 0028C784  90 A1 00 14 */	stw r5, 0x14(r1)
/* 8028FBA8 0028C788  88 01 00 54 */	lbz r0, 0x54(r1)
/* 8028FBAC 0028C78C  50 80 3E 30 */	rlwimi r0, r4, 7, 0x18, 0x18
/* 8028FBB0 0028C790  98 01 00 54 */	stb r0, 0x54(r1)
/* 8028FBB4 0028C794  90 A1 00 50 */	stw r5, 0x50(r1)
/* 8028FBB8 0028C798  4B FD 8F 61 */	bl Item_80268B18
/* 8028FBBC 0028C79C  7C 7F 1B 79 */	or. r31, r3, r3
/* 8028FBC0 0028C7A0  41 82 00 08 */	beq .L_8028FBC8
/* 8028FBC4 0028C7A4  4B FE 53 15 */	bl it_80274ED8
.L_8028FBC8:
/* 8028FBC8 0028C7A8  7F E3 FB 78 */	mr r3, r31
.L_8028FBCC:
/* 8028FBCC 0028C7AC  80 01 00 6C */	lwz r0, 0x6c(r1)
/* 8028FBD0 0028C7B0  83 E1 00 64 */	lwz r31, 0x64(r1)
/* 8028FBD4 0028C7B4  83 C1 00 60 */	lwz r30, 0x60(r1)
/* 8028FBD8 0028C7B8  38 21 00 68 */	addi r1, r1, 0x68
/* 8028FBDC 0028C7BC  7C 08 03 A6 */	mtlr r0
/* 8028FBE0 0028C7C0  4E 80 00 20 */	blr

.global it_8028FBE4
it_8028FBE4:
/* 8028FBE4 0028C7C4  7C 08 02 A6 */	mflr r0
/* 8028FBE8 0028C7C8  90 01 00 04 */	stw r0, 4(r1)
/* 8028FBEC 0028C7CC  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8028FBF0 0028C7D0  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 8028FBF4 0028C7D4  93 C1 00 28 */	stw r30, 0x28(r1)
/* 8028FBF8 0028C7D8  93 A1 00 24 */	stw r29, 0x24(r1)
/* 8028FBFC 0028C7DC  7C 7D 1B 78 */	mr r29, r3
/* 8028FC00 0028C7E0  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 8028FC04 0028C7E4  80 7E 00 C4 */	lwz r3, 0xc4(r30)
/* 8028FC08 0028C7E8  83 E3 00 04 */	lwz r31, 4(r3)
/* 8028FC0C 0028C7EC  80 7F 00 00 */	lwz r3, 0(r31)
/* 8028FC10 0028C7F0  48 0F 09 71 */	bl HSD_Randi
/* 8028FC14 0028C7F4  38 A3 00 00 */	addi r5, r3, 0
/* 8028FC18 0028C7F8  54 60 20 36 */	slwi r0, r3, 4
/* 8028FC1C 0028C7FC  7C 9F 02 14 */	add r4, r31, r0
/* 8028FC20 0028C800  80 04 00 08 */	lwz r0, 8(r4)
/* 8028FC24 0028C804  7F A3 EB 78 */	mr r3, r29
/* 8028FC28 0028C808  90 1E 0D D8 */	stw r0, 0xdd8(r30)
/* 8028FC2C 0028C80C  90 BE 0D D4 */	stw r5, 0xdd4(r30)
/* 8028FC30 0028C810  80 84 00 04 */	lwz r4, 4(r4)
/* 8028FC34 0028C814  4B FE 36 E5 */	bl it_80273318
/* 8028FC38 0028C818  7F A3 EB 78 */	mr r3, r29
/* 8028FC3C 0028C81C  48 00 00 21 */	bl it_8028FC5C
/* 8028FC40 0028C820  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8028FC44 0028C824  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 8028FC48 0028C828  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 8028FC4C 0028C82C  83 A1 00 24 */	lwz r29, 0x24(r1)
/* 8028FC50 0028C830  38 21 00 30 */	addi r1, r1, 0x30
/* 8028FC54 0028C834  7C 08 03 A6 */	mtlr r0
/* 8028FC58 0028C838  4E 80 00 20 */	blr

.global it_8028FC5C
it_8028FC5C:
/* 8028FC5C 0028C83C  7C 08 02 A6 */	mflr r0
/* 8028FC60 0028C840  38 80 00 00 */	li r4, 0
/* 8028FC64 0028C844  90 01 00 04 */	stw r0, 4(r1)
/* 8028FC68 0028C848  38 A0 00 02 */	li r5, 2
/* 8028FC6C 0028C84C  94 21 FF F8 */	stwu r1, -8(r1)
/* 8028FC70 0028C850  4B FD 91 ED */	bl Item_80268E5C
/* 8028FC74 0028C854  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8028FC78 0028C858  38 21 00 08 */	addi r1, r1, 8
/* 8028FC7C 0028C85C  7C 08 03 A6 */	mtlr r0
/* 8028FC80 0028C860  4E 80 00 20 */	blr

.global it_8028FC84
it_8028FC84:
/* 8028FC84 0028C864  38 60 00 00 */	li r3, 0
/* 8028FC88 0028C868  4E 80 00 20 */	blr

.global it_8028FC8C
it_8028FC8C:
/* 8028FC8C 0028C86C  7C 08 02 A6 */	mflr r0
/* 8028FC90 0028C870  90 01 00 04 */	stw r0, 4(r1)
/* 8028FC94 0028C874  94 21 FF F8 */	stwu r1, -8(r1)
/* 8028FC98 0028C878  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 8028FC9C 0028C87C  80 84 00 CC */	lwz r4, 0xcc(r4)
/* 8028FCA0 0028C880  C0 24 00 10 */	lfs f1, 0x10(r4)
/* 8028FCA4 0028C884  C0 44 00 14 */	lfs f2, 0x14(r4)
/* 8028FCA8 0028C888  4B FE 2B B9 */	bl it_80272860
/* 8028FCAC 0028C88C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8028FCB0 0028C890  38 21 00 08 */	addi r1, r1, 8
/* 8028FCB4 0028C894  7C 08 03 A6 */	mtlr r0
/* 8028FCB8 0028C898  4E 80 00 20 */	blr

.global it_8028FCBC
it_8028FCBC:
/* 8028FCBC 0028C89C  7C 08 02 A6 */	mflr r0
/* 8028FCC0 0028C8A0  3C 80 80 29 */	lis r4, it_8028FCE8@ha
/* 8028FCC4 0028C8A4  90 01 00 04 */	stw r0, 4(r1)
/* 8028FCC8 0028C8A8  38 84 FC E8 */	addi r4, r4, it_8028FCE8@l
/* 8028FCCC 0028C8AC  94 21 FF F8 */	stwu r1, -8(r1)
/* 8028FCD0 0028C8B0  4B FD E7 45 */	bl it_8026E414
/* 8028FCD4 0028C8B4  38 60 00 00 */	li r3, 0
/* 8028FCD8 0028C8B8  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8028FCDC 0028C8BC  38 21 00 08 */	addi r1, r1, 8
/* 8028FCE0 0028C8C0  7C 08 03 A6 */	mtlr r0
/* 8028FCE4 0028C8C4  4E 80 00 20 */	blr

.global it_8028FCE8
it_8028FCE8:
/* 8028FCE8 0028C8C8  7C 08 02 A6 */	mflr r0
/* 8028FCEC 0028C8CC  38 80 01 07 */	li r4, 0x107
/* 8028FCF0 0028C8D0  90 01 00 04 */	stw r0, 4(r1)
/* 8028FCF4 0028C8D4  38 A0 00 7F */	li r5, 0x7f
/* 8028FCF8 0028C8D8  38 C0 00 40 */	li r6, 0x40
/* 8028FCFC 0028C8DC  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8028FD00 0028C8E0  93 E1 00 24 */	stw r31, 0x24(r1)
/* 8028FD04 0028C8E4  7C 7F 1B 78 */	mr r31, r3
/* 8028FD08 0028C8E8  C0 02 D0 B4 */	lfs f0, it_804DCA94@sda21(r2)
/* 8028FD0C 0028C8EC  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8028FD10 0028C8F0  D0 03 00 48 */	stfs f0, 0x48(r3)
/* 8028FD14 0028C8F4  D0 03 00 44 */	stfs f0, 0x44(r3)
/* 8028FD18 0028C8F8  D0 03 00 40 */	stfs f0, 0x40(r3)
/* 8028FD1C 0028C8FC  4B FD B1 69 */	bl Item_8026AE84
/* 8028FD20 0028C900  38 7F 00 00 */	addi r3, r31, 0
/* 8028FD24 0028C904  38 80 00 01 */	li r4, 1
/* 8028FD28 0028C908  38 A0 00 02 */	li r5, 2
/* 8028FD2C 0028C90C  4B FD 91 31 */	bl Item_80268E5C
/* 8028FD30 0028C910  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8028FD34 0028C914  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 8028FD38 0028C918  38 21 00 28 */	addi r1, r1, 0x28
/* 8028FD3C 0028C91C  7C 08 03 A6 */	mtlr r0
/* 8028FD40 0028C920  4E 80 00 20 */	blr

.global it_8028FD44
it_8028FD44:
/* 8028FD44 0028C924  38 60 00 00 */	li r3, 0
/* 8028FD48 0028C928  4E 80 00 20 */	blr

.global it_8028FD4C
it_8028FD4C:
/* 8028FD4C 0028C92C  4E 80 00 20 */	blr

.global it_8028FD50
it_8028FD50:
/* 8028FD50 0028C930  7C 08 02 A6 */	mflr r0
/* 8028FD54 0028C934  3C 80 80 29 */	lis r4, it_8028FC5C@ha
/* 8028FD58 0028C938  90 01 00 04 */	stw r0, 4(r1)
/* 8028FD5C 0028C93C  38 84 FC 5C */	addi r4, r4, it_8028FC5C@l
/* 8028FD60 0028C940  94 21 FF F8 */	stwu r1, -8(r1)
/* 8028FD64 0028C944  4B FD D8 C9 */	bl it_8026D62C
/* 8028FD68 0028C948  38 60 00 00 */	li r3, 0
/* 8028FD6C 0028C94C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8028FD70 0028C950  38 21 00 08 */	addi r1, r1, 8
/* 8028FD74 0028C954  7C 08 03 A6 */	mtlr r0
/* 8028FD78 0028C958  4E 80 00 20 */	blr

.global it_8028FD7C
it_8028FD7C:
/* 8028FD7C 0028C95C  7C 08 02 A6 */	mflr r0
/* 8028FD80 0028C960  90 01 00 04 */	stw r0, 4(r1)
/* 8028FD84 0028C964  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8028FD88 0028C968  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8028FD8C 0028C96C  7C 7F 1B 78 */	mr r31, r3
/* 8028FD90 0028C970  80 63 00 28 */	lwz r3, 0x28(r3)
/* 8028FD94 0028C974  28 03 00 00 */	cmplwi r3, 0
/* 8028FD98 0028C978  40 82 00 0C */	bne .L_8028FDA4
/* 8028FD9C 0028C97C  38 00 00 00 */	li r0, 0
/* 8028FDA0 0028C980  48 00 00 08 */	b .L_8028FDA8
.L_8028FDA4:
/* 8028FDA4 0028C984  80 03 00 10 */	lwz r0, 0x10(r3)
.L_8028FDA8:
/* 8028FDA8 0028C988  7C 03 03 78 */	mr r3, r0
/* 8028FDAC 0028C98C  38 80 00 10 */	li r4, 0x10
/* 8028FDB0 0028C990  48 0E 21 ED */	bl HSD_JObjClearFlagsAll
/* 8028FDB4 0028C994  38 7F 00 00 */	addi r3, r31, 0
/* 8028FDB8 0028C998  38 80 00 02 */	li r4, 2
/* 8028FDBC 0028C99C  38 A0 00 02 */	li r5, 2
/* 8028FDC0 0028C9A0  4B FD 90 9D */	bl Item_80268E5C
/* 8028FDC4 0028C9A4  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8028FDC8 0028C9A8  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8028FDCC 0028C9AC  38 21 00 18 */	addi r1, r1, 0x18
/* 8028FDD0 0028C9B0  7C 08 03 A6 */	mtlr r0
/* 8028FDD4 0028C9B4  4E 80 00 20 */	blr

.global it_8028FDD8
it_8028FDD8:
/* 8028FDD8 0028C9B8  38 60 00 00 */	li r3, 0
/* 8028FDDC 0028C9BC  4E 80 00 20 */	blr

.global it_8028FDE0
it_8028FDE0:
/* 8028FDE0 0028C9C0  4E 80 00 20 */	blr

.global it_8028FDE4
it_8028FDE4:
/* 8028FDE4 0028C9C4  7C 08 02 A6 */	mflr r0
/* 8028FDE8 0028C9C8  38 80 00 03 */	li r4, 3
/* 8028FDEC 0028C9CC  90 01 00 04 */	stw r0, 4(r1)
/* 8028FDF0 0028C9D0  38 A0 00 06 */	li r5, 6
/* 8028FDF4 0028C9D4  94 21 FF F8 */	stwu r1, -8(r1)
/* 8028FDF8 0028C9D8  4B FD 90 65 */	bl Item_80268E5C
/* 8028FDFC 0028C9DC  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8028FE00 0028C9E0  38 21 00 08 */	addi r1, r1, 8
/* 8028FE04 0028C9E4  7C 08 03 A6 */	mtlr r0
/* 8028FE08 0028C9E8  4E 80 00 20 */	blr

.global it_8028FE0C
it_8028FE0C:
/* 8028FE0C 0028C9EC  38 60 00 00 */	li r3, 0
/* 8028FE10 0028C9F0  4E 80 00 20 */	blr

.global it_8028FE14
it_8028FE14:
/* 8028FE14 0028C9F4  7C 08 02 A6 */	mflr r0
/* 8028FE18 0028C9F8  90 01 00 04 */	stw r0, 4(r1)
/* 8028FE1C 0028C9FC  94 21 FF F8 */	stwu r1, -8(r1)
/* 8028FE20 0028CA00  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 8028FE24 0028CA04  80 84 00 CC */	lwz r4, 0xcc(r4)
/* 8028FE28 0028CA08  C0 24 00 10 */	lfs f1, 0x10(r4)
/* 8028FE2C 0028CA0C  C0 44 00 14 */	lfs f2, 0x14(r4)
/* 8028FE30 0028CA10  4B FE 2A 31 */	bl it_80272860
/* 8028FE34 0028CA14  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8028FE38 0028CA18  38 21 00 08 */	addi r1, r1, 8
/* 8028FE3C 0028CA1C  7C 08 03 A6 */	mtlr r0
/* 8028FE40 0028CA20  4E 80 00 20 */	blr

.global it_8028FE44
it_8028FE44:
/* 8028FE44 0028CA24  7C 08 02 A6 */	mflr r0
/* 8028FE48 0028CA28  3C 80 80 29 */	lis r4, it_8028FCE8@ha
/* 8028FE4C 0028CA2C  90 01 00 04 */	stw r0, 4(r1)
/* 8028FE50 0028CA30  38 84 FC E8 */	addi r4, r4, it_8028FCE8@l
/* 8028FE54 0028CA34  94 21 FF F8 */	stwu r1, -8(r1)
/* 8028FE58 0028CA38  4B FD E5 BD */	bl it_8026E414
/* 8028FE5C 0028CA3C  38 60 00 00 */	li r3, 0
/* 8028FE60 0028CA40  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8028FE64 0028CA44  38 21 00 08 */	addi r1, r1, 8
/* 8028FE68 0028CA48  7C 08 03 A6 */	mtlr r0
/* 8028FE6C 0028CA4C  4E 80 00 20 */	blr

.global it_8028FE70
it_8028FE70:
/* 8028FE70 0028CA50  7C 08 02 A6 */	mflr r0
/* 8028FE74 0028CA54  90 01 00 04 */	stw r0, 4(r1)
/* 8028FE78 0028CA58  94 21 FF F8 */	stwu r1, -8(r1)
/* 8028FE7C 0028CA5C  4B FD BA 19 */	bl it_8026B894
/* 8028FE80 0028CA60  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8028FE84 0028CA64  38 21 00 08 */	addi r1, r1, 8
/* 8028FE88 0028CA68  7C 08 03 A6 */	mtlr r0
/* 8028FE8C 0028CA6C  4E 80 00 20 */	blr


.section .data
    .balign 8
.global it_803F5DB0
it_803F5DB0:
    .4byte -1
    .4byte it_8028FC84
    .4byte it_8028FC8C
    .4byte it_8028FCBC
    .4byte -1
    .4byte it_8028FD44
    .4byte it_8028FD4C
    .4byte it_8028FD50
    .4byte -1
    .4byte it_8028FDD8
    .4byte it_8028FDE0
    .4byte NULL
    .4byte -1
    .4byte it_8028FE0C
    .4byte it_8028FE14
    .4byte it_8028FE44
.global it_803F5DF0
it_803F5DF0:
    .asciz "translate"


.section .sdata
    .balign 8
.global it_804D52A0
it_804D52A0:
    .asciz "jobj.h"
    .balign 4
.global it_804D52A8
it_804D52A8:
    .asciz "jobj"


.section .sdata2
    .balign 8
.global it_804DCA90
it_804DCA90:
    .4byte 0xBF800000
.global it_804DCA94
it_804DCA94:
    .4byte 0x00000000
