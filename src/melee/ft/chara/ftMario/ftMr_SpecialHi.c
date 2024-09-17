#include <platform.h>

#include "ftMr_SpecialHi.h"

#include "inlines.h"
#include "math.h"
#include "types.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0D14.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "ftCommon/ftCo_FallSpecial.h"

#include <common_structs.h>
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

// 0x800E1B24
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

// 0x800E1B84
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
            fp->input.lstick.x > 0 ? -(deg_to_rad * deg) : +(deg_to_rad * deg);
        if (abs(rad) > abs(fp->lstick_angle)) {
            fp->lstick_angle = rad;
        }
    }
    if (ftCheckThrowB3(fp)) {
        if (abs(fp->input.lstick.x) > sa->specialhi.reverse_stick_range) {
            ftCommon_8007D9FC(fp);
            ftParts_80075AF0(fp, 0, M_PI_2 * fp->facing_dir);
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
        ftCommon_8007D494(fp, sa->specialhi.grav, attrs->terminal_vel);
        ftCommon_8007CF58(fp);
    }
}

void ftMr_SpecialHi_CheckLanding(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMario_DatAttrs* sa = fp->dat_attrs;
    ftCo_800D5CB0(gobj, 0, sa->specialhi.landing_lag);
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
