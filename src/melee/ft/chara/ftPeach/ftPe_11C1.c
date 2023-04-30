#include <platform.h>

#include "ftPe_11C1.h"

#include "ft/fighter.h"
#include "ft/ftanim.h"

#include <baselib/gobj.h>

#ifdef MWERKS_GEKKO
#pragma push
asm void ftPe_8011C1C0(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 8011C1C0 00118DA0  7C 08 02 A6 */	mflr r0
/* 8011C1C4 00118DA4  90 01 00 04 */	stw r0, 4(r1)
/* 8011C1C8 00118DA8  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8011C1CC 00118DAC  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8011C1D0 00118DB0  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8011C1D4 00118DB4  7C 7E 1B 78 */	mr r30, r3
/* 8011C1D8 00118DB8  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8011C1DC 00118DBC  38 60 00 00 */	li r3, 0
/* 8011C1E0 00118DC0  88 1F 22 18 */	lbz r0, 0x2218(r31)
/* 8011C1E4 00118DC4  50 60 3E 30 */	rlwimi r0, r3, 7, 0x18, 0x18
/* 8011C1E8 00118DC8  98 1F 22 18 */	stb r0, 0x2218(r31)
/* 8011C1EC 00118DCC  90 7F 22 00 */	stw r3, 0x2200(r31)
lbl_8011C1F0:
/* 8011C1F0 00118DD0  38 60 00 03 */	li r3, 3
/* 8011C1F4 00118DD4  48 26 43 8D */	bl HSD_Randi
/* 8011C1F8 00118DD8  80 1F 22 34 */	lwz r0, 0x2234(r31)
/* 8011C1FC 00118DDC  38 83 01 5D */	addi r4, r3, 0x15d
/* 8011C200 00118DE0  7C 04 00 00 */	cmpw r4, r0
/* 8011C204 00118DE4  41 82 FF EC */	beq lbl_8011C1F0
/* 8011C208 00118DE8  90 9F 22 34 */	stw r4, 0x2234(r31)
/* 8011C20C 00118DEC  7F C3 F3 78 */	mr r3, r30
/* 8011C210 00118DF0  38 A0 00 00 */	li r5, 0
/* 8011C214 00118DF4  C0 22 9D F8 */	lfs f1, 0.0f
/* 8011C218 00118DF8  38 C0 00 00 */	li r6, 0
/* 8011C21C 00118DFC  C0 42 9D FC */	lfs f2, 1.0f
/* 8011C220 00118E00  FC 60 08 90 */	fmr f3, f1
/* 8011C224 00118E04  4B F4 D1 89 */	bl Fighter_ChangeMotionState
/* 8011C228 00118E08  7F C3 F3 78 */	mr r3, r30
/* 8011C22C 00118E0C  4B F5 29 79 */	bl ftAnim_8006EBA4
/* 8011C230 00118E10  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8011C234 00118E14  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8011C238 00118E18  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8011C23C 00118E1C  38 21 00 18 */	addi r1, r1, 0x18
/* 8011C240 00118E20  7C 08 03 A6 */	mtlr r0
/* 8011C244 00118E24  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif
