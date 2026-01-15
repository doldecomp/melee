#ifndef MELEE_IT_TYPES_H
#define MELEE_IT_TYPES_H

#include <placeholder.h>
#include <platform.h>

#include "cm/forward.h"

#include "ft/types.h"
#include "gm/types.h"

#include "it/forward.h" // IWYU pragma: export

#include "it/itCharItems.h"
#include "it/itCommonItems.h"

#include "it/items/forward.h"

#include "it/itPKFlash.h"
#include "it/itPKThunder.h"
#include "lb/types.h"

#include <baselib/forward.h>

#include <common_structs.h>
#include <dolphin/gx.h>
#include <dolphin/mtx.h>

struct CameraBoxFlags {
    struct {
        u8 b01 : 2;
        u8 b2 : 1;
        u8 b3 : 1;
        u8 b4 : 1;
        u8 b5 : 1;
        u8 b6 : 1;
        u8 b7 : 1;
    };
};

struct flag32 {
    struct {
        u32 x0 : 1;
        u32 x1 : 1;
        u32 x2 : 1;
        u32 x3 : 1;
        u32 x4 : 1;
        u32 x5 : 1;
        u32 x6 : 1;
        u32 x7 : 1;
        u32 x8 : 1;
        u32 x9 : 1;
        u32 xA : 1;
        u32 xB : 1;
        u32 xC : 1;
        u32 xD : 1;
        u32 xE : 1;
        u32 xF : 4;
        u32 x13 : 1;
        u32 x14 : 1;
        u32 x15 : 1;
        u32 x16 : 1;
        u32 x17 : 2;
        u32 x19 : 1;
        u32 x1A : 1;
        u32 x1B : 1;
        u32 x1C : 1;
        u32 x1D : 1;
        u32 x1E : 1;
        u32 x1F : 1;
    } flags;
};

struct DynamicBoneTable {
    /// @at{0} @sz{190}
    HSD_JObj* bones[100];
};
STATIC_ASSERT(sizeof(struct DynamicBoneTable) == 0x190);

struct Item_DynamicBones {
    int flags;
    HSD_JObj* skeleton;
    DynamicsDesc dyn_desc;
};
STATIC_ASSERT(sizeof(struct Item_DynamicBones) == 0x1C);

struct ItemAttr {
    u8 x0_is_heavy : 1; // 0x0, bit 0x80, is heavy item (crate)
    u8 x0_78 : 4; // Should be enum (Item_UnkKinds?) for type of action char
                  // takes when using - 0: throwable, 2: Swingable, 3:
                  // Shootable (Relation to Samus Missile lock-on behavior?)
    u8 x0_hold_kind : 3;    // defines hand hold behavior (Item_HoldKinds?)
    u8 x1_1 : 2;            // 0x1 0xB0
    u8 x1_3 : 1;            // 0x1 0x20
    u8 x1_4 : 1;            // 0x1 0x10
    u8 x1_5 : 1;            // 0x1 0x08
    u8 x1_67_cam_kind : 2;  // 0x1 0x06, is stored to 0xdcd
    u8 x1_8 : 1;            // 0x1 0x01    char flags3; //0x2
    u8 x3;                  // 0x3
    f32 x4_throw_speed_mul; // 0x4, speed multiplier at which this item is
                            // thrown at
    s32 x8;
    f32 xC_spin_speed;
    f32 x10_fall_speed;     // 0x10
    f32 x14_fall_speed_max; // 0x14
    f32 x18;
    f32 x1C_damage_mul; // collision related? referenced on taking damage @
                        // 80270f90
    itECB x20;
    Vec2 x30_unk;        // 0x34
    Vec2 x38_grab_range; // 0x38
    itECB x40;
    f32 x50;       // 0x50
    f32 x54;       // 0x54
    f32 x58;       // 0x58
    f32 x5c;       // 0x5c
    f32 x60_scale; // 0x60, does not affect hitboxes

