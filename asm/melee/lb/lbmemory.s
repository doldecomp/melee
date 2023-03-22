.include "macros.inc"

.section .text

.global lbMemory_80014E24
lbMemory_80014E24:
/* 80014E24 00011A04  7C 08 02 A6 */	mflr r0
/* 80014E28 00011A08  3C A0 80 43 */	lis r5, lbl_804318B0@ha
/* 80014E2C 00011A0C  90 01 00 04 */	stw r0, 4(r1)
/* 80014E30 00011A10  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 80014E34 00011A14  BF 61 00 14 */	stmw r27, 0x14(r1)
/* 80014E38 00011A18  3B E5 18 B0 */	addi r31, r5, lbl_804318B0@l
/* 80014E3C 00011A1C  3C A0 80 3C */	lis r5, lbl_803BA2C0@ha
/* 80014E40 00011A20  3B BF 06 98 */	addi r29, r31, 0x698
/* 80014E44 00011A24  3B C5 A2 C0 */	addi r30, r5, lbl_803BA2C0@l
/* 80014E48 00011A28  3B 63 00 00 */	addi r27, r3, 0
/* 80014E4C 00011A2C  3B 84 00 00 */	addi r28, r4, 0
/* 80014E50 00011A30  80 1F 06 98 */	lwz r0, 0x698(r31)
/* 80014E54 00011A34  28 00 00 00 */	cmplwi r0, 0
/* 80014E58 00011A38  40 82 00 14 */	bne lbMemory_80014E6C
/* 80014E5C 00011A3C  38 7E 00 00 */	addi r3, r30, 0
/* 80014E60 00011A40  38 BE 00 0C */	addi r5, r30, 0xc
/* 80014E64 00011A44  38 80 00 7B */	li r4, 0x7b
/* 80014E68 00011A48  48 37 33 B9 */	bl __assert
lbMemory_80014E6C:
/* 80014E6C 00011A4C  3C 00 80 00 */	lis r0, 0x8000
/* 80014E70 00011A50  7C 1B 00 40 */	cmplw r27, r0
/* 80014E74 00011A54  40 80 00 44 */	bge lbMemory_80014EB8
/* 80014E78 00011A58  7C 1C 00 40 */	cmplw r28, r0
/* 80014E7C 00011A5C  40 80 00 3C */	bge lbMemory_80014EB8
/* 80014E80 00011A60  80 1F 00 00 */	lwz r0, 0(r31)
/* 80014E84 00011A64  38 60 00 00 */	li r3, 0
/* 80014E88 00011A68  7C 1B 00 40 */	cmplw r27, r0
/* 80014E8C 00011A6C  41 80 00 14 */	blt lbMemory_80014EA0
/* 80014E90 00011A70  80 1F 00 04 */	lwz r0, 4(r31)
/* 80014E94 00011A74  7C 1C 00 40 */	cmplw r28, r0
/* 80014E98 00011A78  41 81 00 08 */	bgt lbMemory_80014EA0
/* 80014E9C 00011A7C  38 60 00 01 */	li r3, 1
lbMemory_80014EA0:
/* 80014EA0 00011A80  2C 03 00 00 */	cmpwi r3, 0
/* 80014EA4 00011A84  40 82 00 14 */	bne lbMemory_80014EB8
/* 80014EA8 00011A88  38 7E 00 00 */	addi r3, r30, 0
/* 80014EAC 00011A8C  38 BE 00 1C */	addi r5, r30, 0x1c
/* 80014EB0 00011A90  38 80 00 80 */	li r4, 0x80
/* 80014EB4 00011A94  48 37 33 6D */	bl __assert
lbMemory_80014EB8:
/* 80014EB8 00011A98  80 7D 00 00 */	lwz r3, 0(r29)
/* 80014EBC 00011A9C  38 00 00 00 */	li r0, 0
/* 80014EC0 00011AA0  80 83 00 00 */	lwz r4, 0(r3)
/* 80014EC4 00011AA4  90 9D 00 00 */	stw r4, 0(r29)
/* 80014EC8 00011AA8  90 03 00 00 */	stw r0, 0(r3)
/* 80014ECC 00011AAC  93 63 00 04 */	stw r27, 4(r3)
/* 80014ED0 00011AB0  93 83 00 08 */	stw r28, 8(r3)
/* 80014ED4 00011AB4  90 03 00 0C */	stw r0, 0xc(r3)
/* 80014ED8 00011AB8  BB 61 00 14 */	lmw r27, 0x14(r1)
/* 80014EDC 00011ABC  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 80014EE0 00011AC0  38 21 00 28 */	addi r1, r1, 0x28
/* 80014EE4 00011AC4  7C 08 03 A6 */	mtlr r0
/* 80014EE8 00011AC8  4E 80 00 20 */	blr

.global lbMemory_80014EEC
lbMemory_80014EEC:
/* 80014EEC 00011ACC  7C 08 02 A6 */	mflr r0
/* 80014EF0 00011AD0  90 01 00 04 */	stw r0, 4(r1)
/* 80014EF4 00011AD4  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80014EF8 00011AD8  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80014EFC 00011ADC  93 C1 00 10 */	stw r30, 0x10(r1)
/* 80014F00 00011AE0  7C 7E 1B 79 */	or. r30, r3, r3
/* 80014F04 00011AE4  3C 60 80 43 */	lis r3, lbl_804318B0@ha
/* 80014F08 00011AE8  3B E3 18 B0 */	addi r31, r3, lbl_804318B0@l
/* 80014F0C 00011AEC  40 82 00 18 */	bne lbMemory_80014F24
/* 80014F10 00011AF0  3C 60 80 3C */	lis r3, lbl_803BA2C0@ha
/* 80014F14 00011AF4  38 63 A2 C0 */	addi r3, r3, lbl_803BA2C0@l
/* 80014F18 00011AF8  38 80 00 95 */	li r4, 0x95
/* 80014F1C 00011AFC  38 AD 80 E8 */	addi r5, r13, lbl_804D3788@sda21
/* 80014F20 00011B00  48 37 33 01 */	bl __assert
lbMemory_80014F24:
/* 80014F24 00011B04  80 BE 00 0C */	lwz r5, 0xc(r30)
/* 80014F28 00011B08  38 9F 06 2C */	addi r4, r31, 0x62c
/* 80014F2C 00011B0C  48 00 00 24 */	b lbMemory_80014F50
lbMemory_80014F30:
/* 80014F30 00011B10  80 65 00 00 */	lwz r3, 0(r5)
/* 80014F34 00011B14  80 04 00 00 */	lwz r0, 0(r4)
/* 80014F38 00011B18  90 05 00 00 */	stw r0, 0(r5)
/* 80014F3C 00011B1C  90 A4 00 00 */	stw r5, 0(r4)
/* 80014F40 00011B20  7C 65 1B 78 */	mr r5, r3
/* 80014F44 00011B24  80 7F 06 30 */	lwz r3, 0x630(r31)
/* 80014F48 00011B28  38 03 FF FF */	addi r0, r3, -1
/* 80014F4C 00011B2C  90 1F 06 30 */	stw r0, 0x630(r31)
lbMemory_80014F50:
/* 80014F50 00011B30  28 05 00 00 */	cmplwi r5, 0
/* 80014F54 00011B34  40 82 FF DC */	bne lbMemory_80014F30
/* 80014F58 00011B38  80 1F 06 98 */	lwz r0, 0x698(r31)
/* 80014F5C 00011B3C  90 1E 00 00 */	stw r0, 0(r30)
/* 80014F60 00011B40  93 DF 06 98 */	stw r30, 0x698(r31)
/* 80014F64 00011B44  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80014F68 00011B48  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80014F6C 00011B4C  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 80014F70 00011B50  38 21 00 18 */	addi r1, r1, 0x18
/* 80014F74 00011B54  7C 08 03 A6 */	mtlr r0
/* 80014F78 00011B58  4E 80 00 20 */	blr

