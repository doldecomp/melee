.include "macros.inc"

.section .text

.global it_802BDE18
it_802BDE18:
/* 802BDE18 002BA9F8  7C 08 02 A6 */	mflr r0
/* 802BDE1C 002BA9FC  38 E0 00 00 */	li r7, 0
/* 802BDE20 002BAA00  90 01 00 04 */	stw r0, 4(r1)
/* 802BDE24 002BAA04  94 21 FF 88 */	stwu r1, -0x78(r1)
/* 802BDE28 002BAA08  93 E1 00 74 */	stw r31, 0x74(r1)
/* 802BDE2C 002BAA0C  93 C1 00 70 */	stw r30, 0x70(r1)
/* 802BDE30 002BAA10  7C BE 2B 78 */	mr r30, r5
/* 802BDE34 002BAA14  93 A1 00 6C */	stw r29, 0x6c(r1)
/* 802BDE38 002BAA18  3B A3 00 00 */	addi r29, r3, 0
/* 802BDE3C 002BAA1C  90 C1 00 24 */	stw r6, 0x24(r1)
/* 802BDE40 002BAA20  38 C0 00 01 */	li r6, 1
/* 802BDE44 002BAA24  80 64 00 00 */	lwz r3, 0(r4)
/* 802BDE48 002BAA28  80 04 00 04 */	lwz r0, 4(r4)
/* 802BDE4C 002BAA2C  90 61 00 3C */	stw r3, 0x3c(r1)
/* 802BDE50 002BAA30  38 61 00 1C */	addi r3, r1, 0x1c
/* 802BDE54 002BAA34  90 01 00 40 */	stw r0, 0x40(r1)
/* 802BDE58 002BAA38  80 04 00 08 */	lwz r0, 8(r4)
/* 802BDE5C 002BAA3C  90 01 00 44 */	stw r0, 0x44(r1)
/* 802BDE60 002BAA40  80 81 00 3C */	lwz r4, 0x3c(r1)
/* 802BDE64 002BAA44  80 01 00 40 */	lwz r0, 0x40(r1)
/* 802BDE68 002BAA48  C0 02 D7 40 */	lfs f0, it_804DD120@sda21(r2)
/* 802BDE6C 002BAA4C  90 81 00 30 */	stw r4, 0x30(r1)
/* 802BDE70 002BAA50  90 01 00 34 */	stw r0, 0x34(r1)
/* 802BDE74 002BAA54  80 01 00 44 */	lwz r0, 0x44(r1)
/* 802BDE78 002BAA58  90 01 00 38 */	stw r0, 0x38(r1)
/* 802BDE7C 002BAA5C  D0 21 00 54 */	stfs f1, 0x54(r1)
/* 802BDE80 002BAA60  B0 E1 00 58 */	sth r7, 0x58(r1)
/* 802BDE84 002BAA64  D0 01 00 50 */	stfs f0, 0x50(r1)
/* 802BDE88 002BAA68  D0 01 00 4C */	stfs f0, 0x4c(r1)
/* 802BDE8C 002BAA6C  D0 01 00 48 */	stfs f0, 0x48(r1)
/* 802BDE90 002BAA70  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 802BDE94 002BAA74  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 802BDE98 002BAA78  90 01 00 20 */	stw r0, 0x20(r1)
/* 802BDE9C 002BAA7C  88 01 00 60 */	lbz r0, 0x60(r1)
/* 802BDEA0 002BAA80  50 C0 3E 30 */	rlwimi r0, r6, 7, 0x18, 0x18
/* 802BDEA4 002BAA84  98 01 00 60 */	stb r0, 0x60(r1)
/* 802BDEA8 002BAA88  90 E1 00 5C */	stw r7, 0x5c(r1)
/* 802BDEAC 002BAA8C  4B FA AC 6D */	bl Item_80268B18
/* 802BDEB0 002BAA90  7C 7F 1B 79 */	or. r31, r3, r3
/* 802BDEB4 002BAA94  41 82 00 28 */	beq .L_802BDEDC
/* 802BDEB8 002BAA98  38 7F 00 00 */	addi r3, r31, 0
/* 802BDEBC 002BAA9C  38 9D 00 00 */	addi r4, r29, 0
/* 802BDEC0 002BAAA0  38 BE 00 00 */	addi r5, r30, 0
/* 802BDEC4 002BAAA4  4B FA CC 91 */	bl Item_8026AB54
/* 802BDEC8 002BAAA8  38 7F 00 00 */	addi r3, r31, 0
/* 802BDECC 002BAAAC  38 9D 00 00 */	addi r4, r29, 0
/* 802BDED0 002BAAB0  4B F6 7F 09 */	bl db_80225DD8
/* 802BDED4 002BAAB4  7F E3 FB 78 */	mr r3, r31
/* 802BDED8 002BAAB8  48 00 00 08 */	b .L_802BDEE0
.L_802BDEDC:
/* 802BDEDC 002BAABC  38 60 00 00 */	li r3, 0
.L_802BDEE0:
/* 802BDEE0 002BAAC0  80 01 00 7C */	lwz r0, 0x7c(r1)
/* 802BDEE4 002BAAC4  83 E1 00 74 */	lwz r31, 0x74(r1)
/* 802BDEE8 002BAAC8  83 C1 00 70 */	lwz r30, 0x70(r1)
/* 802BDEEC 002BAACC  83 A1 00 6C */	lwz r29, 0x6c(r1)
/* 802BDEF0 002BAAD0  38 21 00 78 */	addi r1, r1, 0x78
/* 802BDEF4 002BAAD4  7C 08 03 A6 */	mtlr r0
/* 802BDEF8 002BAAD8  4E 80 00 20 */	blr

