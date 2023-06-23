.include "macros.inc"

.section .text

.global it_8029B0C8
it_8029B0C8:
/* 8029B0C8 00297CA8  7C 08 02 A6 */	mflr r0
/* 8029B0CC 00297CAC  38 80 00 01 */	li r4, 1
/* 8029B0D0 00297CB0  90 01 00 04 */	stw r0, 4(r1)
/* 8029B0D4 00297CB4  38 00 00 2A */	li r0, 0x2a
/* 8029B0D8 00297CB8  94 21 FF 98 */	stwu r1, -0x68(r1)
/* 8029B0DC 00297CBC  93 E1 00 64 */	stw r31, 0x64(r1)
/* 8029B0E0 00297CC0  3B E0 00 00 */	li r31, 0
/* 8029B0E4 00297CC4  93 C1 00 60 */	stw r30, 0x60(r1)
/* 8029B0E8 00297CC8  90 01 00 1C */	stw r0, 0x1c(r1)
/* 8029B0EC 00297CCC  C0 22 D2 A8 */	lfs f1, it_804DCC88@sda21(r2)
/* 8029B0F0 00297CD0  80 A3 00 00 */	lwz r5, 0(r3)
/* 8029B0F4 00297CD4  80 03 00 04 */	lwz r0, 4(r3)
/* 8029B0F8 00297CD8  C0 02 D2 AC */	lfs f0, it_804DCC8C@sda21(r2)
/* 8029B0FC 00297CDC  90 A1 00 34 */	stw r5, 0x34(r1)
/* 8029B100 00297CE0  90 01 00 38 */	stw r0, 0x38(r1)
/* 8029B104 00297CE4  80 03 00 08 */	lwz r0, 8(r3)
/* 8029B108 00297CE8  90 01 00 3C */	stw r0, 0x3c(r1)
/* 8029B10C 00297CEC  80 A3 00 00 */	lwz r5, 0(r3)
/* 8029B110 00297CF0  80 03 00 04 */	lwz r0, 4(r3)
/* 8029B114 00297CF4  90 A1 00 28 */	stw r5, 0x28(r1)
/* 8029B118 00297CF8  90 01 00 2C */	stw r0, 0x2c(r1)
/* 8029B11C 00297CFC  80 03 00 08 */	lwz r0, 8(r3)
/* 8029B120 00297D00  38 61 00 14 */	addi r3, r1, 0x14
/* 8029B124 00297D04  90 01 00 30 */	stw r0, 0x30(r1)
/* 8029B128 00297D08  D0 21 00 4C */	stfs f1, 0x4c(r1)
/* 8029B12C 00297D0C  B3 E1 00 50 */	sth r31, 0x50(r1)
/* 8029B130 00297D10  D0 01 00 48 */	stfs f0, 0x48(r1)
/* 8029B134 00297D14  D0 01 00 44 */	stfs f0, 0x44(r1)
/* 8029B138 00297D18  D0 01 00 40 */	stfs f0, 0x40(r1)
/* 8029B13C 00297D1C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8029B140 00297D20  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8029B144 00297D24  90 01 00 18 */	stw r0, 0x18(r1)
/* 8029B148 00297D28  88 01 00 58 */	lbz r0, 0x58(r1)
/* 8029B14C 00297D2C  50 80 3E 30 */	rlwimi r0, r4, 7, 0x18, 0x18
/* 8029B150 00297D30  98 01 00 58 */	stb r0, 0x58(r1)
/* 8029B154 00297D34  93 E1 00 54 */	stw r31, 0x54(r1)
/* 8029B158 00297D38  4B FC D9 C1 */	bl Item_80268B18
/* 8029B15C 00297D3C  28 03 00 00 */	cmplwi r3, 0
/* 8029B160 00297D40  41 82 00 10 */	beq .L_8029B170
/* 8029B164 00297D44  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 8029B168 00297D48  48 00 01 01 */	bl it_8029B268
/* 8029B16C 00297D4C  93 FE 0D D4 */	stw r31, 0xdd4(r30)
.L_8029B170:
/* 8029B170 00297D50  80 01 00 6C */	lwz r0, 0x6c(r1)
/* 8029B174 00297D54  83 E1 00 64 */	lwz r31, 0x64(r1)
/* 8029B178 00297D58  83 C1 00 60 */	lwz r30, 0x60(r1)
/* 8029B17C 00297D5C  38 21 00 68 */	addi r1, r1, 0x68
/* 8029B180 00297D60  7C 08 03 A6 */	mtlr r0
/* 8029B184 00297D64  4E 80 00 20 */	blr

