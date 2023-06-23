.include "macros.inc"

.section .text

.global it_8028FE90
it_8028FE90:
/* 8028FE90 0028CA70  7C 08 02 A6 */	mflr r0
/* 8028FE94 0028CA74  90 01 00 04 */	stw r0, 4(r1)
/* 8028FE98 0028CA78  94 21 FF F8 */	stwu r1, -8(r1)
/* 8028FE9C 0028CA7C  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 8028FEA0 0028CA80  88 04 0D CA */	lbz r0, 0xdca(r4)
/* 8028FEA4 0028CA84  54 00 E7 FF */	rlwinm. r0, r0, 0x1c, 0x1f, 0x1f
/* 8028FEA8 0028CA88  40 82 00 1C */	bne .L_8028FEC4
/* 8028FEAC 0028CA8C  80 04 00 24 */	lwz r0, 0x24(r4)
/* 8028FEB0 0028CA90  2C 00 00 04 */	cmpwi r0, 4
/* 8028FEB4 0028CA94  41 82 00 0C */	beq .L_8028FEC0
/* 8028FEB8 0028CA98  2C 00 00 05 */	cmpwi r0, 5
/* 8028FEBC 0028CA9C  40 82 00 08 */	bne .L_8028FEC4
.L_8028FEC0:
/* 8028FEC0 0028CAA0  48 00 07 19 */	bl it_802905D8
.L_8028FEC4:
/* 8028FEC4 0028CAA4  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8028FEC8 0028CAA8  38 21 00 08 */	addi r1, r1, 8
/* 8028FECC 0028CAAC  7C 08 03 A6 */	mtlr r0
/* 8028FED0 0028CAB0  4E 80 00 20 */	blr

.global it_8028FED4
it_8028FED4:
/* 8028FED4 0028CAB4  7C 08 02 A6 */	mflr r0
/* 8028FED8 0028CAB8  38 A0 00 00 */	li r5, 0
/* 8028FEDC 0028CABC  90 01 00 04 */	stw r0, 4(r1)
/* 8028FEE0 0028CAC0  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8028FEE4 0028CAC4  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8028FEE8 0028CAC8  7C 7F 1B 78 */	mr r31, r3
/* 8028FEEC 0028CACC  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 8028FEF0 0028CAD0  88 04 0D D4 */	lbz r0, 0xdd4(r4)
/* 8028FEF4 0028CAD4  50 A0 3E 30 */	rlwimi r0, r5, 7, 0x18, 0x18
/* 8028FEF8 0028CAD8  98 04 0D D4 */	stb r0, 0xdd4(r4)
/* 8028FEFC 0028CADC  4B FE 57 D5 */	bl it_802756D0
/* 8028FF00 0028CAE0  7F E3 FB 78 */	mr r3, r31
/* 8028FF04 0028CAE4  48 00 00 89 */	bl it_8028FF8C
/* 8028FF08 0028CAE8  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8028FF0C 0028CAEC  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8028FF10 0028CAF0  38 21 00 20 */	addi r1, r1, 0x20
/* 8028FF14 0028CAF4  7C 08 03 A6 */	mtlr r0
/* 8028FF18 0028CAF8  4E 80 00 20 */	blr

.global it_8028FF1C
it_8028FF1C:
/* 8028FF1C 0028CAFC  7C 08 02 A6 */	mflr r0
/* 8028FF20 0028CB00  90 01 00 04 */	stw r0, 4(r1)
/* 8028FF24 0028CB04  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8028FF28 0028CB08  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8028FF2C 0028CB0C  7C 7F 1B 78 */	mr r31, r3
/* 8028FF30 0028CB10  4B FD B4 61 */	bl it_8026B390
/* 8028FF34 0028CB14  7F E3 FB 78 */	mr r3, r31
/* 8028FF38 0028CB18  4B FE 35 1D */	bl it_80273454
/* 8028FF3C 0028CB1C  38 7F 00 00 */	addi r3, r31, 0
/* 8028FF40 0028CB20  38 80 00 00 */	li r4, 0
/* 8028FF44 0028CB24  38 A0 00 02 */	li r5, 2
/* 8028FF48 0028CB28  4B FD 8F 15 */	bl Item_80268E5C
/* 8028FF4C 0028CB2C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8028FF50 0028CB30  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8028FF54 0028CB34  38 21 00 20 */	addi r1, r1, 0x20
/* 8028FF58 0028CB38  7C 08 03 A6 */	mtlr r0
/* 8028FF5C 0028CB3C  4E 80 00 20 */	blr

.global it_8028FF60
it_8028FF60:
/* 8028FF60 0028CB40  7C 08 02 A6 */	mflr r0
/* 8028FF64 0028CB44  3C 80 80 29 */	lis r4, it_8028FF8C@ha
/* 8028FF68 0028CB48  90 01 00 04 */	stw r0, 4(r1)
/* 8028FF6C 0028CB4C  38 84 FF 8C */	addi r4, r4, it_8028FF8C@l
/* 8028FF70 0028CB50  94 21 FF F8 */	stwu r1, -8(r1)
/* 8028FF74 0028CB54  4B FD D6 B9 */	bl it_8026D62C
/* 8028FF78 0028CB58  38 60 00 00 */	li r3, 0
/* 8028FF7C 0028CB5C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8028FF80 0028CB60  38 21 00 08 */	addi r1, r1, 8
/* 8028FF84 0028CB64  7C 08 03 A6 */	mtlr r0
/* 8028FF88 0028CB68  4E 80 00 20 */	blr

