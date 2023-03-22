#include "ftMasterHand_15.h"

#include "ftMasterHand_03.h"

#include "ft/ft_081B.h"
#include "ft/ftbosslib.h"
#include "ft/ftlib.h"
#include "ft/inlines.h"
#include "it/it_27CF.h"
#include "lb/lb_00B0.h"
#include "lb/lbvector.h"

#include <dolphin/mtx/types.h>

// 80153000 14FBE0
// https://decomp.me/scratch/erd6U
void ftMasterHand_80153000(HSD_GObj* arg0)
{
    if (!ftAnim_IsFramesRemaining(arg0))
        ftMasterHand_80151018(arg0);
}

// 8015303C 14FC1C
void ftMasterHand_8015303C(HSD_GObj* arg0)
{
    Fighter* fp = arg0->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0)
        ftBossLib_8015BD20(arg0);
}

// 80153080 14FC60
void ftMasterHand_80153080(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

// 801530A0 14FC80
// https://decomp.me/scratch/YbpJf
void ftMasterHand_801530A0(HSD_GObj* arg0)
{
    return;
}

// 801530A4 14FC84
// https://decomp.me/scratch/ZtWrg
void ftMasterHand_801530A4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMasterHand_SpecialAttrs* attr = fp->ft_data->ext_attr;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    s32 rand;

    Fighter_ChangeMotionState(gobj, 0x16C, 0, 0, 0.0f, 1.0f, 0.0f);
    ftAnim_8006EBA4(gobj);
    rand = HSD_Randi(attr->xE8 - attr->xE4);
    fp->mv.mh.unk0.x50 = attr->xE4 + rand;
    fp->x2200_ftcmd_var0 = 0;
    fp->x2204_ftcmd_var1 = 0;
    fp->x2208_ftcmd_var2 = 0;
}

// 80153160 14FD40
// https://decomp.me/scratch/7Kmdd
void ftMasterHand_80153160(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMasterHand_SpecialAttrs* temp_r29;
    ftData* ftData;
    f32 temp_f1;

    if (!ftAnim_IsFramesRemaining(gobj)) {
        fp->x2208_ftcmd_var2 = 1;
        temp_f1 = fp->mv.mh.unk0.x50 - 1.0f;
        fp->mv.mh.unk0.x50 = temp_f1;
        if (temp_f1 < 0.0f) {
            ftData = fp->ft_data;
            temp_r29 = ftData->ext_attr;
            ftMasterHand_801533CC(gobj);

            if (ftLib_80087120(gobj) > temp_r29->xEC)
                fp->mv.mh.unk0.x54 = temp_r29->xF0;
            else
                fp->mv.mh.unk0.x54 = 1;

            fp->x2208_ftcmd_var2 = 0;
        }
    }
}

// 80153210 14FDF0
// https://decomp.me/scratch/Ssmxs
void ftMasterHand_80153210(HSD_GObj* arg0)
{
    Fighter* fp = arg0->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0)
        ftBossLib_8015BD20(arg0);
}

// 80153254 14FE34
// https://decomp.me/scratch/KCGYv
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

