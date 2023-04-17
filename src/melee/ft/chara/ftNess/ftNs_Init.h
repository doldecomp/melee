#ifndef _ftness_h_
#define _ftness_h_

#include <platform.h>

#include "ft/fighter.h"
#include "it/item.h"
#include "lb/lbvector.h"

#include <math.h>
#include <baselib/gobj.h>

typedef enum ftNessAction {
    AS_NESS_ATTACKS4 = ASID_MAX,
    AS_NESS_ATTACKHI4,
    AS_NESS_ATTACKHI4_CHARGE,
    AS_NESS_ATTACKHI4_RELEASE,
    AS_NESS_ATTACKLW4,
    AS_NESS_ATTACKLW4_CHARGE,
    AS_NESS_ATTACKLW4_RELEASE,
    AS_NESS_SPECIALN_START,
    AS_NESS_SPECIALN_HOLD,
    AS_NESS_SPECIALN_HOLD_RELEASE,
    AS_NESS_SPECIALN_END,
    AS_NESS_SPECIALAIRN_START,
    AS_NESS_SPECIALAIRN_HOLD,
    AS_NESS_SPECIALAIRN_HOLD_RELEASE,
    AS_NESS_SPECIALAIRN_END,
    AS_NESS_SPECIALS,
    AS_NESS_SPECIALAIRS,
    AS_NESS_SPECIALHI_START,
    AS_NESS_SPECIALHI_HOLD,
    AS_NESS_SPECIALHI_END,
    AS_NESS_SPECIALHI,
    AS_NESS_SPECIALAIRHI_START,
    AS_NESS_SPECIALAIRHI_HOLD,
    AS_NESS_SPECIALAIRHI_END,
    AS_NESS_SPECIALAIRHI,
    AS_NESS_SPECIALAIRHI_HITWALL,
    AS_NESS_SPECIALLW_START,
    AS_NESS_SPECIALLW_HOLD,
    AS_NESS_SPECIALLW_HIT,
    AS_NESS_SPECIALLW_END,
    AS_NESS_SPECIALLW_TURN,
    AS_NESS_SPECIALAIRLW_START,
    AS_NESS_SPECIALAIRLW_HOLD,
    AS_NESS_SPECIALAIRLW_HIT,
    AS_NESS_SPECIALAIRLW_END,
    AS_NESS_SPECIALAIRLW_TURN,

} ftNessAction;

// Flags used by Ness in Motion State Change

// SpecialN/SpecialAirN (PK Flash)
#define FTNESS_SPECIALN_COLL_FLAG                                             \
    FtStateChange_SkipUpdateMatAnim | FtStateChange_SkipUpdateColAnim |       \
        FtStateChange_UpdateCmd | FtStateChange_SkipUpdateItemVis |           \
        FtStateChange_Unk_19 | FtStateChange_SkipUpdateModelPartVis |         \
        FtStateChange_SkipUpdateModelFlag | FtStateChange_Unk_27

// SpecialHi/SpecialAirHi (PK Thunder)
#define FTNESS_SPECIALHI_COLL_FLAG                                            \
    FtStateChange_SkipUpdateMatAnim | FtStateChange_SkipUpdateColAnim |       \
        FtStateChange_UpdateCmd | FtStateChange_SkipUpdateItemVis |           \
        FtStateChange_Unk_19 | FtStateChange_SkipUpdateModelPartVis |         \
        FtStateChange_SkipUpdateModelFlag | FtStateChange_Unk_27

// SpecialHi Jibaku (PK Thunder 2 Self-Hit)
#define FTNESS_JIBAKU_COLL_FLAG                                               \
    FtStateChange_PreserveGfx | FtStateChange_SkipUpdateHit |                 \
        FtStateChange_SkipUpdateMatAnim | FtStateChange_SkipUpdateColAnim |   \
        FtStateChange_UpdateCmd | FtStateChange_SkipUpdateItemVis |           \
        FtStateChange_Unk_19 | FtStateChange_SkipUpdateModelPartVis |         \
        FtStateChange_SkipUpdateModelFlag | FtStateChange_Unk_27

