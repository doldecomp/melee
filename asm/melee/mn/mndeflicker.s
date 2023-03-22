.include "macros.inc"

.section .text  # 0x8024A168 - 0x8024A78C

.global func_8024A168
func_8024A168:
/* 8024A168 00246D48  7C 08 02 A6 */	mflr r0
/* 8024A16C 00246D4C  90 01 00 04 */	stw r0, 4(r1)
/* 8024A170 00246D50  94 21 FF A8 */	stwu r1, -0x58(r1)
/* 8024A174 00246D54  93 E1 00 54 */	stw r31, 0x54(r1)
/* 8024A178 00246D58  93 C1 00 50 */	stw r30, 0x50(r1)
/* 8024A17C 00246D5C  93 A1 00 4C */	stw r29, 0x4c(r1)
/* 8024A180 00246D60  A0 6D B5 28 */	lhz r3, lbl_804D6BC8@sda21(r13)
/* 8024A184 00246D64  80 8D B5 98 */	lwz r4, lbl_804D6C38@sda21(r13)
/* 8024A188 00246D68  28 03 00 00 */	cmplwi r3, 0
/* 8024A18C 00246D6C  83 E4 00 2C */	lwz r31, 0x2c(r4)
/* 8024A190 00246D70  41 82 00 20 */	beq lbl_8024A1B0
/* 8024A194 00246D74  38 03 FF FF */	addi r0, r3, -1
/* 8024A198 00246D78  B0 0D B5 28 */	sth r0, lbl_804D6BC8@sda21(r13)
/* 8024A19C 00246D7C  38 00 00 00 */	li r0, 0
/* 8024A1A0 00246D80  38 6D B5 28 */	addi r3, r13, lbl_804D6BC8@sda21
/* 8024A1A4 00246D84  B0 03 00 02 */	sth r0, 2(r3)
/* 8024A1A8 00246D88  90 03 00 04 */	stw r0, 4(r3)
/* 8024A1AC 00246D8C  48 00 01 20 */	b lbl_8024A2CC
lbl_8024A1B0:
/* 8024A1B0 00246D90  38 60 00 04 */	li r3, 4
/* 8024A1B4 00246D94  4B FD F4 71 */	bl mn_80229624
/* 8024A1B8 00246D98  3B A0 00 00 */	li r29, 0
/* 8024A1BC 00246D9C  38 00 00 20 */	li r0, 0x20
/* 8024A1C0 00246DA0  3C 80 80 4A */	lis r4, lbl_804A04F0@ha
/* 8024A1C4 00246DA4  3B C4 04 F0 */	addi r30, r4, lbl_804A04F0@l
/* 8024A1C8 00246DA8  7C 60 00 38 */	and r0, r3, r0
/* 8024A1CC 00246DAC  90 7E 00 0C */	stw r3, 0xc(r30)
/* 8024A1D0 00246DB0  7F A5 E8 38 */	and r5, r29, r29
/* 8024A1D4 00246DB4  7C 04 EA 78 */	xor r4, r0, r29
/* 8024A1D8 00246DB8  93 BE 00 08 */	stw r29, 8(r30)
/* 8024A1DC 00246DBC  7C A0 EA 78 */	xor r0, r5, r29
/* 8024A1E0 00246DC0  7C 80 03 79 */	or. r0, r4, r0
/* 8024A1E4 00246DC4  41 82 00 38 */	beq lbl_8024A21C
/* 8024A1E8 00246DC8  38 60 00 00 */	li r3, 0
/* 8024A1EC 00246DCC  4B DD 9E 45 */	bl func_80024030
/* 8024A1F0 00246DD0  80 6D B5 98 */	lwz r3, lbl_804D6C38@sda21(r13)
/* 8024A1F4 00246DD4  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8024A1F8 00246DD8  88 63 00 00 */	lbz r3, 0(r3)
/* 8024A1FC 00246DDC  4B F1 52 F9 */	bl gmMainLib_8015F4F4
/* 8024A200 00246DE0  4B DD 2C 01 */	bl lb_8001CE00
/* 8024A204 00246DE4  9B BE 00 11 */	stb r29, 0x11(r30)
/* 8024A208 00246DE8  38 60 00 04 */	li r3, 4
/* 8024A20C 00246DEC  38 80 00 02 */	li r4, 2
/* 8024A210 00246DF0  38 A0 00 03 */	li r5, 3
/* 8024A214 00246DF4  4B FD F6 81 */	bl mn_80229894
/* 8024A218 00246DF8  48 00 00 B4 */	b lbl_8024A2CC
lbl_8024A21C:
/* 8024A21C 00246DFC  88 0D B5 9C */	lbz r0, lbl_804D6C3C@sda21(r13)
/* 8024A220 00246E00  28 00 00 00 */	cmplwi r0, 0
/* 8024A224 00246E04  41 82 00 A8 */	beq lbl_8024A2CC
/* 8024A228 00246E08  38 00 02 00 */	li r0, 0x200
/* 8024A22C 00246E0C  7C 60 00 38 */	and r0, r3, r0
/* 8024A230 00246E10  7C 03 EA 78 */	xor r3, r0, r29
/* 8024A234 00246E14  7C A0 EA 78 */	xor r0, r5, r29
/* 8024A238 00246E18  7C 60 03 79 */	or. r0, r3, r0
/* 8024A23C 00246E1C  41 82 00 90 */	beq lbl_8024A2CC
/* 8024A240 00246E20  38 60 00 02 */	li r3, 2
/* 8024A244 00246E24  4B DD 9D ED */	bl func_80024030
/* 8024A248 00246E28  88 1F 00 00 */	lbz r0, 0(r31)
/* 8024A24C 00246E2C  38 81 00 30 */	addi r4, r1, 0x30
/* 8024A250 00246E30  4C C6 31 82 */	crclr 6
/* 8024A254 00246E34  38 A0 00 05 */	li r5, 5
/* 8024A258 00246E38  7C 00 00 D0 */	neg r0, r0
/* 8024A25C 00246E3C  7C 00 00 34 */	cntlzw r0, r0
/* 8024A260 00246E40  54 00 DE 3E */	rlwinm r0, r0, 0x1b, 0x18, 0x1f
/* 8024A264 00246E44  98 1F 00 00 */	stb r0, 0(r31)
/* 8024A268 00246E48  38 C0 FF FF */	li r6, -1
/* 8024A26C 00246E4C  80 6D B5 98 */	lwz r3, lbl_804D6C38@sda21(r13)
/* 8024A270 00246E50  8B BF 00 00 */	lbz r29, 0(r31)
/* 8024A274 00246E54  80 63 00 28 */	lwz r3, 0x28(r3)
/* 8024A278 00246E58  4B DC 7B AD */	bl lb_80011E24
/* 8024A27C 00246E5C  93 A1 00 44 */	stw r29, 0x44(r1)
/* 8024A280 00246E60  3C 00 43 30 */	lis r0, 0x4330
/* 8024A284 00246E64  C8 22 C6 B8 */	lfd f1, lbl_804DC098@sda21(r2)
/* 8024A288 00246E68  90 01 00 40 */	stw r0, 0x40(r1)
/* 8024A28C 00246E6C  80 61 00 30 */	lwz r3, 0x30(r1)
/* 8024A290 00246E70  C8 01 00 40 */	lfd f0, 0x40(r1)
/* 8024A294 00246E74  EC 20 08 28 */	fsubs f1, f0, f1
/* 8024A298 00246E78  48 12 56 25 */	bl HSD_JObjReqAnimAll
/* 8024A29C 00246E7C  80 61 00 30 */	lwz r3, 0x30(r1)
/* 8024A2A0 00246E80  38 80 00 FF */	li r4, 0xff
/* 8024A2A4 00246E84  38 A0 00 20 */	li r5, 0x20
/* 8024A2A8 00246E88  4B FE 51 31 */	bl mn_8022F3D8
/* 8024A2AC 00246E8C  80 61 00 30 */	lwz r3, 0x30(r1)
/* 8024A2B0 00246E90  48 12 66 79 */	bl HSD_JObjAnimAll
/* 8024A2B4 00246E94  7F A3 EB 78 */	mr r3, r29
/* 8024A2B8 00246E98  4B F1 52 D1 */	bl gmMainLib_8015F588
/* 8024A2BC 00246E9C  80 6D B5 98 */	lwz r3, lbl_804D6C38@sda21(r13)
/* 8024A2C0 00246EA0  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8024A2C4 00246EA4  88 63 00 00 */	lbz r3, 0(r3)
/* 8024A2C8 00246EA8  4B F1 52 2D */	bl gmMainLib_8015F4F4
lbl_8024A2CC:
/* 8024A2CC 00246EAC  80 01 00 5C */	lwz r0, 0x5c(r1)
/* 8024A2D0 00246EB0  83 E1 00 54 */	lwz r31, 0x54(r1)
/* 8024A2D4 00246EB4  83 C1 00 50 */	lwz r30, 0x50(r1)
/* 8024A2D8 00246EB8  83 A1 00 4C */	lwz r29, 0x4c(r1)
/* 8024A2DC 00246EBC  38 21 00 58 */	addi r1, r1, 0x58
/* 8024A2E0 00246EC0  7C 08 03 A6 */	mtlr r0
/* 8024A2E4 00246EC4  4E 80 00 20 */	blr
lbl_8024A2E8:
/* 8024A2E8 00246EC8  7C 08 02 A6 */	mflr r0
/* 8024A2EC 00246ECC  3C 80 80 3F */	lis r4, lbl_803EEFE4@ha
/* 8024A2F0 00246ED0  90 01 00 04 */	stw r0, 4(r1)
/* 8024A2F4 00246ED4  38 A0 04 00 */	li r5, 0x400
/* 8024A2F8 00246ED8  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8024A2FC 00246EDC  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8024A300 00246EE0  3B E4 EF E4 */	addi r31, r4, lbl_803EEFE4@l
/* 8024A304 00246EE4  38 9F 00 00 */	addi r4, r31, 0
/* 8024A308 00246EE8  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8024A30C 00246EEC  7C 7E 1B 78 */	mr r30, r3
/* 8024A310 00246EF0  80 63 00 28 */	lwz r3, 0x28(r3)
/* 8024A314 00246EF4  4B FE 49 05 */	bl mn_8022EC18
/* 8024A318 00246EF8  C0 1F 00 04 */	lfs f0, 4(r31)
/* 8024A31C 00246EFC  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8024A320 00246F00  40 82 00 0C */	bne lbl_8024A32C
/* 8024A324 00246F04  7F C3 F3 78 */	mr r3, r30
/* 8024A328 00246F08  48 14 5F 01 */	bl func_80390228
lbl_8024A32C:
/* 8024A32C 00246F0C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8024A330 00246F10  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8024A334 00246F14  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8024A338 00246F18  38 21 00 20 */	addi r1, r1, 0x20
/* 8024A33C 00246F1C  7C 08 03 A6 */	mtlr r0
/* 8024A340 00246F20  4E 80 00 20 */	blr
lbl_8024A344:
/* 8024A344 00246F24  7C 08 02 A6 */	mflr r0
/* 8024A348 00246F28  3C 80 80 4A */	lis r4, lbl_804A04F0@ha
/* 8024A34C 00246F2C  90 01 00 04 */	stw r0, 4(r1)
/* 8024A350 00246F30  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8024A354 00246F34  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8024A358 00246F38  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8024A35C 00246F3C  7C 7E 1B 78 */	mr r30, r3
/* 8024A360 00246F40  88 04 04 F0 */	lbz r0, lbl_804A04F0@l(r4)
/* 8024A364 00246F44  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8024A368 00246F48  28 00 00 15 */	cmplwi r0, 0x15
/* 8024A36C 00246F4C  80 63 00 28 */	lwz r3, 0x28(r3)
/* 8024A370 00246F50  41 82 00 3C */	beq lbl_8024A3AC
/* 8024A374 00246F54  80 6D C1 98 */	lwz r3, lbl_804D7838@sda21(r13)
/* 8024A378 00246F58  48 14 5A AD */	bl func_8038FE24
/* 8024A37C 00246F5C  3C 60 80 25 */	lis r3, lbl_8024A2E8@ha
/* 8024A380 00246F60  38 83 A2 E8 */	addi r4, r3, lbl_8024A2E8@l
/* 8024A384 00246F64  38 7E 00 00 */	addi r3, r30, 0
/* 8024A388 00246F68  38 A0 00 00 */	li r5, 0
/* 8024A38C 00246F6C  48 14 59 C9 */	bl func_8038FD54
/* 8024A390 00246F70  80 8D C1 9C */	lwz r4, lbl_804D783C@sda21(r13)
/* 8024A394 00246F74  88 03 00 0D */	lbz r0, 0xd(r3)
/* 8024A398 00246F78  50 80 26 B6 */	rlwimi r0, r4, 4, 0x1a, 0x1b
/* 8024A39C 00246F7C  98 03 00 0D */	stb r0, 0xd(r3)
/* 8024A3A0 00246F80  80 7F 00 04 */	lwz r3, 4(r31)
/* 8024A3A4 00246F84  48 15 B9 21 */	bl func_803A5CC4
/* 8024A3A8 00246F88  48 00 00 28 */	b lbl_8024A3D0
lbl_8024A3AC:
/* 8024A3AC 00246F8C  4C C6 31 82 */	crclr 6
/* 8024A3B0 00246F90  38 81 00 14 */	addi r4, r1, 0x14
/* 8024A3B4 00246F94  38 A0 00 06 */	li r5, 6
/* 8024A3B8 00246F98  38 C0 FF FF */	li r6, -1
/* 8024A3BC 00246F9C  4B DC 7A 69 */	bl lb_80011E24
/* 8024A3C0 00246FA0  3C 80 80 3F */	lis r4, lbl_803EEFF0@ha
/* 8024A3C4 00246FA4  80 61 00 14 */	lwz r3, 0x14(r1)
/* 8024A3C8 00246FA8  38 84 EF F0 */	addi r4, r4, lbl_803EEFF0@l
/* 8024A3CC 00246FAC  4B FE 49 A1 */	bl mn_8022ED6C
lbl_8024A3D0:
/* 8024A3D0 00246FB0  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8024A3D4 00246FB4  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8024A3D8 00246FB8  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8024A3DC 00246FBC  38 21 00 20 */	addi r1, r1, 0x20
/* 8024A3E0 00246FC0  7C 08 03 A6 */	mtlr r0
/* 8024A3E4 00246FC4  4E 80 00 20 */	blr
lbl_8024A3E8:
/* 8024A3E8 00246FC8  7C 08 02 A6 */	mflr r0
/* 8024A3EC 00246FCC  3C 80 80 4A */	lis r4, lbl_804A04F0@ha
/* 8024A3F0 00246FD0  90 01 00 04 */	stw r0, 4(r1)
/* 8024A3F4 00246FD4  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8024A3F8 00246FD8  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8024A3FC 00246FDC  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8024A400 00246FE0  7C 7E 1B 78 */	mr r30, r3
/* 8024A404 00246FE4  88 04 04 F0 */	lbz r0, lbl_804A04F0@l(r4)
/* 8024A408 00246FE8  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8024A40C 00246FEC  28 00 00 15 */	cmplwi r0, 0x15
/* 8024A410 00246FF0  80 63 00 28 */	lwz r3, 0x28(r3)
/* 8024A414 00246FF4  41 82 00 3C */	beq lbl_8024A450
/* 8024A418 00246FF8  80 6D C1 98 */	lwz r3, lbl_804D7838@sda21(r13)
/* 8024A41C 00246FFC  48 14 5A 09 */	bl func_8038FE24
/* 8024A420 00247000  3C 60 80 25 */	lis r3, lbl_8024A2E8@ha
/* 8024A424 00247004  38 83 A2 E8 */	addi r4, r3, lbl_8024A2E8@l
/* 8024A428 00247008  38 7E 00 00 */	addi r3, r30, 0
/* 8024A42C 0024700C  38 A0 00 00 */	li r5, 0
/* 8024A430 00247010  48 14 59 25 */	bl func_8038FD54
/* 8024A434 00247014  80 8D C1 9C */	lwz r4, lbl_804D783C@sda21(r13)
/* 8024A438 00247018  88 03 00 0D */	lbz r0, 0xd(r3)
/* 8024A43C 0024701C  50 80 26 B6 */	rlwimi r0, r4, 4, 0x1a, 0x1b
/* 8024A440 00247020  98 03 00 0D */	stb r0, 0xd(r3)
/* 8024A444 00247024  80 7F 00 04 */	lwz r3, 4(r31)
/* 8024A448 00247028  48 15 B8 7D */	bl func_803A5CC4
/* 8024A44C 0024702C  48 00 00 58 */	b lbl_8024A4A4
lbl_8024A450:
/* 8024A450 00247030  3C 80 80 3F */	lis r4, lbl_803EEFD8@ha
/* 8024A454 00247034  3B E4 EF D8 */	addi r31, r4, lbl_803EEFD8@l
/* 8024A458 00247038  38 9F 00 00 */	addi r4, r31, 0
/* 8024A45C 0024703C  38 A0 04 00 */	li r5, 0x400
/* 8024A460 00247040  4B FE 47 B9 */	bl mn_8022EC18
/* 8024A464 00247044  C0 1F 00 04 */	lfs f0, 4(r31)
/* 8024A468 00247048  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8024A46C 0024704C  40 82 00 38 */	bne lbl_8024A4A4
/* 8024A470 00247050  80 6D C1 98 */	lwz r3, lbl_804D7838@sda21(r13)
/* 8024A474 00247054  48 14 59 B1 */	bl func_8038FE24
/* 8024A478 00247058  3C 60 80 25 */	lis r3, lbl_8024A344@ha
/* 8024A47C 0024705C  38 83 A3 44 */	addi r4, r3, lbl_8024A344@l
/* 8024A480 00247060  38 7E 00 00 */	addi r3, r30, 0
/* 8024A484 00247064  38 A0 00 00 */	li r5, 0
/* 8024A488 00247068  48 14 58 CD */	bl func_8038FD54
/* 8024A48C 0024706C  80 AD C1 9C */	lwz r5, lbl_804D783C@sda21(r13)
/* 8024A490 00247070  38 00 00 01 */	li r0, 1
/* 8024A494 00247074  88 83 00 0D */	lbz r4, 0xd(r3)
/* 8024A498 00247078  50 A4 26 B6 */	rlwimi r4, r5, 4, 0x1a, 0x1b
/* 8024A49C 0024707C  98 83 00 0D */	stb r4, 0xd(r3)
/* 8024A4A0 00247080  98 0D B5 9C */	stb r0, lbl_804D6C3C@sda21(r13)
lbl_8024A4A4:
/* 8024A4A4 00247084  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8024A4A8 00247088  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8024A4AC 0024708C  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8024A4B0 00247090  38 21 00 20 */	addi r1, r1, 0x20
/* 8024A4B4 00247094  7C 08 03 A6 */	mtlr r0
/* 8024A4B8 00247098  4E 80 00 20 */	blr

