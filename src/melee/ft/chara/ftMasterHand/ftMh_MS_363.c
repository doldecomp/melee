#include "ftMh_MS_363.h"

#include "ftMh_MS_389.h"

#include "ft/ft_081B.h"
#include "ft/ftbosslib.h"
#include "ft/ftlib.h"
#include "ft/inlines.h"
#include "it/it_27CF.h"
#include "lb/lb_00B0.h"
#include "lb/lbvector.h"

#include <dolphin/mtx/types.h>

void ftMh_MS_363_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftMh_MS_389_80151018(gobj);
    }
}

void ftMh_MS_363_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_MS_363_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftMh_MS_363_Coll(HSD_GObj* gobj) {}

void ftMh_MS_363_801530A4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMasterHand_SpecialAttrs* attr = fp->ft_data->ext_attr;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter_ChangeMotionState(gobj, ftMh_MS_Unk364, 0, 0, 0, 1, 0);
    ftAnim_8006EBA4(gobj);

    {
        int rand;
        rand = HSD_Randi(attr->xE8 - attr->xE4);
        fp->mv.mh.unk0.x50 = attr->xE4 + rand;
    }

    fp->x2200_ftcmd_var0 = 0;
    fp->x2204_ftcmd_var1 = 0;
    fp->x2208_ftcmd_var2 = 0;
}

void ftMh_MS_364_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!ftAnim_IsFramesRemaining(gobj)) {
        fp->x2208_ftcmd_var2 = 1;

        {
            float f = fp->mv.mh.unk0.x50 - 1;
            fp->mv.mh.unk0.x50 = f;
            if (f < 0) {
                ftData* data = fp->ft_data;
                ftMasterHand_SpecialAttrs* attr = data->ext_attr;
                ftMh_MS_364_801533CC(gobj);

                if (ftLib_80087120(gobj) > attr->xEC) {
                    fp->mv.mh.unk0.x54 = attr->xF0;
                } else {
                    fp->mv.mh.unk0.x54 = 1;
                }

                fp->x2208_ftcmd_var2 = 0;
            }
        }
    }
}

void ftMh_MS_364_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftBossLib_8015BD20(gobj);
    }
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

void ftMh_MS_364_Phys(HSD_GObj* gobj)
{
    /// @todo Not enough stack for #GET_FIGHTER; inline issue.
    Fighter* fp = gobj->user_data;

    ftMasterHand_SpecialAttrs* attr;
    float len;
    float speed;
    Vec3 pos;
    Vec3 vel;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    ft_80085134(gobj);
    if (fp->x2208_ftcmd_var2 != 0) {
        attr = fp->ft_data->ext_attr;
        ftBossLib_8015C208(gobj, &pos);
        pos.x += attr->xDC;
        pos.y += attr->xE0;
        pos.z = 0;
        lbVector_Diff(&pos, &fp->cur_pos, &vel);
        {
            len = my_lbVector_Len(&vel);
            if (len < attr->x2C) {
                fp->x80_self_vel.x = vel.x;
                fp->x80_self_vel.y = vel.y;
            } else {
                lbVector_Normalize(&vel);
                speed = len * attr->x28;
                vel.x *= speed;
                vel.y *= speed;
                vel.z *= speed;
                fp->x80_self_vel.x = vel.x;
                fp->x80_self_vel.y = vel.y;
            }
        }
    }
}

void ftMh_MS_364_Coll(HSD_GObj* gobj) {}

void ftMh_MS_364_801533CC(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMasterHand_SpecialAttrs* attr = fp->ft_data->ext_attr;
    Fighter_ChangeMotionState(gobj, ftMh_MS_Gun_StartMotion, 0, 0, 0, 1, 0);
    ftAnim_8006EBA4(gobj);
    if (ftLib_80087120(gobj) > attr->xEC) {
        ftAnim_SetAnimRate(gobj, attr->xF4);
    }
    fp->x80_self_vel.x = 0;
    fp->x80_self_vel.y = 0;
    fp->cb.x21BC_callback_Accessory4 = ftMh_MS_365_801535B0;
}

static inline void lbl_8015346C_inline(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMasterHand_SpecialAttrs* attr = fp->ft_data->ext_attr;
    Fighter_ChangeMotionState(gobj, ftMh_MS_Gun_StartMotion, 0, 0, 0, 1, 0);
    ftAnim_8006EBA4(gobj);
    if (ftLib_80087120(gobj) > attr->xEC) {
        ftAnim_SetAnimRate(gobj, attr->xF4);
    }
    fp->x80_self_vel.x = 0;
    fp->x80_self_vel.y = 0;
    fp->cb.x21BC_callback_Accessory4 = ftMh_MS_365_801535B0;
}

void ftMh_MS_365_Anim(HSD_GObj* gobj)
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

void ftMh_MS_365_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_MS_365_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftMh_MS_365_Coll(HSD_GObj* gobj) {}

static void ftMh_MS_365_8015364C(HSD_GObj* gobj, HSD_JObj* arg1, f32 arg2,
                                 f32 arg3);

void ftMh_MS_365_801535B0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMasterHand_SpecialAttrs* attr = fp->ft_data->ext_attr;

    if (fp->x2200_ftcmd_var0 != 0) {
        ftMh_MS_365_8015364C(gobj, fp->ft_bones[LKneeJ].x0_jobj, attr->xF8,
                             attr->xFC);
        fp->x2200_ftcmd_var0 = 0;
    }
    if (fp->x2204_ftcmd_var1 != 0) {
        ftMh_MS_365_8015364C(gobj, fp->ft_bones[RKneeJ].x0_jobj, attr->x100,
                             attr->x104);
        fp->x2204_ftcmd_var1 = 0;
    }
}

void ftMh_MS_365_8015364C(HSD_GObj* gobj, HSD_JObj* arg1, f32 arg2, f32 arg3)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMasterHand_SpecialAttrs* attr = fp->ft_data->ext_attr;
    bool b = false;

    {
        Vec3 vec0;
        lb_8000B1CC(arg1, 0, &vec0);

        {
            Vec3 vec1 = vec0;
            vec0.x += arg2;
            vec0.y += arg3;

            if (ftLib_80087120(gobj) > attr->xEC) {
                b = true;
            }

            it_802F0AE0(gobj, &vec0, &vec1, 126, b, fp->facing_dir, attr->xD4,
                        attr->xD8);
        }
    }
}

void ftMh_MS_365_80153730(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter_ChangeMotionState(gobj, ftMh_MS_Unk366, 0, 0, 0, 1, 0);
    ftAnim_8006EBA4(gobj);
}
