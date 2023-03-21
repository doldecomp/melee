#ifndef MELEE_FT_CHARA_FTCOMMON_TYPES_H
#define MELEE_FT_CHARA_FTCOMMON_TYPES_H

#include <platform.h>
#include "forward.h"

union ftCommon_MotionVars {
    struct ftCommon_CliffVars {
        /// 0x2340 - Used to check against opponent's variable @ 0x213C while
        /// they're occupying a ledge within grab range
        s32 ledge_id;
    } cliff;

    struct ftCommon_WalkVars {
        f32 x0;
        ftCommon_MotionState x4;
        f32 x8;
        f32 xC;
        f32 x10;
        f32 x14;
        f32 x18;
        f32 x1C;
        f32 x20;
    } walk;
};

#endif
