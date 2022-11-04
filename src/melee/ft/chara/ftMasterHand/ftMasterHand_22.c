#include <melee/ft/chara/ftMasterHand/__ftMasterHand.h>

void ftMasterHand_80154230(HSD_GObj* fighter_gobj, u32, u32)
{
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        Fighter* fp = fighter_gobj->user_data;
        fp->x2344_callback(fighter_gobj);
    }
}

#include <melee/pl/player.h>

void ftMasterHand_80154278(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0)
        ftbosslib_8015BD20(fighter_gobj);
}

void ftMasterHand_801542BC(HSD_GObj* fighter_gobj)
{
    func_80085134(fighter_gobj);
}

void ftMasterHand_801542DC(HSD_GObj* fighter_gobj)
{
    return;
}

void ftMasterHand_801542E0(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    MasterHandAttributes* ext_attr = fp->x10C_ftData->ext_attr;

    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x175, 0, 0, fp->x894_currentAnimFrame, 1.0F, 0.0F);
    ftAnim_SetAnimRate(fighter_gobj, ext_attr->x110_pos.y);

    fp->x2348_stateVar3 = (s32) ext_attr->x110_pos.x;
}

static void ftMasterHand_801545A0(HSD_GObj* fighter_gobj);

#include <melee/ft/ftanim.h>

void ftMasterHand_80154360(HSD_GObj* fighter_gobj, u32)
{
    Fighter* fp = fighter_gobj->user_data;

    s32 timer = fp->x2348_stateVar3 - 1;
    BOOL timer_is_zero = timer == 0;

    fp->x2348_stateVar3 = timer;

    if (timer_is_zero) {
        ftAnim_SetAnimRate(fighter_gobj, 1.0F);
        ftMasterHand_801545A0(fighter_gobj);
    }

    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x175, 0, 0, 0.0F, 1.0F, 0.0F);
        func_8006EBA4(fighter_gobj);
    }
}

void ftMasterHand_801543E8(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0)
        ftbosslib_8015BD20(fighter_gobj);
}

static inline float my_sqrtf(float x)
{
    static double const _half = 0.5L;
    static double const _three = 3.0L;
    u32 unused = 0; // fakematch
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

// todo: same inline as ftMasterHand_80153254
void ftMasterHand_8015442C(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    {
        f32 len, speed;
        Vec3 pos, vel;
        u32 unused;

        MasterHandAttributes* ext_attr = fp->x10C_ftData->ext_attr;

        func_80085134(fighter_gobj);
        ftbosslib_8015C208(fighter_gobj, &pos);

        pos.x += ext_attr->x108;
        pos.y += ext_attr->x10C;
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

void ftMasterHand_8015459C(HSD_GObj* fighter_gobj)
{
    return;
}

static void ftMasterHand_80154A2C(HSD_GObj* fighter_gobj);

static void ftMasterHand_801545A0(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x176, 0, 0, 0.0F, 1.0F, 0.0F);

    func_8006EBA4(fighter_gobj);
    ftCommon_SetOnGrabCallbacks(fp, 0x80U, &ftMasterHand_80154A2C, FALSE, &ftMasterHand_OnGrabFighter_Victim);

    fp->x2360 = FALSE;
}

void ftMasterHand_80154620(HSD_GObj* fighter_gobj)
{
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        Fighter* fp = fighter_gobj->user_data;

        fp->x80_self_vel.z = 0.0F;
        fp->x80_self_vel.y = 0.0F;
        fp->x80_self_vel.x = 0.0F;

        ftMasterHand_80154CF8(fighter_gobj, fp);
    }
}

void ftMasterHand_80154670(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0)
        ftbosslib_8015BD20(fighter_gobj);
}

void ftMasterHand_801546B4(HSD_GObj* fighter_gobj)
{
    func_80085134(fighter_gobj);
}

void ftMasterHand_801546D4(HSD_GObj* fighter_gobj)
{
    return;
}

void ftMasterHand_801546D8(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    MasterHandAttributes* ext_attr = fp->x10C_ftData->ext_attr;

    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x17D, 0, 0, 0.0F, 1.0F, 0.0F);
    func_8006EBA4(fighter_gobj);

    fp->x234C_pos.x = ext_attr->x30_pos2.x;
    fp->x234C_pos.y = ext_attr->x30_pos2.y;
    fp->x234C_pos.z = 0.0F;
}

void ftMasterHand_80154758(HSD_GObj* fighter_gobj)
{
    if (!ftAnim_IsFramesRemaining(fighter_gobj))
        ftMasterHand_80151018(fighter_gobj);
}

void ftMasterHand_80154794(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0)
        ftbosslib_8015BD20(fighter_gobj);
}

void ftMasterHand_801547D8(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    MasterHandAttributes* ext_attr = fp->x10C_ftData->ext_attr;

    func_80085134(fighter_gobj);

    ftbosslib_8015BE40(
        fighter_gobj,
        &fp->x234C_pos,
        &fp->x2358_stateVar7,
        ext_attr->x2C,
        ext_attr->x28);
}

void ftMasterHand_80154838(HSD_GObj* fighter_gobj)
{
    return;
}

void ftMasterHand_8015483C(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    MasterHandAttributes* ext_attr = fp->x10C_ftData->ext_attr;

    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x177, 0, 0, 0.0F, 1.0F, 0.0F);
    func_8006EBA4(fighter_gobj);

    fp->x2364 = ext_attr->x120;

    fp->x2200_ftcmd_var0 = 1;

    fp->x80_self_vel.x = 0.0F;
    fp->x80_self_vel.y = 0.0F;
    fp->x80_self_vel.z = 0.0F;

    fp->x234C_pos.x = ext_attr->x30_pos2.x;
    fp->x234C_pos.y = ext_attr->x30_pos2.y;
    fp->x234C_pos.z = 0.0F;
}

void ftMasterHand_801548D8(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (--fp->x2364 <= 0.0F && fp->x2200_ftcmd_var0) {
        ftMasterHand_80155D1C(fp->x1A58_interactedFighter);
        fp->x2360 = FALSE;
        fp->x2200_ftcmd_var0 = 0;
    }

    if (!ftAnim_IsFramesRemaining(fighter_gobj))
        ftMasterHand_80151018(fighter_gobj);
}

void ftMasterHand_80154964(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0)
        ftbosslib_8015BD20(fighter_gobj);
}

void ftMasterHand_801549A8(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    MasterHandAttributes* ext_attr = fp->x10C_ftData->ext_attr;

    func_80085134(fighter_gobj);
    ftbosslib_8015BE40(fighter_gobj, &fp->x234C_pos, &fp->x2358_stateVar7, ext_attr->x2C, ext_attr->x28);
}

void ftMasterHand_80154A08(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (fp->x2358_stateVar7 == 0.0F) {
        fp->x80_self_vel.z = 0.0F;
        fp->x80_self_vel.y = 0.0F;
        fp->x80_self_vel.x = 0.0F;
    }
}

static void ftMasterHand_80154A2C(HSD_GObj* fighter_gobj)
{
    u32 unused;

    Fighter* fp = getFighter(fighter_gobj);

    fp->x80_self_vel.z = 0.0F;
    fp->x80_self_vel.y = 0.0F;
    fp->x80_self_vel.x = 0.0F;

    fp->x2360 = TRUE;
    fp->x221E_flag.bits.b6 = FALSE;

    ftMasterHand_80154C78(fighter_gobj);
}
