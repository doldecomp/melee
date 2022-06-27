#ifndef _ftness_h_
#define _ftness_h_

#include <global.h>

#include <dolphin/types.h>

#include "sysdolphin/baselib/gobj.h"

#include "melee/lb/lbvector.h"

#include "math.h"

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
	f32 x20_PKFIRE_AERIAL_LAUNCH_TRAJECTORY;//Radians
	f32 x24_PKFIRE_AERIAL_VELOCITY;
	f32 x28_PKFIRE_GROUNDED_LAUNCH_TRAJECTORY;
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
	f32 x6C_PK_THUNDER_2_FREEFALL_ANIM_BLEND;
	f32 x70_PK_THUNDER_2_LANDING_LAG;
	// Down Special - PSI Magnet
	f32 x74_PSI_MAGNET_RELEASE_LAG; // Automatic lag frames after initializing PSI Magnet if B is not being held. PSI Magnet is immediately released with no lag once these frames have passed.
	f32 x78_PSI_MAGNET_UNK1; // Note: Reminiscent of Fox and Falco's Reflector turn duration attribute?
	f32 x7C_PSI_MAGNET_UNK2; // Note: Reminiscent of Fox and Falco's Reflector Unk1 attribute?
	f32 x80_PSI_MAGNET_UNK3;
	s32 x84_PSI_MAGNET_FRAMES_BEFORE_GRAVITY;
	f32 x88_PSI_MAGNET_MOMENTUM_PRESERVATION;
	f32 x8C_PSI_MAGNET_FALL_ACCEL;
	f32 x90_PSI_MAGNET_UNK6;
	f32 x94_PSI_MAGNET_HEAL_MUL;
	AbsorbDesc x98_PSI_MAGNET_ABSORPTION;
	// Up/Down Smash - Yo-Yo
	f32 xAC_YOYO_CHARGE_DURATION;	// Amount of frames Yo-Yo can be charged //
	f32 xB0_YOYO_DAMAGE_MUL;	// Charged Yo-Yo damage multiplier; 350 by default, identical to the Smash Charge standard //
	f32 xB4_YOYO_REHIT_RATE; // Amount of frames needed for the Yo-Yo to hit again after colliding with a hurtbox //
	// Forward Smash - Baseball Bat
	ReflectDesc xB8_BASEBALL_BAT;

}ftNessAttributes;

// Ness functions // 

void ftNess_OnDeath(HSD_GObj* gobj, s32 arg1);
void ftNess_OnLoad(HSD_GObj* gobj);
void ftNess_OnDamage(HSD_GObj* gobj);
void func_8011493C(HSD_GObj* gobj);
f32 ftNess_GetAbsorbHeal(Fighter* ft);
void func_80114968(HSD_GObj* gobj, s32 arg1);
void func_80114A48(HSD_GObj* gobj);
void func_80114A90(HSD_GObj* gobj);
void func_80114AD8(HSD_GObj* gobj, s32 arg1);
void func_80114B2C(HSD_GObj* gobj);
void func_80114B6C(HSD_GObj* gobj);

// Forward Smash //

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
void ftNess_SpecialS_Action(HSD_GObj* gobj);
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
void ftNess_SpecialN_Action(HSD_GObj* gobj);
void ftNess_SpecialAirN_Action(HSD_GObj* gobj);
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

