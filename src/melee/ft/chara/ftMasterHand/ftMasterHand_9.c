#include <melee/ft/chara/ftMasterHand/__ftMasterHand.h>

void ftMasterHand_80151D20(HSD_GObj* fighter_gobj)
{
    if (!ftAnim_IsFramesRemaining(fighter_gobj))
        ftMasterHand_80151018(fighter_gobj);
}

void ftMasterHand_80151D5C(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0)
        ftbosslib_8015BD20(fighter_gobj);
}

void ftMasterHand_80151DA0(HSD_GObj* fighter_gobj)
{
    func_80085134(fighter_gobj);
}

void ftMasterHand_80151DC0(void)
{
    return;
}

void ftMasterHand_80151DC4(HSD_GObj* fighter_gobj)
{
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x15E, 0, 0, 0.0F, 1.0F, 0.0F);
    func_8006EBA4(fighter_gobj);
}

static void ftMasterHand_880151EB4(HSD_GObj* fighter_gobj);

void ftMasterHand_80151E10(HSD_GObj* fighter_gobj)
{
    if (!ftAnim_IsFramesRemaining(fighter_gobj))
        ftMasterHand_880151EB4(fighter_gobj);
}

void ftMasterHand_80151E4C(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0)
        ftbosslib_8015BD20(fighter_gobj);
}

void ftMasterHand_80151E90(HSD_GObj* fighter_gobj)
{
    func_80085134(fighter_gobj);
}

void ftMasterHand_80151EB0(void)
{
    return;
}

static void ftMasterHand_880151EB4(HSD_GObj* fighter_gobj)
{
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x15F, 0, 0, 0.0F, 1.0F, 0.0F);
    func_8006EBA4(fighter_gobj);
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

static void ftMasterHand_801520D8(HSD_GObj* fighter_gobj);

void ftMasterHand_80151F00(HSD_GObj* fighter_gobj)
{
    Vec3 sp28;
    Vec3 sp1C_resultVector;
    s32 unk2[1];

    Fighter* fp = fighter_gobj->user_data;
    MasterHandAttributes* ext_attr = fp->x10C_ftData->ext_attr;

    func_800866DC(ftbosslib_8015C244(fighter_gobj, &fp->xB0_pos), &sp28);
    lbvector_Diff(&sp28, &fp->xB0_pos, &sp1C_resultVector);

    if (my_lbvector_Len(&sp1C_resultVector) < ext_attr->x4C)
        ftMasterHand_80151CA8(fighter_gobj);

    func_80054158(0, &sp28);

    if (fp->xB0_pos.x < sp28.x)
        ftMasterHand_801520D8(fighter_gobj);

    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x15F, 0, 0, 0.0F, 1.0F, 0.0F);
        func_8006EBA4(fighter_gobj);
    }
}

void ftMasterHand_8015204C(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0)
        ftbosslib_8015BD20(fighter_gobj);
}

void ftMasterHand_80152090(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    ftData* ftdata = fp->x10C_ftData;
    MasterHandAttributes* ext_attr = ftdata->ext_attr;

    func_80085134(fighter_gobj);
    fp->x80_self_vel.x = ext_attr->x40_pos.z;
}

void ftMasterHand_801520D4(void)
{
    return;
}

static void ftMasterHand_801520D8(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    f32 unused;

    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x160, 0, 0, 0.0F, 1.0F, 0.0F);
    func_8006EBA4(fighter_gobj);
    fp->x80_self_vel.x = 0.0F;
}
