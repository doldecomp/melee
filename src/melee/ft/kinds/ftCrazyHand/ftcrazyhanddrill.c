#include "ftcrazyhanddrill.h"

#include "types.h"

#include <Runtime/platform.h>

#include <melee/ft/fighter.h>
#include <melee/ft/ft_084E.h>
#include <melee/ft/ftbosslib.h>
#include <melee/ft/inlines.h>
#include <melee/ft/types.h>
#include "ftcrazyhandtagcancel.h"
#include <melee/ft/kinds/ftMasterHand/types.h>
#include <melee/pl/player.h>

#include <sysdolphin/baselib/forward.h>

#include <dolphin/mtx.h>

void fn_80157C50(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftMh_MS_Drill, 0, 0, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    fp->mv.ch.unk0.x0 = 0;
}

void ftCh_Drill_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}

void ftCh_Drill_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_Drill_Phys(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftCrazyHand_DatAttrs* da = fp->ft_data->ext_attr;
    ft_80085134(gobj);
    {
        float f = ++fp->mv.ch.unk0.x0;
        if (f > da->x74 && fp->mv.ch.unk0.x0 < da->x78) {
            ftBossLib_8015C010(gobj, da->x7C);
        } else {
            fp->self_vel.x = 0;
        }
    }
    ftBossLib_8015C190(gobj);
}

void ftCh_Drill_Coll(HSD_GObj* gobj) {}
