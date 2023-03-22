.include "macros.inc"

.section .text  # 0x8024BFE0 - 0x8024C688

.global func_8024BFE0
func_8024BFE0:
/* 8024BFE0 00248BC0  7C 08 02 A6 */	mflr r0
/* 8024BFE4 00248BC4  90 01 00 04 */	stw r0, 4(r1)
/* 8024BFE8 00248BC8  94 21 FF B8 */	stwu r1, -0x48(r1)
/* 8024BFEC 00248BCC  93 E1 00 44 */	stw r31, 0x44(r1)
/* 8024BFF0 00248BD0  93 C1 00 40 */	stw r30, 0x40(r1)
/* 8024BFF4 00248BD4  93 A1 00 3C */	stw r29, 0x3c(r1)
/* 8024BFF8 00248BD8  A0 6D B5 28 */	lhz r3, lbl_804D6BC8@sda21(r13)
/* 8024BFFC 00248BDC  80 8D B5 B0 */	lwz r4, lbl_804D6C50@sda21(r13)
/* 8024C000 00248BE0  28 03 00 00 */	cmplwi r3, 0
/* 8024C004 00248BE4  83 E4 00 2C */	lwz r31, 0x2c(r4)
/* 8024C008 00248BE8  41 82 00 20 */	beq lbl_8024C028
/* 8024C00C 00248BEC  38 03 FF FF */	addi r0, r3, -1
/* 8024C010 00248BF0  B0 0D B5 28 */	sth r0, lbl_804D6BC8@sda21(r13)
/* 8024C014 00248BF4  38 00 00 00 */	li r0, 0
/* 8024C018 00248BF8  38 6D B5 28 */	addi r3, r13, lbl_804D6BC8@sda21
/* 8024C01C 00248BFC  B0 03 00 02 */	sth r0, 2(r3)
/* 8024C020 00248C00  90 03 00 04 */	stw r0, 4(r3)
/* 8024C024 00248C04  48 00 01 D0 */	b lbl_8024C1F4
lbl_8024C028:
/* 8024C028 00248C08  38 60 00 04 */	li r3, 4
/* 8024C02C 00248C0C  4B FD D5 F9 */	bl mn_80229624
/* 8024C030 00248C10  3B C0 00 00 */	li r30, 0
/* 8024C034 00248C14  38 00 00 20 */	li r0, 0x20
/* 8024C038 00248C18  3C 80 80 4A */	lis r4, lbl_804A04F0@ha
/* 8024C03C 00248C1C  3B A4 04 F0 */	addi r29, r4, lbl_804A04F0@l
/* 8024C040 00248C20  7C 60 00 38 */	and r0, r3, r0
/* 8024C044 00248C24  90 7D 00 0C */	stw r3, 0xc(r29)
/* 8024C048 00248C28  7F C5 F0 38 */	and r5, r30, r30
/* 8024C04C 00248C2C  7C 04 F2 78 */	xor r4, r0, r30
/* 8024C050 00248C30  93 DD 00 08 */	stw r30, 8(r29)
/* 8024C054 00248C34  7C A0 F2 78 */	xor r0, r5, r30
/* 8024C058 00248C38  7C 80 03 79 */	or. r0, r4, r0
/* 8024C05C 00248C3C  41 82 00 24 */	beq lbl_8024C080
/* 8024C060 00248C40  38 60 00 00 */	li r3, 0
/* 8024C064 00248C44  4B DD 7F CD */	bl func_80024030
/* 8024C068 00248C48  9B DD 00 11 */	stb r30, 0x11(r29)
/* 8024C06C 00248C4C  38 60 00 04 */	li r3, 4
/* 8024C070 00248C50  38 80 00 04 */	li r4, 4
/* 8024C074 00248C54  38 A0 00 03 */	li r5, 3
/* 8024C078 00248C58  4B FD D8 1D */	bl mn_80229894
/* 8024C07C 00248C5C  48 00 01 78 */	b lbl_8024C1F4
lbl_8024C080:
/* 8024C080 00248C60  38 00 02 00 */	li r0, 0x200
/* 8024C084 00248C64  7C 60 00 38 */	and r0, r3, r0
/* 8024C088 00248C68  7C 04 F2 78 */	xor r4, r0, r30
/* 8024C08C 00248C6C  7C A0 F2 78 */	xor r0, r5, r30
/* 8024C090 00248C70  7C 80 03 79 */	or. r0, r4, r0
/* 8024C094 00248C74  41 82 00 50 */	beq lbl_8024C0E4
/* 8024C098 00248C78  80 6D B5 B0 */	lwz r3, lbl_804D6C50@sda21(r13)
/* 8024C09C 00248C7C  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8024C0A0 00248C80  88 03 00 01 */	lbz r0, 1(r3)
/* 8024C0A4 00248C84  88 63 00 00 */	lbz r3, 0(r3)
/* 8024C0A8 00248C88  7C 00 18 40 */	cmplw r0, r3
/* 8024C0AC 00248C8C  41 82 01 48 */	beq lbl_8024C1F4
/* 8024C0B0 00248C90  4B DB ED 69 */	bl lbLang_SetSavedLanguage
/* 8024C0B4 00248C94  4B DD 0D 4D */	bl func_8001CE00
/* 8024C0B8 00248C98  38 60 00 AD */	li r3, 0xad
/* 8024C0BC 00248C9C  4B DD B9 F5 */	bl func_80027AB0
/* 8024C0C0 00248CA0  38 60 00 01 */	li r3, 1
/* 8024C0C4 00248CA4  4B FD D7 9D */	bl mn_80229860
/* 8024C0C8 00248CA8  38 60 00 01 */	li r3, 1
/* 8024C0CC 00248CAC  38 80 00 09 */	li r4, 9
/* 8024C0D0 00248CB0  4B FE 30 D9 */	bl mn_8022F1A8
/* 8024C0D4 00248CB4  38 00 00 04 */	li r0, 4
/* 8024C0D8 00248CB8  98 1D 00 00 */	stb r0, 0(r29)
/* 8024C0DC 00248CBC  B0 1D 00 02 */	sth r0, 2(r29)
/* 8024C0E0 00248CC0  48 00 01 14 */	b lbl_8024C1F4
lbl_8024C0E4:
/* 8024C0E4 00248CC4  88 1F 00 02 */	lbz r0, 2(r31)
/* 8024C0E8 00248CC8  28 00 00 00 */	cmplwi r0, 0
/* 8024C0EC 00248CCC  41 82 01 08 */	beq lbl_8024C1F4
/* 8024C0F0 00248CD0  38 00 00 04 */	li r0, 4
/* 8024C0F4 00248CD4  7C 60 00 38 */	and r0, r3, r0
/* 8024C0F8 00248CD8  7C 04 F2 78 */	xor r4, r0, r30
/* 8024C0FC 00248CDC  7C A0 F2 78 */	xor r0, r5, r30
/* 8024C100 00248CE0  7C 80 03 79 */	or. r0, r4, r0
/* 8024C104 00248CE4  41 82 00 70 */	beq lbl_8024C174
/* 8024C108 00248CE8  38 60 00 02 */	li r3, 2
/* 8024C10C 00248CEC  4B DD 7F 25 */	bl func_80024030
/* 8024C110 00248CF0  88 1F 00 00 */	lbz r0, 0(r31)
/* 8024C114 00248CF4  28 00 00 00 */	cmplwi r0, 0
/* 8024C118 00248CF8  40 82 00 08 */	bne lbl_8024C120
/* 8024C11C 00248CFC  3B C0 00 01 */	li r30, 1
lbl_8024C120:
/* 8024C120 00248D00  9B DF 00 00 */	stb r30, 0(r31)
/* 8024C124 00248D04  4C C6 31 82 */	crclr 6
/* 8024C128 00248D08  38 81 00 2C */	addi r4, r1, 0x2c
/* 8024C12C 00248D0C  80 6D B5 B0 */	lwz r3, lbl_804D6C50@sda21(r13)
/* 8024C130 00248D10  38 A0 00 01 */	li r5, 1
/* 8024C134 00248D14  8B BF 00 00 */	lbz r29, 0(r31)
/* 8024C138 00248D18  38 C0 FF FF */	li r6, -1
/* 8024C13C 00248D1C  80 63 00 28 */	lwz r3, 0x28(r3)
/* 8024C140 00248D20  4B DC 5C E5 */	bl lb_80011E24
/* 8024C144 00248D24  57 A0 10 3A */	slwi r0, r29, 2
/* 8024C148 00248D28  80 61 00 2C */	lwz r3, 0x2c(r1)
/* 8024C14C 00248D2C  38 8D 99 78 */	addi r4, r13, lbl_804D5018@sda21
/* 8024C150 00248D30  7C 24 04 2E */	lfsx f1, r4, r0
/* 8024C154 00248D34  48 12 37 69 */	bl HSD_JObjReqAnimAll
/* 8024C158 00248D38  80 61 00 2C */	lwz r3, 0x2c(r1)
/* 8024C15C 00248D3C  38 80 00 FF */	li r4, 0xff
/* 8024C160 00248D40  38 A0 00 20 */	li r5, 0x20
/* 8024C164 00248D44  4B FE 32 75 */	bl mn_8022F3D8
/* 8024C168 00248D48  80 61 00 2C */	lwz r3, 0x2c(r1)
/* 8024C16C 00248D4C  48 12 47 BD */	bl HSD_JObjAnimAll
/* 8024C170 00248D50  48 00 00 84 */	b lbl_8024C1F4
lbl_8024C174:
/* 8024C174 00248D54  38 00 00 08 */	li r0, 8
/* 8024C178 00248D58  7C 60 00 38 */	and r0, r3, r0
/* 8024C17C 00248D5C  7C 03 F2 78 */	xor r3, r0, r30
/* 8024C180 00248D60  7C A0 F2 78 */	xor r0, r5, r30
/* 8024C184 00248D64  7C 60 03 79 */	or. r0, r3, r0
/* 8024C188 00248D68  41 82 00 6C */	beq lbl_8024C1F4
/* 8024C18C 00248D6C  38 60 00 02 */	li r3, 2
/* 8024C190 00248D70  4B DD 7E A1 */	bl func_80024030
/* 8024C194 00248D74  88 1F 00 00 */	lbz r0, 0(r31)
/* 8024C198 00248D78  28 00 00 00 */	cmplwi r0, 0
/* 8024C19C 00248D7C  40 82 00 08 */	bne lbl_8024C1A4
/* 8024C1A0 00248D80  3B C0 00 01 */	li r30, 1
lbl_8024C1A4:
/* 8024C1A4 00248D84  9B DF 00 00 */	stb r30, 0(r31)
/* 8024C1A8 00248D88  4C C6 31 82 */	crclr 6
/* 8024C1AC 00248D8C  38 81 00 24 */	addi r4, r1, 0x24
/* 8024C1B0 00248D90  80 6D B5 B0 */	lwz r3, lbl_804D6C50@sda21(r13)
/* 8024C1B4 00248D94  38 A0 00 01 */	li r5, 1
/* 8024C1B8 00248D98  8B BF 00 00 */	lbz r29, 0(r31)
/* 8024C1BC 00248D9C  38 C0 FF FF */	li r6, -1
/* 8024C1C0 00248DA0  80 63 00 28 */	lwz r3, 0x28(r3)
/* 8024C1C4 00248DA4  4B DC 5C 61 */	bl lb_80011E24
/* 8024C1C8 00248DA8  57 A0 10 3A */	slwi r0, r29, 2
/* 8024C1CC 00248DAC  80 61 00 24 */	lwz r3, 0x24(r1)
/* 8024C1D0 00248DB0  38 8D 99 78 */	addi r4, r13, lbl_804D5018@sda21
/* 8024C1D4 00248DB4  7C 24 04 2E */	lfsx f1, r4, r0
/* 8024C1D8 00248DB8  48 12 36 E5 */	bl HSD_JObjReqAnimAll
/* 8024C1DC 00248DBC  80 61 00 24 */	lwz r3, 0x24(r1)
/* 8024C1E0 00248DC0  38 80 00 FF */	li r4, 0xff
/* 8024C1E4 00248DC4  38 A0 00 20 */	li r5, 0x20
/* 8024C1E8 00248DC8  4B FE 31 F1 */	bl mn_8022F3D8
/* 8024C1EC 00248DCC  80 61 00 24 */	lwz r3, 0x24(r1)
/* 8024C1F0 00248DD0  48 12 47 39 */	bl HSD_JObjAnimAll
lbl_8024C1F4:
/* 8024C1F4 00248DD4  80 01 00 4C */	lwz r0, 0x4c(r1)
/* 8024C1F8 00248DD8  83 E1 00 44 */	lwz r31, 0x44(r1)
/* 8024C1FC 00248DDC  83 C1 00 40 */	lwz r30, 0x40(r1)
/* 8024C200 00248DE0  83 A1 00 3C */	lwz r29, 0x3c(r1)
/* 8024C204 00248DE4  38 21 00 48 */	addi r1, r1, 0x48
/* 8024C208 00248DE8  7C 08 03 A6 */	mtlr r0
/* 8024C20C 00248DEC  4E 80 00 20 */	blr
lbl_8024C210:
/* 8024C210 00248DF0  7C 08 02 A6 */	mflr r0
/* 8024C214 00248DF4  3C 80 80 3F */	lis r4, lbl_803EF5AC@ha
/* 8024C218 00248DF8  90 01 00 04 */	stw r0, 4(r1)
/* 8024C21C 00248DFC  38 A0 00 80 */	li r5, 0x80
/* 8024C220 00248E00  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8024C224 00248E04  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8024C228 00248E08  3B E4 F5 AC */	addi r31, r4, lbl_803EF5AC@l
/* 8024C22C 00248E0C  38 9F 00 00 */	addi r4, r31, 0
/* 8024C230 00248E10  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8024C234 00248E14  7C 7E 1B 78 */	mr r30, r3
/* 8024C238 00248E18  80 63 00 28 */	lwz r3, 0x28(r3)
/* 8024C23C 00248E1C  4B FE 29 DD */	bl mn_8022EC18
/* 8024C240 00248E20  C0 1F 00 04 */	lfs f0, 4(r31)
/* 8024C244 00248E24  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8024C248 00248E28  4C 41 13 82 */	cror 2, 1, 2
/* 8024C24C 00248E2C  40 82 00 0C */	bne lbl_8024C258
/* 8024C250 00248E30  7F C3 F3 78 */	mr r3, r30
/* 8024C254 00248E34  48 14 3F D5 */	bl func_80390228
lbl_8024C258:
/* 8024C258 00248E38  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8024C25C 00248E3C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8024C260 00248E40  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8024C264 00248E44  38 21 00 20 */	addi r1, r1, 0x20
/* 8024C268 00248E48  7C 08 03 A6 */	mtlr r0
/* 8024C26C 00248E4C  4E 80 00 20 */	blr
lbl_8024C270:
/* 8024C270 00248E50  7C 08 02 A6 */	mflr r0
/* 8024C274 00248E54  3C 80 80 4A */	lis r4, lbl_804A04F0@ha
/* 8024C278 00248E58  90 01 00 04 */	stw r0, 4(r1)
/* 8024C27C 00248E5C  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8024C280 00248E60  93 E1 00 24 */	stw r31, 0x24(r1)
/* 8024C284 00248E64  93 C1 00 20 */	stw r30, 0x20(r1)
/* 8024C288 00248E68  7C 7E 1B 78 */	mr r30, r3
/* 8024C28C 00248E6C  88 04 04 F0 */	lbz r0, lbl_804A04F0@l(r4)
/* 8024C290 00248E70  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8024C294 00248E74  28 00 00 17 */	cmplwi r0, 0x17
/* 8024C298 00248E78  41 82 00 38 */	beq lbl_8024C2D0
/* 8024C29C 00248E7C  80 6D C1 98 */	lwz r3, lbl_804D7838@sda21(r13)
/* 8024C2A0 00248E80  48 14 3B 85 */	bl func_8038FE24
/* 8024C2A4 00248E84  3C 60 80 25 */	lis r3, lbl_8024C210@ha
/* 8024C2A8 00248E88  38 83 C2 10 */	addi r4, r3, lbl_8024C210@l
/* 8024C2AC 00248E8C  38 7E 00 00 */	addi r3, r30, 0
/* 8024C2B0 00248E90  38 A0 00 00 */	li r5, 0
/* 8024C2B4 00248E94  48 14 3A A1 */	bl func_8038FD54
/* 8024C2B8 00248E98  80 8D C1 9C */	lwz r4, lbl_804D783C@sda21(r13)
/* 8024C2BC 00248E9C  88 03 00 0D */	lbz r0, 0xd(r3)
/* 8024C2C0 00248EA0  50 80 26 B6 */	rlwimi r0, r4, 4, 0x1a, 0x1b
/* 8024C2C4 00248EA4  98 03 00 0D */	stb r0, 0xd(r3)
/* 8024C2C8 00248EA8  80 7F 00 04 */	lwz r3, 4(r31)
/* 8024C2CC 00248EAC  48 15 99 F9 */	bl func_803A5CC4
lbl_8024C2D0:
/* 8024C2D0 00248EB0  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8024C2D4 00248EB4  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 8024C2D8 00248EB8  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 8024C2DC 00248EBC  38 21 00 28 */	addi r1, r1, 0x28
/* 8024C2E0 00248EC0  7C 08 03 A6 */	mtlr r0
/* 8024C2E4 00248EC4  4E 80 00 20 */	blr
lbl_8024C2E8:
/* 8024C2E8 00248EC8  7C 08 02 A6 */	mflr r0
/* 8024C2EC 00248ECC  3C 80 80 4A */	lis r4, lbl_804A04F0@ha
/* 8024C2F0 00248ED0  90 01 00 04 */	stw r0, 4(r1)
/* 8024C2F4 00248ED4  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8024C2F8 00248ED8  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8024C2FC 00248EDC  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8024C300 00248EE0  93 A1 00 14 */	stw r29, 0x14(r1)
/* 8024C304 00248EE4  7C 7D 1B 78 */	mr r29, r3
/* 8024C308 00248EE8  88 04 04 F0 */	lbz r0, lbl_804A04F0@l(r4)
/* 8024C30C 00248EEC  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 8024C310 00248EF0  28 00 00 17 */	cmplwi r0, 0x17
/* 8024C314 00248EF4  80 63 00 28 */	lwz r3, 0x28(r3)
/* 8024C318 00248EF8  41 82 00 3C */	beq lbl_8024C354
/* 8024C31C 00248EFC  80 6D C1 98 */	lwz r3, lbl_804D7838@sda21(r13)
/* 8024C320 00248F00  48 14 3B 05 */	bl func_8038FE24
/* 8024C324 00248F04  3C 60 80 25 */	lis r3, lbl_8024C210@ha
/* 8024C328 00248F08  38 83 C2 10 */	addi r4, r3, lbl_8024C210@l
/* 8024C32C 00248F0C  38 7D 00 00 */	addi r3, r29, 0
/* 8024C330 00248F10  38 A0 00 00 */	li r5, 0
/* 8024C334 00248F14  48 14 3A 21 */	bl func_8038FD54
/* 8024C338 00248F18  80 8D C1 9C */	lwz r4, lbl_804D783C@sda21(r13)
/* 8024C33C 00248F1C  88 03 00 0D */	lbz r0, 0xd(r3)
/* 8024C340 00248F20  50 80 26 B6 */	rlwimi r0, r4, 4, 0x1a, 0x1b
/* 8024C344 00248F24  98 03 00 0D */	stb r0, 0xd(r3)
/* 8024C348 00248F28  80 7E 00 04 */	lwz r3, 4(r30)
/* 8024C34C 00248F2C  48 15 99 79 */	bl func_803A5CC4
/* 8024C350 00248F30  48 00 00 58 */	b lbl_8024C3A8
lbl_8024C354:
/* 8024C354 00248F34  3C 80 80 3F */	lis r4, lbl_803EF5A0@ha
/* 8024C358 00248F38  3B E4 F5 A0 */	addi r31, r4, lbl_803EF5A0@l
/* 8024C35C 00248F3C  38 9F 00 00 */	addi r4, r31, 0
/* 8024C360 00248F40  38 A0 00 80 */	li r5, 0x80
/* 8024C364 00248F44  4B FE 28 B5 */	bl mn_8022EC18
/* 8024C368 00248F48  C0 1F 00 04 */	lfs f0, 4(r31)
/* 8024C36C 00248F4C  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8024C370 00248F50  40 82 00 38 */	bne lbl_8024C3A8
/* 8024C374 00248F54  80 6D C1 98 */	lwz r3, lbl_804D7838@sda21(r13)
/* 8024C378 00248F58  48 14 3A AD */	bl func_8038FE24
/* 8024C37C 00248F5C  3C 60 80 25 */	lis r3, lbl_8024C270@ha
/* 8024C380 00248F60  38 83 C2 70 */	addi r4, r3, lbl_8024C270@l
/* 8024C384 00248F64  38 7D 00 00 */	addi r3, r29, 0
/* 8024C388 00248F68  38 A0 00 00 */	li r5, 0
/* 8024C38C 00248F6C  48 14 39 C9 */	bl func_8038FD54
/* 8024C390 00248F70  80 AD C1 9C */	lwz r5, lbl_804D783C@sda21(r13)
/* 8024C394 00248F74  38 00 00 01 */	li r0, 1
/* 8024C398 00248F78  88 83 00 0D */	lbz r4, 0xd(r3)
/* 8024C39C 00248F7C  50 A4 26 B6 */	rlwimi r4, r5, 4, 0x1a, 0x1b
/* 8024C3A0 00248F80  98 83 00 0D */	stb r4, 0xd(r3)
/* 8024C3A4 00248F84  98 1E 00 02 */	stb r0, 2(r30)
lbl_8024C3A8:
/* 8024C3A8 00248F88  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8024C3AC 00248F8C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8024C3B0 00248F90  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8024C3B4 00248F94  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 8024C3B8 00248F98  38 21 00 20 */	addi r1, r1, 0x20
/* 8024C3BC 00248F9C  7C 08 03 A6 */	mtlr r0
/* 8024C3C0 00248FA0  4E 80 00 20 */	blr

