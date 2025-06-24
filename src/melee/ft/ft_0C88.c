#include <placeholder.h>

#include "ft/forward.h"
#include "ftCommon/forward.h"

#include "ft/ft_0C88.h"

#include "math.h"
#include "platform.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0892.h"
#include "ft/ft_0CEE.h"
#include "ft/ft_0D14.h"
#include "ft/ftcommon.h"
#include "ft/ftlib.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCommon/ftCo_AirCatch.h"
#include "ftCommon/ftCo_AttackAir.h"
#include "ftCommon/ftCo_AttackDash.h"
#include "ftCommon/ftCo_AttackS4.h"
#include "ftCommon/ftCo_DamageFall.h"
#include "ftCommon/ftCo_Escape.h"
#include "ftCommon/ftCo_EscapeAir.h"
#include "ftCommon/ftCo_Guard.h"
#include "ftCommon/ftCo_HammerFall.h"
#include "ftCommon/ftCo_HammerJump.h"
#include "ftCommon/ftCo_HammerWait.h"
#include "ftCommon/ftCo_ItemThrow.h"
#include "ftCommon/ftCo_SpecialAir.h"
#include "ftCommon/ftCo_SpecialS.h"
#include "ftCrazyHand/ftCh_Init.h"
#include "ftMasterHand/ftMh_Wait1_2.h"
#include "ftPeach/ftPe_Float.h"

#include <baselib/gobj.h>

/* 0C9D94 */ static void ftCo_TurnRun_Enter(Fighter_GObj* gobj,
                                            float anim_start);
/* 0CA644 */ static bool fn_800CA644(ftCo_GObj* gobj);
/* 0CABC4 */ static bool fn_800CABC4(ftCo_GObj* gobj);
/* 0CAC18 */ static void ftCo_RunBrake_Enter(ftCo_GObj* gobj);
/* 0CAF78 */ static bool fn_800CAF78(ftCo_GObj* gobj);
/* 0CB4E0 */ static void ftCo_KneeBend_Enter(ftCo_GObj* gobj, int arg1);
/* 0CC654 */ static void ftNs_JumpAerial_Phys_Cb(ftCo_GObj* gobj);

/// #ftCo_800C884C

/// #ftCo_800C88A0

/// #ftCo_800C88D4

/// #ftCo_800C89A0

/// #ftCo_800C8A64

/// #ftCo_800C8AF0

void fn_800C8B1C(Fighter_GObj* gobj)
{
    GET_FIGHTER(gobj)->smash_attrs.x2134_vibrateFrame = 0;
}

/// #ftCo_800C8B2C

void ftCo_800C8B60(Fighter* fp, int arg1, s8 arg2)
{
    fp->x2226_b5 = arg1;
    fp->smash_attrs.x2134_vibrateFrame = arg2;
}

/// #ftCo_800C8B74

/// #ftCo_DownSpot_Anim

void ftCo_DownSpot_IASA(Fighter_GObj* gobj) {}

/// #ftCo_DownSpot_Phys

/// #ftCo_DownSpot_Coll

/// #ftCo_800C8C84

/// #ftCo_800C8D00

/// #fn_800C8E40

/// #fn_800C8E74

/// #ftCo_800C8F6C

/// #ftCo_800C8FC4

/// #ftCo_800C9034

/// #fn_800C9058

/// #ftCo_800C9078

/// #fn_800C9198

/// #ftCo_Barrel_Anim

/// #ftCo_Barrel_IASA

void ftCo_Barrel_Phys(Fighter_GObj* gobj) {}

void ftCo_Barrel_Coll(Fighter_GObj* gobj) {}

/// #fn_800C9264

/// #fn_800C9290

/// #ftCo_800C92E4

/// #ftCo_Walk_CheckInput

/// #ftCo_800C94B4

/// #fn_800C9528

/// #ftCo_Walk_Anim

/// #ftCo_Walk_IASA

/// #ftCo_Walk_Phys

/// #ftCo_Walk_Coll

/// #ftCo_800C97A8

/// #ftCo_Turn_CheckInput

/// #ftCo_800C9840

/// #fn_800C98AC

