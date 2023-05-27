#include <platform.h>

#include "ftCo_ShieldBreakStand.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_08A4.h"

#include <placeholder.h>

float const ftCo_804D8668 = 0;
float const ftCo_804D866C = 1;

#ifdef MWERKS_GEKKO
#pragma push
asm void ftCo_80098F3C(ftCo_GObj*)
{ // clang-format off
    nofralloc
/* 80098F3C 00095B1C  7C 08 02 A6 */	mflr r0
/* 80098F40 00095B20  90 01 00 04 */	stw r0, 4(r1)
/* 80098F44 00095B24  94 21 FF F8 */	stwu r1, -8(r1)
/* 80098F48 00095B28  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 80098F4C 00095B2C  80 04 00 10 */	lwz r0, 0x10(r4)
/* 80098F50 00095B30  2C 00 00 CF */	cmpwi r0, 0xcf
/* 80098F54 00095B34  40 82 00 0C */	bne lbl_80098F60
/* 80098F58 00095B38  38 00 00 D1 */	li r0, 0xd1
/* 80098F5C 00095B3C  48 00 00 08 */	b lbl_80098F64
lbl_80098F60:
/* 80098F60 00095B40  38 00 00 D2 */	li r0, 0xd2
lbl_80098F64:
/* 80098F64 00095B44  C0 22 8C 88 */	lfs f1, ftCo_804D8668
/* 80098F68 00095B48  7C 04 03 78 */	mr r4, r0
/* 80098F6C 00095B4C  C0 42 8C 8C */	lfs f2, ftCo_804D866C
/* 80098F70 00095B50  38 A0 10 94 */	li r5, 0x1094
/* 80098F74 00095B54  FC 60 08 90 */	fmr f3, f1
/* 80098F78 00095B58  38 C0 00 00 */	li r6, 0
/* 80098F7C 00095B5C  4B FD 04 31 */	bl Fighter_ChangeMotionState
/* 80098F80 00095B60  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80098F84 00095B64  38 21 00 08 */	addi r1, r1, 8
/* 80098F88 00095B68  7C 08 03 A6 */	mtlr r0
/* 80098F8C 00095B6C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void ftCo_ShieldBreakStand_Anim(ftCo_GObj*)
{ // clang-format off
    nofralloc
/* 80098F90 00095B70  7C 08 02 A6 */	mflr r0
/* 80098F94 00095B74  90 01 00 04 */	stw r0, 4(r1)
/* 80098F98 00095B78  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80098F9C 00095B7C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80098FA0 00095B80  7C 7F 1B 78 */	mr r31, r3
/* 80098FA4 00095B84  4B FD 62 95 */	bl ftAnim_IsFramesRemaining
/* 80098FA8 00095B88  2C 03 00 00 */	cmpwi r3, 0
/* 80098FAC 00095B8C  40 82 00 0C */	bne lbl_80098FB8
/* 80098FB0 00095B90  7F E3 FB 78 */	mr r3, r31
/* 80098FB4 00095B94  48 00 00 5D */	bl ftCo_80099010
lbl_80098FB8:
/* 80098FB8 00095B98  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80098FBC 00095B9C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80098FC0 00095BA0  38 21 00 18 */	addi r1, r1, 0x18
/* 80098FC4 00095BA4  7C 08 03 A6 */	mtlr r0
/* 80098FC8 00095BA8  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

void ftCo_ShieldBreakStand_IASA(HSD_GObj* gobj) {}

#ifdef MWERKS_GEKKO
#pragma push
asm void ftCo_ShieldBreakStand_Phys(ftCo_GObj*)
{ // clang-format off
    nofralloc
/* 80098FD0 00095BB0  7C 08 02 A6 */	mflr r0
/* 80098FD4 00095BB4  90 01 00 04 */	stw r0, 4(r1)
/* 80098FD8 00095BB8  94 21 FF F8 */	stwu r1, -8(r1)
/* 80098FDC 00095BBC  4B FE BF 61 */	bl ft_80084F3C
/* 80098FE0 00095BC0  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80098FE4 00095BC4  38 21 00 08 */	addi r1, r1, 8
/* 80098FE8 00095BC8  7C 08 03 A6 */	mtlr r0
/* 80098FEC 00095BCC  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void ftCo_ShieldBreakStand_Coll(ftCo_GObj*)
{ // clang-format off
    nofralloc
/* 80098FF0 00095BD0  7C 08 02 A6 */	mflr r0
/* 80098FF4 00095BD4  90 01 00 04 */	stw r0, 4(r1)
/* 80098FF8 00095BD8  94 21 FF F8 */	stwu r1, -8(r1)
/* 80098FFC 00095BDC  4B FE AF 8D */	bl ft_80083F88
/* 80099000 00095BE0  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80099004 00095BE4  38 21 00 08 */	addi r1, r1, 8
/* 80099008 00095BE8  7C 08 03 A6 */	mtlr r0
/* 8009900C 00095BEC  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif
