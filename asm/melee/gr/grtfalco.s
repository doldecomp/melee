.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

.global func_802207F0
func_802207F0:
/* 802207F0 0021D3D0  4E 80 00 20 */	blr 
/* 802207F4 0021D3D4  7C 08 02 A6 */	mflr r0
/* 802207F8 0021D3D8  90 01 00 04 */	stw r0, 4(r1)
/* 802207FC 0021D3DC  94 21 FF F8 */	stwu r1, -8(r1)
/* 80220800 0021D3E0  4B FA 41 F9 */	bl func_801C49F8
/* 80220804 0021D3E4  3C 80 80 4A */	lis r4, lbl_8049E6C8@ha
/* 80220808 0021D3E8  90 6D B4 58 */	stw r3, lbl_804D6AF8@sda21(r13)
/* 8022080C 0021D3EC  38 64 E6 C8 */	addi r3, r4, lbl_8049E6C8@l
/* 80220810 0021D3F0  38 A3 00 8C */	addi r5, r3, 0x8c
/* 80220814 0021D3F4  88 03 00 8C */	lbz r0, 0x8c(r3)
/* 80220818 0021D3F8  38 60 00 00 */	li r3, 0
/* 8022081C 0021D3FC  50 60 1F 38 */	rlwimi r0, r3, 3, 0x1c, 0x1c
/* 80220820 0021D400  98 05 00 00 */	stb r0, 0(r5)
/* 80220824 0021D404  38 80 00 01 */	li r4, 1
/* 80220828 0021D408  38 60 00 00 */	li r3, 0
/* 8022082C 0021D40C  88 05 00 00 */	lbz r0, 0(r5)
/* 80220830 0021D410  50 80 17 7A */	rlwimi r0, r4, 2, 0x1d, 0x1d
/* 80220834 0021D414  98 05 00 00 */	stb r0, 0(r5)
/* 80220838 0021D418  48 00 00 65 */	bl func_8022089C
/* 8022083C 0021D41C  38 60 00 01 */	li r3, 1
/* 80220840 0021D420  48 00 00 5D */	bl func_8022089C
/* 80220844 0021D424  38 60 00 02 */	li r3, 2
/* 80220848 0021D428  48 00 00 55 */	bl func_8022089C
/* 8022084C 0021D42C  4B FA 31 75 */	bl func_801C39C0
/* 80220850 0021D430  4B FA 33 65 */	bl func_801C3BB4
/* 80220854 0021D434  4B FA 39 BD */	bl func_801C4210
/* 80220858 0021D438  4B FA 3A 55 */	bl func_801C42AC
/* 8022085C 0021D43C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80220860 0021D440  38 21 00 08 */	addi r1, r1, 8
/* 80220864 0021D444  7C 08 03 A6 */	mtlr r0
/* 80220868 0021D448  4E 80 00 20 */	blr 
/* 8022086C 0021D44C  4E 80 00 20 */	blr 
/* 80220870 0021D450  7C 08 02 A6 */	mflr r0
/* 80220874 0021D454  38 60 00 00 */	li r3, 0
/* 80220878 0021D458  90 01 00 04 */	stw r0, 4(r1)
/* 8022087C 0021D45C  94 21 FF F8 */	stwu r1, -8(r1)
/* 80220880 0021D460  4B FA A5 85 */	bl func_801CAE04
/* 80220884 0021D464  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80220888 0021D468  38 21 00 08 */	addi r1, r1, 8
/* 8022088C 0021D46C  7C 08 03 A6 */	mtlr r0
/* 80220890 0021D470  4E 80 00 20 */	blr 
/* 80220894 0021D474  38 60 00 00 */	li r3, 0
/* 80220898 0021D478  4E 80 00 20 */	blr 

