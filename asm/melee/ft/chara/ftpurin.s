.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

.global lbl_80142070
lbl_80142070:
/* 80142070 0013EC50  7C 08 02 A6 */	mflr r0
/* 80142074 0013EC54  90 01 00 04 */	stw r0, 4(r1)
/* 80142078 0013EC58  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8014207C 0013EC5C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80142080 0013EC60  93 C1 00 10 */	stw r30, 0x10(r1)
/* 80142084 0013EC64  7C 7E 1B 78 */	mr r30, r3
/* 80142088 0013EC68  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8014208C 0013EC6C  4B F3 FC 81 */	bl func_80081D0C
/* 80142090 0013EC70  2C 03 00 00 */	cmpwi r3, 0
/* 80142094 0013EC74  41 82 00 24 */	beq lbl_801420B8
/* 80142098 0013EC78  7F E3 FB 78 */	mr r3, r31
/* 8014209C 0013EC7C  4B F3 B7 61 */	bl func_8007D7FC
/* 801420A0 0013EC80  3C 80 0C 4C */	lis r4, 0x0C4C5092@ha
/* 801420A4 0013EC84  C0 3F 08 94 */	lfs f1, 0x894(r31)
/* 801420A8 0013EC88  38 7E 00 00 */	addi r3, r30, 0
/* 801420AC 0013EC8C  38 A4 50 92 */	addi r5, r4, 0x0C4C5092@l
/* 801420B0 0013EC90  38 80 00 00 */	li r4, 0
/* 801420B4 0013EC94  4B FF B9 71 */	bl func_8013DA24
lbl_801420B8:
/* 801420B8 0013EC98  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 801420BC 0013EC9C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 801420C0 0013ECA0  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 801420C4 0013ECA4  38 21 00 18 */	addi r1, r1, 0x18
/* 801420C8 0013ECA8  7C 08 03 A6 */	mtlr r0
/* 801420CC 0013ECAC  4E 80 00 20 */	blr 

