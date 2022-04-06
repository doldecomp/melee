.include "macros.inc"

.section .text

.global lbl_8015FD24
lbl_8015FD24:
/* 8015FD24 0015C904  7C 08 02 A6 */	mflr r0
/* 8015FD28 0015C908  38 60 00 05 */	li r3, 5
/* 8015FD2C 0015C90C  90 01 00 04 */	stw r0, 4(r1)
/* 8015FD30 0015C910  94 21 FF F8 */	stwu r1, -8(r1)
/* 8015FD34 0015C914  48 1E E2 2D */	bl PADSetSpec
/* 8015FD38 0015C918  3C 80 80 47 */	lis r4, lbl_8046B108@ha
/* 8015FD3C 0015C91C  3C 60 80 47 */	lis r3, lbl_8046B1F8@ha
/* 8015FD40 0015C920  38 C3 B1 F8 */	addi r6, r3, lbl_8046B1F8@l
/* 8015FD44 0015C924  38 84 B1 08 */	addi r4, r4, lbl_8046B108@l
/* 8015FD48 0015C928  38 60 00 05 */	li r3, 5
/* 8015FD4C 0015C92C  38 A0 00 0C */	li r5, 0xc
/* 8015FD50 0015C930  48 21 80 49 */	bl func_80377D98
/* 8015FD54 0015C934  3C 60 80 4C */	lis r3, HSD_PadLibData@ha
/* 8015FD58 0015C938  38 A3 1F 78 */	addi r5, r3, HSD_PadLibData@l
/* 8015FD5C 0015C93C  38 C0 00 00 */	li r6, 0
/* 8015FD60 0015C940  98 C5 00 1C */	stb r6, 0x1c(r5)
/* 8015FD64 0015C944  38 80 00 01 */	li r4, 1
/* 8015FD68 0015C948  38 60 00 50 */	li r3, 0x50
/* 8015FD6C 0015C94C  98 85 00 1D */	stb r4, 0x1d(r5)
/* 8015FD70 0015C950  38 00 00 8C */	li r0, 0x8c
/* 8015FD74 0015C954  98 65 00 1E */	stb r3, 0x1e(r5)
/* 8015FD78 0015C958  98 C5 00 1F */	stb r6, 0x1f(r5)
/* 8015FD7C 0015C95C  98 65 00 26 */	stb r3, 0x26(r5)
/* 8015FD80 0015C960  98 85 00 20 */	stb r4, 0x20(r5)
/* 8015FD84 0015C964  98 05 00 21 */	stb r0, 0x21(r5)
/* 8015FD88 0015C968  98 C5 00 22 */	stb r6, 0x22(r5)
/* 8015FD8C 0015C96C  98 05 00 27 */	stb r0, 0x27(r5)
/* 8015FD90 0015C970  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8015FD94 0015C974  38 21 00 08 */	addi r1, r1, 8
/* 8015FD98 0015C978  7C 08 03 A6 */	mtlr r0
/* 8015FD9C 0015C97C  4E 80 00 20 */	blr 

.global lbl_8015FDA0
lbl_8015FDA0:
/* 8015FDA0 0015C980  4E 80 00 20 */	blr 

