#include <melee/ft/chara/ftMasterHand/__ftMasterHand.h>

void ftMasterHand_8015287C(HSD_GObj* fighter_gobj)
{
    return;
}

void ftMasterHand_80152880(HSD_GObj* fighter_gobj)
{
    Fighter* fp;
    MasterHandAttributes* ext_attr;
    s32 unk[2];

    fp = fighter_gobj->user_data;
    ext_attr = fp->x10C_ftData->ext_attr;
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x167, 0, 0, 0.0F, 1.0F, 0.0F);
    func_8006EBA4(fighter_gobj);
    fp->x2340_f32 = ext_attr->x94 + HSD_Randi(ext_attr->x90 - ext_attr->x94);
    fp->x2344_f32 = 0.0F;
}

// 80152928 14F508
// https://decomp.me/scratch/WyNdB
void lbl_80152928(HSD_GObj* gobj) {
    Fighter* temp_r31;
    Fighter* temp_r4;
    u32 unk[2];

    if (!ftAnim_IsFramesRemaining(gobj)) {
        temp_r4 = gobj->user_data;
        temp_r4->x2344_f32 = 1.0f;

        if (--temp_r4->x2340_f32 < 0.0f) {
            temp_r4->x2344_f32 = 0.0f;
            temp_r4->x80_self_vel.x = 0.0f;
            temp_r4->x80_self_vel.y = 0.0f;
            temp_r31 = gobj->user_data;
            Fighter_ActionStateChange_800693AC(gobj, 0x168, 0, 0, 0.0f, 1.0f, 0.0f);
            func_8006EBA4(gobj);
            func_80088148(temp_r31, 0x4E207, 0x7F, 0x40);
        }
    }
}



// 801529D0 14F5B0
// https://decomp.me/scratch/IBucf
void lbl_801529D0(HSD_GObj* arg0) {
    if (ftAnim_IsFramesRemaining(arg0) == 0) {
        ftMasterHand_80151018(arg0);
    }
}



// 80152A0C 14F5EC
// https://decomp.me/scratch/7UfC7
void lbl_80152A0C(HSD_GObj* arg0) {
    Fighter* fp = arg0->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        func_8015BD20(arg0);
    }
}



// 80152A50 14F630
// https://decomp.me/scratch/YmoFC
static inline float my_sqrtf(float x)
{
static const double _half=.5;
static const double _three=3.0;
    s32 unused = 0; //fakematch
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

void lbl_80152A50(HSD_GObj* gobj) {
    Fighter* fp;
    MasterHandAttributes* attr;
    f32 speed;
    ftData* ftData;
    Vec3 sp28_pos;
    Vec3 sp1C_vel;
    f32 len;

    fp = gobj->user_data;
    func_80085134(gobj);
    if (fp->x2344_f32) {
        ftData = fp->x10C_ftData;
        attr = ftData->ext_attr;
        func_8015C208(gobj, &sp28_pos);
        sp28_pos.x += attr->x98;
        sp28_pos.y += attr->x9C;
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
