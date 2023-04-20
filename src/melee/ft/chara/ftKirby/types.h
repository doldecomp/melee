#ifndef MELEE_FT_CHARA_FTKIRBY_TYPES_H
#define MELEE_FT_CHARA_FTKIRBY_TYPES_H

#include <platform.h>

#include <common_structs.h>

struct ftKirby_FighterVars {
    /* 0x222C */ s32 x222C;
    /* 0x2230 */ u32 x2230;
    /* 0x2234 */ UnkFlagStruct x2234;
    /* 0x2235 */ u8 x2235[3];
    /* 0x2238 */ u32 x2238;
    /* 0x223C */ u32 x223C;
    /* 0x2240 */ u32 x2240;
    /* 0x2244 */ u32 x2244;
    /* 0x2248 */ u32 x2248;
    /* 0x224C */ u8 x224C[0x228C - 0x224C];
    /* 0x228C */ u32 x228C;
    /* 0x2290 */ u32 x2290;
    /* 0x2294 */ u8 x2294[0x22C8 - 0x2294];
    /* 0x22C8 */ s32 x22C8;
    /* 0x22CC */ s32 x22CC;
    /* 0x22D0 */ s32 x22D0;
    /* 0x22D4 */ s32 x22D4;
    /* 0x22D8 */ s32 x22D8;
    /* 0x22DC */ s32 x22DC;
    /* 0x22E0 */ s32 x22E0;
    /* 0x22E4 */ s32 x22E4;
    /* 0x22E8 */ s32 x22E8;
};

typedef struct _ftKirbyAttributes {
    f32 x0;
    f32 x4;
    f32 x8;
    f32 xC;
    f32 x10;
    s32 x14;
    f32 x18;
    s32 x1C;
    s32 x20;
    s32 x24;
    s32 x28;
    s32 x2C;
    u8 data_filler_1[0x168 - 0x30];
    f32 x168;
    u8 data_filler_2[0x190 - 0x16C];
    s32 x190;
    u8 data_filler_3[0x384 - 0x194];
    f32 x384;
    u8 data_filler_4[0x424 - 0x388];
} ftKirbyAttributes;

#endif
