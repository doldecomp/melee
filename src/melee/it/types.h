/**
 * @file types.h
 * @brief Core data structures and state definitions for Melee items.
 * @details This header defines the central Item structure representing dynamic
 *          items, projectiles, and Pokémon in Super Smash Bros. Melee. It contains
 *          kinematic states, collision attributes (ECB, hitboxes, hurtboxes),
 *          owner and victim tracking, animation state machine pointers, and per-item
 *          variable storage.
 * Module prefix: it (Item)
 */

#ifndef MELEE_IT_TYPES_H
#define MELEE_IT_TYPES_H

#include <Runtime/platform.h>

#include <melee/cm/forward.h>
#include <melee/ef/forward.h>
#include <melee/it/forward.h> // IWYU pragma: export
#include <melee/it/kinds/forward.h>
#include <sysdolphin/baselib/forward.h>

#include <dat_macros.h>
#include <placeholder.h>

#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <melee/ft/types.h>
#include <melee/it/itCharItems.h>
#include <melee/it/itCommonItems.h>
#include <melee/it/itPKFlash.h>
#include <melee/it/itPKThunder.h>
#include <melee/lb/types.h>

/// Recent Pokemon selections and the shared Mew/Celebi spawn limit.
struct PokemonSelectionState {
    /* 0x0 */ ItemKind last_kind;       ///< Most recently spawned Pokémon kind.
    /* 0x4 */ ItemKind previous_kind;   ///< Second most recently spawned Pokémon kind.
    /* 0x8 */ bool rare_spawned;        ///< True if Mew or Celebi has already spawned this match.
};

/// Camera subject bounding box flags for item tracking.
struct CameraBoxFlags {
    struct CameraBoxFlags_x0 {
        u8 b01 : 2; ///< Camera tracking mode (from ItemAttr->x1_67_cam_kind).
        u8 b2 : 1;  ///< Camera bounding box enable flag.
        u8 b3 : 1;  ///< Camera focus flag.
        u8 b4 : 1;  ///< Viewport culling flag.
        u8 b5 : 1;  ///< Zoom consideration flag.
        u8 b6 : 1;  ///< Subject priority bit 0.
        u8 b7 : 1;  ///< Subject priority bit 1.
    } x0;
};

/// 32-bit individual flag structure for item script commands and physics states.
struct flag32 {
    struct flag32_flags {
        u32 x0 : 1;  ///< Flag 0: Active / initialized state.
        u32 x1 : 1;  ///< Flag 1: Spawned by non-fighter entity.
        u32 x2 : 1;  ///< Flag 2: Can be picked up.
        u32 x3 : 1;  ///< Flag 3: Surface collision enabled.
        u32 x4 : 1;  ///< Flag 4: Heavy item carry state.
        u32 x5 : 1;  ///< Flag 5: In air / falling.
        u32 x6 : 1;  ///< Flag 6: Thrown item state.
        u32 x7 : 1;  ///< Flag 7: Grounded resting state.
        u32 x8 : 1;  ///< Flag 8: Destroy on landing.
        u32 x9 : 1;  ///< Flag 9: Invulnerable to attacks.
        u32 xA : 1;  ///< Flag 10: Reflected projectile state.
        u32 xB : 1;  ///< Flag 11: Absorbed projectile state.
        u32 xC : 1;  ///< Flag 12: Shield bounce enabled (from ItemAttr->x1_5).
        u32 xD : 1;  ///< Flag 13: Clank enabled against other hitboxes.
        u32 xE : 1;  ///< Flag 14: Hitbox active flag.
        u32 xF : 4;  ///< Flags 15-18: Attack sub-state nibble.
        u32 x13 : 1; ///< Flag 19: Attached / stuck to target.
        u32 x14 : 1; ///< Flag 20: Exploding / detonating.
        u32 x15 : 1; ///< Flag 21: Despawn timer expired.
        u32 x16 : 1; ///< Flag 22: Flashing half-life warning.
        u32 x17 : 2; ///< Flags 23-24: Hold category (from ItemAttr->x1_1).
        u32 x19 : 1; ///< Flag 25: Spin enabled (from ItemAttr->x1_3).
        u32 x1A : 1; ///< Flag 26: Facing direction flip on throw (from ItemAttr->x1_4).
        u32 x1B : 1; ///< Flag 27: Custom physics flag.
        u32 x1C : 1; ///< Flag 28: ECB collision update flag.
        u32 x1D : 1; ///< Flag 29: Floor collision sensor enabled.
        u32 x1E : 1; ///< Flag 30: Wall collision sensor enabled.
        u32 x1F : 1; ///< Flag 31: Ceiling collision sensor enabled.
    } flags;
};

/// Dynamic bone pointer hierarchy table for item physics simulation.
struct DynamicBoneTable {
    HSD_JObj* bones[100]; ///< Array of up to 100 dynamic bone joints.
};
ASSERT_SIZE(struct DynamicBoneTable, 0x190);

/// Descriptor for a single physics-simulated dynamic bone chain.
struct Item_DynamicBones {
    int flags;             ///< Dynamics simulation control flags.
    HSD_JObj* skeleton;    ///< Root skeleton joint for the dynamic bone chain.
    DynamicsDesc dyn_desc; ///< Dynamics parameters (gravity, damping, spring constant).
};
ASSERT_SIZE(struct Item_DynamicBones, 0x1C);

