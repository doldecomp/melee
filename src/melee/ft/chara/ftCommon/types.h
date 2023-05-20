#ifndef MELEE_FT_CHARA_FTCOMMON_TYPES_H
#define MELEE_FT_CHARA_FTCOMMON_TYPES_H

#include <platform.h>
#include "ft/forward.h"
#include "ftCommon/forward.h"

#include "ft/ftcolltypes.h"

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
    struct ftCo_AttackDashVars {
        /* fp+2340 */ int x0;
    } attackdash;
    struct ftCo_AttackLw3Vars {
        /* fp+2340 */ bool x0;
    } attacklw3;
    struct ftCo_DamageVars {
        /* fp+2340 */ float x0;
        /* fp+2344 */ int x4;
        /* fp+2348 */ int x8;
        /* fp+234C */ UNK_T xC;
        /* fp+2350 */ UNK_T x10;
        /* fp+2354 */ float x14;
        /* fp+2358 */ u8 x18[0x1A - 0x18];
        /* fp+235A */ u8 x1A;
        /* fp+235B */ u8 x1B;
    } damage;
    struct ftCo_DamageIceVars {
        /* fp+2340 */ s8 x0;
        /* fp+2341 */ s8 x1;
        /* fp+2342 */ s8 x2;
        /* fp+2343 */ s8 x3;
        /* fp+2344 */ float x4;
        /* fp+2348 */ ftCollisionBox x8;
    } damageice;
};

#endif
