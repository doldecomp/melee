#include <platform.h>
#include <placeholder.h>

#include "ft/forward.h"
#include <dolphin/mtx/forward.h>
#include <baselib/forward.h>

#include "ftCo_Guard.h"

#include "ftCo_0C35.h"
#include "ftCo_Attack1.h"
#include "ftCo_AttackHi3.h"
#include "ftCo_AttackHi4.h"
#include "ftCo_AttackLw3.h"
#include "ftCo_AttackLw4.h"
#include "ftCo_AttackS3.h"
#include "ftCo_AttackS4.h"
#include "ftCo_Escape.h"
#include "ftCo_ItemThrow.h"
#include "ftCo_Pass.h"
#include "ftCo_ShieldBreakFly.h"
#include "ftCo_SpecialS.h"

#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0892.h"
#include "ft/ft_0C88.h"
#include "ft/ft_0D14.h"
#include "ft/ftanim.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftdata.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "ftCommon/types.h"
#include "ftYoshi/ftYs_Guard.h"
#include "ftYoshi/ftYs_Init.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00CE.h"
#include "pl/pl_0371.h"
#include "pl/player.h"

#include <common_structs.h>
#include <math.h>
#include <math_ppc.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>

float const ftCo_804D8538 = 0;
float const ftCo_804D853C = 2 * M_PI;
float const ftCo_804D8540 = rad_to_deg;
float const ftCo_804D8544 = 359;
float const ftCo_804D8548 = 10;
float const ftCo_804D854C = 180;
float const ftCo_804D8550 = 360;
float const ftCo_804D8554 = -180;
double const ftCo_804D8558 = 0.5;
double const ftCo_804D8560 = 3;

float const ftCo_804D8568 = 1;
float const ftCo_804D856C = 255;
double const ftCo_804D8570 = 4503601774854144;
float const ftCo_804D8578 = 0.1;

/* 091BC4 */ static void ftCo_80091BC4(ftCo_Fighter* fp);
/* 091E78 */ static void ftCo_80091E78(ftCo_GObj* gobj, float);
/* 092158 */ static void ftCo_80092158(ftCo_GObj* gobj, int arg1,
                                       HSD_JObj* arg2);
/* 0921DC */ static void ftCo_800921DC(ftCo_GObj* gobj);
/* 0923B4 */ static void ftCo_800923B4(ftCo_GObj* gobj);
/* 0924C0 */ static void ftCo_800924C0(HSD_GObj* gobj);
/* 092908 */ static void ftCo_80092908(ftCo_GObj* gobj);
/* 092C54 */ static void ftCo_80092C54(ftCo_GObj* gobj);
/* 092E50 */ static void ftCo_80092E50(ftCo_GObj* gobj);
/* 092F2C */ static void ftCo_80092F2C(ftCo_GObj* gobj, bool);
/* 093790 */ static void ftCo_80093790(ftCo_GObj* gobj);
/* 093850 */ static void ftCo_80093850(ftCo_GObj* gobj);
/* 09388C */ static void ftCo_8009388C(ftCo_GObj* gobj);
/* 0939B4 */ static void ftCo_800939B4(ftCo_GObj* gobj);
/* 093A50 */ static void ftCo_80093A50(ftCo_GObj* gobj);

bool ftCo_80091A2C(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    return fp->input.held_inputs & HSD_PAD_LR ? true : false;
}

static inline bool inlineA0(ftCo_Fighter* fp)
{
    return fp->input.held_inputs & HSD_PAD_LR ? true : false;
}

int ftCo_80091A4C(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->input.x668 & (HSD_PAD_R | HSD_PAD_L) &&
        fp->x672_input_timer_counter < p_ftCommonData->x2A0)
    {
        ftCo_800939B4(gobj);
        return true;
    }
    if (inlineA0(fp) && fp->shield_health) {
        ftCo_800923B4(gobj);
        return true;
    }
    return false;
}

/// @todo @c inline of #ftCo_80091A4C and something else.
bool ftCo_80091AD8(ftCo_GObj* gobj, int mv_x20)
{
    u8 _[16] = { 0 };
    bool ret0;
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->input.x668 & (HSD_PAD_R | HSD_PAD_L) &&
        fp->x672_input_timer_counter < p_ftCommonData->x2A0)
    {
        ftCo_800939B4(gobj);
        ret0 = true;
    } else {
        bool ret1;
        if (fp->input.held_inputs & HSD_PAD_LR) {
            ret1 = true;
        } else {
            ret1 = false;
        }
        if (ret1 && fp->shield_health) {
            ftCo_800923B4(gobj);
            ret0 = true;
        } else {
            ret0 = false;
        }
    }
    if (ret0 != false) {
        fp->mv.co.guard.x20 = mv_x20;
        return true;
    }
    return false;
}

