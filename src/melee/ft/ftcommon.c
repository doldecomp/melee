#include "ftcommon.h"

#include "fighter.h"
#include "ft_081B.h"
#include "ft_0877.h"
#include "ftcamera.h"
#include "ftcoll.h"
#include "ftlib.h"
#include "ftparts.h"
#include "stdbool.h"

#include "ef/eflib.h"

#include "ft/forward.h"

#include "ft/ft_0881.h"
#include "ft/ft_0892.h"
#include "ft/ft_0C88.h"
#include "ft/ft_0DF0.h"
#include "ft/ftchangeparam.h"
#include "ft/ftcolanim.h"
#include "ft/ftmaterial.h"
#include "ft/ftmetal.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Damage.h"
#include "ftCommon/ftCo_DamageFall.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/ftCo_HammerWait.h"
#include "ftCommon/ftpickupitem.h"
#include "gm/gm_unsplit.h"

#include "it/forward.h"

#include "it/it_26B1.h"
#include "it/item.h"
#include "it/items/it_2E5A.h"
#include "it/items/itfflowerflame.h"
#include "it/items/itrabbitc.h"
#include "it/items/itsword.h"
#include "lb/lb_00F9.h"

#include "mp/forward.h"

#include "mp/mplib.h"
#include "pl/player.h"
#include "pl/plbonuslib.h"
#include "vi/vi1202.h"

#include <common_structs.h>
#include <math.h>
#include <trigf.h>
#include <dolphin/os/OSError.h>
#include <baselib/debug.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>
#include <baselib/rumble.h>
#include <melee/it/items/itpeachparasol.h>

const Vec3 ftCo_803B74A0 = { 0 };

void ftCommon_ApplyFrictionGround(Fighter* fp, float friction)
{
    if (ABS(friction) > ABS(fp->gr_vel)) {
        friction = -fp->gr_vel;
    } else if (fp->gr_vel > 0) {
        friction = -friction;
    }
    fp->xE4_ground_accel_1 = friction;
}

void ftCommon_8007C98C(Fighter* fp, float accel, float target_vel,
                       float friction)
{
    if (!target_vel) {
        ftCommon_ApplyFrictionGround(fp, friction);
        return;
    }

    if (!(fp->gr_vel * accel < 0)) {
        if (accel > 0) {
            if (fp->gr_vel + accel > target_vel) {
                accel = -friction;
                if (fp->gr_vel + accel < target_vel) {
                    accel = target_vel - fp->gr_vel;
                }
                if (fp->gr_vel + accel >
                    fp->co_attrs.ground_max_horizontal_velocity)
                {
                    accel = fp->co_attrs.ground_max_horizontal_velocity -
                            fp->gr_vel;
                }
            }
        } else if (fp->gr_vel + accel < target_vel) {
            accel = friction;
            if (fp->gr_vel + accel > target_vel) {
                accel = target_vel - fp->gr_vel;
            }
            if (fp->gr_vel + accel <
                -fp->co_attrs.ground_max_horizontal_velocity)
            {
                accel =
                    -fp->co_attrs.ground_max_horizontal_velocity - fp->gr_vel;
            }
        }
    }
    fp->xE4_ground_accel_1 = accel;
}

void ftCommon_8007CA80(Fighter* fp, float accel, float target_vel,
                       float friction)
{
    if (!target_vel) {
        accel = -fp->gr_vel;
    } else if (!(fp->gr_vel * accel < 0)) {
        if (accel > 0) {
            if (fp->gr_vel + accel > target_vel) {
                accel = target_vel - fp->gr_vel;
            }
        } else if (fp->gr_vel + accel < target_vel) {
            accel = target_vel - fp->gr_vel;
        }
    }
    fp->xE4_ground_accel_1 = accel;
}

void ftCommon_8007CADC(Fighter* fp, float threshold, float accel_max,
                       float target_max)
{
    float lsx = fp->input.lstick.x;
    float accel;
    float target_vel;

    if (ABS(lsx) >= threshold) {
        accel = lsx * accel_max;
        target_vel = lsx * target_max;
    } else {
        target_vel = 0;
        accel = 0;
    }
    ftCommon_8007CA80(fp, accel, target_vel, lsx);
}

void ftCommon_ApplyGroundMovement(HSD_GObj* gobj)
{
    float temp_f1;
    Vec3* ground_normal;
    Fighter* fp = gobj->user_data;

    u8 _[8];

    ground_normal = &fp->coll_data.floor.normal;
    temp_f1 = ft_GetGroundFrictionMultiplier(fp);
    if (temp_f1 < 1) {
        fp->xE4_ground_accel_1 *= temp_f1;
    }
    fp->x74_anim_vel.x = +ground_normal->y * fp->xE4_ground_accel_1;
    fp->x74_anim_vel.y = -ground_normal->x * fp->xE4_ground_accel_1;
    fp->x74_anim_vel.z = 0;
    fp->self_vel.x = +ground_normal->y * fp->gr_vel;
    fp->self_vel.y = -ground_normal->x * fp->gr_vel;
    fp->self_vel.z = 0;
}

HSD_GObj* ftCommon_ApplyGroundMovementNoSlide(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    Vec3* ground_normal = &fp->coll_data.floor.normal;
    fp->x74_anim_vel.x = +ground_normal->y * fp->xE4_ground_accel_1;
    fp->x74_anim_vel.y = -ground_normal->x * fp->xE4_ground_accel_1;
    fp->x74_anim_vel.z = 0;
    fp->self_vel.x = +ground_normal->y * fp->gr_vel;
    fp->self_vel.y = -ground_normal->x * fp->gr_vel;
    fp->self_vel.z = 0;
    return gobj;
}

void ftCommon_ClampGrVel(Fighter* fp, float max)
{
    if (fp->gr_vel < -max) {
        fp->gr_vel = -max;
    } else if (fp->gr_vel > max) {
        fp->gr_vel = +max;
    }
}

void ftCommon_8007CCA0(Fighter* fp, float arg1)
{
    if (fp->xF0_ground_kb_vel < 0) {
        fp->xF0_ground_kb_vel = fp->xF0_ground_kb_vel + arg1;
        if (fp->xF0_ground_kb_vel > 0) {
            fp->xF0_ground_kb_vel = 0;
        }
    } else {
        fp->xF0_ground_kb_vel = fp->xF0_ground_kb_vel - arg1;
        if (fp->xF0_ground_kb_vel < 0) {
            fp->xF0_ground_kb_vel = 0;
        }
    }
}

void ftCommon_8007CCE8(Fighter* fp)
{
    Vec3* ground_normal;
    if (fp->ground_or_air == GA_Ground && fp->xF0_ground_kb_vel == 0) {
        ground_normal = &fp->coll_data.floor.normal;
        fp->xF0_ground_kb_vel = fp->x8c_kb_vel.x;
        if (fp->xF0_ground_kb_vel > p_ftCommonData->x164) {
            fp->xF0_ground_kb_vel = p_ftCommonData->x164;
        }
        if (fp->xF0_ground_kb_vel < -p_ftCommonData->x164) {
            fp->xF0_ground_kb_vel = -p_ftCommonData->x164;
        }
        fp->x8c_kb_vel.x = +ground_normal->y * fp->xF0_ground_kb_vel;
        fp->x8c_kb_vel.y = -ground_normal->x * fp->xF0_ground_kb_vel;
    }
}

float ftCommon_8007CD6C(float value, float decrement)
{
    float result = value;
    if (value > 0) {
        result -= decrement;
        if (result < 0) {
            return 0;
        }
    } else if (value < 0) {
        result += decrement;
        if (result > 0) {
            return 0;
        }
    }
    return result;
}

#define Ft_Kind_Sandbag FTKIND_SANDBAG
float ftCommon_8007CDA4(Fighter* fp)
{
    HSD_ASSERT(299, fp->kind == Ft_Kind_Sandbag);
    return ((float*) fp->dat_attrs)[0];
}

