/// @file
/// @todo Restructure this, possibly items/chara/types.h
#ifndef MELEE_IT_ITCHARITEMS_H
#define MELEE_IT_ITCHARITEMS_H

#include "platform.h"

#include "baselib/forward.h"
#include "it/forward.h"
#include "lb/forward.h"

#include "lb/types.h"

#include <dolphin/mtx.h>
#include <baselib/jobj.h>

typedef struct itCLinkMilk_ItemVars {
    /* +0 ip+DD4 */ Fighter_GObj* x0;
} itCLinkMilk_ItemVars;

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

typedef struct itClimbersIce_ItemVars {
    /* +0 */ Item_GObj* x0;
    /* +4 */ f32 x4;
    /* +8 */ u8 x8_b0 : 1;
} itClimbersIce_ItemVars;

typedef struct itClimbersStringAttributes {
    /* +00 */ s32 x0_count;
    /* +04 */ s32 x4;
    /* +08 */ f32 x8;
    /* +0C */ f32 xC;
    /* +10 */ u8 pad_10[0x4];
    /* +14 */ f32 x14;
    /* +18 */ s32 x18;
    /* +1C */ s32 x1C;
    /* +20 */ s32 x20;
    /* +24 */ HSD_Joint* x24_joint;
    /* +28 */ HSD_Joint* x28_joint;
} itClimbersStringAttributes;

typedef struct itClimbersIceAttributes {
    /* +00 */ f32 x0;
    /* +04 */ f32 x4;
    /* +08 */ f32 x8;
    /* +0C */ f32 xC;
    /* +10 */ f32 x10;
    /* +14 */ f32 x14;
    /* +18 */ f32 x18;
    /* +1C */ f32 x1C;
    /* +20 */ u8 pad_20[0x4];
    /* +24 */ f32 x24;
    /* +28 */ f32 x28;
    /* +2C */ s32 x2C;
    /* +30 */ u32 x30;
} itClimbersIceAttributes;

typedef struct itNessbat_ItemVars {
    /* +0 ip+DD4 */ HSD_GObj* x0;
} itNessbat_ItemVars;

typedef struct itNesspkthundertrail_ItemVars {
    /* +0 ip+DD4 */ Item_GObj* x0;
    /* +4 ip+DD8 */ s32 x4;
    /* +8 ip+DDC */ s32 x8;
} itNesspkthundertrail_ItemVars;

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
    s32 x3C;
    s32 x40;
    s32 x44;
    f32 x48;
    f32 x4C;
    f32 x50;
    f32 x54;
    f32 x58;
} itHitodemanAttributes;

typedef struct {
    /* x0 */ f32 x0;
    /* x4 */ f32 x4;
    /* x8 */ f32 x8;
    /* xC */ f32 xC;
} itFireAttributes;

typedef struct {
    /* x0 */ f32 x0;
} itThunderAttributes;

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
    /* xC */ bool xDE0;    // false when not shot yet; true after shot (in this
                           // spawn instance of the blaster - not put away)
    /* x10 */ s32 xDE4[6]; // group 1; gets set to 0 in func (it_802ADF10)
                           // that sets item joint locations from
                           // corresponding fighter joint locations
    /* x28 */ s32 xDFC[6]; // group 2; gets set to 0 in func (it_802ADF10)
                           // that sets item joint locations from
                           // corresponding fighter joint locations
    /* x40 */ Vec3 xE14[6]; // group 3; gets set as the vector from fighter's
                            // current position to the joint holding the
                            // blaster on the frame blaster its shot
    /* x88 */ f32 angle[6]; // xE5C group 4; angle[0] gets set to an angle
                            // value in func (it_802ADF10) that sets item
                            // joint locations from corresponding fighter
                            // joint locations
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

typedef struct {
    /* 0x00 */ int xDD4;
    /* 0x00 */ Item_GObj* xDD8;
} itGamewatchrescue_ItemVars;

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