.global func_8015FDA4
func_8015FDA4:
/* 8015FDA4 0015C984  7C 08 02 A6 */	mflr r0
/* 8015FDA8 0015C988  3C 60 80 3D */	lis r3, lbl_803D4AC8@ha
/* 8015FDAC 0015C98C  90 01 00 04 */	stw r0, 4(r1)
/* 8015FDB0 0015C990  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8015FDB4 0015C994  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8015FDB8 0015C998  3B E3 4A C8 */	addi r31, r3, lbl_803D4AC8@l
/* 8015FDBC 0015C99C  38 7F 00 00 */	addi r3, r31, 0
/* 8015FDC0 0015C9A0  48 1D 7B AD */	bl DVDConvertPathToEntrynum
/* 8015FDC4 0015C9A4  2C 03 FF FF */	cmpwi r3, -1
/* 8015FDC8 0015C9A8  41 82 00 B4 */	beq lbl_8015FE7C
/* 8015FDCC 0015C9AC  A0 6D B4 90 */	lhz r3, lbl_804D6B30@sda21(r13)
/* 8015FDD0 0015C9B0  38 00 00 01 */	li r0, 1
/* 8015FDD4 0015C9B4  90 0D B4 80 */	stw r0, lbl_804D6B20@sda21(r13)
/* 8015FDD8 0015C9B8  54 60 05 6B */	rlwinm. r0, r3, 0, 0x15, 0x15
/* 8015FDDC 0015C9BC  41 82 00 5C */	beq lbl_8015FE38
/* 8015FDE0 0015C9C0  80 0D 93 68 */	lwz r0, lbl_804D4A08@sda21(r13)
/* 8015FDE4 0015C9C4  2C 00 00 03 */	cmpwi r0, 3
/* 8015FDE8 0015C9C8  41 82 00 34 */	beq lbl_8015FE1C
/* 8015FDEC 0015C9CC  40 80 00 14 */	bge lbl_8015FE00
/* 8015FDF0 0015C9D0  2C 00 00 01 */	cmpwi r0, 1
/* 8015FDF4 0015C9D4  41 82 00 18 */	beq lbl_8015FE0C
/* 8015FDF8 0015C9D8  40 80 00 1C */	bge lbl_8015FE14
/* 8015FDFC 0015C9DC  48 00 00 30 */	b lbl_8015FE2C
lbl_8015FE00:
/* 8015FE00 0015C9E0  2C 00 00 05 */	cmpwi r0, 5
/* 8015FE04 0015C9E4  40 80 00 28 */	bge lbl_8015FE2C
/* 8015FE08 0015C9E8  48 00 00 1C */	b lbl_8015FE24
lbl_8015FE0C:
/* 8015FE0C 0015C9EC  38 00 00 03 */	li r0, 3
/* 8015FE10 0015C9F0  48 00 00 20 */	b lbl_8015FE30
lbl_8015FE14:
/* 8015FE14 0015C9F4  38 00 00 04 */	li r0, 4
/* 8015FE18 0015C9F8  48 00 00 18 */	b lbl_8015FE30
lbl_8015FE1C:
/* 8015FE1C 0015C9FC  38 00 00 01 */	li r0, 1
/* 8015FE20 0015CA00  48 00 00 10 */	b lbl_8015FE30
lbl_8015FE24:
/* 8015FE24 0015CA04  38 00 00 02 */	li r0, 2
/* 8015FE28 0015CA08  48 00 00 08 */	b lbl_8015FE30
lbl_8015FE2C:
/* 8015FE2C 0015CA0C  38 00 00 02 */	li r0, 2
lbl_8015FE30:
/* 8015FE30 0015CA10  90 0D 93 68 */	stw r0, lbl_804D4A08@sda21(r13)
/* 8015FE34 0015CA14  48 00 00 6C */	b lbl_8015FEA0
lbl_8015FE38:
/* 8015FE38 0015CA18  54 60 05 29 */	rlwinm. r0, r3, 0, 0x14, 0x14
/* 8015FE3C 0015CA1C  41 82 00 64 */	beq lbl_8015FEA0
/* 8015FE40 0015CA20  80 0D 93 68 */	lwz r0, lbl_804D4A08@sda21(r13)
/* 8015FE44 0015CA24  2C 00 00 02 */	cmpwi r0, 2
/* 8015FE48 0015CA28  7C 03 03 78 */	mr r3, r0
/* 8015FE4C 0015CA2C  41 82 00 1C */	beq lbl_8015FE68
/* 8015FE50 0015CA30  40 80 00 1C */	bge lbl_8015FE6C
/* 8015FE54 0015CA34  2C 00 00 01 */	cmpwi r0, 1
/* 8015FE58 0015CA38  40 80 00 08 */	bge lbl_8015FE60
/* 8015FE5C 0015CA3C  48 00 00 10 */	b lbl_8015FE6C
lbl_8015FE60:
/* 8015FE60 0015CA40  38 60 00 03 */	li r3, 3
/* 8015FE64 0015CA44  48 00 00 08 */	b lbl_8015FE6C
lbl_8015FE68:
/* 8015FE68 0015CA48  38 60 00 04 */	li r3, 4
lbl_8015FE6C:
/* 8015FE6C 0015CA4C  38 00 00 00 */	li r0, 0
/* 8015FE70 0015CA50  90 6D 93 68 */	stw r3, lbl_804D4A08@sda21(r13)
/* 8015FE74 0015CA54  90 0D B4 80 */	stw r0, lbl_804D6B20@sda21(r13)
/* 8015FE78 0015CA58  48 00 00 28 */	b lbl_8015FEA0
lbl_8015FE7C:
/* 8015FE7C 0015CA5C  80 0D 93 68 */	lwz r0, lbl_804D4A08@sda21(r13)
/* 8015FE80 0015CA60  2C 00 00 01 */	cmpwi r0, 1
/* 8015FE84 0015CA64  41 82 00 14 */	beq lbl_8015FE98
/* 8015FE88 0015CA68  38 7F 00 10 */	addi r3, r31, 0x10
/* 8015FE8C 0015CA6C  38 BF 00 1C */	addi r5, r31, 0x1c
/* 8015FE90 0015CA70  38 80 00 D2 */	li r4, 0xd2
/* 8015FE94 0015CA74  48 22 83 8D */	bl __assert
lbl_8015FE98:
/* 8015FE98 0015CA78  38 00 00 00 */	li r0, 0
/* 8015FE9C 0015CA7C  90 0D 93 68 */	stw r0, lbl_804D4A08@sda21(r13)
lbl_8015FEA0:
/* 8015FEA0 0015CA80  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8015FEA4 0015CA84  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8015FEA8 0015CA88  38 21 00 10 */	addi r1, r1, 0x10
/* 8015FEAC 0015CA8C  7C 08 03 A6 */	mtlr r0
/* 8015FEB0 0015CA90  4E 80 00 20 */	blr 

