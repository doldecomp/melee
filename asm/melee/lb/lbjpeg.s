.include "macros.inc"

.section .text

.global func_8001F890
func_8001F890:
/* 8001F890 0001C470  7C 08 02 A6 */	mflr r0
/* 8001F894 0001C474  3C 80 80 43 */	lis r4, .L_804335B8@ha
/* 8001F898 0001C478  90 01 00 04 */	stw r0, 4(r1)
/* 8001F89C 0001C47C  39 20 00 00 */	li r9, 0
/* 8001F8A0 0001C480  38 00 00 06 */	li r0, 6
/* 8001F8A4 0001C484  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8001F8A8 0001C488  38 C0 00 00 */	li r6, 0
/* 8001F8AC 0001C48C  38 E0 00 80 */	li r7, 0x80
/* 8001F8B0 0001C490  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8001F8B4 0001C494  3B E4 35 B8 */	addi r31, r4, .L_804335B8@l
/* 8001F8B8 0001C498  39 5F 00 70 */	addi r10, r31, 0x70
/* 8001F8BC 0001C49C  91 3F 00 70 */	stw r9, 0x70(r31)
/* 8001F8C0 0001C4A0  38 9F 00 88 */	addi r4, r31, 0x88
/* 8001F8C4 0001C4A4  A0 BF 00 6C */	lhz r5, 0x6c(r31)
/* 8001F8C8 0001C4A8  B0 BF 00 74 */	sth r5, 0x74(r31)
/* 8001F8CC 0001C4AC  38 A0 00 00 */	li r5, 0
/* 8001F8D0 0001C4B0  A1 1F 00 6E */	lhz r8, 0x6e(r31)
/* 8001F8D4 0001C4B4  B1 1F 00 76 */	sth r8, 0x76(r31)
/* 8001F8D8 0001C4B8  39 00 00 00 */	li r8, 0
/* 8001F8DC 0001C4BC  90 1F 00 78 */	stw r0, 0x78(r31)
/* 8001F8E0 0001C4C0  91 3F 00 7C */	stw r9, 0x7c(r31)
/* 8001F8E4 0001C4C4  C0 02 83 00 */	lfs f0, .L_804D7CE0@sda21(r2)
/* 8001F8E8 0001C4C8  D0 1F 00 84 */	stfs f0, 0x84(r31)
/* 8001F8EC 0001C4CC  D0 1F 00 80 */	stfs f0, 0x80(r31)
/* 8001F8F0 0001C4D0  91 5F 00 88 */	stw r10, 0x88(r31)
/* 8001F8F4 0001C4D4  91 3F 00 8C */	stw r9, 0x8c(r31)
/* 8001F8F8 0001C4D8  48 38 4E 85 */	bl func_803A477C
/* 8001F8FC 0001C4DC  90 7F 00 90 */	stw r3, 0x90(r31)
/* 8001F900 0001C4E0  80 7F 00 90 */	lwz r3, 0x90(r31)
/* 8001F904 0001C4E4  80 03 00 40 */	lwz r0, 0x40(r3)
/* 8001F908 0001C4E8  60 00 00 10 */	ori r0, r0, 0x10
/* 8001F90C 0001C4EC  90 03 00 40 */	stw r0, 0x40(r3)
/* 8001F910 0001C4F0  80 7F 00 90 */	lwz r3, 0x90(r31)
/* 8001F914 0001C4F4  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8001F918 0001C4F8  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8001F91C 0001C4FC  38 21 00 18 */	addi r1, r1, 0x18
/* 8001F920 0001C500  7C 08 03 A6 */	mtlr r0
/* 8001F924 0001C504  4E 80 00 20 */	blr

