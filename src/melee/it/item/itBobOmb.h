#ifndef MELEE_IT_ITEM_ITBOBOMB_H
#define MELEE_IT_ITEM_ITBOBOMB_H

#include <ctypes.h>

typedef struct _BobOmbAttrs {
    s32 xDD4;
    s32 xDD8;
    s32 xDDC;
    s32 xDE0;
    s32 xDE4;
    s32 xDE8;
    f32 xDEC;
} BobOmbAttrs;

typedef struct _BobOmbRain {
    s32 x0;
    s32 x4;
    Vec3 x8_vec;
    s32 x14;
    s32 x18;
    UnkFlagStruct x1C;
} BobOmbRain;

#endif