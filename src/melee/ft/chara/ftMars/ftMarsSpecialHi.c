#include <melee/ft/chara/ftMars/ftMars.h>

// 80138208 00134DE8
// https://decomp.me/scratch/lrV6F
void ftMars_SpecialHi_StartAction(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;

    fp->x2208_ftcmd_var2 = 0;
    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;
    fp->x2210_ThrowFlags.flags = 0;
    // ActionStateChange
    Fighter_ActionStateChange_800693AC(gobj, 0x16F, 0, NULL, 0.0f, 1.0f, 0.0f);
    // AS_AnimationFrameUpdate&More
    func_8006EBA4(gobj);
}

// 8013826C 00134E4C
// https://decomp.me/scratch/PuVdx
void ftMars_SpecialAirHi_StartAction(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    MarsAttributes* attr = fp->x2D4_specialAttributes;
    s32 unused[2];

    fp->x2208_ftcmd_var2 = 0;
    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;
    fp->x2210_ThrowFlags.flags = 0;
    fp->x80_self_vel.y = 0.0f;
    fp->x80_self_vel.x *= attr->x3C;
    // ActionStateChange
    Fighter_ActionStateChange_800693AC(gobj, 0x170, 0, NULL, 0.0f, 1.0f, 0.0f);
    // AS_AnimationFrameUpdate&More
    func_8006EBA4(gobj);
}

// 801382E8 00134EC8
// https://decomp.me/scratch/56Ycw
void lbl_801382E8(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    MarsAttributes* attr = fp->x2D4_specialAttributes;
    s32 unused[2];

    // FrameTimerCheck
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        // AS_035_FallSpecial
        func_80096900(gobj, 0, 1, 0, attr->x28, attr->x2C);
    }
}

// 80138348 00134F28
// https://decomp.me/scratch/WdpFi
void lbl_80138348(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    MarsAttributes* attr = fp->x2D4_specialAttributes;
    s32 unused[4];

    // FrameTimerCheck
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        // AS_035_FallSpecial
        func_80096900(gobj, 0, 1, 0, attr->x28, attr->x2C);
    }
}

#define DEGREES_TO_RADIANS (3.14159265359f / 180.0f)
#define HALF_PI 1.5707963267948966
#define abs(x) (x < 0.0f ? -x : x)

// 801383A8 00134F88
// https://decomp.me/scratch/0VOrt
void lbl_801383A8(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    MarsAttributes* attr = fp->x2D4_specialAttributes;

    f32 abs_lstick_x = abs(fp->input.x620_lstick_x);

    s32 phi_r0;
    s32 unused;

    if (fp->x2200_ftcmd_var0 == 0 && abs_lstick_x > attr->x34) {
        f32 temp_f1 = attr->x38 * ((abs_lstick_x - attr->x34) / (1.0/*d*/ - attr->x34));
        temp_f1 = (fp->input.x620_lstick_x > 0.0f) ? -(DEGREES_TO_RADIANS * temp_f1) : (DEGREES_TO_RADIANS * temp_f1);
        if (abs(temp_f1) > abs(fp->x6BC_inputStickangle)) {
            fp->x6BC_inputStickangle = temp_f1;
        }
    }
    if (fp->x2210_ThrowFlags.b3) {
        fp->x2210_ThrowFlags.b3 = 0;
        phi_r0 = 1;
    } else {
        phi_r0 = 0;
    }
    if (phi_r0 != 0) {
        if (abs(fp->input.x620_lstick_x) > attr->x30) {
            func_8007D9FC(fp);
            func_80075AF0(fp, 0, (f32) (HALF_PI * fp->x2C_facing_direction));
        }
    }
}

// 801384F0 001350D0
// https://decomp.me/scratch/2yXhH
void lbl_801384F0(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    MarsAttributes* attr = fp->x2D4_specialAttributes;

    f32 abs_lstick_x = abs(fp->input.x620_lstick_x);

    s32 phi_r0;
    s32 unused[6];

    if (fp->x2200_ftcmd_var0 == 0 && abs_lstick_x > attr->x34) {
        f32 temp_f1 = attr->x38 * ((abs_lstick_x - attr->x34) / (1.0/*d*/ - attr->x34));
        temp_f1 = (fp->input.x620_lstick_x > 0.0f) ? -(DEGREES_TO_RADIANS * temp_f1) : (DEGREES_TO_RADIANS * temp_f1);
        if (abs(temp_f1) > abs(fp->x6BC_inputStickangle)) {
            fp->x6BC_inputStickangle = temp_f1;
        }
    }
    if (fp->x2210_ThrowFlags.b3) {
        fp->x2210_ThrowFlags.b3 = 0;
        phi_r0 = 1;
    } else {
        phi_r0 = 0;
    }
    if (phi_r0 != 0) {
        if (abs(fp->input.x620_lstick_x) > attr->x30) {
            func_8007D9FC(fp);
            func_80075AF0(fp, 0, (f32) (HALF_PI * fp->x2C_facing_direction));
        }
    }
}