void ftCo_80091B90(ftCo_GObj* gobj, int mv_x20)
{
    ftCo_Fighter* fp = gobj->user_data;
    fp->mv.co.guard.x20 = mv_x20;
}

void ftCo_80091B9C(ftCo_GObj* gobj)
{
    u8 _[8] = { 0 };
    ftCo_Fighter* fp = gobj->user_data;
    fp->mv.co.guard.x24 = p_ftCommonData->x68;
}

static inline float normalizeAngle180(float deg)
{
    if (deg > 180) {
        deg -= 360;
    } else if (deg < -180) {
        deg += 360;
    }
    return deg;
}

static inline float normalizeAngle0(float deg)
{
    if (deg > 360) {
        deg -= 360;
    } else if (deg < 0) {
        deg += 360;
    }
    return deg;
}

void ftCo_80091BC4(Fighter* fp)
{
    float lstick_x = fp->input.lstick.x * fp->facing_dir;
    float lstick_rad = lb_8000D008(fp->input.lstick.y, lstick_x);
    if (lstick_rad < 0) {
        lstick_rad += 2 * (float) M_PI;
    }
    {
        float lstick_deg = rad_to_deg * lstick_rad;
        if (lstick_deg < 0) {
            lstick_deg = 0;
        }
        if (lstick_deg > 359) {
            lstick_deg = 359;
        }
        {
            Fighter* fp0;
            float offset = (fp0 = fp)->mv.co.guard.x8 - 10;
            float deg = lstick_deg - offset;
            lstick_x = normalizeAngle180(deg);
            fp->mv.co.guard.x8 =
                10 + normalizeAngle0(lstick_x * p_ftCommonData->x44C + offset);
            {
                float lstick_mag =
                    sqrtf(SQ(fp0->input.lstick.x) + SQ(fp0->input.lstick.y));
                if (lstick_mag > 1) {
                    lstick_mag = 1;
                }
                fp->mv.co.guard.x4 = (lstick_rad = p_ftCommonData->x44C) *
                                         (lstick_mag - fp->mv.co.guard.x4) +
                                     fp->mv.co.guard.x4;
            }
        }
    }
}

static inline float inlineB0(ftCo_Fighter* fp)
{
    if (fp->kind == FTKIND_YOSHI) {
        return fp->co_attrs.initial_shield_size;
    } else {
        float n1 =
            (fp->shield_health / p_ftCommonData->x260_startShieldHealth) *
            (fp->lightshield_amount *
                 (p_ftCommonData->x2D8 - p_ftCommonData->x2D4) +
             p_ftCommonData->x2D4);
        float n2 = 1 - p_ftCommonData->x264;
        float n3 = n2 * n1 + p_ftCommonData->x264;
        return n3 * fp->co_attrs.initial_shield_size;
    }
}

void ftCo_80091D58(Fighter* fp)
{
    Vec3 scl;
    scl.x = scl.y = scl.z = inlineB0(fp);
    HSD_JObjSetScale(fp->parts[fp->ft_data->x8->x11].joint, &scl);
}

static inline void inlineD0(ftCo_GObj* gobj)
{
    float temp_f2_2;
    float temp_f3;
    ftCo_Fighter* fp = gobj->user_data;
    if ((int) M2C_FIELD(fp, int*, 4) != 0xE) {
        temp_f3 = M2C_FIELD(p_ftCommonData, float*, 0x2F4);
        temp_f2_2 = M2C_FIELD(fp, float*, 0x199C);
        efLib_8005F864(
            gobj, (s8) (temp_f3 + (float) (int) (temp_f2_2 * (255 - temp_f3))),
            temp_f2_2, temp_f3);
    }
}