.global it_8028FF8C
it_8028FF8C:
/* 8028FF8C 0028CB6C  7C 08 02 A6 */	mflr r0
/* 8028FF90 0028CB70  38 80 00 01 */	li r4, 1
/* 8028FF94 0028CB74  90 01 00 04 */	stw r0, 4(r1)
/* 8028FF98 0028CB78  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8028FF9C 0028CB7C  DB E1 00 20 */	stfd f31, 0x20(r1)
/* 8028FFA0 0028CB80  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8028FFA4 0028CB84  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8028FFA8 0028CB88  80 A3 00 2C */	lwz r5, 0x2c(r3)
/* 8028FFAC 0028CB8C  83 C3 00 28 */	lwz r30, 0x28(r3)
/* 8028FFB0 0028CB90  80 C5 00 C4 */	lwz r6, 0xc4(r5)
/* 8028FFB4 0028CB94  38 A0 00 02 */	li r5, 2
/* 8028FFB8 0028CB98  83 E6 00 04 */	lwz r31, 4(r6)
/* 8028FFBC 0028CB9C  4B FD 8E A1 */	bl Item_80268E5C
/* 8028FFC0 0028CBA0  28 1E 00 00 */	cmplwi r30, 0
/* 8028FFC4 0028CBA4  C3 FF 00 00 */	lfs f31, 0(r31)
/* 8028FFC8 0028CBA8  40 82 00 14 */	bne .L_8028FFDC
/* 8028FFCC 0028CBAC  38 6D 9C 10 */	addi r3, r13, it_804D52B0@sda21
/* 8028FFD0 0028CBB0  38 80 02 7F */	li r4, 0x27f
/* 8028FFD4 0028CBB4  38 AD 9C 18 */	addi r5, r13, it_804D52B8@sda21
/* 8028FFD8 0028CBB8  48 0F 82 49 */	bl __assert
.L_8028FFDC:
/* 8028FFDC 0028CBBC  80 1E 00 14 */	lwz r0, 0x14(r30)
/* 8028FFE0 0028CBC0  54 00 03 9D */	rlwinm. r0, r0, 0, 0xe, 0xe
/* 8028FFE4 0028CBC4  41 82 00 18 */	beq .L_8028FFFC
/* 8028FFE8 0028CBC8  3C 60 80 3F */	lis r3, it_803F5E80@ha
/* 8028FFEC 0028CBCC  38 A3 5E 80 */	addi r5, r3, it_803F5E80@l
/* 8028FFF0 0028CBD0  38 6D 9C 10 */	addi r3, r13, it_804D52B0@sda21
/* 8028FFF4 0028CBD4  38 80 02 80 */	li r4, 0x280
/* 8028FFF8 0028CBD8  48 0F 82 29 */	bl __assert
.L_8028FFFC:
/* 8028FFFC 0028CBDC  D3 FE 00 1C */	stfs f31, 0x1c(r30)
/* 80290000 0028CBE0  80 1E 00 14 */	lwz r0, 0x14(r30)
/* 80290004 0028CBE4  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 80290008 0028CBE8  40 82 00 4C */	bne .L_80290054
/* 8029000C 0028CBEC  28 1E 00 00 */	cmplwi r30, 0
/* 80290010 0028CBF0  41 82 00 44 */	beq .L_80290054
/* 80290014 0028CBF4  40 82 00 14 */	bne .L_80290028
/* 80290018 0028CBF8  38 6D 9C 10 */	addi r3, r13, it_804D52B0@sda21
/* 8029001C 0028CBFC  38 80 02 34 */	li r4, 0x234
/* 80290020 0028CC00  38 AD 9C 18 */	addi r5, r13, it_804D52B8@sda21
/* 80290024 0028CC04  48 0F 81 FD */	bl __assert
.L_80290028:
/* 80290028 0028CC08  80 9E 00 14 */	lwz r4, 0x14(r30)
/* 8029002C 0028CC0C  38 60 00 00 */	li r3, 0
/* 80290030 0028CC10  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 80290034 0028CC14  40 82 00 10 */	bne .L_80290044
/* 80290038 0028CC18  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 8029003C 0028CC1C  41 82 00 08 */	beq .L_80290044
/* 80290040 0028CC20  38 60 00 01 */	li r3, 1
.L_80290044:
/* 80290044 0028CC24  2C 03 00 00 */	cmpwi r3, 0
/* 80290048 0028CC28  40 82 00 0C */	bne .L_80290054
/* 8029004C 0028CC2C  7F C3 F3 78 */	mr r3, r30
/* 80290050 0028CC30  48 0E 32 99 */	bl HSD_JObjSetMtxDirtySub
.L_80290054:
/* 80290054 0028CC34  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 80290058 0028CC38  CB E1 00 20 */	lfd f31, 0x20(r1)
/* 8029005C 0028CC3C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80290060 0028CC40  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80290064 0028CC44  38 21 00 28 */	addi r1, r1, 0x28
/* 80290068 0028CC48  7C 08 03 A6 */	mtlr r0
/* 8029006C 0028CC4C  4E 80 00 20 */	blr

.global it_80290070
it_80290070:
/* 80290070 0028CC50  7C 08 02 A6 */	mflr r0
/* 80290074 0028CC54  90 01 00 04 */	stw r0, 4(r1)
/* 80290078 0028CC58  94 21 FF F8 */	stwu r1, -8(r1)
/* 8029007C 0028CC5C  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 80290080 0028CC60  80 84 00 CC */	lwz r4, 0xcc(r4)
/* 80290084 0028CC64  C0 24 00 10 */	lfs f1, 0x10(r4)
/* 80290088 0028CC68  C0 44 00 14 */	lfs f2, 0x14(r4)
/* 8029008C 0028CC6C  4B FE 27 D5 */	bl it_80272860
/* 80290090 0028CC70  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80290094 0028CC74  38 21 00 08 */	addi r1, r1, 8
/* 80290098 0028CC78  7C 08 03 A6 */	mtlr r0
/* 8029009C 0028CC7C  4E 80 00 20 */	blr

.global it_802900A0
it_802900A0:
/* 802900A0 0028CC80  7C 08 02 A6 */	mflr r0
/* 802900A4 0028CC84  3C 80 80 29 */	lis r4, it_8028FF1C@ha
/* 802900A8 0028CC88  90 01 00 04 */	stw r0, 4(r1)
/* 802900AC 0028CC8C  38 84 FF 1C */	addi r4, r4, it_8028FF1C@l
/* 802900B0 0028CC90  94 21 FF F8 */	stwu r1, -8(r1)
/* 802900B4 0028CC94  4B FD E0 A9 */	bl it_8026E15C
/* 802900B8 0028CC98  38 60 00 00 */	li r3, 0
/* 802900BC 0028CC9C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802900C0 0028CCA0  38 21 00 08 */	addi r1, r1, 8
/* 802900C4 0028CCA4  7C 08 03 A6 */	mtlr r0
/* 802900C8 0028CCA8  4E 80 00 20 */	blr

.global it_802900CC
it_802900CC:
/* 802900CC 0028CCAC  7C 08 02 A6 */	mflr r0
/* 802900D0 0028CCB0  38 80 00 02 */	li r4, 2
/* 802900D4 0028CCB4  90 01 00 04 */	stw r0, 4(r1)
/* 802900D8 0028CCB8  38 A0 00 02 */	li r5, 2
/* 802900DC 0028CCBC  94 21 FF F8 */	stwu r1, -8(r1)
/* 802900E0 0028CCC0  4B FD 8D 7D */	bl Item_80268E5C
/* 802900E4 0028CCC4  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802900E8 0028CCC8  38 21 00 08 */	addi r1, r1, 8
/* 802900EC 0028CCCC  7C 08 03 A6 */	mtlr r0
/* 802900F0 0028CCD0  4E 80 00 20 */	blr

.global it_802900F4
it_802900F4:
/* 802900F4 0028CCD4  7C 08 02 A6 */	mflr r0
/* 802900F8 0028CCD8  90 01 00 04 */	stw r0, 4(r1)
/* 802900FC 0028CCDC  94 21 FF F8 */	stwu r1, -8(r1)
/* 80290100 0028CCE0  48 00 00 15 */	bl it_80290114
/* 80290104 0028CCE4  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80290108 0028CCE8  38 21 00 08 */	addi r1, r1, 8
/* 8029010C 0028CCEC  7C 08 03 A6 */	mtlr r0
/* 80290110 0028CCF0  4E 80 00 20 */	blr