/// Common item attributes loaded from common item archive (.dat).
struct ItemAttr {
    u8 x0_is_heavy : 1;     ///< Bit 0x80: Heavy item (e.g. crate, barrel; requires 2-handed carry).
    u8 x0_78 : 4;           ///< Character usage action type: 0: throwable, 2: swingable, 3: shootable.
    u8 x0_hold_kind : 3;    ///< Grip and hand hold behavior (Item_HoldKinds).
    u8 x1_1 : 2;            ///< Hold flags (bits 0x30).
    u8 x1_3 : 1;            ///< Spin on throw flag (bit 0x20).
    u8 x1_4 : 1;            ///< Facing flip on throw (bit 0x10).
    u8 x1_5 : 1;            ///< Shield bounce flag (bit 0x08).
    u8 x1_67_cam_kind : 2;  ///< Camera tracking kind (bits 0x06, stored to Item->xDCD_flag).
    u8 x1_8 : 1;            ///< Bit 0x01: Miscellaneous flag.
    u8 x3;                  ///< Padding / reserved byte.
    f32 x4_throw_speed_mul; ///< Throw velocity multiplier applied when thrown by a fighter.
    s32 x8;                 ///< Throw animation or sound index.
    f32 xC_spin_speed;      ///< Angular spin velocity in radians per frame when airborne.
    f32 x10_fall_speed;     ///< Terminal fall velocity / gravity acceleration.
    f32 x14_fall_speed_max; ///< Maximum downward fall speed.
    f32 x18;                ///< Air friction / drag coefficient.
    f32 x1C_damage_mul;     ///< Damage scaling multiplier applied when taking damage (@ 80270F90).
    itECB x20;              ///< Base Environment Collision Box (ECB) offsets.
    Vec2 x30_unk;           ///< Bounding collision extent vector.
    Vec2 x38_grab_range;    ///< Pickup detection range bounding box.
    itECB x40;              ///< Secondary Environment Collision Box offsets.
    f32 x50;                ///< Horizontal ground friction deceleration.
    f32 x54;                ///< Air mobility / horizontal deceleration.
    f32 x58;                ///< Bounce restitution elasticity multiplier.
    f32 x5c;                ///< Minimum velocity cutoff threshold before stopping.
    f32 x60_scale;          ///< Base model visual scale (does not alter hitbox radii).

    /// GFX to play on destroy.
    enum_t destroy_gfx;

    s32 x68;                ///< Destruction visual effect parameter.
    s32 x6C;                ///< SFX played when item is picked up.
    s32 x70;                ///< SFX played when item is thrown.
    s32 x74;                ///< SFX played when item impacts a surface or target.

    /// SFX that plays when this item is destroyed.
    enum_t destroy_sfx;

    s32 x7C;                ///< Custom SFX 1.
    s32 x80;                ///< Custom SFX 2.
};

/// Joint dynamics template list container for secondary item animations.
struct ItemDynamics {
    int count;                                          ///< Number of bone dynamics templates.
    BoneDynamicsTemplate* dyn_descs DAT_COUNT(count);   ///< Array of dynamic bone descriptors.
};

/// Animation joint and script descriptors for an item action state.
struct ItemStateDesc {
    HSD_AnimJoint* x0_anim_joint;           ///< Skeletal bone animation joint tree.
    HSD_MatAnimJoint* x4_matanim_joint;     ///< Material / texture color animation joint tree.
    HSD_ShapeAnimJoint* x8_parameters;      ///< Shape / morph target animation joint tree.
    UNK_T xC_script;                        ///< Subaction bytecode script pointer.
};

/// Array of state descriptors indexed by state anim_id.
struct ItemStateArray {
    struct ItemStateDesc x0_itemStateDesc[8] DAT_EXTENT; ///< State descriptor array.
};

/// Item 3D model hierarchy descriptor.
struct ItemModelDesc {
    HSD_Joint* x0_joint;        ///< Root HSD_Joint node for the item skeleton.
    u32 x4_bone_count;          ///< Total number of joints/bones in the hierarchy.
    s32 x8_bone_attach_id;      ///< Bone ID used when attaching to a fighter's hand.
    u8 xC_bit_field;            ///< Model rendering configuration flags.
};

/// Hurtbox capsule descriptor from Article archive definition.
typedef struct {
    enum_t bone_id; ///< Target bone index to attach this hurtbox to.
    Vec3 a_offset;  ///< First sphere center offset relative to bone.
    Vec3 b_offset;  ///< Second sphere center offset relative to bone.
    f32 scale;      ///< Capsule radius scale factor.
} ItHurtBoneDesc;

/// List of vulnerable hurtboxes attached to an item.
typedef struct {
    s32 count;              ///< Number of hurtbox descriptors.
    ItHurtBoneDesc* descs;  ///< Array of hurtbox descriptors.
} ItHurtBoneList;

/// Article archive definition containing all assets and descriptors for an item kind.
struct Article {
    ItemAttr* x0_common_attr;                                   ///< Common physics and gameplay attributes.
    void* x4_specialAttributes DAT_TYPE(ItemSpecialAttributes); ///< Item-specific custom attributes from DAT.
    ItHurtBoneList* x8_hurtbones;                               ///< List of vulnerable hurtbox definitions.
    ItemStateArray* xC_itemStates;                              ///< Array of action state descriptors.
    ItemModelDesc* x10_modelDesc;                               ///< Model hierarchy and bone attachment info.
    ItemDynamics* x14_dynamics;                                 ///< Dynamic bone physics templates.
};

/// Internal state variables for item state machine 266F.
typedef struct it_266F_ItemVars {
    u16 x0;                             ///< State parameter 0.
    u8* x4;                             ///< Data buffer pointer.
    u16 x8;                             ///< State parameter 1.
    u8* xC;                             ///< Secondary buffer pointer.
    s32 x10;                            ///< Counter variable 0.
    s32 x14;                            ///< Counter variable 1.
    UnkFlagStruct x18;                  ///< Control flags.
    struct lbColl_8000A10C_arg0_t x1C;  ///< Collision parameter structure.
} it_266F_ItemVars;

/// Material color modifier for items.
struct ItemModStruct {
    GXColor x0_unk; ///< Tint color applied to item material.
};