.global lbl_801420D0
lbl_801420D0:
/* 801420D0 0013ECB0  7C 08 02 A6 */	mflr r0
/* 801420D4 0013ECB4  90 01 00 04 */	stw r0, 4(r1)
/* 801420D8 0013ECB8  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 801420DC 0013ECBC  BF 41 00 20 */	stmw r26, 0x20(r1)
/* 801420E0 0013ECC0  7C 7E 1B 78 */	mr r30, r3
/* 801420E4 0013ECC4  80 A3 00 2C */	lwz r5, 0x2c(r3)
/* 801420E8 0013ECC8  3C 60 80 3D */	lis r3, lbl_803D0610@ha
/* 801420EC 0013ECCC  38 83 06 10 */	addi r4, r3, lbl_803D0610@l
/* 801420F0 0013ECD0  83 E5 02 D4 */	lwz r31, 0x2d4(r5)
/* 801420F4 0013ECD4  3B 45 00 00 */	addi r26, r5, 0
/* 801420F8 0013ECD8  38 7E 00 00 */	addi r3, r30, 0
/* 801420FC 0013ECDC  4B F4 03 A5 */	bl func_800824A0
/* 80142100 0013ECE0  2C 03 00 00 */	cmpwi r3, 0
/* 80142104 0013ECE4  41 82 01 14 */	beq lbl_80142218
/* 80142108 0013ECE8  83 BE 00 28 */	lwz r29, 0x28(r30)
/* 8014210C 0013ECEC  83 7E 00 2C */	lwz r27, 0x2c(r30)
/* 80142110 0013ECF0  28 1D 00 00 */	cmplwi r29, 0
/* 80142114 0013ECF4  3B 9B 22 30 */	addi r28, r27, 0x2230
/* 80142118 0013ECF8  40 82 00 14 */	bne lbl_8014212C
/* 8014211C 0013ECFC  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98@sda21
/* 80142120 0013ED00  38 80 02 F8 */	li r4, 0x2f8
/* 80142124 0013ED04  38 AD 88 00 */	addi r5, r13, lbl_804D3EA0@sda21
/* 80142128 0013ED08  48 24 60 F9 */	bl __assert
lbl_8014212C:
/* 8014212C 0013ED0C  28 1C 00 00 */	cmplwi r28, 0
/* 80142130 0013ED10  40 82 00 14 */	bne lbl_80142144
/* 80142134 0013ED14  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98@sda21
/* 80142138 0013ED18  38 80 02 F9 */	li r4, 0x2f9
/* 8014213C 0013ED1C  38 AD 88 08 */	addi r5, r13, lbl_804D3EA8@sda21
/* 80142140 0013ED20  48 24 60 E1 */	bl __assert
lbl_80142144:
/* 80142144 0013ED24  80 7C 00 00 */	lwz r3, 0(r28)
/* 80142148 0013ED28  80 1C 00 04 */	lwz r0, 4(r28)
/* 8014214C 0013ED2C  90 7D 00 2C */	stw r3, 0x2c(r29)
/* 80142150 0013ED30  90 1D 00 30 */	stw r0, 0x30(r29)
/* 80142154 0013ED34  80 1C 00 08 */	lwz r0, 8(r28)
/* 80142158 0013ED38  90 1D 00 34 */	stw r0, 0x34(r29)
/* 8014215C 0013ED3C  80 1D 00 14 */	lwz r0, 0x14(r29)
/* 80142160 0013ED40  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 80142164 0013ED44  40 82 00 4C */	bne lbl_801421B0
/* 80142168 0013ED48  28 1D 00 00 */	cmplwi r29, 0
/* 8014216C 0013ED4C  41 82 00 44 */	beq lbl_801421B0
/* 80142170 0013ED50  40 82 00 14 */	bne lbl_80142184
/* 80142174 0013ED54  38 6D 87 F8 */	addi r3, r13, lbl_804D3E98@sda21
/* 80142178 0013ED58  38 80 02 34 */	li r4, 0x234
/* 8014217C 0013ED5C  38 AD 88 00 */	addi r5, r13, lbl_804D3EA0@sda21
/* 80142180 0013ED60  48 24 60 A1 */	bl __assert
lbl_80142184:
/* 80142184 0013ED64  80 9D 00 14 */	lwz r4, 0x14(r29)
/* 80142188 0013ED68  38 60 00 00 */	li r3, 0
/* 8014218C 0013ED6C  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 80142190 0013ED70  40 82 00 10 */	bne lbl_801421A0
/* 80142194 0013ED74  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 80142198 0013ED78  41 82 00 08 */	beq lbl_801421A0
/* 8014219C 0013ED7C  38 60 00 01 */	li r3, 1
lbl_801421A0:
/* 801421A0 0013ED80  2C 03 00 00 */	cmpwi r3, 0
/* 801421A4 0013ED84  40 82 00 0C */	bne lbl_801421B0
/* 801421A8 0013ED88  7F A3 EB 78 */	mr r3, r29
/* 801421AC 0013ED8C  48 23 11 3D */	bl HSD_JObjSetMtxDirtySub
lbl_801421B0:
/* 801421B0 0013ED90  C8 22 A2 60 */	lfd f1, lbl_804D9C40@sda21(r2)
/* 801421B4 0013ED94  7F 63 DB 78 */	mr r3, r27
/* 801421B8 0013ED98  C0 1B 00 2C */	lfs f0, 0x2c(r27)
/* 801421BC 0013ED9C  38 80 00 00 */	li r4, 0
/* 801421C0 0013EDA0  FC 21 00 32 */	fmul f1, f1, f0
/* 801421C4 0013EDA4  FC 20 08 18 */	frsp f1, f1
/* 801421C8 0013EDA8  4B F3 39 29 */	bl func_80075AF0
/* 801421CC 0013EDAC  C0 02 A2 68 */	lfs f0, lbl_804D9C48@sda21(r2)
/* 801421D0 0013EDB0  C0 3B 23 60 */	lfs f1, 0x2360(r27)
/* 801421D4 0013EDB4  FC 00 08 00 */	fcmpu cr0, f0, f1
/* 801421D8 0013EDB8  41 82 00 08 */	beq lbl_801421E0
/* 801421DC 0013EDBC  D0 3B 00 2C */	stfs f1, 0x2c(r27)
lbl_801421E0:
/* 801421E0 0013EDC0  C0 02 A2 68 */	lfs f0, lbl_804D9C48@sda21(r2)
/* 801421E4 0013EDC4  7F 43 D3 78 */	mr r3, r26
/* 801421E8 0013EDC8  D0 1B 23 60 */	stfs f0, 0x2360(r27)
/* 801421EC 0013EDCC  4B F3 B6 11 */	bl func_8007D7FC
/* 801421F0 0013EDD0  C0 02 A2 68 */	lfs f0, lbl_804D9C48@sda21(r2)
/* 801421F4 0013EDD4  C0 3F 00 D8 */	lfs f1, 0xd8(r31)
/* 801421F8 0013EDD8  FC 00 08 00 */	fcmpu cr0, f0, f1
/* 801421FC 0013EDDC  40 82 00 10 */	bne lbl_8014220C
/* 80142200 0013EDE0  7F C3 F3 78 */	mr r3, r30
/* 80142204 0013EDE4  4B F4 80 B9 */	bl func_8008A2BC
/* 80142208 0013EDE8  48 00 00 10 */	b lbl_80142218
lbl_8014220C:
/* 8014220C 0013EDEC  38 7E 00 00 */	addi r3, r30, 0
/* 80142210 0013EDF0  38 80 00 00 */	li r4, 0
/* 80142214 0013EDF4  4B F9 3A 9D */	bl func_800D5CB0
lbl_80142218:
/* 80142218 0013EDF8  BB 41 00 20 */	lmw r26, 0x20(r1)
/* 8014221C 0013EDFC  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 80142220 0013EE00  38 21 00 38 */	addi r1, r1, 0x38
/* 80142224 0013EE04  7C 08 03 A6 */	mtlr r0
/* 80142228 0013EE08  4E 80 00 20 */	blr 