.global func_8024C3C4
func_8024C3C4:
/* 8024C3C4 00248FA4  7C 08 02 A6 */	mflr r0
/* 8024C3C8 00248FA8  3C 80 80 3F */	lis r4, lbl_803EF5A0@ha
/* 8024C3CC 00248FAC  90 01 00 04 */	stw r0, 4(r1)
/* 8024C3D0 00248FB0  3C 60 80 4A */	lis r3, lbl_804A08D8@ha
/* 8024C3D4 00248FB4  38 A0 00 80 */	li r5, 0x80
/* 8024C3D8 00248FB8  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 8024C3DC 00248FBC  93 E1 00 3C */	stw r31, 0x3c(r1)
/* 8024C3E0 00248FC0  93 C1 00 38 */	stw r30, 0x38(r1)
/* 8024C3E4 00248FC4  3B C3 08 D8 */	addi r30, r3, lbl_804A08D8@l
/* 8024C3E8 00248FC8  38 60 00 06 */	li r3, 6
/* 8024C3EC 00248FCC  93 A1 00 34 */	stw r29, 0x34(r1)
/* 8024C3F0 00248FD0  3B A4 F5 A0 */	addi r29, r4, lbl_803EF5A0@l
/* 8024C3F4 00248FD4  38 80 00 07 */	li r4, 7
/* 8024C3F8 00248FD8  93 81 00 30 */	stw r28, 0x30(r1)
/* 8024C3FC 00248FDC  48 14 3D F5 */	bl GObj_Create
/* 8024C400 00248FE0  7C 7C 1B 78 */	mr r28, r3
/* 8024C404 00248FE4  93 8D B5 B0 */	stw r28, lbl_804D6C50@sda21(r13)
/* 8024C408 00248FE8  80 7E 00 00 */	lwz r3, 0(r30)
/* 8024C40C 00248FEC  48 12 4A 39 */	bl HSD_JObjLoadJoint
/* 8024C410 00248FF0  3B E3 00 00 */	addi r31, r3, 0
/* 8024C414 00248FF4  88 8D C1 A9 */	lbz r4, lbl_804D7849@sda21(r13)
/* 8024C418 00248FF8  38 7C 00 00 */	addi r3, r28, 0
/* 8024C41C 00248FFC  38 BF 00 00 */	addi r5, r31, 0
/* 8024C420 00249000  48 14 46 51 */	bl func_80390A70
/* 8024C424 00249004  3C 60 80 39 */	lis r3, func_80391070@ha
/* 8024C428 00249008  38 83 10 70 */	addi r4, r3, func_80391070@l
/* 8024C42C 0024900C  38 7C 00 00 */	addi r3, r28, 0
/* 8024C430 00249010  38 A0 00 04 */	li r5, 4
/* 8024C434 00249014  38 C0 00 80 */	li r6, 0x80
/* 8024C438 00249018  48 14 42 65 */	bl GObj_SetupGXLink
/* 8024C43C 0024901C  80 9E 00 04 */	lwz r4, 4(r30)
/* 8024C440 00249020  7F E3 FB 78 */	mr r3, r31
/* 8024C444 00249024  80 BE 00 08 */	lwz r5, 8(r30)
/* 8024C448 00249028  80 DE 00 0C */	lwz r6, 0xc(r30)
/* 8024C44C 0024902C  48 12 37 11 */	bl HSD_JObjAddAnimAll
/* 8024C450 00249030  7F E3 FB 78 */	mr r3, r31
/* 8024C454 00249034  C0 22 C7 48 */	lfs f1, lbl_804DC128@sda21(r2)
/* 8024C458 00249038  48 12 34 65 */	bl HSD_JObjReqAnimAll
/* 8024C45C 0024903C  7F E3 FB 78 */	mr r3, r31
/* 8024C460 00249040  48 12 44 C9 */	bl HSD_JObjAnimAll
/* 8024C464 00249044  38 60 00 08 */	li r3, 8
/* 8024C468 00249048  48 13 2D 7D */	bl HSD_MemAlloc
/* 8024C46C 0024904C  7C 7E 1B 79 */	or. r30, r3, r3
/* 8024C470 00249050  40 82 00 20 */	bne lbl_8024C490
/* 8024C474 00249054  38 7D 00 18 */	addi r3, r29, 0x18
/* 8024C478 00249058  4C C6 31 82 */	crclr 6
/* 8024C47C 0024905C  48 0F 92 2D */	bl OSReport
/* 8024C480 00249060  38 7D 00 30 */	addi r3, r29, 0x30
/* 8024C484 00249064  38 BD 00 40 */	addi r5, r29, 0x40
/* 8024C488 00249068  38 80 01 63 */	li r4, 0x163
/* 8024C48C 0024906C  48 13 BD 95 */	bl __assert
lbl_8024C490:
/* 8024C490 00249070  4B DB E9 65 */	bl lbLang_GetSavedLanguage
/* 8024C494 00249074  98 7E 00 00 */	stb r3, 0(r30)
/* 8024C498 00249078  3C 80 80 38 */	lis r4, HSD_Free@ha
/* 8024C49C 0024907C  38 A4 F1 B0 */	addi r5, r4, HSD_Free@l
/* 8024C4A0 00249080  98 7E 00 01 */	stb r3, 1(r30)
/* 8024C4A4 00249084  38 00 00 00 */	li r0, 0
/* 8024C4A8 00249088  38 7C 00 00 */	addi r3, r28, 0
/* 8024C4AC 0024908C  90 1E 00 04 */	stw r0, 4(r30)
/* 8024C4B0 00249090  7F C6 F3 78 */	mr r6, r30
/* 8024C4B4 00249094  38 80 00 00 */	li r4, 0
/* 8024C4B8 00249098  98 1E 00 02 */	stb r0, 2(r30)
/* 8024C4BC 0024909C  48 14 46 AD */	bl GObj_InitUserData
/* 8024C4C0 002490A0  3C 60 80 25 */	lis r3, lbl_8024C2E8@ha
/* 8024C4C4 002490A4  38 83 C2 E8 */	addi r4, r3, lbl_8024C2E8@l
/* 8024C4C8 002490A8  38 7C 00 00 */	addi r3, r28, 0
/* 8024C4CC 002490AC  38 A0 00 00 */	li r5, 0
/* 8024C4D0 002490B0  48 14 38 85 */	bl func_8038FD54
/* 8024C4D4 002490B4  80 AD C1 9C */	lwz r5, lbl_804D783C@sda21(r13)
/* 8024C4D8 002490B8  38 81 00 1C */	addi r4, r1, 0x1c
/* 8024C4DC 002490BC  88 03 00 0D */	lbz r0, 0xd(r3)
/* 8024C4E0 002490C0  4C C6 31 82 */	crclr 6
/* 8024C4E4 002490C4  50 A0 26 B6 */	rlwimi r0, r5, 4, 0x1a, 0x1b
/* 8024C4E8 002490C8  98 03 00 0D */	stb r0, 0xd(r3)
/* 8024C4EC 002490CC  38 A0 00 01 */	li r5, 1
/* 8024C4F0 002490D0  38 C0 FF FF */	li r6, -1
/* 8024C4F4 002490D4  80 7C 00 28 */	lwz r3, 0x28(r28)
/* 8024C4F8 002490D8  8B BE 00 00 */	lbz r29, 0(r30)
/* 8024C4FC 002490DC  4B DC 59 29 */	bl lb_80011E24
/* 8024C500 002490E0  57 A0 10 3A */	slwi r0, r29, 2
/* 8024C504 002490E4  80 61 00 1C */	lwz r3, 0x1c(r1)
/* 8024C508 002490E8  38 8D 99 78 */	addi r4, r13, lbl_804D5018@sda21
/* 8024C50C 002490EC  7C 24 04 2E */	lfsx f1, r4, r0
/* 8024C510 002490F0  48 12 33 AD */	bl HSD_JObjReqAnimAll
/* 8024C514 002490F4  80 61 00 1C */	lwz r3, 0x1c(r1)
/* 8024C518 002490F8  38 80 00 FF */	li r4, 0xff
/* 8024C51C 002490FC  38 A0 00 20 */	li r5, 0x20
/* 8024C520 00249100  4B FE 2E B9 */	bl mn_8022F3D8
/* 8024C524 00249104  80 61 00 1C */	lwz r3, 0x1c(r1)
/* 8024C528 00249108  48 12 44 01 */	bl HSD_JObjAnimAll
/* 8024C52C 0024910C  7F E3 FB 78 */	mr r3, r31
/* 8024C530 00249110  C0 22 C7 48 */	lfs f1, lbl_804DC128@sda21(r2)
/* 8024C534 00249114  48 12 33 89 */	bl HSD_JObjReqAnimAll
/* 8024C538 00249118  38 7F 00 00 */	addi r3, r31, 0
/* 8024C53C 0024911C  38 80 00 FF */	li r4, 0xff
/* 8024C540 00249120  38 A0 00 80 */	li r5, 0x80
/* 8024C544 00249124  4B FE 2E 95 */	bl mn_8022F3D8
/* 8024C548 00249128  7F E3 FB 78 */	mr r3, r31
/* 8024C54C 0024912C  48 12 43 DD */	bl HSD_JObjAnimAll
/* 8024C550 00249130  80 6D B5 B0 */	lwz r3, lbl_804D6C50@sda21(r13)
/* 8024C554 00249134  83 A3 00 2C */	lwz r29, 0x2c(r3)
/* 8024C558 00249138  80 7D 00 04 */	lwz r3, 4(r29)
/* 8024C55C 0024913C  28 03 00 00 */	cmplwi r3, 0
/* 8024C560 00249140  41 82 00 08 */	beq lbl_8024C568
/* 8024C564 00249144  48 15 97 61 */	bl func_803A5CC4
lbl_8024C568:
/* 8024C568 00249148  C0 22 C7 30 */	lfs f1, lbl_804DC110@sda21(r2)
/* 8024C56C 0024914C  38 60 00 00 */	li r3, 0
/* 8024C570 00249150  C0 42 C7 34 */	lfs f2, lbl_804DC114@sda21(r2)
/* 8024C574 00249154  38 80 00 01 */	li r4, 1
/* 8024C578 00249158  C0 62 C7 38 */	lfs f3, lbl_804DC118@sda21(r2)
/* 8024C57C 0024915C  C0 82 C7 3C */	lfs f4, lbl_804DC11C@sda21(r2)
/* 8024C580 00249160  C0 A2 C7 40 */	lfs f5, lbl_804DC120@sda21(r2)
/* 8024C584 00249164  48 15 95 49 */	bl func_803A5ACC
/* 8024C588 00249168  90 7D 00 04 */	stw r3, 4(r29)
/* 8024C58C 0024916C  38 80 00 BF */	li r4, 0xbf
/* 8024C590 00249170  C0 02 C7 44 */	lfs f0, lbl_804DC124@sda21(r2)
/* 8024C594 00249174  D0 03 00 24 */	stfs f0, 0x24(r3)
/* 8024C598 00249178  D0 03 00 28 */	stfs f0, 0x28(r3)
/* 8024C59C 0024917C  48 15 9D CD */	bl func_803A6368
/* 8024C5A0 00249180  80 01 00 44 */	lwz r0, 0x44(r1)
/* 8024C5A4 00249184  83 E1 00 3C */	lwz r31, 0x3c(r1)
/* 8024C5A8 00249188  83 C1 00 38 */	lwz r30, 0x38(r1)
/* 8024C5AC 0024918C  83 A1 00 34 */	lwz r29, 0x34(r1)
/* 8024C5B0 00249190  83 81 00 30 */	lwz r28, 0x30(r1)
/* 8024C5B4 00249194  38 21 00 40 */	addi r1, r1, 0x40
/* 8024C5B8 00249198  7C 08 03 A6 */	mtlr r0
/* 8024C5BC 0024919C  4E 80 00 20 */	blr

