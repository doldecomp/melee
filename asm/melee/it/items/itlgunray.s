.include "macros.inc"
.file "itlgunray.c"

# 0x80298168..0x802988E4 | size: 0x77C
.text
.balign 4

# .text:0x0 | 0x80298168 | size: 0x144
.fn it_80298168, global
/* 80298168 00294D48  7C 08 02 A6 */	mflr r0
/* 8029816C 00294D4C  90 01 00 04 */	stw r0, 0x4(r1)
/* 80298170 00294D50  38 00 00 23 */	li r0, 0x23
/* 80298174 00294D54  94 21 FF 80 */	stwu r1, -0x80(r1)
/* 80298178 00294D58  DB E1 00 78 */	stfd f31, 0x78(r1)
/* 8029817C 00294D5C  FF E0 08 90 */	fmr f31, f1
/* 80298180 00294D60  38 C1 00 2C */	addi r6, r1, 0x2c
/* 80298184 00294D64  93 E1 00 74 */	stw r31, 0x74(r1)
/* 80298188 00294D68  93 C1 00 70 */	stw r30, 0x70(r1)
/* 8029818C 00294D6C  93 A1 00 6C */	stw r29, 0x6c(r1)
/* 80298190 00294D70  93 81 00 68 */	stw r28, 0x68(r1)
/* 80298194 00294D74  7C 7C 1B 78 */	mr r28, r3
/* 80298198 00294D78  90 01 00 20 */	stw r0, 0x20(r1)
/* 8029819C 00294D7C  C0 02 D1 F0 */	lfs f0, it_804DCBD0@sda21(r0)
/* 802981A0 00294D80  80 A4 00 00 */	lwz r5, 0x0(r4)
/* 802981A4 00294D84  80 04 00 04 */	lwz r0, 0x4(r4)
/* 802981A8 00294D88  90 A1 00 38 */	stw r5, 0x38(r1)
/* 802981AC 00294D8C  90 01 00 3C */	stw r0, 0x3c(r1)
/* 802981B0 00294D90  80 04 00 08 */	lwz r0, 0x8(r4)
/* 802981B4 00294D94  7C C4 33 78 */	mr r4, r6
/* 802981B8 00294D98  90 01 00 40 */	stw r0, 0x40(r1)
/* 802981BC 00294D9C  D0 01 00 40 */	stfs f0, 0x40(r1)
/* 802981C0 00294DA0  4B FD 39 A9 */	bl it_8026BB68
/* 802981C4 00294DA4  D3 E1 00 50 */	stfs f31, 0x50(r1)
/* 802981C8 00294DA8  38 A0 00 00 */	li r5, 0x0
/* 802981CC 00294DAC  C0 02 D1 F0 */	lfs f0, it_804DCBD0@sda21(r0)
/* 802981D0 00294DB0  38 80 00 01 */	li r4, 0x1
/* 802981D4 00294DB4  B0 A1 00 54 */	sth r5, 0x54(r1)
/* 802981D8 00294DB8  38 61 00 18 */	addi r3, r1, 0x18
/* 802981DC 00294DBC  D0 01 00 4C */	stfs f0, 0x4c(r1)
/* 802981E0 00294DC0  D0 01 00 48 */	stfs f0, 0x48(r1)
/* 802981E4 00294DC4  D0 01 00 44 */	stfs f0, 0x44(r1)
/* 802981E8 00294DC8  93 81 00 18 */	stw r28, 0x18(r1)
/* 802981EC 00294DCC  80 01 00 18 */	lwz r0, 0x18(r1)
/* 802981F0 00294DD0  90 01 00 1C */	stw r0, 0x1c(r1)
/* 802981F4 00294DD4  88 01 00 5C */	lbz r0, 0x5c(r1)
/* 802981F8 00294DD8  50 80 3E 30 */	rlwimi r0, r4, 7, 24, 24
/* 802981FC 00294DDC  98 01 00 5C */	stb r0, 0x5c(r1)
/* 80298200 00294DE0  90 A1 00 58 */	stw r5, 0x58(r1)
/* 80298204 00294DE4  4B FD 09 15 */	bl Item_80268B18
/* 80298208 00294DE8  7C 7F 1B 79 */	mr. r31, r3
/* 8029820C 00294DEC  41 82 00 7C */	beq .L_80298288
/* 80298210 00294DF0  83 DF 00 2C */	lwz r30, 0x2c(r31)
/* 80298214 00294DF4  38 7F 00 00 */	addi r3, r31, 0x0
/* 80298218 00294DF8  38 9C 00 00 */	addi r4, r28, 0x0
/* 8029821C 00294DFC  80 BE 00 C4 */	lwz r5, 0xc4(r30)
/* 80298220 00294E00  83 A5 00 04 */	lwz r29, 0x4(r5)
/* 80298224 00294E04  48 00 00 89 */	bl it_802982AC
/* 80298228 00294E08  C0 42 D1 F0 */	lfs f2, it_804DCBD0@sda21(r0)
/* 8029822C 00294E0C  D0 5E 0D D4 */	stfs f2, 0xdd4(r30)
/* 80298230 00294E10  C0 22 D1 F4 */	lfs f1, it_804DCBD4@sda21(r0)
/* 80298234 00294E14  C0 1E 00 2C */	lfs f0, 0x2c(r30)
/* 80298238 00294E18  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8029823C 00294E1C  40 82 00 08 */	bne .L_80298244
/* 80298240 00294E20  48 00 00 08 */	b .L_80298248
.L_80298244:
/* 80298244 00294E24  C0 42 D1 F8 */	lfs f2, it_804DCBD8@sda21(r0)
.L_80298248:
/* 80298248 00294E28  D0 5E 0D D8 */	stfs f2, 0xdd8(r30)
/* 8029824C 00294E2C  38 7F 00 00 */	addi r3, r31, 0x0
/* 80298250 00294E30  38 9C 00 00 */	addi r4, r28, 0x0
/* 80298254 00294E34  C0 1D 00 00 */	lfs f0, 0x0(r29)
/* 80298258 00294E38  D0 1E 0D DC */	stfs f0, 0xddc(r30)
/* 8029825C 00294E3C  80 A1 00 2C */	lwz r5, 0x2c(r1)
/* 80298260 00294E40  80 01 00 30 */	lwz r0, 0x30(r1)
/* 80298264 00294E44  90 BE 0D E0 */	stw r5, 0xde0(r30)
/* 80298268 00294E48  90 1E 0D E4 */	stw r0, 0xde4(r30)
/* 8029826C 00294E4C  80 01 00 34 */	lwz r0, 0x34(r1)
/* 80298270 00294E50  90 1E 0D E8 */	stw r0, 0xde8(r30)
/* 80298274 00294E54  C0 3D 00 00 */	lfs f1, 0x0(r29)
/* 80298278 00294E58  C0 1E 00 2C */	lfs f0, 0x2c(r30)
/* 8029827C 00294E5C  EC 01 00 32 */	fmuls f0, f1, f0
/* 80298280 00294E60  D0 1E 00 40 */	stfs f0, 0x40(r30)
/* 80298284 00294E64  4B F8 DB 55 */	bl db_80225DD8
.L_80298288:
/* 80298288 00294E68  80 01 00 84 */	lwz r0, 0x84(r1)
/* 8029828C 00294E6C  CB E1 00 78 */	lfd f31, 0x78(r1)
/* 80298290 00294E70  83 E1 00 74 */	lwz r31, 0x74(r1)
/* 80298294 00294E74  83 C1 00 70 */	lwz r30, 0x70(r1)
/* 80298298 00294E78  83 A1 00 6C */	lwz r29, 0x6c(r1)
/* 8029829C 00294E7C  83 81 00 68 */	lwz r28, 0x68(r1)
/* 802982A0 00294E80  38 21 00 80 */	addi r1, r1, 0x80
/* 802982A4 00294E84  7C 08 03 A6 */	mtlr r0
/* 802982A8 00294E88  4E 80 00 20 */	blr
.endfn it_80298168

