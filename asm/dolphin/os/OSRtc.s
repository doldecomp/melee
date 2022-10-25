.include "macros.inc"

.section .text  # 0x80348A90 - 0x803B7240 

.global __OSSyncSram
__OSSyncSram:
/* 80349144 00345D24  3C 60 80 4A */	lis r3, lbl_804A7D60@ha
/* 80349148 00345D28  38 63 7D 60 */	addi r3, r3, lbl_804A7D60@l
/* 8034914C 00345D2C  80 63 00 4C */	lwz r3, 0x4c(r3)
/* 80349150 00345D30  4E 80 00 20 */	blr 

.global OSGetSoundMode
OSGetSoundMode:
/* 80349154 00345D34  7C 08 02 A6 */	mflr r0
/* 80349158 00345D38  3C 60 80 4A */	lis r3, lbl_804A7D60@ha
/* 8034915C 00345D3C  90 01 00 04 */	stw r0, 4(r1)
/* 80349160 00345D40  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80349164 00345D44  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80349168 00345D48  3B E3 7D 60 */	addi r31, r3, lbl_804A7D60@l
/* 8034916C 00345D4C  4B FF E1 F9 */	bl OSDisableInterrupts
/* 80349170 00345D50  80 1F 00 48 */	lwz r0, 0x48(r31)
/* 80349174 00345D54  38 9F 00 48 */	addi r4, r31, 0x48
/* 80349178 00345D58  2C 00 00 00 */	cmpwi r0, 0
/* 8034917C 00345D5C  41 82 00 10 */	beq lbl_8034918C
/* 80349180 00345D60  4B FF E2 0D */	bl OSRestoreInterrupts
/* 80349184 00345D64  3B E0 00 00 */	li r31, 0
/* 80349188 00345D68  48 00 00 10 */	b lbl_80349198
lbl_8034918C:
/* 8034918C 00345D6C  90 7F 00 44 */	stw r3, 0x44(r31)
/* 80349190 00345D70  38 00 00 01 */	li r0, 1
/* 80349194 00345D74  90 04 00 00 */	stw r0, 0(r4)
lbl_80349198:
/* 80349198 00345D78  88 1F 00 13 */	lbz r0, 0x13(r31)
/* 8034919C 00345D7C  54 00 07 7B */	rlwinm. r0, r0, 0, 0x1d, 0x1d
/* 803491A0 00345D80  41 82 00 0C */	beq lbl_803491AC
/* 803491A4 00345D84  3B E0 00 01 */	li r31, 1
/* 803491A8 00345D88  48 00 00 08 */	b lbl_803491B0
lbl_803491AC:
/* 803491AC 00345D8C  3B E0 00 00 */	li r31, 0
lbl_803491B0:
/* 803491B0 00345D90  38 60 00 00 */	li r3, 0
/* 803491B4 00345D94  38 80 00 00 */	li r4, 0
/* 803491B8 00345D98  4B FF FC 3D */	bl UnlockSram
/* 803491BC 00345D9C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 803491C0 00345DA0  7F E3 FB 78 */	mr r3, r31
/* 803491C4 00345DA4  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 803491C8 00345DA8  38 21 00 20 */	addi r1, r1, 0x20
/* 803491CC 00345DAC  7C 08 03 A6 */	mtlr r0
/* 803491D0 00345DB0  4E 80 00 20 */	blr 

