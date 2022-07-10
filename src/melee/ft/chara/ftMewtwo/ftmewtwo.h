#ifndef _ftMewTwo_h_
#define _ftMewTwo_h_

#include <global.h>

#include <dolphin/types.h>

#include "sysdolphin/baselib/gobj.h"

#include "melee/ft/fighter.h"

typedef struct _ftMewTwoAttributes {
    f32 x0;
    s32 x4;
    s32 x8;
    s32 xC;
    s32 x10;
    u8 x14_filler[0x2C - 0x14];
    s32 x2C;
    u8 x30_filler[0x48 - 0x30];
    s32 x48;
    s32 x4C;
    s32 x50;
    f32 x54;
    u8 x58_filler[0x70 - 0x58];
    s32 x70;
    s32 x74;
    s32 x78;
    s32 x7C;
    f32 x80;
    f32 x84;
} ftMewTwoAttributes; 

void ftMewtwo_OnDeath(HSD_GObj* gobj);

#endif
