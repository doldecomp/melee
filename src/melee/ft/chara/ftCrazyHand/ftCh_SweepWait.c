#include "ftCh_SweepWait.h"

#include "ftCh_Init.h"
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

static void fn_801577B4(HSD_GObj* gobj);

void fn_8015755C(HSD_GObj* gobj)
{
    PAD_STACK(8);
    Fighter_ChangeMotionState(gobj, ftMh_MS_SweepWait, 0, 0.0f,
                              1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
}

void ftCh_SweepWait_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCh_Init_8015764C(gobj);
    }
}

void ftCh_SweepWait_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_SweepWait_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_SweepWait_Coll(HSD_GObj* gobj) {}

void ftCh_Init_8015764C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, 0x15D, 0, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    fp->accessory4_cb = fn_801577B4;
}

void ftCh_Slap_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        Fighter* fp = GET_FIGHTER(gobj);
        Fighter_ChangeMotionState(gobj, 0x15D, 0, 0.0f, 1.0f, 0.0f, NULL);
        ftAnim_8006EBA4(gobj);
        fp->accessory4_cb = fn_801577B4;
    }
}

void ftCh_Slap_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_Slap_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCrazyHand_DatAttrs* da = fp->ft_data->ext_attr;
    ft_80085134(gobj);
    fp->self_vel.x += da->x40;
}

/// #fn_801577B4

static void fn_801577B4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCrazyHand_DatAttrs* da = fp->ft_data->ext_attr;

    if (fp->cur_pos.x > da->x3C) {
        fp->self_vel.x = 0.0f;
        ftCh_Init_801577F8(gobj);
    }
}

void ftCh_Init_801577F8(HSD_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, ftMh_MS_Walk2, 0, 0.0f,
                              1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
}

void ftCh_Walk2_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}

void ftCh_Walk2_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_Walk2_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_Slap_Coll(HSD_GObj* gobj) {}
