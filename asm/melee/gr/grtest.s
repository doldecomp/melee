.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

.global func_80206E2C
func_80206E2C:
/* 80206E2C 00203A0C  4E 80 00 20 */	blr 

.global func_80206E30
func_80206E30:
/* 80206E30 00203A10  7C 08 02 A6 */	mflr r0
/* 80206E34 00203A14  3C 60 80 4A */	lis r3, stage_info@ha
/* 80206E38 00203A18  90 01 00 04 */	stw r0, 4(r1)
/* 80206E3C 00203A1C  38 63 E6 C8 */	addi r3, r3, stage_info@l
/* 80206E40 00203A20  38 A3 00 8C */	addi r5, r3, 0x8c
/* 80206E44 00203A24  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80206E48 00203A28  38 80 00 01 */	li r4, 1
/* 80206E4C 00203A2C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80206E50 00203A30  88 03 00 8C */	lbz r0, 0x8c(r3)
/* 80206E54 00203A34  38 60 00 00 */	li r3, 0
/* 80206E58 00203A38  50 60 1F 38 */	rlwimi r0, r3, 3, 0x1c, 0x1c
/* 80206E5C 00203A3C  98 05 00 00 */	stb r0, 0(r5)
/* 80206E60 00203A40  38 60 00 00 */	li r3, 0
/* 80206E64 00203A44  88 05 00 00 */	lbz r0, 0(r5)
/* 80206E68 00203A48  50 80 17 7A */	rlwimi r0, r4, 2, 0x1d, 0x1d
/* 80206E6C 00203A4C  98 05 00 00 */	stb r0, 0(r5)
/* 80206E70 00203A50  48 00 01 D5 */	bl func_80207044
/* 80206E74 00203A54  38 60 00 02 */	li r3, 2
/* 80206E78 00203A58  48 00 01 CD */	bl func_80207044
/* 80206E7C 00203A5C  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 80206E80 00203A60  3C 80 80 20 */	lis r4, lbl_802073B0@ha
/* 80206E84 00203A64  38 04 73 B0 */	addi r0, r4, lbl_802073B0@l
/* 80206E88 00203A68  90 03 00 08 */	stw r0, 8(r3)
/* 80206E8C 00203A6C  38 60 00 01 */	li r3, 1
/* 80206E90 00203A70  48 00 01 B5 */	bl func_80207044
/* 80206E94 00203A74  80 03 00 28 */	lwz r0, 0x28(r3)
/* 80206E98 00203A78  28 00 00 00 */	cmplwi r0, 0
/* 80206E9C 00203A7C  7C 1F 03 78 */	mr r31, r0
/* 80206EA0 00203A80  40 82 00 14 */	bne lbl_80206EB4
/* 80206EA4 00203A84  38 6D 91 48 */	addi r3, r13, lbl_804D47E8@sda21
/* 80206EA8 00203A88  38 80 03 08 */	li r4, 0x308
/* 80206EAC 00203A8C  38 AD 91 50 */	addi r5, r13, lbl_804D47F0@sda21
/* 80206EB0 00203A90  48 18 13 71 */	bl __assert
lbl_80206EB4:
/* 80206EB4 00203A94  C0 02 BE 38 */	lfs f0, lbl_804DB818@sda21(r2)
/* 80206EB8 00203A98  D0 1F 00 2C */	stfs f0, 0x2c(r31)
/* 80206EBC 00203A9C  80 1F 00 14 */	lwz r0, 0x14(r31)
/* 80206EC0 00203AA0  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 80206EC4 00203AA4  40 82 00 4C */	bne lbl_80206F10
/* 80206EC8 00203AA8  28 1F 00 00 */	cmplwi r31, 0
/* 80206ECC 00203AAC  41 82 00 44 */	beq lbl_80206F10
/* 80206ED0 00203AB0  40 82 00 14 */	bne lbl_80206EE4
/* 80206ED4 00203AB4  38 6D 91 48 */	addi r3, r13, lbl_804D47E8@sda21
/* 80206ED8 00203AB8  38 80 02 34 */	li r4, 0x234
/* 80206EDC 00203ABC  38 AD 91 50 */	addi r5, r13, lbl_804D47F0@sda21
/* 80206EE0 00203AC0  48 18 13 41 */	bl __assert
lbl_80206EE4:
/* 80206EE4 00203AC4  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80206EE8 00203AC8  38 60 00 00 */	li r3, 0
/* 80206EEC 00203ACC  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 80206EF0 00203AD0  40 82 00 10 */	bne lbl_80206F00
/* 80206EF4 00203AD4  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 80206EF8 00203AD8  41 82 00 08 */	beq lbl_80206F00
/* 80206EFC 00203ADC  38 60 00 01 */	li r3, 1
lbl_80206F00:
/* 80206F00 00203AE0  2C 03 00 00 */	cmpwi r3, 0
/* 80206F04 00203AE4  40 82 00 0C */	bne lbl_80206F10
/* 80206F08 00203AE8  7F E3 FB 78 */	mr r3, r31
/* 80206F0C 00203AEC  48 16 C3 DD */	bl HSD_JObjSetMtxDirtySub
lbl_80206F10:
/* 80206F10 00203AF0  28 1F 00 00 */	cmplwi r31, 0
/* 80206F14 00203AF4  40 82 00 14 */	bne lbl_80206F28
/* 80206F18 00203AF8  38 6D 91 48 */	addi r3, r13, lbl_804D47E8@sda21
/* 80206F1C 00203AFC  38 80 03 17 */	li r4, 0x317
/* 80206F20 00203B00  38 AD 91 50 */	addi r5, r13, lbl_804D47F0@sda21
/* 80206F24 00203B04  48 18 12 FD */	bl __assert
lbl_80206F28:
/* 80206F28 00203B08  C0 02 BE 38 */	lfs f0, lbl_804DB818@sda21(r2)
/* 80206F2C 00203B0C  D0 1F 00 30 */	stfs f0, 0x30(r31)
/* 80206F30 00203B10  80 1F 00 14 */	lwz r0, 0x14(r31)
/* 80206F34 00203B14  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 80206F38 00203B18  40 82 00 4C */	bne lbl_80206F84
/* 80206F3C 00203B1C  28 1F 00 00 */	cmplwi r31, 0
/* 80206F40 00203B20  41 82 00 44 */	beq lbl_80206F84
/* 80206F44 00203B24  40 82 00 14 */	bne lbl_80206F58
/* 80206F48 00203B28  38 6D 91 48 */	addi r3, r13, lbl_804D47E8@sda21
/* 80206F4C 00203B2C  38 80 02 34 */	li r4, 0x234
/* 80206F50 00203B30  38 AD 91 50 */	addi r5, r13, lbl_804D47F0@sda21
/* 80206F54 00203B34  48 18 12 CD */	bl __assert
lbl_80206F58:
/* 80206F58 00203B38  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80206F5C 00203B3C  38 60 00 00 */	li r3, 0
/* 80206F60 00203B40  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 80206F64 00203B44  40 82 00 10 */	bne lbl_80206F74
/* 80206F68 00203B48  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 80206F6C 00203B4C  41 82 00 08 */	beq lbl_80206F74
/* 80206F70 00203B50  38 60 00 01 */	li r3, 1
lbl_80206F74:
/* 80206F74 00203B54  2C 03 00 00 */	cmpwi r3, 0
/* 80206F78 00203B58  40 82 00 0C */	bne lbl_80206F84
/* 80206F7C 00203B5C  7F E3 FB 78 */	mr r3, r31
/* 80206F80 00203B60  48 16 C3 69 */	bl HSD_JObjSetMtxDirtySub
lbl_80206F84:
/* 80206F84 00203B64  28 1F 00 00 */	cmplwi r31, 0
/* 80206F88 00203B68  40 82 00 14 */	bne lbl_80206F9C
/* 80206F8C 00203B6C  38 6D 91 48 */	addi r3, r13, lbl_804D47E8@sda21
/* 80206F90 00203B70  38 80 03 26 */	li r4, 0x326
/* 80206F94 00203B74  38 AD 91 50 */	addi r5, r13, lbl_804D47F0@sda21
/* 80206F98 00203B78  48 18 12 89 */	bl __assert
lbl_80206F9C:
/* 80206F9C 00203B7C  C0 02 BE 38 */	lfs f0, lbl_804DB818@sda21(r2)
/* 80206FA0 00203B80  D0 1F 00 34 */	stfs f0, 0x34(r31)
/* 80206FA4 00203B84  80 1F 00 14 */	lwz r0, 0x14(r31)
/* 80206FA8 00203B88  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 80206FAC 00203B8C  40 82 00 4C */	bne lbl_80206FF8
/* 80206FB0 00203B90  28 1F 00 00 */	cmplwi r31, 0
/* 80206FB4 00203B94  41 82 00 44 */	beq lbl_80206FF8
/* 80206FB8 00203B98  40 82 00 14 */	bne lbl_80206FCC
/* 80206FBC 00203B9C  38 6D 91 48 */	addi r3, r13, lbl_804D47E8@sda21
/* 80206FC0 00203BA0  38 80 02 34 */	li r4, 0x234
/* 80206FC4 00203BA4  38 AD 91 50 */	addi r5, r13, lbl_804D47F0@sda21
/* 80206FC8 00203BA8  48 18 12 59 */	bl __assert
lbl_80206FCC:
/* 80206FCC 00203BAC  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80206FD0 00203BB0  38 60 00 00 */	li r3, 0
/* 80206FD4 00203BB4  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 80206FD8 00203BB8  40 82 00 10 */	bne lbl_80206FE8
/* 80206FDC 00203BBC  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 80206FE0 00203BC0  41 82 00 08 */	beq lbl_80206FE8
/* 80206FE4 00203BC4  38 60 00 01 */	li r3, 1
lbl_80206FE8:
/* 80206FE8 00203BC8  2C 03 00 00 */	cmpwi r3, 0
/* 80206FEC 00203BCC  40 82 00 0C */	bne lbl_80206FF8
/* 80206FF0 00203BD0  7F E3 FB 78 */	mr r3, r31
/* 80206FF4 00203BD4  48 16 C2 F5 */	bl HSD_JObjSetMtxDirtySub
lbl_80206FF8:
/* 80206FF8 00203BD8  4B FB C9 C9 */	bl func_801C39C0
/* 80206FFC 00203BDC  4B FB CB B9 */	bl func_801C3BB4
/* 80207000 00203BE0  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80207004 00203BE4  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80207008 00203BE8  38 21 00 20 */	addi r1, r1, 0x20
/* 8020700C 00203BEC  7C 08 03 A6 */	mtlr r0
/* 80207010 00203BF0  4E 80 00 20 */	blr 