/// #ftCo_800C9924

/// #ftCo_Turn_Anim

/// #ftCo_Turn_IASA

/// #ftCo_Turn_Phys

/// #ftCo_Turn_Coll

/// #fn_800C9C2C

void fn_800C9C74(Fighter_GObj* gobj)
{
    Fighter* fp_r7 = GET_FIGHTER(gobj);
    float facing = fp_r7->facing_dir;
    PAD_STACK(1);

    fp_r7->mv.co.turn.x0 = 0;
    fp_r7->mv.co.turn.x18 = 0;
    fp_r7->mv.co.turn.x4 = -fp_r7->facing_dir;
    fp_r7->mv.co.turn.x10 = 0.0F;
    fp_r7->mv.co.turn.x8 = facing;
    fp_r7->mv.co.turn.x1C = 0;

    Fighter_ChangeMotionState(gobj, ftCo_MS_Turn, Ft_MF_None, 0.0F, 1.0F, 0.0F,
                              NULL);
    ftAnim_8006EBA4(gobj);
}

bool fn_800C9CEC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->input.lstick.x * fp->facing_dir <=
        p_ftCommonData->x38_someLStickXThreshold)
    {
        ftCo_TurnRun_Enter(gobj, fp->cur_anim_frame);
        return true;
    }
    return false;
}

void ftCo_TurnRun_Enter(Fighter_GObj* gobj, float anim_start)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[1] = 0;
    fp->mv.co.turnrun.accel_mul = fp->facing_dir;
    Fighter_ChangeMotionState(gobj, ftCo_MS_TurnRun, Ft_MF_SkipAnimVel,
                              anim_start, 1.0F, 0.0F, NULL);
    fp->mv.co.turnrun.x14 = 0;
    if (fp->x197C != NULL) {
        ft_80088148(fp, 0x119, 0x7F, 0x40);
    }
}

#pragma push
#pragma dont_inline on
bool fn_800C9D40(Fighter_GObj* gobj)
{
    // We can't use GET_FIGHTER due to dont_inline
    Fighter* fp = gobj->user_data;

    float facing = fp->facing_dir;
    float threshold = p_ftCommonData->x38_someLStickXThreshold;
    float lsx = fp->input.lstick.x;

    if ((lsx * facing) <= threshold) {
        ftCo_TurnRun_Enter(gobj, 0.0F);
        return true;
    }
    return false;
}
#pragma pop

static inline void getAccelAndTarget(Fighter* fp, float* accel,
                                     float* target_vel)
{
    ftCo_DatAttrs* co_attrs = &fp->co_attrs;
    *accel = fp->input.lstick.x * fp->co_attrs.dash_run_acceleration_a;
    *accel += fp->input.lstick.x > 0 ? +co_attrs->dash_run_acceleration_b
                                     : -co_attrs->dash_run_acceleration_b;
    *target_vel = fp->input.lstick.x * co_attrs->dash_run_terminal_velocity;
}

