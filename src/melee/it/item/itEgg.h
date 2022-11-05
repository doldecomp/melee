#ifndef MELEE_IT_ITEM_ITEGG_H
#define MELEE_IT_ITEM_ITEGG_H

#include <ctypes.h>

// Eggs spawned on Yoshi stages or by Chansey.
typedef struct _EggAttrss {
    u8 filler[0x60];
    s32 xE34_heal;
} EggAttrs;

#endif