/// Offensive hitbox capsule attached to an item.
typedef struct ItemHitbox {
    HitCapsule hit;     ///< Core HitCapsule structure (damage, angle, knockback, element).
    u8 x138 : 1;        ///< Hitbox active enable bit.
    u8 x138_b1_7 : 7;   ///< Hitbox priority / interaction bits.
    u8 x139[3];         ///< Padding / reserved bytes.
} ItemHitbox;

/// Dynamic bone runtime state record.
struct xB6C_t {
    Vec3 xB6C;      ///< Current dynamic bone world position.
    f32 xB78;       ///< Bone length or scale.
    HSD_JObj* xB7C; ///< Pointer to target HSD_JObj bone.
    u32 xB80;       ///< Dynamics status flags.
    Vec3 xB84;      ///< Previous frame dynamic bone position.
    u32 xB90;       ///< Target bone ID.
};

/**
 * @brief Core Game Object state structure for Super Smash Bros. Melee items.
 * @details Represents dynamic items, thrown projectiles, container drops, and Pokémon.
 *          Contains complete physical state (position, velocity, ECB collision data),
 *          action state indices, owner/victim entity links, timers, and offensive hitboxes.
 * Size: 0xFCC (4044 bytes).
 */
struct Item {
    /* 0x000 */ void* x0;                   ///< Pointer to internal render or display structure.
    /* 0x004 */ HSD_GObj* entity;           ///< Pointer to the owning HSD_GObj game object container.
    /* 0x008 */ s32 x8;                     ///< Item processing flags or state variable.
    /* 0x00C */ enum_t spawn_kind;          ///< Spawn origin type (ambient spawn, fighter drop, container break).
    /* 0x010 */ ItemKind kind;              ///< Item kind identifier enum (e.g. It_Kind_Capsule, It_Kind_BombHei).
    /* 0x014 */ Item_HoldKinds hold_kind;   ///< Hold behavior kind defining how fighters grip and swing this item.
    /* 0x018 */ s32 x18;                    ///< Spawn parameter flags passed from SpawnItem->x10.
    /* 0x01C */ s32 x1C;                    ///< Global sequential spawn instance counter (it_804D6D10++).
    /* 0x020 */ u8 x20_team_id;             ///< Owning player's team ID (-1: neutral/none, 0: Red, 1: Blue, 2: Green).
    /* 0x021 */ u8 x21;                     ///< Player port / sub-index of owner.
    /* 0x022 */ u8 x22;                     ///< Secondary state or collision flag byte.
    /* 0x023 */ u8 x23;                     ///< Padding / state flag byte.
    /* 0x024 */ enum_t msid;                ///< Main State ID (Item Action State, e.g. Wait, Fall, Thrown).
    /* 0x028 */ enum_t anim_id;             ///< Current animation ID within the item's state table.
    /* 0x02C */ f32 facing_dir;             ///< Current horizontal facing direction (+1.0f: right, -1.0f: left).
    /* 0x030 */ f32 init_facing_dir;        ///< Initial facing direction when spawned or thrown.
    /* 0x034 */ f32 spin_spd;               ///< Angular tumble/spin speed in radians per frame.
    /* 0x038 */ f32 scl;                    ///< Item model visual scale factor (from ItemAttr->x60_scale).
    /* 0x03C */ f32 x3C;                    ///< Secondary scale or model interpolation parameter.

    // --- Velocity and Kinematic State ---
    /* 0x040 */ Vec3 x40_vel;               ///< Linear velocity vector (velocity_x, velocity_y, velocity_z).
    /* 0x04C */ Vec3 pos;                   ///< Current 3D world position coordinates.
    /* 0x058 */ Vec3 x58_vec_unk;           ///< Previous frame world position vector.
    /* 0x064 */ Vec3 x64_vec_unk2;          ///< Secondary position / velocity accumulator vector.
    /* 0x070 */ Vec3 x70_nudge;             ///< Positional displacement / nudge vector applied during collision.
    /* 0x07C */ Vec3 x7C;                   ///< Collision offset or ground surface adjustment vector.
    /* 0x088 */ Vec3 x88;                   ///< Interpolated position vector (used in it_80277040).
    /* 0x094 */ Vec3 x94;                   ///< Secondary interpolation vector (used in it_80277040).
    /* 0x0A0 */ Vec3 xA0;                   ///< Target tracking or trajectory vector (from it_802734B4).
    /* 0x0AC */ Vec3 xAC_unk;               ///< Trajectory offset vector (from it_80276CEC).

    // --- Logic, State Machine, and Model Definitions ---
    /* 0x0B8 */ ItemLogicTable* xB8_itemLogicTable;     ///< Global logic callback table (states, think, physics).
    /* 0x0BC */ ItemStateTable* xBC_itemStateContainer; ///< Pointer to current item state transition table.
    /* 0x0C0 */ GroundOrAir ground_or_air;              ///< Ground/Air state (GA_Ground = 0, GA_Air = 1).
    /* 0x0C4 */ Article* xC4_article_data;              ///< Pointer to Article definition (attributes, models, states).
    /* 0x0C8 */ HSD_Joint* xC8_joint;                   ///< Pointer to root HSD_Joint model tree.
    /* 0x0CC */ ItemAttr* xCC_item_attr;                ///< Pointer to common item attributes loaded from DAT.
    /* 0x0D0 */ ItemStateDesc* xD0_itemStateDesc;       ///< Current state descriptors (anim, matanim, shapeanim, script).
    /* 0x0D4 */ Item_DynamicBones xD4_dynamicBones[24]; ///< Array of up to 24 physics-driven dynamic bone descriptors.
    /* 0x374 */ s32 x374_dynamicBonesNum;               ///< Number of active dynamic bones in xD4_dynamicBones.

    // --- Environment Collision (CollData / ECB) ---
    /* 0x378 */ CollData x378_itemColl;     ///< Environment collision data (ECB box, floor/wall/ceiling line sensors).
    /* 0x514 */ s32 ecb_lock;               ///< ECB lock timer/state (-1 when unlocked, >= 0 locks ECB updates).

