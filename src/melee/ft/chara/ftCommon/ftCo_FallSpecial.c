#include <platform.h>

#include "ftCo_FallSpecial.h"

#include "ftCo_DamageFall.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ft_0CEE.h"
#include "ft/ft_0D14.h"
#include "ft/ftchangeparam.h"
#include "ft/ftcommon.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/ftCo_JumpAerial.h"
#include "ftCommon/types.h"
#include "mp/mplib.h"
#include "un/un_2FC9.h"
#include "vi/vi1202.h"

#include <common_structs.h>
#include <math.h>
#include <dolphin/mtx.h>

void ftCo_800968C8(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftCo_80096900(gobj, 1, 0, true, 1, fp->x2EC);
}

/// @todo Real solution is @c 0. Inline needs to be fixed.
#define SOLUTION 1
void ftCo_80096900(Fighter_GObj* gobj, int arg1, int arg2, bool allow_interrupt,
                   float arg4, float arg5)
{
#if SOLUTION == 0
    ftCo_800969D8(gobj, arg1, arg2, allow_interrupt, arg4, arg5, 0);
#elif SOLUTION == 1

    ftCo_DatAttrs* ca;
    Fighter* fp;
    fp = GET_FIGHTER(gobj);
    ca = &fp->co_attrs;
    if (fp->x2224_b2) {
        ftCo_80090780(gobj);
        return;
    }
    Fighter_ChangeMotionState(gobj, ftCo_MS_FallSpecial, Ft_MF_KeepFastFall, 0,
                              1, 0, NULL);
    fp->mv.co.fallspecial.x8 = ca->air_drift_max * arg4;
    fp->mv.co.fallspecial.xC = arg1;
    fp->mv.co.fallspecial.x10 = arg2;
    fp->mv.co.fallspecial.x14 = arg5;
    fp->mv.co.fallspecial.allow_interrupt = allow_interrupt;
    fp->mv.co.fallspecial.x0 = 26;
    fp->mv.co.fallspecial.x4 = 0;
    if (fp->ground_or_air == GA_Ground) {
        ftCommon_8007D60C(fp);
    } else {
        ftCommon_8007D698(fp);
    }
    un_80322598(fp->x8_spawnNum, fp->cur_pos.y);
#endif
}
#undef SOLUTION

void ftCo_800969D8(Fighter_GObj* gobj, int arg1, int arg2, int allow_interrupt,
                   float arg4, float arg5, float arg6)
{
    u8 _[8] = { 0 };
    ftCo_DatAttrs* ca;
    Fighter* fp;
    fp = GET_FIGHTER(gobj);
    ca = &fp->co_attrs;
    if (fp->x2224_b2) {
        ftCo_80090780(gobj);
        return;
    }
    Fighter_ChangeMotionState(gobj, ftCo_MS_FallSpecial, Ft_MF_KeepFastFall, 0,
                              1, arg6, NULL);
    fp->mv.co.fallspecial.x8 = ca->air_drift_max * arg4;
    fp->mv.co.fallspecial.xC = arg1;
    fp->mv.co.fallspecial.x10 = arg2;
    fp->mv.co.fallspecial.x14 = arg5;
    fp->mv.co.fallspecial.allow_interrupt = allow_interrupt;
    fp->mv.co.fallspecial.x0 = 26;
    fp->mv.co.fallspecial.x4 = 0;
    if (fp->ground_or_air == GA_Ground) {
        ftCommon_8007D60C(fp);
    }
    un_80322598(fp->x8_spawnNum, fp->cur_pos.y);
}

void ftCo_FallSpecial_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftCo_Fall_Anim_Inner(gobj, &fp->mv.co.fallspecial.x4, ftCo_SM_FallSpecial,
                         ftCo_SM_FallSpecialF, ftCo_SM_FallSpecialB);
    ftCo_800CC988(gobj, fp->mv.co.fallspecial.x4);
}

void ftCo_FallSpecial_IASA(Fighter_GObj* gobj)
{
    RETURN_IF(ftCo_800CEE70(gobj));
    RETURN_IF(ftCo_800D705C(gobj));
    RETURN_IF(ftCo_800CB870(gobj));
}

void ftCo_FallSpecial_Phys(Fighter_GObj* gobj)
{
    float f1;
    float lstick_x;
    float base;

    ftCo_DatAttrs* ca;
    Fighter* fp;
    fp = GET_FIGHTER(gobj);
    ca = &fp->co_attrs;
    ftCommon_8007D528(fp);
    if (fp->mv.co.fallspecial.xC != 0) {
        if (fp->x221A_b4) {
            ftCommon_8007D4E4(fp);
        } else {
            ftCommon_8007D494(fp, ca->grav, ca->terminal_vel);
        }
        {
            f1 = ca->air_drift_stick_mul;
            lstick_x = fp->input.lstick.x;
            f1 = lstick_x * f1;
            base =
                lstick_x > 0 ? ca->aerial_drift_base : -ca->aerial_drift_base;

            ftCommon_8007D140(fp, f1 + base, lstick_x * ca->air_drift_max,
                              ca->aerial_friction);
        }
    } else {
        if (fp->x221A_b4) {
            ftCommon_8007D4E4(fp);
        } else {
            ftCommon_8007D494(fp, ca->grav, ca->fast_fall_velocity);
        }
        {
            f1 = ca->air_drift_stick_mul;
            lstick_x = fp->input.lstick.x;
            f1 = lstick_x * f1;
            base =
                lstick_x > 0 ? ca->aerial_drift_base : -ca->aerial_drift_base;
            {
                float drift_max = lstick_x * ca->air_drift_max;
#define mv_x8 fp->mv.co.fallspecial.x8
                float tmp4 = f1 + base;
                if (ABS(drift_max) > mv_x8) {
                    drift_max = drift_max < 0 ? -mv_x8 : mv_x8;
                }
                ftCommon_8007D140(fp, tmp4, drift_max, ca->aerial_friction);
            }
        }
    }
}

void ftCo_FallSpecial_Coll(Fighter_GObj* gobj)
{
    ft_80083090(gobj, ftCo_80096CC8, ftCo_80096D28);
}

bool ftCo_80096CC8(Fighter_GObj* gobj, enum_t arg1)
{
    u8 _[8] = { 0 };
    Fighter* fp = gobj->user_data;
    if (arg1 != -1 && (!(mpLib_80054CEC(arg1) & (1 << 8)) ||
                       fp->input.lstick.y > p_ftCommonData->x25C))
    {
        return true;
    }
    return false;
}

void ftCo_80096D28(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->mv.co.fallspecial.x10 || fp->self_vel.y < ftCo_800D0EC8(fp)) {
        ftCo_800D5CB0(gobj, fp->mv.co.fallspecial.allow_interrupt,
                      fp->mv.co.fallspecial.x14);
    } else {
        ft_8008A2BC(gobj);
    }
}
