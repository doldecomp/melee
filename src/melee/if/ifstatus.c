#include <melee/if/ifstatus.h>

s8 lbl_804D6D60;

extern unk_t lbl_802F74D0();
extern unk_t lbl_802F73C4();

extern Thing_803F9628 lbl_803F9628;

asm unk_t func_802F61FC()
{
/* 802F61FC 002F2DDC  7C 08 02 A6 */	mflr r0
/* 802F6200 002F2DE0  3C C0 80 40 */	lis r6, lbl_803F9598@ha
/* 802F6204 002F2DE4  90 01 00 04 */	stw r0, 4(r1)
/* 802F6208 002F2DE8  3C A0 80 4A */	lis r5, lbl_804A10C8@ha
/* 802F620C 002F2DEC  94 21 FF B8 */	stwu r1, -0x48(r1)
/* 802F6210 002F2DF0  BF 21 00 2C */	stmw r25, 0x2c(r1)
/* 802F6214 002F2DF4  54 9F 06 3E */	clrlwi r31, r4, 0x18
/* 802F6218 002F2DF8  3B A3 00 00 */	addi r29, r3, 0
/* 802F621C 002F2DFC  38 7F 00 00 */	addi r3, r31, 0
/* 802F6220 002F2E00  3B 66 95 98 */	addi r27, r6, lbl_803F9598@l
/* 802F6224 002F2E04  3B 45 10 C8 */	addi r26, r5, lbl_804A10C8@l
/* 802F6228 002F2E08  4B D3 C1 09 */	bl Player_GetPlayerCharacter
/* 802F622C 002F2E0C  80 9D 00 04 */	lwz r4, 4(r29)
/* 802F6230 002F2E10  3B 83 00 00 */	addi r28, r3, 0
/* 802F6234 002F2E14  28 04 00 00 */	cmplwi r4, 0
/* 802F6238 002F2E18  40 82 00 98 */	bne lbl_802F62D0
/* 802F623C 002F2E1C  4B FF D4 55 */	bl func_802F3690
/* 802F6240 002F2E20  38 60 00 0E */	li r3, 0xe
/* 802F6244 002F2E24  38 80 00 0F */	li r4, 0xf
/* 802F6248 002F2E28  38 A0 00 00 */	li r5, 0
/* 802F624C 002F2E2C  48 09 9F A5 */	bl func_803901F0
/* 802F6250 002F2E30  7C 79 1B 79 */	or. r25, r3, r3
/* 802F6254 002F2E34  40 82 00 20 */	bne lbl_802F6274
/* 802F6258 002F2E38  38 7B 00 34 */	addi r3, r27, 0x34
/* 802F625C 002F2E3C  4C C6 31 82 */	crclr 6
/* 802F6260 002F2E40  48 04 F4 49 */	bl OSReport
/* 802F6264 002F2E44  38 7B 00 5C */	addi r3, r27, 0x5c
/* 802F6268 002F2E48  38 80 03 0A */	li r4, 0x30a
/* 802F626C 002F2E4C  38 AD A1 20 */	addi r5, r13, lbl_804D57C0@sda21
/* 802F6270 002F2E50  48 09 1F B1 */	bl __assert
lbl_802F6274:
/* 802F6274 002F2E54  80 7A 02 68 */	lwz r3, 0x268(r26)
/* 802F6278 002F2E58  48 07 AB CD */	bl HSD_JObjLoadJoint
/* 802F627C 002F2E5C  7C 7E 1B 79 */	or. r30, r3, r3
/* 802F6280 002F2E60  40 82 00 20 */	bne lbl_802F62A0
/* 802F6284 002F2E64  38 7B 00 68 */	addi r3, r27, 0x68
/* 802F6288 002F2E68  4C C6 31 82 */	crclr 6
/* 802F628C 002F2E6C  48 04 F4 1D */	bl OSReport
/* 802F6290 002F2E70  38 7B 00 5C */	addi r3, r27, 0x5c
/* 802F6294 002F2E74  38 80 03 0E */	li r4, 0x30e
/* 802F6298 002F2E78  38 AD A1 20 */	addi r5, r13, lbl_804D57C0@sda21
/* 802F629C 002F2E7C  48 09 1F 85 */	bl __assert
lbl_802F62A0:
/* 802F62A0 002F2E80  88 8D C1 A9 */	lbz r4, lbl_804D7849@sda21(r13)
/* 802F62A4 002F2E84  38 79 00 00 */	addi r3, r25, 0
/* 802F62A8 002F2E88  38 BE 00 00 */	addi r5, r30, 0
/* 802F62AC 002F2E8C  48 09 A7 C5 */	bl func_80390A70
/* 802F62B0 002F2E90  3C 60 80 2F */	lis r3, lbl_802F5E50@ha
/* 802F62B4 002F2E94  38 83 5E 50 */	addi r4, r3, lbl_802F5E50@l
/* 802F62B8 002F2E98  38 79 00 00 */	addi r3, r25, 0
/* 802F62BC 002F2E9C  38 A0 00 0B */	li r5, 0xb
/* 802F62C0 002F2EA0  38 C0 00 00 */	li r6, 0
/* 802F62C4 002F2EA4  48 09 A3 D9 */	bl GObj_SetupGXLink
/* 802F62C8 002F2EA8  93 3D 00 04 */	stw r25, 4(r29)
/* 802F62CC 002F2EAC  48 00 00 08 */	b lbl_802F62D4
lbl_802F62D0:
/* 802F62D0 002F2EB0  83 C4 00 28 */	lwz r30, 0x28(r4)
lbl_802F62D4:
/* 802F62D4 002F2EB4  80 DE 00 10 */	lwz r6, 0x10(r30)
/* 802F62D8 002F2EB8  7F C3 F3 78 */	mr r3, r30
/* 802F62DC 002F2EBC  80 BA 02 6C */	lwz r5, 0x26c(r26)
/* 802F62E0 002F2EC0  38 80 00 00 */	li r4, 0
/* 802F62E4 002F2EC4  80 E6 00 18 */	lwz r7, 0x18(r6)
/* 802F62E8 002F2EC8  80 DA 02 70 */	lwz r6, 0x270(r26)
/* 802F62EC 002F2ECC  81 07 00 08 */	lwz r8, 8(r7)
/* 802F62F0 002F2ED0  80 FA 02 74 */	lwz r7, 0x274(r26)
/* 802F62F4 002F2ED4  83 48 00 08 */	lwz r26, 8(r8)
/* 802F62F8 002F2ED8  4B D1 5D 85 */	bl func_8000C07C
/* 802F62FC 002F2EDC  2C 1C 00 1A */	cmpwi r28, 0x1a
/* 802F6300 002F2EE0  41 82 00 10 */	beq lbl_802F6310
/* 802F6304 002F2EE4  38 1C FF E3 */	addi r0, r28, -29
/* 802F6308 002F2EE8  28 00 00 01 */	cmplwi r0, 1
/* 802F630C 002F2EEC  41 81 00 08 */	bgt lbl_802F6314
lbl_802F6310:
/* 802F6310 002F2EF0  3B 80 00 1B */	li r28, 0x1b
lbl_802F6314:
/* 802F6314 002F2EF4  38 7C 00 00 */	addi r3, r28, 0
/* 802F6318 002F2EF8  38 80 00 00 */	li r4, 0
/* 802F631C 002F2EFC  38 A0 00 00 */	li r5, 0
/* 802F6320 002F2F00  4B E7 28 15 */	bl func_80168B34
/* 802F6324 002F2F04  C0 02 E0 B4 */	lfs f0, lbl_804DDA94@sda21(r2)
/* 802F6328 002F2F08  7F 43 D3 78 */	mr r3, r26
/* 802F632C 002F2F0C  EC 20 08 2A */	fadds f1, f0, f1
/* 802F6330 002F2F10  48 06 84 D1 */	bl HSD_TObjReqAnimAll
/* 802F6334 002F2F14  80 7A 00 64 */	lwz r3, 0x64(r26)
/* 802F6338 002F2F18  C0 22 E0 BC */	lfs f1, lbl_804DDA9C@sda21(r2)
/* 802F633C 002F2F1C  48 06 EF D1 */	bl HSD_AObjSetRate
/* 802F6340 002F2F20  7F 43 D3 78 */	mr r3, r26
/* 802F6344 002F2F24  48 06 88 29 */	bl HSD_TObjAnim
/* 802F6348 002F2F28  7F E3 FB 78 */	mr r3, r31
/* 802F634C 002F2F2C  4B FF D0 D9 */	bl func_802F3424
/* 802F6350 002F2F30  28 1E 00 00 */	cmplwi r30, 0
/* 802F6354 002F2F34  3B 43 00 00 */	addi r26, r3, 0
/* 802F6358 002F2F38  40 82 00 14 */	bne lbl_802F636C
/* 802F635C 002F2F3C  38 6D A1 10 */	addi r3, r13, lbl_804D57B0@sda21
/* 802F6360 002F2F40  38 80 03 94 */	li r4, 0x394
/* 802F6364 002F2F44  38 AD A1 18 */	addi r5, r13, lbl_804D57B8@sda21
/* 802F6368 002F2F48  48 09 1E B9 */	bl __assert
lbl_802F636C:
/* 802F636C 002F2F4C  28 1A 00 00 */	cmplwi r26, 0
/* 802F6370 002F2F50  40 82 00 14 */	bne lbl_802F6384
/* 802F6374 002F2F54  38 BB 00 28 */	addi r5, r27, 0x28
/* 802F6378 002F2F58  38 6D A1 10 */	addi r3, r13, lbl_804D57B0@sda21
/* 802F637C 002F2F5C  38 80 03 95 */	li r4, 0x395
/* 802F6380 002F2F60  48 09 1E A1 */	bl __assert
lbl_802F6384:
/* 802F6384 002F2F64  80 7A 00 00 */	lwz r3, 0(r26)
/* 802F6388 002F2F68  80 1A 00 04 */	lwz r0, 4(r26)
/* 802F638C 002F2F6C  90 7E 00 38 */	stw r3, 0x38(r30)
/* 802F6390 002F2F70  90 1E 00 3C */	stw r0, 0x3c(r30)
/* 802F6394 002F2F74  80 1A 00 08 */	lwz r0, 8(r26)
/* 802F6398 002F2F78  90 1E 00 40 */	stw r0, 0x40(r30)
/* 802F639C 002F2F7C  80 1E 00 14 */	lwz r0, 0x14(r30)
/* 802F63A0 002F2F80  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 802F63A4 002F2F84  40 82 00 4C */	bne lbl_802F63F0
/* 802F63A8 002F2F88  28 1E 00 00 */	cmplwi r30, 0
/* 802F63AC 002F2F8C  41 82 00 44 */	beq lbl_802F63F0
/* 802F63B0 002F2F90  40 82 00 14 */	bne lbl_802F63C4
/* 802F63B4 002F2F94  38 6D A1 10 */	addi r3, r13, lbl_804D57B0@sda21
/* 802F63B8 002F2F98  38 80 02 34 */	li r4, 0x234
/* 802F63BC 002F2F9C  38 AD A1 18 */	addi r5, r13, lbl_804D57B8@sda21
/* 802F63C0 002F2FA0  48 09 1E 61 */	bl __assert
lbl_802F63C4:
/* 802F63C4 002F2FA4  80 9E 00 14 */	lwz r4, 0x14(r30)
/* 802F63C8 002F2FA8  38 60 00 00 */	li r3, 0
/* 802F63CC 002F2FAC  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 802F63D0 002F2FB0  40 82 00 10 */	bne lbl_802F63E0
/* 802F63D4 002F2FB4  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 802F63D8 002F2FB8  41 82 00 08 */	beq lbl_802F63E0
/* 802F63DC 002F2FBC  38 60 00 01 */	li r3, 1
lbl_802F63E0:
/* 802F63E0 002F2FC0  2C 03 00 00 */	cmpwi r3, 0
/* 802F63E4 002F2FC4  40 82 00 0C */	bne lbl_802F63F0
/* 802F63E8 002F2FC8  7F C3 F3 78 */	mr r3, r30
/* 802F63EC 002F2FCC  48 07 CE FD */	bl HSD_JObjSetMtxDirtySub
lbl_802F63F0:
/* 802F63F0 002F2FD0  28 1E 00 00 */	cmplwi r30, 0
/* 802F63F4 002F2FD4  40 82 00 14 */	bne lbl_802F6408
/* 802F63F8 002F2FD8  38 6D A1 10 */	addi r3, r13, lbl_804D57B0@sda21
/* 802F63FC 002F2FDC  38 80 04 4E */	li r4, 0x44e
/* 802F6400 002F2FE0  38 AD A1 18 */	addi r5, r13, lbl_804D57B8@sda21
/* 802F6404 002F2FE4  48 09 1E 1D */	bl __assert
lbl_802F6408:
/* 802F6408 002F2FE8  C0 3E 00 38 */	lfs f1, 0x38(r30)
/* 802F640C 002F2FEC  C0 02 E0 C0 */	lfs f0, lbl_804DDAA0@sda21(r2)
/* 802F6410 002F2FF0  EC 01 00 2A */	fadds f0, f1, f0
/* 802F6414 002F2FF4  D0 1E 00 38 */	stfs f0, 0x38(r30)
/* 802F6418 002F2FF8  80 1E 00 14 */	lwz r0, 0x14(r30)
/* 802F641C 002F2FFC  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 802F6420 002F3000  40 82 00 4C */	bne lbl_802F646C
/* 802F6424 002F3004  28 1E 00 00 */	cmplwi r30, 0
/* 802F6428 002F3008  41 82 00 44 */	beq lbl_802F646C
/* 802F642C 002F300C  40 82 00 14 */	bne lbl_802F6440
/* 802F6430 002F3010  38 6D A1 10 */	addi r3, r13, lbl_804D57B0@sda21
/* 802F6434 002F3014  38 80 02 34 */	li r4, 0x234
/* 802F6438 002F3018  38 AD A1 18 */	addi r5, r13, lbl_804D57B8@sda21
/* 802F643C 002F301C  48 09 1D E5 */	bl __assert
lbl_802F6440:
/* 802F6440 002F3020  80 9E 00 14 */	lwz r4, 0x14(r30)
/* 802F6444 002F3024  38 60 00 00 */	li r3, 0
/* 802F6448 002F3028  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 802F644C 002F302C  40 82 00 10 */	bne lbl_802F645C
/* 802F6450 002F3030  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 802F6454 002F3034  41 82 00 08 */	beq lbl_802F645C
/* 802F6458 002F3038  38 60 00 01 */	li r3, 1
lbl_802F645C:
/* 802F645C 002F303C  2C 03 00 00 */	cmpwi r3, 0
/* 802F6460 002F3040  40 82 00 0C */	bne lbl_802F646C
/* 802F6464 002F3044  7F C3 F3 78 */	mr r3, r30
/* 802F6468 002F3048  48 07 CE 81 */	bl HSD_JObjSetMtxDirtySub
lbl_802F646C:
/* 802F646C 002F304C  7F E3 FB 78 */	mr r3, r31
/* 802F6470 002F3050  4B D3 BF AD */	bl Player_GetPlayerSlotType
/* 802F6474 002F3054  54 7A 06 3E */	clrlwi r26, r3, 0x18
/* 802F6478 002F3058  4B E7 4C F1 */	bl func_8016B168
/* 802F647C 002F305C  54 7B 06 3E */	clrlwi r27, r3, 0x18
/* 802F6480 002F3060  38 7F 00 00 */	addi r3, r31, 0
/* 802F6484 002F3064  4B D3 CE ED */	bl Player_GetTeam
/* 802F6488 002F3068  54 7C 06 3E */	clrlwi r28, r3, 0x18
/* 802F648C 002F306C  38 7F 00 00 */	addi r3, r31, 0
/* 802F6490 002F3070  4B D3 CF CD */	bl Player_GetPlayerId
/* 802F6494 002F3074  54 63 06 3E */	clrlwi r3, r3, 0x18
/* 802F6498 002F3078  38 9C 00 00 */	addi r4, r28, 0
/* 802F649C 002F307C  38 BB 00 00 */	addi r5, r27, 0
/* 802F64A0 002F3080  38 DA 00 00 */	addi r6, r26, 0
/* 802F64A4 002F3084  4B E6 A3 B1 */	bl func_80160854
/* 802F64A8 002F3088  4B E6 A4 C1 */	bl func_80160968
/* 802F64AC 002F308C  28 1E 00 00 */	cmplwi r30, 0
/* 802F64B0 002F3090  90 61 00 20 */	stw r3, 0x20(r1)
/* 802F64B4 002F3094  40 82 00 0C */	bne lbl_802F64C0
/* 802F64B8 002F3098  38 60 00 00 */	li r3, 0
/* 802F64BC 002F309C  48 00 00 08 */	b lbl_802F64C4
lbl_802F64C0:
/* 802F64C0 002F30A0  80 7E 00 10 */	lwz r3, 0x10(r30)
lbl_802F64C4:
/* 802F64C4 002F30A4  80 63 00 18 */	lwz r3, 0x18(r3)
/* 802F64C8 002F30A8  88 01 00 20 */	lbz r0, 0x20(r1)
/* 802F64CC 002F30AC  80 83 00 08 */	lwz r4, 8(r3)
/* 802F64D0 002F30B0  80 64 00 0C */	lwz r3, 0xc(r4)
/* 802F64D4 002F30B4  98 03 00 04 */	stb r0, 4(r3)
/* 802F64D8 002F30B8  88 01 00 21 */	lbz r0, 0x21(r1)
/* 802F64DC 002F30BC  80 64 00 0C */	lwz r3, 0xc(r4)
/* 802F64E0 002F30C0  98 03 00 05 */	stb r0, 5(r3)
/* 802F64E4 002F30C4  88 01 00 22 */	lbz r0, 0x22(r1)
/* 802F64E8 002F30C8  80 64 00 0C */	lwz r3, 0xc(r4)
/* 802F64EC 002F30CC  98 03 00 06 */	stb r0, 6(r3)
/* 802F64F0 002F30D0  80 7D 00 04 */	lwz r3, 4(r29)
/* 802F64F4 002F30D4  80 01 00 4C */	lwz r0, 0x4c(r1)
/* 802F64F8 002F30D8  BB 21 00 2C */	lmw r25, 0x2c(r1)
/* 802F64FC 002F30DC  38 21 00 48 */	addi r1, r1, 0x48
/* 802F6500 002F30E0  7C 08 03 A6 */	mtlr r0
/* 802F6504 002F30E4  4E 80 00 20 */	blr 
}