    // --- Owner and Camera Tracking ---
    /* 0x518 */ HSD_GObj* owner;            ///< Fighter or entity GObj currently carrying or controlling this item.
    /* 0x51C */ HSD_GObj* x51C;             ///< Predecessor or parent owner GObj.
    /* 0x520 */ CmSubject* x520_cameraBox;  ///< Camera subject tracker bounding box for viewport framing.

    // --- Animation Script VM and Display ---
    /* 0x524 */ CommandInfo x524_cmd;       ///< Item animation script bytecode virtual machine execution state.
    /* 0x548 */ ColorOverlay x548_colorOverlay; ///< Color flash and overlay state (hitlag, freeze, invincibility).
    /* 0x5C8 */ u8 x5C8;                    ///< Display flag / alpha modulation state byte.
    /* 0x5C9 */ u8 x5C9;                    ///< Alpha transparency override byte (255 = fully opaque).
    /* 0x5CA */ u8 x5CA;                    ///< Secondary visual effect flag byte.
    /* 0x5CB */ u8 x5CB;                    ///< Tertiary visual effect flag byte.
    /* 0x5CC */ f32 x5CC_currentAnimFrame;  ///< Current animation playback frame counter.
    /* 0x5D0 */ f32 x5D0_animFrameSpeed;    ///< Animation playback speed rate (1.0f = normal speed).

    // --- Offensive Hitboxes and Defensive Hurtboxes ---
    /* 0x5D4 */ ItemHitbox x5D4_hitboxes[4];        ///< Array of 4 offensive hitbox capsules.
    /* 0xAC4 */ u32 xAC4_ignoreItemID;              ///< Unique item ID to ignore for collision (prevents self-hit).
    /* 0xAC8 */ u8 xAC8_hurtboxNum;                 ///< Number of active hurtbox capsules on this item.
    /* 0xACC */ HurtCapsule xACC_itemHurtbox[2];    ///< Array of up to 2 vulnerable hurtboxes (crates, barrels, Bob-ombs).
    /* 0xB54 */ struct lb_80014638_arg1_t xB54;     ///< Hurtbox collision intersection record.

    // --- Dynamic Bone Hierarchy State ---
    /* 0xB68 */ u8 xB68;                            ///< Dynamic bone calculation count.
    /* 0xB69 */ u8 xB69;                            ///< Dynamic bone update flag.
    /* 0xB6A */ u8 xB6A;                            ///< Dynamic bone physics flag.
    /* 0xB6B */ u8 xB6B;                            ///< Dynamic bone state flag.
    /* 0xB6C */ struct xB6C_t xB6C_vars[2];         ///< Dynamic bone transform cache entries.
    /* 0xBBC */ DynamicBoneTable* xBBC_dynamicBoneTable; ///< Pointer to dynamic bone hierarchy table.
    /* 0xBC0 */ EF_QueuedEffect* xBC0;              ///< Pointer to queued particle or special effect generator.
    /* 0xBC4 */ GXColor xBC4;                       ///< Material color modulation tint.
    /* 0xBC8 */ ItemModStruct xBC8;                 ///< Color modifier structure.

    // --- Interaction and Bounding Ranges ---
    /* 0xBCC */ Vec2 xBCC_unk;                      ///< Bounding collision extent vector (from ItemAttr->x30_unk).
    /* 0xBD4 */ Vec2 xBD4_grabRange;                ///< Pickup detection range bounding box (from ItemAttr->x38_grab_range).
    /* 0xBDC */ itECB xBDC;                         ///< Environment collision box variant 1 (top/bottom/left/right offsets).
    /* 0xBEC */ itECB xBEC;                         ///< Environment collision box variant 2 (current base ECB).
    /* 0xBFC */ itECB xBFC;                         ///< Secondary collision box variant 1.
    /* 0xC0C */ itECB xC0C;                         ///< Secondary collision box variant 2.
    /* 0xC1C */ itECB xC1C;                         ///< Secondary collision box variant 3.
    /* 0xC2C */ s32 xC2C;                           ///< Collision sensor status flags.
    /* 0xC30 */ s32 xC30;                           ///< Collision surface interaction flags.

