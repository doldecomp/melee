.include "macros.inc"

.section .text  # 0x80343E44 - 0x803444C4

.global OSInitAlloc
OSInitAlloc:
/* 80344078 00340C58  1C E5 00 0C */	mulli r7, r5, 0xc
/* 8034407C 00340C5C  90 6D BC C0 */	stw r3, HeapArray@sda21(r13)
/* 80344080 00340C60  90 AD BC C4 */	stw r5, NumHeaps@sda21(r13)
/* 80344084 00340C64  38 C0 00 00 */	li r6, 0
/* 80344088 00340C68  38 66 00 00 */	addi r3, r6, 0
/* 8034408C 00340C6C  39 00 00 00 */	li r8, 0
/* 80344090 00340C70  38 A0 FF FF */	li r5, -1
/* 80344094 00340C74  48 00 00 20 */	b lbl_803440B4
lbl_80344098:
/* 80344098 00340C78  80 0D BC C0 */	lwz r0, HeapArray@sda21(r13)
/* 8034409C 00340C7C  39 08 00 01 */	addi r8, r8, 1
/* 803440A0 00340C80  7D 20 32 14 */	add r9, r0, r6
/* 803440A4 00340C84  90 A9 00 00 */	stw r5, 0(r9)
/* 803440A8 00340C88  38 C6 00 0C */	addi r6, r6, 0xc
/* 803440AC 00340C8C  90 69 00 08 */	stw r3, 8(r9)
/* 803440B0 00340C90  90 69 00 04 */	stw r3, 4(r9)
lbl_803440B4:
/* 803440B4 00340C94  80 0D BC C4 */	lwz r0, NumHeaps@sda21(r13)
/* 803440B8 00340C98  7C 08 00 00 */	cmpw r8, r0
/* 803440BC 00340C9C  41 80 FF DC */	blt lbl_80344098
/* 803440C0 00340CA0  80 6D BC C0 */	lwz r3, HeapArray@sda21(r13)
/* 803440C4 00340CA4  54 80 00 34 */	rlwinm r0, r4, 0, 0, 0x1a
/* 803440C8 00340CA8  38 80 FF FF */	li r4, -1
/* 803440CC 00340CAC  90 0D BC CC */	stw r0, ArenaEnd@sda21(r13)
/* 803440D0 00340CB0  7C 63 3A 14 */	add r3, r3, r7
/* 803440D4 00340CB4  38 03 00 1F */	addi r0, r3, 0x1f
/* 803440D8 00340CB8  90 8D A5 68 */	stw r4, __OSCurrHeap@sda21(r13)
/* 803440DC 00340CBC  54 03 00 34 */	rlwinm r3, r0, 0, 0, 0x1a
/* 803440E0 00340CC0  90 6D BC C8 */	stw r3, ArenaStart@sda21(r13)
/* 803440E4 00340CC4  4E 80 00 20 */	blr 