.global it_8029B188
it_8029B188:
/* 8029B188 00297D68  7C 08 02 A6 */	mflr r0
/* 8029B18C 00297D6C  38 60 00 01 */	li r3, 1
/* 8029B190 00297D70  90 01 00 04 */	stw r0, 4(r1)
/* 8029B194 00297D74  94 21 FF F8 */	stwu r1, -8(r1)
/* 8029B198 00297D78  4B F2 39 D1 */	bl gm_801BEB68
/* 8029B19C 00297D7C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8029B1A0 00297D80  38 21 00 08 */	addi r1, r1, 8
/* 8029B1A4 00297D84  7C 08 03 A6 */	mtlr r0
/* 8029B1A8 00297D88  4E 80 00 20 */	blr

.global it_8029B1AC
it_8029B1AC:
/* 8029B1AC 00297D8C  7C 08 02 A6 */	mflr r0
/* 8029B1B0 00297D90  90 01 00 04 */	stw r0, 4(r1)
/* 8029B1B4 00297D94  38 00 00 00 */	li r0, 0
/* 8029B1B8 00297D98  94 21 FF F8 */	stwu r1, -8(r1)
/* 8029B1BC 00297D9C  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 8029B1C0 00297DA0  90 04 0D D4 */	stw r0, 0xdd4(r4)
/* 8029B1C4 00297DA4  48 00 00 A5 */	bl it_8029B268
/* 8029B1C8 00297DA8  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8029B1CC 00297DAC  38 21 00 08 */	addi r1, r1, 8
/* 8029B1D0 00297DB0  7C 08 03 A6 */	mtlr r0
/* 8029B1D4 00297DB4  4E 80 00 20 */	blr

.global it_8029B1D8
it_8029B1D8:
/* 8029B1D8 00297DB8  7C 08 02 A6 */	mflr r0
/* 8029B1DC 00297DBC  90 01 00 04 */	stw r0, 4(r1)
/* 8029B1E0 00297DC0  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8029B1E4 00297DC4  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8029B1E8 00297DC8  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8029B1EC 00297DCC  7C 7E 1B 78 */	mr r30, r3
/* 8029B1F0 00297DD0  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8029B1F4 00297DD4  4B FD 01 9D */	bl it_8026B390
/* 8029B1F8 00297DD8  C0 02 D2 AC */	lfs f0, it_804DCC8C@sda21(r2)
/* 8029B1FC 00297DDC  38 7E 00 00 */	addi r3, r30, 0
/* 8029B200 00297DE0  38 80 00 00 */	li r4, 0
/* 8029B204 00297DE4  D0 1F 00 48 */	stfs f0, 0x48(r31)
/* 8029B208 00297DE8  38 A0 00 02 */	li r5, 2
/* 8029B20C 00297DEC  D0 1F 00 44 */	stfs f0, 0x44(r31)
/* 8029B210 00297DF0  D0 1F 00 40 */	stfs f0, 0x40(r31)
/* 8029B214 00297DF4  4B FC DC 49 */	bl Item_80268E5C
/* 8029B218 00297DF8  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8029B21C 00297DFC  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8029B220 00297E00  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8029B224 00297E04  38 21 00 20 */	addi r1, r1, 0x20
/* 8029B228 00297E08  7C 08 03 A6 */	mtlr r0
/* 8029B22C 00297E0C  4E 80 00 20 */	blr

.global it_8029B230
it_8029B230:
/* 8029B230 00297E10  38 60 00 00 */	li r3, 0
/* 8029B234 00297E14  4E 80 00 20 */	blr

.global it_8029B238
it_8029B238:
/* 8029B238 00297E18  4E 80 00 20 */	blr

.global it_8029B23C
it_8029B23C:
/* 8029B23C 00297E1C  7C 08 02 A6 */	mflr r0
/* 8029B240 00297E20  3C 80 80 2A */	lis r4, it_8029B268@ha
/* 8029B244 00297E24  90 01 00 04 */	stw r0, 4(r1)
/* 8029B248 00297E28  38 84 B2 68 */	addi r4, r4, it_8029B268@l
/* 8029B24C 00297E2C  94 21 FF F8 */	stwu r1, -8(r1)
/* 8029B250 00297E30  4B FD 23 DD */	bl it_8026D62C
/* 8029B254 00297E34  38 60 00 00 */	li r3, 0
/* 8029B258 00297E38  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8029B25C 00297E3C  38 21 00 08 */	addi r1, r1, 8
/* 8029B260 00297E40  7C 08 03 A6 */	mtlr r0
/* 8029B264 00297E44  4E 80 00 20 */	blr

