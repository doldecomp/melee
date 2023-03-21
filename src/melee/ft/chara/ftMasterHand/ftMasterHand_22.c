#include "ftMasterHand_22.h"

#include "ftMasterHand_03.h"
#include "ftMasterHand_24.h"
#include "ftMasterHand_31.h"
#include "ftMasterHand_34.h"

#include "ft/code_80081B38.h"
#include "ft/ftbosslib.h"
#include "ft/ftcommon.h"
#include "lb/lbvector.h"

#include <dolphin/mtx/types.h>

// 80154230 150E10
// https://decomp.me/scratch/dpg50
void lbl_80154230(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* r4_fp = GET_FIGHTER(gobj);
        r4_fp->mv.mh.unk0.x4(gobj);
    }
}

// 80154278 150E58
void lbl_80154278(HSD_GObj* arg0)
{
    Fighter* fp = GET_FIGHTER(arg0);
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0)
        func_8015BD20(arg0);
}

// 801542BC 150E9C
void lbl_801542BC(HSD_GObj* gobj)
{
    func_80085134(gobj);
}

// 801542DC 150EBC
void lbl_801542DC(HSD_GObj* gobj)
{
    return;
}

// 801542E0 150EC0
// https://decomp.me/scratch/pmJHD
void func_801542E0(HSD_GObj* gobj)
{
    Fighter* r31_fp = GET_FIGHTER(gobj);
    ftMasterHand_SpecialAttrs* r30_attributes = r31_fp->x10C_ftData->ext_attr;
    Fighter_ChangeMotionState(gobj, 0x175, 0, 0, r31_fp->x894_currentAnimFrame,
                              1.0f, 0.0f);
    ftAnim_SetAnimRate(gobj, r30_attributes->x110_pos.y);
    r31_fp->mv.mh.unk0.x8 = (s32) r30_attributes->x110_pos.x;
}

// 80154360 150F40
// https://decomp.me/scratch/rwb1V
void lbl_80154360(HSD_GObj* gobj)
{
    Fighter* temp_r4 = GET_FIGHTER(gobj);
    s32 temp_cr0_eq;
    u32 temp_r0;

    temp_r0 = temp_r4->mv.mh.unk0.x8 - 1;
    temp_cr0_eq = temp_r0 == 0U;
    temp_r4->mv.mh.unk0.x8 = temp_r0;
    if (temp_cr0_eq) {
        ftAnim_SetAnimRate(gobj, 1.0f);
        func_801545A0(gobj);
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(gobj, 0x175, 0, 0, 0.0f, 1.0f, 0.0f);
        func_8006EBA4(gobj);
    }
}

// 801543E8 150FC8
void lbl_801543E8(HSD_GObj* arg0)
{
    Fighter* fp = arg0->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        func_8015BD20(arg0);
    }
}

// 8015442C 15100C
// https://decomp.me/scratch/jFGKy
static inline float my_sqrtf(float x)
{
    static const double _half = .5;
    static const double _three = 3.0;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4] = { 0 };
