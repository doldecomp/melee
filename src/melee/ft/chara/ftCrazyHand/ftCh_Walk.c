#include "ftCh_Walk.h"

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

void fn_801578E8(HSD_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, ftMh_MS_WalkLoop, 0, 0.0f,
                              1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
}

void ftCh_WalkLoop_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = gobj->user_data;
        ftCrazyHand_DatAttrs* da = fp->ft_data->ext_attr;
        ftCh_Init_801579F4(gobj);
        fp->mv.ch.unk0.x8 = da->x64;
    }
}

void ftCh_WalkLoop_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_WalkLoop_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_WalkLoop_Coll(HSD_GObj* gobj) {}

void ftCh_Init_801579F4(HSD_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, ftMh_MS_WalkWait, 0, 0.0f,
                              1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
}

void ftCh_WalkWait_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!--fp->mv.ch.unk0.x8) {
        ftCh_Init_80157B58(gobj);
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(gobj, 0x160, 0, 0, 1.0f, 0.0f, NULL);
        ftAnim_8006EBA4(gobj);
    }
}

void ftCh_WalkWait_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_WalkWait_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftData* data = fp->ft_data;
    ftCrazyHand_DatAttrs* da = data->ext_attr;
    ft_80085134(gobj);
    ftBossLib_8015C010(gobj, da->x68);
    ftBossLib_8015C190(gobj);
}

void ftCh_WalkWait_Coll(HSD_GObj* gobj) {}

void ftCh_Init_80157B58(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->self_vel.x = 0;
    Fighter_ChangeMotionState(gobj, ftMh_MS_WalkShoot, 0, 0, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
}

void ftCh_WalkShoot_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}

void ftCh_WalkShoot_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_WalkShoot_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_WalkShoot_Coll(HSD_GObj* gobj) {}
