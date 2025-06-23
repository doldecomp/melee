/// @file
/// @todo Restructure this, possibly items/common/types.h
#ifndef MELEE_IT_ITCOMMONITEMS_H
#define MELEE_IT_ITCOMMONITEMS_H

#include <platform.h>
#include <placeholder.h>

#include <melee/gr/forward.h>

#include "it/forward.h"
#include <baselib/forward.h>

#include <common_structs.h>
#include <dolphin/mtx.h>

struct ECB {
    f32 top;
    f32 bottom;
    f32 right;
    f32 left;
};

typedef struct {
    bool x0;
    bool x4;
} itCapsule_ItemVars;

typedef struct {
    bool x0; // [true]
    s32 x4;  // [8]
} ItCapsuleAttr;

typedef struct {
    /* ip+DD4 */ float dir;
    /* ip+DD8 */ float x4;
    /* ip+DDC */ float x8;
    /* ip+DE0 */ float xC;
    /* ip+DE4 */ float xvel;
    /* ip+DE8 */ float yvel;
} itStar_ItemVars;

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

typedef struct itBombHei_ItemVars {
    s32 xDD4;
    s32 xDD8;
    s32 xDDC;
    s32 xDE0;
    s32 xDE4;
    s32 xDE8;
    float xDEC;
} itBombHei_ItemVars;

typedef struct itHeart_ItemVars {
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
        };
        u32 flags;
    } xDD8;
    s32 xDDC;
    u8 xDE0_filler[8];
    f32 xDE8_float;
    f32 xDEC;
} itHeart_ItemVars;

typedef struct HeartContainerAttr {
    s32 x0_heal; // [100]
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
    } x4;    // [999]
    s32 x8;  // [1200]
    s32 xC;  // [1140]
    s32 x10; // [120]
    f32 x14; // y velocity? [1.5]
    f32 x18; // y rotation? [0.0349066]
} HeartContainerAttr;

typedef struct itTomato_ItemVars {
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
        };
        u32 flags;
    } x4;
    s32 x8;
} itTomato_ItemVars;

typedef struct {
    int x0;
    int x4;
    int x8;
    int xC;
    int x10;
    f32 x14;
} MaximTomatoSpecialAttr;

typedef struct itLGun_ItemVars {
    /*  +0 ip+DD4 */ int timer;
} itLGun_ItemVars;

typedef struct ItLGunAttr {
    int max_ammo; // [16]
    Vec3 pos;     // [0, 2.128, 6.668]
} ItLGunAttr;

typedef struct itLGunRay_ItemVars {
    /* +0 ip+DD4 */ float scale;
    /* +4 ip+DD8 */ float angle;
    /* +8 ip+DDC */ float speed;
    /* +C ip+DE0 */ Vec3 pos;
} itLGunRay_ItemVars;

typedef struct ItLGunRayAttr {
    /* +0 */ float speed;     // [5]
    /* +4 */ float lifetime;  // [80]
    /* +8 */ float max_scale; // [3]
} ItLGunRayAttr;

typedef struct itLGunBeam_ItemVars {
    /*  +0 ip+DD4 */ Vec3 position0;
    /*  +C ip+DE0 */ Vec3 position1;
    /* +18 ip+DEC */ Vec3 velocity;
    /* +24 ip+DF8 */ f32 angle0;
    /* +28 ip+DFC */ f32 angle1;
    /* +2C ip+E00 */ f32 lifetime;
    /* +30 ip+E04 */ int xE04;
} itLGunBeam_ItemVars;

typedef struct ItLGunBeamAttr {
    float lifetime; // lifetime - [18]
    float x4;       // related to position calcs for var angle1 - [1]
    float x8;       // related to position calcs for var angle1 - [2]
    float xC;       // related to position calcs for var angle0 - [1.22173]
    float x10;      // related to position calcs for var angle0 - [2/3 * pi]
} ItLGunBeamAttr;