asm void func_802F6508(s32 arg0)
{
/* 802F6508 002F30E8  7C 08 02 A6 */	mflr r0
/* 802F650C 002F30EC  90 01 00 04 */	stw r0, 4(r1)
/* 802F6510 002F30F0  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 802F6514 002F30F4  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 802F6518 002F30F8  7C 7F 1B 78 */	mr r31, r3
/* 802F651C 002F30FC  93 C1 00 18 */	stw r30, 0x18(r1)
/* 802F6520 002F3100  93 A1 00 14 */	stw r29, 0x14(r1)
/* 802F6524 002F3104  93 81 00 10 */	stw r28, 0x10(r1)
/* 802F6528 002F3108  4B D3 BE F5 */	bl Player_GetPlayerSlotType
/* 802F652C 002F310C  2C 03 00 03 */	cmpwi r3, 3
/* 802F6530 002F3110  41 82 01 0C */	beq lbl_802F663C
/* 802F6534 002F3114  88 0D B6 C0 */	lbz r0, lbl_804D6D60@sda21(r13)
/* 802F6538 002F3118  7C 00 F8 00 */	cmpw r0, r31
/* 802F653C 002F311C  40 81 01 00 */	ble lbl_802F663C
/* 802F6540 002F3120  4B E7 49 11 */	bl func_8016AE50
/* 802F6544 002F3124  88 03 00 02 */	lbz r0, 2(r3)
/* 802F6548 002F3128  7C 7D 1B 78 */	mr r29, r3
/* 802F654C 002F312C  54 00 FF FF */	rlwinm. r0, r0, 0x1f, 0x1f, 0x1f
/* 802F6550 002F3130  41 82 00 EC */	beq lbl_802F663C
/* 802F6554 002F3134  57 FE 06 3E */	clrlwi r30, r31, 0x18
/* 802F6558 002F3138  1C 9E 00 64 */	mulli r4, r30, 0x64
/* 802F655C 002F313C  3C 60 80 4A */	lis r3, lbl_804A10C8@ha
/* 802F6560 002F3140  38 03 10 C8 */	addi r0, r3, lbl_804A10C8@l
/* 802F6564 002F3144  7F 80 22 14 */	add r28, r0, r4
/* 802F6568 002F3148  38 00 FF FF */	li r0, -1
/* 802F656C 002F314C  B0 1C 00 0A */	sth r0, 0xa(r28)
/* 802F6570 002F3150  38 A0 00 00 */	li r5, 0
/* 802F6574 002F3154  38 7C 00 00 */	addi r3, r28, 0
/* 802F6578 002F3158  B0 1C 00 0C */	sth r0, 0xc(r28)
/* 802F657C 002F315C  7F C4 F3 78 */	mr r4, r30
/* 802F6580 002F3160  98 BC 00 0F */	stb r5, 0xf(r28)
/* 802F6584 002F3164  88 1C 00 10 */	lbz r0, 0x10(r28)
/* 802F6588 002F3168  50 A0 3E 30 */	rlwimi r0, r5, 7, 0x18, 0x18
/* 802F658C 002F316C  98 1C 00 10 */	stb r0, 0x10(r28)
/* 802F6590 002F3170  88 1C 00 10 */	lbz r0, 0x10(r28)
/* 802F6594 002F3174  50 A0 36 72 */	rlwimi r0, r5, 6, 0x19, 0x19
/* 802F6598 002F3178  98 1C 00 10 */	stb r0, 0x10(r28)
/* 802F659C 002F317C  88 1C 00 10 */	lbz r0, 0x10(r28)
/* 802F65A0 002F3180  50 A0 2E B4 */	rlwimi r0, r5, 5, 0x1a, 0x1a
/* 802F65A4 002F3184  98 1C 00 10 */	stb r0, 0x10(r28)
/* 802F65A8 002F3188  88 1C 00 10 */	lbz r0, 0x10(r28)
/* 802F65AC 002F318C  50 A0 26 F6 */	rlwimi r0, r5, 4, 0x1b, 0x1b
/* 802F65B0 002F3190  98 1C 00 10 */	stb r0, 0x10(r28)
/* 802F65B4 002F3194  9B FC 00 08 */	stb r31, 8(r28)
/* 802F65B8 002F3198  98 BC 00 09 */	stb r5, 9(r28)
/* 802F65BC 002F319C  4B FF FC 41 */	bl func_802F61FC
/* 802F65C0 002F31A0  38 7C 00 00 */	addi r3, r28, 0
/* 802F65C4 002F31A4  38 9E 00 00 */	addi r4, r30, 0
/* 802F65C8 002F31A8  4B FF F8 F9 */	bl func_802F5EC0
/* 802F65CC 002F31AC  88 1D 00 03 */	lbz r0, 3(r29)
/* 802F65D0 002F31B0  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 802F65D4 002F31B4  41 82 00 18 */	beq lbl_802F65EC
/* 802F65D8 002F31B8  4B E7 4C 61 */	bl func_8016B238
/* 802F65DC 002F31BC  2C 03 00 00 */	cmpwi r3, 0
/* 802F65E0 002F31C0  40 82 00 0C */	bne lbl_802F65EC
/* 802F65E4 002F31C4  7F E3 FB 78 */	mr r3, r31
/* 802F65E8 002F31C8  48 00 8D 7D */	bl func_802FF364
lbl_802F65EC:
/* 802F65EC 002F31CC  88 7D 00 00 */	lbz r3, 0(r29)
/* 802F65F0 002F31D0  54 63 DF 7E */	rlwinm r3, r3, 0x1b, 0x1d, 0x1f
/* 802F65F4 002F31D4  28 03 00 01 */	cmplwi r3, 1
/* 802F65F8 002F31D8  41 82 00 10 */	beq lbl_802F6608
/* 802F65FC 002F31DC  88 1D 00 04 */	lbz r0, 4(r29)
/* 802F6600 002F31E0  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 802F6604 002F31E4  41 82 00 14 */	beq lbl_802F6618
lbl_802F6608:
/* 802F6608 002F31E8  57 E3 06 3E */	clrlwi r3, r31, 0x18
/* 802F660C 002F31EC  38 80 00 00 */	li r4, 0
/* 802F6610 002F31F0  48 00 32 D9 */	bl func_802F98E8
/* 802F6614 002F31F4  48 00 00 28 */	b lbl_802F663C
lbl_802F6618:
/* 802F6618 002F31F8  28 03 00 02 */	cmplwi r3, 2
/* 802F661C 002F31FC  40 82 00 14 */	bne lbl_802F6630
/* 802F6620 002F3200  57 E3 06 3E */	clrlwi r3, r31, 0x18
/* 802F6624 002F3204  38 80 00 02 */	li r4, 2
/* 802F6628 002F3208  48 00 32 C1 */	bl func_802F98E8
/* 802F662C 002F320C  48 00 00 10 */	b lbl_802F663C
lbl_802F6630:
/* 802F6630 002F3210  57 E3 06 3E */	clrlwi r3, r31, 0x18
/* 802F6634 002F3214  38 80 00 01 */	li r4, 1
/* 802F6638 002F3218  48 00 32 B1 */	bl func_802F98E8
lbl_802F663C:
/* 802F663C 002F321C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 802F6640 002F3220  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 802F6644 002F3224  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 802F6648 002F3228  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 802F664C 002F322C  83 81 00 10 */	lwz r28, 0x10(r1)
/* 802F6650 002F3230  38 21 00 20 */	addi r1, r1, 0x20
/* 802F6654 002F3234  7C 08 03 A6 */	mtlr r0
/* 802F6658 002F3238  4E 80 00 20 */	blr 
}