.global it_8029B268
it_8029B268:
/* 8029B268 00297E48  7C 08 02 A6 */	mflr r0
/* 8029B26C 00297E4C  38 80 00 01 */	li r4, 1
/* 8029B270 00297E50  90 01 00 04 */	stw r0, 4(r1)
/* 8029B274 00297E54  38 A0 00 02 */	li r5, 2
/* 8029B278 00297E58  94 21 FF F8 */	stwu r1, -8(r1)
/* 8029B27C 00297E5C  4B FC DB E1 */	bl Item_80268E5C
/* 8029B280 00297E60  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8029B284 00297E64  38 21 00 08 */	addi r1, r1, 8
/* 8029B288 00297E68  7C 08 03 A6 */	mtlr r0
/* 8029B28C 00297E6C  4E 80 00 20 */	blr

.global it_8029B290
it_8029B290:
/* 8029B290 00297E70  38 60 00 00 */	li r3, 0
/* 8029B294 00297E74  4E 80 00 20 */	blr

.global it_8029B298
it_8029B298:
/* 8029B298 00297E78  7C 08 02 A6 */	mflr r0
/* 8029B29C 00297E7C  90 01 00 04 */	stw r0, 4(r1)
/* 8029B2A0 00297E80  94 21 FF F8 */	stwu r1, -8(r1)
/* 8029B2A4 00297E84  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 8029B2A8 00297E88  80 84 00 CC */	lwz r4, 0xcc(r4)
/* 8029B2AC 00297E8C  C0 24 00 10 */	lfs f1, 0x10(r4)
/* 8029B2B0 00297E90  C0 44 00 14 */	lfs f2, 0x14(r4)
/* 8029B2B4 00297E94  4B FD 75 AD */	bl it_80272860
/* 8029B2B8 00297E98  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8029B2BC 00297E9C  38 21 00 08 */	addi r1, r1, 8
/* 8029B2C0 00297EA0  7C 08 03 A6 */	mtlr r0
/* 8029B2C4 00297EA4  4E 80 00 20 */	blr

.global it_8029B2C8
it_8029B2C8:
/* 8029B2C8 00297EA8  7C 08 02 A6 */	mflr r0
/* 8029B2CC 00297EAC  3C 80 80 2A */	lis r4, it_8029B1D8@ha
/* 8029B2D0 00297EB0  90 01 00 04 */	stw r0, 4(r1)
/* 8029B2D4 00297EB4  38 84 B1 D8 */	addi r4, r4, it_8029B1D8@l
/* 8029B2D8 00297EB8  94 21 FF F8 */	stwu r1, -8(r1)
/* 8029B2DC 00297EBC  4B FD 30 51 */	bl it_8026E32C
/* 8029B2E0 00297EC0  38 60 00 00 */	li r3, 0
/* 8029B2E4 00297EC4  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8029B2E8 00297EC8  38 21 00 08 */	addi r1, r1, 8
/* 8029B2EC 00297ECC  7C 08 03 A6 */	mtlr r0
/* 8029B2F0 00297ED0  4E 80 00 20 */	blr

.global it_8029B2F4
it_8029B2F4:
/* 8029B2F4 00297ED4  7C 08 02 A6 */	mflr r0
/* 8029B2F8 00297ED8  38 80 00 02 */	li r4, 2
/* 8029B2FC 00297EDC  90 01 00 04 */	stw r0, 4(r1)
/* 8029B300 00297EE0  38 A0 00 02 */	li r5, 2
/* 8029B304 00297EE4  94 21 FF F8 */	stwu r1, -8(r1)
/* 8029B308 00297EE8  4B FC DB 55 */	bl Item_80268E5C
/* 8029B30C 00297EEC  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8029B310 00297EF0  38 21 00 08 */	addi r1, r1, 8
/* 8029B314 00297EF4  7C 08 03 A6 */	mtlr r0
/* 8029B318 00297EF8  4E 80 00 20 */	blr

.global it_8029B31C
it_8029B31C:
/* 8029B31C 00297EFC  38 60 00 00 */	li r3, 0
/* 8029B320 00297F00  4E 80 00 20 */	blr

