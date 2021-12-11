.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

.global func_8022192C
func_8022192C:
/* 8022192C 0021E50C  4E 80 00 20 */	blr 
.global lbl_80221930
lbl_80221930:
/* 80221930 0021E510  7C 08 02 A6 */	mflr r0
/* 80221934 0021E514  3C 60 80 4A */	lis r3, stage_info@ha
/* 80221938 0021E518  90 01 00 04 */	stw r0, 4(r1)
/* 8022193C 0021E51C  38 63 E6 C8 */	addi r3, r3, stage_info@l
/* 80221940 0021E520  38 A3 00 8C */	addi r5, r3, 0x8c
/* 80221944 0021E524  94 21 FF F8 */	stwu r1, -8(r1)
/* 80221948 0021E528  38 80 00 01 */	li r4, 1
/* 8022194C 0021E52C  88 03 00 8C */	lbz r0, 0x8c(r3)
/* 80221950 0021E530  38 60 00 00 */	li r3, 0
/* 80221954 0021E534  50 60 1F 38 */	rlwimi r0, r3, 3, 0x1c, 0x1c
/* 80221958 0021E538  98 05 00 00 */	stb r0, 0(r5)
/* 8022195C 0021E53C  38 60 00 00 */	li r3, 0
/* 80221960 0021E540  88 05 00 00 */	lbz r0, 0(r5)
/* 80221964 0021E544  50 80 17 7A */	rlwimi r0, r4, 2, 0x1d, 0x1d
/* 80221968 0021E548  98 05 00 00 */	stb r0, 0(r5)
/* 8022196C 0021E54C  48 00 00 65 */	bl func_802219D0
/* 80221970 0021E550  38 60 00 01 */	li r3, 1
/* 80221974 0021E554  48 00 00 5D */	bl func_802219D0
/* 80221978 0021E558  38 60 00 02 */	li r3, 2
/* 8022197C 0021E55C  48 00 00 55 */	bl func_802219D0
/* 80221980 0021E560  4B FA 20 41 */	bl func_801C39C0
/* 80221984 0021E564  4B FA 22 31 */	bl func_801C3BB4
/* 80221988 0021E568  4B FA 28 89 */	bl func_801C4210
/* 8022198C 0021E56C  4B FA 29 21 */	bl func_801C42AC
/* 80221990 0021E570  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80221994 0021E574  38 21 00 08 */	addi r1, r1, 8
/* 80221998 0021E578  7C 08 03 A6 */	mtlr r0
/* 8022199C 0021E57C  4E 80 00 20 */	blr 
.global lbl_802219A0
lbl_802219A0:
/* 802219A0 0021E580  4E 80 00 20 */	blr 
.global lbl_802219A4
lbl_802219A4:
/* 802219A4 0021E584  7C 08 02 A6 */	mflr r0
/* 802219A8 0021E588  38 60 00 00 */	li r3, 0
/* 802219AC 0021E58C  90 01 00 04 */	stw r0, 4(r1)
/* 802219B0 0021E590  94 21 FF F8 */	stwu r1, -8(r1)
/* 802219B4 0021E594  4B FA 94 51 */	bl func_801CAE04
/* 802219B8 0021E598  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802219BC 0021E59C  38 21 00 08 */	addi r1, r1, 8
/* 802219C0 0021E5A0  7C 08 03 A6 */	mtlr r0
/* 802219C4 0021E5A4  4E 80 00 20 */	blr 
.global lbl_802219C8
lbl_802219C8:
/* 802219C8 0021E5A8  38 60 00 00 */	li r3, 0
/* 802219CC 0021E5AC  4E 80 00 20 */	blr 

