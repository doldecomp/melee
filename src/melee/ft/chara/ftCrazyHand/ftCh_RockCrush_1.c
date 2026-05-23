#include "ftCh_RockCrush_1.h"

#include "ftCh_Init.h"

#include "math.h"
#include "types.h"

#include <placeholder.h>
#include <platform.h>

#include "baselib/forward.h"

#include "cm/camera.h"
#include "ft/chara/ftCommon/ftCo_Attack100.h"
#include "ft/chara/ftCommon/ftCo_CaptureCut.h"
#include "ft/chara/ftCommon/ftCo_Lift.h"
#include "ft/chara/ftCommon/ftCo_Throw.h"
#include "ft/chara/ftCommon/ftCo_Thrown.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0881.h"
#include "ft/ft_0D4D.h"
#include "ft/ftbosslib.h"
#include "ft/ftcamera.h"
#include "ft/ftcommon.h"
#include "ft/ftlib.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include "ftCrazyHand/forward.h"

#include "ftMasterHand/types.h"
#include "gr/stage.h"
#include "it/it_26B1.h"
#include "it/items/itcrazyhandbomb.h"
#include "it/items/itmasterhandlaser.h"
#include "lb/lb_00B0.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbvector.h"
#include "mp/mplib.h"
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