.global it_8029B324
it_8029B324:
/* 8029B324 00297F04  4E 80 00 20 */	blr

.global it_8029B328
it_8029B328:
/* 8029B328 00297F08  7C 08 02 A6 */	mflr r0
/* 8029B32C 00297F0C  90 01 00 04 */	stw r0, 4(r1)
/* 8029B330 00297F10  94 21 FF F8 */	stwu r1, -8(r1)
/* 8029B334 00297F14  48 00 00 15 */	bl it_8029B348
/* 8029B338 00297F18  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8029B33C 00297F1C  38 21 00 08 */	addi r1, r1, 8
/* 8029B340 00297F20  7C 08 03 A6 */	mtlr r0
/* 8029B344 00297F24  4E 80 00 20 */	blr

.global it_8029B348
it_8029B348:
/* 8029B348 00297F28  7C 08 02 A6 */	mflr r0
/* 8029B34C 00297F2C  38 80 00 03 */	li r4, 3
/* 8029B350 00297F30  90 01 00 04 */	stw r0, 4(r1)
/* 8029B354 00297F34  38 A0 00 06 */	li r5, 6
/* 8029B358 00297F38  94 21 FF F8 */	stwu r1, -8(r1)
/* 8029B35C 00297F3C  4B FC DB 01 */	bl Item_80268E5C
/* 8029B360 00297F40  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8029B364 00297F44  38 21 00 08 */	addi r1, r1, 8
/* 8029B368 00297F48  7C 08 03 A6 */	mtlr r0
/* 8029B36C 00297F4C  4E 80 00 20 */	blr

.global it_8029B370
it_8029B370:
/* 8029B370 00297F50  7C 08 02 A6 */	mflr r0
/* 8029B374 00297F54  90 01 00 04 */	stw r0, 4(r1)
/* 8029B378 00297F58  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8029B37C 00297F5C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8029B380 00297F60  7C 7F 1B 78 */	mr r31, r3
/* 8029B384 00297F64  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 8029B388 00297F68  80 84 00 CC */	lwz r4, 0xcc(r4)
/* 8029B38C 00297F6C  C0 24 00 10 */	lfs f1, 0x10(r4)
/* 8029B390 00297F70  C0 44 00 14 */	lfs f2, 0x14(r4)
/* 8029B394 00297F74  4B FD 74 CD */	bl it_80272860
/* 8029B398 00297F78  80 8D B6 88 */	lwz r4, it_804D6D28@sda21(r13)
/* 8029B39C 00297F7C  7F E3 FB 78 */	mr r3, r31
/* 8029B3A0 00297F80  C0 24 00 68 */	lfs f1, 0x68(r4)
/* 8029B3A4 00297F84  4B FD 92 B5 */	bl it_80274658
/* 8029B3A8 00297F88  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8029B3AC 00297F8C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8029B3B0 00297F90  38 21 00 18 */	addi r1, r1, 0x18
/* 8029B3B4 00297F94  7C 08 03 A6 */	mtlr r0
/* 8029B3B8 00297F98  4E 80 00 20 */	blr

.global it_8029B3BC
it_8029B3BC:
/* 8029B3BC 00297F9C  7C 08 02 A6 */	mflr r0
/* 8029B3C0 00297FA0  90 01 00 04 */	stw r0, 4(r1)
/* 8029B3C4 00297FA4  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8029B3C8 00297FA8  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8029B3CC 00297FAC  7C 7F 1B 78 */	mr r31, r3
/* 8029B3D0 00297FB0  4B FD 26 39 */	bl it_8026DA08
/* 8029B3D4 00297FB4  2C 03 00 00 */	cmpwi r3, 0
/* 8029B3D8 00297FB8  41 82 00 10 */	beq .L_8029B3E8
/* 8029B3DC 00297FBC  7F E3 FB 78 */	mr r3, r31
/* 8029B3E0 00297FC0  48 00 00 8D */	bl it_8029B46C
/* 8029B3E4 00297FC4  48 00 00 08 */	b .L_8029B3EC
.L_8029B3E8:
/* 8029B3E8 00297FC8  38 60 00 00 */	li r3, 0
.L_8029B3EC:
/* 8029B3EC 00297FCC  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8029B3F0 00297FD0  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8029B3F4 00297FD4  38 21 00 18 */	addi r1, r1, 0x18
/* 8029B3F8 00297FD8  7C 08 03 A6 */	mtlr r0
/* 8029B3FC 00297FDC  4E 80 00 20 */	blr

