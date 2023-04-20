#ifndef MELEE_FT_CHARA_FTPEACH_TYPES_H
#define MELEE_FT_CHARA_FTPEACH_TYPES_H

#include <platform.h>

struct ftPeach_FighterVars {
    /* 0x222C */ u32 x222C;
    /* 0x2230 */ u32 x2230;
    /* 0x2234 */ u32 x2234;
    /* 0x2238 */ u32 x2238;
    /* 0x223C */ u32 x223C;
    /* 0x2240 */ u32 x2240;
    /* 0x2244 */ u32 x2244;
    /* 0x2248 */ u32 x2248;
};

typedef struct _ftPeachAttributes {
    f32 unk0;
    f32 unk4;
    u8 padding[0xB8];
} ftPeachAttributes;

#endif