.global lbl_8014222C
lbl_8014222C:
/* 8014222C 0013EE0C  7C 08 02 A6 */	mflr r0
/* 80142230 0013EE10  38 80 00 00 */	li r4, 0
/* 80142234 0013EE14  90 01 00 04 */	stw r0, 4(r1)
/* 80142238 0013EE18  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8014223C 0013EE1C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80142240 0013EE20  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80142244 0013EE24  C8 22 A2 60 */	lfd f1, lbl_804D9C40@sda21(r2)
/* 80142248 0013EE28  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 8014224C 0013EE2C  7F E3 FB 78 */	mr r3, r31
/* 80142250 0013EE30  FC 21 00 32 */	fmul f1, f1, f0
/* 80142254 0013EE34  FC 20 08 18 */	frsp f1, f1
/* 80142258 0013EE38  4B F3 38 99 */	bl func_80075AF0
/* 8014225C 0013EE3C  C0 1F 00 80 */	lfs f0, 0x80(r31)
/* 80142260 0013EE40  FC 00 00 50 */	fneg f0, f0
/* 80142264 0013EE44  D0 1F 00 80 */	stfs f0, 0x80(r31)
/* 80142268 0013EE48  C0 1F 00 EC */	lfs f0, 0xec(r31)
/* 8014226C 0013EE4C  FC 00 00 50 */	fneg f0, f0
/* 80142270 0013EE50  D0 1F 00 EC */	stfs f0, 0xec(r31)
/* 80142274 0013EE54  C0 1F 00 E4 */	lfs f0, 0xe4(r31)
/* 80142278 0013EE58  FC 00 00 50 */	fneg f0, f0
/* 8014227C 0013EE5C  D0 1F 00 E4 */	stfs f0, 0xe4(r31)
/* 80142280 0013EE60  C0 1F 23 50 */	lfs f0, 0x2350(r31)
/* 80142284 0013EE64  FC 00 00 50 */	fneg f0, f0
/* 80142288 0013EE68  D0 1F 23 50 */	stfs f0, 0x2350(r31)
/* 8014228C 0013EE6C  C0 1F 23 54 */	lfs f0, 0x2354(r31)
/* 80142290 0013EE70  FC 00 00 50 */	fneg f0, f0
/* 80142294 0013EE74  D0 1F 23 54 */	stfs f0, 0x2354(r31)
/* 80142298 0013EE78  C0 1F 23 58 */	lfs f0, 0x2358(r31)
/* 8014229C 0013EE7C  FC 00 00 50 */	fneg f0, f0
/* 801422A0 0013EE80  D0 1F 23 58 */	stfs f0, 0x2358(r31)
/* 801422A4 0013EE84  C0 1F 23 5C */	lfs f0, 0x235c(r31)
/* 801422A8 0013EE88  FC 00 00 50 */	fneg f0, f0
/* 801422AC 0013EE8C  D0 1F 23 5C */	stfs f0, 0x235c(r31)
/* 801422B0 0013EE90  C0 1F 23 60 */	lfs f0, 0x2360(r31)
/* 801422B4 0013EE94  FC 00 00 50 */	fneg f0, f0
/* 801422B8 0013EE98  D0 1F 23 60 */	stfs f0, 0x2360(r31)
/* 801422BC 0013EE9C  C0 1F 23 74 */	lfs f0, 0x2374(r31)
/* 801422C0 0013EEA0  FC 00 00 50 */	fneg f0, f0
/* 801422C4 0013EEA4  D0 1F 23 74 */	stfs f0, 0x2374(r31)
/* 801422C8 0013EEA8  C0 1F 23 78 */	lfs f0, 0x2378(r31)
/* 801422CC 0013EEAC  FC 00 00 50 */	fneg f0, f0
/* 801422D0 0013EEB0  D0 1F 23 78 */	stfs f0, 0x2378(r31)
/* 801422D4 0013EEB4  80 01 00 24 */	lwz r0, 0x24(r1)
/* 801422D8 0013EEB8  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 801422DC 0013EEBC  38 21 00 20 */	addi r1, r1, 0x20
/* 801422E0 0013EEC0  7C 08 03 A6 */	mtlr r0
/* 801422E4 0013EEC4  4E 80 00 20 */	blr 