# .text:0x144 | 0x802982AC | size: 0x54
.fn it_802982AC, global
/* 802982AC 00294E8C  7C 08 02 A6 */	mflr r0
/* 802982B0 00294E90  90 01 00 04 */	stw r0, 0x4(r1)
/* 802982B4 00294E94  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 802982B8 00294E98  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 802982BC 00294E9C  7C 7F 1B 78 */	mr r31, r3
/* 802982C0 00294EA0  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 802982C4 00294EA4  80 84 00 C4 */	lwz r4, 0xc4(r4)
/* 802982C8 00294EA8  80 84 00 04 */	lwz r4, 0x4(r4)
/* 802982CC 00294EAC  C0 24 00 04 */	lfs f1, 0x4(r4)
/* 802982D0 00294EB0  4B FD CE 89 */	bl it_80275158
/* 802982D4 00294EB4  7F E3 FB 78 */	mr r3, r31
/* 802982D8 00294EB8  4B FD 30 D1 */	bl it_8026B3A8
/* 802982DC 00294EBC  38 7F 00 00 */	addi r3, r31, 0x0
/* 802982E0 00294EC0  38 80 00 00 */	li r4, 0x0
/* 802982E4 00294EC4  38 A0 00 02 */	li r5, 0x2
/* 802982E8 00294EC8  4B FD 0B 75 */	bl Item_80268E5C
/* 802982EC 00294ECC  80 01 00 24 */	lwz r0, 0x24(r1)
/* 802982F0 00294ED0  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 802982F4 00294ED4  38 21 00 20 */	addi r1, r1, 0x20
/* 802982F8 00294ED8  7C 08 03 A6 */	mtlr r0
/* 802982FC 00294EDC  4E 80 00 20 */	blr
.endfn it_802982AC