.global it_802BDEFC
it_802BDEFC:
/* 802BDEFC 002BAADC  7C 08 02 A6 */	mflr r0
/* 802BDF00 002BAAE0  90 01 00 04 */	stw r0, 4(r1)
/* 802BDF04 002BAAE4  94 21 FF F8 */	stwu r1, -8(r1)
/* 802BDF08 002BAAE8  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 802BDF0C 002BAAEC  80 64 05 18 */	lwz r3, 0x518(r4)
/* 802BDF10 002BAAF0  28 03 00 00 */	cmplwi r3, 0
/* 802BDF14 002BAAF4  41 82 00 1C */	beq .L_802BDF30
/* 802BDF18 002BAAF8  80 04 00 10 */	lwz r0, 0x10(r4)
/* 802BDF1C 002BAAFC  2C 00 00 68 */	cmpwi r0, 0x68
/* 802BDF20 002BAB00  40 82 00 0C */	bne .L_802BDF2C
/* 802BDF24 002BAB04  4B E6 03 89 */	bl ftPe_SpecialN_DoDeath2
/* 802BDF28 002BAB08  48 00 00 08 */	b .L_802BDF30
.L_802BDF2C:
/* 802BDF2C 002BAB0C  4B E4 E4 95 */	bl ftKb_SpecialNPe_8010C3C0
.L_802BDF30:
/* 802BDF30 002BAB10  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802BDF34 002BAB14  38 21 00 08 */	addi r1, r1, 8
/* 802BDF38 002BAB18  7C 08 03 A6 */	mtlr r0
/* 802BDF3C 002BAB1C  4E 80 00 20 */	blr

