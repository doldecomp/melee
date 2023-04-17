#include "ftMh_MS_359.h"

#include "ftMh_MS_389.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftbosslib.h"
#include "ft/inlines.h"
#include "lb/lbvector.h"

#include <dolphin/mtx/types.h>

// 8015287C 14F45C
void ftMh_MS_358_Coll(HSD_GObj* gobj)
{
    return;
}

// 80152880 14F460
// https://decomp.me/scratch/is1xu
void ftMh_MS_358_80152880(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMasterHand_SpecialAttrs* attr = fp->ft_data->ext_attr;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter_ChangeMotionState(gobj, 0x167, 0, 0, 0.0f, 1.0f, 0.0f);
    ftAnim_8006EBA4(gobj);
    fp->mv.mh.unk13.x0 = attr->x94 + HSD_Randi(attr->x90 - attr->x94);
    fp->mv.mh.unk13.x4 = 0.0f;
}

// 80152928 14F508
// https://decomp.me/scratch/WyNdB
void ftMh_MS_359_Anim(HSD_GObj* gobj)
{
    Fighter* temp_r31;
    Fighter* temp_r4;

    if (!ftAnim_IsFramesRemaining(gobj)) {
        temp_r4 = GET_FIGHTER(gobj);
        temp_r4->mv.mh.unk13.x4 = 1.0f;

        if (--temp_r4->mv.mh.unk13.x0 < 0.0f) {
            temp_r4->mv.mh.unk13.x4 = 0.0f;
            temp_r4->x80_self_vel.x = 0.0f;
            temp_r4->x80_self_vel.y = 0.0f;
            temp_r31 = GET_FIGHTER(gobj);
            Fighter_ChangeMotionState(gobj, 0x168, 0, 0, 0.0f, 1.0f, 0.0f);
            ftAnim_8006EBA4(gobj);
            ft_80088148(temp_r31, 0x4E207, 0x7F, 0x40);
        }
    }
}

// 801529D0 14F5B0
// https://decomp.me/scratch/IBucf
void ftMh_MS_360_Anim(HSD_GObj* arg0)
{
    if (!ftAnim_IsFramesRemaining(arg0)) {
        ftMh_MS_389_80151018(arg0);
    }
}

// 80152A0C 14F5EC
// https://decomp.me/scratch/7UfC7
void ftMh_MS_359_IASA(HSD_GObj* arg0)
{
    Fighter* fp = arg0->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftBossLib_8015BD20(arg0);
    }
}

// 80152A50 14F630
// https://decomp.me/scratch/YmoFC
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

void ftMh_MS_359_Phys(HSD_GObj* gobj)
{
    Fighter* fp;
    ftMasterHand_SpecialAttrs* attr;
    f32 speed;
    ftData* ftData;
    Vec3 sp28_pos;
    Vec3 sp1C_vel;
    f32 len;

    fp = gobj->user_data;
    ft_80085134(gobj);
    if (fp->mv.mh.unk13.x4) {
        ftData = fp->ft_data;
        attr = ftData->ext_attr;
        ftBossLib_8015C208(gobj, &sp28_pos);
        sp28_pos.x += attr->x98;
        sp28_pos.y += attr->x9C;
        sp28_pos.z = 0.0f;
        lbVector_Diff(&sp28_pos, &fp->cur_pos, &sp1C_vel);
        len = my_lbvector_Len(&sp1C_vel);
        if (len < attr->x2C) {
            fp->x80_self_vel.x = sp1C_vel.x;
            fp->x80_self_vel.y = sp1C_vel.y;
        } else {
            lbVector_Normalize(&sp1C_vel);
            speed = len * attr->x28;
            sp1C_vel.x *= speed;
            sp1C_vel.y *= speed;
            sp1C_vel.z *= speed;
            fp->x80_self_vel.x = sp1C_vel.x;
            fp->x80_self_vel.y = sp1C_vel.y;
        }
    }
}