void func_802F665C(s8 arg0) {
    s32 i;

    func_802F343C();
    lbl_804D6D60 = arg0;
    for (i = 0; i < 6; i++) {
        func_802F6508(i);        
    }
}

asm unk_t func_802F66A4()
{
/* 802F66A4 002F3284  7C 08 02 A6 */	mflr r0
/* 802F66A8 002F3288  3C 60 80 4A */	lis r3, lbl_804A10C8@ha
/* 802F66AC 002F328C  90 01 00 04 */	stw r0, 4(r1)
/* 802F66B0 002F3290  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 802F66B4 002F3294  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 802F66B8 002F3298  3B E3 10 C8 */	addi r31, r3, lbl_804A10C8@l
/* 802F66BC 002F329C  93 C1 00 18 */	stw r30, 0x18(r1)
/* 802F66C0 002F32A0  4B FF CF D1 */	bl func_802F3690
/* 802F66C4 002F32A4  3C A0 80 40 */	lis r5, lbl_803F9598@ha
/* 802F66C8 002F32A8  80 63 00 00 */	lwz r3, 0(r3)
/* 802F66CC 002F32AC  3C 80 80 40 */	lis r4, lbl_803F95AC@ha
/* 802F66D0 002F32B0  4C C6 31 82 */	crclr 6
/* 802F66D4 002F32B4  38 E4 95 AC */	addi r7, r4, lbl_803F95AC@l
/* 802F66D8 002F32B8  38 A5 95 98 */	addi r5, r5, lbl_803F9598@l
/* 802F66DC 002F32BC  38 81 00 08 */	addi r4, r1, 8
/* 802F66E0 002F32C0  38 C1 00 0C */	addi r6, r1, 0xc
/* 802F66E4 002F32C4  39 00 00 00 */	li r8, 0
/* 802F66E8 002F32C8  4B D2 04 09 */	bl func_80016AF0
/* 802F66EC 002F32CC  80 81 00 08 */	lwz r4, 8(r1)
/* 802F66F0 002F32D0  2C 1E 00 00 */	cmpwi r30, 0
/* 802F66F4 002F32D4  80 64 00 00 */	lwz r3, 0(r4)
/* 802F66F8 002F32D8  80 03 00 00 */	lwz r0, 0(r3)
/* 802F66FC 002F32DC  90 1F 02 58 */	stw r0, 0x258(r31)
/* 802F6700 002F32E0  80 64 00 00 */	lwz r3, 0(r4)
/* 802F6704 002F32E4  80 03 00 04 */	lwz r0, 4(r3)
/* 802F6708 002F32E8  90 1F 02 5C */	stw r0, 0x25c(r31)
/* 802F670C 002F32EC  80 64 00 00 */	lwz r3, 0(r4)
/* 802F6710 002F32F0  80 03 00 08 */	lwz r0, 8(r3)
/* 802F6714 002F32F4  90 1F 02 60 */	stw r0, 0x260(r31)
/* 802F6718 002F32F8  80 64 00 00 */	lwz r3, 0(r4)
/* 802F671C 002F32FC  80 03 00 0C */	lwz r0, 0xc(r3)
/* 802F6720 002F3300  90 1F 02 64 */	stw r0, 0x264(r31)
/* 802F6724 002F3304  80 81 00 0C */	lwz r4, 0xc(r1)
/* 802F6728 002F3308  80 64 00 00 */	lwz r3, 0(r4)
/* 802F672C 002F330C  80 03 00 00 */	lwz r0, 0(r3)
/* 802F6730 002F3310  90 1F 02 68 */	stw r0, 0x268(r31)
/* 802F6734 002F3314  80 64 00 00 */	lwz r3, 0(r4)
/* 802F6738 002F3318  80 03 00 04 */	lwz r0, 4(r3)
/* 802F673C 002F331C  90 1F 02 6C */	stw r0, 0x26c(r31)
/* 802F6740 002F3320  80 64 00 00 */	lwz r3, 0(r4)
/* 802F6744 002F3324  80 03 00 08 */	lwz r0, 8(r3)
/* 802F6748 002F3328  90 1F 02 70 */	stw r0, 0x270(r31)
/* 802F674C 002F332C  80 64 00 00 */	lwz r3, 0(r4)
/* 802F6750 002F3330  80 03 00 0C */	lwz r0, 0xc(r3)
/* 802F6754 002F3334  90 1F 02 74 */	stw r0, 0x274(r31)
/* 802F6758 002F3338  41 82 00 18 */	beq lbl_802F6770
/* 802F675C 002F333C  38 00 00 00 */	li r0, 0
/* 802F6760 002F3340  98 0D B6 C0 */	stb r0, lbl_804D6D60@sda21(r13)
/* 802F6764 002F3344  38 7F 00 00 */	addi r3, r31, 0
/* 802F6768 002F3348  38 80 02 58 */	li r4, 0x258
/* 802F676C 002F334C  4B D1 59 F5 */	bl func_8000C160
lbl_802F6770:
/* 802F6770 002F3350  80 01 00 24 */	lwz r0, 0x24(r1)
/* 802F6774 002F3354  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 802F6778 002F3358  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 802F677C 002F335C  38 21 00 20 */	addi r1, r1, 0x20
/* 802F6780 002F3360  7C 08 03 A6 */	mtlr r0
/* 802F6784 002F3364  4E 80 00 20 */	blr
}

