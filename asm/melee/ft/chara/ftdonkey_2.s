.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

.global ftDonkey_8010FCD4
ftDonkey_8010FCD4:
/* 8010FCD4 0010C8B4  7C 08 02 A6 */	mflr r0
/* 8010FCD8 0010C8B8  90 01 00 04 */	stw r0, 4(r1)
/* 8010FCDC 0010C8BC  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8010FCE0 0010C8C0  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8010FCE4 0010C8C4  7C 7F 1B 78 */	mr r31, r3
/* 8010FCE8 0010C8C8  4B F5 F5 51 */	bl ftAnim_IsFramesRemaining
/* 8010FCEC 0010C8CC  2C 03 00 00 */	cmpwi r3, 0
/* 8010FCF0 0010C8D0  40 82 00 0C */	bne lbl_8010FCFC
/* 8010FCF4 0010C8D4  7F E3 FB 78 */	mr r3, r31
/* 8010FCF8 0010C8D8  4B F7 A5 C5 */	bl func_8008A2BC
lbl_8010FCFC:
/* 8010FCFC 0010C8DC  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8010FD00 0010C8E0  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8010FD04 0010C8E4  38 21 00 18 */	addi r1, r1, 0x18
/* 8010FD08 0010C8E8  7C 08 03 A6 */	mtlr r0
/* 8010FD0C 0010C8EC  4E 80 00 20 */	blr 

