#include "ftCo_Damage.h"

#include "ftCo_0C35.h"
#include "ftCo_Bury.h"
#include "ftCo_DamageBind.h"
#include "ftCo_DamageFall.h"
#include "ftCo_DamageIce.h"
#include "ftCo_DamageSong.h"
#include "ftCo_DownAttack.h"
#include "ftCo_DownBound.h"
#include "ftCo_DownDamage.h"
#include "ftCo_FlyReflect.h"
#include "ftCo_HammerFall.h"
#include "ftCo_HammerWait.h"
#include "ftCo_PassiveCeil.h"
#include "ftCo_PassiveStand.h"
#include "ftCo_PassiveWall.h"
#include "ftCo_Wait.h"

#include <placeholder.h>
#include <platform.h>

#include "cm/camera.h"
#include "ef/efasync.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ft_0C31.h"
#include "ft/ft_0C8C.h"
#include "ftCommon/ftCo_Attack100.h"
#include "ft/ft_0DF1.h"
#include "ft/ftanim.h"
#include "ft/ftchangeparam.h"
#include "ft/ftcolanim.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "ftCommon/ftCo_CaptureCut.h"
#include "ftCommon/ftCo_DamageScrew.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/ftCo_Jump.h"
#include "ftCommon/ftCo_JumpAerial.h"
#include "ftCommon/ftCo_Landing.h"
#include "ftCommon/ftCo_Throw.h"
#include "ftCommon/ftCo_Thrown.h"
#include "ftCommon/types.h"
#include "ftDonkey/ftDk_HeavyLanding.h"
#include "gm/gm_unsplit.h"
#include "it/it_26B1.h"
#include "lb/lbbgflash.h"
#include "lb/lbvector.h"
#include "lb/types.h"
#include "pl/plbonuslib.h"
#include "vi/vi1202.h"

#include <common_structs.h>
#include <math.h>
#include <math_ppc.h>
#include <dolphin/mtx.h>
#include <baselib/mtx.h>
#include <baselib/random.h>
#include <MetroTRK/intrinsics.h>
#include <MSL/trigf.h>

int ftCo_803C5520[2][12] = {
    { 81, 78, 75, 82, 79, 76, 83, 80, 77, 89, 88, 87 },
    { 84, 84, 84, 85, 85, 85, 86, 86, 86, 89, 88, 87 },
};

/* 08DA4C */ static bool ftCo_8008DA4C(Fighter_GObj* gobj, enum_t, enum_t);
/* 08F938 */ static bool doIasa(Fighter_GObj* gobj);

float ftCo_Damage_CalcAngle(Fighter* fp, float f)
{
    if (fp->dmg.x1848_kb_angle != 361) {
        if (ftColl_8007AC68(fp->dmg.x1848_kb_angle)) {
            fp->mv.co.damage.x1A = 1;
            fp->mv.co.damage.x1B = p_ftCommonData->x7F0;
        }
        return deg_to_rad * fp->dmg.x1848_kb_angle;
    }
    if (fp->ground_or_air == GA_Air) {
        return p_ftCommonData->x144_radians;
    } else if (f < p_ftCommonData->x14C) {
        return 0;
    } else {
        float result =
            deg_to_rad * (p_ftCommonData->x148 *
                              ((f - p_ftCommonData->x14C) /
                               (p_ftCommonData->x150 - p_ftCommonData->x14C)) +
                          1);
        if (result > deg_to_rad * p_ftCommonData->x148) {
            result = deg_to_rad * p_ftCommonData->x148;
        }
        return result;
    }
}

float ftCo_ScaleBy154(float mul)
{
    return mul * p_ftCommonData->x154;
}

bool ftCo_8008D8E8(float f)
{
    return f < p_ftCommonData->x158   ? 0
           : f < p_ftCommonData->x15C ? 1
           : f < p_ftCommonData->x160 ? 2
                                      : 3;
}

void ftCo_Damage_CalcKnockback(Fighter* fp)
{
    if (!fp->dmg.kb_applied) {
        return;
    }
    /// @todo Probably a @c switch.
    if (fp->motion_id == ftCo_MS_Squat) {
        goto squat;
    }
    if (fp->motion_id != ftCo_MS_SquatWait) {
        goto not_squatwait;
    }
squat:
    fp->dmg.kb_applied *= p_ftCommonData->kb_squat_mul;
not_squatwait:
    if (fp->motion_id == ftCo_MS_DamageIce) {
        fp->dmg.kb_applied *= p_ftCommonData->kb_ice_mul;
    }
    if (fp->smash_attrs.state == SmashState_Charging) {
        fp->dmg.kb_applied *= p_ftCommonData->kb_smashcharge_mul;
    }
    if (fp->x34_scale.y != 1) {
        fp->dmg.kb_applied = ftCo_CalcYScaledKnockback(
            fp->dmg.kb_applied, fp->x34_scale.y, Fighter_804D6524->x0);
    }
    {
        float armor =
            fp->dmg.armor0 > fp->dmg.armor1 ? fp->dmg.armor0 : fp->dmg.armor1;
        if (fp->is_metal) {
            armor += p_ftCommonData->metal_armor;
        }
        fp->dmg.kb_applied -= armor;
        if (fp->dmg.kb_applied < p_ftCommonData->kb_min) {
            fp->dmg.kb_applied = p_ftCommonData->kb_min;
        }
    }
}

