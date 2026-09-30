/**
 * @file forward.h
 * @brief Forward declarations and core enumerations for the Fighter (ft) module.
 * @details Defines character identifiers (FighterKind, CharacterKind), action state
 * transition bitmasks (MotionFlags), skeletal bone hierarchies (Fighter_Part), attack move
 * identifiers (FtMoveId), and forward declarations of core fighter structures used throughout Melee.
 * Module prefix: ft (Fighter)
 */

#ifndef MELEE_FT_FORWARD_H
#define MELEE_FT_FORWARD_H

#include <Runtime/platform.h>

#include <melee/gr/forward.h>
#include <melee/lb/forward.h>
#include <sysdolphin/baselib/forward.h>

#include <dolphin/mtx.h>
#include <dolphin/types.h>

/// HSD_GObj classifier value designating an entity as a Fighter (Class 4).
#define HSD_GOBJ_CLASS_FIGHTER 4

/// HSD_GObj priority link index for the fighter linked list in HSD_GObjPLinkHead (Link 8).
#define HSD_GOBJ_PLINK_FIGHTER 8

/// Size in bytes of the per-character custom variables union (`fp->mv`) inside Fighter struct (0xF8 = 248 bytes).
#define FIGHTERVARS_SIZE 0xF8

typedef enum_t FtMotionId;
typedef struct CostumeTObjList CostumeTObjList;
typedef struct DObjList DObjList;
typedef struct Fighter Fighter;
typedef struct Fighter_804D653C_t Fighter_804D653C_t;
typedef struct Fighter_CostumeStrings Fighter_CostumeStrings;
typedef struct Fighter_DemoStrings Fighter_DemoStrings;
typedef struct Fighter_x1670_t Fighter_x1670_t;
typedef struct FighterBone FighterBone;
typedef struct FighterPartsTable FighterPartsTable;
typedef struct ft_800898B4_t ft_800898B4_t;
typedef struct ftCo_803C6594_t ftCo_803C6594_t;
typedef struct ftCo_DatAttrs_xBC_t ftCo_DatAttrs_xBC_t;
typedef struct ftCommonData ftCommonData;
typedef struct ftData ftData;
typedef struct ftData_UnkCountStruct ftData_UnkCountStruct;
typedef struct ftData_x58_t ftData_x58_t;
typedef struct ftData_x8 ftData_x8;
typedef struct ftData_x8_x8 ftData_x8_x8;
typedef struct ftDynamics ftDynamics;
typedef struct ftLk_SpecialN_Vec3Group ftLk_SpecialN_Vec3Group;
typedef struct ftMaterial_UnkTevStruct ftMaterial_UnkTevStruct;
typedef struct FtPartsDesc FtPartsDesc;
typedef struct FtPartsVis FtPartsVis;
typedef struct FtPartsVisLookup FtPartsVisLookup;
typedef struct FtSFX FtSFX;
typedef struct gmScriptEventDefault gmScriptEventDefault;
typedef struct IKState IKState;
typedef struct KirbyHatStruct KirbyHatStruct;
typedef struct MotionState MotionState;
typedef struct TempS TempS;
typedef struct UnkCostumeStruct UnkCostumeStruct;
typedef struct UnkFloat6_Camera UnkFloat6_Camera;
typedef u32 MotionFlags;

#ifdef M2C
typedef struct Fighter_GObj Fighter_GObj;
/// Specialized HSD_GObj representation for fighters used during decompilation analysis.
struct Fighter_GObj {
    /*  +0 */ u16 classifier;
    /*  +2 */ u8 p_link;
    /*  +3 */ u8 gx_link;
    /*  +4 */ u8 p_priority;
    /*  +5 */ u8 render_priority;
    /*  +6 */ u8 obj_kind;
    /*  +7 */ u8 user_data_kind;
    /*  +8 */ Fighter_GObj* next;
    /*  +C */ Fighter_GObj* prev;
    /* +10 */ Fighter_GObj* next_gx;
    /* +14 */ Fighter_GObj* prev_gx;
    /* +18 */ HSD_GObjProc* proc;
    /* +1C */ void (*rendered)(Fighter_GObj* gobj, s32 code);
    /* +20 */ u64 gxlink_prios;
    /* +28 */ HSD_JObj* hsd_obj;
    /* +2C */ Fighter* user_data;
    /* +30 */ void (*user_data_remove_func)(Fighter* data);
    /* +34 */ void* x34_unk;
};
#else
#include <sysdolphin/baselib/gobj.h>
typedef struct HSD_GObj Fighter_GObj;
#endif