void ftCo_TurnRun_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(8);

    if (fp->cmd_vars[1] != 0) {
        if (fp->mv.co.turnrun.x14 == 0) {
            ftAnim_SetAnimRate(gobj, 0.0F);
            fp->mv.co.turnrun.x14 = 1;
        } else {
            if ((fp->mv.co.walk.middle_anim_frame * fp->gr_vel) <= 0.01F) {
                ftAnim_SetAnimRate(gobj, 1.0F);
                fp->cmd_vars[1] = 0;
                fp->facing_dir = -fp->facing_dir;
            }
        }
    }
    if (!ftAnim_IsFramesRemaining(gobj) && !fn_800CA644(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftCo_TurnRun_IASA(Fighter_GObj* gobj)
{
    RETURN_IF(fn_800CAF78(gobj));
}

void ftCo_TurnRun_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_DatAttrs* co_attrs = &fp->co_attrs;
    float accel, target_vel;
    getAccelAndTarget(fp, &accel, &target_vel);

    if (!target_vel) {
        ftCommon_8007C930(fp, co_attrs->gr_friction *
                                  p_ftCommonData->x60_someFrictionMul);
    } else if (fp->mv.co.turnrun.accel_mul * accel < 0) {
        if (accel > 0) {
            if (fp->gr_vel + accel > target_vel) {
                accel -= co_attrs->gr_friction *
                         p_ftCommonData->x60_someFrictionMul;
                if (fp->gr_vel + accel < target_vel) {
                    accel = target_vel - fp->gr_vel;
                }
            }
        } else {
            if (fp->gr_vel + accel < target_vel) {
                accel += co_attrs->gr_friction *
                         p_ftCommonData->x60_someFrictionMul;
                if (fp->gr_vel + accel > target_vel) {
                    accel = target_vel - fp->gr_vel;
                }
            }
        }
        fp->xE4_ground_accel_1 = accel;
    } else {
        ftCommon_8007C930(fp, co_attrs->gr_friction *
                                  p_ftCommonData->x60_someFrictionMul);
    }
    ftCommon_8007CB74(gobj);
}

void ftCo_TurnRun_Coll(Fighter_GObj* gobj)
{
    s32 env_flags;
    bool var_r4;

    if (!ft_800827A0(gobj)) {
        ftCo_800CC730(gobj);
        return;
    }
    var_r4 = true;
    env_flags = GET_FIGHTER(gobj)->coll_data.env_flags;
    if (!(env_flags & MPCOLL_FLAGS_B20) && !(env_flags & MPCOLL_FLAGS_B21)) {
        var_r4 = false;
    }
    if (var_r4) {
        ftCommon_8007E2FC(gobj);
    }
}

#pragma push
#pragma dont_inline on
bool ftCo_Dash_CheckInput(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    float lsx_abs = fp->input.lstick.x;
    if (lsx_abs < 0.0F) {
        lsx_abs = -lsx_abs;
    }

    if ((lsx_abs >= p_ftCommonData->x3C) &&
        ((int) fp->x670_timer_lstick_tilt_x < p_ftCommonData->x40))
    {
        if ((fp->input.lstick.x * fp->facing_dir) < 0.0F) {
            fn_800C9C74(gobj);
        } else {
            ftCo_Dash_Enter(gobj, 1);
        }
        return true;
    }
    return false;
}
#pragma pop

#pragma push
#pragma dont_inline on
static inline bool ftCo_Dash_CheckInput_inline(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    float var_f1 = fp->input.lstick.x;
    if (var_f1 < 0.0F) {
        var_f1 = -var_f1;
    }

    if ((var_f1 >= p_ftCommonData->x3C) &&
        ((s32) fp->x670_timer_lstick_tilt_x < (s32) p_ftCommonData->x40))
    {
        if ((fp->input.lstick.x * fp->facing_dir) < 0.0F) {
            fn_800C9C74(gobj);
        } else {
            ftCo_Dash_Enter(gobj, 1);
        }
        return true;
    }
    return false;
}
#pragma pop

void ftCo_Dash_Enter(Fighter_GObj* gobj, int arg1)
{
    Fighter* fp = GET_FIGHTER(gobj);
    f32 init_vel;
    PAD_STACK(8);

    fp->cmd_vars[0] = 0;

    Fighter_ChangeMotionState(gobj, ftCo_MS_Dash, Ft_MF_None, 0.0F, 1.0F, 0.0F,
                              NULL);
    ftAnim_8006EBA4(gobj);
    fp->x670_timer_lstick_tilt_x = 0xFE;
    init_vel = fp->facing_dir * fp->co_attrs.dash_initial_velocity;
    if ((fp->gr_vel * fp->facing_dir) < 0.0F) {
        fp->mv.co.dash.x0 = init_vel;
    } else {
        fp->mv.co.dash.x0 = init_vel - fp->gr_vel;
    }
    ftCommon_800804A0(fp, fp->mv.ca.specials.grav);
    fp->mv.co.dash.x4 = arg1;
    if (fp->x197C != NULL) {
        ft_80088148(fp, 0x118, 0x7F, 0x40);
    }
}

void ftCo_Dash_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftCo_Dash_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if ((fp->mv.co.dash.x4 != 0) &&
        (fp->cur_anim_frame <= p_ftCommonData->x44))
    {
        if (!ftCo_SpecialS_CheckInput(gobj)) {
            if ((fp->item_gobj != NULL) && ftCo_80094E54(fp)) {
                ftCo_800957F4(gobj, ftCo_MS_LightThrowF4);
            } else if (ftCo_800D8A38(gobj)) {
                return;
            } else {
                if (!ftCo_AttackS4_8008C114(gobj)) {
                    if (!(fp->cur_anim_frame <= p_ftCommonData->x48 &&
                          ftCo_80099264(gobj)))
                    {
                        goto block_42;
                    }
                }
            }
        }
    } else if (fp->cur_anim_frame <= p_ftCommonData->x4C) {
        if (!ftCo_SpecialS_CheckInput(gobj)) {
            RETURN_IF(ftCo_800D8A38(gobj));
            if (ftCo_AttackDash_CheckInput(gobj)) {
                ftCo_AttackDash_SetMv0(gobj);
                return;
            }
            if (!(fp->input.lstick.x * fp->facing_dir < 0.0F) ||
                !ftCo_Dash_CheckInput_inline(gobj))
            {
                if (ftCo_80091AD8(gobj, (s32) (p_ftCommonData->x4C -
                                               fp->cur_anim_frame)))
                {
                } else {
                    goto block_42;
                }
            }
        }
    } else {
        RETURN_IF(ftCo_800D8A38(gobj));
        if (!ftCo_Dash_CheckInput_inline(gobj)) {
            if (ftCo_80091A4C(gobj)) {
                ftCo_80091B9C(gobj);
            } else {
            block_42:
                if (!ftCo_800DE9D8(gobj)) {
                    RETURN_IF(fn_800CAF78(gobj));
                    RETURN_IF(!fp->cmd_vars[0]);
                    RETURN_IF(fn_800CA5F0(gobj));
                    return;
                }
            }
        }
    }

    {
        float friction = ft_GetGroundFrictionMultiplier(fp);
        float temp_f0 = fp->gr_vel * p_ftCommonData->x54;
        fp->gr_vel += -temp_f0 * friction;
    }
}

