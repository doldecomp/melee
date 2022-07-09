#ifndef _ftfox_h_
#define _ftfox_h_

#include <global.h>

#include <dolphin/types.h>

#include "sysdolphin/baselib/gobj.h"

#include "melee/ft/fighter.h"

typedef struct _ftFoxAttributes {
    f32 x0;
    f32 x4;
    f32 x8;
    f32 xC;

    f32 x10;
    f32 x14;
    f32 x18;
    s32 x1C;

    s32 x20;

    u8 data_filler_10[0xD1 - 0x24];
} ftFoxAttributes;

BOOL func_800E5534(HSD_GObj* gobj);
void ftFox_OnDeath(HSD_GObj* gobj);
void func_800E5588(HSD_GObj* gobj);
void ftFox_OnItemPickup(HSD_GObj* gobj, BOOL arg1);
void ftFox_OnItemInvisible(HSD_GObj* gobj);
void ftFox_OnItemVisible(HSD_GObj* gobj);
void ftFox_OnItemDrop(HSD_GObj* gobj, BOOL arg1);

#endif