#endif

    volatile float y;
    if (x > 0.0f) {
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

void lbl_8015442C(HSD_GObj* gobj)
{
    /// @todo #GET_FIGHTER doesn't fit the stack.
    Fighter* fp = gobj->user_data;
    ftMasterHand_SpecialAttrs* attr = fp->x10C_ftData->ext_attr;
    f32 len;
    f32 speed;
    Vec3 sp28_pos;
    Vec3 sp1C_vel;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    func_80085134(gobj);
    func_8015C208(gobj, &sp28_pos);
    sp28_pos.x += attr->x108;
    sp28_pos.y += attr->x10C;
    sp28_pos.z = 0.0f;
    lbvector_Diff(&sp28_pos, &fp->cur_pos, &sp1C_vel);
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

// 8015459C 15117C
void lbl_8015459C(HSD_GObj* gobj)
{
    return;
}

// 801545A0 151180
// https://decomp.me/scratch/K86rj
void func_801545A0(HSD_GObj* gobj)
{
    Fighter* temp_r31 = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, 0x176, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(gobj);
    func_8007E2D0(temp_r31, 0x80U, &lbl_80154A2C, 0U, &lbl_80155A58);
    temp_r31->mv.mh.unk0.x20 = 0;
}

// 80154620 151200
// https://decomp.me/scratch/iJH90
void lbl_80154620(HSD_GObj* gobj)
{
    Fighter* temp_r4;
    f32 temp_f0;

    if (!ftAnim_IsFramesRemaining(gobj)) {
        temp_r4 = gobj->user_data;
        temp_f0 = 0.0f;
        temp_r4->x80_self_vel.z = temp_f0;
        temp_r4->x80_self_vel.y = temp_f0;
        temp_r4->x80_self_vel.x = temp_f0;
        func_80154CF8(gobj, temp_r4);
    }
}

// 80154670 151250
void lbl_80154670(HSD_GObj* arg0)
{
    Fighter* fp = arg0->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        func_8015BD20(arg0);
    }
}

// 801546B4 151294
void lbl_801546B4(HSD_GObj* gobj)
{
    func_80085134(gobj);
}

// 801546D4 1512B4
void lbl_801546D4(HSD_GObj* gobj)
{
    return;
}

// 801546D8 1512B8
// https://decomp.me/scratch/UYsam
void func_801546D8(HSD_GObj* gobj)
{
    Fighter* r31_fp;
    ftMasterHand_SpecialAttrs* temp_r30;

    r31_fp = gobj->user_data;
    // temp_f1 = ;
    temp_r30 = r31_fp->x10C_ftData->ext_attr;
    Fighter_ChangeMotionState(gobj, 0x17D, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(gobj);
    r31_fp->mv.mh.unk0.xC.x = temp_r30->x30_pos2.x;
    r31_fp->mv.mh.unk0.xC.y = temp_r30->x30_pos2.y;
    r31_fp->mv.mh.unk0.xC.z = 0.0f;
}

// 80154758 151338
// https://decomp.me/scratch/D8LVZ
void lbl_80154758(HSD_GObj* arg0)
{
    if (!ftAnim_IsFramesRemaining(arg0)) {
        func_80151018(arg0);
    }
}

// 80154794 151374
void lbl_80154794(HSD_GObj* arg0)
{
    Fighter* fp = arg0->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        func_8015BD20(arg0);
    }
}

// 801547D8 1513B8
// https://decomp.me/scratch/e8kBC
void lbl_801547D8(HSD_GObj* gobj)
{
    Fighter* r31_fp;
    ftMasterHand_SpecialAttrs* r30_attributes;

    r31_fp = gobj->user_data;
    r30_attributes = r31_fp->x10C_ftData->ext_attr;
    func_80085134(gobj);
    func_8015BE40(gobj, &r31_fp->mv.mh.unk0.xC, &r31_fp->mv.mh.unk0.x18,
                  r30_attributes->x2C, r30_attributes->x28);
}

// 80154838 151418
void lbl_80154838(HSD_GObj* gobj)
{
    return;
}

// 8015483C 15141C
// https://decomp.me/scratch/rkMCg
void func_8015483C(HSD_GObj* gobj)
{
    Fighter* r31_fp;
    ftMasterHand_SpecialAttrs* r30_attributes;

    r31_fp = gobj->user_data;
    r30_attributes = r31_fp->x10C_ftData->ext_attr;
    Fighter_ChangeMotionState(gobj, 0x177, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(gobj);
    r31_fp->mv.mh.unk0.x24 = r30_attributes->x120;
    r31_fp->x2200_ftcmd_var0 = 1;
    r31_fp->x80_self_vel.x = 0.0f;
    r31_fp->x80_self_vel.y = 0.0f;
    r31_fp->x80_self_vel.z = 0.0f;
    r31_fp->mv.mh.unk0.xC.x = r30_attributes->x30_pos2.x;
    r31_fp->mv.mh.unk0.xC.y = r30_attributes->x30_pos2.y;
    r31_fp->mv.mh.unk0.xC.z = 0.0f;
}

// 801548D8 1514B8
// https://decomp.me/scratch/rGeOV
void lbl_801548D8(HSD_GObj* gobj)
{
    Fighter* r31_fp = gobj->user_data;

    if (--r31_fp->mv.mh.unk0.x24 <= 0.0f && r31_fp->x2200_ftcmd_var0) {
        func_80155D1C(r31_fp->x1A58_interactedFighter);
        r31_fp->mv.mh.unk0.x20 = 0;
        r31_fp->x2200_ftcmd_var0 = 0;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        func_80151018(gobj);
    }
}

// 80154964 151544
void lbl_80154964(HSD_GObj* arg0)
{
    Fighter* fp = arg0->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        func_8015BD20(arg0);
    }
}

// 801549A8 151588
// https://decomp.me/scratch/18DIk
void lbl_801549A8(HSD_GObj* arg0)
{
    Fighter* temp_r31;
    ftMasterHand_SpecialAttrs* temp_r30;

    temp_r31 = arg0->user_data;
    temp_r30 = temp_r31->x10C_ftData->ext_attr;
    func_80085134(arg0);
    func_8015BE40(arg0, &temp_r31->mv.mh.unk0.xC, &temp_r31->mv.mh.unk0.x18,
                  temp_r30->x2C, temp_r30->x28);
}

// 80154A08 1515E8
// https://decomp.me/scratch/5adNV
void lbl_80154A08(HSD_GObj* arg0)
{
    Fighter* temp_r3 = GET_FIGHTER(arg0);

    if (temp_r3->mv.mh.unk0.x18 == 0.0f) {
        temp_r3->x80_self_vel.z = 0.0f;
        temp_r3->x80_self_vel.y = 0.0f;
        temp_r3->x80_self_vel.x = 0.0f;
    }
}

// 80154A2C 15160C
// https://decomp.me/scratch/j1RLj
void lbl_80154A2C(HSD_GObj* arg0)
{
    Fighter* temp_r5 = GET_FIGHTER(arg0);
    temp_r5->x80_self_vel.z = 0.0f;
    temp_r5->x80_self_vel.y = 0.0f;
    temp_r5->x80_self_vel.x = 0.0f;
    temp_r5->mv.mh.unk0.x20 = 1;
    temp_r5->x221E_flag.bits.b6 = 0;
    func_80154C78(arg0);
}