.global lbMemory_80014F7C
lbMemory_80014F7C:
/* 80014F7C 00011B5C  80 83 00 04 */	lwz r4, 4(r3)
/* 80014F80 00011B60  38 A3 00 0C */	addi r5, r3, 0xc
/* 80014F84 00011B64  38 C0 00 00 */	li r6, 0
lbMemory_80014F88:
/* 80014F88 00011B68  80 A5 00 00 */	lwz r5, 0(r5)
/* 80014F8C 00011B6C  28 05 00 00 */	cmplwi r5, 0
/* 80014F90 00011B70  41 82 00 0C */	beq lbMemory_80014F9C
/* 80014F94 00011B74  80 05 00 04 */	lwz r0, 4(r5)
/* 80014F98 00011B78  48 00 00 08 */	b lbMemory_80014FA0
lbMemory_80014F9C:
/* 80014F9C 00011B7C  80 03 00 08 */	lwz r0, 8(r3)
lbMemory_80014FA0:
/* 80014FA0 00011B80  28 05 00 00 */	cmplwi r5, 0
/* 80014FA4 00011B84  7C 04 00 50 */	subf r0, r4, r0
/* 80014FA8 00011B88  7C C6 02 14 */	add r6, r6, r0
/* 80014FAC 00011B8C  41 82 00 14 */	beq lbMemory_80014FC0
/* 80014FB0 00011B90  80 85 00 04 */	lwz r4, 4(r5)
/* 80014FB4 00011B94  80 05 00 08 */	lwz r0, 8(r5)
/* 80014FB8 00011B98  7C 84 02 14 */	add r4, r4, r0
/* 80014FBC 00011B9C  4B FF FF CC */	b lbMemory_80014F88
lbMemory_80014FC0:
/* 80014FC0 00011BA0  7C C3 33 78 */	mr r3, r6
/* 80014FC4 00011BA4  4E 80 00 20 */	blr

.global lbMemory_80014FC8
lbMemory_80014FC8:
/* 80014FC8 00011BA8  7C 08 02 A6 */	mflr r0
/* 80014FCC 00011BAC  3C A0 80 43 */	lis r5, lbl_804318B0@ha
/* 80014FD0 00011BB0  90 01 00 04 */	stw r0, 4(r1)
/* 80014FD4 00011BB4  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 80014FD8 00011BB8  BF 01 00 18 */	stmw r24, 0x18(r1)
/* 80014FDC 00011BBC  3B A5 18 B0 */	addi r29, r5, lbl_804318B0@l
/* 80014FE0 00011BC0  3C A0 80 3C */	lis r5, lbl_803BA2C0@ha
/* 80014FE4 00011BC4  3B 7D 06 2C */	addi r27, r29, 0x62c
/* 80014FE8 00011BC8  3B 85 A2 C0 */	addi r28, r5, lbl_803BA2C0@l
/* 80014FEC 00011BCC  3B 03 00 00 */	addi r24, r3, 0
/* 80014FF0 00011BD0  3B C4 00 00 */	addi r30, r4, 0
/* 80014FF4 00011BD4  3F 20 40 00 */	lis r25, 0x4000
/* 80014FF8 00011BD8  80 1D 06 2C */	lwz r0, 0x62c(r29)
/* 80014FFC 00011BDC  28 00 00 00 */	cmplwi r0, 0
/* 80015000 00011BE0  40 82 00 14 */	bne lbMemory_80015014
/* 80015004 00011BE4  38 7C 00 00 */	addi r3, r28, 0
/* 80015008 00011BE8  38 BC 00 68 */	addi r5, r28, 0x68
/* 8001500C 00011BEC  38 80 00 CC */	li r4, 0xcc
/* 80015010 00011BF0  48 37 32 11 */	bl __assert
lbMemory_80015014:
/* 80015014 00011BF4  38 1E 00 1F */	addi r0, r30, 0x1f
/* 80015018 00011BF8  80 78 00 04 */	lwz r3, 4(r24)
/* 8001501C 00011BFC  54 1E 00 34 */	rlwinm r30, r0, 0, 0, 0x1a
/* 80015020 00011C00  38 B8 00 0C */	addi r5, r24, 0xc
/* 80015024 00011C04  3B 40 00 00 */	li r26, 0
lbMemory_80015028:
/* 80015028 00011C08  80 85 00 00 */	lwz r4, 0(r5)
/* 8001502C 00011C0C  28 04 00 00 */	cmplwi r4, 0
/* 80015030 00011C10  41 82 00 0C */	beq lbMemory_8001503C
/* 80015034 00011C14  80 04 00 04 */	lwz r0, 4(r4)
/* 80015038 00011C18  48 00 00 08 */	b lbMemory_80015040
lbMemory_8001503C:
/* 8001503C 00011C1C  80 18 00 08 */	lwz r0, 8(r24)
lbMemory_80015040:
/* 80015040 00011C20  7C 03 00 50 */	subf r0, r3, r0
/* 80015044 00011C24  7C 00 F0 40 */	cmplw r0, r30
/* 80015048 00011C28  41 80 00 1C */	blt lbMemory_80015064
/* 8001504C 00011C2C  7C 1E 00 50 */	subf r0, r30, r0
/* 80015050 00011C30  7C 00 C8 40 */	cmplw r0, r25
/* 80015054 00011C34  41 81 00 10 */	bgt lbMemory_80015064
/* 80015058 00011C38  7C 19 03 78 */	mr r25, r0
/* 8001505C 00011C3C  3B E3 00 00 */	addi r31, r3, 0
/* 80015060 00011C40  3B 45 00 00 */	addi r26, r5, 0
lbMemory_80015064:
/* 80015064 00011C44  28 04 00 00 */	cmplwi r4, 0
/* 80015068 00011C48  41 82 00 18 */	beq lbMemory_80015080
/* 8001506C 00011C4C  80 64 00 04 */	lwz r3, 4(r4)
/* 80015070 00011C50  7C 85 23 78 */	mr r5, r4
/* 80015074 00011C54  80 04 00 08 */	lwz r0, 8(r4)
/* 80015078 00011C58  7C 63 02 14 */	add r3, r3, r0
/* 8001507C 00011C5C  4B FF FF AC */	b lbMemory_80015028
lbMemory_80015080:
/* 80015080 00011C60  28 1A 00 00 */	cmplwi r26, 0
/* 80015084 00011C64  40 82 00 14 */	bne lbMemory_80015098
/* 80015088 00011C68  38 7C 00 00 */	addi r3, r28, 0
/* 8001508C 00011C6C  38 BC 00 78 */	addi r5, r28, 0x78
/* 80015090 00011C70  38 80 00 E9 */	li r4, 0xe9
/* 80015094 00011C74  48 37 31 8D */	bl __assert
lbMemory_80015098:
/* 80015098 00011C78  80 7B 00 00 */	lwz r3, 0(r27)
/* 8001509C 00011C7C  38 DD 06 34 */	addi r6, r29, 0x634
/* 800150A0 00011C80  80 03 00 00 */	lwz r0, 0(r3)
/* 800150A4 00011C84  90 1B 00 00 */	stw r0, 0(r27)
/* 800150A8 00011C88  93 C3 00 08 */	stw r30, 8(r3)
/* 800150AC 00011C8C  93 E3 00 04 */	stw r31, 4(r3)
/* 800150B0 00011C90  80 1A 00 00 */	lwz r0, 0(r26)
/* 800150B4 00011C94  90 03 00 00 */	stw r0, 0(r3)
/* 800150B8 00011C98  90 7A 00 00 */	stw r3, 0(r26)
/* 800150BC 00011C9C  80 9D 06 30 */	lwz r4, 0x630(r29)
/* 800150C0 00011CA0  38 04 00 01 */	addi r0, r4, 1
/* 800150C4 00011CA4  90 1D 06 30 */	stw r0, 0x630(r29)
/* 800150C8 00011CA8  80 9D 06 30 */	lwz r4, 0x630(r29)
/* 800150CC 00011CAC  80 1D 06 34 */	lwz r0, 0x634(r29)
/* 800150D0 00011CB0  7C 04 00 00 */	cmpw r4, r0
/* 800150D4 00011CB4  40 81 00 08 */	ble lbMemory_800150DC
/* 800150D8 00011CB8  90 86 00 00 */	stw r4, 0(r6)
lbMemory_800150DC:
/* 800150DC 00011CBC  BB 01 00 18 */	lmw r24, 0x18(r1)
/* 800150E0 00011CC0  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 800150E4 00011CC4  38 21 00 38 */	addi r1, r1, 0x38
/* 800150E8 00011CC8  7C 08 03 A6 */	mtlr r0
/* 800150EC 00011CCC  4E 80 00 20 */	blr

