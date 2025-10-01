#ifndef MELEE_FT_CHARA_FTPOPO_TYPES_H
#define MELEE_FT_CHARA_FTPOPO_TYPES_H

#include <placeholder.h>
#include <platform.h>

#include "ft/forward.h"
#include "it/forward.h"

struct ftPopo_FighterVars {
    /* 0x222C */ Item_GObj* x222C;
    /* 0x2230:0 */ u8 x2230_b0 : 1;
    /* 0x2231 */ u8 filler_x2231[3];
    /* 0x2234 */ u32 x2234;
    /* 0x2238 */ Item_GObj* x2238;
    /* 0x223C */ u32 x223C;
    /* 0x2240 */ Vec x2240;
    /* 0x224C */ u32 x224C;
    /* 0x2250 */ float x2250;
};

typedef struct ftIceClimberAttributes {
    float x0;
    float x4;
    float x8;
    float xC;
    float x10;
    float x14;
    float x18;
    int x1C;
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
    float x4C_gravity;
    float x50_gravity;
    float x54_terminal_vel;
    float x58_terminal_vel;
    float x5C;
    float x60;
    float x64;
    int x68;
    float x6C;
    float x70;
    u8 _74[0x94 - 0x74];
    float x94;
    float x98;
    u8 _9C[0xB0 - 0x9C];
    float xB0;
    float xB4;
    u8 _B8[0xC4 - 0xB8];
    float xC4;
    float xC8;
    u8 _CC[0xD0 - 0xCC];
    float xD0;
    u8 _D4[0x12C - 0xD4];
    float x12C;
    float x130;
    float x134;
    float x138;
    float x13C;
    float x140;
    float x144;
    float x148;
    float x14C;
    u8 _150[0x15C - 0x150];
} ftIceClimberAttributes;
STATIC_ASSERT(sizeof(ftIceClimberAttributes) == 0x15C);

union ftPp_MotionVars {
    struct ftPp_SpecialSVars {
        /* fp+2340 */ float x0;
        /* fp+2344 */ int x4;
        /* fp+2348 */ struct ftPp_SpecialSVars_x8_t {
            int x0;
            HSD_GObj* x4;
        }* x8;
        /* fp+234C */ int xC;
        /* fp+2350 */ int x10;
        /* fp+2354 */ int x14;
        /* fp+2358 */ int x18;
        /* fp+235C */ float x1C;
    } specials;
    struct {
        /* fp+2340 */ int x0;
    } unk_80123954;
};

#endif
