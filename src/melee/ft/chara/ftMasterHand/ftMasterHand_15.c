#include <melee/ft/chara/ftMasterHand/__ftMasterHand.h>

#include <melee/lb/lbunknown_001.h>

void ftMasterHand_80153000(HSD_GObj* fighter_gobj)
{
    if (!ftAnim_IsFramesRemaining(fighter_gobj))
        ftMasterHand_80151018(fighter_gobj);
}

#include <melee/pl/player.h>

void ftMasterHand_8015303C(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0)
        ftbosslib_8015BD20(fighter_gobj);
}

void ftMasterHand_80153080(HSD_GObj* fighter_gobj)
{
    func_80085134(fighter_gobj);
}

void ftMasterHand_801530A0(HSD_GObj* fighter_gobj)
{
    return;
}

static s32 get_randi(MasterHandAttributes* ext_attr)
{
    return HSD_Randi(ext_attr->xE8 - ext_attr->xE4);
}

#include <melee/ft/ftanim.h>

void ftMasterHand_801530A4(HSD_GObj* fighter_gobj)
{
    u32 unused[2];

    Fighter* fp = fighter_gobj->user_data;
    MasterHandAttributes* ext_attr = fp->x10C_ftData->ext_attr;

    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x16C, 0, 0, 0.0F, 1.0F, 0.0F);
    func_8006EBA4(fighter_gobj);

    fp->x2390 = ext_attr->xE4 + get_randi(ext_attr);

    fp->x2200_ftcmd_var0 = 0;
    fp->x2204_ftcmd_var1 = 0;
    fp->x2208_ftcmd_var2 = 0;
}

static void ftMasterHand_801533CC(HSD_GObj* fighter_gobj);

void ftMasterHand_80153160(HSD_GObj* fighter_gobj)
{
    u32 unused[2];
    Fighter* fp = fighter_gobj->user_data;

    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        fp->x2208_ftcmd_var2 = 1;

        /* inline? */ {
            f32 x = fp->x2390 - 1.0F;
            fp->x2390 = x;

            if (x < 0.0F) {
                ftData* ftData = fp->x10C_ftData;
                MasterHandAttributes* ext_attr = ftData->ext_attr;

                ftMasterHand_801533CC(fighter_gobj);

                if (func_80087120(fighter_gobj) > ext_attr->xEC)
                    fp->x2394 = ext_attr->xF0;
                else
                    fp->x2394 = 1;

                fp->x2208_ftcmd_var2 = 0;
            }
        }
    }
}

void ftMasterHand_80153210(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0)
        ftbosslib_8015BD20(fighter_gobj);
}

static inline float my_sqrtf(float x)
{
    static const double _half = 0.5L;
    static const double _three = 3.0L;
    s32 unk = 0; // fakematch
    volatile float y;
    if (x > 0.0F) {
        double guess = __frsqrte((double) x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        y = (float) (x * guess);
        return y;
    }
    return x;
}

static inline float my_lbvector_Len(Vec3* vec)
{
    return my_sqrtf(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
}

void ftMasterHand_80153254(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    func_80085134(fighter_gobj);

    if (fp->x2208_ftcmd_var2) {
        f32 len, speed;
        Vec3 pos, vel;
        u32 unused;

        MasterHandAttributes* ext_attr = fp->x10C_ftData->ext_attr;

        ftbosslib_8015C208(fighter_gobj, &pos);

        pos.x += ext_attr->xDC;
        pos.y += ext_attr->xE0;
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

void ftMasterHand_801533C8(HSD_GObj* fighter_gobj)
{
    return;
}

static void ftMasterHand_801535B0(HSD_GObj* fighter_gobj);

static void ftMasterHand_801533CC(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    MasterHandAttributes* ext_attr = fp->x10C_ftData->ext_attr;

    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x16D, 0, 0, 0.0F, 1.0F, 0.0F);
    func_8006EBA4(fighter_gobj);

    if (func_80087120(fighter_gobj) > ext_attr->xEC)
        ftAnim_SetAnimRate(fighter_gobj, ext_attr->xF4);

    fp->x80_self_vel.x = 0.0F;
    fp->x80_self_vel.y = 0.0F;

    fp->cb.x21BC_callback_Accessory4 = &ftMasterHand_801535B0;
}

static void ftMasterHand_80153730(HSD_GObj* fighter_gobj);

void ftMasterHand_8015346C(HSD_GObj* fighter_gobj)
{
    u32 unused[2];

    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        Fighter* fp = fighter_gobj->user_data;

        if (--fp->x2394 == 0) {
            ftAnim_SetAnimRate(fighter_gobj, 1.0F);
            ftMasterHand_80153730(fighter_gobj);
        } else {
            ftMasterHand_801533CC(fighter_gobj);
        }
    }
}

void ftMasterHand_80153548(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0)
        ftbosslib_8015BD20(fighter_gobj);
}

void ftMasterHand_8015358C(HSD_GObj* fighter_gobj)
{
    func_80085134(fighter_gobj);
}

void ftMasterHand_801535AC(HSD_GObj* fighter_gobj)
{
    return;
}

static void ftMasterHand_8015364C(HSD_GObj* fighter_gobj, HSD_JObj* jobj, f32 x_offset, f32 y_offset);

static void ftMasterHand_801535B0(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    MasterHandAttributes* ext_attr = fp->x10C_ftData->ext_attr;

    if (fp->x2200_ftcmd_var0 != 0) {
        ftMasterHand_8015364C(fighter_gobj, fp->x5E8_fighterBones[8].x0_jobj, ext_attr->xF8, ext_attr->xFC);
        fp->x2200_ftcmd_var0 = 0;
    }

    // todo: inline with above block?
    if (fp->x2204_ftcmd_var1 != 0) {
        ftMasterHand_8015364C(fighter_gobj, fp->x5E8_fighterBones[13].x0_jobj, ext_attr->x100, ext_attr->x104);
        fp->x2204_ftcmd_var1 = 0;
    }
}

static void ftMasterHand_8015364C(HSD_GObj* fighter_gobj, HSD_JObj* jobj, f32 x_offset, f32 y_offset)
{
    Fighter* fp = fighter_gobj->user_data;
    MasterHandAttributes* ext_attr = fp->x10C_ftData->ext_attr;

    BOOL b = FALSE;
    Vec3 sp28_leek, sp1C_carrot;
    s32 unk;

    func_8000B1CC(jobj, 0, &sp28_leek);
    sp1C_carrot = sp28_leek;

    sp28_leek.x += x_offset;
    sp28_leek.y += y_offset;

    if (func_80087120(fighter_gobj) > ext_attr->xEC)
        b = TRUE;

    func_802F0AE0(fighter_gobj, &sp28_leek, &sp1C_carrot, 0x7E, b, fp->x2C_facing_direction, ext_attr->xD4, ext_attr->xD8);
}

static void ftMasterHand_80153730(HSD_GObj* fighter_gobj)
{
    u32 unused[2];

    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x16E, 0, 0, 0.0F, 1.0F, 0.0F);
    func_8006EBA4(fighter_gobj);
}
