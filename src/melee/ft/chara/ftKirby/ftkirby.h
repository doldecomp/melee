#ifndef MELEE_FT_CHARA_FTKIRBY_FTKIRBY_H
#define MELEE_FT_CHARA_FTKIRBY_FTKIRBY_H

#include <melee/ft/ftcommon.h>
#include <melee/lb/lbvector.h>

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

unk_t func_800F5AF0();
unk_t func_800F5B20();
unk_t func_800F5B5C();
unk_t func_800F5B3C();
unk_t func_800F5B4C();
unk_t func_800F5954();
unk_t func_800F597C();
unk_t func_800F5A60();
unk_t func_800F598C();
unk_t func_800F5B10();
unk_t func_800F5B00();
unk_t func_800F5A04();
unk_t func_800F5A38();
unk_t func_800F5820();
unk_t func_800F5898();
unk_t func_800F5A88();
unk_t func_800F58AC();
unk_t func_800F5AD8();
unk_t func_800F5AC0();
unk_t func_800F5AB0();
unk_t func_800F58D8();

#endif