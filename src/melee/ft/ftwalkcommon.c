#include "ftwalkcommon.h"

#include "fighter.h"
#include "ft_081B.h"
#include "ftcommon.h"
#include "math.h"

#include "ft/forward.h"

#include "ft/ftanim.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

#include "ftCommon/types.h"

#include <baselib/forward.h>

#include <dolphin/mtx.h>
#include <dolphin/os/OSError.h>
#include <baselib/debug.h>

FtWalkType ftWalkCommon_GetWalkType(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    float gr_vel = fp->gr_vel;
    float walk_vel = ABS(gr_vel);
    if (walk_vel >= (fp->mv.co.walk.accel_mul *
                     (p_ftCommonData->x2C * fp->co_attrs.walk_max_vel)))
    {
        return FtWalkType_Fast;
    } else if (walk_vel >= (fp->mv.co.walk.accel_mul *
                            (p_ftCommonData->x28 * fp->co_attrs.walk_max_vel)))
    {
        return FtWalkType_Middle;
    } else {
        return FtWalkType_Slow;
    }
}

static inline FtWalkType ftWalkCommon_GetWalkType_800DFBF8_fake(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    float walking_velocity = ABS(fp->gr_vel);
    float tempf = fp->mv.co.walk.accel_mul;
    if (walking_velocity >=
        (tempf * (p_ftCommonData->x2C * fp->co_attrs.walk_max_vel)))
    {
        return FtWalkType_Fast;
    } else if (walking_velocity >=
               (tempf * (p_ftCommonData->x28 * fp->co_attrs.walk_max_vel)))
    {
        return FtWalkType_Middle;
    } else {
        return FtWalkType_Slow;
    }
}

bool ftWalkCommon_800DFC70(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->input.lstick.x * fp->facing_dir >= p_ftCommonData->x24) {
        return true;
    }

    return false;
}

void ftWalkCommon_800DFCA4(Fighter_GObj* gobj, FtMotionId msid,
                           MotionFlags ms_flags, float anim_start,
                           float slow_anim_frame, float middle_anim_frame,
                           float fast_anim_frame, float slow_anim_rate,
                           float middle_anim_rate, float fast_anim_rate,
                           float accel_mul)
{
    u8 _[20];

    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.co.walk.accel_mul = accel_mul;
    {
        FtWalkType walk_type = ftWalkCommon_GetWalkType_800DFBF8_fake(gobj);
        ftCommon_MotionState new_msid = msid + walk_type;
        Fighter_ChangeMotionState(gobj, new_msid, ms_flags, anim_start, 1, 0,
                                  0);
        ftAnim_8006EBA4(gobj);
        fp->mv.co.walk.x0 = fp->gr_vel;
        fp->mv.co.walk.msid = msid;
        fp->mv.co.walk.slow_anim_frame = slow_anim_frame;
        fp->mv.co.walk.middle_anim_frame = middle_anim_frame;
        fp->mv.co.walk.fast_anim_frame = fast_anim_frame;
        fp->mv.co.walk.slow_anim_rate = slow_anim_rate;
        fp->mv.co.walk.middle_anim_rate = middle_anim_rate;
        fp->mv.co.walk.fast_anim_rate = fast_anim_rate;
    }
}

void ftWalkCommon_800DFDDC(HSD_GObj* gobj)
{
    float mv_x0;
    float anim_rate;

    Fighter* fp = GET_FIGHTER(gobj);

    if (ft_GetGroundFrictionMultiplier(fp) < 1) {
        mv_x0 = fp->mv.co.walk.x0;
    } else {
        mv_x0 = fp->gr_vel;
    }
    if (mv_x0 * fp->facing_dir <= 0) {
        anim_rate = 0;
    } else {
        mv_x0 = ABS(mv_x0);
        switch (fp->motion_id - fp->mv.co.walk.msid) {
        case FtWalkType_Slow:
            anim_rate = mv_x0 / fp->mv.co.walk.slow_anim_rate;
            break;
        case FtWalkType_Middle:
            anim_rate = mv_x0 / fp->mv.co.walk.middle_anim_rate;
            break;
        case FtWalkType_Fast:
            anim_rate = mv_x0 / fp->mv.co.walk.fast_anim_rate;
            break;
        }
    }
    ftAnim_SetAnimRate(gobj, anim_rate);
}

void ftWalkCommon_800DFEC8(HSD_GObj* gobj, void (*arg_cb)(HSD_GObj*, float))
{
    int motion_state_sum;
    int motion_state_base;
    Fighter* fp = GET_FIGHTER(gobj);
    s32 walk_action_type = ftWalkCommon_GetWalkType_800DFBF8_fake(gobj);

    motion_state_base = fp->mv.co.walk.msid;
    motion_state_sum = motion_state_base + walk_action_type;

    if (motion_state_sum != (int) fp->motion_id) {
        float float_result;
        float frame;
        float init_animFrame;
        float adjusted_animFrame;
        s32 final_animFrame;
        s32 quotient;

        switch (motion_state_sum - motion_state_base) {
        case FtWalkType_Slow:
            frame = fp->mv.co.walk.slow_anim_frame;
            break;
        case FtWalkType_Middle:
            frame = fp->mv.co.walk.middle_anim_frame;
            break;
        case FtWalkType_Fast:
            frame = fp->mv.co.walk.fast_anim_frame;
            break;
        default:
            OSReport("couldn't get walk frame\n");
            HSD_ASSERT(71, 0);
        }

        float_result = ftAnim_8006F484(gobj);
        init_animFrame = fp->cur_anim_frame;
        quotient = init_animFrame / float_result;
        adjusted_animFrame = fp->cur_anim_frame - float_result * quotient;
        final_animFrame = frame * (adjusted_animFrame / float_result);
        arg_cb(gobj, final_animFrame);
    }
}

static float getWalkAccel(Fighter* fp, float mul)
{
    return fp->input.lstick.x > 0 ? mul * +fp->co_attrs.walk_accel
                                  : mul * -fp->co_attrs.walk_accel;
}

void ftWalkCommon_800E0060(HSD_GObj* gobj)
{
    u8 _[12];

    Fighter* fp = GET_FIGHTER(gobj);
    float accel_mul = fp->mv.co.walk.accel_mul;

    {
        float _ = accel_mul;
    }

    {
        float walk_vel =
            fp->input.lstick.x * fp->co_attrs.walk_init_vel * accel_mul;
        walk_vel += getWalkAccel(fp, accel_mul);

        {
            float stick_mul =
                fp->input.lstick.x * fp->co_attrs.walk_max_vel * accel_mul;

            if (stick_mul) {
                float gr_vel = fp->gr_vel / stick_mul;

                if (gr_vel > 0 && gr_vel < 1) {
                    walk_vel *= (1 - gr_vel) * p_ftCommonData->x30;
                }
            }

            fp->mv.co.walk.x0 = stick_mul * p_ftCommonData->x440;
            ftCommon_8007C98C(fp, walk_vel, stick_mul,
                              fp->co_attrs.gr_friction);
        }

        ftCommon_8007CB74(gobj);
    }
}
