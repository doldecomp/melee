#include "ftmario.h"
#include <sysdolphin/baselib/random.h>

#include <melee/it/id.h>

extern void func_800E1368(HSD_GObj*);
extern void func_8008A4D4(HSD_GObj*);
extern void func_800E0EE0(HSD_GObj*);
extern void func_80084F3C(HSD_GObj*);
extern long func_8007500C(struct _Fighter *, long);
extern void func_8000B1CC(HSD_JObj*, Vec*, Vec*);
extern void func_8029B6F8(f32,HSD_GObj*,Vec*,u8);
extern HSD_GObj* func_802B2560(HSD_GObj*,f32,Vec3*,long,u32);
extern void func_802C0510(HSD_GObj*,Vec*,int,u8,f32);
extern void func_800E13C8(HSD_GObj*);
extern void func_800E13F8(HSD_GObj*);
extern void ef_Spawn(long,...);
//TODO: Replace these
//Currently issues with float placement in sdata2 when replacing these with float literals
extern const ftMarioUnkStruct lbl_803C72A0;
extern s32 lbl_803C5A20[];

void func_800E1A54(HSD_GObj* gobj) {
    Fighter* ft;

    ft = gobj->user_data;
    ft->x2200_ftcmd_var0 = 0;
    ft->x2210_ThrowFlags.flags = 0;
	Fighter_ActionStateChange_800693AC(gobj, 0x15B, 0, NULL, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(gobj);
}

void func_800E1AB0(HSD_GObj* gobj) {
    f32 temp_f1;
    Fighter* ft;
    ftMarioAttributes *sA;
    u8 unused[8];

    ft = gobj->user_data;
    sA = (ftMarioAttributes*)ft->x2D4_specialAttributes;
    ft->x2200_ftcmd_var0 = 0;
    ft->x2210_ThrowFlags.flags = 0;
    ft->x80_self_vel.y = temp_f1 = 0.0f;
    ft->x80_self_vel.x = (f32) (ft->x80_self_vel.x * sA->x2C);
    Fighter_ActionStateChange_800693AC(gobj, 0x15C, 0, NULL, temp_f1, 1.0f, temp_f1);
    func_8006EBA4(gobj);
}

void func_800E1B24(HSD_GObj* gobj) {
    Fighter* ft;
    ftMarioAttributes *sA;
    u8 unused[8];

    ft = gobj->user_data;
    sA = (ftMarioAttributes*)ft->x2D4_specialAttributes;
    if (func_8006F238(gobj) == 0) {
            func_80096900(gobj, 0, 1, 0, sA->x18, sA->x1C);
    }
}

void func_800E1B84(HSD_GObj* gobj) {
    Fighter* ft;
    ftMarioAttributes *sA;
    u8 unused[16];

    ft = gobj->user_data;
    sA = (ftMarioAttributes*)ft->x2D4_specialAttributes;
    if (func_8006F238(gobj) == 0) {
            func_80096900(gobj, 0, 1, 0, sA->x18, sA->x1C);
    }
}

#define DEGREES_TO_RADIANS (3.14159265359f / 180.0f)
//#define HALF_PI (3.141592653589792d / 2.0)
#define HALF_PI 1.5707963267948966d

#define abs(x) (x < 0.0f ? -x : x)

//https://decomp.me/scratch/9AoMu
//TODO: This all matches, just keeping in NON_MATCHING for now until label issues are cleared up
inline void func_800E1BE4_and_800E1D2C(HSD_GObj* gobj) {
    Fighter* ft;
    ftMarioAttributes* sa;

    f32  inputStickangle, lstick_x;
    f32 tmp_expr;
    f32 tmp;

    s32 throwflag_flag;
    ft = gobj->user_data;
    
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

void func_800E1BE4(HSD_GObj* gobj) {
    func_800E1BE4_and_800E1D2C(gobj);
}

void func_800E1D2C(HSD_GObj* gobj) {
    u8 padding[16];
    func_800E1BE4_and_800E1D2C(gobj);
}

//https://decomp.me/scratch/8axfI
void func_800E1E74(HSD_GObj* gobj) {
    Fighter* ft = gobj->user_data;
    if (ft->xE0_ground_or_air == 1) {
        func_80085154(gobj);
    } else {
        func_80084FA8(gobj);
    }
}

//https://decomp.me/scratch/1jYsR
void func_800E1EAC(HSD_GObj* gobj) {
    Fighter* ft;
    ftMarioAttributes* sa;
    struct attr* attr_ptr;
    u8 padding[8];
    
    ft = gobj->user_data;
    sa = (ftMarioAttributes*)ft->x2D4_specialAttributes;
    attr_ptr = &(ft->x110_attr);
    
    if ((u32) ft->x2200_ftcmd_var0 != 0U) {
        func_80085154(gobj);
        ft->x80_self_vel.x = (f32) (ft->x80_self_vel.x * sa->x34);
        ft->x80_self_vel.y = (f32) (ft->x80_self_vel.y * sa->x34);
        ft->x80_self_vel.z = (f32) (ft->x80_self_vel.z * sa->x34);
        return;
    }
    //func_8007D494(ft, sa->x30, (ft + 0x110)->unk60);
    func_8007D494(ft, sa->x30, attr_ptr->x170_TerminalVelocity);
    func_8007CF58(ft);
}

//https://decomp.me/scratch/5eIAp
void func_800E1F40(HSD_GObj* gobj) {
    Fighter* ft;
    ftMarioAttributes* sa;

    ft = gobj->user_data;
    

    sa = (ftMarioAttributes*)ft->x2D4_specialAttributes;
    func_800D5CB0(gobj, 0, sa->x1C);
}

//https://decomp.me/scratch/k2DCy
void func_800E1F70(HSD_GObj* gobj) {
    Fighter* ft;

    ft = gobj->user_data;
    if (ft->xE0_ground_or_air == GA_Air) {
        if (ft->x2200_ftcmd_var0 == 0 || ft->x80_self_vel.y >= 0.0f) {
            func_80083B68(gobj);
        } else {
            func_800831CC(gobj, &func_80096CC8, &func_800E1F40);
        }
    } else {
        func_80084104(gobj);
    }
}

void func_800E1FE0(HSD_GObj* gobj) {
	func_800E1F70(gobj);
}