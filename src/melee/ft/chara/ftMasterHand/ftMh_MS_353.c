#include "ftMh_MS_353.h"

#include "ftMh_MS_389.h"
#include "ftMh_MS_349.h"

#include "ft/ft_081B.h"
#include "ft/ftbosslib.h"
#include "ft/ftlib.h"
#include "lb/lbvector.h"
#include "mp/mplib.h"

// 80151D20 14E900
// https://decomp.me/scratch/wVowU
void ftMh_MS_353_Anim(HSD_GObj* arg0)
{
    if (!ftAnim_IsFramesRemaining(arg0)) {
        ftMh_MS_389_80151018(arg0);
    }
}

// 80151D5C 14E93C
// https://decomp.me/scratch/8YW2K
void ftMh_MS_353_IASA(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

// 80151DA0 14E980
// https://decomp.me/scratch/LHwFj
void ftMh_MS_353_Phys(HSD_GObj* arg0)
{
    ft_80085134(arg0);
}

void ftMh_MS_353_Coll(HSD_GObj* arg0) {}

// 80151DC4 14E9A4
// https://decomp.me/scratch/1PULy
void ftMh_MS_353_80151DC4(HSD_GObj* arg0)
{
    Fighter_ChangeMotionState(arg0, 0x15E, 0, 0, 0.0f, 1.0f, 0.0f);
    ftAnim_8006EBA4(arg0);
}

// 80151E10 14E9F0
// https://decomp.me/scratch/acoIs
void ftMh_MS_350_Anim(HSD_GObj* arg0)
{
    if (!ftAnim_IsFramesRemaining(arg0)) {
        ftMh_MS_350_80151EB4(arg0);
    }
}

// 80151E4C 14EA2C
// https://decomp.me/scratch/FpXjP
void ftMh_MS_350_IASA(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

// 80151E90 14EA70
// https://decomp.me/scratch/HeWua
void ftMh_MS_350_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftMh_MS_350_Coll(HSD_GObj* arg0) {}

// 80151EB4 14EA94
// https://decomp.me/scratch/ZzhS3
void ftMh_MS_350_80151EB4(HSD_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, 0x15F, 0, 0, 0.0f, 1.0f, 0.0f);
    ftAnim_8006EBA4(gobj);
}

// 80151F00 14EAE0
// https://decomp.me/scratch/12qfC
static inline float my_sqrtf(float x)
{
    static const double _half = .5;
    static const double _three = 3.0;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4] = { 0 };
#endif

    volatile float y;
    if (x > 0.0f) {
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

static inline float my_lbvector_Len(Vec3* vec)
{
    return my_sqrtf(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
}

void ftMh_MS_351_Anim(HSD_GObj* gobj)
{
    Vec3 sp28;
    Vec3 sp1C_resultVector;

    /// @todo #GET_FIGHTER uses slightly too much stack; inline issue.
    Fighter* r31_fp = gobj->user_data;
    ftMasterHand_SpecialAttrs* r30_attributes = r31_fp->x10C_ftData->ext_attr;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    ftLib_800866DC(ftBossLib_8015C244(gobj, &r31_fp->cur_pos), &sp28);
    lbVector_Diff(&sp28, &r31_fp->cur_pos, &sp1C_resultVector);

    if (my_lbvector_Len(&sp1C_resultVector) < r30_attributes->x4C) {
        ftMh_MS_349_80151CA8(gobj);
    }

    mpLib_80054158(0, &sp28);

    if (r31_fp->cur_pos.x < sp28.x) {
        ftMh_MS_351_801520D8(gobj);
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(gobj, 0x15F, 0, 0, 0.0f, 1.0f, 0.0f);
        ftAnim_8006EBA4(gobj);
    }
}

// 8015204C 14EC2C
// https://decomp.me/scratch/6N3wk
void ftMh_MS_351_IASA(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

// 80152090 14EC70
// https://decomp.me/scratch/B021s
void ftMh_MS_351_Phys(HSD_GObj* gobj)
{
    ftData* r4_ftData;
    Fighter* r31_fp;
    ftMasterHand_SpecialAttrs* r30_attributes;

    r31_fp = gobj->user_data;
    r4_ftData = r31_fp->x10C_ftData;
    r30_attributes = r4_ftData->ext_attr;
    ft_80085134(gobj);
    r31_fp->x80_self_vel.x = r30_attributes->x40_pos.z;
}

void ftMh_MS_351_Coll(HSD_GObj* arg0) {}

// 801520D8 14ECB8
// https://decomp.me/scratch/HUhGv
void ftMh_MS_351_801520D8(HSD_GObj* gobj)
{
    Fighter* r31_fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, 0x160, 0, 0, 0.0f, 1.0f, 0.0f);
    ftAnim_8006EBA4(gobj);
    r31_fp->x80_self_vel.x = 0.0f;
}