.global ftDonkey_8010FD10
ftDonkey_8010FD10:
/* 8010FD10 0010C8F0  7C 08 02 A6 */	mflr r0
/* 8010FD14 0010C8F4  90 01 00 04 */	stw r0, 4(r1)
/* 8010FD18 0010C8F8  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8010FD1C 0010C8FC  93 E1 00 24 */	stw r31, 0x24(r1)
/* 8010FD20 0010C900  93 C1 00 20 */	stw r30, 0x20(r1)
/* 8010FD24 0010C904  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 8010FD28 0010C908  7C 7D 1B 78 */	mr r29, r3
/* 8010FD2C 0010C90C  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 8010FD30 0010C910  83 C4 02 D4 */	lwz r30, 0x2d4(r4)
/* 8010FD34 0010C914  7C 9F 23 78 */	mr r31, r4
/* 8010FD38 0010C918  4B F5 F5 01 */	bl ftAnim_IsFramesRemaining
/* 8010FD3C 0010C91C  2C 03 00 00 */	cmpwi r3, 0
/* 8010FD40 0010C920  40 82 00 40 */	bne lbl_8010FD80
/* 8010FD44 0010C924  7F E3 FB 78 */	mr r3, r31
/* 8010FD48 0010C928  4B F6 D8 C5 */	bl func_8007D60C
/* 8010FD4C 0010C92C  C0 02 9C 08 */	lfs f0, lbl_804D95E8@sda21(r2)
/* 8010FD50 0010C930  C0 5E 00 64 */	lfs f2, 0x64(r30)
/* 8010FD54 0010C934  FC 00 10 00 */	fcmpu cr0, f0, f2
/* 8010FD58 0010C938  40 82 00 10 */	bne lbl_8010FD68
/* 8010FD5C 0010C93C  7F A3 EB 78 */	mr r3, r29
/* 8010FD60 0010C940  4B FB C9 D1 */	bl func_800CC730
/* 8010FD64 0010C944  48 00 00 1C */	b lbl_8010FD80
lbl_8010FD68:
/* 8010FD68 0010C948  C0 22 9C 0C */	lfs f1, lbl_804D95EC@sda21(r2)
/* 8010FD6C 0010C94C  38 7D 00 00 */	addi r3, r29, 0
/* 8010FD70 0010C950  38 80 00 01 */	li r4, 1
/* 8010FD74 0010C954  38 A0 00 00 */	li r5, 0
/* 8010FD78 0010C958  38 C0 00 01 */	li r6, 1
/* 8010FD7C 0010C95C  4B F8 6B 85 */	bl func_80096900
lbl_8010FD80:
/* 8010FD80 0010C960  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8010FD84 0010C964  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 8010FD88 0010C968  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 8010FD8C 0010C96C  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 8010FD90 0010C970  38 21 00 28 */	addi r1, r1, 0x28
/* 8010FD94 0010C974  7C 08 03 A6 */	mtlr r0
/* 8010FD98 0010C978  4E 80 00 20 */	blr 
.global lbl_8010FD9C
lbl_8010FD9C:
/* 8010FD9C 0010C97C  4E 80 00 20 */	blr 
.global lbl_8010FDA0
lbl_8010FDA0:
/* 8010FDA0 0010C980  4E 80 00 20 */	blr 
.global lbl_8010FDA4
lbl_8010FDA4:
/* 8010FDA4 0010C984  7C 08 02 A6 */	mflr r0
/* 8010FDA8 0010C988  90 01 00 04 */	stw r0, 4(r1)
/* 8010FDAC 0010C98C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8010FDB0 0010C990  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8010FDB4 0010C994  7C 7F 1B 78 */	mr r31, r3
/* 8010FDB8 0010C998  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8010FDBC 0010C99C  C0 22 9C 08 */	lfs f1, lbl_804D95E8@sda21(r2)
/* 8010FDC0 0010C9A0  80 83 02 D4 */	lwz r4, 0x2d4(r3)
/* 8010FDC4 0010C9A4  C0 44 00 5C */	lfs f2, 0x5c(r4)
/* 8010FDC8 0010C9A8  C0 64 00 54 */	lfs f3, 0x54(r4)
/* 8010FDCC 0010C9AC  4B F6 CD 11 */	bl func_8007CADC
/* 8010FDD0 0010C9B0  7F E3 FB 78 */	mr r3, r31
/* 8010FDD4 0010C9B4  4B F6 CD A1 */	bl func_8007CB74
/* 8010FDD8 0010C9B8  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8010FDDC 0010C9BC  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8010FDE0 0010C9C0  38 21 00 20 */	addi r1, r1, 0x20
/* 8010FDE4 0010C9C4  7C 08 03 A6 */	mtlr r0
/* 8010FDE8 0010C9C8  4E 80 00 20 */	blr 
.global lbl_8010FDEC
lbl_8010FDEC:
/* 8010FDEC 0010C9CC  7C 08 02 A6 */	mflr r0
/* 8010FDF0 0010C9D0  90 01 00 04 */	stw r0, 4(r1)
/* 8010FDF4 0010C9D4  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8010FDF8 0010C9D8  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8010FDFC 0010C9DC  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8010FE00 0010C9E0  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8010FE04 0010C9E4  80 1F 22 00 */	lwz r0, 0x2200(r31)
/* 8010FE08 0010C9E8  83 DF 02 D4 */	lwz r30, 0x2d4(r31)
/* 8010FE0C 0010C9EC  28 00 00 00 */	cmplwi r0, 0
/* 8010FE10 0010C9F0  41 82 00 0C */	beq lbl_8010FE1C
/* 8010FE14 0010C9F4  C0 22 9C 0C */	lfs f1, lbl_804D95EC@sda21(r2)
/* 8010FE18 0010C9F8  48 00 00 08 */	b lbl_8010FE20
lbl_8010FE1C:
/* 8010FE1C 0010C9FC  C0 3E 00 50 */	lfs f1, 0x50(r30)
lbl_8010FE20:
/* 8010FE20 0010CA00  C0 1F 01 6C */	lfs f0, 0x16c(r31)
/* 8010FE24 0010CA04  7F E3 FB 78 */	mr r3, r31
/* 8010FE28 0010CA08  C0 5F 01 70 */	lfs f2, 0x170(r31)
/* 8010FE2C 0010CA0C  EC 21 00 32 */	fmuls f1, f1, f0
/* 8010FE30 0010CA10  4B F6 D6 65 */	bl func_8007D494
/* 8010FE34 0010CA14  C0 22 9C 08 */	lfs f1, lbl_804D95E8@sda21(r2)
/* 8010FE38 0010CA18  7F E3 FB 78 */	mr r3, r31
/* 8010FE3C 0010CA1C  C0 5E 00 60 */	lfs f2, 0x60(r30)
/* 8010FE40 0010CA20  C0 7E 00 58 */	lfs f3, 0x58(r30)
/* 8010FE44 0010CA24  4B F6 D5 01 */	bl func_8007D344
/* 8010FE48 0010CA28  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8010FE4C 0010CA2C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8010FE50 0010CA30  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8010FE54 0010CA34  38 21 00 20 */	addi r1, r1, 0x20
/* 8010FE58 0010CA38  7C 08 03 A6 */	mtlr r0
/* 8010FE5C 0010CA3C  4E 80 00 20 */	blr 
.global lbl_8010FE60
lbl_8010FE60:
/* 8010FE60 0010CA40  7C 08 02 A6 */	mflr r0
/* 8010FE64 0010CA44  90 01 00 04 */	stw r0, 4(r1)
/* 8010FE68 0010CA48  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8010FE6C 0010CA4C  93 E1 00 24 */	stw r31, 0x24(r1)
/* 8010FE70 0010CA50  93 C1 00 20 */	stw r30, 0x20(r1)
/* 8010FE74 0010CA54  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 8010FE78 0010CA58  7C 7D 1B 78 */	mr r29, r3
/* 8010FE7C 0010CA5C  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 8010FE80 0010CA60  83 C4 02 D4 */	lwz r30, 0x2d4(r4)
/* 8010FE84 0010CA64  7C 9F 23 78 */	mr r31, r4
/* 8010FE88 0010CA68  4B F7 28 81 */	bl func_80082708
/* 8010FE8C 0010CA6C  2C 03 00 00 */	cmpwi r3, 0
/* 8010FE90 0010CA70  40 82 00 68 */	bne lbl_8010FEF8
/* 8010FE94 0010CA74  7F E3 FB 78 */	mr r3, r31
/* 8010FE98 0010CA78  4B F6 D7 75 */	bl func_8007D60C
/* 8010FE9C 0010CA7C  3C 80 0C 4C */	lis r4, 0x0C4C5080@ha
/* 8010FEA0 0010CA80  C0 3F 08 94 */	lfs f1, 0x894(r31)
/* 8010FEA4 0010CA84  C0 42 9C 0C */	lfs f2, lbl_804D95EC@sda21(r2)
/* 8010FEA8 0010CA88  7F A3 EB 78 */	mr r3, r29
/* 8010FEAC 0010CA8C  C0 62 9C 08 */	lfs f3, lbl_804D95E8@sda21(r2)
/* 8010FEB0 0010CA90  38 A4 50 80 */	addi r5, r4, 0x0C4C5080@l
/* 8010FEB4 0010CA94  38 80 01 7E */	li r4, 0x17e
/* 8010FEB8 0010CA98  38 C0 00 00 */	li r6, 0
/* 8010FEBC 0010CA9C  4B F5 94 F1 */	bl Fighter_ActionStateChange_800693AC
/* 8010FEC0 0010CAA0  3C 60 80 11 */	lis r3, ftDonkey_8010D774@ha
/* 8010FEC4 0010CAA4  80 BD 00 2C */	lwz r5, 0x2c(r29)
/* 8010FEC8 0010CAA8  38 03 D7 74 */	addi r0, r3, ftDonkey_8010D774@l
/* 8010FECC 0010CAAC  90 05 21 DC */	stw r0, 0x21dc(r5)
/* 8010FED0 0010CAB0  3C 80 80 06 */	lis r4, efLib_PauseAll@ha
/* 8010FED4 0010CAB4  3C 60 80 06 */	lis r3, efLib_ResumeAll@ha
/* 8010FED8 0010CAB8  90 05 21 E4 */	stw r0, 0x21e4(r5)
/* 8010FEDC 0010CABC  38 84 BA 40 */	addi r4, r4, efLib_PauseAll@l
/* 8010FEE0 0010CAC0  38 03 BA C4 */	addi r0, r3, efLib_ResumeAll@l
/* 8010FEE4 0010CAC4  90 85 21 D4 */	stw r4, 0x21d4(r5)
/* 8010FEE8 0010CAC8  7F E3 FB 78 */	mr r3, r31
/* 8010FEEC 0010CACC  90 05 21 D8 */	stw r0, 0x21d8(r5)
/* 8010FEF0 0010CAD0  C0 3E 00 58 */	lfs f1, 0x58(r30)
/* 8010FEF4 0010CAD4  4B F6 D5 4D */	bl func_8007D440
lbl_8010FEF8:
/* 8010FEF8 0010CAD8  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8010FEFC 0010CADC  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 8010FF00 0010CAE0  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 8010FF04 0010CAE4  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 8010FF08 0010CAE8  38 21 00 28 */	addi r1, r1, 0x28
/* 8010FF0C 0010CAEC  7C 08 03 A6 */	mtlr r0
/* 8010FF10 0010CAF0  4E 80 00 20 */	blr 
.global lbl_8010FF14
lbl_8010FF14:
/* 8010FF14 0010CAF4  7C 08 02 A6 */	mflr r0
/* 8010FF18 0010CAF8  90 01 00 04 */	stw r0, 4(r1)
/* 8010FF1C 0010CAFC  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8010FF20 0010CB00  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 8010FF24 0010CB04  93 C1 00 28 */	stw r30, 0x28(r1)
/* 8010FF28 0010CB08  93 A1 00 24 */	stw r29, 0x24(r1)
/* 8010FF2C 0010CB0C  7C 7D 1B 78 */	mr r29, r3
/* 8010FF30 0010CB10  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8010FF34 0010CB14  C0 02 9C 08 */	lfs f0, lbl_804D95E8@sda21(r2)
/* 8010FF38 0010CB18  C0 3F 00 84 */	lfs f1, 0x84(r31)
/* 8010FF3C 0010CB1C  83 DF 02 D4 */	lwz r30, 0x2d4(r31)
/* 8010FF40 0010CB20  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8010FF44 0010CB24  4C 41 13 82 */	cror 2, 1, 2
/* 8010FF48 0010CB28  40 82 00 7C */	bne lbl_8010FFC4
/* 8010FF4C 0010CB2C  7F A3 EB 78 */	mr r3, r29
/* 8010FF50 0010CB30  4B F7 1D BD */	bl func_80081D0C
/* 8010FF54 0010CB34  2C 03 00 00 */	cmpwi r3, 0
/* 8010FF58 0010CB38  41 82 01 00 */	beq lbl_80110058
/* 8010FF5C 0010CB3C  7F E3 FB 78 */	mr r3, r31
/* 8010FF60 0010CB40  4B F6 D8 9D */	bl func_8007D7FC
/* 8010FF64 0010CB44  3C 80 0C 4C */	lis r4, 0x0C4C5080@ha
/* 8010FF68 0010CB48  C0 3F 08 94 */	lfs f1, 0x894(r31)
/* 8010FF6C 0010CB4C  C0 42 9C 0C */	lfs f2, lbl_804D95EC@sda21(r2)
/* 8010FF70 0010CB50  7F A3 EB 78 */	mr r3, r29
/* 8010FF74 0010CB54  C0 62 9C 08 */	lfs f3, lbl_804D95E8@sda21(r2)
/* 8010FF78 0010CB58  38 A4 50 80 */	addi r5, r4, 0x0C4C5080@l
/* 8010FF7C 0010CB5C  38 80 01 7D */	li r4, 0x17d
/* 8010FF80 0010CB60  38 C0 00 00 */	li r6, 0
/* 8010FF84 0010CB64  4B F5 94 29 */	bl Fighter_ActionStateChange_800693AC
/* 8010FF88 0010CB68  3C 60 80 11 */	lis r3, ftDonkey_8010D774@ha
/* 8010FF8C 0010CB6C  80 BD 00 2C */	lwz r5, 0x2c(r29)
/* 8010FF90 0010CB70  38 03 D7 74 */	addi r0, r3, ftDonkey_8010D774@l
/* 8010FF94 0010CB74  90 05 21 DC */	stw r0, 0x21dc(r5)
/* 8010FF98 0010CB78  3C 80 80 06 */	lis r4, efLib_PauseAll@ha
/* 8010FF9C 0010CB7C  3C 60 80 06 */	lis r3, efLib_ResumeAll@ha
/* 8010FFA0 0010CB80  90 05 21 E4 */	stw r0, 0x21e4(r5)
/* 8010FFA4 0010CB84  38 84 BA 40 */	addi r4, r4, efLib_PauseAll@l
/* 8010FFA8 0010CB88  38 03 BA C4 */	addi r0, r3, efLib_ResumeAll@l
/* 8010FFAC 0010CB8C  90 85 21 D4 */	stw r4, 0x21d4(r5)
/* 8010FFB0 0010CB90  7F E3 FB 78 */	mr r3, r31
/* 8010FFB4 0010CB94  90 05 21 D8 */	stw r0, 0x21d8(r5)
/* 8010FFB8 0010CB98  C0 3E 00 54 */	lfs f1, 0x54(r30)
/* 8010FFBC 0010CB9C  4B F6 CC BD */	bl func_8007CC78
/* 8010FFC0 0010CBA0  48 00 00 98 */	b lbl_80110058
lbl_8010FFC4:
/* 8010FFC4 0010CBA4  38 7D 00 00 */	addi r3, r29, 0
/* 8010FFC8 0010CBA8  38 80 00 00 */	li r4, 0
/* 8010FFCC 0010CBAC  4B F7 22 D9 */	bl EnvColl_CheckGroundAndLedge
/* 8010FFD0 0010CBB0  2C 03 00 00 */	cmpwi r3, 0
/* 8010FFD4 0010CBB4  41 82 00 6C */	beq lbl_80110040
/* 8010FFD8 0010CBB8  7F E3 FB 78 */	mr r3, r31
/* 8010FFDC 0010CBBC  4B F6 D8 21 */	bl func_8007D7FC
/* 8010FFE0 0010CBC0  3C 80 0C 4C */	lis r4, 0x0C4C5080@ha
/* 8010FFE4 0010CBC4  C0 3F 08 94 */	lfs f1, 0x894(r31)
/* 8010FFE8 0010CBC8  C0 42 9C 0C */	lfs f2, lbl_804D95EC@sda21(r2)
/* 8010FFEC 0010CBCC  7F A3 EB 78 */	mr r3, r29
/* 8010FFF0 0010CBD0  C0 62 9C 08 */	lfs f3, lbl_804D95E8@sda21(r2)
/* 8010FFF4 0010CBD4  38 A4 50 80 */	addi r5, r4, 0x0C4C5080@l
/* 8010FFF8 0010CBD8  38 80 01 7D */	li r4, 0x17d
/* 8010FFFC 0010CBDC  38 C0 00 00 */	li r6, 0
/* 80110000 0010CBE0  4B F5 93 AD */	bl Fighter_ActionStateChange_800693AC
/* 80110004 0010CBE4  3C 60 80 11 */	lis r3, ftDonkey_8010D774@ha
/* 80110008 0010CBE8  80 BD 00 2C */	lwz r5, 0x2c(r29)
/* 8011000C 0010CBEC  38 03 D7 74 */	addi r0, r3, ftDonkey_8010D774@l
/* 80110010 0010CBF0  90 05 21 DC */	stw r0, 0x21dc(r5)
/* 80110014 0010CBF4  3C 80 80 06 */	lis r4, efLib_PauseAll@ha
/* 80110018 0010CBF8  3C 60 80 06 */	lis r3, efLib_ResumeAll@ha
/* 8011001C 0010CBFC  90 05 21 E4 */	stw r0, 0x21e4(r5)
/* 80110020 0010CC00  38 84 BA 40 */	addi r4, r4, efLib_PauseAll@l
/* 80110024 0010CC04  38 03 BA C4 */	addi r0, r3, efLib_ResumeAll@l
/* 80110028 0010CC08  90 85 21 D4 */	stw r4, 0x21d4(r5)
/* 8011002C 0010CC0C  7F E3 FB 78 */	mr r3, r31
/* 80110030 0010CC10  90 05 21 D8 */	stw r0, 0x21d8(r5)
/* 80110034 0010CC14  C0 3E 00 54 */	lfs f1, 0x54(r30)
/* 80110038 0010CC18  4B F6 CC 41 */	bl func_8007CC78
/* 8011003C 0010CC1C  48 00 00 1C */	b lbl_80110058
lbl_80110040:
/* 80110040 0010CC20  7F A3 EB 78 */	mr r3, r29
/* 80110044 0010CC24  4B F7 12 55 */	bl func_80081298
/* 80110048 0010CC28  2C 03 00 00 */	cmpwi r3, 0
/* 8011004C 0010CC2C  41 82 00 0C */	beq lbl_80110058
/* 80110050 0010CC30  7F A3 EB 78 */	mr r3, r29
/* 80110054 0010CC34  4B F7 13 1D */	bl func_80081370
lbl_80110058:
/* 80110058 0010CC38  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8011005C 0010CC3C  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 80110060 0010CC40  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 80110064 0010CC44  83 A1 00 24 */	lwz r29, 0x24(r1)
/* 80110068 0010CC48  38 21 00 30 */	addi r1, r1, 0x30
/* 8011006C 0010CC4C  7C 08 03 A6 */	mtlr r0
/* 80110070 0010CC50  4E 80 00 20 */	blr 