    /// @at{64} @sz{4}
    /// @brief GFX to play on destroy.
    enum_t destroy_gfx;

    s32 x68; // 0x68
    s32 x6C; // 0x6c
    s32 x70; // 0x70
    s32 x74; // 0x74

    /// @at{78} @sz{4}
    /// @brief SFX that plays when this item is destroyed
    enum_t destroy_sfx;

    s32 x7C; // 0x7c
    s32 x80; // 0x80
};

/// @sz{8}
struct ItemDynamics {
    /// @todo Combine with ftDynamics? Can see in it_8027163C that this struct
    /// does not work perfectly
    /// @at{0} @sz{4}
    int count;

    /// @at{4} @sz{4}
    BoneDynamicsDesc* dyn_descs;
};

/// @sz{10}
struct ItemStateDesc {
    /// @at{0} @sz{4}
    HSD_AnimJoint* x0_anim_joint;

    /// @at{0} @sz{4}
    HSD_MatAnimJoint* x4_matanim_joint;

    /// @at{0} @sz{4}
    HSD_ShapeAnimJoint* x8_parameters;

    /// @at{0} @sz{4}
    UNK_T xC_script;
};

struct ItemStateArray {
    struct ItemStateDesc x0_itemStateDesc[8];
};

/// @sz{10}
struct ItemModelDesc {
    /// @at{0} @sz{4}
    HSD_Joint* x0_joint;

    /// @at{4} @sz{4}
    u32 x4_bone_count;

    /// @at{8} @sz{4}
    s32 x8_bone_attach_id;

    /// @at{C} @sz{4}
    u8 xC_bit_field;
};

struct Article {
    ItemAttr* x0_common_attr;
    void* x4_specialAttributes;
    UNK_T x8_hurtbox;
    ItemStateArray* xC_itemStates;
    ItemModelDesc* x10_modelDesc;
    ItemDynamics* x14_dynamics;
};

typedef struct it_266F_ItemVars {
    u16 x0;
    u8* x4;
    u16 x8;
    u8* xC;
    s32 x10;
    s32 x14;
    UnkFlagStruct x18;
    struct lbColl_8000A10C_arg0_t x1C;
} it_266F_ItemVars;

struct Item {
    void* x0;

    /// @at{4} @sz{4}
    HSD_GObj* entity;

    s32 x8;

    /// @at{C} @sz{4}
    enum_t spawn_kind;

    /// @at{10} @sz{4}
    ItemKind kind;

    /// @at{14} @sz{4}
    enum_t hold_kind;

    s32 x18;
    s32 x1C;

    /// @at{20} @sz1
    u8 x20_team_id;

    u8 x21;
    u8 x22;
    u8 x23;

    /// @at{24} @sz{4}
    enum_t msid;

    /// @at{28} @sz{4}
    enum_t anim_id;

    /// @at{2C} @sz{4}
    f32 facing_dir;

    /// @at{30} @sz{4}
    f32 init_facing_dir;

    /// @at{34} @sz{4}
    f32 spin_spd;

    /// @at{38} @sz{4}
    f32 scl;

    /// @at{3C} @sz{4}
    f32 x3C;

    /// @at{40} @sz{C}
    Vec3 x40_vel;

    /// @at{4C} @sz{C}
    Vec3 pos;

    /// @at{58} @sz{C}
    Vec3 x58_vec_unk;

    /// @at{64} @sz{C}
    Vec3 x64_vec_unk2;

    /// @at{70} @sz{C}
    Vec3 x70_nudge;

    Vec3 x7C;
    Vec3 x88;                           // From it_80277040
    Vec3 x94;                           // From it_80277040
    Vec3 xA0;                           // From it_802734B4
    Vec3 xAC_unk;                       // From it_80276CEC
    ItemLogicTable* xB8_itemLogicTable; // Global item callbacks
    ItemStateTable* xBC_itemStateContainer;
    GroundOrAir ground_or_air;
    Article* xC4_article_data;
    HSD_Joint* xC8_joint;
    ItemAttr* xCC_item_attr;
    ItemStateDesc* xD0_itemStateDesc;
    Item_DynamicBones xD4_dynamicBones[24];
    s32 x374_dynamicBonesNum;
    /*  ip+378 */ CollData x378_itemColl;
    s32 ecb_lock;