.global it_8029B400
it_8029B400:
/* 8029B400 00297FE0  7C 08 02 A6 */	mflr r0
/* 8029B404 00297FE4  90 01 00 04 */	stw r0, 4(r1)
/* 8029B408 00297FE8  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8029B40C 00297FEC  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8029B410 00297FF0  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8029B414 00297FF4  80 1F 0D D8 */	lwz r0, 0xdd8(r31)
/* 8029B418 00297FF8  2C 00 00 28 */	cmpwi r0, 0x28
/* 8029B41C 00297FFC  40 82 00 0C */	bne .L_8029B428
/* 8029B420 00298000  38 60 00 01 */	li r3, 1
/* 8029B424 00298004  4B F2 37 45 */	bl gm_801BEB68
.L_8029B428:
/* 8029B428 00298008  80 7F 0D D8 */	lwz r3, 0xdd8(r31)
/* 8029B42C 0029800C  38 03 FF FF */	addi r0, r3, -1
/* 8029B430 00298010  90 1F 0D D8 */	stw r0, 0xdd8(r31)
/* 8029B434 00298014  80 1F 0D D8 */	lwz r0, 0xdd8(r31)
/* 8029B438 00298018  2C 00 00 00 */	cmpwi r0, 0
/* 8029B43C 0029801C  40 81 00 0C */	ble .L_8029B448
/* 8029B440 00298020  38 60 00 00 */	li r3, 0
/* 8029B444 00298024  48 00 00 08 */	b .L_8029B44C
.L_8029B448:
/* 8029B448 00298028  38 60 00 01 */	li r3, 1
.L_8029B44C:
/* 8029B44C 0029802C  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8029B450 00298030  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8029B454 00298034  38 21 00 18 */	addi r1, r1, 0x18
/* 8029B458 00298038  7C 08 03 A6 */	mtlr r0
/* 8029B45C 0029803C  4E 80 00 20 */	blr

.global it_8029B460
it_8029B460:
/* 8029B460 00298040  4E 80 00 20 */	blr

.global it_8029B464
it_8029B464:
/* 8029B464 00298044  38 60 00 00 */	li r3, 0
/* 8029B468 00298048  4E 80 00 20 */	blr

.global it_8029B46C
it_8029B46C:
/* 8029B46C 0029804C  7C 08 02 A6 */	mflr r0
/* 8029B470 00298050  38 80 00 01 */	li r4, 1
/* 8029B474 00298054  90 01 00 04 */	stw r0, 4(r1)
/* 8029B478 00298058  38 A0 00 02 */	li r5, 2
/* 8029B47C 0029805C  94 21 FF F8 */	stwu r1, -8(r1)
/* 8029B480 00298060  C0 02 D2 AC */	lfs f0, it_804DCC8C@sda21(r2)
/* 8029B484 00298064  80 C3 00 2C */	lwz r6, 0x2c(r3)
/* 8029B488 00298068  D0 06 00 40 */	stfs f0, 0x40(r6)
/* 8029B48C 0029806C  C0 02 D2 B0 */	lfs f0, it_804DCC90@sda21(r2)
/* 8029B490 00298070  D0 06 00 44 */	stfs f0, 0x44(r6)
/* 8029B494 00298074  4B FC D9 C9 */	bl Item_80268E5C
/* 8029B498 00298078  38 60 00 00 */	li r3, 0
/* 8029B49C 0029807C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8029B4A0 00298080  38 21 00 08 */	addi r1, r1, 8
/* 8029B4A4 00298084  7C 08 03 A6 */	mtlr r0
/* 8029B4A8 00298088  4E 80 00 20 */	blr