.section .data
    .balign 8

.global as_table_purin
as_table_purin:
    .4byte 0x00000127
    .4byte NULL
    .4byte 0x01000000
    .4byte func_800D7590
    .4byte func_800D7614
    .4byte func_800D7634
    .4byte func_800D767C
    .4byte func_800761C8
    .4byte 0x00000128
    .4byte NULL
    .4byte 0x01000000
    .4byte func_800D7590
    .4byte func_800D7614
    .4byte func_800D7634
    .4byte func_800D767C
    .4byte func_800761C8
    .4byte 0x00000129
    .4byte NULL
    .4byte 0x01000000
    .4byte func_800D7590
    .4byte func_800D7614
    .4byte func_800D7634
    .4byte func_800D767C
    .4byte func_800761C8
    .4byte 0x0000012A
    .4byte NULL
    .4byte 0x01000000
    .4byte func_800D7590
    .4byte func_800D7614
    .4byte func_800D7634
    .4byte func_800D767C
    .4byte func_800761C8
    .4byte 0x0000012B
    .4byte NULL
    .4byte 0x01000000
    .4byte func_800D7590
    .4byte func_800D7614
    .4byte func_800D7634
    .4byte func_800D767C
    .4byte func_800761C8
    .4byte 0x0000012C
    .4byte 0x00340211
    .4byte 0x12000000
    .4byte lbl_8013E014
    .4byte lbl_8013FF00
    .4byte lbl_80140620
    .4byte lbl_80140FA4
    .4byte func_800761C8
    .4byte 0x0000012D
    .4byte 0x00340211
    .4byte 0x12000000
    .4byte lbl_8013E014
    .4byte lbl_8013FF00
    .4byte lbl_80140620
    .4byte lbl_80140FA4
    .4byte func_800761C8
    .4byte 0x0000012E
    .4byte 0x003C0211
    .4byte 0x12000000
    .4byte lbl_8013E0F0
    .4byte lbl_8013FF04
    .4byte lbl_80140650
    .4byte lbl_80141054
    .4byte func_800761C8
    .4byte 0x0000012F
    .4byte 0x003C0211
    .4byte 0x12000000
    .4byte lbl_8013E2A0
    .4byte lbl_80140064
    .4byte lbl_80140680
    .4byte lbl_80141154
    .4byte func_800761C8
    .4byte 0x00000130
    .4byte 0x00340211
    .4byte 0x12000000
    .4byte lbl_8013E410
    .4byte lbl_801401C4
    .4byte lbl_801406B0
    .4byte lbl_80141254
    .4byte func_800761C8
    .4byte 0x00000131
    .4byte 0x00340211
    .4byte 0x12000000
    .4byte lbl_8013E7E0
    .4byte lbl_80140344
    .4byte lbl_801408B8
    .4byte lbl_801415F4
    .4byte func_800761C8
    .4byte 0x00000132
    .4byte 0x00340211
    .4byte 0x12000000
    .4byte lbl_8013EAD8
    .4byte lbl_80140348
    .4byte lbl_80140BAC
    .4byte lbl_801416D0
    .4byte func_800761C8
    .4byte 0x00000133
    .4byte 0x00340211
    .4byte 0x12000000
    .4byte lbl_8013EAD8
    .4byte lbl_80140348
    .4byte lbl_80140BAC
    .4byte lbl_801416D0
    .4byte func_800761C8
    .4byte 0x00000134
    .4byte 0x00340611
    .4byte 0x12000000
    .4byte lbl_8013EDB0
    .4byte lbl_8014034C
    .4byte lbl_80140BE8
    .4byte lbl_80141730
    .4byte func_800761C8
    .4byte 0x00000135
    .4byte 0x00340611
    .4byte 0x12000000
    .4byte lbl_8013EDB0
    .4byte lbl_8014034C
    .4byte lbl_80140BE8
    .4byte lbl_80141730
    .4byte func_800761C8
    .4byte 0x00000136
    .4byte 0x003C0611
    .4byte 0x12000000
    .4byte lbl_8013EE84
    .4byte lbl_80140350
    .4byte lbl_80140C18
    .4byte lbl_801417E0
    .4byte func_800761C8
    .4byte 0x00000137
    .4byte 0x003C0611
    .4byte 0x12000000
    .4byte lbl_8013F034
    .4byte lbl_801404B0
    .4byte lbl_80140C48
    .4byte lbl_801418E0
    .4byte func_800761C8
    .4byte 0x00000138
    .4byte 0x00340611
    .4byte 0x12000000
    .4byte lbl_8013F1A4
    .4byte lbl_80140610
    .4byte lbl_80140C78
    .4byte lbl_801419E0
    .4byte func_800761C8
    .4byte 0x00000139
    .4byte 0x00340211
    .4byte 0x12000000
    .4byte lbl_8013F708
    .4byte lbl_80140614
    .4byte lbl_80140DF8
    .4byte lbl_80141FB8
    .4byte func_800761C8
    .4byte 0x0000013A
    .4byte 0x00340611
    .4byte 0x12000000
    .4byte lbl_8013F9C0
    .4byte lbl_80140618
    .4byte lbl_80140F10
    .4byte lbl_80142070
    .4byte func_800761C8
    .4byte 0x0000013B
    .4byte 0x00340611
    .4byte 0x12000000
    .4byte lbl_8013F9C0
    .4byte lbl_80140618
    .4byte lbl_80140F10
    .4byte lbl_80142070
    .4byte func_800761C8
    .4byte 0x0000013C
    .4byte 0x00340611
    .4byte 0x12000000
    .4byte lbl_8013FCAC
    .4byte lbl_8014061C
    .4byte lbl_80140F40
    .4byte lbl_801420D0
    .4byte func_800761C8
    .4byte 0x0000013D
    .4byte 0x00340212
    .4byte 0x13000000
    .4byte lbl_8013D30C
    .4byte lbl_8013D384
    .4byte lbl_8013D38C
    .4byte lbl_8013D518
    .4byte func_800761C8
    .4byte 0x0000013E
    .4byte 0x00340612
    .4byte 0x13000000
    .4byte lbl_8013D348
    .4byte lbl_8013D388
    .4byte lbl_8013D3AC
    .4byte lbl_8013D554
    .4byte func_800761C8
    .4byte 0x0000013F
    .4byte 0x00340013
    .4byte 0x14000000
    .4byte lbl_8013CB68
    .4byte lbl_8013CC60
    .4byte lbl_8013CC68
    .4byte lbl_8013CCA8
    .4byte func_800761C8
    .4byte 0x00000140
    .4byte 0x00340413
    .4byte 0x14000000
    .4byte lbl_8013CBE4
    .4byte lbl_8013CC64
    .4byte lbl_8013CC88
    .4byte lbl_8013CCE4
    .4byte func_800761C8
    .4byte 0x00000141
    .4byte 0x00340013
    .4byte 0x14000000
    .4byte lbl_8013CB68
    .4byte lbl_8013CC60
    .4byte lbl_8013CC68
    .4byte lbl_8013CCA8
    .4byte func_800761C8
    .4byte 0x00000142
    .4byte 0x00340413
    .4byte 0x14000000
    .4byte lbl_8013CBE4
    .4byte lbl_8013CC64
    .4byte lbl_8013CC88
    .4byte lbl_8013CCE4
    .4byte func_800761C8
    .4byte 0x00000143
    .4byte 0x00340014
    .4byte 0x15000000
    .4byte lbl_8013CFCC
    .4byte lbl_8013D044
    .4byte lbl_8013D04C
    .4byte lbl_8013D08C
    .4byte func_800761C8
    .4byte 0x00000144
    .4byte 0x00340414
    .4byte 0x15000000
    .4byte lbl_8013D008
    .4byte lbl_8013D048
    .4byte lbl_8013D06C
    .4byte lbl_8013D0C8
    .4byte func_800761C8
    .4byte 0x00000145
    .4byte 0x00340014
    .4byte 0x15000000
    .4byte lbl_8013CFCC
    .4byte lbl_8013D044
    .4byte lbl_8013D04C
    .4byte lbl_8013D08C
    .4byte func_800761C8
    .4byte 0x00000146
    .4byte 0x00340414
    .4byte 0x15000000
    .4byte lbl_8013D008
    .4byte lbl_8013D048
    .4byte lbl_8013D06C
    .4byte lbl_8013D0C8
    .4byte func_800761C8