.global OSSetSoundMode
OSSetSoundMode:
/* 803491D4 00345DB4  7C 08 02 A6 */	mflr r0
/* 803491D8 00345DB8  3C 80 80 4A */	lis r4, lbl_804A7D60@ha
/* 803491DC 00345DBC  90 01 00 04 */	stw r0, 4(r1)
/* 803491E0 00345DC0  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 803491E4 00345DC4  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 803491E8 00345DC8  3B E4 7D 60 */	addi r31, r4, lbl_804A7D60@l
/* 803491EC 00345DCC  93 C1 00 18 */	stw r30, 0x18(r1)
/* 803491F0 00345DD0  54 7E 17 7A */	rlwinm r30, r3, 2, 0x1d, 0x1d
/* 803491F4 00345DD4  4B FF E1 71 */	bl OSDisableInterrupts
/* 803491F8 00345DD8  80 1F 00 48 */	lwz r0, 0x48(r31)
/* 803491FC 00345DDC  38 9F 00 48 */	addi r4, r31, 0x48
/* 80349200 00345DE0  2C 00 00 00 */	cmpwi r0, 0
/* 80349204 00345DE4  41 82 00 10 */	beq lbl_80349214
/* 80349208 00345DE8  4B FF E1 85 */	bl OSRestoreInterrupts
/* 8034920C 00345DEC  3B E0 00 00 */	li r31, 0
/* 80349210 00345DF0  48 00 00 10 */	b lbl_80349220
lbl_80349214:
/* 80349214 00345DF4  90 7F 00 44 */	stw r3, 0x44(r31)
/* 80349218 00345DF8  38 00 00 01 */	li r0, 1
/* 8034921C 00345DFC  90 04 00 00 */	stw r0, 0(r4)
lbl_80349220:
/* 80349220 00345E00  88 7F 00 13 */	lbz r3, 0x13(r31)
/* 80349224 00345E04  54 60 07 7A */	rlwinm r0, r3, 0, 0x1d, 0x1d
/* 80349228 00345E08  7C 1E 00 40 */	cmplw r30, r0
/* 8034922C 00345E0C  40 82 00 14 */	bne lbl_80349240
/* 80349230 00345E10  38 60 00 00 */	li r3, 0
/* 80349234 00345E14  38 80 00 00 */	li r4, 0
/* 80349238 00345E18  4B FF FB BD */	bl UnlockSram
/* 8034923C 00345E1C  48 00 00 24 */	b lbl_80349260
lbl_80349240:
/* 80349240 00345E20  54 60 07 B8 */	rlwinm r0, r3, 0, 0x1e, 0x1c
/* 80349244 00345E24  98 1F 00 13 */	stb r0, 0x13(r31)
/* 80349248 00345E28  38 60 00 01 */	li r3, 1
/* 8034924C 00345E2C  38 80 00 00 */	li r4, 0
/* 80349250 00345E30  88 1F 00 13 */	lbz r0, 0x13(r31)
/* 80349254 00345E34  7C 00 F3 78 */	or r0, r0, r30
/* 80349258 00345E38  98 1F 00 13 */	stb r0, 0x13(r31)
/* 8034925C 00345E3C  4B FF FB 99 */	bl UnlockSram
lbl_80349260:
/* 80349260 00345E40  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80349264 00345E44  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80349268 00345E48  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8034926C 00345E4C  7C 08 03 A6 */	mtlr r0
/* 80349270 00345E50  38 21 00 20 */	addi r1, r1, 0x20
/* 80349274 00345E54  4E 80 00 20 */	blr 

.global OSGetProgressiveMode
OSGetProgressiveMode:
/* 80349278 00345E58  7C 08 02 A6 */	mflr r0
/* 8034927C 00345E5C  3C 60 80 4A */	lis r3, lbl_804A7D60@ha
/* 80349280 00345E60  90 01 00 04 */	stw r0, 4(r1)
/* 80349284 00345E64  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80349288 00345E68  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8034928C 00345E6C  3B E3 7D 60 */	addi r31, r3, lbl_804A7D60@l
/* 80349290 00345E70  4B FF E0 D5 */	bl OSDisableInterrupts
/* 80349294 00345E74  80 1F 00 48 */	lwz r0, 0x48(r31)
/* 80349298 00345E78  38 9F 00 48 */	addi r4, r31, 0x48
/* 8034929C 00345E7C  2C 00 00 00 */	cmpwi r0, 0
/* 803492A0 00345E80  41 82 00 10 */	beq lbl_803492B0
/* 803492A4 00345E84  4B FF E0 E9 */	bl OSRestoreInterrupts
/* 803492A8 00345E88  3B E0 00 00 */	li r31, 0
/* 803492AC 00345E8C  48 00 00 10 */	b lbl_803492BC
lbl_803492B0:
/* 803492B0 00345E90  90 7F 00 44 */	stw r3, 0x44(r31)
/* 803492B4 00345E94  38 00 00 01 */	li r0, 1
/* 803492B8 00345E98  90 04 00 00 */	stw r0, 0(r4)
lbl_803492BC:
/* 803492BC 00345E9C  88 1F 00 13 */	lbz r0, 0x13(r31)
/* 803492C0 00345EA0  38 60 00 00 */	li r3, 0
/* 803492C4 00345EA4  38 80 00 00 */	li r4, 0
/* 803492C8 00345EA8  54 1F CF FE */	rlwinm r31, r0, 0x19, 0x1f, 0x1f
/* 803492CC 00345EAC  4B FF FB 29 */	bl UnlockSram
/* 803492D0 00345EB0  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 803492D4 00345EB4  7F E3 FB 78 */	mr r3, r31
/* 803492D8 00345EB8  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 803492DC 00345EBC  38 21 00 18 */	addi r1, r1, 0x18
/* 803492E0 00345EC0  7C 08 03 A6 */	mtlr r0
/* 803492E4 00345EC4  4E 80 00 20 */	blr 

