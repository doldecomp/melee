#ifndef _fighter_h_
#define _fighter_h_

#include <dolphin/types.h>

#include "sysdolphin/baselib/gobj.h"

typedef struct _ftData
{
    /* 0x00 */ s32* common_attr;
    /* 0x04 */ s32* ext_attr;
    u8* x08;
    void* x0C;
    s32 x10;
    s32 x14;
    s32 x18;
    s32 x1C;
    s32 x20;
    s32 x24;
    s32 x28;
    void* x2C;
    s32 x30;
    void* x34;
    s32 x38;
    s32 x3C;
    s32 x40;
    void* x44;
    /* 0x48 */ void* items;
    void* x4C;
    s32 x50;
    s32 x54;
    void* x58;
} ftData;

typedef struct _UnkFlagStruct {
    struct {
        u8 b0 : 1;
        u8 b1 : 1;
        u8 b2 : 1;
        u8 b3 : 1;
        u8 b4 : 1;
        u8 b5 : 1;
        u8 b6 : 1;
        u8 b7 : 1;
    } bits;
} UnkFlagStruct;

typedef struct _FighterBone
{
    u32 *x0_joint; // 0x00
    u32 *x4_joint2; // 0x04 used for interpolation
    u32 data_filler[2];
} FighterBone;

typedef struct _Fighter {
    /* 0x00 */ HSD_GObj* x0_fighter;
    u32 data_filler_0[(0xE0 - 0x4) / 4];
    u32 xE0_airState;
    u32 data_filler_1[(0x10C - 0xE4) / 4];
    /* 0x10C */ ftData* x10C_ftData;
    u32 data_filler_2[(0x2D4 - 0x110) / 4];
    /* 0x2D4 */ void* x2D4_specialAttributes;
    /* 0x2D8 */ void* x2D8_specialAttributes2;
    u32 data_filler_3[(0x5E8 - 0x2DC) / 4];
    /* 0x538 */ FighterBone* x5E8_fighterBones;
    u32 data_filler_4[(0x618 - 0x5EC) / 4];
    /* 0x618 */ s8 x618_flag;
    /* 0x619 */ s8 x619_flag;
    u32 data_filler_5[(0x2224 - 0x61C) / 4];
    /* 0x2224 */ u8 x2224;
    /* 0x2225 */ u8 x2225;
    /* 0x2226 */ UnkFlagStruct x2226_flag;
    /* 0x2227 */ u8 x2227;
    /* 0x2228 */ UnkFlagStruct x2228_flag;
    /* 0x2229 */ u8 data_filler_6[3];
    /* 0x222C */ u32 x222C;
    /* 0x2230 */ u32 x2230;
    /* 0x2234 */ u32 x2234;
    /* 0x2238 */ u32 x2238;
    /* 0x223C */ u32 x223C;
    /* 0x2240 */ u32 x2240;
    /* 0x2244 */ u32 x2244;
    /* 0x2248 */ u32 x2248;
} Fighter;

#endif
