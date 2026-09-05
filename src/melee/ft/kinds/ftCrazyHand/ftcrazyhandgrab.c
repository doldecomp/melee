#include "ftcrazyhandgrab.h"

#include "ftcrazyhandcancel.h"

#include <sysdolphin/baselib/forward.h>

#include <melee/ft/fighter.h>
#include <melee/ft/ft_084E.h>
#include <melee/ft/ftbosslib.h>
#include <melee/ft/inlines.h>
#include <melee/ft/kinds/ftMasterHand/types.h>
#include <melee/ft/types.h>
#include <melee/pl/player.h>
#include <Runtime/platform.h>

void ftCh_Init_80159F40(HSD_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, ftMh_MS_Grab, 0, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
}

void ftCh_Grab_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCh_Init_8015A030(gobj);
    }
}

void ftCh_Grab_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_Grab_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_Grab_Coll(HSD_GObj* gobj) {}
