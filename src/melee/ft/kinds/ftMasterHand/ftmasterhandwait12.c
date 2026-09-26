#include "ftmasterhandwait12.h"

#include <Runtime/platform.h>

#include <sysdolphin/baselib/forward.h>

#include "ftmasterhandwait10.h"
#include "inlines.h"
#include "types.h"
#include <melee/ft/fighter.h>
#include <melee/ft/ftanim.h>
#include <melee/ft/types.h>

void ftMh_MS_389_80150C8C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->u.mh.x2258 == ftMh_MS_Wait1_0 || fp->u.mh.x2258 == ftMh_MS_Wait1_2)
    {
        Fighter_ChangeMotionState(gobj, ftMh_MS_Wait1_2, 0, fp->cur_anim_frame,
                                  1, 0, 0);
    } else {
        Fighter_ChangeMotionState(gobj, ftMh_MS_Wait1_2, 0, 0, 1, 0, 0);
        ftAnim_8006EBA4(gobj);
    }
    fp->u.mh.x2258 = ftMh_MS_Wait1_2;
}

void ftMh_MS_389_80150D28(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->u.mh.x2258 == ftMh_MS_Wait2_0 || fp->u.mh.x2258 == ftMh_MS_Wait2_1)
    {
        Fighter_ChangeMotionState(gobj, ftMh_MS_Wait2_1, 0, fp->cur_anim_frame,
                                  1, 0, 0);
    } else {
        Fighter_ChangeMotionState(gobj, ftMh_MS_Wait2_1, 0, 0, 1, 0, 0);
        ftAnim_8006EBA4(gobj);
    }
    fp->u.mh.x2258 = ftMh_MS_Wait2_1;
}

void ftMh_MS_389_80150DC4(HSD_GObj* gobj, HSD_GObjEvent cb, Vec3* pos)
{
    Fighter* fp = GET_FIGHTER(gobj);
    u8 _[8];
    if (fp->u.mh.x2258 == ftMh_MS_Wait2_0) {
        ftMh_MS_389_80150D28(gobj);
    } else {
        ftMh_MS_389_80150C8C(gobj);
    }
    fp->mv.mh.unk0.x4 = cb;
    fp->mv.mh.unk0.xC = *pos;
}

void ftMh_Wait1_2_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->u.mh.x2258 = ftMh_MS_Wait1_2;
        Fighter_ChangeMotionState(gobj, ftMh_MS_Wait1_2, 0, 0, 1, 0, 0);
        ftAnim_8006EBA4(gobj);
    }
}

void ftMh_Wait1_2_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMasterHand_SpecialAttrs* da = fp->ft_data->ext_attr;
    ftMh_UpdateBossMotion(gobj, fp, da);
}

void ftMh_Wait1_2_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->mv.mh.unk0.x18 == 0) {
        fp->self_vel.x = fp->self_vel.y = fp->self_vel.z = 0;
        if (fp->mv.mh.unk0.x4) {
            fp->mv.mh.unk0.x4(gobj);
        }
    }
}

void ftMh_MS_389_80151018(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMasterHand_SpecialAttrs* da = fp->ft_data->ext_attr;
    Vec3 pos;
    u8 _[8];
    fp->mv.mh.unk0.x20 = 0;
    pos.x = da->x30_pos2.x;
    pos.y = da->x30_pos2.y;
    pos.z = 0;
    fp->u.mh.x2258 = ftMh_MS_Wait2_1;
    ftMh_MS_389_80150DC4(gobj, ftMh_MS_341_8014FFDC, &pos);
}
