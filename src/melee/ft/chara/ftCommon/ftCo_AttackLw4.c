#include <platform.h>

#include "forward.h"
#include <dolphin/mtx/forward.h>

#include "ftCo_AttackLw4.h"

#include "ftCo_Wait.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ft_0D14.h"
#include "ft/ftanim.h"
#include "ft/types.h"
#include "ftCommon/ftCo_ItemThrow.h"
#include "ftNess/ftNs_AttackLw4.h"

#include <common_structs.h>

/* 08CC5C */ static void doEnter(ftCo_GObj* gobj);

static bool checkLStick(ftCo_Fighter* fp)
{
    if (fp->input.x668 & HSD_PAD_A &&
        fp->input.lstick.y <= p_ftCommonData->xD4 &&
        fp->x671_timer_lstick_tilt_y < p_ftCommonData->xD8)
    {
        return true;
    }
    return false;
}

bool ftCo_AttackLw4_CheckInput(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    if (checkLStick(fp) || ftCo_800DF3A8(fp)) {
        if (fp->item_gobj != NULL && (ftCo_80094E54(fp) || ftCo_800DF3DC(fp)))
        {
            ftCo_800957F4(gobj, ftCo_MS_LightThrowLw4);
            return true;
        }
        switch (fp->kind) {
        case FTKIND_NESS:
            ftNs_AttackLw4_Enter(gobj);
            break;
        default:
            doEnter(gobj);
        }
        return true;
    }
    return false;
}

void doEnter(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    fp->allow_interrupt = false;
    Fighter_ChangeMotionState(gobj, ftCo_MS_AttackLw4, Ft_MF_None, 0, 1, 0,
                              NULL);
    ftAnim_8006EBA4(gobj);
}

void ftCo_AttackLw4_Anim(ftCo_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftCo_AttackLw4_IASA(ftCo_GObj* gobj)
{
    if (GET_FIGHTER(gobj)->allow_interrupt) {
        ftCo_Wait_IASA(gobj);
    }
}

void ftCo_AttackLw4_Phys(ftCo_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftCo_AttackLw4_Coll(ftCo_GObj* gobj)
{
    ft_80084104(gobj);
}