.global func_80110074
func_80110074:
/* 80110074 0010CC54  7C 08 02 A6 */	mflr r0
/* 80110078 0010CC58  90 01 00 04 */	stw r0, 4(r1)
/* 8011007C 0010CC5C  94 21 FF F8 */	stwu r1, -8(r1)
/* 80110080 0010CC60  4B F4 B8 01 */	bl efLib_DestroyAll
/* 80110084 0010CC64  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80110088 0010CC68  38 21 00 08 */	addi r1, r1, 8
/* 8011008C 0010CC6C  7C 08 03 A6 */	mtlr r0
/* 80110090 0010CC70  4E 80 00 20 */	blr 


.section .data
    .balign 8
.global as_table_donkey
as_table_donkey:
    .4byte 0x00000127
    .4byte 0x00480000
    .4byte 0x35400000
    .4byte NULL
    .4byte func_800DF9F0
    .4byte func_800DFA50
    .4byte func_800DFA70
    .4byte func_800761C8
    .4byte 0x00000128
    .4byte 0x00484066
    .4byte 0x35000000
    .4byte func_800DFB34
    .4byte func_800DFB54
    .4byte func_800DFBB8
    .4byte func_800DFBD8
    .4byte func_800761C8
    .4byte 0x00000129
    .4byte 0x00484066
    .4byte 0x35000000
    .4byte func_800DFB34
    .4byte func_800DFB54
    .4byte func_800DFBB8
    .4byte func_800DFBD8
    .4byte func_800761C8
    .4byte 0x0000012A
    .4byte 0x00484066
    .4byte 0x35000000
    .4byte func_800DFB34
    .4byte func_800DFB54
    .4byte func_800DFBB8
    .4byte func_800DFBD8
    .4byte func_800761C8
    .4byte 0x0000012B
    .4byte 0x00482064
    .4byte 0x35000000
    .4byte func_800E01BC
    .4byte func_800E0200
    .4byte func_800E0254
    .4byte func_800E0274
    .4byte func_800761C8
    .4byte 0x0000012C
    .4byte 0x00480000
    .4byte 0x35000000
    .4byte func_800E0518
    .4byte func_800E0568
    .4byte func_800E05A4
    .4byte func_800E05C4
    .4byte func_800761C8
    .4byte 0x0000012D
    .4byte 0x00480000
    .4byte 0x35000000
    .4byte NULL
    .4byte func_800E030C
    .4byte func_800E0330
    .4byte func_800E0350
    .4byte func_800761C8
    .4byte 0x0000012E
    .4byte 0x00488069
    .4byte 0x35000000
    .4byte NULL
    .4byte func_800E0440
    .4byte func_800E0464
    .4byte func_800E0484
    .4byte func_800761C8
    .4byte 0x0000012F
    .4byte 0x00480000
    .4byte 0x35400000
    .4byte func_800E0648
    .4byte NULL
    .4byte func_800E0698
    .4byte func_800E06B8
    .4byte func_800761C8
    .4byte 0x00000130
    .4byte 0x004A0000
    .4byte 0x35000000
    .4byte func_800E07E4
    .4byte NULL
    .4byte func_800E0848
    .4byte func_800E0868
    .4byte func_800761C8
    .4byte 0x00000131
    .4byte 0x00A80035
    .4byte 0x35400000
    .4byte func_8009B5C0
    .4byte func_8009B5C4
    .4byte func_8009B634
    .4byte func_8009B654
    .4byte func_800761C8
    .4byte 0x00000132
    .4byte 0x00A84035
    .4byte 0x35000000
    .4byte func_8009B744
    .4byte func_8009B764
    .4byte func_8009B7D8
    .4byte func_8009B7F8
    .4byte func_800761C8
    .4byte 0x00000133
    .4byte 0x00A84035
    .4byte 0x35000000
    .4byte func_8009B744
    .4byte func_8009B764
    .4byte func_8009B7D8
    .4byte func_8009B7F8
    .4byte func_800761C8
    .4byte 0x00000134
    .4byte 0x00A84035
    .4byte 0x35000000
    .4byte func_8009B744
    .4byte func_8009B764
    .4byte func_8009B7D8
    .4byte func_8009B7F8
    .4byte func_800761C8
    .4byte 0x00000135
    .4byte 0x00A82035
    .4byte 0x35000000
    .4byte func_8009B8B4
    .4byte func_8009B948
    .4byte func_8009B988
    .4byte func_8009B9A8
    .4byte func_800761C8
    .4byte 0x00000136
    .4byte 0x00A80035
    .4byte 0x35000000
    .4byte func_8009BA50
    .4byte func_8009BAA0
    .4byte func_8009BADC
    .4byte func_8009BAFC
    .4byte func_800761C8
    .4byte 0x00000137
    .4byte 0x00A80035
    .4byte 0x35000000
    .4byte func_8009BCDC
    .4byte func_8009BCE0
    .4byte func_8009BD04
    .4byte func_8009BD24
    .4byte func_800761C8
    .4byte 0x00000138
    .4byte 0x00A88035
    .4byte 0x35000000
    .4byte func_8009BBF0
    .4byte func_8009BBF4
    .4byte func_8009BC18
    .4byte func_8009BC38
    .4byte func_800761C8
    .4byte 0x00000139
    .4byte 0x00A80035
    .4byte 0x35400000
    .4byte func_8009BDC4
    .4byte NULL
    .4byte func_8009BE14
    .4byte func_8009BE34
    .4byte func_800761C8
    .4byte 0x0000013A
    .4byte 0x00AA0035
    .4byte 0x35000000
    .4byte func_8009BE54
    .4byte NULL
    .4byte func_8009BEB8
    .4byte func_8009BED8
    .4byte func_800761C8
    .4byte 0x0000013B
    .4byte 0x00A40039
    .4byte 0x39000000
    .4byte func_8009C0EC
    .4byte func_8009C130
    .4byte func_8009C150
    .4byte func_8009C20C
    .4byte func_800761C8
    .4byte 0x0000013C
    .4byte 0x00A4003A
    .4byte 0x3A000000
    .4byte func_8009C234
    .4byte func_8009C254
    .4byte func_8009C274
    .4byte func_8009C294
    .4byte func_800761C8
    .4byte 0x0000013D
    .4byte 0x00A4003B
    .4byte 0x3B000000
    .4byte func_8009C2BC
    .4byte func_8009C2DC
    .4byte func_8009C2FC
    .4byte func_8009C31C
    .4byte func_800761C8
    .4byte 0x0000013E
    .4byte 0x00A4003C
    .4byte 0x3C000000
    .4byte func_8009C344
    .4byte func_8009C364
    .4byte func_8009C384
    .4byte func_8009C3A4
    .4byte func_800761C8
    .4byte 0x0000013B
    .4byte 0x00A40039
    .4byte 0x39000000
    .4byte func_8009C3CC
    .4byte func_8009C410
    .4byte func_8009C414
    .4byte func_8009C434
    .4byte func_800761C8
    .4byte 0x0000013C
    .4byte 0x00A4003A
    .4byte 0x3A000000
    .4byte func_8009C3CC
    .4byte func_8009C410
    .4byte func_8009C414
    .4byte func_8009C434
    .4byte func_800761C8
    .4byte 0x0000013D
    .4byte 0x00A4003B
    .4byte 0x3B000000
    .4byte func_8009C3CC
    .4byte func_8009C410
    .4byte func_8009C414
    .4byte func_8009C434
    .4byte func_800761C8
    .4byte 0x0000013E
    .4byte 0x00A4003C
    .4byte 0x3C000000
    .4byte func_8009C3CC
    .4byte func_8009C410
    .4byte func_8009C414
    .4byte func_8009C434
    .4byte func_800761C8
    .4byte 0x0000013F
    .4byte 0x00340211
    .4byte 0x12000000
    .4byte ftDonkey_8010E7B4
    .4byte ftDonkey_8010F094
    .4byte ftDonkey_8010F328
    .4byte ftDonkey_8010F468
    .4byte func_800761C8
    .4byte 0x00000140
    .4byte 0x00340211
    .4byte 0x12000000
    .4byte ftDonkey_8010E840
    .4byte ftDonkey_8010F098
    .4byte ftDonkey_8010F348
    .4byte ftDonkey_8010F50C
    .4byte func_800761C8
    .4byte 0x00000141
    .4byte 0x00340211
    .4byte 0x12000000
    .4byte ftDonkey_8010E8E0
    .4byte ftDonkey_8010F1D8
    .4byte ftDonkey_8010F368
    .4byte ftDonkey_8010F5B0
    .4byte func_800761C8
    .4byte 0x00000142
    .4byte 0x00340211
    .4byte 0x12000000
    .4byte ftDonkey_8010E930
    .4byte ftDonkey_8010F1DC
    .4byte ftDonkey_8010F388
    .4byte ftDonkey_8010F654
    .4byte func_800761C8
    .4byte 0x00000143
    .4byte 0x00340211
    .4byte 0x12000000
    .4byte ftDonkey_8010EB0C
    .4byte ftDonkey_8010F1E0
    .4byte ftDonkey_8010F3A8
    .4byte ftDonkey_8010F6F8
    .4byte func_800761C8
    .4byte 0x00000144
    .4byte 0x00340611
    .4byte 0x12000000
    .4byte ftDonkey_8010EC5C
    .4byte ftDonkey_8010F1E4
    .4byte ftDonkey_8010F3C8
    .4byte ftDonkey_8010F79C
    .4byte func_800761C8
    .4byte 0x00000145
    .4byte 0x00340611
    .4byte 0x12000000
    .4byte ftDonkey_8010ECE8
    .4byte ftDonkey_8010F1E8
    .4byte ftDonkey_8010F3E8
    .4byte ftDonkey_8010F840
    .4byte func_800761C8
    .4byte 0x00000146
    .4byte 0x00340611
    .4byte 0x12000000
    .4byte ftDonkey_8010ED88
    .4byte ftDonkey_8010F31C
    .4byte ftDonkey_8010F408
    .4byte ftDonkey_8010F8E4
    .4byte func_800761C8
    .4byte 0x00000147
    .4byte 0x00340611
    .4byte 0x12000000
    .4byte ftDonkey_8010EDD8
    .4byte ftDonkey_8010F320
    .4byte ftDonkey_8010F428
    .4byte ftDonkey_8010F988
    .4byte func_800761C8
    .4byte 0x00000148
    .4byte 0x00340611
    .4byte 0x12000000
    .4byte ftDonkey_8010EF7C
    .4byte ftDonkey_8010F324
    .4byte ftDonkey_8010F448
    .4byte ftDonkey_8010FA2C
    .4byte func_800761C8
    .4byte 0x00000149
    .4byte 0x00340212
    .4byte 0x13000000
    .4byte ftDonkey_8010E2BC
    .4byte ftDonkey_8010E334
    .4byte ftDonkey_8010E33C
    .4byte ftDonkey_8010E3BC
    .4byte func_800761C8
    .4byte 0x0000014A
    .4byte 0x00340612
    .4byte 0x13000000
    .4byte ftDonkey_8010E2F8
    .4byte ftDonkey_8010E338
    .4byte ftDonkey_8010E35C
    .4byte ftDonkey_8010E428
    .4byte func_800761C8
    .4byte 0x0000014B
    .4byte 0x00340213
    .4byte 0x14000000
    .4byte ftDonkey_8010FCD4
    .4byte lbl_8010FD9C
    .4byte lbl_8010FDA4
    .4byte lbl_8010FE60
    .4byte func_800761C8
    .4byte 0x0000014C
    .4byte 0x00340613
    .4byte 0x14000000
    .4byte ftDonkey_8010FD10
    .4byte lbl_8010FDA0
    .4byte lbl_8010FDEC
    .4byte lbl_8010FF14
    .4byte func_800761C8
    .4byte 0x0000014D
    .4byte 0x00340214
    .4byte 0x15000000
    .4byte ftDonkey_8010DCD8
    .4byte ftDonkey_8010DD14
    .4byte ftDonkey_8010DD18
    .4byte ftDonkey_8010DD38
    .4byte func_800761C8
    .4byte 0x0000014E
    .4byte 0x003C0214
    .4byte 0x15000000
    .4byte ftDonkey_8010DD74
    .4byte ftDonkey_8010DDDC
    .4byte ftDonkey_8010DDF8
    .4byte ftDonkey_8010DE18
    .4byte func_800761C8
    .4byte 0x0000014F
    .4byte 0x00340214
    .4byte 0x15000000
    .4byte ftDonkey_8010DF5C
    .4byte ftDonkey_8010DF98
    .4byte ftDonkey_8010DF9C
    .4byte ftDonkey_8010DFBC
    .4byte func_800761C8
    .4byte 0x00000150
    .4byte 0x00340614
    .4byte 0x15000000
    .4byte ftDonkey_8010E030
    .4byte ftDonkey_8010E06C
    .4byte ftDonkey_8010E070
    .4byte ftDonkey_8010E090
    .4byte func_800761C8