.global it_8029B4AC
it_8029B4AC:
/* 8029B4AC 0029808C  7C 08 02 A6 */	mflr r0
/* 8029B4B0 00298090  38 80 00 01 */	li r4, 1
/* 8029B4B4 00298094  90 01 00 04 */	stw r0, 4(r1)
/* 8029B4B8 00298098  38 A0 00 02 */	li r5, 2
/* 8029B4BC 0029809C  94 21 FF F8 */	stwu r1, -8(r1)
/* 8029B4C0 002980A0  C0 02 D2 AC */	lfs f0, it_804DCC8C@sda21(r2)
/* 8029B4C4 002980A4  80 C3 00 2C */	lwz r6, 0x2c(r3)
/* 8029B4C8 002980A8  D0 06 00 40 */	stfs f0, 0x40(r6)
/* 8029B4CC 002980AC  C0 02 D2 B0 */	lfs f0, it_804DCC90@sda21(r2)
/* 8029B4D0 002980B0  D0 06 00 44 */	stfs f0, 0x44(r6)
/* 8029B4D4 002980B4  4B FC D9 89 */	bl Item_80268E5C
/* 8029B4D8 002980B8  38 60 00 00 */	li r3, 0
/* 8029B4DC 002980BC  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8029B4E0 002980C0  38 21 00 08 */	addi r1, r1, 8
/* 8029B4E4 002980C4  7C 08 03 A6 */	mtlr r0
/* 8029B4E8 002980C8  4E 80 00 20 */	blr

.global it_8029B4EC
it_8029B4EC:
/* 8029B4EC 002980CC  7C 08 02 A6 */	mflr r0
/* 8029B4F0 002980D0  38 80 00 01 */	li r4, 1
/* 8029B4F4 002980D4  90 01 00 04 */	stw r0, 4(r1)
/* 8029B4F8 002980D8  38 A0 00 02 */	li r5, 2
/* 8029B4FC 002980DC  94 21 FF F8 */	stwu r1, -8(r1)
/* 8029B500 002980E0  C0 02 D2 AC */	lfs f0, it_804DCC8C@sda21(r2)
/* 8029B504 002980E4  80 C3 00 2C */	lwz r6, 0x2c(r3)
/* 8029B508 002980E8  D0 06 00 40 */	stfs f0, 0x40(r6)
/* 8029B50C 002980EC  C0 02 D2 B0 */	lfs f0, it_804DCC90@sda21(r2)
/* 8029B510 002980F0  D0 06 00 44 */	stfs f0, 0x44(r6)
/* 8029B514 002980F4  4B FC D9 49 */	bl Item_80268E5C
/* 8029B518 002980F8  38 60 00 00 */	li r3, 0
/* 8029B51C 002980FC  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8029B520 00298100  38 21 00 08 */	addi r1, r1, 8
/* 8029B524 00298104  7C 08 03 A6 */	mtlr r0
/* 8029B528 00298108  4E 80 00 20 */	blr

.global it_8029B52C
it_8029B52C:
/* 8029B52C 0029810C  7C 08 02 A6 */	mflr r0
/* 8029B530 00298110  38 80 00 01 */	li r4, 1
/* 8029B534 00298114  90 01 00 04 */	stw r0, 4(r1)
/* 8029B538 00298118  38 A0 00 02 */	li r5, 2
/* 8029B53C 0029811C  94 21 FF F8 */	stwu r1, -8(r1)
/* 8029B540 00298120  C0 02 D2 AC */	lfs f0, it_804DCC8C@sda21(r2)
/* 8029B544 00298124  80 C3 00 2C */	lwz r6, 0x2c(r3)
/* 8029B548 00298128  D0 06 00 40 */	stfs f0, 0x40(r6)
/* 8029B54C 0029812C  C0 02 D2 B0 */	lfs f0, it_804DCC90@sda21(r2)
/* 8029B550 00298130  D0 06 00 44 */	stfs f0, 0x44(r6)
/* 8029B554 00298134  4B FC D9 09 */	bl Item_80268E5C
/* 8029B558 00298138  38 60 00 00 */	li r3, 0
/* 8029B55C 0029813C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8029B560 00298140  38 21 00 08 */	addi r1, r1, 8
/* 8029B564 00298144  7C 08 03 A6 */	mtlr r0
/* 8029B568 00298148  4E 80 00 20 */	blr