.global OSCreateHeap
OSCreateHeap:
/* 803440E8 00340CC8  80 CD BC C4 */	lwz r6, NumHeaps@sda21(r13)
/* 803440EC 00340CCC  38 03 00 1F */	addi r0, r3, 0x1f
/* 803440F0 00340CD0  80 AD BC C0 */	lwz r5, HeapArray@sda21(r13)
/* 803440F4 00340CD4  54 07 00 34 */	rlwinm r7, r0, 0, 0, 0x1a
/* 803440F8 00340CD8  2C 06 00 00 */	cmpwi r6, 0
/* 803440FC 00340CDC  7C C9 03 A6 */	mtctr r6
/* 80344100 00340CE0  54 84 00 34 */	rlwinm r4, r4, 0, 0, 0x1a
/* 80344104 00340CE4  38 60 00 00 */	li r3, 0
/* 80344108 00340CE8  40 81 00 44 */	ble lbl_8034414C
lbl_8034410C:
/* 8034410C 00340CEC  80 05 00 00 */	lwz r0, 0(r5)
/* 80344110 00340CF0  2C 00 00 00 */	cmpwi r0, 0
/* 80344114 00340CF4  40 80 00 2C */	bge lbl_80344140
/* 80344118 00340CF8  7C 07 20 50 */	subf r0, r7, r4
/* 8034411C 00340CFC  90 05 00 00 */	stw r0, 0(r5)
/* 80344120 00340D00  38 80 00 00 */	li r4, 0
/* 80344124 00340D04  90 87 00 00 */	stw r4, 0(r7)
/* 80344128 00340D08  90 87 00 04 */	stw r4, 4(r7)
/* 8034412C 00340D0C  80 05 00 00 */	lwz r0, 0(r5)
/* 80344130 00340D10  90 07 00 08 */	stw r0, 8(r7)
/* 80344134 00340D14  90 E5 00 04 */	stw r7, 4(r5)
/* 80344138 00340D18  90 85 00 08 */	stw r4, 8(r5)
/* 8034413C 00340D1C  4E 80 00 20 */	blr 
lbl_80344140:
/* 80344140 00340D20  38 A5 00 0C */	addi r5, r5, 0xc
/* 80344144 00340D24  38 63 00 01 */	addi r3, r3, 1
/* 80344148 00340D28  42 00 FF C4 */	bdnz lbl_8034410C
lbl_8034414C:
/* 8034414C 00340D2C  38 60 FF FF */	li r3, -1
/* 80344150 00340D30  4E 80 00 20 */	blr 

.global OSDestroyHeap
OSDestroyHeap:
/* 80344154 00340D34  1C 03 00 0C */	mulli r0, r3, 0xc
/* 80344158 00340D38  80 6D BC C0 */	lwz r3, HeapArray@sda21(r13)
/* 8034415C 00340D3C  38 80 FF FF */	li r4, -1
/* 80344160 00340D40  7C 83 01 2E */	stwx r4, r3, r0
/* 80344164 00340D44  4E 80 00 20 */	blr 