float ftCommon_8007CDF8(Fighter* fp)
{
    HSD_ASSERT(308, fp->kind == Ft_Kind_Sandbag);
    return ((float*) fp->dat_attrs)[1];
}

void ftCommon_8007CE4C(Fighter* fp, float val)
{
    if (fp->xF4_ground_attacker_shield_kb_vel < 0) {
        fp->xF4_ground_attacker_shield_kb_vel += val;
        if (fp->xF4_ground_attacker_shield_kb_vel > 0) {
            fp->xF4_ground_attacker_shield_kb_vel = 0;
        }
    } else {
        fp->xF4_ground_attacker_shield_kb_vel -= val;
        if (fp->xF4_ground_attacker_shield_kb_vel < 0) {
            fp->xF4_ground_attacker_shield_kb_vel = 0;
        }
    }
}

void ftCommon_ApplyFrictionAir(Fighter* fp, float friction)
{
    if (ABS(friction) >= ABS(fp->self_vel.x)) {
        friction = -fp->self_vel.x;
    } else if (fp->self_vel.x > 0) {
        friction = -friction;
    }
    fp->x74_anim_vel.x = friction;
}

#define SOLUTION 0
/// @todo This surely calls #ftCommon_ApplyFrictionAir somehow...
void ftCommon_8007CEF4(Fighter* fp)
{
#if SOLUTION == 0
    float result = fp->co_attrs.aerial_friction;
    float lhs = ABS(result);
    float absvel = ABS(fp->self_vel.x);
    if (ABS(result) >= absvel) {
        result = -fp->self_vel.x;
    } else if (fp->self_vel.x > 0) {
        result = -fp->co_attrs.aerial_friction;
    }
    fp->x74_anim_vel.x = result;
#elif SOLUTION == 1
    ftCommon_ApplyFrictionAir(fp, fp->co_attrs.aerial_friction);
#endif
}
#undef SOLUTION

bool ftCommon_8007CF58(Fighter* fp)
{
    ftCo_DatAttrs* ca = &fp->co_attrs;
    float vel = fp->self_vel.x;
    float _ = ABS(vel);

    if (ABS(vel) > ca->air_drift_max) {
        float accel = p_ftCommonData->x1FC;
        if (ABS(accel) >= ABS(vel)) {
            accel = -vel;
        } else if (vel > 0) {
            accel = -p_ftCommonData->x1FC;
        }
        fp->x74_anim_vel.x = accel;
        return true;
    } else {
        float accel = fp->co_attrs.aerial_friction;
        if (ABS(accel) >= ABS(vel)) {
            accel = -vel;
        } else if (vel > 0) {
            accel = -fp->co_attrs.aerial_friction;
        }
        fp->x74_anim_vel.x = accel;
        return false;
    }
}

bool ftCommon_8007D050(Fighter* fp, float max_vel)
{
    float vel = fp->self_vel.x;
    float _ = ABS(vel);

    if (ABS(vel) > max_vel) {
        float accel = p_ftCommonData->x1FC;
        if (ABS(accel) >= ABS(vel)) {
            accel = -vel;
        } else if (vel > 0) {
            accel = -p_ftCommonData->x1FC;
        }
        fp->x74_anim_vel.x = accel;
        return true;
    } else {
        float accel = fp->co_attrs.aerial_friction;
        if (ABS(accel) >= ABS(vel)) {
            accel = -vel;
        } else if (vel > 0) {
            accel = -fp->co_attrs.aerial_friction;
        }
        fp->x74_anim_vel.x = accel;
        return false;
    }
}

void ftCommon_8007D140(Fighter* fp, float accel, float target_vel,
                       float friction)
{
    ftCommon_8007D174(fp, fp->self_vel.x, accel, target_vel, friction);
}

void ftCommon_8007D174(Fighter* fp, float vel, float accel, float target_vel,
                       float friction)
{
    if (!target_vel) {
        ftCommon_ApplyFrictionAir(fp, friction);
        return;
    }

    if (!(vel * accel < 0.0F)) {
        if (accel > 0) {
            if (vel + accel > target_vel) {
                accel = -friction;
                if (vel + accel < target_vel) {
                    accel = target_vel - vel;
                }
                if (vel + accel > fp->co_attrs.air_max_horizontal_velocity) {
                    accel = fp->co_attrs.air_max_horizontal_velocity - vel;
                }
            }
        } else if (vel + accel < target_vel) {
            accel = friction;
            if (vel + accel > target_vel) {
                accel = target_vel - vel;
            }
            if (vel + accel < -fp->co_attrs.air_max_horizontal_velocity) {
                accel = -fp->co_attrs.air_max_horizontal_velocity - vel;
            }
        }
    }
    fp->x74_anim_vel.x = accel;
}

void ftCommon_8007D268(Fighter* fp)
{
    ftCommon_8007D28C(fp, fp->self_vel.x);
}

void ftCommon_8007D28C(Fighter* fp, float vel)
{
    float accel_scaling;
    float accel_flat;
    float lsx = fp->input.lstick.x;
    ftCo_DatAttrs* attrs = &fp->co_attrs;
    accel_scaling = lsx * attrs->air_drift_stick_mul;

    if (lsx > 0) {
        accel_flat = +attrs->aerial_drift_base;
    } else {
        accel_flat = -attrs->aerial_drift_base;
    }
    ftCommon_8007D174(fp, vel, accel_scaling + accel_flat,
                      lsx * attrs->air_drift_max, attrs->aerial_friction);
}

void ftCommon_8007D2E8(Fighter* fp, float accel, float target_vel,
                       float unused)
{
    if (!target_vel) {
        accel = -fp->self_vel.x;
    } else if (!(fp->self_vel.x * accel < 0)) {
        if (accel > 0) {
            if (fp->self_vel.x + accel > target_vel) {
                accel = target_vel - fp->self_vel.x;
            }
        } else {
            if (fp->self_vel.x + accel < target_vel) {
                accel = target_vel - fp->self_vel.x;
            }
        }
    }
    fp->x74_anim_vel.x = accel;
}

void ftCommon_8007D344(Fighter* fp, float threshold, float accel_max,
                       float target_max)
{
    float accel, target;

    if (ABS(fp->input.lstick.x) >= threshold) {
        accel = fp->input.lstick.x * accel_max;
        target = fp->input.lstick.x * target_max;
    } else {
        target = 0;
        accel = 0;
    }
    ftCommon_8007D140(fp, accel, target, fp->co_attrs.aerial_friction);
}

void ftCommon_8007D3A8(Fighter* fp, float threshold, float accel_max,
                       float target_max)
{
    float accel;
    float target_vel;

    if (ABS(fp->input.lstick.x) >= threshold) {
        accel = fp->input.lstick.x * accel_max;
        target_vel = fp->input.lstick.x * target_max;
    } else {
        target_vel = 0;
        accel = 0;
    }

    ftCommon_8007D2E8(fp, accel, target_vel, 0.0F);
}

void ftCommon_ClampSelfVelX(Fighter* fp, float max)
{
    float vel = fp->self_vel.x;
    if (vel < -max) {
        fp->self_vel.x = -max;
    } else if (vel > max) {
        fp->self_vel.x = +max;
    }
}

void ftCommon_ClampAirDrift(Fighter* fp)
{
    ftCommon_ClampSelfVelX(fp, fp->co_attrs.air_drift_max);
}

void ftCommon_Fall(Fighter* fp, float gravity, float terminal_vel)
{
    fp->self_vel.y -= gravity;
    if (fp->self_vel.y < -terminal_vel) {
        fp->self_vel.y = -terminal_vel;
    }
}