.global lbl_803D02F0
lbl_803D02F0:
    .asciz "PlPr.dat"
    .balign 4

.global lbl_803D02FC
lbl_803D02FC:
    .asciz "ftDataPurin"
    .balign 4

.global lbl_803D0308
lbl_803D0308:
    .asciz "PlPrNr.dat"
    .balign 4

.global lbl_803D0314
lbl_803D0314:
    .asciz "PlyPurin5K_Share_joint"
    .balign 4

.global lbl_803D032C
lbl_803D032C:
    .asciz "PlyPurin5K_Share_matanim_joint"
    .balign 4

.global lbl_803D034C
lbl_803D034C:
    .asciz "PlPrRe.dat"
    .balign 4

.global lbl_803D0358
lbl_803D0358:
    .asciz "PlyPurin5KRe_Share_joint"
    .balign 4

.global lbl_803D0374
lbl_803D0374:
    .asciz "PlyPurin5KRe_Share_matanim_joint"
    .balign 4

.global lbl_803D0398
lbl_803D0398:
    .asciz "PlPrBu.dat"
    .balign 4

.global lbl_803D03A4
lbl_803D03A4:
    .asciz "PlyPurin5KBu_Share_joint"
    .balign 4

.global lbl_803D03C0
lbl_803D03C0:
    .asciz "PlyPurin5KBu_Share_matanim_joint"
    .balign 4