.global func_8024A4BC
func_8024A4BC:
/* 8024A4BC 0024709C  7C 08 02 A6 */	mflr r0
/* 8024A4C0 002470A0  3C 80 80 3F */	lis r4, lbl_803EEFD8@ha
/* 8024A4C4 002470A4  90 01 00 04 */	stw r0, 4(r1)
/* 8024A4C8 002470A8  3C 60 80 4A */	lis r3, lbl_804A08B8@ha
/* 8024A4CC 002470AC  38 A0 00 80 */	li r5, 0x80
/* 8024A4D0 002470B0  94 21 FF B8 */	stwu r1, -0x48(r1)
/* 8024A4D4 002470B4  93 E1 00 44 */	stw r31, 0x44(r1)
/* 8024A4D8 002470B8  93 C1 00 40 */	stw r30, 0x40(r1)
/* 8024A4DC 002470BC  3B C3 08 B8 */	addi r30, r3, lbl_804A08B8@l
/* 8024A4E0 002470C0  38 60 00 06 */	li r3, 6
/* 8024A4E4 002470C4  93 A1 00 3C */	stw r29, 0x3c(r1)
/* 8024A4E8 002470C8  3B A4 EF D8 */	addi r29, r4, lbl_803EEFD8@l
/* 8024A4EC 002470CC  38 80 00 07 */	li r4, 7
/* 8024A4F0 002470D0  93 81 00 38 */	stw r28, 0x38(r1)
/* 8024A4F4 002470D4  48 14 5C FD */	bl GObj_Create
/* 8024A4F8 002470D8  7C 7C 1B 78 */	mr r28, r3
/* 8024A4FC 002470DC  93 8D B5 98 */	stw r28, lbl_804D6C38@sda21(r13)
/* 8024A500 002470E0  80 7E 00 00 */	lwz r3, 0(r30)
/* 8024A504 002470E4  48 12 69 41 */	bl HSD_JObjLoadJoint
/* 8024A508 002470E8  3B E3 00 00 */	addi r31, r3, 0
/* 8024A50C 002470EC  88 8D C1 A9 */	lbz r4, lbl_804D7849@sda21(r13)
/* 8024A510 002470F0  38 7C 00 00 */	addi r3, r28, 0
/* 8024A514 002470F4  38 BF 00 00 */	addi r5, r31, 0
/* 8024A518 002470F8  48 14 65 59 */	bl func_80390A70
/* 8024A51C 002470FC  3C 60 80 39 */	lis r3, func_80391070@ha
/* 8024A520 00247100  38 83 10 70 */	addi r4, r3, func_80391070@l
/* 8024A524 00247104  38 7C 00 00 */	addi r3, r28, 0
/* 8024A528 00247108  38 A0 00 04 */	li r5, 4
/* 8024A52C 0024710C  38 C0 00 80 */	li r6, 0x80
/* 8024A530 00247110  48 14 61 6D */	bl GObj_SetupGXLink
/* 8024A534 00247114  80 9E 00 04 */	lwz r4, 4(r30)
/* 8024A538 00247118  7F E3 FB 78 */	mr r3, r31
/* 8024A53C 0024711C  80 BE 00 08 */	lwz r5, 8(r30)
/* 8024A540 00247120  80 DE 00 0C */	lwz r6, 0xc(r30)
/* 8024A544 00247124  48 12 56 19 */	bl HSD_JObjAddAnimAll
/* 8024A548 00247128  7F E3 FB 78 */	mr r3, r31
/* 8024A54C 0024712C  C0 22 C6 D8 */	lfs f1, lbl_804DC0B8@sda21(r2)
/* 8024A550 00247130  48 12 53 6D */	bl HSD_JObjReqAnimAll
/* 8024A554 00247134  7F E3 FB 78 */	mr r3, r31
/* 8024A558 00247138  48 12 63 D1 */	bl HSD_JObjAnimAll
/* 8024A55C 0024713C  38 60 00 08 */	li r3, 8
/* 8024A560 00247140  48 13 4C 85 */	bl HSD_MemAlloc
/* 8024A564 00247144  7C 7E 1B 79 */	or. r30, r3, r3
/* 8024A568 00247148  40 82 00 20 */	bne lbl_8024A588
/* 8024A56C 0024714C  38 7D 00 24 */	addi r3, r29, 0x24
/* 8024A570 00247150  4C C6 31 82 */	crclr 6
/* 8024A574 00247154  48 0F B1 35 */	bl OSReport
/* 8024A578 00247158  38 7D 00 3C */	addi r3, r29, 0x3c
/* 8024A57C 0024715C  38 BD 00 4C */	addi r5, r29, 0x4c
/* 8024A580 00247160  38 80 01 58 */	li r4, 0x158
/* 8024A584 00247164  48 13 DC 9D */	bl __assert
lbl_8024A588:
/* 8024A588 00247168  4B F1 4F 61 */	bl gmMainLib_8015F4E8
/* 8024A58C 0024716C  98 7E 00 00 */	stb r3, 0(r30)
/* 8024A590 00247170  38 00 00 00 */	li r0, 0
/* 8024A594 00247174  3C 60 80 38 */	lis r3, HSD_Free@ha
/* 8024A598 00247178  90 1E 00 04 */	stw r0, 4(r30)
/* 8024A59C 0024717C  38 A3 F1 B0 */	addi r5, r3, HSD_Free@l
/* 8024A5A0 00247180  38 7C 00 00 */	addi r3, r28, 0
/* 8024A5A4 00247184  38 DE 00 00 */	addi r6, r30, 0
/* 8024A5A8 00247188  38 80 00 00 */	li r4, 0
/* 8024A5AC 0024718C  48 14 65 BD */	bl GObj_InitUserData
/* 8024A5B0 00247190  3C 60 80 25 */	lis r3, lbl_8024A3E8@ha
/* 8024A5B4 00247194  38 83 A3 E8 */	addi r4, r3, lbl_8024A3E8@l
/* 8024A5B8 00247198  38 7C 00 00 */	addi r3, r28, 0
/* 8024A5BC 0024719C  38 A0 00 00 */	li r5, 0
/* 8024A5C0 002471A0  48 14 57 95 */	bl func_8038FD54
/* 8024A5C4 002471A4  80 AD C1 9C */	lwz r5, lbl_804D783C@sda21(r13)
/* 8024A5C8 002471A8  38 81 00 1C */	addi r4, r1, 0x1c
/* 8024A5CC 002471AC  88 03 00 0D */	lbz r0, 0xd(r3)
/* 8024A5D0 002471B0  4C C6 31 82 */	crclr 6
/* 8024A5D4 002471B4  50 A0 26 B6 */	rlwimi r0, r5, 4, 0x1a, 0x1b
/* 8024A5D8 002471B8  98 03 00 0D */	stb r0, 0xd(r3)
/* 8024A5DC 002471BC  38 A0 00 05 */	li r5, 5
/* 8024A5E0 002471C0  38 C0 FF FF */	li r6, -1
/* 8024A5E4 002471C4  80 7C 00 28 */	lwz r3, 0x28(r28)
/* 8024A5E8 002471C8  8B BE 00 00 */	lbz r29, 0(r30)
/* 8024A5EC 002471CC  4B DC 78 39 */	bl lb_80011E24
/* 8024A5F0 002471D0  93 A1 00 34 */	stw r29, 0x34(r1)
/* 8024A5F4 002471D4  3C 00 43 30 */	lis r0, 0x4330
/* 8024A5F8 002471D8  C8 22 C6 B8 */	lfd f1, lbl_804DC098@sda21(r2)
/* 8024A5FC 002471DC  90 01 00 30 */	stw r0, 0x30(r1)
/* 8024A600 002471E0  80 61 00 1C */	lwz r3, 0x1c(r1)
/* 8024A604 002471E4  C8 01 00 30 */	lfd f0, 0x30(r1)
/* 8024A608 002471E8  EC 20 08 28 */	fsubs f1, f0, f1
/* 8024A60C 002471EC  48 12 52 B1 */	bl HSD_JObjReqAnimAll
/* 8024A610 002471F0  80 61 00 1C */	lwz r3, 0x1c(r1)
/* 8024A614 002471F4  38 80 00 FF */	li r4, 0xff
/* 8024A618 002471F8  38 A0 00 20 */	li r5, 0x20
/* 8024A61C 002471FC  4B FE 4D BD */	bl mn_8022F3D8
/* 8024A620 00247200  80 61 00 1C */	lwz r3, 0x1c(r1)
/* 8024A624 00247204  48 12 63 05 */	bl HSD_JObjAnimAll
/* 8024A628 00247208  7F A3 EB 78 */	mr r3, r29
/* 8024A62C 0024720C  4B F1 4F 5D */	bl gmMainLib_8015F588
/* 8024A630 00247210  7F E3 FB 78 */	mr r3, r31
/* 8024A634 00247214  C0 22 C6 D8 */	lfs f1, lbl_804DC0B8@sda21(r2)
/* 8024A638 00247218  48 12 52 85 */	bl HSD_JObjReqAnimAll
/* 8024A63C 0024721C  38 7F 00 00 */	addi r3, r31, 0
/* 8024A640 00247220  38 80 00 FF */	li r4, 0xff
/* 8024A644 00247224  38 A0 04 00 */	li r5, 0x400
/* 8024A648 00247228  4B FE 4D 91 */	bl mn_8022F3D8
/* 8024A64C 0024722C  7F E3 FB 78 */	mr r3, r31
/* 8024A650 00247230  48 12 62 D9 */	bl HSD_JObjAnimAll
/* 8024A654 00247234  80 6D B5 98 */	lwz r3, lbl_804D6C38@sda21(r13)
/* 8024A658 00247238  83 A3 00 2C */	lwz r29, 0x2c(r3)
/* 8024A65C 0024723C  80 7D 00 04 */	lwz r3, 4(r29)
/* 8024A660 00247240  28 03 00 00 */	cmplwi r3, 0
/* 8024A664 00247244  41 82 00 08 */	beq lbl_8024A66C
/* 8024A668 00247248  48 15 B6 5D */	bl func_803A5CC4
lbl_8024A66C:
/* 8024A66C 0024724C  C0 22 C6 C0 */	lfs f1, lbl_804DC0A0@sda21(r2)
/* 8024A670 00247250  38 60 00 00 */	li r3, 0
/* 8024A674 00247254  C0 42 C6 C4 */	lfs f2, lbl_804DC0A4@sda21(r2)
/* 8024A678 00247258  38 80 00 01 */	li r4, 1
/* 8024A67C 0024725C  C0 62 C6 C8 */	lfs f3, lbl_804DC0A8@sda21(r2)
/* 8024A680 00247260  C0 82 C6 CC */	lfs f4, lbl_804DC0AC@sda21(r2)
/* 8024A684 00247264  C0 A2 C6 D0 */	lfs f5, lbl_804DC0B0@sda21(r2)
/* 8024A688 00247268  48 15 B4 45 */	bl func_803A5ACC
/* 8024A68C 0024726C  90 7D 00 04 */	stw r3, 4(r29)
/* 8024A690 00247270  38 80 00 BD */	li r4, 0xbd
/* 8024A694 00247274  C0 02 C6 D4 */	lfs f0, lbl_804DC0B4@sda21(r2)
/* 8024A698 00247278  D0 03 00 24 */	stfs f0, 0x24(r3)
/* 8024A69C 0024727C  D0 03 00 28 */	stfs f0, 0x28(r3)
/* 8024A6A0 00247280  48 15 BC C9 */	bl func_803A6368
/* 8024A6A4 00247284  80 01 00 4C */	lwz r0, 0x4c(r1)
/* 8024A6A8 00247288  83 E1 00 44 */	lwz r31, 0x44(r1)
/* 8024A6AC 0024728C  83 C1 00 40 */	lwz r30, 0x40(r1)
/* 8024A6B0 00247290  83 A1 00 3C */	lwz r29, 0x3c(r1)
/* 8024A6B4 00247294  83 81 00 38 */	lwz r28, 0x38(r1)
/* 8024A6B8 00247298  38 21 00 48 */	addi r1, r1, 0x48
/* 8024A6BC 0024729C  7C 08 03 A6 */	mtlr r0
/* 8024A6C0 002472A0  4E 80 00 20 */	blr