.global lbMemory_800150F0
lbMemory_800150F0:
/* 800150F0 00011CD0  7C 08 02 A6 */	mflr r0
/* 800150F4 00011CD4  38 C3 00 0C */	addi r6, r3, 0xc
/* 800150F8 00011CD8  90 01 00 04 */	stw r0, 4(r1)
/* 800150FC 00011CDC  94 21 FF F8 */	stwu r1, -8(r1)
/* 80015100 00011CE0  80 A3 00 0C */	lwz r5, 0xc(r3)
/* 80015104 00011CE4  48 00 00 44 */	b lbMemory_80015148
lbMemory_80015108:
/* 80015108 00011CE8  80 05 00 04 */	lwz r0, 4(r5)
/* 8001510C 00011CEC  7C 00 20 40 */	cmplw r0, r4
/* 80015110 00011CF0  40 82 00 30 */	bne lbMemory_80015140
/* 80015114 00011CF4  80 05 00 00 */	lwz r0, 0(r5)
/* 80015118 00011CF8  3C 60 80 43 */	lis r3, lbl_804318B0@ha
/* 8001511C 00011CFC  38 83 18 B0 */	addi r4, r3, lbl_804318B0@l
/* 80015120 00011D00  90 06 00 00 */	stw r0, 0(r6)
/* 80015124 00011D04  80 04 06 2C */	lwz r0, 0x62c(r4)
/* 80015128 00011D08  90 05 00 00 */	stw r0, 0(r5)
/* 8001512C 00011D0C  90 A4 06 2C */	stw r5, 0x62c(r4)
/* 80015130 00011D10  80 64 06 30 */	lwz r3, 0x630(r4)
/* 80015134 00011D14  38 03 FF FF */	addi r0, r3, -1
/* 80015138 00011D18  90 04 06 30 */	stw r0, 0x630(r4)
/* 8001513C 00011D1C  48 00 00 38 */	b lbMemory_80015174
lbMemory_80015140:
/* 80015140 00011D20  7C A6 2B 78 */	mr r6, r5
/* 80015144 00011D24  80 A5 00 00 */	lwz r5, 0(r5)
lbMemory_80015148:
/* 80015148 00011D28  28 05 00 00 */	cmplwi r5, 0
/* 8001514C 00011D2C  40 82 FF BC */	bne lbMemory_80015108
/* 80015150 00011D30  3C 60 80 3C */	lis r3, lbl_803BA344@ha
/* 80015154 00011D34  4C C6 31 82 */	crclr 6
/* 80015158 00011D38  38 63 A3 44 */	addi r3, r3, lbl_803BA344@l
/* 8001515C 00011D3C  48 33 05 4D */	bl OSReport
/* 80015160 00011D40  3C 60 80 3C */	lis r3, lbl_803BA2C0@ha
/* 80015164 00011D44  38 63 A2 C0 */	addi r3, r3, lbl_803BA2C0@l
/* 80015168 00011D48  38 80 01 1B */	li r4, 0x11b
/* 8001516C 00011D4C  38 AD 80 F0 */	addi r5, r13, lbl_804D3790@sda21
/* 80015170 00011D50  48 37 30 B1 */	bl __assert
lbMemory_80015174:
/* 80015174 00011D54  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80015178 00011D58  38 21 00 08 */	addi r1, r1, 8
/* 8001517C 00011D5C  7C 08 03 A6 */	mtlr r0
/* 80015180 00011D60  4E 80 00 20 */	blr
lbMemory_80015184:
/* 80015184 00011D64  7C 08 02 A6 */	mflr r0
/* 80015188 00011D68  3C 60 80 43 */	lis r3, lbl_804318B0@ha
/* 8001518C 00011D6C  90 01 00 04 */	stw r0, 4(r1)
/* 80015190 00011D70  38 63 18 B0 */	addi r3, r3, lbl_804318B0@l
/* 80015194 00011D74  38 63 06 A0 */	addi r3, r3, 0x6a0
/* 80015198 00011D78  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8001519C 00011D7C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 800151A0 00011D80  3B E3 00 00 */	addi r31, r3, 0
/* 800151A4 00011D84  93 C1 00 10 */	stw r30, 0x10(r1)
/* 800151A8 00011D88  80 03 00 30 */	lwz r0, 0x30(r3)
/* 800151AC 00011D8C  28 00 00 00 */	cmplwi r0, 0
/* 800151B0 00011D90  40 82 00 18 */	bne lbMemory_800151C8
/* 800151B4 00011D94  3C 60 80 3C */	lis r3, lbl_803BA2C0@ha
/* 800151B8 00011D98  38 63 A2 C0 */	addi r3, r3, lbl_803BA2C0@l
/* 800151BC 00011D9C  38 80 01 27 */	li r4, 0x127
/* 800151C0 00011DA0  38 AD 80 F4 */	addi r5, r13, lbl_804D3794@sda21
/* 800151C4 00011DA4  48 37 30 5D */	bl __assert
lbMemory_800151C8:
/* 800151C8 00011DA8  80 DF 00 34 */	lwz r6, 0x34(r31)
/* 800151CC 00011DAC  3C 60 00 02 */	lis r3, 0x00019000@ha
/* 800151D0 00011DB0  80 9F 00 30 */	lwz r4, 0x30(r31)
/* 800151D4 00011DB4  38 03 90 00 */	addi r0, r3, 0x00019000@l
/* 800151D8 00011DB8  7C 66 20 50 */	subf r3, r6, r4
/* 800151DC 00011DBC  7C 03 00 40 */	cmplw r3, r0
/* 800151E0 00011DC0  3B C3 00 00 */	addi r30, r3, 0
/* 800151E4 00011DC4  40 81 00 08 */	ble lbMemory_800151EC
/* 800151E8 00011DC8  7C 1E 03 78 */	mr r30, r0
lbMemory_800151EC:
/* 800151EC 00011DCC  80 7F 00 2C */	lwz r3, 0x2c(r31)
/* 800151F0 00011DD0  7F C5 F3 78 */	mr r5, r30
/* 800151F4 00011DD4  80 1F 00 28 */	lwz r0, 0x28(r31)
/* 800151F8 00011DD8  7C 63 32 14 */	add r3, r3, r6
/* 800151FC 00011DDC  7C 80 32 14 */	add r4, r0, r6
/* 80015200 00011DE0  4B FE DF F5 */	bl memcpy
/* 80015204 00011DE4  80 1F 00 34 */	lwz r0, 0x34(r31)
/* 80015208 00011DE8  7C 00 F2 14 */	add r0, r0, r30
/* 8001520C 00011DEC  90 1F 00 34 */	stw r0, 0x34(r31)
/* 80015210 00011DF0  80 7F 00 34 */	lwz r3, 0x34(r31)
/* 80015214 00011DF4  80 1F 00 30 */	lwz r0, 0x30(r31)
/* 80015218 00011DF8  7C 03 00 40 */	cmplw r3, r0
/* 8001521C 00011DFC  40 82 00 2C */	bne lbMemory_80015248
/* 80015220 00011E00  38 00 00 00 */	li r0, 0
/* 80015224 00011E04  90 1F 00 30 */	stw r0, 0x30(r31)
/* 80015228 00011E08  38 60 00 00 */	li r3, 0
/* 8001522C 00011E0C  38 A0 00 00 */	li r5, 0
/* 80015230 00011E10  81 9F 00 3C */	lwz r12, 0x3c(r31)
/* 80015234 00011E14  38 C0 00 00 */	li r6, 0
/* 80015238 00011E18  80 9F 00 38 */	lwz r4, 0x38(r31)
/* 8001523C 00011E1C  7D 88 03 A6 */	mtlr r12
/* 80015240 00011E20  4E 80 00 21 */	blrl
/* 80015244 00011E24  48 00 00 40 */	b lbMemory_80015284
lbMemory_80015248:
/* 80015248 00011E28  7F E3 FB 78 */	mr r3, r31
/* 8001524C 00011E2C  48 32 E5 21 */	bl OSCreateAlarm
/* 80015250 00011E30  3C 60 80 00 */	lis r3, 0x800000F8@ha
/* 80015254 00011E34  80 03 00 F8 */	lwz r0, 0x800000F8@l(r3)
/* 80015258 00011E38  3C 80 10 62 */	lis r4, 0x10624DD3@ha
/* 8001525C 00011E3C  3C 60 80 01 */	lis r3, lbMemory_80015184@ha
/* 80015260 00011E40  54 00 F0 BE */	srwi r0, r0, 2
/* 80015264 00011E44  38 84 4D D3 */	addi r4, r4, 0x10624DD3@l
/* 80015268 00011E48  7C 04 00 16 */	mulhwu r0, r4, r0
/* 8001526C 00011E4C  54 00 D1 BE */	srwi r0, r0, 6
/* 80015270 00011E50  1C C0 00 03 */	mulli r6, r0, 3
/* 80015274 00011E54  38 E3 51 84 */	addi r7, r3, lbMemory_80015184@l
/* 80015278 00011E58  38 7F 00 00 */	addi r3, r31, 0
/* 8001527C 00011E5C  38 A0 00 00 */	li r5, 0
/* 80015280 00011E60  48 32 E7 49 */	bl OSSetAlarm
lbMemory_80015284:
/* 80015284 00011E64  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80015288 00011E68  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8001528C 00011E6C  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 80015290 00011E70  38 21 00 18 */	addi r1, r1, 0x18
/* 80015294 00011E74  7C 08 03 A6 */	mtlr r0
/* 80015298 00011E78  4E 80 00 20 */	blr