void ftCo_80091E78(HSD_GObj* gobj, float arg1)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->x2218_b3 || fp->x221B_b0) {
        ftCo_80091BC4(fp);
        if (fp->mv.co.guard.x4) {
            HSD_JObj* jobj = fp->x8AC_animSkeleton;
            ftAnim_8006F4C8(fp, 1, ftData_80085E50(fp, 38));
            ftAnim_80070710(jobj, fp->mv.co.guard.x8);
            ftAnim_8006FB88(fp, 1, fp->x108_costume_joint->child);
            HSD_JObjAnimAll(jobj);
            if (fp->mv.co.guard.x4 < 1) {
                ftAnim_80070108(fp, 1, fp->ft_data->x20->x8,
                                1 - fp->mv.co.guard.x4, fp->mv.co.guard.x4);
            }
            if (arg1 < 1) {
                ftAnim_8006FE9C(fp, 1, arg1, 1 - arg1);
            } else {
                ftAnim_8006FF74(fp, 1);
            }
        } else if (arg1 < 1) {
            ftAnim_80070010(fp, 1, fp->ft_data->x20->x8, arg1, 1 - arg1);
        } else {
            ftAnim_8006FA58(fp, 1, fp->ft_data->x20->x8);
        }
        ftCo_80091D58(fp);
        inlineD0(gobj);
    }
}

#pragma push
#pragma force_active on

void ftCo_80092158(ftCo_GObj* gobj, int arg1, HSD_JObj* arg2)
{
    u8 temp_ret = Player_GetUnk45(GET_FIGHTER(gobj)->player_id);
    int* temp_r7 = &Fighter_804D650C[temp_ret];
    u8 temp_r7_2 = M2C_FIELD(temp_r7, u8*, 2);
    efSync_Spawn(arg1, gobj, arg2,
                 temp_r7_2 |
                     (((M2C_FIELD(temp_r7, u8*, 1) << 8) & ~0xFF0000) |
                      ((M2C_FIELD(temp_r7, u8*, 0) << 0x10) & 0xFF0000)),
                 temp_r7_2, M2C_BITWISE(float, temp_ret));
}
void ftCo_800921DC(HSD_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    ftCo_80092158(gobj, 1047, fp->parts[fp->ft_data->x8->x11].joint);
    fp->x2219_b0 = true;
    fp->mv.co.guard.xC = false;
    fp->mv.co.guard.x0 = 0;
    fp->mv.co.guard.x10 = p_ftCommonData->x268;
    fp->mv.co.guard.x8 = 10;
    fp->mv.co.guard.x4 = 0;
    fp->mv.co.guard.x2C = 0;
    {
        float lightshield_amount = fp->input.x650 / (1 - p_ftCommonData->x10);
        if (lightshield_amount < 0) {
            lightshield_amount = fp->mv.co.guard.x2C;
        }
        fp->lightshield_amount = lightshield_amount;
    }
    fp->mv.co.guard.x20 = fp->mv.co.guard.x24 = 0;
    {
        Vec3 trans;
        trans.x = trans.y = trans.z = 0;
        HSD_JObjSetTranslate(fp->parts[fp->ft_data->x8->x11].joint, &trans);
    }
    ftCo_80091E78(gobj, 0);
    ft_80088148(fp, 110, 127, 64);
}

void ftCo_800923B4(ftCo_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    switch (fp->kind) {
    case FTKIND_YOSHI:
        ftYs_Init_8012BECC(gobj);
        return;
    case FTKIND_MARS:
        ftCo_800924C0(gobj);
        ftParts_80074B0C(gobj, 1, 1);
        ft_80088148(fp, 190115, 127, 64);
        return;
    default:
        ftCo_800924C0(gobj);
        return;
    }
}

void ftCo_80092450(ftCo_GObj* gobj)
{
    AbsorbDesc absorb;
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    absorb.x0_bone_id = fp->ft_data->x8->x11;
    absorb.x10_size = 1;
    absorb.x4_offset.x = absorb.x4_offset.y = absorb.x4_offset.z = 0.0f;
    ftColl_8007B1B8(gobj, (ShieldDesc*) &absorb, ftCo_80092E50);
    fp->x221A_b7 = true;
}

void ftCo_800924C0(ftCo_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftCo_MS_GuardOn, Ft_MF_SkipAnim, 0, 1, 0,
                              NULL);
    ftAnim_8006EBA4(gobj);
    fp->x221C_b3 = 0;
    fp->x221C_b1 = 0;
    fp->x221C_b2 = 0;
    fp->mv.co.guard.x1C = 0;
    fp->mv.co.guard.x14 = 0;
    fp->mv.co.guard.x18 = 0;
    ftCo_80092450(gobj);
    ftCo_800921DC(gobj);
}