// SpecialLw (PSI Magnet)
#define FTNESS_SPECIALLW_COLL_FLAG                                            \
    FtStateChange_PreserveGfx | FtStateChange_SkipUpdateMatAnim |             \
        FtStateChange_SkipUpdateColAnim | FtStateChange_UpdateCmd |           \
        FtStateChange_SkipUpdateItemVis | FtStateChange_Unk_19 |              \
        FtStateChange_SkipUpdateModelPartVis |                                \
        FtStateChange_SkipUpdateModelFlag | FtStateChange_Unk_27

#define FTNESS_SPECIALLW_END_FLAG                                             \
    FtStateChange_SkipUpdateMatAnim | FtStateChange_SkipUpdateColAnim |       \
        FtStateChange_UpdateCmd | FtStateChange_SkipUpdateItemVis |           \
        FtStateChange_Unk_19 | FtStateChange_SkipUpdateModelPartVis |         \
        FtStateChange_SkipUpdateModelFlag | FtStateChange_Unk_27

// Special Attributes

typedef struct ftNessAttributes {
    // Neutral Special - PK Flash
    s32 x0_PKFLASH_TIMER1_LOOPFRAMES;
    s32 x4_PKFLASH_TIMER2_LOOPFRAMES;
    s32 x8_PKFLASH_GRAVITY_DELAY;
    s32 xC_PKFLASH_MINCHARGEFRAMES;
    f32 x10_PKFLASH_UNK1;
    f32 x14_PKFLASH_FALL_ACCEL;
    f32 x18_PKFLASH_UNK2;
    f32 x1C_PKFLASH_LANDING_LAG; // If set to 0, Ness does not enter freefall
                                 // after aerial PK Flash, but loses his double
                                 // jump.
    // Side Special - PK Fire
    f32 x20_PKFIRE_AERIAL_LAUNCH_TRAJECTORY; // Radians
    f32 x24_PKFIRE_AERIAL_VELOCITY;
    f32 x28_PKFIRE_GROUNDED_LAUNCH_TRAJECTORY; // Radians
    f32 x2C_PKFIRE_GROUNDED_VELOCITY;
    f32 x30_PKFIRE_SPAWN_X;
    f32 x34_PKFIRE_SPAWN_Y;
    f32 x38_PKFIRE_LANDING_LAG;
    // Up Special - PK Thunder
    f32 x3C_PK_THUNDER_UNK1;
    u32 x40_PK_THUNDER_LOOP1;
    u32 x44_PK_THUNDER_LOOP2;
    u32 x48_PK_THUNDER_GRAVITY_DELAY;
    f32 x4C_PK_THUNDER_UNK2;
    f32 x50_PK_THUNDER_FALL_ACCEL;
    // Up Special - PK Thunder 2 (Self-Hit)
    f32 x54_PK_THUNDER_2_MOMENTUM;
    f32 x58_PK_THUNDER_2_UNK1;
    f32 x5C_PK_THUNDER_2_DECELERATION_RATE;
    f32 x60_PK_THUNDER_2_KNOCKDOWN_ANGLE; // Angle to determine whether to
                                          // enter PK Thunder 2 or DownBound
                                          // state (Ground Only)
    f32 x64_PK_THUNDER_2_WALLHUG_ANGLE;   // Surface angle to determine whether
                                          // PK Thunder 2 wallhugs or bounces
    f32 x68_PK_THUNDER_2_UNK2;
    f32 x6C_PK_THUNDER_2_FREEFALL_ANIM_BLEND; // Amount of animation blend
                                              // frames Ness goes through when
                                              // entering FallSpecial through
                                              // his SpecialHi Motion States
    f32 x70_PK_THUNDER_2_LANDING_LAG; // If set to 0, Ness does not enter
                                      // freefall after aerial PK Thunder, but
                                      // loses his double jump.
    // Down Special - PSI Magnet
    f32 x74_PSI_MAGNET_RELEASE_LAG; // Auto lag frames after initializing PSI
                                    // Magnet if B is not being held. PSI
                                    // Magnet is immediately released with no
                                    // lag once these frames have passed.
    f32 x78_PSI_MAGNET_UNK1; // Note: Reminiscent of Fox and Falco's Reflector
                             // turn duration attribute? Unused.
    f32 x7C_PSI_MAGNET_UNK2; // Note: Reminiscent of Fox and Falco's Reflector
                             // Unk1 attribute? Unused.
    f32 x80_PSI_MAGNET_UNK3; // Unused.
    s32 x84_PSI_MAGNET_FRAMES_BEFORE_GRAVITY;
    f32 x88_PSI_MAGNET_MOMENTUM_PRESERVATION;
    f32 x8C_PSI_MAGNET_FALL_ACCEL;
    f32 x90_PSI_MAGNET_UNK4;     // Unused.
    f32 x94_PSI_MAGNET_HEAL_MUL; // Multiplies projectile damage by this value
                                 // and heals result
    AbsorbDesc x98_PSI_MAGNET_ABSORPTION;
    // Up/Down Smash - Yo-Yo
    f32 xAC_YOYO_CHARGE_DURATION; // Amount of frames Yo-Yo can be charged
    f32 xB0_YOYO_DAMAGE_MUL;      // Charged Yo-Yo damage multiplier; 350 by
                             // default, identical to the Smash Charge standard
    f32 xB4_YOYO_REHIT_RATE; // Amount of frames needed for the Yo-Yo to hit
                             // again after colliding with a hurtbox
    // Forward Smash - Baseball Bat
    ReflectDesc xB8_BASEBALL_BAT;

} ftNessAttributes;