.global func_8001F928
func_8001F928:
/* 8001F928 0001C508  7C 08 02 A6 */	mflr r0
/* 8001F92C 0001C50C  3C A0 80 43 */	lis r5, .L_804335B8@ha
/* 8001F930 0001C510  90 01 00 04 */	stw r0, 4(r1)
/* 8001F934 0001C514  38 E0 00 01 */	li r7, 1
/* 8001F938 0001C518  39 00 00 00 */	li r8, 0
/* 8001F93C 0001C51C  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8001F940 0001C520  39 20 00 00 */	li r9, 0
/* 8001F944 0001C524  39 40 00 00 */	li r10, 0
/* 8001F948 0001C528  BF 41 00 10 */	stmw r26, 0x10(r1)
/* 8001F94C 0001C52C  3B E5 35 B8 */	addi r31, r5, .L_804335B8@l
/* 8001F950 0001C530  7C 9B 23 78 */	mr r27, r4
/* 8001F954 0001C534  7C 7A 1B 78 */	mr r26, r3
/* 8001F958 0001C538  3B BF 00 6C */	addi r29, r31, 0x6c
/* 8001F95C 0001C53C  3B DF 00 6E */	addi r30, r31, 0x6e
/* 8001F960 0001C540  38 7F 00 00 */	addi r3, r31, 0
/* 8001F964 0001C544  A0 BF 00 6C */	lhz r5, 0x6c(r31)
/* 8001F968 0001C548  80 9F 00 20 */	lwz r4, 0x20(r31)
/* 8001F96C 0001C54C  A0 DF 00 6E */	lhz r6, 0x6e(r31)
/* 8001F970 0001C550  48 31 F0 41 */	bl GXInitTexObj
/* 8001F974 0001C554  C0 22 83 00 */	lfs f1, .L_804D7CE0@sda21(r2)
/* 8001F978 0001C558  38 7F 00 00 */	addi r3, r31, 0
/* 8001F97C 0001C55C  38 80 00 00 */	li r4, 0
/* 8001F980 0001C560  FC 40 08 90 */	fmr f2, f1
/* 8001F984 0001C564  38 A0 00 00 */	li r5, 0
/* 8001F988 0001C568  FC 60 08 90 */	fmr f3, f1
/* 8001F98C 0001C56C  38 C0 00 00 */	li r6, 0
/* 8001F990 0001C570  38 E0 00 00 */	li r7, 0
/* 8001F994 0001C574  39 00 00 00 */	li r8, 0
/* 8001F998 0001C578  48 31 F2 D5 */	bl GXInitTexObjLOD
/* 8001F99C 0001C57C  38 7F 00 00 */	addi r3, r31, 0
/* 8001F9A0 0001C580  38 80 00 00 */	li r4, 0
/* 8001F9A4 0001C584  48 31 F6 2D */	bl GXLoadTexObj
/* 8001F9A8 0001C588  A0 9D 00 00 */	lhz r4, 0(r29)
/* 8001F9AC 0001C58C  3B 9F 00 24 */	addi r28, r31, 0x24
/* 8001F9B0 0001C590  A0 1E 00 00 */	lhz r0, 0(r30)
/* 8001F9B4 0001C594  38 7C 00 00 */	addi r3, r28, 0
/* 8001F9B8 0001C598  7C 85 0E 70 */	srawi r5, r4, 1
/* 8001F9BC 0001C59C  7C 00 0E 70 */	srawi r0, r0, 1
/* 8001F9C0 0001C5A0  80 9F 00 44 */	lwz r4, 0x44(r31)
/* 8001F9C4 0001C5A4  54 A5 04 3E */	clrlwi r5, r5, 0x10
/* 8001F9C8 0001C5A8  54 06 04 3E */	clrlwi r6, r0, 0x10
/* 8001F9CC 0001C5AC  38 E0 00 01 */	li r7, 1
/* 8001F9D0 0001C5B0  39 00 00 00 */	li r8, 0
/* 8001F9D4 0001C5B4  39 20 00 00 */	li r9, 0
/* 8001F9D8 0001C5B8  39 40 00 00 */	li r10, 0
/* 8001F9DC 0001C5BC  48 31 EF D5 */	bl GXInitTexObj
/* 8001F9E0 0001C5C0  C0 22 83 00 */	lfs f1, .L_804D7CE0@sda21(r2)
/* 8001F9E4 0001C5C4  38 7C 00 00 */	addi r3, r28, 0
/* 8001F9E8 0001C5C8  38 80 00 00 */	li r4, 0
/* 8001F9EC 0001C5CC  FC 40 08 90 */	fmr f2, f1
/* 8001F9F0 0001C5D0  38 A0 00 00 */	li r5, 0
/* 8001F9F4 0001C5D4  FC 60 08 90 */	fmr f3, f1
/* 8001F9F8 0001C5D8  38 C0 00 00 */	li r6, 0
/* 8001F9FC 0001C5DC  38 E0 00 00 */	li r7, 0
/* 8001FA00 0001C5E0  39 00 00 00 */	li r8, 0
/* 8001FA04 0001C5E4  48 31 F2 69 */	bl GXInitTexObjLOD
/* 8001FA08 0001C5E8  38 7C 00 00 */	addi r3, r28, 0
/* 8001FA0C 0001C5EC  38 80 00 01 */	li r4, 1
/* 8001FA10 0001C5F0  48 31 F5 C1 */	bl GXLoadTexObj
/* 8001FA14 0001C5F4  A0 9D 00 00 */	lhz r4, 0(r29)
/* 8001FA18 0001C5F8  3B 9F 00 48 */	addi r28, r31, 0x48
/* 8001FA1C 0001C5FC  A0 1E 00 00 */	lhz r0, 0(r30)
/* 8001FA20 0001C600  38 7C 00 00 */	addi r3, r28, 0
/* 8001FA24 0001C604  7C 85 0E 70 */	srawi r5, r4, 1
/* 8001FA28 0001C608  7C 00 0E 70 */	srawi r0, r0, 1
/* 8001FA2C 0001C60C  80 9F 00 68 */	lwz r4, 0x68(r31)
/* 8001FA30 0001C610  54 A5 04 3E */	clrlwi r5, r5, 0x10
/* 8001FA34 0001C614  54 06 04 3E */	clrlwi r6, r0, 0x10
/* 8001FA38 0001C618  38 E0 00 01 */	li r7, 1
/* 8001FA3C 0001C61C  39 00 00 00 */	li r8, 0
/* 8001FA40 0001C620  39 20 00 00 */	li r9, 0
/* 8001FA44 0001C624  39 40 00 00 */	li r10, 0
/* 8001FA48 0001C628  48 31 EF 69 */	bl GXInitTexObj
/* 8001FA4C 0001C62C  C0 22 83 00 */	lfs f1, .L_804D7CE0@sda21(r2)
/* 8001FA50 0001C630  38 7C 00 00 */	addi r3, r28, 0
/* 8001FA54 0001C634  38 80 00 00 */	li r4, 0
/* 8001FA58 0001C638  FC 40 08 90 */	fmr f2, f1
/* 8001FA5C 0001C63C  38 A0 00 00 */	li r5, 0
/* 8001FA60 0001C640  FC 60 08 90 */	fmr f3, f1
/* 8001FA64 0001C644  38 C0 00 00 */	li r6, 0
/* 8001FA68 0001C648  38 E0 00 00 */	li r7, 0
/* 8001FA6C 0001C64C  39 00 00 00 */	li r8, 0
/* 8001FA70 0001C650  48 31 F1 FD */	bl GXInitTexObjLOD
/* 8001FA74 0001C654  38 7C 00 00 */	addi r3, r28, 0
/* 8001FA78 0001C658  38 80 00 02 */	li r4, 2
/* 8001FA7C 0001C65C  48 31 F5 55 */	bl GXLoadTexObj
/* 8001FA80 0001C660  38 7A 00 00 */	addi r3, r26, 0
/* 8001FA84 0001C664  38 9B 00 00 */	addi r4, r27, 0
/* 8001FA88 0001C668  48 38 4F 59 */	bl func_803A49E0
/* 8001FA8C 0001C66C  BB 41 00 10 */	lmw r26, 0x10(r1)
/* 8001FA90 0001C670  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8001FA94 0001C674  38 21 00 28 */	addi r1, r1, 0x28
/* 8001FA98 0001C678  7C 08 03 A6 */	mtlr r0
/* 8001FA9C 0001C67C  4E 80 00 20 */	blr