.global OSCheckHeap
OSCheckHeap:
/* 80344168 00340D48  7C 08 02 A6 */	mflr r0
/* 8034416C 00340D4C  3C 80 80 40 */	lis r4, lbl_804017D8@ha
/* 80344170 00340D50  90 01 00 04 */	stw r0, 4(r1)
/* 80344174 00340D54  38 C4 17 D8 */	addi r6, r4, lbl_804017D8@l
/* 80344178 00340D58  38 00 00 00 */	li r0, 0
/* 8034417C 00340D5C  94 21 FF F8 */	stwu r1, -8(r1)
/* 80344180 00340D60  38 80 00 00 */	li r4, 0
/* 80344184 00340D64  80 ED BC C0 */	lwz r7, HeapArray@sda21(r13)
/* 80344188 00340D68  28 07 00 00 */	cmplwi r7, 0
/* 8034418C 00340D6C  40 82 00 1C */	bne lbl_803441A8
/* 80344190 00340D70  38 66 00 00 */	addi r3, r6, 0
/* 80344194 00340D74  4C C6 31 82 */	crclr 6
/* 80344198 00340D78  38 80 03 7D */	li r4, 0x37d
/* 8034419C 00340D7C  48 00 15 0D */	bl OSReport
/* 803441A0 00340D80  38 60 FF FF */	li r3, -1
/* 803441A4 00340D84  48 00 03 14 */	b lbl_803444B8
lbl_803441A8:
/* 803441A8 00340D88  2C 03 00 00 */	cmpwi r3, 0
/* 803441AC 00340D8C  41 80 00 10 */	blt lbl_803441BC
/* 803441B0 00340D90  80 AD BC C4 */	lwz r5, NumHeaps@sda21(r13)
/* 803441B4 00340D94  7C 03 28 00 */	cmpw r3, r5
/* 803441B8 00340D98  41 80 00 1C */	blt lbl_803441D4
lbl_803441BC:
/* 803441BC 00340D9C  38 66 00 24 */	addi r3, r6, 0x24
/* 803441C0 00340DA0  4C C6 31 82 */	crclr 6
/* 803441C4 00340DA4  38 80 03 7E */	li r4, 0x37e
/* 803441C8 00340DA8  48 00 14 E1 */	bl OSReport
/* 803441CC 00340DAC  38 60 FF FF */	li r3, -1
/* 803441D0 00340DB0  48 00 02 E8 */	b lbl_803444B8
lbl_803441D4:
/* 803441D4 00340DB4  1C 63 00 0C */	mulli r3, r3, 0xc
/* 803441D8 00340DB8  7C A7 1A 14 */	add r5, r7, r3
/* 803441DC 00340DBC  80 65 00 00 */	lwz r3, 0(r5)
/* 803441E0 00340DC0  2C 03 00 00 */	cmpwi r3, 0
/* 803441E4 00340DC4  40 80 00 1C */	bge lbl_80344200
/* 803441E8 00340DC8  38 66 00 5C */	addi r3, r6, 0x5c
/* 803441EC 00340DCC  4C C6 31 82 */	crclr 6
/* 803441F0 00340DD0  38 80 03 81 */	li r4, 0x381
/* 803441F4 00340DD4  48 00 14 B5 */	bl OSReport
/* 803441F8 00340DD8  38 60 FF FF */	li r3, -1
/* 803441FC 00340DDC  48 00 02 BC */	b lbl_803444B8
lbl_80344200:
/* 80344200 00340DE0  80 E5 00 08 */	lwz r7, 8(r5)
/* 80344204 00340DE4  28 07 00 00 */	cmplwi r7, 0
/* 80344208 00340DE8  41 82 00 28 */	beq lbl_80344230
/* 8034420C 00340DEC  80 67 00 00 */	lwz r3, 0(r7)
/* 80344210 00340DF0  28 03 00 00 */	cmplwi r3, 0
/* 80344214 00340DF4  41 82 00 1C */	beq lbl_80344230
/* 80344218 00340DF8  38 66 00 84 */	addi r3, r6, 0x84
/* 8034421C 00340DFC  4C C6 31 82 */	crclr 6
/* 80344220 00340E00  38 80 03 83 */	li r4, 0x383
/* 80344224 00340E04  48 00 14 85 */	bl OSReport
/* 80344228 00340E08  38 60 FF FF */	li r3, -1
/* 8034422C 00340E0C  48 00 02 8C */	b lbl_803444B8
lbl_80344230:
/* 80344230 00340E10  81 2D BC C8 */	lwz r9, ArenaStart@sda21(r13)
/* 80344234 00340E14  7C E8 3B 78 */	mr r8, r7
/* 80344238 00340E18  81 4D BC CC */	lwz r10, ArenaEnd@sda21(r13)
/* 8034423C 00340E1C  48 00 00 F0 */	b lbl_8034432C
lbl_80344240:
/* 80344240 00340E20  7C 09 40 40 */	cmplw r9, r8
/* 80344244 00340E24  41 81 00 0C */	bgt lbl_80344250
/* 80344248 00340E28  7C 08 50 40 */	cmplw r8, r10
/* 8034424C 00340E2C  41 80 00 1C */	blt lbl_80344268
lbl_80344250:
/* 80344250 00340E30  38 66 00 D4 */	addi r3, r6, 0xd4
/* 80344254 00340E34  4C C6 31 82 */	crclr 6
/* 80344258 00340E38  38 80 03 86 */	li r4, 0x386
/* 8034425C 00340E3C  48 00 14 4D */	bl OSReport
/* 80344260 00340E40  38 60 FF FF */	li r3, -1
/* 80344264 00340E44  48 00 02 54 */	b lbl_803444B8
lbl_80344268:
/* 80344268 00340E48  55 03 06 FF */	clrlwi. r3, r8, 0x1b
/* 8034426C 00340E4C  41 82 00 1C */	beq lbl_80344288
/* 80344270 00340E50  38 66 01 14 */	addi r3, r6, 0x114
/* 80344274 00340E54  4C C6 31 82 */	crclr 6
/* 80344278 00340E58  38 80 03 87 */	li r4, 0x387
/* 8034427C 00340E5C  48 00 14 2D */	bl OSReport
/* 80344280 00340E60  38 60 FF FF */	li r3, -1
/* 80344284 00340E64  48 00 02 34 */	b lbl_803444B8
lbl_80344288:
/* 80344288 00340E68  80 E8 00 04 */	lwz r7, 4(r8)
/* 8034428C 00340E6C  28 07 00 00 */	cmplwi r7, 0
/* 80344290 00340E70  41 82 00 28 */	beq lbl_803442B8
/* 80344294 00340E74  80 67 00 00 */	lwz r3, 0(r7)
/* 80344298 00340E78  7C 03 40 40 */	cmplw r3, r8
/* 8034429C 00340E7C  41 82 00 1C */	beq lbl_803442B8
/* 803442A0 00340E80  38 66 01 4C */	addi r3, r6, 0x14c
/* 803442A4 00340E84  4C C6 31 82 */	crclr 6
/* 803442A8 00340E88  38 80 03 88 */	li r4, 0x388
/* 803442AC 00340E8C  48 00 13 FD */	bl OSReport
/* 803442B0 00340E90  38 60 FF FF */	li r3, -1
/* 803442B4 00340E94  48 00 02 04 */	b lbl_803444B8
lbl_803442B8:
/* 803442B8 00340E98  81 08 00 08 */	lwz r8, 8(r8)
/* 803442BC 00340E9C  28 08 00 40 */	cmplwi r8, 0x40
/* 803442C0 00340EA0  40 80 00 1C */	bge lbl_803442DC
/* 803442C4 00340EA4  38 66 01 98 */	addi r3, r6, 0x198
/* 803442C8 00340EA8  4C C6 31 82 */	crclr 6
/* 803442CC 00340EAC  38 80 03 89 */	li r4, 0x389
/* 803442D0 00340EB0  48 00 13 D9 */	bl OSReport
/* 803442D4 00340EB4  38 60 FF FF */	li r3, -1
/* 803442D8 00340EB8  48 00 01 E0 */	b lbl_803444B8
lbl_803442DC:
/* 803442DC 00340EBC  55 03 06 FF */	clrlwi. r3, r8, 0x1b
/* 803442E0 00340EC0  41 82 00 1C */	beq lbl_803442FC
/* 803442E4 00340EC4  38 66 01 CC */	addi r3, r6, 0x1cc
/* 803442E8 00340EC8  4C C6 31 82 */	crclr 6
/* 803442EC 00340ECC  38 80 03 8A */	li r4, 0x38a
/* 803442F0 00340ED0  48 00 13 B9 */	bl OSReport
/* 803442F4 00340ED4  38 60 FF FF */	li r3, -1
/* 803442F8 00340ED8  48 00 01 C0 */	b lbl_803444B8
lbl_803442FC:
/* 803442FC 00340EDC  7C 00 42 15 */	add. r0, r0, r8
/* 80344300 00340EE0  40 81 00 10 */	ble lbl_80344310
/* 80344304 00340EE4  80 65 00 00 */	lwz r3, 0(r5)
/* 80344308 00340EE8  7C 00 18 00 */	cmpw r0, r3
/* 8034430C 00340EEC  40 81 00 1C */	ble lbl_80344328
lbl_80344310:
/* 80344310 00340EF0  38 66 02 0C */	addi r3, r6, 0x20c
/* 80344314 00340EF4  4C C6 31 82 */	crclr 6
/* 80344318 00340EF8  38 80 03 8D */	li r4, 0x38d
/* 8034431C 00340EFC  48 00 13 8D */	bl OSReport
/* 80344320 00340F00  38 60 FF FF */	li r3, -1
/* 80344324 00340F04  48 00 01 94 */	b lbl_803444B8
lbl_80344328:
/* 80344328 00340F08  7C E8 3B 78 */	mr r8, r7
lbl_8034432C:
/* 8034432C 00340F0C  28 08 00 00 */	cmplwi r8, 0
/* 80344330 00340F10  40 82 FF 10 */	bne lbl_80344240
/* 80344334 00340F14  81 65 00 04 */	lwz r11, 4(r5)
/* 80344338 00340F18  28 0B 00 00 */	cmplwi r11, 0
/* 8034433C 00340F1C  41 82 01 4C */	beq lbl_80344488
/* 80344340 00340F20  80 6B 00 00 */	lwz r3, 0(r11)
/* 80344344 00340F24  28 03 00 00 */	cmplwi r3, 0
/* 80344348 00340F28  41 82 01 40 */	beq lbl_80344488
/* 8034434C 00340F2C  38 66 02 48 */	addi r3, r6, 0x248
/* 80344350 00340F30  4C C6 31 82 */	crclr 6
/* 80344354 00340F34  38 80 03 95 */	li r4, 0x395
/* 80344358 00340F38  48 00 13 51 */	bl OSReport
/* 8034435C 00340F3C  38 60 FF FF */	li r3, -1
/* 80344360 00340F40  48 00 01 58 */	b lbl_803444B8
/* 80344364 00340F44  48 00 01 24 */	b lbl_80344488
lbl_80344368:
/* 80344368 00340F48  7C 09 58 40 */	cmplw r9, r11
/* 8034436C 00340F4C  41 81 00 0C */	bgt lbl_80344378
/* 80344370 00340F50  7C 0B 50 40 */	cmplw r11, r10
/* 80344374 00340F54  41 80 00 1C */	blt lbl_80344390
lbl_80344378:
/* 80344378 00340F58  38 66 00 D4 */	addi r3, r6, 0xd4
/* 8034437C 00340F5C  4C C6 31 82 */	crclr 6
/* 80344380 00340F60  38 80 03 98 */	li r4, 0x398
/* 80344384 00340F64  48 00 13 25 */	bl OSReport
/* 80344388 00340F68  38 60 FF FF */	li r3, -1
/* 8034438C 00340F6C  48 00 01 2C */	b lbl_803444B8
lbl_80344390:
/* 80344390 00340F70  55 63 06 FF */	clrlwi. r3, r11, 0x1b
/* 80344394 00340F74  41 82 00 1C */	beq lbl_803443B0
/* 80344398 00340F78  38 66 01 14 */	addi r3, r6, 0x114
/* 8034439C 00340F7C  4C C6 31 82 */	crclr 6
/* 803443A0 00340F80  38 80 03 99 */	li r4, 0x399
/* 803443A4 00340F84  48 00 13 05 */	bl OSReport
/* 803443A8 00340F88  38 60 FF FF */	li r3, -1
/* 803443AC 00340F8C  48 00 01 0C */	b lbl_803444B8
lbl_803443B0:
/* 803443B0 00340F90  80 EB 00 04 */	lwz r7, 4(r11)
/* 803443B4 00340F94  28 07 00 00 */	cmplwi r7, 0
/* 803443B8 00340F98  41 82 00 28 */	beq lbl_803443E0
/* 803443BC 00340F9C  80 67 00 00 */	lwz r3, 0(r7)
/* 803443C0 00340FA0  7C 03 58 40 */	cmplw r3, r11
/* 803443C4 00340FA4  41 82 00 1C */	beq lbl_803443E0
/* 803443C8 00340FA8  38 66 01 4C */	addi r3, r6, 0x14c
/* 803443CC 00340FAC  4C C6 31 82 */	crclr 6
/* 803443D0 00340FB0  38 80 03 9A */	li r4, 0x39a
/* 803443D4 00340FB4  48 00 12 D5 */	bl OSReport
/* 803443D8 00340FB8  38 60 FF FF */	li r3, -1
/* 803443DC 00340FBC  48 00 00 DC */	b lbl_803444B8
lbl_803443E0:
/* 803443E0 00340FC0  81 0B 00 08 */	lwz r8, 8(r11)
/* 803443E4 00340FC4  28 08 00 40 */	cmplwi r8, 0x40
/* 803443E8 00340FC8  40 80 00 1C */	bge lbl_80344404
/* 803443EC 00340FCC  38 66 01 98 */	addi r3, r6, 0x198
/* 803443F0 00340FD0  4C C6 31 82 */	crclr 6
/* 803443F4 00340FD4  38 80 03 9B */	li r4, 0x39b
/* 803443F8 00340FD8  48 00 12 B1 */	bl OSReport
/* 803443FC 00340FDC  38 60 FF FF */	li r3, -1
/* 80344400 00340FE0  48 00 00 B8 */	b lbl_803444B8
lbl_80344404:
/* 80344404 00340FE4  55 03 06 FF */	clrlwi. r3, r8, 0x1b
/* 80344408 00340FE8  41 82 00 1C */	beq lbl_80344424
/* 8034440C 00340FEC  38 66 01 CC */	addi r3, r6, 0x1cc
/* 80344410 00340FF0  4C C6 31 82 */	crclr 6
/* 80344414 00340FF4  38 80 03 9C */	li r4, 0x39c
/* 80344418 00340FF8  48 00 12 91 */	bl OSReport
/* 8034441C 00340FFC  38 60 FF FF */	li r3, -1
/* 80344420 00341000  48 00 00 98 */	b lbl_803444B8
lbl_80344424:
/* 80344424 00341004  28 07 00 00 */	cmplwi r7, 0
/* 80344428 00341008  41 82 00 28 */	beq lbl_80344450
/* 8034442C 0034100C  7C 6B 42 14 */	add r3, r11, r8
/* 80344430 00341010  7C 03 38 40 */	cmplw r3, r7
/* 80344434 00341014  41 80 00 1C */	blt lbl_80344450
/* 80344438 00341018  38 66 02 90 */	addi r3, r6, 0x290
/* 8034443C 0034101C  4C C6 31 82 */	crclr 6
/* 80344440 00341020  38 80 03 9D */	li r4, 0x39d
/* 80344444 00341024  48 00 12 65 */	bl OSReport
/* 80344448 00341028  38 60 FF FF */	li r3, -1
/* 8034444C 0034102C  48 00 00 6C */	b lbl_803444B8
lbl_80344450:
/* 80344450 00341030  7C 00 42 15 */	add. r0, r0, r8
/* 80344454 00341034  7C 88 22 14 */	add r4, r8, r4
/* 80344458 00341038  38 84 FF E0 */	addi r4, r4, -32
/* 8034445C 0034103C  40 81 00 10 */	ble lbl_8034446C
/* 80344460 00341040  80 65 00 00 */	lwz r3, 0(r5)
/* 80344464 00341044  7C 00 18 00 */	cmpw r0, r3
/* 80344468 00341048  40 81 00 1C */	ble lbl_80344484
lbl_8034446C:
/* 8034446C 0034104C  38 66 02 0C */	addi r3, r6, 0x20c
/* 80344470 00341050  4C C6 31 82 */	crclr 6
/* 80344474 00341054  38 80 03 A1 */	li r4, 0x3a1
/* 80344478 00341058  48 00 12 31 */	bl OSReport
/* 8034447C 0034105C  38 60 FF FF */	li r3, -1
/* 80344480 00341060  48 00 00 38 */	b lbl_803444B8
lbl_80344484:
/* 80344484 00341064  7C EB 3B 78 */	mr r11, r7
lbl_80344488:
/* 80344488 00341068  28 0B 00 00 */	cmplwi r11, 0
/* 8034448C 0034106C  40 82 FE DC */	bne lbl_80344368
/* 80344490 00341070  80 65 00 00 */	lwz r3, 0(r5)
/* 80344494 00341074  7C 00 18 00 */	cmpw r0, r3
/* 80344498 00341078  41 82 00 1C */	beq lbl_803444B4
/* 8034449C 0034107C  38 66 02 F0 */	addi r3, r6, 0x2f0
/* 803444A0 00341080  4C C6 31 82 */	crclr 6
/* 803444A4 00341084  38 80 03 A8 */	li r4, 0x3a8
/* 803444A8 00341088  48 00 12 01 */	bl OSReport
/* 803444AC 0034108C  38 60 FF FF */	li r3, -1
/* 803444B0 00341090  48 00 00 08 */	b lbl_803444B8
lbl_803444B4:
/* 803444B4 00341094  7C 83 23 78 */	mr r3, r4
lbl_803444B8:
/* 803444B8 00341098  80 01 00 0C */	lwz r0, 0xc(r1)
/* 803444BC 0034109C  38 21 00 08 */	addi r1, r1, 8
/* 803444C0 003410A0  7C 08 03 A6 */	mtlr r0
/* 803444C4 003410A4  4E 80 00 20 */	blr 


