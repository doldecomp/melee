#include "ftmario.h"
#include <sysdolphin/baselib/random.h>

#include <melee/it/itkind.h>

void ftMario_SpecialHi_StartAction(HSD_GObj* gobj) {
    Fighter* ft;

    ft = getFighter(gobj);
    ft->x2200_ftcmd_var0 = 0;
    ft->x2210_ThrowFlags.flags = 0;
	Fighter_ActionStateChange_800693AC(gobj, AS_MARIO_SPECIALHI, 0, NULL, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(gobj);
}

void ftMario_SpecialAirHi_StartAction(HSD_GObj* gobj) 
{
    Fighter* ft;
    ftMarioAttributes *sa;
    u8 unused[4];

    ft = getFighter(gobj);
    sa = (ftMarioAttributes*)ft->x2D4_specialAttributes;
    ft->x2200_ftcmd_var0 = 0;
    ft->x2210_ThrowFlags.flags = 0;
    ft->x80_self_vel.y = 0.0f;
    ft->x80_self_vel.x = (f32) (ft->x80_self_vel.x * sa->x2C_MARIO_SUPERJUMP_VEL_X);
    Fighter_ActionStateChange_800693AC(gobj, AS_MARIO_SPECIALAIRHI, 0, NULL, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(gobj);
}

// 0x800E1B24
void ftMario_SpecialHi_Anim(HSD_GObj* gobj) 
{
    Fighter* ft;
    ftMarioAttributes *sa;

    ft = getFighter(gobj);
    sa = (ftMarioAttributes*)ft->x2D4_specialAttributes;
    if (ftAnim_IsFramesRemaining(gobj) == FALSE) 
    {
        func_80096900(gobj, 0, 1, 0, sa->x18_MARIO_SUPERJUMP_FREEFALL_MOBILITY, sa->x1C_MARIO_SUPERJUMP_LANDING_LAG);
    }
}

// 0x800E1B84
void ftMario_SpecialAirHi_Anim(HSD_GObj* gobj) 
{
    u8 unused[8];
    ftMario_SpecialHi_Anim(gobj);
}

#define DEGREES_TO_RADIANS (3.14159265359f / 180.0f)
#define HALF_PI 1.5707963267948966

#define abs(x) (x < 0.0f ? -x : x)

//https://decomp.me/scratch/9AoMu
inline void ftMario_SpecialHi_CalcAngle(HSD_GObj* gobj) 
{
    Fighter* ft;
    ftMarioAttributes* sa;

    f32  inputStickangle, lstick_x;
    f32 tmp_expr;
    f32 tmp;

    s32 throwflag_flag;
    ft = getFighter(gobj);

    sa = (ftMarioAttributes*)ft->x2D4_specialAttributes;

    lstick_x = abs(ft->input.x620_lstick_x);

    if ((s32) ft->x2200_ftcmd_var0 == 0U) {
        if(lstick_x > sa->x24_MARIO_SUPERJUMP_MOMENTUM_STICK_RANGE) {
            tmp_expr = (f32) ((f64) sa->x28_MARIO_SUPERJUMP_ANGLE_DIFF *
                ((f64) (lstick_x - sa->x24_MARIO_SUPERJUMP_MOMENTUM_STICK_RANGE) / (1.0 - (f64)sa->x24_MARIO_SUPERJUMP_MOMENTUM_STICK_RANGE)));

            tmp = (ft->input.x620_lstick_x > 0.0f) ? -(DEGREES_TO_RADIANS * tmp_expr) : (DEGREES_TO_RADIANS * tmp_expr);
            inputStickangle = ft->x6BC_inputStickangle;

            if (abs(tmp) > abs(inputStickangle)) {
                ft->x6BC_inputStickangle = tmp;
            }
        }
    }

    if (ft->x2210_ThrowFlags.b3 != 0) {
        ft->x2210_ThrowFlags.b3 = 0;
        throwflag_flag= 1;
    } else {
        throwflag_flag = 0;
    }
    if (throwflag_flag != 0) {
        if (abs(ft->input.x620_lstick_x) > sa->x20_MARIO_SUPERJUMP_REVERSE_STICK_RANGE) {
            func_8007D9FC(ft);
            func_80075AF0(ft, 0, (f32) (HALF_PI * (f64) ft->x2C_facing_direction));
        }
    }
}

// 0x800E1BE4
void ftMario_SpecialHi_IASA(HSD_GObj* gobj) {
    ftMario_SpecialHi_CalcAngle(gobj);
}

// 0x800E1D2C
void ftMario_SpecialAirHi_IASA(HSD_GObj* gobj) {
    u8 padding[16];
    ftMario_SpecialHi_CalcAngle(gobj);
}

// 0x800E1E74
// https://decomp.me/scratch/8axfI
void ftMario_SpecialHi_Phys(HSD_GObj* gobj) {
    Fighter* ft = getFighter(gobj);
    if (ft->xE0_ground_or_air == GA_Air) {
        func_80085154(gobj);
    } else {
        func_80084FA8(gobj);
    }
}

// 0x800E1EAC
// https://decomp.me/scratch/1jYsR
void ftMario_SpecialAirHi_Phys(HSD_GObj* gobj) {
    Fighter* ft;
    ftMarioAttributes* sa;
    struct attr* attr_ptr;

    ft = getFighter(gobj);
    sa = GetMarioAttr(ft);
    attr_ptr = &(ft->x110_attr);

    if ((u32) ft->x2200_ftcmd_var0 != 0U) {
        func_80085154(gobj);
        ft->x80_self_vel.x = (f32) (ft->x80_self_vel.x * sa->x34_MARIO_SUPERJUMP_VEL_MUL);
        ft->x80_self_vel.y = (f32) (ft->x80_self_vel.y * sa->x34_MARIO_SUPERJUMP_VEL_MUL);
        ft->x80_self_vel.z = (f32) (ft->x80_self_vel.z * sa->x34_MARIO_SUPERJUMP_VEL_MUL);
        return;
    }
    func_8007D494(ft, sa->x30_MARIO_SUPERJUMP_GRAVITY, attr_ptr->x170_TerminalVelocity);
    func_8007CF58(ft);
}

// 0x800E1F40
// https://decomp.me/scratch/5eIAp
void ftMario_SpecialHi_CheckLanding(HSD_GObj* gobj) {
    Fighter* ft;
    ftMarioAttributes* sa;

    ft = getFighter(gobj);

    sa = (ftMarioAttributes*)ft->x2D4_specialAttributes;
    func_800D5CB0(gobj, 0, sa->x1C_MARIO_SUPERJUMP_LANDING_LAG);
}

// 0x800E1F70
// https://decomp.me/scratch/k2DCy
void ftMario_SpecialHi_Coll(HSD_GObj* gobj) 
{
    Fighter* ft;

    ft = getFighter(gobj);
    if (ft->xE0_ground_or_air == GA_Air) {
        if (ft->x2200_ftcmd_var0 == 0 || ft->x80_self_vel.y >= 0.0f) 
        {
            func_80083B68(gobj);
        } 
        else 
        {
            func_800831CC(gobj, &func_80096CC8, &ftMario_SpecialHi_CheckLanding);
        }
    } else 
    {
        func_80084104(gobj);
    }
}

// 0x800E1FE0
void ftMario_SpecialAirHi_Coll(HSD_GObj* gobj) 
{
	ftMario_SpecialHi_Coll(gobj);
}
