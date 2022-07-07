#ifndef _ftness_h_
#define _ftness_h_

#include <global.h>

#include <dolphin/types.h>

#include <sysdolphin/baselib/gobj.h>

#include <melee/lb/lbvector.h>

#include <math.h>

#include <melee/ft/fighter.h>

#include <melee/it/item.h>

typedef enum ftNessAction
{
	AS_FTCOMMON = 340,
	AS_NESS_ATTACKS4,
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

// Flags used by Ness in Action State Change //

// SpecialN/SpecialAirN (PK Flash) //
#define NESS_SPECIALN_COLL_FLAG FIGHTER_MATANIM_NOUPDATE | FIGHTER_UNK_0x1000 | FIGHTER_CMD_UPDATE | FIGHTER_ITEMVIS_NOUPDATE | FIGHTER_SKIP_UNK_0x2222 | FIGHTER_UNK_0x400000 | FIGHTER_UNK_0x4000000 | FIGHTER_UNK_0x2227

// SpecialHi/SpecialAirHi (PK Thunder) //
#define NESS_SPECIALHI_COLL_FLAG FIGHTER_MATANIM_NOUPDATE | FIGHTER_UNK_0x1000 | FIGHTER_CMD_UPDATE | FIGHTER_ITEMVIS_NOUPDATE | FIGHTER_SKIP_UNK_0x2222 | FIGHTER_UNK_0x400000 | FIGHTER_UNK_0x4000000 | FIGHTER_UNK_0x2227

// SpecialHi Jibaku (PK Thunder 2 Self-Hit) //
#define NESS_JIBAKU_COLL_FLAG FIGHTER_GFX_PRESERVE | FIGHTER_UNK_HAMMER | FIGHTER_MATANIM_NOUPDATE | FIGHTER_UNK_0x1000 | FIGHTER_CMD_UPDATE | FIGHTER_ITEMVIS_NOUPDATE | FIGHTER_SKIP_UNK_0x2222 | FIGHTER_UNK_0x400000 | FIGHTER_UNK_0x4000000 | FIGHTER_UNK_0x2227

// SpecialLw (PSI Magnet) //
#define NESS_SPECIALLW_COLL_FLAG FIGHTER_GFX_PRESERVE | FIGHTER_MATANIM_NOUPDATE | FIGHTER_UNK_0x1000 | FIGHTER_CMD_UPDATE | FIGHTER_ITEMVIS_NOUPDATE | FIGHTER_SKIP_UNK_0x2222 | FIGHTER_UNK_0x400000 | FIGHTER_UNK_0x4000000 | FIGHTER_UNK_0x2227

#define NESS_SPECIALLW_END_FLAG FIGHTER_MATANIM_NOUPDATE | FIGHTER_UNK_0x1000 | FIGHTER_CMD_UPDATE | FIGHTER_ITEMVIS_NOUPDATE | FIGHTER_SKIP_UNK_0x2222 | FIGHTER_UNK_0x400000 | FIGHTER_UNK_0x4000000 | FIGHTER_UNK_0x2227

// Special Attributes //

typedef struct ftNessAttributes
{
	// Neutral Special - PK Flash
	s32 x0_PKFLASH_TIMER1_MINCHARGEFRAMES;
	s32 x4_PKFLASH_TIMER2_LOOPFRAMES;
	s32 x8_PKFLASH_FALLING_ACCEL_DELAY;
	s32 xC_PKFLASH_RELEASE_UNK;
	f32 x10_PKFLASH_UNK1;
	f32 x14_PKFLASH_FALL_ACCEL;
	f32 x18_PKFLASH_UNK2;
	f32 x1C_PKFLASH_LANDING_LAG; // If set to 0, Ness does not enter freefall after aerial PK Flash, but loses his double jump.
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
	u32 x48_PK_THUNDER_FALLING_ACCEL_DELAY;
	f32 x4C_PK_THUNDER_UNK2;
	f32 x50_PK_THUNDER_FALL_ACCEL;
	// Up Special - PK Thunder 2 (Self-Hit)
	f32 x54_PK_THUNDER_2_MOMENTUM;
	f32 x58_PK_THUNDER_2_UNK1;
	f32 x5C_PK_THUNDER_2_DECELERATION_RATE;
	f32 x60_PK_THUNDER_2_KNOCKDOWN_ANGLE; // Angle to determine whether to enter PK Thunder 2 or DownBound state (Ground Only)
	f32 x64_PK_THUNDER_2_WALLHUG_ANGLE; // Surface angle to determine whether PK Thunder 2 wallhugs or bounces
	f32 x68_PK_THUNDER_2_UNK2;
	f32 x6C_PK_THUNDER_2_FREEFALL_ANIM_BLEND; // Amount of animation blend frames Ness goes through when entering FallSpecial through his SpecialHi Action States
	f32 x70_PK_THUNDER_2_LANDING_LAG; // If set to 0, Ness does not enter freefall after aerial PK Thunder, but loses his double jump.
	// Down Special - PSI Magnet
	f32 x74_PSI_MAGNET_RELEASE_LAG; // Auto lag frames after initializing PSI Magnet if B is not being held. PSI Magnet is immediately released with no lag once these frames have passed.
	f32 x78_PSI_MAGNET_UNK1; // Note: Reminiscent of Fox and Falco's Reflector turn duration attribute? Unused.
	f32 x7C_PSI_MAGNET_UNK2; // Note: Reminiscent of Fox and Falco's Reflector Unk1 attribute? Unused.
	f32 x80_PSI_MAGNET_UNK3; // Unused.
	s32 x84_PSI_MAGNET_FRAMES_BEFORE_GRAVITY;
	f32 x88_PSI_MAGNET_MOMENTUM_PRESERVATION;
	f32 x8C_PSI_MAGNET_FALL_ACCEL;
	f32 x90_PSI_MAGNET_UNK4; // Unused.
	f32 x94_PSI_MAGNET_HEAL_MUL; // Multiplies projectile damage by this value and heals result // 
	AbsorbDesc x98_PSI_MAGNET_ABSORPTION;
	// Up/Down Smash - Yo-Yo
	f32 xAC_YOYO_CHARGE_DURATION;	// Amount of frames Yo-Yo can be charged //
	f32 xB0_YOYO_DAMAGE_MUL;	// Charged Yo-Yo damage multiplier; 350 by default, identical to the Smash Charge standard //
	f32 xB4_YOYO_REHIT_RATE; // Amount of frames needed for the Yo-Yo to hit again after colliding with a hurtbox //
	// Forward Smash - Baseball Bat
	ReflectDesc xB8_BASEBALL_BAT;

}ftNessAttributes;

// Ness functions // 

void ftNess_OnDeath(HSD_GObj* gobj);
void ftNess_OnLoad(HSD_GObj* gobj);
void ftNess_OnDamage(HSD_GObj* gobj);
void ftNess_OnAbsorb(HSD_GObj* gobj);
f32 ftNess_GetAbsorbHeal(Fighter* ft);
void ftNess_OnItemPickup(HSD_GObj* gobj, BOOL catchItemFlag);
void ftNess_OnItemInvisible(HSD_GObj* gobj);
void ftNess_OnItemVisible(HSD_GObj* gobj);
void ftNess_OnItemDrop(HSD_GObj* gobj, BOOL dropItemFlag);
void ftNess_CopySpecialAttrs(HSD_GObj* gobj);
void ftNess_OnKnockbackEnter(HSD_GObj* gobj);
void ftNess_OnKnockbackExit(HSD_GObj* gobj);

// Forward Smash (AttackS4) //

void ftNess_AttackS4_OnReflect(HSD_GObj* gobj);
BOOL ftNess_CheckNessBatRemove(HSD_GObj* gobj);
void ftNess_ItemNessBatRemove(HSD_GObj* gobj);
void ftNess_ItemNessBatSetNULL(HSD_GObj* gobj);

void ftNess_AttackS4_Anim(HSD_GObj* gobj);
void ftNess_AttackS4_IASA(HSD_GObj* gobj);
void ftNess_AttackS4_Phys(HSD_GObj* gobj);
void ftNess_AttackS4_Coll(HSD_GObj* gobj);

// Yo-Yo item setup & math //

void ftNess_YoyoUpdateHitPos(HSD_GObj* gobj);
void ftNess_YoyoCheckTimedRehit(HSD_GObj* gobj);
void ftNess_YoyoApplyDamage(f32 unk_float, HSD_GObj* gobj); // Used by Down Smash //
s32 ftNess_YoyoCheckEnvColl(HSD_GObj* gobj, Vec3* ECBUnk, Vec3* ECBUnk2, f32 float_unk);
void ftNess_YoyoSetUnkPos(HSD_GObj* gobj, Vec3* arg1);
void ftNess_YoyoSetHitPos(HSD_GObj* gobj);
void ftNess_YoyoSetHitPosUnk(HSD_GObj* gobj, f32 arg8);
BOOL ftNess_YoyoCheckNoObstruct(HSD_GObj* gobj);
void ftNess_YoyoSetVarAll(HSD_GObj* gobj);
void ftNess_YoyoApplySmash(HSD_GObj* gobj);
void ftNess_YoyoSetChargeDamage(HSD_GObj* gobj); // Used by Up Smash //
BOOL ftNess_YoyoThink_IsRemove(HSD_GObj* gobj);
void ftNess_YoyoSetUnkRate(HSD_GObj* gobj);
void ftNess_YoyoCreateItem(HSD_GObj* gobj);
void ftNess_YoyoItemSetFlag(HSD_GObj* gobj);
void ftNess_YoyoItemDespawn(HSD_GObj* gobj);
void ftNess_YoyoItemSetUnk(HSD_GObj* gobj);
void ftNess_YoyoItemSetUnk2(HSD_GObj* gobj);

// Up Smash Action State hook //

void ftNess_AttackHi4_Action(HSD_GObj* gobj);

// Start rehit timer if target is hit //

void ftNess_YoyoStartTimedRehit(HSD_GObj* gobj);

// Up Smash callbacks (AttackHi4) //

void ftNess_AttackHi4_Anim(HSD_GObj* gobj);
void ftNess_AttackHi4_IASA(HSD_GObj* gobj);
void ftNess_AttackHi4_Phys(HSD_GObj* gobj);
void ftNess_AttackHi4_Coll(HSD_GObj* gobj);
void ftNess_AttackHi4_Charge_Anim(HSD_GObj* gobj);
void ftNess_AttackHi4_Charge_IASA(HSD_GObj* gobj);
void ftNess_AttackHi4_Charge_Phys(HSD_GObj* gobj);
void ftNess_AttackHi4_Charge_Coll(HSD_GObj* gobj);
void ftNess_AttackHi4_Charge_Action(HSD_GObj* gobj);
void ftNess_AttackHi4_Release_Anim(HSD_GObj* gobj);
void ftNess_AttackHi4_Release_IASA(HSD_GObj* gobj);
void ftNess_AttackHi4_Release_Phys(HSD_GObj* gobj);
void ftNess_AttackHi4_Release_Coll(HSD_GObj* gobj);
void ftNess_AttackHi4_Release_Action(HSD_GObj* gobj);

// Down Smash callbacks (AttackLw4) //

void ftNess_AttackLw4_Action(HSD_GObj* gobj);
void ftNess_AttackLw4_Anim(HSD_GObj* gobj);
void ftNess_AttackLw4_IASA(HSD_GObj* gobj);
void ftNess_AttackLw4_Phys(HSD_GObj* gobj);
void ftNess_AttackLw4_Coll(HSD_GObj* gobj);
void ftNess_AttackLw4_Charge_Anim(HSD_GObj* gobj);
void ftNess_AttackLw4_Charge_IASA(HSD_GObj* gobj);
void ftNess_AttackLw4_Charge_Phys(HSD_GObj* gobj);
void ftNess_AttackLw4_Charge_Coll(HSD_GObj* gobj);
void ftNess_AttackLw4_Charge_Action(HSD_GObj* gobj);
void ftNess_AttackLw4_Release_Anim(HSD_GObj* gobj);
void ftNess_AttackLw4_Release_IASA(HSD_GObj* gobj);
void ftNess_AttackLw4_Release_Phys(HSD_GObj* gobj);
void ftNess_AttackLw4_Release_Coll(HSD_GObj* gobj);
void ftNess_AttackLw4_Release_Action(HSD_GObj* gobj);

// PK Fire callbacks (SpecialS) //

void ftNess_ItemPKFireSpawn(HSD_GObj* gobj);
void ftNess_SpecialS_StartAction(HSD_GObj* gobj);
void ftNess_SpecialAirS_Action(HSD_GObj* gobj);
void ftNess_SpecialS_Anim(HSD_GObj* gobj);
void ftNess_SpecialAirS_Anim(HSD_GObj* gobj);
void ftNess_SpecialS_Phys(HSD_GObj* gobj);
void ftNess_SpecialAirS_Phys(HSD_GObj* gobj);
void ftNess_SpecialS_Coll(HSD_GObj* gobj);
void ftNess_SpecialAirS_Coll(HSD_GObj* gobj);

// PK Flash callbacks (SpecialN) //

BOOL ftNess_CheckSpecialNHold(HSD_GObj* gobj);
void ftNess_SpecialNSetNULL(HSD_GObj* gobj);
void ftNess_ItemPKFlushSetNULL(HSD_GObj* gobj);
void ftNess_SpecialNStart_Action(HSD_GObj* gobj);
void ftNess_SpecialAirNStart_Action(HSD_GObj* gobj);
void ftNess_SpecialNStart_Anim(HSD_GObj* gobj);
void ftNess_SpecialNHold_Anim(HSD_GObj* gobj);
void ftNess_SpecialNEnd_Anim(HSD_GObj* gobj);
void ftNess_SpecialAirNStart_Anim(HSD_GObj* gobj);
void ftNess_SpecialAirNHold_Anim(HSD_GObj* gobj);
void ftNess_SpecialAirNEnd_Anim(HSD_GObj* gobj);
void ftNess_SpecialNStart_IASA(HSD_GObj* gobj);
void ftNess_SpecialNHold_IASA(HSD_GObj* gobj);
void ftNess_SpecialNEnd_IASA(HSD_GObj* gobj);
void ftNess_SpecialAirNStart_IASA(HSD_GObj* gobj);
void ftNess_SpecialAirNHold_IASA(HSD_GObj* gobj);
void ftNess_SpecialAirNEnd_IASA(HSD_GObj* gobj);
void ftNess_SpecialNStart_Phys(HSD_GObj* gobj);
void ftNess_SpecialNHold_Phys(HSD_GObj* gobj);
void ftNess_SpecialNEnd_Phys(HSD_GObj* gobj);
void ftNess_SpecialAirNStart_Phys(HSD_GObj* gobj);
void ftNess_SpecialAirNHold_Phys(HSD_GObj* gobj);
void ftNess_SpecialAirNEnd_Phys(HSD_GObj* gobj);
void ftNess_SpecialNStart_Coll(HSD_GObj* gobj);
void ftNess_SpecialNHold_Coll(HSD_GObj* gobj);
void ftNess_SpecialNEnd_Coll(HSD_GObj* gobj);
void ftNess_SpecialAirNStart_Coll(HSD_GObj* gobj);
void ftNess_SpecialAirNHold_Coll(HSD_GObj* gobj);
void ftNess_SpecialAirNEnd_Coll(HSD_GObj* gobj);

// PK Thunder callbacks (SpecialHi) //

void ftNess_SpecialHiStopGFX(HSD_GObj* gobj);
BOOL ftNess_ItemPKThunder_CheckNessCollide(HSD_GObj* gobj);
BOOL ftNess_CheckSpecialHiHold(HSD_GObj* gobj);
void ftNess_ItemPKThunderRemove(HSD_GObj* gobj);
void ftNess_SpecialHiTakeDamage(HSD_GObj* gobj);
void ftNess_ItemPKThunderCheckOwn(HSD_GObj* gobj, HSD_GObj* gobj2);
void ftNess_SpecialAirHi_CollisionModVel(HSD_GObj* gobj, CollData* coll_data);
void ftNess_SpecialHi_StartAction(HSD_GObj* gobj);
void ftNess_SpecialAirHiStart_Action(HSD_GObj* gobj);
void ftNess_SpecialHi_Action(HSD_GObj* gobj);
void ftNess_SpecialAirHi_Action(HSD_GObj* gobj);
void ftNess_SpecialHiStart_Anim(HSD_GObj* gobj);
void ftNess_SpecialHiHold_Anim(HSD_GObj* gobj);
void ftNess_SpecialHiEnd_Anim(HSD_GObj* gobj);
void ftNess_SpecialHi_Anim(HSD_GObj* gobj);
void ftNess_SpecialAirHiStart_Anim(HSD_GObj* gobj);
void ftNess_SpecialAirHiHold_Anim(HSD_GObj* gobj);
void ftNess_SpecialAirHiEnd_Anim(HSD_GObj* gobj);
void ftNess_SpecialAirHi_Anim(HSD_GObj* gobj);
void ftNess_SpecialAirHiRebound_Anim(HSD_GObj* gobj);
void ftNess_SpecialHiStart_IASA(HSD_GObj* gobj);
void ftNess_SpecialHiHold_IASA(HSD_GObj* gobj);
void ftNess_SpecialHiEnd_IASA(HSD_GObj* gobj);
void ftNess_SpecialHi_IASA(HSD_GObj* gobj);
void ftNess_SpecialAirHiStart_IASA(HSD_GObj* gobj);
void ftNess_SpecialAirHiHold_IASA(HSD_GObj* gobj);
void ftNess_SpecialAirHiEnd_IASA(HSD_GObj* gobj);
void ftNess_SpecialAirHi_IASA(HSD_GObj* gobj);
void ftNess_SpecialAirHiRebound_IASA(HSD_GObj* gobj);
void ftNess_SpecialHiStart_Phys(HSD_GObj* gobj);
void ftNess_SpecialHiHold_Phys(HSD_GObj* gobj);
void ftNess_SpecialHiEnd_Phys(HSD_GObj* gobj);
void ftNess_SpecialHi_Phys(HSD_GObj* gobj);
void ftNess_SpecialAirHiStart_Phys(HSD_GObj* gobj);
void ftNess_SpecialAirHiHold_Phys(HSD_GObj* gobj);
void ftNess_SpecialAirHiEnd_Phys(HSD_GObj* gobj);
void ftNess_SpecialAirHi_Phys(HSD_GObj* gobj);
void ftNess_SpecialAirHiRebound_Phys(HSD_GObj* gobj);
void ftNess_SpecialHiStart_Coll(HSD_GObj* gobj);
void ftNess_SpecialHiHold_Coll(HSD_GObj* gobj);
void ftNess_SpecialHiEnd_Coll(HSD_GObj* gobj);
void ftNess_SpecialHi_Coll(HSD_GObj* gobj);
void ftNess_SpecialAirHiStart_Coll(HSD_GObj* gobj);
void ftNess_SpecialAirHiHold_Coll(HSD_GObj* gobj);
void ftNess_SpecialAirHiEnd_Coll(HSD_GObj* gobj);
void ftNess_SpecialAirHi_Coll(HSD_GObj* gobj);
void ftNess_SpecialAirHiRebound_Coll(HSD_GObj* gobj);

// PSI Magnet callbacks (SpecialLw)

void ftNess_SpecialLwStart_Action(HSD_GObj* gobj);
void ftNess_SpecialAirLwStart_Action(HSD_GObj* gobj);
void ftNess_SpecialLwStart_IASA(HSD_GObj* gobj);
void ftNess_SpecialAirLwStart_IASA(HSD_GObj* gobj);
void ftNess_SpecialLwStart_Phys(HSD_GObj* gobj);
void ftNess_SpecialAirLwStart_Phys(HSD_GObj* gobj);
void ftNess_SpecialLwStart_Coll(HSD_GObj* gobj);
void ftNess_SpecialLwStart_GroundToAir(HSD_GObj* gobj);
void ftNess_SpecialAirLwStart_AirToGround(HSD_GObj* gobj);
void ftNess_SpecialLwHold_Anim(HSD_GObj* gobj);
void ftNess_SpecialAirLwHold_Anim(HSD_GObj* gobj);
void ftNess_SpecialLwHold_IASA(HSD_GObj* gobj);
void ftNess_SpecialAirLwHold_IASA(HSD_GObj* gobj);
void ftNess_SpecialLwHold_Phys(HSD_GObj* gobj);
void ftNess_SpecialAirLwHold_Phys(HSD_GObj* gobj);
void ftNess_SpecialLwHold_Coll(HSD_GObj* gobj);
void ftNess_SpecialAirLwHold_Coll(HSD_GObj* gobj);
void ftNess_SpecialLwHold_GroundToAir(HSD_GObj* gobj);
void ftNess_SpecialAirLwHold_AirToGround(HSD_GObj* gobj);
void ftNess_SpecialLwHold_Action(HSD_GObj* gobj);
void ftNess_SpecialAirLwHold_Action(HSD_GObj* gobj);
void ftNess_SpecialLwTurn_Anim(HSD_GObj* gobj);
void ftNess_SpecialAirLwTurn_Anim(HSD_GObj* gobj);
void ftNess_SpecialLwTurn_IASA(HSD_GObj* gobj);
void ftNess_SpecialAirLwTurn_IASA(HSD_GObj* gobj);
void ftNess_SpecialLwTurn_Phys(HSD_GObj* gobj);
void ftNess_SpecialAirLwTurn_Phys(HSD_GObj* gobj);
void ftNess_SpecialLwTurn_Coll(HSD_GObj* gobj);
void ftNess_SpecialAirLwTurn_Coll(HSD_GObj* gobj);
void ftNess_SpecialLwTurn_GroundToAir(HSD_GObj* gobj);
void ftNess_SpecialAirLwTurn_AirToGround(HSD_GObj* gobj);
BOOL ftNess_SpecialLwHold_GroundOrAir(HSD_GObj* gobj);
void ftNess_SpecialLwHit_Anim(HSD_GObj* gobj);
void ftNess_SpecialAirLwHit_Anim(HSD_GObj* gobj);
void ftNess_SpecialLwHit_IASA(HSD_GObj* gobj);
void ftNess_SpecialAirLwHit_IASA(HSD_GObj* gobj);
void ftNess_SpecialLwHit_Phys(HSD_GObj* gobj);
void ftNess_SpecialAirLwHit_Phys(HSD_GObj* gobj);
void ftNess_SpecialLwHit_Coll(HSD_GObj* gobj);
void ftNess_SpecialAirLwHit_Coll(HSD_GObj* gobj);
void ftNess_SpecialLwHit_GroundToAir(HSD_GObj* gobj);
void ftNess_SpecialAirLwHit_AirToGround(HSD_GObj* gobj);
void ftNess_AbsorbThink_DecideAction(HSD_GObj* gobj);
void ftNess_SpecialLwEnd_Anim(HSD_GObj* gobj);
void ftNess_SpecialAirLwEnd_Anim(HSD_GObj* gobj);
void ftNess_SpecialLwEnd_IASA(HSD_GObj* gobj);
void ftNess_SpecialAirLwEnd_IASA(HSD_GObj* gobj);
void ftNess_SpecialLwEnd_Phys(HSD_GObj* gobj);
void ftNess_SpecialAirLwEnd_Phys(HSD_GObj* gobj);
void ftNess_SpecialLwEnd_Coll(HSD_GObj* gobj);
void ftNess_SpecialAirLwEnd_Coll(HSD_GObj* gobj);
void ftNess_SpecialLwEnd_GroundToAir(HSD_GObj* gobj);
void ftNess_SpecialAirLwEnd_AirToGround(HSD_GObj* gobj);
void ftNess_SpecialLwEnd_Action(HSD_GObj* gobj);
void ftNess_SpecialAirLwEnd_Action(HSD_GObj* gobj);

#endif
