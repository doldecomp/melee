#include <melee/ft/chara/ftMasterHand/ftMasterHand.h>

// 80153000 14FBE0
// https://decomp.me/scratch/erd6U
void lbl_80153000(HSD_GObj* arg0) {
    if (ftAnim_IsFramesRemaining(arg0) == 0) {
        func_80151018(arg0);
    }
}



// 8015303C 14FC1C
void lbl_8015303C(HSD_GObj* arg0) {
    Fighter* fp = arg0->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        func_8015BD20(arg0);
    }
}



// 80153080 14FC60
void lbl_80153080(HSD_GObj* gobj) {
    func_80085134(gobj);
}


// 801530A0 14FC80
// https://decomp.me/scratch/YbpJf
void lbl_801530A0(HSD_GObj* arg0) {
    return;
}



// 801530A4 14FC84
// https://decomp.me/scratch/ZtWrg
void func_801530A4(HSD_GObj* gobj) {
    Fighter* fp;
    MasterHandAttributes* attr;
    s32 rand;
    s32 unk[2];

    fp = gobj->user_data;
    attr = fp->x10C_ftData->ext_attr;
    Fighter_ActionStateChange_800693AC(gobj, 0x16C, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(gobj);
    rand = HSD_Randi(attr->xE8 - attr->xE4);
    fp->x2390 = attr->xE4 + rand;
    fp->x2200_ftcmd_var0 = 0;
    fp->x2204_ftcmd_var1 = 0;
    fp->x2208_ftcmd_var2 = 0;
}



// 80153160 14FD40
// https://decomp.me/scratch/7Kmdd
void lbl_80153160(HSD_GObj* gobj) {
    Fighter* fp;
    MasterHandAttributes* temp_r29;
    ftData* ftData;
    f32 temp_f1;
    s32 unk[2];

    fp = gobj->user_data;
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        fp->x2208_ftcmd_var2 = 1;
        temp_f1 = fp->x2390 - 1.0f;
        fp->x2390 = temp_f1;
        if (temp_f1 < 0.0f) {
            ftData = fp->x10C_ftData;
            temp_r29 = ftData->ext_attr;
            func_801533CC(gobj);
            if (func_80087120(gobj) > temp_r29->xEC) {
                fp->x2394 = (s32) temp_r29->xF0;
            } else {
                fp->x2394 = 1;
            }
            fp->x2208_ftcmd_var2 = 0;
        }
    }
}



// 80153210 14FDF0
// https://decomp.me/scratch/Ssmxs
void lbl_80153210(HSD_GObj* arg0) {
    Fighter* fp = arg0->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        func_8015BD20(arg0);
    }
}