void ftCommon_FallBasic(Fighter* fp)
{
    ftCommon_Fall(fp, fp->co_attrs.grav, fp->co_attrs.terminal_vel);
}

void ftCommon_FallFast(Fighter* fp)
{
    fp->self_vel.y = -fp->co_attrs.fast_fall_velocity;
}

void ftCommon_ClampFallSpeed(Fighter* fp, float val)
{
    if (fp->self_vel.y > val) {
        fp->self_vel.y = val;
    }
}

void ftCommon_Ascend(Fighter* fp, float accel, float max)
{
    fp->self_vel.y += accel;
    if (fp->self_vel.y > max) {
        fp->self_vel.y = max;
    }
}

bool ftCommon_CheckFallFast(Fighter* fp)
{
    if (!fp->fall_fast && fp->self_vel.y < 0 &&
        fp->input.lstick.y <= -p_ftCommonData->x88 &&
        fp->x671_timer_lstick_tilt_y < p_ftCommonData->x8C)
    {
        fp->fall_fast = true;
        fp->x671_timer_lstick_tilt_y = 0xFE;
        ft_PlaySFX(fp, 0x96, 0x7F, 0x40);
        return true;
    }
    return false;
}

void ftCommon_UnlockECB(Fighter* fp)
{
    fp->ecb_lock = 0;
    fp->coll_data.x130_flags &= ~CollData_X130_Locked;
}

void ftCommon_8007D5D4(Fighter* fp)
{
    fp->ground_or_air = GA_Air;
    fp->gr_vel = 0;
    fp->x98_atk_shield_kb.z = 0;
    fp->cur_pos.z = 0;
    fp->x74_anim_vel.y = 0;
    fp->x1968_jumpsUsed = 1;
    fp->ecb_lock = 10;
    fp->coll_data.x130_flags |= CollData_X130_Locked;
}

void ftCommon_8007D60C(Fighter* fp)
{
    ftCo_DatAttrs* ca = &fp->co_attrs;
    if (fp->x2227_b0 && fp->x1968_jumpsUsed <= 1) {
        pl_8003FC44(fp->player_id, fp->x221F_b4);
    }
    fp->ground_or_air = GA_Air;
    fp->gr_vel = 0;
    fp->x74_anim_vel.y = 0;
    fp->x1968_jumpsUsed = ca->max_jumps;
    fp->ecb_lock = 5;
    fp->coll_data.x130_flags |= CollData_X130_Locked;
}

void ftCommon_UseAllJumps(Fighter* fp)
{
    fp->x1968_jumpsUsed = fp->co_attrs.max_jumps;
}

void ftCommon_8007D6A4(Fighter* fp)
{
    if (fp->x594_b0) {
        fp->self_vel.x = fp->x6A4_transNOffset.z * fp->facing_dir;
    }
    ftCommon_ClampGrVel(fp, fp->co_attrs.ground_max_horizontal_velocity);
    fp->ground_or_air = GA_Ground;
    fp->gr_vel = fp->self_vel.x;
    fp->x1968_jumpsUsed = 0;
    fp->x1969_walljumpUsed = 0;
    fp->x2227_b0 = 0;
    ftCommon_UnlockECB(fp);
    if (!ft_80084A18(fp->gobj)) {
        OSReport("fighter ground no under Id! %d %d\n", fp->player_id,
                 fp->motion_id);
        HSD_ASSERT(686, 0);
    }
}

void ftCommon_8007D780(Fighter* fp)
{
    if (fp->ground_or_air != GA_Air) {
        return;
    }

    if (un_803224DC(fp->x8_spawnNum, fp->cur_pos.x,
                    fp->dmg.x18A4_knockbackMagnitude))
    {
        fp->dmg.x18A4_knockbackMagnitude = 0;
    }
    if (fp->x2227_b0 && fp->x1968_jumpsUsed <= 1) {
        pl_8003FC44(fp->player_id, fp->x221F_b4);
    }
}

void ftCommon_8007D7FC(Fighter* fp)
{
    if (fp->ground_or_air == GA_Air) {
        if (un_803224DC(fp->x8_spawnNum, fp->cur_pos.x,
                        fp->dmg.x18A4_knockbackMagnitude))
        {
            fp->dmg.x18A4_knockbackMagnitude = 0;
        }
        if (fp->x2227_b0 && fp->x1968_jumpsUsed <= 1) {
            pl_8003FC44(fp->player_id, fp->x221F_b4);
        }
    }
    ftCommon_8007D6A4(fp);
}

void ftCommon_8007D92C(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->ground_or_air == GA_Air) {
        ftCo_Fall_Enter(gobj);
    } else {
        ft_8008A2BC(gobj);
    }
}

float ftCo_GetLStickAngle(Fighter* fp)
{
    return atan2f(fp->input.lstick.y, ABS(fp->input.lstick.x));
}

float ftCo_GetCStickAngle(Fighter* fp)
{
    return atan2f(fp->input.cstick.y, ABS(fp->input.cstick.x));
}

float ftCommon_8007D9D4(Fighter* fp)
{
    return atan2f(fp->input.lstick.y, fp->input.lstick.x);
}

void ftCommon_UpdateFacing(Fighter* fp)
{
    float dir;
    if (fp->input.lstick.x >= 0) {
        dir = +1;
    } else {
        dir = -1;
    }
    fp->facing_dir = dir;
}

void ftCommon_8007DA24(Fighter* fp)
{
    if (ABS(fp->input.lstick.x) > p_ftCommonData->x0) {
        ftCommon_UpdateFacing(fp);
    }
}

float ftCommon_CalcHitlag(int dmg, FtMotionId msid, float mul)
{
    int tmp = dmg * p_ftCommonData->x198 + p_ftCommonData->x19C;
    float result = (int) (tmp * mul);
    if ((unsigned) msid - ftCo_MS_Squat <= 1) {
        result = (int) (result * p_ftCommonData->x1A0);
    }
    return result;
}

void ftCommon_8007DB24(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    fp->x2219_b0 = 0;
    efLib_DestroyAll(gobj);
}

void ftCommon_8007DB58(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ft_80088770(fp);
    ft_800887CC(fp);
    if (fp->take_dmg_cb != NULL) {
        fp->take_dmg_cb(gobj);
    }
    if (fp->death1_cb != NULL) {
        fp->death1_cb(gobj);
    }
}

extern struct {
    Vec2* x0;
    s32 x4;
}* Fighter_804D652C;

void ftCommon_InitGrab(Fighter* fp, bool arg1, float timer)
{
    fp->grab_timer = timer;
    fp->x1A51 = 0;
    fp->x1A50 = 0;
    fp->x2224_b6 = arg1;
    if (fp->x2224_b6) {
        fp->x1A52 = 0;
        fp->x1A53 = Fighter_804D652C->x4;
    }
}

bool ftCommon_GrabMash(Fighter* fp, float arg1)
{
    bool result = false;
    if (fp->input.x668 & (HSD_PAD_AB | HSD_PAD_XY | HSD_PAD_LR)) {
        fp->grab_timer -= arg1;
        result = true;
    }
    {
        s8 r5 = fp->x1A50;
        s8 r6 = fp->x1A51;
        if (fp->input.lstick.x < -p_ftCommonData->x308) {
            fp->x1A50 = -1;
        }
        if (fp->input.lstick.x > p_ftCommonData->x308) {
            fp->x1A50 = 1;
        }
        if (fp->input.lstick.y < -p_ftCommonData->x308) {
            fp->x1A51 = -1;
        }
        if (fp->input.lstick.y > p_ftCommonData->x308) {
            fp->x1A51 = 1;
        }
        if (r5 != fp->x1A50 || r6 != fp->x1A51) {
            fp->grab_timer -= arg1;
            result = true;
        }
    }
    if (result && fp->x2224_b6) {
        fp->x2224_b5 = true;
        fp->x1A52 += 1;
        if (fp->x1A52 >= fp->x1A53) {
            fp->x1A52 = 0;
        }
    } else {
        fp->x2224_b5 = false;
    }
    pl_800402D0(fp->player_id, fp->x221F_b4, result);
    return result;
}

