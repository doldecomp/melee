#include "ftCh_Grab.h"

#include "ftCh_Init.h"

#include <placeholder.h>
#include <platform.h>

#include "baselib/forward.h"

#include "ft/fighter.h"
#include "ft/ft_084E.h"
#include "ft/ftbosslib.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCrazyHand/ftCh_Cancel.h"
#include "ftMasterHand/types.h"
#include "pl/player.h"

#include <common_structs.h>
#include <dolphin/mtx.h>
#include <MetroTRK/intrinsics.h>

void ftCh_Init_80159F40(HSD_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, ftMh_MS_Grab, 0, 0.0f,
                              1.0f, 0.0f, NULL);
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
