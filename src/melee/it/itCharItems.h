/// @file
/// @todo Restructure this, possibly items/chara/types.h
#ifndef MELEE_IT_ITCHARITEMS_H
#define MELEE_IT_ITCHARITEMS_H

#include "platform.h"

#include "it/forward.h"
#include "lb/forward.h"

#include "lb/types.h"

#include <dolphin/mtx.h>
#include <baselib/jobj.h>

typedef struct itClimbersBlizzard_ItemVars {
    /* +0 */ f32 x0;
    /* +4 */ u8 flag0 : 1;
} itClimbersBlizzard_ItemVars;

typedef struct itClimbersBlizzardAttributes {
    /* +0 */ f32 x0;
    /* +4 */ f32 x4;
    /* +8 */ f32 x8;
    /* +C */ f32 xC;
    /* +10 */ f32 x10;
} itClimbersBlizzardAttributes;

typedef struct {
    /* x0 ip+DD4 */ f32 x0;
    /* x4 ip+DD8 */ HSD_GObj* x4;
    /* x8 ip+DDC */ f32 x8;
    /* xC ip+DE0 */ f32 xC;
} itDrMarioPill_ItemVars;

typedef struct {
    /* x0 */ f32 x0;
    /* x4 */ f32 x4;
    /* x8 */ f32 x8;
    /* xC */ f32 xC;
    /* x10 */ f32 x10;
} itDrMarioPillAttributes;

typedef struct {
    /* x0 */ f32 x0;
    /* x4 */ f32 x4;
    /* x8 */ f32 x8;
    /* xC */ f32 xC;
} itFireAttributes;

typedef struct {
    /* x0 */ s32 xDD4; // gets iterated from 0 to 14 in function (it_802AE200)
                       // that transforms the item model (possibly frame number
                       // of animation?)
    /* x4 */ s32 xDD8; // {0-4} Used to index into array (it_803F6E28) that has
                       // floats to translate item model by
                       // 1->4 when blaster shooting starting (at cmd_var3 = 1)
                       // 3->0 when blaster getting put away (at cmd_var3 = 2)
    /* x8 */ s32 xDDC; // {-1, 0, 1} Value gets added to xDD8 to iterate it
                       // during blaster collision callback
                       // -1: when cmd_var3 = 2 (when gun is getting put away,
                       // ____but not yet invisible)
                       // 0: when xDD8 <= 0 or xDD8 >= 5
                       // 1: when cmd_var3 = 1 (when gun shooting sfx starts)
    /* xC */ bool xDE0; // false when not shot yet; true after shot (in this
                        // spawn instance of the blaster - not put away)
    /* x10 */ s32 xDE4; // group 1; gets set to 0 in func (it_802ADF10) that
                        // sets item joint locations from corresponding fighter
                        // joint locations
    /* x14 */ s32 xDE8; // group 1
    /* x18 */ s32 xDEC; // group 1
    /* x1C */ s32 xDF0; // group 1
    /* x20 */ s32 xDF4; // group 1
    /* x24 */ s32 xDF8; // group 1
    /* x28 */ s32 xDFC; // group 2; gets set to 0 in func (it_802ADF10) that
                        // sets item joint locations from corresponding fighter
                        // joint locations
    /* x2C */ s32 xE00; // group 2
    /* x30 */ s32 xE04; // group 2
    /* x34 */ s32 xE08; // group 2
    /* x38 */ s32 xE0C; // group 2
    /* x3C */ s32 xE10; // group 2
    /* x40 */ Vec3 xE14; // group 3; gets set as the vector from fighter's
                         // current position to the joint holding the blaster
                         // on the frame blaster its shot
    /* x4C */ Vec3 xE20; // group 3
    /* x58 */ Vec3 xE2C; // group 3
    /* x64 */ Vec3 xE38; // group 3
    /* x70 */ Vec3 xE44; // group 3
    /* x7C */ Vec3 xE50; // group 3
    /* x88 */ f32 angle; // xE5C group 4; gets set to an angle value in func
                         // (it_802ADF10) that sets item joint locations from
                         // corresponding fighter joint locations
    /* x8C */ f32 xE60;  // group 4
    /* x90 */ f32 xE64;  // group 4
    /* x94 */ f32 xE68;  // group 4
    /* x98 */ f32 xE6C;  // group 4
    /* x9C */ f32 xE70;  // group 4
    /* x100 */ bool gfx_spawn_var; // xE74 Signals to spawn shoot gfx from
                                   // blaster when set to true, which is done
                                   // from subaction funcs on frame of shot
    /* x104 */ s32 set_sfx_var2;   // xE78 Sets blaster destroy sfx func when
                                   // Flag 1 = 2
                                   // ---------------
                                   // Blaster/Throw Subaction cmd Flags
                                   // .
                                   // Flag 0 is ??? (multipurpose?)
                                   // 0: ?
                                   // 1: ?
                                   // .
                                   // Flag 1 is for if blaster is present?
                                   // 0: Default (invisible)
                                   // ___Initial value for blaster actions and
                                   // ___set on 1st frame of throw actions
                                   // 1: Present (visible)
                                   // ___Set 1st frame of SpecialAirNStart
                                   // ___action and upon blaster spawn in
                                   // ___throw actions
                                   // 2: Put away (invisible again)
                                   // ___Set frame of putting away blaster in
                                   // ___all blaster and throw actions
                                   // .
                                   // Flag 2 is for spawning laser shots
                                   // 0: Default (don't spawn)
                                   // 1: Spawn
                                   // ___Set on shoot frame, then immediately
                                   // ___reset to 0 after triggering those
                                   // ___functions
                                   // .
                                   // Flag 3 is for blaster action
                                   // 0: Default
                                   // 1: Starting to shoot
                                   // 2: Being put away
    /* x108 */ HSD_GObj* owner;    // xE7C
} itFoxBlaster_ItemVars;