.global OSSetProgressiveMode
OSSetProgressiveMode:
/* 803492E8 00345EC8  7C 08 02 A6 */	mflr r0
/* 803492EC 00345ECC  3C 80 80 4A */	lis r4, lbl_804A7D60@ha
/* 803492F0 00345ED0  90 01 00 04 */	stw r0, 4(r1)
/* 803492F4 00345ED4  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 803492F8 00345ED8  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 803492FC 00345EDC  3B E4 7D 60 */	addi r31, r4, lbl_804A7D60@l
/* 80349300 00345EE0  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80349304 00345EE4  54 7E 3E 30 */	rlwinm r30, r3, 7, 0x18, 0x18
/* 80349308 00345EE8  4B FF E0 5D */	bl OSDisableInterrupts
/* 8034930C 00345EEC  80 1F 00 48 */	lwz r0, 0x48(r31)
/* 80349310 00345EF0  38 9F 00 48 */	addi r4, r31, 0x48
/* 80349314 00345EF4  2C 00 00 00 */	cmpwi r0, 0
/* 80349318 00345EF8  41 82 00 10 */	beq lbl_80349328
/* 8034931C 00345EFC  4B FF E0 71 */	bl OSRestoreInterrupts
/* 80349320 00345F00  3B E0 00 00 */	li r31, 0
/* 80349324 00345F04  48 00 00 10 */	b lbl_80349334
lbl_80349328:
/* 80349328 00345F08  90 7F 00 44 */	stw r3, 0x44(r31)
/* 8034932C 00345F0C  38 00 00 01 */	li r0, 1
/* 80349330 00345F10  90 04 00 00 */	stw r0, 0(r4)
lbl_80349334:
/* 80349334 00345F14  88 7F 00 13 */	lbz r3, 0x13(r31)
/* 80349338 00345F18  54 60 06 30 */	rlwinm r0, r3, 0, 0x18, 0x18
/* 8034933C 00345F1C  7C 1E 00 40 */	cmplw r30, r0
/* 80349340 00345F20  40 82 00 14 */	bne lbl_80349354
/* 80349344 00345F24  38 60 00 00 */	li r3, 0
/* 80349348 00345F28  38 80 00 00 */	li r4, 0
/* 8034934C 00345F2C  4B FF FA A9 */	bl UnlockSram
/* 80349350 00345F30  48 00 00 24 */	b lbl_80349374
lbl_80349354:
/* 80349354 00345F34  54 60 06 6E */	rlwinm r0, r3, 0, 0x19, 0x17
/* 80349358 00345F38  98 1F 00 13 */	stb r0, 0x13(r31)
/* 8034935C 00345F3C  38 60 00 01 */	li r3, 1
/* 80349360 00345F40  38 80 00 00 */	li r4, 0
/* 80349364 00345F44  88 1F 00 13 */	lbz r0, 0x13(r31)
/* 80349368 00345F48  7C 00 F3 78 */	or r0, r0, r30
/* 8034936C 00345F4C  98 1F 00 13 */	stb r0, 0x13(r31)
/* 80349370 00345F50  4B FF FA 85 */	bl UnlockSram
lbl_80349374:
/* 80349374 00345F54  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80349378 00345F58  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8034937C 00345F5C  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80349380 00345F60  7C 08 03 A6 */	mtlr r0
/* 80349384 00345F64  38 21 00 20 */	addi r1, r1, 0x20
/* 80349388 00345F68  4E 80 00 20 */	blr 

.global OSGetWirelessID
OSGetWirelessID:
/* 8034938C 00345F6C  7C 08 02 A6 */	mflr r0
/* 80349390 00345F70  3C 80 80 4A */	lis r4, lbl_804A7D60@ha
/* 80349394 00345F74  90 01 00 04 */	stw r0, 4(r1)
/* 80349398 00345F78  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8034939C 00345F7C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 803493A0 00345F80  3B E4 7D 60 */	addi r31, r4, lbl_804A7D60@l
/* 803493A4 00345F84  93 C1 00 18 */	stw r30, 0x18(r1)
/* 803493A8 00345F88  3B C3 00 00 */	addi r30, r3, 0
/* 803493AC 00345F8C  4B FF DF B9 */	bl OSDisableInterrupts
/* 803493B0 00345F90  80 1F 00 48 */	lwz r0, 0x48(r31)
/* 803493B4 00345F94  38 9F 00 48 */	addi r4, r31, 0x48
/* 803493B8 00345F98  2C 00 00 00 */	cmpwi r0, 0
/* 803493BC 00345F9C  41 82 00 10 */	beq lbl_803493CC
/* 803493C0 00345FA0  4B FF DF CD */	bl OSRestoreInterrupts
/* 803493C4 00345FA4  38 60 00 00 */	li r3, 0
/* 803493C8 00345FA8  48 00 00 14 */	b lbl_803493DC
lbl_803493CC:
/* 803493CC 00345FAC  90 7F 00 44 */	stw r3, 0x44(r31)
/* 803493D0 00345FB0  38 00 00 01 */	li r0, 1
/* 803493D4 00345FB4  38 7F 00 14 */	addi r3, r31, 0x14
/* 803493D8 00345FB8  90 04 00 00 */	stw r0, 0(r4)
lbl_803493DC:
/* 803493DC 00345FBC  57 C0 08 3C */	slwi r0, r30, 1
/* 803493E0 00345FC0  7C 63 02 14 */	add r3, r3, r0
/* 803493E4 00345FC4  A3 E3 00 1C */	lhz r31, 0x1c(r3)
/* 803493E8 00345FC8  38 60 00 00 */	li r3, 0
/* 803493EC 00345FCC  38 80 00 14 */	li r4, 0x14
/* 803493F0 00345FD0  4B FF FA 05 */	bl UnlockSram
/* 803493F4 00345FD4  80 01 00 24 */	lwz r0, 0x24(r1)
/* 803493F8 00345FD8  7F E3 FB 78 */	mr r3, r31
/* 803493FC 00345FDC  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80349400 00345FE0  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80349404 00345FE4  7C 08 03 A6 */	mtlr r0
/* 80349408 00345FE8  38 21 00 20 */	addi r1, r1, 0x20
/* 8034940C 00345FEC  4E 80 00 20 */	blr 

