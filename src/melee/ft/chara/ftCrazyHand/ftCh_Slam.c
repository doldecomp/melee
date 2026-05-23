#include "ftCh_Slam.h"

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

void ftCh_Slam_Anim(HSD_GObj* gobj)
{
    if (ftBossLib_8015C2E0() || ftBossLib_8015C358() ||
        !ftAnim_IsFramesRemaining(gobj))
    {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->self_vel.x = fp->self_vel.y = fp->self_vel.z = 0.0f;
        Fighter_UnkSetFlag_8006CFBC(gobj);
        fp->x1A5C = 0;
        ftCh_GrabUnk1_8015A888(gobj);
    }
}

void ftCh_Slam_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_Slam_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_Slam_Coll(HSD_GObj* gobj) {}

void ftCh_Fail_Anim(HSD_GObj* gobj)
{
    PAD_STACK(8);
    if (ftBossLib_8015C31C() || !ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        Fighter_UnkSetFlag_8006CFBC(gobj);
        fp->x1A5C = 0;
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}

void ftCh_Fail_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_Fail_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_Fail_Coll(HSD_GObj* gobj) {}

void ftCh_GrabUnk1_8015A888(HSD_GObj* gobj)
{
    PAD_STACK(8);
    Fighter_ChangeMotionState(gobj, 0x17E, 0, 0.0f,
                              1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
}

void ftCh_TagCrush_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}

void ftCh_TagCrush_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_TagCrush_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_TagCrush_Coll(HSD_GObj* gobj) {}

void ftCh_TagApplaud_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if ((--fp->mv.ch.unk0.x24 <= 0) && (fp->cmd_vars[0] != 0)) {
        ftCh_GrabUnk1_8015B800(fp->victim_gobj);
        fp->cmd_vars[0] = 0;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}

void ftCh_TagApplaud_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_TagApplaud_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCrazyHand_DatAttrs* da = fp->ft_data->ext_attr;
    ft_80085134(gobj);
    ftBossLib_8015BE40(gobj, &fp->mv.ch.unk0.xC, &fp->mv.ch.unk0.x18, da->x14,
                       da->x10);
}

void ftCh_TagApplaud_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->mv.ch.unk0.x18 == 0) {
        fp->self_vel.x = fp->self_vel.y = fp->self_vel.z = 0;
    }
}

