#include <platform.h>

#include "ftMh_FingerGun.h"

#include "ftMh_Wait1_2.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ftanim.h"
#include "ft/ftbosslib.h"
#include "ft/ftlib.h"
#include "ft/types.h"
#include "ftMasterHand/types.h"
#include "it/items/itmasterhandbullet.h"
#include "lb/lb_00B0.h"
#include "lb/lbvector.h"
#include "pl/player.h"

#include <dolphin/mtx/types.h>
#include <baselib/random.h>
#include <MetroTRK/intrinsics.h>

void ftMh_FingerBeamEnd_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftMh_MS_389_80151018(gobj);
    }
}

void ftMh_FingerBeamEnd_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(fp->player_id) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_FingerBeamEnd_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftMh_FingerBeamEnd_Coll(HSD_GObj* gobj) {}

void ftMh_MS_363_801530A4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMasterHand_SpecialAttrs* da = fp->ft_data->ext_attr;

    u8 _[8];

    Fighter_ChangeMotionState(gobj, ftMh_MS_FingerGun1, 0, 0, 1, 0, 0);
    ftAnim_8006EBA4(gobj);

    {
        int rand;
        rand = HSD_Randi(da->xE8 - da->xE4);
        fp->mv.mh.unk0.x50 = da->xE4 + rand;
    }

    fp->cmd_vars[0] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[2] = 0;
}

void ftMh_FingerGun1_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!ftAnim_IsFramesRemaining(gobj)) {
        fp->cmd_vars[2] = 1;

        {
            float f = fp->mv.mh.unk0.x50 - 1;
            fp->mv.mh.unk0.x50 = f;
            if (f < 0) {
                ftData* data = fp->ft_data;
                ftMasterHand_SpecialAttrs* da = data->ext_attr;
                ftMh_MS_364_801533CC(gobj);

                if (ftLib_80087120(gobj) > da->xEC) {
                    fp->mv.mh.unk0.x54 = da->xF0;
                } else {
                    fp->mv.mh.unk0.x54 = 1;
                }

                fp->cmd_vars[2] = 0;
            }
        }
    }
}

void ftMh_FingerGun1_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(fp->player_id) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

static inline float my_sqrtf(float x)
{
    static const double _half = .5;
    static const double _three = 3.0;

    u8 _[4] = { 0 };

    volatile float y;
    if (x > 0) {
        double guess = __frsqrte((double) x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        y = (float) (x * guess);
        return y;
    }
    return x;
}

static inline float my_lbVector_Len(Vec3* vec)
{
    return my_sqrtf(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
}

void ftMh_FingerGun1_Phys(HSD_GObj* gobj)
{
    /// @todo Not enough stack for #GET_FIGHTER; inline issue.
    Fighter* fp = gobj->user_data;

    ftMasterHand_SpecialAttrs* da;
    float len;
    float speed;
    Vec3 pos;
    Vec3 vel;

    u8 _[4];

    ft_80085134(gobj);
    if (fp->cmd_vars[2] != 0) {
        da = fp->ft_data->ext_attr;
        ftBossLib_8015C208(gobj, &pos);
        pos.x += da->xDC;
        pos.y += da->xE0;
        pos.z = 0;
        lbVector_Diff(&pos, &fp->cur_pos, &vel);
        {
            len = my_lbVector_Len(&vel);
            if (len < da->x2C) {
                fp->self_vel.x = vel.x;
                fp->self_vel.y = vel.y;
            } else {
                lbVector_Normalize(&vel);
                speed = len * da->x28;
                vel.x *= speed;
                vel.y *= speed;
                vel.z *= speed;
                fp->self_vel.x = vel.x;
                fp->self_vel.y = vel.y;
            }
        }
    }
}

void ftMh_FingerGun1_Coll(HSD_GObj* gobj) {}

void ftMh_MS_364_801533CC(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMasterHand_SpecialAttrs* da = fp->ft_data->ext_attr;
    Fighter_ChangeMotionState(gobj, ftMh_MS_FingerGun2, 0, 0, 1, 0, 0);
    ftAnim_8006EBA4(gobj);
    if (ftLib_80087120(gobj) > da->xEC) {
        ftAnim_SetAnimRate(gobj, da->xF4);
    }
    fp->self_vel.x = 0;
    fp->self_vel.y = 0;
    fp->accessory4_cb = ftMh_MS_365_801535B0;
}

static inline void lbl_8015346C_inline(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMasterHand_SpecialAttrs* da = fp->ft_data->ext_attr;
    Fighter_ChangeMotionState(gobj, ftMh_MS_FingerGun2, 0, 0, 1, 0, 0);
    ftAnim_8006EBA4(gobj);
    if (ftLib_80087120(gobj) > da->xEC) {
        ftAnim_SetAnimRate(gobj, da->xF4);
    }
    fp->self_vel.x = 0;
    fp->self_vel.y = 0;
    fp->accessory4_cb = ftMh_MS_365_801535B0;
}

void ftMh_FingerGun2_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        if (--fp->mv.mh.unk0.x54 == 0) {
            ftAnim_SetAnimRate(gobj, 1);
            ftMh_MS_365_80153730(gobj);
        } else {
            lbl_8015346C_inline(gobj);
        }
    }
}

void ftMh_FingerGun2_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(fp->player_id) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_FingerGun2_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftMh_FingerGun2_Coll(HSD_GObj* gobj) {}

static void ftMh_MS_365_8015364C(HSD_GObj* gobj, HSD_JObj* arg1, float arg2,
                                 float arg3);

void ftMh_MS_365_801535B0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMasterHand_SpecialAttrs* da = fp->ft_data->ext_attr;

    if (fp->cmd_vars[0] != 0) {
        ftMh_MS_365_8015364C(gobj, fp->parts[FtPart_LKneeJ].joint, da->xF8,
                             da->xFC);
        fp->cmd_vars[0] = 0;
    }
    if (fp->cmd_vars[1] != 0) {
        ftMh_MS_365_8015364C(gobj, fp->parts[FtPart_RKneeJ].joint, da->x100,
                             da->x104);
        fp->cmd_vars[1] = 0;
    }
}

void ftMh_MS_365_8015364C(HSD_GObj* gobj, HSD_JObj* arg1, float arg2,
                          float arg3)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMasterHand_SpecialAttrs* da = fp->ft_data->ext_attr;
    bool b = false;

    {
        Vec3 vec0;
        lb_8000B1CC(arg1, 0, &vec0);

        {
            Vec3 vec1 = vec0;
            vec0.x += arg2;
            vec0.y += arg3;

            if (ftLib_80087120(gobj) > da->xEC) {
                b = true;
            }

            it_802F0AE0(gobj, &vec0, &vec1, 126, b, fp->facing_dir, da->xD4,
                        da->xD8);
        }
    }
}

void ftMh_MS_365_80153730(HSD_GObj* gobj)
{
    u8 _[8];

    Fighter_ChangeMotionState(gobj, ftMh_MS_FingerGun3, 0, 0, 1, 0, 0);
    ftAnim_8006EBA4(gobj);
}
