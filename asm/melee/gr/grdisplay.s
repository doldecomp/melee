.include "macros.inc"

.section .text

.global grDisplay_801C5B90
grDisplay_801C5B90:
/* 801C5B90 001C2770  7C 08 02 A6 */	mflr r0
/* 801C5B94 001C2774  90 01 00 04 */	stw r0, 4(r1)
/* 801C5B98 001C2778  94 21 FF 70 */	stwu r1, -0x90(r1)
/* 801C5B9C 001C277C  BF 21 00 74 */	stmw r25, 0x74(r1)
/* 801C5BA0 001C2780  7C 7C 1B 79 */	or. r28, r3, r3
/* 801C5BA4 001C2784  3B A4 00 00 */	addi r29, r4, 0
/* 801C5BA8 001C2788  3B C5 00 00 */	addi r30, r5, 0
/* 801C5BAC 001C278C  3B E6 00 00 */	addi r31, r6, 0
/* 801C5BB0 001C2790  41 82 01 EC */	beq grDisplay_801C5D9C
/* 801C5BB4 001C2794  80 7C 00 14 */	lwz r3, 0x14(r28)
/* 801C5BB8 001C2798  54 60 04 E7 */	rlwinm. r0, r3, 0, 0x13, 0x13
/* 801C5BBC 001C279C  41 82 00 FC */	beq grDisplay_801C5CB8
/* 801C5BC0 001C27A0  54 60 06 F7 */	rlwinm. r0, r3, 0, 0x1b, 0x1b
/* 801C5BC4 001C27A4  40 82 01 D8 */	bne grDisplay_801C5D9C
/* 801C5BC8 001C27A8  28 1C 00 00 */	cmplwi r28, 0
/* 801C5BCC 001C27AC  41 82 00 44 */	beq grDisplay_801C5C10
/* 801C5BD0 001C27B0  40 82 00 14 */	bne grDisplay_801C5BE4
/* 801C5BD4 001C27B4  38 6D 8E 90 */	addi r3, r13, lbl_804D4530@sda21
/* 801C5BD8 001C27B8  38 80 02 34 */	li r4, 0x234
/* 801C5BDC 001C27BC  38 AD 8E 98 */	addi r5, r13, lbl_804D4538@sda21
/* 801C5BE0 001C27C0  48 1C 26 41 */	bl __assert
grDisplay_801C5BE4:
/* 801C5BE4 001C27C4  80 9C 00 14 */	lwz r4, 0x14(r28)
/* 801C5BE8 001C27C8  38 60 00 00 */	li r3, 0
/* 801C5BEC 001C27CC  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 801C5BF0 001C27D0  40 82 00 10 */	bne grDisplay_801C5C00
/* 801C5BF4 001C27D4  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 801C5BF8 001C27D8  41 82 00 08 */	beq grDisplay_801C5C00
/* 801C5BFC 001C27DC  38 60 00 01 */	li r3, 1
grDisplay_801C5C00:
/* 801C5C00 001C27E0  2C 03 00 00 */	cmpwi r3, 0
/* 801C5C04 001C27E4  41 82 00 0C */	beq grDisplay_801C5C10
/* 801C5C08 001C27E8  7F 83 E3 78 */	mr r3, r28
/* 801C5C0C 001C27EC  48 1A D4 6D */	bl HSD_JObjSetupMatrixSub
grDisplay_801C5C10:
/* 801C5C10 001C27F0  83 3C 00 10 */	lwz r25, 0x10(r28)
/* 801C5C14 001C27F4  28 19 00 00 */	cmplwi r25, 0
/* 801C5C18 001C27F8  41 82 00 44 */	beq grDisplay_801C5C5C
/* 801C5C1C 001C27FC  40 82 00 14 */	bne grDisplay_801C5C30
/* 801C5C20 001C2800  38 6D 8E 90 */	addi r3, r13, lbl_804D4530@sda21
/* 801C5C24 001C2804  38 80 02 34 */	li r4, 0x234
/* 801C5C28 001C2808  38 AD 8E 98 */	addi r5, r13, lbl_804D4538@sda21
/* 801C5C2C 001C280C  48 1C 25 F5 */	bl __assert
grDisplay_801C5C30:
/* 801C5C30 001C2810  80 99 00 14 */	lwz r4, 0x14(r25)
/* 801C5C34 001C2814  38 60 00 00 */	li r3, 0
/* 801C5C38 001C2818  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 801C5C3C 001C281C  40 82 00 10 */	bne grDisplay_801C5C4C
/* 801C5C40 001C2820  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 801C5C44 001C2824  41 82 00 08 */	beq grDisplay_801C5C4C
/* 801C5C48 001C2828  38 60 00 01 */	li r3, 1
grDisplay_801C5C4C:
/* 801C5C4C 001C282C  2C 03 00 00 */	cmpwi r3, 0
/* 801C5C50 001C2830  41 82 00 0C */	beq grDisplay_801C5C5C
/* 801C5C54 001C2834  7F 23 CB 78 */	mr r3, r25
/* 801C5C58 001C2838  48 1A D4 21 */	bl HSD_JObjSetupMatrixSub
grDisplay_801C5C5C:
/* 801C5C5C 001C283C  80 7C 00 10 */	lwz r3, 0x10(r28)
/* 801C5C60 001C2840  38 9C 00 44 */	addi r4, r28, 0x44
/* 801C5C64 001C2844  38 A1 00 3C */	addi r5, r1, 0x3c
/* 801C5C68 001C2848  38 63 00 44 */	addi r3, r3, 0x44
/* 801C5C6C 001C284C  48 1B 39 2D */	bl HSD_MtxInverseConcat
/* 801C5C70 001C2850  48 1A 46 19 */	bl HSD_CObjGetCurrent
/* 801C5C74 001C2854  7C 7A 1B 79 */	or. r26, r3, r3
/* 801C5C78 001C2858  40 82 00 18 */	bne grDisplay_801C5C90
/* 801C5C7C 001C285C  3C 60 80 3E */	lis r3, lbl_803E0730@ha
/* 801C5C80 001C2860  38 63 07 30 */	addi r3, r3, lbl_803E0730@l
/* 801C5C84 001C2864  38 80 00 52 */	li r4, 0x52
/* 801C5C88 001C2868  38 AD 8E A0 */	addi r5, r13, lbl_804D4540@sda21
/* 801C5C8C 001C286C  48 1C 25 95 */	bl __assert
grDisplay_801C5C90:
/* 801C5C90 001C2870  38 81 00 3C */	addi r4, r1, 0x3c
/* 801C5C94 001C2874  38 7A 00 54 */	addi r3, r26, 0x54
/* 801C5C98 001C2878  38 A4 00 00 */	addi r5, r4, 0
/* 801C5C9C 001C287C  48 17 C5 69 */	bl PSMTXConcat
/* 801C5CA0 001C2880  80 7C 00 10 */	lwz r3, 0x10(r28)
/* 801C5CA4 001C2884  38 BE 00 00 */	addi r5, r30, 0
/* 801C5CA8 001C2888  38 DF 00 00 */	addi r6, r31, 0
/* 801C5CAC 001C288C  38 81 00 3C */	addi r4, r1, 0x3c
/* 801C5CB0 001C2890  4B FF FE E1 */	bl grDisplay_801C5B90
/* 801C5CB4 001C2894  48 00 00 E8 */	b grDisplay_801C5D9C
grDisplay_801C5CB8:
/* 801C5CB8 001C2898  57 C0 90 1A */	slwi r0, r30, 0x12
/* 801C5CBC 001C289C  7C 60 00 39 */	and. r0, r3, r0
/* 801C5CC0 001C28A0  41 82 00 A4 */	beq grDisplay_801C5D64
/* 801C5CC4 001C28A4  80 8D C1 8C */	lwz r4, lbl_804D782C@sda21(r13)
/* 801C5CC8 001C28A8  3C 60 80 4A */	lis r3, stage_info@ha
/* 801C5CCC 001C28AC  3B 63 E6 C8 */	addi r27, r3, stage_info@l
/* 801C5CD0 001C28B0  83 24 00 20 */	lwz r25, 0x20(r4)
/* 801C5CD4 001C28B4  48 00 00 70 */	b grDisplay_801C5D44
grDisplay_801C5CD8:
/* 801C5CD8 001C28B8  7F 23 CB 78 */	mr r3, r25
/* 801C5CDC 001C28BC  4B EC 15 D5 */	bl ftLib_800872B0
/* 801C5CE0 001C28C0  3B 43 00 00 */	addi r26, r3, 0
/* 801C5CE4 001C28C4  38 79 00 00 */	addi r3, r25, 0
/* 801C5CE8 001C28C8  38 81 00 30 */	addi r4, r1, 0x30
/* 801C5CEC 001C28CC  4B EC 09 59 */	bl ftLib_80086644
/* 801C5CF0 001C28D0  4B E6 AE 35 */	bl func_80030B24
/* 801C5CF4 001C28D4  2C 03 00 00 */	cmpwi r3, 0
/* 801C5CF8 001C28D8  40 82 00 24 */	bne grDisplay_801C5D1C
/* 801C5CFC 001C28DC  81 9B 01 7C */	lwz r12, 0x17c(r27)
/* 801C5D00 001C28E0  38 BC 00 00 */	addi r5, r28, 0
/* 801C5D04 001C28E4  38 61 00 30 */	addi r3, r1, 0x30
/* 801C5D08 001C28E8  7D 88 03 A6 */	mtlr r12
/* 801C5D0C 001C28EC  38 80 FF FF */	li r4, -1
/* 801C5D10 001C28F0  4E 80 00 21 */	blrl
/* 801C5D14 001C28F4  2C 03 00 00 */	cmpwi r3, 0
/* 801C5D18 001C28F8  41 82 00 18 */	beq grDisplay_801C5D30
grDisplay_801C5D1C:
/* 801C5D1C 001C28FC  88 1A 00 00 */	lbz r0, 0(r26)
/* 801C5D20 001C2900  38 60 00 00 */	li r3, 0
/* 801C5D24 001C2904  50 60 1F 38 */	rlwimi r0, r3, 3, 0x1c, 0x1c
/* 801C5D28 001C2908  98 1A 00 00 */	stb r0, 0(r26)
/* 801C5D2C 001C290C  48 00 00 14 */	b grDisplay_801C5D40
grDisplay_801C5D30:
/* 801C5D30 001C2910  88 1A 00 00 */	lbz r0, 0(r26)
/* 801C5D34 001C2914  38 60 00 01 */	li r3, 1
/* 801C5D38 001C2918  50 60 1F 38 */	rlwimi r0, r3, 3, 0x1c, 0x1c
/* 801C5D3C 001C291C  98 1A 00 00 */	stb r0, 0(r26)
grDisplay_801C5D40:
/* 801C5D40 001C2920  83 39 00 08 */	lwz r25, 8(r25)
grDisplay_801C5D44:
/* 801C5D44 001C2924  28 19 00 00 */	cmplwi r25, 0
/* 801C5D48 001C2928  40 82 FF 90 */	bne grDisplay_801C5CD8
/* 801C5D4C 001C292C  4B E4 92 A1 */	bl lbShadow_8000EFEC
/* 801C5D50 001C2930  38 7C 00 00 */	addi r3, r28, 0
/* 801C5D54 001C2934  38 9D 00 00 */	addi r4, r29, 0
/* 801C5D58 001C2938  38 BE 00 00 */	addi r5, r30, 0
/* 801C5D5C 001C293C  38 DF 00 00 */	addi r6, r31, 0
/* 801C5D60 001C2940  48 1A EC 51 */	bl HSD_JObjDisp
grDisplay_801C5D64:
/* 801C5D64 001C2944  80 7C 00 14 */	lwz r3, 0x14(r28)
/* 801C5D68 001C2948  57 C0 E0 06 */	slwi r0, r30, 0x1c
/* 801C5D6C 001C294C  7C 60 00 39 */	and. r0, r3, r0
/* 801C5D70 001C2950  41 82 00 2C */	beq grDisplay_801C5D9C
/* 801C5D74 001C2954  83 9C 00 10 */	lwz r28, 0x10(r28)
/* 801C5D78 001C2958  48 00 00 1C */	b grDisplay_801C5D94
grDisplay_801C5D7C:
/* 801C5D7C 001C295C  38 7C 00 00 */	addi r3, r28, 0
/* 801C5D80 001C2960  38 9D 00 00 */	addi r4, r29, 0
/* 801C5D84 001C2964  38 BE 00 00 */	addi r5, r30, 0
/* 801C5D88 001C2968  38 DF 00 00 */	addi r6, r31, 0
/* 801C5D8C 001C296C  4B FF FE 05 */	bl grDisplay_801C5B90
/* 801C5D90 001C2970  83 9C 00 08 */	lwz r28, 8(r28)
grDisplay_801C5D94:
/* 801C5D94 001C2974  28 1C 00 00 */	cmplwi r28, 0
/* 801C5D98 001C2978  40 82 FF E4 */	bne grDisplay_801C5D7C
grDisplay_801C5D9C:
/* 801C5D9C 001C297C  BB 21 00 74 */	lmw r25, 0x74(r1)
/* 801C5DA0 001C2980  80 01 00 94 */	lwz r0, 0x94(r1)
/* 801C5DA4 001C2984  38 21 00 90 */	addi r1, r1, 0x90
/* 801C5DA8 001C2988  7C 08 03 A6 */	mtlr r0
/* 801C5DAC 001C298C  4E 80 00 20 */	blr