bool ftCo_800925A4(HSD_GObj* gobj)
{
    u8 _[8] = { 0 };
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->x221B_b0) {
        fp->mv.co.guard.x2C = fp->lightshield_amount;
        {
            fp->lightshield_amount =
                (fp->input.x650 - p_ftCommonData->x10) /
                            (1 - p_ftCommonData->x10) <
                        0
                    ? fp->mv.co.guard.x2C
                    : (fp->input.x650 - p_ftCommonData->x10) /
                          (1 - p_ftCommonData->x10);
        }
        fp->shield_health -= p_ftCommonData->x278 *
                             ((fp->lightshield_amount *
                               (p_ftCommonData->x2F0 - p_ftCommonData->x2EC)) +
                              p_ftCommonData->x2EC);
        if (fp->shield_health < 0) {
            fp->shield_health = 0;
            fp->x221A_b7 = false;
            fp->x221B_b0 = false;
            pl_8003E0E8(fp->player_id, fp->x221F_b4);
            ftCo_80098B20(gobj);
            ft_80088148(fp, 129, 127, 64);
            return true;
        }
        if (fp->mv.co.guard.x10 > 0) {
            fp->mv.co.guard.x10 -= 1;
            if (fp->mv.co.guard.x10 < 0) {
                fp->mv.co.guard.x10 = 0;
            }
        }
    }
    return false;
}

void ftCo_GuardOn_Anim(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    fp->mv.co.guard.x0 += 1;
    if (ftCo_800925A4(gobj) == 0) {
        if (fp->mv.co.guard.x0 >= fp->x2E8) {
            ftCo_800928CC(gobj);
        } else {
            ftCo_80091E78(gobj, fp->mv.co.guard.x0 / fp->x2E8);
        }
    }
}

static inline bool inlineC0(ftCo_GObj* gobj, HSD_GObjEvent cb)
{
    ftCo_Fighter* fp = gobj->user_data;
    if ((fp->mv.co.guard.xC && !fp->mv.co.guard.x10) ||
        (!fp->x221B_b0 && !fp->x2218_b3))
    {
        cb(gobj);
        return true;
    }
    if (fp->mv.co.guard.x1C != 0) {
        --fp->mv.co.guard.x1C;
    }
    return false;
}

void ftCo_GuardOn_IASA(ftCo_GObj* gobj)
{
    RETURN_IF(inlineC0(gobj, ftCo_80092BE8));
    RETURN_IF(ftCo_80093694(gobj));
    RETURN_IF(ftCo_8009515C(gobj));
    RETURN_IF(ftCo_8009980C(gobj));
    RETURN_IF(ftCo_8009917C(gobj));
    RETURN_IF(ftCo_800D8B9C(gobj));
    RETURN_IF(ftCo_Catch_CheckInput(gobj));
    RETURN_IF(ftCo_800CB024(gobj));
    RETURN_IF(ftCo_8009A080(gobj));
}

void ftCo_GuardOn_Phys(ftCo_GObj* gobj)
{
    ft_80084F3C(gobj);
    ftColl_8007AEE0(gobj);
    ftColl_8007AEF8(gobj);
}

void ftCo_GuardOn_Coll(ftCo_GObj* gobj)
{
    ft_800845B4(gobj);
}

void ftCo_800928CC(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    switch (fp->kind) {
    case FTKIND_YOSHI:
        ftYs_Shield_8012C1D4(gobj);
        return;
    default:
        ftCo_80092908(gobj);
        return;
    }
}

void ftCo_80092908(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    Fighter_ChangeMotionState(gobj, ftCo_MS_Guard, Ft_MF_SkipAnim, 0, 1, 0,
                              NULL);
    {
        HSD_JObj* jobj = fp->parts[fp->ft_data->x8->x11].joint;
        ftCo_80092158(gobj, 1048, jobj);
        fp->x2219_b0 = true;
        ftCo_80092450(gobj);
        ftCo_80091E78(gobj, 1);
    }
}

void ftCo_Guard_Anim(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    fp->mv.co.guard.x0 += 1;
    if (!ftCo_800925A4(gobj)) {
        ftCo_80091E78(gobj, 1);
    }
}