    /// @at{518} @sz{4}
    /// @brief Item's current owner
    HSD_GObj* owner;

    HSD_GObj* x51C;            // Related to the owner gobj
    CmSubject* x520_cameraBox; // CmSubject
    CommandInfo x524_cmd;      // should this be CommandInfo* instead?
                               // f32 x528;
                               // void* x52C_item_script; // Script parse?
                               // u32 x530;
                               // u32 x534;
                               // u32 x538;
                               // u32 x53C;
                               // u32 x540;
                               // u32 x544;
    ColorOverlay x548_colorOverlay;
    u8 x5C8;
    u8 x5C9; // used heavily in it_80278108
    u8 x5CA;
    u8 x5CB;
    f32 x5CC_currentAnimFrame;
    f32 x5D0_animFrameSpeed;
    struct {
        HitCapsule hit; // x5D4, x710, x84C, x988
        s32 x138;       // x70C, x848, x984, xAC0
    } x5D4_hitboxes[4];
    u32 xAC4_ignoreItemID;           // Cannot hit items with this index?
    u8 xAC8_hurtboxNum;              // Number of hurtboxes this item has
    HurtCapsule xACC_itemHurtbox[2]; // xACC, xB10
    struct lb_80014638_arg1_t xB54;
    u8 xB68; // int for ItemDynamics->count?
    u8 xB69;
    u8 xB6A;
    u8 xB6B;
    struct xB6C_t {
        Vec3 xB6C;
        // u32 xB6C; // struct DynamicsData* for DynamicsDesc->data?
        // u32 xB70; // int for DynamicsDesc->count?
        // u32 xB74; // pos.x?
        f32 xB78;       // pos.y? scale?
        HSD_JObj* xB7C; // HSD_JObj* for bone?
        u32 xB80;
        Vec3 xB84;
        // u32 xB88;
        // u32 xB8C;
        u32 xB90; // enum_t for BoneDynamicsDesc->bone_id?
    } xB6C_vars[2];
    // u32 xB94;
    // u32 xB98;
    // u32 xB9C;
    // u32 xBA0;
    // u32 xBA4;
    // u32 xBA8;
    // u32 xBAC;
    // u32 xBB0;
    // u32 xBB4;
    // u32 xBB8;
    DynamicBoneTable* xBBC_dynamicBoneTable;
    UNK_T xBC0;
    u8 xBC4;
    u8 xBC5;
    u8 xBC6;
    u8 xBC7;
    u32 xBC8;
    Vec2 xBCC_unk;
    Vec2 xBD4_grabRange;
    itECB xBDC;
    itECB xBEC;
    itECB xBFC;
    itECB xC0C;
    itECB xC1C;
    s32 xC2C;
    s32 xC30;