    // --- Damage, Reflection, and Absorption Dynamics ---
    /* 0xC34 */ s32 xC34_damageDealt;               ///< Amount of damage dealt to target on impact, rounded down.
    /* 0xC38 */ s32 xC38;                           ///< Stored ItemKind or interaction state.
    /* 0xC3C */ f32 xC3C;                           ///< Damage scaling factor.
    /* 0xC40 */ f32 xC40;                           ///< Damage knockback factor.
    /* 0xC44 */ f32 xC44;                           ///< Secondary knockback scaling.
    /* 0xC48 */ s32 xC48;                           ///< Damage state counter.
    /* 0xC4C */ s32 xC4C;                           ///< Reflected damage amount; tested against reflector max damage threshold.
    /* 0xC50 */ s32 xC50;                           ///< Reflection count or state.
    /* 0xC54 */ f32 xC54;                           ///< Reflected speed multiplier.
    /* 0xC58 */ Vec3 xC58;                          ///< Reflected direction velocity vector.
    /* 0xC64 */ HSD_GObj* xC64_reflectGObj;         ///< GObj (reflector/fighter) that reflected this item/projectile.
    /* 0xC68 */ f32 xC68;                           ///< Reflected angular velocity or speed modifier.
    /* 0xC6C */ f32 xC6C;                           ///< Knockback scaling multiplier.
    /* 0xC70 */ f32 xC70;                           ///< Damage scaling multiplier.
    /* 0xC74 */ s32 xC74;                           ///< Hit counter.
    /* 0xC78 */ S32Vec2 xC78;                       ///< Grid coordinate or sensor offsets.
    /* 0xC80 */ struct Struct207C xC80;             ///< Shield interaction status.
    /* 0xC88 */ s32 xC88;                           ///< Shield bounce counter.
    /* 0xC8C */ u16 xC8C;                           ///< Shield hit timer.
    /* 0xC90 */ HSD_GObj* xC90_absorbGObj;          ///< GObj that absorbed this projectile (e.g. PSI Magnet, Oil Bucket).
    /* 0xC94 */ s32 xC94;                           ///< Absorption damage accumulator.
    /* 0xC98 */ f32 xC98;                           ///< Absorbed health recovery amount.
    /* 0xC9C */ s32 xC9C;                           ///< Total cumulative damage taken by this item.
    /* 0xCA0 */ s32 xCA0;                           ///< Last single amount of damage received.
    /* 0xCA4 */ s32 xCA4;                           ///< Hit lag duration in frames.
    /* 0xCA8 */ s32 xCA8;                           ///< Hitlag frames counter (hitlag = knockback * 0.4 frames).
    /* 0xCAC */ s32 xCAC_angle;                     ///< Trajectory angle in degrees from incoming attack.
    /* 0xCB0 */ s32 xCB0_source_ply;                ///< Player port number (0..5, 6: neutral) that caused damage.
    /* 0xCB4 */ s32 xCB4;                           ///< Player port number of last thrower.
    /* 0xCB8 */ f32 xCB8_outDamageDirection;        ///< Facing direction of outgoing damage/knockback (+1.0f or -1.0f).
    /* 0xCBC */ f32 xCBC_hitlagFrames;              ///< Fractional hitlag freeze frames remaining.
    /* 0xCC0 */ f32 xCC0;                           ///< Secondary hitlag timer.
    /* 0xCC4 */ s32 xCC4;                           ///< Damage response category (switched in it_8027CBFC).
    /* 0xCC8 */ f32 xCC8_knockback;                 ///< Knockback magnitude applied to the item.
    /* 0xCCC */ f32 xCCC_incDamageDirection;        ///< Direction from which incoming attack arrived (+1.0f or -1.0f).
    /* 0xCD0 */ f32 xCD0;                           ///< Secondary damage angle / force.
    /* 0xCD4 */ Vec3 xCD4;                          ///< Incoming knockback velocity impulse vector.
    /* 0xCE0 */ Vec3 xCE0;                          ///< Target position offset.

    // --- Entity and Target Tracking ---
    /* 0xCEC */ HSD_GObj* xCEC_fighterGObj;         ///< Fighter GObj interacting with or holding this item.
    /* 0xCF0 */ HSD_GObj* xCF0_itemGObj;            ///< Item GObj that collided with or spawned this item.
    /* 0xCF4 */ HSD_GObj* xCF4_fighterGObjUnk;      ///< Secondary fighter GObj reference.
    /* 0xCF8 */ HSD_GObj* toucher;                  ///< Entity detected by this item's proximity / touch hitbox.
    /* 0xCFC */ HSD_GObj* xCFC;                     ///< Secondary interaction target entity.
    /* 0xD00 */ HSD_GObj* grab_victim;              ///< Entity currently grabbed or held captive by this item.
    /* 0xD04 */ HSD_GObj* atk_victim;               ///< Entity struck by this item's attack hitbox.

    /* 0xD08 */ u8 xD08;                            ///< State update counter.
    /* 0xD09 */ u8 xD09;                            ///< Transition state byte.
    /* 0xD0A */ u8 xD0A;                            ///< Animation looping flag.
    /* 0xD0B */ u8 xD0B;                            ///< Subaction update byte.
    /* 0xD0C */ enum_t xD0C;                        ///< Subaction state ID.
    /* 0xD10 */ f32 xD10;                           ///< State timer / animation blend weight.

    // --- Event and Callback Hooks ---
    /* 0xD14 */ HSD_GObjPredicate animated;         ///< Callback invoked after animation frame updates.
    /* 0xD18 */ HSD_GObjEvent physics_updated;      ///< Callback invoked after physics (gravity, friction, velocity).
    /* 0xD1C */ HSD_GObjPredicate collided;         ///< Callback invoked after environment / surface collision.
    /* 0xD20 */ HSD_GObjEvent on_accessory;         ///< Callback for accessory updates (particles, dynamic joints).
    /* 0xD24 */ HSD_GObjPredicate touched;          ///< Callback invoked when an entity touches proximity hitbox.
    /* 0xD28 */ HSD_GObjEvent entered_hitlag;       ///< Callback invoked when entering hitlag freeze.
    /* 0xD2C */ HSD_GObjEvent exited_hitlag;        ///< Callback invoked when exiting hitlag freeze.
    /* 0xD30 */ HSD_GObjPredicate jumped_on;        ///< Callback invoked when a fighter jumps on the item (Flipper, Spring).
    /* 0xD34 */ HSD_GObjEvent grab_dealt;           ///< Callback invoked on self when this item grabs a fighter.
    /* 0xD38 */ HSD_GObjInteraction grabbed_for_victim; ///< Interaction callback invoked on victim when grabbed.