.global lbl_803CBDF8
lbl_803CBDF8:
    .asciz "PlDk.dat"
    .balign 4
.global lbl_803CBE04
lbl_803CBE04:
    .asciz "ftDataDonkey"
    .balign 4
.global lbl_803CBE14
lbl_803CBE14:
    .asciz "PlDkNr.dat"
    .balign 4
.global lbl_803CBE20
lbl_803CBE20:
    .asciz "PlyDonkey5K_Share_joint"
    .balign 4
.global lbl_803CBE38
lbl_803CBE38:
    .asciz "PlyDonkey5K_Share_matanim_joint"
    .balign 4
.global lbl_803CBE58
lbl_803CBE58:
    .asciz "PlDkBk.dat"
    .balign 4
.global lbl_803CBE64
lbl_803CBE64:
    .asciz "PlyDonkey5KBk_Share_joint"
    .balign 4
.global lbl_803CBE80
lbl_803CBE80:
    .asciz "PlyDonkey5KBk_Share_matanim_joint"
    .balign 4
.global lbl_803CBEA4
lbl_803CBEA4:
    .asciz "PlDkRe.dat"
    .balign 4
.global lbl_803CBEB0
lbl_803CBEB0:
    .asciz "PlyDonkey5KRe_Share_joint"
    .balign 4