void func_802F6788(s32 player_idx) {
    HudValue* player_hud;
    s8 p_idx = (u8)player_idx;
    player_hud = &lbl_804A10C8.players[p_idx & 0xFF];
    if (player_hud->HUD_parent_entity != NULL) {
        func_80390228(player_hud->HUD_parent_entity);
        player_hud->HUD_parent_entity = NULL;
    }
    if (player_hud->next != NULL) {
        func_80390228(player_hud->next);
        player_hud->next = NULL;
    }
    func_802FB650(player_idx & 0xFF);
}

void func_802F6804(void) {
    s32 i;
    HudValue* v;

    i = 0;
    do {
        v = &lbl_804A10C8.players[i & 0xFF];
        if (v->HUD_parent_entity != NULL) {
            func_80390228(v->HUD_parent_entity);
            v->HUD_parent_entity = NULL;
        }
        if (v->next != NULL) {
            func_80390228(v->next);
            v->next = NULL;
        }
        func_802FB650((s8)i & 0xFF);
        i++;
    } while (i < 6);
}

// Hide Percentage Digits
void func_802F6898() {
    s32 i;
    HudIndex* v = &lbl_804A10C8;
    for (i = 0; i < 6; i++) {
        v->players[i].flags.hide_all_digits = 1;
    }
}