typedef struct {
    /* 0x00 ip+0xDD4 */ char _pad0[0xDF4 - 0xDD4];
    /* 0x20 ip+0xDF4 */ Item_GObj* xDF4;
    /* 0x24 ip+0xDF8 */ HSD_JObj* xDF8;
    /* 0x28 ip+0xDFC */ f32 xDFC;
    /* 0x2C ip+0xE00 */ f32 xE00;
    /* 0x30 ip+0xE04 */ f32 xE04;
    /* 0x34 ip+0xE08 */ f32 xE08;
    /* 0x38 ip+0xE0C */ Vec3 xE0C;
    /* 0x44 ip+0xE18 */ Vec3 xE18;
    /* 0x50 ip+0xE24 */ Vec3 xE24;
    /* 0x5C ip+0xE30 */ s16 xE30;
    /* 0x5E ip+0xE32 */ s16 xE32_pad;
    /* 0x60 ip+0xE34 */ f32 xE34;
    /* 0x64 ip+0xE38 */ s32 xE38;
    /* 0x68 ip+0xE3C */ s32 xE3C;
    /* 0x6C ip+0xE40 */ Item_GObj* xE40;
    /* 0x70 ip+0xE44 */ Item_GObj* xE44;
    /* 0x74 ip+0xE48 */ s32 xE48;
    /* 0x78 ip+0xE4C */ s32 xE4C;
} itArwingLaser_ItemVars;

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

typedef struct {
    /*  +0 ip+DD4 */ f32 angle;
    /*  +4 ip+DD8 */ f32 speed;
    /*  +8 ip+DDC */ Vec3 dir;
    /* +14 ip+DE8 */ Vec3 init_pos;
} itKirbyCutterBeam_ItemVars;

typedef struct {
    /* +000 ip+DD4 */ u8 _pad[0x1C8];
    /* +1C8 ip+F9C */ f32 x1C8;
    /* +1CC ip+FA0 */ f32 x1CC;
    /* +1D0 ip+FA4 */ f32 x1D0;
    /* +1D4 ip+FA8 */ f32 x1D4;
    /* +1D8 ip+FAC */ f32 x1D8;
    /* +1DC ip+FB0 */ f32 x1DC;
    /* +1E0 ip+FB4 */ u8 _pad2[0x8];
    /* +1E8 ip+FBC */ Vec3 x1E8;
    /* +1F4 ip+FC8 */ f32 x1F4;
} itKirby2F23_ItemVars;

/// user_data struct of GObj class 7
typedef struct ItemLink {
    /*   +0 */ struct ItemLink* prev;
    /*   +4 */ struct ItemLink* next;
    /*   +8 */ Vec3 vel;
    /*   +C */ Vec3 pos;
    /*  +20 */ Vec3 x20; ///< Previous position?
    /*  +2C:0 */ u8 x2C_b0 : 1;
    /*  +2C:1 */ u8 x2C_b1 : 1;
    /*  +2C:2 */ u8 x2C_b2 : 1;
    /*  +2C:3 */ u8 x2C_b3 : 1;
    /*  +2C:4 */ u8 x2C_b4 : 1;
    /*  +2C:5 */ u8 x2C_b5 : 1;
    /*  +2C:6 */ u8 x2C_b6 : 1;
    /*  +2C:7 */ u8 x2C_b7 : 1;
    /*  +30 */ CollData coll_data;
    /* +1CC */ s32 x1CC;
    /* +1D0 */ HSD_GObj* gobj;
    /* +1D4 */ HSD_JObj* jobj;
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
    /* ip+DF0 */ Vec3 xDF0[16];
    /* ip+EB0 */ Vec3 xEB0[16];
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
    /* x0 */ u32 x0;
    /* x4 */ u32 x4;
    /* x8 */ u32 x8;
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
    /* x4C */ HSD_AnimJoint* x4C_anim;
    /* x50 */ HSD_MatAnimJoint* x50_matanim;
    /* x54 */ HSD_ShapeAnimJoint* x54_shapeanim;
    /* x58 */ HSD_AnimJoint* x58_anim;
    /* x5C */ HSD_MatAnimJoint* x5C_matanim;
    /* x60 */ HSD_ShapeAnimJoint* x60_shapeanim;
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
    /* +0 +DD4 */ f32 xDD4;
    /* +4 +DD8 */ HSD_GObj* xDD8;
    /* +8 +DDC */ Item_GObj* xDDC;
    /* +C +DE0 */ s32 xDE0;
    /* +10 +DE4 */ s32 xDE4;
    /* +14 +DE8 */ Vec3 xDE8;
    /* +20 +DF4 */ Vec3 xDF4;
    /* +2C +E00 */ Vec3 xE00;
} itPikachutJoltGround_ItemVars;

typedef struct itPikachutJoltAir_ItemVars {
    /* +0  ip+DD4 */ HSD_GObj* xDD4;
    /* +4  ip+DD8 */ Item_GObj* xDD8;
    /* +8  ip+DDC */ u8 pad_8[0xC];
    /* +14 ip+DE8 */ Vec3 xDE8;
    /* +20 ip+DF4 */ s32 xDF4;
} itPikachutJoltAir_ItemVars;