    // --- Timers, Ammo, and Destruction Parameters ---
    /* 0xD3C */ f32 xD3C_spinSpeed;                 ///< Tumble angular velocity applied when airborne or thrown.
    /* 0xD40 */ f32 xD40;                           ///< Secondary spin or bounce damping factor.
    /* 0xD44 */ f32 xD44_lifeTimer;                 ///< Remaining lifetime in frames before despawning.
    /* 0xD48 */ f32 xD48_halfLifeTimer;             ///< Half of original lifetime; flashing warning begins below this.
    /* 0xD4C */ int xD4C;                           ///< Ammo counter for shootable items (Scope, Ray Gun, Star Rod).
    /* 0xD50 */ u32 xD50_landNum;                   ///< Number of times this item has landed on the stage.
    /* 0xD54 */ u32 xD54_throwNum;                  ///< Number of times this item has been thrown by fighters.
    /* 0xD58 */ u32 xD58;                           ///< Bounce counter.
    /* 0xD5C */ u32 xD5C;                           ///< Drop / spawn state counter.
    /* 0xD60 */ enum_t destroy_type;                ///< Destruction mode (e.g. 4: despawn, break, explode).
    /* 0xD64 */ enum_t sfx_unk1;                    ///< Primary sound effect ID.
    /* 0xD68 */ enum_t sfx_unk2;                    ///< Secondary sound effect ID.
    /* 0xD6C */ s32 xD6C;                           ///< Sound effect playback voice channel.
    /* 0xD70 */ s32 xD70;                           ///< Pickup SFX ID (from ItemAttr->x6C).
    /* 0xD74 */ s32 xD74;                           ///< Throw SFX ID (from ItemAttr->x70).
    /* 0xD78 */ s32 xD78;                           ///< Hit SFX ID (from ItemAttr->x74).
    /* 0xD7C */ enum_t destroy_sfx;                 ///< Destruction SFX ID played when item breaks or explodes.
    /* 0xD80 */ s32 xD80;                           ///< Custom SFX 1 (from ItemAttr->x7C).
    /* 0xD84 */ s32 xD84;                           ///< Custom SFX 2 (from ItemAttr->x80).
    /* 0xD88 */ s32 xD88_attackID;                  ///< Attack ID for move stale queue tracking and attribution.
    /* 0xD8C */ u16 xD8C_attack_instance;           ///< Attack instance sequence counter for fresh hit detection.
    /* 0xD8E */ s16 xD8E;                           ///< Secondary instance counter.
    /* 0xD90 */ union Struct2070 xD90;              ///< Collision bitfield union.
    /* 0xD94 */ S32Vec2 xD94;                       ///< Secondary sensor grid coordinates.
    /* 0xD9C */ struct Struct207C xD9C;             ///< Shield collision interaction cache.
    /* 0xDA4 */ u32 xDA4_word;                      ///< General state flags word.
    /* 0xDA8 */ u16 xDA8_short;                     ///< General state short.
    /* 0xDAA */ union Item_xDAA {
        UnkFlagStruct xDAA_flag;                    ///< Debug develop mode flags.
        u8 xDAA_byte;                               ///< Byte access to debug flags.
    } xDAA;                                         ///< Debug pickup range display and develop mode flags.

    // --- Script Scratch Registers (itcmd) ---
    /* 0xDAC */ u32 xDAC_itcmd_var0;                ///< Item command script variable 0 (itcmd scratch register).
    /* 0xDB0 */ u32 xDB0_itcmd_var1;                ///< Item command script variable 1 (itcmd scratch register).
    /* 0xDB4 */ u32 xDB4_itcmd_var2;                ///< Item command script variable 2 (itcmd scratch register).
    /* 0xDB8 */ u32 xDB8_itcmd_var3;                ///< Item command script variable 3 (itcmd scratch register).
    /* 0xDBC */ union Item_xDBC {
        flag32 xDBC_itcmd_var4;                     ///< Flag bits for script variable 4.
        u32 xDBC_itcmd_var4_word;                   ///< Word access for script variable 4.
    } xDBC;                                         ///< Item command script variable 4.
    /* 0xDC0 */ u32 xDC0;                           ///< Timer or counter variable.
    /* 0xDC4 */ u32 xDC4;                           ///< Timer or counter variable.

    // --- State and Interaction Bitfields ---
    /* 0xDC8 */ flag32 xDC8_word;                   ///< Primary 32-bit state flags (grounded, thrown, heavy, etc.).
    /* 0xDCC */ struct Item_xDCC_flag {
        u8 b0 : 1;                                  ///< Flag b0.
        u8 b1 : 1;                                  ///< Flag b1.
        u8 b2 : 1;                                  ///< Flag b2.
        u8 b3 : 1;                                  ///< Flag b3.
        u8 b4567 : 4;                               ///< Flags b4567.
    } xDCC_flag;                                    ///< Bitfield flags controlling pickup, throw, and collisions.
    /* 0xDCD */ CameraBoxFlags xDCD_flag;           ///< Camera tracking box configuration flags.
    /* 0xDCE */ UnkFlagStruct xDCE_flag;            ///< Secondary status bitfield.
    /* 0xDCF */ UnkFlagStruct xDCF_flag;            ///< Physics and visibility bitfield.
    /* 0xDD0 */ UnkFlagStruct xDD0_flag;            ///< Hitbox and collision bitfield.
    /* 0xDD1 */ UnkFlagStruct xDD1_flag;            ///< Interaction bitfield.
    /* 0xDD2 */ UnkFlagStruct xDD2_flag;            ///< Auxiliary status bitfield.
    /* 0xDD3 */ UnkFlagStruct xDD3_flag;            ///< Auxiliary status bitfield.