.global func_8024C5C0
func_8024C5C0:
/* 8024C5C0 002491A0  7C 08 02 A6 */	mflr r0
/* 8024C5C4 002491A4  3C 80 80 4A */	lis r4, lbl_804A04F0@ha
/* 8024C5C8 002491A8  90 01 00 04 */	stw r0, 4(r1)
/* 8024C5CC 002491AC  38 A4 04 F0 */	addi r5, r4, lbl_804A04F0@l
/* 8024C5D0 002491B0  3C 80 80 3F */	lis r4, lbl_803EF5A0@ha
/* 8024C5D4 002491B4  4C C6 31 82 */	crclr 6
/* 8024C5D8 002491B8  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8024C5DC 002491BC  39 24 F5 A0 */	addi r9, r4, lbl_803EF5A0@l
/* 8024C5E0 002491C0  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8024C5E4 002491C4  38 00 00 05 */	li r0, 5
/* 8024C5E8 002491C8  3C 80 80 4A */	lis r4, lbl_804A08D8@ha
/* 8024C5EC 002491CC  B0 0D B5 28 */	sth r0, lbl_804D6BC8@sda21(r13)
/* 8024C5F0 002491D0  38 84 08 D8 */	addi r4, r4, lbl_804A08D8@l
/* 8024C5F4 002491D4  38 C0 00 00 */	li r6, 0
/* 8024C5F8 002491D8  88 05 00 00 */	lbz r0, 0(r5)
/* 8024C5FC 002491DC  7C 7F 1B 78 */	mr r31, r3
/* 8024C600 002491E0  38 E9 00 64 */	addi r7, r9, 0x64
/* 8024C604 002491E4  98 05 00 01 */	stb r0, 1(r5)
/* 8024C608 002491E8  38 00 00 17 */	li r0, 0x17
/* 8024C60C 002491EC  39 04 00 08 */	addi r8, r4, 8
/* 8024C610 002491F0  98 05 00 00 */	stb r0, 0(r5)
/* 8024C614 002491F4  38 09 00 A0 */	addi r0, r9, 0xa0
/* 8024C618 002491F8  39 44 00 0C */	addi r10, r4, 0xc
/* 8024C61C 002491FC  B0 C5 00 02 */	sth r6, 2(r5)
/* 8024C620 00249200  80 AD B5 18 */	lwz r5, lbl_804D6BB8@sda21(r13)
/* 8024C624 00249204  90 01 00 08 */	stw r0, 8(r1)
/* 8024C628 00249208  38 65 00 00 */	addi r3, r5, 0
/* 8024C62C 0024920C  38 A9 00 4C */	addi r5, r9, 0x4c
/* 8024C630 00249210  90 C1 00 0C */	stw r6, 0xc(r1)
/* 8024C634 00249214  38 C4 00 04 */	addi r6, r4, 4
/* 8024C638 00249218  39 29 00 80 */	addi r9, r9, 0x80
/* 8024C63C 0024921C  4B DC A4 B5 */	bl func_80016AF0
/* 8024C640 00249220  7F E3 FB 78 */	mr r3, r31
/* 8024C644 00249224  4B FF FD 81 */	bl func_8024C3C4
/* 8024C648 00249228  38 60 00 00 */	li r3, 0
/* 8024C64C 0024922C  38 80 00 01 */	li r4, 1
/* 8024C650 00249230  38 A0 00 80 */	li r5, 0x80
/* 8024C654 00249234  48 14 3B 9D */	bl GObj_Create
/* 8024C658 00249238  3C 80 80 25 */	lis r4, func_8024BFE0@ha
/* 8024C65C 0024923C  38 84 BF E0 */	addi r4, r4, func_8024BFE0@l
/* 8024C660 00249240  38 A0 00 00 */	li r5, 0
/* 8024C664 00249244  48 14 36 F1 */	bl func_8038FD54
/* 8024C668 00249248  80 8D C1 9C */	lwz r4, lbl_804D783C@sda21(r13)
/* 8024C66C 0024924C  88 03 00 0D */	lbz r0, 0xd(r3)
/* 8024C670 00249250  50 80 26 B6 */	rlwimi r0, r4, 4, 0x1a, 0x1b
/* 8024C674 00249254  98 03 00 0D */	stb r0, 0xd(r3)
/* 8024C678 00249258  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8024C67C 0024925C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8024C680 00249260  38 21 00 20 */	addi r1, r1, 0x20
/* 8024C684 00249264  7C 08 03 A6 */	mtlr r0
/* 8024C688 00249268  4E 80 00 20 */	blr