.global lbl_803D03E4
lbl_803D03E4:
    .asciz "PlPrGr.dat"
    .balign 4

.global lbl_803D03F0
lbl_803D03F0:
    .asciz "PlyPurin5KGr_Share_joint"
    .balign 4

.global lbl_803D040C
lbl_803D040C:
    .asciz "PlyPurin5KGr_Share_matanim_joint"
    .balign 4

.global lbl_803D0430
lbl_803D0430:
    .asciz "PlPrYe.dat"
    .balign 4

.global lbl_803D043C
lbl_803D043C:
    .asciz "PlyPurin5KYe_Share_joint"
    .balign 4

.global lbl_803D0458
lbl_803D0458:
    .asciz "PlyPurin5KYe_Share_matanim_joint"
    .balign 4

.global lbl_803D047C
lbl_803D047C:
    .asciz "PlPrAJ.dat"
    .balign 4

.global lbl_803D0488
lbl_803D0488:
    .asciz "ftDemoResultMotionFilePurin"
    .balign 4

.global lbl_803D04A4
lbl_803D04A4:
    .asciz "ftDemoIntroMotionFilePurin"
    .balign 4

.global lbl_803D04C0
lbl_803D04C0:
    .asciz "ftDemoEndingMotionFilePurin"
    .balign 4

.global lbl_803D04DC
lbl_803D04DC:
    .asciz "ftDemoViWaitMotionFilePurin"
    .balign 4

.global lbl_803D04F8
lbl_803D04F8:
    .4byte lbl_803D0488
    .4byte lbl_803D04A4
    .4byte lbl_803D04C0
    .4byte lbl_803D04DC

.global lbl_803D0508
lbl_803D0508:
    .4byte lbl_803D0308
    .4byte lbl_803D0314
    .4byte lbl_803D032C
    .4byte lbl_803D034C
    .4byte lbl_803D0358
    .4byte lbl_803D0374
    .4byte lbl_803D0398
    .4byte lbl_803D03A4
    .4byte lbl_803D03C0
    .4byte lbl_803D03E4
    .4byte lbl_803D03F0
    .4byte lbl_803D040C
    .4byte lbl_803D0430
    .4byte lbl_803D043C
    .4byte lbl_803D0458

