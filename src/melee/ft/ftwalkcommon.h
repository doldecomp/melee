/**
 * @file ftwalkcommon.h
 * @brief Walk state common physics and logic
 * @details Handles the calculation of walk speed, transitions between slow/mid/fast walk states, and animation rate syncing.
 * Module prefix: ft (Fighter)
 */

#ifndef GALE01_0DFBF8
#define GALE01_0DFBF8

#include <melee/ft/forward.h>

/**
 * @brief Get the type of walk based on the stick input and velocity
 * @param gobj The fighter's GObj
 * @return Walk type (0 = slow, 1 = middle, 2 = fast)
 */
/* 0DFBF8 */ FtWalkType ftWalkCommon_GetWalkType(Fighter_GObj* gobj);

/**
 * @brief Checks if the stick input is sufficient to maintain a walk state
 * @param gobj The fighter's GObj
 * @return true if walking should continue, false otherwise
 */
/* 0DFC70 */ bool ftWalkCommon_800DFC70(Fighter_GObj* gobj);

/**
 * @brief Setup the initial state and animation variables for walking
 * @param gobj The fighter's GObj
 * @param msid The base motion state ID for walking (e.g., FtWalk_Slow)
 * @param ms_flags Motion state flags
 * @param anim_start The start frame for the animation
 * @param slow_anim_frame Total frames in slow walk animation
 * @param middle_anim_frame Total frames in middle walk animation
 * @param fast_anim_frame Total frames in fast walk animation
 * @param slow_anim_rate Base animation rate for slow walk
 * @param middle_anim_rate Base animation rate for middle walk
 * @param fast_anim_rate Base animation rate for fast walk
 * @param accel_mul Walk acceleration multiplier (often tied to items or size)
 */
/* 0DFCA4 */ void ftWalkCommon_800DFCA4(
    Fighter_GObj* gobj, FtMotionId msid, MotionFlags ms_flags,
    float anim_start, float slow_anim_frame, float middle_anim_frame,
    float fast_anim_frame, float slow_anim_rate, float middle_anim_rate,
    float fast_anim_rate, float accel_mul);

/**
 * @brief Calculate and set the animation rate for the walking state based on current velocity
 * @param gobj The fighter's GObj
 */
/* 0DFDDC */ void ftWalkCommon_800DFDDC(Fighter_GObj* gobj);

/**
 * @brief Handle transition between different walk types (slow, middle, fast) maintaining sync
 * @param gobj The fighter's GObj
 * @param arg_cb Callback function to change motion state
 */
/* 0DFEC8 */ void ftWalkCommon_800DFEC8(Fighter_GObj* gobj,
                                        void (*arg_cb)(Fighter_GObj*, float));

/**
 * @brief Update the walking velocity based on stick input and fighter attributes
 * @param gobj The fighter's GObj
 */
/* 0E0060 */ void ftWalkCommon_800E0060(Fighter_GObj* gobj);

#endif