.global it_8029B56C
it_8029B56C:
/* 8029B56C 0029814C  7C 08 02 A6 */	mflr r0
/* 8029B570 00298150  90 01 00 04 */	stw r0, 4(r1)
/* 8029B574 00298154  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8029B578 00298158  93 E1 00 24 */	stw r31, 0x24(r1)
/* 8029B57C 0029815C  93 C1 00 20 */	stw r30, 0x20(r1)
/* 8029B580 00298160  7C 7E 1B 78 */	mr r30, r3
/* 8029B584 00298164  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8029B588 00298168  80 1F 0D D4 */	lwz r0, 0xdd4(r31)
/* 8029B58C 0029816C  80 7F 00 C4 */	lwz r3, 0xc4(r31)
/* 8029B590 00298170  2C 00 00 00 */	cmpwi r0, 0
/* 8029B594 00298174  80 83 00 04 */	lwz r4, 4(r3)
/* 8029B598 00298178  41 82 00 0C */	beq .L_8029B5A4
/* 8029B59C 0029817C  38 60 00 00 */	li r3, 0
/* 8029B5A0 00298180  48 00 00 B8 */	b .L_8029B658
.L_8029B5A4:
/* 8029B5A4 00298184  80 7F 0C 9C */	lwz r3, 0xc9c(r31)
/* 8029B5A8 00298188  80 04 00 00 */	lwz r0, 0(r4)
/* 8029B5AC 0029818C  7C 03 00 00 */	cmpw r3, r0
/* 8029B5B0 00298190  40 80 00 0C */	bge .L_8029B5BC
/* 8029B5B4 00298194  38 60 00 00 */	li r3, 0
/* 8029B5B8 00298198  48 00 00 A0 */	b .L_8029B658
.L_8029B5BC:
/* 8029B5BC 0029819C  C0 02 D2 B0 */	lfs f0, it_804DCC90@sda21(r2)
/* 8029B5C0 002981A0  38 9E 00 00 */	addi r4, r30, 0
/* 8029B5C4 002981A4  38 BF 00 4C */	addi r5, r31, 0x4c
/* 8029B5C8 002981A8  4C C6 31 82 */	crclr 6
/* 8029B5CC 002981AC  D0 01 00 18 */	stfs f0, 0x18(r1)
/* 8029B5D0 002981B0  38 C1 00 18 */	addi r6, r1, 0x18
/* 8029B5D4 002981B4  38 60 04 CF */	li r3, 0x4cf
/* 8029B5D8 002981B8  4B DC 48 05 */	bl efSync_Spawn
/* 8029B5DC 002981BC  38 9E 00 00 */	addi r4, r30, 0
/* 8029B5E0 002981C0  4C C6 31 82 */	crclr 6
/* 8029B5E4 002981C4  38 BF 00 4C */	addi r5, r31, 0x4c
/* 8029B5E8 002981C8  38 C1 00 18 */	addi r6, r1, 0x18
/* 8029B5EC 002981CC  38 60 04 CF */	li r3, 0x4cf
/* 8029B5F0 002981D0  4B DC 47 ED */	bl efSync_Spawn
/* 8029B5F4 002981D4  38 7F 00 00 */	addi r3, r31, 0
/* 8029B5F8 002981D8  38 80 00 F4 */	li r4, 0xf4
/* 8029B5FC 002981DC  38 A0 00 7F */	li r5, 0x7f
/* 8029B600 002981E0  38 C0 00 40 */	li r6, 0x40
/* 8029B604 002981E4  4B FC F8 81 */	bl Item_8026AE84
/* 8029B608 002981E8  80 7E 00 28 */	lwz r3, 0x28(r30)
/* 8029B60C 002981EC  38 80 00 10 */	li r4, 0x10
/* 8029B610 002981F0  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 8029B614 002981F4  48 0D 67 89 */	bl HSD_JObjSetFlagsAll
/* 8029B618 002981F8  7F C3 F3 78 */	mr r3, r30
/* 8029B61C 002981FC  4B FD A0 B5 */	bl it_802756D0
/* 8029B620 00298200  C0 02 D2 AC */	lfs f0, it_804DCC8C@sda21(r2)
/* 8029B624 00298204  38 80 00 01 */	li r4, 1
/* 8029B628 00298208  38 00 00 3C */	li r0, 0x3c
/* 8029B62C 0029820C  D0 1F 00 40 */	stfs f0, 0x40(r31)
/* 8029B630 00298210  7F C3 F3 78 */	mr r3, r30
/* 8029B634 00298214  D0 1F 00 44 */	stfs f0, 0x44(r31)
/* 8029B638 00298218  90 9F 0D D4 */	stw r4, 0xdd4(r31)
/* 8029B63C 0029821C  90 1F 0D D8 */	stw r0, 0xdd8(r31)
/* 8029B640 00298220  4B FC FD 69 */	bl it_8026B3A8
/* 8029B644 00298224  38 7E 00 00 */	addi r3, r30, 0
/* 8029B648 00298228  38 80 00 05 */	li r4, 5
/* 8029B64C 0029822C  38 A0 00 02 */	li r5, 2
/* 8029B650 00298230  4B FC D8 0D */	bl Item_80268E5C
/* 8029B654 00298234  38 60 00 00 */	li r3, 0
.L_8029B658:
/* 8029B658 00298238  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8029B65C 0029823C  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 8029B660 00298240  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 8029B664 00298244  38 21 00 28 */	addi r1, r1, 0x28
/* 8029B668 00298248  7C 08 03 A6 */	mtlr r0
/* 8029B66C 0029824C  4E 80 00 20 */	blr

