.include "macros.inc"

.section .text

.global it_802D5CF8
it_802D5CF8:
/* 802D5CF8 002D28D8  7C 08 02 A6 */	mflr r0
/* 802D5CFC 002D28DC  38 80 00 00 */	li r4, 0
/* 802D5D00 002D28E0  90 01 00 04 */	stw r0, 4(r1)
/* 802D5D04 002D28E4  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 802D5D08 002D28E8  93 E1 00 14 */	stw r31, 0x14(r1)
/* 802D5D0C 002D28EC  93 C1 00 10 */	stw r30, 0x10(r1)
/* 802D5D10 002D28F0  7C 7E 1B 78 */	mr r30, r3
/* 802D5D14 002D28F4  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 802D5D18 002D28F8  90 9F 0D AC */	stw r4, 0xdac(r31)
/* 802D5D1C 002D28FC  90 9F 0D B0 */	stw r4, 0xdb0(r31)
/* 802D5D20 002D2900  88 1F 0E 34 */	lbz r0, 0xe34(r31)
/* 802D5D24 002D2904  50 80 3E 30 */	rlwimi r0, r4, 7, 0x18, 0x18
/* 802D5D28 002D2908  98 1F 0E 34 */	stb r0, 0xe34(r31)
/* 802D5D2C 002D290C  88 1F 0E 34 */	lbz r0, 0xe34(r31)
/* 802D5D30 002D2910  50 80 36 72 */	rlwimi r0, r4, 6, 0x19, 0x19
/* 802D5D34 002D2914  98 1F 0E 34 */	stb r0, 0xe34(r31)
/* 802D5D38 002D2918  C0 02 DB 40 */	lfs f0, it_804DD520@sda21(r2)
/* 802D5D3C 002D291C  D0 1F 0E 38 */	stfs f0, 0xe38(r31)
/* 802D5D40 002D2920  C0 3F 00 38 */	lfs f1, 0x38(r31)
/* 802D5D44 002D2924  4B FA 3F 99 */	bl it_80279CDC
/* 802D5D48 002D2928  38 7F 00 00 */	addi r3, r31, 0
/* 802D5D4C 002D292C  38 80 27 34 */	li r4, 0x2734
/* 802D5D50 002D2930  38 A0 00 7F */	li r5, 0x7f
/* 802D5D54 002D2934  38 C0 00 40 */	li r6, 0x40
/* 802D5D58 002D2938  4B F9 51 2D */	bl Item_8026AE84
/* 802D5D5C 002D293C  7F C3 F3 78 */	mr r3, r30
/* 802D5D60 002D2940  48 00 00 ED */	bl it_802D5E4C
/* 802D5D64 002D2944  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 802D5D68 002D2948  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 802D5D6C 002D294C  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 802D5D70 002D2950  38 21 00 18 */	addi r1, r1, 0x18
/* 802D5D74 002D2954  7C 08 03 A6 */	mtlr r0
/* 802D5D78 002D2958  4E 80 00 20 */	blr

.global it_802D5D7C
it_802D5D7C:
/* 802D5D7C 002D295C  7C 08 02 A6 */	mflr r0
/* 802D5D80 002D2960  90 01 00 04 */	stw r0, 4(r1)
/* 802D5D84 002D2964  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 802D5D88 002D2968  93 E1 00 24 */	stw r31, 0x24(r1)
/* 802D5D8C 002D296C  93 C1 00 20 */	stw r30, 0x20(r1)
/* 802D5D90 002D2970  7C 7E 1B 78 */	mr r30, r3
/* 802D5D94 002D2974  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 802D5D98 002D2978  80 1F 0D AC */	lwz r0, 0xdac(r31)
/* 802D5D9C 002D297C  28 00 00 00 */	cmplwi r0, 0
/* 802D5DA0 002D2980  41 82 00 68 */	beq .L_802D5E08
/* 802D5DA4 002D2984  88 7F 0E 34 */	lbz r3, 0xe34(r31)
/* 802D5DA8 002D2988  54 60 CF FF */	rlwinm. r0, r3, 0x19, 0x1f, 0x1f
/* 802D5DAC 002D298C  40 82 00 28 */	bne .L_802D5DD4
/* 802D5DB0 002D2990  38 00 00 01 */	li r0, 1
/* 802D5DB4 002D2994  4C C6 31 82 */	crclr 6
/* 802D5DB8 002D2998  50 03 3E 30 */	rlwimi r3, r0, 7, 0x18, 0x18
/* 802D5DBC 002D299C  98 7F 0E 34 */	stb r3, 0xe34(r31)
/* 802D5DC0 002D29A0  38 9E 00 00 */	addi r4, r30, 0
/* 802D5DC4 002D29A4  38 60 04 73 */	li r3, 0x473
/* 802D5DC8 002D29A8  80 BF 0B BC */	lwz r5, 0xbbc(r31)
/* 802D5DCC 002D29AC  80 A5 00 08 */	lwz r5, 8(r5)
/* 802D5DD0 002D29B0  4B D8 A0 0D */	bl efSync_Spawn
.L_802D5DD4:
/* 802D5DD4 002D29B4  80 7F 0B BC */	lwz r3, 0xbbc(r31)
/* 802D5DD8 002D29B8  38 A1 00 10 */	addi r5, r1, 0x10
/* 802D5DDC 002D29BC  38 80 00 00 */	li r4, 0
/* 802D5DE0 002D29C0  80 63 00 08 */	lwz r3, 8(r3)
/* 802D5DE4 002D29C4  4B D3 53 E9 */	bl lb_8000B1CC
/* 802D5DE8 002D29C8  4B F9 50 79 */	bl Item_8026AE60
/* 802D5DEC 002D29CC  C0 3F 00 2C */	lfs f1, 0x2c(r31)
/* 802D5DF0 002D29D0  7C 65 1B 78 */	mr r5, r3
/* 802D5DF4 002D29D4  38 7E 00 00 */	addi r3, r30, 0
/* 802D5DF8 002D29D8  38 81 00 10 */	addi r4, r1, 0x10
/* 802D5DFC 002D29DC  48 00 06 BD */	bl it_802D64B8
/* 802D5E00 002D29E0  38 00 00 00 */	li r0, 0
/* 802D5E04 002D29E4  90 1F 0D AC */	stw r0, 0xdac(r31)
.L_802D5E08:
/* 802D5E08 002D29E8  80 1F 0D B0 */	lwz r0, 0xdb0(r31)
/* 802D5E0C 002D29EC  28 00 00 00 */	cmplwi r0, 0
/* 802D5E10 002D29F0  41 82 00 24 */	beq .L_802D5E34
/* 802D5E14 002D29F4  7F C3 F3 78 */	mr r3, r30
/* 802D5E18 002D29F8  4B D8 5A 69 */	bl efLib_DestroyAll
/* 802D5E1C 002D29FC  88 1F 0E 34 */	lbz r0, 0xe34(r31)
/* 802D5E20 002D2A00  38 60 00 01 */	li r3, 1
/* 802D5E24 002D2A04  50 60 36 72 */	rlwimi r0, r3, 6, 0x19, 0x19
/* 802D5E28 002D2A08  98 1F 0E 34 */	stb r0, 0xe34(r31)
/* 802D5E2C 002D2A0C  38 00 00 00 */	li r0, 0
/* 802D5E30 002D2A10  90 1F 0D B0 */	stw r0, 0xdb0(r31)
.L_802D5E34:
/* 802D5E34 002D2A14  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 802D5E38 002D2A18  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 802D5E3C 002D2A1C  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 802D5E40 002D2A20  38 21 00 28 */	addi r1, r1, 0x28
/* 802D5E44 002D2A24  7C 08 03 A6 */	mtlr r0
/* 802D5E48 002D2A28  4E 80 00 20 */	blr

