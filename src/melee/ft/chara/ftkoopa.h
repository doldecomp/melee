#ifndef _ftkoopa_h_
#define _ftkoopa_h_

#include <global.h>

#include <dolphin/types.h>

#include "sysdolphin/baselib/gobj.h"

#include "melee/ft/fighter.h"

typedef struct _ftKoopaAttributes {
    f32 x0;
    f32 x4;
    f32 x8;
    f32 xC;
    u8 data[0x34 - 0x10];
    f32 unk34;
    f32 unk38;
    f32 unk3C;
    f32 unk40;
    f32 unk44;
    f32 unk48;
    f32 unk4C;
} ftKoopaAttributes;

void func_80132EFC(HSD_GObj *gobj);
void func_8013302C(HSD_GObj *gobj);

#endif