.global grDisplay_801C5DB0
grDisplay_801C5DB0:
/* 801C5DB0 001C2990  7C 08 02 A6 */	mflr r0
/* 801C5DB4 001C2994  90 01 00 04 */	stw r0, 4(r1)
/* 801C5DB8 001C2998  94 21 FF 88 */	stwu r1, -0x78(r1)
/* 801C5DBC 001C299C  BF 61 00 64 */	stmw r27, 0x64(r1)
/* 801C5DC0 001C29A0  7C 7D 1B 78 */	mr r29, r3
/* 801C5DC4 001C29A4  7C 9E 23 78 */	mr r30, r4
/* 801C5DC8 001C29A8  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 801C5DCC 001C29AC  4B E6 B2 C1 */	bl func_8003108C
/* 801C5DD0 001C29B0  88 1F 00 11 */	lbz r0, 0x11(r31)
/* 801C5DD4 001C29B4  54 00 DF 7E */	rlwinm r0, r0, 0x1b, 0x1d, 0x1f
/* 801C5DD8 001C29B8  7C 00 18 00 */	cmpw r0, r3
/* 801C5DDC 001C29BC  40 82 01 70 */	bne grDisplay_801C5F4C
/* 801C5DE0 001C29C0  80 9F 00 18 */	lwz r4, 0x18(r31)
/* 801C5DE4 001C29C4  28 04 00 00 */	cmplwi r4, 0
/* 801C5DE8 001C29C8  41 82 00 68 */	beq grDisplay_801C5E50
/* 801C5DEC 001C29CC  54 80 00 01 */	rlwinm. r0, r4, 0, 0, 0
/* 801C5DF0 001C29D0  40 82 00 14 */	bne grDisplay_801C5E04
/* 801C5DF4 001C29D4  3C 60 80 3E */	lis r3, lbl_803E073C@ha
/* 801C5DF8 001C29D8  4C C6 31 82 */	crclr 6
/* 801C5DFC 001C29DC  38 63 07 3C */	addi r3, r3, lbl_803E073C@l
/* 801C5E00 001C29E0  48 17 F8 A9 */	bl OSReport
grDisplay_801C5E04:
/* 801C5E04 001C29E4  80 8D C1 78 */	lwz r4, lbl_804D7818@sda21(r13)
/* 801C5E08 001C29E8  80 7F 00 18 */	lwz r3, 0x18(r31)
/* 801C5E0C 001C29EC  80 84 00 28 */	lwz r4, 0x28(r4)
/* 801C5E10 001C29F0  80 03 00 28 */	lwz r0, 0x28(r3)
/* 801C5E14 001C29F4  7C 04 00 40 */	cmplw r4, r0
/* 801C5E18 001C29F8  41 82 00 4C */	beq grDisplay_801C5E64
/* 801C5E1C 001C29FC  88 1F 00 10 */	lbz r0, 0x10(r31)
/* 801C5E20 001C2A00  54 00 E7 FF */	rlwinm. r0, r0, 0x1c, 0x1f, 0x1f
/* 801C5E24 001C2A04  41 82 01 28 */	beq grDisplay_801C5F4C
/* 801C5E28 001C2A08  4B E6 AC 29 */	bl func_80030A50
/* 801C5E2C 001C2A0C  28 03 00 00 */	cmplwi r3, 0
/* 801C5E30 001C2A10  41 82 01 1C */	beq grDisplay_801C5F4C
/* 801C5E34 001C2A14  83 63 00 28 */	lwz r27, 0x28(r3)
/* 801C5E38 001C2A18  28 1B 00 00 */	cmplwi r27, 0
/* 801C5E3C 001C2A1C  41 82 01 10 */	beq grDisplay_801C5F4C
/* 801C5E40 001C2A20  48 1A 44 49 */	bl HSD_CObjGetCurrent
/* 801C5E44 001C2A24  7C 03 D8 40 */	cmplw r3, r27
/* 801C5E48 001C2A28  41 82 00 1C */	beq grDisplay_801C5E64
/* 801C5E4C 001C2A2C  48 00 01 00 */	b grDisplay_801C5F4C
grDisplay_801C5E50:
/* 801C5E50 001C2A30  80 6D C1 78 */	lwz r3, lbl_804D7818@sda21(r13)
/* 801C5E54 001C2A34  80 63 00 28 */	lwz r3, 0x28(r3)
/* 801C5E58 001C2A38  4B FF CE 35 */	bl Ground_801C2C8C
/* 801C5E5C 001C2A3C  2C 03 00 00 */	cmpwi r3, 0
/* 801C5E60 001C2A40  40 82 00 EC */	bne grDisplay_801C5F4C
grDisplay_801C5E64:
/* 801C5E64 001C2A44  4B E6 AC 15 */	bl func_80030A78
/* 801C5E68 001C2A48  2C 03 00 00 */	cmpwi r3, 0
/* 801C5E6C 001C2A4C  40 82 00 E0 */	bne grDisplay_801C5F4C
/* 801C5E70 001C2A50  4B E6 AC 55 */	bl func_80030AC4
/* 801C5E74 001C2A54  2C 03 00 00 */	cmpwi r3, 0
/* 801C5E78 001C2A58  41 82 00 D4 */	beq grDisplay_801C5F4C
/* 801C5E7C 001C2A5C  88 1F 00 10 */	lbz r0, 0x10(r31)
/* 801C5E80 001C2A60  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 801C5E84 001C2A64  40 82 00 0C */	bne grDisplay_801C5E90
/* 801C5E88 001C2A68  38 60 00 00 */	li r3, 0
/* 801C5E8C 001C2A6C  48 1B 7A E5 */	bl HSD_FogSet
grDisplay_801C5E90:
/* 801C5E90 001C2A70  38 60 FF FF */	li r3, -1
/* 801C5E94 001C2A74  48 19 C1 31 */	bl HSD_StateInvalidate
/* 801C5E98 001C2A78  88 1F 00 10 */	lbz r0, 0x10(r31)
/* 801C5E9C 001C2A7C  54 00 F7 FF */	rlwinm. r0, r0, 0x1e, 0x1f, 0x1f
/* 801C5EA0 001C2A80  41 82 00 28 */	beq grDisplay_801C5EC8
/* 801C5EA4 001C2A84  83 7D 00 28 */	lwz r27, 0x28(r29)
/* 801C5EA8 001C2A88  7F C3 F3 78 */	mr r3, r30
/* 801C5EAC 001C2A8C  48 1C B0 0D */	bl func_80390EB8
/* 801C5EB0 001C2A90  38 A3 00 00 */	addi r5, r3, 0
/* 801C5EB4 001C2A94  38 7B 00 00 */	addi r3, r27, 0
/* 801C5EB8 001C2A98  38 80 00 00 */	li r4, 0
/* 801C5EBC 001C2A9C  38 C0 00 00 */	li r6, 0
/* 801C5EC0 001C2AA0  4B FF FC D1 */	bl grDisplay_801C5B90
/* 801C5EC4 001C2AA4  48 00 00 48 */	b grDisplay_801C5F0C
grDisplay_801C5EC8:
/* 801C5EC8 001C2AA8  80 6D C1 8C */	lwz r3, lbl_804D782C@sda21(r13)
/* 801C5ECC 001C2AAC  3B 80 00 00 */	li r28, 0
/* 801C5ED0 001C2AB0  83 63 00 20 */	lwz r27, 0x20(r3)
/* 801C5ED4 001C2AB4  48 00 00 24 */	b grDisplay_801C5EF8
grDisplay_801C5ED8:
/* 801C5ED8 001C2AB8  7F 63 DB 78 */	mr r3, r27
/* 801C5EDC 001C2ABC  4B EC 13 D5 */	bl ftLib_800872B0
/* 801C5EE0 001C2AC0  88 03 00 00 */	lbz r0, 0(r3)
/* 801C5EE4 001C2AC4  53 80 1F 38 */	rlwimi r0, r28, 3, 0x1c, 0x1c
/* 801C5EE8 001C2AC8  98 03 00 00 */	stb r0, 0(r3)
/* 801C5EEC 001C2ACC  7F 63 DB 78 */	mr r3, r27
/* 801C5EF0 001C2AD0  4B E4 8F F1 */	bl lbShadow_8000EEE0
/* 801C5EF4 001C2AD4  83 7B 00 08 */	lwz r27, 8(r27)
grDisplay_801C5EF8:
/* 801C5EF8 001C2AD8  28 1B 00 00 */	cmplwi r27, 0
/* 801C5EFC 001C2ADC  40 82 FF DC */	bne grDisplay_801C5ED8
/* 801C5F00 001C2AE0  38 7D 00 00 */	addi r3, r29, 0
/* 801C5F04 001C2AE4  38 9E 00 00 */	addi r4, r30, 0
/* 801C5F08 001C2AE8  48 1C B1 69 */	bl func_80391070
grDisplay_801C5F0C:
/* 801C5F0C 001C2AEC  88 1F 00 10 */	lbz r0, 0x10(r31)
/* 801C5F10 001C2AF0  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 801C5F14 001C2AF4  40 82 00 38 */	bne grDisplay_801C5F4C
/* 801C5F18 001C2AF8  4B E6 AB 61 */	bl func_80030A78
/* 801C5F1C 001C2AFC  2C 03 00 00 */	cmpwi r3, 0
/* 801C5F20 001C2B00  40 82 00 2C */	bne grDisplay_801C5F4C
/* 801C5F24 001C2B04  4B FF BE F5 */	bl Ground_801C1E18
/* 801C5F28 001C2B08  2C 03 00 00 */	cmpwi r3, 0
/* 801C5F2C 001C2B0C  41 82 00 20 */	beq grDisplay_801C5F4C
/* 801C5F30 001C2B10  4B FF BF 55 */	bl Ground_801C1E84
/* 801C5F34 001C2B14  28 03 00 00 */	cmplwi r3, 0
/* 801C5F38 001C2B18  41 82 00 14 */	beq grDisplay_801C5F4C
/* 801C5F3C 001C2B1C  80 63 00 28 */	lwz r3, 0x28(r3)
/* 801C5F40 001C2B20  28 03 00 00 */	cmplwi r3, 0
/* 801C5F44 001C2B24  41 82 00 08 */	beq grDisplay_801C5F4C
/* 801C5F48 001C2B28  48 1B 7A 29 */	bl HSD_FogSet
grDisplay_801C5F4C:
/* 801C5F4C 001C2B2C  BB 61 00 64 */	lmw r27, 0x64(r1)
/* 801C5F50 001C2B30  80 01 00 7C */	lwz r0, 0x7c(r1)
/* 801C5F54 001C2B34  38 21 00 78 */	addi r1, r1, 0x78
/* 801C5F58 001C2B38  7C 08 03 A6 */	mtlr r0
/* 801C5F5C 001C2B3C  4E 80 00 20 */	blr

