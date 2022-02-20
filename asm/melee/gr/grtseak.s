.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

.global func_80223864
func_80223864:
/* 80223864 00220444  4E 80 00 20 */	blr 
.global lbl_80223868
lbl_80223868:
/* 80223868 00220448  7C 08 02 A6 */	mflr r0
/* 8022386C 0022044C  3C 60 80 4A */	lis r3, stage_info@ha
/* 80223870 00220450  90 01 00 04 */	stw r0, 4(r1)
/* 80223874 00220454  38 63 E6 C8 */	addi r3, r3, stage_info@l
/* 80223878 00220458  38 A3 00 8C */	addi r5, r3, 0x8c
/* 8022387C 0022045C  94 21 FF F8 */	stwu r1, -8(r1)
/* 80223880 00220460  38 80 00 01 */	li r4, 1
/* 80223884 00220464  88 03 00 8C */	lbz r0, 0x8c(r3)
/* 80223888 00220468  38 60 00 00 */	li r3, 0
/* 8022388C 0022046C  50 60 1F 38 */	rlwimi r0, r3, 3, 0x1c, 0x1c
/* 80223890 00220470  98 05 00 00 */	stb r0, 0(r5)
/* 80223894 00220474  38 60 00 00 */	li r3, 0
/* 80223898 00220478  88 05 00 00 */	lbz r0, 0(r5)
/* 8022389C 0022047C  50 80 17 7A */	rlwimi r0, r4, 2, 0x1d, 0x1d
/* 802238A0 00220480  98 05 00 00 */	stb r0, 0(r5)
/* 802238A4 00220484  48 00 00 65 */	bl func_80223908
/* 802238A8 00220488  38 60 00 01 */	li r3, 1
/* 802238AC 0022048C  48 00 00 5D */	bl func_80223908
/* 802238B0 00220490  38 60 00 02 */	li r3, 2
/* 802238B4 00220494  48 00 00 55 */	bl func_80223908
/* 802238B8 00220498  4B FA 01 09 */	bl func_801C39C0
/* 802238BC 0022049C  4B FA 02 F9 */	bl func_801C3BB4
/* 802238C0 002204A0  4B FA 09 51 */	bl func_801C4210
/* 802238C4 002204A4  4B FA 09 E9 */	bl func_801C42AC
/* 802238C8 002204A8  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802238CC 002204AC  38 21 00 08 */	addi r1, r1, 8
/* 802238D0 002204B0  7C 08 03 A6 */	mtlr r0
/* 802238D4 002204B4  4E 80 00 20 */	blr 
.global lbl_802238D8
lbl_802238D8:
/* 802238D8 002204B8  4E 80 00 20 */	blr 
.global lbl_802238DC
lbl_802238DC:
/* 802238DC 002204BC  7C 08 02 A6 */	mflr r0
/* 802238E0 002204C0  38 60 00 00 */	li r3, 0
/* 802238E4 002204C4  90 01 00 04 */	stw r0, 4(r1)
/* 802238E8 002204C8  94 21 FF F8 */	stwu r1, -8(r1)
/* 802238EC 002204CC  4B FA 75 19 */	bl func_801CAE04
/* 802238F0 002204D0  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802238F4 002204D4  38 21 00 08 */	addi r1, r1, 8
/* 802238F8 002204D8  7C 08 03 A6 */	mtlr r0
/* 802238FC 002204DC  4E 80 00 20 */	blr 
.global lbl_80223900
lbl_80223900:
/* 80223900 002204E0  38 60 00 00 */	li r3, 0
/* 80223904 002204E4  4E 80 00 20 */	blr 

