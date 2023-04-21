#include "ftMh_MS_355.h"

#include "ft/ft_081B.h"
#include "ft/ftbosslib.h"
#include "ft/inlines.h"

void ftMh_MS_354_Coll(HSD_GObj* gobj) {}

void ftMh_MS_354_80152370(HSD_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, ftMh_MS_Punch_StartMotion, 0, 0, 0, 1, 0);
    ftAnim_8006EBA4(gobj);
}

void ftMh_MS_355_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = gobj->user_data;
        ftMasterHand_SpecialAttrs* attr = fp->ft_data->ext_attr;
        ftMh_MS_355_8015247C(gobj);
        fp->mv.mh.unk0.x8 = attr->xA0;
    }
}

void ftMh_MS_355_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_MS_355_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftMh_MS_355_Coll(HSD_GObj* gobj) {}

void ftMh_MS_355_8015247C(HSD_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, ftMh_MS_Unk356, 0, 0, 0, 1, 0);
    ftAnim_8006EBA4(gobj);
}

void ftMh_MS_356_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!--fp->mv.mh.unk0.x8) {
        ftMh_MS_356_801525E0(gobj);
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(gobj, ftMh_MS_Unk356, 0, 0, 0, 1, 0);
        ftAnim_8006EBA4(gobj);
    }
}

void ftMh_MS_356_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_MS_356_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftData* data = fp->ft_data;
    ftMasterHand_SpecialAttrs* attr = data->ext_attr;
    ft_80085134(gobj);
    ftBossLib_8015C010(gobj, attr->xA4);
    ftBossLib_8015C190(gobj);
}

void ftMh_MS_356_Coll(HSD_GObj* gobj) {}

void ftMh_MS_356_801525E0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x80_self_vel.x = 0;
    Fighter_ChangeMotionState(gobj, ftMh_MS_Unk357, 0, 0, 0, 1, 0);
    ftAnim_8006EBA4(gobj);
}