.global it_80290114
it_80290114:
/* 80290114 0028CCF4  7C 08 02 A6 */	mflr r0
/* 80290118 0028CCF8  38 80 00 03 */	li r4, 3
/* 8029011C 0028CCFC  90 01 00 04 */	stw r0, 4(r1)
/* 80290120 0028CD00  38 A0 00 06 */	li r5, 6
/* 80290124 0028CD04  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 80290128 0028CD08  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 8029012C 0028CD0C  93 C1 00 28 */	stw r30, 0x28(r1)
/* 80290130 0028CD10  93 A1 00 24 */	stw r29, 0x24(r1)
/* 80290134 0028CD14  7C 7D 1B 78 */	mr r29, r3
/* 80290138 0028CD18  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8029013C 0028CD1C  80 DF 00 C4 */	lwz r6, 0xc4(r31)
/* 80290140 0028CD20  83 C6 00 04 */	lwz r30, 4(r6)
/* 80290144 0028CD24  4B FD 8D 19 */	bl Item_80268E5C
/* 80290148 0028CD28  80 BE 00 08 */	lwz r5, 8(r30)
/* 8029014C 0028CD2C  7F A3 EB 78 */	mr r3, r29
/* 80290150 0028CD30  80 1E 00 0C */	lwz r0, 0xc(r30)
/* 80290154 0028CD34  38 81 00 10 */	addi r4, r1, 0x10
/* 80290158 0028CD38  90 A1 00 10 */	stw r5, 0x10(r1)
/* 8029015C 0028CD3C  90 01 00 14 */	stw r0, 0x14(r1)
/* 80290160 0028CD40  80 BE 00 10 */	lwz r5, 0x10(r30)
/* 80290164 0028CD44  80 1E 00 14 */	lwz r0, 0x14(r30)
/* 80290168 0028CD48  90 A1 00 18 */	stw r5, 0x18(r1)
/* 8029016C 0028CD4C  90 01 00 1C */	stw r0, 0x1c(r1)
/* 80290170 0028CD50  80 A1 00 10 */	lwz r5, 0x10(r1)
/* 80290174 0028CD54  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80290178 0028CD58  90 BF 0B FC */	stw r5, 0xbfc(r31)
/* 8029017C 0028CD5C  90 1F 0C 00 */	stw r0, 0xc00(r31)
/* 80290180 0028CD60  80 A1 00 18 */	lwz r5, 0x18(r1)
/* 80290184 0028CD64  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80290188 0028CD68  90 BF 0C 04 */	stw r5, 0xc04(r31)
/* 8029018C 0028CD6C  90 1F 0C 08 */	stw r0, 0xc08(r31)
/* 80290190 0028CD70  4B FE 5B CD */	bl it_80275D5C
/* 80290194 0028CD74  88 1F 0D CE */	lbz r0, 0xdce(r31)
/* 80290198 0028CD78  38 60 00 00 */	li r3, 0
/* 8029019C 0028CD7C  50 60 07 FE */	rlwimi r0, r3, 0, 0x1f, 0x1f
/* 802901A0 0028CD80  98 1F 0D CE */	stb r0, 0xdce(r31)
/* 802901A4 0028CD84  80 01 00 34 */	lwz r0, 0x34(r1)
/* 802901A8 0028CD88  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 802901AC 0028CD8C  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 802901B0 0028CD90  83 A1 00 24 */	lwz r29, 0x24(r1)
/* 802901B4 0028CD94  38 21 00 30 */	addi r1, r1, 0x30
/* 802901B8 0028CD98  7C 08 03 A6 */	mtlr r0
/* 802901BC 0028CD9C  4E 80 00 20 */	blr

.global it_802901C0
it_802901C0:
/* 802901C0 0028CDA0  7C 08 02 A6 */	mflr r0
/* 802901C4 0028CDA4  90 01 00 04 */	stw r0, 4(r1)
/* 802901C8 0028CDA8  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 802901CC 0028CDAC  93 E1 00 14 */	stw r31, 0x14(r1)
/* 802901D0 0028CDB0  7C 7F 1B 78 */	mr r31, r3
/* 802901D4 0028CDB4  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 802901D8 0028CDB8  80 84 00 CC */	lwz r4, 0xcc(r4)
/* 802901DC 0028CDBC  C0 24 00 10 */	lfs f1, 0x10(r4)
/* 802901E0 0028CDC0  C0 44 00 14 */	lfs f2, 0x14(r4)
/* 802901E4 0028CDC4  4B FE 26 7D */	bl it_80272860
/* 802901E8 0028CDC8  80 8D B6 88 */	lwz r4, it_804D6D28@sda21(r13)
/* 802901EC 0028CDCC  7F E3 FB 78 */	mr r3, r31
/* 802901F0 0028CDD0  C0 24 00 68 */	lfs f1, 0x68(r4)
/* 802901F4 0028CDD4  4B FE 44 65 */	bl it_80274658
/* 802901F8 0028CDD8  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 802901FC 0028CDDC  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80290200 0028CDE0  38 21 00 18 */	addi r1, r1, 0x18
/* 80290204 0028CDE4  7C 08 03 A6 */	mtlr r0
/* 80290208 0028CDE8  4E 80 00 20 */	blr

.global it_8029020C
it_8029020C:
/* 8029020C 0028CDEC  7C 08 02 A6 */	mflr r0
/* 80290210 0028CDF0  3C 80 80 29 */	lis r4, it_80290314@ha
/* 80290214 0028CDF4  90 01 00 04 */	stw r0, 4(r1)
/* 80290218 0028CDF8  38 84 03 14 */	addi r4, r4, it_80290314@l
/* 8029021C 0028CDFC  94 21 FF F8 */	stwu r1, -8(r1)
/* 80290220 0028CE00  4B FD E4 FD */	bl it_8026E71C
/* 80290224 0028CE04  38 60 00 00 */	li r3, 0
/* 80290228 0028CE08  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8029022C 0028CE0C  38 21 00 08 */	addi r1, r1, 8
/* 80290230 0028CE10  7C 08 03 A6 */	mtlr r0
/* 80290234 0028CE14  4E 80 00 20 */	blr

