#ifndef _ftness_h_
#define _ftness_h_

#include <global.h>

#include <dolphin/types.h>

#include "sysdolphin/baselib/gobj.h"

#include "melee/ft/fighter.h"

#include "melee/it/item.h"

// Ness functions // 

void ftNess_OnDeath(HSD_GObj* gobj, s32 arg1);
void ftNess_OnLoad(HSD_GObj* gobj);
void func_801148F8(HSD_GObj* gobj);
void func_8011493C(HSD_GObj* gobj);
f32 func_8011495C(Fighter* ft);
void func_80114968(HSD_GObj* gobj, s32 arg1);
void func_80114A48(HSD_GObj* gobj);
void func_80114A90(HSD_GObj* gobj);
void func_80114AD8(HSD_GObj* gobj, s32 arg1);
void func_80114B2C(HSD_GObj* gobj);
void func_80114B6C(HSD_GObj* gobj);
void func_80114BF4(HSD_GObj* gobj);
s32 func_80114CC0(HSD_GObj* gobj);
void func_80114CF4(HSD_GObj* gobj);
void func_80114D34(HSD_GObj* gobj);
void lbl_80114D50(HSD_GObj* gobj);
void lbl_80114E04(HSD_GObj* gobj);
void lbl_80114E64(HSD_GObj* gobj);
void lbl_80114E98(HSD_GObj* gobj);
void lbl_80114EB8(HSD_GObj* gobj);
void func_80114F0C(HSD_GObj* gobj);
void func_80114F70(f32 unk_float, HSD_GObj* gobj);
s32 func_80114FF8(HSD_GObj* gobj, Vec3* ECBUnk, Vec3* ECBUnk2, f32 float_unk);
void func_80115114(HSD_GObj* gobj, Point3d* arg1);
void func_801151EC(HSD_GObj* gobj);
void func_801152D0(HSD_GObj* gobj, f32 arg8);
s32 func_80115404(HSD_GObj* gobj);
void func_80115534(HSD_GObj* gobj);
void func_8011556C(HSD_GObj* gobj);
void func_80115680(HSD_GObj* gobj);
s32 func_80115784(HSD_GObj* gobj);
void func_8011599C(HSD_GObj* gobj);
void func_80115A08(HSD_GObj* gobj);
void func_80115AC4(HSD_GObj* gobj);
void func_80115AF8(HSD_GObj* gobj);
void lbl_80115B50(HSD_GObj* gobj);
void func_80115B80(HSD_GObj* gobj);
void func_80115BB0(HSD_GObj* gobj);
void lbl_80115C74(HSD_GObj* gobj);
void lbl_80115C9C(HSD_GObj* gobj);
void lbl_80115E74(HSD_GObj* gobj);
void lbl_80115EB8(HSD_GObj* gobj);
void lbl_80115F14(HSD_GObj* gobj);
void lbl_80115F88(HSD_GObj* gobj);
void lbl_801160B4(HSD_GObj* gobj);
void lbl_801160E4(HSD_GObj* gobj);
void lbl_80116104(HSD_GObj* gobj);
void func_80116178(HSD_GObj* gobj);
void lbl_8011620C(HSD_GObj* gobj);
void lbl_801162B0(HSD_GObj* gobj);
void lbl_801162E0(HSD_GObj* gobj);
void lbl_80116420(HSD_GObj* gobj);
void func_80116494(HSD_GObj* gobj);
void func_8011B0F8(HSD_GObj* gobj);