// Show All Percentage Digits
void func_802F68F0(void) {
    s32 i;
    HudIndex* v = &lbl_804A10C8;
    for (i = 0; i < 6; i++) {
        v->players[i].flags.hide_all_digits = 0;
    }
}

void func_802F6948(s32 player_idx) {
    HudValue* hud_player;
    Placeholder_8016AE50_ret_val* small_thing;
    HudFlags* hud_player_flags;

    small_thing = func_8016AE50();
    hud_player = &lbl_804A10C8.players[player_idx];
    hud_player_flags = &hud_player->flags;
    if (hud_player_flags->explode_animation != 1) {
        hud_player_flags->explode_animation = 1;
        hud_player_flags->unk40 = 1;
        if (small_thing->flags.unk1 != 0) {
            hud_player->unk9 = 1;
        }
    }
}

// 99.94% complete
// https://decomp.me/scratch/in6rt
void func_802F69C0(s32 player_idx, s32 arg1) {
    HudValue* hud_player;
    HudFlags* hud_player_flags;
    Placeholder_8016AE38_ret_val* big_thing;
    Placeholder_8016AE50_ret_val* small_thing;

    big_thing = func_8016AE38();
    if ((big_thing->unk24C8.top3 != 1U) && (big_thing->unk24CA.unk4 != 0)) {
        func_802F7C30(arg1);
    }
    
    big_thing = func_8016AE38();
    big_thing->unkD = player_idx;
    small_thing = func_8016AE50();
    hud_player = &lbl_804A10C8.players[player_idx];
    hud_player_flags = &hud_player->flags;
    if (hud_player_flags->explode_animation != 1) {
        hud_player_flags->explode_animation = 1;
        hud_player_flags->unk40 = 1;
        if (small_thing->flags.unk1 != 0) {
            hud_player->unk9 = 1;
        }
    }
    if ((big_thing->unk24CA.unk80 != 0) && ((Player_GetPlayerSlotType(player_idx) == 0) || (Player_GetPlayerSlotType(player_idx) == 1)) && (Player_GetStocks(player_idx) == 0)) {
        func_8016B8D4(player_idx, Player_GetPlayerSlotType(player_idx) & 0xFF);
    }
    if ((big_thing->unk24C8.top3 != 1U) && (big_thing->unk24CA.unk4 != 0) && (func_802F7BB4 != NULL)) {
        func_802F7BB4(player_idx);
    }
}

// 99.93% complete
// https://decomp.me/scratch/SDDvF
void func_802F6AF8(s32 player_idx) {
    HudValue* hud_player;
    Placeholder_8016AE38_ret_val* big_thing;
    Placeholder_8016AE50_ret_val* small_thing;
    HudFlags* hud_player_flags;

    big_thing = func_8016AE38();
    big_thing->unkD = player_idx;
    small_thing = func_8016AE50();
    hud_player = &lbl_804A10C8.players[player_idx];
    hud_player_flags = &hud_player->flags;
    if (hud_player_flags->explode_animation != 1) {
        hud_player_flags->explode_animation = 1;
        hud_player_flags->unk40 = 1;
        if (small_thing->flags.unk1 != 0) {
            hud_player->unk9 = 1;
        }
    }
    if ((big_thing->unk24CA.unk80 != 0) && ((Player_GetPlayerSlotType(player_idx) == 0) || (Player_GetPlayerSlotType(player_idx) == 1)) && (Player_GetStocks(player_idx) == 0)) {
        func_8016B8D4(player_idx, Player_GetPlayerSlotType(player_idx) & 0xFF);
    }
    if ((big_thing->unk24C8.top3 != 1U) && (big_thing->unk24CA.unk4 != 0) && (func_802F7AF8 != NULL)) {
        func_802F7AF8(player_idx);
    }
}

// 99.93% complete
// https://decomp.me/scratch/qmpwG
void func_802F6C04(s32 player_idx) {
    HudValue* hud_player;
    HudFlags* hud_player_flags;
    Placeholder_8016AE38_ret_val* big_thing;
    Placeholder_8016AE50_ret_val* small_thing;

    big_thing = func_8016AE38();
    big_thing->unkD = player_idx;
    small_thing = func_8016AE50();
    hud_player = &lbl_804A10C8.players[player_idx];
    hud_player_flags = &hud_player->flags;
    if (hud_player_flags->explode_animation != 1) {
        hud_player_flags->explode_animation = 1;
        hud_player_flags->unk40 = 1;
        if (small_thing->flags.unk1 != 0) {
            hud_player->unk9 = 1;
        }
    }
    if ((big_thing->unk24CA.unk80 != 0) && ((Player_GetPlayerSlotType(player_idx) == 0) || (Player_GetPlayerSlotType(player_idx) == 1)) && (Player_GetStocks(player_idx) == 0)) {
        func_8016B8D4(player_idx, Player_GetPlayerSlotType(player_idx) & 0xFF);
    }
    if ((big_thing->unk24C8.top3 != 1U) && (big_thing->unk24CA.unk4 != 0) && (func_802F7C30 != NULL)) {
        func_802F7C30(player_idx);
    }
}

