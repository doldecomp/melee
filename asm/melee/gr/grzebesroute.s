.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

.global func_8020B160
func_8020B160:
/* 8020B160 00207D40  4E 80 00 20 */	blr 

.global func_8020B164
func_8020B164:
/* 8020B164 00207D44  7C 08 02 A6 */	mflr r0
/* 8020B168 00207D48  90 01 00 04 */	stw r0, 4(r1)
/* 8020B16C 00207D4C  94 21 FF F8 */	stwu r1, -8(r1)
/* 8020B170 00207D50  4B FB 98 89 */	bl func_801C49F8
/* 8020B174 00207D54  3C 80 80 4A */	lis r4, stage_info@ha
/* 8020B178 00207D58  90 6D B3 C0 */	stw r3, lbl_804D6A60@sda21(r13)
/* 8020B17C 00207D5C  38 64 E6 C8 */	addi r3, r4, stage_info@l
/* 8020B180 00207D60  38 A3 00 8C */	addi r5, r3, 0x8c
/* 8020B184 00207D64  88 03 00 8C */	lbz r0, 0x8c(r3)
/* 8020B188 00207D68  38 60 00 00 */	li r3, 0
/* 8020B18C 00207D6C  50 60 1F 38 */	rlwimi r0, r3, 3, 0x1c, 0x1c
/* 8020B190 00207D70  98 05 00 00 */	stb r0, 0(r5)
/* 8020B194 00207D74  38 80 00 01 */	li r4, 1
/* 8020B198 00207D78  38 60 00 00 */	li r3, 0
/* 8020B19C 00207D7C  88 05 00 00 */	lbz r0, 0(r5)
/* 8020B1A0 00207D80  50 80 17 7A */	rlwimi r0, r4, 2, 0x1d, 0x1d
/* 8020B1A4 00207D84  98 05 00 00 */	stb r0, 0(r5)
/* 8020B1A8 00207D88  48 00 00 B9 */	bl func_8020B260
/* 8020B1AC 00207D8C  38 60 00 01 */	li r3, 1
/* 8020B1B0 00207D90  48 00 00 B1 */	bl func_8020B260
/* 8020B1B4 00207D94  38 60 00 02 */	li r3, 2
/* 8020B1B8 00207D98  48 00 00 A9 */	bl func_8020B260
/* 8020B1BC 00207D9C  4B FB 88 05 */	bl func_801C39C0
/* 8020B1C0 00207DA0  4B FB 89 F5 */	bl func_801C3BB4
/* 8020B1C4 00207DA4  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8020B1C8 00207DA8  38 21 00 08 */	addi r1, r1, 8
/* 8020B1CC 00207DAC  7C 08 03 A6 */	mtlr r0
/* 8020B1D0 00207DB0  4E 80 00 20 */	blr 
.global lbl_8020B1D4
lbl_8020B1D4:
/* 8020B1D4 00207DB4  7C 08 02 A6 */	mflr r0
/* 8020B1D8 00207DB8  90 01 00 04 */	stw r0, 4(r1)
/* 8020B1DC 00207DBC  94 21 FF F8 */	stwu r1, -8(r1)
/* 8020B1E0 00207DC0  48 00 03 69 */	bl func_8020B548
/* 8020B1E4 00207DC4  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8020B1E8 00207DC8  38 21 00 08 */	addi r1, r1, 8
/* 8020B1EC 00207DCC  7C 08 03 A6 */	mtlr r0
/* 8020B1F0 00207DD0  4E 80 00 20 */	blr 
.global lbl_8020B1F4
lbl_8020B1F4:
/* 8020B1F4 00207DD4  7C 08 02 A6 */	mflr r0
/* 8020B1F8 00207DD8  38 60 00 00 */	li r3, 0
/* 8020B1FC 00207DDC  90 01 00 04 */	stw r0, 4(r1)
/* 8020B200 00207DE0  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8020B204 00207DE4  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8020B208 00207DE8  4B FB FB FD */	bl func_801CAE04
/* 8020B20C 00207DEC  80 6D B3 C0 */	lwz r3, lbl_804D6A60@sda21(r13)
/* 8020B210 00207DF0  80 63 00 04 */	lwz r3, 4(r3)
/* 8020B214 00207DF4  2C 03 00 00 */	cmpwi r3, 0
/* 8020B218 00207DF8  41 82 00 0C */	beq lbl_8020B224
/* 8020B21C 00207DFC  48 17 53 65 */	bl HSD_Randi
/* 8020B220 00207E00  48 00 00 08 */	b lbl_8020B228
lbl_8020B224:
/* 8020B224 00207E04  38 60 00 00 */	li r3, 0
lbl_8020B228:
/* 8020B228 00207E08  2C 03 00 00 */	cmpwi r3, 0
/* 8020B22C 00207E0C  40 82 00 18 */	bne lbl_8020B244
/* 8020B230 00207E10  4B FB A7 11 */	bl func_801C5940
/* 8020B234 00207E14  7C 7F 1B 78 */	mr r31, r3
/* 8020B238 00207E18  4B FB A6 09 */	bl func_801C5840
/* 8020B23C 00207E1C  7F E4 FB 78 */	mr r4, r31
/* 8020B240 00207E20  4B FB FC 71 */	bl func_801CAEB0
lbl_8020B244:
/* 8020B244 00207E24  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8020B248 00207E28  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8020B24C 00207E2C  38 21 00 10 */	addi r1, r1, 0x10
/* 8020B250 00207E30  7C 08 03 A6 */	mtlr r0
/* 8020B254 00207E34  4E 80 00 20 */	blr 
.global lbl_8020B258
lbl_8020B258:
/* 8020B258 00207E38  38 60 00 00 */	li r3, 0
/* 8020B25C 00207E3C  4E 80 00 20 */	blr 