typedef struct ftNessAttributes
{
	//Neutral B
	u32 x0_PKFLASH_TIMER1_MINCHARGEFRAMES;
	u32 x4_PKFLASH_TIMER2_LOOPFRAMES;
	u32 x8_FALLING_ACCELERATION_DELAY;
	u32 xC_RELEASE_UNK;
	f32 x10_UNK1;
	f32 x14_FALL_ACCELERATION;
	f32 x18_UNK2;
	f32 x1C_LANDING_LAG;//If set to 0, Ness does not enter freefall after aerial PK Flash, but loses his double jump.
	//Side B
	f32 x20_AERIAL_LAUNCH_TRAJECTORY;//Radians
	f32 x24_AERIAL_VELOCITY;
	f32 x28_GROUNDED_LAUNCH_TRAJECTORY;
	f32 x2C_GROUNDED_VELOCITY;
	f32 x30_PKFIRE_SPAWN_X;
	f32 x34_PKFIRE_SPAWN_Y;
	f32 x38_LANDING_LAG;
	//Up B - Control
	f32 x3C_PK_THUNDER_UNK1;
	u32 x40_LOOP_VARIABLE;
	u32 x44_FRAMES_TO_LOOP_AFTER_HIT;
	u32 x48_FALLING_ACCELERATION_DELAY;
	f32 x4C_PK_THUNDER_UNK2;
	f32 x50_PK_THUNDER_FALLING_ACCELERATION;
	//Up B - PK Thunder 2
	f32 x54_PK_THUNDER_2_MOMENTUM;
	f32 x58_PK_THUNDER_2_UNK1;
	f32 x5C_PK_THUNDER_2_DECELERATION_RATE;
	f32 x60_PK_THUNDER_2_KNOCKDOWN_ANGLE;//Angle to determine whether to enter PK Thunder 2 or knockdown state (Ground Only)
	f32 x64_PK_THUNDER_2_WALLHUG_ANGLE;//Surface angle to determine whether PK Thunder 2 wallhugs or bounces
	f32 x68_PK_THUNDER_2_UNK3;
	f32 x6C_PK_THUNDER_2_FREEFALL_ANIM_BLEND;
	f32 x70_PK_THUNDER_2_LANDING_LAG;
	//DownB
	f32 x74_COOLDOWN_AFTER_RELEASE;
	f32 x78_PSI_MAGNET_UNK1;//Note: Reminiscent of Fox and Falco's Reflector turn duration attribute?
	f32 x7C_PSI_MAGNET_UNK2;//Note: Reminiscent of Fox and Falco's Reflector Unk1 attribute?
	f32 x80_PSI_MAGNET_UNK3;
	f32 x84_PSI_MAGNET_FRAMES_BEFORE_GRAVITY;
	f32 x88_PSI_MAGNET_MOMENTUM_PRESERVATION;
	f32 x8C_PSI_MAGNET_FALL_ACCELERATION;
	f32 x90_PSI_MAGNET_UNK6;
	f32 x94_PSI_MAGNET_HEALING_MULTIPLIER;
	f32 x98_PSI_MAGNET_ABSORPTION_BUBBLE_BONE_ID;
	f32 x9C_PSI_MAGNET_ABSORPTION_BUBBLE_OFFSET_X;
	f32 xA0_PSI_MAGNET_ABSORPTION_BUBBLE_OFFSET_Y;
	f32 xA4_PSI_MAGNET_ABSORPTION_BUBBLE_OFFSET_Z;
	f32 xA8_PSI_MAGNET_ABSORPTION_BUBBLE_SIZE;
	//Yo-yo
	f32 xAC_SMASH_CHARGE_DURATION;	// Amount of frames Yo-Yo can be charged //
	f32 xB0_SMASH_CHARGE_DAMAGE_MULTIPLIER;	// Charged Yo-Yo damage multiplier; 350 by default, identical to the Smash Charge standard //
	f32 xB4_SMASH_CHARGE_REHIT_RATE; // Amount of frames needed for the Yo-Yo to hit again after colliding with a hurtbox //
	//Baseball Bat
	u32 xB8_REFLECTION_BUBBLE_BONE_ID;
	u32 xBC_MAXIMUM_DAMAGE_REFLECTABLE;
	f32 xC0_REFLECTION_BUBBLE_POSITION_X;
	f32 xC4_REFLECTION_BUBBLE_POSITION_Y;
	f32 xC8_REFLECTION_BUBBLE_POSITION_Z;
	f32 xCC_REFLECTION_BUBBLE_SIZE;
	f32 xD0_REFLECTION_DAMAGE_MULTIPLIER;
	f32 xD4_REFLECTED_PROJECTILE_SPEED_MULTIPLIER;
	u32 xD8_REFLECTOR_BEHAVIOR;
}ftNessAttributes;

#endif
