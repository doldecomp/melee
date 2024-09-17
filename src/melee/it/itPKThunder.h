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
    Vec3 xDEC;
    Vec3 xDFC;
    Vec3 xE08;
    Vec3 xE14;
    Vec3 xE20;
    Vec3 xE2C;
    Vec3 xE38;
    Vec3 xE44;
    Vec3 xE50;
    Vec3 xE5C;
    Vec3 xE68;
    Vec3 xE74;
    Vec3 xE80;
    Vec3 xE8C;
    Vec3 xE98;
    Vec3 xEA0;
    float xEAC; // PK Thunder release angles?
    float xEB0;
    float xEB4;
    float xEB8;
    float xEBC;
    float xEC0;
    float xEC4;
    float xEC8;
    float xECC;
    float xED0;
    float xED4;
    float xED8;
    float xEDC;
    float xEE0;
    float xEE4;
    float xEE8;
    s32 xEEC;
    s32 xEF0;
    HSD_GObj* xEF4;
    HSD_GObj* xEF8;
    HSD_GObj* xEFC;
    HSD_GObj* xF00;
    HSD_GObj* xF04;
    HSD_GObj* xF08;
} itPKThunder_ItemVars;

#endif
