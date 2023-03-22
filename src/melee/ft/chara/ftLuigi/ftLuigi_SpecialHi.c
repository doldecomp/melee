#include "forward.h"

#include "ftluigi.h"

#include "ef/efsync.h"
#include "ft/code_80081B38.h"
#include "ft/ftparts.h"
#include "ft/ftunk_04.h"
#include "ft/inlines.h"

// 0x80143FC8
// https://decomp.me/scratch/MAoxx // Luigi's grounded Super Jump Punch Action
// State handler
void ftLuigi_SpecialHi_StartMotion(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    fp->x2200_ftcmd_var0 = 0;
    fp->x2210_ThrowFlags.flags = 0;
    Fighter_ChangeMotionState(gobj, MS_LUIGI_SPECIALHI, 0, NULL, 0.0f, 1.0f,
                              0.0f);
    ftAnim_8006EBA4(gobj);
}

/// Luigi's aerial Super Jump Punch Motion State handler
void ftLuigi_SpecialAirHi_StartMotion(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftLuigiAttributes* luigiAttrs = fp->x2D4_specialAttributes;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    fp->x2200_ftcmd_var0 = 0;
    fp->x2210_ThrowFlags.flags = 0;
    fp->x80_self_vel.y = 0.0f;
    fp->x80_self_vel.x *= luigiAttrs->x64_LUIGI_SUPERJUMP_VEL_X;
    Fighter_ChangeMotionState(gobj, MS_LUIGI_SPECIALAIRHI, 0, NULL, 0.0f, 1.0f,
                              0.0f);
    ftAnim_8006EBA4(gobj);
}

/// Luigi's grounded Super Jump Punch Animation callback
void ftLuigi_SpecialHi_Anim(HSD_GObj* gobj)
{
    ftLuigiAttributes* luigiAttrs = GET_FIGHTER(gobj)->x2D4_specialAttributes;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    if (!ftAnim_IsFramesRemaining(gobj)) {
        func_80096900(gobj, 0, 1, 0,
                      luigiAttrs->x50_LUIGI_SUPERJUMP_FREEFALL_MOBILITY,
                      luigiAttrs->x54_LUIGI_SUPERJUMP_LANDING_LAG);
    }
}

/// Luigi's aerial Super Jump Punch Animation callback
void ftLuigi_SpecialAirHi_Anim(HSD_GObj* gobj)
{
    ftLuigiAttributes* luigiAttrs = GET_FIGHTER(gobj)->x2D4_specialAttributes;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[12];
#endif

    if (!ftAnim_IsFramesRemaining(gobj)) {
        func_80096900(gobj, 0, 1, 0,
                      luigiAttrs->x50_LUIGI_SUPERJUMP_FREEFALL_MOBILITY,
                      luigiAttrs->x54_LUIGI_SUPERJUMP_LANDING_LAG);
    }
}