void ftCo_Dash_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(1);

    if (fp->mv.co.dash.x0) {
        fp->mv.co.dash.x0 = 0;
    } else {
        ftCo_DatAttrs* attrs = &fp->co_attrs;
        float accel, target_vel;
        getAccelAndTarget(fp, &accel, &target_vel);
        ftCommon_8007C98C(fp, accel, target_vel,
                          attrs->gr_friction *
                              p_ftCommonData->x60_someFrictionMul);
    }
    ftCommon_8007CB74(gobj);
}

void ftCo_Dash_Coll(Fighter_GObj* gobj)
{
    ft_800844EC();
}

bool fn_800CA5F0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->input.lstick.x * fp->facing_dir >=
        p_ftCommonData->x58_someLStickXThreshold)
    {
        ftCo_Run_Enter(gobj, 0.0F);
        return true;
    }
    return false;
}

bool fn_800CA644(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if ((fp->input.lstick.x * fp->facing_dir) >=
        p_ftCommonData->x58_someLStickXThreshold)
    {
        ftCo_Run_Enter(gobj, p_ftCommonData->x430);
        return true;
    }
    return false;
}

bool fn_800CA698(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->input.lstick.x * fp->facing_dir >=
        p_ftCommonData->x58_someLStickXThreshold)
    {
        ftCo_Run_Enter_Full(gobj, 0.0F, fp->cur_anim_frame,
                            fp->frame_speed_mul);
        return true;
    }
    return false;
}

void ftCo_Run_Enter(Fighter_GObj* gobj, float arg0)
{
    ftCo_Run_Enter_Full(gobj, arg0, 0.0F, 1.0F);
}

void ftCo_Run_Enter_Full(Fighter_GObj* gobj, float arg0, float anim_start,
                         float anim_speed)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftCo_MS_Run, Ft_MF_None, anim_start,
                              anim_speed, 0.0F, NULL);
    fp->mv.co.run.x0 = arg0;
    fp->mv.co.run.x4 = fp->gr_vel;
}