.global lbMemory_8001529C
lbMemory_8001529C:
/* 8001529C 00011E7C  7C 08 02 A6 */	mflr r0
/* 800152A0 00011E80  3C C0 80 43 */	lis r6, lbl_804318B0@ha
/* 800152A4 00011E84  90 01 00 04 */	stw r0, 4(r1)
/* 800152A8 00011E88  38 C6 18 B0 */	addi r6, r6, lbl_804318B0@l
/* 800152AC 00011E8C  38 E6 06 E4 */	addi r7, r6, 0x6e4
/* 800152B0 00011E90  94 21 FF F8 */	stwu r1, -8(r1)
/* 800152B4 00011E94  90 86 06 E8 */	stw r4, 0x6e8(r6)
/* 800152B8 00011E98  90 A6 06 E0 */	stw r5, 0x6e0(r6)
/* 800152BC 00011E9C  80 03 00 04 */	lwz r0, 4(r3)
/* 800152C0 00011EA0  90 06 06 E4 */	stw r0, 0x6e4(r6)
/* 800152C4 00011EA4  80 83 00 0C */	lwz r4, 0xc(r3)
/* 800152C8 00011EA8  48 00 00 3C */	b lbMemory_80015304
lbMemory_800152CC:
/* 800152CC 00011EAC  80 64 00 04 */	lwz r3, 4(r4)
/* 800152D0 00011EB0  80 07 00 00 */	lwz r0, 0(r7)
/* 800152D4 00011EB4  7C 03 00 40 */	cmplw r3, r0
/* 800152D8 00011EB8  41 82 00 1C */	beq lbMemory_800152F4
/* 800152DC 00011EBC  38 60 00 00 */	li r3, 0
/* 800152E0 00011EC0  38 A0 00 00 */	li r5, 0
/* 800152E4 00011EC4  38 C0 00 00 */	li r6, 0
/* 800152E8 00011EC8  48 00 00 39 */	bl lbMemory_80015320
/* 800152EC 00011ECC  38 60 00 01 */	li r3, 1
/* 800152F0 00011ED0  48 00 00 20 */	b lbMemory_80015310
lbMemory_800152F4:
/* 800152F4 00011ED4  80 04 00 08 */	lwz r0, 8(r4)
/* 800152F8 00011ED8  7C 03 02 14 */	add r0, r3, r0
/* 800152FC 00011EDC  90 07 00 00 */	stw r0, 0(r7)
/* 80015300 00011EE0  80 84 00 00 */	lwz r4, 0(r4)
lbMemory_80015304:
/* 80015304 00011EE4  28 04 00 00 */	cmplwi r4, 0
/* 80015308 00011EE8  40 82 FF C4 */	bne lbMemory_800152CC
/* 8001530C 00011EEC  38 60 00 00 */	li r3, 0
lbMemory_80015310:
/* 80015310 00011EF0  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80015314 00011EF4  38 21 00 08 */	addi r1, r1, 8
/* 80015318 00011EF8  7C 08 03 A6 */	mtlr r0
/* 8001531C 00011EFC  4E 80 00 20 */	blr

