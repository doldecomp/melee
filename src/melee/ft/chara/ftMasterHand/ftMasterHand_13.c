#include <melee/ft/chara/ftMasterHand/__ftMasterHand.h>

void ftMasterHand_8015287C(HSD_GObj* fighter_gobj)
{
    return;
}

#include <melee/ft/ftanim.h>

void ftMasterHand_80152880(HSD_GObj* fighter_gobj)
{
    u32 unused[2];

    Fighter* fp = fighter_gobj->user_data;
    MasterHandAttributes* ext_attr = fp->x10C_ftData->ext_attr;

    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x167, 0, 0, 0.0F, 1.0F, 0.0F);
    func_8006EBA4(fighter_gobj);

    fp->x2340_f32 = ext_attr->x94 + HSD_Randi(ext_attr->x90 - ext_attr->x94);
    fp->x2344_f32 = 0.0F;
}

static inline void ftMasterHand_80152928_inline(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x168, 0, 0, 0.0F, 1.0F, 0.0F);
    func_8006EBA4(fighter_gobj);
    func_80088148(fp, 0x4E207, 0x7F, 0x40);
}

void ftMasterHand_80152928(HSD_GObj* fighter_gobj)
{
    u32 unused[2];

    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        Fighter* fp = fighter_gobj->user_data;
        fp->x2344_f32 = 1.0F;

        if (--fp->x2340_f32 < 0.0F) {
            fp->x2344_f32 = 0.0F;
            fp->x80_self_vel.x = 0.0F;
            fp->x80_self_vel.y = 0.0F;
            ftMasterHand_80152928_inline(fighter_gobj);
        }
    }
}

void ftMasterHand_801529D0(HSD_GObj* fighter_gobj)
{
    if (!ftAnim_IsFramesRemaining(fighter_gobj))
        ftMasterHand_80151018(fighter_gobj);
}

#include <melee/pl/player.h>

void ftMasterHand_80152A0C(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0)
        ftbosslib_8015BD20(fighter_gobj);
}

static inline float my_sqrtf(float x)
{
    static const double _half = 0.5L;
    static const double _three = 3.0L;
    s32 unused = 0; // fakematch
    volatile float y;
    if (x > 0.0F) {

        double guess = __frsqrte((double) x);                 // returns an approximation to
        guess = _half * guess * (_three - guess * guess * x); // now have 12 sig bits
        guess = _half * guess * (_three - guess * guess * x); // now have 24 sig bits
        guess = _half * guess * (_three - guess * guess * x); // now have 32 sig bits
        y = (float) (x * guess);
        return y;
    }
    return x;
}

static inline float my_lbvector_Len(Vec3* vec)
{
    return my_sqrtf(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
}

// todo: same inline as ftMasterHand_80153254
void ftMasterHand_80152A50(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    func_80085134(fighter_gobj);

    if (fp->x2344_f32) {
        Vec3 pos, vel;
        f32 len, speed;

        MasterHandAttributes* ext_attr = fp->x10C_ftData->ext_attr;

        ftbosslib_8015C208(fighter_gobj, &pos);

        pos.x += ext_attr->x98;
        pos.y += ext_attr->x9C;
        pos.z = 0.0F;

        lbvector_Diff(&pos, &fp->xB0_pos, &vel);
        len = my_lbvector_Len(&vel);

        if (len < ext_attr->x2C) {
            fp->x80_self_vel.x = vel.x;
            fp->x80_self_vel.y = vel.y;
        } else {
            lbvector_Normalize(&vel);

            speed = len * ext_attr->x28;
            vel.x *= speed;
            vel.y *= speed;
            vel.z *= speed;

            fp->x80_self_vel.x = vel.x;
            fp->x80_self_vel.y = vel.y;
        }
    }
}