// 99.93% complete
// https://decomp.me/scratch/cFb6Y
void func_802F6D10(s32 player_idx) {
    HudValue* hud_player;
    Placeholder_8016AE38_ret_val* big_thing;
    Placeholder_8016AE50_ret_val* small_thing;
    HudFlags* hud_player_flags;

    big_thing = func_8016AE38();
    big_thing->unkD = player_idx;
    small_thing = func_8016AE50();
    hud_player = &lbl_804A10C8.players[player_idx];
    hud_player_flags = &hud_player->flags;
    if (hud_player_flags->explode_animation != 1) {
        hud_player_flags->explode_animation = 1;
        hud_player_flags->unk40 = 1;
        if (small_thing->flags.unk1 != 0) {
            hud_player->unk9 = 1;
        }
    }
    if ((big_thing->unk24CA.unk80 != 0) && ((Player_GetPlayerSlotType(player_idx) == 0) || (Player_GetPlayerSlotType(player_idx) == 1)) && (Player_GetStocks(player_idx) == 0)) {
        func_8016B8D4(player_idx, Player_GetPlayerSlotType(player_idx) & 0xFF);
    }
    if ((big_thing->unk24C8.top3 != 1U) && (big_thing->unk24CA.unk4 != 0) && (func_802F7D08 != NULL)) {
        func_802F7D08(player_idx);
    }
}

void func_802F6E1C(void) {
    func_802F6508();
}

void func_802F6E3C(s32 player_num) {
    HudValue* player;

    player = &lbl_804A10C8.players[player_num];
    if (player->HUD_parent_entity != NULL) {
        func_80390CAC(player->HUD_parent_entity);
    }
    if (player->next != NULL) {
        func_80390CAC(player->next);
    }
    func_802FB6AC(player_num);
}

asm unk_t func_802F6EA4()
{
/* 802F6EA4 002F3A84  7C 08 02 A6 */	mflr r0
/* 802F6EA8 002F3A88  2C 03 00 08 */	cmpwi r3, 8
/* 802F6EAC 002F3A8C  90 01 00 04 */	stw r0, 4(r1)
/* 802F6EB0 002F3A90  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 802F6EB4 002F3A94  BF 61 00 24 */	stmw r27, 0x24(r1)
/* 802F6EB8 002F3A98  3B A4 00 00 */	addi r29, r4, 0
/* 802F6EBC 002F3A9C  3B 85 00 00 */	addi r28, r5, 0
/* 802F6EC0 002F3AA0  3B C7 00 00 */	addi r30, r7, 0
/* 802F6EC4 002F3AA4  3B E8 00 00 */	addi r31, r8, 0
/* 802F6EC8 002F3AA8  40 82 00 68 */	bne lbl_802F6F30
/* 802F6ECC 002F3AAC  28 1E 00 00 */	cmplwi r30, 0
/* 802F6ED0 002F3AB0  41 82 00 14 */	beq lbl_802F6EE4
/* 802F6ED4 002F3AB4  39 9E 00 00 */	addi r12, r30, 0
/* 802F6ED8 002F3AB8  7D 88 03 A6 */	mtlr r12
/* 802F6EDC 002F3ABC  38 60 FF FF */	li r3, -1
/* 802F6EE0 002F3AC0  4E 80 00 21 */	blrl 
lbl_802F6EE4:
/* 802F6EE4 002F3AC4  28 1F 00 00 */	cmplwi r31, 0
/* 802F6EE8 002F3AC8  41 82 00 14 */	beq lbl_802F6EFC
/* 802F6EEC 002F3ACC  39 9F 00 00 */	addi r12, r31, 0
/* 802F6EF0 002F3AD0  7D 88 03 A6 */	mtlr r12
/* 802F6EF4 002F3AD4  38 60 FF FF */	li r3, -1
/* 802F6EF8 002F3AD8  4E 80 00 21 */	blrl 
lbl_802F6EFC:
/* 802F6EFC 002F3ADC  2C 1D 00 00 */	cmpwi r29, 0
/* 802F6F00 002F3AE0  41 80 00 14 */	blt lbl_802F6F14
/* 802F6F04 002F3AE4  38 7D 00 00 */	addi r3, r29, 0
/* 802F6F08 002F3AE8  38 80 00 7F */	li r4, 0x7f
/* 802F6F0C 002F3AEC  38 A0 00 40 */	li r5, 0x40
/* 802F6F10 002F3AF0  4B D2 C8 99 */	bl func_800237A8
lbl_802F6F14:
/* 802F6F14 002F3AF4  2C 1D 00 00 */	cmpwi r29, 0
/* 802F6F18 002F3AF8  41 80 01 08 */	blt lbl_802F7020
/* 802F6F1C 002F3AFC  38 7C 00 00 */	addi r3, r28, 0
/* 802F6F20 002F3B00  38 80 00 7F */	li r4, 0x7f
/* 802F6F24 002F3B04  38 A0 00 40 */	li r5, 0x40
/* 802F6F28 002F3B08  4B D2 C8 81 */	bl func_800237A8
/* 802F6F2C 002F3B0C  48 00 00 F4 */	b lbl_802F7020
lbl_802F6F30:
/* 802F6F30 002F3B10  1C 83 00 28 */	mulli r4, r3, 0x28
/* 802F6F34 002F3B14  3C 60 80 40 */	lis r3, lbl_803F9628@ha
/* 802F6F38 002F3B18  38 03 96 28 */	addi r0, r3, lbl_803F9628@l
/* 802F6F3C 002F3B1C  7F 60 22 14 */	add r27, r0, r4
/* 802F6F40 002F3B20  93 BB 00 20 */	stw r29, 0x20(r27)
/* 802F6F44 002F3B24  93 9B 00 24 */	stw r28, 0x24(r27)
/* 802F6F48 002F3B28  98 DB 00 11 */	stb r6, 0x11(r27)
/* 802F6F4C 002F3B2C  80 7B 00 00 */	lwz r3, 0(r27)
/* 802F6F50 002F3B30  28 03 00 00 */	cmplwi r3, 0
/* 802F6F54 002F3B34  41 82 00 08 */	beq lbl_802F6F5C
/* 802F6F58 002F3B38  48 09 92 D1 */	bl func_80390228
lbl_802F6F5C:
/* 802F6F5C 002F3B3C  38 60 00 0E */	li r3, 0xe
/* 802F6F60 002F3B40  38 80 00 0E */	li r4, 0xe
/* 802F6F64 002F3B44  38 A0 00 00 */	li r5, 0
/* 802F6F68 002F3B48  48 09 92 89 */	bl func_803901F0
/* 802F6F6C 002F3B4C  80 9B 00 14 */	lwz r4, 0x14(r27)
/* 802F6F70 002F3B50  7C 7D 1B 78 */	mr r29, r3
/* 802F6F74 002F3B54  80 64 00 00 */	lwz r3, 0(r4)
/* 802F6F78 002F3B58  48 07 9E CD */	bl HSD_JObjLoadJoint
/* 802F6F7C 002F3B5C  3B 83 00 00 */	addi r28, r3, 0
/* 802F6F80 002F3B60  3C 80 08 00 */	lis r4, 0x800
/* 802F6F84 002F3B64  4B D1 AC 95 */	bl func_80011C18
/* 802F6F88 002F3B68  88 8D C1 A9 */	lbz r4, lbl_804D7849@sda21(r13)
/* 802F6F8C 002F3B6C  38 7D 00 00 */	addi r3, r29, 0
/* 802F6F90 002F3B70  38 BC 00 00 */	addi r5, r28, 0
/* 802F6F94 002F3B74  48 09 9A DD */	bl func_80390A70
/* 802F6F98 002F3B78  3C 60 80 39 */	lis r3, func_80391070@ha
/* 802F6F9C 002F3B7C  38 83 10 70 */	addi r4, r3, func_80391070@l
/* 802F6FA0 002F3B80  38 7D 00 00 */	addi r3, r29, 0
/* 802F6FA4 002F3B84  38 A0 00 0B */	li r5, 0xb
/* 802F6FA8 002F3B88  38 C0 00 00 */	li r6, 0
/* 802F6FAC 002F3B8C  48 09 96 F1 */	bl GObj_SetupGXLink
/* 802F6FB0 002F3B90  80 9B 00 08 */	lwz r4, 8(r27)
/* 802F6FB4 002F3B94  28 04 00 00 */	cmplwi r4, 0
/* 802F6FB8 002F3B98  41 82 00 10 */	beq lbl_802F6FC8
/* 802F6FBC 002F3B9C  38 7D 00 00 */	addi r3, r29, 0
/* 802F6FC0 002F3BA0  38 A0 00 00 */	li r5, 0
/* 802F6FC4 002F3BA4  48 09 8D 91 */	bl func_8038FD54
lbl_802F6FC8:
/* 802F6FC8 002F3BA8  80 BB 00 14 */	lwz r5, 0x14(r27)
/* 802F6FCC 002F3BAC  38 7C 00 00 */	addi r3, r28, 0
/* 802F6FD0 002F3BB0  38 80 00 00 */	li r4, 0
/* 802F6FD4 002F3BB4  4B D1 51 15 */	bl func_8000C0E8
/* 802F6FD8 002F3BB8  7F 83 E3 78 */	mr r3, r28
/* 802F6FDC 002F3BBC  C0 22 E0 C8 */	lfs f1, lbl_804DDAA8@sda21(r2)
/* 802F6FE0 002F3BC0  48 07 88 DD */	bl HSD_JObjReqAnimAll
/* 802F6FE4 002F3BC4  7F 83 E3 78 */	mr r3, r28
/* 802F6FE8 002F3BC8  48 07 99 41 */	bl HSD_JObjAnimAll
/* 802F6FEC 002F3BCC  88 1B 00 12 */	lbz r0, 0x12(r27)
/* 802F6FF0 002F3BD0  38 60 00 00 */	li r3, 0
/* 802F6FF4 002F3BD4  50 60 3E 30 */	rlwimi r0, r3, 7, 0x18, 0x18
/* 802F6FF8 002F3BD8  98 1B 00 12 */	stb r0, 0x12(r27)
/* 802F6FFC 002F3BDC  88 1B 00 12 */	lbz r0, 0x12(r27)
/* 802F7000 002F3BE0  50 60 36 72 */	rlwimi r0, r3, 6, 0x19, 0x19
/* 802F7004 002F3BE4  98 1B 00 12 */	stb r0, 0x12(r27)
/* 802F7008 002F3BE8  88 1B 00 12 */	lbz r0, 0x12(r27)
/* 802F700C 002F3BEC  50 60 2E B4 */	rlwimi r0, r3, 5, 0x1a, 0x1a
/* 802F7010 002F3BF0  98 1B 00 12 */	stb r0, 0x12(r27)
/* 802F7014 002F3BF4  93 BB 00 00 */	stw r29, 0(r27)
/* 802F7018 002F3BF8  93 DB 00 18 */	stw r30, 0x18(r27)
/* 802F701C 002F3BFC  93 FB 00 1C */	stw r31, 0x1c(r27)
lbl_802F7020:
/* 802F7020 002F3C00  BB 61 00 24 */	lmw r27, 0x24(r1)
/* 802F7024 002F3C04  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 802F7028 002F3C08  38 21 00 38 */	addi r1, r1, 0x38
/* 802F702C 002F3C0C  7C 08 03 A6 */	mtlr r0
/* 802F7030 002F3C10  4E 80 00 20 */	blr 
}