.global func_80207014
func_80207014:
/* 80207014 00203BF4  4E 80 00 20 */	blr 

.global func_80207018
func_80207018:
/* 80207018 00203BF8  7C 08 02 A6 */	mflr r0
/* 8020701C 00203BFC  38 60 00 00 */	li r3, 0
/* 80207020 00203C00  90 01 00 04 */	stw r0, 4(r1)
/* 80207024 00203C04  94 21 FF F8 */	stwu r1, -8(r1)
/* 80207028 00203C08  4B FC 3D DD */	bl func_801CAE04
/* 8020702C 00203C0C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80207030 00203C10  38 21 00 08 */	addi r1, r1, 8
/* 80207034 00203C14  7C 08 03 A6 */	mtlr r0
/* 80207038 00203C18  4E 80 00 20 */	blr 

.global func_8020703C
func_8020703C:
/* 8020703C 00203C1C  38 60 00 00 */	li r3, 0
/* 80207040 00203C20  4E 80 00 20 */	blr 

.global func_80207044
func_80207044:
/* 80207044 00203C24  7C 08 02 A6 */	mflr r0
/* 80207048 00203C28  90 01 00 04 */	stw r0, 4(r1)
/* 8020704C 00203C2C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80207050 00203C30  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80207054 00203C34  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80207058 00203C38  93 A1 00 14 */	stw r29, 0x14(r1)
/* 8020705C 00203C3C  93 81 00 10 */	stw r28, 0x10(r1)
/* 80207060 00203C40  3B 83 00 00 */	addi r28, r3, 0
/* 80207064 00203C44  1C 1C 00 14 */	mulli r0, r28, 0x14
/* 80207068 00203C48  3C 60 80 3E */	lis r3, lbl_803E56B8@ha
/* 8020706C 00203C4C  3B E3 56 B8 */	addi r31, r3, lbl_803E56B8@l
/* 80207070 00203C50  7F BF 02 14 */	add r29, r31, r0
/* 80207074 00203C54  38 7C 00 00 */	addi r3, r28, 0
/* 80207078 00203C58  3B BD 00 50 */	addi r29, r29, 0x50
/* 8020707C 00203C5C  4B FB A4 55 */	bl func_801C14D0
/* 80207080 00203C60  7C 7E 1B 79 */	or. r30, r3, r3
/* 80207084 00203C64  41 82 00 70 */	beq lbl_802070F4
/* 80207088 00203C68  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 8020708C 00203C6C  38 00 00 00 */	li r0, 0
/* 80207090 00203C70  3C 60 80 1C */	lis r3, func_801C5DB0@ha
/* 80207094 00203C74  90 1F 00 08 */	stw r0, 8(r31)
/* 80207098 00203C78  38 83 5D B0 */	addi r4, r3, func_801C5DB0@l
/* 8020709C 00203C7C  38 7E 00 00 */	addi r3, r30, 0
/* 802070A0 00203C80  90 1F 00 0C */	stw r0, 0xc(r31)
/* 802070A4 00203C84  38 A0 00 03 */	li r5, 3
/* 802070A8 00203C88  38 C0 00 00 */	li r6, 0
/* 802070AC 00203C8C  48 18 95 F1 */	bl func_8039069C
/* 802070B0 00203C90  80 1D 00 0C */	lwz r0, 0xc(r29)
/* 802070B4 00203C94  28 00 00 00 */	cmplwi r0, 0
/* 802070B8 00203C98  41 82 00 08 */	beq lbl_802070C0
/* 802070BC 00203C9C  90 1F 00 1C */	stw r0, 0x1c(r31)
lbl_802070C0:
/* 802070C0 00203CA0  81 9D 00 00 */	lwz r12, 0(r29)
/* 802070C4 00203CA4  28 0C 00 00 */	cmplwi r12, 0
/* 802070C8 00203CA8  41 82 00 10 */	beq lbl_802070D8
/* 802070CC 00203CAC  7D 88 03 A6 */	mtlr r12
/* 802070D0 00203CB0  38 7E 00 00 */	addi r3, r30, 0
/* 802070D4 00203CB4  4E 80 00 21 */	blrl 
lbl_802070D8:
/* 802070D8 00203CB8  80 9D 00 08 */	lwz r4, 8(r29)
/* 802070DC 00203CBC  28 04 00 00 */	cmplwi r4, 0
/* 802070E0 00203CC0  41 82 00 2C */	beq lbl_8020710C
/* 802070E4 00203CC4  38 7E 00 00 */	addi r3, r30, 0
/* 802070E8 00203CC8  38 A0 00 04 */	li r5, 4
/* 802070EC 00203CCC  48 18 8C 69 */	bl func_8038FD54
/* 802070F0 00203CD0  48 00 00 1C */	b lbl_8020710C
lbl_802070F4:
/* 802070F4 00203CD4  38 DC 00 00 */	addi r6, r28, 0
/* 802070F8 00203CD8  4C C6 31 82 */	crclr 6
/* 802070FC 00203CDC  38 7F 00 E0 */	addi r3, r31, 0xe0
/* 80207100 00203CE0  38 9F 01 04 */	addi r4, r31, 0x104
/* 80207104 00203CE4  38 A0 00 D1 */	li r5, 0xd1
/* 80207108 00203CE8  48 13 E5 A1 */	bl OSReport
lbl_8020710C:
/* 8020710C 00203CEC  7F C3 F3 78 */	mr r3, r30
/* 80207110 00203CF0  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80207114 00203CF4  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80207118 00203CF8  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8020711C 00203CFC  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 80207120 00203D00  83 81 00 10 */	lwz r28, 0x10(r1)
/* 80207124 00203D04  38 21 00 20 */	addi r1, r1, 0x20
/* 80207128 00203D08  7C 08 03 A6 */	mtlr r0
/* 8020712C 00203D0C  4E 80 00 20 */	blr 

