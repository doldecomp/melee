#ifndef MELEE_FT_CHARA_FTCOMMON_TYPES_H
#define MELEE_FT_CHARA_FTCOMMON_TYPES_H

#include <platform.h>
#include "ft/forward.h"
#include "ftCommon/forward.h"

#include "ft/ftcolltypes.h"

#include <placeholder.h>

union ftCommon_MotionVars {
    struct {
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
    struct {
        /* fp+2340 */ bool x0;
    } attack1;
    struct {
        /* fp+2340 */ int x0;
    } attackdash;
    struct {
        /* fp+2340 */ bool x0;
    } attacklw3;
    struct {
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
    struct {
        /* fp+2340 */ s8 x0;
        /* fp+2341 */ s8 x1;
        /* fp+2342 */ s8 x2;
        /* fp+2343 */ s8 x3;
        /* fp+2344 */ float x4;
        /* fp+2348 */ ftCollisionBox x8;
    } damageice;
    struct {
        /* fp+2340 */ float x0;
    } damageicejump;
    struct {
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
    struct {
        /* fp+2340 */ bool x0;
    } itemget;
    struct {
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
    struct {
        /* fp+2340 */ int unk_timer;
        /* fp+2344 */ float anim_spd;
        /* fp+2348 */ Vec3 x8;
    } itemthrow4;
    struct {
        /* fp+2340 */ int x0;
        /* fp+2344 */ float x4;
        /* fp+2348 */ float x8;
        /* fp+234C */ int xC;
        /* fp+2350 */ bool x10;
        /* fp+2354 */ float x14;
        /* fp+2358 */ bool allow_interrupt;
    } fallspecial;
    struct {
        /* fp+2340 */ bool x0;
        /* fp+2344 */ float x4;
        /* fp+2348 */ bool x8;
    } lift;
    struct {
        /* fp+2340 */ float x0;
    } downwait;
    struct {
        /* fp+2340 */ bool x0;
        /* fp+2344 */ bool x4;
    } escape;
    struct {
        /* fp+2340 */ int timer;
        /* fp+2344 */ Vec3 self_vel;
    } escapeair;
    struct {
        /* fp+2340 */ float x0;
        /* fp+2344 */ float anim_start;
    } rebound;
    struct {
        /* fp+2340 */ bool x0;
        /* fp+2344 */ float x4;
    } pass;
    struct {
        /**
         * Used to check against opponent's #Fighter::213C while they're
         * occupying a ledge within grab range
         */
        /* fp+2340 */ int ledge_id;
        /* fp+2344 */ float x4;
        /* fp+2348 */ bool x8;
    } cliff;
    struct {
        /* fp+2340 */ bool x0;
    } cliffjump;
    struct {
        /* fp+2340 */ bool x0;
    } cargoturn;
    struct {
        /* fp+2340 */ int x0;
        /* fp+2344 */ int x4;
        /* fp+2348 */ float x8;
    } cargokneebend;
    struct {
        /* fp+2340 */ float x0;
        /* fp+2344 */ int x4;
    } shouldered;
};

#endif