.global it_80290238
it_80290238:
/* 80290238 0028CE18  7C 08 02 A6 */	mflr r0
/* 8029023C 0028CE1C  38 80 00 01 */	li r4, 1
/* 80290240 0028CE20  90 01 00 04 */	stw r0, 4(r1)
/* 80290244 0028CE24  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 80290248 0028CE28  93 E1 00 34 */	stw r31, 0x34(r1)
/* 8029024C 0028CE2C  93 C1 00 30 */	stw r30, 0x30(r1)
/* 80290250 0028CE30  93 A1 00 2C */	stw r29, 0x2c(r1)
/* 80290254 0028CE34  7C 7D 1B 78 */	mr r29, r3
/* 80290258 0028CE38  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8029025C 0028CE3C  80 BF 00 C4 */	lwz r5, 0xc4(r31)
/* 80290260 0028CE40  88 1F 0D CE */	lbz r0, 0xdce(r31)
/* 80290264 0028CE44  50 80 26 F6 */	rlwimi r0, r4, 4, 0x1b, 0x1b
/* 80290268 0028CE48  83 C5 00 04 */	lwz r30, 4(r5)
/* 8029026C 0028CE4C  98 1F 0D CE */	stb r0, 0xdce(r31)
/* 80290270 0028CE50  4B FE 61 49 */	bl it_802763B8
/* 80290274 0028CE54  2C 03 00 01 */	cmpwi r3, 1
/* 80290278 0028CE58  41 82 00 6C */	beq .L_802902E4
/* 8029027C 0028CE5C  7F A3 EB 78 */	mr r3, r29
/* 80290280 0028CE60  4B FE 61 61 */	bl it_802763E0
/* 80290284 0028CE64  2C 03 00 02 */	cmpwi r3, 2
/* 80290288 0028CE68  40 82 00 24 */	bne .L_802902AC
/* 8029028C 0028CE6C  C0 3E 00 08 */	lfs f1, 8(r30)
/* 80290290 0028CE70  C0 1E 00 0C */	lfs f0, 0xc(r30)
/* 80290294 0028CE74  C0 5F 00 38 */	lfs f2, 0x38(r31)
/* 80290298 0028CE78  EC 21 00 28 */	fsubs f1, f1, f0
/* 8029029C 0028CE7C  C0 1F 00 50 */	lfs f0, 0x50(r31)
/* 802902A0 0028CE80  EC 02 00 7A */	fmadds f0, f2, f1, f0
/* 802902A4 0028CE84  D0 1F 00 50 */	stfs f0, 0x50(r31)
/* 802902A8 0028CE88  48 00 00 3C */	b .L_802902E4
.L_802902AC:
/* 802902AC 0028CE8C  7F A3 EB 78 */	mr r3, r29
/* 802902B0 0028CE90  4B FE 60 59 */	bl it_80276308
/* 802902B4 0028CE94  2C 03 00 08 */	cmpwi r3, 8
/* 802902B8 0028CE98  40 82 00 14 */	bne .L_802902CC
/* 802902BC 0028CE9C  C0 3F 00 4C */	lfs f1, 0x4c(r31)
/* 802902C0 0028CEA0  C0 1E 00 04 */	lfs f0, 4(r30)
/* 802902C4 0028CEA4  EC 01 00 2A */	fadds f0, f1, f0
/* 802902C8 0028CEA8  D0 1F 00 4C */	stfs f0, 0x4c(r31)
.L_802902CC:
/* 802902CC 0028CEAC  2C 03 00 04 */	cmpwi r3, 4
/* 802902D0 0028CEB0  40 82 00 14 */	bne .L_802902E4
/* 802902D4 0028CEB4  C0 3F 00 4C */	lfs f1, 0x4c(r31)
/* 802902D8 0028CEB8  C0 1E 00 04 */	lfs f0, 4(r30)
/* 802902DC 0028CEBC  EC 01 00 28 */	fsubs f0, f1, f0
/* 802902E0 0028CEC0  D0 1F 00 4C */	stfs f0, 0x4c(r31)
.L_802902E4:
/* 802902E4 0028CEC4  38 7F 00 00 */	addi r3, r31, 0
/* 802902E8 0028CEC8  38 80 00 F3 */	li r4, 0xf3
/* 802902EC 0028CECC  38 A0 00 7F */	li r5, 0x7f
/* 802902F0 0028CED0  38 C0 00 40 */	li r6, 0x40
/* 802902F4 0028CED4  4B FD AB 91 */	bl Item_8026AE84
/* 802902F8 0028CED8  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 802902FC 0028CEDC  83 E1 00 34 */	lwz r31, 0x34(r1)
/* 80290300 0028CEE0  83 C1 00 30 */	lwz r30, 0x30(r1)
/* 80290304 0028CEE4  83 A1 00 2C */	lwz r29, 0x2c(r1)
/* 80290308 0028CEE8  38 21 00 38 */	addi r1, r1, 0x38
/* 8029030C 0028CEEC  7C 08 03 A6 */	mtlr r0
/* 80290310 0028CEF0  4E 80 00 20 */	blr

.global it_80290314
it_80290314:
/* 80290314 0028CEF4  7C 08 02 A6 */	mflr r0
/* 80290318 0028CEF8  90 01 00 04 */	stw r0, 4(r1)
/* 8029031C 0028CEFC  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80290320 0028CF00  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80290324 0028CF04  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80290328 0028CF08  7C 7E 1B 78 */	mr r30, r3
/* 8029032C 0028CF0C  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 80290330 0028CF10  88 03 0D D4 */	lbz r0, 0xdd4(r3)
/* 80290334 0028CF14  3B E3 00 00 */	addi r31, r3, 0
/* 80290338 0028CF18  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 8029033C 0028CF1C  41 82 00 18 */	beq .L_80290354
/* 80290340 0028CF20  38 7E 00 00 */	addi r3, r30, 0
/* 80290344 0028CF24  38 80 00 04 */	li r4, 4
/* 80290348 0028CF28  38 A0 00 11 */	li r5, 0x11
/* 8029034C 0028CF2C  4B FD 8B 11 */	bl Item_80268E5C
/* 80290350 0028CF30  48 00 00 14 */	b .L_80290364
.L_80290354:
/* 80290354 0028CF34  38 7E 00 00 */	addi r3, r30, 0
/* 80290358 0028CF38  38 80 00 04 */	li r4, 4
/* 8029035C 0028CF3C  38 A0 00 02 */	li r5, 2
/* 80290360 0028CF40  4B FD 8A FD */	bl Item_80268E5C
.L_80290364:
/* 80290364 0028CF44  7F E3 FB 78 */	mr r3, r31
/* 80290368 0028CF48  4B FE 5F 49 */	bl it_802762B0
/* 8029036C 0028CF4C  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 80290370 0028CF50  7F C3 F3 78 */	mr r3, r30
/* 80290374 0028CF54  4B FE 30 E1 */	bl it_80273454
/* 80290378 0028CF58  80 1F 00 C0 */	lwz r0, 0xc0(r31)
/* 8029037C 0028CF5C  2C 00 00 00 */	cmpwi r0, 0
/* 80290380 0028CF60  40 82 00 20 */	bne .L_802903A0
/* 80290384 0028CF64  7F C3 F3 78 */	mr r3, r30
/* 80290388 0028CF68  4B FE 43 B9 */	bl it_80274740
/* 8029038C 0028CF6C  38 7E 00 00 */	addi r3, r30, 0
/* 80290390 0028CF70  38 80 00 00 */	li r4, 0
/* 80290394 0028CF74  4B FE 62 29 */	bl it_802765BC
/* 80290398 0028CF78  7F C3 F3 78 */	mr r3, r30
/* 8029039C 0028CF7C  4B FF FE 9D */	bl it_80290238
.L_802903A0:
/* 802903A0 0028CF80  7F C3 F3 78 */	mr r3, r30
/* 802903A4 0028CF84  4B FD B0 05 */	bl it_8026B3A8
/* 802903A8 0028CF88  3C 60 80 29 */	lis r3, it_802908D8@ha
/* 802903AC 0028CF8C  38 03 08 D8 */	addi r0, r3, it_802908D8@l
/* 802903B0 0028CF90  90 1F 0D 24 */	stw r0, 0xd24(r31)
/* 802903B4 0028CF94  38 80 00 00 */	li r4, 0
/* 802903B8 0028CF98  38 7E 00 00 */	addi r3, r30, 0
/* 802903BC 0028CF9C  88 1F 0D CB */	lbz r0, 0xdcb(r31)
/* 802903C0 0028CFA0  50 80 2E B4 */	rlwimi r0, r4, 5, 0x1a, 0x1a
/* 802903C4 0028CFA4  98 1F 0D CB */	stb r0, 0xdcb(r31)
/* 802903C8 0028CFA8  4B FE 53 19 */	bl it_802756E0
/* 802903CC 0028CFAC  7F C3 F3 78 */	mr r3, r30
/* 802903D0 0028CFB0  4B FE 50 75 */	bl it_80275444
/* 802903D4 0028CFB4  7F C3 F3 78 */	mr r3, r30
/* 802903D8 0028CFB8  4B FE 50 FD */	bl it_802754D4
/* 802903DC 0028CFBC  88 1F 0D D4 */	lbz r0, 0xdd4(r31)
/* 802903E0 0028CFC0  38 60 00 01 */	li r3, 1
/* 802903E4 0028CFC4  50 60 3E 30 */	rlwimi r0, r3, 7, 0x18, 0x18
/* 802903E8 0028CFC8  98 1F 0D D4 */	stb r0, 0xdd4(r31)
/* 802903EC 0028CFCC  80 01 00 24 */	lwz r0, 0x24(r1)
/* 802903F0 0028CFD0  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 802903F4 0028CFD4  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 802903F8 0028CFD8  38 21 00 20 */	addi r1, r1, 0x20
/* 802903FC 0028CFDC  7C 08 03 A6 */	mtlr r0
/* 80290400 0028CFE0  4E 80 00 20 */	blr

