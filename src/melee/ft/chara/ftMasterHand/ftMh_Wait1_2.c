#include "ftMh_Wait1_2.h"

#include "ftMh_Wait1_0.h"

#include <platform.h>

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ftanim.h"
#include "ft/ftbosslib.h"
#include "ft/types.h"
#include "ftMasterHand/types.h"

#include <baselib/forward.h>

#pragma push
#pragma dont_inline on
void ftMh_MS_389_80150C8C(HSD_GObj* gobj)
{
    /// @@todo the @c #pragma above is preventing use of #GET_FIGHTER.
    Fighter* fp = gobj->user_data;
    if (fp->fv.mh.x2258 == ftMh_MS_Wait1_0 ||
        fp->fv.mh.x2258 == ftMh_MS_Wait1_2)
    {
        Fighter_ChangeMotionState(gobj, ftMh_MS_Wait1_2, 0, fp->cur_anim_frame,
                                  1, 0, 0);
    } else {
        Fighter_ChangeMotionState(gobj, ftMh_MS_Wait1_2, 0, 0, 1, 0, 0);
        ftAnim_8006EBA4(gobj);
    }
    fp->fv.mh.x2258 = ftMh_MS_Wait1_2;
}

void ftMh_MS_389_80150D28(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->fv.mh.x2258 == ftMh_MS_Wait2_0 ||
        fp->fv.mh.x2258 == ftMh_MS_Wait2_1)
    {
        Fighter_ChangeMotionState(gobj, ftMh_MS_Wait2_1, 0, fp->cur_anim_frame,
                                  1, 0, 0);
    } else {
        Fighter_ChangeMotionState(gobj, ftMh_MS_Wait2_1, 0, 0, 1, 0, 0);
        ftAnim_8006EBA4(gobj);
    }
    fp->fv.mh.x2258 = ftMh_MS_Wait2_1;
}
#pragma pop

void ftMh_MS_389_80150DC4(HSD_GObj* gobj, HSD_GObjEvent cb, Vec3* pos)
{
    Fighter* fp = GET_FIGHTER(gobj);
    u8 _[16];
    if (fp->fv.mh.x2258 == ftMh_MS_Wait2_0) {
        if ((fp->fv.mh.x2258 == ftMh_MS_Wait2_0) ||
            (fp->fv.mh.x2258 == ftMh_MS_Wait2_1))
        {
            Fighter_ChangeMotionState(gobj, ftMh_MS_Wait2_1, 0,
                                      fp->cur_anim_frame, 1, 0, 0);
        } else {
            Fighter_ChangeMotionState(gobj, ftMh_MS_Wait2_1, 0, 0, 1, 0, 0);
            ftAnim_8006EBA4(gobj);
        }
        fp->fv.mh.x2258 = ftMh_MS_Wait2_1;
    } else {
        if (fp->fv.mh.x2258 == ftMh_MS_Wait1_0 ||
            fp->fv.mh.x2258 == ftMh_MS_Wait1_2)
        {
            Fighter_ChangeMotionState(gobj, ftMh_MS_Wait1_2, 0,
                                      fp->cur_anim_frame, 1, 0, 0);
        } else {
            Fighter_ChangeMotionState(gobj, ftMh_MS_Wait1_2, 0, 0, 1, 0, 0);
            ftAnim_8006EBA4(gobj);
        }
        fp->fv.mh.x2258 = ftMh_MS_Wait1_2;
    }
    fp->mv.mh.unk0.x4 = cb;
    fp->mv.mh.unk0.xC = *pos;
}

void ftMh_Wait1_2_Anim(HSD_GObj* gobj)
{
    u8 _[4];
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->fv.mh.x2258 = ftMh_MS_Wait1_2;
        Fighter_ChangeMotionState(gobj, ftMh_MS_Wait1_2, 0, 0, 1, 0, 0);
        ftAnim_8006EBA4(gobj);
    }
}

void ftMh_Wait1_2_Phys(HSD_GObj* gobj)
{
    /// @@todo #GET_FIGHTER
    Fighter* fp = gobj->user_data;
    ftData* data = fp->ft_data;
    ftMasterHand_SpecialAttrs* da = data->ext_attr;
    ft_80085134(gobj);
    ftBossLib_8015BE40(gobj, &fp->mv.mh.unk0.xC, &fp->mv.mh.unk0.x18, da->x2C,
                       da->x28);
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
    fp->mv.mh.unk0.x20 = 0;
    {
        Vec3 pos;
        u8 _[8];
        pos.x = da->x30_pos2.x;
        pos.y = da->x30_pos2.y;
        pos.z = 0;
        fp->fv.mh.x2258 = ftMh_MS_Wait2_1;
        {
            Fighter* fp = GET_FIGHTER(gobj);
            if (fp->fv.mh.x2258 == ftMh_MS_Wait2_0) {
                ftMh_MS_389_80150D28(gobj);
            } else {
                ftMh_MS_389_80150C8C(gobj);
            }
            fp->mv.mh.unk0.x4 = ftMh_MS_341_8014FFDC;
            fp->mv.mh.unk0.xC = pos;
        }
    }
}
