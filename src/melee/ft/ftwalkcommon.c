/**
 * @file ftwalkcommon.c
 * @brief Walk state common physics and logic
 * @details Handles the calculation of walk speed, transitions between slow/mid/fast walk states, and animation rate syncing.
 * Module prefix: ft (Fighter)
 */

#include "ftwalkcommon.h"

#include <sysdolphin/baselib/forward.h>

#include "fighter.h"
#include "forward.h"
#include "ft_081B.h"
#include "ftanim.h"
#include "ftcommon.h"
#include "kinds/ftCommon/forward.h"
#include "kinds/ftCommon/types.h"
#include "types.h"
#include <dolphin/mtx.h>
#include <sysdolphin/baselib/debug.h>

/**
 * @brief Get the type of walk based on the stick input and velocity
 * @param gobj The fighter's GObj
 * @return Walk type (0 = slow, 1 = middle, 2 = fast)
 */
FtWalkType ftWalkCommon_GetWalkType(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    float gr_vel = fp->gr_vel;
    float walk_vel = ABS(gr_vel);
    
    // Check if fast walk
    if (walk_vel >= (fp->mv.co.walk.accel_mul *
                     (p_ftCommonData->walk_fast_stick_threshold *
                      fp->co_attrs.walk_max_vel)))
    {
        return FtWalkType_Fast;
    } 
    // Check if middle walk
    else if (walk_vel >=
               (fp->mv.co.walk.accel_mul *
                (p_ftCommonData->walk_middle_animation_stick_threshold *
                 fp->co_attrs.walk_max_vel)))
    {
        return FtWalkType_Middle;
    } 
    // Otherwise slow walk
    else {
        return FtWalkType_Slow;
    }
}

/**
 * @brief Inline version of ftWalkCommon_GetWalkType
 */
static inline FtWalkType ftWalkCommon_GetWalkType_800DFBF8_fake(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    float walk_velocity = ABS(fp->gr_vel);
    float accel_multiplier = fp->mv.co.walk.accel_mul;
    
    if (walk_velocity >=
        (accel_multiplier * (p_ftCommonData->walk_fast_stick_threshold *
                  fp->co_attrs.walk_max_vel)))
    {
        return FtWalkType_Fast;
    } else if (walk_velocity >=
               (accel_multiplier *
                (p_ftCommonData->walk_middle_animation_stick_threshold *
                 fp->co_attrs.walk_max_vel)))
    {
        return FtWalkType_Middle;
    } else {
        return FtWalkType_Slow;
    }
}

/**
 * @brief Checks if the stick input is sufficient to maintain a walk state
 * @param gobj The fighter's GObj
 * @return true if walking should continue, false otherwise
 */
bool ftWalkCommon_800DFC70(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->input.lstick[0].x * fp->facing_dir >=
        p_ftCommonData->walk_stick_threshold)
    {
        return true;
    }

    return false;
}

/**
 * @brief Setup the initial state and animation variables for walking
 */
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
        
        // Enter the chosen walk action state
        Fighter_ChangeMotionState(gobj, new_msid, ms_flags, anim_start, 1, 0,
                                  0);
        ftAnim_8006EBA4(gobj);
        
        // Setup walk data
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

/**
 * @brief Calculate and set the animation rate for the walking state based on current velocity
 */
void ftWalkCommon_800DFDDC(HSD_GObj* gobj)
{
    float walk_vel;
    float anim_rate;

    Fighter* fp = GET_FIGHTER(gobj);

    // Get true walking speed depending on friction
    if (ft_GetGroundFrictionMultiplier(fp) < 1) {
        walk_vel = fp->mv.co.walk.x0;
    } else {
        walk_vel = fp->gr_vel;
    }
    
    if (walk_vel * fp->facing_dir <= 0) {
        anim_rate = 0;
    } else {
        walk_vel = ABS(walk_vel);
        
        // Calculate the animation speed scale based on how fast the fighter is moving
        switch (fp->motion_id - fp->mv.co.walk.msid) {
        case FtWalkType_Slow:
            anim_rate = walk_vel / fp->mv.co.walk.slow_anim_rate;
            break;
        case FtWalkType_Middle:
            anim_rate = walk_vel / fp->mv.co.walk.middle_anim_rate;
            break;
        case FtWalkType_Fast:
            anim_rate = walk_vel / fp->mv.co.walk.fast_anim_rate;
            break;
        }
    }
    
    // Apply animation rate
    ftAnim_SetAnimRate(gobj, anim_rate);
}

