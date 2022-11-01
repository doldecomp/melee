#include <melee/ft/chara/ftMasterHand/ftMasterHand.h>

#include <melee/lb/lbunknown_001.h>

// 80153000 14FBE0
// https://decomp.me/scratch/erd6U
void lbl_80153000(HSD_GObj* arg0) {
    if (ftAnim_IsFramesRemaining(arg0) == 0) {
        ftMasterHand_80151018(arg0);
    }
}



// 8015303C 14FC1C
void lbl_8015303C(HSD_GObj* arg0) {
    Fighter* fp = arg0->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        func_8015BD20(arg0);
    }
}

void ftMasterHand_80153080(HSD_GObj* fighter_gobj)
{
    func_80085134(fighter_gobj);
}

void ftMasterHand_801530A0(HSD_GObj* fighter_gobj)
{
    return;
}

void ftMasterHand_801530A4(HSD_GObj* fighter_gobj)
{
    Fighter* fp;
    MasterHandAttributes* ext_attr;
    s32 rand;
    s32 unk[2];

    fp = fighter_gobj->user_data;
    ext_attr = fp->x10C_ftData->ext_attr;
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x16C, 0, 0, 0.0F, 1.0F, 0.0F);
    func_8006EBA4(fighter_gobj);
    rand = HSD_Randi(ext_attr->xE8 - ext_attr->xE4);
    fp->x2390 = ext_attr->xE4 + rand;
    fp->x2200_ftcmd_var0 = 0;
    fp->x2204_ftcmd_var1 = 0;
    fp->x2208_ftcmd_var2 = 0;
}

void ftMasterHand_801533CC(HSD_GObj* fighter_gobj);

void ftMasterHand_80153160(HSD_GObj* fighter_gobj)
{
    Fighter* fp;
    MasterHandAttributes* ext_attr;
    ftData* ftData;
    f32 temp_f1;
    s32 unk[2];

    fp = fighter_gobj->user_data;
    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE) {
        fp->x2208_ftcmd_var2 = 1;
        temp_f1 = fp->x2390 - 1.0f;
        fp->x2390 = temp_f1;
        if (temp_f1 < 0.0F) {
            ftData = fp->x10C_ftData;
            ext_attr = ftData->ext_attr;
            ftMasterHand_801533CC(fighter_gobj);
            if (func_80087120(fighter_gobj) > ext_attr->xEC) {
                fp->x2394 = (s32) ext_attr->xF0;
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

void ftMasterHand_801533C8(HSD_GObj* fighter_gobj)
{
    return;
}

static void ftMasterHand_801533CC(HSD_GObj* fighter_gobj)
{
    Fighter* fp;
    MasterHandAttributes* ext_attr;

    fp = fighter_gobj->user_data;
    ext_attr = fp->x10C_ftData->ext_attr;
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x16D, 0, 0, 0.0F, 1.0F, 0.0F);
    func_8006EBA4(fighter_gobj);
    if (func_80087120(fighter_gobj) > ext_attr->xEC) {
        ftAnim_SetAnimRate(fighter_gobj, ext_attr->xF4);
    }
    fp->x80_self_vel.x = 0.0F;
    fp->x80_self_vel.y = 0.0F;
    fp->cb.x21BC_callback_Accessory4 = &lbl_801535B0;
}

inline void ftMasterHand_8015346C_inline(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    MasterHandAttributes* ext_attr = fp->x10C_ftData->ext_attr;
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x16D, 0, 0, 0.0F, 1.0F, 0.0F);
    func_8006EBA4(fighter_gobj);
    if (func_80087120(fighter_gobj) > ext_attr->xEC) {
        ftAnim_SetAnimRate(fighter_gobj, ext_attr->xF4);
    }
    fp->x80_self_vel.x = 0.0F;
    fp->x80_self_vel.y = 0.0F;
    fp->cb.x21BC_callback_Accessory4 = lbl_801535B0;
}

void ftMasterHand_80153730(HSD_GObj* fighter_gobj);

void ftMasterHand_8015346C(HSD_GObj* fighter_gobj)
{
    Fighter* ft4;
    s32 unk[2];

    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE) {
        ft4 = fighter_gobj->user_data;
        if (--ft4->x2394 == 0) {
            ftAnim_SetAnimRate(fighter_gobj, 1.0F);
            ftMasterHand_80153730(fighter_gobj);
        } else {
            ftMasterHand_8015346C_inline(fighter_gobj);
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
static void ftMasterHand_80153730(HSD_GObj* arg0)
{
    s32 unk[2];
    Fighter_ActionStateChange_800693AC(arg0, 0x16E, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(arg0);
}