/// Callback to resolve the motion file string for a given motion ID.
typedef char* (*Fighter_MotionFileStringGetter)(enum_t arg0);

/// Callback invoked on fighter item interaction events (e.g. pickup, drop).
typedef void (*Fighter_ItemEvent)(HSD_GObj* gobj, bool arg1);

/// Callback for fighter model part alteration events.
typedef void (*Fighter_ModelEvent)(Fighter* fp, int arg1, bool arg2);

/// Callback for bone matrix transformation updates.
typedef void (*Fighter_UnkMtxEvent)(HSD_GObj* gobj, int arg1, Mtx vmtx);

/// Callback for low-level fighter pointer manipulation events.
typedef void (*Fighter_UnkPtrEvent)(int arg0, int* arg1, int* arg2);

/// General fighter event callback receiving a fighter state pointer.
typedef void (*FighterEvent)(Fighter* fp);

/// Subaction command script interpreter event callback.
typedef void (*FtCmd)(Fighter_GObj*, CommandInfo*);

/// Extended subaction command script event callback.
typedef void (*FtCmd2)(Fighter_GObj*, CommandInfo*, int);

/// Stage collision device interaction callback.
typedef bool (*ftDevice_Callback0)(Ground_GObj*, Fighter_GObj*, Vec3*);

/**
 * @brief Internal fighter slot IDs used by the engine (`fp->kind`).
 * @details Identifies each playable fighter entity, sub-entity (Nana), boss, and special entity.
 * Unlike CharacterKind, Popo and Nana have distinct fighter kinds here.
 */
typedef enum FighterKind {
    /* 00 */ Ft_Kind_Mario,     ///< Mario
    /* 01 */ Ft_Kind_Fox,       ///< Fox McCloud
    /* 02 */ Ft_Kind_Captain,   ///< Captain Falcon
    /* 03 */ Ft_Kind_Donkey,    ///< Donkey Kong
    /* 04 */ Ft_Kind_Kirby,     ///< Kirby
    /* 05 */ Ft_Kind_Koopa,     ///< Bowser (Koopa)
    /* 06 */ Ft_Kind_Link,      ///< Link
    /* 07 */ Ft_Kind_Seak,      ///< Sheik
    /* 08 */ Ft_Kind_Ness,      ///< Ness
    /* 09 */ Ft_Kind_Peach,     ///< Princess Peach
    /* 0A */ Ft_Kind_Popo,      ///< Popo (Ice Climbers leader / solo)
    /* 0B */ Ft_Kind_Nana,      ///< Nana (Ice Climbers partner)
    /* 0C */ Ft_Kind_Pikachu,   ///< Pikachu
    /* 0D */ Ft_Kind_Samus,     ///< Samus Aran
    /* 0E */ Ft_Kind_Yoshi,     ///< Yoshi
    /* 0F */ Ft_Kind_Purin,     ///< Jigglypuff (Purin)
    /* 10 */ Ft_Kind_Mewtwo,    ///< Mewtwo
    /* 11 */ Ft_Kind_Luigi,     ///< Luigi
    /* 12 */ Ft_Kind_Mars,      ///< Marth (Mars)
    /* 13 */ Ft_Kind_Zelda,     ///< Princess Zelda
    /* 14 */ Ft_Kind_CLink,     ///< Young Link (Child Link)
    /* 15 */ Ft_Kind_DrMario,   ///< Dr. Mario
    /* 16 */ Ft_Kind_Falco,     ///< Falco Lombardi
    /* 17 */ Ft_Kind_Pichu,     ///< Pichu
    /* 18 */ Ft_Kind_GameWatch, ///< Mr. Game & Watch
    /* 19 */ Ft_Kind_Ganon,     ///< Ganondorf
    /* 1A */ Ft_Kind_Emblem,    ///< Roy (Fire Emblem)
    /* 1B */ Ft_Kind_MasterH,   ///< Master Hand (Boss)
    /* 1C */ Ft_Kind_CrezyH,    ///< Crazy Hand (Boss)
    /* 1D */ Ft_Kind_Boy,       ///< Fighting Wire Frame Male (Boy)
    /* 1E */ Ft_Kind_Girl,      ///< Fighting Wire Frame Female (Girl)
    /* 1F */ Ft_Kind_GKoops,    ///< Giga Bowser (Giga Koopa)
    /* 20 */ Ft_Kind_Sandbag,   ///< Sandbag
    /* 21 */ Ft_Kind_None,      ///< Invalid / None sentinel
    /* 21 */ Ft_Kind_Max = Ft_Kind_None
} FighterKind;