/**
 * @brief Handle transition between different walk types (slow, middle, fast) maintaining sync
 */
void ftWalkCommon_800DFEC8(HSD_GObj* gobj, void (*arg_cb)(HSD_GObj*, float))
{
    int current_motion_state;
    int base_motion_state;
    Fighter* fp = GET_FIGHTER(gobj);
    s32 walk_action_type = ftWalkCommon_GetWalkType_800DFBF8_fake(gobj);

    base_motion_state = fp->mv.co.walk.msid;
    current_motion_state = base_motion_state + walk_action_type;

    // Check if walk type has changed and we need to sync frames
    if (current_motion_state != (int) fp->motion_id) {
        float anim_length;
        float frame_count;
        float init_animFrame;
        float adjusted_animFrame;
        s32 final_animFrame;
        s32 quotient;

        switch (current_motion_state - base_motion_state) {
        case FtWalkType_Slow:
            frame_count = fp->mv.co.walk.slow_anim_frame;
            break;
        case FtWalkType_Middle:
            frame_count = fp->mv.co.walk.middle_anim_frame;
            break;
        case FtWalkType_Fast:
            frame_count = fp->mv.co.walk.fast_anim_frame;
            break;
        default:
            OSReport("couldn't get walk frame\n");
            HSD_ASSERT(71, 0);
        }

        anim_length = ftAnim_8006F484(gobj);
        init_animFrame = fp->cur_anim_frame;
        quotient = init_animFrame / anim_length;
        adjusted_animFrame = fp->cur_anim_frame - anim_length * quotient;
        
        // Calculate the synchronized frame for the newly switched walk animation
        final_animFrame = frame_count * (adjusted_animFrame / anim_length);
        
        // Invoke state change callback (e.g. Fighter_ChangeMotionState)
        arg_cb(gobj, final_animFrame);
    }
}

/**
 * @brief Calculates walker base acceleration considering facing dir
 * @param fp The fighter
 * @param mul Acceleration multiplier
 * @return the raw walk acceleration
 */
static float getWalkAccel(Fighter* fp, float mul)
{
    return fp->input.lstick[0].x > 0 ? mul * +fp->co_attrs.walk_accel_base
                                     : mul * -fp->co_attrs.walk_accel_base;
}

/**
 * @brief Update the walking velocity based on stick input and fighter attributes
 */
void ftWalkCommon_800E0060(HSD_GObj* gobj)
{
    u8 _[12];

    Fighter* fp = GET_FIGHTER(gobj);
    float accel_mul = fp->mv.co.walk.accel_mul;

    {
        float _ = accel_mul;
    }

    {
        // Calculate total walk acceleration
        float accel =
            fp->input.lstick[0].x * fp->co_attrs.walk_accel_mul * accel_mul;
        accel += getWalkAccel(fp, accel_mul);

        {
            // Calculate target walking velocity based on stick input and fighter max walk speed
            float target_vel =
                fp->input.lstick[0].x * fp->co_attrs.walk_max_vel * accel_mul;

            if (target_vel) {
                float vel_ratio = fp->gr_vel / target_vel;

                // Dampen acceleration when approaching target velocity
                if (vel_ratio > 0 && vel_ratio < 1) {
                    accel *=
                        (1 - vel_ratio) * p_ftCommonData->walk_accel_taper_gain;
                }
            }

            fp->mv.co.walk.x0 = target_vel * p_ftCommonData->x440;
            
            // Apply physics changes
            ftCommon_CalcGroundAccel_DashRun(fp, accel, target_vel,
                                             fp->co_attrs.ground_friction);
        }

        ftCommon_SetSelfMovementFromGroundedMovement(gobj);
    }
}