.global it_80290404
it_80290404:
/* 80290404 0028CFE4  7C 08 02 A6 */	mflr r0
/* 80290408 0028CFE8  90 01 00 04 */	stw r0, 4(r1)
/* 8029040C 0028CFEC  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80290410 0028CFF0  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80290414 0028CFF4  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80290418 0028CFF8  93 A1 00 14 */	stw r29, 0x14(r1)
/* 8029041C 0028CFFC  7C 7D 1B 78 */	mr r29, r3
/* 80290420 0028D000  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80290424 0028D004  3B DF 03 78 */	addi r30, r31, 0x378
/* 80290428 0028D008  4B FD D1 DD */	bl it_8026D604
/* 8029042C 0028D00C  2C 03 00 00 */	cmpwi r3, 0
/* 80290430 0028D010  41 82 00 1C */	beq .L_8029044C
/* 80290434 0028D014  7F C3 F3 78 */	mr r3, r30
/* 80290438 0028D018  80 9F 0C 30 */	lwz r4, 0xc30(r31)
/* 8029043C 0028D01C  4B DB 31 1D */	bl mpColl_80043558
/* 80290440 0028D020  38 7D 00 00 */	addi r3, r29, 0
/* 80290444 0028D024  38 80 00 00 */	li r4, 0
/* 80290448 0028D028  4B FE 64 ED */	bl it_80276934
.L_8029044C:
/* 8029044C 0028D02C  3C 60 80 29 */	lis r3, it_8029047C@ha
/* 80290450 0028D030  38 83 04 7C */	addi r4, r3, it_8029047C@l
/* 80290454 0028D034  38 7D 00 00 */	addi r3, r29, 0
/* 80290458 0028D038  4B FD D4 E1 */	bl it_8026D938
/* 8029045C 0028D03C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80290460 0028D040  38 60 00 00 */	li r3, 0
/* 80290464 0028D044  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80290468 0028D048  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8029046C 0028D04C  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 80290470 0028D050  38 21 00 20 */	addi r1, r1, 0x20
/* 80290474 0028D054  7C 08 03 A6 */	mtlr r0
/* 80290478 0028D058  4E 80 00 20 */	blr

.global it_8029047C
it_8029047C:
/* 8029047C 0028D05C  7C 08 02 A6 */	mflr r0
/* 80290480 0028D060  38 80 00 05 */	li r4, 5
/* 80290484 0028D064  90 01 00 04 */	stw r0, 4(r1)
/* 80290488 0028D068  38 A0 00 11 */	li r5, 0x11
/* 8029048C 0028D06C  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 80290490 0028D070  93 E1 00 24 */	stw r31, 0x24(r1)
/* 80290494 0028D074  93 C1 00 20 */	stw r30, 0x20(r1)
/* 80290498 0028D078  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 8029049C 0028D07C  93 81 00 18 */	stw r28, 0x18(r1)
/* 802904A0 0028D080  7C 7C 1B 78 */	mr r28, r3
/* 802904A4 0028D084  83 A3 00 2C */	lwz r29, 0x2c(r3)
/* 802904A8 0028D088  4B FD 89 B5 */	bl Item_80268E5C
/* 802904AC 0028D08C  7F A3 EB 78 */	mr r3, r29
/* 802904B0 0028D090  4B FE 5E 0D */	bl it_802762BC
/* 802904B4 0028D094  83 DC 00 2C */	lwz r30, 0x2c(r28)
/* 802904B8 0028D098  7F 83 E3 78 */	mr r3, r28
/* 802904BC 0028D09C  4B FE 2F 99 */	bl it_80273454
/* 802904C0 0028D0A0  80 1E 00 C0 */	lwz r0, 0xc0(r30)
/* 802904C4 0028D0A4  2C 00 00 00 */	cmpwi r0, 0
/* 802904C8 0028D0A8  40 82 00 20 */	bne .L_802904E8
/* 802904CC 0028D0AC  7F 83 E3 78 */	mr r3, r28
/* 802904D0 0028D0B0  4B FE 42 71 */	bl it_80274740
/* 802904D4 0028D0B4  38 7C 00 00 */	addi r3, r28, 0
/* 802904D8 0028D0B8  38 80 00 00 */	li r4, 0
/* 802904DC 0028D0BC  4B FE 60 E1 */	bl it_802765BC
/* 802904E0 0028D0C0  7F 83 E3 78 */	mr r3, r28
/* 802904E4 0028D0C4  4B FF FD 55 */	bl it_80290238
.L_802904E8:
/* 802904E8 0028D0C8  7F 83 E3 78 */	mr r3, r28
/* 802904EC 0028D0CC  4B FD AE BD */	bl it_8026B3A8
/* 802904F0 0028D0D0  3C 60 80 29 */	lis r3, it_802908D8@ha
/* 802904F4 0028D0D4  38 03 08 D8 */	addi r0, r3, it_802908D8@l
/* 802904F8 0028D0D8  90 1E 0D 24 */	stw r0, 0xd24(r30)
/* 802904FC 0028D0DC  3B E0 00 00 */	li r31, 0
/* 80290500 0028D0E0  38 7C 00 00 */	addi r3, r28, 0
/* 80290504 0028D0E4  88 1E 0D CB */	lbz r0, 0xdcb(r30)
/* 80290508 0028D0E8  53 E0 2E B4 */	rlwimi r0, r31, 5, 0x1a, 0x1a
/* 8029050C 0028D0EC  98 1E 0D CB */	stb r0, 0xdcb(r30)
/* 80290510 0028D0F0  4B FE 51 D1 */	bl it_802756E0
/* 80290514 0028D0F4  7F 83 E3 78 */	mr r3, r28
/* 80290518 0028D0F8  4B FE 4F 2D */	bl it_80275444
/* 8029051C 0028D0FC  7F 83 E3 78 */	mr r3, r28
/* 80290520 0028D100  4B FE 4F B5 */	bl it_802754D4
/* 80290524 0028D104  88 1E 0D D4 */	lbz r0, 0xdd4(r30)
/* 80290528 0028D108  38 60 00 01 */	li r3, 1
/* 8029052C 0028D10C  50 60 3E 30 */	rlwimi r0, r3, 7, 0x18, 0x18
/* 80290530 0028D110  98 1E 0D D4 */	stb r0, 0xdd4(r30)
/* 80290534 0028D114  88 1D 0D CE */	lbz r0, 0xdce(r29)
/* 80290538 0028D118  53 E0 26 F6 */	rlwimi r0, r31, 4, 0x1b, 0x1b
/* 8029053C 0028D11C  98 1D 0D CE */	stb r0, 0xdce(r29)
/* 80290540 0028D120  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 80290544 0028D124  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 80290548 0028D128  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 8029054C 0028D12C  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 80290550 0028D130  83 81 00 18 */	lwz r28, 0x18(r1)
/* 80290554 0028D134  38 21 00 28 */	addi r1, r1, 0x28
/* 80290558 0028D138  7C 08 03 A6 */	mtlr r0
/* 8029055C 0028D13C  4E 80 00 20 */	blr