.global func_80207130
func_80207130:
/* 80207130 00203D10  7C 08 02 A6 */	mflr r0
/* 80207134 00203D14  38 A0 00 00 */	li r5, 0
/* 80207138 00203D18  90 01 00 04 */	stw r0, 4(r1)
/* 8020713C 00203D1C  94 21 FF F8 */	stwu r1, -8(r1)
/* 80207140 00203D20  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 80207144 00203D24  80 84 00 14 */	lwz r4, 0x14(r4)
/* 80207148 00203D28  4B FC 0F F1 */	bl func_801C8138
/* 8020714C 00203D2C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80207150 00203D30  38 21 00 08 */	addi r1, r1, 8
/* 80207154 00203D34  7C 08 03 A6 */	mtlr r0
/* 80207158 00203D38  4E 80 00 20 */	blr 

.global func_8020715C
func_8020715C:
/* 8020715C 00203D3C  38 60 00 00 */	li r3, 0
/* 80207160 00203D40  4E 80 00 20 */	blr 

.global func_80207164
func_80207164:
/* 80207164 00203D44  4E 80 00 20 */	blr 

.global func_80207168
func_80207168:
/* 80207168 00203D48  4E 80 00 20 */	blr 

.global func_8020716C
func_8020716C:
/* 8020716C 00203D4C  7C 08 02 A6 */	mflr r0
/* 80207170 00203D50  90 01 00 04 */	stw r0, 4(r1)
/* 80207174 00203D54  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80207178 00203D58  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8020717C 00203D5C  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80207180 00203D60  7C 7E 1B 78 */	mr r30, r3
/* 80207184 00203D64  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80207188 00203D68  80 63 00 28 */	lwz r3, 0x28(r3)
/* 8020718C 00203D6C  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80207190 00203D70  4B FB BD 41 */	bl func_801C2ED0
/* 80207194 00203D74  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80207198 00203D78  38 7E 00 00 */	addi r3, r30, 0
/* 8020719C 00203D7C  38 A0 00 00 */	li r5, 0
/* 802071A0 00203D80  4B FC 0F 99 */	bl func_801C8138
/* 802071A4 00203D84  80 01 00 24 */	lwz r0, 0x24(r1)
/* 802071A8 00203D88  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 802071AC 00203D8C  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 802071B0 00203D90  38 21 00 20 */	addi r1, r1, 0x20
/* 802071B4 00203D94  7C 08 03 A6 */	mtlr r0
/* 802071B8 00203D98  4E 80 00 20 */	blr 

