#include "ftmario.h"
#include <sysdolphin/baselib/random.h>

#include <melee/it/itkind.h>

void ftMario_SpecialHi_StartAction(HSD_GObj* gobj) {
    Fighter* ft;

    ft = getFighter(gobj);
    ft->x2200_ftcmd_var0 = 0;
    ft->x2210_ThrowFlags.flags = 0;
	Fighter_ActionStateChange_800693AC(gobj, 0x15B, 0, NULL, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(gobj);
}

void ftMario_SpecialHiAir_StartAction(HSD_GObj* gobj) {
    Fighter* ft;
    ftMarioAttributes *sa;
    u8 unused[4];

    ft = getFighter(gobj);
    sa = (ftMarioAttributes*)ft->x2D4_specialAttributes;
    ft->x2200_ftcmd_var0 = 0;
    ft->x2210_ThrowFlags.flags = 0;
    ft->x80_self_vel.y = 0.0f;
    ft->x80_self_vel.x = (f32) (ft->x80_self_vel.x * sa->x2C);
    Fighter_ActionStateChange_800693AC(gobj, 0x15C, 0, NULL, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(gobj);
}

void ftMario_func_800E1B24(HSD_GObj* gobj) {
    Fighter* ft;
    ftMarioAttributes *sa;

    ft = getFighter(gobj);
    sa = (ftMarioAttributes*)ft->x2D4_specialAttributes;
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        func_80096900(gobj, 0, 1, 0, sa->x18, sa->x1C);
    }
}

void ftMario_func_800E1B84(HSD_GObj* gobj) {
    u8 unused[8];
    ftMario_func_800E1B24(gobj);
}

#define DEGREES_TO_RADIANS (3.14159265359f / 180.0f)
#define HALF_PI 1.5707963267948966d

#define abs(x) (x < 0.0f ? -x : x)

//https://decomp.me/scratch/9AoMu
inline void _ftMario_func_800E1BE4_and_800E1D2C(HSD_GObj* gobj) {
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
        if(lstick_x > sa->x24) {
            tmp_expr = (f32) ((f64) sa->x28 *
                ((f64) (lstick_x - sa->x24) / (1.0d - (f64) sa->x24)));

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
        if (abs(ft->input.x620_lstick_x) > sa->x20) {
            func_8007D9FC(ft);
            func_80075AF0(ft, 0, (f32) (HALF_PI * (f64) ft->x2C_facing_direction));
        }
    }
}

void ftMario_func_800E1BE4(HSD_GObj* gobj) {
    _ftMario_func_800E1BE4_and_800E1D2C(gobj);
}

void ftMario_func_800E1D2C(HSD_GObj* gobj) {
    u8 padding[16];
    _ftMario_func_800E1BE4_and_800E1D2C(gobj);
}

//https://decomp.me/scratch/8axfI
void ftMario_func_800E1E74(HSD_GObj* gobj) {
    Fighter* ft = getFighter(gobj);
    if (ft->xE0_ground_or_air == GA_Air) {
        func_80085154(gobj);
    } else {
        func_80084FA8(gobj);
    }
}

//https://decomp.me/scratch/1jYsR
void ftMario_func_800E1EAC(HSD_GObj* gobj) {
    Fighter* ft;
    ftMarioAttributes* sa;
    struct attr* attr_ptr;

    ft = getFighter(gobj);
    sa = GetMarioAttr(ft);
    attr_ptr = &(ft->x110_attr);

    if ((u32) ft->x2200_ftcmd_var0 != 0U) {
        func_80085154(gobj);
        ft->x80_self_vel.x = (f32) (ft->x80_self_vel.x * sa->x34);
        ft->x80_self_vel.y = (f32) (ft->x80_self_vel.y * sa->x34);
        ft->x80_self_vel.z = (f32) (ft->x80_self_vel.z * sa->x34);
        return;
    }
    func_8007D494(ft, sa->x30, attr_ptr->x170_TerminalVelocity);
    func_8007CF58(ft);
}

//https://decomp.me/scratch/5eIAp
void ftMario_func_800E1F40(HSD_GObj* gobj) {
    Fighter* ft;
    ftMarioAttributes* sa;

    ft = getFighter(gobj);

    sa = (ftMarioAttributes*)ft->x2D4_specialAttributes;
    func_800D5CB0(gobj, 0, sa->x1C);
}

//https://decomp.me/scratch/k2DCy
void ftMario_func_800E1F70(HSD_GObj* gobj) {
    Fighter* ft;

    ft = getFighter(gobj);
    if (ft->xE0_ground_or_air == GA_Air) {
        if (ft->x2200_ftcmd_var0 == 0 || ft->x80_self_vel.y >= 0.0f) {
            func_80083B68(gobj);
        } else {
            func_800831CC(gobj, &func_80096CC8, &ftMario_func_800E1F40);
        }
    } else {
        func_80084104(gobj);
    }
}

void ftMario_func_800E1FE0(HSD_GObj* gobj) {
	ftMario_func_800E1F70(gobj);
}
