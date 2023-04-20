#ifndef MELEE_FT_CHARA_FTPOPO_TYPES_H
#define MELEE_FT_CHARA_FTPOPO_TYPES_H

#include <platform.h>

#include <common_structs.h>

struct ftPopo_FighterVars {
    /* 0x222C */ uint x222C;
    /* 0x2230 */ UnkFlagStruct x2230;
    /* 0x2231 */ u8 filler_x2231[3];
    /* 0x2234 */ u32 x2234;
    /* 0x2238 */ u32 x2238;
    /* 0x223C */ u32 x223C;
    /* 0x2240 */ u32 x2240;
    /* 0x2244 */ u32 x2244;
    /* 0x2248 */ u32 x2248;
    /* 0x224C */ u32 x224C;
    /* 0x2250 */ f32 x2250;
};

typedef struct _ftIceClimberAttributes {
    f32 x0;
    f32 x4;
    f32 x8;
    f32 xC;
    f32 x10;
    f32 x14;
    f32 x18;
    s32 x1C;
    s32 x20;
    s32 x24;
    s32 x28;
    s32 x2C;
    u8 data_filler_1[0xC4 - 0x30];
    f32 xC4;
    f32 xC8;
    u8 data_filler_2[0x90];
} ftIceClimberAttributes;

#endif
