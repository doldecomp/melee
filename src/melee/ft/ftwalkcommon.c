#include "ftwalkcommon.h"

#include "code_80081B38.h"
#include "fighter.h"
#include "ftcommon.h"

#include <dolphin/os/os.h>

s32 ftWalkCommon_GetWalkType(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    f32 ground_vel = fp->xEC_ground_vel;
    f32 walking_velocity = fabs_inline(ground_vel);
    if (walking_velocity >=
        (fp->sv.co.walk.x20 *
         (p_ftCommonData->x2C * fp->x110_attr.x118_WalkMaximumVelocity)))
    {
        return 2;
    } else if (walking_velocity >=
               (fp->sv.co.walk.x20 * (p_ftCommonData->x28 *
                                      fp->x110_attr.x118_WalkMaximumVelocity)))
    {
        return 1;
    } else {
        return 0;
    }
}

static inline s32
ftWalkCommon_GetWalkType_800DFBF8_fake(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    f32 walking_velocity = fabs_inline(fp->xEC_ground_vel);
    f32 tempf = fp->sv.co.walk.x20;
    if (walking_velocity >= (tempf * (p_ftCommonData->x2C *
                                      fp->x110_attr.x118_WalkMaximumVelocity)))
    {
        return 2;
    } else if (walking_velocity >=
               (tempf * (p_ftCommonData->x28 *
                         fp->x110_attr.x118_WalkMaximumVelocity)))
    {
        return 1;
    } else {
        return 0;
    }
}

bool ftWalkCommon_800DFC70(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    if ((fp->input.x620_lstick_x * fp->facing_dir) >= p_ftCommonData->x24) {
        return true;
    }

    return false;
}

void ftWalkCommon_800DFCA4(HSD_GObj* fighter_gobj, s32 arg1, s32 arg2,
                           f32 arg8, f32 arg9, f32 argA, f32 argB, f32 argC,
                           f32 argD, f32 argE, f32 argF)
{
    s32 new_action_state;
    s32 walking_state;
    Fighter* fp;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[20];
#endif

    fp = GET_FIGHTER(fighter_gobj);
    fp->sv.co.walk.x20 = argF;
    walking_state = ftWalkCommon_GetWalkType_800DFBF8_fake(fighter_gobj);
    new_action_state = arg1 + walking_state;
    Fighter_ChangeMotionState(fighter_gobj, new_action_state, arg2, 0, arg8,
                              1.0f, 0.0f);
    ftAnim_8006EBA4(fighter_gobj);
    fp->sv.co.walk.x0 = fp->xEC_ground_vel;
    fp->sv.co.walk.x4 = arg1;
    fp->sv.co.walk.x8 = arg9;
    fp->sv.co.walk.xC = argA;
    fp->sv.co.walk.x10 = argB;
    fp->sv.co.walk.x14 = argC;
    fp->sv.co.walk.x18 = argD;
    fp->sv.co.walk.x1C = argE;
}

void ftWalkCommon_800DFDDC(HSD_GObj* fighter_gobj)
{
    f32 velocity_f2;
    f32 anim_rate;

    Fighter* fp = GET_FIGHTER(fighter_gobj);

    if (ft_GetGroundFrictionMultiplier(fp) < 1.0f) {
        velocity_f2 = fp->sv.co.walk.x0;
    } else {
        velocity_f2 = fp->xEC_ground_vel;
    }
    if ((velocity_f2 * fp->facing_dir) <= 0.0f) {
        anim_rate = 0.0f;
    } else {
        velocity_f2 = fabs_inline(velocity_f2);
        switch (fp->action_id - fp->sv.co.walk.x4) {
        case 0:
            anim_rate = velocity_f2 / fp->sv.co.walk.x14;
            break;
        case 1:
            anim_rate = velocity_f2 / fp->sv.co.walk.x18;
            break;
        case 2:
            anim_rate = velocity_f2 / fp->sv.co.walk.x1C;
            break;
        }
    }
    ftAnim_SetAnimRate(fighter_gobj, anim_rate);
}

void ftWalkCommon_800DFEC8(HSD_GObj* fighter_gobj,
                           void (*arg_cb)(HSD_GObj*, f32))
{
    s32 action_state_sum;
    s32 action_state_base;
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    s32 walk_action_type =
        ftWalkCommon_GetWalkType_800DFBF8_fake(fighter_gobj);

    action_state_base = fp->sv.co.walk.x4;
    action_state_sum = action_state_base + walk_action_type;
    if (action_state_sum != fp->action_id) {
        f32 float_result;
        f32 var_f31;
        f32 init_animFrame;
        f32 adjusted_animFrame;
        s32 final_animFrame;
        s32 quotient;

        switch (action_state_sum - action_state_base) {
        case 0:
            var_f31 = fp->sv.co.walk.x8;
            break;
        case 1:
            var_f31 = fp->sv.co.walk.xC;
            break;
        case 2:
            var_f31 = fp->sv.co.walk.x10;
            break;
        default:
            OSReport("couldn't get walk frame\n");
            HSD_ASSERT(71, 0);
        }
        float_result = ftAnim_8006F484(fighter_gobj);
        init_animFrame = fp->x894_currentAnimFrame;
        quotient = init_animFrame / float_result;
        adjusted_animFrame =
            fp->x894_currentAnimFrame - float_result * quotient;
        final_animFrame = var_f31 * (adjusted_animFrame / float_result);
        arg_cb(fighter_gobj, final_animFrame);
    }
}

inline f32 getFtWalkAcceleration(Fighter* fp, f32 multiplier)
{
    if (fp->input.x620_lstick_x > 0.0f) {
        return multiplier * fp->x110_attr.x114_WalkAcceleration;
    } else {
        return multiplier * -fp->x110_attr.x114_WalkAcceleration;
    }
}

void ftWalkCommon_800E0060(HSD_GObj* fighter_gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[20];
#endif

    Fighter* fp;
    f32 temp_f0;
    f32 temp_f4;
    f32 ftx2360_f5;
    f32 velocity_f1;

    fp = GET_FIGHTER(fighter_gobj);
    ftx2360_f5 = fp->sv.co.walk.x20;

/// @todo Unused assignment.
#ifdef MUST_MATCH
    {
        f32 _ = ftx2360_f5;
    }
#endif

    velocity_f1 = fp->input.x620_lstick_x *
                  fp->x110_attr.x110_WalkInitialVelocity * ftx2360_f5;
    velocity_f1 += getFtWalkAcceleration(fp, ftx2360_f5);
    temp_f0 =
        (fp->input.x620_lstick_x * fp->x110_attr.x118_WalkMaximumVelocity) *
        ftx2360_f5;
    if (temp_f0) {
        temp_f4 = fp->xEC_ground_vel / temp_f0;
        if (temp_f4 > 0.0f && temp_f4 < 1.0f) {
            velocity_f1 *= (1.0f - temp_f4) * p_ftCommonData->x30;
        }
    }
    fp->sv.co.walk.x0 = temp_f0 * p_ftCommonData->x440;
    ftCommon_8007C98C(fp, velocity_f1, temp_f0,
                      fp->x110_attr.x128_GroundFriction);
    ftCommon_8007CB74(fighter_gobj);
}