void func_80117B70(HSD_GObj* gobj);
BOOL func_80117BBC(HSD_GObj* gobj);
BOOL func_80117D9C(HSD_GObj* gobj);
void func_80117DD4(HSD_GObj* gobj);
void func_80117E60(HSD_GObj* gobj);
void func_80117F00(HSD_GObj* gobj, HSD_GObj* gobj2);
void func_80117F24(HSD_GObj* gobj, CollData* coll_data);
void func_80118120(HSD_GObj* gobj);
void func_80118250(HSD_GObj* gobj);
void func_80118384(HSD_GObj* gobj);
void func_80118570(HSD_GObj* gobj);
void lbl_801186B0(HSD_GObj* gobj);
void lbl_801187A4(HSD_GObj* gobj);
void lbl_80118900(HSD_GObj* gobj);
void lbl_8011893C(HSD_GObj* gobj);
void lbl_80118A10(HSD_GObj* gobj);
void lbl_80118B04(HSD_GObj* gobj);
void lbl_80118D60(HSD_GObj* gobj);
void lbl_80118DF8(HSD_GObj* gobj);
void lbl_80118EF0(HSD_GObj* gobj);
void lbl_80118F80(HSD_GObj* gobj);
void lbl_80118F84(HSD_GObj* gobj);
void lbl_80118F88(HSD_GObj* gobj);
void lbl_80118F8C(HSD_GObj* gobj);
void lbl_80118F90(HSD_GObj* gobj);
void lbl_80118F94(HSD_GObj* gobj);
void lbl_80118F98(HSD_GObj* gobj);
void lbl_80118F9C(HSD_GObj* gobj);
void lbl_80118FA0(HSD_GObj* gobj);
void lbl_80118FA4(HSD_GObj* gobj);
void lbl_80118FDC(HSD_GObj* gobj);
void lbl_80118FFC(HSD_GObj* gobj);
void lbl_8011901C(HSD_GObj* gobj);
void lbl_80119134(HSD_GObj* gobj);
void lbl_80119194(HSD_GObj* gobj);
void lbl_801191F4(HSD_GObj* gobj);
void lbl_80119254(HSD_GObj* gobj);
void lbl_80119410(HSD_GObj* gobj);
void lbl_80119460(HSD_GObj* gobj);
void lbl_801194CC(HSD_GObj* gobj);
void lbl_80119538(HSD_GObj* gobj);
void lbl_801195A4(HSD_GObj* gobj);
void lbl_80119798(HSD_GObj* gobj);
void lbl_80119804(HSD_GObj* gobj);
void lbl_80119870(HSD_GObj* gobj);
void lbl_801198DC(HSD_GObj* gobj);
void lbl_80119D58(HSD_GObj* gobj);
void func_80119E14(HSD_GObj* gobj);
void func_80119E90(HSD_GObj* gobj);
void lbl_8011A0E0(HSD_GObj* gobj);
void lbl_8011A0E4(HSD_GObj* gobj);
void lbl_8011A0E8(HSD_GObj* gobj);
void lbl_8011A108(HSD_GObj* gobj);
void lbl_8011A168(HSD_GObj* gobj);
void func_8011A1E0(HSD_GObj* gobj);
void func_8011A240(HSD_GObj* gobj);
void lbl_8011A2A8(HSD_GObj* gobj);
void lbl_8011A370(HSD_GObj* gobj);
void lbl_8011A438(HSD_GObj* gobj);
void lbl_8011A43C(HSD_GObj* gobj);
void lbl_8011A440(HSD_GObj* gobj);
void lbl_8011A474(HSD_GObj* gobj);
void lbl_8011A4E8(HSD_GObj* gobj);
void lbl_8011A524(HSD_GObj* gobj);
void func_8011A560(HSD_GObj* gobj);
void func_8011A5D4(HSD_GObj* gobj);
void func_8011A650(HSD_GObj* gobj);
void func_8011A6A8(HSD_GObj* gobj);
void lbl_8011A700(HSD_GObj* gobj);
void lbl_8011A810(HSD_GObj* gobj);
void lbl_8011A920(HSD_GObj* gobj);
void lbl_8011A924(HSD_GObj* gobj);
void lbl_8011A928(HSD_GObj* gobj);
void lbl_8011A95C(HSD_GObj* gobj);
void lbl_8011A9D0(HSD_GObj* gobj);
void lbl_8011AA0C(HSD_GObj* gobj);
void func_8011AA48(HSD_GObj* gobj);
void func_8011AAA8(HSD_GObj* gobj);
BOOL func_8011AB10(HSD_GObj* gobj);
void lbl_8011ABF8(HSD_GObj* gobj);
void lbl_8011ADC8(HSD_GObj* gobj);
void lbl_8011AEE0(HSD_GObj* gobj);
void lbl_8011AEE4(HSD_GObj* gobj);
void lbl_8011AEE8(HSD_GObj* gobj);
void lbl_8011AF1C(HSD_GObj* gobj);
void lbl_8011AF90(HSD_GObj* gobj);
void lbl_8011AFCC(HSD_GObj* gobj);
void func_8011B008(HSD_GObj* gobj);
void func_8011B07C(HSD_GObj* gobj);
void func_8011B0F8(HSD_GObj* gobj);
void lbl_8011B25C(HSD_GObj* gobj);
void lbl_8011B2A0(HSD_GObj* gobj);
void lbl_8011B2E4(HSD_GObj* gobj);
void lbl_8011B2E8(HSD_GObj* gobj);
void lbl_8011B2EC(HSD_GObj* gobj);
void lbl_8011B30C(HSD_GObj* gobj);
void lbl_8011B36C(HSD_GObj* gobj);
void lbl_8011B3A8(HSD_GObj* gobj);
void func_8011B3E4(HSD_GObj* gobj);
void func_8011B444(HSD_GObj* gobj);
void func_8011B4AC(HSD_GObj* gobj);
void func_8011B4E4(HSD_GObj* gobj);

#endif