.global it_80290560
it_80290560:
/* 80290560 0028D140  7C 08 02 A6 */	mflr r0
/* 80290564 0028D144  90 01 00 04 */	stw r0, 4(r1)
/* 80290568 0028D148  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8029056C 0028D14C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80290570 0028D150  7C 7F 1B 78 */	mr r31, r3
/* 80290574 0028D154  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 80290578 0028D158  80 84 00 CC */	lwz r4, 0xcc(r4)
/* 8029057C 0028D15C  C0 24 00 10 */	lfs f1, 0x10(r4)
/* 80290580 0028D160  C0 44 00 14 */	lfs f2, 0x14(r4)
/* 80290584 0028D164  4B FE 22 DD */	bl it_80272860
/* 80290588 0028D168  80 8D B6 88 */	lwz r4, it_804D6D28@sda21(r13)
/* 8029058C 0028D16C  7F E3 FB 78 */	mr r3, r31
/* 80290590 0028D170  C0 24 00 68 */	lfs f1, 0x68(r4)
/* 80290594 0028D174  4B FE 40 C5 */	bl it_80274658
/* 80290598 0028D178  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8029059C 0028D17C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 802905A0 0028D180  38 21 00 18 */	addi r1, r1, 0x18
/* 802905A4 0028D184  7C 08 03 A6 */	mtlr r0
/* 802905A8 0028D188  4E 80 00 20 */	blr

.global it_802905AC
it_802905AC:
/* 802905AC 0028D18C  7C 08 02 A6 */	mflr r0
/* 802905B0 0028D190  3C 80 80 29 */	lis r4, it_80290314@ha
/* 802905B4 0028D194  90 01 00 04 */	stw r0, 4(r1)
/* 802905B8 0028D198  38 84 03 14 */	addi r4, r4, it_80290314@l
/* 802905BC 0028D19C  94 21 FF F8 */	stwu r1, -8(r1)
/* 802905C0 0028D1A0  4B FD E1 5D */	bl it_8026E71C
/* 802905C4 0028D1A4  38 60 00 00 */	li r3, 0
/* 802905C8 0028D1A8  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802905CC 0028D1AC  38 21 00 08 */	addi r1, r1, 8
/* 802905D0 0028D1B0  7C 08 03 A6 */	mtlr r0
/* 802905D4 0028D1B4  4E 80 00 20 */	blr

.global it_802905D8
it_802905D8:
/* 802905D8 0028D1B8  7C 08 02 A6 */	mflr r0
/* 802905DC 0028D1BC  38 80 00 06 */	li r4, 6
/* 802905E0 0028D1C0  90 01 00 04 */	stw r0, 4(r1)
/* 802905E4 0028D1C4  38 A0 00 02 */	li r5, 2
/* 802905E8 0028D1C8  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 802905EC 0028D1CC  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 802905F0 0028D1D0  3B E3 00 00 */	addi r31, r3, 0
/* 802905F4 0028D1D4  4B FD 88 69 */	bl Item_80268E5C
/* 802905F8 0028D1D8  7F E3 FB 78 */	mr r3, r31
/* 802905FC 0028D1DC  48 00 00 19 */	bl it_80290614
/* 80290600 0028D1E0  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80290604 0028D1E4  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80290608 0028D1E8  38 21 00 20 */	addi r1, r1, 0x20
/* 8029060C 0028D1EC  7C 08 03 A6 */	mtlr r0
/* 80290610 0028D1F0  4E 80 00 20 */	blr

.global it_80290614
it_80290614:
/* 80290614 0028D1F4  7C 08 02 A6 */	mflr r0
/* 80290618 0028D1F8  38 80 00 10 */	li r4, 0x10
/* 8029061C 0028D1FC  90 01 00 04 */	stw r0, 4(r1)
/* 80290620 0028D200  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 80290624 0028D204  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 80290628 0028D208  93 C1 00 28 */	stw r30, 0x28(r1)
/* 8029062C 0028D20C  7C 7E 1B 78 */	mr r30, r3
/* 80290630 0028D210  80 63 00 28 */	lwz r3, 0x28(r3)
/* 80290634 0028D214  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 80290638 0028D218  48 0E 17 65 */	bl HSD_JObjSetFlagsAll
/* 8029063C 0028D21C  7F C3 F3 78 */	mr r3, r30
/* 80290640 0028D220  4B FD B6 E5 */	bl it_8026BD24
/* 80290644 0028D224  7F C3 F3 78 */	mr r3, r30
/* 80290648 0028D228  4B FE 4B 45 */	bl it_8027518C
/* 8029064C 0028D22C  3C 80 00 44 */	lis r4, 0x00440061@ha
/* 80290650 0028D230  38 7E 00 00 */	addi r3, r30, 0
/* 80290654 0028D234  38 84 00 61 */	addi r4, r4, 0x00440061@l
/* 80290658 0028D238  4B FE AC 31 */	bl it_8027B288
/* 8029065C 0028D23C  7F C3 F3 78 */	mr r3, r30
/* 80290660 0028D240  4B FE AF 05 */	bl it_8027B564
/* 80290664 0028D244  80 BF 00 4C */	lwz r5, 0x4c(r31)
/* 80290668 0028D248  38 61 00 14 */	addi r3, r1, 0x14
/* 8029066C 0028D24C  80 1F 00 50 */	lwz r0, 0x50(r31)
/* 80290670 0028D250  38 80 00 78 */	li r4, 0x78
/* 80290674 0028D254  C0 22 D0 B8 */	lfs f1, it_804DCA98@sda21(r2)
/* 80290678 0028D258  90 A1 00 14 */	stw r5, 0x14(r1)
/* 8029067C 0028D25C  C0 42 D0 BC */	lfs f2, it_804DCA9C@sda21(r2)
/* 80290680 0028D260  90 01 00 18 */	stw r0, 0x18(r1)
/* 80290684 0028D264  C0 62 D0 C0 */	lfs f3, it_804DCAA0@sda21(r2)
/* 80290688 0028D268  80 1F 00 54 */	lwz r0, 0x54(r31)
/* 8029068C 0028D26C  90 01 00 1C */	stw r0, 0x1c(r1)
/* 80290690 0028D270  4B D8 13 4D */	bl lb_800119DC
/* 80290694 0028D274  7F C3 F3 78 */	mr r3, r30
/* 80290698 0028D278  4B FE 25 71 */	bl it_80272C08
/* 8029069C 0028D27C  7F C3 F3 78 */	mr r3, r30
/* 802906A0 0028D280  4B FE 4D A5 */	bl it_80275444
/* 802906A4 0028D284  7F C3 F3 78 */	mr r3, r30
/* 802906A8 0028D288  4B FE 50 29 */	bl it_802756D0
/* 802906AC 0028D28C  80 01 00 34 */	lwz r0, 0x34(r1)
/* 802906B0 0028D290  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 802906B4 0028D294  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 802906B8 0028D298  38 21 00 30 */	addi r1, r1, 0x30
/* 802906BC 0028D29C  7C 08 03 A6 */	mtlr r0
/* 802906C0 0028D2A0  4E 80 00 20 */	blr