// 0x80144158
// https://decomp.me/scratch/M9q8b // Luigi's grounded Super Jump Punch IASA
// callback
void ftLuigi_SpecialHi_IASA(HSD_GObj* gobj)
{
    Fighter* fp;
    ftLuigiAttributes* luigiAttrs;
    f32 temp_range;
    f32 superJump_StickRange;
    f32 stick_x;
    f32 control;
    f32 control_2;
    f32 stick_range;
    f32 stick_range_2;
    f32 stick_angle;
    bool flag;

    fp = GET_FIGHTER(gobj);
    stick_x = fp->input.x620_lstick_x;
    luigiAttrs = fp->x2D4_specialAttributes;
    stick_range = stickGetDir(fp->input.x620_lstick_x, 0.0f);
    if ((u32) fp->x2200_ftcmd_var0 == 0U) {
        superJump_StickRange =
            luigiAttrs->x5C_LUIGI_SUPERJUMP_MOMENTUM_STICK_RANGE;
        if (stick_range > superJump_StickRange) {
            temp_range =
                (f32) ((f64) luigiAttrs->x60_LUIGI_SUPERJUMP_ANGLE_DIFF *
                       ((f64) (stick_range - superJump_StickRange) /
                        (1.0 - (f64) superJump_StickRange)));
            if (stick_x > 0.0f) {
                control = -(0.01745329238474369f * temp_range);
            } else {
                control = 0.01745329238474369f * temp_range;
            }
            control_2 = fp->x6BC_inputStickangle;
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
                fp->x6BC_inputStickangle = control;
            }
        }
    }
    if (fp->x2210_ThrowFlags.b3 != 0) {
        fp->x2210_ThrowFlags.b3 = 0;
        flag = true;
    } else {
        flag = false;
    }
    if (flag != false) {
        control = fp->input.x620_lstick_x;
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
void ftLuigi_SpecialAirHi_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    f32 stick_x = fp->input.x620_lstick_x;
    ftLuigiAttributes* luigiAttrs = fp->x2D4_specialAttributes;
    f32 stick_range = stickGetDir(fp->input.x620_lstick_x, 0.0f);
    f32 temp_range;
    f32 superJump_StickRange;
    f32 control;
    f32 control_2;
    f32 stick_range_2;
    f32 stick_angle;
    bool flag;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[12];
#endif

    if (fp->x2200_ftcmd_var0 == 0) {
        superJump_StickRange =
            luigiAttrs->x5C_LUIGI_SUPERJUMP_MOMENTUM_STICK_RANGE;
        if (stick_range > superJump_StickRange) {
            temp_range =
                (f32) ((f64) luigiAttrs->x60_LUIGI_SUPERJUMP_ANGLE_DIFF *
                       ((f64) (stick_range - superJump_StickRange) /
                        (1.0 - (f64) superJump_StickRange)));
            if (stick_x > 0.0f) {
                control = -(0.01745329238474369f * temp_range);
            } else {
                control = 0.01745329238474369f * temp_range;
            }
            control_2 = fp->x6BC_inputStickangle;
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
                fp->x6BC_inputStickangle = control;
            }
        }
    }
    if (fp->x2210_ThrowFlags.b3 != 0) {
        fp->x2210_ThrowFlags.b3 = 0;
        flag = true;
    } else {
        flag = false;
    }
    if (flag != false) {
        control = fp->input.x620_lstick_x;
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
void ftLuigi_SpecialHi_Phys(HSD_GObj* gobj)
{
    if ((s32) GET_FIGHTER(gobj)->ground_or_air == GA_Air) {
        func_80085154(gobj);
        return;
    }
    func_80084FA8(gobj);
}

// 0x80144420
// https://decomp.me/scratch/vIYcm // Luigi's aerial Super Jump Punch Physics
// callback
void ftLuigi_SpecialAirHi_Phys(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    ftLuigiAttributes* luigiAttrs = getFtSpecialAttrs(fp);
    attr* ftAttrs = &fp->x110_attr;

    if ((u32) fp->x2200_ftcmd_var0 != 0U) {
        func_80085154(gobj);
        fp->x80_self_vel.x *= luigiAttrs->x6C_LUIGI_SUPERJUMP_VEL_Y;
        fp->x80_self_vel.y *= luigiAttrs->x6C_LUIGI_SUPERJUMP_VEL_Y;
        fp->x80_self_vel.z *= luigiAttrs->x6C_LUIGI_SUPERJUMP_VEL_Y;
        return;
    }
    ftCommon_8007D494(fp, luigiAttrs->x68_LUIGI_SUPERJUMP_GRAVITY_START,
                      ftAttrs->x170_TerminalVelocity);
    ftCommon_8007CF58(fp);
}

// 0x801444B4
// https://decomp.me/scratch/l7min // Luigi's Super Jump Punch Landing check
void ftLuigi_SpecialHi_CheckLanding(HSD_GObj* gobj)
{
    func_800D5CB0(
        gobj, 0,
        ((ftLuigiAttributes*) GET_FIGHTER(gobj)->x2D4_specialAttributes)
            ->x54_LUIGI_SUPERJUMP_LANDING_LAG);
}

// 0x801444E4
// https://decomp.me/scratch/5aRWp // Luigi's grounded Super Jump Punch
// Collision callback
void ftLuigi_SpecialHi_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if ((s32) fp->ground_or_air == GA_Air) {
        if (((u32) fp->x2200_ftcmd_var0 == 0U) || (fp->x80_self_vel.y >= 0.0f))
        {
            func_80083B68(gobj);
            return;
        }
        func_800831CC(gobj, func_80096CC8, ftLuigi_SpecialHi_CheckLanding);
        return;
    }
    func_80084104(gobj);
}

// 0x80144554
// https://decomp.me/scratch/h03kd // Luigi's aerial Super Jump Punch Collision
// callback
void ftLuigi_SpecialAirHi_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if ((s32) fp->ground_or_air == GA_Air) {
        if (((u32) fp->x2200_ftcmd_var0 == 0U) || (fp->x80_self_vel.y >= 0.0f))
        {
            func_80083B68(gobj);
            return;
        }
        func_800831CC(gobj, func_80096CC8, ftLuigi_SpecialHi_CheckLanding);
        return;
    }
    func_80084104(gobj);
}
