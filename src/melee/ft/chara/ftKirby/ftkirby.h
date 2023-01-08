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

void func_800EED50(s32, s32);
void func_800F1D24(void);
void func_800F5BA4(void);
void func_800F5C34(void);
void func_800F5D04(HSD_GObj* fighter_gobj, BOOL);
void ftKirby_OnItemPickup(HSD_GObj* fighter_gobj, BOOL bool);

#endif
