#ifndef MELEE_FT_CHARA_FTKIRBY_TYPES_H
#define MELEE_FT_CHARA_FTKIRBY_TYPES_H

#include <platform.h>
#include "ft/forward.h"
#include <baselib/forward.h>

#include <common_structs.h>
#include <placeholder.h>

struct ftKb_FighterVars {
    /* fp+222C */ struct ftKb_Hat {
        /* fp+222C */ UNK_T x0;
        /* fp+2230 */ uint x4;
        /* fp+2234:0 */ u8 x8_b0 : 1;
        /* fp+2235 */ u8 x9[3];
        /* fp+2238 */ FighterKind victim_kind;
        /* fp+223C */ HSD_JObj* jobj;
        /* fp+2240 */ UNK_T x14;
        /* fp+2244 */ UNK_T x18;
        /* fp+2248 */ UNK_T x1C;
        /* fp+224C */ UNK_T x20;
        /* fp+2250 */ UNK_T x24;
    } hat;
    /* fp+224C */ u8 _28[0x60 - 0x28];
    /* fp+228C */ UNK_T x60;
    /* fp+2290 */ UNK_T x64;
    /* fp+2294 */ u8 _68[0x9C - 0x68];
    /* fp+22C8 */ int x9C;
    /* fp+22CC */ UNK_T xA0;
    /* fp+22D0 */ UNK_T xA4;
    /* fp+22D4 */ int xA8;
    /* fp+22D8 */ UNK_T xAC;
    /* fp+22DC */ UNK_T xB0;
    /* fp+22E0 */ int xB4;
    /* fp+22E4 */ UNK_T xB8;
    /* fp+22E8 */ int xBC;
};
STATIC_ASSERT(sizeof(struct ftKb_FighterVars) == 0xC0);

struct ftKb_DatAttrs {
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
    u8 data_filler_1[0x168 - 0x30];
    float x168;
    u8 data_filler_2[0x190 - 0x16C];
    s32 x190;
    u8 data_filler_3[0x384 - 0x194];
    float x384;
    u8 data_filler_4[0x424 - 0x388];
};

#endif