.global it_802906C4
it_802906C4:
/* 802906C4 0028D2A4  7C 08 02 A6 */	mflr r0
/* 802906C8 0028D2A8  90 01 00 04 */	stw r0, 4(r1)
/* 802906CC 0028D2AC  94 21 FF F8 */	stwu r1, -8(r1)
/* 802906D0 0028D2B0  4B FE 4B 09 */	bl it_802751D8
/* 802906D4 0028D2B4  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802906D8 0028D2B8  38 21 00 08 */	addi r1, r1, 8
/* 802906DC 0028D2BC  7C 08 03 A6 */	mtlr r0
/* 802906E0 0028D2C0  4E 80 00 20 */	blr

.global it_802906E4
it_802906E4:
/* 802906E4 0028D2C4  7C 08 02 A6 */	mflr r0
/* 802906E8 0028D2C8  90 01 00 04 */	stw r0, 4(r1)
/* 802906EC 0028D2CC  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 802906F0 0028D2D0  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 802906F4 0028D2D4  7C 7F 1B 78 */	mr r31, r3
/* 802906F8 0028D2D8  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 802906FC 0028D2DC  80 03 00 24 */	lwz r0, 0x24(r3)
/* 80290700 0028D2E0  2C 00 00 03 */	cmpwi r0, 3
/* 80290704 0028D2E4  40 82 00 1C */	bne .L_80290720
/* 80290708 0028D2E8  7F E3 FB 78 */	mr r3, r31
/* 8029070C 0028D2EC  4B FE 26 A5 */	bl itColl_BounceOffVictim
/* 80290710 0028D2F0  7F E3 FB 78 */	mr r3, r31
/* 80290714 0028D2F4  4B FD AC 95 */	bl it_8026B3A8
/* 80290718 0028D2F8  7F E3 FB 78 */	mr r3, r31
/* 8029071C 0028D2FC  4B FE 1E B9 */	bl it_802725D4
.L_80290720:
/* 80290720 0028D300  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80290724 0028D304  38 60 00 00 */	li r3, 0
/* 80290728 0028D308  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8029072C 0028D30C  38 21 00 20 */	addi r1, r1, 0x20
/* 80290730 0028D310  7C 08 03 A6 */	mtlr r0
/* 80290734 0028D314  4E 80 00 20 */	blr

.global it_80290738
it_80290738:
/* 80290738 0028D318  7C 08 02 A6 */	mflr r0
/* 8029073C 0028D31C  90 01 00 04 */	stw r0, 4(r1)
/* 80290740 0028D320  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 80290744 0028D324  93 E1 00 24 */	stw r31, 0x24(r1)
/* 80290748 0028D328  7C 7F 1B 78 */	mr r31, r3
/* 8029074C 0028D32C  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 80290750 0028D330  80 03 00 24 */	lwz r0, 0x24(r3)
/* 80290754 0028D334  2C 00 00 04 */	cmpwi r0, 4
/* 80290758 0028D338  41 82 00 0C */	beq .L_80290764
/* 8029075C 0028D33C  2C 00 00 05 */	cmpwi r0, 5
/* 80290760 0028D340  40 82 00 1C */	bne .L_8029077C
.L_80290764:
/* 80290764 0028D344  38 7F 00 00 */	addi r3, r31, 0
/* 80290768 0028D348  38 80 00 06 */	li r4, 6
/* 8029076C 0028D34C  38 A0 00 02 */	li r5, 2
/* 80290770 0028D350  4B FD 86 ED */	bl Item_80268E5C
/* 80290774 0028D354  7F E3 FB 78 */	mr r3, r31
/* 80290778 0028D358  4B FF FE 9D */	bl it_80290614
.L_8029077C:
/* 8029077C 0028D35C  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 80290780 0028D360  38 60 00 00 */	li r3, 0
/* 80290784 0028D364  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 80290788 0028D368  38 21 00 28 */	addi r1, r1, 0x28
/* 8029078C 0028D36C  7C 08 03 A6 */	mtlr r0
/* 80290790 0028D370  4E 80 00 20 */	blr

.global it_80290794
it_80290794:
/* 80290794 0028D374  7C 08 02 A6 */	mflr r0
/* 80290798 0028D378  38 80 00 07 */	li r4, 7
/* 8029079C 0028D37C  90 01 00 04 */	stw r0, 4(r1)
/* 802907A0 0028D380  38 A0 00 02 */	li r5, 2
/* 802907A4 0028D384  94 21 FF F8 */	stwu r1, -8(r1)
/* 802907A8 0028D388  4B FD 86 B5 */	bl Item_80268E5C
/* 802907AC 0028D38C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802907B0 0028D390  38 21 00 08 */	addi r1, r1, 8
/* 802907B4 0028D394  7C 08 03 A6 */	mtlr r0
/* 802907B8 0028D398  4E 80 00 20 */	blr

.global it_802907BC
it_802907BC:
/* 802907BC 0028D39C  7C 08 02 A6 */	mflr r0
/* 802907C0 0028D3A0  3C 80 80 29 */	lis r4, it_8028FF1C@ha
/* 802907C4 0028D3A4  90 01 00 04 */	stw r0, 4(r1)
/* 802907C8 0028D3A8  3C A0 80 29 */	lis r5, it_8028FF8C@ha
/* 802907CC 0028D3AC  38 84 FF 1C */	addi r4, r4, it_8028FF1C@l
/* 802907D0 0028D3B0  94 21 FF F8 */	stwu r1, -8(r1)
/* 802907D4 0028D3B4  38 A5 FF 8C */	addi r5, r5, it_8028FF8C@l
/* 802907D8 0028D3B8  4B FD E0 ED */	bl it_8026E8C4
/* 802907DC 0028D3BC  38 60 00 00 */	li r3, 0
/* 802907E0 0028D3C0  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802907E4 0028D3C4  38 21 00 08 */	addi r1, r1, 8
/* 802907E8 0028D3C8  7C 08 03 A6 */	mtlr r0
/* 802907EC 0028D3CC  4E 80 00 20 */	blr