    s32 xC34_damageDealt; // Rounded down
    s32 xC38;             // 0xc38 - ItemKind?
    f32 xC3C;             // 0xc3c
    f32 xC40;             // 0xc40
    f32 xC44;             // 0xc44
    s32 xC48;             // 0xc48
    s32 xC4C;  // Something to do with damage. 0x80077464 checks this against
               // reflectors' maximum damage threshold
    s32 xC50;  // 0xc50
    f32 xC54;  // 0xc54
    Vec3 xC58; // 0xc58
    HSD_GObj* xC64_reflectGObj; // GObj that reflected this item?
    f32 xC68;                   // 0xc68
    f32 xC6C;                   // 0xc6c
    f32 xC70;                   // 0xc70
    s32 xC74;
    Vec2 xC78;                   // 0xc78
    S32Vec2 xC80;                // 0xc80
    s32 xC88;                    // 0xc88
    u16 xC8C;                    // 0xc8c
    HSD_GObj* xC90_absorbGObj;   // 0xc90
    s32 xC94;                    // 0xc94
    f32 xC98;                    // 0xc98
    s32 xC9C;                    // Total damage taken?
    s32 xCA0;                    // Last amount of damage taken?
    s32 xCA4;                    // 0xca4
    s32 xCA8;                    // 0xca8, hitlag related
    s32 xCAC_angle;              // 0xcac
    s32 xCB0_source_ply;         // 0xcb0, damage source ply number
    s32 xCB4;                    // 0xcb4
    f32 xCB8_outDamageDirection; // 0xcb8, updated @ 80078184
    f32 xCBC_hitlagFrames;       // 0xcbc, hitlag frames remaining
    f32 xCC0;                    // 0xcc0
    s32 xCC4;           // 0xcc4, switch statement for this in it_8027CBFC
    f32 xCC8_knockback; // 0xcc8
    f32 xCCC_incDamageDirection; // Direction from which damage was applied?
    f32 xCD0;                    // 0xcd0
    Vec3 xCD4;                   // 0xcd4
    Vec3 xCE0;                   // 0xce0
    HSD_GObj* xCEC_fighterGObj;  // 0xcec
    HSD_GObj* xCF0_itemGObj; // 0xcf0, is a fp GObj, but is the owner of the

    HSD_GObj* xCF4_fighterGObjUnk;

    /// @at{CF8} @sz{4}
    /// @brief The entity that was detected by this item's inert hitbox.
    HSD_GObj* toucher;

    HSD_GObj* xCFC;

    /// @at{D00} @sz{4}
    /// @brief The entity that got grabbed by this item.
    HSD_GObj* grab_victim;

    /// @at{D04} @sz{4}
    /// @brief The entity that collided with this item's hitbox?
    HSD_GObj* atk_victim;

    u8 xD08;
    u8 xD09;
    u8 xD0A;
    u8 xD0B;

    /// @at{D0C} @sz{4}
    enum_t xD0C;

    f32 xD10;

    /// @at{D14} @sz{4}
    HSD_GObjPredicate animated;

    /// @at{D18} @sz{4}
    HSD_GObjEvent physics_updated;

    /// @at{D1C} @sz{4}
    HSD_GObjPredicate collided;

    /// @at{D20} @sz{4}
    /// @todo What does this mean?
    HSD_GObjEvent on_accessory;

    /// @at{D24} @sz{4}
    /// @brief Runs when an entity is detected by this item's inert hibox.
    HSD_GObjPredicate touched;

    /// @at{D28} @sz{4}
    /// @brief Runs after applying hitlag in damage.
    /// @todo What function is @c 8026a62c?
    HSD_GObjEvent entered_hitlag;

    // 0xd2c, runs after exiting hitlag in hitlag, update proc 8026a200
    HSD_GObjEvent exited_hitlag;

    /// @at{D28} @sz{4}
    /// @brief Runs when the item is jumped on.
    /// @todo What function is @c 80269bac?
    HSD_GObjPredicate jumped_on;

    /// @at{D34} @sz{4}
    /// @brief When grabbing a fighter, run this function on self.
    HSD_GObjEvent grab_dealt;

    /** @at{D38} @sz{4}
     * @brief When grabbing a fighter, run this function on them.
     *
     * @p gobj0 - The victim of the grab. \n
     * @p gobj1 - This item's entity.
     */
    HSD_GObjInteraction grabbed_for_victim;

    f32 xD3C_spinSpeed;
    f32 xD40;
    f32 xD44_lifeTimer;
    f32 xD48_halfLifeTimer; // Not radioactive, just the item's original
                            // lifetime halved
    int xD4C; // Number of ammo remaining (Checked by shootable items in
              // it_8026B594)
    u32 xD50_landNum;  // Number of times this item has landed
    u32 xD54_throwNum; // Number of times this item has been thrown
    u32 xD58;
    u32 xD5C;