extern MotionState ftNs_Init_MotionStateTable[];
extern char ftNs_Init_DatFilename[];
extern char ftNs_Init_DataName[];
extern Fighter_CostumeStrings ftNs_Init_CostumeStrings[];
extern char ftNs_Init_AnimDatFilename[];
extern Fighter_DemoStrings ftNs_Init_DemoMotionFilenames;

// Ness functions

void ftNs_Init_OnDeath(HSD_GObj* gobj);
void ftNs_Init_OnLoad(HSD_GObj* gobj);
void ftNs_Init_OnDamage(HSD_GObj* gobj);
void ftNs_Init_OnAbsorb(HSD_GObj* gobj);
f32 ftNs_Init_GetAbsorbHeal(Fighter* fp);
void ftNs_Init_OnItemPickup(HSD_GObj* gobj, bool catchItemFlag);
void ftNs_Init_OnItemInvisible(HSD_GObj* gobj);
void ftNs_Init_OnItemVisible(HSD_GObj* gobj);
void ftNs_Init_OnItemDrop(HSD_GObj* gobj, bool dropItemFlag);
void ftNs_Init_LoadSpecialAttrs(HSD_GObj* gobj);

/// Change model's MatAnim frames to hurt textures
void ftNs_Init_OnKnockbackEnter(HSD_GObj* gobj);

/// Change model's MatAnim frames to normal textures
void ftNs_Init_OnKnockbackExit(HSD_GObj* gobj);

// Forward Smash (AttackS4)

void ftNs_AttackS4_OnReflect(HSD_GObj* gobj);
bool ftNs_AttackS4_CheckNessBatRemove(HSD_GObj* gobj);
void ftNs_AttackS4_ItemNessBatRemove(HSD_GObj* gobj);
void ftNs_AttackS4_ItemNessBatSetNULL(HSD_GObj* gobj);

void ftNs_AttackS4_Anim(HSD_GObj* gobj);
void ftNs_AttackS4_IASA(HSD_GObj* gobj);
void ftNs_AttackS4_Phys(HSD_GObj* gobj);
void ftNs_AttackS4_Coll(HSD_GObj* gobj);

// Yo-Yo item setup & math

/// Ness Yo-Yo HitCapsule Position Update
void ftNs_AttackHi4_YoyoUpdateHitPos(HSD_GObj* gobj);

/// Ness D-Smash HitCapsule Refresh Timer
void ftNs_AttackHi4_YoyoCheckTimedRehit(HSD_GObj* gobj);

/// Check collision of Bone (Yo-Yo attach bone)
/// @remarks Also used by Sheik???
s32 ftNs_AttackHi4_YoyoCheckEnvColl(HSD_GObj* gobj, Vec3* ECBUnk,
                                    Vec3* ECBUnk2, f32 float_unk);