.global it_802907F0
it_802907F0:
/* 802907F0 0028D3D0  7C 08 02 A6 */	mflr r0
/* 802907F4 0028D3D4  90 01 00 04 */	stw r0, 4(r1)
/* 802907F8 0028D3D8  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 802907FC 0028D3DC  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80290800 0028D3E0  7C 7F 1B 78 */	mr r31, r3
/* 80290804 0028D3E4  4B FE 25 AD */	bl itColl_BounceOffVictim
/* 80290808 0028D3E8  7F E3 FB 78 */	mr r3, r31
/* 8029080C 0028D3EC  4B FD AB 9D */	bl it_8026B3A8
/* 80290810 0028D3F0  7F E3 FB 78 */	mr r3, r31
/* 80290814 0028D3F4  4B FE 1D C1 */	bl it_802725D4
/* 80290818 0028D3F8  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8029081C 0028D3FC  38 60 00 00 */	li r3, 0
/* 80290820 0028D400  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80290824 0028D404  38 21 00 18 */	addi r1, r1, 0x18
/* 80290828 0028D408  7C 08 03 A6 */	mtlr r0
/* 8029082C 0028D40C  4E 80 00 20 */	blr

.global it_80290830
it_80290830:
/* 80290830 0028D410  7C 08 02 A6 */	mflr r0
/* 80290834 0028D414  90 01 00 04 */	stw r0, 4(r1)
/* 80290838 0028D418  94 21 FF F8 */	stwu r1, -8(r1)
/* 8029083C 0028D41C  4B FE 27 F5 */	bl it_80273030
/* 80290840 0028D420  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80290844 0028D424  38 21 00 08 */	addi r1, r1, 8
/* 80290848 0028D428  7C 08 03 A6 */	mtlr r0
/* 8029084C 0028D42C  4E 80 00 20 */	blr

.global it_80290850
it_80290850:
/* 80290850 0028D430  7C 08 02 A6 */	mflr r0
/* 80290854 0028D434  90 01 00 04 */	stw r0, 4(r1)
/* 80290858 0028D438  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8029085C 0028D43C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80290860 0028D440  7C 7F 1B 78 */	mr r31, r3
/* 80290864 0028D444  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 80290868 0028D448  80 03 00 24 */	lwz r0, 0x24(r3)
/* 8029086C 0028D44C  2C 00 00 03 */	cmpwi r0, 3
/* 80290870 0028D450  40 82 00 1C */	bne .L_8029088C
/* 80290874 0028D454  7F E3 FB 78 */	mr r3, r31
/* 80290878 0028D458  4B FE 25 39 */	bl itColl_BounceOffVictim
/* 8029087C 0028D45C  7F E3 FB 78 */	mr r3, r31
/* 80290880 0028D460  4B FD AB 29 */	bl it_8026B3A8
/* 80290884 0028D464  7F E3 FB 78 */	mr r3, r31
/* 80290888 0028D468  4B FE 1D 4D */	bl it_802725D4
.L_8029088C:
/* 8029088C 0028D46C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80290890 0028D470  38 60 00 00 */	li r3, 0
/* 80290894 0028D474  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80290898 0028D478  38 21 00 20 */	addi r1, r1, 0x20
/* 8029089C 0028D47C  7C 08 03 A6 */	mtlr r0
/* 802908A0 0028D480  4E 80 00 20 */	blr

.global it_802908A4
it_802908A4:
/* 802908A4 0028D484  7C 08 02 A6 */	mflr r0
/* 802908A8 0028D488  90 01 00 04 */	stw r0, 4(r1)
/* 802908AC 0028D48C  94 21 FF F8 */	stwu r1, -8(r1)
/* 802908B0 0028D490  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 802908B4 0028D494  80 04 00 24 */	lwz r0, 0x24(r4)
/* 802908B8 0028D498  2C 00 00 03 */	cmpwi r0, 3
/* 802908BC 0028D49C  40 82 00 08 */	bne .L_802908C4
/* 802908C0 0028D4A0  4B FE 27 B9 */	bl itColl_BounceOffShield
.L_802908C4:
/* 802908C4 0028D4A4  38 60 00 00 */	li r3, 0
/* 802908C8 0028D4A8  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802908CC 0028D4AC  38 21 00 08 */	addi r1, r1, 8
/* 802908D0 0028D4B0  7C 08 03 A6 */	mtlr r0
/* 802908D4 0028D4B4  4E 80 00 20 */	blr

.global it_802908D8
it_802908D8:
/* 802908D8 0028D4B8  7C 08 02 A6 */	mflr r0
/* 802908DC 0028D4BC  38 80 00 06 */	li r4, 6
/* 802908E0 0028D4C0  90 01 00 04 */	stw r0, 4(r1)
/* 802908E4 0028D4C4  38 A0 00 02 */	li r5, 2
/* 802908E8 0028D4C8  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 802908EC 0028D4CC  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 802908F0 0028D4D0  3B E3 00 00 */	addi r31, r3, 0
/* 802908F4 0028D4D4  4B FD 85 69 */	bl Item_80268E5C
/* 802908F8 0028D4D8  7F E3 FB 78 */	mr r3, r31
/* 802908FC 0028D4DC  4B FF FD 19 */	bl it_80290614
/* 80290900 0028D4E0  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80290904 0028D4E4  38 60 00 00 */	li r3, 0
/* 80290908 0028D4E8  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8029090C 0028D4EC  38 21 00 20 */	addi r1, r1, 0x20
/* 80290910 0028D4F0  7C 08 03 A6 */	mtlr r0
/* 80290914 0028D4F4  4E 80 00 20 */	blr

.global it_80290918
it_80290918:
/* 80290918 0028D4F8  7C 08 02 A6 */	mflr r0
/* 8029091C 0028D4FC  90 01 00 04 */	stw r0, 4(r1)
/* 80290920 0028D500  94 21 FF F8 */	stwu r1, -8(r1)
/* 80290924 0028D504  4B FD AF 71 */	bl it_8026B894
/* 80290928 0028D508  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8029092C 0028D50C  38 21 00 08 */	addi r1, r1, 8
/* 80290930 0028D510  7C 08 03 A6 */	mtlr r0
/* 80290934 0028D514  4E 80 00 20 */	blr


.section .data
    .balign 8
.global it_803F5E00
it_803F5E00:
    .4byte -1
    .4byte NULL
    .4byte NULL
    .4byte it_8028FF60
    .4byte -1
    .4byte NULL
    .4byte it_80290070
    .4byte it_802900A0
    .4byte -1
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 1
    .4byte NULL
    .4byte it_802901C0
    .4byte it_8029020C
    .4byte 0
    .4byte NULL
    .4byte NULL
    .4byte it_80290404
    .4byte 0
    .4byte NULL
    .4byte it_80290560
    .4byte it_802905AC
    .4byte 2
    .4byte it_802906C4
    .4byte NULL
    .4byte NULL
    .4byte -1
    .4byte NULL
    .4byte NULL
    .4byte it_802907BC
.global it_803F5E80
it_803F5E80:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"


.section .sdata
    .balign 8
.global it_804D52B0
it_804D52B0:
    .asciz "jobj.h"
    .balign 4
.global it_804D52B8
it_804D52B8:
    .asciz "jobj"
    .balign 4


.section .sdata2
    .balign 8
.global it_804DCA98
it_804DCA98:
    .4byte 0x3F800000
.global it_804DCA9C
it_804DCA9C:
    .4byte 0x3CA3D70A
.global it_804DCAA0
it_804DCAA0:
    .4byte 0x3F860A92