.global it_802D5E4C
it_802D5E4C:
/* 802D5E4C 002D2A2C  7C 08 02 A6 */	mflr r0
/* 802D5E50 002D2A30  90 01 00 04 */	stw r0, 4(r1)
/* 802D5E54 002D2A34  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 802D5E58 002D2A38  93 E1 00 14 */	stw r31, 0x14(r1)
/* 802D5E5C 002D2A3C  93 C1 00 10 */	stw r30, 0x10(r1)
/* 802D5E60 002D2A40  7C 7E 1B 78 */	mr r30, r3
/* 802D5E64 002D2A44  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 802D5E68 002D2A48  7F E3 FB 78 */	mr r3, r31
/* 802D5E6C 002D2A4C  4B FA 04 51 */	bl it_802762BC
/* 802D5E70 002D2A50  38 7E 00 00 */	addi r3, r30, 0
/* 802D5E74 002D2A54  38 80 00 00 */	li r4, 0
/* 802D5E78 002D2A58  38 A0 00 02 */	li r5, 2
/* 802D5E7C 002D2A5C  4B F9 2F E1 */	bl Item_80268E5C
/* 802D5E80 002D2A60  3C 60 80 06 */	lis r3, efLib_PauseAll@ha
/* 802D5E84 002D2A64  38 03 BA 40 */	addi r0, r3, efLib_PauseAll@l
/* 802D5E88 002D2A68  3C 60 80 06 */	lis r3, efLib_ResumeAll@ha
/* 802D5E8C 002D2A6C  90 1F 0D 28 */	stw r0, 0xd28(r31)
/* 802D5E90 002D2A70  38 03 BA C4 */	addi r0, r3, efLib_ResumeAll@l
/* 802D5E94 002D2A74  90 1F 0D 2C */	stw r0, 0xd2c(r31)
/* 802D5E98 002D2A78  38 7E 00 00 */	addi r3, r30, 0
/* 802D5E9C 002D2A7C  38 80 00 00 */	li r4, 0
/* 802D5EA0 002D2A80  C0 22 DB 40 */	lfs f1, it_804DD520@sda21(r2)
/* 802D5EA4 002D2A84  4B F9 D7 CD */	bl it_80273670
/* 802D5EA8 002D2A88  7F C3 F3 78 */	mr r3, r30
/* 802D5EAC 002D2A8C  4B F9 5F 09 */	bl it_8026BDB4
/* 802D5EB0 002D2A90  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 802D5EB4 002D2A94  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 802D5EB8 002D2A98  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 802D5EBC 002D2A9C  38 21 00 18 */	addi r1, r1, 0x18
/* 802D5EC0 002D2AA0  7C 08 03 A6 */	mtlr r0
/* 802D5EC4 002D2AA4  4E 80 00 20 */	blr

.global it_802D5EC8
it_802D5EC8:
/* 802D5EC8 002D2AA8  7C 08 02 A6 */	mflr r0
/* 802D5ECC 002D2AAC  90 01 00 04 */	stw r0, 4(r1)
/* 802D5ED0 002D2AB0  94 21 FF F8 */	stwu r1, -8(r1)
/* 802D5ED4 002D2AB4  4B FA 41 25 */	bl it_80279FF8
/* 802D5ED8 002D2AB8  38 60 00 00 */	li r3, 0
/* 802D5EDC 002D2ABC  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802D5EE0 002D2AC0  38 21 00 08 */	addi r1, r1, 8
/* 802D5EE4 002D2AC4  7C 08 03 A6 */	mtlr r0
/* 802D5EE8 002D2AC8  4E 80 00 20 */	blr

.global it_802D5EEC
it_802D5EEC:
/* 802D5EEC 002D2ACC  7C 08 02 A6 */	mflr r0
/* 802D5EF0 002D2AD0  90 01 00 04 */	stw r0, 4(r1)
/* 802D5EF4 002D2AD4  94 21 FF F8 */	stwu r1, -8(r1)
/* 802D5EF8 002D2AD8  4B FA 41 A5 */	bl it_8027A09C
/* 802D5EFC 002D2ADC  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802D5F00 002D2AE0  38 21 00 08 */	addi r1, r1, 8
/* 802D5F04 002D2AE4  7C 08 03 A6 */	mtlr r0
/* 802D5F08 002D2AE8  4E 80 00 20 */	blr

.global it_802D5F0C
it_802D5F0C:
/* 802D5F0C 002D2AEC  7C 08 02 A6 */	mflr r0
/* 802D5F10 002D2AF0  3C 80 80 2D */	lis r4, it_802D5F34@ha
/* 802D5F14 002D2AF4  90 01 00 04 */	stw r0, 4(r1)
/* 802D5F18 002D2AF8  38 84 5F 34 */	addi r4, r4, it_802D5F34@l
/* 802D5F1C 002D2AFC  94 21 FF F8 */	stwu r1, -8(r1)
/* 802D5F20 002D2B00  4B FA 41 F9 */	bl it_8027A118
/* 802D5F24 002D2B04  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802D5F28 002D2B08  38 21 00 08 */	addi r1, r1, 8
/* 802D5F2C 002D2B0C  7C 08 03 A6 */	mtlr r0
/* 802D5F30 002D2B10  4E 80 00 20 */	blr

.global it_802D5F34
it_802D5F34:
/* 802D5F34 002D2B14  7C 08 02 A6 */	mflr r0
/* 802D5F38 002D2B18  38 80 00 01 */	li r4, 1
/* 802D5F3C 002D2B1C  90 01 00 04 */	stw r0, 4(r1)
/* 802D5F40 002D2B20  38 A0 00 02 */	li r5, 2
/* 802D5F44 002D2B24  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 802D5F48 002D2B28  93 E1 00 14 */	stw r31, 0x14(r1)
/* 802D5F4C 002D2B2C  93 C1 00 10 */	stw r30, 0x10(r1)
/* 802D5F50 002D2B30  7C 7E 1B 78 */	mr r30, r3
/* 802D5F54 002D2B34  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 802D5F58 002D2B38  4B F9 2F 05 */	bl Item_80268E5C
/* 802D5F5C 002D2B3C  3C 60 80 06 */	lis r3, efLib_PauseAll@ha
/* 802D5F60 002D2B40  38 03 BA 40 */	addi r0, r3, efLib_PauseAll@l
/* 802D5F64 002D2B44  3C 60 80 06 */	lis r3, efLib_ResumeAll@ha
/* 802D5F68 002D2B48  90 1F 0D 28 */	stw r0, 0xd28(r31)
/* 802D5F6C 002D2B4C  38 03 BA C4 */	addi r0, r3, efLib_ResumeAll@l
/* 802D5F70 002D2B50  90 1F 0D 2C */	stw r0, 0xd2c(r31)
/* 802D5F74 002D2B54  7F C3 F3 78 */	mr r3, r30
/* 802D5F78 002D2B58  4B F9 F7 69 */	bl it_802756E0
/* 802D5F7C 002D2B5C  7F C3 F3 78 */	mr r3, r30
/* 802D5F80 002D2B60  4B F9 F5 55 */	bl it_802754D4
/* 802D5F84 002D2B64  7F C3 F3 78 */	mr r3, r30
/* 802D5F88 002D2B68  4B F9 F5 35 */	bl it_802754BC
/* 802D5F8C 002D2B6C  7F C3 F3 78 */	mr r3, r30
/* 802D5F90 002D2B70  4B F9 D4 C5 */	bl it_80273454
/* 802D5F94 002D2B74  3C 60 80 2D */	lis r3, it_802D5D7C@ha
/* 802D5F98 002D2B78  38 03 5D 7C */	addi r0, r3, it_802D5D7C@l
/* 802D5F9C 002D2B7C  90 1F 0D 20 */	stw r0, 0xd20(r31)
/* 802D5FA0 002D2B80  38 60 00 01 */	li r3, 1
/* 802D5FA4 002D2B84  88 1F 0D D1 */	lbz r0, 0xdd1(r31)
/* 802D5FA8 002D2B88  50 60 36 72 */	rlwimi r0, r3, 6, 0x19, 0x19
/* 802D5FAC 002D2B8C  98 1F 0D D1 */	stb r0, 0xdd1(r31)
/* 802D5FB0 002D2B90  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 802D5FB4 002D2B94  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 802D5FB8 002D2B98  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 802D5FBC 002D2B9C  38 21 00 18 */	addi r1, r1, 0x18
/* 802D5FC0 002D2BA0  7C 08 03 A6 */	mtlr r0
/* 802D5FC4 002D2BA4  4E 80 00 20 */	blr