void ftCommon_8007DD7C(HSD_GObj* gobj, Vec3* v)
{
    u8 unused0[4];

    Vec2* temp_r31;
    Vec3 sp24;
    Fighter* arg_ft;
    Fighter* cur_ft;
    float temp_f0;
    s32 arg_gnd;
    s32 cur_gnd;
    HSD_GObj* cur;
    bool phi_r28;
    Vec2* vtmp;

    u8 unused1[20];

    arg_ft = gobj->user_data;
    phi_r28 = false;
    for (cur = HSD_GObj_Entities->fighters; cur != NULL; cur = cur->next) {
        temp_r31 = &arg_ft->x2C4;
        if (cur != gobj && !ftLib_80086FD4(cur, gobj)) {
            cur_ft = cur->user_data;
            if (cur_ft->x221F_b3 || cur_ft->ground_or_air != GA_Ground ||
                cur_ft->victim_gobj != NULL || cur_ft->x221F_b4)
            {
                continue;
            }
            arg_gnd = arg_ft->coll_data.floor.index;
            cur_gnd = cur_ft->coll_data.floor.index;
            if (arg_gnd == cur_gnd || cur_gnd == mpLineGetNext(arg_gnd) ||
                cur_gnd == mpLineGetPrev(arg_gnd))
            {
                ftCommon_8007F8B4(cur_ft, &sp24);
                vtmp = &cur_ft->x2C4;
                temp_f0 = (temp_r31->x * arg_ft->facing_dir + v->x) -
                          (cur_ft->facing_dir * vtmp->x + sp24.x);
                if (ABS(temp_f0) < temp_r31->y + vtmp->y) {
                    if (temp_f0) {
                        arg_ft->xF8_playerNudgeVel.x +=
                            temp_f0 < 0 ? -p_ftCommonData->x450
                                        : p_ftCommonData->x450;
                    } else {
                        arg_ft->xF8_playerNudgeVel.x +=
                            phi_r28 ? -p_ftCommonData->x450
                                    : p_ftCommonData->x450;
                    }
                    if (v->z - sp24.z) {
                        arg_ft->xF8_playerNudgeVel.y +=
                            v->z - sp24.z < 0 ? -p_ftCommonData->x454
                                              : p_ftCommonData->x454;
                    } else if (temp_f0) {
                        arg_ft->xF8_playerNudgeVel.y +=
                            temp_f0 < 0 ? -p_ftCommonData->x454
                                        : p_ftCommonData->x454;
                    } else {
                        arg_ft->xF8_playerNudgeVel.y +=
                            phi_r28 ? -p_ftCommonData->x454
                                    : p_ftCommonData->x454;
                    }
                }
            }
        } else {
            phi_r28 = true;
        }
    }
}

void ftCommon_8007DFD0(HSD_GObj* gobj, Vec3* arg1)
{
    u8 unused0[4];

    Vec3 sp1C;
    Vec2* temp_r31;
    HSD_GObj* new_var;
    s32 new_var2;
    Fighter* fp;
    Fighter* temp_r3;
    float temp_f1;
    s32 temp_r0;
    s32 temp_r30;
    Vec2* tmp;
    u8 unused1[12];
    fp = gobj->user_data;
    temp_r31 = &fp->x2C4;
    new_var = Player_GetEntity(fp->player_id);
    temp_r3 = new_var->user_data;
    if (!temp_r3->x221F_b3 && temp_r3->ground_or_air == GA_Ground) {
        temp_r0 = fp->coll_data.floor.index;
        temp_r30 = (new_var2 = temp_r3->coll_data.floor.index);
        if (temp_r0 == temp_r30 || temp_r30 == mpLineGetNext(temp_r0) ||
            temp_r30 == mpLineGetPrev(temp_r0))
        {
            ftCommon_8007F8B4(temp_r3, &sp1C);
            tmp = &temp_r3->x2C4;
            temp_f1 = (temp_r31->x * fp->facing_dir + arg1->x) -
                      (temp_r3->facing_dir * tmp->x + sp1C.x);
            if (ABS(temp_f1) < temp_r31->y + tmp->y) {
                fp->xF8_playerNudgeVel.y -= p_ftCommonData->x45C;
            }
        }
    }
    ftCommon_8007DD7C(gobj, arg1);
}

void ftCommon_8007E0E4(HSD_GObj* gobj)
{
    Vec3 sp10;
    Fighter* fp;

    u8 _[4];

    float phi_f0;
    float phi_f31;
    float phi_f30;

    fp = gobj->user_data;
    fp->xF8_playerNudgeVel.y = 0;
    fp->xF8_playerNudgeVel.x = 0;
    if (!fp->x2219_b1 && !fp->x2219_b5 && fp->ground_or_air == GA_Ground) {
        if (!fp->x221F_b4) {
            phi_f30 = p_ftCommonData->x454;
            phi_f31 = p_ftCommonData->x458;
        } else {
            phi_f30 = p_ftCommonData->x45C;
            phi_f31 = p_ftCommonData->x460;
        }
        ftCommon_8007F8B4(fp, &sp10);
        if (!fp->x221D_b5) {
            if (!fp->x221F_b4) {
                ftCommon_8007DD7C(gobj, &sp10);
            } else {
                ftCommon_8007DFD0(gobj, &sp10);
            }
        }
        if (!fp->xF8_playerNudgeVel.y && sp10.z) {
            if (sp10.z < 0) {
                phi_f0 = phi_f30;
            } else {
                phi_f0 = -phi_f30;
            }
            fp->xF8_playerNudgeVel.y = phi_f0;
        }
        if ((fp->xF8_playerNudgeVel.y > 0 && sp10.z < 0 &&
             sp10.z + fp->xF8_playerNudgeVel.y >= 0) ||
            (fp->xF8_playerNudgeVel.y < 0 && sp10.z > 0 &&
             sp10.z + fp->xF8_playerNudgeVel.y <= 0))
        {
            fp->xF8_playerNudgeVel.y = -sp10.z;
            sp10.z = 0;
        }
        if (sp10.z + fp->xF8_playerNudgeVel.y > phi_f31) {
            fp->xF8_playerNudgeVel.y = phi_f31 - sp10.z;
        } else if (sp10.z + fp->xF8_playerNudgeVel.y < -phi_f31) {
            fp->xF8_playerNudgeVel.y = -phi_f31 - sp10.z;
        }
        if (fp->x221F_b4 == 1) {
            fp->xF8_playerNudgeVel.x = 0;
        }
    }
}

HSD_GObj* ftCommon_8007E2A4(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    CollData* colldata = &fp->coll_data;
    fp->x98_atk_shield_kb.x =
        colldata->floor.normal.y * fp->xF4_ground_attacker_shield_kb_vel;
    fp->x98_atk_shield_kb.y =
        -colldata->floor.normal.x * fp->xF4_ground_attacker_shield_kb_vel;
    return gobj;
}

void ftCommon_8007E2D0(Fighter* fp, s16 arg1, HSD_GObjEvent grab_cb,
                       HSD_GObjEvent unk_cb,
                       void (*grabbed_cb)(HSD_GObj*, HSD_GObj*))
{
    fp->x221E_b6 = true;
    fp->x1A68 = arg1;
    fp->grab_cb = grab_cb;
    fp->grabbed_cb = grabbed_cb;
    fp->x2194 = unk_cb;
}

void ftCommon_8007E2F4(Fighter* fp, s16 val)
{
    fp->x1A6A = val;
}

