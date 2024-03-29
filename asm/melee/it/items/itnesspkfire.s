.include "macros.inc"

.section .text

.global it_802AA054
it_802AA054:
/* 802AA054 002A6C34  7C 08 02 A6 */	mflr r0
/* 802AA058 002A6C38  90 01 00 04 */	stw r0, 4(r1)
/* 802AA05C 002A6C3C  38 00 00 42 */	li r0, 0x42
/* 802AA060 002A6C40  94 21 FF 68 */	stwu r1, -0x98(r1)
/* 802AA064 002A6C44  DB E1 00 90 */	stfd f31, 0x90(r1)
/* 802AA068 002A6C48  FF E0 10 90 */	fmr f31, f2
/* 802AA06C 002A6C4C  DB C1 00 88 */	stfd f30, 0x88(r1)
/* 802AA070 002A6C50  FF C0 08 90 */	fmr f30, f1
/* 802AA074 002A6C54  93 E1 00 84 */	stw r31, 0x84(r1)
/* 802AA078 002A6C58  93 C1 00 80 */	stw r30, 0x80(r1)
/* 802AA07C 002A6C5C  7C BE 2B 78 */	mr r30, r5
/* 802AA080 002A6C60  93 A1 00 7C */	stw r29, 0x7c(r1)
/* 802AA084 002A6C64  7C 7D 1B 78 */	mr r29, r3
/* 802AA088 002A6C68  90 01 00 30 */	stw r0, 0x30(r1)
/* 802AA08C 002A6C6C  C0 02 D4 78 */	lfs f0, it_804DCE58@sda21(r2)
/* 802AA090 002A6C70  80 64 00 00 */	lwz r3, 0(r4)
/* 802AA094 002A6C74  80 04 00 04 */	lwz r0, 4(r4)
/* 802AA098 002A6C78  90 61 00 48 */	stw r3, 0x48(r1)
/* 802AA09C 002A6C7C  7F A3 EB 78 */	mr r3, r29
/* 802AA0A0 002A6C80  90 01 00 4C */	stw r0, 0x4c(r1)
/* 802AA0A4 002A6C84  80 04 00 08 */	lwz r0, 8(r4)
/* 802AA0A8 002A6C88  38 81 00 3C */	addi r4, r1, 0x3c
/* 802AA0AC 002A6C8C  90 01 00 50 */	stw r0, 0x50(r1)
/* 802AA0B0 002A6C90  D0 01 00 50 */	stfs f0, 0x50(r1)
/* 802AA0B4 002A6C94  4B FC 1A B5 */	bl it_8026BB68
/* 802AA0B8 002A6C98  80 DE 00 00 */	lwz r6, 0(r30)
/* 802AA0BC 002A6C9C  38 A0 00 00 */	li r5, 0
/* 802AA0C0 002A6CA0  80 1E 00 04 */	lwz r0, 4(r30)
/* 802AA0C4 002A6CA4  38 80 00 01 */	li r4, 1
/* 802AA0C8 002A6CA8  38 61 00 28 */	addi r3, r1, 0x28
/* 802AA0CC 002A6CAC  90 C1 00 54 */	stw r6, 0x54(r1)
/* 802AA0D0 002A6CB0  90 01 00 58 */	stw r0, 0x58(r1)
/* 802AA0D4 002A6CB4  80 1E 00 08 */	lwz r0, 8(r30)
/* 802AA0D8 002A6CB8  90 01 00 5C */	stw r0, 0x5c(r1)
/* 802AA0DC 002A6CBC  D3 C1 00 60 */	stfs f30, 0x60(r1)
/* 802AA0E0 002A6CC0  B0 A1 00 64 */	sth r5, 0x64(r1)
/* 802AA0E4 002A6CC4  93 A1 00 28 */	stw r29, 0x28(r1)
/* 802AA0E8 002A6CC8  80 01 00 28 */	lwz r0, 0x28(r1)
/* 802AA0EC 002A6CCC  90 01 00 2C */	stw r0, 0x2c(r1)
/* 802AA0F0 002A6CD0  88 01 00 6C */	lbz r0, 0x6c(r1)
/* 802AA0F4 002A6CD4  50 80 3E 30 */	rlwimi r0, r4, 7, 0x18, 0x18
/* 802AA0F8 002A6CD8  98 01 00 6C */	stb r0, 0x6c(r1)
/* 802AA0FC 002A6CDC  90 A1 00 68 */	stw r5, 0x68(r1)
/* 802AA100 002A6CE0  4B FB EA 19 */	bl Item_80268B18
/* 802AA104 002A6CE4  7C 7F 1B 79 */	or. r31, r3, r3
/* 802AA108 002A6CE8  41 82 00 AC */	beq .L_802AA1B4
/* 802AA10C 002A6CEC  83 DF 00 28 */	lwz r30, 0x28(r31)
/* 802AA110 002A6CF0  38 7F 00 00 */	addi r3, r31, 0
/* 802AA114 002A6CF4  38 9D 00 00 */	addi r4, r29, 0
/* 802AA118 002A6CF8  4B F7 BC C1 */	bl db_80225DD8
/* 802AA11C 002A6CFC  7F E3 FB 78 */	mr r3, r31
/* 802AA120 002A6D00  48 00 00 B9 */	bl it_802AA1D8
/* 802AA124 002A6D04  28 1E 00 00 */	cmplwi r30, 0
/* 802AA128 002A6D08  40 82 00 14 */	bne .L_802AA13C
/* 802AA12C 002A6D0C  38 6D 9D 28 */	addi r3, r13, it_804D53C8@sda21
/* 802AA130 002A6D10  38 80 02 A9 */	li r4, 0x2a9
/* 802AA134 002A6D14  38 AD 9D 30 */	addi r5, r13, it_804D53D0@sda21
/* 802AA138 002A6D18  48 0D E0 E9 */	bl __assert
.L_802AA13C:
/* 802AA13C 002A6D1C  80 1E 00 14 */	lwz r0, 0x14(r30)
/* 802AA140 002A6D20  54 00 03 9D */	rlwinm. r0, r0, 0, 0xe, 0xe
/* 802AA144 002A6D24  41 82 00 18 */	beq .L_802AA15C
/* 802AA148 002A6D28  3C 60 80 3F */	lis r3, it_803F6B38@ha
/* 802AA14C 002A6D2C  38 A3 6B 38 */	addi r5, r3, it_803F6B38@l
/* 802AA150 002A6D30  38 6D 9D 28 */	addi r3, r13, it_804D53C8@sda21
/* 802AA154 002A6D34  38 80 02 AA */	li r4, 0x2aa
/* 802AA158 002A6D38  48 0D E0 C9 */	bl __assert
.L_802AA15C:
/* 802AA15C 002A6D3C  D3 FE 00 24 */	stfs f31, 0x24(r30)
/* 802AA160 002A6D40  80 1E 00 14 */	lwz r0, 0x14(r30)
/* 802AA164 002A6D44  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 802AA168 002A6D48  40 82 00 4C */	bne .L_802AA1B4
/* 802AA16C 002A6D4C  28 1E 00 00 */	cmplwi r30, 0
/* 802AA170 002A6D50  41 82 00 44 */	beq .L_802AA1B4
/* 802AA174 002A6D54  40 82 00 14 */	bne .L_802AA188
/* 802AA178 002A6D58  38 6D 9D 28 */	addi r3, r13, it_804D53C8@sda21
/* 802AA17C 002A6D5C  38 80 02 34 */	li r4, 0x234
/* 802AA180 002A6D60  38 AD 9D 30 */	addi r5, r13, it_804D53D0@sda21
/* 802AA184 002A6D64  48 0D E0 9D */	bl __assert
.L_802AA188:
/* 802AA188 002A6D68  80 9E 00 14 */	lwz r4, 0x14(r30)
/* 802AA18C 002A6D6C  38 60 00 00 */	li r3, 0
/* 802AA190 002A6D70  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 802AA194 002A6D74  40 82 00 10 */	bne .L_802AA1A4
/* 802AA198 002A6D78  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 802AA19C 002A6D7C  41 82 00 08 */	beq .L_802AA1A4
/* 802AA1A0 002A6D80  38 60 00 01 */	li r3, 1
.L_802AA1A4:
/* 802AA1A4 002A6D84  2C 03 00 00 */	cmpwi r3, 0
/* 802AA1A8 002A6D88  40 82 00 0C */	bne .L_802AA1B4
/* 802AA1AC 002A6D8C  7F C3 F3 78 */	mr r3, r30
/* 802AA1B0 002A6D90  48 0C 91 39 */	bl HSD_JObjSetMtxDirtySub
.L_802AA1B4:
/* 802AA1B4 002A6D94  80 01 00 9C */	lwz r0, 0x9c(r1)
/* 802AA1B8 002A6D98  CB E1 00 90 */	lfd f31, 0x90(r1)
/* 802AA1BC 002A6D9C  CB C1 00 88 */	lfd f30, 0x88(r1)
/* 802AA1C0 002A6DA0  83 E1 00 84 */	lwz r31, 0x84(r1)
/* 802AA1C4 002A6DA4  83 C1 00 80 */	lwz r30, 0x80(r1)
/* 802AA1C8 002A6DA8  83 A1 00 7C */	lwz r29, 0x7c(r1)
/* 802AA1CC 002A6DAC  38 21 00 98 */	addi r1, r1, 0x98
/* 802AA1D0 002A6DB0  7C 08 03 A6 */	mtlr r0
/* 802AA1D4 002A6DB4  4E 80 00 20 */	blr

