#include <platform.h>
#include "forward.h"
#include "ft/forward.h"

#include "ftPe_Float.h"

#include "ftPe_FloatAttack.h"
#include "ftPe_FloatFall.h"
#include "ftPe_Init.h"

#include "ef/efasync.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ftCommon/ftCo_FallSpecial.h"
#include "ftCommon/ftCo_SpecialAir.h"
#include "ftPeach/types.h"

#include <common_structs.h>
#include <baselib/gobj.h>

bool ftPe_Float_CheckContinueInput(Fighter* fp)
{
    return fp->input.lstick.y >= p_ftCommonData->x70_someLStickYMax ||
           fp->input.held_inputs & HSD_PAD_XY;
}

static bool checkStartFloatInput(HSD_GObj* gobj)
{
    Fighter* temp_r6 = GET_FIGHTER(gobj);
    return temp_r6->input.lstick.y <= -p_ftCommonData->x88 &&
           temp_r6->input.held_inputs & HSD_PAD_XY;
}

bool ftPe_8011BA54(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    bool float_input = checkStartFloatInput(gobj);
    if (fp->kind == FTKIND_PEACH && fp->fv.pe.has_float && float_input) {
        ftPe_8011BB6C(gobj, true);
        return true;
    }
    return false;
}

bool ftPe_8011BAD8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->kind == FTKIND_PEACH) {
        if (fp->self_vel.y <= 0 && fp->fv.pe.has_float) {
            if (ftPe_Float_CheckContinueInput(fp)) {
                ftPe_8011BB6C(gobj, true);
                return true;
            }
        }
    }
    return false;
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftPe_8011BB6C(HSD_GObj*, bool)
{ // clang-format off
    nofralloc
/* 8011BB6C 0011874C  7C 08 02 A6 */	mflr r0
/* 8011BB70 00118750  38 A0 00 00 */	li r5, 0
/* 8011BB74 00118754  90 01 00 04 */	stw r0, 4(r1)
/* 8011BB78 00118758  38 C0 00 00 */	li r6, 0
/* 8011BB7C 0011875C  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8011BB80 00118760  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 8011BB84 00118764  93 C1 00 28 */	stw r30, 0x28(r1)
/* 8011BB88 00118768  93 A1 00 24 */	stw r29, 0x24(r1)
/* 8011BB8C 0011876C  7C 9D 23 78 */	mr r29, r4
/* 8011BB90 00118770  38 80 01 55 */	li r4, 0x155
/* 8011BB94 00118774  93 81 00 20 */	stw r28, 0x20(r1)
/* 8011BB98 00118778  7C 7C 1B 78 */	mr r28, r3
/* 8011BB9C 0011877C  C0 22 9D E0 */	lfs f1, 0.0
/* 8011BBA0 00118780  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8011BBA4 00118784  FC 60 08 90 */	fmr f3, f1
/* 8011BBA8 00118788  C0 42 9D E4 */	lfs f2, 1.0
/* 8011BBAC 0011878C  83 DF 02 D4 */	lwz r30, 0x2d4(r31)
/* 8011BBB0 00118790  4B F4 D7 FD */	bl Fighter_ChangeMotionState
/* 8011BBB4 00118794  38 00 00 00 */	li r0, 0
/* 8011BBB8 00118798  2C 1D 00 00 */	cmpwi r29, 0
/* 8011BBBC 0011879C  90 1F 22 2C */	stw r0, 0x222c(r31)
/* 8011BBC0 001187A0  41 82 00 0C */	beq lbl_8011BBCC
/* 8011BBC4 001187A4  C0 1E 00 0C */	lfs f0, 0xc(r30)
/* 8011BBC8 001187A8  D0 1F 22 30 */	stfs f0, 0x2230(r31)
lbl_8011BBCC:
/* 8011BBCC 001187AC  C0 02 9D E0 */	lfs f0, 0.0
/* 8011BBD0 001187B0  38 A0 00 01 */	li r5, 1
/* 8011BBD4 001187B4  38 7F 00 00 */	addi r3, r31, 0
/* 8011BBD8 001187B8  D0 1F 00 84 */	stfs f0, 0x84(r31)
/* 8011BBDC 001187BC  38 80 00 01 */	li r4, 1
/* 8011BBE0 001187C0  88 1F 22 19 */	lbz r0, 0x2219(r31)
/* 8011BBE4 001187C4  50 A0 3E 30 */	rlwimi r0, r5, 7, 0x18, 0x18
/* 8011BBE8 001187C8  98 1F 22 19 */	stb r0, 0x2219(r31)
/* 8011BBEC 001187CC  4B F5 94 21 */	bl ftParts_8007500C
/* 8011BBF0 001187D0  80 9F 05 E8 */	lwz r4, 0x5e8(r31)
/* 8011BBF4 001187D4  54 60 20 36 */	slwi r0, r3, 4
/* 8011BBF8 001187D8  80 BC 00 2C */	lwz r5, 0x2c(r28)
/* 8011BBFC 001187DC  7F 83 E3 78 */	mr r3, r28
/* 8011BC00 001187E0  7C E4 00 2E */	lwzx r7, r4, r0
/* 8011BC04 001187E4  38 85 06 0C */	addi r4, r5, 0x60c
/* 8011BC08 001187E8  4C C6 31 82 */	crclr 6
/* 8011BC0C 001187EC  38 A0 00 00 */	li r5, 0
/* 8011BC10 001187F0  38 C0 04 D4 */	li r6, 0x4d4
/* 8011BC14 001187F4  4B F4 BA DD */	bl efAsync_Spawn
/* 8011BC18 001187F8  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8011BC1C 001187FC  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 8011BC20 00118800  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 8011BC24 00118804  83 A1 00 24 */	lwz r29, 0x24(r1)
/* 8011BC28 00118808  83 81 00 20 */	lwz r28, 0x20(r1)
/* 8011BC2C 0011880C  38 21 00 30 */	addi r1, r1, 0x30
/* 8011BC30 00118810  7C 08 03 A6 */	mtlr r0
/* 8011BC34 00118814  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftPe_8011BB6C(HSD_GObj* gobj, bool arg1)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif
    Fighter* fp = GET_FIGHTER(gobj);
    ftPe_DatAttrs* da = fp->dat_attrs;
    Fighter_ChangeMotionState(gobj, ftPe_MS_Float, 0, 0, 1, 0, NULL);
    fp->fv.pe.has_float = false;
    if (arg1) {
        fp->fv.pe.x4 = da->xC;
    }
    fp->self_vel.y = 0;
    fp->x2219_b0 = true;
    efAsync_Spawn(gobj, &fp->x60C, 0, 1236,
                  fp->parts[ftParts_8007500C(fp, FtPart_TransN)].joint);
}
#endif

void ftPe_Float_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.pe.x4 > 0) {
        fp->fv.pe.x4 -= 1;
    }
    if (fp->fv.pe.x4 <= 0) {
        updateFloatDir(gobj);
    }
}

void ftPe_Float_IASA(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (!ftCo_SpecialAir_CheckInput(gobj) && !ftPe_8011BE80(gobj)) {
        /// @todo Call #checkContinueFloatInput
        bool float_input =
            fp->input.lstick.y >= p_ftCommonData->x70_someLStickYMax ||
            fp->input.held_inputs & HSD_PAD_XY;
        if (!float_input) {
            updateFloatDir(gobj);
        }
    }
}

void ftPe_Float_Phys(HSD_GObj* gobj)
{
    ftCommon_8007D268(GET_FIGHTER(gobj));
}

void ftPe_Float_Coll(HSD_GObj* gobj)
{
    ft_800831CC(gobj, ftCo_80096CC8, ft_80082B1C);
}