asm unk_t func_802F7034()
{
/* 802F7034 002F3C14  7C 08 02 A6 */	mflr r0
/* 802F7038 002F3C18  90 01 00 04 */	stw r0, 4(r1)
/* 802F703C 002F3C1C  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 802F7040 002F3C20  93 E1 00 14 */	stw r31, 0x14(r1)
/* 802F7044 002F3C24  7C 7F 1B 78 */	mr r31, r3
/* 802F7048 002F3C28  4B E7 3D F1 */	bl func_8016AE38
/* 802F704C 002F3C2C  80 83 00 10 */	lwz r4, 0x10(r3)
/* 802F7050 002F3C30  2C 04 00 00 */	cmpwi r4, 0
/* 802F7054 002F3C34  41 82 00 0C */	beq lbl_802F7060
/* 802F7058 002F3C38  38 84 FF FF */	addi r4, r4, -1
/* 802F705C 002F3C3C  48 00 00 08 */	b lbl_802F7064
lbl_802F7060:
/* 802F7060 002F3C40  38 80 FF FF */	li r4, -1
lbl_802F7064:
/* 802F7064 002F3C44  80 A3 00 14 */	lwz r5, 0x14(r3)
/* 802F7068 002F3C48  2C 05 00 00 */	cmpwi r5, 0
/* 802F706C 002F3C4C  41 82 00 0C */	beq lbl_802F7078
/* 802F7070 002F3C50  38 A5 FF FF */	addi r5, r5, -1
/* 802F7074 002F3C54  48 00 00 08 */	b lbl_802F707C
lbl_802F7078:
/* 802F7078 002F3C58  38 A0 FF FF */	li r5, -1
lbl_802F707C:
/* 802F707C 002F3C5C  88 03 00 18 */	lbz r0, 0x18(r3)
/* 802F7080 002F3C60  28 00 00 00 */	cmplwi r0, 0
/* 802F7084 002F3C64  41 82 00 0C */	beq lbl_802F7090
/* 802F7088 002F3C68  7C 06 03 78 */	mr r6, r0
/* 802F708C 002F3C6C  48 00 00 08 */	b lbl_802F7094
lbl_802F7090:
/* 802F7090 002F3C70  38 C0 00 00 */	li r6, 0
lbl_802F7094:
/* 802F7094 002F3C74  89 03 00 0B */	lbz r8, 0xb(r3)
/* 802F7098 002F3C78  28 08 00 00 */	cmplwi r8, 0
/* 802F709C 002F3C7C  41 82 00 18 */	beq lbl_802F70B4
/* 802F70A0 002F3C80  38 68 FF FF */	addi r3, r8, -1
/* 802F70A4 002F3C84  38 FF 00 00 */	addi r7, r31, 0
/* 802F70A8 002F3C88  39 00 00 00 */	li r8, 0
/* 802F70AC 002F3C8C  4B FF FD F9 */	bl func_802F6EA4
/* 802F70B0 002F3C90  48 00 00 70 */	b lbl_802F7120
lbl_802F70B4:
/* 802F70B4 002F3C94  88 E3 00 08 */	lbz r7, 8(r3)
/* 802F70B8 002F3C98  28 07 00 01 */	cmplwi r7, 1
/* 802F70BC 002F3C9C  40 82 00 18 */	bne lbl_802F70D4
/* 802F70C0 002F3CA0  38 FF 00 00 */	addi r7, r31, 0
/* 802F70C4 002F3CA4  38 60 00 00 */	li r3, 0
/* 802F70C8 002F3CA8  39 00 00 00 */	li r8, 0
/* 802F70CC 002F3CAC  4B FF FD D9 */	bl func_802F6EA4
/* 802F70D0 002F3CB0  48 00 00 50 */	b lbl_802F7120
lbl_802F70D4:
/* 802F70D4 002F3CB4  88 03 24 CD */	lbz r0, 0x24cd(r3)
/* 802F70D8 002F3CB8  54 00 D7 FF */	rlwinm. r0, r0, 0x1a, 0x1f, 0x1f
/* 802F70DC 002F3CBC  41 82 00 34 */	beq lbl_802F7110
/* 802F70E0 002F3CC0  28 07 00 06 */	cmplwi r7, 6
/* 802F70E4 002F3CC4  40 82 00 18 */	bne lbl_802F70FC
/* 802F70E8 002F3CC8  38 FF 00 00 */	addi r7, r31, 0
/* 802F70EC 002F3CCC  38 60 00 07 */	li r3, 7
/* 802F70F0 002F3CD0  39 00 00 00 */	li r8, 0
/* 802F70F4 002F3CD4  4B FF FD B1 */	bl func_802F6EA4
/* 802F70F8 002F3CD8  48 00 00 28 */	b lbl_802F7120
lbl_802F70FC:
/* 802F70FC 002F3CDC  38 FF 00 00 */	addi r7, r31, 0
/* 802F7100 002F3CE0  38 60 00 06 */	li r3, 6
/* 802F7104 002F3CE4  39 00 00 00 */	li r8, 0
/* 802F7108 002F3CE8  4B FF FD 9D */	bl func_802F6EA4
/* 802F710C 002F3CEC  48 00 00 14 */	b lbl_802F7120
lbl_802F7110:
/* 802F7110 002F3CF0  38 FF 00 00 */	addi r7, r31, 0
/* 802F7114 002F3CF4  38 60 00 05 */	li r3, 5
/* 802F7118 002F3CF8  39 00 00 00 */	li r8, 0
/* 802F711C 002F3CFC  4B FF FD 89 */	bl func_802F6EA4
lbl_802F7120:
/* 802F7120 002F3D00  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 802F7124 002F3D04  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 802F7128 002F3D08  38 21 00 18 */	addi r1, r1, 0x18
/* 802F712C 002F3D0C  7C 08 03 A6 */	mtlr r0
/* 802F7130 002F3D10  4E 80 00 20 */	blr 
}