.global func_802071BC
func_802071BC:
/* 802071BC 00203D9C  38 60 00 00 */	li r3, 0
/* 802071C0 00203DA0  4E 80 00 20 */	blr 

.global func_802071C4
func_802071C4:
/* 802071C4 00203DA4  7C 08 02 A6 */	mflr r0
/* 802071C8 00203DA8  3C 80 80 4C */	lis r4, HSD_PadMasterStatus@ha
/* 802071CC 00203DAC  90 01 00 04 */	stw r0, 4(r1)
/* 802071D0 00203DB0  38 84 1F AC */	addi r4, r4, HSD_PadMasterStatus@l
/* 802071D4 00203DB4  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 802071D8 00203DB8  DB E1 00 28 */	stfd f31, 0x28(r1)
/* 802071DC 00203DBC  93 E1 00 24 */	stw r31, 0x24(r1)
/* 802071E0 00203DC0  93 C1 00 20 */	stw r30, 0x20(r1)
/* 802071E4 00203DC4  3B C3 00 00 */	addi r30, r3, 0
/* 802071E8 00203DC8  80 04 00 4C */	lwz r0, 0x4c(r4)
/* 802071EC 00203DCC  54 00 05 EF */	rlwinm. r0, r0, 0, 0x17, 0x17
/* 802071F0 00203DD0  41 82 00 4C */	beq lbl_8020723C
/* 802071F4 00203DD4  38 7E 00 00 */	addi r3, r30, 0
/* 802071F8 00203DD8  38 80 00 10 */	li r4, 0x10
/* 802071FC 00203DDC  4B FB CD A9 */	bl func_801C3FA4
/* 80207200 00203DE0  7C 7F 1B 79 */	or. r31, r3, r3
/* 80207204 00203DE4  41 82 00 38 */	beq lbl_8020723C
/* 80207208 00203DE8  7F E3 FB 78 */	mr r3, r31
/* 8020720C 00203DEC  48 16 AA DD */	bl HSD_JObjGetFlags
/* 80207210 00203DF0  54 60 06 F7 */	rlwinm. r0, r3, 0, 0x1b, 0x1b
/* 80207214 00203DF4  41 82 00 14 */	beq lbl_80207228
/* 80207218 00203DF8  38 7F 00 00 */	addi r3, r31, 0
/* 8020721C 00203DFC  38 80 00 10 */	li r4, 0x10
/* 80207220 00203E00  48 16 AC E1 */	bl HSD_JObjClearFlags
/* 80207224 00203E04  48 00 00 10 */	b lbl_80207234
lbl_80207228:
/* 80207228 00203E08  38 7F 00 00 */	addi r3, r31, 0
/* 8020722C 00203E0C  38 80 00 10 */	li r4, 0x10
/* 80207230 00203E10  48 16 AA D1 */	bl HSD_JObjSetFlags
lbl_80207234:
/* 80207234 00203E14  C0 02 BE 3C */	lfs f0, lbl_804DB81C@sda21(r2)
/* 80207238 00203E18  D0 0D B3 A8 */	stfs f0, lbl_804D6A48@sda21(r13)
lbl_8020723C:
/* 8020723C 00203E1C  3C 60 80 4C */	lis r3, HSD_PadMasterStatus@ha
/* 80207240 00203E20  38 63 1F AC */	addi r3, r3, HSD_PadMasterStatus@l
/* 80207244 00203E24  80 03 00 90 */	lwz r0, 0x90(r3)
/* 80207248 00203E28  54 00 05 EF */	rlwinm. r0, r0, 0, 0x17, 0x17
/* 8020724C 00203E2C  41 82 00 4C */	beq lbl_80207298
/* 80207250 00203E30  38 7E 00 00 */	addi r3, r30, 0
/* 80207254 00203E34  38 80 00 11 */	li r4, 0x11
/* 80207258 00203E38  4B FB CD 4D */	bl func_801C3FA4
/* 8020725C 00203E3C  7C 7F 1B 79 */	or. r31, r3, r3
/* 80207260 00203E40  41 82 00 38 */	beq lbl_80207298
/* 80207264 00203E44  7F E3 FB 78 */	mr r3, r31
/* 80207268 00203E48  48 16 AA 81 */	bl HSD_JObjGetFlags
/* 8020726C 00203E4C  54 60 06 F7 */	rlwinm. r0, r3, 0, 0x1b, 0x1b
/* 80207270 00203E50  41 82 00 14 */	beq lbl_80207284
/* 80207274 00203E54  38 7F 00 00 */	addi r3, r31, 0
/* 80207278 00203E58  38 80 00 10 */	li r4, 0x10
/* 8020727C 00203E5C  48 16 AC 85 */	bl HSD_JObjClearFlags
/* 80207280 00203E60  48 00 00 10 */	b lbl_80207290
lbl_80207284:
/* 80207284 00203E64  38 7F 00 00 */	addi r3, r31, 0
/* 80207288 00203E68  38 80 00 10 */	li r4, 0x10
/* 8020728C 00203E6C  48 16 AA 75 */	bl HSD_JObjSetFlags
lbl_80207290:
/* 80207290 00203E70  C0 02 BE 3C */	lfs f0, lbl_804DB81C@sda21(r2)
/* 80207294 00203E74  D0 0D B3 A8 */	stfs f0, lbl_804D6A48@sda21(r13)
lbl_80207298:
/* 80207298 00203E78  3C 60 80 4C */	lis r3, HSD_PadMasterStatus@ha
/* 8020729C 00203E7C  38 63 1F AC */	addi r3, r3, HSD_PadMasterStatus@l
/* 802072A0 00203E80  80 63 00 44 */	lwz r3, 0x44(r3)
/* 802072A4 00203E84  54 60 05 6B */	rlwinm. r0, r3, 0, 0x15, 0x15
/* 802072A8 00203E88  41 82 00 20 */	beq lbl_802072C8
/* 802072AC 00203E8C  C0 2D B3 A8 */	lfs f1, lbl_804D6A48@sda21(r13)
/* 802072B0 00203E90  C0 02 BE 40 */	lfs f0, lbl_804DB820@sda21(r2)
/* 802072B4 00203E94  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 802072B8 00203E98  40 81 00 10 */	ble lbl_802072C8
/* 802072BC 00203E9C  C0 02 BE 44 */	lfs f0, lbl_804DB824@sda21(r2)
/* 802072C0 00203EA0  EC 01 00 28 */	fsubs f0, f1, f0
/* 802072C4 00203EA4  D0 0D B3 A8 */	stfs f0, lbl_804D6A48@sda21(r13)
lbl_802072C8:
/* 802072C8 00203EA8  54 60 05 29 */	rlwinm. r0, r3, 0, 0x14, 0x14
/* 802072CC 00203EAC  41 82 00 20 */	beq lbl_802072EC
/* 802072D0 00203EB0  C0 2D B3 A8 */	lfs f1, lbl_804D6A48@sda21(r13)
/* 802072D4 00203EB4  C0 02 BE 48 */	lfs f0, lbl_804DB828@sda21(r2)
/* 802072D8 00203EB8  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 802072DC 00203EBC  40 80 00 10 */	bge lbl_802072EC
/* 802072E0 00203EC0  C0 02 BE 44 */	lfs f0, lbl_804DB824@sda21(r2)
/* 802072E4 00203EC4  EC 01 00 2A */	fadds f0, f1, f0
/* 802072E8 00203EC8  D0 0D B3 A8 */	stfs f0, lbl_804D6A48@sda21(r13)
lbl_802072EC:
/* 802072EC 00203ECC  38 7E 00 00 */	addi r3, r30, 0
/* 802072F0 00203ED0  38 80 00 0B */	li r4, 0xb
/* 802072F4 00203ED4  4B FB CC B1 */	bl func_801C3FA4
/* 802072F8 00203ED8  7C 7F 1B 79 */	or. r31, r3, r3
/* 802072FC 00203EDC  41 82 00 94 */	beq lbl_80207390
/* 80207300 00203EE0  C3 ED B3 A8 */	lfs f31, lbl_804D6A48@sda21(r13)
/* 80207304 00203EE4  40 82 00 14 */	bne lbl_80207318
/* 80207308 00203EE8  38 6D 91 48 */	addi r3, r13, lbl_804D47E8@sda21
/* 8020730C 00203EEC  38 80 02 A9 */	li r4, 0x2a9
/* 80207310 00203EF0  38 AD 91 50 */	addi r5, r13, lbl_804D47F0@sda21
/* 80207314 00203EF4  48 18 0F 0D */	bl __assert
lbl_80207318:
/* 80207318 00203EF8  80 1F 00 14 */	lwz r0, 0x14(r31)
/* 8020731C 00203EFC  54 00 03 9D */	rlwinm. r0, r0, 0, 0xe, 0xe
/* 80207320 00203F00  41 82 00 18 */	beq lbl_80207338
/* 80207324 00203F04  3C 60 80 3E */	lis r3, lbl_803E57C8@ha
/* 80207328 00203F08  38 A3 57 C8 */	addi r5, r3, lbl_803E57C8@l
/* 8020732C 00203F0C  38 6D 91 48 */	addi r3, r13, lbl_804D47E8@sda21
/* 80207330 00203F10  38 80 02 AA */	li r4, 0x2aa
/* 80207334 00203F14  48 18 0E ED */	bl __assert
lbl_80207338:
/* 80207338 00203F18  D3 FF 00 24 */	stfs f31, 0x24(r31)
/* 8020733C 00203F1C  80 1F 00 14 */	lwz r0, 0x14(r31)
/* 80207340 00203F20  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 80207344 00203F24  40 82 00 4C */	bne lbl_80207390
/* 80207348 00203F28  28 1F 00 00 */	cmplwi r31, 0
/* 8020734C 00203F2C  41 82 00 44 */	beq lbl_80207390
/* 80207350 00203F30  40 82 00 14 */	bne lbl_80207364
/* 80207354 00203F34  38 6D 91 48 */	addi r3, r13, lbl_804D47E8@sda21
/* 80207358 00203F38  38 80 02 34 */	li r4, 0x234
/* 8020735C 00203F3C  38 AD 91 50 */	addi r5, r13, lbl_804D47F0@sda21
/* 80207360 00203F40  48 18 0E C1 */	bl __assert
lbl_80207364:
/* 80207364 00203F44  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80207368 00203F48  38 60 00 00 */	li r3, 0
/* 8020736C 00203F4C  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 80207370 00203F50  40 82 00 10 */	bne lbl_80207380
/* 80207374 00203F54  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 80207378 00203F58  41 82 00 08 */	beq lbl_80207380
/* 8020737C 00203F5C  38 60 00 01 */	li r3, 1
lbl_80207380:
/* 80207380 00203F60  2C 03 00 00 */	cmpwi r3, 0
/* 80207384 00203F64  40 82 00 0C */	bne lbl_80207390
/* 80207388 00203F68  7F E3 FB 78 */	mr r3, r31
/* 8020738C 00203F6C  48 16 BF 5D */	bl HSD_JObjSetMtxDirtySub
lbl_80207390:
/* 80207390 00203F70  80 01 00 34 */	lwz r0, 0x34(r1)
/* 80207394 00203F74  CB E1 00 28 */	lfd f31, 0x28(r1)
/* 80207398 00203F78  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 8020739C 00203F7C  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 802073A0 00203F80  38 21 00 30 */	addi r1, r1, 0x30
/* 802073A4 00203F84  7C 08 03 A6 */	mtlr r0
/* 802073A8 00203F88  4E 80 00 20 */	blr 