/// Eggs spawned on Yoshi stages / by Chansey
typedef struct itEgg_ItemVars {
    /* +0 */ bool x0;
    /* +4 */ int rand_max;
    /* +8 */ u8 _8[0x60 - 0x8];
    /* +60 */ int heal_amount;
} itEgg_ItemVars;

typedef struct itHeiho_ItemVars {
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
} itHeiho_ItemVars;

typedef struct itFoods_ItemVars {
    /* +0 ip+DD4 */ s32 x0;
    /* +4 ip+DD8 */ s32 heal_amount;
} itFoods_ItemVars;

typedef struct itFoodsAttributes {
    s32 x0;
    HSD_Joint* x4;
    s32 x8;
    s32 xC;
} itFoodsAttributes;

typedef struct itWhispyApple_ItemVars {
    s32 xDD4_heal;
} itWhispyApple_ItemVars;

typedef struct itFreeze_ItemVars {
    /*  +0 */ char pad_0[0x1C];
    /* +1C */ int unk_1C;
} itFreeze_ItemVars;

typedef struct itPeachTurnipAttributes {
    f32 x0_lifetime;
    s32 x4_length; // length of x8, should be 8 for the number of turnip types
    struct {
        s32 x0_odds;
        s32 x4_damage;
    } x8 UNK_SIZE_ARRAY;
} itPeachTurnipAttributes;

typedef struct itPeachTurnip_ItemVars {
    /*  +0 ip+DD4 */ UnkFlagStruct xDD4;
    /*  +4 ip+DD8 */ s32 xDD8; // turnip type index
    /*  +8 ip+DDC */ s32 xDDC_damage;
    /*  +C ip+DE0 */ f32 xDE0_scl; // Scale - Mr. Saturn, Turnip
    /*  +10 ip+DE4 */ HSD_GObj* xDE4_owner;
    /*  +14 ip+DE8 */ f32 xDE8_scl; // Scale - Bob-omb
} itPeachTurnip_ItemVars;

typedef struct itPikachutJoltGround_ItemVars {
    /* +0 +DD4 */ char pad_0[0x8];
    /* +8 +DDC */ UNK_T unk_8;
} itPikachutJoltGround_ItemVars;

typedef struct itSamusGrapple_ItemVars {
    /*  +0 +DD4 */ char pad_0[0x10];
    /* +10 +DE4 */ UNK_RET (*unk_10)(UNK_PARAMS);
} itSamusGrapple_ItemVars;

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
    HSD_JObj* x4;
} itMato_ItemVars;

typedef struct {
    int x0;
    int x4;
} itTomatoVars;

typedef struct itTincle_ItemVars {
    /*  +0 ip+DD4 */ u8 x0[0x54 - 0x0];
    /* +54 ip+E28 */ float x54;
} itTincle_ItemVars;

typedef struct {
    /* ip+DD4 */ char pad_0[0x3C];
    /* ip+E10 */ int xE10;
    /* ip+E14 */ char pad_40[0xC];
    /* ip+E24 */ Vec3 vel;
} itGShell_ItemVars;

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
    s16 x0;
    u8 padding[0xE34 - 0xDD8];
    s32 timer;
    int x64;
} itPokemon_ItemVars;

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

typedef struct itCoin_ItemVars {
    int x0;
    int x4;
    f32 x8;
    f32 xC;
    int x10;
    int x14;
} itCoin_ItemVars;

typedef struct itFFlower_ItemVars {
    int x0;
    u32 x4;
} itFFlower_ItemVars;

typedef struct FFlowerAttr {
    int x0;    // [120]
    int x4;    // [1200]
    int x8;    // [1140]
    int xC;    // [120]
    float x10; // [1.5]
    float x14;
} FFlowerAttr;

typedef struct itFFlowerFlame_ItemVars {
    /* +0 */ Vec3 pos;
    /* +C */ f32 unk;
} itFFlowerFlame_ItemVars;

typedef struct itHassam_ItemVars {
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
} itHassam_ItemVars;