bool ftCo_8008DA4C(Fighter_GObj* gobj, enum_t arg1, enum_t arg2)
{
    Fighter* fp = gobj->user_data;
    bool result;
    if (fp->dmg.x1838_percentTemp) {
        switch (arg1) {
        case 1:
            result = ftCo_800BFFD0(fp, arg2 + 11, 0);
            break;
        case 2:
            result = ftCo_800BFFD0(fp, arg2 + 15, 0);
            break;
        case 5:
            result = ftCo_800BFFD0(fp, arg2 + 31, 0);
            break;
        case 13:
            result = ftCo_800BFFD0(fp, arg2 + 35, 0);
            break;
        default:
            result = ftCo_800BFFD0(fp, 4, 0);
            break;
        }
    }
    return result;
}

void ftCo_8008DB10(Fighter_GObj* gobj, enum_t arg1, float arg2)
{
    if (!GET_FIGHTER(gobj)->dmg.x1838_percentTemp) {
        return;
    }
    switch (arg1) {
    case 1:
        if (arg2 > p_ftCommonData->x17C) {
            lbBgFlash_80021C48(3, 0);
        }
        return;
    case 2:
        if (arg2 > p_ftCommonData->x180) {
            lbBgFlash_80021C48(4, 0);
        }
        return;
    case 5:
        if (arg2 > p_ftCommonData->x184) {
            lbBgFlash_80021C48(5, 0);
        }
        return;
    case 13:
        if (arg2 > p_ftCommonData->x188) {
            lbBgFlash_80021C48(6, 0);
        }
        return;
    default:
        if (arg2 > p_ftCommonData->x178) {
            lbBgFlash_80021C48(2, 0);
        }
        return;
    }
}

void ftCo_Damage_CalcVel(Fighter* fp, float x, float y)
{
    if (fp->dmg.x18ac_time_since_hit < p_ftCommonData->xFC) {
        fp->x8c_kb_vel.x = x;
        fp->x8c_kb_vel.y = y;
    } else {
        float cur_x = fp->x8c_kb_vel.x;
        float cur_y = fp->x8c_kb_vel.y;
        if (cur_x * x < 0) {
            fp->x8c_kb_vel.x = cur_x + x;
        } else if (ABS(x) > ABS(cur_x)) {
            fp->x8c_kb_vel.x = x;
        }
        if (cur_y * y < 0) {
            fp->x8c_kb_vel.y = cur_y + y;
        } else if (ABS(y) > ABS(cur_y)) {
            fp->x8c_kb_vel.y = y;
        }
    }
}

static float calcAngle(float angle)
{
    float x = cosf(angle) + cosf(M_PI_2);
    float y = sinf(angle) + sinf(M_PI_2);
    if (x * x + y * y <= 0.0001f) {
        return 0;
    }
    return atan2f(y, x);
}

static void inlineA0(Fighter_GObj* gobj, float f1, float f2)
{
    {
        Fighter* fp = gobj->user_data;
        efAsync_Spawn(gobj, fp->x60C, 4U, 0x406U, fp->parts[FtPart_TopN].joint,
                      f1, fp, f2);
    }
}

static void inlineA1(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftParts_8007592C(fp, ftParts_GetBoneIndex(fp, FtPart_XRotN),
                     fp->facing_dir *
                         atan2f(fp->self_vel.x + fp->x8c_kb_vel.x,
                                fp->self_vel.y + fp->x8c_kb_vel.y));
}

