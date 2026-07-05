#include "ftCh_RockCrush_1.h"

#include "types.h"

#include <placeholder.h>
#include <platform.h>

#include "baselib/forward.h"

#include "ft/fighter.h"
#include "ft/ft_084E.h"
#include "ft/ftbosslib.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCrazyHand/ftCh_TagCancel.h"
#include "ftMasterHand/types.h"
#include "pl/player.h"

#include <common_structs.h>
#include <dolphin/mtx.h>
#include <MetroTRK/intrinsics.h>

void fn_80158144(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    u8 _[8];

    Fighter_ChangeMotionState(gobj, ftMh_MS_RockCrushDown, 0, 0, 1.0f, 0.0f,
                              NULL);
    ftAnim_8006EBA4(gobj);
    fp->mv.ch.unk0.x0 = 107;
}

void ftCh_RockCrushDown_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}

void ftCh_RockCrushDown_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_RockCrushDown_Phys(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftData* data = fp->ft_data;
    ftCrazyHand_DatAttrs* da = data->ext_attr;
    ft_80085134(gobj);
    if (--fp->mv.ch.unk0.x0 > da->x48 || fp->mv.ch.unk0.x0 < 0) {
        fp->self_vel.x = 0;
    } else {
        ftBossLib_8015C010(gobj, da->x44);
    }
    ftBossLib_8015C190(gobj);
}

void ftCh_RockCrushDown_Coll(HSD_GObj* gobj) {}
