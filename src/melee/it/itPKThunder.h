#ifndef MELEE_IT_ITPKTHUNDER_H
#define MELEE_IT_ITPKTHUNDER_H

#include <platform.h>

#include <baselib/forward.h>

#include <dolphin/mtx.h>

typedef struct itPKThunderAttributes {
    float x0_PKTHUNDER_LIFETIME;
    float x4_PKTHUNDER_SPEED;
    float x8_PKTHUNDER_SPAWN_ANGLE;
    float xC_PKTHUNDER_STICK_THRESHOLD;
    float x10_PKTHUNDER_TURN_RADIUS;
} itPKThunderAttributes;

typedef struct itPKThunder_ItemVars {
    HSD_GObj* xDD4[6];
    Vec3 positions[16];
    f32 angles[16];
    f32 xEEC;
    s32 xEF0;
    HSD_GObj* xEF4;
    s32 xEF8;
    s32 xEFC;
    s32 xF00;
    HSD_GObj* xF04;
    HSD_GObj* xF08;
} itPKThunder_ItemVars;

#endif