.global it_802D5FC8
it_802D5FC8:
/* 802D5FC8 002D2BA8  7C 08 02 A6 */	mflr r0
/* 802D5FCC 002D2BAC  90 01 00 04 */	stw r0, 4(r1)
/* 802D5FD0 002D2BB0  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 802D5FD4 002D2BB4  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 802D5FD8 002D2BB8  93 C1 00 18 */	stw r30, 0x18(r1)
/* 802D5FDC 002D2BBC  93 A1 00 14 */	stw r29, 0x14(r1)
/* 802D5FE0 002D2BC0  7C 7D 1B 78 */	mr r29, r3
/* 802D5FE4 002D2BC4  80 A3 00 2C */	lwz r5, 0x2c(r3)
/* 802D5FE8 002D2BC8  80 85 00 C4 */	lwz r4, 0xc4(r5)
/* 802D5FEC 002D2BCC  7C BF 2B 78 */	mr r31, r5
/* 802D5FF0 002D2BD0  83 C4 00 04 */	lwz r30, 4(r4)
/* 802D5FF4 002D2BD4  4B F9 CC 79 */	bl it_80272C6C
/* 802D5FF8 002D2BD8  2C 03 00 00 */	cmpwi r3, 0
/* 802D5FFC 002D2BDC  40 82 00 0C */	bne .L_802D6008
/* 802D6000 002D2BE0  38 60 00 01 */	li r3, 1
/* 802D6004 002D2BE4  48 00 00 64 */	b .L_802D6068
.L_802D6008:
/* 802D6008 002D2BE8  88 7F 0E 34 */	lbz r3, 0xe34(r31)
/* 802D600C 002D2BEC  54 60 CF FF */	rlwinm. r0, r3, 0x19, 0x1f, 0x1f
/* 802D6010 002D2BF0  41 82 00 44 */	beq .L_802D6054
/* 802D6014 002D2BF4  54 60 D7 FF */	rlwinm. r0, r3, 0x1a, 0x1f, 0x1f
/* 802D6018 002D2BF8  40 82 00 3C */	bne .L_802D6054
/* 802D601C 002D2BFC  C0 3F 0E 38 */	lfs f1, 0xe38(r31)
/* 802D6020 002D2C00  C0 02 DB 40 */	lfs f0, it_804DD520@sda21(r2)
/* 802D6024 002D2C04  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 802D6028 002D2C08  40 82 00 1C */	bne .L_802D6044
/* 802D602C 002D2C0C  C0 1E 00 08 */	lfs f0, 8(r30)
/* 802D6030 002D2C10  38 7D 00 00 */	addi r3, r29, 0
/* 802D6034 002D2C14  38 80 00 03 */	li r4, 3
/* 802D6038 002D2C18  D0 1F 0E 38 */	stfs f0, 0xe38(r31)
/* 802D603C 002D2C1C  38 A0 27 35 */	li r5, 0x2735
/* 802D6040 002D2C20  4B F9 F2 99 */	bl it_802752D8
.L_802D6044:
/* 802D6044 002D2C24  C0 3F 0E 38 */	lfs f1, 0xe38(r31)
/* 802D6048 002D2C28  C0 02 DB 44 */	lfs f0, it_804DD524@sda21(r2)
/* 802D604C 002D2C2C  EC 01 00 28 */	fsubs f0, f1, f0
/* 802D6050 002D2C30  D0 1F 0E 38 */	stfs f0, 0xe38(r31)
.L_802D6054:
/* 802D6054 002D2C34  80 7F 0B BC */	lwz r3, 0xbbc(r31)
/* 802D6058 002D2C38  7F E4 FB 78 */	mr r4, r31
/* 802D605C 002D2C3C  80 63 00 04 */	lwz r3, 4(r3)
/* 802D6060 002D2C40  4B FA 41 01 */	bl it_8027A160
/* 802D6064 002D2C44  38 60 00 00 */	li r3, 0
.L_802D6068:
/* 802D6068 002D2C48  80 01 00 24 */	lwz r0, 0x24(r1)
/* 802D606C 002D2C4C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 802D6070 002D2C50  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 802D6074 002D2C54  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 802D6078 002D2C58  38 21 00 20 */	addi r1, r1, 0x20
/* 802D607C 002D2C5C  7C 08 03 A6 */	mtlr r0
/* 802D6080 002D2C60  4E 80 00 20 */	blr

.global it_802D6084
it_802D6084:
/* 802D6084 002D2C64  7C 08 02 A6 */	mflr r0
/* 802D6088 002D2C68  90 01 00 04 */	stw r0, 4(r1)
/* 802D608C 002D2C6C  94 21 FF F8 */	stwu r1, -8(r1)
/* 802D6090 002D2C70  4B FA 42 B5 */	bl it_8027A344
/* 802D6094 002D2C74  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802D6098 002D2C78  38 21 00 08 */	addi r1, r1, 8
/* 802D609C 002D2C7C  7C 08 03 A6 */	mtlr r0
/* 802D60A0 002D2C80  4E 80 00 20 */	blr

.global it_802D60A4
it_802D60A4:
/* 802D60A4 002D2C84  7C 08 02 A6 */	mflr r0
/* 802D60A8 002D2C88  90 01 00 04 */	stw r0, 4(r1)
/* 802D60AC 002D2C8C  94 21 FF F8 */	stwu r1, -8(r1)
/* 802D60B0 002D2C90  4B F9 79 59 */	bl it_8026DA08
/* 802D60B4 002D2C94  38 60 00 00 */	li r3, 0
/* 802D60B8 002D2C98  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802D60BC 002D2C9C  38 21 00 08 */	addi r1, r1, 8
/* 802D60C0 002D2CA0  7C 08 03 A6 */	mtlr r0
/* 802D60C4 002D2CA4  4E 80 00 20 */	blr

.global it_802D60C8
it_802D60C8:
/* 802D60C8 002D2CA8  38 60 00 00 */	li r3, 0
/* 802D60CC 002D2CAC  4E 80 00 20 */	blr

.global it_802D60D0
it_802D60D0:
/* 802D60D0 002D2CB0  7C 08 02 A6 */	mflr r0
/* 802D60D4 002D2CB4  90 01 00 04 */	stw r0, 4(r1)
/* 802D60D8 002D2CB8  94 21 FF F8 */	stwu r1, -8(r1)
/* 802D60DC 002D2CBC  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 802D60E0 002D2CC0  80 84 00 CC */	lwz r4, 0xcc(r4)
/* 802D60E4 002D2CC4  C0 24 00 10 */	lfs f1, 0x10(r4)
/* 802D60E8 002D2CC8  C0 44 00 14 */	lfs f2, 0x14(r4)
/* 802D60EC 002D2CCC  4B F9 C7 75 */	bl it_80272860
/* 802D60F0 002D2CD0  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802D60F4 002D2CD4  38 21 00 08 */	addi r1, r1, 8
/* 802D60F8 002D2CD8  7C 08 03 A6 */	mtlr r0
/* 802D60FC 002D2CDC  4E 80 00 20 */	blr