.global func_802073AC
func_802073AC:
/* 802073AC 00203F8C  4E 80 00 20 */	blr 
lbl_802073B0:
/* 802073B0 00203F90  7C 08 02 A6 */	mflr r0
/* 802073B4 00203F94  90 01 00 04 */	stw r0, 4(r1)
/* 802073B8 00203F98  94 21 FF F8 */	stwu r1, -8(r1)
/* 802073BC 00203F9C  4B FB BC 25 */	bl func_801C2FE0
/* 802073C0 00203FA0  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802073C4 00203FA4  38 21 00 08 */	addi r1, r1, 8
/* 802073C8 00203FA8  7C 08 03 A6 */	mtlr r0
/* 802073CC 00203FAC  4E 80 00 20 */	blr 

.global func_802073D0
func_802073D0:
/* 802073D0 00203FB0  7C 08 02 A6 */	mflr r0
/* 802073D4 00203FB4  38 A0 00 00 */	li r5, 0
/* 802073D8 00203FB8  90 01 00 04 */	stw r0, 4(r1)
/* 802073DC 00203FBC  94 21 FF F8 */	stwu r1, -8(r1)
/* 802073E0 00203FC0  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 802073E4 00203FC4  80 84 00 14 */	lwz r4, 0x14(r4)
/* 802073E8 00203FC8  4B FC 0D 51 */	bl func_801C8138
/* 802073EC 00203FCC  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802073F0 00203FD0  38 21 00 08 */	addi r1, r1, 8
/* 802073F4 00203FD4  7C 08 03 A6 */	mtlr r0
/* 802073F8 00203FD8  4E 80 00 20 */	blr 