void ftNs_AttackHi4_YoyoSetUnkPos(HSD_GObj* gobj, Vec3* arg1);

/// Set Yo-Yo hitbox position?
void ftNs_AttackHi4_YoyoSetHitPos(HSD_GObj* gobj);

void ftNs_AttackHi4_YoyoSetHitPosUnk(HSD_GObj* gobj, f32 arg8);

/// Check if Yo-Yo is colliding with an obstacle (wall / air)
bool ftNs_AttackHi4_YoyoCheckNoObstruct(HSD_GObj* gobj);

/// Set ftcmd-, fp- and stateVars
void ftNs_AttackHi4_YoyoSetVarAll(HSD_GObj* gobj);

/// Applies Smash Charge attributes to Ness's Up/Down Smash
void ftNs_AttackHi4_YoyoApplySmash(HSD_GObj* gobj);

void ftNs_AttackHi4_YoyoSetChargeDamage(HSD_GObj* gobj); // Used by Up Smash

/// Ness Yo-Yo Think
bool ftNs_AttackHi4_YoyoThink_IsRemove(HSD_GObj* gobj);

/// Calculates Yo-Yo texture rotation speed?
void ftNs_AttackHi4_YoyoSetUnkRate(HSD_GObj* gobj);

/// Creates Yo-Yo item and sets up callbacks
void ftNs_AttackHi4_YoyoCreateItem(HSD_GObj* gobj);

/// Something to do with Yo-Yo flags
void ftNs_AttackHi4_YoyoItemSetFlag(HSD_GObj* gobj);

/// Despawn Yo-Yo item
void ftNs_AttackHi4_YoyoItemDespawn(HSD_GObj* gobj);

void ftNs_AttackHi4_YoyoItemSetUnk(HSD_GObj* gobj);
void ftNs_AttackHi4_YoyoItemSetUnk2(HSD_GObj* gobj);

// Up Smash Motion State hook

/// Ness's Up Smash Motion State handler
void ftNs_AttackHi4_Enter(HSD_GObj* gobj);

// Start rehit timer if target is hit

/// Initiates rehit timer for Yo-Yo hitbox
void ftNs_AttackHi4_YoyoStartTimedRehit(HSD_GObj* gobj);

// Up Smash callbacks (AttackHi4)

/// Ness's Up Smash Animation Callback
void ftNs_AttackHi4_Anim(HSD_GObj* gobj);

void ftNs_AttackHi4_IASA(HSD_GObj* gobj);
void ftNs_AttackHi4_Phys(HSD_GObj* gobj);
void ftNs_AttackHi4_Coll(HSD_GObj* gobj);
void ftNs_AttackHi4Charge_Anim(HSD_GObj* gobj);
void ftNs_AttackHi4Charge_IASA(HSD_GObj* gobj);
void ftNs_AttackHi4Charge_Phys(HSD_GObj* gobj);
void ftNs_AttackHi4Charge_Coll(HSD_GObj* gobj);
void ftNs_AttackHi4Charge_Enter(HSD_GObj* gobj);
void ftNs_AttackHi4Release_Anim(HSD_GObj* gobj);
void ftNs_AttackHi4Release_IASA(HSD_GObj* gobj);
void ftNs_AttackHi4Release_Phys(HSD_GObj* gobj);
void ftNs_AttackHi4Release_Coll(HSD_GObj* gobj);

/// Ness's Up Smash Post-Charge Motion State handler
void ftNs_AttackHi4Release_Enter(HSD_GObj* gobj);

// Down Smash callbacks (AttackLw4)

void ftNs_AttackLw4_Enter(HSD_GObj* gobj);
void ftNs_AttackLw4_Anim(HSD_GObj* gobj);
void ftNs_AttackLw4_IASA(HSD_GObj* gobj);
void ftNs_AttackLw4_Phys(HSD_GObj* gobj);
void ftNs_AttackLw4_Coll(HSD_GObj* gobj);
void ftNs_AttackLw4Charge_Anim(HSD_GObj* gobj);
void ftNs_AttackLw4Charge_IASA(HSD_GObj* gobj);
void ftNs_AttackLw4Charge_Phys(HSD_GObj* gobj);
void ftNs_AttackLw4Charge_Coll(HSD_GObj* gobj);
void ftNs_AttackLw4Charge_Enter(HSD_GObj* gobj);
void ftNs_AttackLw4Release_Anim(HSD_GObj* gobj);
void ftNs_AttackLw4Release_IASA(HSD_GObj* gobj);
void ftNs_AttackLw4Release_Phys(HSD_GObj* gobj);
void ftNs_AttackLw4Release_Coll(HSD_GObj* gobj);
void ftNs_AttackLw4Release_Enter(HSD_GObj* gobj);