.global it_802D6100
it_802D6100:
/* 802D6100 002D2CE0  7C 08 02 A6 */	mflr r0
/* 802D6104 002D2CE4  90 01 00 04 */	stw r0, 4(r1)
/* 802D6108 002D2CE8  3C 00 43 30 */	lis r0, 0x4330
/* 802D610C 002D2CEC  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 802D6110 002D2CF0  93 E1 00 24 */	stw r31, 0x24(r1)
/* 802D6114 002D2CF4  7C 7F 1B 78 */	mr r31, r3
/* 802D6118 002D2CF8  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 802D611C 002D2CFC  C8 42 DB 48 */	lfd f2, it_804DD528@sda21(r2)
/* 802D6120 002D2D00  80 83 0C 9C */	lwz r4, 0xc9c(r3)
/* 802D6124 002D2D04  80 63 00 C4 */	lwz r3, 0xc4(r3)
/* 802D6128 002D2D08  6C 84 80 00 */	xoris r4, r4, 0x8000
/* 802D612C 002D2D0C  90 81 00 1C */	stw r4, 0x1c(r1)
/* 802D6130 002D2D10  80 63 00 04 */	lwz r3, 4(r3)
/* 802D6134 002D2D14  90 01 00 18 */	stw r0, 0x18(r1)
/* 802D6138 002D2D18  C0 03 00 04 */	lfs f0, 4(r3)
/* 802D613C 002D2D1C  C8 21 00 18 */	lfd f1, 0x18(r1)
/* 802D6140 002D2D20  EC 21 10 28 */	fsubs f1, f1, f2
/* 802D6144 002D2D24  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 802D6148 002D2D28  4C 41 13 82 */	cror 2, 1, 2
/* 802D614C 002D2D2C  40 82 00 44 */	bne .L_802D6190
/* 802D6150 002D2D30  7F E3 FB 78 */	mr r3, r31
/* 802D6154 002D2D34  4B FA 3B E5 */	bl it_80279D38
/* 802D6158 002D2D38  80 7F 00 2C */	lwz r3, 0x2c(r31)
/* 802D615C 002D2D3C  4B FA 01 61 */	bl it_802762BC
/* 802D6160 002D2D40  7F E3 FB 78 */	mr r3, r31
/* 802D6164 002D2D44  4B F9 F5 6D */	bl it_802756D0
/* 802D6168 002D2D48  7F E3 FB 78 */	mr r3, r31
/* 802D616C 002D2D4C  4B D8 57 15 */	bl efLib_DestroyAll
/* 802D6170 002D2D50  38 7F 00 00 */	addi r3, r31, 0
/* 802D6174 002D2D54  38 80 00 02 */	li r4, 2
/* 802D6178 002D2D58  38 A0 00 02 */	li r5, 2
/* 802D617C 002D2D5C  4B F9 2C E1 */	bl Item_80268E5C
/* 802D6180 002D2D60  C0 22 DB 40 */	lfs f1, it_804DD520@sda21(r2)
/* 802D6184 002D2D64  38 7F 00 00 */	addi r3, r31, 0
/* 802D6188 002D2D68  38 80 00 00 */	li r4, 0
/* 802D618C 002D2D6C  4B F9 D4 E5 */	bl it_80273670
.L_802D6190:
/* 802D6190 002D2D70  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 802D6194 002D2D74  38 60 00 00 */	li r3, 0
/* 802D6198 002D2D78  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 802D619C 002D2D7C  38 21 00 28 */	addi r1, r1, 0x28
/* 802D61A0 002D2D80  7C 08 03 A6 */	mtlr r0
/* 802D61A4 002D2D84  4E 80 00 20 */	blr

.global it_802D61A8
it_802D61A8:
/* 802D61A8 002D2D88  7C 08 02 A6 */	mflr r0
/* 802D61AC 002D2D8C  90 01 00 04 */	stw r0, 4(r1)
/* 802D61B0 002D2D90  94 21 FF F8 */	stwu r1, -8(r1)
/* 802D61B4 002D2D94  4B F9 56 E1 */	bl it_8026B894
/* 802D61B8 002D2D98  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802D61BC 002D2D9C  38 21 00 08 */	addi r1, r1, 8
/* 802D61C0 002D2DA0  7C 08 03 A6 */	mtlr r0
/* 802D61C4 002D2DA4  4E 80 00 20 */	blr

