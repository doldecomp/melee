#include <platform.h>
#include "ft/forward.h"
#include "ftCommon/forward.h"
#include <baselib/forward.h>

#include "ftCo_AttackLw3.h"

#include "ftCo_Attack1.h"
#include "ftCo_AttackHi3.h"
#include "ftCo_AttackHi4.h"
#include "ftCo_AttackS3.h"
#include "ftCo_AttackS4.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_08A4.h"
#include "ft/ftcommon.h"
#include "ftGameWatch/ftGw_AttackLw3.h"

#include <placeholder.h>

typedef enum cmd_var_idx {
    cmd_unk0_bool,
} cmd_var_idx;

/* 08BC00 */ static void callUnk(ftCo_GObj* gobj);
/* 08BC34 */ static void decideFighter(ftCo_GObj* gobj);
/* 08BC70 */ static void doEnter(ftCo_GObj* gobj);

bool ftCo_AttackLw3_CheckInput(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    if (fp->input.x668 & HSD_Pad_A) {
        if (fp->input.lstick.y <= p_ftCommonData->xB0 &&
            ftCo_GetLStickAngle(fp) < -p_ftCommonData->x20)
        {
            if (fp->item_gobj != NULL && ft_80094E54(fp)) {
                ft_800957F4(gobj, ftCo_MS_LightThrowLw);
                return true;
            }
            decideFighter(gobj);
            return true;
        }
    }
    return false;
}

void callUnk(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    ft_800892A0(gobj);
    ft_80089824(gobj);
}

void decideFighter(HSD_GObj* gobj)
{
    switch (GET_FIGHTER(gobj)->kind) {
    case FTKIND_GAMEWATCH:
        ftGw_AttackLw3_Enter(gobj);
        return;
    default:
        doEnter(gobj);
        return;
    }
}

static void doEnter(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    if (!ft_80094790(gobj)) {
        fp->cmd_vars[cmd_unk0_bool] = false;
        fp->allow_interrupt = false;
        fp->mv.co.attacklw3.x0 = 0;
        fp->cb.x21EC_callback = callUnk;
        Fighter_ChangeMotionState(gobj, ftCo_MS_AttackLw3,
                                  Ft_MF_SkipAttackCount, NULL, 0, 1, 0);
        ftAnim_8006EBA4(gobj);
    }
}

/// @todo This is fake.
static void wrapper(ftCo_GObj* gobj)
{
    decideFighter(gobj);
}

void ftCo_AttackLw3_Anim(HSD_GObj* gobj)
{
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    if (fp->cmd_vars[cmd_unk0_bool] && fp->mv.co.attacklw3.x0) {
        wrapper(gobj);
        return;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_800D638C(gobj);
    }
}

static bool checkPadA(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    if (fp->input.x668 & HSD_Pad_A) {
        if (fp->cmd_vars[cmd_unk0_bool]) {
            decideFighter(gobj);
            return true;
        }
        fp->mv.co.attacklw3.x0 = true;
    }
    return false;
}

static bool checkItemThrowInput(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    if (fp->input.x668 & HSD_Pad_A &&
        fp->input.lstick.y <= p_ftCommonData->xB0 &&
        ftCo_GetLStickAngle(fp) < -p_ftCommonData->x20)
    {
        if (fp->item_gobj != NULL && ft_80094E54(fp)) {
            ft_800957F4(gobj, ftCo_MS_LightThrowLw);
            return true;
        }
        decideFighter(gobj);
        return true;
    }
    return false;
}

void ftCo_AttackLw3_IASA(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    if (fp->allow_interrupt) {
        RETURN_IF(ftCo_AttackS4_CheckInput(gobj))
        RETURN_IF(ftCo_AttackHi4_CheckInput(gobj))
        RETURN_IF(ftCo_AttackLw4_CheckInput(gobj))
        RETURN_IF(ftCo_AttackS3_CheckInput(gobj))
        RETURN_IF(ftCo_AttackHi3_CheckInput(gobj))
    }
    RETURN_IF(checkPadA(gobj))
    if (fp->allow_interrupt) {
        RETURN_IF(checkItemThrowInput(gobj))
        RETURN_IF(ftCo_Attack1_CheckInput(gobj))
        RETURN_IF(ftCo_Jump_CheckInput(gobj))
        RETURN_IF(ftCo_Dash_CheckInput(gobj))
        RETURN_IF(ftCo_Squat_CheckInput(gobj))
        RETURN_IF(ftCo_Turn_CheckInput(gobj))
        RETURN_IF(ftCo_Walk_CheckInput(gobj))
    }
}

void ftCo_AttackLw3_Phys(ftCo_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftCo_AttackLw3_Coll(ftCo_GObj* gobj)
{
    ft_80084104(gobj);
}
