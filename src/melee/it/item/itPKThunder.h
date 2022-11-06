#ifndef MELEE_IT_ITEM_ITPKTHUNDER_H
#define MELEE_IT_ITEM_ITPKTHUNDER_H

#include <dolphin/types.h>

typedef struct _itPKThunderAttributes {
    // at 0x0
    f32 lifetime;

    // at 0x4
    f32 speed;

    // at 0x8
    f32 spawn_angle;

    // at 0xC
    f32 stick_threshold;

    // at 010
    f32 turn_radius;
} itPKThunderAttributes;

typedef struct _PKThunderAttrs {
    HSD_GObj* xDD4[6]; // GObj pointers?
    Vec3 xDEC;         // Start of vars
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
    f32 xEAC; // PK Thunder release angles?
    f32 xEB0;
    f32 xEB4;
    f32 xEB8;
    f32 xEBC;
    f32 xEC0;
    f32 xEC4;
    f32 xEC8;
    f32 xECC;
    f32 xED0;
    f32 xED4;
    f32 xED8;
    f32 xEDC;
    f32 xEE0;
    f32 xEE4;
    f32 xEE8;
    s32 xEEC;
    s32 xEF0;
    HSD_GObj* xEF4;
    HSD_GObj* xEF8;
    HSD_GObj* xEFC;
    HSD_GObj* xF00;
    HSD_GObj* xF04;
    HSD_GObj* xF08;
} PKThunderAttrs;

#endif