typedef struct itPikachuthunder_ItemVars {
    /* +0 ip+DD4 */ s32 x0;
    /* +4 ip+DD8 */ s32 x4;
    /* +8 ip+DDC */ s32 x8;
    /* +C ip+DE0 */ f32 xC;
    /* +10 ip+DE4 */ f32 x10;
    /* +14 ip+DE8 */ f32 x14;
    /* +18 ip+DEC */ f32 x18;
    /* +1C ip+DF0 */ Vec3 x1C;
    /* +28 ip+DFC */ Vec3 x28;
    /* +34 ip+E08 */ Item_GObj* x34;
    /* +38 ip+E0C */ Item_GObj* x38;
} itPikachuthunder_ItemVars;

typedef struct itPikachutJoltGroundAttributes {
    /* +0 */ f32 x0;
    /* +4 */ f32 x4;
    /* +8 */ f32 x8;
    /* +C */ f32 xC;
} itPikachutJoltGroundAttributes;

typedef struct itPikachuthunderAttributes {
    /* +0 ip+DD4 */ f32 x0;
    /* +4 ip+DD8 */ f32 x4;
    /* +8 ip+DDC */ f32 x8;
} itPikachuthunderAttributes;

typedef struct itSamusBombAttributes {
    /* +0 */ f32 x0;
    /* +4 */ f32 x4;
    /* +8 */ f32 x8;
    /* +C */ f32 xC;
    /* +10 */ f32 x10;
    /* +14 */ f32 x14;
    /* +18 */ f32 x18;
} itSamusBombAttributes;

typedef struct itSamusBomb_ItemVars {
    /* +0 +DD4 */ bool x0;
    /* +4 +DD8 */ Fighter_GObj* owner;
} itSamusBomb_ItemVars;

typedef struct itSamusChargeshot_ItemVars {
    /* +0  +DD4 */ u32 xDD4_pad;
    /* +4  +DD8 */ f32 xDD8;
    /* +8  +DDC */ f32 xDDC;
    /* +C  +DE0 */ f32 xDE0;
    /* +10 +DE4 */ f32 xDE4;
    /* +14 +DE8 */ s32 xDE8;
    /* +18 +DEC */ s32 xDEC;
    /* +1C +DF0 */ s32 xDF0;
    /* +20 +DF4 */ s32 xDF4;
    /* +24 +DF8 */ s32 xDF8;
    /* +28 +DFC */ s32 xDFC;
    /* +2C +E00 */ Fighter_GObj* xE00;
    /* +30 +E04 */ f32 xE04;
    /* +34 +E08 */ u32 pad1[9];
    /* +78 +E2C */ f32 xE2C;
    /* +7C +E30 */ f32 xE30;
    /* +80 +E34 */ f32 xE34;
    /* +84 +E38 */ u32 padding[15]; /* gap 0x84-0xC0 (0x3C bytes) */
} itSamusChargeshot_ItemVars;

typedef struct itSamusChargeShot_Attributes {
    /* +0 */ f32 lifetime;
    /* +4 */ u32 x4;
    /* +8 */ f32 x8;
    /* +C */ f32 xC;
    /* +10 */ f32 x10;
    /* +14 */ f32 x14;
    /* +18 */ f32 x18;
    /* +1C */ f32 x1C;
} itSamusChargeShot_Attributes;

typedef struct itSamusGrapple_ItemVars {
    /*  +0 ip+DD4 */ ItemLink* x0;
    /*  +4 ip+DD8 */ ItemLink* x4;
    /*  +8 ip+DDC */ HSD_GObj* x8;
    /*  +C ip+DE0 */ HSD_JObj* xC;
    /* +10 ip+DE4 */ void (*unk_10)(Item_GObj*);
    /* +14 ip+DE8 */ u8 x14;
    /* +15 ip+DE9 */ u8 x15;
    /* +16 ip+DEA */ u8 x16;
} itSamusGrapple_ItemVars;

