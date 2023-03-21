#include "ft/forward.h"
#include "ftCommon/forward.h"

#include "ftwalkcommon.h"

#include "code_80081B38.h"
#include "fighter.h"
#include "ftcommon.h"

#include <dolphin/os/os.h>

FtWalkType ftWalkCommon_GetWalkType(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    float gr_vel = fp->gr_vel;
    float walk_vel = fabs_inline(gr_vel);
    if (walk_vel >= (fp->mv.co.walk.accel_mul *
                     (p_ftCommonData->x2C * fp->x110_attr.walk_max_vel)))
    {
        return FtWalkType_Fast;
    } else if (walk_vel >=
               (fp->mv.co.walk.accel_mul *
                (p_ftCommonData->x28 * fp->x110_attr.walk_max_vel)))
    {
        return FtWalkType_Middle;
    } else {
        return FtWalkType_Slow;
    }
}

static inline enum_t ftWalkCommon_GetWalkType_800DFBF8_fake(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    f32 walking_velocity = fabs_inline(fp->gr_vel);
    f32 tempf = fp->mv.co.walk.accel_mul;
    if (walking_velocity >=
        (tempf * (p_ftCommonData->x2C * fp->x110_attr.walk_max_vel)))
    {
        return FtWalkType_Fast;
    } else if (walking_velocity >=
               (tempf * (p_ftCommonData->x28 * fp->x110_attr.walk_max_vel)))
    {
        return FtWalkType_Middle;
    } else {
        return FtWalkType_Slow;
    }
}

bool ftWalkCommon_800DFC70(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->input.x620_lstick_x * fp->facing_dir >= p_ftCommonData->x24)
        return true;

    return false;
}

void ftWalkCommon_800DFCA4(HSD_GObj* gobj, ftCommon_MotionState msid, s32 arg2,
                           f32 arg8, f32 arg9, f32 argA, f32 argB, f32 argC,
                           f32 argD, f32 argE, f32 argF)
{
    s32 new_motion_state;
    s32 walk_type;
    Fighter* fp;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[20];
#endif

    fp = GET_FIGHTER(gobj);
    fp->mv.co.walk.accel_mul = argF;
    walk_type = ftWalkCommon_GetWalkType_800DFBF8_fake(gobj);
    new_motion_state = msid + walk_type;
    Fighter_ChangeMotionState(gobj, new_motion_state, arg2, 0, arg8, 1.0f,
                              0.0f);
    func_8006EBA4(gobj);
    fp->mv.co.walk.x0 = fp->gr_vel;
    fp->mv.co.walk.x4 = msid;
    fp->mv.co.walk.x8 = arg9;
    fp->mv.co.walk.xC = argA;
    fp->mv.co.walk.x10 = argB;
    fp->mv.co.walk.x14 = argC;
    fp->mv.co.walk.x18 = argD;
    fp->mv.co.walk.x1C = argE;
}

void ftWalkCommon_800DFDDC(HSD_GObj* gobj)
{
    f32 velocity_f2;
    f32 anim_rate;

    Fighter* fp = GET_FIGHTER(gobj);

    if (Stage_GetGroundFrictionMultiplier(fp) < 1.0f) {
        velocity_f2 = fp->mv.co.walk.x0;
    } else {
        velocity_f2 = fp->gr_vel;
    }
    if ((velocity_f2 * fp->facing_dir) <= 0.0f) {
        anim_rate = 0.0f;
    } else {
        velocity_f2 = fabs_inline(velocity_f2);
        switch (fp->motion_id - fp->mv.co.walk.x4) {
        case 0:
            anim_rate = velocity_f2 / fp->mv.co.walk.x14;
            break;
        case 1:
            anim_rate = velocity_f2 / fp->mv.co.walk.x18;
            break;
        case 2:
            anim_rate = velocity_f2 / fp->mv.co.walk.x1C;
            break;
        }
    }
    ftAnim_SetAnimRate(gobj, anim_rate);
}

void ftWalkCommon_800DFEC8(HSD_GObj* gobj, void (*arg_cb)(HSD_GObj*, f32))
{
    int motion_state_sum;
    int motion_state_base;
    Fighter* fp = GET_FIGHTER(gobj);
    s32 walk_action_type = ftWalkCommon_GetWalkType_800DFBF8_fake(gobj);

    motion_state_base = fp->mv.co.walk.x4;
    motion_state_sum = motion_state_base + walk_action_type;

    if (motion_state_sum != (int) fp->motion_id) {
        f32 float_result;
        f32 frame;
        f32 init_animFrame;
        f32 adjusted_animFrame;
        s32 final_animFrame;
        s32 quotient;

        switch (motion_state_sum - motion_state_base) {
        case 0:
            frame = fp->mv.co.walk.x8;
            break;
        case 1:
            frame = fp->mv.co.walk.xC;
            break;
        case 2:
            frame = fp->mv.co.walk.x10;
            break;
        default:
            OSReport("couldn't get walk frame\n");
            HSD_ASSERT(71, 0);
        }

        float_result = func_8006F484(gobj);
        init_animFrame = fp->x894_currentAnimFrame;
        quotient = init_animFrame / float_result;
        adjusted_animFrame =
            fp->x894_currentAnimFrame - float_result * quotient;
        final_animFrame = frame * (adjusted_animFrame / float_result);
        arg_cb(gobj, final_animFrame);
    }
}

static float getWalkAccel(Fighter* fp, float mul)
{
    return fp->input.x620_lstick_x > 0 ? mul * +fp->x110_attr.walk_accel
                                       : mul * -fp->x110_attr.walk_accel;
}

void ftWalkCommon_800E0060(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[12];
#endif

    Fighter* fp;
    f32 temp_f0;
    f32 temp_f4;
    f32 ftx2360_f5;
    f32 velocity_f1;

    fp = GET_FIGHTER(gobj);
    ftx2360_f5 = fp->mv.co.walk.accel_mul;

/// @todo Unused assignment.
#ifdef MUST_MATCH
    {
        f32 _ = ftx2360_f5;
    }
#endif

    velocity_f1 = fp->input.x620_lstick_x *
                  fp->x110_attr.x110_WalkInitialVelocity * ftx2360_f5;
    velocity_f1 += getWalkAccel(fp, ftx2360_f5);
    temp_f0 =
        (fp->input.x620_lstick_x * fp->x110_attr.walk_max_vel) * ftx2360_f5;
    if (temp_f0) {
        temp_f4 = fp->gr_vel / temp_f0;
        if (temp_f4 > 0.0f && temp_f4 < 1.0f) {
            velocity_f1 *= (1.0f - temp_f4) * p_ftCommonData->x30;
        }
    }
    fp->mv.co.walk.x0 = temp_f0 * p_ftCommonData->x440;
    func_8007C98C(fp, velocity_f1, temp_f0, fp->x110_attr.gr_friction);
    func_8007CB74(gobj);
}
