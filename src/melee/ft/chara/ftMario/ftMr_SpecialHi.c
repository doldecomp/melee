#include "ftMr_SpecialHi.h"

#include "inlines.h"
#include "types.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"

#include <baselib/random.h>

void ftMr_SpecialHi_Enter(HSD_GObj* gobj)
{
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    fp->x2200_ftcmd_var0 = 0;
    fp->x2210_ThrowFlags.flags = 0;
    Fighter_ChangeMotionState(gobj, ftMr_MS_SpecialHi, 0, NULL, 0, 1, 0);
    ftAnim_8006EBA4(gobj);
}

void ftMr_SpecialAirHi_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMario_DatAttrs* sa = fp->x2D4_specialAttributes;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    fp->x2200_ftcmd_var0 = 0;
    fp->x2210_ThrowFlags.flags = 0;
    fp->x80_self_vel.y = 0;
    fp->x80_self_vel.x = fp->x80_self_vel.x * sa->specialhi.vel_x;
    Fighter_ChangeMotionState(gobj, ftMr_MS_SpecialAirHi, 0, NULL, 0, 1, 0);
    ftAnim_8006EBA4(gobj);
}

// 0x800E1B24
void ftMr_SpecialHi_Anim(HSD_GObj* gobj)
{
    Fighter* fp;
    ftMario_DatAttrs* sa;

    fp = GET_FIGHTER(gobj);
    sa = (ftMario_DatAttrs*) fp->x2D4_specialAttributes;
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_80096900(gobj, 0, 1, 0, sa->specialhi.freefall_mobility,
                    sa->specialhi.landing_lag);
    }
}

// 0x800E1B84
void ftMr_SpecialAirHi_Anim(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    ftMr_SpecialHi_Anim(gobj);
}

#define abs(x) (x < 0 ? -x : x)

// https://decomp.me/scratch/9AoMu
inline void ftMario_SpecialHi_CalcAngle(HSD_GObj* gobj)
{
    Fighter* fp;
    ftMario_DatAttrs* sa;

    f32 lstick_x;

    bool throwflags_b3;
    fp = GET_FIGHTER(gobj);

    sa = (ftMario_DatAttrs*) fp->x2D4_specialAttributes;

    lstick_x = abs(fp->input.x620_lstick_x);

    if (fp->x2200_ftcmd_var0 == 0 &&
        lstick_x > sa->specialhi.momentum_stick_range)
    {
        f32 deg = (f64) sa->specialhi.angle_diff *
                  ((lstick_x - sa->specialhi.momentum_stick_range) /
                   (1.0 - sa->specialhi.momentum_stick_range));

        f32 rad = fp->input.x620_lstick_x > 0 ? -(DEG_TO_RAD * deg)
                                              : +(DEG_TO_RAD * deg);

        if (abs(rad) > abs(fp->x6BC_inputStickangle)) {
            fp->x6BC_inputStickangle = rad;
        }
    }

    if (fp->x2210_ThrowFlags.b3) {
        fp->x2210_ThrowFlags.b3 = false;
        throwflags_b3 = true;
    } else {
        throwflags_b3 = false;
    }

    if (throwflags_b3) {
        if (abs(fp->input.x620_lstick_x) > sa->specialhi.reverse_stick_range) {
            ftCommon_8007D9FC(fp);
            ftParts_80075AF0(fp, 0, (f32) (M_PI_2 * fp->facing_dir));
        }
    }
}

void ftMr_SpecialHi_IASA(HSD_GObj* gobj)
{
    ftMario_SpecialHi_CalcAngle(gobj);
}

void ftMr_SpecialAirHi_IASA(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16];
#endif

    ftMario_SpecialHi_CalcAngle(gobj);
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
    attr* attrs = &fp->x110_attr;

    if (fp->x2200_ftcmd_var0 != 0) {
        ft_80085154(gobj);
        fp->x80_self_vel.x *= sa->specialhi.vel_mul;
        fp->x80_self_vel.y *= sa->specialhi.vel_mul;
        fp->x80_self_vel.z *= sa->specialhi.vel_mul;
    } else {
        ftCommon_8007D494(fp, sa->specialhi.grav,
                          attrs->x170_TerminalVelocity);
        ftCommon_8007CF58(fp);
    }
}

void ftMr_SpecialHi_CheckLanding(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMario_DatAttrs* sa = fp->x2D4_specialAttributes;
    ft_800D5CB0(gobj, 0, sa->specialhi.landing_lag);
}

void ftMr_SpecialHi_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->ground_or_air == GA_Air) {
        if (fp->x2200_ftcmd_var0 == 0 || fp->x80_self_vel.y >= 0) {
            ft_80083B68(gobj);
        } else {
            ft_800831CC(gobj, &ft_80096CC8, &ftMr_SpecialHi_CheckLanding);
        }
    } else {
        ft_80084104(gobj);
    }
}

void ftMr_SpecialAirHi_Coll(HSD_GObj* gobj)
{
    ftMr_SpecialHi_Coll(gobj);
}
