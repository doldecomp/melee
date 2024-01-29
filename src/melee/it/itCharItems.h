/// @file
/// @todo Restructure this, possibly items/chara/types.h
#ifndef MELEE_IT_ITCHARITEMS_H
#define MELEE_IT_ITCHARITEMS_H

#include <dolphin/mtx/types.h>
#include <baselib/jobj.h>

typedef struct {
    float xDD4;
    float xDD8;
    float xDDC;
    Vec3 xDE0;
} FoxLaserVars;

typedef struct {
    HSD_Joint* xDD4;
    float xDD8;
    HSD_JObj* xDDC;
} FoxIllusionVars;

#endif
