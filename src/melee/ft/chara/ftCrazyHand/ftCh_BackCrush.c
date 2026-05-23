#include "ftCh_BackCrush.h"

#include <placeholder.h>
#include <platform.h>

#include "baselib/forward.h"

#include "ft/fighter.h"
#include "ft/ft_084E.h"
#include "ft/ftbosslib.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftMasterHand/types.h"
#include "pl/player.h"

#include <common_structs.h>
#include <dolphin/mtx.h>
#include <MetroTRK/intrinsics.h>

void ftCh_Init_801597F0(HSD_GObj* gobj, HSD_GObjEvent cb)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, 0x173, 0, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    fp->mv.ch.unk0.x4 = cb;
}

void ftCh_BackCrush_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->mv.ch.unk0.x4(gobj);
    }
}
void ftCh_BackCrush_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_BackCrush_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_BackCrush_Coll(HSD_GObj* gobj) {}