.global OSSetWirelessID
OSSetWirelessID:
/* 80349410 00345FF0  7C 08 02 A6 */	mflr r0
/* 80349414 00345FF4  3C A0 80 4A */	lis r5, lbl_804A7D60@ha
/* 80349418 00345FF8  90 01 00 04 */	stw r0, 4(r1)
/* 8034941C 00345FFC  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 80349420 00346000  93 E1 00 24 */	stw r31, 0x24(r1)
/* 80349424 00346004  3B E5 7D 60 */	addi r31, r5, lbl_804A7D60@l
/* 80349428 00346008  93 C1 00 20 */	stw r30, 0x20(r1)
/* 8034942C 0034600C  3B C4 00 00 */	addi r30, r4, 0
/* 80349430 00346010  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 80349434 00346014  3B A3 00 00 */	addi r29, r3, 0
/* 80349438 00346018  4B FF DF 2D */	bl OSDisableInterrupts
/* 8034943C 0034601C  80 1F 00 48 */	lwz r0, 0x48(r31)
/* 80349440 00346020  38 9F 00 48 */	addi r4, r31, 0x48
/* 80349444 00346024  2C 00 00 00 */	cmpwi r0, 0
/* 80349448 00346028  41 82 00 10 */	beq lbl_80349458
/* 8034944C 0034602C  4B FF DF 41 */	bl OSRestoreInterrupts
/* 80349450 00346030  38 60 00 00 */	li r3, 0
/* 80349454 00346034  48 00 00 14 */	b lbl_80349468
lbl_80349458:
/* 80349458 00346038  90 7F 00 44 */	stw r3, 0x44(r31)
/* 8034945C 0034603C  38 00 00 01 */	li r0, 1
/* 80349460 00346040  38 7F 00 14 */	addi r3, r31, 0x14
/* 80349464 00346044  90 04 00 00 */	stw r0, 0(r4)
lbl_80349468:
/* 80349468 00346048  57 A0 08 3C */	slwi r0, r29, 1
/* 8034946C 0034604C  7C 83 02 14 */	add r4, r3, r0
/* 80349470 00346050  A4 64 00 1C */	lhzu r3, 0x1c(r4)
/* 80349474 00346054  57 C0 04 3E */	clrlwi r0, r30, 0x10
/* 80349478 00346058  7C 03 00 40 */	cmplw r3, r0
/* 8034947C 0034605C  41 82 00 18 */	beq lbl_80349494
/* 80349480 00346060  B3 C4 00 00 */	sth r30, 0(r4)
/* 80349484 00346064  38 60 00 01 */	li r3, 1
/* 80349488 00346068  38 80 00 14 */	li r4, 0x14
/* 8034948C 0034606C  4B FF F9 69 */	bl UnlockSram
/* 80349490 00346070  48 00 00 10 */	b lbl_803494A0
lbl_80349494:
/* 80349494 00346074  38 60 00 00 */	li r3, 0
/* 80349498 00346078  38 80 00 14 */	li r4, 0x14
/* 8034949C 0034607C  4B FF F9 59 */	bl UnlockSram
lbl_803494A0:
/* 803494A0 00346080  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 803494A4 00346084  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 803494A8 00346088  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 803494AC 0034608C  7C 08 03 A6 */	mtlr r0
/* 803494B0 00346090  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 803494B4 00346094  38 21 00 28 */	addi r1, r1, 0x28
/* 803494B8 00346098  4E 80 00 20 */	blr 


.section .bss, "wa"
    .balign 8
.global lbl_804A7D60
lbl_804A7D60:
	.skip 0x58