.global it_802AA1D8
it_802AA1D8:
/* 802AA1D8 002A6DB8  7C 08 02 A6 */	mflr r0
/* 802AA1DC 002A6DBC  38 80 00 00 */	li r4, 0
/* 802AA1E0 002A6DC0  90 01 00 04 */	stw r0, 4(r1)
/* 802AA1E4 002A6DC4  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 802AA1E8 002A6DC8  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 802AA1EC 002A6DCC  93 C1 00 18 */	stw r30, 0x18(r1)
/* 802AA1F0 002A6DD0  7C 7E 1B 78 */	mr r30, r3
/* 802AA1F4 002A6DD4  80 A3 00 2C */	lwz r5, 0x2c(r3)
/* 802AA1F8 002A6DD8  80 C5 00 C4 */	lwz r6, 0xc4(r5)
/* 802AA1FC 002A6DDC  38 A0 00 02 */	li r5, 2
/* 802AA200 002A6DE0  83 E6 00 04 */	lwz r31, 4(r6)
/* 802AA204 002A6DE4  4B FB EC 59 */	bl Item_80268E5C
/* 802AA208 002A6DE8  7F C3 F3 78 */	mr r3, r30
/* 802AA20C 002A6DEC  C0 3F 00 00 */	lfs f1, 0(r31)
/* 802AA210 002A6DF0  4B FC AF 49 */	bl it_80275158
/* 802AA214 002A6DF4  80 01 00 24 */	lwz r0, 0x24(r1)
/* 802AA218 002A6DF8  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 802AA21C 002A6DFC  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 802AA220 002A6E00  38 21 00 20 */	addi r1, r1, 0x20
/* 802AA224 002A6E04  7C 08 03 A6 */	mtlr r0
/* 802AA228 002A6E08  4E 80 00 20 */	blr

