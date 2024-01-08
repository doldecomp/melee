.include "macros.inc"

.section .text  # 0x803124BC - 0x8032261C

.global un_8031E124
un_8031E124:
/* 8031E124 0031AD04  7C 08 02 A6 */	mflr r0
/* 8031E128 0031AD08  90 01 00 04 */	stw r0, 4(r1)
/* 8031E12C 0031AD0C  94 21 FF A8 */	stwu r1, -0x58(r1)
/* 8031E130 0031AD10  93 E1 00 54 */	stw r31, 0x54(r1)
/* 8031E134 0031AD14  3B E3 00 00 */	addi r31, r3, 0
/* 8031E138 0031AD18  38 60 00 06 */	li r3, 6
/* 8031E13C 0031AD1C  93 C1 00 50 */	stw r30, 0x50(r1)
/* 8031E140 0031AD20  3B C4 00 00 */	addi r30, r4, 0
/* 8031E144 0031AD24  93 A1 00 4C */	stw r29, 0x4c(r1)
/* 8031E148 0031AD28  3B A5 00 00 */	addi r29, r5, 0
/* 8031E14C 0031AD2C  4B D0 AA 51 */	bl Camera_80028B9C
/* 8031E150 0031AD30  4B CF 1B 8D */	bl lb_8000FCDC
/* 8031E154 0031AD34  4B D2 3B 25 */	bl mpColl_80041C78
/* 8031E158 0031AD38  38 60 00 40 */	li r3, 0x40
/* 8031E15C 0031AD3C  4B EA 22 1D */	bl Ground_801C0378
/* 8031E160 0031AD40  38 60 00 11 */	li r3, 0x11
/* 8031E164 0031AD44  38 80 00 00 */	li r4, 0
/* 8031E168 0031AD48  4B F0 70 81 */	bl Stage_802251E8
/* 8031E16C 0031AD4C  4B F4 8E 3D */	bl Item_80266FA8
/* 8031E170 0031AD50  4B F4 8E 5D */	bl Item_80266FCC
/* 8031E174 0031AD54  C0 22 E6 B0 */	lfs f1, un_804DE090@sda21(r2)
/* 8031E178 0031AD58  4B EA 23 45 */	bl Ground_801C04BC
/* 8031E17C 0031AD5C  4B F0 70 D1 */	bl Stage_8022524C
/* 8031E180 0031AD60  38 60 00 11 */	li r3, 0x11
/* 8031E184 0031AD64  38 80 00 00 */	li r4, 0
/* 8031E188 0031AD68  4B F0 71 A5 */	bl Stage_8022532C
/* 8031E18C 0031AD6C  4B DA 09 9D */	bl ftDemo_ObjAllocInit
/* 8031E190 0031AD70  4B D1 8B C9 */	bl Player_InitAllPlayers
/* 8031E194 0031AD74  80 8D B8 F4 */	lwz r4, un_804D6F94@sda21(r13)
/* 8031E198 0031AD78  38 7F 00 00 */	addi r3, r31, 0
/* 8031E19C 0031AD7C  38 A0 00 03 */	li r5, 3
/* 8031E1A0 0031AD80  4B D1 8C 81 */	bl Player_80036E20
/* 8031E1A4 0031AD84  38 60 00 00 */	li r3, 0
/* 8031E1A8 0031AD88  38 9F 00 00 */	addi r4, r31, 0
/* 8031E1AC 0031AD8C  4B D1 41 F5 */	bl Player_SetPlayerCharacter
/* 8031E1B0 0031AD90  38 60 00 00 */	li r3, 0
/* 8031E1B4 0031AD94  38 9E 00 00 */	addi r4, r30, 0
/* 8031E1B8 0031AD98  4B D1 50 51 */	bl Player_SetCostumeId
/* 8031E1BC 0031AD9C  38 60 00 00 */	li r3, 0
/* 8031E1C0 0031ADA0  38 80 00 00 */	li r4, 0
/* 8031E1C4 0031ADA4  4B D1 53 09 */	bl Player_SetPlayerId
/* 8031E1C8 0031ADA8  38 60 00 00 */	li r3, 0
/* 8031E1CC 0031ADAC  38 80 00 02 */	li r4, 2
/* 8031E1D0 0031ADB0  4B D1 43 7D */	bl Player_SetSlottype
/* 8031E1D4 0031ADB4  38 60 00 00 */	li r3, 0
/* 8031E1D8 0031ADB8  C0 22 E6 B4 */	lfs f1, un_804DE094@sda21(r2)
/* 8031E1DC 0031ADBC  4B D1 4E B9 */	bl Player_SetFacingDirection
/* 8031E1E0 0031ADC0  3C 60 80 40 */	lis r3, un_804000D0@ha
/* 8031E1E4 0031ADC4  38 83 00 D0 */	addi r4, r3, un_804000D0@l
/* 8031E1E8 0031ADC8  38 60 00 00 */	li r3, 0
/* 8031E1EC 0031ADCC  4B D1 45 7D */	bl Player_80032768
/* 8031E1F0 0031ADD0  38 60 00 00 */	li r3, 0
/* 8031E1F4 0031ADD4  38 80 00 08 */	li r4, 8
/* 8031E1F8 0031ADD8  4B D1 8D 3D */	bl Player_80036F34
/* 8031E1FC 0031ADDC  80 8D B8 FC */	lwz r4, un_804D6F9C@sda21(r13)
/* 8031E200 0031ADE0  38 60 00 04 */	li r3, 4
/* 8031E204 0031ADE4  38 A0 00 07 */	li r5, 7
/* 8031E208 0031ADE8  4B D1 8C 19 */	bl Player_80036E20
/* 8031E20C 0031ADEC  38 60 00 01 */	li r3, 1
/* 8031E210 0031ADF0  38 80 00 04 */	li r4, 4
/* 8031E214 0031ADF4  4B D1 41 8D */	bl Player_SetPlayerCharacter
/* 8031E218 0031ADF8  38 60 00 01 */	li r3, 1
/* 8031E21C 0031ADFC  38 9D 00 00 */	addi r4, r29, 0
/* 8031E220 0031AE00  4B D1 4F E9 */	bl Player_SetCostumeId
/* 8031E224 0031AE04  38 60 00 01 */	li r3, 1
/* 8031E228 0031AE08  38 80 00 00 */	li r4, 0
/* 8031E22C 0031AE0C  4B D1 52 A1 */	bl Player_SetPlayerId
/* 8031E230 0031AE10  38 60 00 01 */	li r3, 1
/* 8031E234 0031AE14  38 80 00 02 */	li r4, 2
/* 8031E238 0031AE18  4B D1 43 15 */	bl Player_SetSlottype
/* 8031E23C 0031AE1C  38 60 00 01 */	li r3, 1
/* 8031E240 0031AE20  C0 22 E6 B8 */	lfs f1, un_804DE098@sda21(r2)
/* 8031E244 0031AE24  4B D1 4E 51 */	bl Player_SetFacingDirection
/* 8031E248 0031AE28  38 60 00 01 */	li r3, 1
/* 8031E24C 0031AE2C  38 80 00 0E */	li r4, 0xe
/* 8031E250 0031AE30  4B D1 8C E5 */	bl Player_80036F34
/* 8031E254 0031AE34  38 60 00 01 */	li r3, 1
/* 8031E258 0031AE38  4B D1 5E B9 */	bl Player_GetEntity
/* 8031E25C 0031AE3C  90 6D B9 04 */	stw r3, un_804D6FA4@sda21(r13)
/* 8031E260 0031AE40  C0 22 E6 BC */	lfs f1, un_804DE09C@sda21(r2)
/* 8031E264 0031AE44  80 6D B9 04 */	lwz r3, un_804D6FA4@sda21(r13)
/* 8031E268 0031AE48  83 A3 00 28 */	lwz r29, 0x28(r3)
/* 8031E26C 0031AE4C  7F A3 EB 78 */	mr r3, r29
/* 8031E270 0031AE50  48 05 16 4D */	bl HSD_JObjReqAnimAll
/* 8031E274 0031AE54  7F A3 EB 78 */	mr r3, r29
/* 8031E278 0031AE58  48 05 26 B1 */	bl HSD_JObjAnimAll
/* 8031E27C 0031AE5C  80 6D B9 04 */	lwz r3, un_804D6FA4@sda21(r13)
/* 8031E280 0031AE60  83 C3 00 28 */	lwz r30, 0x28(r3)
/* 8031E284 0031AE64  4B EA B7 8D */	bl grLib_801C9A10
/* 8031E288 0031AE68  28 1E 00 00 */	cmplwi r30, 0
/* 8031E28C 0031AE6C  3B E3 00 00 */	addi r31, r3, 0
/* 8031E290 0031AE70  40 82 00 14 */	bne .L_8031E2A4
/* 8031E294 0031AE74  38 6D A4 48 */	addi r3, r13, un_804D5AE8@sda21
/* 8031E298 0031AE78  38 80 03 D3 */	li r4, 0x3d3
/* 8031E29C 0031AE7C  38 AD A4 50 */	addi r5, r13, un_804D5AF0@sda21
/* 8031E2A0 0031AE80  48 06 9F 81 */	bl __assert
.L_8031E2A4:
/* 8031E2A4 0031AE84  80 9E 00 38 */	lwz r4, 0x38(r30)
/* 8031E2A8 0031AE88  7F A3 EB 78 */	mr r3, r29
/* 8031E2AC 0031AE8C  80 1E 00 3C */	lwz r0, 0x3c(r30)
/* 8031E2B0 0031AE90  90 9F 00 0C */	stw r4, 0xc(r31)
/* 8031E2B4 0031AE94  90 1F 00 10 */	stw r0, 0x10(r31)
/* 8031E2B8 0031AE98  80 1E 00 40 */	lwz r0, 0x40(r30)
/* 8031E2BC 0031AE9C  90 1F 00 14 */	stw r0, 0x14(r31)
/* 8031E2C0 0031AEA0  C0 22 E6 C0 */	lfs f1, un_804DE0A0@sda21(r2)
/* 8031E2C4 0031AEA4  48 05 15 F9 */	bl HSD_JObjReqAnimAll
/* 8031E2C8 0031AEA8  38 60 00 1C */	li r3, 0x1c
/* 8031E2CC 0031AEAC  4B D0 8C 61 */	bl lbAudioAx_80026F2C
/* 8031E2D0 0031AEB0  38 60 00 0C */	li r3, 0xc
/* 8031E2D4 0031AEB4  38 C0 40 00 */	li r6, 0x4000
/* 8031E2D8 0031AEB8  38 A0 08 00 */	li r5, 0x800
/* 8031E2DC 0031AEBC  4B D0 8D 51 */	bl lbAudioAx_8002702C
/* 8031E2E0 0031AEC0  4B D0 8E 89 */	bl lbAudioAx_80027168
/* 8031E2E4 0031AEC4  4B D0 93 65 */	bl lbAudioAx_80027648
/* 8031E2E8 0031AEC8  80 01 00 5C */	lwz r0, 0x5c(r1)
/* 8031E2EC 0031AECC  83 E1 00 54 */	lwz r31, 0x54(r1)
/* 8031E2F0 0031AED0  83 C1 00 50 */	lwz r30, 0x50(r1)
/* 8031E2F4 0031AED4  83 A1 00 4C */	lwz r29, 0x4c(r1)
/* 8031E2F8 0031AED8  38 21 00 58 */	addi r1, r1, 0x58
/* 8031E2FC 0031AEDC  7C 08 03 A6 */	mtlr r0
/* 8031E300 0031AEE0  4E 80 00 20 */	blr
.L_8031E304:
/* 8031E304 0031AEE4  7C 08 02 A6 */	mflr r0
/* 8031E308 0031AEE8  90 01 00 04 */	stw r0, 4(r1)
/* 8031E30C 0031AEEC  94 21 FF F8 */	stwu r1, -8(r1)
/* 8031E310 0031AEF0  80 63 00 28 */	lwz r3, 0x28(r3)
/* 8031E314 0031AEF4  48 05 26 15 */	bl HSD_JObjAnimAll
/* 8031E318 0031AEF8  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8031E31C 0031AEFC  38 21 00 08 */	addi r1, r1, 8
/* 8031E320 0031AF00  7C 08 03 A6 */	mtlr r0
/* 8031E324 0031AF04  4E 80 00 20 */	blr
.L_8031E328:
/* 8031E328 0031AF08  7C 08 02 A6 */	mflr r0
/* 8031E32C 0031AF0C  90 01 00 04 */	stw r0, 4(r1)
/* 8031E330 0031AF10  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8031E334 0031AF14  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8031E338 0031AF18  3B E3 00 00 */	addi r31, r3, 0
/* 8031E33C 0031AF1C  38 60 00 00 */	li r3, 0
/* 8031E340 0031AF20  4B CF 10 4D */	bl lbShadow_8000F38C
/* 8031E344 0031AF24  80 7F 00 28 */	lwz r3, 0x28(r31)
/* 8031E348 0031AF28  48 04 A1 11 */	bl HSD_CObjSetCurrent
/* 8031E34C 0031AF2C  2C 03 00 00 */	cmpwi r3, 0
/* 8031E350 0031AF30  41 82 00 58 */	beq .L_8031E3A8
/* 8031E354 0031AF34  38 CD B9 00 */	addi r6, r13, un_804D6FA0@sda21
/* 8031E358 0031AF38  88 6D B9 00 */	lbz r3, un_804D6FA0@sda21(r13)
/* 8031E35C 0031AF3C  88 86 00 01 */	lbz r4, 1(r6)
/* 8031E360 0031AF40  88 A6 00 02 */	lbz r5, 2(r6)
/* 8031E364 0031AF44  88 C6 00 03 */	lbz r6, 3(r6)
/* 8031E368 0031AF48  48 05 67 21 */	bl HSD_SetEraseColor
/* 8031E36C 0031AF4C  80 7F 00 28 */	lwz r3, 0x28(r31)
/* 8031E370 0031AF50  38 80 00 01 */	li r4, 1
/* 8031E374 0031AF54  38 A0 00 00 */	li r5, 0
/* 8031E378 0031AF58  38 C0 00 01 */	li r6, 1
/* 8031E37C 0031AF5C  48 04 93 7D */	bl HSD_CObjEraseScreen
/* 8031E380 0031AF60  7F E3 FB 78 */	mr r3, r31
/* 8031E384 0031AF64  4B FF E6 81 */	bl un_8031CA04
/* 8031E388 0031AF68  38 00 02 81 */	li r0, 0x281
/* 8031E38C 0031AF6C  90 1F 00 24 */	stw r0, 0x24(r31)
/* 8031E390 0031AF70  38 00 00 00 */	li r0, 0
/* 8031E394 0031AF74  38 7F 00 00 */	addi r3, r31, 0
/* 8031E398 0031AF78  90 1F 00 20 */	stw r0, 0x20(r31)
/* 8031E39C 0031AF7C  38 80 00 07 */	li r4, 7
/* 8031E3A0 0031AF80  48 07 2B 31 */	bl HSD_GObj_80390ED0
/* 8031E3A4 0031AF84  48 04 A2 65 */	bl HSD_CObjEndCurrent
.L_8031E3A8:
/* 8031E3A8 0031AF88  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8031E3AC 0031AF8C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8031E3B0 0031AF90  38 21 00 20 */	addi r1, r1, 0x20
/* 8031E3B4 0031AF94  7C 08 03 A6 */	mtlr r0
/* 8031E3B8 0031AF98  4E 80 00 20 */	blr
.L_8031E3BC:
/* 8031E3BC 0031AF9C  7C 08 02 A6 */	mflr r0
/* 8031E3C0 0031AFA0  90 01 00 04 */	stw r0, 4(r1)
/* 8031E3C4 0031AFA4  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8031E3C8 0031AFA8  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8031E3CC 0031AFAC  83 E3 00 28 */	lwz r31, 0x28(r3)
/* 8031E3D0 0031AFB0  7F E3 FB 78 */	mr r3, r31
/* 8031E3D4 0031AFB4  48 04 96 E5 */	bl HSD_CObjAnim
/* 8031E3D8 0031AFB8  80 7F 00 24 */	lwz r3, 0x24(r31)
/* 8031E3DC 0031AFBC  C0 22 E6 C4 */	lfs f1, un_804DE0A4@sda21(r2)
/* 8031E3E0 0031AFC0  80 63 00 18 */	lwz r3, 0x18(r3)
/* 8031E3E4 0031AFC4  C0 03 00 04 */	lfs f0, 4(r3)
/* 8031E3E8 0031AFC8  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8031E3EC 0031AFCC  40 82 00 24 */	bne .L_8031E410
/* 8031E3F0 0031AFD0  38 60 00 0E */	li r3, 0xe
/* 8031E3F4 0031AFD4  38 80 00 00 */	li r4, 0
/* 8031E3F8 0031AFD8  4B FF E5 BD */	bl un_8031C9B4
/* 8031E3FC 0031AFDC  3C 60 00 07 */	lis r3, 0x00068FB9@ha
/* 8031E400 0031AFE0  38 63 8F B9 */	addi r3, r3, 0x00068FB9@l
/* 8031E404 0031AFE4  38 80 00 7F */	li r4, 0x7f
/* 8031E408 0031AFE8  38 A0 00 40 */	li r5, 0x40
/* 8031E40C 0031AFEC  4B D0 53 9D */	bl lbAudioAx_800237A8
.L_8031E410:
/* 8031E410 0031AFF0  80 7F 00 24 */	lwz r3, 0x24(r31)
/* 8031E414 0031AFF4  80 63 00 18 */	lwz r3, 0x18(r3)
/* 8031E418 0031AFF8  C0 23 00 04 */	lfs f1, 4(r3)
/* 8031E41C 0031AFFC  C0 03 00 0C */	lfs f0, 0xc(r3)
/* 8031E420 0031B000  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8031E424 0031B004  40 82 00 0C */	bne .L_8031E430
/* 8031E428 0031B008  4B CF 61 CD */	bl lb_800145F4
/* 8031E42C 0031B00C  4B E8 67 35 */	bl gm_801A4B60
.L_8031E430:
/* 8031E430 0031B010  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8031E434 0031B014  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8031E438 0031B018  38 21 00 18 */	addi r1, r1, 0x18
/* 8031E43C 0031B01C  7C 08 03 A6 */	mtlr r0
/* 8031E440 0031B020  4E 80 00 20 */	blr
.global un_8031E444
un_8031E444:
/* 8031E444 0031B024  7C 08 02 A6 */	mflr r0
/* 8031E448 0031B028  3C 80 80 40 */	lis r4, un_804000D0@ha
/* 8031E44C 0031B02C  90 01 00 04 */	stw r0, 4(r1)
/* 8031E450 0031B030  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8031E454 0031B034  BF 41 00 10 */	stmw r26, 0x10(r1)
/* 8031E458 0031B038  3B E3 00 00 */	addi r31, r3, 0
/* 8031E45C 0031B03C  3B 84 00 D0 */	addi r28, r4, un_804000D0@l
/* 8031E460 0031B040  4B D0 52 7D */	bl lbAudioAx_800236DC
/* 8031E464 0031B044  4B D3 D0 55 */	bl efLib_8005B4B8
/* 8031E468 0031B048  38 60 00 00 */	li r3, 0
/* 8031E46C 0031B04C  4B D4 8F 11 */	bl efAsync_8006737C
/* 8031E470 0031B050  8B BF 00 00 */	lbz r29, 0(r31)
/* 8031E474 0031B054  38 7C 00 0C */	addi r3, r28, 0xc
/* 8031E478 0031B058  38 BC 00 18 */	addi r5, r28, 0x18
/* 8031E47C 0031B05C  4C C6 31 82 */	crclr 6
/* 8031E480 0031B060  38 8D B8 F0 */	addi r4, r13, un_804D6F90@sda21
/* 8031E484 0031B064  38 C0 00 00 */	li r6, 0
/* 8031E488 0031B068  4B CF 87 DD */	bl lbArchive_80016C64
/* 8031E48C 0031B06C  90 6D B8 FC */	stw r3, un_804D6F9C@sda21(r13)
/* 8031E490 0031B070  7F A3 EB 78 */	mr r3, r29
/* 8031E494 0031B074  4B FF E5 09 */	bl un_8031C99C
/* 8031E498 0031B078  4C C6 31 82 */	crclr 6
/* 8031E49C 0031B07C  38 80 00 00 */	li r4, 0
/* 8031E4A0 0031B080  4B CF 87 C5 */	bl lbArchive_80016C64
/* 8031E4A4 0031B084  90 6D B8 F4 */	stw r3, un_804D6F94@sda21(r13)
/* 8031E4A8 0031B088  38 7C 00 28 */	addi r3, r28, 0x28
/* 8031E4AC 0031B08C  4C C6 31 82 */	crclr 6
/* 8031E4B0 0031B090  38 80 00 00 */	li r4, 0
/* 8031E4B4 0031B094  4B CF 87 B1 */	bl lbArchive_80016C64
/* 8031E4B8 0031B098  90 6D B8 F8 */	stw r3, un_804D6F98@sda21(r13)
/* 8031E4BC 0031B09C  38 60 00 0B */	li r3, 0xb
/* 8031E4C0 0031B0A0  38 80 00 03 */	li r4, 3
/* 8031E4C4 0031B0A4  38 A0 00 00 */	li r5, 0
/* 8031E4C8 0031B0A8  48 07 1D 29 */	bl GObj_Create
/* 8031E4CC 0031B0AC  80 8D B8 F0 */	lwz r4, un_804D6F90@sda21(r13)
/* 8031E4D0 0031B0B0  7C 7D 1B 78 */	mr r29, r3
/* 8031E4D4 0031B0B4  80 64 00 0C */	lwz r3, 0xc(r4)
/* 8031E4D8 0031B0B8  80 63 00 00 */	lwz r3, 0(r3)
/* 8031E4DC 0031B0BC  48 05 F7 5D */	bl HSD_FogLoadDesc
/* 8031E4E0 0031B0C0  3B 83 00 00 */	addi r28, r3, 0
/* 8031E4E4 0031B0C4  88 8D C1 A8 */	lbz r4, HSD_GObj_804D7848@sda21(r13)
/* 8031E4E8 0031B0C8  38 7D 00 00 */	addi r3, r29, 0
/* 8031E4EC 0031B0CC  38 BC 00 00 */	addi r5, r28, 0
/* 8031E4F0 0031B0D0  48 07 25 81 */	bl HSD_GObjObjet_80390A70
/* 8031E4F4 0031B0D4  3C 60 80 39 */	lis r3, HSD_GObj_803910B4@ha
/* 8031E4F8 0031B0D8  38 83 10 B4 */	addi r4, r3, HSD_GObj_803910B4@l
/* 8031E4FC 0031B0DC  38 7D 00 00 */	addi r3, r29, 0
/* 8031E500 0031B0E0  38 A0 00 00 */	li r5, 0
/* 8031E504 0031B0E4  38 C0 00 00 */	li r6, 0
/* 8031E508 0031B0E8  48 07 21 95 */	bl GObj_SetupGXLink
/* 8031E50C 0031B0EC  80 1C 00 18 */	lwz r0, 0x18(r28)
/* 8031E510 0031B0F0  38 60 00 0B */	li r3, 0xb
/* 8031E514 0031B0F4  38 80 00 03 */	li r4, 3
/* 8031E518 0031B0F8  90 0D B9 00 */	stw r0, un_804D6FA0@sda21(r13)
/* 8031E51C 0031B0FC  38 A0 00 00 */	li r5, 0
/* 8031E520 0031B100  48 07 1C D1 */	bl GObj_Create
/* 8031E524 0031B104  80 8D B8 F0 */	lwz r4, un_804D6F90@sda21(r13)
/* 8031E528 0031B108  7C 7C 1B 78 */	mr r28, r3
/* 8031E52C 0031B10C  80 64 00 08 */	lwz r3, 8(r4)
/* 8031E530 0031B110  4B CF 35 95 */	bl lb_80011AC4
/* 8031E534 0031B114  88 8D C1 AA */	lbz r4, HSD_GObj_804D784A@sda21(r13)
/* 8031E538 0031B118  38 A3 00 00 */	addi r5, r3, 0
/* 8031E53C 0031B11C  38 7C 00 00 */	addi r3, r28, 0
/* 8031E540 0031B120  48 07 25 31 */	bl HSD_GObjObjet_80390A70
/* 8031E544 0031B124  3C 60 80 39 */	lis r3, HSD_GObj_80391044@ha
/* 8031E548 0031B128  38 83 10 44 */	addi r4, r3, HSD_GObj_80391044@l
/* 8031E54C 0031B12C  38 7C 00 00 */	addi r3, r28, 0
/* 8031E550 0031B130  38 A0 00 00 */	li r5, 0
/* 8031E554 0031B134  38 C0 00 00 */	li r6, 0
/* 8031E558 0031B138  48 07 21 45 */	bl GObj_SetupGXLink
/* 8031E55C 0031B13C  38 60 00 13 */	li r3, 0x13
/* 8031E560 0031B140  38 80 00 14 */	li r4, 0x14
/* 8031E564 0031B144  38 A0 00 00 */	li r5, 0
/* 8031E568 0031B148  48 07 1C 89 */	bl GObj_Create
/* 8031E56C 0031B14C  80 8D B8 F0 */	lwz r4, un_804D6F90@sda21(r13)
/* 8031E570 0031B150  7C 7D 1B 78 */	mr r29, r3
/* 8031E574 0031B154  80 64 00 04 */	lwz r3, 4(r4)
/* 8031E578 0031B158  80 63 00 00 */	lwz r3, 0(r3)
/* 8031E57C 0031B15C  4B CF 55 99 */	bl lb_80013B14
/* 8031E580 0031B160  3B 83 00 00 */	addi r28, r3, 0
/* 8031E584 0031B164  88 8D C1 AB */	lbz r4, HSD_GObj_804D784B@sda21(r13)
/* 8031E588 0031B168  38 7D 00 00 */	addi r3, r29, 0
/* 8031E58C 0031B16C  38 BC 00 00 */	addi r5, r28, 0
/* 8031E590 0031B170  48 07 24 E1 */	bl HSD_GObjObjet_80390A70
/* 8031E594 0031B174  3C 60 80 32 */	lis r3, .L_8031E328@ha
/* 8031E598 0031B178  38 83 E3 28 */	addi r4, r3, .L_8031E328@l
/* 8031E59C 0031B17C  38 7D 00 00 */	addi r3, r29, 0
/* 8031E5A0 0031B180  38 A0 00 05 */	li r5, 5
/* 8031E5A4 0031B184  48 07 21 B9 */	bl GObj_SetupGXLinkMax
/* 8031E5A8 0031B188  80 8D B8 F0 */	lwz r4, un_804D6F90@sda21(r13)
/* 8031E5AC 0031B18C  7F 83 E3 78 */	mr r3, r28
/* 8031E5B0 0031B190  80 84 00 04 */	lwz r4, 4(r4)
/* 8031E5B4 0031B194  80 84 00 04 */	lwz r4, 4(r4)
/* 8031E5B8 0031B198  80 84 00 00 */	lwz r4, 0(r4)
/* 8031E5BC 0031B19C  48 04 93 11 */	bl HSD_CObjAddAnim
/* 8031E5C0 0031B1A0  7F 83 E3 78 */	mr r3, r28
/* 8031E5C4 0031B1A4  C0 22 E6 C0 */	lfs f1, un_804DE0A0@sda21(r2)
/* 8031E5C8 0031B1A8  48 04 95 41 */	bl HSD_CObjReqAnim
/* 8031E5CC 0031B1AC  7F 83 E3 78 */	mr r3, r28
/* 8031E5D0 0031B1B0  48 04 94 E9 */	bl HSD_CObjAnim
/* 8031E5D4 0031B1B4  3C 60 80 32 */	lis r3, .L_8031E3BC@ha
/* 8031E5D8 0031B1B8  38 83 E3 BC */	addi r4, r3, .L_8031E3BC@l
/* 8031E5DC 0031B1BC  38 7D 00 00 */	addi r3, r29, 0
/* 8031E5E0 0031B1C0  38 A0 00 00 */	li r5, 0
/* 8031E5E4 0031B1C4  48 07 17 71 */	bl HSD_GObjProc_8038FD54
/* 8031E5E8 0031B1C8  38 00 00 00 */	li r0, 0
/* 8031E5EC 0031B1CC  3C 80 80 39 */	lis r4, HSD_GObj_80391070@ha
/* 8031E5F0 0031B1D0  3C 60 80 32 */	lis r3, .L_8031E304@ha
/* 8031E5F4 0031B1D4  54 1E 10 3A */	slwi r30, r0, 2
/* 8031E5F8 0031B1D8  3B 84 10 70 */	addi r28, r4, HSD_GObj_80391070@l
/* 8031E5FC 0031B1DC  3B A3 E3 04 */	addi r29, r3, .L_8031E304@l
/* 8031E600 0031B1E0  48 00 00 94 */	b .L_8031E694
.L_8031E604:
/* 8031E604 0031B1E4  38 60 00 0E */	li r3, 0xe
/* 8031E608 0031B1E8  38 80 00 0F */	li r4, 0xf
/* 8031E60C 0031B1EC  38 A0 00 00 */	li r5, 0
/* 8031E610 0031B1F0  48 07 1B E1 */	bl GObj_Create
/* 8031E614 0031B1F4  80 8D B8 F0 */	lwz r4, un_804D6F90@sda21(r13)
/* 8031E618 0031B1F8  7C 7A 1B 78 */	mr r26, r3
/* 8031E61C 0031B1FC  80 64 00 00 */	lwz r3, 0(r4)
/* 8031E620 0031B200  7C 63 F0 2E */	lwzx r3, r3, r30
/* 8031E624 0031B204  80 63 00 00 */	lwz r3, 0(r3)
/* 8031E628 0031B208  48 05 28 1D */	bl HSD_JObjLoadJoint
/* 8031E62C 0031B20C  3B 63 00 00 */	addi r27, r3, 0
/* 8031E630 0031B210  88 8D C1 A9 */	lbz r4, HSD_GObj_804D7849@sda21(r13)
/* 8031E634 0031B214  38 7A 00 00 */	addi r3, r26, 0
/* 8031E638 0031B218  38 BB 00 00 */	addi r5, r27, 0
/* 8031E63C 0031B21C  48 07 24 35 */	bl HSD_GObjObjet_80390A70
/* 8031E640 0031B220  38 7A 00 00 */	addi r3, r26, 0
/* 8031E644 0031B224  38 9C 00 00 */	addi r4, r28, 0
/* 8031E648 0031B228  38 A0 00 09 */	li r5, 9
/* 8031E64C 0031B22C  38 C0 00 00 */	li r6, 0
/* 8031E650 0031B230  48 07 20 4D */	bl GObj_SetupGXLink
/* 8031E654 0031B234  80 8D B8 F0 */	lwz r4, un_804D6F90@sda21(r13)
/* 8031E658 0031B238  38 7B 00 00 */	addi r3, r27, 0
/* 8031E65C 0031B23C  38 A0 00 00 */	li r5, 0
/* 8031E660 0031B240  80 84 00 00 */	lwz r4, 0(r4)
/* 8031E664 0031B244  7C 84 F0 2E */	lwzx r4, r4, r30
/* 8031E668 0031B248  4B E4 A2 F5 */	bl gm_8016895C
/* 8031E66C 0031B24C  7F 63 DB 78 */	mr r3, r27
/* 8031E670 0031B250  C0 22 E6 C0 */	lfs f1, un_804DE0A0@sda21(r2)
/* 8031E674 0031B254  48 05 12 49 */	bl HSD_JObjReqAnimAll
/* 8031E678 0031B258  7F 63 DB 78 */	mr r3, r27
/* 8031E67C 0031B25C  48 05 22 AD */	bl HSD_JObjAnimAll
/* 8031E680 0031B260  38 7A 00 00 */	addi r3, r26, 0
/* 8031E684 0031B264  38 9D 00 00 */	addi r4, r29, 0
/* 8031E688 0031B268  38 A0 00 17 */	li r5, 0x17
/* 8031E68C 0031B26C  48 07 16 C9 */	bl HSD_GObjProc_8038FD54
/* 8031E690 0031B270  3B DE 00 04 */	addi r30, r30, 4
.L_8031E694:
/* 8031E694 0031B274  80 6D B8 F0 */	lwz r3, un_804D6F90@sda21(r13)
/* 8031E698 0031B278  80 63 00 00 */	lwz r3, 0(r3)
/* 8031E69C 0031B27C  7C 03 F0 2E */	lwzx r0, r3, r30
/* 8031E6A0 0031B280  28 00 00 00 */	cmplwi r0, 0
/* 8031E6A4 0031B284  40 82 FF 60 */	bne .L_8031E604
/* 8031E6A8 0031B288  88 7F 00 00 */	lbz r3, 0(r31)
/* 8031E6AC 0031B28C  88 9F 00 01 */	lbz r4, 1(r31)
/* 8031E6B0 0031B290  88 BF 00 03 */	lbz r5, 3(r31)
/* 8031E6B4 0031B294  4B FF FA 71 */	bl un_8031E124
/* 8031E6B8 0031B298  BB 41 00 10 */	lmw r26, 0x10(r1)
/* 8031E6BC 0031B29C  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8031E6C0 0031B2A0  38 21 00 28 */	addi r1, r1, 0x28
/* 8031E6C4 0031B2A4  7C 08 03 A6 */	mtlr r0
/* 8031E6C8 0031B2A8  4E 80 00 20 */	blr


.section .data
    .balign 8
.global un_804000D0
un_804000D0:
    .4byte NULL
    .4byte 0xC0400000
    .4byte NULL
    .asciz "Vi0502.dat"
    .balign 4
    .asciz "visual0502Scene"
    .balign 4
    .asciz "IrAls.dat"
    .balign 4
    .4byte NULL


.section .sdata
    .balign 8
.global un_804D5AE8
un_804D5AE8:
    .asciz "jobj.h"
    .balign 4
.global un_804D5AF0
un_804D5AF0:
    .asciz "jobj"
    .balign 4


.section .sdata2
    .balign 8
.global un_804DE090
un_804DE090:
    .4byte 0x3F333333
.global un_804DE094
un_804DE094:
    .4byte 0x3F800000
.global un_804DE098
un_804DE098:
    .4byte 0xBF800000
.global un_804DE09C
un_804DE09C:
    .4byte 0x42F00000
.global un_804DE0A0
un_804DE0A0:
    .4byte 0x00000000
.global un_804DE0A4
un_804DE0A4:
    .4byte 0x41F00000