// PK Fire callbacks (SpecialS)

void ftNs_SpecialS_ItemPKFireSpawn(HSD_GObj* gobj);
void ftNs_SpecialS_Enter(HSD_GObj* gobj);
void ftNs_SpecialAirS_Enter(HSD_GObj* gobj);
void ftNs_SpecialS_Anim(HSD_GObj* gobj);
void ftNs_SpecialAirS_Anim(HSD_GObj* gobj);
void ftNs_SpecialS_Phys(HSD_GObj* gobj);
void ftNs_SpecialAirS_Phys(HSD_GObj* gobj);
void ftNs_SpecialS_Coll(HSD_GObj* gobj);
void ftNs_SpecialAirS_Coll(HSD_GObj* gobj);

// PK Flash callbacks (SpecialN)

bool ftNs_SpecialN_CheckSpecialNHold(HSD_GObj* gobj);
void ftNs_SpecialN_SetNULL(HSD_GObj* gobj);
void ftNs_SpecialN_ItemPKFlushSetNULL(HSD_GObj* gobj);
void ftNs_SpecialNStart_Enter(HSD_GObj* gobj);
void ftNs_SpecialAirNStart_Enter(HSD_GObj* gobj);
void ftNs_SpecialNStart_Anim(HSD_GObj* gobj);
void ftNs_SpecialNHold_Anim(HSD_GObj* gobj);
void ftNs_SpecialNEnd_Anim(HSD_GObj* gobj);
void ftNs_SpecialAirNStart_Anim(HSD_GObj* gobj);
void ftNs_SpecialAirNHold_Anim(HSD_GObj* gobj);
void ftNs_SpecialAirNEnd_Anim(HSD_GObj* gobj);
void ftNs_SpecialNStart_IASA(HSD_GObj* gobj);
void ftNs_SpecialNHold_IASA(HSD_GObj* gobj);
void ftNs_SpecialNEnd_IASA(HSD_GObj* gobj);
void ftNs_SpecialAirNStart_IASA(HSD_GObj* gobj);
void ftNs_SpecialAirNHold_IASA(HSD_GObj* gobj);
void ftNs_SpecialAirNEnd_IASA(HSD_GObj* gobj);
void ftNs_SpecialNStart_Phys(HSD_GObj* gobj);
void ftNs_SpecialNHold_Phys(HSD_GObj* gobj);
void ftNs_SpecialNEnd_Phys(HSD_GObj* gobj);
void ftNs_SpecialAirNStart_Phys(HSD_GObj* gobj);
void ftNs_SpecialAirNHold_Phys(HSD_GObj* gobj);
void ftNs_SpecialAirNEnd_Phys(HSD_GObj* gobj);
void ftNs_SpecialNStart_Coll(HSD_GObj* gobj);
void ftNs_SpecialNHold_Coll(HSD_GObj* gobj);
void ftNs_SpecialNEnd_Coll(HSD_GObj* gobj);
void ftNs_SpecialAirNStart_Coll(HSD_GObj* gobj);
void ftNs_SpecialAirNHold_Coll(HSD_GObj* gobj);
void ftNs_SpecialAirNEnd_Coll(HSD_GObj* gobj);

// PK Thunder callbacks (SpecialHi)

