#ifndef _ftness_h_
#define _ftness_h_

#include <dolphin/types.h>

#include "sysdolphin/baselib/gobj.h"

#include "melee/ft/fighter.h"

typedef struct _ftNessAttributes {
    u8 data[0x94];
    f32 unk94;
} ftNessAttributes;

void func_801147C0(HSD_GObj* gobj, s32 arg1);
void ftNess_OnLoad(HSD_GObj* gobj);
void func_801148F8(HSD_GObj* gobj);
void func_8011493C(HSD_GObj* gobj);
f32 func_8011495C(Fighter* ft);
void func_80114968(HSD_GObj* gobj);
void func_80114A48(HSD_GObj* gobj);
void func_80114A90(HSD_GObj* gobj);
void func_80114AD8(HSD_GObj* gobj, s32 arg1);
void func_80114B2C(HSD_GObj* gobj);
void func_80114B6C(HSD_GObj* gobj);

#endif