.global it_802BDF40
it_802BDF40:
/* 802BDF40 002BAB20  7C 08 02 A6 */	mflr r0
/* 802BDF44 002BAB24  90 01 00 04 */	stw r0, 4(r1)
/* 802BDF48 002BAB28  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 802BDF4C 002BAB2C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 802BDF50 002BAB30  7C 7F 1B 78 */	mr r31, r3
/* 802BDF54 002BAB34  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 802BDF58 002BAB38  28 04 00 00 */	cmplwi r4, 0
/* 802BDF5C 002BAB3C  41 82 00 30 */	beq .L_802BDF8C
/* 802BDF60 002BAB40  80 64 05 18 */	lwz r3, 0x518(r4)
/* 802BDF64 002BAB44  28 03 00 00 */	cmplwi r3, 0
/* 802BDF68 002BAB48  41 82 00 1C */	beq .L_802BDF84
/* 802BDF6C 002BAB4C  80 04 00 10 */	lwz r0, 0x10(r4)
/* 802BDF70 002BAB50  2C 00 00 68 */	cmpwi r0, 0x68
/* 802BDF74 002BAB54  40 82 00 0C */	bne .L_802BDF80
/* 802BDF78 002BAB58  4B E6 03 35 */	bl ftPe_SpecialN_DoDeath2
/* 802BDF7C 002BAB5C  48 00 00 08 */	b .L_802BDF84
.L_802BDF80:
/* 802BDF80 002BAB60  4B E4 E4 41 */	bl ftKb_SpecialNPe_8010C3C0
.L_802BDF84:
/* 802BDF84 002BAB64  7F E3 FB 78 */	mr r3, r31
/* 802BDF88 002BAB68  4B FA C9 65 */	bl Item_8026A8EC
.L_802BDF8C:
/* 802BDF8C 002BAB6C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 802BDF90 002BAB70  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 802BDF94 002BAB74  38 21 00 20 */	addi r1, r1, 0x20
/* 802BDF98 002BAB78  7C 08 03 A6 */	mtlr r0
/* 802BDF9C 002BAB7C  4E 80 00 20 */	blr

.global it_802BDFA0
it_802BDFA0:
/* 802BDFA0 002BAB80  7C 08 02 A6 */	mflr r0
/* 802BDFA4 002BAB84  90 01 00 04 */	stw r0, 4(r1)
/* 802BDFA8 002BAB88  94 21 FF F8 */	stwu r1, -8(r1)
/* 802BDFAC 002BAB8C  4B FA D7 79 */	bl it_8026B724
/* 802BDFB0 002BAB90  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802BDFB4 002BAB94  38 21 00 08 */	addi r1, r1, 8
/* 802BDFB8 002BAB98  7C 08 03 A6 */	mtlr r0
/* 802BDFBC 002BAB9C  4E 80 00 20 */	blr

.global it_802BDFC0
it_802BDFC0:
/* 802BDFC0 002BABA0  7C 08 02 A6 */	mflr r0
/* 802BDFC4 002BABA4  90 01 00 04 */	stw r0, 4(r1)
/* 802BDFC8 002BABA8  94 21 FF F8 */	stwu r1, -8(r1)
/* 802BDFCC 002BABAC  4B FA D7 71 */	bl it_8026B73C
/* 802BDFD0 002BABB0  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802BDFD4 002BABB4  38 21 00 08 */	addi r1, r1, 8
/* 802BDFD8 002BABB8  7C 08 03 A6 */	mtlr r0
/* 802BDFDC 002BABBC  4E 80 00 20 */	blr

.global it_802BDFE0
it_802BDFE0:
/* 802BDFE0 002BABC0  7C 08 02 A6 */	mflr r0
/* 802BDFE4 002BABC4  38 80 00 00 */	li r4, 0
/* 802BDFE8 002BABC8  90 01 00 04 */	stw r0, 4(r1)
/* 802BDFEC 002BABCC  38 A0 00 02 */	li r5, 2
/* 802BDFF0 002BABD0  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 802BDFF4 002BABD4  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 802BDFF8 002BABD8  3B E3 00 00 */	addi r31, r3, 0
/* 802BDFFC 002BABDC  4B FA AE 61 */	bl Item_80268E5C
/* 802BE000 002BABE0  7F E3 FB 78 */	mr r3, r31
/* 802BE004 002BABE4  4B FA B4 C9 */	bl Item_802694CC
/* 802BE008 002BABE8  7F E3 FB 78 */	mr r3, r31
/* 802BE00C 002BABEC  4B FA DB 39 */	bl it_8026BB44
/* 802BE010 002BABF0  7F E3 FB 78 */	mr r3, r31
/* 802BE014 002BABF4  4B FB 65 61 */	bl it_80274574
/* 802BE018 002BABF8  80 01 00 24 */	lwz r0, 0x24(r1)
/* 802BE01C 002BABFC  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 802BE020 002BAC00  38 21 00 20 */	addi r1, r1, 0x20
/* 802BE024 002BAC04  7C 08 03 A6 */	mtlr r0
/* 802BE028 002BAC08  4E 80 00 20 */	blr