void ftNs_SpecialHiStopGFX(HSD_GObj* gobj);
bool ftNs_SpecialHi_ItemPKThunder_CheckNessCollide(HSD_GObj* gobj);
bool ftNs_SpecialHi_CheckSpecialHiHold(HSD_GObj* gobj);
void ftNs_SpecialHi_ItemPKThunderRemove(HSD_GObj* gobj);
void ftNs_SpecialHi_TakeDamage(HSD_GObj* gobj);
void ftNs_SpecialHi_ItemPKThunderCheckOwn(HSD_GObj* gobj, HSD_GObj* gobj2);
void ftNs_SpecialAirHi_CollisionModVel(HSD_GObj* gobj, CollData* coll_data);
void ftNs_SpecialHiStart_Enter(HSD_GObj* gobj);
void ftNs_SpecialAirHiStart_Enter(HSD_GObj* gobj);
void ftNs_SpecialHi_Enter(HSD_GObj* gobj);
void ftNs_SpecialAirHi_Enter(HSD_GObj* gobj);
void ftNs_SpecialHiStart_Anim(HSD_GObj* gobj);
void ftNs_SpecialHiHold_Anim(HSD_GObj* gobj);
void ftNs_SpecialHiEnd_Anim(HSD_GObj* gobj);
void ftNs_SpecialHi_Anim(HSD_GObj* gobj);
void ftNs_SpecialAirHiStart_Anim(HSD_GObj* gobj);
void ftNs_SpecialAirHiHold_Anim(HSD_GObj* gobj);
void ftNs_SpecialAirHiEnd_Anim(HSD_GObj* gobj);
void ftNs_SpecialAirHi_Anim(HSD_GObj* gobj);
void ftNs_SpecialAirHiRebound_Anim(HSD_GObj* gobj);
void ftNs_SpecialHiStart_IASA(HSD_GObj* gobj);
void ftNs_SpecialHiHold_IASA(HSD_GObj* gobj);
void ftNs_SpecialHiEnd_IASA(HSD_GObj* gobj);
void ftNs_SpecialHi_IASA(HSD_GObj* gobj);
void ftNs_SpecialAirHiStart_IASA(HSD_GObj* gobj);
void ftNs_SpecialAirHiHold_IASA(HSD_GObj* gobj);
void ftNs_SpecialAirHiEnd_IASA(HSD_GObj* gobj);
void ftNs_SpecialAirHi_IASA(HSD_GObj* gobj);
void ftNs_SpecialAirHiRebound_IASA(HSD_GObj* gobj);
void ftNs_SpecialHiStart_Phys(HSD_GObj* gobj);
void ftNs_SpecialHiHold_Phys(HSD_GObj* gobj);
void ftNs_SpecialHiEnd_Phys(HSD_GObj* gobj);
void ftNs_SpecialHi_Phys(HSD_GObj* gobj);
void ftNs_SpecialAirHiStart_Phys(HSD_GObj* gobj);
void ftNs_SpecialAirHiHold_Phys(HSD_GObj* gobj);
void ftNs_SpecialAirHiEnd_Phys(HSD_GObj* gobj);
void ftNs_SpecialAirHi_Phys(HSD_GObj* gobj);
void ftNs_SpecialAirHiRebound_Phys(HSD_GObj* gobj);
void ftNs_SpecialHiStart_Coll(HSD_GObj* gobj);
void ftNs_SpecialHiHold_Coll(HSD_GObj* gobj);
void ftNs_SpecialHiEnd_Coll(HSD_GObj* gobj);
void ftNs_SpecialHi_Coll(HSD_GObj* gobj);
void ftNs_SpecialAirHiStart_Coll(HSD_GObj* gobj);
void ftNs_SpecialAirHiHold_Coll(HSD_GObj* gobj);
void ftNs_SpecialAirHiEnd_Coll(HSD_GObj* gobj);
void ftNs_SpecialAirHi_Coll(HSD_GObj* gobj);
void ftNs_SpecialAirHiRebound_Coll(HSD_GObj* gobj);

// PSI Magnet callbacks (SpecialLw)