void ftCo_Run_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    f32 vel;
    f32 anim_rate;
    PAD_STACK(1);

    if (ft_GetGroundFrictionMultiplier(fp) < 1.0F) {
        vel = fp->mv.co.run.x4;
    } else {
        vel = fp->gr_vel;
    }

    if (vel * fp->facing_dir <= 0.0F) {
        anim_rate = 0.0F;
    } else {
        anim_rate = fabs_inline(vel) / fp->co_attrs.run_animation_scaling;
    }

    ftAnim_SetAnimRate(gobj, anim_rate);
    if (fp->mv.co.run.x0 > 0.0F) {
        fp->mv.co.run.x0 -= 1.0F;
    }
}

void ftCo_Run_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    RETURN_IF(ftCo_SpecialS_CheckInput(gobj));
    RETURN_IF(ftCo_Attack100_CheckInput(gobj));
    RETURN_IF(ftCo_800D6824(gobj));
    RETURN_IF(ftCo_800D68C0(gobj));
    RETURN_IF(ftCo_800D8A38(gobj));

    if (ftCo_AttackDash_CheckInput(gobj)) {
        ftCo_AttackDash_SetMv0(gobj);
        return;
    }

    if (ftCo_80091A4C(gobj)) {
        ftCo_80091B90(gobj, p_ftCommonData->x410);
        ftCo_80091B9C(gobj);
        return;
    }

    RETURN_IF(ftCo_800DE9D8(gobj));
    RETURN_IF(fn_800CAF78(gobj));

    RETURN_IF((fp->mv.co.run.x0 <= 0.0F) && fn_800C9D40(gobj));
    RETURN_IF(!(fp->mv.co.run.x0 <= 0.0F));
    RETURN_IF(fn_800CABC4(gobj));
}

void ftCo_Run_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_DatAttrs* attrs = &fp->co_attrs;
    float accel, target_vel;
    getAccelAndTarget(fp, &accel, &target_vel);
    if (target_vel) {
        float gr_frac = fp->gr_vel / target_vel;
        if ((gr_frac > 0.0F) && (gr_frac < 1.0F)) {
            accel *= (1.0F - gr_frac) * p_ftCommonData->x5C;
        }
    }
    fp->mv.co.run.x4 = target_vel * p_ftCommonData->x440;
    ftCommon_8007C98C(fp, accel, target_vel,
                      attrs->gr_friction *
                          p_ftCommonData->x60_someFrictionMul);
    ftCommon_8007CB74(gobj);
}

void ftCo_Run_Coll(Fighter_GObj* gobj)
{
    ft_800844EC();
}

#pragma push
#pragma dont_inline on
void ftCo_RunDirect_Anim(Fighter_GObj* gobj)
{
    ftCo_Run_Anim(gobj);
}
#pragma pop

#pragma push
#pragma dont_inline on
void ftCo_RunDirect_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    RETURN_IF(ftCo_SpecialS_CheckInput(gobj));
    RETURN_IF(ftCo_Attack100_CheckInput(gobj));
    RETURN_IF(ftCo_800D6824(gobj));
    RETURN_IF(ftCo_800D68C0(gobj));
    RETURN_IF(ftCo_800D8A38(gobj));

    if (ftCo_AttackDash_CheckInput(gobj)) {
        ftCo_AttackDash_SetMv0(gobj);
        return;
    }

    if (ftCo_80091A4C(gobj)) {
        ftCo_80091B90(gobj, p_ftCommonData->x410);
        ftCo_80091B9C(gobj);
        return;
    }

    RETURN_IF(ftCo_800DE9D8(gobj));
    RETURN_IF(fn_800CAF78(gobj));
    RETURN_IF(fp->mv.ca.specials.grav <= 0.0F && fn_800CA698(gobj));
    RETURN_IF(ft_8008A244(gobj));
}
#pragma pop

#pragma push
#pragma dont_inline on
void ftCo_RunDirect_Phys(Fighter_GObj* gobj)
{
    ftCo_Run_Phys(gobj);
}
#pragma pop

#pragma push
#pragma dont_inline on
void ftCo_RunDirect_Coll(Fighter_GObj* gobj)
{
    ftCo_Run_Coll(gobj);
}
#pragma pop