inline void _func_8007E2FC_inline(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    fp->xE4_ground_accel_1 = 0;
    fp->xE8_ground_accel_2 = 0;
    fp->x74_anim_vel.z = 0;
    fp->x74_anim_vel.y = 0;
    fp->x74_anim_vel.x = 0;
    fp->gr_vel = 0;
    fp->self_vel.z = 0;
    fp->self_vel.y = 0;
    fp->self_vel.x = 0;
    fp->xF0_ground_kb_vel = 0;
    fp->x8c_kb_vel.z = 0;
    fp->x8c_kb_vel.y = 0;
    fp->x8c_kb_vel.x = 0;
    fp->xF4_ground_attacker_shield_kb_vel = 0;
    fp->x98_atk_shield_kb.z = 0;
    fp->x98_atk_shield_kb.y = 0;
    fp->x98_atk_shield_kb.x = 0;
    fp->xD4_unk_vel.z = 0;
    fp->xD4_unk_vel.y = 0;
    fp->xD4_unk_vel.x = 0;
}

void ftCommon_8007E2FC(HSD_GObj* gobj)
{
    _func_8007E2FC_inline(gobj);
}

void ftCommon_8007E358(HSD_GObj* gobj)
{
    HSD_JObj* jobj;
    Fighter* fp = gobj->user_data;
    jobj = fp->parts[ftParts_GetBoneIndex(fp, 4)].joint;
    HSD_JObjGetTranslation(jobj, &fp->x1A7C);
}

void ftCommon_8007E3EC(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    HSD_JObj* jobj = fp->parts[ftParts_GetBoneIndex(fp, 4)].joint;
    Vec3 sp10;

    u8 _[4];

    if (HSD_JObjMtxIsDirty(jobj)) {
        HSD_JObjGetTranslation(jobj, &sp10);
        sp10.x -= fp->x1A7C.x;
        sp10.y -= fp->x1A7C.y;
        sp10.z -= fp->x1A7C.z;
        fp->x1A7C.x += sp10.x * fp->x1A6C;
        fp->x1A7C.y += sp10.y * fp->x1A6C;
        fp->x1A7C.z += sp10.z * fp->x1A6C;
        HSD_JObjSetTranslate(jobj, &fp->x1A7C);
    }
}

void ftCommon_8007E5AC(Fighter* fp)
{
    Vec3* ground_normal = &fp->coll_data.floor.normal;
    float tmp = -atan2f(ground_normal->x, ground_normal->y);
    HSD_ASSERT(1146, fp->ground_or_air == GA_Ground);
    ftParts_80075CB4(fp, 0, tmp);
}

void ftCommon_SetAccessory(Fighter* fp, HSD_Joint* joint)
{
    if (fp->x20A0_accessory != NULL) {
        OSReport("fighter accessory already exsist!\n");
        HSD_ASSERT(0x486, 0);
    }
    fp->x20A0_accessory = HSD_JObjLoadJoint(joint);
}

void ftCommon_8007E690(Fighter* fp, HSD_AnimJoint* arg1)
{
    if (fp->x20A0_accessory != NULL) {
        HSD_JObjAddAnimAll(fp->x20A0_accessory, arg1, NULL, NULL);
        HSD_JObjReqAnimAll(fp->x20A0_accessory, 0);
    }
}

extern void (*ftData_OnItemDropExt[])(HSD_GObj*, s32);
extern void (*ftData_OnItemDrop[])(HSD_GObj*, s32); // OnItemDrop?
extern void (*ftData_OnItemPickup[])(HSD_GObj*, s32);

void ftCommon_8007E6DC(HSD_GObj* gobj, HSD_GObj* item_gobj, s32 arg2)
{
    Fighter* fp = gobj->user_data;
    if ((fp->x1978 != NULL) && (fp->x1978 == item_gobj)) {
        fp->x1978 = NULL;
        return;
    }
    if (ftCo_800C5240(gobj)) {
        ftCo_800C5500(gobj);
    }
    if (ftData_OnItemDropExt[fp->kind] != NULL) {
        ftData_OnItemDropExt[fp->kind](gobj, arg2);
    }
    pl_8003EA08(fp->player_id, fp->x221F_b4);
    fp->item_gobj = NULL;
}

void ftCommon_8007E79C(HSD_GObj* gobj, s32 arg1)
{
    Fighter* fp = gobj->user_data;
    if (ftData_OnItemDrop[fp->kind] != NULL) {
        ftData_OnItemDrop[fp->kind](gobj, arg1);
    }
}

void ftCommon_8007E7E4(HSD_GObj* gobj, s32 arg1)
{
    Fighter* fp = gobj->user_data;
    if (ftData_OnItemPickup[fp->kind] != NULL) {
        ftData_OnItemPickup[fp->kind](gobj, arg1);
    }
}

void ftCommon_8007E82C(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    fp->x1984_heldItemSpec = NULL;
}

void it_8028B718(HSD_GObj*, float);
void it_8028B780(HSD_GObj*, float);
void it_8028B7E8(HSD_GObj*, float);
void it_8028B850(HSD_GObj*, float);
void it_8028B648(HSD_GObj*, float);
void it_8028B6B0(HSD_GObj*, float);
void it_8028B618(HSD_GObj*, float);
void it_802BDD40(HSD_GObj*, float);
void it_802BDDB4(HSD_GObj*, float);
static void (*parasol_table_1[7])(HSD_GObj*, float) = {
    it_8028B718, it_8028B780, it_8028B7E8, it_8028B850,
    it_8028B648, it_8028B6B0, it_8028B618,
};
static s32 parasol_table_2[7] = {
    7, 8, 9, 10, 5, 6, 4,
};
static void (*parasol_table_3[7])(HSD_GObj*, float) = {
    NULL, NULL, NULL, NULL, it_802BDD40, NULL, it_802BDDB4,
};
static s32 parasol_table_4[7] = {
    -1, -1, -1, -1, 1, -1, 2,
};

s32 it_8028B08C(void*, s32);

static const int FtParasol_None = -1;

void ftCommon_8007E83C(HSD_GObj* gobj, s32 arg1, float div)
{
    float val;

    Fighter* fp = gobj->user_data;

    HSD_ASSERT(1276, ftGetParasolStatus(gobj) != FtParasol_None);

    if (div == 0) {
        val = fp->frame_speed_mul;
    } else if (itGetKind(fp->item_gobj) == It_Kind_Parasol) {
        val = fp->frame_speed_mul *
              (it_8028B08C(fp->item_gobj, parasol_table_2[arg1]) / div);
    } else {
        val = fp->frame_speed_mul *
              (it_802BDA40(fp->item_gobj, parasol_table_4[arg1]) / div);
    }
    if (itGetKind(fp->item_gobj) == It_Kind_Parasol) {
        parasol_table_1[arg1](fp->item_gobj, val);
    } else {
        parasol_table_3[arg1](fp->item_gobj, val);
    }
}

/// @was{ftGetParasolStatus}
s32 ftGetParasolStatus(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->item_gobj != NULL && itGetKind(fp->item_gobj) == It_Kind_Parasol) {
        switch (it_8026B7A4(fp->item_gobj)) {
        case 7:
            return 0;
        case 8:
            return 1;
        case 9:
            return 2;
        case 10:
            return 3;
        case 5:
            return 4;
        case 6:
            return 5;
        case 4:
            return 6;
        }
    }
    if (fp->item_gobj != NULL &&
        itGetKind(fp->item_gobj) == It_Kind_Peach_Parasol)
    {
        switch (it_8026B7A4(fp->item_gobj)) {
        case 1:
            return 4;
        case 0:
        case 2:
            return 6;
        }
    }
    return FtParasol_None;
}