// in progress
// https://decomp.me/scratch/XzfAH
asm unk_t func_802F7134()
{
/* 802F7134 002F3D14  7C 08 02 A6 */	mflr r0
/* 802F7138 002F3D18  3C 60 80 40 */	lis r3, lbl_803F9628@ha
/* 802F713C 002F3D1C  90 01 00 04 */	stw r0, 4(r1)
/* 802F7140 002F3D20  38 00 00 00 */	li r0, 0
/* 802F7144 002F3D24  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 802F7148 002F3D28  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 802F714C 002F3D2C  3B E3 96 28 */	addi r31, r3, lbl_803F9628@l
/* 802F7150 002F3D30  90 1F 00 00 */	stw r0, 0(r31)
/* 802F7154 002F3D34  90 1F 00 04 */	stw r0, 4(r31)
/* 802F7158 002F3D38  90 1F 00 28 */	stw r0, 0x28(r31)
/* 802F715C 002F3D3C  90 1F 00 2C */	stw r0, 0x2c(r31)
/* 802F7160 002F3D40  90 1F 00 50 */	stw r0, 0x50(r31)
/* 802F7164 002F3D44  90 1F 00 54 */	stw r0, 0x54(r31)
/* 802F7168 002F3D48  90 1F 00 78 */	stw r0, 0x78(r31)
/* 802F716C 002F3D4C  90 1F 00 7C */	stw r0, 0x7c(r31)
/* 802F7170 002F3D50  90 1F 00 A0 */	stw r0, 0xa0(r31)
/* 802F7174 002F3D54  90 1F 00 A4 */	stw r0, 0xa4(r31)
/* 802F7178 002F3D58  90 1F 00 C8 */	stw r0, 0xc8(r31)
/* 802F717C 002F3D5C  90 1F 00 CC */	stw r0, 0xcc(r31)
/* 802F7180 002F3D60  90 1F 00 F0 */	stw r0, 0xf0(r31)
/* 802F7184 002F3D64  90 1F 00 F4 */	stw r0, 0xf4(r31)
/* 802F7188 002F3D68  90 1F 01 18 */	stw r0, 0x118(r31)
/* 802F718C 002F3D6C  90 1F 01 1C */	stw r0, 0x11c(r31)
/* 802F7190 002F3D70  4B FF C5 01 */	bl func_802F3690
/* 802F7194 002F3D74  80 63 00 00 */	lwz r3, 0(r3)
/* 802F7198 002F3D78  38 81 00 1C */	addi r4, r1, 0x1c
/* 802F719C 002F3D7C  38 BF 01 40 */	addi r5, r31, 0x140
/* 802F71A0 002F3D80  4C C6 31 82 */	crclr 6
/* 802F71A4 002F3D84  38 C0 00 00 */	li r6, 0
/* 802F71A8 002F3D88  4B D1 F9 49 */	bl func_80016AF0
/* 802F71AC 002F3D8C  80 61 00 1C */	lwz r3, 0x1c(r1)
/* 802F71B0 002F3D90  80 03 00 00 */	lwz r0, 0(r3)
/* 802F71B4 002F3D94  90 1F 00 14 */	stw r0, 0x14(r31)
/* 802F71B8 002F3D98  80 61 00 1C */	lwz r3, 0x1c(r1)
/* 802F71BC 002F3D9C  80 03 00 04 */	lwz r0, 4(r3)
/* 802F71C0 002F3DA0  90 1F 00 3C */	stw r0, 0x3c(r31)
/* 802F71C4 002F3DA4  80 61 00 1C */	lwz r3, 0x1c(r1)
/* 802F71C8 002F3DA8  80 03 00 08 */	lwz r0, 8(r3)
/* 802F71CC 002F3DAC  90 1F 00 64 */	stw r0, 0x64(r31)
/* 802F71D0 002F3DB0  80 61 00 1C */	lwz r3, 0x1c(r1)
/* 802F71D4 002F3DB4  80 03 00 0C */	lwz r0, 0xc(r3)
/* 802F71D8 002F3DB8  90 1F 00 8C */	stw r0, 0x8c(r31)
/* 802F71DC 002F3DBC  80 61 00 1C */	lwz r3, 0x1c(r1)
/* 802F71E0 002F3DC0  80 03 00 10 */	lwz r0, 0x10(r3)
/* 802F71E4 002F3DC4  90 1F 00 B4 */	stw r0, 0xb4(r31)
/* 802F71E8 002F3DC8  80 61 00 1C */	lwz r3, 0x1c(r1)
/* 802F71EC 002F3DCC  80 03 00 14 */	lwz r0, 0x14(r3)
/* 802F71F0 002F3DD0  90 1F 00 DC */	stw r0, 0xdc(r31)
/* 802F71F4 002F3DD4  80 61 00 1C */	lwz r3, 0x1c(r1)
/* 802F71F8 002F3DD8  80 03 00 18 */	lwz r0, 0x18(r3)
/* 802F71FC 002F3DDC  90 1F 01 04 */	stw r0, 0x104(r31)
/* 802F7200 002F3DE0  80 61 00 1C */	lwz r3, 0x1c(r1)
/* 802F7204 002F3DE4  80 03 00 1C */	lwz r0, 0x1c(r3)
/* 802F7208 002F3DE8  90 1F 01 2C */	stw r0, 0x12c(r31)
/* 802F720C 002F3DEC  80 01 00 34 */	lwz r0, 0x34(r1)
/* 802F7210 002F3DF0  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 802F7214 002F3DF4  38 21 00 30 */	addi r1, r1, 0x30
/* 802F7218 002F3DF8  7C 08 03 A6 */	mtlr r0
/* 802F721C 002F3DFC  4E 80 00 20 */	blr 
}

// free
void func_802F7220(void) {
    s32 i;
    for (i = 0; i < 8; i++) {
        if (lbl_803F9628.things[i].unk0 != NULL) {
            func_80390228(lbl_803F9628.things[i].unk0);
            lbl_803F9628.things[i].unk0 = NULL;
        }
    }
}


