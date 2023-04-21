#include "ftMh_MS_353.h"

#include "ftMh_MS_349.h"
#include "ftMh_MS_389.h"

#include "ft/ft_081B.h"
#include "ft/ftbosslib.h"
#include "ft/ftlib.h"
#include "ft/inlines.h"
#include "lb/lbvector.h"
#include "mp/mplib.h"

#include <dolphin/mtx/types.h>

void ftMh_MS_353_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftMh_MS_389_80151018(gobj);
    }
}

void ftMh_MS_353_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_MS_353_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftMh_MS_353_Coll(HSD_GObj* gobj) {}

void ftMh_MS_353_80151DC4(HSD_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, ftMh_MS_Unk350, 0, 0, 0, 1, 0);
    ftAnim_8006EBA4(gobj);
}

void ftMh_MS_350_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftMh_MS_350_80151EB4(gobj);
    }
}

void ftMh_MS_350_IASA(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_MS_350_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftMh_MS_350_Coll(HSD_GObj* gobj) {}

void ftMh_MS_350_80151EB4(HSD_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, ftMh_MS_Walk_StartMotion, 0, 0, 0, 1, 0);
    ftAnim_8006EBA4(gobj);
}

static inline float my_sqrtf(float x)
{
    static const double _half = .5;
    static const double _three = 3.0;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4] = { 0 };
#endif

    volatile float y;
    if (x > 0) {
        double guess = __frsqrte((double) x); // returns an approximation to
        guess = _half * guess *
                (_three - guess * guess * x); // now have 12 sig bits
        guess = _half * guess *
                (_three - guess * guess * x); // now have 24 sig bits
        guess = _half * guess *
                (_three - guess * guess * x); // now have 32 sig bits
        y = (float) (x * guess);
        return y;
    }
    return x;
}

static inline float my_lbVector_Len(Vec3* vec)
{
    return my_sqrtf(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
}

void ftMh_MS_351_Anim(HSD_GObj* gobj)
{
    Vec3 pos;
    Vec3 vel;

    /// @todo #GET_FIGHTER uses slightly too much stack; inline issue.
    Fighter* fp = gobj->user_data;
    ftMasterHand_SpecialAttrs* attr = fp->ft_data->ext_attr;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    ftLib_800866DC(ftBossLib_8015C244(gobj, &fp->cur_pos), &pos);
    lbVector_Diff(&pos, &fp->cur_pos, &vel);

    if (my_lbVector_Len(&vel) < attr->x4C) {
        ftMh_MS_349_80151CA8(gobj);
    }

    mpLib_80054158(0, &pos);

    if (fp->cur_pos.x < pos.x) {
        ftMh_MS_351_801520D8(gobj);
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(gobj, ftMh_MS_Walk_StartMotion, 0, 0, 0, 1,
                                  0);
        ftAnim_8006EBA4(gobj);
    }
}

void ftMh_MS_351_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_MS_351_Phys(HSD_GObj* gobj)
{
    /// @todo #GET_FIGHTER
    Fighter* fp = gobj->user_data;
    ftData* data = fp->ft_data;
    ftMasterHand_SpecialAttrs* attr = data->ext_attr;
    ft_80085134(gobj);
    fp->x80_self_vel.x = attr->x40_pos.z;
}

void ftMh_MS_351_Coll(HSD_GObj* gobj) {}

void ftMh_MS_351_801520D8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftMh_MS_Unk352, 0, 0, 0, 1, 0);
    ftAnim_8006EBA4(gobj);
    fp->x80_self_vel.x = 0;
}