void ftCommon_8007EA90(Fighter* fp, s32 arg1)
{
    s32 temp_r31;
    float phi_f31;
    float phi_f30;
    Vec3 sp10;

    if (gm_8016B0B4() == 0) {
        return;
    }
    if (fp->dmg.kb_applied) {
        phi_f30 = fp->dmg.kb_applied;
        phi_f31 = ftCo_Damage_CalcAngle(fp, phi_f30);
        if (fp->dmg.facing_dir_1 > 0) {
            if (phi_f31 > M_PI) {
                phi_f31 = M_PI * 3 - phi_f31;
            } else {
                phi_f31 = M_PI - phi_f31;
            }
        }
        sp10.x = fp->dmg.x1854_collpos.x;
        sp10.y = fp->dmg.x1854_collpos.y;
        sp10.z = 0;
    } else {
        phi_f31 = M_PI / 2;
        phi_f30 = p_ftCommonData->x5C0;
        ftLib_800866DC(fp->gobj, &sp10);
    }
    temp_r31 = it_802E5F8C(fp->gobj, &sp10, arg1, 1, phi_f31, phi_f30);
    if (fp->dmg.x18c4_source_ply != 6) {
        Player_SetUnk98(fp->dmg.x18c4_source_ply,
                        temp_r31 + Player_GetUnk98(fp->dmg.x18c4_source_ply));
    }
}

void ftCommon_8007EBAC(Fighter* fp, u32 arg1, u32 arg2)
{
    if (Player_8003544C(fp->player_id, fp->x221F_b4) && !fp->x221F_b3 &&
        !fp->x2224_b2)
    {
        lb_80014574(fp->x618_player_id, arg1 + 2, arg1, arg2);
    }
}

void ftCommon_8007EC30(u32 arg0, u32 arg1)
{
    Fighter* fp;
    HSD_GObj* cur = HSD_GObj_Entities->fighters;

    u8 _[16];

    while (cur != NULL) {
        fp = cur->user_data;
        ftCommon_8007EBAC(fp, arg0, arg1);
        cur = cur->next;
    }
}

void ftCommon_8007ECD4(Fighter* fp, s32 arg1)
{
    if (Player_8003544C(fp->player_id, fp->x221F_b4)) {
        HSD_PadRumbleRemoveId(fp->x618_player_id, arg1 + 2);
    }
}

void ftCommon_8007ED2C(Fighter* fp)
{
    lb_800145C0(fp->x618_player_id);
}

void ftCommon_8007ED50(Fighter* fp, s32 arg1)
{
    float tmp = arg1 * p_ftCommonData->x138 + p_ftCommonData->x13C;
    s32 val2 = tmp;
    if ((s32) tmp < 1) {
        return;
    }
    ftCommon_8007EBAC(fp, 5, val2);
}

void ftCommon_8007EE0C(Fighter* fp, s32 arg1)
{
    float tmp = arg1 * p_ftCommonData->xEC + p_ftCommonData->xF0;
    s32 val2 = tmp;
    if ((s32) tmp < 1) {
        return;
    }
    ftCommon_8007EBAC(fp, 10, val2);
}

void ftCommon_8007EEC8(Fighter* fp, s32 arg1, s32 arg2)
{
    if (fp->item_gobj != NULL &&
        fp->item_gobj->classifier == HSD_GOBJ_CLASS_ITEM &&
        itGetKind(fp->item_gobj) == It_Kind_Sword)
    {
        float multiplier = 1.0 / 256;
        float tmp = arg2 * multiplier;
        it_80284FC4(fp->item_gobj, arg1, tmp);
    }
}

void ftCommon_8007EF5C(Fighter* fp, s32 arg1)
{
    if (fp->item_gobj != NULL &&
        fp->item_gobj->classifier == HSD_GOBJ_CLASS_ITEM &&
        itGetKind(fp->item_gobj) == It_Kind_Sword)
    {
        it_80285024(fp->item_gobj, arg1);
    }
}

void ftCommon_8007EFC0(Fighter* fp, u32 val)
{
    fp->x209A = val;
}

void ftCommon_8007EFC8(HSD_GObj* gobj, void (*arg1)(HSD_GObj*))
{
    Fighter* src = gobj->user_data;
    HSD_GObj* dst_gobj = Player_GetEntityAtIndex(src->player_id, 1);
    Fighter* dst = dst_gobj->user_data;
    s32 tmp_bit;

    u8 _[16];

    Player_SwapTransformedStates(src->player_id, src->x221F_b4, dst->x221F_b4);
    tmp_bit = src->x221F_b4;
    src->x221F_b4 = dst->x221F_b4;
    dst->x221F_b4 = tmp_bit;
    Fighter_UnkInitReset_80067C98(dst);
    _func_8007E2FC_inline(dst_gobj);
    dst->cur_pos = src->cur_pos;
    dst->prev_pos = src->prev_pos;
    dst->pos_delta = src->pos_delta;
    dst->facing_dir = src->facing_dir;
    dst->dmg.x1830_percent = src->dmg.x1830_percent;
    Player_SetHPByIndex(dst->player_id, dst->x221F_b4, dst->dmg.x1830_percent);
    dst->dmg.x18F0 = src->dmg.x18F0;
    dst->self_vel = src->self_vel;
    dst->ground_or_air = src->ground_or_air;
    dst->gr_vel = src->gr_vel;
    dst->xF0_ground_kb_vel = src->xF0_ground_kb_vel;
    dst->xF4_ground_attacker_shield_kb_vel =
        src->xF4_ground_attacker_shield_kb_vel;
    dst->xF8_playerNudgeVel.x = src->xF8_playerNudgeVel.x;
    dst->xF8_playerNudgeVel.y = src->xF8_playerNudgeVel.y;
    dst->input = src->input;
    dst->x670_timer_lstick_tilt_x = src->x670_timer_lstick_tilt_x;
    dst->x671_timer_lstick_tilt_y = src->x671_timer_lstick_tilt_y;
    dst->x672_input_timer_counter = src->x672_input_timer_counter;
    dst->x673 = src->x673;
    dst->x674 = src->x674;
    dst->x675 = src->x675;
    dst->x679_x = src->x679_x;
    dst->x67A_y = src->x67A_y;
    dst->x67B = src->x67B;
    dst->x685 = src->x685;
    dst->x686 = src->x686;
    dst->x687 = src->x687;
    dst->x688 = src->x688;
    dst->x689 = src->x689;
    dst->x68A = src->x68A;
    dst->x68B = src->x68B;
    dst->x67C = src->x67C;
    dst->x67D = src->x67D;
    dst->x67E = src->x67E;
    dst->x681 = src->x681;
    dst->x682 = src->x682;
    dst->x67F = src->x67F;
    dst->x680 = src->x680;
    dst->x683 = src->x683;
    dst->x684 = src->x684;
    dst->dmg.x18c4_source_ply = src->dmg.x18c4_source_ply;
    dst->dmg.x18C8 = src->dmg.x18C8;
    dst->x221F_b5 = src->x221F_b5;
    dst->dmg.x18CC = src->dmg.x18CC;
    dst->dmg.x18D0 = src->dmg.x18D0;
    dst->dmg.x18d4 = src->dmg.x18d4;
    dst->dmg.x18ec_instancehitby = src->dmg.x18ec_instancehitby;
    dst->x21FC_flag.u8 = src->x21FC_flag.u8;
    dst->x2221_b7 = src->x2221_b7;
    dst->x2221_b6 = src->x2221_b6;
    dst->x2221_b4 = src->x2221_b4;
    dst->x2221_b5 = src->x2221_b5;
    dst->x2104 = src->x2104;
    dst->dmg.x1910 = src->dmg.x1910;
    dst->x1968_jumpsUsed = src->x1968_jumpsUsed;
    dst->x1969_walljumpUsed = src->x1969_walljumpUsed;
    dst->shield_health = src->shield_health;
    dst->bury_timer_2 = src->bury_timer_2;
    dst->x2330 = src->x2330;
    dst->x2338 = src->x2338;
    dst->x2224_b2 = src->x2224_b2;
    if (src->x221D_b6) {
        ftColl_8007B7FC(dst, src->x2004);
        ftCo_800C0358(src, dst, 0x6B);
        ft_800880D8(src);
    } else {
        ftCo_800C0200(dst, 9);
    }
    if ((src->x198C = 2) && (src->x1990 != 0)) {
        ftColl_8007B760(dst_gobj, src->x1990);
    }
    dst->x2220_b5 = src->x2220_b5;
    dst->x2220_b6 = src->x2220_b6;
    dst->x2008 = src->x2008;
    ftLib_SetScale(dst_gobj, src->x34_scale.y);
    if (src->is_metal) {
        ftCo_800C8348(dst_gobj, src->metal_timer, src->metal_health);
        ftCo_800C8540(gobj);
    }
    if (src->x2226_b4) {
        if (!src->x2226_b7) {
            ftCo_800C88D4(dst_gobj, src->x2030, 0);
        }
        ftCo_800C8A64(gobj);
    }
    dst->x221E_b4 = src->x221E_b4;
    if (src->x197C != NULL) {
        it_8026B9A8(src->x197C, dst_gobj, dst->ft_data->x8->x12);
        it_802950D4(src->x197C, 0);
        ftCommon_8007F948(dst_gobj, src->x197C, src->x2014);
        ftCommon_8007FA00(gobj);
    } else {
        dst->x197C = NULL;
    }
    if (src->x1980 != NULL) {
        it_8026B9A8(src->x1980, dst_gobj, dst->ft_data->x8->x12);
        ftCommon_8007FE84(dst_gobj, src->x1980, src->x2018, src->x2024);
        ftCommon_8007FDA0(gobj);
    } else {
        dst->x1980 = NULL;
    }
    ftCo_800D105C(dst_gobj);
    ftCamera_80076064(dst);
    ft_800849EC(src, dst);
    ft_80081C88(dst_gobj, src->x34_scale.y);
    if (src->item_gobj != NULL) {
        dst->item_gobj = src->item_gobj;
        dst->x221E_b3 = src->x221E_b3;
        ftpickupitem_80094818(dst_gobj, 1);
        it_8026B9A8(src->item_gobj, dst_gobj, dst->ft_data->x8->x10);
    }
    un_80322314();
    ftMaterial_800BFD04(gobj);
    arg1(dst_gobj);
}

