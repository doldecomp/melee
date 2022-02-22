#ifndef _ftclink_h_
#define _ftclink_h_

#include <melee/ft/fighter.h>
#include <sysdolphin/baselib/gobj.h>

typedef struct _CLinkAttributes {
    s32 x0_pad[(0xC - 0x0) / 4];
    s32 xC;
    s32 x10;
    s32 x14_pad[(0x2C - 0x14) / 4];
    s32 x2C;
    s32 x30_pad[(0x48 - 0x30) / 4];
    s32 x48;
    s32 x4C;
    s32 x50;
    f32 x54;
    s32 x58_pad[(0xBC - 0x58) / 4];
    s32 xBC;
    s32 xC0;
    s32 xC4;
    s32 xC8_pad[(0xD8 - 0xC8) / 4];
    f32 xD8;
} CLinkAttributes;

void func_80148F38(HSD_GObj*, s32);
void func_80149018(HSD_GObj*, s32);

#define ITEM_CLINK_MILK 0x7B

#endif
