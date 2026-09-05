#include "ftmariospecialhi.h"

#include "inlines.h"
#include "types.h"

#include <Runtime/platform.h>

#include <melee/ft/fighter.h>

#include <melee/ft/forward.h>

#include <melee/ft/ft_081B.h>
#include <melee/ft/ft_084E.h>
#include <melee/ft/ftanim.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/ftparts.h>
#include <melee/ft/types.h>
#include <melee/ft/kinds/ftCommon/ftCo_FallSpecial.h>
#include <melee/ft/kinds/ftCommon/ftCo_Landing.h>

#include <math.h>
#include <dolphin/mtx.h>

void ftMr_SpecialHi_Enter(HSD_GObj* gobj)
{
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    fp->cmd_vars[0] = 0;
    fp->throw_flags = 0;
    Fighter_ChangeMotionState(gobj, ftMr_MS_SpecialHi, 0, 0, 1, 0, NULL);
    ftAnim_8006EBA4(gobj);
}

void ftMr_SpecialAirHi_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMario_DatAttrs* sa = fp->dat_attrs;

    u8 _[4];

    fp->cmd_vars[0] = 0;
    fp->throw_flags = 0;
    fp->self_vel.y = 0;
    fp->self_vel.x = fp->self_vel.x * sa->specialhi.vel_x;
    Fighter_ChangeMotionState(gobj, ftMr_MS_SpecialAirHi, 0, 0, 1, 0, NULL);
    ftAnim_8006EBA4(gobj);
}

/// 0x800E1B24
void ftMr_SpecialHi_Anim(HSD_GObj* gobj)
{
    Fighter* fp;
    ftMario_DatAttrs* sa;

    fp = GET_FIGHTER(gobj);
    sa = (ftMario_DatAttrs*) fp->dat_attrs;
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_80096900(gobj, 0, 1, 0, sa->specialhi.freefall_mobility,
                      sa->specialhi.landing_lag);
    }
}

/// 0x800E1B84
void ftMr_SpecialAirHi_Anim(HSD_GObj* gobj)
{
    u8 _[8];

    ftMr_SpecialHi_Anim(gobj);
}

#define abs(x) (x < 0 ? -x : x)

void ftMr_SpecialHi_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMario_DatAttrs* sa = (ftMario_DatAttrs*) fp->dat_attrs;
    float lstick_x = abs(fp->input.lstick.x);
    if (fp->cmd_vars[0] == 0 && lstick_x > sa->specialhi.momentum_stick_range)
    {
        float deg = sa->specialhi.angle_diff *
                    ((lstick_x - sa->specialhi.momentum_stick_range) /
                     (1.0 - sa->specialhi.momentum_stick_range));
        float rad =
            fp->input.lstick.x > 0 ? -MTXDegToRad(deg) : +MTXDegToRad(deg);
        if (abs(rad) > abs(fp->lstick_angle)) {
            fp->lstick_angle = rad;
        }
    }
    if (ftCheckThrowB3(fp)) {
        if (abs(fp->input.lstick.x) > sa->specialhi.reverse_stick_range) {
            ftCommon_UpdateFacing(fp);
            ftPartSetRotY(fp, 0, M_PI_2 * fp->facing_dir);
        }
    }
}

void ftMr_SpecialAirHi_IASA(HSD_GObj* gobj)
{
    u8 _[8];
    ftMr_SpecialHi_IASA(gobj);
}

void ftMr_SpecialHi_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->ground_or_air == GA_Air) {
        ft_80085154(gobj);
    } else {
        ft_80084FA8(gobj);
    }
}

void ftMr_SpecialAirHi_Phys(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    ftMario_DatAttrs* sa = GetMarioAttr(fp);
    ftCo_DatAttrs* attrs = &fp->co_attrs;

    if (fp->cmd_vars[0] != 0) {
        ft_80085154(gobj);
        fp->self_vel.x *= sa->specialhi.vel_mul;
        fp->self_vel.y *= sa->specialhi.vel_mul;
        fp->self_vel.z *= sa->specialhi.vel_mul;
    } else {
        ftCommon_Fall(fp, sa->specialhi.grav, attrs->terminal_velocity);
        ftCommon_8007CF58(fp);
    }
}

void ftMr_SpecialHi_CheckLanding(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMario_DatAttrs* sa = fp->dat_attrs;
    ftCo_LandingFallSpecial_Enter(gobj, false, sa->specialhi.landing_lag);
}

void ftMr_SpecialHi_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->ground_or_air == GA_Air) {
        if (fp->cmd_vars[0] == 0 || fp->self_vel.y >= 0) {
            ft_80083B68(gobj);
        } else {
            ft_800831CC(gobj, &ftCo_80096CC8, &ftMr_SpecialHi_CheckLanding);
        }
    } else {
        ft_80084104(gobj);
    }
}

void ftMr_SpecialAirHi_Coll(HSD_GObj* gobj)
{
    ftMr_SpecialHi_Coll(gobj);
}