extern void (*ftData_OnItemInvisible[])(HSD_GObj*);
extern void (*ftData_OnItemVisible[])(HSD_GObj*);
extern void (*ftData_OnKnockbackEnter[])(HSD_GObj*);
extern void (*ftData_OnKnockbackExit[])(HSD_GObj*);

void ftCommon_8007F578(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->item_gobj == NULL) {
        return;
    }
    if (ftData_OnItemInvisible[fp->kind] != NULL) {
        ftData_OnItemInvisible[fp->kind](gobj);
    }
}

void ftCommon_8007F5CC(Item_GObj* gobj, bool arg1)
{
    Fighter* fp = gobj->user_data;
    Item_GObj* item = fp->item_gobj;

    PAD_STACK(8);

    if (item != NULL && fp->x221E_b3 != arg1) {
        if (!arg1) {
            ftCommon_8007F578(gobj);
        } else if (item != NULL) {
            if (ftData_OnItemVisible[fp->kind] != NULL) {
                ftData_OnItemVisible[fp->kind](gobj);
            }
        }
    }
    fp->x221E_b3 = arg1;
}

float ftCommon_GetModelScale(Fighter* fp)
{
    return fp->x34_scale.y * fp->co_attrs.model_scaling;
}

void ftCommon_8007F6A4(Fighter* fp, HSD_JObj* jobj)
{
    Vec3 scale;
    float val = 1.0f / fp->ft_data->x0->model_scaling;
    scale.z = val;
    scale.y = val;
    scale.x = val;
    HSD_JObjSetScale(jobj, &scale);
}

void ftCommon_8007F76C(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    fp->gr_vel = fp->facing_dir * ABS(fp->gr_vel);
    fp->self_vel.x = fp->facing_dir * ABS(fp->self_vel.x);
}

void ftCommon_8007F7B4(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    fp->gr_vel = -fp->facing_dir * ABS(fp->gr_vel);
    fp->self_vel.x = -fp->facing_dir * ABS(fp->self_vel.x);
}

MtxPtr ftCommon_8007F804(Fighter* fp)
{
    if (fp->x34_scale.z != 1) {
        return fp->x44_mtx;
    }
    return NULL;
}

void ftCommon_8007F824(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (ftData_OnKnockbackEnter[fp->kind] != NULL) {
        ftData_OnKnockbackEnter[fp->kind](gobj);
    }
}

void ftCommon_8007F86C(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (ftData_OnKnockbackExit[fp->kind] != NULL) {
        ftData_OnKnockbackExit[fp->kind](gobj);
    }
}

void ftCommon_8007F8B4(Fighter* fp, Vec3* v)
{
    v->x = fp->cur_pos.x + fp->xD4_unk_vel.x;
    v->y = fp->cur_pos.y + fp->xD4_unk_vel.y;
    v->z = fp->cur_pos.z + fp->xD4_unk_vel.z;
}

extern void (*ftData_UnkMotionStates2[])(HSD_GObj*);

void ftCommon_8007F8E8(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->x197C == NULL || fp->x1980 == NULL) {
        if (ftData_UnkMotionStates2[fp->kind] != NULL) {
            ftData_UnkMotionStates2[fp->kind](gobj);
        }
    }
}

extern void (*ftData_UnkMotionStates1[])(HSD_GObj*);

inline void _func_8007F948_inline(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->x197C == NULL || fp->x1980 == NULL) {
        if (ftData_UnkMotionStates1[fp->kind] != NULL) {
            ftData_UnkMotionStates1[fp->kind](gobj);
        }
    }
}

void ftCommon_8007F948(HSD_GObj* gobj, HSD_GObj* arg1, s32 arg2)
{
    Fighter* fp = gobj->user_data;
    fp->x197C = arg1;
    fp->x2014 = arg2;
    _func_8007F948_inline(gobj);
}

void ftCommon_8007F9B4(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    fp->x197C = NULL;
    ftCo_800D105C(gobj);
    ft_80081C88(gobj, fp->x34_scale.y);
}

void ftCommon_8007FA00(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    Vec3* vec = &fp->co_attrs.x114;

    u8 _[8];

    it_80294EB0(fp->x197C, &vec[1], &vec[0]);
    it_80294E78(fp->x197C, fp->x34_scale.y * vec[2].x);
}

void ftCommon_8007FA58(Fighter_GObj* gobj, Item_GObj* arg1)
{
    Fighter* fp = gobj->user_data;
    Vec3 vec;

    /// @todo This is an inline.
    {
        Fighter* fp2 = fp;

        u8 _[24];

        if (fp2->x197C != NULL) {
            fp->x2014 = it_8026B54C(arg1);
            ft_PlaySFX(fp, 0x117, 0x7F, 0x40);
            ftCommon_8007EBAC(fp, 0x10, 0);
            Item_8026A8EC(arg1);
            return;
        }
    }

    vec = ftCo_803B74A0;
    it_8026BD0C(arg1);
    Item_8026ABD8(arg1, &vec, 0);
    Item_8026AB54(arg1, gobj, fp->ft_data->x8->x12);
    ftCommon_8007F948(gobj, arg1, it_8026B54C(arg1));
    ftCo_800D105C(gobj);
    ft_80081C88(gobj, fp->x34_scale.y);
    ft_PlaySFX(fp, 0x117, 0x7F, 0x40);
    ftCommon_8007EBAC(fp, 0x10, 0);
    it_8026BCF4(arg1);
    ftCommon_8007FA00(gobj);
}