    // --- Item-Specific Custom State Storage ---
    /* 0xDD4 */ union Item_ItemVars {
        it_266F_ItemVars it_266F;
        it_2E5A_ItemVars it_2E5A;
        itArwingLaser_ItemVars arwinglaser;
        itBombHei_ItemVars bombhei;
        itBox_ItemVars box;
        itCapsule_ItemVars capsule;
        itChicorita_ItemVars chicorita;
        itClimbersBlizzard_ItemVars climbersblizzard;
        itClimbersIce_ItemVars climbersice;
        itClimbersString_ItemVars climbersstring;
        itCLinkMilk_ItemVars clinkmilk;
        itCoin_ItemVars coin;
        itDosei_ItemVars dosei;
        itDrMarioPill_ItemVars drmariopill;
        itEgg_ItemVars egg;
        itEvYoshiEgg_ItemVars evyoshiegg;
        itFFlower_ItemVars fflower;
        itFFlowerFlame_ItemVars fflowerflame;
        itFlipper_ItemVars flipper;
        itFoods_ItemVars foods;
        itFoxBlaster_ItemVars foxblaster;
        itFoxIllusion_ItemVars foxillusion;
        itFoxLaser_ItemVars foxlaser;
        itFreeze_ItemVars freeze;
        itFreezer_ItemVars freezer;
        itFushigibana_ItemVars fushigibana;
        itGamewatch_ItemVars gamewatch;
        itGamewatchchef_ItemVars gamewatchchef;
        itGamewatchrescue_ItemVars gamewatchrescue;
        itGreatFoxLaser_ItemVars greatfoxlaser;
        itGShell_ItemVars gshell, zgshell, zrshell;
        itHassam_ItemVars hassam;
        itHeart_ItemVars heart;
        itHeiho_ItemVars heiho;
        itHinoarashi_ItemVars hinoarashi;
        itHitodeman_ItemVars hitodeman;
        itHouou_ItemVars houou;
        itKabigon_ItemVars kabigon;
        itKinoko_ItemVars kinoko;
        itKirby2F23_ItemVars kirby2f23;
        itKirbyCutterBeam_ItemVars kirbycutterbeam;
        itKirbyHammer_ItemVars kirbyhammer;
        itkireihana_ItemVars kireihana;
        itKlap_ItemVars klap;
        itKoopaFlame_ItemVars koopaflame;
        itKusudama_ItemVars kusudama;
        itKyasarin_ItemVars kyasarin;
        itKyasarinEgg_ItemVars kyasarinEgg;
        itLeadead_ItemVars leadead;
        itLGun_ItemVars lgun;
        itLGunBeam_ItemVars lgunbeam;
        itLGunRay_ItemVars lgunray;
        itRay_ItemVars ray;
        itLikelike_ItemVars likelike;
        itLinkArrow_ItemVars linkarrow;
        itLinkBomb_ItemVars linkbomb;
        itLinkBoomerang_ItemVars linkboomerang;
        itLinkBow_ItemVars linkbow;
        itLinkHookshot_ItemVars linkhookshot;
        itLipstickSpore_ItemVars lipstickspore;
        itLizardon_ItemVars lizardon;
        itLucky_ItemVars lucky;
        itLugia_ItemVars lugia;
        itMaril_ItemVars maril;
        itMasterHandBullet_ItemVars masterhandbullet;
        itMasterHandLaser_ItemVars masterhandlaser;
        itMatadogas_ItemVars matadogas;
        itMato_ItemVars mato;
        itMBall_ItemVars mball;
        itMDisable_ItemVars mdisable;
        itMewtwoShadowball_ItemVars mewtwoshadowball;
        itMsBomb_ItemVars msbomb;
        itNessbat_ItemVars nessbat;
        itNesspkthundertrail_ItemVars nesspkthundertrail;
        itNessYoyo_ItemVars nessyoyo;
        itNokoNoko_ItemVars nokonoko;
        itOctarock_ItemVars octarock;
        itOldkuri_ItemVars oldkuri;
        itOldottosea_ItemVars oldottosea;
        itPatapata_ItemVars patapata;
        itPeachTurnip_ItemVars peachturnip;
        itPikachuthunder_ItemVars pikachuthunder;
        itPikachutJoltAir_ItemVars pikachujoltair;
        itPikachutJoltGround_ItemVars pikachujoltground;
        itPKFlush_ItemVars pkflush;
        itPKFlushExplode_ItemVars pkflushexplode;
        itPKThunder_ItemVars pkthunder;
        itPokemon_ItemVars pokemon;
        itPokemonSpawn_ItemVars pokemon_spawn;
        itRShell_ItemVars rshell;
        itSamusBomb_ItemVars samusbomb;
        itSamusChargeshot_ItemVars samuschargeshot;
        itSamusGrapple_ItemVars samusgrapple;
        itSamusMissile_ItemVars samusmissile;
        itScopeBeam_ItemVars scopebeam;
        itSeakChain_ItemVars seakchain;
        itSeakNeedleHeld_ItemVars seakneedleheld;
        itSeakNeedleThrown_ItemVars seakneedlethrown;
        itSonans_ItemVars sonans;
        itStar_ItemVars star;
        itStarRodStar_ItemVars starrodstar;
        itSword_ItemVars sword;
        itTaru_ItemVars taru;
        itTarucann_ItemVars tarucann;
        itThunder_ItemVars thunder;
        itTincle_ItemVars tincle;
        itTomato_ItemVars tomato;
        itTools_ItemVars tools;
        itTosakinto_ItemVars tosakinto;
        itUnk2_ItemVars unk2;
        itUnk4_ItemVars unk4;
        itUnknown_ItemVars unknown;
        itWhispyApple_ItemVars whispyapple;
        itWhiteBea_ItemVars whitebea;
        itWstar_ItemVars wstar;
        itYaku_ItemVars yaku;
        itYoshiEggLay_ItemVars yoshiegglay;
        itZako_ItemVars zako;
        itZeldaDinFire_ItemVars zeldadinfire;
        itZeldaDinFireExplode_ItemVars zeldadinfireexplode;
        u8 _[0xFCC - 0xDD4];
    } xDD4_itemVar;
};
ASSERT_SIZE(struct Item, 0xFCC);

/// Render callback wrapper for item GX rendering.
struct sdata_ItemGXLink {
    GObj_RenderFunc x0_renderFunc; ///< Function callback invoked during item GX rendering pass.
};

/// Global article table indexed by ItemKind.
struct r13_ItemTable {
    s32 filler;
    Article* x0_article[0x9F]; ///< Array of article archive pointers for all item kinds.
};

/// Sudden Death Bob-omb raining spawner state.
struct BobOmbRain {
    HSD_GObj* x0;           ///< Spawner GObj.
    HSD_JObj* x4;           ///< Spawner root JObj.
    Vec3 x8_vec;            ///< Target spawn position.
    enum_t x14;             ///< Spawn state.
    s32 x18;                ///< Timer counter.
    UnkFlagStruct x1C;      ///< Spawner control flags.
};