.global it_802AA22C
it_802AA22C:
/* 802AA22C 002A6E0C  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 802AA230 002A6E10  C0 02 D4 7C */	lfs f0, it_804DCE5C@sda21(r2)
/* 802AA234 002A6E14  C0 23 0D 44 */	lfs f1, 0xd44(r3)
/* 802AA238 002A6E18  EC 01 00 28 */	fsubs f0, f1, f0
/* 802AA23C 002A6E1C  D0 03 0D 44 */	stfs f0, 0xd44(r3)
/* 802AA240 002A6E20  C0 23 0D 44 */	lfs f1, 0xd44(r3)
/* 802AA244 002A6E24  C0 02 D4 78 */	lfs f0, it_804DCE58@sda21(r2)
/* 802AA248 002A6E28  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 802AA24C 002A6E2C  4C 40 13 82 */	cror 2, 0, 2
/* 802AA250 002A6E30  40 82 00 0C */	bne .L_802AA25C
/* 802AA254 002A6E34  38 60 00 01 */	li r3, 1
/* 802AA258 002A6E38  4E 80 00 20 */	blr
.L_802AA25C:
/* 802AA25C 002A6E3C  38 60 00 00 */	li r3, 0
/* 802AA260 002A6E40  4E 80 00 20 */	blr

.global it_802AA264
it_802AA264:
/* 802AA264 002A6E44  7C 08 02 A6 */	mflr r0
/* 802AA268 002A6E48  90 01 00 04 */	stw r0, 4(r1)
/* 802AA26C 002A6E4C  94 21 FF F8 */	stwu r1, -8(r1)
/* 802AA270 002A6E50  4B FC 3D E9 */	bl it_8026E058
/* 802AA274 002A6E54  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802AA278 002A6E58  38 21 00 08 */	addi r1, r1, 8
/* 802AA27C 002A6E5C  7C 08 03 A6 */	mtlr r0
/* 802AA280 002A6E60  4E 80 00 20 */	blr