bool fn_800CABC4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    float lsx_abs = fp->input.lstick.x;
    if (lsx_abs < 0.0F) {
        lsx_abs = -lsx_abs;
    }
    if (lsx_abs < p_ftCommonData->x58_someLStickXThreshold) {
        ftCo_RunBrake_Enter(gobj);
        return true;
    }
    return false;
}

void ftCo_RunBrake_Enter(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(1);

    fp->cmd_vars[0] = 0;
    fp->cmd_vars[1] = 0;
    Fighter_ChangeMotionState(gobj, ftCo_MS_RunBrake, Ft_MF_None, 0.0F, 1.0F,
                              0.0F, NULL);
    fp->mv.co.runbrake.x0 = 0;
    fp->mv.co.runbrake.x4 = fp->co_attrs.max_run_brake_frames;
    if (fp->x197C != NULL) {
        ft_80088148(fp, 0x119, 0x7F, 0x40);
    }
}

void ftCo_RunBrake_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->cmd_vars[1] != 0) {
        float gr_vel;
        float maybe_max_vel = p_ftCommonData->x42C;
        if (fp->mv.co.runbrake.x0 == 0) {
            gr_vel = fabs_inline(fp->gr_vel);
            if (gr_vel >= maybe_max_vel) {
                ftAnim_SetAnimRate(gobj, 0.0F);
                fp->mv.co.runbrake.x0 = 1;
            }
        } else {
            gr_vel = fabs_inline(fp->gr_vel);
            if (gr_vel <= maybe_max_vel) {
                ftAnim_SetAnimRate(gobj, 1.0F);
                fp->cmd_vars[1] = 0;
            }
        }
    }

    if (fp->mv.co.runbrake.x4) {
        fp->mv.co.runbrake.x4 -= 1.0F;
        if (fp->mv.co.runbrake.x4 < 0.0F) {
            fp->mv.co.runbrake.x4 = 0.0F;
        }
    }

    if (!ftAnim_IsFramesRemaining(gobj) || (!fp->mv.co.runbrake.x4)) {
        ft_8008A2BC(gobj);
    }
}

#pragma push
#pragma dont_inline on
void ftCo_RunBrake_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    RETURN_IF(fn_800CAF78(gobj));
    RETURN_IF(fp->cmd_vars[0] && fn_800C9CEC(gobj));
    RETURN_IF(ftCo_800D5FB0(gobj));
}
#pragma pop

void ftCo_RunBrake_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007C930(fp, p_ftCommonData->x60_someFrictionMul *
                              fp->co_attrs.gr_friction);
    ftCommon_8007CB74(gobj);
}

void ftCo_RunBrake_Coll(Fighter_GObj* gobj)
{
    ft_80084280(gobj);
}

/// #ftCo_800CAE80

/// #ftCo_Jump_CheckInput

bool fn_800CAF78(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ftCo_800C5240(gobj)) {
        return ftCo_800C5A50(gobj);
    }

    if ((fp->input.lstick.y >= p_ftCommonData->x80) &&
        (fp->x671_timer_lstick_tilt_y < p_ftCommonData->x74))
    {
        ftCo_KneeBend_Enter(gobj, 1);
        return true;
    }

    if (fp->input.x668 & HSD_PAD_XY) {
        ftCo_KneeBend_Enter(gobj, 3);
        return true;
    }
    return false;
}

/// #ftCo_800CB024

/// #ftCo_800CB110

/// #fn_800CB250

/// #ftCo_Jump_Anim

void ftCo_Jump_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    RETURN_IF(ftCo_SpecialAir_CheckInput(gobj));
    RETURN_IF(ftCo_80095328(gobj, NULL));
    RETURN_IF(ftCo_800D7100(gobj));
    RETURN_IF(ftCo_800C3B10(gobj));
    RETURN_IF(ftCo_80099A58(gobj));
    RETURN_IF(ftCo_AttackAir_CheckItemThrowInput(gobj));
    RETURN_IF(ftCo_800D705C(gobj));
    RETURN_IF(!(fp->mv.co.jump.x4 == 0) && ftCo_800CEE70(gobj));
    RETURN_IF(!(fp->mv.co.jump.x4 == 0) && ftPe_8011BA54(gobj));
    RETURN_IF(ftCo_800CB870(gobj));
    RETURN_IF(fp->mv.co.jump.x4 == 0);
    RETURN_IF(ftPe_8011BAD8(gobj));
}