.global func_8020B260
func_8020B260:
/* 8020B260 00207E40  7C 08 02 A6 */	mflr r0
/* 8020B264 00207E44  90 01 00 04 */	stw r0, 4(r1)
/* 8020B268 00207E48  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8020B26C 00207E4C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8020B270 00207E50  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8020B274 00207E54  93 A1 00 14 */	stw r29, 0x14(r1)
/* 8020B278 00207E58  93 81 00 10 */	stw r28, 0x10(r1)
/* 8020B27C 00207E5C  3B 83 00 00 */	addi r28, r3, 0
/* 8020B280 00207E60  1C 1C 00 14 */	mulli r0, r28, 0x14
/* 8020B284 00207E64  3C 60 80 3E */	lis r3, lbl_803E5DB0@ha
/* 8020B288 00207E68  3B E3 5D B0 */	addi r31, r3, lbl_803E5DB0@l
/* 8020B28C 00207E6C  38 7C 00 00 */	addi r3, r28, 0
/* 8020B290 00207E70  7F BF 02 14 */	add r29, r31, r0
/* 8020B294 00207E74  4B FB 62 3D */	bl func_801C14D0
/* 8020B298 00207E78  7C 7E 1B 79 */	or. r30, r3, r3
/* 8020B29C 00207E7C  41 82 00 70 */	beq lbl_8020B30C
/* 8020B2A0 00207E80  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 8020B2A4 00207E84  38 00 00 00 */	li r0, 0
/* 8020B2A8 00207E88  3C 60 80 1C */	lis r3, func_801C5DB0@ha
/* 8020B2AC 00207E8C  90 1F 00 08 */	stw r0, 8(r31)
/* 8020B2B0 00207E90  38 83 5D B0 */	addi r4, r3, func_801C5DB0@l
/* 8020B2B4 00207E94  38 7E 00 00 */	addi r3, r30, 0
/* 8020B2B8 00207E98  90 1F 00 0C */	stw r0, 0xc(r31)
/* 8020B2BC 00207E9C  38 A0 00 03 */	li r5, 3
/* 8020B2C0 00207EA0  38 C0 00 00 */	li r6, 0
/* 8020B2C4 00207EA4  48 18 53 D9 */	bl func_8039069C
/* 8020B2C8 00207EA8  80 1D 00 0C */	lwz r0, 0xc(r29)
/* 8020B2CC 00207EAC  28 00 00 00 */	cmplwi r0, 0
/* 8020B2D0 00207EB0  41 82 00 08 */	beq lbl_8020B2D8
/* 8020B2D4 00207EB4  90 1F 00 1C */	stw r0, 0x1c(r31)
lbl_8020B2D8:
/* 8020B2D8 00207EB8  81 9D 00 00 */	lwz r12, 0(r29)
/* 8020B2DC 00207EBC  28 0C 00 00 */	cmplwi r12, 0
/* 8020B2E0 00207EC0  41 82 00 10 */	beq lbl_8020B2F0
/* 8020B2E4 00207EC4  7D 88 03 A6 */	mtlr r12
/* 8020B2E8 00207EC8  38 7E 00 00 */	addi r3, r30, 0
/* 8020B2EC 00207ECC  4E 80 00 21 */	blrl 
lbl_8020B2F0:
/* 8020B2F0 00207ED0  80 9D 00 08 */	lwz r4, 8(r29)
/* 8020B2F4 00207ED4  28 04 00 00 */	cmplwi r4, 0
/* 8020B2F8 00207ED8  41 82 00 2C */	beq lbl_8020B324
/* 8020B2FC 00207EDC  38 7E 00 00 */	addi r3, r30, 0
/* 8020B300 00207EE0  38 A0 00 04 */	li r5, 4
/* 8020B304 00207EE4  48 18 4A 51 */	bl func_8038FD54
/* 8020B308 00207EE8  48 00 00 1C */	b lbl_8020B324
lbl_8020B30C:
/* 8020B30C 00207EEC  38 DC 00 00 */	addi r6, r28, 0
/* 8020B310 00207EF0  4C C6 31 82 */	crclr 6
/* 8020B314 00207EF4  38 7F 00 90 */	addi r3, r31, 0x90
/* 8020B318 00207EF8  38 9F 00 B4 */	addi r4, r31, 0xb4
/* 8020B31C 00207EFC  38 A0 00 C5 */	li r5, 0xc5
/* 8020B320 00207F00  48 13 A3 89 */	bl OSReport
lbl_8020B324:
/* 8020B324 00207F04  7F C3 F3 78 */	mr r3, r30
/* 8020B328 00207F08  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8020B32C 00207F0C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8020B330 00207F10  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8020B334 00207F14  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 8020B338 00207F18  83 81 00 10 */	lwz r28, 0x10(r1)
/* 8020B33C 00207F1C  38 21 00 20 */	addi r1, r1, 0x20
/* 8020B340 00207F20  7C 08 03 A6 */	mtlr r0
/* 8020B344 00207F24  4E 80 00 20 */	blr 
.global lbl_8020B348
lbl_8020B348:
/* 8020B348 00207F28  7C 08 02 A6 */	mflr r0
/* 8020B34C 00207F2C  38 A0 00 00 */	li r5, 0
/* 8020B350 00207F30  90 01 00 04 */	stw r0, 4(r1)
/* 8020B354 00207F34  94 21 FF F8 */	stwu r1, -8(r1)
/* 8020B358 00207F38  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 8020B35C 00207F3C  80 84 00 14 */	lwz r4, 0x14(r4)
/* 8020B360 00207F40  4B FB CD D9 */	bl func_801C8138
/* 8020B364 00207F44  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8020B368 00207F48  38 21 00 08 */	addi r1, r1, 8
/* 8020B36C 00207F4C  7C 08 03 A6 */	mtlr r0
/* 8020B370 00207F50  4E 80 00 20 */	blr 
.global lbl_8020B374
lbl_8020B374:
/* 8020B374 00207F54  38 60 00 00 */	li r3, 0
/* 8020B378 00207F58  4E 80 00 20 */	blr 
.global lbl_8020B37C
lbl_8020B37C:
/* 8020B37C 00207F5C  4E 80 00 20 */	blr 
.global lbl_8020B380
lbl_8020B380:
/* 8020B380 00207F60  4E 80 00 20 */	blr 
.global lbl_8020B384
lbl_8020B384:
/* 8020B384 00207F64  7C 08 02 A6 */	mflr r0
/* 8020B388 00207F68  38 A0 00 00 */	li r5, 0
/* 8020B38C 00207F6C  90 01 00 04 */	stw r0, 4(r1)
/* 8020B390 00207F70  94 21 FF F8 */	stwu r1, -8(r1)
/* 8020B394 00207F74  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 8020B398 00207F78  80 84 00 14 */	lwz r4, 0x14(r4)
/* 8020B39C 00207F7C  4B FB CD 9D */	bl func_801C8138
/* 8020B3A0 00207F80  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8020B3A4 00207F84  38 21 00 08 */	addi r1, r1, 8
/* 8020B3A8 00207F88  7C 08 03 A6 */	mtlr r0
/* 8020B3AC 00207F8C  4E 80 00 20 */	blr 
.global lbl_8020B3B0
lbl_8020B3B0:
/* 8020B3B0 00207F90  38 60 00 00 */	li r3, 0
/* 8020B3B4 00207F94  4E 80 00 20 */	blr 
.global lbl_8020B3B8
lbl_8020B3B8:
/* 8020B3B8 00207F98  4E 80 00 20 */	blr 
.global lbl_8020B3BC
lbl_8020B3BC:
/* 8020B3BC 00207F9C  4E 80 00 20 */	blr 
.global lbl_8020B3C0
lbl_8020B3C0:
/* 8020B3C0 00207FA0  7C 08 02 A6 */	mflr r0
/* 8020B3C4 00207FA4  38 A0 00 00 */	li r5, 0
/* 8020B3C8 00207FA8  90 01 00 04 */	stw r0, 4(r1)
/* 8020B3CC 00207FAC  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8020B3D0 00207FB0  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8020B3D4 00207FB4  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8020B3D8 00207FB8  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 8020B3DC 00207FBC  4B FB CD 5D */	bl func_801C8138
/* 8020B3E0 00207FC0  38 00 00 00 */	li r0, 0
/* 8020B3E4 00207FC4  90 1F 00 08 */	stw r0, 8(r31)
/* 8020B3E8 00207FC8  3C 60 80 21 */	lis r3, lbl_8020B4D8@ha
/* 8020B3EC 00207FCC  38 A3 B4 D8 */	addi r5, r3, lbl_8020B4D8@l
/* 8020B3F0 00207FD0  90 1F 00 0C */	stw r0, 0xc(r31)
/* 8020B3F4 00207FD4  38 9F 00 00 */	addi r4, r31, 0
/* 8020B3F8 00207FD8  38 60 00 01 */	li r3, 1
/* 8020B3FC 00207FDC  4B E4 CC CD */	bl func_800580C8
/* 8020B400 00207FE0  80 6D B3 C0 */	lwz r3, lbl_804D6A60@sda21(r13)
/* 8020B404 00207FE4  80 03 00 00 */	lwz r0, 0(r3)
/* 8020B408 00207FE8  7C 00 07 34 */	extsh r0, r0
/* 8020B40C 00207FEC  B0 1F 00 C4 */	sth r0, 0xc4(r31)
/* 8020B410 00207FF0  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8020B414 00207FF4  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8020B418 00207FF8  38 21 00 18 */	addi r1, r1, 0x18
/* 8020B41C 00207FFC  7C 08 03 A6 */	mtlr r0
/* 8020B420 00208000  4E 80 00 20 */	blr 
.global lbl_8020B424
lbl_8020B424:
/* 8020B424 00208004  38 60 00 00 */	li r3, 0
/* 8020B428 00208008  4E 80 00 20 */	blr 
.global lbl_8020B42C
lbl_8020B42C:
/* 8020B42C 0020800C  7C 08 02 A6 */	mflr r0
/* 8020B430 00208010  3C 80 80 3C */	lis r4, lbl_803B83A0@ha
/* 8020B434 00208014  90 01 00 04 */	stw r0, 4(r1)
/* 8020B438 00208018  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8020B43C 0020801C  93 E1 00 24 */	stw r31, 0x24(r1)
/* 8020B440 00208020  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8020B444 00208024  84 64 83 A0 */	lwzu r3, lbl_803B83A0@l(r4)
/* 8020B448 00208028  80 04 00 04 */	lwz r0, 0x4(r4)
/* 8020B44C 0020802C  90 61 00 10 */	stw r3, 0x10(r1)
/* 8020B450 00208030  90 01 00 14 */	stw r0, 0x14(r1)
/* 8020B454 00208034  80 04 00 08 */	lwz r0, 8(r4)
/* 8020B458 00208038  90 01 00 18 */	stw r0, 0x18(r1)
/* 8020B45C 0020803C  4B FB A3 49 */	bl func_801C57A4
/* 8020B460 00208040  28 03 00 00 */	cmplwi r3, 0
/* 8020B464 00208044  41 82 00 34 */	beq lbl_8020B498
/* 8020B468 00208048  38 81 00 10 */	addi r4, r1, 0x10
/* 8020B46C 0020804C  4B E7 B1 D9 */	bl func_80086644
/* 8020B470 00208050  C0 21 00 14 */	lfs f1, 0x14(r1)
/* 8020B474 00208054  C0 02 BF 38 */	lfs f0, lbl_804DB918@sda21(r2)
/* 8020B478 00208058  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8020B47C 0020805C  40 80 00 08 */	bge lbl_8020B484
/* 8020B480 00208060  D0 01 00 14 */	stfs f0, 0x14(r1)
lbl_8020B484:
/* 8020B484 00208064  C0 02 BF 3C */	lfs f0, lbl_804DB91C@sda21(r2)
/* 8020B488 00208068  D0 01 00 10 */	stfs f0, 0x10(r1)
/* 8020B48C 0020806C  C0 21 00 10 */	lfs f1, 0x10(r1)
/* 8020B490 00208070  C0 41 00 14 */	lfs f2, 0x14(r1)
/* 8020B494 00208074  4B FB 84 29 */	bl func_801C38BC
lbl_8020B498:
/* 8020B498 00208078  A8 7F 00 C4 */	lha r3, 0xc4(r31)
/* 8020B49C 0020807C  2C 03 00 00 */	cmpwi r3, 0
/* 8020B4A0 00208080  40 81 00 10 */	ble lbl_8020B4B0
/* 8020B4A4 00208084  38 03 FF FF */	addi r0, r3, -1
/* 8020B4A8 00208088  B0 1F 00 C4 */	sth r0, 0xc4(r31)
/* 8020B4AC 0020808C  48 00 00 10 */	b lbl_8020B4BC
lbl_8020B4B0:
/* 8020B4B0 00208090  38 60 00 01 */	li r3, 1
/* 8020B4B4 00208094  38 80 00 00 */	li r4, 0
/* 8020B4B8 00208098  4B E2 59 8D */	bl func_80030E44
lbl_8020B4BC:
/* 8020B4BC 0020809C  4B E0 61 39 */	bl func_800115F4
/* 8020B4C0 002080A0  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8020B4C4 002080A4  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 8020B4C8 002080A8  38 21 00 28 */	addi r1, r1, 0x28
/* 8020B4CC 002080AC  7C 08 03 A6 */	mtlr r0
/* 8020B4D0 002080B0  4E 80 00 20 */	blr 
.global lbl_8020B4D4
lbl_8020B4D4:
/* 8020B4D4 002080B4  4E 80 00 20 */	blr 
lbl_8020B4D8:
/* 8020B4D8 002080B8  7C 08 02 A6 */	mflr r0
/* 8020B4DC 002080BC  90 01 00 04 */	stw r0, 4(r1)
/* 8020B4E0 002080C0  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 8020B4E4 002080C4  93 E1 00 34 */	stw r31, 0x34(r1)
/* 8020B4E8 002080C8  3B E7 00 00 */	addi r31, r7, 0
/* 8020B4EC 002080CC  93 C1 00 30 */	stw r30, 0x30(r1)
/* 8020B4F0 002080D0  7C BE 2B 78 */	mr r30, r5
/* 8020B4F4 002080D4  88 05 00 34 */	lbz r0, 0x34(r5)
/* 8020B4F8 002080D8  54 00 EF 3E */	rlwinm r0, r0, 0x1d, 0x1c, 0x1f
/* 8020B4FC 002080DC  2C 00 00 01 */	cmpwi r0, 1
/* 8020B500 002080E0  40 82 00 30 */	bne lbl_8020B530
/* 8020B504 002080E4  4B FB A2 A1 */	bl func_801C57A4
/* 8020B508 002080E8  80 1E 00 00 */	lwz r0, 0(r30)
/* 8020B50C 002080EC  7C 03 00 40 */	cmplw r3, r0
/* 8020B510 002080F0  40 82 00 20 */	bne lbl_8020B530
/* 8020B514 002080F4  2C 1F 00 01 */	cmpwi r31, 1
/* 8020B518 002080F8  40 82 00 18 */	bne lbl_8020B530
/* 8020B51C 002080FC  3C 60 80 4A */	lis r3, stage_info@ha
/* 8020B520 00208100  38 63 E6 C8 */	addi r3, r3, stage_info@l
/* 8020B524 00208104  80 03 00 84 */	lwz r0, 0x84(r3)
/* 8020B528 00208108  60 00 00 10 */	ori r0, r0, 0x10
/* 8020B52C 0020810C  90 03 00 84 */	stw r0, 0x84(r3)
lbl_8020B530:
/* 8020B530 00208110  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 8020B534 00208114  83 E1 00 34 */	lwz r31, 0x34(r1)
/* 8020B538 00208118  83 C1 00 30 */	lwz r30, 0x30(r1)
/* 8020B53C 0020811C  38 21 00 38 */	addi r1, r1, 0x38
/* 8020B540 00208120  7C 08 03 A6 */	mtlr r0
/* 8020B544 00208124  4E 80 00 20 */	blr 