.global it_802BE02C
it_802BE02C:
/* 802BE02C 002BAC0C  7C 08 02 A6 */	mflr r0
/* 802BE030 002BAC10  90 01 00 04 */	stw r0, 4(r1)
/* 802BE034 002BAC14  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 802BE038 002BAC18  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 802BE03C 002BAC1C  93 C1 00 18 */	stw r30, 0x18(r1)
/* 802BE040 002BAC20  7C 7E 1B 78 */	mr r30, r3
/* 802BE044 002BAC24  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 802BE048 002BAC28  C0 22 D7 44 */	lfs f1, it_804DD124@sda21(r2)
/* 802BE04C 002BAC2C  C0 1F 05 CC */	lfs f0, 0x5cc(r31)
/* 802BE050 002BAC30  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 802BE054 002BAC34  40 82 00 0C */	bne .L_802BE060
/* 802BE058 002BAC38  7F C3 F3 78 */	mr r3, r30
/* 802BE05C 002BAC3C  4B FA DA C5 */	bl it_8026BB20
.L_802BE060:
/* 802BE060 002BAC40  C0 3F 05 CC */	lfs f1, 0x5cc(r31)
/* 802BE064 002BAC44  C0 02 D7 48 */	lfs f0, it_804DD128@sda21(r2)
/* 802BE068 002BAC48  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 802BE06C 002BAC4C  4C 41 13 82 */	cror 2, 1, 2
/* 802BE070 002BAC50  40 82 00 0C */	bne .L_802BE07C
/* 802BE074 002BAC54  7F C3 F3 78 */	mr r3, r30
/* 802BE078 002BAC58  4B FA DA CD */	bl it_8026BB44
.L_802BE07C:
/* 802BE07C 002BAC5C  80 9E 00 2C */	lwz r4, 0x2c(r30)
/* 802BE080 002BAC60  80 64 05 18 */	lwz r3, 0x518(r4)
/* 802BE084 002BAC64  28 03 00 00 */	cmplwi r3, 0
/* 802BE088 002BAC68  41 82 00 20 */	beq .L_802BE0A8
/* 802BE08C 002BAC6C  80 04 00 10 */	lwz r0, 0x10(r4)
/* 802BE090 002BAC70  2C 00 00 68 */	cmpwi r0, 0x68
/* 802BE094 002BAC74  40 82 00 0C */	bne .L_802BE0A0
/* 802BE098 002BAC78  4B E6 03 11 */	bl ftPe_SpecialN_IsActive
/* 802BE09C 002BAC7C  48 00 00 10 */	b .L_802BE0AC
.L_802BE0A0:
/* 802BE0A0 002BAC80  4B E4 E4 0D */	bl ftKb_SpecialNPe_8010C4AC
/* 802BE0A4 002BAC84  48 00 00 08 */	b .L_802BE0AC
.L_802BE0A8:
/* 802BE0A8 002BAC88  38 60 00 01 */	li r3, 1
.L_802BE0AC:
/* 802BE0AC 002BAC8C  2C 03 00 00 */	cmpwi r3, 0
/* 802BE0B0 002BAC90  41 82 00 34 */	beq .L_802BE0E4
/* 802BE0B4 002BAC94  80 9E 00 2C */	lwz r4, 0x2c(r30)
/* 802BE0B8 002BAC98  80 64 05 18 */	lwz r3, 0x518(r4)
/* 802BE0BC 002BAC9C  28 03 00 00 */	cmplwi r3, 0
/* 802BE0C0 002BACA0  41 82 00 1C */	beq .L_802BE0DC
/* 802BE0C4 002BACA4  80 04 00 10 */	lwz r0, 0x10(r4)
/* 802BE0C8 002BACA8  2C 00 00 68 */	cmpwi r0, 0x68
/* 802BE0CC 002BACAC  40 82 00 0C */	bne .L_802BE0D8
/* 802BE0D0 002BACB0  4B E6 01 DD */	bl ftPe_SpecialN_DoDeath2
/* 802BE0D4 002BACB4  48 00 00 08 */	b .L_802BE0DC
.L_802BE0D8:
/* 802BE0D8 002BACB8  4B E4 E2 E9 */	bl ftKb_SpecialNPe_8010C3C0
.L_802BE0DC:
/* 802BE0DC 002BACBC  38 60 00 01 */	li r3, 1
/* 802BE0E0 002BACC0  48 00 00 08 */	b .L_802BE0E8
.L_802BE0E4:
/* 802BE0E4 002BACC4  38 60 00 00 */	li r3, 0
.L_802BE0E8:
/* 802BE0E8 002BACC8  80 01 00 24 */	lwz r0, 0x24(r1)
/* 802BE0EC 002BACCC  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 802BE0F0 002BACD0  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 802BE0F4 002BACD4  38 21 00 20 */	addi r1, r1, 0x20
/* 802BE0F8 002BACD8  7C 08 03 A6 */	mtlr r0
/* 802BE0FC 002BACDC  4E 80 00 20 */	blr