typedef struct itKinoko_ItemVars {
    f32 x0;
    Vec3 x4;
    // f32 x8;
    // f32 xC;
} itKinoko_ItemVars;

typedef struct itNokoNoko_ItemVars {
    f32 x0;
    s32 x4;
    f32 x8;
    f32 xC;
    f32 x10;
    s32 x14;
    s32 x18;
    s32 x1C;
    s32 x20;
    s32 x24;
    s32 x28;
    s32 x2C;
    s32 x30;
    f32 x34;
    f32 x38;
    s32 x3C;
    s32 x40;
    s32 x44;
    f32 x48;
    f32 x4C;
    f32 x50;
    f32 x54;
    f32 x58;
    f32 x5C;
    f32 x60;
    f32 x64;
    f32 x68;
    f32 x6C;
    f32 x70;
    ECB x74;
    f32 x84;
    f32 x88;
    f32 x8C;
    f32 x90;
    f32 x94;
    f32 x98;
    f32 x9C;
} itNokoNoko_ItemVars;

typedef struct itNokoNoko_DatAttrs2 {
    s32 x0;
    f32 x4;
} itNokoNoko_DatAttrs2;

typedef struct itNokoNoko_DatAttrs {
    itNokoNoko_DatAttrs2* x0;
    f32 x4;
    f32 x8;
} itNokoNoko_DatAttrs;

typedef struct itTaruCann_DatAttrs {
    /*  +0 */ char pad_0[0x28];
    /* +28 */ int x28;
    /* +2C */ int x2C;
} itTaruCann_DatAttrs;

typedef struct itKlap_ItemVars {
    /*  +0 ip+DD4 */ f32 x0;
    /*  +4 ip+DD8 */ f32 x4;
    /*  +8 ip+DDC */ f32 x8;
    /*  +C ip+DE0 */ f32 xC;
    /* +10 ip+DE4 */ f32 x10;
    /* +14 ip+DE8 */ f32 x14;
    /* +18 ip+DEC */ f32 x18;
    /* +1C ip+DF0 */ f32 x1C;
    /* +20 ip+DF4 */ f32 x20;
    /* +24 ip+DF8 */ f32 x24;
    /* +28 ip+DFC */ f32 x28;
} itKlap_ItemVars;

typedef struct itChicorita_ItemVars {
    /* ip+DD4 */ u8 _0[0x60 - 0x0];
    /* ip+E34 */ s32 x60; // timer?
    /* ip+E38 */ f32 x64; // y vel
} itChicorita_ItemVars;

typedef struct itChicoritaAttr {
    f32 scale;
    s32 x4; // x60 in item vars gets set to this if -1; max timer/lifetime?
} itChicoritaAttr;

typedef struct itChicoritaLeafAttr {
    f32 timer;
    f32 x4;
    f32 x8;  // x pos
    f32 xC;  // y pos
    f32 x10; // x vel
} itChicoritaLeafAttr;

typedef struct it_2728_DatAttrs {
    Fighter* fighter;
} it_2728_DatAttrs;

typedef struct it_279D_ItemVars {
    /* ip+DD4 */ s32 x0;
    /* ip+DD8 */ Vec3 x4;
    /* ip+DE4 */ Vec3 x10;
    /* ip+DF0 */ f32 x1C;
    /* ip+DF4 */ f32 x20;
    /* ip+DF8 */ f32 x24;
    /* ip+DFC */ f32 x28;
    /* ip+E00 */ f32 x2C[6];
    // /* ip+E04 */ s32 x30; // scale?
    // /* ip+E08 */ s32 x34;
    // /* ip+E0C */ s32 x38;
    // /* ip+E10 */ s32 x3C;
    // /* ip+E14 */ s32 x40;
    /* ip+E18 */ f32 x44;
    /* ip+E1C */ f32 x48;
    /* ip+E20 */ f32 x4C; // scale
    /* ip+E24 */ f32 x50;
    /* ip+E28 */ s32 x54;
    /* ip+E2C */ s32 x58; // used as an index back into this struct?
    /* ip+E30 */ s32 x5C;
} it_279D_ItemVars;