.global func_8020B548
func_8020B548:
/* 8020B548 00208128  7C 08 02 A6 */	mflr r0
/* 8020B54C 0020812C  3C 80 80 3C */	lis r4, lbl_803B83A0@ha
/* 8020B550 00208130  90 01 00 04 */	stw r0, 4(r1)
/* 8020B554 00208134  94 21 FF 48 */	stwu r1, -0xb8(r1)
/* 8020B558 00208138  DB E1 00 B0 */	stfd f31, 0xb0(r1)
/* 8020B55C 0020813C  DB C1 00 A8 */	stfd f30, 0xa8(r1)
/* 8020B560 00208140  DB A1 00 A0 */	stfd f29, 0xa0(r1)
/* 8020B564 00208144  DB 81 00 98 */	stfd f28, 0x98(r1)
/* 8020B568 00208148  DB 61 00 90 */	stfd f27, 0x90(r1)
/* 8020B56C 0020814C  BF 21 00 74 */	stmw r25, 0x74(r1)
/* 8020B570 00208150  3B C4 83 A0 */	addi r30, r4, lbl_803B83A0@l
/* 8020B574 00208154  80 6D C1 84 */	lwz r3, lbl_804D7824@sda21(r13)
/* 8020B578 00208158  83 23 00 10 */	lwz r25, 0x10(r3)
/* 8020B57C 0020815C  28 19 00 00 */	cmplwi r25, 0
/* 8020B580 00208160  40 82 00 18 */	bne lbl_8020B598
/* 8020B584 00208164  3C 60 80 3E */	lis r3, lbl_803E5E64@ha
/* 8020B588 00208168  38 63 5E 64 */	addi r3, r3, lbl_803E5E64@l
/* 8020B58C 0020816C  38 80 01 69 */	li r4, 0x169
/* 8020B590 00208170  38 AD 91 A0 */	addi r5, r13, lbl_804D4840@sda21
/* 8020B594 00208174  48 17 CC 8D */	bl __assert
lbl_8020B598:
/* 8020B598 00208178  83 39 00 28 */	lwz r25, 0x28(r25)
/* 8020B59C 0020817C  4B FB 4E FD */	bl func_801C0498
/* 8020B5A0 00208180  FF E0 08 90 */	fmr f31, f1
/* 8020B5A4 00208184  28 19 00 00 */	cmplwi r25, 0
/* 8020B5A8 00208188  40 82 00 0C */	bne lbl_8020B5B4
/* 8020B5AC 0020818C  38 00 00 00 */	li r0, 0
/* 8020B5B0 00208190  48 00 00 08 */	b lbl_8020B5B8
lbl_8020B5B4:
/* 8020B5B4 00208194  80 19 00 0C */	lwz r0, 0xc(r25)
lbl_8020B5B8:
/* 8020B5B8 00208198  C0 42 BF 4C */	lfs f2, lbl_804DB92C@sda21(r2)
/* 8020B5BC 0020819C  3C 60 80 3E */	lis r3, lbl_803E5E64@ha
/* 8020B5C0 002081A0  C0 22 BF 50 */	lfs f1, lbl_804DB930@sda21(r2)
/* 8020B5C4 002081A4  7C 1A 03 78 */	mr r26, r0
/* 8020B5C8 002081A8  C0 02 BF 54 */	lfs f0, lbl_804DB934@sda21(r2)
/* 8020B5CC 002081AC  EF C2 07 F2 */	fmuls f30, f2, f31
/* 8020B5D0 002081B0  C3 62 BF 60 */	lfs f27, lbl_804DB940@sda21(r2)
/* 8020B5D4 002081B4  EF A1 07 F2 */	fmuls f29, f1, f31
/* 8020B5D8 002081B8  3B 61 00 14 */	addi r27, r1, 0x14
/* 8020B5DC 002081BC  EF 80 07 F2 */	fmuls f28, f0, f31
/* 8020B5E0 002081C0  3B 81 00 18 */	addi r28, r1, 0x18
/* 8020B5E4 002081C4  3B E3 5E 64 */	addi r31, r3, lbl_803E5E64@l
/* 8020B5E8 002081C8  3B A1 00 1C */	addi r29, r1, 0x1c
/* 8020B5EC 002081CC  3B 20 00 00 */	li r25, 0
/* 8020B5F0 002081D0  48 00 02 2C */	b lbl_8020B81C
lbl_8020B5F4:
/* 8020B5F4 002081D4  38 7A 00 00 */	addi r3, r26, 0
/* 8020B5F8 002081D8  38 81 00 5C */	addi r4, r1, 0x5c
/* 8020B5FC 002081DC  48 15 B7 75 */	bl func_80366D70
/* 8020B600 002081E0  2C 03 00 00 */	cmpwi r3, 0
/* 8020B604 002081E4  40 82 00 14 */	bne lbl_8020B618
/* 8020B608 002081E8  38 7F 00 00 */	addi r3, r31, 0
/* 8020B60C 002081EC  38 80 01 74 */	li r4, 0x174
/* 8020B610 002081F0  38 AD 91 A8 */	addi r5, r13, lbl_804D4848@sda21
/* 8020B614 002081F4  48 17 CC 0D */	bl __assert
lbl_8020B618:
/* 8020B618 002081F8  A0 1A 00 08 */	lhz r0, 8(r26)
/* 8020B61C 002081FC  54 00 07 BE */	clrlwi r0, r0, 0x1e
/* 8020B620 00208200  28 00 00 03 */	cmplwi r0, 3
/* 8020B624 00208204  40 82 00 D0 */	bne lbl_8020B6F4
/* 8020B628 00208208  80 DE 00 0C */	lwz r6, 0xc(r30)
/* 8020B62C 0020820C  7F 43 D3 78 */	mr r3, r26
/* 8020B630 00208210  80 BE 00 10 */	lwz r5, 0x10(r30)
/* 8020B634 00208214  7F A4 EB 78 */	mr r4, r29
/* 8020B638 00208218  80 02 BF 40 */	lwz r0, lbl_804DB920@sda21(r2)
/* 8020B63C 0020821C  90 C1 00 4C */	stw r6, 0x4c(r1)
/* 8020B640 00208220  90 A1 00 50 */	stw r5, 0x50(r1)
/* 8020B644 00208224  80 BE 00 14 */	lwz r5, 0x14(r30)
/* 8020B648 00208228  90 A1 00 54 */	stw r5, 0x54(r1)
/* 8020B64C 0020822C  80 DE 00 18 */	lwz r6, 0x18(r30)
/* 8020B650 00208230  80 BE 00 1C */	lwz r5, 0x1c(r30)
/* 8020B654 00208234  90 C1 00 40 */	stw r6, 0x40(r1)
/* 8020B658 00208238  90 A1 00 44 */	stw r5, 0x44(r1)
/* 8020B65C 0020823C  80 BE 00 20 */	lwz r5, 0x20(r30)
/* 8020B660 00208240  90 A1 00 48 */	stw r5, 0x48(r1)
/* 8020B664 00208244  90 01 00 1C */	stw r0, 0x1c(r1)
/* 8020B668 00208248  48 15 B6 3D */	bl func_80366CA4
/* 8020B66C 0020824C  C0 01 00 4C */	lfs f0, 0x4c(r1)
/* 8020B670 00208250  38 7A 00 00 */	addi r3, r26, 0
/* 8020B674 00208254  38 81 00 4C */	addi r4, r1, 0x4c
/* 8020B678 00208258  EC 00 07 F2 */	fmuls f0, f0, f31
/* 8020B67C 0020825C  D0 01 00 4C */	stfs f0, 0x4c(r1)
/* 8020B680 00208260  C0 01 00 50 */	lfs f0, 0x50(r1)
/* 8020B684 00208264  EC 00 07 F2 */	fmuls f0, f0, f31
/* 8020B688 00208268  D0 01 00 50 */	stfs f0, 0x50(r1)
/* 8020B68C 0020826C  C0 01 00 54 */	lfs f0, 0x54(r1)
/* 8020B690 00208270  EC 00 07 F2 */	fmuls f0, f0, f31
/* 8020B694 00208274  D0 01 00 54 */	stfs f0, 0x54(r1)
/* 8020B698 00208278  48 15 B6 51 */	bl func_80366CE8
/* 8020B69C 0020827C  C0 01 00 40 */	lfs f0, 0x40(r1)
/* 8020B6A0 00208280  38 7A 00 00 */	addi r3, r26, 0
/* 8020B6A4 00208284  38 81 00 40 */	addi r4, r1, 0x40
/* 8020B6A8 00208288  EC 00 07 F2 */	fmuls f0, f0, f31
/* 8020B6AC 0020828C  D0 01 00 40 */	stfs f0, 0x40(r1)
/* 8020B6B0 00208290  C0 01 00 44 */	lfs f0, 0x44(r1)
/* 8020B6B4 00208294  EC 00 07 F2 */	fmuls f0, f0, f31
/* 8020B6B8 00208298  D0 01 00 44 */	stfs f0, 0x44(r1)
/* 8020B6BC 0020829C  C0 01 00 48 */	lfs f0, 0x48(r1)
/* 8020B6C0 002082A0  EC 00 07 F2 */	fmuls f0, f0, f31
/* 8020B6C4 002082A4  D0 01 00 48 */	stfs f0, 0x48(r1)
/* 8020B6C8 002082A8  48 15 B6 E9 */	bl func_80366DB0
/* 8020B6CC 002082AC  C0 22 BF 58 */	lfs f1, lbl_804DB938@sda21(r2)
/* 8020B6D0 002082B0  38 7A 00 00 */	addi r3, r26, 0
/* 8020B6D4 002082B4  38 80 00 03 */	li r4, 3
/* 8020B6D8 002082B8  48 15 B5 E5 */	bl func_80366CBC
/* 8020B6DC 002082BC  FC 20 F0 90 */	fmr f1, f30
/* 8020B6E0 002082C0  C0 42 BF 5C */	lfs f2, lbl_804DB93C@sda21(r2)
/* 8020B6E4 002082C4  38 7A 00 00 */	addi r3, r26, 0
/* 8020B6E8 002082C8  38 80 00 03 */	li r4, 3
/* 8020B6EC 002082CC  48 15 B5 E5 */	bl func_80366CD0
/* 8020B6F0 002082D0  48 00 01 10 */	b lbl_8020B800
lbl_8020B6F4:
/* 8020B6F4 002082D4  28 00 00 02 */	cmplwi r0, 2
/* 8020B6F8 002082D8  40 82 00 84 */	bne lbl_8020B77C
/* 8020B6FC 002082DC  C0 01 00 60 */	lfs f0, 0x60(r1)
/* 8020B700 002082E0  FC 00 D8 40 */	fcmpo cr0, f0, f27
/* 8020B704 002082E4  40 81 00 78 */	ble lbl_8020B77C
/* 8020B708 002082E8  80 DE 00 24 */	lwz r6, 0x24(r30)
/* 8020B70C 002082EC  7F 43 D3 78 */	mr r3, r26
/* 8020B710 002082F0  80 BE 00 28 */	lwz r5, 0x28(r30)
/* 8020B714 002082F4  7F 84 E3 78 */	mr r4, r28
/* 8020B718 002082F8  80 02 BF 44 */	lwz r0, lbl_804DB924@sda21(r2)
/* 8020B71C 002082FC  90 C1 00 30 */	stw r6, 0x30(r1)
/* 8020B720 00208300  90 A1 00 34 */	stw r5, 0x34(r1)
/* 8020B724 00208304  80 BE 00 2C */	lwz r5, 0x2c(r30)
/* 8020B728 00208308  90 A1 00 38 */	stw r5, 0x38(r1)
/* 8020B72C 0020830C  90 01 00 18 */	stw r0, 0x18(r1)
/* 8020B730 00208310  48 15 B5 75 */	bl func_80366CA4
/* 8020B734 00208314  C0 01 00 30 */	lfs f0, 0x30(r1)
/* 8020B738 00208318  38 7A 00 00 */	addi r3, r26, 0
/* 8020B73C 0020831C  38 81 00 30 */	addi r4, r1, 0x30
/* 8020B740 00208320  EC 00 07 F2 */	fmuls f0, f0, f31
/* 8020B744 00208324  D0 01 00 30 */	stfs f0, 0x30(r1)
/* 8020B748 00208328  C0 01 00 34 */	lfs f0, 0x34(r1)
/* 8020B74C 0020832C  EC 00 07 F2 */	fmuls f0, f0, f31
/* 8020B750 00208330  D0 01 00 34 */	stfs f0, 0x34(r1)
/* 8020B754 00208334  C0 01 00 38 */	lfs f0, 0x38(r1)
/* 8020B758 00208338  EC 00 07 F2 */	fmuls f0, f0, f31
/* 8020B75C 0020833C  D0 01 00 38 */	stfs f0, 0x38(r1)
/* 8020B760 00208340  48 15 B5 89 */	bl func_80366CE8
/* 8020B764 00208344  FC 20 E8 90 */	fmr f1, f29
/* 8020B768 00208348  C0 42 BF 64 */	lfs f2, lbl_804DB944@sda21(r2)
/* 8020B76C 0020834C  38 7A 00 00 */	addi r3, r26, 0
/* 8020B770 00208350  38 80 00 03 */	li r4, 3
/* 8020B774 00208354  48 15 B5 5D */	bl func_80366CD0
/* 8020B778 00208358  48 00 00 88 */	b lbl_8020B800
lbl_8020B77C:
/* 8020B77C 0020835C  28 00 00 02 */	cmplwi r0, 2
/* 8020B780 00208360  40 82 00 80 */	bne lbl_8020B800
/* 8020B784 00208364  C0 01 00 60 */	lfs f0, 0x60(r1)
/* 8020B788 00208368  FC 00 D8 40 */	fcmpo cr0, f0, f27
/* 8020B78C 0020836C  40 80 00 74 */	bge lbl_8020B800
/* 8020B790 00208370  80 DE 00 30 */	lwz r6, 0x30(r30)
/* 8020B794 00208374  7F 43 D3 78 */	mr r3, r26
/* 8020B798 00208378  80 BE 00 34 */	lwz r5, 0x34(r30)
/* 8020B79C 0020837C  7F 64 DB 78 */	mr r4, r27
/* 8020B7A0 00208380  80 02 BF 48 */	lwz r0, lbl_804DB928@sda21(r2)
/* 8020B7A4 00208384  90 C1 00 20 */	stw r6, 0x20(r1)
/* 8020B7A8 00208388  90 A1 00 24 */	stw r5, 0x24(r1)
/* 8020B7AC 0020838C  80 BE 00 38 */	lwz r5, 0x38(r30)
/* 8020B7B0 00208390  90 A1 00 28 */	stw r5, 0x28(r1)
/* 8020B7B4 00208394  90 01 00 14 */	stw r0, 0x14(r1)
/* 8020B7B8 00208398  48 15 B4 ED */	bl func_80366CA4
/* 8020B7BC 0020839C  C0 01 00 20 */	lfs f0, 0x20(r1)
/* 8020B7C0 002083A0  38 7A 00 00 */	addi r3, r26, 0
/* 8020B7C4 002083A4  38 81 00 20 */	addi r4, r1, 0x20
/* 8020B7C8 002083A8  EC 00 07 F2 */	fmuls f0, f0, f31
/* 8020B7CC 002083AC  D0 01 00 20 */	stfs f0, 0x20(r1)
/* 8020B7D0 002083B0  C0 01 00 24 */	lfs f0, 0x24(r1)
/* 8020B7D4 002083B4  EC 00 07 F2 */	fmuls f0, f0, f31
/* 8020B7D8 002083B8  D0 01 00 24 */	stfs f0, 0x24(r1)
/* 8020B7DC 002083BC  C0 01 00 28 */	lfs f0, 0x28(r1)
/* 8020B7E0 002083C0  EC 00 07 F2 */	fmuls f0, f0, f31
/* 8020B7E4 002083C4  D0 01 00 28 */	stfs f0, 0x28(r1)
/* 8020B7E8 002083C8  48 15 B5 01 */	bl func_80366CE8
/* 8020B7EC 002083CC  FC 20 E0 90 */	fmr f1, f28
/* 8020B7F0 002083D0  C0 42 BF 64 */	lfs f2, lbl_804DB944@sda21(r2)
/* 8020B7F4 002083D4  38 7A 00 00 */	addi r3, r26, 0
/* 8020B7F8 002083D8  38 80 00 03 */	li r4, 3
/* 8020B7FC 002083DC  48 15 B4 D5 */	bl func_80366CD0
lbl_8020B800:
/* 8020B800 002083E0  28 1A 00 00 */	cmplwi r26, 0
/* 8020B804 002083E4  3B 39 00 01 */	addi r25, r25, 1
/* 8020B808 002083E8  40 82 00 0C */	bne lbl_8020B814
/* 8020B80C 002083EC  38 00 00 00 */	li r0, 0
/* 8020B810 002083F0  48 00 00 08 */	b lbl_8020B818
lbl_8020B814:
/* 8020B814 002083F4  80 1A 00 0C */	lwz r0, 0xc(r26)
lbl_8020B818:
/* 8020B818 002083F8  7C 1A 03 78 */	mr r26, r0
lbl_8020B81C:
/* 8020B81C 002083FC  2C 19 00 03 */	cmpwi r25, 3
/* 8020B820 00208400  40 80 00 0C */	bge lbl_8020B82C
/* 8020B824 00208404  28 1A 00 00 */	cmplwi r26, 0
/* 8020B828 00208408  40 82 FD CC */	bne lbl_8020B5F4
lbl_8020B82C:
/* 8020B82C 0020840C  BB 21 00 74 */	lmw r25, 0x74(r1)
/* 8020B830 00208410  80 01 00 BC */	lwz r0, 0xbc(r1)
/* 8020B834 00208414  CB E1 00 B0 */	lfd f31, 0xb0(r1)
/* 8020B838 00208418  CB C1 00 A8 */	lfd f30, 0xa8(r1)
/* 8020B83C 0020841C  CB A1 00 A0 */	lfd f29, 0xa0(r1)
/* 8020B840 00208420  CB 81 00 98 */	lfd f28, 0x98(r1)
/* 8020B844 00208424  CB 61 00 90 */	lfd f27, 0x90(r1)
/* 8020B848 00208428  38 21 00 B8 */	addi r1, r1, 0xb8
/* 8020B84C 0020842C  7C 08 03 A6 */	mtlr r0
/* 8020B850 00208430  4E 80 00 20 */	blr 
.global lbl_8020B854
lbl_8020B854:
/* 8020B854 00208434  38 60 00 00 */	li r3, 0
/* 8020B858 00208438  4E 80 00 20 */	blr 
.global lbl_8020B85C
lbl_8020B85C:
/* 8020B85C 0020843C  38 60 00 01 */	li r3, 1
/* 8020B860 00208440  4E 80 00 20 */	blr