// 80153254 14FE34
// https://decomp.me/scratch/KCGYv
static inline float my_sqrtf(float x)
{
static const double _half=.5;
static const double _three=3.0;
    s32 unk = 0; // fakematch
volatile float y;
if(x > 0.0f)
{
double guess = __frsqrte((double)x);
guess = _half*guess*(_three - guess*guess*x);
guess = _half*guess*(_three - guess*guess*x);
guess = _half*guess*(_three - guess*guess*x);
y=(float)(x*guess);
return y ;
}
return x ;
}
static inline float my_lbvector_Len(Vec3 *vec)
{
    return my_sqrtf(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
}

void lbl_80153254(HSD_GObj* gobj) {
    Fighter* fp;
    MasterHandAttributes* attr;
    f32 len;
    f32 speed;
    Vec3 sp28_pos;
    Vec3 sp1C_vel;
    s32 unk;

    fp = gobj->user_data;
    func_80085134(gobj);
    if (fp->x2208_ftcmd_var2 != 0) {
        attr = fp->x10C_ftData->ext_attr;
        func_8015C208(gobj, &sp28_pos);
        sp28_pos.x += attr->xDC;
        sp28_pos.y += attr->xE0;
        sp28_pos.z = 0.0f;
        lbvector_Diff(&sp28_pos, &fp->xB0_pos, &sp1C_vel);
        len = my_lbvector_Len(&sp1C_vel);
        if (len < attr->x2C) {
            fp->x80_self_vel.x = sp1C_vel.x;
            fp->x80_self_vel.y = sp1C_vel.y;
        } else {
            lbvector_Normalize(&sp1C_vel);
            speed = len * attr->x28;
            sp1C_vel.x *= speed;
            sp1C_vel.y *= speed;
            sp1C_vel.z *= speed;
            fp->x80_self_vel.x = sp1C_vel.x;
            fp->x80_self_vel.y = sp1C_vel.y;
        }
    }
}



// 801533C8 14FFA8
void lbl_801533C8(HSD_GObj* gobj) {
    return;
}


// 801533CC 14FFAC
// https://decomp.me/scratch/uSNs4
void func_801533CC(HSD_GObj* arg0) {
    Fighter* fp;
    MasterHandAttributes* attr;

    fp = arg0->user_data;
    attr = fp->x10C_ftData->ext_attr;
    Fighter_ActionStateChange_800693AC(arg0, 0x16D, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(arg0);
    if (func_80087120(arg0) > attr->xEC) {
        ftAnim_SetAnimRate(arg0, attr->xF4);
    }
    fp->x80_self_vel.x = 0.0f;
    fp->x80_self_vel.y = 0.0f;
    fp->cb.x21BC_callback_Accessory4 = &lbl_801535B0;
}



// 8015346C 15004C
// https://decomp.me/scratch/6Hvy9
inline void lbl_8015346C_inline(HSD_GObj *gobj) {
    Fighter *ft30 = gobj->user_data;
    MasterHandAttributes *attr = ft30->x10C_ftData->ext_attr;
    Fighter_ActionStateChange_800693AC(gobj, 0x16D, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(gobj);
    if (func_80087120(gobj) > attr->xEC) {
        ftAnim_SetAnimRate(gobj, attr->xF4);
    }
    ft30->x80_self_vel.x = 0.0f;
    ft30->x80_self_vel.y = 0.0f;
    ft30->cb.x21BC_callback_Accessory4 = lbl_801535B0;
}

void lbl_8015346C(HSD_GObj* gobj) {
    Fighter* ft4;
    s32 unk[2];

    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ft4 = gobj->user_data;
        if (--ft4->x2394 == 0) {
            ftAnim_SetAnimRate(gobj, 1.0f);
            func_80153730(gobj);
        } else {
            lbl_8015346C_inline(gobj);
        }
    }
}



// 80153548 150128
// https://decomp.me/scratch/VcNLJ
void lbl_80153548(HSD_GObj* arg0) {
    Fighter* fp = arg0->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        func_8015BD20(arg0);
    }
}



// 8015358C 15016C
void lbl_8015358C(HSD_GObj* gobj) {
    func_80085134(gobj);
}



// 801535AC 15018C
void lbl_801535AC(HSD_GObj* gobj) {
    return;
}



// 801535B0 150190
// https://decomp.me/scratch/zL8mX
void lbl_801535B0(HSD_GObj* gobj) {
    Fighter* fp;
    MasterHandAttributes* attr;

    fp = gobj->user_data;
    attr = fp->x10C_ftData->ext_attr;
    if (fp->x2200_ftcmd_var0 != 0) {
        func_8015364C(gobj, fp->x5E8_fighterBones[8].x0_jobj, attr->xF8, attr->xFC);
        fp->x2200_ftcmd_var0 = 0;
    }
    if (fp->x2204_ftcmd_var1 != 0) {
        func_8015364C(gobj, fp->x5E8_fighterBones[13].x0_jobj, attr->x100, attr->x104);
        fp->x2204_ftcmd_var1 = 0;
    }
}



// 8015364C 15022C
// https://decomp.me/scratch/YITWN
void func_8015364C(HSD_GObj* arg0, HSD_JObj* arg1, f32 arg2, f32 arg3) {
    Fighter* fp;
    MasterHandAttributes* attr;
    s32 phi_r29;
    Vec3 sp28_leek;
    Vec3 sp1C_carrot;
    s32 unk;

    fp = arg0->user_data;
    attr = fp->x10C_ftData->ext_attr;
    phi_r29 = 0;
    func_8000B1CC(arg1, 0, &sp28_leek);
    sp1C_carrot = sp28_leek;
    sp28_leek.x += arg2;
    sp28_leek.y += arg3;
    if (func_80087120(arg0) > attr->xEC) {
        phi_r29 = 1;
    }
    func_802F0AE0(arg0, &sp28_leek, &sp1C_carrot, 0x7E, phi_r29, fp->x2C_facing_direction, attr->xD4, attr->xD8);
}



// 80153730 150310
// https://decomp.me/scratch/0IqUp
void func_80153730(HSD_GObj* arg0) {
    s32 unk[2];
    Fighter_ActionStateChange_800693AC(arg0, 0x16E, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(arg0);
}