.global it_802AA284
it_802AA284:
/* 802AA284 002A6E64  7C 08 02 A6 */	mflr r0
/* 802AA288 002A6E68  90 01 00 04 */	stw r0, 4(r1)
/* 802AA28C 002A6E6C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 802AA290 002A6E70  80 E3 00 2C */	lwz r7, 0x2c(r3)
/* 802AA294 002A6E74  38 A1 00 10 */	addi r5, r1, 0x10
/* 802AA298 002A6E78  80 C7 00 C4 */	lwz r6, 0xc4(r7)
/* 802AA29C 002A6E7C  80 87 00 4C */	lwz r4, 0x4c(r7)
/* 802AA2A0 002A6E80  80 C6 00 04 */	lwz r6, 4(r6)
/* 802AA2A4 002A6E84  80 07 00 50 */	lwz r0, 0x50(r7)
/* 802AA2A8 002A6E88  90 81 00 10 */	stw r4, 0x10(r1)
/* 802AA2AC 002A6E8C  90 01 00 14 */	stw r0, 0x14(r1)
/* 802AA2B0 002A6E90  80 07 00 54 */	lwz r0, 0x54(r7)
/* 802AA2B4 002A6E94  90 01 00 18 */	stw r0, 0x18(r1)
/* 802AA2B8 002A6E98  C0 21 00 14 */	lfs f1, 0x14(r1)
/* 802AA2BC 002A6E9C  C0 06 00 04 */	lfs f0, 4(r6)
/* 802AA2C0 002A6EA0  EC 01 00 2A */	fadds f0, f1, f0
/* 802AA2C4 002A6EA4  D0 01 00 14 */	stfs f0, 0x14(r1)
/* 802AA2C8 002A6EA8  80 87 05 18 */	lwz r4, 0x518(r7)
/* 802AA2CC 002A6EAC  C0 27 00 2C */	lfs f1, 0x2c(r7)
/* 802AA2D0 002A6EB0  48 00 01 C5 */	bl it_802AA494
/* 802AA2D4 002A6EB4  38 60 00 01 */	li r3, 1
/* 802AA2D8 002A6EB8  80 01 00 24 */	lwz r0, 0x24(r1)
/* 802AA2DC 002A6EBC  38 21 00 20 */	addi r1, r1, 0x20
/* 802AA2E0 002A6EC0  7C 08 03 A6 */	mtlr r0
/* 802AA2E4 002A6EC4  4E 80 00 20 */	blr

.global it_802AA2E8
it_802AA2E8:
/* 802AA2E8 002A6EC8  7C 08 02 A6 */	mflr r0
/* 802AA2EC 002A6ECC  90 01 00 04 */	stw r0, 4(r1)
/* 802AA2F0 002A6ED0  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 802AA2F4 002A6ED4  80 E3 00 2C */	lwz r7, 0x2c(r3)
/* 802AA2F8 002A6ED8  38 A1 00 10 */	addi r5, r1, 0x10
/* 802AA2FC 002A6EDC  80 C7 00 C4 */	lwz r6, 0xc4(r7)
/* 802AA300 002A6EE0  80 87 00 4C */	lwz r4, 0x4c(r7)
/* 802AA304 002A6EE4  80 C6 00 04 */	lwz r6, 4(r6)
/* 802AA308 002A6EE8  80 07 00 50 */	lwz r0, 0x50(r7)
/* 802AA30C 002A6EEC  90 81 00 10 */	stw r4, 0x10(r1)
/* 802AA310 002A6EF0  90 01 00 14 */	stw r0, 0x14(r1)
/* 802AA314 002A6EF4  80 07 00 54 */	lwz r0, 0x54(r7)
/* 802AA318 002A6EF8  90 01 00 18 */	stw r0, 0x18(r1)
/* 802AA31C 002A6EFC  C0 21 00 14 */	lfs f1, 0x14(r1)
/* 802AA320 002A6F00  C0 06 00 04 */	lfs f0, 4(r6)
/* 802AA324 002A6F04  EC 01 00 2A */	fadds f0, f1, f0
/* 802AA328 002A6F08  D0 01 00 14 */	stfs f0, 0x14(r1)
/* 802AA32C 002A6F0C  80 87 05 18 */	lwz r4, 0x518(r7)
/* 802AA330 002A6F10  C0 27 00 2C */	lfs f1, 0x2c(r7)
/* 802AA334 002A6F14  48 00 01 61 */	bl it_802AA494
/* 802AA338 002A6F18  38 60 00 01 */	li r3, 1
/* 802AA33C 002A6F1C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 802AA340 002A6F20  38 21 00 20 */	addi r1, r1, 0x20
/* 802AA344 002A6F24  7C 08 03 A6 */	mtlr r0
/* 802AA348 002A6F28  4E 80 00 20 */	blr