/**
 * @brief Character identity IDs used by menus, UI, CSS, and player profile systems.
 * @details Differs from FighterKind: Popo & Nana share a single character ID (PopoNana),
 * and the ordering corresponds to CSS / tournament standard ordering.
 */
typedef enum CharacterKind {
    /* 00 */ CKind_Captain,   ///< Captain Falcon (Captain)
    /* 01 */ CKind_Donkey,    ///< Donkey Kong (Donkey)
    /* 02 */ CKind_Fox,       ///< Fox McCloud
    /* 03 */ CKind_GameWatch, ///< Mr. Game & Watch (GameWatch)
    /* 04 */ CKind_Kirby,     ///< Kirby
    /* 05 */ CKind_Koopa,     ///< Bowser (Koopa)
    /* 06 */ CKind_Link,      ///< Link
    /* 07 */ CKind_Luigi,     ///< Luigi
    /* 08 */ CKind_Mario,     ///< Mario
    /* 09 */ CKind_Mars,      ///< Marth (Mars)
    /* 0A */ CKind_Mewtwo,    ///< Mewtwo
    /* 0B */ CKind_Ness,      ///< Ness
    /* 0C */ CKind_Peach,     ///< Princess Peach
    /* 0D */ CKind_Pikachu,   ///< Pikachu
    /* 0E */ CKind_PopoNana,  ///< Ice Climbers (Popo & Nana)
    /* 0F */ CKind_Purin,     ///< Jigglypuff (Purin)
    /* 10 */ CKind_Samus,     ///< Samus Aran
    /* 11 */ CKind_Yoshi,     ///< Yoshi
    /* 12 */ CKind_Zelda,     ///< Princess Zelda (transforms into Sheik)
    /* 13 */ CKind_Seak,      ///< Sheik (transforms into Zelda)
    /* 14 */ CKind_Falco,     ///< Falco Lombardi
    /* 15 */ CKind_CLink,     ///< Young Link (CLink)
    /* 16 */ CKind_DrMario,   ///< Dr. Mario
    /* 17 */ CKind_Emblem,    ///< Roy (Fire Emblem)
    /* 18 */ CKind_Pichu,     ///< Pichu
    /* 19 */ CKind_Ganon,     ///< Ganondorf (Ganon)

    /* 1A */ CKind_Playable_Count, ///< Total count of playable characters (26)

    /* 1A */ CKind_MasterH = CKind_Playable_Count, ///< Master Hand (MasterH)
    /* 1B */ CKind_Boy,                            ///< Male Wireframe (Boy)
    /* 1C */ CKind_Girl,                           ///< Female Wireframe (Girl)
    /* 1D */ CKind_GKoops,                         ///< Giga Bowser (GKoops)
    /* 1E */ CKind_CrezyH,                         ///< Crazy Hand (CrezyH)
    /* 1F */ ChKind_Sandbag,                       ///< Sandbag
    /* 20 */ ChKind_Popo,                          ///< Solo Popo
    /* 21 */ ChKind_None,                          ///< None
    /* 21 */ ChKind_Max = ChKind_None
} CharacterKind;

/**
 * @name MotionFlags
 * @brief Bitmask flags passed to Fighter_ChangeMotionState controlling state preservation.
 * @details By default (Ft_MF_None = 0), changing motion state clears velocities, cancels hitboxes,
 * resets hurtboxes, stops sounds, flushes graphics, resets models, and clears animation data.
 * Setting these flags selectively preserves specific systems across the transition.
 * @{
 */

/// Default transition: resets all transient state, hitboxes, SFX, and effects.
static MotionFlags const Ft_MF_None = 0;

/// Preserve fast fall status (`fp->fall_fast`). If not set, fast fall is cancelled.
static MotionFlags const Ft_MF_KeepFastFall = 1 << 0;

/// Preserve graphical and particle effect instances (`fp->x2219_b0`) without flushing.
static MotionFlags const Ft_MF_KeepGfx = 1 << 1;

/// Preserve full body collision / hurtbox status (invulnerable/intangible/armor color animations).
static MotionFlags const Ft_MF_KeepColAnimHitStatus = 1 << 2;

/// Keep active hitboxes across state transition (prevents hitbox reset; used in multi-state moves).
static MotionFlags const Ft_MF_SkipHit = 1 << 3;

/// Skip resetting model parts and bones (`ftParts_80074A8C`).
static MotionFlags const Ft_MF_SkipModel = 1 << 4;

