#include "forward.h"
#include "ftmario.h"
#include "inlines.h"
#include "types.h"

#include "ft/code_80081B38.h"
#include "ft/ft_unknown_006.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "it/forward.h"

#include <baselib/random.h>

void ftMario_SpecialHi_StartAction(HSD_GObj* gobj)
{
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    fp->x2200_ftcmd_var0 = 0;
    fp->x2210_ThrowFlags.flags = 0;
    Fighter_ActionStateChange_800693AC(gobj, ftMario_AS_SpecialHi, 0, NULL,
                                       0.0f, 1.0f, 0.0f);
    func_8006EBA4(gobj);
}

void ftMario_SpecialAirHi_StartAction(HSD_GObj* gobj)
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
    Fighter_ActionStateChange_800693AC(gobj, ftMario_AS_SpecialAirHi, 0, NULL,
                                       0.0f, 1.0f, 0.0f);
    func_8006EBA4(gobj);
}

// 0x800E1B24
void ftMario_SpecialHi_Anim(HSD_GObj* gobj)
{
    Fighter* fp;
    ftMario_DatAttrs* sa;

    fp = GET_FIGHTER(gobj);
    sa = (ftMario_DatAttrs*) fp->x2D4_specialAttributes;
    if (!ftAnim_IsFramesRemaining(gobj)) {
        func_80096900(gobj, 0, 1, 0, sa->specialhi.freefall_mobility,
                      sa->specialhi.landing_lag);
    }
}

// 0x800E1B84
void ftMario_SpecialAirHi_Anim(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    ftMario_SpecialHi_Anim(gobj);
}

#define abs(x) (x < 0.0f ? -x : x)

// https://decomp.me/scratch/9AoMu
inline void ftMario_SpecialHi_CalcAngle(HSD_GObj* gobj)
{
    Fighter* fp;
    ftMario_DatAttrs* sa;

    f32 inputStickangle, lstick_x;
    f32 tmp_expr;
    f32 tmp;

    bool throwflags_b3;
    fp = GET_FIGHTER(gobj);

    sa = (ftMario_DatAttrs*) fp->x2D4_specialAttributes;

    lstick_x = abs(fp->input.x620_lstick_x);

    if (fp->x2200_ftcmd_var0 == 0) {
        if (lstick_x > sa->specialhi.momentum_stick_range) {
            tmp_expr = (f32) ((f64) sa->specialhi.angle_diff *
                              (lstick_x - sa->specialhi.momentum_stick_range) /
                              (1.0 - sa->specialhi.momentum_stick_range));

            tmp = fp->input.x620_lstick_x > 0 ? -(DEG_TO_RAD * tmp_expr)
                                              : +(DEG_TO_RAD * tmp_expr);
            inputStickangle = fp->x6BC_inputStickangle;

            if (abs(tmp) > abs(inputStickangle)) {
                fp->x6BC_inputStickangle = tmp;
            }
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
            func_8007D9FC(fp);
            func_80075AF0(fp, 0, (f32) (M_PI_2 * fp->facing_dir));
        }
    }
}

void ftMario_SpecialHi_IASA(HSD_GObj* gobj)
{
    ftMario_SpecialHi_CalcAngle(gobj);
}

void ftMario_SpecialAirHi_IASA(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16];
#endif

    ftMario_SpecialHi_CalcAngle(gobj);
}

void ftMario_SpecialHi_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->ground_or_air == GA_Air)
        func_80085154(gobj);
    else
        func_80084FA8(gobj);
}

void ftMario_SpecialAirHi_Phys(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    ftMario_DatAttrs* sa = GetMarioAttr(fp);
    attr* attrs = &fp->x110_attr;

    if (fp->x2200_ftcmd_var0 != 0) {
        func_80085154(gobj);
        fp->x80_self_vel.x *= sa->specialhi.vel_mul;
        fp->x80_self_vel.y *= sa->specialhi.vel_mul;
        fp->x80_self_vel.z *= sa->specialhi.vel_mul;
    } else {
        func_8007D494(fp, sa->specialhi.grav, attrs->x170_TerminalVelocity);
        func_8007CF58(fp);
    }
}

void ftMario_SpecialHi_CheckLanding(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMario_DatAttrs* sa = fp->x2D4_specialAttributes;
    func_800D5CB0(gobj, 0, sa->specialhi.landing_lag);
}

void ftMario_SpecialHi_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->ground_or_air == GA_Air) {
        if (fp->x2200_ftcmd_var0 == 0 || fp->x80_self_vel.y >= 0.0f) {
            func_80083B68(gobj);
        } else {
            func_800831CC(gobj, &func_80096CC8,
                          &ftMario_SpecialHi_CheckLanding);
        }
    } else {
        func_80084104(gobj);
    }
}

void ftMario_SpecialAirHi_Coll(HSD_GObj* gobj)
{
    ftMario_SpecialHi_Coll(gobj);
}