void ftCo_Guard_IASA(ftCo_GObj* gobj)
{
    RETURN_IF(inlineC0(gobj, ftCo_80092BE8));
    RETURN_IF(ftCo_8009515C(gobj));
    RETURN_IF(ftCo_8009980C(gobj));
    RETURN_IF(ftCo_8009917C(gobj));
    RETURN_IF(ftCo_Catch_CheckInput(gobj));
    RETURN_IF(ftCo_800CB024(gobj));
    RETURN_IF(ftCo_8009A080(gobj));
}

void ftCo_Guard_Phys(ftCo_GObj* gobj)
{
    ft_80084F3C(gobj);
    ftColl_8007AEE0(gobj);
    ftColl_8007AEF8(gobj);
}

void ftCo_Guard_Coll(ftCo_GObj* gobj)
{
    ft_800845B4(gobj);
}

void ftCo_80092BCC(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (!(fp->input.held_inputs & HSD_PAD_LR)) {
        fp->mv.co.guard.xC = true;
    }
}

void ftCo_80092BE8(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    pl_8003E114(fp->player_id, fp->x221F_b4, fp->shield_health);
    switch (fp->kind) {
    case FTKIND_YOSHI:
        ftYs_Shield_8012C49C(gobj);
        return;
    default:
        ftCo_80092C54(gobj);
        return;
    }
}

void ftCo_80092C54(ftCo_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    Fighter_ChangeMotionState(gobj, ftCo_MS_GuardOff, Ft_MF_None, 0, 1, 0,
                              NULL);
    ft_80088148(fp, 127, 127, 64);
}

void ftCo_GuardOff_Anim(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    fp->mv.co.guard.x0 += 1;
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftCo_GuardOff_IASA(ftCo_GObj* gobj)
{
    u8 _[8] = { 0 };
    ftCo_Fighter* fp = gobj->user_data;
    /// @todo #RETURN_IF chain
    if (!fp->mv.co.guard.x1C ||
        (!ftCo_SpecialS_CheckInput(gobj) && !ftCo_Attack100_CheckInput(gobj) &&
         !ftCo_800D6824(gobj) && !ftCo_800D68C0(gobj) &&
         !ftCo_Catch_CheckInput(gobj) && !ftCo_AttackS4_CheckInput(gobj) &&
         !ftCo_AttackHi4_CheckInput(gobj) &&
         !ftCo_AttackLw4_CheckInput(gobj) && !ftCo_AttackS3_CheckInput(gobj) &&
         !ftCo_AttackHi3_CheckInput(gobj) &&
         !ftCo_AttackLw3_CheckInput(gobj) && !ftCo_Attack1_CheckInput(gobj)))
    {
        RETURN_IF(ftCo_8009980C(gobj));
        RETURN_IF(!ftCo_800CB024(gobj));
    }
}

void ftCo_GuardOff_Phys(ftCo_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftCo_GuardOff_Coll(ftCo_GObj* gobj)
{
    ft_800845B4(gobj);
}

void ftCo_80092E50(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    bool b;
    if (fp->x19B0 == 10U) {
        b = true;
    } else {
        b = false;
    }
    switch (fp->kind) {
    case FTKIND_YOSHI:
        ftYs_Shield_8012C600(gobj, b);
        break;
    default:
        ftCo_80092F2C(gobj, b);
        break;
    }
    if (b) {
        ftCo_800C36DC(gobj);
    }
}

float ftCo_80092ED8(int arg0, float arg1)
{
    return p_ftCommonData->x28C *
               (arg0 *
                (1 - (arg1 * (p_ftCommonData->x2E8 - p_ftCommonData->x2E4) +
                      p_ftCommonData->x2E4))) +
           p_ftCommonData->x290;
}

void ftCo_80092F2C(HSD_GObj* gobj, bool arg1)
{
    ftCo_Fighter* fp = gobj->user_data;
    Fighter_ChangeMotionState(gobj, ftCo_MS_GuardSetOff, Ft_MF_None, 0, 1, 0,
                              NULL);
    fp->hitlag_cb = ftCo_80093240;
    fp->x670_timer_lstick_tilt_x = -2;
    fp->post_hitlag_cb = ftCo_800932DC;
    if (!fp->x221C_b2) {
        ftCo_80092158(gobj, 1049, fp->parts[fp->ft_data->x8->x11].joint);
        fp->x2219_b0 = true;
    }
    {
        float f = (p_ftCommonData->x28C *
                   (fp->x19A4 *
                    (1.0f - ((fp->lightshield_amount *
                              (p_ftCommonData->x2E8 - p_ftCommonData->x2E4)) +
                             p_ftCommonData->x2E4)))) +
                  p_ftCommonData->x290;
        ftAnim_SetAnimRate(gobj,
                           (0.1f + lbGetJObjEndFrame(GET_JOBJ(gobj))) / f);
        if (!arg1) {
            float var_f2 = f * p_ftCommonData->x294;
            if (!fp->x221C_b2) {
                var_f2 *= p_ftCommonData->x2BC;
            }
            {
                /// @todo What happens to this value?
                float temp_f0 = p_ftCommonData->x298;
                if (var_f2 > temp_f0) {
                    var_f2 = temp_f0;
                }
            }
            fp->gr_vel = ABS(fp->specialn_facing_dir);
        }
    }
    ftCo_80092450(gobj);
    ftCo_80091D58(fp);
}

void ftCo_80093240(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->x221A_b2 && fp->ground_or_air == GA_Ground) {
        if ((fp->input.lstick.x < 0
                 ? -fp->input.lstick.x
                 : fp->input.lstick.x) >= p_ftCommonData->x4B0 &&
            fp->x670_timer_lstick_tilt_x < p_ftCommonData->x4B4)
        {
            float scl = p_ftCommonData->x4C0 *
                        (fp->input.lstick.x * p_ftCommonData->x4B8);
            fp->cur_pos.x += fp->coll_data.floor.normal.y * scl;
            fp->cur_pos.y += -fp->coll_data.floor.normal.x * scl;
            fp->x670_timer_lstick_tilt_x = 254;
        }
    }
}

void ftCo_800932DC(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->ground_or_air == GA_Ground) {
        if ((fp->input.lstick.x < 0
                 ? -fp->input.lstick.x
                 : fp->input.lstick.x) >= p_ftCommonData->x4B0)
        {
            float scl = p_ftCommonData->x4C0 *
                        (fp->input.lstick.x * p_ftCommonData->x4BC);
            fp->cur_pos.x += fp->coll_data.floor.normal.y * scl;
            fp->cur_pos.y += -fp->coll_data.floor.normal.x * scl;

            /// @todo Fake.
            !gobj;
        }
    }
}