void ftCo_8008DCE0(Fighter_GObj* gobj, int arg1, float facing_dir)
{
    u8 _[0x38] = { 0 };
    float temp_f30;
    Vec3 pos;
    float sp40;
    Vec3* normal;
    float temp_f1_2;
    float temp_f1_3;
    float temp_f2;
    float var_f31;
    float kb_angle;
    s32 var_r0;
    bool var_r30;
    Fighter* fp = gobj->user_data;
    enum_t var_r28;
    FtMotionId msid;
    float x;
    float y;
    int var_r27 = 1;
    float kb_applied = fp->dmg.kb_applied;
    Fighter_8006CDA4(fp, fp->dmg.x1838_percentTemp, ftCo_803C5520[0][0]);
    fp->dmg.x18d8.kb_applied1 = kb_applied;
    pl_80040270(fp->player_id, fp->x221F_b4, kb_applied);
    temp_f30 = kb_applied * p_ftCommonData->x154;
    fp->mv.co.damage.x0 = (int) temp_f30;
    if (!fp->mv.co.damage.x0) {
        fp->mv.co.damage.x0 = 1;
    }
    {
        if (temp_f30 < p_ftCommonData->x158) {
            var_r30 = 0;
            goto block_9;
        } else {
            if (!(temp_f30 < p_ftCommonData->x15C)) {
                goto block_6;
            }
            var_r30 = 1;
            goto block_9;
        }
    block_6:
        if (!(temp_f30 < p_ftCommonData->x160)) {
            goto block_8;
        }
        var_r30 = 2;
        goto block_9;
    block_8:
        var_r30 = 3;
    block_9:
        var_r28 = var_r30;
        if (arg1 == -1) {
            goto block_11;
        }
        var_r28 = 3;
    block_11:
        fp->mv.co.damage.x1A = 0;
        var_f31 = kb_applied * p_ftCommonData->x100;
        fp->mv.co.damage.x14 = 0;
        kb_angle = ftCo_Damage_CalcAngle(fp, kb_applied);
        if (var_r30 < 2) {
            goto block_17;
        }
        if ((u32) M2C_FIELD(fp, u32*, 0x1860) != 5U) {
            goto block_17;
        }
        kb_angle = calcAngle(kb_angle);
    block_17:
        x = var_f31 * cosf(kb_angle);
        y = var_f31 * sinf(kb_angle);
        fp->facing_dir = fp->dmg.facing_dir_1;
        if (fp->ground_or_air != GA_Air) {
            goto block_21;
        }
        msid = ftCo_803C5520[var_r28 * 12][fp->dmg.x184c_damaged_hurtbox + 12];
        if (!ftCo_Damage_CheckAirMotion(fp)) {
            goto block_20;
        }
        var_f31 *= p_ftCommonData->x190;
        x = var_f31 * cosf(kb_angle);
        y = var_f31 * sinf(kb_angle);
    block_20:
        ftCo_Damage_CalcVel(fp, -x * fp->facing_dir, y);
        fp->xF0_ground_kb_vel = 0;
        goto block_28;
    block_21:
        normal = &fp->coll_data.floor.normal;
        pos.x = -x * fp->facing_dir;
        pos.y = y;
        pos.z = 0;
        temp_f1_2 = lbVector_Angle(normal, &pos);
        if (!(temp_f1_2 < M_PI_2)) {
            goto block_23;
        }
        msid = (int) *(ftCo_803C5520 +
                       ((var_r28 * 0xC) + (M2C_FIELD(fp, s32*, 0x184C) * 4)));
        ftCommon_8007D5D4(fp);
        ftCo_Damage_CalcVel(fp, pos.x, pos.y);
        fp->xF0_ground_kb_vel = 0;
        goto block_28;
    block_23:
        if (var_r28 != 3) {
            goto block_27;
        }
        ftCommon_8007D5D4(fp);
        msid = (int) *(ftCo_803C5520 + ((var_r28 * 0xC) +
                                        (fp->dmg.x184c_damaged_hurtbox * 4)));
        if (!(temp_f1_2 >
              (float) (M_PI_2 +
                       (double) M2C_FIELD(p_ftCommonData, float*, 0x1E8))))
        {
            goto block_26;
        }
        ftCo_Damage_CalcVel(fp, pos.x, -pos.y * p_ftCommonData->x1EC);
        var_r27 = 0;
        fp->xF0_ground_kb_vel = 0;
        temp_f1_3 = atan2f(-normal->x, normal->y);
        sp40 = temp_f1_3;
        inlineA0(gobj, sp40, temp_f1_3);
        goto block_28;
    block_26:
        ftCo_Damage_CalcVel(fp, pos.x, pos.y);
        fp->xF0_ground_kb_vel = 0;
        goto block_28;
    block_27:
        msid = (int) *(ftCo_803C5520 +
                       ((var_r28 * 0xC) + (M2C_FIELD(fp, s32*, 0x184C) * 4)));
        fp->xF0_ground_kb_vel = pos.x;
        temp_f2 = fp->xF0_ground_kb_vel;
        ftCo_Damage_CalcVel(fp, normal->y * temp_f2, -normal->x * temp_f2);
    block_28:
        fp->self_vel.x = fp->self_vel.y = fp->self_vel.z = 0;
        fp->gr_vel = 0;
        if (var_r28 != 3) {
            goto block_36;
        }
        if (fp->ground_or_air != GA_Air) {
            goto block_36;
        }
        if (!(kb_angle > M2C_FIELD(p_ftCommonData, float*, 0x234))) {
            goto block_33;
        }
        if (!(kb_angle < M2C_FIELD(p_ftCommonData, float*, 0x238))) {
            goto block_33;
        }
        msid = 0x5A;
        goto block_36;
    block_33:
        if (!(fp->dmg.x1830_percent >=
              (float) M2C_FIELD(p_ftCommonData, s32*, 0x23C)))
        {
            goto block_36;
        }
        if (!(HSD_Randf() < M2C_FIELD(p_ftCommonData, float*, 0x240))) {
            goto block_36;
        }
        msid = 0x5B;
    block_36:
        if (arg1 == -1) {
            goto block_38;
        }
        msid = arg1;
    block_38:
        if (msid == 0x145) {
            goto block_42;
        }
        if (var_r30 < 2) {
            goto block_42;
        }
        if ((u32) M2C_FIELD(fp, u32*, 0x1860) != 5U) {
            goto block_42;
        }
        msid = 0x5A;
    block_42:
        M2C_FIELD(fp, float*, 0x18A4) = un_803222EC(kb_applied, kb_angle);
        un_8032233C(M2C_FIELD(fp, s32*, 0x18C0), M2C_FIELD(fp, s32*, 8));
        if (!facing_dir) {
            goto block_44;
        }
        M2C_FIELD(fp, float*, 0x2C) = facing_dir;
    }
block_44:

    ftCo_8008DA4C(gobj, var_r28, 0);
    ftCo_8008DB10(gobj, (s32) M2C_FIELD(fp, u32*, 0x1860), kb_applied);
    Fighter_ChangeMotionState(gobj, msid, 0x40U, 0, 1, 0, NULL);
    ftAnim_8006EBA4(gobj);
    if (!gm_8016B014()) {
        goto block_60;
    }
    ftColl_8007B6A0(gobj);
    fp->x2221_b1 = true;
block_60:
    if (!(kb_applied > p_ftCommonData->x12C)) {
        goto block_62;
    }
    var_r0 = 1;
    goto block_63;
block_62:
    var_r0 = 0;
block_63:
    M2C_FIELD(fp, s32*, 0x2344) = var_r0;
    M2C_FIELD(fp, s8*, 0x2359) = 0;
    M2C_FIELD(fp, void (**)(Fighter_GObj*), 0x21D0) =
        ftCo_Damage_OnEveryHitlag;
    fp->x670_timer_lstick_tilt_x = 0xFE;
    fp->x671_timer_lstick_tilt_y = 0xFE;
    M2C_FIELD(fp, void (**)(Fighter_GObj*), 0x21D8) = ftCo_Damage_OnExitHitlag;
    M2C_FIELD(fp, float*, 0x18A8) = (float) M2C_FIELD(fp, float*, 0x1850);
    fp->x221C_b6 = true;
    M2C_FIELD(fp, s32*, 0x18AC) = (s32) 0;
    if (msid == 0x5B) {
        inlineA1(gobj);
    }
    fp->x67F = 0xFF;
    ftCo_Damage_SetMv8FromKbThreshold(fp);
    if (M2C_FIELD(fp, s32*, 0x2348) == 0) {
        goto block_67;
    }
    fp->mv.co.damage.x8 = 1;
block_67:
    if (var_r28 != 3) {
        goto block_70;
    }
    if (!(var_f31 >= M2C_FIELD(p_ftCommonData, float*, 0x5E8))) {
        goto block_70;
    }
    ftCommon_8007EFC0(fp, M2C_FIELD(p_ftCommonData, u32*, 0x5EC));
block_70:
    if (var_r27 == 0) {
        goto block_75;
    }
    if (!(temp_f30 >= M2C_FIELD(p_ftCommonData, float*, 0x20C))) {
        goto block_73;
    }
    M2C_FIELD(fp, s32*, 0x1908) = 0x4F;
    M2C_FIELD(fp, s32*, 0x190C) = (s32) M2C_FIELD(
        M2C_FIELD(M2C_FIELD(fp, void**, 0x10C), void**, 0x4C), s32*, 0x20);
    goto block_75;
block_73:
    if (!(temp_f30 >= M2C_FIELD(p_ftCommonData, float*, 0x208))) {
        goto block_75;
    }
    M2C_FIELD(fp, s32*, 0x1908) = 0x50;
    M2C_FIELD(fp, s32*, 0x190C) = (s32) M2C_FIELD(
        M2C_FIELD(M2C_FIELD(fp, void**, 0x10C), void**, 0x4C), s32*, 0x1C);
block_75:
    if (var_r28 != 3) {
        goto block_83;
    }
    if (fp->ground_or_air != GA_Air) {
        goto block_83;
    }
    if (!(temp_f30 >= M2C_FIELD(p_ftCommonData, float*, 0x174))) {
        goto block_79;
    }
    {
        enum_t cam_enum = 4;
        goto block_82;
    block_79:
        if (!(temp_f30 >= p_ftCommonData->x170)) {
            goto block_81;
        }
        cam_enum = 3;
        goto block_82;
    block_81:
        cam_enum = 2;
    block_82:
        Camera_80030E44(cam_enum, &fp->cur_pos);
    }
block_83:
    ftCommon_8007F824(gobj);
    if (fp->motion_id == 0x145) {
        return;
    }
    if (var_r30 < 2) {
        return;
    }
    if ((u32) fp->dmg.x1860_element == 5U) {
        ftCo_DamageIce_Init(gobj);
    }
}

