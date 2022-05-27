#ifndef _ftpeach_h_
#define _ftpeach_h_

#include <global.h>

#include <dolphin/types.h>

#include "sysdolphin/baselib/gobj.h"

#include "melee/ft/fighter.h"

typedef struct _ftPeachAttributes {
    f32 unk0;
    f32 unk4;
    u8 padding[0xB8];
} ftPeachAttributes;

void ftPeach_OnDeath(HSD_GObj* gobj);

#endif