# .text:0x198 | 0x80298300 | size: 0x2D8
.fn it_80298300, global
/* 80298300 00294EE0  7C 08 02 A6 */	mflr r0
/* 80298304 00294EE4  90 01 00 04 */	stw r0, 0x4(r1)
/* 80298308 00294EE8  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8029830C 00294EEC  DB E1 00 28 */	stfd f31, 0x28(r1)
/* 80298310 00294EF0  93 E1 00 24 */	stw r31, 0x24(r1)
/* 80298314 00294EF4  93 C1 00 20 */	stw r30, 0x20(r1)
/* 80298318 00294EF8  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 8029831C 00294EFC  93 81 00 18 */	stw r28, 0x18(r1)
/* 80298320 00294F00  7C 7C 1B 78 */	mr r28, r3
/* 80298324 00294F04  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80298328 00294F08  83 A3 00 28 */	lwz r29, 0x28(r3)
/* 8029832C 00294F0C  80 7F 00 C4 */	lwz r3, 0xc4(r31)
/* 80298330 00294F10  C0 3F 0D D8 */	lfs f1, 0xdd8(r31)
/* 80298334 00294F14  83 C3 00 04 */	lwz r30, 0x4(r3)
/* 80298338 00294F18  48 08 DF 09 */	bl cosf
/* 8029833C 00294F1C  C0 1F 0D DC */	lfs f0, 0xddc(r31)
/* 80298340 00294F20  EC 00 00 72 */	fmuls f0, f0, f1
/* 80298344 00294F24  D0 1F 00 40 */	stfs f0, 0x40(r31)
/* 80298348 00294F28  C0 3F 0D D8 */	lfs f1, 0xdd8(r31)
/* 8029834C 00294F2C  48 08 E0 89 */	bl sinf
/* 80298350 00294F30  C0 1F 0D DC */	lfs f0, 0xddc(r31)
/* 80298354 00294F34  EC 00 00 72 */	fmuls f0, f0, f1
/* 80298358 00294F38  D0 1F 00 44 */	stfs f0, 0x44(r31)
/* 8029835C 00294F3C  C0 22 D1 F0 */	lfs f1, it_804DCBD0@sda21(r0)
/* 80298360 00294F40  D0 3F 00 48 */	stfs f1, 0x48(r31)
/* 80298364 00294F44  C0 1F 00 40 */	lfs f0, 0x40(r31)
/* 80298368 00294F48  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 8029836C 00294F4C  40 81 00 0C */	ble .L_80298378
/* 80298370 00294F50  C0 02 D1 F4 */	lfs f0, it_804DCBD4@sda21(r0)
/* 80298374 00294F54  48 00 00 08 */	b .L_8029837C
.L_80298378:
/* 80298378 00294F58  C0 02 D1 FC */	lfs f0, it_804DCBDC@sda21(r0)
.L_8029837C:
/* 8029837C 00294F5C  D0 1F 00 2C */	stfs f0, 0x2c(r31)
/* 80298380 00294F60  28 1D 00 00 */	cmplwi r29, 0x0
/* 80298384 00294F64  C8 22 D2 00 */	lfd f1, it_804DCBE0@sda21(r0)
/* 80298388 00294F68  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 8029838C 00294F6C  FF E1 00 32 */	fmul f31, f1, f0
/* 80298390 00294F70  FF E0 F8 18 */	frsp f31, f31
/* 80298394 00294F74  40 82 00 14 */	bne .L_802983A8
/* 80298398 00294F78  38 6D 9C 60 */	li r3, it_804D5300@sda21
/* 8029839C 00294F7C  38 80 02 94 */	li r4, 0x294
/* 802983A0 00294F80  38 AD 9C 68 */	li r5, it_804D5308@sda21
/* 802983A4 00294F84  48 0E FE 7D */	bl __assert
.L_802983A8:
/* 802983A8 00294F88  80 1D 00 14 */	lwz r0, 0x14(r29)
/* 802983AC 00294F8C  54 00 03 9D */	rlwinm. r0, r0, 0, 14, 14
/* 802983B0 00294F90  41 82 00 18 */	beq .L_802983C8
/* 802983B4 00294F94  3C 60 80 3F */	lis r3, it_803F6508@ha
/* 802983B8 00294F98  38 A3 65 08 */	addi r5, r3, it_803F6508@l
/* 802983BC 00294F9C  38 6D 9C 60 */	li r3, it_804D5300@sda21
/* 802983C0 00294FA0  38 80 02 95 */	li r4, 0x295
/* 802983C4 00294FA4  48 0E FE 5D */	bl __assert
.L_802983C8:
/* 802983C8 00294FA8  D3 FD 00 20 */	stfs f31, 0x20(r29)
/* 802983CC 00294FAC  80 1D 00 14 */	lwz r0, 0x14(r29)
/* 802983D0 00294FB0  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 802983D4 00294FB4  40 82 00 4C */	bne .L_80298420
/* 802983D8 00294FB8  28 1D 00 00 */	cmplwi r29, 0x0
/* 802983DC 00294FBC  41 82 00 44 */	beq .L_80298420
/* 802983E0 00294FC0  40 82 00 14 */	bne .L_802983F4
/* 802983E4 00294FC4  38 6D 9C 60 */	li r3, it_804D5300@sda21
/* 802983E8 00294FC8  38 80 02 34 */	li r4, 0x234
/* 802983EC 00294FCC  38 AD 9C 68 */	li r5, it_804D5308@sda21
/* 802983F0 00294FD0  48 0E FE 31 */	bl __assert
.L_802983F4:
/* 802983F4 00294FD4  80 9D 00 14 */	lwz r4, 0x14(r29)
/* 802983F8 00294FD8  38 60 00 00 */	li r3, 0x0
/* 802983FC 00294FDC  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 80298400 00294FE0  40 82 00 10 */	bne .L_80298410
/* 80298404 00294FE4  54 80 06 73 */	rlwinm. r0, r4, 0, 25, 25
/* 80298408 00294FE8  41 82 00 08 */	beq .L_80298410
/* 8029840C 00294FEC  38 60 00 01 */	li r3, 0x1
.L_80298410:
/* 80298410 00294FF0  2C 03 00 00 */	cmpwi r3, 0x0
/* 80298414 00294FF4  40 82 00 0C */	bne .L_80298420
/* 80298418 00294FF8  7F A3 EB 78 */	mr r3, r29
/* 8029841C 00294FFC  48 0D AE CD */	bl HSD_JObjSetMtxDirtySub
.L_80298420:
/* 80298420 00295000  C0 22 D1 F4 */	lfs f1, it_804DCBD4@sda21(r0)
/* 80298424 00295004  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 80298428 00295008  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8029842C 0029500C  40 82 00 10 */	bne .L_8029843C
/* 80298430 00295010  C0 1F 00 40 */	lfs f0, 0x40(r31)
/* 80298434 00295014  FC 40 00 50 */	fneg f2, f0
/* 80298438 00295018  48 00 00 08 */	b .L_80298440
.L_8029843C:
/* 8029843C 0029501C  C0 5F 00 40 */	lfs f2, 0x40(r31)
.L_80298440:
/* 80298440 00295020  C0 3F 00 44 */	lfs f1, 0x44(r31)
/* 80298444 00295024  4B D8 A7 ED */	bl atan2f
/* 80298448 00295028  C8 02 D2 08 */	lfd f0, it_804DCBE8@sda21(r0)
/* 8029844C 0029502C  28 1D 00 00 */	cmplwi r29, 0x0
/* 80298450 00295030  FF E0 08 2A */	fadd f31, f0, f1
/* 80298454 00295034  FF E0 F8 18 */	frsp f31, f31
/* 80298458 00295038  40 82 00 14 */	bne .L_8029846C
/* 8029845C 0029503C  38 6D 9C 60 */	li r3, it_804D5300@sda21
/* 80298460 00295040  38 80 02 7F */	li r4, 0x27f
/* 80298464 00295044  38 AD 9C 68 */	li r5, it_804D5308@sda21
/* 80298468 00295048  48 0E FD B9 */	bl __assert
.L_8029846C:
/* 8029846C 0029504C  80 1D 00 14 */	lwz r0, 0x14(r29)
/* 80298470 00295050  54 00 03 9D */	rlwinm. r0, r0, 0, 14, 14
/* 80298474 00295054  41 82 00 18 */	beq .L_8029848C
/* 80298478 00295058  3C 60 80 3F */	lis r3, it_803F6508@ha
/* 8029847C 0029505C  38 A3 65 08 */	addi r5, r3, it_803F6508@l
/* 80298480 00295060  38 6D 9C 60 */	li r3, it_804D5300@sda21
/* 80298484 00295064  38 80 02 80 */	li r4, 0x280
/* 80298488 00295068  48 0E FD 99 */	bl __assert
.L_8029848C:
/* 8029848C 0029506C  D3 FD 00 1C */	stfs f31, 0x1c(r29)
/* 80298490 00295070  80 1D 00 14 */	lwz r0, 0x14(r29)
/* 80298494 00295074  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 80298498 00295078  40 82 00 4C */	bne .L_802984E4
/* 8029849C 0029507C  28 1D 00 00 */	cmplwi r29, 0x0
/* 802984A0 00295080  41 82 00 44 */	beq .L_802984E4
/* 802984A4 00295084  40 82 00 14 */	bne .L_802984B8
/* 802984A8 00295088  38 6D 9C 60 */	li r3, it_804D5300@sda21
/* 802984AC 0029508C  38 80 02 34 */	li r4, 0x234
/* 802984B0 00295090  38 AD 9C 68 */	li r5, it_804D5308@sda21
/* 802984B4 00295094  48 0E FD 6D */	bl __assert
.L_802984B8:
/* 802984B8 00295098  80 9D 00 14 */	lwz r4, 0x14(r29)
/* 802984BC 0029509C  38 60 00 00 */	li r3, 0x0
/* 802984C0 002950A0  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 802984C4 002950A4  40 82 00 10 */	bne .L_802984D4
/* 802984C8 002950A8  54 80 06 73 */	rlwinm. r0, r4, 0, 25, 25
/* 802984CC 002950AC  41 82 00 08 */	beq .L_802984D4
/* 802984D0 002950B0  38 60 00 01 */	li r3, 0x1
.L_802984D4:
/* 802984D4 002950B4  2C 03 00 00 */	cmpwi r3, 0x0
/* 802984D8 002950B8  40 82 00 0C */	bne .L_802984E4
/* 802984DC 002950BC  7F A3 EB 78 */	mr r3, r29
/* 802984E0 002950C0  48 0D AE 09 */	bl HSD_JObjSetMtxDirtySub
.L_802984E4:
/* 802984E4 002950C4  C0 5F 0D DC */	lfs f2, 0xddc(r31)
/* 802984E8 002950C8  C0 02 D1 F0 */	lfs f0, it_804DCBD0@sda21(r0)
/* 802984EC 002950CC  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 802984F0 002950D0  40 80 00 08 */	bge .L_802984F8
/* 802984F4 002950D4  FC 40 10 50 */	fneg f2, f2
.L_802984F8:
/* 802984F8 002950D8  C0 02 D2 10 */	lfs f0, it_804DCBF0@sda21(r0)
/* 802984FC 002950DC  C0 3F 0D D4 */	lfs f1, 0xdd4(r31)
/* 80298500 002950E0  EC 02 00 24 */	fdivs f0, f2, f0
/* 80298504 002950E4  EC 01 00 2A */	fadds f0, f1, f0
/* 80298508 002950E8  D0 1F 0D D4 */	stfs f0, 0xdd4(r31)
/* 8029850C 002950EC  C0 1F 0D D4 */	lfs f0, 0xdd4(r31)
/* 80298510 002950F0  C0 3E 00 08 */	lfs f1, 0x8(r30)
/* 80298514 002950F4  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 80298518 002950F8  40 81 00 08 */	ble .L_80298520
/* 8029851C 002950FC  D0 3F 0D D4 */	stfs f1, 0xdd4(r31)
.L_80298520:
/* 80298520 00295100  C0 3F 0D D4 */	lfs f1, 0xdd4(r31)
/* 80298524 00295104  C0 02 D2 14 */	lfs f0, it_804DCBF4@sda21(r0)
/* 80298528 00295108  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8029852C 0029510C  40 80 00 0C */	bge .L_80298538
/* 80298530 00295110  C0 02 D2 18 */	lfs f0, it_804DCBF8@sda21(r0)
/* 80298534 00295114  D0 1F 0D D4 */	stfs f0, 0xdd4(r31)
.L_80298538:
/* 80298538 00295118  28 1D 00 00 */	cmplwi r29, 0x0
/* 8029853C 0029511C  C3 FF 0D D4 */	lfs f31, 0xdd4(r31)
/* 80298540 00295120  40 82 00 14 */	bne .L_80298554
/* 80298544 00295124  38 6D 9C 60 */	li r3, it_804D5300@sda21
/* 80298548 00295128  38 80 03 26 */	li r4, 0x326
/* 8029854C 0029512C  38 AD 9C 68 */	li r5, it_804D5308@sda21
/* 80298550 00295130  48 0E FC D1 */	bl __assert
.L_80298554:
/* 80298554 00295134  D3 FD 00 34 */	stfs f31, 0x34(r29)
/* 80298558 00295138  80 1D 00 14 */	lwz r0, 0x14(r29)
/* 8029855C 0029513C  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 80298560 00295140  40 82 00 4C */	bne .L_802985AC
/* 80298564 00295144  28 1D 00 00 */	cmplwi r29, 0x0
/* 80298568 00295148  41 82 00 44 */	beq .L_802985AC
/* 8029856C 0029514C  40 82 00 14 */	bne .L_80298580
/* 80298570 00295150  38 6D 9C 60 */	li r3, it_804D5300@sda21
/* 80298574 00295154  38 80 02 34 */	li r4, 0x234
/* 80298578 00295158  38 AD 9C 68 */	li r5, it_804D5308@sda21
/* 8029857C 0029515C  48 0E FC A5 */	bl __assert
.L_80298580:
/* 80298580 00295160  80 9D 00 14 */	lwz r4, 0x14(r29)
/* 80298584 00295164  38 60 00 00 */	li r3, 0x0
/* 80298588 00295168  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 8029858C 0029516C  40 82 00 10 */	bne .L_8029859C
/* 80298590 00295170  54 80 06 73 */	rlwinm. r0, r4, 0, 25, 25
/* 80298594 00295174  41 82 00 08 */	beq .L_8029859C
/* 80298598 00295178  38 60 00 01 */	li r3, 0x1
.L_8029859C:
/* 8029859C 0029517C  2C 03 00 00 */	cmpwi r3, 0x0
/* 802985A0 00295180  40 82 00 0C */	bne .L_802985AC
/* 802985A4 00295184  7F A3 EB 78 */	mr r3, r29
/* 802985A8 00295188  48 0D AD 41 */	bl HSD_JObjSetMtxDirtySub
.L_802985AC:
/* 802985AC 0029518C  7F 83 E3 78 */	mr r3, r28
/* 802985B0 00295190  4B FD AB 81 */	bl it_80273130
/* 802985B4 00295194  80 01 00 34 */	lwz r0, 0x34(r1)
/* 802985B8 00295198  CB E1 00 28 */	lfd f31, 0x28(r1)
/* 802985BC 0029519C  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 802985C0 002951A0  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 802985C4 002951A4  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 802985C8 002951A8  83 81 00 18 */	lwz r28, 0x18(r1)
/* 802985CC 002951AC  38 21 00 30 */	addi r1, r1, 0x30
/* 802985D0 002951B0  7C 08 03 A6 */	mtlr r0
/* 802985D4 002951B4  4E 80 00 20 */	blr
.endfn it_80298300