void ftCo_GuardSetOff_Anim(HSD_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    ftCo_80093BC0(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (fp->mv.co.guard.xC) {
            ftCo_80092BE8(gobj);
        } else {
            ftCo_800928CC(gobj);
        }
    } else {
        ftCo_80091D58(fp);
    }
}

void ftCo_GuardSetOff_IASA(ftCo_GObj* gobj) {}

void ftCo_GuardSetOff_Phys(ftCo_GObj* gobj)
{
    ft_80084F3C(gobj);
    ftColl_8007AEE0(gobj);
}

void ftCo_GuardSetOff_Coll(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (!(fp->x221A_b2)) {
        ft_800845B4(gobj);
    } else {
        ft_80084104(gobj);
    }
}

bool ftCo_80093694(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->mv.co.guard.x0 < p_ftCommonData->x2A0 &&
        fp->input.x668 & (HSD_PAD_R | HSD_PAD_L) &&
        fp->x672_input_timer_counter < p_ftCommonData->x2A0)
    {
        ftCo_80093850(gobj);
        return true;
    }
    return false;
}

void ftCo_8009370C(ftCo_GObj* gobj, HSD_GObjEvent on_reflect)
{
    u8 _[8] = { 0 };
    ReflectDesc reflect;
    ftCo_Fighter* fp = gobj->user_data;
    reflect.x0_bone_id = fp->ft_data->x8->x11;
    reflect.x4_max_damage = fp->shield_health;
    reflect.x8_offset.x = reflect.x8_offset.y = reflect.x8_offset.z = 0;
    reflect.x14_size = p_ftCommonData->x2A8;
    reflect.x18_damage_mul = p_ftCommonData->x2AC;
    reflect.x1C_speed_mul = p_ftCommonData->x2B0;
    reflect.x20_behavior = 1;
    ftColl_CreateReflectHit(gobj, &reflect, on_reflect);
}

void ftCo_80093790(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    ftCommon_8007DB24(gobj);
    {
        HSD_JObj* jobj = fp->parts[fp->ft_data->x8->x11].joint;
        ftCo_80092158(gobj, 1050, jobj);
        fp->x2219_b0 = true;
        ft_80088148(fp, 128, 127, 64);
    }
}