.global func_802073FC
func_802073FC:
/* 802073FC 00203FDC  38 60 00 00 */	li r3, 0
/* 80207400 00203FE0  4E 80 00 20 */	blr 

.global func_80207404
func_80207404:
/* 80207404 00203FE4  4E 80 00 20 */	blr 

.global func_80207408
func_80207408:
/* 80207408 00203FE8  4E 80 00 20 */	blr 

.global func_8020740C
func_8020740C:
/* 8020740C 00203FEC  38 60 00 00 */	li r3, 0
/* 80207410 00203FF0  4E 80 00 20 */	blr 

.global func_80207414
func_80207414:
/* 80207414 00203FF4  38 60 00 01 */	li r3, 1
/* 80207418 00203FF8  4E 80 00 20 */	blr 


.section .data

.global lbl_803E56B8
lbl_803E56B8:
    .4byte 0x00000002
    .4byte 0x00010001
    .4byte 0x00020002
    .4byte 0x00020002
    .4byte 0x00030003
    .4byte 0x00020004
    .4byte 0x00040002
    .4byte 0x00050005
    .4byte 0x00020006
    .4byte 0x00060002
    .4byte 0x00070007
    .4byte 0x00020008
    .4byte 0x00080002
    .4byte 0x00090009
    .4byte 0x0002000A
    .4byte 0x000A0002
    .4byte 0x000B000C
    .4byte 0x00020010
    .4byte 0x000D0002
    .4byte 0x00110000
