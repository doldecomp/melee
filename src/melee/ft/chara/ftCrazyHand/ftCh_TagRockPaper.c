#include "ftCh_TagRockPaper.h"

#include "ftCh_Init.h"

#include <placeholder.h>
#include <platform.h>

#include "baselib/forward.h"

#include "ft/fighter.h"
#include "ft/ftbosslib.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCrazyHand/ftCh_TagCancel.h"
#include "pl/player.h"

#include <common_structs.h>
#include <dolphin/mtx.h>
#include <MetroTRK/intrinsics.h>

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
        Fighter_ChangeMotionState(gobj, 0x180, 0, 0.0f,
                                  1.0f, 0.0f,
                                  NULL);
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
