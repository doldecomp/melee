#ifndef _ness_h_
#define _ness_h_
#include <global.h>
#include "sysdolphin/baselib/gobj.h"
#include <dolphin/types.h>
#include "melee/ft/fighter.h"
struct ftNess {
    u8 unkData[0x94];
    f32 unk94;
};
s32 func_8026B2B4(s32 arg);
void func_80070CC4(struct _HSD_GObj* arg0, int arg1);
void func_80074A4C(struct _HSD_GObj* arg0, int arg1, int arg2);
void ftNess_Reset(struct _HSD_GObj* arg0, s32 arg1);
void func_8011B0F8(s32 arg);
void func_8011493C(s32 arg);
f32 func_8011495C(struct Fighter* arg0);
void func_80114A48(struct _HSD_GObj* arg0, s32 arg1);
#endif