/// @file
/// @todo Restructure this, possibly items/common/types.h
#ifndef MELEE_IT_ITCOMMONITEMS_H
#define MELEE_IT_ITCOMMONITEMS_H

#include <platform.h>
#include <baselib/forward.h>

#include <placeholder.h>

typedef struct {
    bool x0;
    bool x4;
} ItCapsuleAttrs;

typedef struct {
    /* ip+DD4 */ float dir;
    /* ip+DD8 */ float x4;
    /* ip+DDC */ float x8;
    /* ip+DE0 */ float xC;
    /* ip+DE4 */ float xvel;
    /* ip+DE8 */ float yvel;
} ItStarVars;

struct itSword_ItemVars {
    /* ip+DD4 */ UNK_T x0;
    /* ip+DD8 */ int x4;
    /* ip+DDC */ int x8;
    /* ip+DE0 */ int xC;
    /* ip+DE4 */ float x10;
    /* ip+DE8 */ float x14;
    /* ip+DEC */ float x18;
    /* ip+DF0 */ int x1C;
    /* ip+DF4 */ int x20;
    /* ip+DF8 */ int x24;
    /* ip+DFC */ float x28;
    /* ip+E00 */ float x2C;
    /* ip+E04 */ float x30;
    /* ip+E08 */ int x34;
    /* ip+E0C */ int x38;
    /* ip+E10 */ int x3C;
    /* ip+E14 */ float x40;
    /* ip+E18 */ float x44;
    /* ip+E1C */ float x48;
    /* ip+E20 */ float x4C;
    /* ip+E24 */ float x50;
    /* ip+E28 */ int x54;
    /* ip+E2C */ float x58;
};

typedef struct BobOmbVars {
    s32 xDD4;
    s32 xDD8;
    s32 xDDC;
    s32 xDE0;
    s32 xDE4;
    s32 xDE8;
    float xDEC;
} BobOmbVars;

typedef struct HeartContainerVars {
    s32 xDD4_heal;
} HeartContainerVars;

typedef struct MaximTomatoVars {
    s32 xDD4_heal;
} MaximTomatoVars;

typedef struct FoodVars {
    s32 xDD4_unk;
    s32 xDD8_heal;
} FoodVars;

typedef struct {
    u32 x0;
} ItLGunVars;

typedef struct EggVars // Eggs spawned on Yoshi stages / by Chansey
{
    u8 filler[0x60];
    s32 xE34_heal;
} EggVars;

typedef struct WhispyAppleVars {
    s32 xDD4_heal;
} WhispyAppleVars;

/// @remarks Might be shared?
typedef struct itUnkAttributes {
    float x0_float;
    float x4_float;
    float x8;
    float xC;
    float x10;
} itUnkAttributes;

typedef struct {
    HSD_JObj* x0;
} ItMatoVars;

typedef struct {
    u8 padding[0xE10 - 0xDD4];
    int xE10;
} itShellVars;

typedef struct itPokemonAttributes {
    f32 x0;
    s32 timer;
    s32 max;
    s32 xC;
    s32 x10;
    s32 x14;
    s32 x18;
} itPokemonAttributes;

typedef struct {
    u8 padding[0xE34 - 0xDD4];
    s32 timer;
} ItPokemonVars;

typedef struct {
    int x0;
    HSD_JObj* jobj;
} itTargetVars;

#endif
