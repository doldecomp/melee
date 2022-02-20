#ifndef _ftness_h_
#define _ftness_h_

#include <dolphin/types.h>

#include "sysdolphin/baselib/gobj.h"

#include "melee/ft/fighter.h"

typedef struct _ftNessAttributes {
    f32 x0;
    f32 x4;
    f32 x8;
    f32 xC;
    u8 data[0x94 - 0x10];
    f32 unk94;
    u8 data2[0xD9 - 0x98];
} ftNessAttributes;

void ftNess_OnDeath(HSD_GObj* gobj, s32 arg1);
void ftNess_OnLoad(HSD_GObj* gobj);
void func_801148F8(HSD_GObj* gobj);
void func_8011493C(HSD_GObj* gobj);
f32 func_8011495C(Fighter* ft);
void func_80114968(HSD_GObj* gobj, s32 arg1);
void func_80114A48(HSD_GObj* gobj);
void func_80114A90(HSD_GObj* gobj);
void func_80114AD8(HSD_GObj* gobj, s32 arg1);
void func_80114B2C(HSD_GObj* gobj);
void func_80114B6C(HSD_GObj* gobj);

#endif
