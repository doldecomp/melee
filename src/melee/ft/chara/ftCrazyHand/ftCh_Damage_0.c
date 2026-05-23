#include "ftCh_Damage_0.h"

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

void fn_80157080(Fighter_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, 0x158, 0, 0.0f,
                              1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
}
void ftCh_Damage_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCh_Init_80157170(gobj);
    }
}

void ftCh_Damage_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_Damage_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_Damage_Coll(HSD_GObj* gobj) {}

void ftCh_Init_80157170(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCrazyHand_DatAttrs* attrs = fp->ft_data->ext_attr;
    fp->mv.ch.unk0.xC.x = fp->cur_pos.x - attrs->x28;
    fp->mv.ch.unk0.xC.y = attrs->x24;
    Fighter_ChangeMotionState(gobj, ftMh_MS_Damage2, 0,
                              fp->mv.ch.unk0.xC.z = 0.0f,
                              1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    ft_PlaySFX(fp, 0x4E207, 127, 64);
}

void ftCh_Damage2_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        Vec3 pos;
        mpFloorGetRight(0, &pos);
        if (fp->cur_pos.x > pos.x) {
            ftCh_Init_8015737C(gobj);
        } else {
            ftCrazyHand_DatAttrs* attrs;
            fp = GET_FIGHTER(gobj);
            attrs = fp->ft_data->ext_attr;
            fp->mv.ch.unk0.xC.x = fp->cur_pos.x - attrs->x28;
            fp->mv.ch.unk0.xC.y = attrs->x24;
            Fighter_ChangeMotionState(gobj, ftMh_MS_Damage2, 0,
                                      fp->mv.ch.unk0.xC.z = 0.0f,
                                      1.0f, 0.0f,
                                      NULL);
            ftAnim_8006EBA4(gobj);
            ft_PlaySFX(fp, 0x4E207, 127, 64);
        }
    }
}

void ftCh_Damage2_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_Damage2_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCrazyHand_DatAttrs* attrs = fp->ft_data->ext_attr;
    ft_80085134(gobj);
    ftBossLib_8015BE40(gobj, &fp->mv.ch.unk0.xC, &fp->mv.ch.unk0.x18,
                       attrs->x14, attrs->x10);
}

void ftCh_Damage2_Coll(HSD_GObj* gobj) {}

void ftCh_Init_8015737C(HSD_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, ftMh_MS_WaitSweep, 0, 0.0f,
                              1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
}

void ftCh_WaitSweep_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}

void ftCh_WaitSweep_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_WaitSweep_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_WaitSweep_Coll(HSD_GObj* gobj) {}