.global it_802BE100
it_802BE100:
/* 802BE100 002BACE0  7C 08 02 A6 */	mflr r0
/* 802BE104 002BACE4  38 80 00 01 */	li r4, 1
/* 802BE108 002BACE8  90 01 00 04 */	stw r0, 4(r1)
/* 802BE10C 002BACEC  38 A0 00 02 */	li r5, 2
/* 802BE110 002BACF0  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 802BE114 002BACF4  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 802BE118 002BACF8  93 C1 00 18 */	stw r30, 0x18(r1)
/* 802BE11C 002BACFC  7C 7E 1B 78 */	mr r30, r3
/* 802BE120 002BAD00  83 E3 00 28 */	lwz r31, 0x28(r3)
/* 802BE124 002BAD04  4B FA AD 39 */	bl Item_80268E5C
/* 802BE128 002BAD08  7F E3 FB 78 */	mr r3, r31
/* 802BE12C 002BAD0C  C0 22 D7 4C */	lfs f1, it_804DD12C@sda21(r2)
/* 802BE130 002BAD10  4B D4 D8 DD */	bl lb_8000BA0C
/* 802BE134 002BAD14  7F E3 FB 78 */	mr r3, r31
/* 802BE138 002BAD18  48 0B 27 F1 */	bl HSD_JObjAnimAll
/* 802BE13C 002BAD1C  7F E3 FB 78 */	mr r3, r31
/* 802BE140 002BAD20  C0 22 D7 50 */	lfs f1, it_804DD130@sda21(r2)
/* 802BE144 002BAD24  4B D4 D8 C9 */	bl lb_8000BA0C
/* 802BE148 002BAD28  7F C3 F3 78 */	mr r3, r30
/* 802BE14C 002BAD2C  4B FB 64 29 */	bl it_80274574
/* 802BE150 002BAD30  80 01 00 24 */	lwz r0, 0x24(r1)
/* 802BE154 002BAD34  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 802BE158 002BAD38  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 802BE15C 002BAD3C  38 21 00 20 */	addi r1, r1, 0x20
/* 802BE160 002BAD40  7C 08 03 A6 */	mtlr r0
/* 802BE164 002BAD44  4E 80 00 20 */	blr