.global main
main:
/* 8015FEB4 0015CA94  7C 08 02 A6 */	mflr r0
/* 8015FEB8 0015CA98  3C 80 80 3D */	lis r4, lbl_803D4AC8@ha
/* 8015FEBC 0015CA9C  90 01 00 04 */	stw r0, 4(r1)
/* 8015FEC0 0015CAA0  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8015FEC4 0015CAA4  93 E1 00 24 */	stw r31, 0x24(r1)
/* 8015FEC8 0015CAA8  3B E4 4A C8 */	addi r31, r4, lbl_803D4AC8@l
/* 8015FECC 0015CAAC  93 C1 00 20 */	stw r30, 0x20(r1)
/* 8015FED0 0015CAB0  48 1E 30 F9 */	bl OSInit
/* 8015FED4 0015CAB4  48 1E EF C9 */	bl func_8034EE9C
/* 8015FED8 0015CAB8  48 1D 7F 11 */	bl DVDInit
/* 8015FEDC 0015CABC  48 1E D9 11 */	bl PADInit
/* 8015FEE0 0015CAC0  48 1F 32 05 */	bl CARDInit
/* 8015FEE4 0015CAC4  48 1E 38 3D */	bl OSInitAlarm
/* 8015FEE8 0015CAC8  48 0C 54 8D */	bl func_80225374
/* 8015FEEC 0015CACC  4B FF FE B9 */	bl func_8015FDA4
/* 8015FEF0 0015CAD0  48 1E 7D 01 */	bl OSGetConsoleSimulatedMemSize
/* 8015FEF4 0015CAD4  54 60 65 3E */	srwi r0, r3, 0x14
/* 8015FEF8 0015CAD8  28 00 00 30 */	cmplwi r0, 0x30
/* 8015FEFC 0015CADC  40 82 00 10 */	bne lbl_8015FF0C
/* 8015FF00 0015CAE0  3C 60 01 80 */	lis r3, 0x180
/* 8015FF04 0015CAE4  38 80 00 04 */	li r4, 4
/* 8015FF08 0015CAE8  48 1E 46 0D */	bl OSAllocFromArenaHi
lbl_8015FF0C:
/* 8015FF0C 0015CAEC  48 1E 45 BD */	bl OSGetArenaHi
/* 8015FF10 0015CAF0  7C 7E 1B 78 */	mr r30, r3
/* 8015FF14 0015CAF4  48 1E 45 BD */	bl OSGetArenaLo
/* 8015FF18 0015CAF8  7C 03 F0 50 */	subf r0, r3, r30
/* 8015FF1C 0015CAFC  4C C6 31 82 */	crclr 6
/* 8015FF20 0015CB00  90 0D AE F0 */	stw r0, lbl_804D6590@sda21(r13)
/* 8015FF24 0015CB04  38 60 00 01 */	li r3, 1
/* 8015FF28 0015CB08  38 80 00 02 */	li r4, 2
/* 8015FF2C 0015CB0C  48 21 57 CD */	bl func_803756F8
/* 8015FF30 0015CB10  3C 80 80 40 */	lis r4, lbl_80401168@ha
/* 8015FF34 0015CB14  4C C6 31 82 */	crclr 6
/* 8015FF38 0015CB18  3B C4 11 68 */	addi r30, r4, lbl_80401168@l
/* 8015FF3C 0015CB1C  38 9E 00 00 */	addi r4, r30, 0
/* 8015FF40 0015CB20  38 60 00 04 */	li r3, 4
/* 8015FF44 0015CB24  48 21 57 B5 */	bl func_803756F8
/* 8015FF48 0015CB28  4C C6 31 82 */	crclr 6
/* 8015FF4C 0015CB2C  38 60 00 00 */	li r3, 0
/* 8015FF50 0015CB30  3C 80 00 04 */	lis r4, 4
/* 8015FF54 0015CB34  48 21 57 A5 */	bl func_803756F8
/* 8015FF58 0015CB38  4C C6 31 82 */	crclr 6
/* 8015FF5C 0015CB3C  38 60 00 02 */	li r3, 2
/* 8015FF60 0015CB40  38 80 00 04 */	li r4, 4
/* 8015FF64 0015CB44  48 21 57 95 */	bl func_803756F8
/* 8015FF68 0015CB48  48 0C 8C E5 */	bl func_80228C4C
/* 8015FF6C 0015CB4C  38 9E 00 00 */	addi r4, r30, 0
/* 8015FF70 0015CB50  38 60 00 02 */	li r3, 2
/* 8015FF74 0015CB54  48 21 50 09 */	bl HSD_AllocateXFB
/* 8015FF78 0015CB58  3C 60 00 04 */	lis r3, 4
/* 8015FF7C 0015CB5C  48 21 52 19 */	bl func_80375194
/* 8015FF80 0015CB60  3C 80 00 04 */	lis r4, 4
/* 8015FF84 0015CB64  48 1D A7 FD */	bl func_8033A780
/* 8015FF88 0015CB68  48 21 4F D9 */	bl HSD_GXSetFifoObj
/* 8015FF8C 0015CB6C  48 21 4E BD */	bl HSD_InitComponent
/* 8015FF90 0015CB70  38 60 00 01 */	li r3, 1
/* 8015FF94 0015CB74  38 80 00 08 */	li r4, 8
/* 8015FF98 0015CB78  48 1D CC 29 */	bl GXSetMisc
/* 8015FF9C 0015CB7C  48 1E C4 6D */	bl OSGetTick
/* 8015FFA0 0015CB80  80 8D A8 F4 */	lwz r4, seed_ptr@sda21(r13)
/* 8015FFA4 0015CB84  90 64 00 00 */	stw r3, 0(r4)
/* 8015FFA8 0015CB88  4B EC 83 E5 */	bl func_8002838C
/* 8015FFAC 0015CB8C  3C 80 80 16 */	lis r4, lbl_8015FD24@ha
/* 8015FFB0 0015CB90  38 64 FD 24 */	addi r3, r4, lbl_8015FD24@l
/* 8015FFB4 0015CB94  4B EB 9A F9 */	bl func_80019AAC
/* 8015FFB8 0015CB98  3C 80 80 16 */	lis r4, lbl_8015FDA0@ha
/* 8015FFBC 0015CB9C  38 64 FD A0 */	addi r3, r4, lbl_8015FDA0@l
/* 8015FFC0 0015CBA0  48 21 59 75 */	bl func_80375934
/* 8015FFC4 0015CBA4  3C 80 80 37 */	lis r4, lbl_803762C4@ha
/* 8015FFC8 0015CBA8  38 64 62 C4 */	addi r3, r4, lbl_803762C4@l
/* 8015FFCC 0015CBAC  48 21 59 C1 */	bl func_8037598C
/* 8015FFD0 0015CBB0  38 60 00 00 */	li r3, 0
/* 8015FFD4 0015CBB4  48 21 67 CD */	bl func_803767A0
/* 8015FFD8 0015CBB8  4B EB 56 75 */	bl func_8001564C
/* 8015FFDC 0015CBBC  4B EB 5F 61 */	bl func_80015F3C
/* 8015FFE0 0015CBC0  4B EB 8F 89 */	bl func_80018F68
/* 8015FFE4 0015CBC4  4B EB 4D 49 */	bl func_80014D2C
/* 8015FFE8 0015CBC8  4B EB C5 D5 */	bl func_8001C5BC
/* 8015FFEC 0015CBCC  4B EB D2 31 */	bl func_8001D21C
/* 8015FFF0 0015CBD0  4B EB E2 A1 */	bl func_8001E290
/* 8015FFF4 0015CBD4  4B FF FC CD */	bl func_8015FCC0
/* 8015FFF8 0015CBD8  4B EB F8 85 */	bl func_8001F87C
/* 8015FFFC 0015CBDC  3C 80 00 01 */	lis r4, 0x0000C000@ha
/* 80160000 0015CBE0  38 64 C0 00 */	addi r3, r4, 0x0000C000@l
/* 80160004 0015CBE4  48 24 60 45 */	bl func_803A6048
/* 80160008 0015CBE8  4B FF FB 9D */	bl func_8015FBA4
/* 8016000C 0015CBEC  80 0D 93 68 */	lwz r0, lbl_804D4A08@sda21(r13)
/* 80160010 0015CBF0  2C 00 00 00 */	cmpwi r0, 0
/* 80160014 0015CBF4  41 82 00 48 */	beq lbl_8016005C
/* 80160018 0015CBF8  A0 0D B4 90 */	lhz r0, lbl_804D6B30@sda21(r13)
/* 8016001C 0015CBFC  54 00 06 B5 */	rlwinm. r0, r0, 0, 0x1a, 0x1a
/* 80160020 0015CC00  41 82 00 3C */	beq lbl_8016005C
/* 80160024 0015CC04  38 60 FF FF */	li r3, -1
/* 80160028 0015CC08  48 23 31 7D */	bl func_803931A4
/* 8016002C 0015CC0C  2C 03 00 00 */	cmpwi r3, 0
/* 80160030 0015CC10  41 82 00 2C */	beq lbl_8016005C
/* 80160034 0015CC14  38 60 00 01 */	li r3, 1
/* 80160038 0015CC18  48 23 3A 1D */	bl func_80393A54
/* 8016003C 0015CC1C  48 00 00 14 */	b lbl_80160050
lbl_80160040:
/* 80160040 0015CC20  38 7F 00 48 */	addi r3, r31, 0x48
/* 80160044 0015CC24  4C C6 31 82 */	crclr 6
/* 80160048 0015CC28  48 1E 56 61 */	bl OSReport
/* 8016004C 0015CC2C  48 23 2E 35 */	bl func_80392E80
lbl_80160050:
/* 80160050 0015CC30  48 23 39 B5 */	bl func_80393A04
/* 80160054 0015CC34  2C 03 00 00 */	cmpwi r3, 0
/* 80160058 0015CC38  41 82 FF E8 */	beq lbl_80160040
lbl_8016005C:
/* 8016005C 0015CC3C  48 0C 88 11 */	bl func_8022886C
/* 80160060 0015CC40  38 7F 00 68 */	addi r3, r31, 0x68
/* 80160064 0015CC44  4C C6 31 82 */	crclr 6
/* 80160068 0015CC48  48 1E 56 41 */	bl OSReport
/* 8016006C 0015CC4C  38 7F 00 9C */	addi r3, r31, 0x9c
/* 80160070 0015CC50  4C C6 31 82 */	crclr 6
/* 80160074 0015CC54  48 1E 56 35 */	bl OSReport
/* 80160078 0015CC58  38 6D 88 48 */	addi r3, r13, lbl_804D3EE8@sda21
/* 8016007C 0015CC5C  4C C6 31 82 */	crclr 6
/* 80160080 0015CC60  48 1E 56 29 */	bl OSReport
/* 80160084 0015CC64  4B EA AD 09 */	bl lbLang_GetLanguageSetting
/* 80160088 0015CC68  38 83 00 00 */	addi r4, r3, 0
/* 8016008C 0015CC6C  4C C6 31 82 */	crclr 6
/* 80160090 0015CC70  38 7F 00 BC */	addi r3, r31, 0xbc
/* 80160094 0015CC74  48 1E 56 15 */	bl OSReport
/* 80160098 0015CC78  4B EA AD 5D */	bl lbLang_GetSavedLanguage
/* 8016009C 0015CC7C  38 83 00 00 */	addi r4, r3, 0
/* 801600A0 0015CC80  4C C6 31 82 */	crclr 6
/* 801600A4 0015CC84  38 7F 00 D0 */	addi r3, r31, 0xd0
/* 801600A8 0015CC88  48 1E 56 01 */	bl OSReport
/* 801600AC 0015CC8C  80 8D 93 68 */	lwz r4, lbl_804D4A08@sda21(r13)
/* 801600B0 0015CC90  38 7F 00 E0 */	addi r3, r31, 0xe0
/* 801600B4 0015CC94  4C C6 31 82 */	crclr 6
/* 801600B8 0015CC98  48 1E 55 F1 */	bl OSReport
/* 801600BC 0015CC9C  80 0D AE F0 */	lwz r0, lbl_804D6590@sda21(r13)
/* 801600C0 0015CCA0  38 7F 00 F0 */	addi r3, r31, 0xf0
/* 801600C4 0015CCA4  4C C6 31 82 */	crclr 6
/* 801600C8 0015CCA8  54 04 65 3E */	srwi r4, r0, 0x14
/* 801600CC 0015CCAC  48 1E 55 DD */	bl OSReport
/* 801600D0 0015CCB0  38 61 00 14 */	addi r3, r1, 0x14
/* 801600D4 0015CCB4  38 81 00 10 */	addi r4, r1, 0x10
/* 801600D8 0015CCB8  4B EB 53 E5 */	bl func_800154BC
/* 801600DC 0015CCBC  80 81 00 14 */	lwz r4, 0x14(r1)
/* 801600E0 0015CCC0  38 7F 01 04 */	addi r3, r31, 0x104
/* 801600E4 0015CCC4  80 01 00 10 */	lwz r0, 0x10(r1)
/* 801600E8 0015CCC8  4C C6 31 82 */	crclr 6
/* 801600EC 0015CCCC  7C 04 00 50 */	subf r0, r4, r0
/* 801600F0 0015CCD0  54 04 65 3E */	srwi r4, r0, 0x14
/* 801600F4 0015CCD4  48 1E 55 B5 */	bl OSReport
/* 801600F8 0015CCD8  3C 80 80 3F */	lis r4, lbl_803EA6C8@ha
/* 801600FC 0015CCDC  4C C6 31 82 */	crclr 6
/* 80160100 0015CCE0  38 84 A6 C8 */	addi r4, r4, lbl_803EA6C8@l
/* 80160104 0015CCE4  38 6D 88 4C */	addi r3, r13, lbl_804D3EEC@sda21
/* 80160108 0015CCE8  48 1E 55 A1 */	bl OSReport
/* 8016010C 0015CCEC  4B EA AE B1 */	bl func_8000AFBC
/* 80160110 0015CCF0  38 81 00 08 */	addi r4, r1, 8
/* 80160114 0015CCF4  48 00 91 D5 */	bl func_801692E8
/* 80160118 0015CCF8  A0 81 00 08 */	lhz r4, 8(r1)
/* 8016011C 0015CCFC  38 7F 01 1C */	addi r3, r31, 0x11c
/* 80160120 0015CD00  88 A1 00 0A */	lbz r5, 0xa(r1)
/* 80160124 0015CD04  4C C6 31 82 */	crclr 6
/* 80160128 0015CD08  88 C1 00 0B */	lbz r6, 0xb(r1)
/* 8016012C 0015CD0C  48 1E 55 7D */	bl OSReport
/* 80160130 0015CD10  88 81 00 0C */	lbz r4, 0xc(r1)
/* 80160134 0015CD14  38 7F 01 44 */	addi r3, r31, 0x144
/* 80160138 0015CD18  88 A1 00 0D */	lbz r5, 0xd(r1)
/* 8016013C 0015CD1C  4C C6 31 82 */	crclr 6
/* 80160140 0015CD20  88 C1 00 0E */	lbz r6, 0xe(r1)
/* 80160144 0015CD24  48 1E 55 65 */	bl OSReport
/* 80160148 0015CD28  38 6D 88 54 */	addi r3, r13, lbl_804D3EF4@sda21
/* 8016014C 0015CD2C  4C C6 31 82 */	crclr 6
/* 80160150 0015CD30  48 1E 55 59 */	bl OSReport
/* 80160154 0015CD34  38 00 00 00 */	li r0, 0
/* 80160158 0015CD38  90 0D AE F4 */	stw r0, lbl_804D6594@sda21(r13)
/* 8016015C 0015CD3C  80 0D AE F4 */	lwz r0, lbl_804D6594@sda21(r13)
/* 80160160 0015CD40  2C 00 00 00 */	cmpwi r0, 0
/* 80160164 0015CD44  41 82 00 0C */	beq lbl_80160170
/* 80160168 0015CD48  48 0C 5B C5 */	bl func_80225D2C
/* 8016016C 0015CD4C  48 00 00 08 */	b lbl_80160174
lbl_80160170:
/* 80160170 0015CD50  48 0C 5B D1 */	bl func_80225D40
lbl_80160174:
/* 80160174 0015CD54  38 60 00 04 */	li r3, 4
/* 80160178 0015CD58  64 63 00 04 */	oris r3, r3, 4
/* 8016017C 0015CD5C  7C 72 E3 A6 */	mtspr 0x392, r3
/* 80160180 0015CD60  38 60 00 05 */	li r3, 5
/* 80160184 0015CD64  64 63 00 05 */	oris r3, r3, 5
/* 80160188 0015CD68  7C 73 E3 A6 */	mtspr 0x393, r3
/* 8016018C 0015CD6C  38 60 00 06 */	li r3, 6
/* 80160190 0015CD70  64 63 00 06 */	oris r3, r3, 6
/* 80160194 0015CD74  7C 74 E3 A6 */	mtspr 0x394, r3
/* 80160198 0015CD78  38 60 00 07 */	li r3, 7
/* 8016019C 0015CD7C  64 63 00 07 */	oris r3, r3, 7
/* 801601A0 0015CD80  7C 75 E3 A6 */	mtspr 0x395, r3
/* 801601A4 0015CD84  48 0C 88 C1 */	bl func_80228A64
/* 801601A8 0015CD88  48 04 43 69 */	bl func_801A4510
/* 801601AC 0015CD8C  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 801601B0 0015CD90  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 801601B4 0015CD94  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 801601B8 0015CD98  38 21 00 28 */	addi r1, r1, 0x28
/* 801601BC 0015CD9C  7C 08 03 A6 */	mtlr r0
/* 801601C0 0015CDA0  4E 80 00 20 */	blr 