.global func_80223908
func_80223908:
/* 80223908 002204E8  7C 08 02 A6 */	mflr r0
/* 8022390C 002204EC  90 01 00 04 */	stw r0, 4(r1)
/* 80223910 002204F0  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80223914 002204F4  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80223918 002204F8  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8022391C 002204FC  93 A1 00 14 */	stw r29, 0x14(r1)
/* 80223920 00220500  93 81 00 10 */	stw r28, 0x10(r1)
/* 80223924 00220504  3B 83 00 00 */	addi r28, r3, 0
/* 80223928 00220508  1C 1C 00 14 */	mulli r0, r28, 0x14
/* 8022392C 0022050C  3C 60 80 3F */	lis r3, lbl_803E94B8@ha
/* 80223930 00220510  3B E3 94 B8 */	addi r31, r3, lbl_803E94B8@l
/* 80223934 00220514  38 7C 00 00 */	addi r3, r28, 0
/* 80223938 00220518  7F BF 02 14 */	add r29, r31, r0
/* 8022393C 0022051C  4B F9 DB 95 */	bl func_801C14D0
/* 80223940 00220520  7C 7E 1B 79 */	or. r30, r3, r3
/* 80223944 00220524  41 82 00 70 */	beq lbl_802239B4
/* 80223948 00220528  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 8022394C 0022052C  38 00 00 00 */	li r0, 0
/* 80223950 00220530  3C 60 80 1C */	lis r3, func_801C5DB0@ha
/* 80223954 00220534  90 1F 00 08 */	stw r0, 8(r31)
/* 80223958 00220538  38 83 5D B0 */	addi r4, r3, func_801C5DB0@l
/* 8022395C 0022053C  38 7E 00 00 */	addi r3, r30, 0
/* 80223960 00220540  90 1F 00 0C */	stw r0, 0xc(r31)
/* 80223964 00220544  38 A0 00 03 */	li r5, 3
/* 80223968 00220548  38 C0 00 00 */	li r6, 0
/* 8022396C 0022054C  48 16 CD 31 */	bl GObj_SetupGXLink
/* 80223970 00220550  80 1D 00 0C */	lwz r0, 0xc(r29)
/* 80223974 00220554  28 00 00 00 */	cmplwi r0, 0
/* 80223978 00220558  41 82 00 08 */	beq lbl_80223980
/* 8022397C 0022055C  90 1F 00 1C */	stw r0, 0x1c(r31)
lbl_80223980:
/* 80223980 00220560  81 9D 00 00 */	lwz r12, 0(r29)
/* 80223984 00220564  28 0C 00 00 */	cmplwi r12, 0
/* 80223988 00220568  41 82 00 10 */	beq lbl_80223998
/* 8022398C 0022056C  7D 88 03 A6 */	mtlr r12
/* 80223990 00220570  38 7E 00 00 */	addi r3, r30, 0
/* 80223994 00220574  4E 80 00 21 */	blrl 
lbl_80223998:
/* 80223998 00220578  80 9D 00 08 */	lwz r4, 8(r29)
/* 8022399C 0022057C  28 04 00 00 */	cmplwi r4, 0
/* 802239A0 00220580  41 82 00 2C */	beq lbl_802239CC
/* 802239A4 00220584  38 7E 00 00 */	addi r3, r30, 0
/* 802239A8 00220588  38 A0 00 04 */	li r5, 4
/* 802239AC 0022058C  48 16 C3 A9 */	bl func_8038FD54
/* 802239B0 00220590  48 00 00 1C */	b lbl_802239CC
lbl_802239B4:
/* 802239B4 00220594  38 DC 00 00 */	addi r6, r28, 0
/* 802239B8 00220598  4C C6 31 82 */	crclr 6
/* 802239BC 0022059C  38 7F 00 90 */	addi r3, r31, 0x90
/* 802239C0 002205A0  38 9F 00 B4 */	addi r4, r31, 0xb4
/* 802239C4 002205A4  38 A0 00 C3 */	li r5, 0xc3
/* 802239C8 002205A8  48 12 1C E1 */	bl OSReport
lbl_802239CC:
/* 802239CC 002205AC  7F C3 F3 78 */	mr r3, r30
/* 802239D0 002205B0  80 01 00 24 */	lwz r0, 0x24(r1)
/* 802239D4 002205B4  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 802239D8 002205B8  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 802239DC 002205BC  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 802239E0 002205C0  83 81 00 10 */	lwz r28, 0x10(r1)
/* 802239E4 002205C4  38 21 00 20 */	addi r1, r1, 0x20
/* 802239E8 002205C8  7C 08 03 A6 */	mtlr r0
/* 802239EC 002205CC  4E 80 00 20 */	blr 
.global lbl_802239F0
lbl_802239F0:
/* 802239F0 002205D0  7C 08 02 A6 */	mflr r0
/* 802239F4 002205D4  38 A0 00 00 */	li r5, 0
/* 802239F8 002205D8  90 01 00 04 */	stw r0, 4(r1)
/* 802239FC 002205DC  94 21 FF F8 */	stwu r1, -8(r1)
/* 80223A00 002205E0  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 80223A04 002205E4  80 84 00 14 */	lwz r4, 0x14(r4)
/* 80223A08 002205E8  4B FA 47 31 */	bl func_801C8138
/* 80223A0C 002205EC  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80223A10 002205F0  38 21 00 08 */	addi r1, r1, 8
/* 80223A14 002205F4  7C 08 03 A6 */	mtlr r0
/* 80223A18 002205F8  4E 80 00 20 */	blr 
.global lbl_80223A1C
lbl_80223A1C:
/* 80223A1C 002205FC  38 60 00 00 */	li r3, 0
/* 80223A20 00220600  4E 80 00 20 */	blr 
.global lbl_80223A24
lbl_80223A24:
/* 80223A24 00220604  4E 80 00 20 */	blr 
.global lbl_80223A28
lbl_80223A28:
/* 80223A28 00220608  4E 80 00 20 */	blr 
.global lbl_80223A2C
lbl_80223A2C:
/* 80223A2C 0022060C  7C 08 02 A6 */	mflr r0
/* 80223A30 00220610  90 01 00 04 */	stw r0, 4(r1)
/* 80223A34 00220614  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80223A38 00220618  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80223A3C 0022061C  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80223A40 00220620  7C 7E 1B 78 */	mr r30, r3
/* 80223A44 00220624  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80223A48 00220628  80 63 00 28 */	lwz r3, 0x28(r3)
/* 80223A4C 0022062C  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80223A50 00220630  4B F9 F4 81 */	bl func_801C2ED0
/* 80223A54 00220634  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80223A58 00220638  38 7E 00 00 */	addi r3, r30, 0
/* 80223A5C 0022063C  38 A0 00 00 */	li r5, 0
/* 80223A60 00220640  4B FA 46 D9 */	bl func_801C8138
/* 80223A64 00220644  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80223A68 00220648  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80223A6C 0022064C  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80223A70 00220650  38 21 00 20 */	addi r1, r1, 0x20
/* 80223A74 00220654  7C 08 03 A6 */	mtlr r0
/* 80223A78 00220658  4E 80 00 20 */	blr 
.global lbl_80223A7C
lbl_80223A7C:
/* 80223A7C 0022065C  38 60 00 00 */	li r3, 0
/* 80223A80 00220660  4E 80 00 20 */	blr 
.global lbl_80223A84
lbl_80223A84:
/* 80223A84 00220664  7C 08 02 A6 */	mflr r0
/* 80223A88 00220668  90 01 00 04 */	stw r0, 4(r1)
/* 80223A8C 0022066C  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80223A90 00220670  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80223A94 00220674  7C 7F 1B 78 */	mr r31, r3
/* 80223A98 00220678  4B DE DB 5D */	bl func_800115F4
/* 80223A9C 0022067C  7F E3 FB 78 */	mr r3, r31
/* 80223AA0 00220680  4B F9 F5 41 */	bl func_801C2FE0
/* 80223AA4 00220684  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80223AA8 00220688  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80223AAC 0022068C  38 21 00 18 */	addi r1, r1, 0x18
/* 80223AB0 00220690  7C 08 03 A6 */	mtlr r0
/* 80223AB4 00220694  4E 80 00 20 */	blr 
.global lbl_80223AB8
lbl_80223AB8:
/* 80223AB8 00220698  4E 80 00 20 */	blr 
.global lbl_80223ABC
lbl_80223ABC:
/* 80223ABC 0022069C  7C 08 02 A6 */	mflr r0
/* 80223AC0 002206A0  90 01 00 04 */	stw r0, 4(r1)
/* 80223AC4 002206A4  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80223AC8 002206A8  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80223ACC 002206AC  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80223AD0 002206B0  7C 7E 1B 78 */	mr r30, r3
/* 80223AD4 002206B4  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80223AD8 002206B8  80 63 00 28 */	lwz r3, 0x28(r3)
/* 80223ADC 002206BC  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80223AE0 002206C0  4B F9 F3 F1 */	bl func_801C2ED0
/* 80223AE4 002206C4  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80223AE8 002206C8  38 7E 00 00 */	addi r3, r30, 0
/* 80223AEC 002206CC  38 A0 00 00 */	li r5, 0
/* 80223AF0 002206D0  4B FA 46 49 */	bl func_801C8138
/* 80223AF4 002206D4  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80223AF8 002206D8  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80223AFC 002206DC  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80223B00 002206E0  38 21 00 20 */	addi r1, r1, 0x20
/* 80223B04 002206E4  7C 08 03 A6 */	mtlr r0
/* 80223B08 002206E8  4E 80 00 20 */	blr 
.global lbl_80223B0C
lbl_80223B0C:
/* 80223B0C 002206EC  38 60 00 00 */	li r3, 0
/* 80223B10 002206F0  4E 80 00 20 */	blr 
.global lbl_80223B14
lbl_80223B14:
/* 80223B14 002206F4  7C 08 02 A6 */	mflr r0
/* 80223B18 002206F8  90 01 00 04 */	stw r0, 4(r1)
/* 80223B1C 002206FC  94 21 FF F8 */	stwu r1, -8(r1)
/* 80223B20 00220700  4B F9 F4 C1 */	bl func_801C2FE0
/* 80223B24 00220704  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80223B28 00220708  38 21 00 08 */	addi r1, r1, 8
/* 80223B2C 0022070C  7C 08 03 A6 */	mtlr r0
/* 80223B30 00220710  4E 80 00 20 */	blr 
.global lbl_80223B34
lbl_80223B34:
/* 80223B34 00220714  4E 80 00 20 */	blr 
.global lbl_80223B38
lbl_80223B38:
/* 80223B38 00220718  38 60 00 00 */	li r3, 0
/* 80223B3C 0022071C  4E 80 00 20 */	blr 
.global lbl_80223B40
lbl_80223B40:
/* 80223B40 00220720  38 60 00 01 */	li r3, 1
/* 80223B44 00220724  4E 80 00 20 */	blr 


.section .data
    .balign 8
.global lbl_803E94B8
lbl_803E94B8:
	.4byte lbl_802239F0
	.4byte lbl_80223A1C
	.4byte lbl_80223A24
	.4byte lbl_80223A28
    .4byte NULL
	.4byte lbl_80223ABC
	.4byte lbl_80223B0C
	.4byte lbl_80223B14
	.4byte lbl_80223B34
    .4byte NULL
	.4byte lbl_80223A2C
	.4byte lbl_80223A7C
	.4byte lbl_80223A84
	.4byte lbl_80223AB8
    .4byte 0xC0000000
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
.global lbl_803E9508
lbl_803E9508:
    .4byte 0x2F477254
    .4byte 0x536B2E64
    .4byte 0x61740000
.global lbl_803E9514
lbl_803E9514:
    .4byte 0x0000003C
    .4byte lbl_803E94B8
    .4byte lbl_803E9508
	.4byte lbl_80223868
	.4byte func_80223864
	.4byte lbl_802238D8
	.4byte lbl_802238DC
	.4byte lbl_80223900
	.4byte lbl_80223B38
	.4byte lbl_80223B40
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
    .4byte 0x67727473
    .4byte 0x65616B2E
    .4byte 0x63000000
