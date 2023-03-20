#ifndef MELEE_FT_CHARA_FTPIKACHU_TYPES_H
#define MELEE_FT_CHARA_FTPIKACHU_TYPES_H

#include <dolphin/mtx/types.h>
#include <platform.h>

typedef struct _ftPikachuAttributes {
    f32 x0;
    f32 x4;
    f32 x8;
    f32 xC;
    f32 x10;
    u32 x14;
    u32 x18;
    f32 x1C;
    f32 x20;
    f32 x24;
    f32 x28;
    f32 x2C;
    f32 x30;
    f32 x34;
    f32 x38;
    f32 x3C;
    f32 x40;
    f32 x44;
    f32 x48;
    f32 x4C;
    f32 x50;
    f32 x54;
    f32 x58;
    s32 x5C;
    s32 x60; // up b zip duration
    f32 x64;
    f32 x68; // up b angle offset 1
    Vec3 x6C_scale;
    f32 x78; // up b angle offset 2
    Vec3 x7C_scale;
    f32 x88;
    f32 x8C; // up b minimum stick magnitude

    f32 x90; // up b zip stick magnitude to velocity slope
    f32 x94; // up b zip stick magnitude to velocity intercept
    f32 x98; // second zip velocity decay
    f32 x9C;

    s32 xA0;
    f32 xA4;
    s32 xA8; // minimum stick angle difference between two up b zips
    f32 xAC;

    f32 xB0;
    f32 xB4;
    f32 xB8;
    f32 xBC;

    f32 xC0;
    f32 xC4;
    f32 xC8;
    f32 xCC;

    f32 xD0;
    s32 xD4;
    s32 xD8;
    u32 xDC;

    f32 height_attributes[6];
} ftPikachuAttributes;

union ftPikachu_StateVars {
    /// @todo Proper state name.
    struct ftPikachu_State2Vars {
        s32 x0;
    } unk2;

    /// @todo Proper state name.
    struct ftPikachu_State3Vars {
        s32 x0;
    } unk3;

    /// @todo Proper state name.
    struct ftPikachu_State4Vars {
        uint x0;
        s32 x4;
        s32 x8;
        int xC;
        Vec2 x10;
        s32 x18;
        Vec2 x1C;
        f32 x24;
    } unk4;

    /// @todo Proper state name.
    struct ftPikachu_State5Vars {
        u32 x0;
        u32 x4;
    } unk5;
};

#endif