typedef struct itSamusGrappleAttributes {
    /* +00 */ f32 x0;
    /* +04 */ f32 x4;
    /* +08 */ f32 x8;
    /* +0C */ s32 xC;
    /* +10 */ f32 x10;
    /* +14 */ f32 x14;
    /* +18 */ f32 x18;
    /* +1C */ f32 x1C;
    /* +20 */ f32 x20;
    /* +24 */ f32 x24;
    /* +28 */ f32 x28;
    /* +2C */ f32 x2C;
    /* +30 */ f32 x30;
    /* +34 */ s32 x34;
    /* +38 */ f32 x38;
    /* +3C */ f32 x3C;
    /* +40 */ f32 x40;
    /* +44 */ f32 x44;
    /* +48 */ f32 x48;
    /* +4C */ f32 x4C;
    /* +50 */ f32 x50;
    /* +54 */ f32 x54;
    /* +58 */ f32 x58;
    /* +5C */ f32 x5C;
    /* +60 */ f32 x60;
    /* +64 */ HSD_Joint* x64;
    /* +68 */ HSD_Joint* x68;
    /* +6C */ HSD_Joint* x6C;
    /* +70 */ HSD_Joint* x70;
    /* +74 */ HSD_AnimJoint** x74;
    /* +78 */ HSD_MatAnimJoint** x78;
    /* +7C */ HSD_ShapeAnimJoint** x7C;
    /* +80 */ HSD_AnimJoint** x80;
    /* +84 */ HSD_MatAnimJoint** x84;
    /* +88 */ HSD_ShapeAnimJoint** x88;
    /* +8C */ HSD_AnimJoint** x8C;
    /* +90 */ HSD_MatAnimJoint** x90;
    /* +94 */ HSD_ShapeAnimJoint** x94;
    /* +98 */ HSD_AnimJoint** x98;
    /* +9C */ HSD_MatAnimJoint** x9C;
    /* +A0 */ HSD_ShapeAnimJoint** xA0;
    /* +A4 */ HSD_AnimJoint** xA4;
    /* +A8 */ HSD_MatAnimJoint** xA8;
    /* +AC */ HSD_ShapeAnimJoint** xAC;
} itSamusGrappleAttributes;

typedef struct itSamusMissileAttributes {
    /* +0 */ f32 x0;
    /* +4 */ f32 x4;
    /* +8 */ f32 x8;
    /* +C */ f32 xC;
    /* +10 */ f32 x10;
    /* +14 */ f32 x14;
    /* +18 */ f32 x18;
    /* +1C */ f32 x1C;
    /* +20 */ f32 x20;
    /* +24 */ f32 x24;
    /* +28 */ f32 x28;
    /* +2C */ f32 x2C;
    /* +30 */ f32 x30;
    /* +34 */ f32 x34;
    /* +38 */ f32 x38;
    /* +3C */ f32 x3C;
} itSamusMissileAttributes;

typedef struct itSamusMissile_ItemVars {
    /* +0 +DD4 */ bool is_smash_missile;
    /* +4 +DD8 */ s32 x4;
    /* +8 +DDC */ f32 x8;
    /* +C +DE0 */ Fighter_GObj* owner;
    /* +10 +DE4 */ HSD_GObj* x10;
} itSamusMissile_ItemVars;

typedef struct itSeakNeedleHeld_ItemVars {
    /* +0 ip+DD4 */ Fighter_GObj* owner;
} itSeakNeedleHeld_ItemVars;

typedef struct itSeakNeedleThrown_ItemVars {
    /*  +0 ip+DD4 */ f32 xDD4;
    /*  +4 ip+DD8 */ f32 xDD8;
    /*  +8 ip+DDC */ f32 xDDC;
    /*  +C ip+DE0 */ f32 xDE0;
    /* +10 ip+DE4 */ Vec3 xDE4;
    /* +1C ip+DF0 */ f32 xDF0;
    /* +20 ip+DF4 */ int xDF4;
    /* +24 ip+DF8 */ f32 xDF8;
    /* +28 ip+DFC */ f32 xDFC;
} itSeakNeedleThrown_ItemVars;

typedef struct itSeakChain_ItemVars {
    /* +0  ip+DD4 */ ItemLink* x0;
    /* +4  ip+DD8 */ ItemLink* x4;
    /* +8  ip+DDC */ Fighter_GObj* parent_gobj;
    /* +C  ip+DE0 */ u8 pad_C[0x4];
    /* +10 ip+DE4 */ s32 x10;
    /* +14 ip+DE8 */ s32 x14;
    /* +18 ip+DEC */ s32 x18;
    /* +1C ip+DF0 */ Vec3 history[0xF];
} itSeakChain_ItemVars;