.global lbMemory_80015320
lbMemory_80015320:
/* 80015320 00011F00  7C 08 02 A6 */	mflr r0
/* 80015324 00011F04  3C 60 80 43 */	lis r3, lbl_804318B0@ha
/* 80015328 00011F08  90 01 00 04 */	stw r0, 4(r1)
/* 8001532C 00011F0C  2C 06 00 00 */	cmpwi r6, 0
/* 80015330 00011F10  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 80015334 00011F14  BF 21 00 1C */	stmw r25, 0x1c(r1)
/* 80015338 00011F18  3B C3 18 B0 */	addi r30, r3, lbl_804318B0@l
/* 8001533C 00011F1C  3C 60 80 3C */	lis r3, lbl_803BA2C0@ha
/* 80015340 00011F20  3B 3E 06 E4 */	addi r25, r30, 0x6e4
/* 80015344 00011F24  3B 63 A2 C0 */	addi r27, r3, lbl_803BA2C0@l
/* 80015348 00011F28  3B 84 00 00 */	addi r28, r4, 0
/* 8001534C 00011F2C  83 BE 06 E4 */	lwz r29, 0x6e4(r30)
/* 80015350 00011F30  41 82 00 14 */	beq lbMemory_80015364
/* 80015354 00011F34  38 7B 00 00 */	addi r3, r27, 0
/* 80015358 00011F38  38 BB 00 B4 */	addi r5, r27, 0xb4
/* 8001535C 00011F3C  38 80 01 88 */	li r4, 0x188
/* 80015360 00011F40  48 37 2E C1 */	bl __assert
lbMemory_80015364:
/* 80015364 00011F44  28 1C 00 00 */	cmplwi r28, 0
/* 80015368 00011F48  41 82 01 30 */	beq lbMemory_80015498
/* 8001536C 00011F4C  83 FC 00 04 */	lwz r31, 4(r28)
/* 80015370 00011F50  7C 1F E8 40 */	cmplw r31, r29
/* 80015374 00011F54  41 82 01 00 */	beq lbMemory_80015474
/* 80015378 00011F58  93 BC 00 04 */	stw r29, 4(r28)
/* 8001537C 00011F5C  3C 00 80 00 */	lis r0, 0x8000
/* 80015380 00011F60  38 9F 00 00 */	addi r4, r31, 0
/* 80015384 00011F64  80 BC 00 04 */	lwz r5, 4(r28)
/* 80015388 00011F68  80 7C 00 08 */	lwz r3, 8(r28)
/* 8001538C 00011F6C  7C 65 1A 14 */	add r3, r5, r3
/* 80015390 00011F70  90 79 00 00 */	stw r3, 0(r25)
/* 80015394 00011F74  80 7C 00 04 */	lwz r3, 4(r28)
/* 80015398 00011F78  7C 03 00 40 */	cmplw r3, r0
/* 8001539C 00011F7C  40 80 00 34 */	bge lbMemory_800153D0
/* 800153A0 00011F80  80 BC 00 08 */	lwz r5, 8(r28)
/* 800153A4 00011F84  3C 60 80 01 */	lis r3, lbMemory_80015320@ha
/* 800153A8 00011F88  39 23 53 20 */	addi r9, r3, lbMemory_80015320@l
/* 800153AC 00011F8C  81 5C 00 00 */	lwz r10, 0(r28)
/* 800153B0 00011F90  38 05 00 1F */	addi r0, r5, 0x1f
/* 800153B4 00011F94  38 BD 00 00 */	addi r5, r29, 0
/* 800153B8 00011F98  54 06 00 34 */	rlwinm r6, r0, 0, 0, 0x1a
/* 800153BC 00011F9C  38 60 00 00 */	li r3, 0
/* 800153C0 00011FA0  38 E0 00 1B */	li r7, 0x1b
/* 800153C4 00011FA4  39 00 00 01 */	li r8, 1
/* 800153C8 00011FA8  48 37 A3 0D */	bl HSD_DevComRequest
/* 800153CC 00011FAC  48 00 00 DC */	b lbMemory_800154A8
lbMemory_800153D0:
/* 800153D0 00011FB0  80 7C 00 08 */	lwz r3, 8(r28)
/* 800153D4 00011FB4  3B DE 06 A0 */	addi r30, r30, 0x6a0
/* 800153D8 00011FB8  83 3C 00 00 */	lwz r25, 0(r28)
/* 800153DC 00011FBC  38 03 00 1F */	addi r0, r3, 0x1f
/* 800153E0 00011FC0  54 1A 00 34 */	rlwinm r26, r0, 0, 0, 0x1a
/* 800153E4 00011FC4  48 33 1F 81 */	bl OSDisableInterrupts
/* 800153E8 00011FC8  80 1E 00 30 */	lwz r0, 0x30(r30)
/* 800153EC 00011FCC  3B 83 00 00 */	addi r28, r3, 0
/* 800153F0 00011FD0  28 00 00 00 */	cmplwi r0, 0
/* 800153F4 00011FD4  41 82 00 14 */	beq lbMemory_80015408
/* 800153F8 00011FD8  38 7B 00 00 */	addi r3, r27, 0
/* 800153FC 00011FDC  38 BB 00 A8 */	addi r5, r27, 0xa8
/* 80015400 00011FE0  38 80 01 4F */	li r4, 0x14f
/* 80015404 00011FE4  48 37 2E 1D */	bl __assert
lbMemory_80015408:
/* 80015408 00011FE8  93 FE 00 28 */	stw r31, 0x28(r30)
/* 8001540C 00011FEC  3C 60 80 01 */	lis r3, lbMemory_80015320@ha
/* 80015410 00011FF0  38 80 00 00 */	li r4, 0
/* 80015414 00011FF4  93 BE 00 2C */	stw r29, 0x2c(r30)
/* 80015418 00011FF8  38 03 53 20 */	addi r0, r3, lbMemory_80015320@l
/* 8001541C 00011FFC  38 7C 00 00 */	addi r3, r28, 0
/* 80015420 00012000  93 5E 00 30 */	stw r26, 0x30(r30)
/* 80015424 00012004  90 9E 00 34 */	stw r4, 0x34(r30)
/* 80015428 00012008  93 3E 00 38 */	stw r25, 0x38(r30)
/* 8001542C 0001200C  90 1E 00 3C */	stw r0, 0x3c(r30)
/* 80015430 00012010  48 33 1F 5D */	bl OSRestoreInterrupts
/* 80015434 00012014  7F C3 F3 78 */	mr r3, r30
/* 80015438 00012018  48 32 E3 35 */	bl OSCreateAlarm
/* 8001543C 0001201C  3C 60 80 00 */	lis r3, 0x800000F8@ha
/* 80015440 00012020  80 03 00 F8 */	lwz r0, 0x800000F8@l(r3)
/* 80015444 00012024  3C 80 10 62 */	lis r4, 0x10624DD3@ha
/* 80015448 00012028  3C 60 80 01 */	lis r3, lbMemory_80015184@ha
/* 8001544C 0001202C  54 00 F0 BE */	srwi r0, r0, 2
/* 80015450 00012030  38 84 4D D3 */	addi r4, r4, 0x10624DD3@l
/* 80015454 00012034  7C 04 00 16 */	mulhwu r0, r4, r0
/* 80015458 00012038  54 00 D1 BE */	srwi r0, r0, 6
/* 8001545C 0001203C  1C C0 00 03 */	mulli r6, r0, 3
/* 80015460 00012040  38 E3 51 84 */	addi r7, r3, lbMemory_80015184@l
/* 80015464 00012044  38 7E 00 00 */	addi r3, r30, 0
/* 80015468 00012048  38 A0 00 00 */	li r5, 0
/* 8001546C 0001204C  48 32 E5 5D */	bl OSSetAlarm
/* 80015470 00012050  48 00 00 38 */	b lbMemory_800154A8
lbMemory_80015474:
/* 80015474 00012054  80 1C 00 08 */	lwz r0, 8(r28)
/* 80015478 00012058  38 60 00 00 */	li r3, 0
/* 8001547C 0001205C  38 A0 00 00 */	li r5, 0
/* 80015480 00012060  7C 1F 02 14 */	add r0, r31, r0
/* 80015484 00012064  90 19 00 00 */	stw r0, 0(r25)
/* 80015488 00012068  38 C0 00 00 */	li r6, 0
/* 8001548C 0001206C  80 9C 00 00 */	lwz r4, 0(r28)
/* 80015490 00012070  4B FF FE 91 */	bl lbMemory_80015320
/* 80015494 00012074  48 00 00 14 */	b lbMemory_800154A8
lbMemory_80015498:
/* 80015498 00012078  81 9E 06 E8 */	lwz r12, 0x6e8(r30)
/* 8001549C 0001207C  80 7E 06 E0 */	lwz r3, 0x6e0(r30)
/* 800154A0 00012080  7D 88 03 A6 */	mtlr r12
/* 800154A4 00012084  4E 80 00 21 */	blrl
lbMemory_800154A8:
/* 800154A8 00012088  BB 21 00 1C */	lmw r25, 0x1c(r1)
/* 800154AC 0001208C  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 800154B0 00012090  38 21 00 38 */	addi r1, r1, 0x38
/* 800154B4 00012094  7C 08 03 A6 */	mtlr r0
/* 800154B8 00012098  4E 80 00 20 */	blr

.global lbMemory_800154BC
lbMemory_800154BC:
/* 800154BC 0001209C  3C A0 80 43 */	lis r5, lbl_804318B0@ha
/* 800154C0 000120A0  84 05 18 B0 */	lwzu r0, lbl_804318B0@l(r5)
/* 800154C4 000120A4  90 03 00 00 */	stw r0, 0(r3)
/* 800154C8 000120A8  80 05 00 04 */	lwz r0, 0x4(r5)
/* 800154CC 000120AC  90 04 00 00 */	stw r0, 0(r4)
/* 800154D0 000120B0  4E 80 00 20 */	blr

