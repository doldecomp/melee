#include "ftLg_SpecialHi.h"

#include "math.h"
#include "types.h"

#include <platform.h>

#include "forward.h"

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

// 0x80143FC8
// https://decomp.me/scratch/MAoxx // Luigi's grounded Super Jump Punch Action
// State handler
void ftLg_SpecialHi_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    fp->cmd_vars[0] = 0;
    fp->throw_flags = 0;
    Fighter_ChangeMotionState(gobj, ftLg_MS_SpecialHi, 0, 0.0f, 1.0f, 0.0f,
                              NULL);
    ftAnim_8006EBA4(gobj);
}

/// Luigi's aerial Super Jump Punch Motion State handler
void ftLg_SpecialAirHi_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftLuigiAttributes* luigiAttrs = fp->dat_attrs;

    u8 _[4];

    fp->cmd_vars[0] = 0;
    fp->throw_flags = 0;
    fp->self_vel.y = 0.0f;
    fp->self_vel.x *= luigiAttrs->x64_LUIGI_SUPERJUMP_VEL_X;
    Fighter_ChangeMotionState(gobj, ftLg_MS_SpecialAirHi, 0, 0.0f, 1.0f, 0.0f,
                              NULL);
    ftAnim_8006EBA4(gobj);
}

/// Luigi's grounded Super Jump Punch Animation callback
void ftLg_SpecialHi_Anim(HSD_GObj* gobj)
{
    ftLuigiAttributes* luigiAttrs = GET_FIGHTER(gobj)->dat_attrs;

    u8 _[4];

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_80096900(gobj, 0, 1, 0,
                      luigiAttrs->x50_LUIGI_SUPERJUMP_FREEFALL_MOBILITY,
                      luigiAttrs->x54_LUIGI_SUPERJUMP_LANDING_LAG);
    }
}

/// Luigi's aerial Super Jump Punch Animation callback
void ftLg_SpecialAirHi_Anim(HSD_GObj* gobj)
{
    ftLuigiAttributes* luigiAttrs = GET_FIGHTER(gobj)->dat_attrs;

    u8 _[12];

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_80096900(gobj, 0, 1, 0,
                      luigiAttrs->x50_LUIGI_SUPERJUMP_FREEFALL_MOBILITY,
                      luigiAttrs->x54_LUIGI_SUPERJUMP_LANDING_LAG);
    }
}

// 0x80144158
// https://decomp.me/scratch/M9q8b // Luigi's grounded Super Jump Punch IASA
// callback
void ftLg_SpecialHi_IASA(HSD_GObj* gobj)
{
    Fighter* fp;
    ftLuigiAttributes* luigiAttrs;
    float temp_range;
    float superJump_StickRange;
    float stick_x;
    float control;
    float control_2;
    float stick_range;
    float stick_range_2;
    float stick_angle;

    fp = GET_FIGHTER(gobj);
    stick_x = fp->input.lstick.x;
    luigiAttrs = fp->dat_attrs;
    stick_range = stickGetDir(fp->input.lstick.x, 0.0f);
    if ((u32) fp->cmd_vars[0] == 0U) {
        superJump_StickRange =
            luigiAttrs->x5C_LUIGI_SUPERJUMP_MOMENTUM_STICK_RANGE;
        if (stick_range > superJump_StickRange) {
            temp_range =
                (float) ((f64) luigiAttrs->x60_LUIGI_SUPERJUMP_ANGLE_DIFF *
                         ((f64) (stick_range - superJump_StickRange) /
                          (1.0 - (f64) superJump_StickRange)));
            if (stick_x > 0.0f) {
                control = -(0.01745329238474369f * temp_range);
            } else {
                control = 0.01745329238474369f * temp_range;
            }
            control_2 = fp->lstick_angle;
            stick_angle = control_2;
            if (stick_angle < 0.0f) {
                stick_angle = -stick_angle;
            }
            if (control < 0.0f) {
                stick_range_2 = -control;
            } else {
                stick_range_2 = control;
            }
            if (stick_range_2 > stick_angle) {
                fp->lstick_angle = control;
            }
        }
    }
    if (ftCheckThrowB3(fp)) {
        control = fp->input.lstick.x;
        if (control < 0.0f) {
            control = -control;
        }
        if (control > luigiAttrs->x58_LUIGI_SUPERJUMP_REVERSE_STICK_RANGE) {
            ftCommon_8007D9FC(fp);
            ftParts_80075AF0(fp, 0, (M_PI / 2) * fp->facing_dir);
        }
    }
}