.global it_802BE168
it_802BE168:
/* 802BE168 002BAD48  7C 08 02 A6 */	mflr r0
/* 802BE16C 002BAD4C  90 01 00 04 */	stw r0, 4(r1)
/* 802BE170 002BAD50  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 802BE174 002BAD54  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 802BE178 002BAD58  7C 7F 1B 78 */	mr r31, r3
/* 802BE17C 002BAD5C  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 802BE180 002BAD60  C0 02 D7 54 */	lfs f0, it_804DD134@sda21(r2)
/* 802BE184 002BAD64  C0 23 05 CC */	lfs f1, 0x5cc(r3)
/* 802BE188 002BAD68  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 802BE18C 002BAD6C  4C 41 13 82 */	cror 2, 1, 2
/* 802BE190 002BAD70  40 82 00 0C */	bne .L_802BE19C
/* 802BE194 002BAD74  7F E3 FB 78 */	mr r3, r31
/* 802BE198 002BAD78  4B FA D9 AD */	bl it_8026BB44
.L_802BE19C:
/* 802BE19C 002BAD7C  80 9F 00 2C */	lwz r4, 0x2c(r31)
/* 802BE1A0 002BAD80  80 64 05 18 */	lwz r3, 0x518(r4)
/* 802BE1A4 002BAD84  28 03 00 00 */	cmplwi r3, 0
/* 802BE1A8 002BAD88  41 82 00 20 */	beq .L_802BE1C8
/* 802BE1AC 002BAD8C  80 04 00 10 */	lwz r0, 0x10(r4)
/* 802BE1B0 002BAD90  2C 00 00 68 */	cmpwi r0, 0x68
/* 802BE1B4 002BAD94  40 82 00 0C */	bne .L_802BE1C0
/* 802BE1B8 002BAD98  4B E6 01 F1 */	bl ftPe_SpecialN_IsActive
/* 802BE1BC 002BAD9C  48 00 00 10 */	b .L_802BE1CC
.L_802BE1C0:
/* 802BE1C0 002BADA0  4B E4 E2 ED */	bl ftKb_SpecialNPe_8010C4AC
/* 802BE1C4 002BADA4  48 00 00 08 */	b .L_802BE1CC
.L_802BE1C8:
/* 802BE1C8 002BADA8  38 60 00 01 */	li r3, 1
.L_802BE1CC:
/* 802BE1CC 002BADAC  2C 03 00 00 */	cmpwi r3, 0
/* 802BE1D0 002BADB0  41 82 00 0C */	beq .L_802BE1DC
/* 802BE1D4 002BADB4  38 60 00 01 */	li r3, 1
/* 802BE1D8 002BADB8  48 00 00 08 */	b .L_802BE1E0
.L_802BE1DC:
/* 802BE1DC 002BADBC  38 60 00 00 */	li r3, 0
.L_802BE1E0:
/* 802BE1E0 002BADC0  80 01 00 24 */	lwz r0, 0x24(r1)
/* 802BE1E4 002BADC4  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 802BE1E8 002BADC8  38 21 00 20 */	addi r1, r1, 0x20
/* 802BE1EC 002BADCC  7C 08 03 A6 */	mtlr r0
/* 802BE1F0 002BADD0  4E 80 00 20 */	blr

.global it_802BE1F4
it_802BE1F4:
/* 802BE1F4 002BADD4  7C 08 02 A6 */	mflr r0
/* 802BE1F8 002BADD8  90 01 00 04 */	stw r0, 4(r1)
/* 802BE1FC 002BADDC  94 21 FF F8 */	stwu r1, -8(r1)
/* 802BE200 002BADE0  4B FA D6 95 */	bl it_8026B894
/* 802BE204 002BADE4  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802BE208 002BADE8  38 21 00 08 */	addi r1, r1, 8
/* 802BE20C 002BADEC  7C 08 03 A6 */	mtlr r0
/* 802BE210 002BADF0  4E 80 00 20 */	blr


.section .data
    .balign 8
.global it_803F7528
it_803F7528:
    .4byte 0
    .4byte it_802BE02C
    .4byte NULL
    .4byte NULL
    .4byte 1
    .4byte it_802BE168
    .4byte NULL
    .4byte NULL


.section .sdata2
    .balign 8
.global it_804DD120
it_804DD120:
    .4byte 0x00000000
.global it_804DD124
it_804DD124:
    .4byte 0x40E00000
.global it_804DD128
it_804DD128:
    .4byte 0x42540000
.global it_804DD12C
it_804DD12C:
    .4byte 0x41200000
.global it_804DD130
it_804DD130:
    .4byte 0x3F800000
.global it_804DD134
it_804DD134:
    .4byte 0x42700000