    /// @at{D60} @sz{4}
    enum_t destroy_type;

    /// @at{D64} @sz{4}
    enum_t sfx_unk1;

    /// @at{D68} @sz{4}
    enum_t sfx_unk2;

    s32 xD6C;
    s32 xD70;
    s32 xD74;
    s32 xD78;

    /// @at{D7C} @sz{4}
    /// @brief SFX that plays when this item is destroyed
    enum_t destroy_sfx;

    s32 xD80;
    s32 xD84;
    s32 xD88_attackID;
    u16 xD8C_attack_instance;
    s16 xD8E;
    union Struct2070 xD90; // some bit struct/union
    Vec2 xD94;
    S32Vec2 xD9C;
    u32 xDA4_word;
    u16 xDA8_short;
    union {
        UnkFlagStruct xDAA_flag; // Develop mode stuff?
        u8 xDAA_byte;
    };
    u32 xDAC_itcmd_var0;
    u32 xDB0_itcmd_var1;
    u32 xDB4_itcmd_var2;
    u32 xDB8_itcmd_var3;
    u32 xDBC_itcmd_var4;
    u32 xDC0;
    u32 xDC4;
    flag32 xDC8_word;
    struct {
        u8 b0 : 1;
        u8 b1 : 1;
        u8 b2 : 1;
        u8 b3 : 1;
        u8 b4567 : 4;
    } xDCC_flag;
    CameraBoxFlags xDCD_flag;
    UnkFlagStruct xDCE_flag;
    UnkFlagStruct xDCF_flag;
    UnkFlagStruct xDD0_flag;
    UnkFlagStruct xDD1_flag;
    UnkFlagStruct xDD2_flag;
    UnkFlagStruct xDD3_flag;
    union Item_ItemVars {
        itBombHei_ItemVars bombhei;
        itBox_ItemVars box;
        itCapsule_ItemVars capsule;
        itDosei_ItemVars dosei;
        itChicorita_ItemVars chicorita;
        itMaril_ItemVars maril;
        itLizardon_ItemVars lizardon;
        itLucky_ItemVars lucky;
        itClimbersBlizzard_ItemVars climbersblizzard;
        itCoin_ItemVars coin;
        itDrMarioPill_ItemVars drmariopill;
        itEgg_ItemVars egg;
        itFFlower_ItemVars fflower;
        itFFlowerFlame_ItemVars fflowerflame;
        itFlipper_ItemVars flipper;
        itFoods_ItemVars foods;
        itFoxBlaster_ItemVars foxblaster;
        itFoxIllusion_ItemVars foxillusion;
        itFoxLaser_ItemVars foxlaser;
        itFreeze_ItemVars freeze;
        itGShell_ItemVars gshell, rshell, zgshell, zrshell;
        itHassam_ItemVars hassam;
        itHeart_ItemVars heart;
        itHeiho_ItemVars heiho;
        it_266F_ItemVars it_266F;
        it_279D_ItemVars it_279D;
        it_27B5_ItemVars it_27B5;
        it_27CE_ItemVars it_27CE;
        it_27CF_ItemVars it_27CF;
        it_2E5A_ItemVars it_2E5A;
        it_2E6A_ItemVars_1 it_2E6A_1;
        it_2F28_ItemVars it_2F28;
        itKinoko_ItemVars kinoko;
        itKirbyHammer_ItemVars kirbyhammer;
        itKusudama_ItemVars kusudama;
        itKlap_ItemVars klap;
        itLeadead_ItemVars leadead;
        itLGun_ItemVars lgun;
        itLGunBeam_ItemVars lgunbeam;
        itLGunRay_ItemVars lgunray;
        itLinkArrow_ItemVars linkarrow;
        itLinkBomb_ItemVars linkbomb;
        itLinkBoomerang_ItemVars linkboomerang;
        itLinkBow_ItemVars linkbow;
        itLinkHookshot_ItemVars linkhookshot;
        itMBall_ItemVars mball;
        itMato_ItemVars mato;
        itMsBomb_ItemVars msbomb;
        itNokoNoko_ItemVars nokonoko;
        itOctarock_ItemVars octarock;
        itPeachTurnip_ItemVars peachturnip;
        itPikachutJoltGround_ItemVars pikachujoltground;
        itPikachutJoltAir_ItemVars pikachujoltair;
        itPKFlush_ItemVars pkflush;
        itPKFlushExplode_ItemVars pkflushexplode;
        itPKThunder_ItemVars pkthunder;
        itPokemon_ItemVars pokemon;
        itSamusBomb_ItemVars samusbomb;
        itSamusGrapple_ItemVars samusgrapple;
        itSeakNeedleThrown_ItemVars seakneedlethrown;
        itSonans_ItemVars sonans;
        itStar_ItemVars star;
        itSword_ItemVars sword;
        itTaru_ItemVars taru;
        itTincle_ItemVars tincle;
        itTomato_ItemVars tomato;
        itWhispyApple_ItemVars whispyapple;
        itWhiteBea_ItemVars whitebea;
        itZeldaDinFireExplode_ItemVars zeldadinfireexplode;
        itMasterHandBullet_ItemVars masterhandbullet;
        itMasterHandLaser_ItemVars masterhandlaser;
        itUnk4_ItemVars unk4;
        itStarRodStar_ItemVars starrodstar;
        itZeldaDinFire_ItemVars zeldadinfire;
        itTosakinto_ItemVars tosakinto;
        itMDisable_ItemVars mdisable;
        itKoopaFlame_ItemVars koopaflame;
        u8 _[0xFCC - 0xDD4];
    } xDD4_itemVar;
};
STATIC_ASSERT(sizeof(struct Item) == 0xFCC);