# .text:0x470 | 0x802985D8 | size: 0x20
.fn it_802985D8, global
/* 802985D8 002951B8  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 802985DC 002951BC  80 64 00 4C */	lwz r3, 0x4c(r4)
/* 802985E0 002951C0  80 04 00 50 */	lwz r0, 0x50(r4)
/* 802985E4 002951C4  90 64 0D E0 */	stw r3, 0xde0(r4)
/* 802985E8 002951C8  90 04 0D E4 */	stw r0, 0xde4(r4)
/* 802985EC 002951CC  80 04 00 54 */	lwz r0, 0x54(r4)
/* 802985F0 002951D0  90 04 0D E8 */	stw r0, 0xde8(r4)
/* 802985F4 002951D4  4E 80 00 20 */	blr
.endfn it_802985D8

# .text:0x490 | 0x802985F8 | size: 0x3C
.fn it_802985F8, global
/* 802985F8 002951D8  7C 08 02 A6 */	mflr r0
/* 802985FC 002951DC  90 01 00 04 */	stw r0, 0x4(r1)
/* 80298600 002951E0  94 21 FF F8 */	stwu r1, -0x8(r1)
/* 80298604 002951E4  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 80298608 002951E8  38 84 03 78 */	addi r4, r4, 0x378
/* 8029860C 002951EC  48 00 3E C9 */	bl it_8029C4D4
/* 80298610 002951F0  2C 03 00 00 */	cmpwi r3, 0x0
/* 80298614 002951F4  41 82 00 0C */	beq .L_80298620
/* 80298618 002951F8  38 60 00 01 */	li r3, 0x1
/* 8029861C 002951FC  48 00 00 08 */	b .L_80298624
.L_80298620:
/* 80298620 00295200  38 60 00 00 */	li r3, 0x0
.L_80298624:
/* 80298624 00295204  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80298628 00295208  38 21 00 08 */	addi r1, r1, 0x8
/* 8029862C 0029520C  7C 08 03 A6 */	mtlr r0
/* 80298630 00295210  4E 80 00 20 */	blr
.endfn it_802985F8

