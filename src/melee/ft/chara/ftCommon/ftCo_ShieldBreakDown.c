#include <platform.h>

#include "ftCo_ShieldBreakDown.h"

#include "ftCo_DownBound.h"

#include "ft/fighter.h"
#include "ft/ftcommon.h"

#include <placeholder.h>

float const ftCo_804D8660 = 0;
float const ftCo_804D8664 = 1;

#ifdef MWERKS_GEKKO
#pragma push
asm /* 098E3C */ void ftCo_80098E3C(ftCo_GObj*, float lag)
{ // clang-format off
    nofralloc
/* 80098E3C 00095A1C  7C 08 02 A6 */	mflr r0
/* 80098E40 00095A20  90 01 00 04 */	stw r0, 4(r1)
/* 80098E44 00095A24  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80098E48 00095A28  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80098E4C 00095A2C  7C 7F 1B 78 */	mr r31, r3
/* 80098E50 00095A30  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 80098E54 00095A34  80 03 00 E0 */	lwz r0, 0xe0(r3)
/* 80098E58 00095A38  2C 00 00 01 */	cmpwi r0, 1
/* 80098E5C 00095A3C  40 82 00 08 */	bne lbl_80098E64
/* 80098E60 00095A40  4B FE 49 9D */	bl ftCommon_8007D7FC
lbl_80098E64:
/* 80098E64 00095A44  7F E3 FB 78 */	mr r3, r31
/* 80098E68 00095A48  4B FF E7 09 */	bl ftCo_80097570
/* 80098E6C 00095A4C  2C 03 00 00 */	cmpwi r3, 0
/* 80098E70 00095A50  41 82 00 0C */	beq lbl_80098E7C
/* 80098E74 00095A54  38 00 00 CF */	li r0, 0xcf
/* 80098E78 00095A58  48 00 00 08 */	b lbl_80098E80
lbl_80098E7C:
/* 80098E7C 00095A5C  38 00 00 D0 */	li r0, 0xd0
lbl_80098E80:
/* 80098E80 00095A60  C0 22 8C 80 */	lfs f1, ftCo_804D8660
/* 80098E84 00095A64  7C 04 03 78 */	mr r4, r0
/* 80098E88 00095A68  C0 42 8C 84 */	lfs f2, ftCo_804D8664
/* 80098E8C 00095A6C  7F E3 FB 78 */	mr r3, r31
/* 80098E90 00095A70  FC 60 08 90 */	fmr f3, f1
/* 80098E94 00095A74  38 A0 10 94 */	li r5, 0x1094
/* 80098E98 00095A78  38 C0 00 00 */	li r6, 0
/* 80098E9C 00095A7C  4B FD 05 11 */	bl Fighter_ChangeMotionState
/* 80098EA0 00095A80  7F E3 FB 78 */	mr r3, r31
/* 80098EA4 00095A84  4B FF EA 31 */	bl ftCo_800978D4
/* 80098EA8 00095A88  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80098EAC 00095A8C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80098EB0 00095A90  38 21 00 18 */	addi r1, r1, 0x18
/* 80098EB4 00095A94  7C 08 03 A6 */	mtlr r0
/* 80098EB8 00095A98  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif
