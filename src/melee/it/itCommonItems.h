/// @file
/// @todo Restructure this, possibly items/common/types.h
#ifndef MELEE_IT_ITCOMMONITEMS_H
#define MELEE_IT_ITCOMMONITEMS_H

#include <platform.h>
#include <baselib/forward.h>

#include <common_structs.h>
#include <placeholder.h>
#include <dolphin/mtx/types.h>

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
    /* ip+DD4 */ int x0;
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

typedef struct itBatAttributes {
    int x0;
    int x4;
    int x8;
    f32 xC_vel;
} itBatAttributes;

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
    union {
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
        u32 flags;
    } xDD8;
    s32 xDDC;
    u8 xDE0_filler[8];
    f32 xDE8_float;
    f32 xDEC;
} HeartContainerVars;

typedef struct MaximTomatoVars {
    s32 heal_amount;
    union {
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
        u32 flags;
    } x4;
    s32 x8;
} MaximTomatoVars;

typedef struct {
    int x0;
    int x4;
    int x8;
    int xC;
    int x10;
    f32 x14;
} MaximTomatoSpecialAttr;

typedef struct FoodVars {
    s32 xDD4_unk;
    s32 xDD8_heal;
} FoodVars;

typedef struct ItLGunAttr {
    int x0;
    float pos_x;
    float pos_y;
    float pos_z;
} ItLGunAttr;

typedef struct ItLGunVars {
    int x0; // May refer to item ID of itlgunbeam?
} ItLGunVars;

typedef struct ItLGunBeamAttr {
    float x0;  // lifetime
    float x4;  // related to position calcs for var xDFC
    float x8;  // related to position calcs for var xDFC
    float xC;  // related to position calcs for var xDF8
    float x10; // related to position calcs for var xDF8
} ItLGunBeamAttr;

typedef struct ItLGunBeamVars {
    /* x0 */ Vec3 xDD4;  // pos
    /* xC */ Vec3 xDE0;  // position
    /* x18 */ Vec3 xDEC; // position
    /* x24 */ f32 xDF8;  // angle?
    /* x28 */ f32 xDFC;  // angle?
    /* x2C */ f32 xE00;  // lifetime?
    /* x30 */ f32 xE04;  // ??
} ItLGunBeamVars;

typedef struct ItLGunRayAttr {
    float speed;
    float lifetime;
    float x8; // reference scale value?
} ItLGunRayAttr;

typedef struct ItLGunRayVars {
    /* ip+DD4 */ float scale;
    /* ip+DD8 */ float angle;
    /* ip+DDC */ float speed;
    /* ip+DE0 */ Vec3 pos;
} ItLGunRayVars;

/// Eggs spawned on Yoshi stages / by Chansey
typedef struct EggVars {
    /* +0 */ bool x0;
    /* +4 */ int rand_max;
    /* +8 */ u8 _8[0x60 - 0x8];
    /* +60 */ int heal_amount;
} EggVars;

typedef struct itHeiHoVars {
    f32 x0;
    f32 x4;
    UnkFlagStruct x8;
    f32 xC;
    f32 x10;
    f32 x14;
    f32 x18;
    f32 x1C;
    s8 x20;
    s8 x21;
    s8 x22;
    s8 x23;
    s32 x24;
    f32 x28;
    s32 x2C;
    f32 x30;
    f32 x34;
    f32 x38;
    Vec3 x3C;
    f32 x48;
    f32 x4C;
    f32 x50;
    HSD_GObj* x54;
    f32 x58;
    f32 x5C;
    f32 x6C;
    f32 x60;
    f32 x64;
    f32 x68;
    f32 x7C;
    f32 x70;
    f32 x74;
    f32 x78;
} itHeiHoVars;

typedef struct itFoodsVars {
    s32 x0;
    s32 x4;
} itFoodsVars;

typedef struct itFoodsAttributes {
    s32 x0;
    HSD_Joint* x4;
    s32 x8;
    s32 xC;
} itFoodsAttributes;

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
    int x0;
    int x4;

} itTomatoVars;

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
    int x64;
} ItPokemonVars;

typedef struct {
    int x0;
    HSD_JObj* jobj;
} itTargetVars;

typedef struct MewVars {
    f32 x0;
    f32 x4;
    f32 x8;
    f32 xC;
} MewVars;

typedef struct itCoinAttributes {
    f32 x0;
    f32 x4;
    f32 x8;
    f32 xC;
    f32 x10;
    f32 x14;
    f32 x18;
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
} itCoinAttributes;

typedef struct CoinVars {
    int x0;
    int x4;
    f32 x8;
    f32 xC;
    int x10;
    int x14;
} CoinVars;

typedef struct FFlowerVars {
    int x0;
    uint x4;
} FFlowerVars;

typedef struct FFlowerFlameVars {
    /* +0 */ Vec3 pos;
    /* +C */ f32 unk;
} FFlowerFlameVars;

typedef struct HassamVars {
    f32 x0;
    f32 x4;
    f32 x8;
    f32 xC;
    f32 x10;
    f32 x14;
    s32 x18;
    s32 x1C;
    s32 x20;
    u8 padding[0x5C - 0x20];
    Vec3 x5C;
    f32 x68;
} HassamVars;

typedef struct KinokoVars {
    f32 x0;
    f32 x4;
    f32 x8;
    f32 xC;
} KinokoVars;

#endif