.global it_802D61C8
it_802D61C8:
/* 802D61C8 002D2DA8  7C 08 02 A6 */	mflr r0
/* 802D61CC 002D2DAC  90 01 00 04 */	stw r0, 4(r1)
/* 802D61D0 002D2DB0  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 802D61D4 002D2DB4  93 E1 00 24 */	stw r31, 0x24(r1)
/* 802D61D8 002D2DB8  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 802D61DC 002D2DBC  C0 02 DB 40 */	lfs f0, it_804DD520@sda21(r2)
/* 802D61E0 002D2DC0  D0 01 00 1C */	stfs f0, 0x1c(r1)
/* 802D61E4 002D2DC4  D0 01 00 18 */	stfs f0, 0x18(r1)
/* 802D61E8 002D2DC8  D0 01 00 14 */	stfs f0, 0x14(r1)
/* 802D61EC 002D2DCC  C8 42 DB 50 */	lfd f2, it_804DD530@sda21(r2)
/* 802D61F0 002D2DD0  C8 02 DB 58 */	lfd f0, it_804DD538@sda21(r2)
/* 802D61F4 002D2DD4  48 00 00 14 */	b .L_802D6208
.L_802D61F8:
/* 802D61F8 002D2DD8  C0 3F 0E 4C */	lfs f1, 0xe4c(r31)
/* 802D61FC 002D2DDC  FC 21 10 2A */	fadd f1, f1, f2
/* 802D6200 002D2DE0  FC 20 08 18 */	frsp f1, f1
/* 802D6204 002D2DE4  D0 3F 0E 4C */	stfs f1, 0xe4c(r31)
.L_802D6208:
/* 802D6208 002D2DE8  C0 3F 0E 4C */	lfs f1, 0xe4c(r31)
/* 802D620C 002D2DEC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 802D6210 002D2DF0  41 80 FF E8 */	blt .L_802D61F8
/* 802D6214 002D2DF4  C8 42 DB 50 */	lfd f2, it_804DD530@sda21(r2)
/* 802D6218 002D2DF8  C8 02 DB 60 */	lfd f0, it_804DD540@sda21(r2)
/* 802D621C 002D2DFC  48 00 00 14 */	b .L_802D6230
.L_802D6220:
/* 802D6220 002D2E00  C0 3F 0E 4C */	lfs f1, 0xe4c(r31)
/* 802D6224 002D2E04  FC 21 10 28 */	fsub f1, f1, f2
/* 802D6228 002D2E08  FC 20 08 18 */	frsp f1, f1
/* 802D622C 002D2E0C  D0 3F 0E 4C */	stfs f1, 0xe4c(r31)
.L_802D6230:
/* 802D6230 002D2E10  C0 3F 0E 4C */	lfs f1, 0xe4c(r31)
/* 802D6234 002D2E14  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 802D6238 002D2E18  41 81 FF E8 */	bgt .L_802D6220
/* 802D623C 002D2E1C  54 80 07 FF */	clrlwi. r0, r4, 0x1f
/* 802D6240 002D2E20  41 82 00 24 */	beq .L_802D6264
/* 802D6244 002D2E24  C0 21 00 14 */	lfs f1, 0x14(r1)
/* 802D6248 002D2E28  C0 1F 04 CC */	lfs f0, 0x4cc(r31)
/* 802D624C 002D2E2C  EC 01 00 2A */	fadds f0, f1, f0
/* 802D6250 002D2E30  D0 01 00 14 */	stfs f0, 0x14(r1)
/* 802D6254 002D2E34  C0 21 00 18 */	lfs f1, 0x18(r1)
/* 802D6258 002D2E38  C0 1F 04 D0 */	lfs f0, 0x4d0(r31)
/* 802D625C 002D2E3C  EC 01 00 2A */	fadds f0, f1, f0
/* 802D6260 002D2E40  D0 01 00 18 */	stfs f0, 0x18(r1)
.L_802D6264:
/* 802D6264 002D2E44  54 80 07 BD */	rlwinm. r0, r4, 0, 0x1e, 0x1e
/* 802D6268 002D2E48  41 82 00 24 */	beq .L_802D628C
/* 802D626C 002D2E4C  C0 21 00 14 */	lfs f1, 0x14(r1)
/* 802D6270 002D2E50  C0 1F 05 08 */	lfs f0, 0x508(r31)
/* 802D6274 002D2E54  EC 01 00 2A */	fadds f0, f1, f0
/* 802D6278 002D2E58  D0 01 00 14 */	stfs f0, 0x14(r1)
/* 802D627C 002D2E5C  C0 21 00 18 */	lfs f1, 0x18(r1)
/* 802D6280 002D2E60  C0 1F 05 0C */	lfs f0, 0x50c(r31)
/* 802D6284 002D2E64  EC 01 00 2A */	fadds f0, f1, f0
/* 802D6288 002D2E68  D0 01 00 18 */	stfs f0, 0x18(r1)
.L_802D628C:
/* 802D628C 002D2E6C  54 80 07 39 */	rlwinm. r0, r4, 0, 0x1c, 0x1c
/* 802D6290 002D2E70  41 82 00 24 */	beq .L_802D62B4
/* 802D6294 002D2E74  C0 21 00 14 */	lfs f1, 0x14(r1)
/* 802D6298 002D2E78  C0 1F 04 E0 */	lfs f0, 0x4e0(r31)
/* 802D629C 002D2E7C  EC 01 00 2A */	fadds f0, f1, f0
/* 802D62A0 002D2E80  D0 01 00 14 */	stfs f0, 0x14(r1)
/* 802D62A4 002D2E84  C0 21 00 18 */	lfs f1, 0x18(r1)
/* 802D62A8 002D2E88  C0 1F 04 E4 */	lfs f0, 0x4e4(r31)
/* 802D62AC 002D2E8C  EC 01 00 2A */	fadds f0, f1, f0
/* 802D62B0 002D2E90  D0 01 00 18 */	stfs f0, 0x18(r1)
.L_802D62B4:
/* 802D62B4 002D2E94  54 80 07 7B */	rlwinm. r0, r4, 0, 0x1d, 0x1d
/* 802D62B8 002D2E98  41 82 00 24 */	beq .L_802D62DC
/* 802D62BC 002D2E9C  C0 21 00 14 */	lfs f1, 0x14(r1)
/* 802D62C0 002D2EA0  C0 1F 04 F4 */	lfs f0, 0x4f4(r31)
/* 802D62C4 002D2EA4  EC 01 00 2A */	fadds f0, f1, f0
/* 802D62C8 002D2EA8  D0 01 00 14 */	stfs f0, 0x14(r1)
/* 802D62CC 002D2EAC  C0 21 00 18 */	lfs f1, 0x18(r1)
/* 802D62D0 002D2EB0  C0 1F 04 F8 */	lfs f0, 0x4f8(r31)
/* 802D62D4 002D2EB4  EC 01 00 2A */	fadds f0, f1, f0
/* 802D62D8 002D2EB8  D0 01 00 18 */	stfs f0, 0x18(r1)
.L_802D62DC:
/* 802D62DC 002D2EBC  38 61 00 14 */	addi r3, r1, 0x14
/* 802D62E0 002D2EC0  4B D3 70 0D */	bl lbVector_Normalize
/* 802D62E4 002D2EC4  80 61 00 14 */	lwz r3, 0x14(r1)
/* 802D62E8 002D2EC8  80 01 00 18 */	lwz r0, 0x18(r1)
/* 802D62EC 002D2ECC  90 7F 0E 34 */	stw r3, 0xe34(r31)
/* 802D62F0 002D2ED0  90 1F 0E 38 */	stw r0, 0xe38(r31)
/* 802D62F4 002D2ED4  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 802D62F8 002D2ED8  90 1F 0E 3C */	stw r0, 0xe3c(r31)
/* 802D62FC 002D2EDC  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 802D6300 002D2EE0  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 802D6304 002D2EE4  38 21 00 28 */	addi r1, r1, 0x28
/* 802D6308 002D2EE8  7C 08 03 A6 */	mtlr r0
/* 802D630C 002D2EEC  4E 80 00 20 */	blr