.global lbl_803E5708
lbl_803E5708:
    .4byte func_80207130
    .4byte func_8020715C
    .4byte func_80207164
    .4byte func_80207168
    .4byte NULL
    .4byte func_802073D0
    .4byte func_802073FC
    .4byte func_80207404
    .4byte func_80207408
    .4byte NULL
    .4byte func_8020716C
    .4byte func_802071BC
    .4byte func_802071C4
    .4byte func_802073AC
    .4byte 0xC0000000
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
.global lbl_803E5758
lbl_803E5758:
    .4byte 0x2F477254
    .4byte 0x652E6461
    .4byte 0x74000000
.global lbl_803E5764
lbl_803E5764:
    .4byte 0x00000001
    .4byte lbl_803E5708
    .4byte lbl_803E5758
    .4byte func_80206E30
    .4byte func_80206E2C
    .4byte func_80207014
    .4byte func_80207018
    .4byte func_8020703C
    .4byte func_8020740C
    .4byte func_80207414
    .4byte 0x00000001
    .4byte lbl_803E56B8
    .4byte 0x0000000D
    .4byte 0x25733A25
    .4byte 0x643A2063
    .4byte 0x6F756C64
    .4byte 0x6E207420
    .4byte 0x67657420
    .4byte 0x676F626A
    .4byte 0x2869643D
    .4byte 0x2564290A
    .4byte NULL
    .4byte 0x67727465
    .4byte 0x73742E63
    .4byte NULL
.global lbl_803E57C8
lbl_803E57C8:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4


.section .sbss

.global lbl_804D6A48
lbl_804D6A48:
	.skip 0x8