.section .data
    .balign 8
.global lbl_803EF5A0
lbl_803EF5A0:
    .4byte NULL
    .4byte 0x41980000
    .4byte 0xBDCCCCCD
.global lbl_803EF5AC
lbl_803EF5AC:
    .4byte 0x41A00000
    .4byte 0x41E80000
    .4byte 0xBDCCCCCD
    .asciz "Can't get user_data.\n"
    .balign 4
    .asciz "mnlanguage.c"
    .balign 4
    .asciz "user_data"
    .balign 4
    .asciz "MenMainConLa_Top_joint"
    .balign 4
    .asciz "MenMainConLa_Top_animjoint"
    .balign 4
    .asciz "MenMainConLa_Top_matanim_joint"
    .balign 4
    .asciz "MenMainConLa_Top_shapeanim_joint"


.section .bss, "wa"
    .balign 8
.global lbl_804A08D8
lbl_804A08D8:
    .skip 0x10


.section .sdata
    .balign 8
.global lbl_804D5018
lbl_804D5018:
    .4byte 0x3F800000
    .4byte 0x00000000


.section .sbss
    .balign 8
.global lbl_804D6C50
lbl_804D6C50:
    .skip 0x4


.section .sdata2
    .balign 8
.global lbl_804DC110
lbl_804DC110:
    .4byte 0xC1180000
.global lbl_804DC114
lbl_804DC114:
    .4byte 0x4111999A
.global lbl_804DC118
lbl_804DC118:
    .4byte 0x41880000
.global lbl_804DC11C
lbl_804DC11C:
    .4byte 0x43B65777
.global lbl_804DC120
lbl_804DC120:
    .4byte 0x42198D06
.global lbl_804DC124
lbl_804DC124:
    .4byte 0x3D5566CF
.global lbl_804DC128
lbl_804DC128:
    .4byte 0x00000000
    .4byte 0x00000000