.global it_802D6310
it_802D6310:
/* 802D6310 002D2EF0  7C 08 02 A6 */	mflr r0
/* 802D6314 002D2EF4  2C 04 00 00 */	cmpwi r4, 0
/* 802D6318 002D2EF8  90 01 00 04 */	stw r0, 4(r1)
/* 802D631C 002D2EFC  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 802D6320 002D2F00  DB E1 00 20 */	stfd f31, 0x20(r1)
/* 802D6324 002D2F04  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 802D6328 002D2F08  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 802D632C 002D2F0C  41 82 01 74 */	beq .L_802D64A0
/* 802D6330 002D2F10  C0 3F 0E 34 */	lfs f1, 0xe34(r31)
/* 802D6334 002D2F14  C0 5F 0E 38 */	lfs f2, 0xe38(r31)
/* 802D6338 002D2F18  4B D4 C8 F9 */	bl atan2f
/* 802D633C 002D2F1C  FF E0 08 90 */	fmr f31, f1
/* 802D6340 002D2F20  C0 3F 0E 40 */	lfs f1, 0xe40(r31)
/* 802D6344 002D2F24  C0 5F 0E 44 */	lfs f2, 0xe44(r31)
/* 802D6348 002D2F28  4B D4 C8 E9 */	bl atan2f
/* 802D634C 002D2F2C  EF E1 F8 28 */	fsubs f31, f1, f31
/* 802D6350 002D2F30  C8 22 DB 50 */	lfd f1, it_804DD530@sda21(r2)
/* 802D6354 002D2F34  C8 02 DB 60 */	lfd f0, it_804DD540@sda21(r2)
/* 802D6358 002D2F38  48 00 00 0C */	b .L_802D6364
.L_802D635C:
/* 802D635C 002D2F3C  FF FF 08 28 */	fsub f31, f31, f1
/* 802D6360 002D2F40  FF E0 F8 18 */	frsp f31, f31
.L_802D6364:
/* 802D6364 002D2F44  FC 1F 00 40 */	fcmpo cr0, f31, f0
/* 802D6368 002D2F48  41 81 FF F4 */	bgt .L_802D635C
/* 802D636C 002D2F4C  C8 22 DB 50 */	lfd f1, it_804DD530@sda21(r2)
/* 802D6370 002D2F50  C8 02 DB 58 */	lfd f0, it_804DD538@sda21(r2)
/* 802D6374 002D2F54  48 00 00 0C */	b .L_802D6380
.L_802D6378:
/* 802D6378 002D2F58  FF FF 08 2A */	fadd f31, f31, f1
/* 802D637C 002D2F5C  FF E0 F8 18 */	frsp f31, f31
.L_802D6380:
/* 802D6380 002D2F60  FC 1F 00 40 */	fcmpo cr0, f31, f0
/* 802D6384 002D2F64  41 80 FF F4 */	blt .L_802D6378
/* 802D6388 002D2F68  C0 02 DB 40 */	lfs f0, it_804DD520@sda21(r2)
/* 802D638C 002D2F6C  FC 00 F8 00 */	fcmpu cr0, f0, f31
/* 802D6390 002D2F70  40 82 00 0C */	bne .L_802D639C
/* 802D6394 002D2F74  FC 20 00 90 */	fmr f1, f0
/* 802D6398 002D2F78  48 00 00 AC */	b .L_802D6444
.L_802D639C:
/* 802D639C 002D2F7C  38 7F 0E 34 */	addi r3, r31, 0xe34
/* 802D63A0 002D2F80  38 9F 0E 40 */	addi r4, r31, 0xe40
/* 802D63A4 002D2F84  4B D3 72 7D */	bl lbVector_Angle
/* 802D63A8 002D2F88  C0 02 DB 40 */	lfs f0, it_804DD520@sda21(r2)
/* 802D63AC 002D2F8C  FC 1F 00 40 */	fcmpo cr0, f31, f0
/* 802D63B0 002D2F90  40 80 00 0C */	bge .L_802D63BC
/* 802D63B4 002D2F94  FC 40 F8 50 */	fneg f2, f31
/* 802D63B8 002D2F98  48 00 00 08 */	b .L_802D63C0
.L_802D63BC:
/* 802D63BC 002D2F9C  FC 40 F8 90 */	fmr f2, f31
.L_802D63C0:
/* 802D63C0 002D2FA0  C8 02 DB 68 */	lfd f0, it_804DD548@sda21(r2)
/* 802D63C4 002D2FA4  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 802D63C8 002D2FA8  40 80 00 34 */	bge .L_802D63FC
/* 802D63CC 002D2FAC  C0 02 DB 40 */	lfs f0, it_804DD520@sda21(r2)
/* 802D63D0 002D2FB0  FC 1F 00 40 */	fcmpo cr0, f31, f0
/* 802D63D4 002D2FB4  40 80 00 0C */	bge .L_802D63E0
/* 802D63D8 002D2FB8  FC 60 F8 50 */	fneg f3, f31
/* 802D63DC 002D2FBC  48 00 00 08 */	b .L_802D63E4
.L_802D63E0:
/* 802D63E0 002D2FC0  FC 60 F8 90 */	fmr f3, f31
.L_802D63E4:
/* 802D63E4 002D2FC4  C8 02 DB 60 */	lfd f0, it_804DD540@sda21(r2)
/* 802D63E8 002D2FC8  C8 42 DB 70 */	lfd f2, it_804DD550@sda21(r2)
/* 802D63EC 002D2FCC  FC 03 00 24 */	fdiv f0, f3, f0
/* 802D63F0 002D2FD0  FC 42 00 32 */	fmul f2, f2, f0
/* 802D63F4 002D2FD4  FC 40 10 18 */	frsp f2, f2
/* 802D63F8 002D2FD8  48 00 00 30 */	b .L_802D6428
.L_802D63FC:
/* 802D63FC 002D2FDC  C0 02 DB 40 */	lfs f0, it_804DD520@sda21(r2)
/* 802D6400 002D2FE0  FC 1F 00 40 */	fcmpo cr0, f31, f0
/* 802D6404 002D2FE4  40 80 00 0C */	bge .L_802D6410
/* 802D6408 002D2FE8  FC 60 F8 50 */	fneg f3, f31
/* 802D640C 002D2FEC  48 00 00 08 */	b .L_802D6414
.L_802D6410:
/* 802D6410 002D2FF0  FC 60 F8 90 */	fmr f3, f31
.L_802D6414:
/* 802D6414 002D2FF4  C8 02 DB 60 */	lfd f0, it_804DD540@sda21(r2)
/* 802D6418 002D2FF8  C8 42 DB 78 */	lfd f2, it_804DD558@sda21(r2)
/* 802D641C 002D2FFC  FC 03 00 24 */	fdiv f0, f3, f0
/* 802D6420 002D3000  FC 42 00 32 */	fmul f2, f2, f0
/* 802D6424 002D3004  FC 40 10 18 */	frsp f2, f2
.L_802D6428:
/* 802D6428 002D3008  C0 02 DB 40 */	lfs f0, it_804DD520@sda21(r2)
/* 802D642C 002D300C  FC 1F 00 40 */	fcmpo cr0, f31, f0
/* 802D6430 002D3010  40 80 00 0C */	bge .L_802D643C
/* 802D6434 002D3014  FC 00 10 50 */	fneg f0, f2
/* 802D6438 002D3018  48 00 00 08 */	b .L_802D6440
.L_802D643C:
/* 802D643C 002D301C  FC 00 10 90 */	fmr f0, f2
.L_802D6440:
/* 802D6440 002D3020  EC 21 00 32 */	fmuls f1, f1, f0
.L_802D6444:
/* 802D6444 002D3024  C0 1F 0E 4C */	lfs f0, 0xe4c(r31)
/* 802D6448 002D3028  EC 00 08 28 */	fsubs f0, f0, f1
/* 802D644C 002D302C  D0 1F 0E 4C */	stfs f0, 0xe4c(r31)
/* 802D6450 002D3030  C8 42 DB 50 */	lfd f2, it_804DD530@sda21(r2)
/* 802D6454 002D3034  C8 02 DB 58 */	lfd f0, it_804DD538@sda21(r2)
/* 802D6458 002D3038  48 00 00 14 */	b .L_802D646C
.L_802D645C:
/* 802D645C 002D303C  C0 3F 0E 4C */	lfs f1, 0xe4c(r31)
/* 802D6460 002D3040  FC 21 10 2A */	fadd f1, f1, f2
/* 802D6464 002D3044  FC 20 08 18 */	frsp f1, f1
/* 802D6468 002D3048  D0 3F 0E 4C */	stfs f1, 0xe4c(r31)
.L_802D646C:
/* 802D646C 002D304C  C0 3F 0E 4C */	lfs f1, 0xe4c(r31)
/* 802D6470 002D3050  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 802D6474 002D3054  41 80 FF E8 */	blt .L_802D645C
/* 802D6478 002D3058  C8 42 DB 50 */	lfd f2, it_804DD530@sda21(r2)
/* 802D647C 002D305C  C8 02 DB 60 */	lfd f0, it_804DD540@sda21(r2)
/* 802D6480 002D3060  48 00 00 14 */	b .L_802D6494
.L_802D6484:
/* 802D6484 002D3064  C0 3F 0E 4C */	lfs f1, 0xe4c(r31)
/* 802D6488 002D3068  FC 21 10 28 */	fsub f1, f1, f2
/* 802D648C 002D306C  FC 20 08 18 */	frsp f1, f1
/* 802D6490 002D3070  D0 3F 0E 4C */	stfs f1, 0xe4c(r31)
.L_802D6494:
/* 802D6494 002D3074  C0 3F 0E 4C */	lfs f1, 0xe4c(r31)
/* 802D6498 002D3078  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 802D649C 002D307C  41 81 FF E8 */	bgt .L_802D6484
.L_802D64A0:
/* 802D64A0 002D3080  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 802D64A4 002D3084  CB E1 00 20 */	lfd f31, 0x20(r1)
/* 802D64A8 002D3088  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 802D64AC 002D308C  38 21 00 28 */	addi r1, r1, 0x28
/* 802D64B0 002D3090  7C 08 03 A6 */	mtlr r0
/* 802D64B4 002D3094  4E 80 00 20 */	blr