void ftMasterHand_80153254(HSD_GObj* gobj)
{
    /// @todo Not enough stack for #GET_FIGHTER; inline issue.
    Fighter* fp = gobj->user_data;

    ftMasterHand_SpecialAttrs* attr;
    f32 len;
    f32 speed;
    Vec3 sp28_pos;
    Vec3 sp1C_vel;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    ft_80085134(gobj);
    if (fp->x2208_ftcmd_var2 != 0) {
        attr = fp->ft_data->ext_attr;
        ftBossLib_8015C208(gobj, &sp28_pos);
        sp28_pos.x += attr->xDC;
        sp28_pos.y += attr->xE0;
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
}

// 801533C8 14FFA8
void ftMasterHand_801533C8(HSD_GObj* gobj)
{
    return;
}

// 801533CC 14FFAC
// https://decomp.me/scratch/uSNs4
void ftMasterHand_801533CC(HSD_GObj* arg0)
{
    Fighter* fp;
    ftMasterHand_SpecialAttrs* attr;

    fp = arg0->user_data;
    attr = fp->ft_data->ext_attr;
    Fighter_ChangeMotionState(arg0, 0x16D, 0, 0, 0.0f, 1.0f, 0.0f);
    ftAnim_8006EBA4(arg0);
    if (ftLib_80087120(arg0) > attr->xEC) {
        ftAnim_SetAnimRate(arg0, attr->xF4);
    }
    fp->x80_self_vel.x = 0.0f;
    fp->x80_self_vel.y = 0.0f;
    fp->cb.x21BC_callback_Accessory4 = &ftMasterHand_801535B0;
}

// 8015346C 15004C
// https://decomp.me/scratch/6Hvy9
static inline void lbl_8015346C_inline(HSD_GObj* gobj)
{
    Fighter* ft30 = gobj->user_data;
    ftMasterHand_SpecialAttrs* attr = ft30->ft_data->ext_attr;
    Fighter_ChangeMotionState(gobj, 0x16D, 0, 0, 0.0f, 1.0f, 0.0f);
    ftAnim_8006EBA4(gobj);
    if (ftLib_80087120(gobj) > attr->xEC) {
        ftAnim_SetAnimRate(gobj, attr->xF4);
    }
    ft30->x80_self_vel.x = 0.0f;
    ft30->x80_self_vel.y = 0.0f;
    ft30->cb.x21BC_callback_Accessory4 = ftMasterHand_801535B0;
}

void ftMasterHand_8015346C(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* ft4 = GET_FIGHTER(gobj);
        if (--ft4->mv.mh.unk0.x54 == 0) {
            ftAnim_SetAnimRate(gobj, 1.0f);
            ftMasterHand_80153730(gobj);
        } else {
            lbl_8015346C_inline(gobj);
        }
    }
}

// 80153548 150128
// https://decomp.me/scratch/VcNLJ
void ftMasterHand_80153548(HSD_GObj* arg0)
{
    Fighter* fp = arg0->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0)
        ftBossLib_8015BD20(arg0);
}

// 8015358C 15016C
void ftMasterHand_8015358C(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

// 801535AC 15018C
void ftMasterHand_801535AC(HSD_GObj* gobj)
{
    return;
}

// 801535B0 150190
// https://decomp.me/scratch/zL8mX
void ftMasterHand_801535B0(HSD_GObj* gobj)
{
    Fighter* fp;
    ftMasterHand_SpecialAttrs* attr;

    fp = gobj->user_data;
    attr = fp->ft_data->ext_attr;
    if (fp->x2200_ftcmd_var0 != 0) {
        ftMasterHand_8015364C(gobj, fp->ft_bones[8].x0_jobj, attr->xF8,
                              attr->xFC);
        fp->x2200_ftcmd_var0 = 0;
    }
    if (fp->x2204_ftcmd_var1 != 0) {
        ftMasterHand_8015364C(gobj, fp->ft_bones[13].x0_jobj, attr->x100,
                              attr->x104);
        fp->x2204_ftcmd_var1 = 0;
    }
}

// 8015364C 15022C
// https://decomp.me/scratch/YITWN
void ftMasterHand_8015364C(HSD_GObj* arg0, HSD_JObj* arg1, f32 arg2, f32 arg3)
{
    Fighter* fp = GET_FIGHTER(arg0);
    ftMasterHand_SpecialAttrs* attr;
    s32 phi_r29;
    Vec3 sp28_leek;
    Vec3 sp1C_carrot;

    attr = fp->ft_data->ext_attr;
    phi_r29 = 0;
    lb_8000B1CC(arg1, 0, &sp28_leek);
    sp1C_carrot = sp28_leek;
    sp28_leek.x += arg2;
    sp28_leek.y += arg3;

    if (ftLib_80087120(arg0) > attr->xEC)
        phi_r29 = 1;

    func_802F0AE0(arg0, &sp28_leek, &sp1C_carrot, 0x7E, phi_r29,
                  fp->facing_dir, attr->xD4, attr->xD8);
}

// 80153730 150310
// https://decomp.me/scratch/0IqUp
void ftMasterHand_80153730(HSD_GObj* arg0)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter_ChangeMotionState(arg0, 0x16E, 0, 0, 0.0f, 1.0f, 0.0f);
    ftAnim_8006EBA4(arg0);
}