/// Skip applying root bone animation translation velocity (`transNOffset`) to grounded fighter velocity.
static MotionFlags const Ft_MF_SkipAnimVel = 1 << 5;

/// Skip resetting the KO attribution / attacker credit countdown timer (`fp->dmg.x18C8`).
static MotionFlags const Ft_MF_Unk06 = 1 << 6;

/// Skip resetting material textures / animations (e.g. hurt textures, facial expressions).
static MotionFlags const Ft_MF_SkipMatAnim = 1 << 7;

/// Preserve thrower GObj owner pointer (`fp->x1064_thrownHitbox.x134.owner`) instead of setting to NULL.
static MotionFlags const Ft_MF_SkipThrowException = 1 << 8;

/// Preserve currently playing fighter sound effects; prevents stopping active SFX.
static MotionFlags const Ft_MF_KeepSfx = 1 << 9;

/// Skip resetting Peach's parasol state (`ftCommon_8007E83C`); keeps parasol deployed.
static MotionFlags const Ft_MF_SkipParasol = 1 << 10;

/// Skip stopping controller rumble / vibration effects.
static MotionFlags const Ft_MF_SkipRumble = 1 << 11;

/// Skip clearing active color animation (`ftCo_800C0134`).
static MotionFlags const Ft_MF_SkipColAnim = 1 << 12;

/// Keep attached accessory JObj (e.g. revival/respawn platform) without removing.
static MotionFlags const Ft_MF_KeepAccessory = 1 << 13;

/// Fast-forward and execute all subaction script commands up to current animation frame (`ftAction_8007349C`).
static MotionFlags const Ft_MF_UpdateCmd = 1 << 14;

/// Skip nametag visibility update (`fp->x209A`).
static MotionFlags const Ft_MF_SkipNametagVis = 1 << 15;

/// Preserve bone-specific hurtbox / collision hit status (`fp->x2221_b1`).
static MotionFlags const Ft_MF_KeepColAnimPartHitStatus = 1 << 16;

/// Preserve sword trail visual effect (`fp->x2100`) across transition.
static MotionFlags const Ft_MF_KeepSwordTrail = 1 << 17;

/// Preserve held item visibility state (used during Ness Up/Down Smash to keep yo-yo visible/hidden).
static MotionFlags const Ft_MF_SkipItemVis = 1 << 18;

/// Preserve sleep immunity / special move action flag (`fp->x2222_b2`).
static MotionFlags const Ft_MF_Unk19 = 1 << 19;

/// Initialize bone rotation cache (`fp->x100 = 0.0f`) for physics translation tracking (`ftAnim_80070FD0`).
static MotionFlags const Ft_MF_UnkUpdatePhys = 1 << 20;

/// Freeze animation playback; sets frame speed multiplier to 0 and marks frozen state (`fp->x2223_b0`).
static MotionFlags const Ft_MF_FreezeState = 1 << 21;

/// Skip resetting model part visibility flags (`fp->x221E_b4`).
static MotionFlags const Ft_MF_SkipModelPartVis = 1 << 22;

/// Preserve special item collision ignore flag (`fp->x2223_b4`), preventing item bounces (e.g. during Fire Fox).
static MotionFlags const Ft_MF_SkipMetalB = 1 << 23;

/// Preserve Inverse Kinematics (IK) leg/foot slope alignment flags (`fp->x221C_u16_y`).
static MotionFlags const Ft_MF_Unk24 = 1 << 24;

/// Skip incrementing attack move usage counter (`pl_80037C60`), preventing multi-hit moves from staling.
static MotionFlags const Ft_MF_SkipAttackCount = 1 << 25;

/// Skip resetting model flags (`fp->x2225_b2`).
static MotionFlags const Ft_MF_SkipModelFlags = 1 << 26;

/// Preserve thrown fighter collision hitbox flag (`fp->x2227_b2`), allowing body collisions while thrown.
static MotionFlags const Ft_MF_Unk27 = 1 << 27;

/// Preserve hitstun status flag (`fp->x221C_b6`) and timer (`fp->x2098`).
static MotionFlags const Ft_MF_SkipHitStun = 1 << 28;

/// Skip loading new animation data; preserves currently playing fighter animation.
static MotionFlags const Ft_MF_SkipAnim = 1 << 29;

/// Unused / reserved motion flag bit 30.
static MotionFlags const Ft_MF_Unk30 = 1 << 30;