# .text:0x4CC | 0x80298634 | size: 0x8
.fn it_80298634, global
/* 80298634 00295214  38 60 00 01 */	li r3, 0x1
/* 80298638 00295218  4E 80 00 20 */	blr
.endfn it_80298634

# .text:0x4D4 | 0x8029863C | size: 0x8
.fn it_8029863C, global
/* 8029863C 0029521C  38 60 00 01 */	li r3, 0x1
/* 80298640 00295220  4E 80 00 20 */	blr
.endfn it_8029863C

# .text:0x4DC | 0x80298644 | size: 0x8
.fn it_80298644, global
/* 80298644 00295224  38 60 00 01 */	li r3, 0x1
/* 80298648 00295228  4E 80 00 20 */	blr
.endfn it_80298644

# .text:0x4E4 | 0x8029864C | size: 0x8
.fn it_8029864C, global
/* 8029864C 0029522C  38 60 00 01 */	li r3, 0x1
/* 80298650 00295230  4E 80 00 20 */	blr
.endfn it_8029864C

# .text:0x4EC | 0x80298654 | size: 0x1D4
.fn it_80298654, global
/* 80298654 00295234  7C 08 02 A6 */	mflr r0
/* 80298658 00295238  90 01 00 04 */	stw r0, 0x4(r1)
/* 8029865C 0029523C  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 80298660 00295240  DB E1 00 20 */	stfd f31, 0x20(r1)
/* 80298664 00295244  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80298668 00295248  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8029866C 0029524C  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80298670 00295250  83 C3 00 28 */	lwz r30, 0x28(r3)
/* 80298674 00295254  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 80298678 00295258  28 1E 00 00 */	cmplwi r30, 0x0
/* 8029867C 0029525C  FC 00 00 50 */	fneg f0, f0
/* 80298680 00295260  D0 1F 00 2C */	stfs f0, 0x2c(r31)
/* 80298684 00295264  C8 22 D2 00 */	lfd f1, it_804DCBE0@sda21(r0)
/* 80298688 00295268  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 8029868C 0029526C  FF E1 00 32 */	fmul f31, f1, f0
/* 80298690 00295270  FF E0 F8 18 */	frsp f31, f31
/* 80298694 00295274  40 82 00 14 */	bne .L_802986A8
/* 80298698 00295278  38 6D 9C 60 */	li r3, it_804D5300@sda21
/* 8029869C 0029527C  38 80 02 94 */	li r4, 0x294
/* 802986A0 00295280  38 AD 9C 68 */	li r5, it_804D5308@sda21
/* 802986A4 00295284  48 0E FB 7D */	bl __assert
.L_802986A8:
/* 802986A8 00295288  80 1E 00 14 */	lwz r0, 0x14(r30)
/* 802986AC 0029528C  54 00 03 9D */	rlwinm. r0, r0, 0, 14, 14
/* 802986B0 00295290  41 82 00 18 */	beq .L_802986C8
/* 802986B4 00295294  3C 60 80 3F */	lis r3, it_803F6508@ha
/* 802986B8 00295298  38 A3 65 08 */	addi r5, r3, it_803F6508@l
/* 802986BC 0029529C  38 6D 9C 60 */	li r3, it_804D5300@sda21
/* 802986C0 002952A0  38 80 02 95 */	li r4, 0x295
/* 802986C4 002952A4  48 0E FB 5D */	bl __assert
.L_802986C8:
/* 802986C8 002952A8  D3 FE 00 20 */	stfs f31, 0x20(r30)
/* 802986CC 002952AC  80 1E 00 14 */	lwz r0, 0x14(r30)
/* 802986D0 002952B0  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 802986D4 002952B4  40 82 00 4C */	bne .L_80298720
/* 802986D8 002952B8  28 1E 00 00 */	cmplwi r30, 0x0
/* 802986DC 002952BC  41 82 00 44 */	beq .L_80298720
/* 802986E0 002952C0  40 82 00 14 */	bne .L_802986F4
/* 802986E4 002952C4  38 6D 9C 60 */	li r3, it_804D5300@sda21
/* 802986E8 002952C8  38 80 02 34 */	li r4, 0x234
/* 802986EC 002952CC  38 AD 9C 68 */	li r5, it_804D5308@sda21
/* 802986F0 002952D0  48 0E FB 31 */	bl __assert
.L_802986F4:
/* 802986F4 002952D4  80 9E 00 14 */	lwz r4, 0x14(r30)
/* 802986F8 002952D8  38 60 00 00 */	li r3, 0x0
/* 802986FC 002952DC  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 80298700 002952E0  40 82 00 10 */	bne .L_80298710
/* 80298704 002952E4  54 80 06 73 */	rlwinm. r0, r4, 0, 25, 25
/* 80298708 002952E8  41 82 00 08 */	beq .L_80298710
/* 8029870C 002952EC  38 60 00 01 */	li r3, 0x1
.L_80298710:
/* 80298710 002952F0  2C 03 00 00 */	cmpwi r3, 0x0
/* 80298714 002952F4  40 82 00 0C */	bne .L_80298720
/* 80298718 002952F8  7F C3 F3 78 */	mr r3, r30
/* 8029871C 002952FC  48 0D AB CD */	bl HSD_JObjSetMtxDirtySub
.L_80298720:
/* 80298720 00295300  C0 3F 0D DC */	lfs f1, 0xddc(r31)
/* 80298724 00295304  28 1E 00 00 */	cmplwi r30, 0x0
/* 80298728 00295308  C0 1F 0C 70 */	lfs f0, 0xc70(r31)
/* 8029872C 0029530C  EC 01 00 32 */	fmuls f0, f1, f0
/* 80298730 00295310  D0 1F 0D DC */	stfs f0, 0xddc(r31)
/* 80298734 00295314  C3 E2 D2 18 */	lfs f31, it_804DCBF8@sda21(r0)
/* 80298738 00295318  D3 FF 0D D4 */	stfs f31, 0xdd4(r31)
/* 8029873C 0029531C  40 82 00 14 */	bne .L_80298750
/* 80298740 00295320  38 6D 9C 60 */	li r3, it_804D5300@sda21
/* 80298744 00295324  38 80 03 26 */	li r4, 0x326
/* 80298748 00295328  38 AD 9C 68 */	li r5, it_804D5308@sda21
/* 8029874C 0029532C  48 0E FA D5 */	bl __assert
.L_80298750:
/* 80298750 00295330  D3 FE 00 34 */	stfs f31, 0x34(r30)
/* 80298754 00295334  80 1E 00 14 */	lwz r0, 0x14(r30)
/* 80298758 00295338  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 8029875C 0029533C  40 82 00 4C */	bne .L_802987A8
/* 80298760 00295340  28 1E 00 00 */	cmplwi r30, 0x0
/* 80298764 00295344  41 82 00 44 */	beq .L_802987A8
/* 80298768 00295348  40 82 00 14 */	bne .L_8029877C
/* 8029876C 0029534C  38 6D 9C 60 */	li r3, it_804D5300@sda21
/* 80298770 00295350  38 80 02 34 */	li r4, 0x234
/* 80298774 00295354  38 AD 9C 68 */	li r5, it_804D5308@sda21
/* 80298778 00295358  48 0E FA A9 */	bl __assert
.L_8029877C:
/* 8029877C 0029535C  80 9E 00 14 */	lwz r4, 0x14(r30)
/* 80298780 00295360  38 60 00 00 */	li r3, 0x0
/* 80298784 00295364  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 80298788 00295368  40 82 00 10 */	bne .L_80298798
/* 8029878C 0029536C  54 80 06 73 */	rlwinm. r0, r4, 0, 25, 25
/* 80298790 00295370  41 82 00 08 */	beq .L_80298798
/* 80298794 00295374  38 60 00 01 */	li r3, 0x1
.L_80298798:
/* 80298798 00295378  2C 03 00 00 */	cmpwi r3, 0x0
/* 8029879C 0029537C  40 82 00 0C */	bne .L_802987A8
/* 802987A0 00295380  7F C3 F3 78 */	mr r3, r30
/* 802987A4 00295384  48 0D AB 45 */	bl HSD_JObjSetMtxDirtySub
.L_802987A8:
/* 802987A8 00295388  C0 3F 0D D8 */	lfs f1, 0xdd8(r31)
/* 802987AC 0029538C  C8 02 D2 08 */	lfd f0, it_804DCBE8@sda21(r0)
/* 802987B0 00295390  FC 01 00 2A */	fadd f0, f1, f0
/* 802987B4 00295394  FC 00 00 18 */	frsp f0, f0
/* 802987B8 00295398  D0 1F 0D D8 */	stfs f0, 0xdd8(r31)
/* 802987BC 0029539C  C8 42 D2 20 */	lfd f2, it_804DCC00@sda21(r0)
/* 802987C0 002953A0  C0 02 D1 F0 */	lfs f0, it_804DCBD0@sda21(r0)
/* 802987C4 002953A4  48 00 00 14 */	b .L_802987D8
.L_802987C8:
/* 802987C8 002953A8  C0 3F 0D D8 */	lfs f1, 0xdd8(r31)
/* 802987CC 002953AC  FC 21 10 2A */	fadd f1, f1, f2
/* 802987D0 002953B0  FC 20 08 18 */	frsp f1, f1
/* 802987D4 002953B4  D0 3F 0D D8 */	stfs f1, 0xdd8(r31)
.L_802987D8:
/* 802987D8 002953B8  C0 3F 0D D8 */	lfs f1, 0xdd8(r31)
/* 802987DC 002953BC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 802987E0 002953C0  41 80 FF E8 */	blt .L_802987C8
/* 802987E4 002953C4  C8 22 D2 20 */	lfd f1, it_804DCC00@sda21(r0)
/* 802987E8 002953C8  48 00 00 14 */	b .L_802987FC
.L_802987EC:
/* 802987EC 002953CC  C0 1F 0D D8 */	lfs f0, 0xdd8(r31)
/* 802987F0 002953D0  FC 00 08 28 */	fsub f0, f0, f1
/* 802987F4 002953D4  FC 00 00 18 */	frsp f0, f0
/* 802987F8 002953D8  D0 1F 0D D8 */	stfs f0, 0xdd8(r31)
.L_802987FC:
/* 802987FC 002953DC  C0 1F 0D D8 */	lfs f0, 0xdd8(r31)
/* 80298800 002953E0  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 80298804 002953E4  41 81 FF E8 */	bgt .L_802987EC
/* 80298808 002953E8  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8029880C 002953EC  38 60 00 00 */	li r3, 0x0
/* 80298810 002953F0  CB E1 00 20 */	lfd f31, 0x20(r1)
/* 80298814 002953F4  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80298818 002953F8  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8029881C 002953FC  38 21 00 28 */	addi r1, r1, 0x28
/* 80298820 00295400  7C 08 03 A6 */	mtlr r0
/* 80298824 00295404  4E 80 00 20 */	blr
.endfn it_80298654