bool ftCo_Damage_CheckAirMotion(Fighter* fp)
{
    switch (fp->motion_id) {
    case ftCo_MS_JumpF:
    case ftCo_MS_JumpB:
    case ftCo_MS_JumpAerialF:
    case ftCo_MS_JumpAerialB:
    case ftCo_MS_Fall:
    case ftCo_MS_FallF:
    case ftCo_MS_FallB:
    case ftCo_MS_FallAerial:
    case ftCo_MS_FallAerialF:
    case ftCo_MS_FallAerialB:
    case ftCo_MS_FallSpecial:
    case ftCo_MS_FallSpecialF:
    case ftCo_MS_FallSpecialB:
    case ftCo_MS_DamageFall:
    case ftCo_MS_EscapeAir:
        if (fp->x680 <= p_ftCommonData->x18C &&
            fp->x684 >= p_ftCommonData->x1C)
        {
            return true;
        }
    default:
        return false;
    }
}

#define SOLUTION 1
void ftCo_Damage_OnEveryHitlag(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->x221A_b2) {
        float lstick_x = fp->input.lstick.x;
        float lstick_y = fp->input.lstick.y;
        float cd_x4B0 = p_ftCommonData->x4B0;
        if (lstick_x * lstick_x + lstick_y * lstick_y == cd_x4B0 * cd_x4B0) {
            s32 cd_x4B4 = p_ftCommonData->x4B4;
#if SOLUTION == 0
            if (((M2C_FIELD(fp, u8*, 0x670) < cd_x4B4) ||
                 M2C_FIELD(fp, u8*, 0x671) < cd_x4B4))
#else
            if (((fp->x670_timer_lstick_tilt_x < cd_x4B4) ||
                 fp->x671_timer_lstick_tilt_y < cd_x4B4))
#endif
            {
                float cd_x4B8 = p_ftCommonData->x4B8;
                float scaled_lstick_x = lstick_x * cd_x4B8;
                float scaled_lstick_y = lstick_y * cd_x4B8;
                fp->cur_pos.x += scaled_lstick_x;
                fp->cur_pos.y += scaled_lstick_y;
#if SOLUTION == 0
                M2C_FIELD(fp, u8*, 0x670) = 0xFE;
                M2C_FIELD(fp, u8*, 0x671) = 0xFE;
#else
                fp->x670_timer_lstick_tilt_x = 0xFE;
                fp->x671_timer_lstick_tilt_y = 0xFE;
#endif
#if SOLUTION == 0
                pl_800401F0(fp->player_id,
                            (M2C_FIELD(fp, u8*, 0x221F) >> 3) & 1,
                            scaled_lstick_x, scaled_lstick_y);
#else
                pl_800401F0(fp->player_id, fp->x221F_b4, scaled_lstick_x,
                            scaled_lstick_y);
#endif
            }
        }
    }
}
#undef SOLUTION

