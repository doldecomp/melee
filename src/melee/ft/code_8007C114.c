#include <dolphin/types.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ftcoll.h>

static f32 const lbl_804D8320 = 0.0F;
static f32 const lbl_804D8324 = 1.0F;

extern unk_t func_800C555C();
extern void func_80008440(Hitbox*);
extern unk_t func_80008688();
extern unk_t func_8000ACFC();
extern unk_t func_800089B8();
extern unk_t func_80007AFC();

void func_8007C224(HSD_GObj* fighter_gobj);

#pragma push
asm void func_8007C114(HSD_GObj* fighter_gobj)
{ // clang-format off
    nofralloc
/* 8007C114 00078CF4  7C 08 02 A6 */	mflr r0
/* 8007C118 00078CF8  90 01 00 04 */	stw r0, 4(r1)
/* 8007C11C 00078CFC  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8007C120 00078D00  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8007C124 00078D04  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8007C128 00078D08  7C 7E 1B 78 */	mr r30, r3
/* 8007C12C 00078D0C  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8007C130 00078D10  80 7F 19 74 */	lwz r3, 0x1974(r31)
/* 8007C134 00078D14  28 03 00 00 */	cmplwi r3, 0
/* 8007C138 00078D18  41 82 00 1C */	beq lbl_8007C154
/* 8007C13C 00078D1C  48 1E F1 C5 */	bl itGetKind
/* 8007C140 00078D20  2C 03 00 1C */	cmpwi r3, 0x1c
/* 8007C144 00078D24  41 82 00 08 */	beq lbl_8007C14C
/* 8007C148 00078D28  48 00 00 0C */	b lbl_8007C154
lbl_8007C14C:
/* 8007C14C 00078D2C  7F C3 F3 78 */	mr r3, r30
/* 8007C150 00078D30  48 04 94 0D */	bl func_800C555C
lbl_8007C154:
/* 8007C154 00078D34  88 1F 22 19 */	lbz r0, 0x2219(r31)
/* 8007C158 00078D38  38 60 00 00 */	li r3, 0
/* 8007C15C 00078D3C  50 60 1F 38 */	rlwimi r0, r3, 3, 0x1c, 0x1c
/* 8007C160 00078D40  98 1F 22 19 */	stb r0, 0x2219(r31)
/* 8007C164 00078D44  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8007C168 00078D48  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8007C16C 00078D4C  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8007C170 00078D50  38 21 00 18 */	addi r1, r1, 0x18
/* 8007C174 00078D54  7C 08 03 A6 */	mtlr r0
/* 8007C178 00078D58  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm void func_8007C17C(HSD_GObj* fighter_gobj)
{ // clang-format off
    nofralloc
/* 8007C17C 00078D5C  7C 08 02 A6 */	mflr r0
/* 8007C180 00078D60  90 01 00 04 */	stw r0, 4(r1)
/* 8007C184 00078D64  38 00 00 01 */	li r0, 1
/* 8007C188 00078D68  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8007C18C 00078D6C  BF 61 00 14 */	stmw r27, 0x14(r1)
/* 8007C190 00078D70  3B E0 00 00 */	li r31, 0
/* 8007C194 00078D74  7C 7B 1B 78 */	mr r27, r3
/* 8007C198 00078D78  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 8007C19C 00078D7C  80 9E 01 0C */	lwz r4, 0x10c(r30)
/* 8007C1A0 00078D80  3B BE 10 64 */	addi r29, r30, 0x1064
/* 8007C1A4 00078D84  38 7D 00 00 */	addi r3, r29, 0
/* 8007C1A8 00078D88  83 84 00 34 */	lwz r28, 0x34(r4)
/* 8007C1AC 00078D8C  93 FE 10 68 */	stw r31, 0x1068(r30)
/* 8007C1B0 00078D90  90 1E 10 64 */	stw r0, 0x1064(r30)
/* 8007C1B4 00078D94  4B F8 C2 8D */	bl func_80008440
/* 8007C1B8 00078D98  80 1C 00 00 */	lwz r0, 0(r28)
/* 8007C1BC 00078D9C  7F 63 DB 78 */	mr r3, r27
/* 8007C1C0 00078DA0  80 9E 05 E8 */	lwz r4, 0x5e8(r30)
/* 8007C1C4 00078DA4  54 00 20 36 */	slwi r0, r0, 4
/* 8007C1C8 00078DA8  7C 04 00 2E */	lwzx r0, r4, r0
/* 8007C1CC 00078DAC  90 1D 00 48 */	stw r0, 0x48(r29)
/* 8007C1D0 00078DB0  C0 1C 00 04 */	lfs f0, 4(r28)
/* 8007C1D4 00078DB4  D0 1D 00 1C */	stfs f0, 0x1c(r29)
/* 8007C1D8 00078DB8  C0 02 89 40 */	lfs f0, lbl_804D8320(r2)
/* 8007C1DC 00078DBC  D0 1D 00 18 */	stfs f0, 0x18(r29)
/* 8007C1E0 00078DC0  D0 1D 00 14 */	stfs f0, 0x14(r29)
/* 8007C1E4 00078DC4  D0 1D 00 10 */	stfs f0, 0x10(r29)
/* 8007C1E8 00078DC8  88 1D 00 43 */	lbz r0, 0x43(r29)
/* 8007C1EC 00078DCC  53 E0 36 72 */	rlwimi r0, r31, 6, 0x19, 0x19
/* 8007C1F0 00078DD0  98 1D 00 43 */	stb r0, 0x43(r29)
/* 8007C1F4 00078DD4  88 1D 00 43 */	lbz r0, 0x43(r29)
/* 8007C1F8 00078DD8  53 E0 2E B4 */	rlwimi r0, r31, 5, 0x1a, 0x1a
/* 8007C1FC 00078DDC  98 1D 00 43 */	stb r0, 0x43(r29)
/* 8007C200 00078DE0  88 1E 22 27 */	lbz r0, 0x2227(r30)
/* 8007C204 00078DE4  53 E0 2E B4 */	rlwimi r0, r31, 5, 0x1a, 0x1a
/* 8007C208 00078DE8  98 1E 22 27 */	stb r0, 0x2227(r30)
/* 8007C20C 00078DEC  48 00 00 19 */	bl func_8007C224
/* 8007C210 00078DF0  BB 61 00 14 */	lmw r27, 0x14(r1)
/* 8007C214 00078DF4  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8007C218 00078DF8  38 21 00 28 */	addi r1, r1, 0x28
/* 8007C21C 00078DFC  7C 08 03 A6 */	mtlr r0
/* 8007C220 00078E00  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm void func_8007C224(HSD_GObj* fighter_gobj)
{ // clang-format off
    nofralloc
/* 8007C224 00078E04  7C 08 02 A6 */	mflr r0
/* 8007C228 00078E08  90 01 00 04 */	stw r0, 4(r1)
/* 8007C22C 00078E0C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8007C230 00078E10  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8007C234 00078E14  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8007C238 00078E18  80 03 10 64 */	lwz r0, 0x1064(r3)
/* 8007C23C 00078E1C  3B E3 10 64 */	addi r31, r3, 0x1064
/* 8007C240 00078E20  2C 00 00 02 */	cmpwi r0, 2
/* 8007C244 00078E24  41 82 00 58 */	beq lbl_8007C29C
/* 8007C248 00078E28  40 80 00 14 */	bge lbl_8007C25C
/* 8007C24C 00078E2C  2C 00 00 00 */	cmpwi r0, 0
/* 8007C250 00078E30  41 82 00 7C */	beq lbl_8007C2CC
/* 8007C254 00078E34  40 80 00 14 */	bge lbl_8007C268
/* 8007C258 00078E38  48 00 00 74 */	b lbl_8007C2CC
lbl_8007C25C:
/* 8007C25C 00078E3C  2C 00 00 04 */	cmpwi r0, 4
/* 8007C260 00078E40  40 80 00 6C */	bge lbl_8007C2CC
/* 8007C264 00078E44  48 00 00 40 */	b lbl_8007C2A4
lbl_8007C268:
/* 8007C268 00078E48  80 7F 00 48 */	lwz r3, 0x48(r31)
/* 8007C26C 00078E4C  38 9F 00 10 */	addi r4, r31, 0x10
/* 8007C270 00078E50  38 BF 00 4C */	addi r5, r31, 0x4c
/* 8007C274 00078E54  4B F8 EF 59 */	bl func_8000B1CC
/* 8007C278 00078E58  80 9F 00 4C */	lwz r4, 0x4c(r31)
/* 8007C27C 00078E5C  38 00 00 02 */	li r0, 2
/* 8007C280 00078E60  80 7F 00 50 */	lwz r3, 0x50(r31)
/* 8007C284 00078E64  90 9F 00 58 */	stw r4, 0x58(r31)
/* 8007C288 00078E68  90 7F 00 5C */	stw r3, 0x5c(r31)
/* 8007C28C 00078E6C  80 7F 00 54 */	lwz r3, 0x54(r31)
/* 8007C290 00078E70  90 7F 00 60 */	stw r3, 0x60(r31)
/* 8007C294 00078E74  90 1F 00 00 */	stw r0, 0(r31)
/* 8007C298 00078E78  48 00 00 34 */	b lbl_8007C2CC
lbl_8007C29C:
/* 8007C29C 00078E7C  38 00 00 03 */	li r0, 3
/* 8007C2A0 00078E80  90 1F 00 00 */	stw r0, 0(r31)
lbl_8007C2A4:
/* 8007C2A4 00078E84  80 7F 00 4C */	lwz r3, 0x4c(r31)
/* 8007C2A8 00078E88  38 9F 00 10 */	addi r4, r31, 0x10
/* 8007C2AC 00078E8C  80 1F 00 50 */	lwz r0, 0x50(r31)
/* 8007C2B0 00078E90  38 BF 00 4C */	addi r5, r31, 0x4c
/* 8007C2B4 00078E94  90 7F 00 58 */	stw r3, 0x58(r31)
/* 8007C2B8 00078E98  90 1F 00 5C */	stw r0, 0x5c(r31)
/* 8007C2BC 00078E9C  80 1F 00 54 */	lwz r0, 0x54(r31)
/* 8007C2C0 00078EA0  90 1F 00 60 */	stw r0, 0x60(r31)
/* 8007C2C4 00078EA4  80 7F 00 48 */	lwz r3, 0x48(r31)
/* 8007C2C8 00078EA8  4B F8 EF 05 */	bl func_8000B1CC
lbl_8007C2CC:
/* 8007C2CC 00078EAC  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8007C2D0 00078EB0  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8007C2D4 00078EB4  38 21 00 20 */	addi r1, r1, 0x20
/* 8007C2D8 00078EB8  7C 08 03 A6 */	mtlr r0
/* 8007C2DC 00078EBC  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8007C2E0()
{ // clang-format off
    nofralloc
/* 8007C2E0 00078EC0  7C 08 02 A6 */	mflr r0
/* 8007C2E4 00078EC4  90 01 00 04 */	stw r0, 4(r1)
/* 8007C2E8 00078EC8  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 8007C2EC 00078ECC  93 E1 00 34 */	stw r31, 0x34(r1)
/* 8007C2F0 00078ED0  3B E6 00 00 */	addi r31, r6, 0
/* 8007C2F4 00078ED4  93 C1 00 30 */	stw r30, 0x30(r1)
/* 8007C2F8 00078ED8  3B C5 00 00 */	addi r30, r5, 0
/* 8007C2FC 00078EDC  93 A1 00 2C */	stw r29, 0x2c(r1)
/* 8007C300 00078EE0  3B A4 00 00 */	addi r29, r4, 0
/* 8007C304 00078EE4  93 81 00 28 */	stw r28, 0x28(r1)
/* 8007C308 00078EE8  3B 83 00 00 */	addi r28, r3, 0
/* 8007C30C 00078EEC  38 7E 00 00 */	addi r3, r30, 0
/* 8007C310 00078EF0  4B F8 E9 ED */	bl func_8000ACFC
/* 8007C314 00078EF4  2C 03 00 00 */	cmpwi r3, 0
/* 8007C318 00078EF8  40 82 01 84 */	bne lbl_8007C49C
/* 8007C31C 00078EFC  38 7F 00 00 */	addi r3, r31, 0
/* 8007C320 00078F00  38 BC 00 00 */	addi r5, r28, 0
/* 8007C324 00078F04  38 80 00 03 */	li r4, 3
/* 8007C328 00078F08  4B F8 C3 61 */	bl func_80008688
/* 8007C32C 00078F0C  80 1E 00 E0 */	lwz r0, 0xe0(r30)
/* 8007C330 00078F10  2C 00 00 01 */	cmpwi r0, 1
/* 8007C334 00078F14  40 82 00 A8 */	bne lbl_8007C3DC
/* 8007C338 00078F18  C0 5C 01 98 */	lfs f2, 0x198(r28)
/* 8007C33C 00078F1C  C0 3E 01 98 */	lfs f1, 0x198(r30)
/* 8007C340 00078F20  C0 02 89 44 */	lfs f0, lbl_804D8324(r2)
/* 8007C344 00078F24  EC 22 08 24 */	fdivs f1, f2, f1
/* 8007C348 00078F28  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8007C34C 00078F2C  FC A0 08 90 */	fmr f5, f1
/* 8007C350 00078F30  40 81 00 08 */	ble lbl_8007C358
/* 8007C354 00078F34  FC A0 00 90 */	fmr f5, f0
lbl_8007C358:
/* 8007C358 00078F38  C0 9C 00 C8 */	lfs f4, 0xc8(r28)
/* 8007C35C 00078F3C  C0 7E 00 C8 */	lfs f3, 0xc8(r30)
/* 8007C360 00078F40  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8007C364 00078F44  EC 24 00 F2 */	fmuls f1, f4, f3
/* 8007C368 00078F48  C0 02 89 40 */	lfs f0, lbl_804D8320(r2)
/* 8007C36C 00078F4C  C0 43 07 D4 */	lfs f2, 0x7d4(r3)
/* 8007C370 00078F50  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8007C374 00078F54  EC A5 00 B2 */	fmuls f5, f5, f2
/* 8007C378 00078F58  4C 41 13 82 */	cror 2, 1, 2
/* 8007C37C 00078F5C  40 82 00 18 */	bne lbl_8007C394
/* 8007C380 00078F60  EC 24 18 28 */	fsubs f1, f4, f3
/* 8007C384 00078F64  C0 1E 00 98 */	lfs f0, 0x98(r30)
/* 8007C388 00078F68  EC 05 00 7A */	fmadds f0, f5, f1, f0
/* 8007C38C 00078F6C  D0 1E 00 98 */	stfs f0, 0x98(r30)
/* 8007C390 00078F70  48 00 00 10 */	b lbl_8007C3A0
lbl_8007C394:
/* 8007C394 00078F74  C0 1E 00 98 */	lfs f0, 0x98(r30)
/* 8007C398 00078F78  EC 04 01 7A */	fmadds f0, f4, f5, f0
/* 8007C39C 00078F7C  D0 1E 00 98 */	stfs f0, 0x98(r30)
lbl_8007C3A0:
/* 8007C3A0 00078F80  C0 7C 00 CC */	lfs f3, 0xcc(r28)
/* 8007C3A4 00078F84  C0 5E 00 CC */	lfs f2, 0xcc(r30)
/* 8007C3A8 00078F88  C0 02 89 40 */	lfs f0, lbl_804D8320(r2)
/* 8007C3AC 00078F8C  EC 23 00 B2 */	fmuls f1, f3, f2
/* 8007C3B0 00078F90  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8007C3B4 00078F94  4C 41 13 82 */	cror 2, 1, 2
/* 8007C3B8 00078F98  40 82 00 18 */	bne lbl_8007C3D0
/* 8007C3BC 00078F9C  EC 23 10 28 */	fsubs f1, f3, f2
/* 8007C3C0 00078FA0  C0 1E 00 9C */	lfs f0, 0x9c(r30)
/* 8007C3C4 00078FA4  EC 05 00 7A */	fmadds f0, f5, f1, f0
/* 8007C3C8 00078FA8  D0 1E 00 9C */	stfs f0, 0x9c(r30)
/* 8007C3CC 00078FAC  48 00 00 10 */	b lbl_8007C3DC
lbl_8007C3D0:
/* 8007C3D0 00078FB0  C0 1E 00 9C */	lfs f0, 0x9c(r30)
/* 8007C3D4 00078FB4  EC 03 01 7A */	fmadds f0, f3, f5, f0
/* 8007C3D8 00078FB8  D0 1E 00 9C */	stfs f0, 0x9c(r30)
lbl_8007C3DC:
/* 8007C3DC 00078FBC  38 7D 00 00 */	addi r3, r29, 0
/* 8007C3E0 00078FC0  38 BE 00 00 */	addi r5, r30, 0
/* 8007C3E4 00078FC4  38 80 00 03 */	li r4, 3
/* 8007C3E8 00078FC8  4B F8 C2 A1 */	bl func_80008688
/* 8007C3EC 00078FCC  80 1C 00 E0 */	lwz r0, 0xe0(r28)
/* 8007C3F0 00078FD0  2C 00 00 01 */	cmpwi r0, 1
/* 8007C3F4 00078FD4  40 82 00 A8 */	bne lbl_8007C49C
/* 8007C3F8 00078FD8  C0 5E 01 98 */	lfs f2, 0x198(r30)
/* 8007C3FC 00078FDC  C0 3C 01 98 */	lfs f1, 0x198(r28)
/* 8007C400 00078FE0  C0 02 89 44 */	lfs f0, lbl_804D8324(r2)
/* 8007C404 00078FE4  EC 22 08 24 */	fdivs f1, f2, f1
/* 8007C408 00078FE8  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8007C40C 00078FEC  FC A0 08 90 */	fmr f5, f1
/* 8007C410 00078FF0  40 81 00 08 */	ble lbl_8007C418
/* 8007C414 00078FF4  FC A0 00 90 */	fmr f5, f0
lbl_8007C418:
/* 8007C418 00078FF8  C0 7C 00 C8 */	lfs f3, 0xc8(r28)
/* 8007C41C 00078FFC  C0 9E 00 C8 */	lfs f4, 0xc8(r30)
/* 8007C420 00079000  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8007C424 00079004  EC 23 01 32 */	fmuls f1, f3, f4
/* 8007C428 00079008  C0 02 89 40 */	lfs f0, lbl_804D8320(r2)
/* 8007C42C 0007900C  C0 43 07 D4 */	lfs f2, 0x7d4(r3)
/* 8007C430 00079010  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8007C434 00079014  EC A5 00 B2 */	fmuls f5, f5, f2
/* 8007C438 00079018  4C 41 13 82 */	cror 2, 1, 2
/* 8007C43C 0007901C  40 82 00 18 */	bne lbl_8007C454
/* 8007C440 00079020  EC 24 18 28 */	fsubs f1, f4, f3
/* 8007C444 00079024  C0 1C 00 98 */	lfs f0, 0x98(r28)
/* 8007C448 00079028  EC 05 00 7A */	fmadds f0, f5, f1, f0
/* 8007C44C 0007902C  D0 1C 00 98 */	stfs f0, 0x98(r28)
/* 8007C450 00079030  48 00 00 10 */	b lbl_8007C460
lbl_8007C454:
/* 8007C454 00079034  C0 1C 00 98 */	lfs f0, 0x98(r28)
/* 8007C458 00079038  EC 04 01 7A */	fmadds f0, f4, f5, f0
/* 8007C45C 0007903C  D0 1C 00 98 */	stfs f0, 0x98(r28)
lbl_8007C460:
/* 8007C460 00079040  C0 5C 00 CC */	lfs f2, 0xcc(r28)
/* 8007C464 00079044  C0 7E 00 CC */	lfs f3, 0xcc(r30)
/* 8007C468 00079048  C0 02 89 40 */	lfs f0, lbl_804D8320(r2)
/* 8007C46C 0007904C  EC 22 00 F2 */	fmuls f1, f2, f3
/* 8007C470 00079050  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8007C474 00079054  4C 41 13 82 */	cror 2, 1, 2
/* 8007C478 00079058  40 82 00 18 */	bne lbl_8007C490
/* 8007C47C 0007905C  EC 23 10 28 */	fsubs f1, f3, f2
/* 8007C480 00079060  C0 1C 00 9C */	lfs f0, 0x9c(r28)
/* 8007C484 00079064  EC 05 00 7A */	fmadds f0, f5, f1, f0
/* 8007C488 00079068  D0 1C 00 9C */	stfs f0, 0x9c(r28)
/* 8007C48C 0007906C  48 00 00 10 */	b lbl_8007C49C
lbl_8007C490:
/* 8007C490 00079070  C0 1C 00 9C */	lfs f0, 0x9c(r28)
/* 8007C494 00079074  EC 03 01 7A */	fmadds f0, f3, f5, f0
/* 8007C498 00079078  D0 1C 00 9C */	stfs f0, 0x9c(r28)
lbl_8007C49C:
/* 8007C49C 0007907C  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 8007C4A0 00079080  83 E1 00 34 */	lwz r31, 0x34(r1)
/* 8007C4A4 00079084  83 C1 00 30 */	lwz r30, 0x30(r1)
/* 8007C4A8 00079088  83 A1 00 2C */	lwz r29, 0x2c(r1)
/* 8007C4AC 0007908C  83 81 00 28 */	lwz r28, 0x28(r1)
/* 8007C4B0 00079090  38 21 00 38 */	addi r1, r1, 0x38
/* 8007C4B4 00079094  7C 08 03 A6 */	mtlr r0
/* 8007C4B8 00079098  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm void func_8007C4BC(HSD_GObj* fighter_gobj)
{ // clang-format off
    nofralloc
/* 8007C4BC 0007909C  7C 08 02 A6 */	mflr r0
/* 8007C4C0 000790A0  90 01 00 04 */	stw r0, 4(r1)
/* 8007C4C4 000790A4  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 8007C4C8 000790A8  BF 01 00 20 */	stmw r24, 0x20(r1)
/* 8007C4CC 000790AC  7C 7C 1B 78 */	mr r28, r3
/* 8007C4D0 000790B0  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8007C4D4 000790B4  88 03 22 27 */	lbz r0, 0x2227(r3)
/* 8007C4D8 000790B8  3B E3 00 00 */	addi r31, r3, 0
/* 8007C4DC 000790BC  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 8007C4E0 000790C0  41 82 01 3C */	beq lbl_8007C61C
/* 8007C4E4 000790C4  7F 83 E3 78 */	mr r3, r28
/* 8007C4E8 000790C8  4B FF F3 81 */	bl func_8007B868
/* 8007C4EC 000790CC  2C 03 00 02 */	cmpwi r3, 2
/* 8007C4F0 000790D0  41 82 01 2C */	beq lbl_8007C61C
/* 8007C4F4 000790D4  88 1F 22 1F */	lbz r0, 0x221f(r31)
/* 8007C4F8 000790D8  54 00 EF FF */	rlwinm. r0, r0, 0x1d, 0x1f, 0x1f
/* 8007C4FC 000790DC  40 82 01 20 */	bne lbl_8007C61C
/* 8007C500 000790E0  80 1F 1A 58 */	lwz r0, 0x1a58(r31)
/* 8007C504 000790E4  3B C0 00 00 */	li r30, 0
/* 8007C508 000790E8  28 00 00 00 */	cmplwi r0, 0
/* 8007C50C 000790EC  41 82 00 0C */	beq lbl_8007C518
/* 8007C510 000790F0  7C 1A 03 78 */	mr r26, r0
/* 8007C514 000790F4  48 00 00 1C */	b lbl_8007C530
lbl_8007C518:
/* 8007C518 000790F8  88 1F 22 1C */	lbz r0, 0x221c(r31)
/* 8007C51C 000790FC  54 00 FF FF */	rlwinm. r0, r0, 0x1f, 0x1f, 0x1f
/* 8007C520 00079100  41 82 00 0C */	beq lbl_8007C52C
/* 8007C524 00079104  83 5F 18 68 */	lwz r26, 0x1868(r31)
/* 8007C528 00079108  48 00 00 08 */	b lbl_8007C530
lbl_8007C52C:
/* 8007C52C 0007910C  3B 40 00 00 */	li r26, 0
lbl_8007C530:
/* 8007C530 00079110  80 6D C1 8C */	lwz r3, lbl_804D782C(r13)
/* 8007C534 00079114  3B BF 10 64 */	addi r29, r31, 0x1064
/* 8007C538 00079118  83 63 00 20 */	lwz r27, 0x20(r3)
/* 8007C53C 0007911C  48 00 00 D8 */	b lbl_8007C614
lbl_8007C540:
/* 8007C540 00079120  7C 1C D8 40 */	cmplw r28, r27
/* 8007C544 00079124  40 82 00 0C */	bne lbl_8007C550
/* 8007C548 00079128  3B C0 00 01 */	li r30, 1
/* 8007C54C 0007912C  48 00 00 C4 */	b lbl_8007C610
lbl_8007C550:
/* 8007C550 00079130  7C 1B D0 40 */	cmplw r27, r26
/* 8007C554 00079134  41 82 00 BC */	beq lbl_8007C610
/* 8007C558 00079138  80 7B 00 2C */	lwz r3, 0x2c(r27)
/* 8007C55C 0007913C  88 03 22 19 */	lbz r0, 0x2219(r3)
/* 8007C560 00079140  3B 23 00 00 */	addi r25, r3, 0
/* 8007C564 00079144  54 00 D7 FF */	rlwinm. r0, r0, 0x1a, 0x1f, 0x1f
/* 8007C568 00079148  40 82 00 A8 */	bne lbl_8007C610
/* 8007C56C 0007914C  88 19 22 27 */	lbz r0, 0x2227(r25)
/* 8007C570 00079150  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 8007C574 00079154  41 82 00 9C */	beq lbl_8007C610
/* 8007C578 00079158  7F 63 DB 78 */	mr r3, r27
/* 8007C57C 0007915C  4B FF F2 ED */	bl func_8007B868
/* 8007C580 00079160  2C 03 00 02 */	cmpwi r3, 2
/* 8007C584 00079164  41 82 00 8C */	beq lbl_8007C610
/* 8007C588 00079168  88 19 22 1F */	lbz r0, 0x221f(r25)
/* 8007C58C 0007916C  54 00 EF FF */	rlwinm. r0, r0, 0x1d, 0x1f, 0x1f
/* 8007C590 00079170  40 82 00 80 */	bne lbl_8007C610
/* 8007C594 00079174  88 19 22 1C */	lbz r0, 0x221c(r25)
/* 8007C598 00079178  54 00 FF FF */	rlwinm. r0, r0, 0x1f, 0x1f, 0x1f
/* 8007C59C 0007917C  41 82 00 10 */	beq lbl_8007C5AC
/* 8007C5A0 00079180  80 19 18 68 */	lwz r0, 0x1868(r25)
/* 8007C5A4 00079184  7C 00 E0 40 */	cmplw r0, r28
/* 8007C5A8 00079188  41 82 00 68 */	beq lbl_8007C610
lbl_8007C5AC:
/* 8007C5AC 0007918C  80 19 10 64 */	lwz r0, 0x1064(r25)
/* 8007C5B0 00079190  3B 19 10 64 */	addi r24, r25, 0x1064
/* 8007C5B4 00079194  2C 00 00 00 */	cmpwi r0, 0
/* 8007C5B8 00079198  41 82 00 58 */	beq lbl_8007C610
/* 8007C5BC 0007919C  2C 1E 00 00 */	cmpwi r30, 0
/* 8007C5C0 000791A0  41 82 00 50 */	beq lbl_8007C610
/* 8007C5C4 000791A4  C0 39 00 38 */	lfs f1, 0x38(r25)
/* 8007C5C8 000791A8  7F 03 C3 78 */	mr r3, r24
/* 8007C5CC 000791AC  C0 5F 00 38 */	lfs f2, 0x38(r31)
/* 8007C5D0 000791B0  7F A4 EB 78 */	mr r4, r29
/* 8007C5D4 000791B4  4B F8 B5 29 */	bl func_80007AFC
/* 8007C5D8 000791B8  2C 03 00 00 */	cmpwi r3, 0
/* 8007C5DC 000791BC  41 82 00 1C */	beq lbl_8007C5F8
/* 8007C5E0 000791C0  38 79 00 00 */	addi r3, r25, 0
/* 8007C5E4 000791C4  38 98 00 00 */	addi r4, r24, 0
/* 8007C5E8 000791C8  38 BF 00 00 */	addi r5, r31, 0
/* 8007C5EC 000791CC  38 DD 00 00 */	addi r6, r29, 0
/* 8007C5F0 000791D0  4B FF FC F1 */	bl func_8007C2E0
/* 8007C5F4 000791D4  48 00 00 1C */	b lbl_8007C610
lbl_8007C5F8:
/* 8007C5F8 000791D8  38 7D 00 00 */	addi r3, r29, 0
/* 8007C5FC 000791DC  38 99 00 00 */	addi r4, r25, 0
/* 8007C600 000791E0  4B F8 C3 B9 */	bl func_800089B8
/* 8007C604 000791E4  38 78 00 00 */	addi r3, r24, 0
/* 8007C608 000791E8  38 9F 00 00 */	addi r4, r31, 0
/* 8007C60C 000791EC  4B F8 C3 AD */	bl func_800089B8
lbl_8007C610:
/* 8007C610 000791F0  83 7B 00 08 */	lwz r27, 8(r27)
lbl_8007C614:
/* 8007C614 000791F4  28 1B 00 00 */	cmplwi r27, 0
/* 8007C618 000791F8  40 82 FF 28 */	bne lbl_8007C540
lbl_8007C61C:
/* 8007C61C 000791FC  BB 01 00 20 */	lmw r24, 0x20(r1)
/* 8007C620 00079200  80 01 00 44 */	lwz r0, 0x44(r1)
/* 8007C624 00079204  38 21 00 40 */	addi r1, r1, 0x40
/* 8007C628 00079208  7C 08 03 A6 */	mtlr r0
/* 8007C62C 0007920C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop
