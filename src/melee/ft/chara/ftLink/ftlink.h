#ifndef MELEE_FT_CHARA_FTLINK_FTLINK_H
#define MELEE_FT_CHARA_FTLINK_FTLINK_H

#include <dolphin/types.h>

#include <sysdolphin/baselib/gobj.h>

#include <melee/ft/ftcommon.h>

typedef struct _ftLinkAttributes {
    s32 x0;
    s32 x4;
    s32 x8;
    s32 xC;
    s32 x10;
    s32 x14_pad[(0x28 - 0x14) / 4];
    f32 x28;
    s32 x2C;
    s32 x30_pad[(0x48 - 0x30) / 4];
    s32 x48;
    s32 x4C;
    s32 x50;
    f32 x54;
    s32 x58_pad[(0xBC - 0x58) / 4];
    s32 xBC;
    s32 xC0;
    f32 xC4;
    s32 xC8_pad[(0xD8 - 0xC8) / 4];
    f32 xD8;
} ftLinkAttributes;

void ftLink_OnItemDrop(HSD_GObj* fighter_gobj, BOOL arg1);
void ftLink_OnItemPickup(HSD_GObj* fighter_gobj, BOOL bool);

#endif