/// Luigi's aerial Super Jump Punch IASA callback
void ftLg_SpecialAirHi_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    float stick_x = fp->input.lstick.x;
    ftLuigiAttributes* luigiAttrs = fp->dat_attrs;
    float stick_range = stickGetDir(fp->input.lstick.x, 0.0f);
    float temp_range;
    float superJump_StickRange;
    float control;
    float control_2;
    float stick_range_2;
    float stick_angle;

    u8 _[12];

    if (fp->cmd_vars[0] == 0) {
        superJump_StickRange =
            luigiAttrs->x5C_LUIGI_SUPERJUMP_MOMENTUM_STICK_RANGE;
        if (stick_range > superJump_StickRange) {
            temp_range =
                (float) ((f64) luigiAttrs->x60_LUIGI_SUPERJUMP_ANGLE_DIFF *
                         ((f64) (stick_range - superJump_StickRange) /
                          (1.0 - (f64) superJump_StickRange)));
            if (stick_x > 0.0f) {
                control = -(0.01745329238474369f * temp_range);
            } else {
                control = 0.01745329238474369f * temp_range;
            }
            control_2 = fp->lstick_angle;
            stick_angle = control_2;
            if (stick_angle < 0.0f) {
                stick_angle = -stick_angle;
            }
            if (control < 0.0f) {
                stick_range_2 = -control;
            } else {
                stick_range_2 = control;
            }
            if (stick_range_2 > stick_angle) {
                fp->lstick_angle = control;
            }
        }
    }
    if (ftCheckThrowB3(fp)) {
        control = fp->input.lstick.x;
        if (control < 0.0f) {
            control = -control;
        }
        if (control > luigiAttrs->x58_LUIGI_SUPERJUMP_REVERSE_STICK_RANGE) {
            ftCommon_8007D9FC(fp);
            ftParts_80075AF0(fp, 0, (M_PI / 2) * fp->facing_dir);
        }
    }
}

// 0x801443E8
// https://decomp.me/scratch/TmnDt // Luigi's grounded Super Jump Punch Physics
// callback
void ftLg_SpecialHi_Phys(HSD_GObj* gobj)
{
    if ((s32) GET_FIGHTER(gobj)->ground_or_air == GA_Air) {
        ft_80085154(gobj);
        return;
    }
    ft_80084FA8(gobj);
}

// 0x80144420
// https://decomp.me/scratch/vIYcm // Luigi's aerial Super Jump Punch Physics
// callback
void ftLg_SpecialAirHi_Phys(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    ftLuigiAttributes* luigiAttrs = getFtSpecialAttrs(fp);
    ftCo_DatAttrs* ca = &fp->co_attrs;

    if ((u32) fp->cmd_vars[0] != 0U) {
        ft_80085154(gobj);
        fp->self_vel.x *= luigiAttrs->x6C_LUIGI_SUPERJUMP_VEL_Y;
        fp->self_vel.y *= luigiAttrs->x6C_LUIGI_SUPERJUMP_VEL_Y;
        fp->self_vel.z *= luigiAttrs->x6C_LUIGI_SUPERJUMP_VEL_Y;
        return;
    }
    ftCommon_8007D494(fp, luigiAttrs->x68_LUIGI_SUPERJUMP_GRAVITY_START,
                      ca->terminal_vel);
    ftCommon_8007CF58(fp);
}

// 0x801444B4
// https://decomp.me/scratch/l7min // Luigi's Super Jump Punch Landing check
void ftLg_SpecialHi_CheckLanding(HSD_GObj* gobj)
{
    ftCo_LandingFallSpecial_Enter(gobj, false,
                  ((ftLuigiAttributes*) GET_FIGHTER(gobj)->dat_attrs)
                      ->x54_LUIGI_SUPERJUMP_LANDING_LAG);
}

// 0x801444E4
// https://decomp.me/scratch/5aRWp // Luigi's grounded Super Jump Punch
// Collision callback
void ftLg_SpecialHi_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if ((s32) fp->ground_or_air == GA_Air) {
        if (((u32) fp->cmd_vars[0] == 0U) || (fp->self_vel.y >= 0.0f)) {
            ft_80083B68(gobj);
            return;
        }
        ft_800831CC(gobj, ftCo_80096CC8, ftLg_SpecialHi_CheckLanding);
        return;
    }
    ft_80084104(gobj);
}

// 0x80144554
// https://decomp.me/scratch/h03kd // Luigi's aerial Super Jump Punch Collision
// callback
void ftLg_SpecialAirHi_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if ((s32) fp->ground_or_air == GA_Air) {
        if (((u32) fp->cmd_vars[0] == 0U) || (fp->self_vel.y >= 0.0f)) {
            ft_80083B68(gobj);
            return;
        }
        ft_800831CC(gobj, ftCo_80096CC8, ftLg_SpecialHi_CheckLanding);
        return;
    }
    ft_80084104(gobj);
}
