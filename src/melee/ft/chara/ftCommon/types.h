#ifndef MELEE_FT_CHARA_FTCOMMON_TYPES_H
#define MELEE_FT_CHARA_FTCOMMON_TYPES_H

#include <platform.h>
#include "ft/forward.h"
#include "ftCommon/forward.h"

#include <placeholder.h>

union ftCommon_MotionVars {
    struct ftCommon_CliffVars {
        /// 0x2340 - Used to check against opponent's variable @ 0x213C while
        /// they're occupying a ledge within grab range
        s32 ledge_id;
    } cliff;

    struct ftCommon_WalkVars {
        /* fp+2340 */ float x0;
        /* fp+2344 */ FtMotionId msid;
        /* fp+2348 */ float slow_anim_frame;
        /* fp+234C */ float middle_anim_frame;
        /* fp+2350 */ float fast_anim_frame;
        /* fp+2354 */ float slow_anim_rate;
        /* fp+2358 */ float middle_anim_rate;
        /* fp+235C */ float fast_anim_rate;
        /* fp+2360 */ float accel_mul;
    } walk;
    struct ftCo_Attack1Vars {
        /* fp+2340 */ bool x0;
    } attack1;
};

#endif
