.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

.global lbl_80221E64
lbl_80221E64:
/* 80221E64 0021EA44  4E 80 00 20 */	blr

.global lbl_80221E68
lbl_80221E68:
/* 80221E68 0021EA48  7C 08 02 A6 */	mflr r0
/* 80221E6C 0021EA4C  90 01 00 04 */	stw r0, 4(r1)
/* 80221E70 0021EA50  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80221E74 0021EA54  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80221E78 0021EA58  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80221E7C 0021EA5C  7C 7E 1B 78 */	mr r30, r3
/* 80221E80 0021EA60  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80221E84 0021EA64  80 63 00 28 */	lwz r3, 0x28(r3)
/* 80221E88 0021EA68  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80221E8C 0021EA6C  4B FA 10 45 */	bl func_801C2ED0
/* 80221E90 0021EA70  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80221E94 0021EA74  38 7E 00 00 */	addi r3, r30, 0
/* 80221E98 0021EA78  38 A0 00 00 */	li r5, 0
/* 80221E9C 0021EA7C  4B FA 62 9D */	bl func_801C8138
/* 80221EA0 0021EA80  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80221EA4 0021EA84  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80221EA8 0021EA88  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80221EAC 0021EA8C  38 21 00 20 */	addi r1, r1, 0x20
/* 80221EB0 0021EA90  7C 08 03 A6 */	mtlr r0
/* 80221EB4 0021EA94  4E 80 00 20 */	blr

.global lbl_80221EB8
lbl_80221EB8:
/* 80221EB8 0021EA98  38 60 00 00 */	li r3, 0
/* 80221EBC 0021EA9C  4E 80 00 20 */	blr

.global lbl_80221EC0
lbl_80221EC0:
/* 80221EC0 0021EAA0  7C 08 02 A6 */	mflr r0
/* 80221EC4 0021EAA4  90 01 00 04 */	stw r0, 4(r1)
/* 80221EC8 0021EAA8  94 21 FF F8 */	stwu r1, -8(r1)
/* 80221ECC 0021EAAC  4B FA 11 15 */	bl func_801C2FE0
/* 80221ED0 0021EAB0  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80221ED4 0021EAB4  38 21 00 08 */	addi r1, r1, 8
/* 80221ED8 0021EAB8  7C 08 03 A6 */	mtlr r0
/* 80221EDC 0021EABC  4E 80 00 20 */	blr

.global lbl_80221EE0
lbl_80221EE0:
/* 80221EE0 0021EAC0  4E 80 00 20 */	blr

.global lbl_80221EE4
lbl_80221EE4:
/* 80221EE4 0021EAC4  38 60 00 00 */	li r3, 0
/* 80221EE8 0021EAC8  4E 80 00 20 */	blr

.global lbl_80221EEC
lbl_80221EEC:
/* 80221EEC 0021EACC  38 60 00 01 */	li r3, 1
/* 80221EF0 0021EAD0  4E 80 00 20 */	blr