.global func_8001FAA0
func_8001FAA0:
/* 8001FAA0 0001C680  7C 08 02 A6 */	mflr r0
/* 8001FAA4 0001C684  3C C0 80 43 */	lis r6, .L_804335B8@ha
/* 8001FAA8 0001C688  90 01 00 04 */	stw r0, 4(r1)
/* 8001FAAC 0001C68C  94 21 FF A8 */	stwu r1, -0x58(r1)
/* 8001FAB0 0001C690  BF 01 00 38 */	stmw r24, 0x38(r1)
/* 8001FAB4 0001C694  3B A6 35 B8 */	addi r29, r6, .L_804335B8@l
/* 8001FAB8 0001C698  54 9E 04 3E */	clrlwi r30, r4, 0x10
/* 8001FABC 0001C69C  3B 7D 00 6C */	addi r27, r29, 0x6c
/* 8001FAC0 0001C6A0  54 BF 04 3E */	clrlwi r31, r5, 0x10
/* 8001FAC4 0001C6A4  3B 9D 00 6E */	addi r28, r29, 0x6e
/* 8001FAC8 0001C6A8  7C 78 1B 78 */	mr r24, r3
/* 8001FACC 0001C6AC  B0 9D 00 6C */	sth r4, 0x6c(r29)
/* 8001FAD0 0001C6B0  B0 BD 00 6E */	sth r5, 0x6e(r29)
/* 8001FAD4 0001C6B4  48 31 61 85 */	bl func_80335C58
/* 8001FAD8 0001C6B8  3B 3D 00 94 */	addi r25, r29, 0x94
/* 8001FADC 0001C6BC  38 78 00 00 */	addi r3, r24, 0
/* 8001FAE0 0001C6C0  38 99 00 00 */	addi r4, r25, 0
/* 8001FAE4 0001C6C4  38 BD 00 98 */	addi r5, r29, 0x98
/* 8001FAE8 0001C6C8  4B FF 6C 79 */	bl func_80016760
/* 8001FAEC 0001C6CC  A0 7B 00 00 */	lhz r3, 0(r27)
/* 8001FAF0 0001C6D0  A0 1C 00 00 */	lhz r0, 0(r28)
/* 8001FAF4 0001C6D4  7F 03 01 D6 */	mullw r24, r3, r0
/* 8001FAF8 0001C6D8  38 78 00 00 */	addi r3, r24, 0
/* 8001FAFC 0001C6DC  48 35 F6 E9 */	bl HSD_MemAlloc
/* 8001FB00 0001C6E0  3B 5D 00 20 */	addi r26, r29, 0x20
/* 8001FB04 0001C6E4  90 7D 00 20 */	stw r3, 0x20(r29)
/* 8001FB08 0001C6E8  7F 04 C3 78 */	mr r4, r24
/* 8001FB0C 0001C6EC  80 7D 00 20 */	lwz r3, 0x20(r29)
/* 8001FB10 0001C6F0  48 32 4C CD */	bl DCInvalidateRange
/* 8001FB14 0001C6F4  A0 7B 00 00 */	lhz r3, 0(r27)
/* 8001FB18 0001C6F8  A0 1C 00 00 */	lhz r0, 0(r28)
/* 8001FB1C 0001C6FC  7C 03 01 D6 */	mullw r0, r3, r0
/* 8001FB20 0001C700  7C 18 16 70 */	srawi r24, r0, 2
/* 8001FB24 0001C704  38 78 00 00 */	addi r3, r24, 0
/* 8001FB28 0001C708  48 35 F6 BD */	bl HSD_MemAlloc
/* 8001FB2C 0001C70C  3B 9D 00 44 */	addi r28, r29, 0x44
/* 8001FB30 0001C710  90 7D 00 44 */	stw r3, 0x44(r29)
/* 8001FB34 0001C714  7F 04 C3 78 */	mr r4, r24
/* 8001FB38 0001C718  80 7D 00 44 */	lwz r3, 0x44(r29)
/* 8001FB3C 0001C71C  48 32 4C A1 */	bl DCInvalidateRange
/* 8001FB40 0001C720  7F 03 C3 78 */	mr r3, r24
/* 8001FB44 0001C724  48 35 F6 A1 */	bl HSD_MemAlloc
/* 8001FB48 0001C728  94 7D 00 68 */	stwu r3, 0x68(r29)
/* 8001FB4C 0001C72C  7F 04 C3 78 */	mr r4, r24
/* 8001FB50 0001C730  80 7D 00 00 */	lwz r3, 0(r29)
/* 8001FB54 0001C734  48 32 4C 89 */	bl DCInvalidateRange
/* 8001FB58 0001C738  38 60 00 0C */	li r3, 0xc
/* 8001FB5C 0001C73C  48 35 F6 89 */	bl HSD_MemAlloc
/* 8001FB60 0001C740  3B 03 00 00 */	addi r24, r3, 0
/* 8001FB64 0001C744  38 61 00 18 */	addi r3, r1, 0x18
/* 8001FB68 0001C748  38 80 00 00 */	li r4, 0
/* 8001FB6C 0001C74C  38 A0 00 1C */	li r5, 0x1c
/* 8001FB70 0001C750  4B FE 35 91 */	bl memset
/* 8001FB74 0001C754  B3 C1 00 18 */	sth r30, 0x18(r1)
/* 8001FB78 0001C758  7F 04 C3 78 */	mr r4, r24
/* 8001FB7C 0001C75C  B3 E1 00 1A */	sth r31, 0x1a(r1)
/* 8001FB80 0001C760  80 79 00 00 */	lwz r3, 0(r25)
/* 8001FB84 0001C764  48 30 FD 51 */	bl JPEGGetFileInfo
/* 8001FB88 0001C768  7F 03 C3 78 */	mr r3, r24
/* 8001FB8C 0001C76C  A0 81 00 1A */	lhz r4, 0x1a(r1)
/* 8001FB90 0001C770  48 31 01 B1 */	bl func_8032FD40
/* 8001FB94 0001C774  48 35 F6 51 */	bl HSD_MemAlloc
/* 8001FB98 0001C778  80 D9 00 00 */	lwz r6, 0(r25)
/* 8001FB9C 0001C77C  3B 23 00 00 */	addi r25, r3, 0
/* 8001FBA0 0001C780  38 B9 00 00 */	addi r5, r25, 0
/* 8001FBA4 0001C784  38 F8 00 00 */	addi r7, r24, 0
/* 8001FBA8 0001C788  38 61 00 18 */	addi r3, r1, 0x18
/* 8001FBAC 0001C78C  38 81 00 14 */	addi r4, r1, 0x14
/* 8001FBB0 0001C790  48 31 02 09 */	bl func_8032FDB8
/* 8001FBB4 0001C794  A0 FB 00 00 */	lhz r7, 0(r27)
/* 8001FBB8 0001C798  28 07 02 80 */	cmplwi r7, 0x280
/* 8001FBBC 0001C79C  40 82 00 18 */	bne .L_8001FBD4
/* 8001FBC0 0001C7A0  80 9A 00 00 */	lwz r4, 0(r26)
/* 8001FBC4 0001C7A4  80 BC 00 00 */	lwz r5, 0(r28)
/* 8001FBC8 0001C7A8  80 DD 00 00 */	lwz r6, 0(r29)
/* 8001FBCC 0001C7AC  48 31 17 75 */	bl func_80331340
/* 8001FBD0 0001C7B0  48 00 00 14 */	b .L_8001FBE4
.L_8001FBD4:
/* 8001FBD4 0001C7B4  80 9A 00 00 */	lwz r4, 0(r26)
/* 8001FBD8 0001C7B8  80 BC 00 00 */	lwz r5, 0(r28)
/* 8001FBDC 0001C7BC  80 DD 00 00 */	lwz r6, 0(r29)
/* 8001FBE0 0001C7C0  48 31 17 F1 */	bl func_803313D0
.L_8001FBE4:
/* 8001FBE4 0001C7C4  7F 03 C3 78 */	mr r3, r24
/* 8001FBE8 0001C7C8  48 35 F5 C9 */	bl HSD_Free
/* 8001FBEC 0001C7CC  7F 23 CB 78 */	mr r3, r25
/* 8001FBF0 0001C7D0  48 35 F5 C1 */	bl HSD_Free
/* 8001FBF4 0001C7D4  BB 01 00 38 */	lmw r24, 0x38(r1)
/* 8001FBF8 0001C7D8  80 01 00 5C */	lwz r0, 0x5c(r1)
/* 8001FBFC 0001C7DC  38 21 00 58 */	addi r1, r1, 0x58
/* 8001FC00 0001C7E0  7C 08 03 A6 */	mtlr r0
/* 8001FC04 0001C7E4  4E 80 00 20 */	blr

.section .bss, "wa"
    .balign 8

.L_804335B8:
    .skip 0xA0

.section .sdata2
    .balign 8

.L_804D7CE0:
    .4byte 0x00000000
    .4byte 0x00000000