void ftCo_80093850(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    switch (fp->kind) {
    case FTKIND_YOSHI:
        ftYs_Shield_8012C850(gobj);
        return;
    default:
        ftCo_8009388C(gobj);
        return;
    }
}

void ftCo_8009388C(HSD_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    Fighter_ChangeMotionState(gobj, ftCo_MS_GuardReflect,
                              Ft_MF_SkipAnim | Ft_MF_KeepGfx,
                              fp->cur_anim_frame, 1, 0, NULL);
    fp->x672_input_timer_counter = 0xFE;
    fp->x221A_b7 = false;
    fp->x221B_b0 = false;
    fp->x221C_b3 = true;
    fp->x221C_b1 = true;
    fp->x221C_b2 = true;
    fp->mv.co.guard.x1C = 0;
    fp->mv.co.guard.x14 = p_ftCommonData->x2A4;
    fp->mv.co.guard.x18 = p_ftCommonData->x2B4;
    ftCo_8009370C(gobj, ftCo_80093790);
}

/// @todo Shares a lot of code with #ftCo_800923B4
void ftCo_800939B4(ftCo_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    switch (fp->kind) {
    case FTKIND_YOSHI:
        ftYs_Shield_8012C914(gobj);
        return;
    case FTKIND_MARS:
        ftCo_80093A50(gobj);
        ftParts_80074B0C(gobj, 1, 1);
        ft_80088148(fp, 190115, 127, 64);
        return;
    default:
        ftCo_80093A50(gobj);
        return;
    }
    ftCo_800923B4(gobj);
}

/// @todo Shared code with #ftCo_8009388C.
void ftCo_80093A50(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    Fighter_ChangeMotionState(gobj, 182, Ft_MF_SkipAnim, 0, 1, 0, NULL);
    ftAnim_8006EBA4(gobj);
    fp->x672_input_timer_counter = 0xFE;
    fp->x221C_b3 = true;
    fp->x221C_b1 = true;
    fp->x221C_b2 = true;
    fp->mv.co.guard.x1C = 0;
    fp->mv.co.guard.x14 = p_ftCommonData->x2A4;
    fp->mv.co.guard.x18 = p_ftCommonData->x2B4;
    ftCo_80092450(gobj);
    ftCo_8009370C(gobj, ftCo_80093790);
    ftCo_800921DC(gobj);
}

void ftCo_80093BC0(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->x221C_b3) {
        fp->x221C_b3 = false;
    }
    if (fp->x221C_b1) {
        fp->mv.co.guard.x14 -= 1;
        if (fp->mv.co.guard.x14 < 0) {
            fp->x221C_b1 = false;
            fp->x2218_b3 = false;
            ftCo_80092450(gobj);
        }
    }
    if (fp->x221C_b2) {
        fp->mv.co.guard.x18 -= 1;
        if (fp->mv.co.guard.x18 < 0) {
            fp->x221C_b2 = false;
        }
    }
}

void ftCo_GuardReflect_Anim(HSD_GObj* gobj)
{
    ftCo_80093BC0(gobj);
    ftCo_GuardOn_Anim(gobj);
}

void ftCo_GuardReflect_IASA(HSD_GObj* gobj)
{
    u8 _[16] = { 0 };
    /// @todo Inline depth.
    RETURN_IF(inlineC0(gobj, ftCo_80092BE8));
    RETURN_IF(ftCo_8009515C(gobj));
    RETURN_IF(ftCo_8009980C(gobj));
    RETURN_IF(ftCo_8009917C(gobj));
    RETURN_IF(ftCo_800D8B9C(gobj));
    RETURN_IF(ftCo_Catch_CheckInput(gobj));
    RETURN_IF(ftCo_800CB024(gobj));
    RETURN_IF(ftCo_8009A080(gobj));
}

void ftCo_GuardReflect_Phys(ftCo_GObj* gobj)
{
    ft_80084F3C(gobj);
    ftColl_8007AEE0(gobj);
    ftColl_8007AEF8(gobj);
}

void ftCo_GuardReflect_Coll(ftCo_GObj* gobj)
{
    ft_800845B4(gobj);
}

f32 ftCo_80094098(HSD_GObj* gobj, f32* arg1)
{
    NOT_IMPLEMENTED;
}

void ftCo_80094138(ftCo_Fighter* fp)
{
    NOT_IMPLEMENTED;
}