typedef struct itLeadead_ItemVars {
    /* 0x00 */ u8 pad[0x18];
    /* 0x18 */ s32 xDEC;
    /* 0x1C */ u8 pad1b[0x1C];
    /* 0x38 */ HSD_GObj* x38;
    /* 0x3C */ f32 x3C;
    /* 0x40 */ s32 xE14;
    /* 0x44 */ s32 x44;
    /* 0x48 */ s32 x48;
    /* 0x4C */ s32 x4C;
    /* 0x50 */ s32 x50;
    /* 0x54 */ u8 pad3[8];
    /* 0x5C */ s32 xE30_state;
    /* 0x60 */ Vec3 xE34_a_offset;
    /* 0x6C */ Vec3 xE40_b_offset;
    /* 0x78 */ f32 xE4C_scale;
    /* 0x7C */ itECB xE50;
} itLeadead_ItemVars;

typedef struct FoxBlasterAttr {
    /* +0 */ float x0;
    /* +4 */ float x4;
    /* +8 */ float x8;
    /* +C */ float xC;
    /* +10 */ float x10;
    /* +14 */ float x14;
    /* +18 */ float x18; // [1]
    /* +1C */ float x1C;
    /* +20 */ float x20; // [2]
    /* +24 */ float x24;
} FoxBlasterAttr;

typedef struct {
    /*  +0 ip+DD4 */ float scale;
    /*  +4 ip+DD8 */ float angle;
    /*  +8 ip+DDC */ float speed;
    /*  +C ip+DE0 */ Vec3 pos;
} itFoxLaser_ItemVars;

typedef struct FoxLaserAttr {
    /* +0 */ float lifetime; // [35]
    /* +4 */ float scale;    // [3]
    /* +8 */ float x8;
    /* +C */ float xC;
    /* +10 */ float x10;
    /* +14 */ float x14;
    /* +18 */ float x18;
    /* +1C */ float x1C;
    /* +20 */ float x20;
    /* +24 */ float x24; // [1]
} FoxLaserAttr;

typedef struct {
    /*  +0 ip+DD4 */ HSD_Joint* xDD4;
    /*  +4 ip+DD8 */ float xDD8;
    /*  +8 ip+DDC */ HSD_JObj* xDDC;
} itFoxIllusion_ItemVars;

typedef struct FoxIllusionAttr {
    float x0; // [5]
    float x4; // [2]
} FoxIllusionAttr;

typedef struct {
    u32 x0;
} itKirbyHammer_ItemVars;