typedef struct it_279D_DatAttrs {
    f32 x0;
    f32 x4;
    f32 x8;
    f32 xC;
    f32 x10;
    f32 x14;
    f32 x18;
    f32 x1C[6];
    // f32 x20;
    // f32 x24;
    // f32 x28;
    // f32 x2C;
    // f32 x30;
    f32 x34;
    s32 x38;
    s32 x3C[160];
    // f32 x3C;
    // f32 x40;
    // f32 x44;
    // f32 x48;
    // f32 x4C;
    // f32 x50;
    // f32 x54;
    // f32 x58;
    // f32 x5C;
    // s32 x60[160];
    // f32 padding[0x248 - 0x4C];
    // f32 x248;
} it_279D_DatAttrs;

typedef struct it_27B5_ItemVars {
    /* ip+DD4 */ HSD_JObj* x0;
    /* ip+DD8 */ s32 x4;
    /* ip+DDC */ Vec3 x8;
    /* ip+DE8 */ S32Vec3 x14;
    /* ip+DF4 */ s32 x20;
    /* ip+DF8 */ s32 x24;
    /* ip+DFC */ s32 x28;
    /* ip+E00 */ f32 x2C;
    /* ip+E04 */ s32 x30; // scale?
    /* ip+E08 */ s32 x34;
    /* ip+E0C */ s32 x38;
    /* ip+E10 */ s32 x3C;
    /* ip+E14 */ s32 x40;
    /* ip+E18 */ f32 x44;
    /* ip+E1C */ s32 x48;
    /* ip+E20 */ f32 x4C; // scale
    /* ip+E24 */ f32 x50;
    /* ip+E28 */ s32 x54;
    /* ip+E2C */ s32 x58;
    /* ip+E30 */ s32 x5C;
} it_27B5_ItemVars;

typedef struct it_27B5_DatAttrs {
    f32 scale;
} it_27B5_DatAttrs;

typedef struct it_27CE_ItemVars {
    /* ip+DD4 */ void* attr;
} it_27CE_ItemVars;

// Should it_2F28 and it_27CF use the same structs?
typedef struct it_27CF_ItemVars {
    f32 x0;
} it_27CF_ItemVars;

typedef struct it_27CF_DatAttrs {
    Vec3 pos;
    Vec3 vel;
    f32 float1; // lifetime
    f32 float2;
    f32 float3; // item var x0
    f32 x24;    // item->xC98
    int x28;    // ItemKind
} it_27CF_DatAttrs;

typedef struct it_2F28_ItemVars {
    f32 x0;
} it_2F28_ItemVars;

struct it_2F28_DatAttrs {
    Vec3 pos;
    Vec3 vel;
    f32 float1; // lifetime
    f32 float2; // item var x0
};

typedef struct it_2E5A_ItemVars_struct {
    f32 x0;       // set to float calc result/item->x3C
    HSD_JObj* x4; // set to item_gobj->hsd_obj
    Vec3 x8;      // called in lb_8000B1CC
    Vec3 x14;     // set equal to x8
} it_2E5A_ItemVars_struct;

typedef struct it_2E5A_ItemVars {
    // /* ip+DD4 */ HSD_GObj* x0;
    /* ip+DD4 */ s32 x0;
    /* ip+DD8 */ s32 x4;  // uses regular registers (#? gets multiplied by 2C,
                          // then indexed into attr)
    /* ip+DDC */ s32 x8;  // uses regular registers
    /* ip+DE0 */ s32 xC;  // uses regular registers
    /* ip+DE4 */ f32 x10; // uses float registers; timer?
    /* ip+DE8 */ f32 x14;
    /* ip+DEC */ UnkFlagStruct x18; // has bit assignments
    /* ip+DF0 */ it_2E5A_ItemVars_struct* x1C;
    // /* ip+DF4 */ s32 x20;
    // /* ip+DF8 */ s32 x24;
    // /* ip+DFC */ s32 x28;
    // /* ip+E00 */ s32 x2C;
    // /* ip+E04 */ s32 x30;
    // /* ip+E08 */ s32 x34;
    // /* ip+E0C */ s32 x38;
    // /* ip+E10 */ s32 x3C;
    // /* ip+E14 */ s32 x40;
    // /* ip+E18 */ s32 x44;
    // /* ip+E1C */ s32 x48;
    // /* ip+E20 */ s32 x4C;
    // /* ip+E24 */ s32 x50;
    // /* ip+E28 */ s32 x54;
    // /* ip+E2C */ s32 x58;
} it_2E5A_ItemVars;