.global lbMemory_800154D4
lbMemory_800154D4:
/* 800154D4 000120B4  7C 08 02 A6 */	mflr r0
/* 800154D8 000120B8  3C A0 80 43 */	lis r5, lbl_804318B0@ha
/* 800154DC 000120BC  90 01 00 04 */	stw r0, 4(r1)
/* 800154E0 000120C0  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 800154E4 000120C4  BF 61 00 1C */	stmw r27, 0x1c(r1)
/* 800154E8 000120C8  3B E5 18 B0 */	addi r31, r5, lbl_804318B0@l
/* 800154EC 000120CC  3C A0 80 3C */	lis r5, lbl_803BA2C0@ha
/* 800154F0 000120D0  3B BF 06 98 */	addi r29, r31, 0x698
/* 800154F4 000120D4  3B C5 A2 C0 */	addi r30, r5, lbl_803BA2C0@l
/* 800154F8 000120D8  3B 63 00 00 */	addi r27, r3, 0
/* 800154FC 000120DC  3B 84 00 00 */	addi r28, r4, 0
/* 80015500 000120E0  80 1F 06 98 */	lwz r0, 0x698(r31)
/* 80015504 000120E4  28 00 00 00 */	cmplwi r0, 0
/* 80015508 000120E8  40 82 00 14 */	bne lbMemory_8001551C
/* 8001550C 000120EC  38 7E 00 00 */	addi r3, r30, 0
/* 80015510 000120F0  38 BE 00 0C */	addi r5, r30, 0xc
/* 80015514 000120F4  38 80 00 7B */	li r4, 0x7b
/* 80015518 000120F8  48 37 2D 09 */	bl __assert
lbMemory_8001551C:
/* 8001551C 000120FC  3C 00 80 00 */	lis r0, 0x8000
/* 80015520 00012100  7C 1B 00 40 */	cmplw r27, r0
/* 80015524 00012104  40 80 00 44 */	bge lbMemory_80015568
/* 80015528 00012108  7C 1C 00 40 */	cmplw r28, r0
/* 8001552C 0001210C  40 80 00 3C */	bge lbMemory_80015568
/* 80015530 00012110  80 1F 00 00 */	lwz r0, 0(r31)
/* 80015534 00012114  38 60 00 00 */	li r3, 0
/* 80015538 00012118  7C 1B 00 40 */	cmplw r27, r0
/* 8001553C 0001211C  41 80 00 14 */	blt lbMemory_80015550
/* 80015540 00012120  80 1F 00 04 */	lwz r0, 4(r31)
/* 80015544 00012124  7C 1C 00 40 */	cmplw r28, r0
/* 80015548 00012128  41 81 00 08 */	bgt lbMemory_80015550
/* 8001554C 0001212C  38 60 00 01 */	li r3, 1
lbMemory_80015550:
/* 80015550 00012130  2C 03 00 00 */	cmpwi r3, 0
/* 80015554 00012134  40 82 00 14 */	bne lbMemory_80015568
/* 80015558 00012138  38 7E 00 00 */	addi r3, r30, 0
/* 8001555C 0001213C  38 BE 00 1C */	addi r5, r30, 0x1c
/* 80015560 00012140  38 80 00 80 */	li r4, 0x80
/* 80015564 00012144  48 37 2C BD */	bl __assert
lbMemory_80015568:
/* 80015568 00012148  80 9D 00 00 */	lwz r4, 0(r29)
/* 8001556C 0001214C  38 00 00 00 */	li r0, 0
/* 80015570 00012150  80 64 00 00 */	lwz r3, 0(r4)
/* 80015574 00012154  90 7D 00 00 */	stw r3, 0(r29)
/* 80015578 00012158  90 04 00 00 */	stw r0, 0(r4)
/* 8001557C 0001215C  93 64 00 04 */	stw r27, 4(r4)
/* 80015580 00012160  93 84 00 08 */	stw r28, 8(r4)
/* 80015584 00012164  90 04 00 0C */	stw r0, 0xc(r4)
/* 80015588 00012168  90 9F 06 9C */	stw r4, 0x69c(r31)
/* 8001558C 0001216C  80 7F 06 9C */	lwz r3, 0x69c(r31)
/* 80015590 00012170  BB 61 00 1C */	lmw r27, 0x1c(r1)
/* 80015594 00012174  80 01 00 34 */	lwz r0, 0x34(r1)
/* 80015598 00012178  38 21 00 30 */	addi r1, r1, 0x30
/* 8001559C 0001217C  7C 08 03 A6 */	mtlr r0
/* 800155A0 00012180  4E 80 00 20 */	blr

.global lbMemory_800155A4
lbMemory_800155A4:
/* 800155A4 00012184  7C 08 02 A6 */	mflr r0
/* 800155A8 00012188  3C 60 80 43 */	lis r3, lbl_804318B0@ha
/* 800155AC 0001218C  90 01 00 04 */	stw r0, 4(r1)
/* 800155B0 00012190  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 800155B4 00012194  93 E1 00 14 */	stw r31, 0x14(r1)
/* 800155B8 00012198  3B E3 18 B0 */	addi r31, r3, lbl_804318B0@l
/* 800155BC 0001219C  93 C1 00 10 */	stw r30, 0x10(r1)
/* 800155C0 000121A0  93 A1 00 0C */	stw r29, 0xc(r1)
/* 800155C4 000121A4  3B BF 06 9C */	addi r29, r31, 0x69c
/* 800155C8 000121A8  83 DF 06 9C */	lwz r30, 0x69c(r31)
/* 800155CC 000121AC  28 1E 00 00 */	cmplwi r30, 0
/* 800155D0 000121B0  40 82 00 18 */	bne lbMemory_800155E8
/* 800155D4 000121B4  3C 60 80 3C */	lis r3, lbl_803BA2C0@ha
/* 800155D8 000121B8  38 63 A2 C0 */	addi r3, r3, lbl_803BA2C0@l
/* 800155DC 000121BC  38 80 00 95 */	li r4, 0x95
/* 800155E0 000121C0  38 AD 80 E8 */	addi r5, r13, lbl_804D3788@sda21
/* 800155E4 000121C4  48 37 2C 3D */	bl __assert
lbMemory_800155E8:
/* 800155E8 000121C8  80 9E 00 0C */	lwz r4, 0xc(r30)
/* 800155EC 000121CC  38 BF 06 2C */	addi r5, r31, 0x62c
/* 800155F0 000121D0  48 00 00 24 */	b lbMemory_80015614
lbMemory_800155F4:
/* 800155F4 000121D4  80 64 00 00 */	lwz r3, 0(r4)
/* 800155F8 000121D8  80 05 00 00 */	lwz r0, 0(r5)
/* 800155FC 000121DC  90 04 00 00 */	stw r0, 0(r4)
/* 80015600 000121E0  90 85 00 00 */	stw r4, 0(r5)
/* 80015604 000121E4  7C 64 1B 78 */	mr r4, r3
/* 80015608 000121E8  80 7F 06 30 */	lwz r3, 0x630(r31)
/* 8001560C 000121EC  38 03 FF FF */	addi r0, r3, -1
/* 80015610 000121F0  90 1F 06 30 */	stw r0, 0x630(r31)
lbMemory_80015614:
/* 80015614 000121F4  28 04 00 00 */	cmplwi r4, 0
/* 80015618 000121F8  40 82 FF DC */	bne lbMemory_800155F4
/* 8001561C 000121FC  80 7F 06 98 */	lwz r3, 0x698(r31)
/* 80015620 00012200  38 00 00 00 */	li r0, 0
/* 80015624 00012204  90 7E 00 00 */	stw r3, 0(r30)
/* 80015628 00012208  93 DF 06 98 */	stw r30, 0x698(r31)
/* 8001562C 0001220C  90 1D 00 00 */	stw r0, 0(r29)
/* 80015630 00012210  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80015634 00012214  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80015638 00012218  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8001563C 0001221C  83 A1 00 0C */	lwz r29, 0xc(r1)
/* 80015640 00012220  38 21 00 18 */	addi r1, r1, 0x18
/* 80015644 00012224  7C 08 03 A6 */	mtlr r0
/* 80015648 00012228  4E 80 00 20 */	blr

