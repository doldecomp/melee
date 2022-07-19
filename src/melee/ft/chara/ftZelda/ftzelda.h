#pragma once

#include "melee/ft/ftcommon.h"
#include "melee/lb/lbvector.h"

typedef struct _ftZeldaAttributes {
    f32 x0;
    f32 x4;
    f32 x8;
    f32 xC;
    f32 x10;
    s32 x14;
    f32 x18;
    s32 x1C;
    s32 x20;
    s32 x24;
    s32 x28;
    s32 x2C;
    s32 x30;
    s32 x34;
    f32 x38; // Type confirmed
    f32 x3C; // Type confirmed
    f32 x40; // Type confirmed
    f32 x44; // Type confirmed
    f32 x48;
    f32 x4C; // Type confirmed

    f32 x50;
    f32 x54;
    f32 x58;
    f32 x5C;

    f32 x60; // Type confirmed
    f32 x64;
    f32 x68;
    f32 x6C;
    u8 data_filler_1[0x38];
} ftZeldaAttributes;