struct sdata_ItemGXLink {
    GObj_RenderFunc x0_renderFunc;
};

struct r13_ItemTable {
    s32 filler;
    Article* x0_article[0x9F];
};

struct BobOmbRain {
    HSD_GObj* x0;
    HSD_JObj* x4;
    Vec3 x8_vec;
    enum_t x14;
    s32 x18;
    UnkFlagStruct x1C;
};

struct SpawnItem {
    /*  +0 */ HSD_GObj* x0_parent_gobj;
    /*  +4 */ HSD_GObj* x4_parent_gobj2;
    /*  +8 */ ItemKind kind;
    /*  +C */ enum_t hold_kind;
    /* +10 */ s32 x10;
    /* +14 */ Vec3 pos;
    /* +20 */ Vec3 prev_pos;
    /* +2C */ Vec3 vel;
    /* +38 */ f32 facing_dir;
    /* +3C */ s16 x3C_damage;
    /* +3E */ s16 x3E;
    /* +40 */ s32 x40;
    /* +44 */ UnkFlagStruct x44_flag;
    /* +45 */ UnkFlagStruct x45_flag;
    /* +46 */ UnkFlagStruct x46_flag;
    /* +47 */ UnkFlagStruct x47_flag;
    /* +48 */ GroundOrAir x48_ground_or_air;
};

struct ItemModStruct {
    GXColor x0_unk;
};

