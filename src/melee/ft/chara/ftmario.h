#ifndef _ftmario_h_
#define _ftmario_h_

#include <global.h>

#include <dolphin/types.h>

#include "sysdolphin/baselib/gobj.h"

#include "melee/ft/fighter.h"

typedef struct _ftMarioAttributes {
    /* 0x00 */u8 x0_padding[0x14 - 0x0];
	/* 0x14 */u32 x14;
    /* 0x18 */u8 x14_padding[0x84 - 0x18];
} ftMarioAttributes;

void ftMario_OnDeath(HSD_GObj* gobj);
void func_800E0920(Fighter* ft);
void ftMario_OnLoad(HSD_GObj* gobj);
void func_800E0A00(void);
void func_800E0A20(HSD_GObj* gobj, s32 arg1);
void func_800E0B00(HSD_GObj* gobj);
void func_800E0B48(HSD_GObj* gobj);
void func_800E0B90(HSD_GObj* gobj, s32 arg1);
void func_800E0BE4(HSD_GObj* gobj);
void func_800E0C24(HSD_GObj* gobj);
void func_800E0C68(HSD_GObj* gobj);
void func_800E0CAC(s32 arg1, u32* arg2, u32* arg3);
s32 func_800E0CE0(s32 arg0);

#endif