typedef struct itSeakChain_Attrs {
    /*  +0 */ s32 x0;
    /*  +4 */ f32 x4;
    /*  +8 */ u8 pad_8[0x8];
    /* +10 */ f32 x10;
    /* +14 */ f32 x14;
    /* +18 */ f32 x18;
    /* +1C */ f32 x1C;
    /* +20 */ f32 x20;
    /* +24 */ f32 x24;
    /* +28 */ f32 x28;
    /* +2C */ f32 x2C;
    /* +30 */ f32 x30;
    /* +34 */ f32 x34;
    /* +38 */ f32 x38;
    /* +3C */ f32 x3C;
    /* +40 */ f32 x40;
    /* +44 */ f32 x44;
    /* +48 */ f32 x48;
    /* +4C */ u8 pad_4C[0x8];
    /* +54 */ f32 x54;
    /* +58 */ f32 x58;
    /* +5C */ f32 x5C;
    /* +60 */ f32 x60;
    /* +64 */ HSD_Joint* x64_joint;
    /* +68 */ HSD_Joint* x68_joint;
} itSeakChain_Attrs;
STATIC_ASSERT(sizeof(struct itSeakChain_Attrs) == 0x6C);

typedef struct itClimbersString_ItemVars {
    /* +0  ip+DD4 */ f32 x0;
    /* +4  ip+DD8 */ ItemLink* x4;
    /* +8  ip+DDC */ ItemLink* x8;
    /* +C  ip+DE0 */ HSD_GObj* xC;
    /* +10 ip+DE4 */ u8 pad_10[0x4];
    /* +14 ip+DE8 */ HSD_JObj* x14;
} itClimbersString_ItemVars;

typedef struct itZako_ItemVars {
    /* +0 ip+DD4 */ s32 pad;
    /* +4 ip+DD8 */ s32 idx;
} itZako_ItemVars;

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

typedef struct itGamewatchchef_ItemVars {
    /* +0 ip+DD4 */ s32 x0;
    /* +4 ip+DD8 */ s32 x4;
} itGamewatchchef_ItemVars;

typedef struct itGamewatchchefAttrEntry {
    /* +0 */ f32 x0;
    /* +4 */ f32 x4;
    /* +8 */ f32 x8;
    /* +C */ f32 xC;
    /* +10 */ f32 x10;
} itGamewatchchefAttrEntry;

typedef struct itGamewatchchefAttributes {
    /* +0 */ void* x0;
    /* +4 */ f32 x4;
    /* +8 */ f32 x8;
    /* +C */ f32 xC;
    /* +10 */ itGamewatchchefAttrEntry entries[1];
} itGamewatchchefAttributes;

typedef struct itGamewatchparachuteAttributes {
    /* +0 */ void* x0;
} itGamewatchparachuteAttributes;

typedef struct itHinoarashi_ItemVars {
    /* xDD4 */ u8 _0[0x60 - 0x0];
    /* xE34 */ UnkFlagStruct x60;
    /* xE35 */ u8 x61[0x64 - 0x61];
    /* xE38 */ f32 x64;
    /* xE3C */ f32 x68;
    /* xE40 */ Vec3 x6C;
    /* xE4C */ f32 x78;
} itHinoarashi_ItemVars;

typedef struct itHinoarashiAttributes {
    /* +0 */ f32 x0;
    /* +4 */ f32 x4;
    /* +8 */ f32 x8;
    /* +C */ u8 _pad[0x10 - 0xC];
    /* +10 */ f32 x10;
    /* +14 */ f32 x14;
} itHinoarashiAttributes;

typedef struct itTools_ItemVars {
    /* +0 ip+DD4 */ s32 x0;
} itTools_ItemVars;

typedef struct itToolsMotionAttrs {
    /* +00 */ f32 x0;
    /* +04 */ f32 x4;
    /* +08 */ f32 x8;
    /* +0C */ f32 xC;
    /* +10 */ f32 x10;
    /* +14 */ f32 x14;
    /* +18 */ f32 x18;
} itToolsMotionAttrs;

typedef struct itToolsAttributes {
    /* +00 */ f32 x0;
    /* +04 */ f32 x4;
    /* +08 */ f32 x8;
    /* +0C */ s32 xC;
    /* +10 */ itToolsMotionAttrs motions[1];
} itToolsAttributes;

typedef struct itNessYoyo_ItemVars {
    /* +0  ip+DD4 */ s32 x0;
    /* +4  ip+DD8 */ f32 x4;
    /* +8  ip+DDC */ ItemLink* x8;
    /* +C  ip+DE0 */ ItemLink* xC;
    /* +10 ip+DE4 */ HSD_GObj* x10;
    /* +14 ip+DE8 */ char pad_14[0x4];
    /* +18 ip+DEC */ HSD_JObj* x18;
} itNessYoyo_ItemVars;

#endif