/// Parameters for spawning a new item instance (passed to it_80268B18).
struct SpawnItem {
    /*  +0 */ HSD_GObj* x0_parent_gobj;     ///< Entity creating this item (e.g. fighter throwing or dropping).
    /*  +4 */ HSD_GObj* x4_parent_gobj2;    ///< Secondary parent entity reference.
    /*  +8 */ ItemKind kind;                ///< Kind of item to spawn.

    /// Defines the behavior of the item, such as thrown and pickup.
    /*  +C */ Item_HoldKinds hold_kind;

    /* +10 */ s32 x10;                      ///< Spawn parameter flags (copied to Item->x18).
    /* +14 */ Vec3 pos;                     ///< Initial 3D spawn position.
    /* +20 */ Vec3 prev_pos;                ///< Previous position for velocity derivation.
    /* +2C */ Vec3 vel;                     ///< Initial 3D launch velocity vector.
    /* +38 */ f32 facing_dir;               ///< Initial horizontal facing direction (+1.0f or -1.0f).
    /* +3C */ s16 x3C_damage;               ///< Base damage dealt on impact.
    /* +3E */ s16 x3E;                      ///< Secondary damage parameter.
    /* +40 */ s32 x40;                      ///< Item ID to ignore for collision detection.
    /* +44 */ UnkFlagStruct x44_flag;       ///< Spawn flags 1.
    /* +45 */ UnkFlagStruct x45_flag;       ///< Spawn flags 2.
    /* +46 */ UnkFlagStruct x46_flag;       ///< Spawn flags 3.
    /* +47 */ UnkFlagStruct x47_flag;       ///< Spawn flags 4.
    /* +48 */ GroundOrAir x48_ground_or_air;///< Initial ground/air state (GA_Ground or GA_Air).
};

/// Global common item attributes loaded from ItCo.dat.
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
    u32 x30_lifetime;   ///< Default item ambient lifetime in frames.
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
    f32 unk_degrees;
    u8 filler_1a[0xE8 - 0xE4];
    f32 xE8;
    u8 filler_1a_2[0xF0 - 0xEC];
    f32 xF0;
    f32 xF4;
    f32 xF8;
    s32 xFC[(0x124 - 0xFC) / 4];
    s32 x124;    // max value for a random integer generation in it_8026F6BC
    s32 x128[4]; // monster item counts for it_8026CF04
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

/// Global item subsystem data pointers stored in r13.
struct Item_r13_Data {
    ItemCommonData* item_common;    ///< Pointer to loaded ItCo.dat data.
    void** common_items;            ///< Pointer to common item archive table.
    void** adventure_items;         ///< Pointer to adventure mode enemy item table.
    void** pokeball_items;          ///< Pointer to Poké Ball Pokémon item table.
    s32 x10;
    s32 x14;
};

/// Per-fighter ECB and position record for item collision detection.
/// Populated by ftCo_80098634; read by it_80271B60 to detect item/fighter overlap.
struct Item_FtTrack {
    itECB ecb_offset_arr[11];   ///< ECB offsets for up to 11 active fighters/ice climbers.
    s32 xB0;
    s32 xB4;
    s32 xB8;
    s32 xBC;
    Vec3 ft_pos_arr[11];        ///< World positions for up to 11 active fighters.
    u32 x144;
    u32 x148;
    u32 x14C;
    size_t count;               ///< Number of active tracked fighters.
    UnkFlagStruct x154;         ///< Tracking status flags.
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
    s32 x2C;
    s32 x30;
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
    s32 x60;
    s32 x64;
};

/// Weighted random pick table for item selection. Holds N parallel entries:
///
///   x4[i] is the ItemKind of entry i.
///   xC[i] is the cumulative weight threshold of entry i (sum of weights of
///         entries 0..i-1; xC[0] == 0).
///   x8    is the total weight (== xC[N], implicit; xC[N] is not stored).
///
/// To pick an item, draw r in [0, x8) and binary-search xC for the largest i
/// with xC[i] <= r; entry i is the chosen item.
///
/// Allocated by HSD_MemAlloc with size N*4.
/// Built by it_8026CA4C / it_8026CB9C / it_8026CD50 / it_8026CF04; queried by it_8026C75C.
struct ItemPickTable {
    u8 size; ///< Entry count N (incremented/decremented as items are added/picked).
    u8* x4;  ///< ItemKind values, length N.
    u16 x8;  ///< Total cumulative weight, used as upper bound of HSD_Randi.
    u16* xC; ///< Cumulative weight thresholds, length N.
};

/// State for the periodic ambient item-spawn system.
/// fn_8026C88C runs each frame: decrements x0; when it reaches 0, picks an item
/// from x4 and spawns it, then resets x0 to a fresh random duration scaled by stage parameters.
struct RandomItemSpawner {
    s32 x0;           ///< Spawn countdown in frames until next spawn attempt.
    ItemPickTable x4; ///< Weighted pick table built from x18 + stage weights.
    s32 x14;          ///< Unused.
    u64 x18;          ///< Stage's allowed-items bitmask, from gm_8016AEA4().
};

struct HSD_ObjAllocUnk5 {
    u8 x0;
    u32 x4;
    u16 x8;
    u16 xA;
    u16 xC;
};

/// Each entry records a single damage hit; x0 selects which member of x4 is valid (1: fighter, 2: item).
typedef struct DamageLogEntry {
    s32 x0;             ///< Entity type discriminator (1 = fighter, 2 = item).
    void* x4;           ///< Pointer to victim entity (Fighter* or Item*).
    HitCapsule* x8;     ///< Pointer to incoming HitCapsule that dealt damage.
    HurtCapsule* xC;    ///< Pointer to target HurtCapsule that received damage.
} DamageLogEntry;

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

#endif