void ftCommon_8007FC7C(HSD_GObj* gobj, float arg8)
{
    HSD_GObj* item_gobj;
    Fighter* fp;
    s32 sp20;

    u8 _[4];

    fp = gobj->user_data;
    sp20 = arg8 * p_ftCommonData->x704;
    if (fp->x1980 != NULL) {
        fp->x2018 += sp20;
        if (fp->x2018 > p_ftCommonData->x700) {
            fp->x2018 = p_ftCommonData->x700;
        }
        sp20 = fp->x2024;
        fp->x2024 = sp20 + arg8;
        ftCommon_8007FDA0(gobj);
    } else {
        item_gobj = it_8029A748(gobj, &fp->cur_pos, fp->ft_data->x8->x12,
                                fp->facing_dir);
        if (item_gobj != NULL) {
            ftCommon_8007FE84(gobj, item_gobj, sp20, arg8);
            ftCommon_8007FDA0(gobj);
        }
    }
    ft_PlaySFX(fp, 0x11F, 0x7F, 0x40);
}

inline float fminf(float a, float b)
{
    float result = a;
    if (a > b) {
        result = b;
    }
    return result;
}

void ftCommon_8007FDA0(HSD_GObj* gobj)
{
    Vec3 sp20;
    Fighter* fp;
    float temp_f1;
    Vec3* temp_r30;
    float phi_f31;

    u8 _[16];

    fp = gobj->user_data;
    temp_r30 = &fp->co_attrs.x130;
    phi_f31 = fminf(p_ftCommonData->x710 * fp->x2024 + p_ftCommonData->x708,
                    p_ftCommonData->x70C);
    temp_f1 = 1.0f / phi_f31;
    sp20 = *temp_r30;
    sp20.x *= temp_f1;
    sp20.y *= temp_f1;
    sp20.z *= temp_f1;
    it_8029A8F4(fp->x1980, &sp20);
    it_8029A89C(fp->x1980, phi_f31 * temp_r30[1].x * fp->x34_scale.y);
}

void ftCommon_8007FE84(HSD_GObj* gobj, HSD_GObj* item_gobj, s32 arg2,
                       float arg3)
{
    u8 _[8];

    Fighter* fp = gobj->user_data;
    fp->x1980 = item_gobj;
    fp->x2018 = arg2;
    fp->x201C = p_ftCommonData->x6F8;
    fp->x2024 = arg3;
    fp->x2021 = 0;
    fp->x2020 = 0;
    ftCommon_8007EBAC(fp, 2, 0);
    _func_8007F948_inline(gobj);
}

void ftCommon_8007FF74(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    fp->x1980 = NULL;
    ftCommon_8007ECD4(fp, 2);
    pl_80040460(fp->player_id, fp->x221F_b4);
}

bool ftCommon_8007FFD8(Fighter* fp, float arg8)
{
    s32 phi_r31;
    s8 b0, b1;
    phi_r31 = false;
    if (fp->input.x668 & (HSD_PAD_AB | HSD_PAD_XY | HSD_PAD_LR)) {
        fp->x2018 -= arg8;
        phi_r31 = true;
    }
    b0 = fp->x2020;
    b1 = fp->x2021;
    if (fp->input.lstick.x < -p_ftCommonData->x308) {
        fp->x2020 = -1;
    }
    if (fp->input.lstick.x > p_ftCommonData->x308) {
        fp->x2020 = 1;
    }
    if (fp->input.lstick.y < -p_ftCommonData->x308) {
        fp->x2021 = -1;
    }
    if (fp->input.lstick.y > p_ftCommonData->x308) {
        fp->x2021 = 1;
    }
    if (b0 != fp->x2020 || b1 != fp->x2021) {
        fp->x2018 = fp->x2018 - arg8;
        phi_r31 = true;
    }
    pl_800402D0(fp->player_id, fp->x221F_b4, phi_r31);
    return phi_r31;
}

bool ftCommon_80080144(Fighter* fp)
{
    int kind = fp->kind;
    if ((kind == FTKIND_POPO || kind == FTKIND_NANA) &&
        fp->x619_costume_id >= 2)
    {
        return true;
    }
    return false;
}

// https://decomp.me/scratch/Jjkwx
void ftCommon_80080174(Fighter* fp)
{
    float phi_f2;
    float phi_f3;
    Vec3* v;

    u8 _[16];

    if (fp->x197C != NULL) {
        it_80294E78(fp->x197C, fp->x34_scale.y * fp->co_attrs.x12C);
    }
    if (fp->x1980 != NULL) {
        v = &fp->co_attrs.x130;
        if ((phi_f2 = p_ftCommonData->x710 * fp->x2024 +
                      p_ftCommonData->x708) > (phi_f3 = p_ftCommonData->x70C))
        {
            phi_f2 = phi_f3;
        }
        it_8029A89C(fp->x1980, phi_f2 * v[1].x * fp->x34_scale.y);
    }
}

void ftCommon_8008021C(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    Vec2 shift;
    Vec2* result;

    u8 _[4];

    fp->dmg.x18BC = 0;
    fp->dmg.x18B8 = 0;
    if (ftCo_80090690(fp, &shift) != NULL) {
        fp->dmg.x18B8 += shift.x;
        fp->dmg.x18BC += shift.y;
    }
    if (fp->x2224_b5) {
        Vec2* temp_r3 = &Fighter_804D652C->x0[fp->x1A52];
        shift.x = temp_r3->x;
        shift.y = temp_r3->y;
        result = &shift;
    } else {
        result = NULL;
    }
    if (result != NULL) {
        fp->dmg.x18B8 += shift.x;
        fp->dmg.x18BC += shift.y;
    }
    if (ftCo_800DEEE8(fp, &shift) != NULL) {
        fp->dmg.x18B8 += shift.x;
        fp->dmg.x18BC += shift.y;
    }
}

void ftCommon_8008031C(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if ((ABS(fp->input.lstick.x) >= p_ftCommonData->x7B8 &&
         fp->x679_x < p_ftCommonData->x7C0) ||
        (ABS(fp->input.lstick.y) >= p_ftCommonData->x7B8 &&
         fp->x67A_y < p_ftCommonData->x7C0))
    {
        Player_UpdateJoystickCountByIndex((s32) fp->player_id, fp->x221F_b4);
        fp->x67A_y = 0xFE;
        fp->x679_x = 0xFE;
    }
    if (ABS(fp->input.x650) >= p_ftCommonData->x7BC) {
        if (fp->x67B < p_ftCommonData->x7C0) {
            Player_UpdateJoystickCountByIndex((s32) fp->player_id,
                                              fp->x221F_b4);
            fp->x67B = 0xFE;
        }
    }
}

void ftCommon_80080460(Fighter* fp)
{
    fp->x2225_b6 = true;
}

void ftCommon_80080474(Fighter* fp)
{
    fp->x2225_b6 = fp->x2225_b5;
}

void ftCommon_80080484(Fighter* fp)
{
    if (fp->smash_attrs.x2138_smashSinceHitbox == -1) {
        fp->smash_attrs.x2138_smashSinceHitbox = 0;
    }
}

void ftCommon_800804A0(Fighter* fp, float arg8)
{
    float temp_f1;
    float phi_f31 = arg8;
    if ((temp_f1 = ft_GetGroundFrictionMultiplier(fp)) < 1) {
        phi_f31 *= temp_f1;
    }
    fp->xE8_ground_accel_2 = phi_f31;
}

float ftCommon_800804EC(Fighter* fp)
{
    return fp->x40 * fp->x34_scale.x;
}

void ftCommon_800804FC(Fighter* fp)
{
    if (fp->ground_or_air == GA_Ground) {
        fp->dmg.x18c4_source_ply = 6;
        fp->dmg.x18C8 = -1;
    }
}