.global it_802AA34C
it_802AA34C:
/* 802AA34C 002A6F2C  38 60 00 01 */	li r3, 1
/* 802AA350 002A6F30  4E 80 00 20 */	blr

.global it_802AA354
it_802AA354:
/* 802AA354 002A6F34  38 60 00 01 */	li r3, 1
/* 802AA358 002A6F38  4E 80 00 20 */	blr

.global it_802AA35C
it_802AA35C:
/* 802AA35C 002A6F3C  7C 08 02 A6 */	mflr r0
/* 802AA360 002A6F40  90 01 00 04 */	stw r0, 4(r1)
/* 802AA364 002A6F44  94 21 FF F8 */	stwu r1, -8(r1)
/* 802AA368 002A6F48  4B FC 8C C9 */	bl it_80273030
/* 802AA36C 002A6F4C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802AA370 002A6F50  38 21 00 08 */	addi r1, r1, 8
/* 802AA374 002A6F54  7C 08 03 A6 */	mtlr r0
/* 802AA378 002A6F58  4E 80 00 20 */	blr

.global it_802AA37C
it_802AA37C:
/* 802AA37C 002A6F5C  7C 08 02 A6 */	mflr r0
/* 802AA380 002A6F60  90 01 00 04 */	stw r0, 4(r1)
/* 802AA384 002A6F64  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 802AA388 002A6F68  DB E1 00 20 */	stfd f31, 0x20(r1)
/* 802AA38C 002A6F6C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 802AA390 002A6F70  93 C1 00 18 */	stw r30, 0x18(r1)
/* 802AA394 002A6F74  7C 7E 1B 78 */	mr r30, r3
/* 802AA398 002A6F78  80 03 00 28 */	lwz r0, 0x28(r3)
/* 802AA39C 002A6F7C  28 00 00 00 */	cmplwi r0, 0
/* 802AA3A0 002A6F80  7C 1F 03 78 */	mr r31, r0
/* 802AA3A4 002A6F84  40 82 00 14 */	bne .L_802AA3B8
/* 802AA3A8 002A6F88  38 6D 9D 28 */	addi r3, r13, it_804D53C8@sda21
/* 802AA3AC 002A6F8C  38 80 02 E9 */	li r4, 0x2e9
/* 802AA3B0 002A6F90  38 AD 9D 30 */	addi r5, r13, it_804D53D0@sda21
/* 802AA3B4 002A6F94  48 0D DE 6D */	bl __assert
.L_802AA3B8:
/* 802AA3B8 002A6F98  28 1F 00 00 */	cmplwi r31, 0
/* 802AA3BC 002A6F9C  C3 FF 00 24 */	lfs f31, 0x24(r31)
/* 802AA3C0 002A6FA0  40 82 00 14 */	bne .L_802AA3D4
/* 802AA3C4 002A6FA4  38 6D 9D 28 */	addi r3, r13, it_804D53C8@sda21
/* 802AA3C8 002A6FA8  38 80 02 A9 */	li r4, 0x2a9
/* 802AA3CC 002A6FAC  38 AD 9D 30 */	addi r5, r13, it_804D53D0@sda21
/* 802AA3D0 002A6FB0  48 0D DE 51 */	bl __assert
.L_802AA3D4:
/* 802AA3D4 002A6FB4  80 1F 00 14 */	lwz r0, 0x14(r31)
/* 802AA3D8 002A6FB8  54 00 03 9D */	rlwinm. r0, r0, 0, 0xe, 0xe
/* 802AA3DC 002A6FBC  41 82 00 18 */	beq .L_802AA3F4
/* 802AA3E0 002A6FC0  3C 60 80 3F */	lis r3, it_803F6B38@ha
/* 802AA3E4 002A6FC4  38 A3 6B 38 */	addi r5, r3, it_803F6B38@l
/* 802AA3E8 002A6FC8  38 6D 9D 28 */	addi r3, r13, it_804D53C8@sda21
/* 802AA3EC 002A6FCC  38 80 02 AA */	li r4, 0x2aa
/* 802AA3F0 002A6FD0  48 0D DE 31 */	bl __assert
.L_802AA3F4:
/* 802AA3F4 002A6FD4  FC 00 F8 50 */	fneg f0, f31
/* 802AA3F8 002A6FD8  D0 1F 00 24 */	stfs f0, 0x24(r31)
/* 802AA3FC 002A6FDC  80 1F 00 14 */	lwz r0, 0x14(r31)
/* 802AA400 002A6FE0  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 802AA404 002A6FE4  40 82 00 4C */	bne .L_802AA450
/* 802AA408 002A6FE8  28 1F 00 00 */	cmplwi r31, 0
/* 802AA40C 002A6FEC  41 82 00 44 */	beq .L_802AA450
/* 802AA410 002A6FF0  40 82 00 14 */	bne .L_802AA424
/* 802AA414 002A6FF4  38 6D 9D 28 */	addi r3, r13, it_804D53C8@sda21
/* 802AA418 002A6FF8  38 80 02 34 */	li r4, 0x234
/* 802AA41C 002A6FFC  38 AD 9D 30 */	addi r5, r13, it_804D53D0@sda21
/* 802AA420 002A7000  48 0D DE 01 */	bl __assert
.L_802AA424:
/* 802AA424 002A7004  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 802AA428 002A7008  38 60 00 00 */	li r3, 0
/* 802AA42C 002A700C  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 802AA430 002A7010  40 82 00 10 */	bne .L_802AA440
/* 802AA434 002A7014  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 802AA438 002A7018  41 82 00 08 */	beq .L_802AA440
/* 802AA43C 002A701C  38 60 00 01 */	li r3, 1
.L_802AA440:
/* 802AA440 002A7020  2C 03 00 00 */	cmpwi r3, 0
/* 802AA444 002A7024  40 82 00 0C */	bne .L_802AA450
/* 802AA448 002A7028  7F E3 FB 78 */	mr r3, r31
/* 802AA44C 002A702C  48 0C 8E 9D */	bl HSD_JObjSetMtxDirtySub
.L_802AA450:
/* 802AA450 002A7030  7F C3 F3 78 */	mr r3, r30
/* 802AA454 002A7034  4B FC 8C 25 */	bl itColl_BounceOffShield
/* 802AA458 002A7038  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 802AA45C 002A703C  CB E1 00 20 */	lfd f31, 0x20(r1)
/* 802AA460 002A7040  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 802AA464 002A7044  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 802AA468 002A7048  38 21 00 28 */	addi r1, r1, 0x28
/* 802AA46C 002A704C  7C 08 03 A6 */	mtlr r0
/* 802AA470 002A7050  4E 80 00 20 */	blr

