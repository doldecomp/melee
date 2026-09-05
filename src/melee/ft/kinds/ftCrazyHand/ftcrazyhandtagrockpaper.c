#include "ftcrazyhandtagrockpaper.h"

#include "ftcrazyhandtagcancel.h"

#include <sysdolphin/baselib/forward.h>

#include <melee/ft/fighter.h>
#include <melee/ft/ftbosslib.h>
#include <melee/ft/inlines.h>
#include <melee/ft/types.h>
#include <melee/pl/player.h>
#include <Runtime/platform.h>

void fn_8015AAC8(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, 0x180, 0, fp->cur_anim_frame, 1.0f, 0.0f,
                              NULL);
}

void ftCh_TagRockPaper_Anim(HSD_GObj* gobj)
{
    if (ftBossLib_8015C2E0() || ftBossLib_8015C358()) {
        ftCh_GrabUnk1_8015BC88(gobj);
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(gobj, 0x180, 0, 0.0f, 1.0f, 0.0f, NULL);
        ftAnim_8006EBA4(gobj);
    }
}

void ftCh_TagRockPaper_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_TagRockPaper_Phys(HSD_GObj* gobj) {}

void ftCh_TagRockPaper_Coll(HSD_GObj* gobj) {}