void ftNs_SpecialLwStart_Enter(HSD_GObj* gobj);
void ftNs_SpecialAirLwStart_Enter(HSD_GObj* gobj);
void ftNs_SpecialLwStart_IASA(HSD_GObj* gobj);
void ftNs_SpecialAirLwStart_IASA(HSD_GObj* gobj);
void ftNs_SpecialLwStart_Phys(HSD_GObj* gobj);
void ftNs_SpecialAirLwStart_Phys(HSD_GObj* gobj);
void ftNs_SpecialLwStart_Coll(HSD_GObj* gobj);
void ftNs_SpecialLwStart_GroundToAir(HSD_GObj* gobj);
void ftNs_SpecialAirLwStart_AirToGround(HSD_GObj* gobj);
void ftNs_SpecialLwHold_Anim(HSD_GObj* gobj);
void ftNs_SpecialAirLwHold_Anim(HSD_GObj* gobj);
void ftNs_SpecialLwHold_IASA(HSD_GObj* gobj);
void ftNs_SpecialAirLwHold_IASA(HSD_GObj* gobj);
void ftNs_SpecialLwHold_Phys(HSD_GObj* gobj);
void ftNs_SpecialAirLwHold_Phys(HSD_GObj* gobj);
void ftNs_SpecialLwHold_Coll(HSD_GObj* gobj);
void ftNs_SpecialAirLwHold_Coll(HSD_GObj* gobj);
void ftNs_SpecialLwHold_GroundToAir(HSD_GObj* gobj);
void ftNs_SpecialAirLwHold_AirToGround(HSD_GObj* gobj);
void ftNs_SpecialLwHold_Enter(HSD_GObj* gobj);
void ftNs_SpecialAirLwHold_Enter(HSD_GObj* gobj);
void ftNs_SpecialLwTurn_Anim(HSD_GObj* gobj);
void ftNs_SpecialAirLwTurn_Anim(HSD_GObj* gobj);
void ftNs_SpecialLwTurn_IASA(HSD_GObj* gobj);
void ftNs_SpecialAirLwTurn_IASA(HSD_GObj* gobj);
void ftNs_SpecialLwTurn_Phys(HSD_GObj* gobj);
void ftNs_SpecialAirLwTurn_Phys(HSD_GObj* gobj);
void ftNs_SpecialLwTurn_Coll(HSD_GObj* gobj);
void ftNs_SpecialAirLwTurn_Coll(HSD_GObj* gobj);
void ftNs_SpecialLwTurn_GroundToAir(HSD_GObj* gobj);
void ftNs_SpecialAirLwTurn_AirToGround(HSD_GObj* gobj);
bool ftNs_SpecialLwHold_GroundOrAir(HSD_GObj* gobj);
void ftNs_SpecialLwHit_Anim(HSD_GObj* gobj);
void ftNs_SpecialAirLwHit_Anim(HSD_GObj* gobj);
void ftNs_SpecialLwHit_IASA(HSD_GObj* gobj);
void ftNs_SpecialAirLwHit_IASA(HSD_GObj* gobj);
void ftNs_SpecialLwHit_Phys(HSD_GObj* gobj);
void ftNs_SpecialAirLwHit_Phys(HSD_GObj* gobj);
void ftNs_SpecialLwHit_Coll(HSD_GObj* gobj);
void ftNs_SpecialAirLwHit_Coll(HSD_GObj* gobj);
void ftNs_SpecialLwHit_GroundToAir(HSD_GObj* gobj);
void ftNs_SpecialAirLwHit_AirToGround(HSD_GObj* gobj);
void ftNs_AbsorbThink_DecideAction(HSD_GObj* gobj);
void ftNs_SpecialLwEnd_Anim(HSD_GObj* gobj);
void ftNs_SpecialAirLwEnd_Anim(HSD_GObj* gobj);
void ftNs_SpecialLwEnd_IASA(HSD_GObj* gobj);
void ftNs_SpecialAirLwEnd_IASA(HSD_GObj* gobj);
void ftNs_SpecialLwEnd_Phys(HSD_GObj* gobj);
void ftNs_SpecialAirLwEnd_Phys(HSD_GObj* gobj);
void ftNs_SpecialLwEnd_Coll(HSD_GObj* gobj);
void ftNs_SpecialAirLwEnd_Coll(HSD_GObj* gobj);
void ftNs_SpecialLwEnd_GroundToAir(HSD_GObj* gobj);
void ftNs_SpecialAirLwEnd_AirToGround(HSD_GObj* gobj);
void ftNs_SpecialLwEnd_Enter(HSD_GObj* gobj);
void ftNs_SpecialAirLwEnd_Enter(HSD_GObj* gobj);

#endif