/// Unused / reserved motion flag bit 31.
static MotionFlags const Ft_MF_Unk31 = 1 << 31;

/** @} */

/**
 * @name Ledge Grab Facing Direction Flags
 * @brief Determines allowed facing directions when catching a cliff / ledge.
 * @{
 */
#define CLIFFCATCH_BOTH 0   ///< Can catch ledge facing either direction
#define CLIFFCATCH_LEFT -1  ///< Can only catch ledge while facing left
#define CLIFFCATCH_RIGHT 1  ///< Can only catch ledge while facing right
/** @} */

/**
 * @brief Standard skeletal bone hierarchy joint/part indices for fighters.
 * @details Matches the standard Melee skeletal rig conventions:
 * - 'N': Transform node / null object
 * - 'J': Joint / bone
 * - 'JA': Joint auxiliary / angle adjustment
 * - 'Na' / 'Nb': Finger / extremity segment nodes
 */
typedef enum Fighter_Part {
    FtPart_TopN,        ///< Root transform node in world space (0)
    FtPart_TransN,      ///< Translation node; tracks animation root motion for physics (1)
    FtPart_XRotN,       ///< Pitch rotation node (2)
    FtPart_YRotN,       ///< Facing direction / yaw rotation node (3)
    FtPart_HipN,        ///< Pelvis / hip node; base of spine and legs (4)
    FtPart_WaistN,      ///< Waist / lower torso node (5)
    FtPart_LLegJA,      ///< Left hip / upper leg auxiliary joint (6)
    FtPart_LLegJ,       ///< Left thigh joint (7)
    FtPart_LKneeJ,      ///< Left knee joint (8)
    FtPart_LFootJA,     ///< Left ankle auxiliary joint (9)
    FtPart_LFootJ,      ///< Left foot / toe joint (10)
    FtPart_RLegJA,      ///< Right hip / upper leg auxiliary joint (11)
    FtPart_RLegJ,       ///< Right thigh joint (12)
    FtPart_RKneeJ,      ///< Right knee joint (13)
    FtPart_RFootJA,     ///< Right ankle auxiliary joint (14)
    FtPart_RFootJ,      ///< Right foot / toe joint (15)
    FtPart_BustN,       ///< Chest / bust / upper torso node (16)
    FtPart_LShoulderN,  ///< Left clavicle / shoulder base node (17)
    FtPart_LShoulderJA, ///< Left shoulder auxiliary joint (18)
    FtPart_LShoulderJ,  ///< Left shoulder joint (19)
    FtPart_LArmJ,       ///< Left elbow / forearm joint (20)
    FtPart_LHandN,      ///< Left wrist / hand node (21)
    FtPart_L1stNa,      ///< Left index finger proximal joint (22)
    FtPart_L1stNb,      ///< Left index finger distal joint (23)
    FtPart_L2ndNa,      ///< Left middle finger proximal joint (24)
    FtPart_L2ndNb,      ///< Left middle finger distal joint (25)
    FtPart_L3rdNa,      ///< Left ring finger proximal joint (26)
    FtPart_L3rdNb,      ///< Left ring finger distal joint (27)
    FtPart_L4thNa,      ///< Left pinky finger proximal joint (28)
    FtPart_L4thNb,      ///< Left pinky finger distal joint (29)
    FtPart_LThumbNa,    ///< Left thumb proximal joint (30)
    FtPart_LThumbNb,    ///< Left thumb distal joint (31)
    FtPart_LHandNb,     ///< Left hand auxiliary node / item hold attachment (32)
    FtPart_NeckN,       ///< Neck base node (33)
    FtPart_HeadN,       ///< Head node (34)
    FtPart_RShoulderN,  ///< Right clavicle / shoulder base node (35)
    FtPart_RShoulderJA, ///< Right shoulder auxiliary joint (36)
    FtPart_RShoulderJ,  ///< Right shoulder joint (37)
    FtPart_RArmJ,       ///< Right elbow / forearm joint (38)
    FtPart_RHandN,      ///< Right wrist / hand node (39)
    FtPart_R1stNa,      ///< Right index finger proximal joint (40)
    FtPart_R1stNb,      ///< Right index finger distal joint (41)
    FtPart_R2ndNa,      ///< Right middle finger proximal joint (42)
    FtPart_R2ndNb,      ///< Right middle finger distal joint (43)
    FtPart_R3rdNa,      ///< Right ring finger proximal joint (44)
    FtPart_R3rdNb,      ///< Right ring finger distal joint (45)
    FtPart_R4thNa,      ///< Right pinky finger proximal joint (46)
    FtPart_R4thNb,      ///< Right pinky finger distal joint (47)
    FtPart_RThumbNa,    ///< Right thumb proximal joint (48)
    FtPart_RThumbNb,    ///< Right thumb distal joint (49)
    FtPart_RHandNb,     ///< Right hand auxiliary node / primary item hold attachment (50)
    FtPart_ThrowN,      ///< Throw attach node; position where grabbed victim is held (51)
    FtPart_TransN2,     ///< Secondary translation node (52)
    FtPart_56 = 56,     ///< Extended bone offset 56 (e.g. tail, cape)
    FtPart_109 = 109,   ///< Maximum standard skeleton bone count
} Fighter_Part;

