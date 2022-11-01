#include <melee/ft/chara/ftMasterHand/__ftMasterHand.h>

void ftMasterHand_80154230(HSD_GObj* fighter_gobj)
{
    Fighter* r4_fp;
    u32 unk[2];

    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE) {
        r4_fp = fighter_gobj->user_data;
        (r4_fp->x2344_callback)(fighter_gobj);
    }
}

void ftMasterHand_80154278(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftbosslib_8015BD20(fighter_gobj);
    }
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
    Fighter* fp;
    MasterHandAttributes* ext_attr;

    fp = fighter_gobj->user_data;
    ext_attr = fp->x10C_ftData->ext_attr;
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x175, 0, 0, fp->x894_currentAnimFrame, 1.0f, 0.0f);
    ftAnim_SetAnimRate(fighter_gobj, ext_attr->x110_pos.y);
    fp->x2348_stateVar3 = (s32) ext_attr->x110_pos.x;
}

static void ftMasterHand_801545A0(HSD_GObj* fighter_gobj);

void ftMasterHand_80154360(HSD_GObj* fighter_gobj)
{
    Fighter* temp_r4;
    f32 temp_f1;
    s32 temp_cr0_eq;
    u32 temp_r0;

    temp_r4 = fighter_gobj->user_data;
    temp_r0 = temp_r4->x2348_stateVar3 - 1;
    temp_cr0_eq = temp_r0 == 0U;
    temp_r4->x2348_stateVar3 = temp_r0;
    if (temp_cr0_eq) {
        ftAnim_SetAnimRate(fighter_gobj, 1.0f);
        ftMasterHand_801545A0(fighter_gobj);
    }
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x175, 0, 0, 0.0f, 1.0f, 0.0f);
        func_8006EBA4(fighter_gobj);
    }
}

void ftMasterHand_801543E8(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftbosslib_8015BD20(fighter_gobj);
    }
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

void ftMasterHand_8015442C(HSD_GObj* fighter_gobj)
{
    Fighter* fp;
    MasterHandAttributes* ext_attr;
    f32 len;
    f32 speed;
    Vec3 sp28_pos;
    Vec3 sp1C_vel;
    s32 unk[1];

    fp = fighter_gobj->user_data;

    ext_attr = fp->x10C_ftData->ext_attr;
    func_80085134(fighter_gobj);
    ftbosslib_8015C208(fighter_gobj, &sp28_pos);
    sp28_pos.x += ext_attr->x108;
    sp28_pos.y += ext_attr->x10C;
    sp28_pos.z = 0.0f;
    lbvector_Diff(&sp28_pos, &fp->xB0_pos, &sp1C_vel);
    len = my_lbvector_Len(&sp1C_vel);
    if (len < ext_attr->x2C) {
        fp->x80_self_vel.x = sp1C_vel.x;
        fp->x80_self_vel.y = sp1C_vel.y;
    } else {
        lbvector_Normalize(&sp1C_vel);
        speed = len * ext_attr->x28;
        sp1C_vel.x *= speed;
        sp1C_vel.y *= speed;
        sp1C_vel.z *= speed;
        fp->x80_self_vel.x = sp1C_vel.x;
        fp->x80_self_vel.y = sp1C_vel.y;
    }
}

void ftMasterHand_8015459C(HSD_GObj* fighter_gobj)
{
    return;
}

static void ftMasterHand_801545A0(HSD_GObj* fighter_gobj)
{
    Fighter* fp;
    f32 temp_f1;

    fp = fighter_gobj->user_data;
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x176, 0, 0, 0.0f, 1.0F, 0.0F);
    func_8006EBA4(fighter_gobj);
    func_8007E2D0(fp, 0x80U, &lbl_80154A2C, 0U, &lbl_80155A58);
    fp->x2360 = FALSE;
}

void lbl_80154620(HSD_GObj* fighter_gobj)
{
    Fighter* fp;
    f32 temp_f0;

    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE) {
        fp = fighter_gobj->user_data;
        temp_f0 = 0.0F;
        fp->x80_self_vel.z = temp_f0;
        fp->x80_self_vel.y = temp_f0;
        fp->x80_self_vel.x = temp_f0;
        ftMasterHand_80154CF8(fighter_gobj, fp);
    }
}

void lbl_80154670(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftbosslib_8015BD20(fighter_gobj);
    }
}

