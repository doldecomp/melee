#include "ftcrazyhandsweep.h"

#include "ftcrazyhandtagcancel.h"

#include <sysdolphin/baselib/forward.h>

#include <melee/ft/fighter.h>
#include <melee/ft/ft_084E.h>
#include <melee/ft/ftbosslib.h>
#include <melee/ft/inlines.h>
#include <melee/ft/kinds/ftMasterHand/types.h>
#include <melee/ft/types.h>
#include <melee/pl/player.h>
#include <Runtime/platform.h>

void fn_8015746C(HSD_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, ftMh_MS_SweepLoop, 0, 0.0f, 1.0f, 0.0f,
                              NULL);
    ftAnim_8006EBA4(gobj);
}

void ftCh_SweepLoop_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}

void ftCh_SweepLoop_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_SweepLoop_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_SweepLoop_Coll(HSD_GObj* gobj) {}