.section .bss, "wa"
    .balign 8
.global lbl_8046B108
lbl_8046B108:
    .skip 0xF0
.global lbl_8046B1F8
lbl_8046B1F8:
    .skip 0x180


.section .data
    .balign 8
.global lbl_803D4AC8
lbl_803D4AC8:
    .asciz "/develop.ini"
    .balign 4
    .asciz "gmmain.c"
    .balign 4
    .asciz "DbLevel == DbLKind_NoDebugRom"
    .balign 4
    .asciz "Data %lx\n"
    .balign 4
    .asciz "please setup server for USB\n"
    .balign 4
    .asciz "# ---------------------------------------------\n"
    .balign 4
    .asciz "#    Super Smash Bros. Melee\n"
    .balign 4
    .asciz "# Distribution %d\n"
    .balign 4
    .asciz "# Language %d\n"
    .balign 4
    .asciz "# DbLevel %d\n"
    .balign 4
    .asciz "# Arena Size %d MB\n"
    .balign 4
    .asciz "# ARAM Free Size %d MB\n"
    .balign 4
    .asciz "# GC Calendar Year %d Month %d Day %d\n"
    .balign 4
    .asciz "#             Hour %d Min %d Sec %d \n"
    .balign 4


.section .sbss
    .balign 8
.global lbl_804D6590
lbl_804D6590:
    .skip 0x4
.global lbl_804D6594
lbl_804D6594:
    .skip 0x4


.section .sdata
    .balign 8
.global lbl_804D3EE8
lbl_804D3EE8:
    .asciz "#\n"
    .balign 4
.global lbl_804D3EEC
lbl_804D3EEC:
    .asciz "# %s\n"
    .balign 4
.global lbl_804D3EF4
lbl_804D3EF4:
    .asciz "#\n\n"
