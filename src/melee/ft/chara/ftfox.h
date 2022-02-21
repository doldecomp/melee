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
    u8 data_filler_10[0xD1 - 0x10];
} ftFoxAttributes;

BOOL func_800E5534(HSD_GObj* gobj);
void ftFox_OnDeath(HSD_GObj* gobj);
void func_800E5588(HSD_GObj* gobj);
void func_800E55A8(HSD_GObj* gobj, s32 arg1);
void func_800E5688(HSD_GObj* gobj);
void func_800E56D0(HSD_GObj* gobj);
void func_800E5718(HSD_GObj* gobj, s32 arg1);

#endif