.global it_802D64B8
it_802D64B8:
/* 802D64B8 002D3098  7C 08 02 A6 */	mflr r0
/* 802D64BC 002D309C  90 01 00 04 */	stw r0, 4(r1)
/* 802D64C0 002D30A0  38 00 00 CE */	li r0, 0xce
/* 802D64C4 002D30A4  94 21 FF 70 */	stwu r1, -0x90(r1)
/* 802D64C8 002D30A8  DB E1 00 88 */	stfd f31, 0x88(r1)
/* 802D64CC 002D30AC  DB C1 00 80 */	stfd f30, 0x80(r1)
/* 802D64D0 002D30B0  FF C0 08 90 */	fmr f30, f1
/* 802D64D4 002D30B4  93 E1 00 7C */	stw r31, 0x7c(r1)
/* 802D64D8 002D30B8  93 C1 00 78 */	stw r30, 0x78(r1)
/* 802D64DC 002D30BC  7C 7E 1B 78 */	mr r30, r3
/* 802D64E0 002D30C0  93 A1 00 74 */	stw r29, 0x74(r1)
/* 802D64E4 002D30C4  7C BD 2B 78 */	mr r29, r5
/* 802D64E8 002D30C8  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 802D64EC 002D30CC  C0 02 DB 40 */	lfs f0, it_804DD520@sda21(r2)
/* 802D64F0 002D30D0  90 01 00 28 */	stw r0, 0x28(r1)
/* 802D64F4 002D30D4  80 A4 00 00 */	lwz r5, 0(r4)
/* 802D64F8 002D30D8  80 04 00 04 */	lwz r0, 4(r4)
/* 802D64FC 002D30DC  90 A1 00 40 */	stw r5, 0x40(r1)
/* 802D6500 002D30E0  90 01 00 44 */	stw r0, 0x44(r1)
/* 802D6504 002D30E4  80 04 00 08 */	lwz r0, 8(r4)
/* 802D6508 002D30E8  38 81 00 34 */	addi r4, r1, 0x34
/* 802D650C 002D30EC  90 01 00 48 */	stw r0, 0x48(r1)
/* 802D6510 002D30F0  D0 01 00 48 */	stfs f0, 0x48(r1)
/* 802D6514 002D30F4  4B F9 56 75 */	bl it_8026BB88
/* 802D6518 002D30F8  D3 C1 00 58 */	stfs f30, 0x58(r1)
/* 802D651C 002D30FC  38 00 00 00 */	li r0, 0
/* 802D6520 002D3100  C0 02 DB 40 */	lfs f0, it_804DD520@sda21(r2)
/* 802D6524 002D3104  38 80 00 01 */	li r4, 1
/* 802D6528 002D3108  B0 01 00 5C */	sth r0, 0x5c(r1)
/* 802D652C 002D310C  38 61 00 20 */	addi r3, r1, 0x20
/* 802D6530 002D3110  D0 01 00 54 */	stfs f0, 0x54(r1)
/* 802D6534 002D3114  D0 01 00 50 */	stfs f0, 0x50(r1)
/* 802D6538 002D3118  D0 01 00 4C */	stfs f0, 0x4c(r1)
/* 802D653C 002D311C  80 1F 05 18 */	lwz r0, 0x518(r31)
/* 802D6540 002D3120  90 01 00 20 */	stw r0, 0x20(r1)
/* 802D6544 002D3124  93 C1 00 24 */	stw r30, 0x24(r1)
/* 802D6548 002D3128  88 01 00 64 */	lbz r0, 0x64(r1)
/* 802D654C 002D312C  50 80 3E 30 */	rlwimi r0, r4, 7, 0x18, 0x18
/* 802D6550 002D3130  98 01 00 64 */	stb r0, 0x64(r1)
/* 802D6554 002D3134  93 A1 00 60 */	stw r29, 0x60(r1)
/* 802D6558 002D3138  4B F9 25 C1 */	bl Item_80268B18
/* 802D655C 002D313C  7C 7F 1B 79 */	or. r31, r3, r3
/* 802D6560 002D3140  41 82 00 F0 */	beq .L_802D6650
/* 802D6564 002D3144  83 DF 00 2C */	lwz r30, 0x2c(r31)
/* 802D6568 002D3148  7F E3 FB 78 */	mr r3, r31
/* 802D656C 002D314C  80 9E 00 C4 */	lwz r4, 0xc4(r30)
/* 802D6570 002D3150  83 A4 00 04 */	lwz r29, 4(r4)
/* 802D6574 002D3154  C0 3D 00 00 */	lfs f1, 0(r29)
/* 802D6578 002D3158  4B F9 EB E1 */	bl it_80275158
/* 802D657C 002D315C  48 0A 9F AD */	bl HSD_Randf
/* 802D6580 002D3160  C0 9D 00 10 */	lfs f4, 0x10(r29)
/* 802D6584 002D3164  C0 7D 00 14 */	lfs f3, 0x14(r29)
/* 802D6588 002D3168  C0 42 DB 44 */	lfs f2, it_804DD524@sda21(r2)
/* 802D658C 002D316C  C0 1E 00 2C */	lfs f0, 0x2c(r30)
/* 802D6590 002D3170  EC 63 20 28 */	fsubs f3, f3, f4
/* 802D6594 002D3174  FC 02 00 00 */	fcmpu cr0, f2, f0
/* 802D6598 002D3178  EC 03 20 7A */	fmadds f0, f3, f1, f4
/* 802D659C 002D317C  40 82 00 0C */	bne .L_802D65A8
/* 802D65A0 002D3180  FC 40 00 90 */	fmr f2, f0
/* 802D65A4 002D3184  48 00 00 08 */	b .L_802D65AC
.L_802D65A8:
/* 802D65A8 002D3188  FC 40 00 50 */	fneg f2, f0
.L_802D65AC:
/* 802D65AC 002D318C  C8 02 DB 68 */	lfd f0, it_804DD548@sda21(r2)
/* 802D65B0 002D3190  C8 22 DB 50 */	lfd f1, it_804DD530@sda21(r2)
/* 802D65B4 002D3194  FF E2 00 28 */	fsub f31, f2, f0
/* 802D65B8 002D3198  C0 02 DB 40 */	lfs f0, it_804DD520@sda21(r2)
/* 802D65BC 002D319C  FF E0 F8 18 */	frsp f31, f31
/* 802D65C0 002D31A0  48 00 00 0C */	b .L_802D65CC
.L_802D65C4:
/* 802D65C4 002D31A4  FF FF 08 2A */	fadd f31, f31, f1
/* 802D65C8 002D31A8  FF E0 F8 18 */	frsp f31, f31
.L_802D65CC:
/* 802D65CC 002D31AC  FC 1F 00 40 */	fcmpo cr0, f31, f0
/* 802D65D0 002D31B0  41 80 FF F4 */	blt .L_802D65C4
/* 802D65D4 002D31B4  C8 02 DB 50 */	lfd f0, it_804DD530@sda21(r2)
/* 802D65D8 002D31B8  48 00 00 0C */	b .L_802D65E4
.L_802D65DC:
/* 802D65DC 002D31BC  FF FF 00 28 */	fsub f31, f31, f0
/* 802D65E0 002D31C0  FF E0 F8 18 */	frsp f31, f31
.L_802D65E4:
/* 802D65E4 002D31C4  FC 1F 00 40 */	fcmpo cr0, f31, f0
/* 802D65E8 002D31C8  41 81 FF F4 */	bgt .L_802D65DC
/* 802D65EC 002D31CC  D3 FE 0E 4C */	stfs f31, 0xe4c(r30)
/* 802D65F0 002D31D0  48 0A 9F 39 */	bl HSD_Randf
/* 802D65F4 002D31D4  C0 5D 00 04 */	lfs f2, 4(r29)
/* 802D65F8 002D31D8  C0 1D 00 08 */	lfs f0, 8(r29)
/* 802D65FC 002D31DC  EC 00 10 28 */	fsubs f0, f0, f2
/* 802D6600 002D31E0  EF C0 10 7A */	fmadds f30, f0, f1, f2
/* 802D6604 002D31E4  FC 20 F8 90 */	fmr f1, f31
/* 802D6608 002D31E8  48 04 FC 39 */	bl cosf
/* 802D660C 002D31EC  EC 1E 00 72 */	fmuls f0, f30, f1
/* 802D6610 002D31F0  FC 20 F8 90 */	fmr f1, f31
/* 802D6614 002D31F4  D0 1E 00 40 */	stfs f0, 0x40(r30)
/* 802D6618 002D31F8  48 04 FD BD */	bl sinf
/* 802D661C 002D31FC  EC 1E 00 72 */	fmuls f0, f30, f1
/* 802D6620 002D3200  38 80 00 00 */	li r4, 0
/* 802D6624 002D3204  38 60 00 04 */	li r3, 4
/* 802D6628 002D3208  D0 1E 00 44 */	stfs f0, 0x44(r30)
/* 802D662C 002D320C  C0 02 DB 40 */	lfs f0, it_804DD520@sda21(r2)
/* 802D6630 002D3210  D0 1E 00 48 */	stfs f0, 0x48(r30)
/* 802D6634 002D3214  88 1E 0D CC */	lbz r0, 0xdcc(r30)
/* 802D6638 002D3218  50 80 26 F6 */	rlwimi r0, r4, 4, 0x1b, 0x1b
/* 802D663C 002D321C  98 1E 0D CC */	stb r0, 0xdcc(r30)
/* 802D6640 002D3220  48 0A 9F 41 */	bl HSD_Randi
/* 802D6644 002D3224  38 83 00 00 */	addi r4, r3, 0
/* 802D6648 002D3228  38 7F 00 00 */	addi r3, r31, 0
/* 802D664C 002D322C  48 00 00 29 */	bl it_802D6674
.L_802D6650:
/* 802D6650 002D3230  80 01 00 94 */	lwz r0, 0x94(r1)
/* 802D6654 002D3234  CB E1 00 88 */	lfd f31, 0x88(r1)
/* 802D6658 002D3238  CB C1 00 80 */	lfd f30, 0x80(r1)
/* 802D665C 002D323C  83 E1 00 7C */	lwz r31, 0x7c(r1)
/* 802D6660 002D3240  83 C1 00 78 */	lwz r30, 0x78(r1)
/* 802D6664 002D3244  83 A1 00 74 */	lwz r29, 0x74(r1)
/* 802D6668 002D3248  38 21 00 90 */	addi r1, r1, 0x90
/* 802D666C 002D324C  7C 08 03 A6 */	mtlr r0
/* 802D6670 002D3250  4E 80 00 20 */	blr