.global lbl_803CBECC
lbl_803CBECC:
    .asciz "PlyDonkey5KRe_Share_matanim_joint"
    .balign 4
.global lbl_803CBEF0
lbl_803CBEF0:
    .asciz "PlDkBu.dat"
    .balign 4
.global lbl_803CBEFC
lbl_803CBEFC:
    .asciz "PlyDonkey5KBu_Share_joint"
    .balign 4
.global lbl_803CBF18
lbl_803CBF18:
    .asciz "PlyDonkey5KBu_Share_matanim_joint"
    .balign 4
.global lbl_803CBF3C
lbl_803CBF3C:
    .asciz "PlDkGr.dat"
    .balign 4
.global lbl_803CBF48
lbl_803CBF48:
    .asciz "PlyDonkey5KGr_Share_joint"
    .balign 4
.global lbl_803CBF64
lbl_803CBF64:
    .asciz "PlyDonkey5KGr_Share_matanim_joint"
    .balign 4
.global lbl_803CBF88
lbl_803CBF88:
    .asciz "PlDkAJ.dat"
    .balign 4
.global lbl_803CBF94
lbl_803CBF94:
    .asciz "ftDemoResultMotionFileDonkey"
    .balign 4
.global lbl_803CBFB4
lbl_803CBFB4:
    .asciz "ftDemoIntroMotionFileDonkey"
    .balign 4