void ftCo_8008E5A4(Fighter* fp)
{
    if (fp->input.lstick.x || fp->input.lstick.y) {
        float lstick_x = fp->input.lstick.x;
        float kb_x = fp->x8c_kb_vel.x;
        float kb_y = fp->x8c_kb_vel.y;
        float kb_vel_x_neg = -kb_x;
        float kb_mag = kb_vel_x_neg * kb_vel_x_neg + kb_y * kb_y;
        if (!(kb_mag < 0.00001f)) {
            Vec3 lstick_vec3;
            lstick_vec3.x = lstick_x;
            {
                float lstick_y = fp->input.lstick.y;
                float f3 = kb_y * lstick_x + kb_vel_x_neg * lstick_y;
                lstick_vec3.y = lstick_y;
                lstick_vec3.z = 0;
                {
                    float f30 = f3 * f3 / kb_mag;
                    Vec3 kb_vel_cross_lstick;
                    PSVECCrossProduct(&fp->x8c_kb_vel, &lstick_vec3,
                                      &kb_vel_cross_lstick);
                    if (kb_vel_cross_lstick.z < 0) {
                        f30 = -f30;
                    }
                    {
                        float angle = atan2f(kb_y, kb_x);
                        float kb_mag = sqrtf(kb_x * kb_x + kb_y * kb_y);
                        angle += deg_to_rad * p_ftCommonData->x1A8 * f30;
                        fp->x8c_kb_vel.x = kb_mag * cosf(angle);
                        fp->x8c_kb_vel.y = kb_mag * sinf(angle);
                    }
                }
            }
        }
    }
}

static bool isPointInCircle(float x, float y, float radius)
{
    if (x + y >= radius) {
        return true;
    } else {
        return false;
    }
}

void ftCo_Damage_OnExitHitlag(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (isPointInCircle(SQ(fp->input.lstick.x), SQ(fp->input.lstick.y),
                        SQ(p_ftCommonData->x4B0)) ||
        ftCo_800DF608(fp))
    {
        float x, y;
        if (ftCo_800DF608(fp)) {
            float cd_x4BC = p_ftCommonData->x4BC;
            x = fp->input.cstick.x * cd_x4BC;
            y = fp->input.cstick.y * cd_x4BC;
        } else {
            float cd_x4BC = p_ftCommonData->x4BC;
            x = fp->input.lstick.x * cd_x4BC;
            y = fp->input.lstick.y * cd_x4BC;
        }
        fp->cur_pos.x += x;
        fp->cur_pos.y += y;
        pl_800401F0(fp->player_id, fp->x221F_b4, x, y);
    }
    if (fp->mv.co.damage.x4) {
        fp->mv.co.damage.x4 = false;
        ftColl_8007B7A4(gobj, p_ftCommonData->x130);
    }
    ftCo_8008E5A4(fp);
    if (fp->input.held_inputs & HSD_PAD_LR) {
        float kb_x = fp->x8c_kb_vel.x;
        float kb_y = fp->x8c_kb_vel.y;
        if (kb_x || kb_y) {
            float kb_angle = atan2f(kb_y, kb_x);
            float scaled_kb_mag =
                sqrtf(kb_x * kb_x + kb_y * kb_y) * p_ftCommonData->x1AC;
            fp->x8c_kb_vel.x = scaled_kb_mag * cosf(kb_angle);
            fp->x8c_kb_vel.y = scaled_kb_mag * sinf(kb_angle);
        }
    }
}

void ftCo_8008E908(Fighter_GObj* gobj, float facing_dir)
{
    Fighter* fp = gobj->user_data;
    if (fp->x221D_b7) {
        fp->x2064_ledgeCooldown = p_ftCommonData->ledge_cooldown;
    }
    {
        u32 fp_x1860 = fp->dmg.x1860_element;
        if ((fp_x1860 == 6 || fp_x1860 == 7) && !fp->x2228_b2) {
            ftCo_800C318C(gobj, fp_x1860 == 6 ? 0 : 1);
        } else {
            ftCo_8008DCE0(gobj, -1, facing_dir);
        }
    }
}

bool ftCo_8008E984(Fighter* fp)
{
    if (fp->dmg.kb_applied == 0 ||
        (fp->x221A_b2 && fp->x221A_b3 &&
         fp->dmg.kb_applied < fp->dmg.x18A8 + p_ftCommonData->x140))
    {
        return true;
    } else {
        return false;
    }
}

static inline void inlineF0(Fighter_GObj* gobj)
{
    ftCo_800C8D00(gobj);
    {
        Fighter* fp = gobj->user_data;
        if (fp->motion_id == 0xe0 || fp->motion_id == 0xe1) {
            ftCo_800DC284(gobj);
        }
        if (fp->motion_id == 0xe3 || fp->motion_id == 0xe4) {
            ftCo_800DC3A4(gobj);
        }
    }
}

void ftCo_8008E9D0(Fighter_GObj* gobj)
{
    u8 _[8] = { 0 };

    Fighter* fp = gobj->user_data;
    inlineF0(gobj);
    if (ftCo_8008DA4C(gobj, ftCo_8008D8E8(fp->dmg.kb_applied), 0)) {
        ftCo_800C0408(gobj);
    }
    ftCommon_800804FC(fp);
}

static bool inlineB0(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    float kb_applied = fp->dmg.kb_applied;
    // might not be correct?
    if (kb_applied != 0) {
        return true;
    }
    if (fp->x221A_b2 && fp->x221A_b3 &&
        fp->dmg.kb_applied < fp->dmg.x18A8 + p_ftCommonData->x140)
    {
        return true;
    }
    return false;
}

/// @todo Inline depth.
#pragma push
#pragma inline_depth(1)
void ftCo_8008EB58(Fighter_GObj* gobj)
{
    if (inlineB0(gobj)) {
        ftCo_800C8D00(gobj);
        inlineF0(gobj);
        {
            Fighter* fp = gobj->user_data;
            if (ftCo_8008DA4C(gobj, fp->dmg.x1860_element,
                              ftCo_8008D8E8(fp->dmg.kb_applied)))
            {
                ftCo_800C0408(gobj);
            }
            ftCommon_800804FC(fp);
        }
    }
}
#pragma pop