.global func_8024A6C4
func_8024A6C4:
/* 8024A6C4 002472A4  7C 08 02 A6 */	mflr r0
/* 8024A6C8 002472A8  3C 80 80 4A */	lis r4, lbl_804A04F0@ha
/* 8024A6CC 002472AC  90 01 00 04 */	stw r0, 4(r1)
/* 8024A6D0 002472B0  38 A4 04 F0 */	addi r5, r4, lbl_804A04F0@l
/* 8024A6D4 002472B4  3C 80 80 3F */	lis r4, lbl_803EEFD8@ha
/* 8024A6D8 002472B8  4C C6 31 82 */	crclr 6
/* 8024A6DC 002472BC  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8024A6E0 002472C0  39 24 EF D8 */	addi r9, r4, lbl_803EEFD8@l
/* 8024A6E4 002472C4  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8024A6E8 002472C8  38 00 00 05 */	li r0, 5
/* 8024A6EC 002472CC  3C 80 80 4A */	lis r4, lbl_804A08B8@ha
/* 8024A6F0 002472D0  B0 0D B5 28 */	sth r0, lbl_804D6BC8@sda21(r13)
/* 8024A6F4 002472D4  38 84 08 B8 */	addi r4, r4, lbl_804A08B8@l
/* 8024A6F8 002472D8  38 E0 00 00 */	li r7, 0
/* 8024A6FC 002472DC  88 05 00 00 */	lbz r0, 0(r5)
/* 8024A700 002472E0  7C 7F 1B 78 */	mr r31, r3
/* 8024A704 002472E4  38 C4 00 04 */	addi r6, r4, 4
/* 8024A708 002472E8  98 05 00 01 */	stb r0, 1(r5)
/* 8024A70C 002472EC  38 00 00 15 */	li r0, 0x15
/* 8024A710 002472F0  39 04 00 08 */	addi r8, r4, 8
/* 8024A714 002472F4  98 05 00 00 */	stb r0, 0(r5)
/* 8024A718 002472F8  38 09 00 AC */	addi r0, r9, 0xac
/* 8024A71C 002472FC  39 44 00 0C */	addi r10, r4, 0xc
/* 8024A720 00247300  B0 E5 00 02 */	sth r7, 2(r5)
/* 8024A724 00247304  38 A9 00 58 */	addi r5, r9, 0x58
/* 8024A728 00247308  98 ED B5 9C */	stb r7, lbl_804D6C3C@sda21(r13)
/* 8024A72C 0024730C  80 6D B5 18 */	lwz r3, lbl_804D6BB8@sda21(r13)
/* 8024A730 00247310  90 01 00 08 */	stw r0, 8(r1)
/* 8024A734 00247314  90 E1 00 0C */	stw r7, 0xc(r1)
/* 8024A738 00247318  38 E9 00 70 */	addi r7, r9, 0x70
/* 8024A73C 0024731C  39 29 00 8C */	addi r9, r9, 0x8c
/* 8024A740 00247320  4B DC C3 B1 */	bl lbArchive_80016AF0
/* 8024A744 00247324  7F E3 FB 78 */	mr r3, r31
/* 8024A748 00247328  4B FF FD 75 */	bl func_8024A4BC
/* 8024A74C 0024732C  38 60 00 00 */	li r3, 0
/* 8024A750 00247330  38 80 00 01 */	li r4, 1
/* 8024A754 00247334  38 A0 00 80 */	li r5, 0x80
/* 8024A758 00247338  48 14 5A 99 */	bl GObj_Create
/* 8024A75C 0024733C  3C 80 80 25 */	lis r4, func_8024A168@ha
/* 8024A760 00247340  38 84 A1 68 */	addi r4, r4, func_8024A168@l
/* 8024A764 00247344  38 A0 00 00 */	li r5, 0
/* 8024A768 00247348  48 14 55 ED */	bl func_8038FD54
/* 8024A76C 0024734C  80 8D C1 9C */	lwz r4, lbl_804D783C@sda21(r13)
/* 8024A770 00247350  88 03 00 0D */	lbz r0, 0xd(r3)
/* 8024A774 00247354  50 80 26 B6 */	rlwimi r0, r4, 4, 0x1a, 0x1b
/* 8024A778 00247358  98 03 00 0D */	stb r0, 0xd(r3)
/* 8024A77C 0024735C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8024A780 00247360  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8024A784 00247364  38 21 00 20 */	addi r1, r1, 0x20
/* 8024A788 00247368  7C 08 03 A6 */	mtlr r0
/* 8024A78C 0024736C  4E 80 00 20 */	blr


