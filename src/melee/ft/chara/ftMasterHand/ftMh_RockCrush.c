#include "ftMh_RockCrush.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ftanim.h"
#include "ft/ftbosslib.h"
#include "ft/types.h"
#include "ftMasterHand/types.h"
#include "pl/player.h"

#include <dolphin/mtx.h>

void ftMh_Drill_Coll(HSD_GObj* gobj) {}

void ftMh_MS_354_80152370(HSD_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, ftMh_MS_RockCrushUp, 0, 0, 1, 0, 0);
    ftAnim_8006EBA4(gobj);
}

void ftMh_RockCrushUp_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = gobj->user_data;
        ftMasterHand_SpecialAttrs* da = fp->ft_data->ext_attr;
        ftMh_MS_355_8015247C(gobj);
        fp->mv.mh.unk0.x8 = da->xA0;
    }
}

void ftMh_RockCrushUp_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(fp->player_id) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_RockCrushUp_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftMh_RockCrushUp_Coll(HSD_GObj* gobj) {}

void ftMh_MS_355_8015247C(HSD_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, ftMh_MS_RockCrushWait, 0, 0, 1, 0, 0);
    ftAnim_8006EBA4(gobj);
}

void ftMh_RockCrushWait_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!--fp->mv.mh.unk0.x8) {
        ftMh_MS_356_801525E0(gobj);
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(gobj, ftMh_MS_RockCrushWait, 0, 0, 1, 0, 0);
        ftAnim_8006EBA4(gobj);
    }
}

void ftMh_RockCrushWait_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(fp->player_id) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_RockCrushWait_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftData* data = fp->ft_data;
    ftMasterHand_SpecialAttrs* da = data->ext_attr;
    ft_80085134(gobj);
    ftBossLib_8015C010(gobj, da->xA4);
    ftBossLib_8015C190(gobj);
}

void ftMh_RockCrushWait_Coll(HSD_GObj* gobj) {}

void ftMh_MS_356_801525E0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->self_vel.x = 0;
    Fighter_ChangeMotionState(gobj, ftMh_MS_RockCrushDown, 0, 0, 1, 0, 0);
    ftAnim_8006EBA4(gobj);
}
