#ifndef MELEE_FT_CHARA_FTPURIN_TYPES_H
#define MELEE_FT_CHARA_FTPURIN_TYPES_H

#include <placeholder.h>
#include <platform.h>

#include <baselib/forward.h>

#include <dolphin/mtx.h>
#include <melee/ft/dobjlist.h>

struct ftPurin_FighterVars {
    /* 0x222C */ u32 x222C;
    /* 0x2230 */ Vec3 x2230;
    /* 0x223C */ HSD_JObj* x223C;
    /* 0x2240 */ DObjList x2240;
    /* 0x2248 */ FtPartsVis x2248;
};

typedef union ftPurin_MotionVars {
    struct ftPurin_SpecialHiVars {
        bool x0;
    } specialhi;
    struct ftPurin_SpecialNVars {
        /* fp+2340 */ int x0;
        /* fp+2344 */ int x4;
        /* fp+2348 */ int x8;
        /* fp+234C */ int xC;
        /* fp+2350 */ float x10;
        /* fp+2354 */ float x14;
        /* fp+2358 */ float x18;
        /* fp+235C */ float x1C;
        /* fp+2360 */ float facing_dir;
        /* fp+2364 */ int x24;
        /* fp+2368 */ int x28;
        /* fp+236C */ int x2C;
        /* fp+2370 */ int x30;
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
    u8 _48[0x4C - 0x48];
    float x4C;
    float x50;
    float x54;
    float x58;
    float x5C;
    u8 _60[0x68 - 0x60];
    float x68;
    float x6C;
    s32 x70;
    float x74;
    float x78;
    float x7C;
    float x80;
    float x84;
    Vec2 specialn_vel;
    float x90;
    float x94;
    float x98;
    s32 x9C;
    float xA0;
    float xA4;
    float xA8;
    float xAC;
    u8 _B0[0xB4 - 0xB0];
    float xB4;
    float xB8;
    float xBC;
    float xC0;
    float xC4;
    float xC8;
    float xCC;
    float xD0;
    float xD4;
    float xD8;
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