/// #ftCo_800CB438

/// #ftCo_Jump_Phys

/// #ftCo_Jump_Coll

void ftCo_KneeBend_Enter(Fighter_GObj* gobj, int arg1)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.co.kneebend.x4 = arg1;
    fp->mv.co.kneebend.x0 = 0;
    Fighter_ChangeMotionState(gobj, ftCo_MS_KneeBend, 0U, 0.0F, 1.0F, 0.0F,
                              NULL);
}

/// #ftCo_KneeBend_Anim

/// #ftCo_800CB59C

/// #ftCo_KneeBend_IASA

/// #ftCo_KneeBend_Phys

/// #ftCo_KneeBend_Coll

/// #ft_800CB6EC

/// #ft_800CB804

bool ftCo_800CB870(Fighter_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

/// #ftCo_800CB8E0

/// #ftCo_800CB950

/// #ftCo_800CBAC4

/// #ftCo_800CBBC0

/// #ftCo_800CBD18

/// #ftCo_800CBE98

/// #ftCo_800CC0E8

/// #ftCo_800CC238

void ftCo_JumpAerial_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_FallAerial_Enter(gobj);
    }
}

/// #fn_800CC3C4

/// #ftCo_JumpAerial_IASA

/// #ftCo_JumpAerial_Phys

void ftNs_JumpAerial_Phys_Cb(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D28C(fp, fp->mv.co.jumpaerial.x4);
    fp->mv.co.jumpaerial.x4 += fp->x74_anim_vel.x;
    fp->x74_anim_vel.x = 0.0F;
    fp->self_vel.x =
        fp->x6A4_transNOffset.z * fp->facing_dir + fp->mv.co.jumpaerial.x4;
    ft_800851D0(gobj);
}

/// #ftCo_800CC6C8

/// #ftCo_JumpAerial_Coll

void ftCo_800CC730(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    bool var_r0;

    if (ftLib_800872A4(gobj) == FTKIND_MASTERH) {
        ftMh_MS_389_80151018(gobj);
        return;
    }

    if (ftLib_800872A4(gobj) == FTKIND_CREZYH) {
        ftCh_GrabUnk1_8015BC88(gobj);
        return;
    }

    if (GET_FIGHTER(gobj)->x2224_b2) {
        ftCo_80090780(gobj);
        var_r0 = true;
    } else if (ftCo_800C5240(gobj)) {
        ftCo_800C5D34(gobj);
        var_r0 = true;
    } else {
        var_r0 = false;
    }
    if (!var_r0) {
        Fighter_ChangeMotionState(gobj, ftCo_MS_Fall, Ft_MF_KeepFastFall, 0.0F,
                                  1.0F, 0.0F, NULL);
        ftCommon_8007D468(fp);
        fp->mv.co.fall.x0 = 20;
        fp->mv.co.fall.x4 = 0.0F;
        if (fp->ground_or_air == GA_Ground) {
            ftCommon_8007D5D4(fp);
        }
    }
}

/// #ftCo_800CC830

/// #ftCo_800CC8DC

/// #ftCo_800CC988

/// #ftCo_Fall_Anim

/// #ftCo_800CCAAC

/// #ftCo_800CCBE0

/// #ftCo_Fall_IASA

/// #ftCo_Fall_Phys

/// #ftCo_Fall_Coll

void ftCo_FallAerial_Enter(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftCo_MS_FallAerial, Ft_MF_None, 0.0F, 1.0F,
                              0.0F, NULL);
    fp->mv.co.fallaerial.x0 = 23;
    fp->mv.co.fallaerial.x4 = 0.0F;
}

/// #ftCo_FallAerial_Anim

/// #ftCo_FallAerial_IASA

/// #ftCo_FallAerial_Phys
