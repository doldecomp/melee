
#include <platform.h>
#include "ft/forward.h"
#include "ftCommon/forward.h"

#include "ftCo_AttackHi4.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_08A4.h"
#include "ftNess/ftNs_AttackHi4.h"

/* 08CA38 */ void doEnter(ftCo_GObj* gobj);

static bool checkLStick(ftCo_Fighter* fp)
{
    if (fp->input.x668 & HSD_Pad_A &&
        fp->input.lstick.y >= p_ftCommonData->xCC &&
        fp->x671_timer_lstick_tilt_y < p_ftCommonData->xD0)
    {
        return true;
    } else {
        return false;
    }
}

bool ftCo_AttackHi4_CheckInput(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    if (checkLStick(fp) || ft_800DF2D8(fp)) {
        if (fp->item_gobj != NULL && (ft_80094E54(fp) || ft_800DF30C(fp))) {
            ft_800957F4(gobj, ftCo_MS_LightThrowHi4);
            return true;
        }
        switch (fp->kind) {
        case FTKIND_NESS:
            ftNs_AttackHi4_Enter(gobj);
            break;
        default:
            doEnter(gobj);
            break;
        }
        return true;
    }
    return false;
}

static bool checkLStickNoD0(ftCo_Fighter* fp)
{
    if (fp->input.x668 & HSD_Pad_A &&
        fp->input.lstick.y >= p_ftCommonData->xCC)
    {
        return true;
    } else {
        return false;
    }
}

bool ftCo_AttackHi4_CheckInputNoD0(HSD_GObj* gobj)
{
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    if (checkLStickNoD0(fp) || ft_800DF2D8(fp)) {
        if (fp->item_gobj != NULL && (ft_80094E54(fp) || ft_800DF30C(fp))) {
            ft_800957F4(gobj, ftCo_MS_LightThrowHi4);
            return true;
        }
        switch (fp->kind) {
        case FTKIND_NESS:
            ftNs_AttackHi4_Enter(gobj);
            break;
        default:
            doEnter(gobj);
            break;
        }
        return true;
    }
    return false;
}

void doEnter(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    fp->allow_interrupt = false;
    Fighter_ChangeMotionState(gobj, ftCo_MS_AttackHi4, Ft_MF_None, NULL, 0, 1,
                              0);
    ftAnim_8006EBA4(gobj);
}

void ftCo_AttackHi4_Anim(ftCo_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftCo_AttackHi4_IASA(HSD_GObj* gobj)
{
    if (GET_FIGHTER(gobj)->allow_interrupt) {
        ftCo_Wait_IASA(gobj);
    }
}

void ftCo_AttackHi4_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftCo_AttackHi4_Coll(HSD_GObj* gobj)
{
    ft_80084104(gobj);
}