/**
 * @brief Walking phase / speed gradation based on analog stick displacement.
 */
typedef enum FtWalkType {
    FtWalkType_Slow,   ///< Slow walk (slight stick tilt, minimal forward speed)
    FtWalkType_Middle, ///< Medium walk (moderate stick tilt)
    FtWalkType_Fast,   ///< Fast walk (full stick tilt up to dash threshold)
} FtWalkType;

/**
 * @brief Attack move IDs used for damage calculation, move staling queue, and statistics.
 * @details Categorizes every offensive action into standard fighting game move archetypes:
 * normal tilts, smashes, aerials, grabs, throws, getup attacks, item swings, and special moves.
 */
typedef enum FtMoveId {
    FtMoveId_None,             ///< No attack / non-damaging state
    FtMoveId_Default,          ///< Default / generic attack
    FtMoveId_Attack11,         ///< Jab 1 (first hit of neutral attack combo)
    FtMoveId_Attack12,         ///< Jab 2 (second hit of neutral attack combo)
    FtMoveId_Attack13,         ///< Jab 3 (third hit of neutral attack combo)
    FtMoveId_Attack100,        ///< Rapid Jab (multi-jab / infinite jab finisher)
    FtMoveId_AttackDash,       ///< Dash Attack
    FtMoveId_AttackS3,         ///< Forward Tilt (Side Tilt / Strong Side Attack)
    FtMoveId_AttackHi3,        ///< Up Tilt (High Tilt / Strong Up Attack)
    FtMoveId_AttackLw3,        ///< Down Tilt (Low Tilt / Strong Down Attack)
    FtMoveId_AttackS4,         ///< Forward Smash (Side Smash)
    FtMoveId_AttackHi4,        ///< Up Smash
    FtMoveId_AttackLw4,        ///< Down Smash
    FtMoveId_AttackAirN,       ///< Neutral Aerial (Nair)
    FtMoveId_AttackAirF,       ///< Forward Aerial (Fair)
    FtMoveId_AttackAirB,       ///< Back Aerial (Bair)
    FtMoveId_AttackAirHi,      ///< Up Aerial (Uair)
    FtMoveId_AttackAirLw,      ///< Down Aerial (Dair)
    FtMoveId_SpecialN,         ///< Neutral Special (Neutral B)
    FtMoveId_SpecialS,         ///< Side Special (Side B / Forward B)
    FtMoveId_SpecialHi,        ///< Up Special (Up B / Recovery)
    FtMoveId_SpecialLw,        ///< Down Special (Down B)
    FtMoveId_KbSpecialNMr,     ///< Kirby copied Neutral Special: Mario (Fireball)
    FtMoveId_KbSpecialNFx,     ///< Kirby copied Neutral Special: Fox (Blaster)
    FtMoveId_KbSpecialNCa,     ///< Kirby copied Neutral Special: Captain Falcon (Falcon Punch)
    FtMoveId_KbSpecialNDk,     ///< Kirby copied Neutral Special: Donkey Kong (Giant Punch)
    FtMoveId_KbSpecialNKp,     ///< Kirby copied Neutral Special: Bowser (Fire Breath)
    FtMoveId_KbSpecialNLk,     ///< Kirby copied Neutral Special: Link (Bow)
    FtMoveId_KbSpecialNSk,     ///< Kirby copied Neutral Special: Sheik (Needle Storm)
    FtMoveId_KbSpecialNNs,     ///< Kirby copied Neutral Special: Ness (PK Flash)
    FtMoveId_KbSpecialNPe,     ///< Kirby copied Neutral Special: Peach (Toad)
    FtMoveId_KbSpecialNPp,     ///< Kirby copied Neutral Special: Popo / Ice Climbers (Ice Shot)
    FtMoveId_KbSpecialNPk,     ///< Kirby copied Neutral Special: Pikachu (Thunder Jolt)
    FtMoveId_KbSpecialNSs,     ///< Kirby copied Neutral Special: Samus (Charge Shot)
    FtMoveId_KbSpecialNYs,     ///< Kirby copied Neutral Special: Yoshi (Egg Lay)
    FtMoveId_KbSpecialNPr,     ///< Kirby copied Neutral Special: Jigglypuff (Rollout)
    FtMoveId_KbSpecialNMt,     ///< Kirby copied Neutral Special: Mewtwo (Shadow Ball)
    FtMoveId_KbSpecialNLg,     ///< Kirby copied Neutral Special: Luigi (Fireball)
    FtMoveId_KbSpecialNMs,     ///< Kirby copied Neutral Special: Marth (Shield Breaker)
    FtMoveId_KbSpecialNZd,     ///< Kirby copied Neutral Special: Zelda (Nayru's Love)
    FtMoveId_KbSpecialNCl,     ///< Kirby copied Neutral Special: Young Link (Fire Bow)
    FtMoveId_KbSpecialNDr,     ///< Kirby copied Neutral Special: Dr. Mario (Megavitamin)
    FtMoveId_KbSpecialNFc,     ///< Kirby copied Neutral Special: Falco (Blaster)
    FtMoveId_KbSpecialNPc,     ///< Kirby copied Neutral Special: Pichu (Thunder Jolt)
    FtMoveId_KbSpecialNGw,     ///< Kirby copied Neutral Special: Mr. Game & Watch (Chef)
    FtMoveId_KbSpecialNGn,     ///< Kirby copied Neutral Special: Ganondorf (Warlock Punch)
    FtMoveId_KbSpecialNFe,     ///< Kirby copied Neutral Special: Roy (Flare Blade)
    FtMoveId_KbSpecialNGk,     ///< Kirby copied Neutral Special: Giga Bowser (Giga Fire Breath)
    FtMoveId_Unk48,            ///< Unused move ID 48
    FtMoveId_Unk49,            ///< Unused move ID 49
    FtMoveId_DownAttackU,      ///< Floor Attack (face up / getup attack from back)
    FtMoveId_DownAttackD,      ///< Floor Attack (face down / getup attack from stomach)
    FtMoveId_CatchAttack,      ///< Pummel (grab attack while holding opponent)
    FtMoveId_ThrowF,           ///< Forward Throw
    FtMoveId_ThrowB,           ///< Back Throw
    FtMoveId_ThrowHi,          ///< Up Throw
    FtMoveId_ThrowLw,          ///< Down Throw
    FtMoveId_CargoThrowF,      ///< Donkey Kong Cargo Forward Throw
    FtMoveId_CargoThrowB,      ///< Donkey Kong Cargo Back Throw
    FtMoveId_CargoThrowHi,     ///< Donkey Kong Cargo Up Throw
    FtMoveId_CargoThrowLw,     ///< Donkey Kong Cargo Down Throw
    FtMoveId_CliffAttackSlow,  ///< Ledge Attack (> 100% damage, 55-frame slow getup attack)
    FtMoveId_CliffAttackQuick, ///< Ledge Attack (< 100% damage, fast getup attack)
    FtMoveId_SwordSwing1,      ///< Beam Sword neutral jab swing
    FtMoveId_SwordSwing3,      ///< Beam Sword side tilt swing
    FtMoveId_SwordSwing4,      ///< Beam Sword side smash swing
    FtMoveId_SwordSwingDash,   ///< Beam Sword dash attack swing
    FtMoveId_BatSwing1,        ///< Home-Run Bat neutral jab swing
    FtMoveId_BatSwing3,        ///< Home-Run Bat side tilt swing
    FtMoveId_BatSwing4,        ///< Home-Run Bat smash swing (instant KO / Home-Run swing)
    FtMoveId_BatSwingDash,     ///< Home-Run Bat dash attack swing
    FtMoveId_ParasolSwing1,    ///< Parasol neutral jab swing
    FtMoveId_ParasolSwing3,    ///< Parasol side tilt swing
    FtMoveId_ParasolSwing4,    ///< Parasol side smash swing
    FtMoveId_ParasolSwingDash, ///< Parasol dash attack swing
    FtMoveId_HarisenSwing1,    ///< Fan (Harisen) neutral jab swing
    FtMoveId_HarisenSwing3,    ///< Fan (Harisen) side tilt swing
    FtMoveId_HarisenSwing4,    ///< Fan (Harisen) side smash swing
    FtMoveId_HarisenSwingDash, ///< Fan (Harisen) dash attack swing
    FtMoveId_StarRodSwing1,    ///< Star Rod neutral jab swing
    FtMoveId_StarRodSwing3,    ///< Star Rod side tilt swing
    FtMoveId_StarRodSwing4,    ///< Star Rod side smash swing (fires star projectile)
    FtMoveId_StarRodSwingDash, ///< Star Rod dash attack swing
    FtMoveId_LipstickSwing1,   ///< Lip's Stick neutral jab swing
    FtMoveId_LipstickSwing3,   ///< Lip's Stick side tilt swing
    FtMoveId_LipstickSwing4,   ///< Lip's Stick side smash swing (causes flower growth)
    FtMoveId_LipstickSwingDash,///< Lip's Stick dash attack swing
    FtMoveId_Parasol,          ///< Parasol open / descent hit
    FtMoveId_LGunShoot,        ///< Ray Gun shot projectile
    FtMoveId_FireFlowerShoot,  ///< Fire Flower flame stream
    FtMoveId_Screw,            ///< Screw Attack jumping multihit
    FtMoveId_ScopeRapid,       ///< Super Scope rapid-fire projectile
    FtMoveId_ScopeFire,        ///< Super Scope charged shot projectile
    FtMoveId_Hammer,           ///< Hammer swing attack
    FtMoveId_WarpStarFall,     ///< Warp Star crash explosion
} FtMoveId;