// 80138638 00135218
// https://decomp.me/scratch/Wx1iY
void lbl_80138638(HSD_GObj* gobj) {
    struct attr* attr2;
    MarsAttributes* attr;
    Fighter* fp = gobj->user_data;
    s32 unused[8];
    s32 num;

    // this is required, dunno why
    fp->xE0_ground_or_air;

    if (fp->xE0_ground_or_air == GA_Air) {
        if (fp->x2208_ftcmd_var2 == 0) {
            func_80085154(gobj);
            if (fp->x80_self_vel.x < 0.0f) {
                num = -1;
            } else {
                num = 1;
            }
            if (fp->x2C_facing_direction != num) {
                fp->x80_self_vel.x *= -1.0f;
            }
            if (fp->x6A4_transNOffset.y < 0.0f) {
                fp->x2208_ftcmd_var2 = 1;
            }
        } else {
            attr = fp->x2D4_specialAttributes;
            attr2 = &fp->x110_attr;
            func_8007D494(fp, attr->x44, attr->x48);
            func_8007D344(fp, 0.0f, attr2->x174_AerialDriftStickMult * attr->x28, attr2->x17C_AerialDriftMax * attr->x28);
        }
    } else {
        func_80084FA8(gobj);
    }
}

// 8013873C 0013531C
// https://decomp.me/scratch/9gz2V
void lbl_8013873C(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    MarsAttributes* attr = fp->x2D4_specialAttributes;
    struct attr* attr2 = &fp->x110_attr;
    s32 num;
    s32 unused[10];

    if (fp->x2200_ftcmd_var0 != 0) {
        if (fp->x2208_ftcmd_var2 == 0) {
            func_80085154(gobj);
            fp->x80_self_vel.x *= attr->x40;
            fp->x80_self_vel.y *= attr->x40;
            fp->x80_self_vel.z *= attr->x40;
            if (fp->x80_self_vel.x < 0.0f) {
                num = -1;
            } else {
                num = 1;
            }
            if (fp->x2C_facing_direction != num) {
                fp->x80_self_vel.x *= -1.0f;
            }
            if (fp->x6A4_transNOffset.y < 0.0f) {
                fp->x2208_ftcmd_var2 = 1;
            }
        } else {
            func_8007D494(fp, attr->x44, attr->x48);
            func_8007D344(fp, 0.0f, attr2->x174_AerialDriftStickMult * attr->x28, attr2->x17C_AerialDriftMax * attr->x28);
        }
    } else {
        func_8007D494(fp, attr2->x16C_Gravity, attr2->x170_TerminalVelocity);
        func_8007CF58(fp);
    }
}

// 80138884 00135464
// https://decomp.me/scratch/NTb4a
void lbl_80138884(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    MarsAttributes* attr = fp->x2D4_specialAttributes;
    func_800D5CB0(gobj, 0, attr->x2C);
}



// 801388B4 00135494
// https://decomp.me/scratch/3MMkJ
void lbl_801388B4(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    if (fp->xE0_ground_or_air == GA_Air) {
        if (fp->x2200_ftcmd_var0 == 0 || fp->x80_self_vel.y >= 0.0f) {
            func_80083B68(gobj);
        } else if (fp->x2204_ftcmd_var1 == 0) {
            fp->x2204_ftcmd_var1 = 1;
            func_80083B68(gobj);
        } else {
            func_800831CC(gobj, &func_80096CC8, &lbl_80138884);
        }
    } else {
        func_80084104(gobj);
    }
}

// 80138940 00135520
// https://decomp.me/scratch/QEKrM
void lbl_80138940(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    if (fp->xE0_ground_or_air == GA_Air) {
        if (fp->x2200_ftcmd_var0 == 0 || fp->x80_self_vel.y >= 0.0f) {
            func_80083B68(gobj);
        } else if (fp->x2204_ftcmd_var1 == 0) {
            fp->x2204_ftcmd_var1 = 1;
            func_80083B68(gobj);
        } else {
            func_800831CC(gobj, &func_80096CC8, &lbl_80138884);
        }
    } else {
        func_80084104(gobj);
    }
}