static bool inlineB1(Fighter* fp)
{
    if (fp->x221C_b0) {
        return true;
    }
    if (fp->dmg.x1838_percentTemp < p_ftCommonData->x3C0) {
        return true;
    }
    return false;
}

static inline void inlineB2(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
#pragma push
#pragma always_inline on
    inlineF0(gobj);
#pragma pop
    if (ftCo_8008DA4C(
            gobj, fp->dmg.x1860_element,
            ftCo_8008D8E8(fp->dmg.kb_applied * p_ftCommonData->x154)))
    {
        ftCo_800C0408(gobj);
    }
    ftCommon_800804FC(fp);
}

void ftCo_8008EC90(Fighter_GObj* gobj)
{
    bool ret0 = false;
    Fighter* fp = gobj->user_data;
    float facing_dir = 0;
    if (fp->x2220_b3 || fp->x2220_b4 || !fp->dmg.kb_applied) {
        inlineB2(gobj);
        goto ret_A8C;
    } else if (fp->dmg.x1860_element == 10U) {
        if (ftCo_800C3538(gobj)) {
            goto ret_A8C;
        }
        facing_dir = fp->facing_dir;
        ret0 = true;
    }
    if (!ftCo_800C44CC(gobj) && !ftCo_800D2FA4(gobj) &&
        fp->victim_gobj != NULL)
    {
        Fighter_GObj* other_gobj = fp->victim_gobj;
        Fighter* other_fp = other_gobj->user_data;
        if (!fp->x221B_b5) {
            if (!ret0 && inlineB1(fp)) {
                if (other_fp->dmg.kb_applied) {
                    if (ftCo_8008E984(other_fp)) {
                        inlineB2(gobj);
                        fp->dmg.x183C_applied = other_fp->dmg.x183C_applied;
                        fp->x1960_vibrateMult = other_fp->x1960_vibrateMult;
                        other_fp->x1828 = 3;
                        goto ret_A8C;
                    }
                    ftCo_800DE854(gobj);
                    ftCo_800DCE34(other_gobj, gobj);
                    ftCommon_8007DB58(gobj);
                    ftCo_8008E908(gobj, facing_dir);
                    other_fp->x1828 = 1;
                    goto ret_A8C;
                }
                if (fp->dmg.x183C_applied != 0) {
                    other_fp->dmg.x195c_hitlag_frames = ftCommon_CalcHitlag(
                        fp->dmg.x183C_applied, other_fp->motion_id,
                        other_fp->x1960_vibrateMult);
                    other_fp->x221A_b2 = true;
                    if (!other_fp->x2219_b5) {
                        if (other_fp->pre_hitlag_cb != NULL) {
                            other_fp->pre_hitlag_cb(gobj);
                        }
                        other_fp->x2219_b5 = true;
                    }
                }
                other_fp->input.x668 = other_fp->input.x66C = 0;
                inlineB2(gobj);
                goto ret_A8C;
            }
            {
                if (other_fp->dmg.kb_applied) {
                    ftCo_800DCE34(other_gobj, gobj);
                    ftCommon_8007DB58(gobj);
                    ftCo_8008E908(gobj, facing_dir);
                    other_fp->x1828 = 1;
                    goto ret_A8C;
                }
                ftCo_800DCE34(other_gobj, gobj);
                ftCommon_8007DB58(gobj);
                ftCo_8008E908(gobj, facing_dir);
                ftCommon_8007DB58(other_gobj);
                ftCo_800DE2F0(other_gobj);
                goto ret_A8C;
            }
        }
        if (inlineB0(gobj)) {
            if (other_fp->dmg.kb_applied) {
                if (inlineB1(other_fp)) {
                    other_fp->dmg.x183C_applied = fp->dmg.x183C_applied;
                    other_fp->x1960_vibrateMult = fp->x1960_vibrateMult;
                    if (inlineB0(gobj)) {
                        ftCo_8008E9D0(gobj);
                    }
                    fp->x1828 = 2;
                    goto ret_A8C;
                }
                ftCo_800DCE34(gobj, other_gobj);
                ftCommon_8007DB58(gobj);
                ftCo_8008E908(gobj, facing_dir);
                fp->x1828 = 1;
                goto ret_A8C;
            }
            if (inlineB0(gobj)) {
                ftCo_8008E9D0(gobj);
            }
            goto ret_A8C;
        }
        if (other_fp->dmg.kb_applied) {
            if (inlineB1(other_fp)) {
                ftCo_800DE854(other_gobj);
            }
            ftCo_800DCE34(gobj, fp->victim_gobj);
            ftCommon_8007DB58(gobj);
            ftCo_8008E908(gobj, facing_dir);
            other_fp->x1828 = 1;
            goto ret_A8C;
        }
        ftCommon_8007DB58(other_gobj);
        ftCo_800DCFD4(fp->victim_gobj);
        ftCo_800DCE34(gobj, fp->victim_gobj);
        ftCommon_8007DB58(gobj);
        ftCo_8008E908(gobj, facing_dir);
    } else if (fp->item_gobj != NULL && it_8026B2D8(fp->item_gobj) &&
               fp->x2222_b0)
    {
        ftDk_MS_349_800E06D8(gobj);
    } else if (!ftCo_8009F0F0(gobj) && !ftCo_800C0CB8(gobj) &&
               fp->motion_id == ftCo_MS_DamageIce)
    {
        ftCo_8008DCE0(gobj, ftCo_MS_DamageIce, fp->facing_dir);
        ftCo_DamageIce_HitWhileFrozen(gobj);
    } else if (!ftCo_800C74F4(gobj)) {
        ftCommon_8007DB58(gobj);
        ftCo_8008E908(gobj, facing_dir);
    }
ret_A8C:
    if (ret0) {
        ftCo_800C3598(gobj);
    }
}

