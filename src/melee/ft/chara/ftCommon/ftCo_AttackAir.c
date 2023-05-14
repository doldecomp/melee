#include <platform.h>
#include "ft/forward.h"
#include "ftCommon/forward.h"

#include "ftCo_AttackAir.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_08A4.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ftGameWatch/ftGw_AttackAir.h"
#include "ftLink/ftLk_AttackAir.h"

#include <common_structs.h>
#include <placeholder.h>

/* 08CE0C */ static void decideFighter(ftCo_GObj* gobj);

/// @todo This probably doesn't exist; see #ftCo_AttackAir_CheckItemThrowInput.
static bool checkItemThrowInput(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    if (fp->input.x668 & HSD_Pad_A || ft_800DF478(fp)) {
        if ((unsigned) ftCo_AttackAir_GetMsidFromCStick(fp) -
                    ftCo_MS_AttackAirN <=
                1 &&
            fp->item_gobj != NULL && it_8026B30C(fp->item_gobj) == 3)
        {
            ft_800CDDA0(gobj);
            return true;
        } else {
            decideFighter(gobj);
            return true;
        }
    } else {
        return false;
    }
}

/**
 * @todo This is exactly #checkItemThrowInput but it uses too much stack for
 *       #ftCo_AttackAirLw_IASA to call it.
 */
bool ftCo_AttackAir_CheckItemThrowInput(ftCo_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    if (fp->input.x668 & HSD_Pad_A || ft_800DF478(fp)) {
        if ((unsigned) ftCo_AttackAir_GetMsidFromCStick(fp) -
                    ftCo_MS_AttackAirN <=
                1 &&
            fp->item_gobj != NULL && it_8026B30C(fp->item_gobj) == 3)
        {
            ft_800CDDA0(gobj);
            return true;
        } else {
            decideFighter(gobj);
            return true;
        }
    } else {
        return false;
    }
}

void decideFighter(ftCo_GObj* gobj)
{
    switch (GET_FIGHTER(gobj)->kind) {
    case FTKIND_LINK:
    case FTKIND_CLINK:
        ftLk_AttackAir_Enter(gobj);
        return;
    case FTKIND_GAMEWATCH:
        ftGw_AttackAirN_DecideAction(gobj);
        return;
    default:
        ftCo_AttackAir_EnterFromCStick(gobj);
        return;
    }
}

FtMotionId ftCo_AttackAir_GetMsidFromCStick(Fighter* fp)
{
    float stick_angle, stick_x, stick_y;
    if (ft_800DF478(fp)) {
        stick_x = fp->input.cstick.x;
        stick_y = fp->input.cstick.y;
        stick_angle = ftCo_GetCStickAngle(fp);
    } else {
        stick_x = fp->input.lstick.x;
        stick_y = fp->input.lstick.y;
        stick_angle = ftCo_GetLStickAngle(fp);
    }
    if (ABS(stick_x) < p_ftCommonData->xDC &&
        ABS(stick_y) < p_ftCommonData->xE0)
    {
        return ftCo_MS_AttackAirN;
    }
    if (stick_angle > p_ftCommonData->x20) {
        return ftCo_MS_AttackAirHi;
    }
    if (stick_angle < -p_ftCommonData->x20) {
        return ftCo_MS_AttackAirLw;
    }
    if (stick_x * fp->facing_dir >= 0) {
        return ftCo_MS_AttackAirF;
    }
    return ftCo_MS_AttackAirB;
}

void ftCo_AttackAir_EnterFromCStick(ftCo_GObj* gobj)
{
    ftCo_AttackAir_EnterFromMsid(
        gobj, ftCo_AttackAir_GetMsidFromCStick(GET_FIGHTER(gobj)));
}

void ftCo_AttackAir_EnterFromMsid(ftCo_GObj* gobj, FtMotionId msid)
{
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    fp->allow_interrupt = false;
    fp->cmd_vars[0] = 0;
    fp->throw_flags.flags = 0;
    Fighter_ChangeMotionState(gobj, msid, Ft_MF_KeepFastFall, NULL, 0, 1, 0);
    ftAnim_8006EBA4(gobj);
}

void ftCo_AttackAir_Anim(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    if (ftCheckThrowB3(fp)) {
        fp->facing_dir = -fp->facing_dir;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_800CC730(gobj);
    }
}

/// @remarks Trying to use an @c inline function breaks inlining.
#define DO_IASA(gobj)                                                         \
    if (GET_FIGHTER(gobj)->allow_interrupt) {                                 \
        RETURN_IF(ft_80095328(gobj, false))                                   \
        RETURN_IF(ftCo_800D7100(gobj))                                        \
        RETURN_IF(ftCo_800C3B10(gobj))                                        \
        RETURN_IF(checkItemThrowInput(gobj))                                  \
        RETURN_IF(ftCo_800D705C(gobj))                                        \
        RETURN_IF(ft_800CB870(gobj))                                          \
    }

void ftCo_AttackAirN_IASA(ftCo_GObj* gobj)
{
    DO_IASA(gobj);
}

void ftCo_AttackAirF_IASA(ftCo_GObj* gobj)
{
    DO_IASA(gobj);
}

void ftCo_AttackAirB_IASA(ftCo_GObj* gobj)
{
    DO_IASA(gobj);
}

void ftCo_AttackAirHi_IASA(ftCo_GObj* gobj)
{
    DO_IASA(gobj);
}

void ftCo_AttackAirLw_IASA(ftCo_GObj* gobj)
{
    DO_IASA(gobj);
}

#undef DO_IASA

void ftCo_AttackAir_Phys(ftCo_GObj* gobj)
{
    ft_80084DB0(gobj);
}

void ftCo_AttackAir_Coll(ftCo_GObj* gobj)
{
    ft_80082C74(gobj, ft_8008D5FC);
}
