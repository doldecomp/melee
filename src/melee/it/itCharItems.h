/// @file
/// @todo Restructure this, possibly items/chara/types.h
#ifndef MELEE_IT_ITCHARITEMS_H
#define MELEE_IT_ITCHARITEMS_H

#include <platform.h>
#include <baselib/forward.h>

#include <dolphin/mtx/types.h>
#include <baselib/jobj.h>

typedef struct {
    f32 xDD4;
    f32 xDD8;
    f32 xDDC;
    Vec3 xDE0;
} FoxLaserVars;

typedef struct {
    HSD_Joint* xDD4;
    f32 xDD8;
    HSD_JObj* xDDC;
} FoxIllusionVars;

#endif