.global lbMemory_8001564C
lbMemory_8001564C:
/* 8001564C 0001222C  7C 08 02 A6 */	mflr r0
/* 80015650 00012230  3C 60 80 43 */	lis r3, lbl_804318B0@ha
/* 80015654 00012234  90 01 00 04 */	stw r0, 4(r1)
/* 80015658 00012238  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8001565C 0001223C  93 E1 00 24 */	stw r31, 0x24(r1)
/* 80015660 00012240  3B E3 18 B0 */	addi r31, r3, lbl_804318B0@l
/* 80015664 00012244  38 60 00 20 */	li r3, 0x20
/* 80015668 00012248  93 C1 00 20 */	stw r30, 0x20(r1)
/* 8001566C 0001224C  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 80015670 00012250  48 33 B7 51 */	bl ARAlloc
/* 80015674 00012254  90 7F 00 00 */	stw r3, 0(r31)
/* 80015678 00012258  38 61 00 14 */	addi r3, r1, 0x14
/* 8001567C 0001225C  48 33 B7 AD */	bl ARFree
/* 80015680 00012260  48 33 B9 11 */	bl ARGetSize
/* 80015684 00012264  3C 00 01 00 */	lis r0, 0x100
/* 80015688 00012268  7C 03 00 40 */	cmplw r3, r0
/* 8001568C 0001226C  40 81 00 08 */	ble lbMemory_80015694
/* 80015690 00012270  48 00 00 0C */	b lbMemory_8001569C
lbMemory_80015694:
/* 80015694 00012274  48 33 B8 FD */	bl ARGetSize
/* 80015698 00012278  7C 60 1B 78 */	mr r0, r3
lbMemory_8001569C:
/* 8001569C 0001227C  90 1F 00 04 */	stw r0, 4(r31)
/* 800156A0 00012280  38 7F 00 08 */	addi r3, r31, 8
/* 800156A4 00012284  38 00 00 08 */	li r0, 8
/* 800156A8 00012288  90 7F 06 2C */	stw r3, 0x62c(r31)
/* 800156AC 0001228C  7C 09 03 A6 */	mtctr r0
/* 800156B0 00012290  38 9F 00 04 */	addi r4, r31, 4
/* 800156B4 00012294  38 7F 00 00 */	addi r3, r31, 0
/* 800156B8 00012298  38 A0 00 00 */	li r5, 0
lbMemory_800156BC:
/* 800156BC 0001229C  38 05 00 01 */	addi r0, r5, 1
/* 800156C0 000122A0  1D 00 00 0C */	mulli r8, r0, 0xc
/* 800156C4 000122A4  38 C5 00 02 */	addi r6, r5, 2
/* 800156C8 000122A8  1C E6 00 0C */	mulli r7, r6, 0xc
/* 800156CC 000122AC  3B C8 00 08 */	addi r30, r8, 8
/* 800156D0 000122B0  38 05 00 03 */	addi r0, r5, 3
/* 800156D4 000122B4  1C C0 00 0C */	mulli r6, r0, 0xc
/* 800156D8 000122B8  7F DF F2 14 */	add r30, r31, r30
/* 800156DC 000122BC  39 87 00 08 */	addi r12, r7, 8
/* 800156E0 000122C0  93 C3 00 08 */	stw r30, 8(r3)
/* 800156E4 000122C4  38 05 00 04 */	addi r0, r5, 4
/* 800156E8 000122C8  1C E0 00 0C */	mulli r7, r0, 0xc
/* 800156EC 000122CC  7D 9F 62 14 */	add r12, r31, r12
/* 800156F0 000122D0  39 66 00 08 */	addi r11, r6, 8
/* 800156F4 000122D4  91 83 00 14 */	stw r12, 0x14(r3)
/* 800156F8 000122D8  38 05 00 05 */	addi r0, r5, 5
/* 800156FC 000122DC  1C C0 00 0C */	mulli r6, r0, 0xc
/* 80015700 000122E0  39 26 00 08 */	addi r9, r6, 8
/* 80015704 000122E4  7D 7F 5A 14 */	add r11, r31, r11
/* 80015708 000122E8  39 47 00 08 */	addi r10, r7, 8
/* 8001570C 000122EC  91 63 00 20 */	stw r11, 0x20(r3)
/* 80015710 000122F0  38 05 00 06 */	addi r0, r5, 6
/* 80015714 000122F4  1D 00 00 0C */	mulli r8, r0, 0xc
/* 80015718 000122F8  7D 5F 52 14 */	add r10, r31, r10
/* 8001571C 000122FC  38 C5 00 07 */	addi r6, r5, 7
/* 80015720 00012300  91 43 00 2C */	stw r10, 0x2c(r3)
/* 80015724 00012304  1C E6 00 0C */	mulli r7, r6, 0xc
/* 80015728 00012308  7D 3F 4A 14 */	add r9, r31, r9
/* 8001572C 0001230C  38 05 00 08 */	addi r0, r5, 8
/* 80015730 00012310  91 23 00 38 */	stw r9, 0x38(r3)
/* 80015734 00012314  39 08 00 08 */	addi r8, r8, 8
/* 80015738 00012318  1C C0 00 0C */	mulli r6, r0, 0xc
/* 8001573C 0001231C  7D 1F 42 14 */	add r8, r31, r8
/* 80015740 00012320  38 E7 00 08 */	addi r7, r7, 8
/* 80015744 00012324  91 03 00 44 */	stw r8, 0x44(r3)
/* 80015748 00012328  38 05 00 09 */	addi r0, r5, 9
/* 8001574C 0001232C  1D 00 00 0C */	mulli r8, r0, 0xc
/* 80015750 00012330  38 06 00 08 */	addi r0, r6, 8
/* 80015754 00012334  7C FF 3A 14 */	add r7, r31, r7
/* 80015758 00012338  3B C8 00 08 */	addi r30, r8, 8
/* 8001575C 0001233C  90 E3 00 50 */	stw r7, 0x50(r3)
/* 80015760 00012340  38 C5 00 0A */	addi r6, r5, 0xa
/* 80015764 00012344  7C 1F 02 14 */	add r0, r31, r0
/* 80015768 00012348  1C E6 00 0C */	mulli r7, r6, 0xc
/* 8001576C 0001234C  90 03 00 5C */	stw r0, 0x5c(r3)
/* 80015770 00012350  38 05 00 0B */	addi r0, r5, 0xb
/* 80015774 00012354  1C C0 00 0C */	mulli r6, r0, 0xc
/* 80015778 00012358  7F DF F2 14 */	add r30, r31, r30
/* 8001577C 0001235C  39 87 00 08 */	addi r12, r7, 8
/* 80015780 00012360  93 C3 00 68 */	stw r30, 0x68(r3)
/* 80015784 00012364  38 05 00 0C */	addi r0, r5, 0xc
/* 80015788 00012368  1C E0 00 0C */	mulli r7, r0, 0xc
/* 8001578C 0001236C  7D 9F 62 14 */	add r12, r31, r12
/* 80015790 00012370  39 66 00 08 */	addi r11, r6, 8
/* 80015794 00012374  91 83 00 74 */	stw r12, 0x74(r3)
/* 80015798 00012378  38 05 00 0D */	addi r0, r5, 0xd
/* 8001579C 0001237C  1C C0 00 0C */	mulli r6, r0, 0xc
/* 800157A0 00012380  39 26 00 08 */	addi r9, r6, 8
/* 800157A4 00012384  7D 7F 5A 14 */	add r11, r31, r11
/* 800157A8 00012388  39 47 00 08 */	addi r10, r7, 8
/* 800157AC 0001238C  91 63 00 80 */	stw r11, 0x80(r3)
/* 800157B0 00012390  38 05 00 0E */	addi r0, r5, 0xe
/* 800157B4 00012394  1D 00 00 0C */	mulli r8, r0, 0xc
/* 800157B8 00012398  7D 5F 52 14 */	add r10, r31, r10
/* 800157BC 0001239C  38 C5 00 0F */	addi r6, r5, 0xf
/* 800157C0 000123A0  91 43 00 8C */	stw r10, 0x8c(r3)
/* 800157C4 000123A4  1C E6 00 0C */	mulli r7, r6, 0xc
/* 800157C8 000123A8  38 05 00 10 */	addi r0, r5, 0x10
/* 800157CC 000123AC  7D 3F 4A 14 */	add r9, r31, r9
/* 800157D0 000123B0  39 08 00 08 */	addi r8, r8, 8
/* 800157D4 000123B4  91 23 00 98 */	stw r9, 0x98(r3)
/* 800157D8 000123B8  1C C0 00 0C */	mulli r6, r0, 0xc
/* 800157DC 000123BC  7D 1F 42 14 */	add r8, r31, r8
/* 800157E0 000123C0  38 E7 00 08 */	addi r7, r7, 8
/* 800157E4 000123C4  91 03 00 A4 */	stw r8, 0xa4(r3)
/* 800157E8 000123C8  7C FF 3A 14 */	add r7, r31, r7
/* 800157EC 000123CC  38 06 00 08 */	addi r0, r6, 8
/* 800157F0 000123D0  90 E3 00 B0 */	stw r7, 0xb0(r3)
/* 800157F4 000123D4  7C 1F 02 14 */	add r0, r31, r0
/* 800157F8 000123D8  90 03 00 BC */	stw r0, 0xbc(r3)
/* 800157FC 000123DC  38 63 00 C0 */	addi r3, r3, 0xc0
/* 80015800 000123E0  38 A5 00 10 */	addi r5, r5, 0x10
/* 80015804 000123E4  42 00 FE B8 */	bdnz lbMemory_800156BC
/* 80015808 000123E8  48 00 00 A0 */	b lbMemory_800158A8
lbMemory_8001580C:
/* 8001580C 000123EC  20 05 00 82 */	subfic r0, r5, 0x82
/* 80015810 000123F0  2C 05 00 82 */	cmpwi r5, 0x82
/* 80015814 000123F4  7C 09 03 A6 */	mtctr r0
/* 80015818 000123F8  40 80 00 24 */	bge lbMemory_8001583C
lbMemory_8001581C:
/* 8001581C 000123FC  38 05 00 01 */	addi r0, r5, 1
/* 80015820 00012400  1C 60 00 0C */	mulli r3, r0, 0xc
/* 80015824 00012404  38 03 00 08 */	addi r0, r3, 8
/* 80015828 00012408  7C 1F 02 14 */	add r0, r31, r0
/* 8001582C 0001240C  90 06 00 08 */	stw r0, 8(r6)
/* 80015830 00012410  38 C6 00 0C */	addi r6, r6, 0xc
/* 80015834 00012414  38 A5 00 01 */	addi r5, r5, 1
/* 80015838 00012418  42 00 FF E4 */	bdnz lbMemory_8001581C
lbMemory_8001583C:
/* 8001583C 0001241C  1C 05 00 0C */	mulli r0, r5, 0xc
/* 80015840 00012420  7C 7F 02 14 */	add r3, r31, r0
/* 80015844 00012424  3B C0 00 00 */	li r30, 0
/* 80015848 00012428  93 C3 00 08 */	stw r30, 8(r3)
/* 8001584C 0001242C  39 1F 06 38 */	addi r8, r31, 0x638
/* 80015850 00012430  38 FF 06 48 */	addi r7, r31, 0x648
/* 80015854 00012434  93 DF 06 34 */	stw r30, 0x634(r31)
/* 80015858 00012438  38 DF 06 58 */	addi r6, r31, 0x658
/* 8001585C 0001243C  38 BF 06 68 */	addi r5, r31, 0x668
/* 80015860 00012440  93 DF 06 30 */	stw r30, 0x630(r31)
/* 80015864 00012444  38 7F 06 78 */	addi r3, r31, 0x678
/* 80015868 00012448  38 1F 06 88 */	addi r0, r31, 0x688
/* 8001586C 0001244C  91 1F 06 98 */	stw r8, 0x698(r31)
/* 80015870 00012450  3B BF 06 9C */	addi r29, r31, 0x69c
/* 80015874 00012454  90 FF 06 38 */	stw r7, 0x638(r31)
/* 80015878 00012458  90 DF 06 48 */	stw r6, 0x648(r31)
/* 8001587C 0001245C  90 BF 06 58 */	stw r5, 0x658(r31)
/* 80015880 00012460  90 7F 06 68 */	stw r3, 0x668(r31)
/* 80015884 00012464  90 1F 06 78 */	stw r0, 0x678(r31)
/* 80015888 00012468  93 DF 06 88 */	stw r30, 0x688(r31)
/* 8001588C 0001246C  93 DF 06 9C */	stw r30, 0x69c(r31)
/* 80015890 00012470  80 84 00 00 */	lwz r4, 0(r4)
/* 80015894 00012474  80 7F 00 00 */	lwz r3, 0(r31)
/* 80015898 00012478  4B FF F5 8D */	bl lbMemory_80014E24
/* 8001589C 0001247C  90 7D 00 00 */	stw r3, 0(r29)
/* 800158A0 00012480  93 DF 06 D0 */	stw r30, 0x6d0(r31)
/* 800158A4 00012484  48 00 00 10 */	b lbMemory_800158B4
lbMemory_800158A8:
/* 800158A8 00012488  1C 05 00 0C */	mulli r0, r5, 0xc
/* 800158AC 0001248C  7C DF 02 14 */	add r6, r31, r0
/* 800158B0 00012490  4B FF FF 5C */	b lbMemory_8001580C
lbMemory_800158B4:
/* 800158B4 00012494  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 800158B8 00012498  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 800158BC 0001249C  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 800158C0 000124A0  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 800158C4 000124A4  38 21 00 28 */	addi r1, r1, 0x28
/* 800158C8 000124A8  7C 08 03 A6 */	mtlr r0
/* 800158CC 000124AC  4E 80 00 20 */	blr


.section .bss, "wa"
    .balign 8
.global lbl_804318B0
lbl_804318B0:
    .skip 0x6F0


.section .data
    .balign 8
.global lbl_803BA2C0
lbl_803BA2C0:
    .asciz "lbmemory.c"
    .balign 4
    .asciz "_p(free_heap)"
    .balign 4
    .asciz "(u32)arenaLo >= (u32)_p(a_arenaLo) && (u32)arenaHi <= (u32)_p(a_arenaHi)"
    .balign 4
    .asciz "_p(free_mem)"
    .balign 4
    .asciz "memp_kouho"
    .balign 4
.global lbl_803BA344
lbl_803BA344:
    .asciz "[LbMem] Error: lbMemFreeToHeap %x.\n"
    .balign 4
    .asciz "!p->size"
    .balign 4
    .asciz "!cancelflag"


.section .sdata
    .balign 8
.global lbl_804D3788
lbl_804D3788:
    .asciz "handle"
    .balign 4
.global lbl_804D3790
lbl_804D3790:
    .asciz "0"
    .balign 4
.global lbl_804D3794
lbl_804D3794:
    .asciz "p->size"