.section .data
    .balign 8
.global lbl_803EEFD8
lbl_803EEFD8:
    .4byte NULL
    .4byte 0x41980000
    .4byte 0xBDCCCCCD
.global lbl_803EEFE4
lbl_803EEFE4:
    .4byte 0x41A00000
    .4byte 0x41F00000
    .4byte 0xBDCCCCCD
.global lbl_803EEFF0
lbl_803EEFF0:
    .4byte 0x42480000
    .4byte 0x43AF0000
    .4byte 0x42480000
    .asciz "Can't get user_data.\n"
    .balign 4
    .asciz "mndeflicker.c"
    .balign 4
    .asciz "user_data"
    .balign 4
    .asciz "MenMainConDf_Top_joint"
    .balign 4
    .asciz "MenMainConDf_Top_animjoint"
    .balign 4
    .asciz "MenMainConDf_Top_matanim_joint"
    .balign 4
    .asciz "MenMainConDf_Top_shapeanim_joint"


.section .bss, "wa"
    .balign 8
.global lbl_804A08B8
lbl_804A08B8:
    .skip 0x10


.section .sbss
    .balign 8
.global lbl_804D6C38
lbl_804D6C38:
    .skip 0x4
.global lbl_804D6C3C
lbl_804D6C3C:
    .skip 0x4


.section .sdata2
    .balign 8
.global lbl_804DC098
lbl_804DC098:
    .4byte 0x43300000
    .4byte 0x00000000
.global lbl_804DC0A0
lbl_804DC0A0:
    .4byte 0xC1180000
.global lbl_804DC0A4
lbl_804DC0A4:
    .4byte 0x4111999A
.global lbl_804DC0A8
lbl_804DC0A8:
    .4byte 0x41880000
.global lbl_804DC0AC
lbl_804DC0AC:
    .4byte 0x43B65777
.global lbl_804DC0B0
lbl_804DC0B0:
    .4byte 0x42198D06
.global lbl_804DC0B4
lbl_804DC0B4:
    .4byte 0x3D5566CF
.global lbl_804DC0B8
lbl_804DC0B8:
    .4byte 0x00000000
    .4byte 0x00000000
