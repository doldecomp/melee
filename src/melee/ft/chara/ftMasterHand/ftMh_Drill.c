#include "ftMh_Drill.h"

#include "ftMh_Wait1_2.h"
#include "ftMh_Walk.h"

#include "ft/ft_081B.h"
#include "ft/ftbosslib.h"
#include "ft/inlines.h"

void ftMh_WalkWait_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftMh_MS_389_80151018(gobj);
    }
}

void ftMh_WalkWait_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_WalkWait_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftMh_WalkWait_Coll(HSD_GObj* gobj) {}

void ftMh_MS_352_801521DC(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter_ChangeMotionState(gobj, ftMh_MS_Drill, 0, 0, 0, 1, 0);
    ftAnim_8006EBA4(gobj);
    fp->mv.mh.unk0.x0 = 107;
}

void ftMh_Drill_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftMh_MS_389_80151018(gobj);
    }
}

void ftMh_Drill_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_Drill_Phys(HSD_GObj* gobj)
{
    /// @todo #GET_FIGHTER
    Fighter* fp = gobj->user_data;
    ftData* data = fp->ft_data;
    ftMasterHand_SpecialAttrs* attr = data->ext_attr;
    ft_80085134(gobj);
    if (--fp->mv.mh.unk0.x0 > attr->x84 || fp->mv.mh.unk0.x0 < 0) {
        fp->self_vel.x = 0;
    } else {
        ftBossLib_8015C010(gobj, attr->x80);
    }
    ftBossLib_8015C190(gobj);
}