.global lbl_803D0544
lbl_803D0544:
    .asciz "PlyPurinReHat_TopN_joint"
    .balign 4

.global lbl_803D0560
lbl_803D0560:
    .asciz "PlyPurinBuHat_TopN_joint"
    .balign 4

.global lbl_803D057C
lbl_803D057C:
    .asciz "PlyPurinGrHat_TopN_joint"
    .balign 4

.global lbl_803D0598
lbl_803D0598:
    .asciz "PlyPurinYeHat_TopN_joint"
    .balign 4

.global lbl_803D05B4
lbl_803D05B4:
    .4byte NULL
    .4byte lbl_803D0544
    .4byte lbl_803D0560
    .4byte lbl_803D057C
    .4byte lbl_803D0598

.global lbl_803D05C8
lbl_803D05C8:
    .4byte 0x3F266666
    .4byte 0x3F333333
    .4byte 0x3F4CCCCD
    .4byte 0x3F800000

.global lbl_803D05D8
lbl_803D05D8:
    .4byte 0x3F8CCCCD
    .4byte 0x3FACCCCD
    .4byte 0x3FA66666
    .4byte 0x3F99999A
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4

.global lbl_803D0610
lbl_803D0610:
    .4byte 0x41000000
    .4byte NULL
    .4byte 0xC0800000
    .4byte 0x40800000
    .4byte 0x40800000
    .4byte 0x40800000


.section .sdata
    .balign 8


.global lbl_804D3E98
lbl_804D3E98:
    .asciz "jobj.h"
    .balign 4

.global lbl_804D3EA0
lbl_804D3EA0:
    .asciz "jobj"
    .balign 4

.global lbl_804D3EA8
lbl_804D3EA8:
    .asciz "scale"
    .balign 4


.section .sdata2
    .balign 8


.global lbl_804D9C10
lbl_804D9C10:
	.4byte 0xBF800000

.global lbl_804D9C14
lbl_804D9C14:
	.4byte 0x00000000

.global lbl_804D9C18
lbl_804D9C18:
	.4byte 0x3F800000
	.4byte 0x00000000

.global lbl_804D9C20
lbl_804D9C20:
	.4byte 0xBF800000

.global lbl_804D9C24
lbl_804D9C24:
	.4byte 0x00000000

.global lbl_804D9C28
lbl_804D9C28:
	.4byte 0x3F800000
	.4byte 0x00000000

.global lbl_804D9C30
lbl_804D9C30:
	.4byte 0x00000000

.global lbl_804D9C34
lbl_804D9C34:
	.4byte 0x3C8EFA35

.global lbl_804D9C38
lbl_804D9C38:
	.4byte 0x3F800000
	.4byte 0x00000000

.global lbl_804D9C40
lbl_804D9C40:
	.4byte 0x3FF921FB
	.4byte 0x54442D18

.global lbl_804D9C48
lbl_804D9C48:
	.4byte 0x00000000

.global lbl_804D9C4C
lbl_804D9C4C:
	.4byte 0x3FC90FDB

.global lbl_804D9C50
lbl_804D9C50:
	.4byte 0x3F800000

.global lbl_804D9C54
lbl_804D9C54:
	.4byte 0x3F000000

.global lbl_804D9C58
lbl_804D9C58:
	.4byte 0x401921FB
	.4byte 0x54442D18

.global lbl_804D9C60
lbl_804D9C60:
	.4byte 0xBF800000

.global lbl_804D9C64
lbl_804D9C64:
	.4byte 0x38D1B717

.global lbl_804D9C68
lbl_804D9C68:
	.4byte 0x3C8EFA35
	.4byte 0x00000000

.global lbl_804D9C70
lbl_804D9C70:
	.4byte 0x43300000
	.4byte 0x80000000

.global lbl_804D9C78
lbl_804D9C78:
	.4byte 0x3FC99999
	.4byte 0x9999999A

.global lbl_804D9C80
lbl_804D9C80:
	.4byte 0x4012D97C
	.4byte 0x7F3321D2

.global lbl_804D9C88
lbl_804D9C88:
	.4byte 0x400921FB
	.4byte 0x54442D18

.global lbl_804D9C90
lbl_804D9C90:
	.4byte 0xBD4CCCCD
	.4byte 0x00000000
