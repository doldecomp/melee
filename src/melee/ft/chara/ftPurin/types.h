#ifndef MELEE_FT_CHARA_FTPURIN_TYPES_H
#define MELEE_FT_CHARA_FTPURIN_TYPES_H

#include <platform.h>
#include <placeholder.h>

#include <baselib/forward.h>

#include <dolphin/mtx/types.h>

struct ftPurin_FighterVars {
    /* 0x222C */ u32 x222C;
    /* 0x2230 */ Vec3 x2230;
    /* 0x223C */ HSD_JObj* x223C;
    /* 0x2240 */ u32 x2240;
    /* 0x2244 */ void* x2244;
    /* 0x2248 */ u32 x2248;
};

typedef union ftPurin_MotionVars {
    struct ftPurin_SpecialHiVars {
        bool x0;
    } specialhi;
    struct ftPurin_SpecialNVars {
        /* fp+2340 */ int x0;
        /* fp+2344 */ UNK_T x4;
        /* fp+2348 */ UNK_T x8;
        /* fp+234C */ UNK_T xC;
        /* fp+2350 */ u8 _10[0x1C - 0x10];
        /* fp+235C */ float x1C;
        /* fp+2360 */ float facing_dir;
        /* fp+2364 */ u8 _24[0x34 - 0x24];
        /* fp+2374 */ Vec3 x34;
    } specialn;
} ftPurin_MotionVars;

typedef struct _ftPurinAttributes {
    float x0;
    float x4;
    float x8;
    float xC;
    float x10;
    s32 x14;
    float x18;
    s32 x1C;
    s32 x20;
    s32 x24;
    s32 x28;
    s32 x2C;
    s32 x30;
    s32 x34;
    s32 x38;
    float x3C;
    float x40;
    float x44;
    u8 _48[0x88 - 0x48];
    Vec2 specialn_vel;
    u8 _90[0xDC - 0x90];
    float xDC;
    float xE0;
    float xE4;
    UNK_T xE8;
    UNK_T xEC;
    float xF0;
    float xF4;
    u8 _F8[0x100 - 0xF8];
} ftPurinAttributes;
STATIC_ASSERT(sizeof(ftPurinAttributes) == 0x100);

#endif
