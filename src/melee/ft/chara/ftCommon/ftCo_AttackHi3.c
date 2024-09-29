#include <platform.h>

#include "forward.h"
#include <dolphin/mtx/forward.h>

#include "ftCo_AttackHi3.h"

#include "ftCo_ItemThrow.h"
#include "ftCo_Wait.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/types.h"

#include <common_structs.h>

/* 08BA38 */ static void doEnter(ftCo_GObj* gobj);

bool ftCo_AttackHi3_CheckInput(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    if (fp->input.x668 & HSD_PAD_A) {
        if (fp->input.lstick.y >=
                p_ftCommonData->attackhi3_stick_threshold_y &&
            ftCo_GetLStickAngle(fp) > p_ftCommonData->x20)
        {
            if (fp->item_gobj != NULL && ftCo_80094E54(fp)) {
                ftCo_800957F4(gobj, ftCo_MS_LightThrowHi);
                return true;
            }
            doEnter(gobj);
            return true;
        }
    }
    return false;
}

void doEnter(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    fp->allow_interrupt = false;
    Fighter_ChangeMotionState(gobj, ftCo_MS_AttackHi3, Ft_MF_None, 0, 1, 0,
                              NULL);
    ftAnim_8006EBA4(gobj);
}

void ftCo_AttackHi3_Anim(ftCo_GObj* arg0)
{
    if (!ftAnim_IsFramesRemaining(arg0)) {
        ft_8008A2BC(arg0);
    }
}

void ftCo_AttackHi3_IASA(ftCo_GObj* gobj)
{
    if (GET_FIGHTER(gobj)->allow_interrupt) {
        ftCo_Wait_IASA(gobj);
    }
}

void ftCo_AttackHi3_Phys(ftCo_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftCo_AttackHi3_Coll(ftCo_GObj* gobj)
{
    ft_80084104(gobj);
}