# .text:0x6C0 | 0x80298828 | size: 0x9C
.fn it_80298828, global
/* 80298828 00295408  7C 08 02 A6 */	mflr r0
/* 8029882C 0029540C  90 01 00 04 */	stw r0, 0x4(r1)
/* 80298830 00295410  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80298834 00295414  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80298838 00295418  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8029883C 0029541C  38 7F 00 40 */	addi r3, r31, 0x40
/* 80298840 00295420  38 9F 0C 58 */	addi r4, r31, 0xc58
/* 80298844 00295424  4B D7 54 29 */	bl lbVector_Mirror
/* 80298848 00295428  C0 02 D2 18 */	lfs f0, it_804DCBF8@sda21(r0)
/* 8029884C 0029542C  D0 1F 0D D4 */	stfs f0, 0xdd4(r31)
/* 80298850 00295430  C0 3F 00 44 */	lfs f1, 0x44(r31)
/* 80298854 00295434  C0 5F 00 40 */	lfs f2, 0x40(r31)
/* 80298858 00295438  4B D8 A3 D9 */	bl atan2f
/* 8029885C 0029543C  D0 3F 0D D8 */	stfs f1, 0xdd8(r31)
/* 80298860 00295440  C8 42 D2 20 */	lfd f2, it_804DCC00@sda21(r0)
/* 80298864 00295444  C0 02 D1 F0 */	lfs f0, it_804DCBD0@sda21(r0)
/* 80298868 00295448  48 00 00 14 */	b .L_8029887C
.L_8029886C:
/* 8029886C 0029544C  C0 3F 0D D8 */	lfs f1, 0xdd8(r31)
/* 80298870 00295450  FC 21 10 2A */	fadd f1, f1, f2
/* 80298874 00295454  FC 20 08 18 */	frsp f1, f1
/* 80298878 00295458  D0 3F 0D D8 */	stfs f1, 0xdd8(r31)
.L_8029887C:
/* 8029887C 0029545C  C0 3F 0D D8 */	lfs f1, 0xdd8(r31)
/* 80298880 00295460  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80298884 00295464  41 80 FF E8 */	blt .L_8029886C
/* 80298888 00295468  C8 22 D2 20 */	lfd f1, it_804DCC00@sda21(r0)
/* 8029888C 0029546C  48 00 00 14 */	b .L_802988A0
.L_80298890:
/* 80298890 00295470  C0 1F 0D D8 */	lfs f0, 0xdd8(r31)
/* 80298894 00295474  FC 00 08 28 */	fsub f0, f0, f1
/* 80298898 00295478  FC 00 00 18 */	frsp f0, f0
/* 8029889C 0029547C  D0 1F 0D D8 */	stfs f0, 0xdd8(r31)
.L_802988A0:
/* 802988A0 00295480  C0 1F 0D D8 */	lfs f0, 0xdd8(r31)
/* 802988A4 00295484  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 802988A8 00295488  41 81 FF E8 */	bgt .L_80298890
/* 802988AC 0029548C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 802988B0 00295490  38 60 00 00 */	li r3, 0x0
/* 802988B4 00295494  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 802988B8 00295498  38 21 00 20 */	addi r1, r1, 0x20
/* 802988BC 0029549C  7C 08 03 A6 */	mtlr r0
/* 802988C0 002954A0  4E 80 00 20 */	blr
.endfn it_80298828