.global it_802D6674
it_802D6674:
/* 802D6674 002D3254  7C 08 02 A6 */	mflr r0
/* 802D6678 002D3258  38 A0 00 02 */	li r5, 2
/* 802D667C 002D325C  90 01 00 04 */	stw r0, 4(r1)
/* 802D6680 002D3260  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 802D6684 002D3264  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 802D6688 002D3268  93 C1 00 28 */	stw r30, 0x28(r1)
/* 802D668C 002D326C  93 A1 00 24 */	stw r29, 0x24(r1)
/* 802D6690 002D3270  7C 9D 23 78 */	mr r29, r4
/* 802D6694 002D3274  38 80 00 00 */	li r4, 0
/* 802D6698 002D3278  93 81 00 20 */	stw r28, 0x20(r1)
/* 802D669C 002D327C  7C 7C 1B 78 */	mr r28, r3
/* 802D66A0 002D3280  C0 02 DB 44 */	lfs f0, it_804DD524@sda21(r2)
/* 802D66A4 002D3284  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 802D66A8 002D3288  83 C3 00 28 */	lwz r30, 0x28(r3)
/* 802D66AC 002D328C  D0 01 00 18 */	stfs f0, 0x18(r1)
/* 802D66B0 002D3290  4B F9 27 AD */	bl Item_80268E5C
/* 802D66B4 002D3294  38 9C 00 00 */	addi r4, r28, 0
/* 802D66B8 002D3298  4C C6 31 82 */	crclr 6
/* 802D66BC 002D329C  38 BE 00 00 */	addi r5, r30, 0
/* 802D66C0 002D32A0  38 7D 04 4E */	addi r3, r29, 0x44e
/* 802D66C4 002D32A4  38 DF 00 2C */	addi r6, r31, 0x2c
/* 802D66C8 002D32A8  38 E1 00 18 */	addi r7, r1, 0x18
/* 802D66CC 002D32AC  4B D8 97 11 */	bl efSync_Spawn
/* 802D66D0 002D32B0  7F 83 E3 78 */	mr r3, r28
/* 802D66D4 002D32B4  4B F9 4C D5 */	bl it_8026B3A8
/* 802D66D8 002D32B8  80 01 00 34 */	lwz r0, 0x34(r1)
/* 802D66DC 002D32BC  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 802D66E0 002D32C0  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 802D66E4 002D32C4  83 A1 00 24 */	lwz r29, 0x24(r1)
/* 802D66E8 002D32C8  83 81 00 20 */	lwz r28, 0x20(r1)
/* 802D66EC 002D32CC  38 21 00 30 */	addi r1, r1, 0x30
/* 802D66F0 002D32D0  7C 08 03 A6 */	mtlr r0
/* 802D66F4 002D32D4  4E 80 00 20 */	blr


.section .data
    .balign 8
.global it_803F8270
it_803F8270:
    .4byte -1
    .4byte it_802D5EC8
    .4byte it_802D5EEC
    .4byte it_802D5F0C
    .4byte 1
    .4byte it_802D5FC8
    .4byte it_802D6084
    .4byte it_802D60A4
    .4byte -1
    .4byte it_802D60C8
    .4byte it_802D60D0
    .4byte NULL
.global it_803F82A0
it_803F82A0:
    .4byte 0
    .4byte it_802D66F8
    .4byte it_802D6740
    .4byte it_802D6798


.section .sdata2
    .balign 8
.global it_804DD520
it_804DD520:
    .4byte 0x00000000
.global it_804DD524
it_804DD524:
    .4byte 0x3F800000
.global it_804DD528
it_804DD528:
    .4byte 0x43300000
    .4byte 0x80000000
.global it_804DD530
it_804DD530:
    .4byte 0x401921FB
    .4byte 0x54442D18
.global it_804DD538
it_804DD538:
    .4byte 0xC00921FB
    .4byte 0x54442D18
.global it_804DD540
it_804DD540:
    .4byte 0x400921FB
    .4byte 0x54442D18
.global it_804DD548
it_804DD548:
    .4byte 0x3FF921FB
    .4byte 0x54442D18
.global it_804DD550
it_804DD550:
    .4byte 0x3F947AE1
    .4byte 0x40000000
.global it_804DD558
it_804DD558:
    .4byte 0x3FE00000
    .4byte 0x00000000
