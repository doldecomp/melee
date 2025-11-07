#include "ftCo_FallSpecial.h"

#include "ftCo_DamageFall.h"

#include <platform.h>

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ftchangeparam.h"
#include "ft/ftcommon.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Attack100.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/ftCo_ItemParasolOpen.h"
#include "ftCommon/ftCo_JumpAerial.h"
#include "ftCommon/ftCo_Landing.h"
#include "ftCommon/types.h"
#include "mp/mplib.h"
#include "vi/vi1202.h"

#include <common_structs.h>
#include <math.h>
#include <dolphin/mtx.h>

void ftCo_800968C8(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_80096900(gobj, 1, 0, true, 1, fp->x2EC);
}

static inline void inline0(Fighter_GObj* gobj, int arg1, int arg2,
                           bool allow_interrupt, float mobility,
                           float landing_lag, float arg6, bool unk)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_DatAttrs* ca = &fp->co_attrs;
    if (fp->x2224_b2) {
        ftCo_80090780(gobj);
        return;
    }
    Fighter_ChangeMotionState(gobj, ftCo_MS_FallSpecial, Ft_MF_KeepFastFall, 0,
                              1, arg6, NULL);
    fp->mv.co.fallspecial.mobility = ca->air_drift_max * mobility;
    fp->mv.co.fallspecial.xC = arg1;
    fp->mv.co.fallspecial.x10 = arg2;
    fp->mv.co.fallspecial.landing_lag = landing_lag;
    fp->mv.co.fallspecial.allow_interrupt = allow_interrupt;
    fp->mv.co.fallspecial.x0 = 26;
    fp->mv.co.fallspecial.x4 = 0;
    if (fp->ground_or_air == GA_Ground) {
        ftCommon_8007D60C(fp);
    } else if (unk) {
        ftCommon_UseAllJumps(fp);
    }
    un_80322598(fp->x8_spawnNum, fp->cur_pos.y);
}

void ftCo_80096900(Fighter_GObj* gobj, int arg1, int arg2,
                   bool allow_interrupt, float mobility, float landing_lag)
{
    inline0(gobj, arg1, arg2, allow_interrupt, mobility, landing_lag, 0, true);
}

void ftCo_800969D8(Fighter_GObj* gobj, int arg1, int arg2, int allow_interrupt,
                   float mobility, float landing_lag, float arg6)
{
    PAD_STACK(8);
    inline0(gobj, arg1, arg2, allow_interrupt, mobility, landing_lag, arg6,
            false);
}

void ftCo_FallSpecial_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
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
    float lstick_x, drift, target_vel;

    ftCo_DatAttrs* ca;
    Fighter* fp;
    fp = GET_FIGHTER(gobj);
    ca = &fp->co_attrs;

    ftCommon_CheckFallFast(fp);
    if (fp->mv.co.fallspecial.xC != 0) {
        if (fp->fall_fast) {
            ftCommon_FallFast(fp);
        } else {
            ftCommon_Fall(fp, ca->grav, ca->terminal_vel);
        }
        {
            lstick_x = fp->input.lstick.x;
            drift = lstick_x * ca->air_drift_stick_mul;
            drift +=
                lstick_x > 0 ? ca->aerial_drift_base : -ca->aerial_drift_base;
            target_vel = lstick_x * ca->air_drift_max;
            ftCommon_8007D140(fp, drift, target_vel, ca->aerial_friction);
        }
    } else {
        if (fp->fall_fast) {
            ftCommon_FallFast(fp);
        } else {
            ftCommon_Fall(fp, ca->grav, ca->fast_fall_velocity);
        }
        {
            lstick_x = fp->input.lstick.x;
            drift = lstick_x * ca->air_drift_stick_mul;
            drift +=
                lstick_x > 0 ? ca->aerial_drift_base : -ca->aerial_drift_base;
            target_vel = lstick_x * ca->air_drift_max;
            if (ABS(target_vel) > fp->mv.co.fallspecial.mobility) {
                target_vel = target_vel < 0 ? -fp->mv.co.fallspecial.mobility
                                            : fp->mv.co.fallspecial.mobility;
            }
            ftCommon_8007D140(fp, drift, target_vel, ca->aerial_friction);
        }
    }
}

void ftCo_FallSpecial_Coll(Fighter_GObj* gobj)
{
    ft_80083090(gobj, ftCo_80096CC8, ftCo_80096D28);
}

bool ftCo_80096CC8(Fighter_GObj* gobj, int line_id)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (line_id != -1 && (!(mpLineGetFlags(line_id) & LINE_FLAG_PLATFORM) ||
                          fp->input.lstick.y > p_ftCommonData->x25C))
    {
        return true;
    }
    return false;
}

void ftCo_80096D28(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->mv.co.fallspecial.x10 || fp->self_vel.y < ftCo_800D0EC8(fp)) {
        ftCo_LandingFallSpecial_Enter(gobj,
                                      fp->mv.co.fallspecial.allow_interrupt,
                                      fp->mv.co.fallspecial.landing_lag);
    } else {
        ft_8008A2BC(gobj);
    }
}
