#ifndef MELEE_FT_CHARA_FTCOMMON_TYPES_H
#define MELEE_FT_CHARA_FTCOMMON_TYPES_H

#include <platform.h>
#include "ft/forward.h"
#include "ftCommon/forward.h" // IWYU pragma: export
#include "ftKirby/forward.h"
#include "it/forward.h"

#include <placeholder.h>
#include <dolphin/mtx/types.h>

struct ftCollisionBox {
    /*  +0 */ float top;
    /*  +4 */ float bottom;
    /*  +8 */ Vec2 left;
    /* +10 */ Vec2 right;
};

struct UNK_SAMUS_S2 {
    Fighter_Part parts[3];
    Vec3 vec1;
    Vec3 vec2;
    float scale;
};

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
        /* fp+2358 */ u8 x18;
        /* fp+2359 */ u8 x19;
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
        /* fp+2340 */ bool x0; // itemget action is heavy type?
    } itemget;
    struct {
        /* fp+2340 */ float facing_dir;
        /* fp+2344 */ float x4;
        /* fp+2348 */ int x8;
        /* fp+234C */ int xC;
        /* fp+2350 */ float x10;
        /* fp+2354 */ int x14;
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
    struct {
        /* fp+2340 */ float x0;
    } downdamage;
    struct {
        /* fp+2340 */ ftCo_GObj* x0;
        /* fp+2344 */ bool x4;
        /* fp+2348 */ float x8;
        /* fp+234C */ float xC;
        /* fp+2350 */ float x10;
        /* fp+2354 */ float x14;
        /* fp+2358 */ Vec3 x18;
        /* fp+2364 */ Vec3 scale;
    } yoshiegg;
    struct {
        /* fp+2340 */ bool x0;
        /* fp+2344 */ UNK_T x4;
        /* fp+2348 */ float x8;
        /* fp+234C */ float xC;
        /* fp+2350 */ float x10;
    } capturekoopa;
    struct {
        /* fp+2340 */ Vec2 pos_offset;
        /* fp+2348 */ Vec2 x8;
        /* fp+2350 */ Vec2 x10;
        /* fp+2358 */ bool x18;
        /* fp+235C */ UNK_T x1C;
        /* fp+2360 */ UNK_T x20;
        /* fp+2364 */ UNK_T x24;
        /* fp+2368 */ UNK_T x28;
        /* fp+236C */ Vec3 scale;
    } capturekirby;
    struct {
        /* fp+2340 */ ftKb_GObj* thrower_gobj;
        /* fp+2344 */ float x4;
        /* fp+2348 */ float x8;
        /* fp+234C */ float xC;
        /* fp+2350 */ float x10;
        /* fp+2354 */ bool x14;
        union {
            u8 x18;
            struct {
                /* fp+2358:0 */ u8 x18_b0 : 1;
                /* fp+2358:1 */ u8 x18_b1 : 1;
                /* fp+2358:2 */ u8 x18_b2 : 1;
                /* fp+2358:3 */ u8 x18_b3 : 1;
                /* fp+2358:4 */ u8 x18_b4 : 1;
                /* fp+2358:5 */ u8 x18_b5 : 1;
                /* fp+2358:6 */ u8 x18_b6 : 1;
                /* fp+2358:7 */ u8 x18_b7 : 1;
            };
        };
        /* fp+235C */ Vec3 scale;
        /* fp+2368 */ ftCollisionBox coll_box;
    } thrownkirby;
    struct {
        /* fp+2340 */ int x0;
        /* fp+2344 */ ftCollisionBox coll_box;
        /* fp+235C */ float x1C;
        /* fp+2360 */ enum_t x20;
        /* fp+2364 */ Vec3 translate;
    } bury;
    struct {
        /* fp+2340 */ float x0;
    } buryjump;
    struct {
        /* fp+2340 */ int timer;
        /* fp+2344 */ int x4;
        /* fp+2348 */ bool x8;
        /* fp+234C */ int vel_y_exponent;
    } passivewall;
    struct {
        /* fp+2340 */ int x0;
        /* fp+2344 */ float x4;
    } aircatchhit;
    struct {
        /* fp+2340 */ float x0;
    } aircatch;
    struct {
        /* fp+2340 */ Vec3 cur_pos;
        /* fp+234C */ Vec3 self_vel;
        /* fp+2358 */ float facing_dir;
        /* fp+235C */ int x1C;
        /* fp+2360 */ ftCollisionBox ecb;
    } warpstar;
    struct {
        /* fp+2340 */ int x0;
        /* fp+2344 */ int x4;
        /* fp+2344 */ float x8;
    } jumpb;
    struct {
        /* fp+2340 */ int x0;
        /* fp+2344 */ int x4;
        /* fp+2348 */ float x8;
    } hammerkneebend;
    struct {
        /* fp+2340 */ UNK_T x0;
        /* fp+2344 */ float x4;
    } hammerlanding;
    struct {
        /* fp+2340 */ Item_GObj* x0;
    } captureleadead;
    struct {
        /* fp+2340 */ bool timer;
    } entry;
    struct {
        /* fp+2340 */ Item_GObj* x0;
    } capturelikelike;
};

#endif
