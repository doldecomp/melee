#include <baselib/forward.h>

#include "ftMh_MS_389.h"

#include "ftMh_MS_341.h"

#include "ft/ft_081B.h"
#include "ft/ftbosslib.h"
#include "ft/inlines.h"

#include <dolphin/mtx/types.h>

/// @todo Inline depth issue.
#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
void ftMh_MS_389_80150C8C(HSD_GObj* gobj)
{
    /// @todo the @c #pragma above is preventing use of #GET_FIGHTER.
    Fighter* fp = gobj->user_data;
    if (fp->fv.mh.x2258 == ftMh_MS_Unk341 || fp->fv.mh.x2258 == ftMh_MS_Unk389)
    {
        Fighter_ChangeMotionState(gobj, ftMh_MS_Unk389, 0, 0,
                                  fp->x894_currentAnimFrame, 1, 0);
    } else {
        Fighter_ChangeMotionState(gobj, ftMh_MS_Unk389, 0, 0, 0, 1, 0);
        ftAnim_8006EBA4(gobj);
    }
    fp->fv.mh.x2258 = ftMh_MS_Unk389;
}

void ftMh_MS_389_80150D28(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->fv.mh.x2258 == ftMh_MS_Unk342 || fp->fv.mh.x2258 == ftMh_MS_Unk390)
    {
        Fighter_ChangeMotionState(gobj, ftMh_MS_Unk390, 0, 0,
                                  fp->x894_currentAnimFrame, 1, 0);
    } else {
        Fighter_ChangeMotionState(gobj, ftMh_MS_Unk390, 0, 0, 0, 1, 0);
        ftAnim_8006EBA4(gobj);
    }
    fp->fv.mh.x2258 = ftMh_MS_Unk390;
}
#ifdef MUST_MATCH
#pragma pop
#endif

void ftMh_MS_389_80150DC4(HSD_GObj* gobj, HSD_GObjEvent cb, Vec3* pos)
{
    Fighter* fp = GET_FIGHTER(gobj);
/// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16];
#endif
    if (fp->fv.mh.x2258 == ftMh_MS_Unk342) {
        if ((fp->fv.mh.x2258 == ftMh_MS_Unk342) ||
            (fp->fv.mh.x2258 == ftMh_MS_Unk390))
        {
            Fighter_ChangeMotionState(gobj, ftMh_MS_Unk390, 0, 0,
                                      fp->x894_currentAnimFrame, 1, 0);
        } else {
            Fighter_ChangeMotionState(gobj, ftMh_MS_Unk390, 0, 0, 0, 1, 0);
            ftAnim_8006EBA4(gobj);
        }
        fp->fv.mh.x2258 = ftMh_MS_Unk390;
    } else {
        if (fp->fv.mh.x2258 == ftMh_MS_Unk341 ||
            fp->fv.mh.x2258 == ftMh_MS_Unk389)
        {
            Fighter_ChangeMotionState(gobj, ftMh_MS_Unk389, 0, 0,
                                      fp->x894_currentAnimFrame, 1, 0);
        } else {
            Fighter_ChangeMotionState(gobj, ftMh_MS_Unk389, 0, 0, 0, 1, 0);
            ftAnim_8006EBA4(gobj);
        }
        fp->fv.mh.x2258 = ftMh_MS_Unk389;
    }
    fp->mv.mh.unk0.x4 = cb;
    fp->mv.mh.unk0.xC = *pos;
}

void ftMh_MS_389_Anim(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->fv.mh.x2258 = ftMh_MS_Unk389;
        Fighter_ChangeMotionState(gobj, ftMh_MS_Unk389, 0, 0, 0, 1, 0);
        ftAnim_8006EBA4(gobj);
    }
}

void ftMh_MS_389_Phys(HSD_GObj* gobj)
{
    /// @todo #GET_FIGHTER
    Fighter* fp = gobj->user_data;
    ftData* data = fp->ft_data;
    ftMasterHand_SpecialAttrs* attr = data->ext_attr;
    ft_80085134(gobj);
    ftBossLib_8015BE40(gobj, &fp->mv.mh.unk0.xC, &fp->mv.mh.unk0.x18,
                       attr->x2C, attr->x28);
}

void ftMh_MS_389_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->mv.mh.unk0.x18 == 0) {
        fp->x80_self_vel.x = fp->x80_self_vel.y = fp->x80_self_vel.z = 0;
        if (fp->mv.mh.unk0.x4) {
            fp->mv.mh.unk0.x4(gobj);
        }
    }
}

void ftMh_MS_389_80151018(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMasterHand_SpecialAttrs* attr = fp->ft_data->ext_attr;
    fp->mv.mh.unk0.x20 = 0;
    {
        Vec3 pos;
/// @todo Unused stack.
#ifdef MUST_MATCH
        u8 _[8];
#endif
        pos.x = attr->x30_pos2.x;
        pos.y = attr->x30_pos2.y;
        pos.z = 0;
        fp->fv.mh.x2258 = ftMh_MS_Unk390;
        {
            Fighter* fp = GET_FIGHTER(gobj);
            if (fp->fv.mh.x2258 == ftMh_MS_Unk342) {
                ftMh_MS_389_80150D28(gobj);
            } else {
                ftMh_MS_389_80150C8C(gobj);
            }
            fp->mv.mh.unk0.x4 = ftMh_MS_341_8014FFDC;
            fp->mv.mh.unk0.xC = pos;
        }
    }
}