void ftCo_8008F744(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->mv.co.damage.x0 > 0) {
        fp->mv.co.damage.x0 -= 1;
    }
    if (fp->x221C_b6) {
        if (fp->mv.co.damage.x0 <= 0) {
            fp->x221C_b6 = false;
            fp->x2098 = p_ftCommonData->x4CC;
            ftCommon_8007F86C(gobj);
            if (ftCo_800C5240(gobj)) {
                ftCo_800C554C((Fighter*) fp);
            }
        }
    }
}

static bool inlineC0(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->mv.co.damage.x14 && fp->mv.co.damage.x14 <= p_ftCommonData->x1D0) {
        fp->input.x668 |= HSD_PAD_XY;
        return ftCo_800CB870(gobj);
    } else {
        return false;
    }
}

void ftCo_Damage_Anim(Fighter_GObj* gobj)
{
    u8 _[8] = { 0 };
    Fighter* fp = gobj->user_data;
    ftCo_8008F744(gobj);
    if (!ftAnim_IsFramesRemaining(gobj) && !fp->x221C_b6) {
        if (fp->ground_or_air == GA_Air) {
            if (fp->x2224_b2) {
                ftCo_80090780(gobj);
            } else if (!inlineC0(gobj)) {
                ftCo_Fall_Enter(gobj);
            }
        } else {
            ft_8008A2BC(gobj);
        }
    }
}

/// @todo Some kind of missing @c bool inline
bool doIasa(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (!(fp->mv.co.damage.x1A)) {
        goto ret_inline;
    }
    if (fp->mv.co.damage.x1B) {
        --fp->mv.co.damage.x1B;
    }
    if (!(!fp->mv.co.damage.x1B)) {
        goto ret_inline;
    }
    if (!(fp->ground_or_air == GA_Air)) {
        goto ret_inline;
    }
    if (!(fp->x8c_kb_vel.y < 0)) {
        goto ret_inline;
    }
    if (!(ftCo_800D69C4(gobj) || ftCo_800CB8E0(gobj))) {
        goto ret_inline;
    }
    fp->x8c_kb_vel.x = fp->x8c_kb_vel.y = fp->x8c_kb_vel.z = 0;
    ftCommon_8007EBAC(fp, 12, 0);
    ftCo_800BFFD0(fp, 121, 0);
    fp->x2227_b4 = true;
    return true;
ret_inline:
    if (ftCo_Jump_GetInput(gobj)) {
        fp->mv.co.damage.x14 = fp->mv.co.damage.x0;
        return true;
    }
    return false;
}

void ftCo_Damage_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (!fp->x221C_b6) {
        if (ftCo_800C5240(gobj)) {
            if (fp->ground_or_air == GA_Air) {
                ftCo_HammerFall_IASA(gobj);
            } else {
                ftCo_HammerWait_IASA(gobj);
            }
        } else {
            if (fp->mv.co.damage.x14 &&
                fp->mv.co.damage.x14 <= p_ftCommonData->x1D0)
            {
                fp->input.x668 |= HSD_PAD_XY;
            }
            if (fp->ground_or_air == GA_Air) {
                ftCo_Fall_IASA_Inner(gobj);
            } else {
                ftCo_Wait_IASA(gobj);
            }
        }
    } else {
        RETURN_IF(doIasa(gobj));
    }
}

void ftCo_Damage_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->ground_or_air == GA_Air) {
        if (!fp->x221C_b6) {
            ft_80084DB0(gobj);
        } else {
            ft_80084EEC(gobj);
        }
    } else {
        ft_80084F3C(gobj);
    }
}

void ftCo_Damage_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->ground_or_air == GA_Ground) {
        ft_800848DC(gobj, ftCo_8008FC94);
    } else if (ft_80081DD4(gobj)) {
        if (fp->x2224_b2) {
            ftCo_80097D40(gobj);
        } else {
            float mag = sqrtf(VEC2_SQ_LEN(fp->x8c_kb_vel));
            if (mag >= p_ftCommonData->x1E0) {
                ftCo_80097D40(gobj);
            } else if (mag >= p_ftCommonData->x1E4) {
                ftCo_Landing_Enter_Basic(gobj);
            } else {
                ftCommon_8007D7FC(fp);
            }
        }
    }
}

void ftCo_8008FC94(Fighter_GObj* gobj)
{
    ftCommon_8007D5D4(gobj->user_data);
}

void ftCo_Damage_SetMv8FromKbThreshold(Fighter* fp)
{
    float kb_vel = fp->ground_or_air == GA_Air
                       ? sqrtf__Ff(VEC3_SQ_LEN(fp->x8c_kb_vel))
                       : ABS(fp->xF0_ground_kb_vel);
    fp->mv.co.damage.x8 =
        kb_vel < p_ftCommonData->x568   ? 0
        : kb_vel < p_ftCommonData->x56C ? p_ftCommonData->x57C
        : kb_vel < p_ftCommonData->x570 ? p_ftCommonData->x57C
        : kb_vel < p_ftCommonData->x574 ? p_ftCommonData->x580
        : kb_vel < p_ftCommonData->x578 ? p_ftCommonData->x584
                                        : p_ftCommonData->x588;
}