.global func_8022089C
func_8022089C:
/* 8022089C 0021D47C  7C 08 02 A6 */	mflr r0
/* 802208A0 0021D480  90 01 00 04 */	stw r0, 4(r1)
/* 802208A4 0021D484  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 802208A8 0021D488  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 802208AC 0021D48C  93 C1 00 18 */	stw r30, 0x18(r1)
/* 802208B0 0021D490  93 A1 00 14 */	stw r29, 0x14(r1)
/* 802208B4 0021D494  93 81 00 10 */	stw r28, 0x10(r1)
/* 802208B8 0021D498  3B 83 00 00 */	addi r28, r3, 0
/* 802208BC 0021D49C  1C 1C 00 14 */	mulli r0, r28, 0x14
/* 802208C0 0021D4A0  3C 60 80 3F */	lis r3, lbl_803E8918@ha
/* 802208C4 0021D4A4  3B E3 89 18 */	addi r31, r3, lbl_803E8918@l
/* 802208C8 0021D4A8  38 7C 00 00 */	addi r3, r28, 0
/* 802208CC 0021D4AC  7F BF 02 14 */	add r29, r31, r0
/* 802208D0 0021D4B0  4B FA 0C 01 */	bl func_801C14D0
/* 802208D4 0021D4B4  7C 7E 1B 79 */	or. r30, r3, r3
/* 802208D8 0021D4B8  41 82 00 70 */	beq lbl_80220948
/* 802208DC 0021D4BC  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 802208E0 0021D4C0  38 00 00 00 */	li r0, 0
/* 802208E4 0021D4C4  3C 60 80 1C */	lis r3, func_801C5DB0@ha
/* 802208E8 0021D4C8  90 1F 00 08 */	stw r0, 8(r31)
/* 802208EC 0021D4CC  38 83 5D B0 */	addi r4, r3, func_801C5DB0@l
/* 802208F0 0021D4D0  38 7E 00 00 */	addi r3, r30, 0
/* 802208F4 0021D4D4  90 1F 00 0C */	stw r0, 0xc(r31)
/* 802208F8 0021D4D8  38 A0 00 03 */	li r5, 3
/* 802208FC 0021D4DC  38 C0 00 00 */	li r6, 0
/* 80220900 0021D4E0  48 16 FD 9D */	bl func_8039069C
/* 80220904 0021D4E4  80 1D 00 0C */	lwz r0, 0xc(r29)
/* 80220908 0021D4E8  28 00 00 00 */	cmplwi r0, 0
/* 8022090C 0021D4EC  41 82 00 08 */	beq lbl_80220914
/* 80220910 0021D4F0  90 1F 00 1C */	stw r0, 0x1c(r31)
lbl_80220914:
/* 80220914 0021D4F4  81 9D 00 00 */	lwz r12, 0(r29)
/* 80220918 0021D4F8  28 0C 00 00 */	cmplwi r12, 0
/* 8022091C 0021D4FC  41 82 00 10 */	beq lbl_8022092C
/* 80220920 0021D500  7D 88 03 A6 */	mtlr r12
/* 80220924 0021D504  38 7E 00 00 */	addi r3, r30, 0
/* 80220928 0021D508  4E 80 00 21 */	blrl 
lbl_8022092C:
/* 8022092C 0021D50C  80 9D 00 08 */	lwz r4, 8(r29)
/* 80220930 0021D510  28 04 00 00 */	cmplwi r4, 0
/* 80220934 0021D514  41 82 00 2C */	beq lbl_80220960
/* 80220938 0021D518  38 7E 00 00 */	addi r3, r30, 0
/* 8022093C 0021D51C  38 A0 00 04 */	li r5, 4
/* 80220940 0021D520  48 16 F4 15 */	bl func_8038FD54
/* 80220944 0021D524  48 00 00 1C */	b lbl_80220960
lbl_80220948:
/* 80220948 0021D528  38 DC 00 00 */	addi r6, r28, 0
/* 8022094C 0021D52C  4C C6 31 82 */	crclr 6
/* 80220950 0021D530  38 7F 00 90 */	addi r3, r31, 0x90
/* 80220954 0021D534  38 9F 00 B4 */	addi r4, r31, 0xb4
/* 80220958 0021D538  38 A0 00 C9 */	li r5, 0xc9
/* 8022095C 0021D53C  48 12 4D 4D */	bl OSReport
lbl_80220960:
/* 80220960 0021D540  7F C3 F3 78 */	mr r3, r30
/* 80220964 0021D544  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80220968 0021D548  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8022096C 0021D54C  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80220970 0021D550  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 80220974 0021D554  83 81 00 10 */	lwz r28, 0x10(r1)
/* 80220978 0021D558  38 21 00 20 */	addi r1, r1, 0x20
/* 8022097C 0021D55C  7C 08 03 A6 */	mtlr r0
/* 80220980 0021D560  4E 80 00 20 */	blr 
/* 80220984 0021D564  7C 08 02 A6 */	mflr r0
/* 80220988 0021D568  38 A0 00 00 */	li r5, 0
/* 8022098C 0021D56C  90 01 00 04 */	stw r0, 4(r1)
/* 80220990 0021D570  94 21 FF F8 */	stwu r1, -8(r1)
/* 80220994 0021D574  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 80220998 0021D578  80 84 00 14 */	lwz r4, 0x14(r4)
/* 8022099C 0021D57C  4B FA 77 9D */	bl func_801C8138
/* 802209A0 0021D580  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802209A4 0021D584  38 21 00 08 */	addi r1, r1, 8
/* 802209A8 0021D588  7C 08 03 A6 */	mtlr r0
/* 802209AC 0021D58C  4E 80 00 20 */	blr 
/* 802209B0 0021D590  38 60 00 00 */	li r3, 0
/* 802209B4 0021D594  4E 80 00 20 */	blr 
/* 802209B8 0021D598  4E 80 00 20 */	blr 
/* 802209BC 0021D59C  4E 80 00 20 */	blr 
/* 802209C0 0021D5A0  7C 08 02 A6 */	mflr r0
/* 802209C4 0021D5A4  90 01 00 04 */	stw r0, 4(r1)
/* 802209C8 0021D5A8  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 802209CC 0021D5AC  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 802209D0 0021D5B0  93 C1 00 18 */	stw r30, 0x18(r1)
/* 802209D4 0021D5B4  7C 7E 1B 78 */	mr r30, r3
/* 802209D8 0021D5B8  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 802209DC 0021D5BC  80 63 00 28 */	lwz r3, 0x28(r3)
/* 802209E0 0021D5C0  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 802209E4 0021D5C4  4B FA 24 ED */	bl func_801C2ED0
/* 802209E8 0021D5C8  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 802209EC 0021D5CC  38 7E 00 00 */	addi r3, r30, 0
/* 802209F0 0021D5D0  38 A0 00 00 */	li r5, 0
/* 802209F4 0021D5D4  4B FA 77 45 */	bl func_801C8138
/* 802209F8 0021D5D8  80 01 00 24 */	lwz r0, 0x24(r1)
/* 802209FC 0021D5DC  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80220A00 0021D5E0  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80220A04 0021D5E4  38 21 00 20 */	addi r1, r1, 0x20
/* 80220A08 0021D5E8  7C 08 03 A6 */	mtlr r0
/* 80220A0C 0021D5EC  4E 80 00 20 */	blr 
/* 80220A10 0021D5F0  38 60 00 00 */	li r3, 0
/* 80220A14 0021D5F4  4E 80 00 20 */	blr 
/* 80220A18 0021D5F8  7C 08 02 A6 */	mflr r0
/* 80220A1C 0021D5FC  90 01 00 04 */	stw r0, 4(r1)
/* 80220A20 0021D600  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80220A24 0021D604  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80220A28 0021D608  7C 7F 1B 78 */	mr r31, r3
/* 80220A2C 0021D60C  4B DF 0B C9 */	bl func_800115F4
/* 80220A30 0021D610  7F E3 FB 78 */	mr r3, r31
/* 80220A34 0021D614  4B FA 25 AD */	bl func_801C2FE0
/* 80220A38 0021D618  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80220A3C 0021D61C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80220A40 0021D620  38 21 00 18 */	addi r1, r1, 0x18
/* 80220A44 0021D624  7C 08 03 A6 */	mtlr r0
/* 80220A48 0021D628  4E 80 00 20 */	blr 
/* 80220A4C 0021D62C  4E 80 00 20 */	blr 
/* 80220A50 0021D630  7C 08 02 A6 */	mflr r0
/* 80220A54 0021D634  90 01 00 04 */	stw r0, 4(r1)
/* 80220A58 0021D638  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80220A5C 0021D63C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80220A60 0021D640  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80220A64 0021D644  7C 7E 1B 78 */	mr r30, r3
/* 80220A68 0021D648  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80220A6C 0021D64C  80 63 00 28 */	lwz r3, 0x28(r3)
/* 80220A70 0021D650  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80220A74 0021D654  4B FA 24 5D */	bl func_801C2ED0
/* 80220A78 0021D658  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80220A7C 0021D65C  38 7E 00 00 */	addi r3, r30, 0
/* 80220A80 0021D660  38 A0 00 00 */	li r5, 0
/* 80220A84 0021D664  4B FA 76 B5 */	bl func_801C8138
/* 80220A88 0021D668  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80220A8C 0021D66C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80220A90 0021D670  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80220A94 0021D674  38 21 00 20 */	addi r1, r1, 0x20
/* 80220A98 0021D678  7C 08 03 A6 */	mtlr r0
/* 80220A9C 0021D67C  4E 80 00 20 */	blr 
/* 80220AA0 0021D680  38 60 00 00 */	li r3, 0
/* 80220AA4 0021D684  4E 80 00 20 */	blr 
/* 80220AA8 0021D688  7C 08 02 A6 */	mflr r0
/* 80220AAC 0021D68C  90 01 00 04 */	stw r0, 4(r1)
/* 80220AB0 0021D690  94 21 FF F8 */	stwu r1, -8(r1)
/* 80220AB4 0021D694  4B FA 25 2D */	bl func_801C2FE0
/* 80220AB8 0021D698  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80220ABC 0021D69C  38 21 00 08 */	addi r1, r1, 8
/* 80220AC0 0021D6A0  7C 08 03 A6 */	mtlr r0
/* 80220AC4 0021D6A4  4E 80 00 20 */	blr 
/* 80220AC8 0021D6A8  4E 80 00 20 */	blr 
/* 80220ACC 0021D6AC  7C 08 02 A6 */	mflr r0
/* 80220AD0 0021D6B0  90 01 00 04 */	stw r0, 4(r1)
/* 80220AD4 0021D6B4  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80220AD8 0021D6B8  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80220ADC 0021D6BC  3B E3 00 00 */	addi r31, r3, 0
/* 80220AE0 0021D6C0  2C 1F FF FF */	cmpwi r31, -1
/* 80220AE4 0021D6C4  41 82 00 7C */	beq lbl_80220B60
/* 80220AE8 0021D6C8  7F E3 FB 78 */	mr r3, r31
/* 80220AEC 0021D6CC  4B E3 60 81 */	bl func_80056B6C
/* 80220AF0 0021D6D0  2C 03 FF FF */	cmpwi r3, -1
/* 80220AF4 0021D6D4  41 82 00 6C */	beq lbl_80220B60
/* 80220AF8 0021D6D8  2C 03 00 00 */	cmpwi r3, 0
/* 80220AFC 0021D6DC  40 82 00 64 */	bne lbl_80220B60
/* 80220B00 0021D6E0  7F E3 FB 78 */	mr r3, r31
/* 80220B04 0021D6E4  4B E3 41 69 */	bl func_80054C6C
/* 80220B08 0021D6E8  2C 03 00 01 */	cmpwi r3, 1
/* 80220B0C 0021D6EC  40 82 00 10 */	bne lbl_80220B1C
/* 80220B10 0021D6F0  80 6D B4 58 */	lwz r3, lbl_804D6AF8@sda21(r13)
/* 80220B14 0021D6F4  80 63 00 00 */	lwz r3, 0(r3)
/* 80220B18 0021D6F8  48 00 00 4C */	b lbl_80220B64
lbl_80220B1C:
/* 80220B1C 0021D6FC  2C 03 00 02 */	cmpwi r3, 2
/* 80220B20 0021D700  40 82 00 10 */	bne lbl_80220B30
/* 80220B24 0021D704  80 6D B4 58 */	lwz r3, lbl_804D6AF8@sda21(r13)
/* 80220B28 0021D708  80 63 00 04 */	lwz r3, 4(r3)
/* 80220B2C 0021D70C  48 00 00 38 */	b lbl_80220B64
lbl_80220B30:
/* 80220B30 0021D710  2C 03 00 04 */	cmpwi r3, 4
/* 80220B34 0021D714  40 82 00 10 */	bne lbl_80220B44
/* 80220B38 0021D718  80 6D B4 58 */	lwz r3, lbl_804D6AF8@sda21(r13)
/* 80220B3C 0021D71C  80 63 00 08 */	lwz r3, 8(r3)
/* 80220B40 0021D720  48 00 00 24 */	b lbl_80220B64
lbl_80220B44:
/* 80220B44 0021D724  2C 03 00 08 */	cmpwi r3, 8
/* 80220B48 0021D728  40 82 00 10 */	bne lbl_80220B58
/* 80220B4C 0021D72C  80 6D B4 58 */	lwz r3, lbl_804D6AF8@sda21(r13)
/* 80220B50 0021D730  80 63 00 0C */	lwz r3, 0xc(r3)
/* 80220B54 0021D734  48 00 00 10 */	b lbl_80220B64
lbl_80220B58:
/* 80220B58 0021D738  38 60 00 00 */	li r3, 0
/* 80220B5C 0021D73C  48 00 00 08 */	b lbl_80220B64
lbl_80220B60:
/* 80220B60 0021D740  38 60 00 00 */	li r3, 0
lbl_80220B64:
/* 80220B64 0021D744  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80220B68 0021D748  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80220B6C 0021D74C  38 21 00 18 */	addi r1, r1, 0x18
/* 80220B70 0021D750  7C 08 03 A6 */	mtlr r0
/* 80220B74 0021D754  4E 80 00 20 */	blr 
/* 80220B78 0021D758  38 60 00 01 */	li r3, 1
/* 80220B7C 0021D75C  4E 80 00 20 */	blr 
