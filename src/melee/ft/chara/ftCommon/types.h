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
    struct ftCo_DamageIceJumpVars {
        /* fp+2340 */ float x0;
    } damageicejump;
    struct ftCo_GuardVars {
        /* fp+2340 */ float x0;
        /* fp+2344 */ float x4;
        /* fp+2348 */ float x8;
        /* fp+234C */ bool xC;
        /* fp+2350 */ float x10;
        /* fp+2354 */ float x14;
        /* fp+2358 */ float x18;
        /* fp+235C */ int x1C;
        /* fp+2360 */ int x20;
        /* fp+2364 */ int x24;
        /* fp+2368 */ UNK_T x28;
        /* fp+236C */ float x2C;
    } guard;
    struct ftCo_ItemGetVars {
        /* fp+2340 */ bool x0;
    } itemget;
    struct ftCo_ItemThrowVars {
        /* fp+2340 */ float facing_dir;
        /* fp+2344 */ UNK_T x4;
        /* fp+2348 */ UNK_T x8;
        /* fp+234C */ UNK_T xC;
        /* fp+2350 */ UNK_T x10;
        /* fp+2354 */ UNK_T x14;
        /* fp+2358 */ UNK_T x18;
        /* fp+235C */ UNK_T x1C;
        /* fp+2360 */ int x20;
    } itemthrow;
    struct ftCo_ItemThrow4Vars {
        /* fp+2340 */ int unk_timer;
        /* fp+2344 */ float anim_spd;
        /* fp+2348 */ Vec3 x8;
    } itemthrow4;
    struct ftCo_FallSpecialVars {
        /* fp+2340 */ int x0;
        /* fp+2344 */ float x4;
        /* fp+2348 */ float x8;
        /* fp+234C */ int xC;
        /* fp+2350 */ bool x10;
        /* fp+2354 */ float x14;
        /* fp+2358 */ bool allow_interrupt;
    } fallspecial;
    struct ftCo_LiftVars {
        /* fp+2340 */ bool x0;
        /* fp+2344 */ float x4;
        /* fp+2348 */ bool x8;
    } lift;
    struct ftCo_DownVars {
        /* fp+2340 */ float x0;
    } downwait;
};

#endif