static inline void inlineD0(Fighter_GObj* gobj)
{
    float param;
    Fighter* fp = gobj->user_data;
    --fp->mv.co.damage.x8;
    if (fp->mv.co.damage.x8 == 0) {
        float x, y;
        if (fp->ground_or_air == GA_Air) {
            y = fp->x8c_kb_vel.x;
            x = fp->x8c_kb_vel.y;
        } else {
            float kb_vel = fp->xF0_ground_kb_vel;
            y = fp->coll_data.floor.normal.y * kb_vel;
            x = -fp->coll_data.floor.normal.x * kb_vel;
        }
        {
            float trajectory = atan2f(-y, x);
            param = trajectory;
            efAsync_Spawn(gobj, &GET_FIGHTER(gobj)->x60C, 4, 1032,
                          fp->parts[FtPart_TopN].joint, &param);
        }
        ftCo_Damage_SetMv8FromKbThreshold(fp);
    }
}

void ftCo_DamageFly_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    inlineD0(gobj);
    ftCo_8008F744(gobj);
    if (!ftAnim_IsFramesRemaining(gobj) && !fp->x221C_b6) {
        if (!inlineC0(gobj)) {
            ftCo_80090780(gobj);
        }
    }
}

void ftCo_DamageFly_IASA(Fighter_GObj* gobj)
{
    if (!GET_FIGHTER(gobj)->x221C_b6) {
        ftCo_DamageFall_IASA(gobj);
    } else {
        RETURN_IF(doIasa(gobj));
    }
}

static void doFlyRoll(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    float trajectory =
        fp->facing_dir * atan2f(fp->self_vel.x + fp->x8c_kb_vel.x,
                                fp->self_vel.y + fp->x8c_kb_vel.y);
    ftParts_8007592C(fp, ftParts_GetBoneIndex(fp, FtPart_XRotN), trajectory);
}

void ftCo_DamageFly_Phys(Fighter_GObj* gobj)
{
    u8 _[16] = { 0 };
    Fighter* fp = gobj->user_data;
    if (fp->ground_or_air == GA_Air) {
        if (!fp->x221C_b6) {
            ft_80084DB0(gobj);
        } else {
            ft_80084EEC(gobj);
        }
    } else {
        ft_80084F3C(gobj);
    }
    if (fp->motion_id == ftCo_MS_DamageFlyRoll) {
        doFlyRoll(gobj);
    }
    if (fp->x1064_thrownHitbox.owner != NULL &&
        sqrtf(VEC3_SQ_LEN(fp->x8c_kb_vel)) < p_ftCommonData->x1C8)
    {
        ftColl_8007AFF8(gobj);
    }
}

void ftCo_DamageFly_Coll(Fighter_GObj* gobj)
{
    u8 _[8] = { 0 };
    CollData* coll = &GET_FIGHTER(gobj)->coll_data;
    if (ft_80081DD4(gobj) != 0) {
        ftCo_80090184(gobj);
        return;
    } else {
        u32 env_flags = coll->env_flags;
        if (env_flags & Collide_RightWallHug ||
            env_flags & Collide_LeftWallHug || env_flags & Collide_CeilingHug)
        {
            RETURN_IF(ftCo_800C1D38(gobj));
            RETURN_IF(ftCo_800C23A0(gobj));
            RETURN_IF(ftCo_800C17CC(gobj));
        }
    }
}

void ftCo_80090184(Fighter_GObj* gobj)
{
    RETURN_IF(ftCo_80098928(gobj));
    RETURN_IF(ftCo_8009872C(gobj));
    ftCo_80097D40(gobj);
}

void ftCo_DamageFlyRoll_Anim(Fighter_GObj* gobj)
{
    u8 _0[8] = { 0 };
    u8 _1[0x18] = { 0 };
    Fighter* fp = gobj->user_data;
    if (fp->mv.co.damage.x8 != 0) {
        inlineD0(gobj);
    }
    ftCo_8008F744(gobj);
    if (!fp->x221C_b6) {
        ftCo_80090780(gobj);
    }
}

void ftCo_DamageFlyRoll_IASA(Fighter_GObj* gobj)
{
    if (!GET_FIGHTER(gobj)->x221C_b6) {
        ftCo_DamageFall_IASA(gobj);
    } else {
        doIasa(gobj);
    }
}

void ftCo_DamageFlyRoll_Phys(Fighter_GObj* gobj)
{
    u8 _[16] = { 0 };
    Fighter* fp = gobj->user_data;
    if (fp->ground_or_air == GA_Air) {
        if (!fp->x221C_b6) {
            ft_80084DB0(gobj);
        } else {
            ft_80084EEC(gobj);
        }
    } else {
        ft_80084F3C(gobj);
    }
    if (fp->motion_id == ftCo_MS_DamageFlyRoll) {
        doFlyRoll(gobj);
    }
    if (fp->x1064_thrownHitbox.owner != NULL) {
        if (sqrtf__Ff(VEC3_SQ_LEN(fp->x8c_kb_vel)) < p_ftCommonData->x1C8) {
            ftColl_8007AFF8(gobj);
        }
    }
    if (fp->motion_id == ftCo_MS_DamageFlyRoll) {
        doFlyRoll(gobj);
    }
}

void ftCo_DamageFlyRoll_Coll(Fighter_GObj* gobj)
{
    u8 _[16] = { 0 };
    CollData* coll = &GET_FIGHTER(gobj)->coll_data;
    if (ft_80081DD4(gobj)) {
        RETURN_IF(ftCo_80098928(gobj));
        RETURN_IF(ftCo_8009872C(gobj));
        ftCo_80097D40(gobj);
    } else {
        u32 env_flags = coll->env_flags;
        if (env_flags & Collide_RightWallHug ||
            env_flags & Collide_LeftWallHug || env_flags & Collide_CeilingHug)
        {
            RETURN_IF(ftCo_800C1D38(gobj));
            RETURN_IF(ftCo_800C23A0(gobj));
            ftCo_800C17CC(gobj);
        }
    }
}