.global lbl_803CBFD0
lbl_803CBFD0:
    .asciz "ftDemoEndingMotionFileDonkey"
    .balign 4
.global lbl_803CBFF0
lbl_803CBFF0:
    .asciz "ftDemoViWaitMotionFileDonkey"
    .balign 4
.global lbl_803CC010
lbl_803CC010:
    .4byte lbl_803CBF94
    .4byte lbl_803CBFB4
    .4byte lbl_803CBFD0
    .4byte lbl_803CBFF0
.global lbl_803CC020
lbl_803CC020:
    .4byte lbl_803CBE14
    .4byte lbl_803CBE20
    .4byte lbl_803CBE38
    .4byte lbl_803CBE58
    .4byte lbl_803CBE64
    .4byte lbl_803CBE80
    .4byte lbl_803CBEA4
    .4byte lbl_803CBEB0
    .4byte lbl_803CBECC
    .4byte lbl_803CBEF0
    .4byte lbl_803CBEFC
    .4byte lbl_803CBF18
    .4byte lbl_803CBF3C
    .4byte lbl_803CBF48
    .4byte lbl_803CBF64
    .4byte NULL


.section .sdata2
.global lbl_804D95E8
lbl_804D95E8:
	.4byte 0x00000000
.global lbl_804D95EC
lbl_804D95EC:
	.4byte 0x3F800000