.global it_8029B670
it_8029B670:
/* 8029B670 00298250  7C 08 02 A6 */	mflr r0
/* 8029B674 00298254  38 80 00 04 */	li r4, 4
/* 8029B678 00298258  90 01 00 04 */	stw r0, 4(r1)
/* 8029B67C 0029825C  38 A0 00 02 */	li r5, 2
/* 8029B680 00298260  94 21 FF F8 */	stwu r1, -8(r1)
/* 8029B684 00298264  4B FC D7 D9 */	bl Item_80268E5C
/* 8029B688 00298268  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8029B68C 0029826C  38 21 00 08 */	addi r1, r1, 8
/* 8029B690 00298270  7C 08 03 A6 */	mtlr r0
/* 8029B694 00298274  4E 80 00 20 */	blr

.global it_8029B698
it_8029B698:
/* 8029B698 00298278  38 60 00 00 */	li r3, 0
/* 8029B69C 0029827C  4E 80 00 20 */	blr

.global it_8029B6A0
it_8029B6A0:
/* 8029B6A0 00298280  4E 80 00 20 */	blr

.global it_8029B6A4
it_8029B6A4:
/* 8029B6A4 00298284  7C 08 02 A6 */	mflr r0
/* 8029B6A8 00298288  3C 80 80 2A */	lis r4, it_8029B1D8@ha
/* 8029B6AC 0029828C  90 01 00 04 */	stw r0, 4(r1)
/* 8029B6B0 00298290  3C A0 80 2A */	lis r5, it_8029B268@ha
/* 8029B6B4 00298294  38 84 B1 D8 */	addi r4, r4, it_8029B1D8@l
/* 8029B6B8 00298298  94 21 FF F8 */	stwu r1, -8(r1)
/* 8029B6BC 0029829C  38 A5 B2 68 */	addi r5, r5, it_8029B268@l
/* 8029B6C0 002982A0  4B FD 32 05 */	bl it_8026E8C4
/* 8029B6C4 002982A4  38 60 00 00 */	li r3, 0
/* 8029B6C8 002982A8  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8029B6CC 002982AC  38 21 00 08 */	addi r1, r1, 8
/* 8029B6D0 002982B0  7C 08 03 A6 */	mtlr r0
/* 8029B6D4 002982B4  4E 80 00 20 */	blr

.global it_8029B6D8
it_8029B6D8:
/* 8029B6D8 002982B8  7C 08 02 A6 */	mflr r0
/* 8029B6DC 002982BC  90 01 00 04 */	stw r0, 4(r1)
/* 8029B6E0 002982C0  94 21 FF F8 */	stwu r1, -8(r1)
/* 8029B6E4 002982C4  4B FD 01 B1 */	bl it_8026B894
/* 8029B6E8 002982C8  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8029B6EC 002982CC  38 21 00 08 */	addi r1, r1, 8
/* 8029B6F0 002982D0  7C 08 03 A6 */	mtlr r0
/* 8029B6F4 002982D4  4E 80 00 20 */	blr


.section .data
    .balign 8
.global it_803F6728
it_803F6728:
    .4byte -1
    .4byte it_8029B230
    .4byte it_8029B238
    .4byte it_8029B23C
    .4byte -1
    .4byte it_8029B290
    .4byte it_8029B298
    .4byte it_8029B2C8
    .4byte -1
    .4byte it_8029B31C
    .4byte it_8029B324
    .4byte NULL
    .4byte 0
    .4byte it_8029B290
    .4byte it_8029B370
    .4byte it_8029B3BC
    .4byte -1
    .4byte it_8029B698
    .4byte it_8029B6A0
    .4byte it_8029B6A4
    .4byte -1
    .4byte it_8029B400
    .4byte it_8029B460
    .4byte it_8029B464


.section .sdata2
    .balign 8
.global it_804DCC88
it_804DCC88:
    .4byte 0x3F800000
.global it_804DCC8C
it_804DCC8C:
    .4byte 0x00000000
.global it_804DCC90
it_804DCC90:
    .4byte 0x3FC00000