.section .data
    .balign 8
.global lbl_804017D8
lbl_804017D8:
    .asciz "OSCheckHeap: Failed HeapArray in %d"
    .balign 4
    .asciz "OSCheckHeap: Failed 0 <= heap && heap < NumHeaps in %d"
    .balign 4
    .asciz "OSCheckHeap: Failed 0 <= hd->size in %d"
    .balign 4
    .asciz "OSCheckHeap: Failed hd->allocated == NULL || hd->allocated->prev == NULL in %d"
    .balign 4
    .asciz "OSCheckHeap: Failed InRange(cell, ArenaStart, ArenaEnd) in %d"
    .balign 4
    .asciz "OSCheckHeap: Failed OFFSET(cell, ALIGNMENT) == 0 in %d"
    .balign 4
    .asciz "OSCheckHeap: Failed cell->next == NULL || cell->next->prev == cell in %d"
    .balign 4
    .asciz "OSCheckHeap: Failed MINOBJSIZE <= cell->size in %d"
    .balign 4
    .asciz "OSCheckHeap: Failed OFFSET(cell->size, ALIGNMENT) == 0 in %d"
    .balign 4
    .asciz "OSCheckHeap: Failed 0 < total && total <= hd->size in %d"
    .balign 4
    .asciz "OSCheckHeap: Failed hd->free == NULL || hd->free->prev == NULL in %d"
    .balign 4
    .asciz "OSCheckHeap: Failed cell->next == NULL || (char*) cell + cell->size < (char*) cell->next in %d"
    .balign 4
    .asciz "OSCheckHeap: Failed total == hd->size in %d"
    .balign 4
    .asciz "\nOSDumpHeap(%d):\n"
    .balign 4
    .asciz "--------Inactive\n"
    .balign 4
    .asciz "addr\tsize\t\tend\tprev\tnext\n"
    .balign 4
    .asciz "--------Allocated\n"
    .balign 4
    .asciz "%x\t%d\t%x\t%x\t%x\n"
    .balign 4
    .asciz "--------Free\n"
    .balign 4
    .4byte NULL


.section .sdata

.global __OSCurrHeap
__OSCurrHeap:
    .4byte 0xFFFFFFFF
    .4byte 0x00000000


.section .sbss

.global HeapArray
HeapArray:
	.skip 0x4
.global NumHeaps
NumHeaps:
	.skip 0x4
.global ArenaStart
ArenaStart:
	.skip 0x4
.global ArenaEnd
ArenaEnd:
	.skip 0x4