/**
 * @brief Smash attack charging state machine.
 * @details Smash attacks can be charged for up to 60 frames. Damage increases linearly
 * by up to 1.367x (formula: base_dmg * (1.0 + 0.367 * charge_frames / 60)).
 */
typedef enum SmashState {
    SmashState_None,       ///< Not charging smash attack
    SmashState_PreCharge,  ///< Entering charge window
    SmashState_Charging,   ///< Holding charge (button held, storing charge frames)
    SmashState_Release,    ///< Releasing charged smash attack
} SmashState;

/**
 * @brief Ground burial status types (e.g. Pitfall item, DK Headbutt).
 */
typedef enum ftCommon_BuryType {
    BuryType_Unk0,
    BuryType_Unk1,
    BuryType_Unk2,
    BuryType_Unk3,
} ftCommon_BuryType;

/**
 * @brief Dynamic bone physics limits.
 */
enum Ft_Dynamics {
    Ft_Dynamics_NumMax = 10, ///< Maximum number of secondary animation dynamic bone sets per character
};

/**
 * @brief High-level game entity classification.
 */
enum EntityKind {
    EntityKind_None,    ///< Empty / invalid entity
    EntityKind_Fighter, ///< Fighter entity (HSD_GOBJ_CLASS_FIGHTER)
    EntityKind_Item,    ///< Item entity (HSD_GOBJ_CLASS_ITEM)
    EntityKind_UNKNOWN, ///< Unknown / unclassified entity
};