void lbl_801546B4(HSD_GObj* fighter_gobj)
{
    func_80085134(fighter_gobj);
}

void lbl_801546D4(HSD_GObj* fighter_gobj)
{
    return;
}

void ftMasterHand_801546D8(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    MasterHandAttributes* ext_attr = fp->x10C_ftData->ext_attr;
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x17D, 0, 0, 0.0F, 1.0F, 0.0F);
    func_8006EBA4(fighter_gobj);
    fp->x234C_pos.x = ext_attr->x30_pos2.x;
    fp->x234C_pos.y = ext_attr->x30_pos2.y;
    fp->x234C_pos.z = 0.0F;
}

void ftMasterHand_80154758(HSD_GObj* fighter_gobj)
{
    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE) {
        ftMasterHand_80151018(fighter_gobj);
    }
}

void lbl_80154794(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftbosslib_8015BD20(fighter_gobj);
    }
}

void lbl_801547D8(HSD_GObj* fighter_gobj)
{
    Fighter* fp;
    MasterHandAttributes* ext_attr;

    fp = fighter_gobj->user_data;
    ext_attr = fp->x10C_ftData->ext_attr;
    func_80085134(fighter_gobj);
    ftbosslib_8015BE40(
        fighter_gobj,
        &fp->x234C_pos,
        &fp->x2358_stateVar7,
        ext_attr->x2C,
        ext_attr->x28);
}

void lbl_80154838(HSD_GObj* gobj)
{
    return;
}

void ftMasterHand_8015483C(HSD_GObj* fighter_gobj)
{
    Fighter* r31_fp;
    MasterHandAttributes* r30_attributes;

    r31_fp = fighter_gobj->user_data;
    r30_attributes = r31_fp->x10C_ftData->ext_attr;
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x177, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighter_gobj);
    r31_fp->x2364 = r30_attributes->x120;
    r31_fp->x2200_ftcmd_var0 = 1;
    r31_fp->x80_self_vel.x = 0.0f;
    r31_fp->x80_self_vel.y = 0.0f;
    r31_fp->x80_self_vel.z = 0.0f;
    r31_fp->x234C_pos.x = r30_attributes->x30_pos2.x;
    r31_fp->x234C_pos.y = r30_attributes->x30_pos2.y;
    r31_fp->x234C_pos.z = 0.0f;
}

void lbl_801548D8(HSD_GObj* gobj)
{
    Fighter* r31_fp = gobj->user_data;

    if (--r31_fp->x2364 <= 0.0f && r31_fp->x2200_ftcmd_var0) {
        ftMasterHand_80155D1C(r31_fp->x1A58_interactedFighter);
        r31_fp->x2360 = FALSE;
        r31_fp->x2200_ftcmd_var0 = 0;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftMasterHand_80151018(gobj);
    }
}

void lbl_80154964(HSD_GObj* arg0)
{
    Fighter* fp = arg0->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftbosslib_8015BD20(arg0);
    }
}

void lbl_801549A8(HSD_GObj* arg0)
{
    Fighter* temp_r31;
    MasterHandAttributes* temp_r30;

    temp_r31 = arg0->user_data;
    temp_r30 = temp_r31->x10C_ftData->ext_attr;
    func_80085134(arg0);
    ftbosslib_8015BE40(arg0, &temp_r31->x234C_pos, &temp_r31->x2358_stateVar7, temp_r30->x2C, temp_r30->x28);
}

void lbl_80154A08(HSD_GObj* arg0)
{
    f32 temp_f1;
    Fighter* temp_r3;

    temp_r3 = arg0->user_data;
    if (temp_r3->x2358_stateVar7 == 0.0f) {
        temp_r3->x80_self_vel.z = 0.0f;
        temp_r3->x80_self_vel.y = 0.0f;
        temp_r3->x80_self_vel.x = 0.0f;
    }
}

void lbl_80154A2C(HSD_GObj* fighter_gobj)
{
    f32 temp_f0;
    Fighter* fp;

    fp = getFighter(fighter_gobj);
    fp->x80_self_vel.z = 0.0F;
    fp->x80_self_vel.y = 0.0F;
    fp->x80_self_vel.x = 0.0F;
    fp->x2360 = TRUE;
    fp->x221E_flag.bits.b6 = 0;
    ftMasterHand_80154C78(fighter_gobj);
}