.global it_802AA474
it_802AA474:
/* 802AA474 002A7054  7C 08 02 A6 */	mflr r0
/* 802AA478 002A7058  90 01 00 04 */	stw r0, 4(r1)
/* 802AA47C 002A705C  94 21 FF F8 */	stwu r1, -8(r1)
/* 802AA480 002A7060  4B FC 14 15 */	bl it_8026B894
/* 802AA484 002A7064  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802AA488 002A7068  38 21 00 08 */	addi r1, r1, 8
/* 802AA48C 002A706C  7C 08 03 A6 */	mtlr r0
/* 802AA490 002A7070  4E 80 00 20 */	blr


.section .data
    .balign 8
.global it_803F6B28
it_803F6B28:
    .4byte 0
    .4byte it_802AA22C
    .4byte NULL
    .4byte it_802AA264
.global it_803F6B38
it_803F6B38:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"


.section .sdata
    .balign 8
.global it_804D53C8
it_804D53C8:
    .asciz "jobj.h"
    .balign 4
.global it_804D53D0
it_804D53D0:
    .asciz "jobj"


.section .sdata2
    .balign 8
.global it_804DCE58
it_804DCE58:
    .4byte 0x00000000
.global it_804DCE5C
it_804DCE5C:
    .4byte 0x3F800000