.global func_802219D0
func_802219D0:
/* 802219D0 0021E5B0  7C 08 02 A6 */	mflr r0
/* 802219D4 0021E5B4  90 01 00 04 */	stw r0, 4(r1)
/* 802219D8 0021E5B8  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 802219DC 0021E5BC  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 802219E0 0021E5C0  93 C1 00 18 */	stw r30, 0x18(r1)
/* 802219E4 0021E5C4  93 A1 00 14 */	stw r29, 0x14(r1)
/* 802219E8 0021E5C8  93 81 00 10 */	stw r28, 0x10(r1)
/* 802219EC 0021E5CC  3B 83 00 00 */	addi r28, r3, 0
/* 802219F0 0021E5D0  1C 1C 00 14 */	mulli r0, r28, 0x14
/* 802219F4 0021E5D4  3C 60 80 3F */	lis r3, lbl_803E8D30@ha
/* 802219F8 0021E5D8  3B E3 8D 30 */	addi r31, r3, lbl_803E8D30@l
/* 802219FC 0021E5DC  38 7C 00 00 */	addi r3, r28, 0
/* 80221A00 0021E5E0  7F BF 02 14 */	add r29, r31, r0
/* 80221A04 0021E5E4  4B F9 FA CD */	bl func_801C14D0
/* 80221A08 0021E5E8  7C 7E 1B 79 */	or. r30, r3, r3
/* 80221A0C 0021E5EC  41 82 00 70 */	beq lbl_80221A7C
/* 80221A10 0021E5F0  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 80221A14 0021E5F4  38 00 00 00 */	li r0, 0
/* 80221A18 0021E5F8  3C 60 80 1C */	lis r3, func_801C5DB0@ha
/* 80221A1C 0021E5FC  90 1F 00 08 */	stw r0, 8(r31)
/* 80221A20 0021E600  38 83 5D B0 */	addi r4, r3, func_801C5DB0@l
/* 80221A24 0021E604  38 7E 00 00 */	addi r3, r30, 0
/* 80221A28 0021E608  90 1F 00 0C */	stw r0, 0xc(r31)
/* 80221A2C 0021E60C  38 A0 00 03 */	li r5, 3
/* 80221A30 0021E610  38 C0 00 00 */	li r6, 0
/* 80221A34 0021E614  48 16 EC 69 */	bl func_8039069C
/* 80221A38 0021E618  80 1D 00 0C */	lwz r0, 0xc(r29)
/* 80221A3C 0021E61C  28 00 00 00 */	cmplwi r0, 0
/* 80221A40 0021E620  41 82 00 08 */	beq lbl_80221A48
/* 80221A44 0021E624  90 1F 00 1C */	stw r0, 0x1c(r31)
lbl_80221A48:
/* 80221A48 0021E628  81 9D 00 00 */	lwz r12, 0(r29)
/* 80221A4C 0021E62C  28 0C 00 00 */	cmplwi r12, 0
/* 80221A50 0021E630  41 82 00 10 */	beq lbl_80221A60
/* 80221A54 0021E634  7D 88 03 A6 */	mtlr r12
/* 80221A58 0021E638  38 7E 00 00 */	addi r3, r30, 0
/* 80221A5C 0021E63C  4E 80 00 21 */	blrl 
lbl_80221A60:
/* 80221A60 0021E640  80 9D 00 08 */	lwz r4, 8(r29)
/* 80221A64 0021E644  28 04 00 00 */	cmplwi r4, 0
/* 80221A68 0021E648  41 82 00 2C */	beq lbl_80221A94
/* 80221A6C 0021E64C  38 7E 00 00 */	addi r3, r30, 0
/* 80221A70 0021E650  38 A0 00 04 */	li r5, 4
/* 80221A74 0021E654  48 16 E2 E1 */	bl func_8038FD54
/* 80221A78 0021E658  48 00 00 1C */	b lbl_80221A94
lbl_80221A7C:
/* 80221A7C 0021E65C  38 DC 00 00 */	addi r6, r28, 0
/* 80221A80 0021E660  4C C6 31 82 */	crclr 6
/* 80221A84 0021E664  38 7F 00 90 */	addi r3, r31, 0x90
/* 80221A88 0021E668  38 9F 00 B4 */	addi r4, r31, 0xb4
/* 80221A8C 0021E66C  38 A0 00 C3 */	li r5, 0xc3
/* 80221A90 0021E670  48 12 3C 19 */	bl OSReport
lbl_80221A94:
/* 80221A94 0021E674  7F C3 F3 78 */	mr r3, r30
/* 80221A98 0021E678  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80221A9C 0021E67C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80221AA0 0021E680  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80221AA4 0021E684  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 80221AA8 0021E688  83 81 00 10 */	lwz r28, 0x10(r1)
/* 80221AAC 0021E68C  38 21 00 20 */	addi r1, r1, 0x20
/* 80221AB0 0021E690  7C 08 03 A6 */	mtlr r0
/* 80221AB4 0021E694  4E 80 00 20 */	blr 
.global lbl_80221AB8
lbl_80221AB8:
/* 80221AB8 0021E698  7C 08 02 A6 */	mflr r0
/* 80221ABC 0021E69C  38 A0 00 00 */	li r5, 0
/* 80221AC0 0021E6A0  90 01 00 04 */	stw r0, 4(r1)
/* 80221AC4 0021E6A4  94 21 FF F8 */	stwu r1, -8(r1)
/* 80221AC8 0021E6A8  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 80221ACC 0021E6AC  80 84 00 14 */	lwz r4, 0x14(r4)
/* 80221AD0 0021E6B0  4B FA 66 69 */	bl func_801C8138
/* 80221AD4 0021E6B4  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80221AD8 0021E6B8  38 21 00 08 */	addi r1, r1, 8
/* 80221ADC 0021E6BC  7C 08 03 A6 */	mtlr r0
/* 80221AE0 0021E6C0  4E 80 00 20 */	blr 
.global lbl_80221AE4
lbl_80221AE4:
/* 80221AE4 0021E6C4  38 60 00 00 */	li r3, 0
/* 80221AE8 0021E6C8  4E 80 00 20 */	blr 
.global lbl_80221AEC
lbl_80221AEC:
/* 80221AEC 0021E6CC  4E 80 00 20 */	blr 
.global lbl_80221AF0
lbl_80221AF0:
/* 80221AF0 0021E6D0  4E 80 00 20 */	blr 
.global lbl_80221AF4
lbl_80221AF4:
/* 80221AF4 0021E6D4  7C 08 02 A6 */	mflr r0
/* 80221AF8 0021E6D8  90 01 00 04 */	stw r0, 4(r1)
/* 80221AFC 0021E6DC  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80221B00 0021E6E0  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80221B04 0021E6E4  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80221B08 0021E6E8  7C 7E 1B 78 */	mr r30, r3
/* 80221B0C 0021E6EC  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80221B10 0021E6F0  80 63 00 28 */	lwz r3, 0x28(r3)
/* 80221B14 0021E6F4  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80221B18 0021E6F8  4B FA 13 B9 */	bl func_801C2ED0
/* 80221B1C 0021E6FC  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80221B20 0021E700  38 7E 00 00 */	addi r3, r30, 0
/* 80221B24 0021E704  38 A0 00 00 */	li r5, 0
/* 80221B28 0021E708  4B FA 66 11 */	bl func_801C8138
/* 80221B2C 0021E70C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80221B30 0021E710  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80221B34 0021E714  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80221B38 0021E718  38 21 00 20 */	addi r1, r1, 0x20
/* 80221B3C 0021E71C  7C 08 03 A6 */	mtlr r0
/* 80221B40 0021E720  4E 80 00 20 */	blr 
.global lbl_80221B44
lbl_80221B44:
/* 80221B44 0021E724  38 60 00 00 */	li r3, 0
/* 80221B48 0021E728  4E 80 00 20 */	blr 
.global lbl_80221B4C
lbl_80221B4C:
/* 80221B4C 0021E72C  7C 08 02 A6 */	mflr r0
/* 80221B50 0021E730  90 01 00 04 */	stw r0, 4(r1)
/* 80221B54 0021E734  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80221B58 0021E738  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80221B5C 0021E73C  7C 7F 1B 78 */	mr r31, r3
/* 80221B60 0021E740  4B DE FA 95 */	bl func_800115F4
/* 80221B64 0021E744  7F E3 FB 78 */	mr r3, r31
/* 80221B68 0021E748  4B FA 14 79 */	bl func_801C2FE0
/* 80221B6C 0021E74C  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80221B70 0021E750  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80221B74 0021E754  38 21 00 18 */	addi r1, r1, 0x18
/* 80221B78 0021E758  7C 08 03 A6 */	mtlr r0
/* 80221B7C 0021E75C  4E 80 00 20 */	blr 
.global lbl_80221B80
lbl_80221B80:
/* 80221B80 0021E760  4E 80 00 20 */	blr 
.global lbl_80221B84
lbl_80221B84:
/* 80221B84 0021E764  7C 08 02 A6 */	mflr r0
/* 80221B88 0021E768  90 01 00 04 */	stw r0, 4(r1)
/* 80221B8C 0021E76C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80221B90 0021E770  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80221B94 0021E774  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80221B98 0021E778  7C 7E 1B 78 */	mr r30, r3
/* 80221B9C 0021E77C  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80221BA0 0021E780  80 63 00 28 */	lwz r3, 0x28(r3)
/* 80221BA4 0021E784  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80221BA8 0021E788  4B FA 13 29 */	bl func_801C2ED0
/* 80221BAC 0021E78C  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80221BB0 0021E790  38 7E 00 00 */	addi r3, r30, 0
/* 80221BB4 0021E794  38 A0 00 00 */	li r5, 0
/* 80221BB8 0021E798  4B FA 65 81 */	bl func_801C8138
/* 80221BBC 0021E79C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80221BC0 0021E7A0  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80221BC4 0021E7A4  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80221BC8 0021E7A8  38 21 00 20 */	addi r1, r1, 0x20
/* 80221BCC 0021E7AC  7C 08 03 A6 */	mtlr r0
/* 80221BD0 0021E7B0  4E 80 00 20 */	blr 
.global lbl_80221BD4
lbl_80221BD4:
/* 80221BD4 0021E7B4  38 60 00 00 */	li r3, 0
/* 80221BD8 0021E7B8  4E 80 00 20 */	blr 
.global lbl_80221BDC
lbl_80221BDC:
/* 80221BDC 0021E7BC  7C 08 02 A6 */	mflr r0
/* 80221BE0 0021E7C0  90 01 00 04 */	stw r0, 4(r1)
/* 80221BE4 0021E7C4  94 21 FF F8 */	stwu r1, -8(r1)
/* 80221BE8 0021E7C8  4B FA 13 F9 */	bl func_801C2FE0
/* 80221BEC 0021E7CC  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80221BF0 0021E7D0  38 21 00 08 */	addi r1, r1, 8
/* 80221BF4 0021E7D4  7C 08 03 A6 */	mtlr r0
/* 80221BF8 0021E7D8  4E 80 00 20 */	blr 
.global lbl_80221BFC
lbl_80221BFC:
/* 80221BFC 0021E7DC  4E 80 00 20 */	blr 
.global lbl_80221C00
lbl_80221C00:
/* 80221C00 0021E7E0  38 60 00 00 */	li r3, 0
/* 80221C04 0021E7E4  4E 80 00 20 */	blr 
.global lbl_80221C08
lbl_80221C08:
/* 80221C08 0021E7E8  38 60 00 01 */	li r3, 1
/* 80221C0C 0021E7EC  4E 80 00 20 */	blr 