struct ItemCommonData {
    s32 x0;
    u32 x4;
    u32 x8;
    u32 xC;
    u32 x10;
    s32 x14;
    u32 x18;
    u32 x1C;
    u32 x20;
    u32 x24;
    u32 x28;
    u32 x2C;
    u32 x30; // lifetime?
    u32 x34;
    u32 x38_float;
    s32 x3C_float;
    s32 x40_float;
    s32 x44_float;
    u8 x48_byte;
    f32 x4C_float;
    s32 x50_float;
    f32 x54_float;
    f32 x58_float;
    f32 x5C_float;
    f32 x60_float;
    s32 x64_float;
    f32 x68_float;
    f32 x6C_float;
    f32 x70_float;
    f32 x74_float;
    f32 x78_float;
    f32 x7C_float;
    f32 x80_float[13];
    s32 xB4;
    f32 xB8;
    f32 xBC;
    f32 xC0;
    f32 xC4;
    f32 xC8;
    f32 xCC;
    f32 xD0;
    f32 xD4;
    u32 xD8;
    s32 xDC;
    f32 unk_degrees; ///< @at{E0}
    u8 filler_1a[0xE8 - 0xE4];
    u8 xE8; // struct that has a float (scale?) as the first member? See
            // it_80275BC8
    u8 filler_1a_2[0xF0 - 0xEC];
    f32 xF0;
    f32 xF4;
    f32 xF8;
    u8 filler_1b[0x124 - 0xFC];
    s32 x124; // max value for a random integer generation in it_8026F6BC
    s32 x128; // used in it_8026CF04
    s32 x12C; // used in it_8026CF04
    s32 x130; // used in it_8026CF04
    s32 x134; // used in it_8026CF04
    // u8 filler_2[0x148 - 0x138]; - replaced with vars that are used for
    // calc's in it_8026F8B4
    s32 x138;
    s32 x13C;
    s32 x140;
    f32 x144;
    s32 x148;
    f32 x14C;
    f32 x150;
    f32 x154;
    f32 x158;
    f32 x15C;
};

struct Item_r13_Data {
    ItemCommonData* item_common;
    void** common_items;
    void** adventure_items;
    void** pokeball_items;
    s32 x10;
    s32 x14;
};

struct HSD_ObjAllocUnk2 {
    // float x0;
    // float x4;
    // float x8;
    // float xC;
    // u8 pad_10[0xB0 - 0x10];
    itECB ecb_arr[11];
    int xB0;
    int xB4;
    int xB8;
    M2C_UNK xBC;
    // Vec3 xC0;
    // u8 pad_CC[0x148 - 0xCC];
    Vec3 xC0_vec3_arr[11];
    u32 x144;
    u32 x148;
    u32 x14C;
    u32 x150; // num of itECB/Vec3's with data?
    UnkFlagStruct x154;
};

struct x1C_struct {
    s32 x1C;
};

struct HSD_ObjAllocUnk {
    s32 x0;
    s32 x4;
    s32 x8;
    s32 xC;
    s32 x10;
    s32 x14;
    u32 x18;
    s32 x1C;
    s32 x20;
    s32 x24;
    s32 x28;
    s32 x2C; // u32 or s32?
    s32 x30; // u32 or s32?
    s32 x34;
    s32 x38;
    s32 x3C;
    s32 x40;
    s32 x44;
    s32 x48;
    s32 x4C;
    s32 x50;
    s32 x54;
    s32 x58;
    s32 x5C;
    s32 x60; // u32 or s32?
    s32 x64; // u32 or s32?
};

struct HSD_ObjAllocUnk6 {
    u8 x0;  // Gets incremented and decremented by 1 for various checks. Gets
            // indexed into x4's struct
    u8* x4; // Points to struct of ItemKinds (or array?)
    u16 x8; // Max value for random integers
    u16 xA;
    u16* xC; // Points to struct of ???
};

struct HSD_ObjAllocUnk4 {
    u32 x0;
    HSD_ObjAllocUnk6 x4;
    s32 x14;
    u64 x18; // Gets set equal to gm_8016AEA4(), aka lbl_8046B6A0.unk_24D3
             // (which is an s8?)
};

struct HSD_ObjAllocUnk5 {
    u8 x0;
    u32 x4;
    u16 x8;
    u16 xA;
    u16 xC;
};

typedef struct HSD_ObjAllocUnk7 {
    s32 x0;
    void* x4;
    HitCapsule* x8;
    void* xC;
} HSD_ObjAllocUnk7;

struct it_8026C47C_arg0_t {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
};

struct it_8026F3D4_arg1_t {
    bool x0;
    ItemKind x4;
    Item_GObj* x8;
};

struct it_8026F3D4_body_t {
    u8 x0[32]; // This array length was a guess
};

#endif