# .text:0x75C | 0x802988C4 | size: 0x20
.fn it_802988C4, global
/* 802988C4 002954A4  7C 08 02 A6 */	mflr r0
/* 802988C8 002954A8  90 01 00 04 */	stw r0, 0x4(r1)
/* 802988CC 002954AC  94 21 FF F8 */	stwu r1, -0x8(r1)
/* 802988D0 002954B0  4B FD 2F C5 */	bl it_8026B894
/* 802988D4 002954B4  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802988D8 002954B8  38 21 00 08 */	addi r1, r1, 0x8
/* 802988DC 002954BC  7C 08 03 A6 */	mtlr r0
/* 802988E0 002954C0  4E 80 00 20 */	blr
.endfn it_802988C4

# 0x803F64F8..0x803F6530 | size: 0x38
.data
.balign 8

# .data:0x0 | 0x803F64F8 | size: 0x10
.obj it_803F64F8, global
	.4byte 0x00000000
	.4byte it_80298300
	.4byte it_802985D8
	.4byte it_802985F8
.endobj it_803F64F8

# .data:0x10 | 0x803F6508 | size: 0x28
.obj it_803F6508, global
	.4byte 0x21286A6F
	.4byte 0x626A2D3E
	.4byte 0x666C6167
	.4byte 0x73202620
	.4byte 0x4A4F424A
	.4byte 0x5F555345
	.4byte 0x5F515541
	.4byte 0x5445524E
	.4byte 0x494F4E29
	.4byte 0x00000000
