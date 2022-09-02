#include <melee/ft/chara/ftMasterHand/ftMasterHand.h>

// 80151D20 14E900
// https://decomp.me/scratch/wVowU
void lbl_80151D20(HSD_GObj* arg0) {
    if (ftAnim_IsFramesRemaining(arg0) == 0) {
        func_80151018(arg0);
    }
}



// 80151D5C 14E93C
// https://decomp.me/scratch/8YW2K
void lbl_80151D5C(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        func_8015BD20(gobj);
    }
}



// 80151DA0 14E980
// https://decomp.me/scratch/LHwFj
void lbl_80151DA0(HSD_GObj* arg0) {
    func_80085134(arg0);
}



// 80151DC0 14E9A0
// https://decomp.me/scratch/xMzaA
void lbl_80151DC0(void) {
    return;
}



// 80151DC4 14E9A4
// https://decomp.me/scratch/1PULy
void lbl_80151DC4(HSD_GObj* arg0) {
    Fighter_ActionStateChange_800693AC(arg0, 0x15E, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(arg0);
}



// 80151E10 14E9F0
// https://decomp.me/scratch/acoIs
void lbl_80151E10(HSD_GObj* arg0) {
    if (ftAnim_IsFramesRemaining(arg0) == 0) {
        func_80151EB4(arg0);
    }
}



// 80151E4C 14EA2C
// https://decomp.me/scratch/FpXjP
void lbl_80151E4C(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        func_8015BD20(gobj);
    }
}



// 80151E90 14EA70
// https://decomp.me/scratch/HeWua
void lbl_80151E90(HSD_GObj* gobj) {
    func_80085134(gobj);
}



// 80151EB0 14EA90
// https://decomp.me/scratch/cjk7N
void lbl_80151EB0(void) {
    return;
}



// 80151EB4 14EA94
// https://decomp.me/scratch/ZzhS3
void func_80151EB4(HSD_GObj* gobj) {
    Fighter_ActionStateChange_800693AC(gobj, 0x15F, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(gobj);
}



// 80151F00 14EAE0
// https://decomp.me/scratch/12qfC
static inline float my_sqrtf(float x)
{
static const double _half=.5;
static const double _three=3.0;
    s32 unused = 0; // fakematch
volatile float y;
 if(x > 0.0f)
 {


   double guess = __frsqrte((double)x);   // returns an approximation to
   guess = _half*guess*(_three - guess*guess*x);  // now have 12 sig bits
   guess = _half*guess*(_three - guess*guess*x);  // now have 24 sig bits
   guess = _half*guess*(_three - guess*guess*x);  // now have 32 sig bits
   y=(float)(x*guess);
   return y ;
 }
  return x ;
}

static inline float my_lbvector_Len(Vec3 *vec)
{
    return my_sqrtf(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
}

void lbl_80151F00(HSD_GObj* gobj) {
    Vec3 sp28;
    Vec3 sp1C_resultVector;
    Fighter* r31_fp;
    MasterHandAttributes* r30_attributes;
    s32 unk2[1];

    r31_fp = gobj->user_data;
    r30_attributes = r31_fp->x10C_ftData->ext_attr;
    func_800866DC(func_8015C244(gobj, &r31_fp->xB0_pos), &sp28);
    lbvector_Diff(&sp28, &r31_fp->xB0_pos, &sp1C_resultVector);
    if (my_lbvector_Len(&sp1C_resultVector) < r30_attributes->x4C) {
        func_80151CA8(gobj);
    }
    func_80054158(0, &sp28);
    if (r31_fp->xB0_pos.x < sp28.x) {
        func_801520D8(gobj);
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ActionStateChange_800693AC(gobj, 0x15F, 0, 0, 0.0f, 1.0f, 0.0f);
        func_8006EBA4(gobj);
    }
}



// 8015204C 14EC2C
// https://decomp.me/scratch/6N3wk
void lbl_8015204C(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        func_8015BD20(gobj);
    }
}



// 80152090 14EC70
// https://decomp.me/scratch/B021s
void lbl_80152090(HSD_GObj* gobj) {
    ftData* r4_ftData;
    Fighter* r31_fp;
    MasterHandAttributes* r30_attributes;

    r31_fp = gobj->user_data;
    r4_ftData = r31_fp->x10C_ftData;
    r30_attributes = r4_ftData->ext_attr;
    func_80085134(gobj);
    r31_fp->x80_self_vel.x = r30_attributes->x40_pos.z;
}



// 801520D4 14ECB4
// https://decomp.me/scratch/xDlzv
void lbl_801520D4(void) {
    return;
}



// 801520D8 14ECB8
// https://decomp.me/scratch/HUhGv
void func_801520D8(HSD_GObj* gobj) {
    Fighter* r31_fp;
    f32 temp_f1;

    r31_fp = gobj->user_data;
    Fighter_ActionStateChange_800693AC(gobj, 0x160, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(gobj);
    r31_fp->x80_self_vel.x = 0.0f;
}