.section .rodata

.global lbl_803B83A0
lbl_803B83A0:
    .4byte 0x00000000
    .4byte 0x00000000
    .4byte 0x00000000
    .4byte 0x00000000
    .4byte 0xC1F00000
    .4byte 0x42480000
    .4byte 0x00000000
    .4byte 0x442A0000
    .4byte 0xC1A00000
    .4byte 0xC0A00000
    .4byte 0x44750000
    .4byte 0x40A00000
    .4byte 0x00000000
    .4byte 0x43570000
    .4byte 0xC2480000
    .4byte 0x00000000


.section .data

.global lbl_803E5DB0
lbl_803E5DB0:
	.4byte lbl_8020B348
	.4byte lbl_8020B374
	.4byte lbl_8020B37C
	.4byte lbl_8020B380
    .4byte NULL
	.4byte lbl_8020B3C0
	.4byte lbl_8020B424
	.4byte lbl_8020B42C
	.4byte lbl_8020B4D4
    .4byte 0xC0000000
	.4byte lbl_8020B384
	.4byte lbl_8020B3B0
	.4byte lbl_8020B3B8
	.4byte lbl_8020B3BC
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
.global lbl_803E5E00
lbl_803E5E00:
    .4byte 0x2F47724E
    .4byte 0x5A722E64
    .4byte 0x61740000
.global lbl_803E5E0C
lbl_803E5E0C:
    .4byte 0x00000021
    .4byte lbl_803E5DB0
    .4byte lbl_803E5E00
	.4byte func_8020B164
	.4byte func_8020B160
	.4byte lbl_8020B1D4
	.4byte lbl_8020B1F4
	.4byte lbl_8020B258
	.4byte lbl_8020B854
	.4byte lbl_8020B85C
    .4byte 0x00000001
    .4byte NULL
    .4byte NULL
    .4byte 0x25733A25
    .4byte 0x643A2063
    .4byte 0x6F756C64
    .4byte 0x6E207420
    .4byte 0x67657420
    .4byte 0x676F626A
    .4byte 0x2869643D
    .4byte 0x2564290A
    .4byte NULL
.global lbl_803E5E64
lbl_803E5E64:
    .asciz "grzebesroute.c"
    .balign 4
    .4byte NULL
