#include "ftCo_AttackHi4.h"

#include "ftCo_ItemThrow.h"
#include "ftCo_Wait.h"

#include <platform.h>

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ft_0DF1.h"
#include "ft/ftanim.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

#include "ftNess/ftNs_AttackHi4.h"

#include <baselib/forward.h>

#include <common_structs.h>
#include <dolphin/mtx.h>

/* 08CA38 */ void doEnter(Fighter_GObj* gobj);

static bool checkLStick(Fighter* fp)
{
    if (fp->input.x668 & HSD_PAD_A &&
        fp->input.lstick.y >= p_ftCommonData->xCC &&
        fp->x671_timer_lstick_tilt_y < p_ftCommonData->xD0)
    {
        return true;
    } else {
        return false;
    }
}

bool ftCo_AttackHi4_CheckInput(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (checkLStick(fp) || ftCo_800DF2D8(fp)) {
        if (fp->item_gobj != NULL && (ftCo_80094E54(fp) || ftCo_800DF30C(fp)))
        {
            ftCo_800957F4(gobj, ftCo_MS_LightThrowHi4);
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

static bool checkLStickNoD0(Fighter* fp)
{
    if (fp->input.x668 & HSD_PAD_A &&
        fp->input.lstick.y >= p_ftCommonData->xCC)
    {
        return true;
    } else {
        return false;
    }
}

bool ftCo_AttackHi4_CheckInputNoD0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (checkLStickNoD0(fp) || ftCo_800DF2D8(fp)) {
        if (fp->item_gobj != NULL && (ftCo_80094E54(fp) || ftCo_800DF30C(fp)))
        {
            ftCo_800957F4(gobj, ftCo_MS_LightThrowHi4);
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

void doEnter(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->allow_interrupt = false;
    Fighter_ChangeMotionState(gobj, ftCo_MS_AttackHi4, Ft_MF_None, 0, 1, 0,
                              NULL);
    ftAnim_8006EBA4(gobj);
}

void ftCo_AttackHi4_Anim(Fighter_GObj* gobj)
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