typedef struct ItemLink // user_data struct of GObj class 7
{
    struct ItemLink* prev;
    struct ItemLink* next;
    Vec3 x8_vel;
    Vec3 pos;
    Vec3 x20_vec; // Previous position?
    u8 flag0 : 1;
    u8 flag1 : 1;
    u8 flag2 : 1;
    u8 flag3 : 1;
    u8 flag4 : 1;
    u8 flag5 : 1;
    u8 flag6 : 1;
    u8 flag7 : 1;
    CollData x30_collData;
    s32 unk;
    HSD_GObj* x1D0_GObj;
    HSD_JObj* x1D4_JObj;
} ItemLink;
STATIC_ASSERT(sizeof(struct ItemLink) == 0x1D8);

typedef struct {
    ItemLink* x0;
    ItemLink* x4;
    HSD_GObj* x8;
    HSD_JObj* xC;
    void (*x10)(Item_GObj*);
    u8 x14;
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
    f32 x4C;
    f32 x50;
    f32 x54;
    f32 x58;
    f32 x5C;
    f32 x60;
} itLinkHookshot_ItemVars;

typedef struct {
    f32 x0;
    f32 x4;
    f32 x8;
    s32 xC;
    f32 x10;
    f32 x14;
    f32 x18;
    f32 x1C;
    f32 x20;
    f32 x24;
    f32 x28;
    s32 x2C;
    f32 x30;
    f32 x34;
    f32 x38;
    f32 x3C;
    f32 x40;
    f32 x44;
    f32 x48;
    f32 x4C;
    f32 x50;
    HSD_Joint* x54;
    HSD_Joint* x58;
    HSD_Joint* x5C;
} itLinkHookshotAttributes;

typedef struct {
    UnkFlagStruct x0;
    u8 x1;
    u8 x2;
    u8 x3;
    f32 x4;
    f32 x8;
    f32 xC;
    Item_GObj* x10;
} itLinkBomb_ItemVars;

typedef struct itLinkBombAttributes {
    /* x0 */ u32 lifetime;
    /* x4 */ f32 x4;
    /* x8 */ f32 x8;
    /* xC */ u32 xC;
    /* x10 */ s32 x10;
    /* x14 */ f32 x14;
    /* x18 */ f32 x18;
    /* x1C */ f32 x1C;
    /* x20 */ f32 x20;
    /* x24 */ f32 x24;
    /* x28 */ f32 x28;
    /* x2C */ f32 x2C;
    /* x30 */ f32 x30;
    /* x28 */ f32 vel[3];
} itLinkBombAttributes;

typedef struct {
    /* ip+DD4 */ s32 xDD4;
    /* ip+DD8 */ s32 xDD8;
    /* ip+DDC */ s32 xDDC;
    /* ip+DE0 */ s32 xDE0;
    /* ip+DE4 */ s32 xDE4;
    /* ip+DE8 */ s32 xDE8;
    /* ip+DEC */ s32 xDEC;
    /* ip+DF0 */ u8 _pad0[0xF70 - 0xDF0];
    /* ip+F70 */ f32 xF70;
    /* ip+F74 */ f32 xF74;
    /* ip+F78 */ f32 xF78;
    /* ip+F7C */ f32 xF7C;
    /* ip+F80 */ f32 xF80;
    /* ip+F84 */ f32 xF84;
    /* ip+F88 */ f32 xF88;
    /* ip+F8C */ f32 xF8C;
    /* ip+F90 */ HSD_JObj* xF90[2];
    /* ip+F98 */ Item_GObj* xF98;
} itLinkBoomerang_ItemVars;

typedef struct itLinkBoomerangAttributes {
    /* x0 */ f32 x0;
    /* x4 */ f32 x4;
    /* x8 */ f32 x8;
    /* xC */ f32 xC;
    /* x10 */ f32 x10;
    /* x14 */ f32 x14;
    /* x18 */ f32 x18;
    /* x1C */ f32 x1C;
    /* x20 */ f32 x20;
    /* x24 */ f32 x24;
    /* x28 */ f32 x28;
    /* x2C */ f32 x2C;
    /* x30 */ f32 x30;
    /* x34 */ f32 x34;
    /* x38 */ f32 x38;
    /* x3C */ f32 x3C;
    /* x40 */ f32 x40;
    /* x44 */ HSD_Joint* x44;
    /* x48 */ HSD_Joint* x48;
} itLinkBoomerangAttributes;