typedef struct it_2E5A_DatAttrs_1 {
    f32 x0; // lifetime?
    f32 x4; // float assignment
    f32 x8;
    f32 xC;
    f32 x10;
    f32 x14; // item->x40_vel.x
    f32 x18;
    f32 x1C;
    f32 x20;
    f32 x24; // float assignment
    f32 x28;
    f32 x2C; // float assignment
    f32 x30;
    f32 x34;
    f32 x38;
    HSD_Joint* x3C; // called in it_80273318
    f32 x40;
    f32 x44;
    f32 x48;
    s32 x4C; // item->xD84
    s32 x50;
    f32 x54;  // item->scl
    ECB* x58; // called in it_80275D5C
    s32 x5C;
} it_2E5A_DatAttrs_1;

typedef struct it_2E5A_DatAttrs_2 {
    f32 x0; // lifetime?
    f32 x4; // float assignment
    f32 x8;
    f32 xC;
    HSD_Joint* x10;     // called in it_80273318
    ItemStateDesc* x14; // item2->xD0_itemStateDesc
    f32 x18;
    f32 x1C;
    s32 x20; // item->xD84
    f32 x24; // float assignment
    f32 x28; // item->scl
    // ECB* x2C; // called in it_80275D5C
} it_2E5A_DatAttrs_2;

typedef struct it_802E5FXX_struct { // used for it_802E5F00 and it_802E5F8C
    HSD_GObj* x0; // Item GObj assignment/passed to db_80225DD8
    f32 x4;       // float assignment (angle?)
    f32 x8;       // float assignment (used in x40_vel.y calc)
    s32 xC;       // non-float assignment (arg3/arg2/while condition)
    s32 x10;      // non-float assignment
    s32 x14;      // non-float assignment
    s32 x18;      // non-float assignment (gm_8016C6C0)
} it_802E5FXX_struct;

typedef struct it_2E6A_ItemVars_1 {
    /*  +0 ip+DD4 */ s16 x0;
    /*  +2 ip+DD6 */ s16 x2; // type of union: 1=jobj, 2=vec
                     union {
    /*  +4 ip+DD8 */     HSD_JObj* x4;
    /*  +4 ip+DD8 */     Vec3 x4_vec;
                     };
    /* +10 ip+DE4 */ Ground* x10;
    /* +14 ip+DE8 */ void (*x14)(Item_GObj*, Ground*);
    /* +18 ip+DEC */ void (*x18)(Item_GObj*, Ground*, Vec3*, HSD_GObj*, f32);
    /* +1C ip+DF0 */ void (*x1C)(Item_GObj*, Ground*, HSD_GObj*);
} it_2E6A_ItemVars_1;

typedef struct itWhiteBea_ItemVars {
    /*  +0 ip+DD4 */ char pad_0[0x20];
    /* +20 ip+DF4 */ UNK_T x20;
} itWhiteBea_ItemVars;

typedef struct itOctarock_ItemVars {
    /*  +0 ip+DD4 */ char pad_0[0x20];
    /* +20 ip+DF4 */ Vec3 x20;
} itOctarock_ItemVars;

typedef struct itMasterHandLaser_ItemVars {
    /*  +0 ip+DD4 */ bool x0;
} itMasterHandLaser_ItemVars;

#endif
