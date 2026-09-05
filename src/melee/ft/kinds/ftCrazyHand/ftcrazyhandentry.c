#include "ftcrazyhandentry.h"

#include "ftcrazyhandtagcancel.h"
#include "types.h"

#include <sysdolphin/baselib/forward.h>

#include <dolphin/mtx.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ft_084E.h>
#include <melee/ft/ftbosslib.h>
#include <melee/ft/inlines.h>
#include <melee/ft/kinds/ftMasterHand/types.h>
#include <melee/ft/types.h>
#include <melee/pl/player.h>
#include <Runtime/platform.h>

void fn_80156F6C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCrazyHand_DatAttrs* da = fp->ft_data->ext_attr;
    Fighter_ChangeMotionState(gobj, ftMh_MS_Entry, 0, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    fp->cur_pos.y = da->x20;
}

void ftCh_Entry_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}

void ftCh_Entry_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_Entry_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_Entry_Coll(HSD_GObj* gobj) {}
