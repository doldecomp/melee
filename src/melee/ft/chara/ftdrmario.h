#ifndef _ftdrmario_h_
#define _ftdrmario_h_

#include <global.h>

#include <dolphin/types.h>

#include "sysdolphin/baselib/gobj.h"

#include "melee/ft/fighter.h"

typedef struct _ftDrMarioAttributes {
    u8 pad_x0[4];
    u32 x4;
    u8 pad_x8[4];
    u32 xC;
    u8 pad_x10[4];
    u32 x14;
} ftDrMarioAttributes;

void ftDrMario_OnDeath(HSD_GObj*);
void ftDrMario_OnLoad(HSD_GObj*);
void func_80149540(HSD_GObj*);
void func_80149560(HSD_GObj*, s32);
void func_80149640(HSD_GObj*);
void func_80149688(HSD_GObj*);
void func_801496D0(HSD_GObj*, s32);
void func_80149724(HSD_GObj*);
void func_80149744(HSD_GObj*);
void func_80149788(HSD_GObj*);
void func_801497CC(HSD_GObj*);
BOOL func_80149844(HSD_GObj*);
void func_801498A0(HSD_GObj*);
u32 func_801498EC(HSD_GObj*);
void func_80149910(HSD_GObj*);


// ftdrmario_2.c
void func_80149954(HSD_GObj*);
void func_80149A6C(HSD_GObj*);
void func_80149A8C(HSD_GObj*);
void func_80149AAC(HSD_GObj*);

#endif