/* this function might belong in the next file */
.global grDisplay_801C5F60
grDisplay_801C5F60:
/* 801C5F60 001C2B40  7C 08 02 A6 */	mflr r0
/* 801C5F64 001C2B44  90 01 00 04 */	stw r0, 4(r1)
/* 801C5F68 001C2B48  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 801C5F6C 001C2B4C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 801C5F70 001C2B50  7C 7F 1B 78 */	mr r31, r3
/* 801C5F74 001C2B54  80 63 00 28 */	lwz r3, 0x28(r3)
/* 801C5F78 001C2B58  48 1A 24 E1 */	bl HSD_CObjSetCurrent
/* 801C5F7C 001C2B5C  2C 03 00 00 */	cmpwi r3, 0
/* 801C5F80 001C2B60  41 82 00 2C */	beq grDisplay_801C5FAC
/* 801C5F84 001C2B64  38 00 00 08 */	li r0, 8
/* 801C5F88 001C2B68  90 1F 00 24 */	stw r0, 0x24(r31)
/* 801C5F8C 001C2B6C  38 00 00 00 */	li r0, 0
/* 801C5F90 001C2B70  38 60 00 00 */	li r3, 0
/* 801C5F94 001C2B74  90 1F 00 20 */	stw r0, 0x20(r31)
/* 801C5F98 001C2B78  4B E6 B1 09 */	bl func_800310A0
/* 801C5F9C 001C2B7C  38 7F 00 00 */	addi r3, r31, 0
/* 801C5FA0 001C2B80  38 80 00 07 */	li r4, 7
/* 801C5FA4 001C2B84  48 1C AF 2D */	bl func_80390ED0
/* 801C5FA8 001C2B88  48 1A 26 61 */	bl HSD_CObjEndCurrent
grDisplay_801C5FAC:
/* 801C5FAC 001C2B8C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 801C5FB0 001C2B90  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 801C5FB4 001C2B94  38 21 00 20 */	addi r1, r1, 0x20
/* 801C5FB8 001C2B98  7C 08 03 A6 */	mtlr r0
/* 801C5FBC 001C2B9C  4E 80 00 20 */	blr


.section .data
    .balign 8
lbl_803E0730:
    .asciz "grdisplay.c"
    .balign 4
lbl_803E073C:
    .asciz "oioi... %08x\n"


.section .sdata
    .balign 8
lbl_804D4530:
    .asciz "jobj.h"
    .balign 4
lbl_804D4538:
    .asciz "jobj"
    .balign 4
lbl_804D4540:
    .asciz "cobj"