/**
 * @brief Fighter environment contact state: grounded vs airborne.
 */
typedef enum GroundOrAir {
    GA_Ground, ///< Fighter is grounded (feet on stage floor or platform)
    GA_Air,    ///< Fighter is airborne (free falling, jumping, tumbling)
} GroundOrAir;

/**
 * @brief CPU AI personality and controller routine identifiers.
 * @see ::ftCo_800B2AFC
 */
typedef enum CpuKind {
    CpuKind_0,
    CpuKind_1,
    CpuKind_2,
    CpuKind_3,
    CpuKind_4,
    CpuKind_5,
    CpuKind_Nana, ///< Nana AI companion follower logic
    CpuKind_7,
    CpuKind_8,
    CpuKind_9,
    CpuKind_10,
    CpuKind_11,
    CpuKind_12,
    CpuKind_13,
    CpuKind_14,
    CpuKind_15,
    CpuKind_16,
    CpuKind_17,
    CpuKind_18,
    CpuKind_19,
    CpuKind_20,
    CpuKind_21,
    CpuKind_22,
    CpuKind_23,
    CpuKind_24,
    CpuKind_25,
    CpuKind_26,
    CpuKind_27,
    CpuKind_28,
    CpuKind_29,
} CpuKind;

/**
 * @brief Color animation (ColAnim) indices for visual tint/flash effects.
 */
typedef enum FtColAnim {
    /// IDs starting here index the separate spycloak (Cloaking Device) list after subtraction.
    /* 0x7B */ FtColAnim_SpycloakStart = 0x7B,
} FtColAnim;

#endif
