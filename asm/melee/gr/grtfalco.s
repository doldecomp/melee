.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

.global lbl_80220AA0
lbl_80220AA0:
/* 80220AA0 0021D680  38 60 00 00 */	li r3, 0
/* 80220AA4 0021D684  4E 80 00 20 */	blr

.global lbl_80220AA8
lbl_80220AA8:
/* 80220AA8 0021D688  7C 08 02 A6 */	mflr r0
/* 80220AAC 0021D68C  90 01 00 04 */	stw r0, 4(r1)
/* 80220AB0 0021D690  94 21 FF F8 */	stwu r1, -8(r1)
/* 80220AB4 0021D694  4B FA 25 2D */	bl func_801C2FE0
/* 80220AB8 0021D698  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80220ABC 0021D69C  38 21 00 08 */	addi r1, r1, 8
/* 80220AC0 0021D6A0  7C 08 03 A6 */	mtlr r0
/* 80220AC4 0021D6A4  4E 80 00 20 */	blr

.global lbl_80220AC8
lbl_80220AC8:
/* 80220AC8 0021D6A8  4E 80 00 20 */	blr

.global lbl_80220ACC
lbl_80220ACC:
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

.global lbl_80220B78
lbl_80220B78:
/* 80220B78 0021D758  38 60 00 01 */	li r3, 1
/* 80220B7C 0021D75C  4E 80 00 20 */	blr