typedef struct {
    f32 x0;
    f32 x4;
    f32 x8;
    f32 xC;
    f32 x10;
    f32 x14;
    Vec3 x18;
    Vec3 x24;
    Vec3 x30;
    Vec3 x3C;
    Vec3 x48;
    Quaternion x54;
    Quaternion x64;
    Quaternion x74;
    Quaternion x84;
    f32 x94;
    f32 x98;
    u32 x9C;
    s32 xA0;
    u32 xA4;
    f32 xA8;
    f32 xAC;
    s32 xB0;
    HSD_JObj* xB4[3];
    f32 xC0;
    HSD_GObj* xC4;
    f32 xC8;
    f32 xCC;
    void* xD0;
    f32 xD4;
    f32 xD8;
    f32 xDC;
    HSD_GObj* xE0;
    int xE4;
    f32 xE8;
    f32 xEC;
    s32 xF0;
} itLinkArrow_ItemVars;

typedef struct {
    f32 x0;
    f32 x4;
    f32 x8;
    f32 xC;
    f32 x10;
    f32 x14;
    f32 x18;
    f32 x1C;
    f32 x20;
    HSD_Joint* x24;
    HSD_Joint* x28;
    f32 x2C;
} itLinkArrowAttributes;

typedef struct {
    f32 x0;
    HSD_GObj* x4;
} itLinkBow_ItemVars;

typedef struct itMasterHandBullet_ItemVars {
    /* ip+DD4 */ f32 x0;
} itMasterHandBullet_ItemVars;

typedef struct itMasterHandBulletAttributes {
    f32 x0;
} itMasterHandBulletAttributes;

typedef struct itMasterHandLaser_ItemVars {
    /* ip+DD4 */ bool x0;
    /* ip+DD8 */ s32 x4;
    /* ip+DDC */ s32 x8;
    /* ip+DE0 */ HSD_JObj* x10;
} itMasterHandLaser_ItemVars;

typedef struct itMasterHandLaserAttributes {
    f32 x0;
    f32 x4;
} itMasterHandLaserAttributes;

typedef struct itPeachToadSporeAttributes {
    f32 x0_min_speed;
    f32 x4_max_speed_offset;
    f32 x8_speed_decay_rate;
    f32 xc_angle;
} itPeachToadSporeAttributes;

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

typedef struct itPikachutJoltAir_ItemVars {
    /* +0 +DD4 */ char pad_0[0x4];
    /* +4 +DD8 */ u32 xDD8;
} itPikachutJoltAir_ItemVars;

typedef struct itSamusBomb_ItemVars {
    /* +0 +DD4 */ char pad_0[0x4];
    /* +4 +DD8 */ s32 xDD8;
} itSamusBomb_ItemVars;

typedef struct itSamusGrapple_ItemVars {
    /*  +0 +DD4 */ char pad_0[0x10];
    /* +10 +DE4 */ UNK_RET (*unk_10)(UNK_PARAMS);
} itSamusGrapple_ItemVars;

typedef struct itSeakNeedleThrown_ItemVars {
    /* +0 +DD4 */ char pad_0[0x4];
    /* +4 +DD8 */ f32 xDD8;
    /* +8 +DDC */ f32 xDDC;
    /* +C +DE0 */ f32 xDE0;
} itSeakNeedleThrown_ItemVars;

typedef struct itZeldaDinFireExplode_ItemVars {
    /* +0 ip+DD4 */ f32 xDD4;
    /* +4 ip+DD8 */ f32 xDD8;
    /* +8 ip+DDC */ HSD_GObj* xDDC;
    /* +C ip+DE0 */ s32 xDE0;
} itZeldaDinFireExplode_ItemVars;

typedef struct itZeldaDinFireExplodeAttributes {
    /* +0 */ f32 x0;
    /* +4 */ f32 x4;
    /* +8 */ f32 x8;
    /* +C */ f32 xC;
    /* +10 */ f32 x10;
} itZeldaDinFireExplodeAttributes;

typedef struct itUnk4_ItemVars {
    /*  +0 ip+DD4 */ u8 pad[0x18];
    /*  +18 ip+DEC */ u8 xDEC_b0 : 1;
    /*  +18 ip+DEC */ u8 xDEC_b1 : 1;
    /*  +1C ip+DF0 */ Mtx xDF0;
} itUnk4_ItemVars;

#endif