.endobj it_803F6508

# 0x804D5300..0x804D5310 | size: 0x10
.section .sdata, "wa"
.balign 8

# .sdata:0x0 | 0x804D5300 | size: 0x8
.obj it_804D5300, global
	.4byte 0x6A6F626A
	.4byte 0x2E680000
.endobj it_804D5300

# .sdata:0x8 | 0x804D5308 | size: 0x8
.obj it_804D5308, global
	.4byte 0x6A6F626A
	.4byte 0x00000000
.endobj it_804D5308

# 0x804DCBD0..0x804DCC08 | size: 0x38
.section .sdata2, "a"
.balign 8

# .sdata2:0x0 | 0x804DCBD0 | size: 0x4
.obj it_804DCBD0, global
	.float 0
.endobj it_804DCBD0

# .sdata2:0x4 | 0x804DCBD4 | size: 0x4
.obj it_804DCBD4, global
	.float 1
.endobj it_804DCBD4

# .sdata2:0x8 | 0x804DCBD8 | size: 0x4
.obj it_804DCBD8, global
	.float 3.1415927
.endobj it_804DCBD8

# .sdata2:0xC | 0x804DCBDC | size: 0x4
.obj it_804DCBDC, global
	.float -1
.endobj it_804DCBDC

# .sdata2:0x10 | 0x804DCBE0 | size: 0x8
.obj it_804DCBE0, global
	.double 1.5707963267948966
.endobj it_804DCBE0

# .sdata2:0x18 | 0x804DCBE8 | size: 0x8
.obj it_804DCBE8, global
	.double 3.141592653589793
.endobj it_804DCBE8

# .sdata2:0x20 | 0x804DCBF0 | size: 0x4
.obj it_804DCBF0, global
	.float 7
.endobj it_804DCBF0

# .sdata2:0x24 | 0x804DCBF4 | size: 0x4
.obj it_804DCBF4, global
	.float 0.00001
.endobj it_804DCBF4

# .sdata2:0x28 | 0x804DCBF8 | size: 0x4
.obj it_804DCBF8, global
	.float 0.001
.endobj it_804DCBF8

# .sdata2:0x2C | 0x804DCBFC | size: 0x4
.obj gap_11_804DCBFC_sdata2, global
.hidden gap_11_804DCBFC_sdata2
	.4byte 0x00000000
.endobj gap_11_804DCBFC_sdata2

# .sdata2:0x30 | 0x804DCC00 | size: 0x8
.obj it_804DCC00, global
	.double 6.283185307179586
.endobj it_804DCC00
