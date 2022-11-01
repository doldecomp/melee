#ifndef MELEE_FT_CHARA_FTCRAZYHAND_FTCRAZYHAND_H
#define MELEE_FT_CHARA_FTCRAZYHAND_FTCRAZYHAND_H

#include <melee/ft/ftcommon.h>
#include <melee/lb/lbvector.h>

typedef struct _ftCrazyHandAttributes {
    s32 x0;
    s32 x4;
    s32 x8;
    s32 xC;
    s32 x10;
    f32 x14;
    f32 x18;
    f32 x1C;
    s32 x20;
    s32 x24;
    f32 x28;
    f32 x2C;
    Vec2 x30_pos2;
    f32 x38;
    f32 x3C;
    Vec3 x40_pos;
    f32 x4C;
    Vec2 x50;
    f32 x58;
    f32 x5C;
    f32 x60;
    f32 x64;
    f32 x68;
    s32 x6C;
    s32 x70;
    s32 x74;
    f32 x78;
    s32 x7C;
    f32 x80;
    s32 x84;
    Vec2 x88_pos;
    s32 x90;
    s32 x94;
    f32 x98;
    f32 x9C;
    s32 xA0;
    f32 xA4;
    Vec2 xA8_pos;
    s32 xB0;
    s32 xB4;
    f32 xB8;
    Vec2 xBC_pos;
    Vec2 xC4_pos;
    Vec2 xCC_pos;
    f32 xD4;
    f32 xD8;
    f32 xDC;
    f32 xE0;
    f32 xE4;
    f32 xE8;
    s32 xEC;
    s32 xF0;
    f32 xF4;
    f32 xF8;
    f32 xFC;
    f32 x100;
    f32 x104;
    f32 x108;
    f32 x10C;
    Vec2 x110_pos;
    Vec2 x118_pos;
    f32 x120;
    Vec2 x124_pos;
    Vec2 x12C_pos;
    Vec2 x134_pos;
    Vec2 x13C_pos;
} ftCrazyHandAttributes;

void ftCrazyHand_80155FCC(HSD_GObj* fighter_gobj);
void ftCrazyHand_80156014(HSD_GObj* fighter_gobj);

#endif