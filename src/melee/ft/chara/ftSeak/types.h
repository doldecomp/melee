#ifndef MELEE_FT_CHARA_FTSEAK_TYPES_H
#define MELEE_FT_CHARA_FTSEAK_TYPES_H

#include <platform.h>
#include <placeholder.h>

#include "it/forward.h"
#include <baselib/forward.h>

#include <dolphin/mtx/types.h>

struct ftSeak_FighterVars {
    /* fp+222C */ int x0;
    /* fp+2230 */ Item_GObj* x4;
    /* fp+2234 */ HSD_GObj* x8;
    /* fp+2238 */ Vec3 xC[4];
    /* fp+2268 */ Vec3 x3C[4];
    /* fp+2298 */ Vec3 lstick_delta;
};

/// @sz{74}
typedef struct _ftSeakAttributes { // x2D4 (fp->dat_attrs)
    float x0;
    float x4;
    float x8;
    float xC;
    float x10;
    float x14;
    float x18;
    float x1C;
    float x20;
    float x24;
    float x28;
    float self_vel_y;
    s32 x30;
    s32 x34;
    s32 x38;
    s32 x3C;
    s32 x40;
    s32 x44;
    s32 x48;
    s32 x4C;
    u8 data_filler_1[0x24];
} ftSeakAttributes;

typedef struct itChainSegment {
    float x00;
    float x04;
    float x08;
    float x0C;
    float x10;
    float x14;
    float x18;
    float x1C;
    float x20;
    float x24;
    float x28;
    float x2C;
    float x30;
    float x34;
    float x38;
    float x3C;
    float x40;
    float x44;
    float x48;
    float x4C;
    float x50;
} itChainSegment;

union ftSeak_MotionVars {
    struct ftSeak_SpecialNVars {
        enum_t x0;
        bool x4;
        s32 x8;
        s32 xC;
        s32 x10;
        s32 x14;
        s32 x18;
        s32 x1C;
        s32 x20;
        s32 x24;
        s32 x28;
        s32 x2C;
    } specialn;

    struct ftSeak_SpecialSVars {
        s32 x0;
        s32 x4;
        s32 x8;
        s32 xC;
        float x10;
        float x14;
        float x18;
        s32 x1C;
        s32 x20;
        s32 x24;
        s32 x28;
        s32 x2C;
    } specials;

    struct ftSeakSpecialHi {
        s32 x0;
        s32 x4;
        s32 x8;
        s32 xC;
        s32 x10;
        s32 x14;
        s32 x18;
        s32 x1C;
        s32 x20;
        s32 x24;
        s32 x28;
        s32 x2C;
    } specialhi;
};

#endif
