#ifndef _ftness_h_
#define _ftness_h_

#include <global.h>

#include <dolphin/types.h>

#include "sysdolphin/baselib/gobj.h"

#include "melee/ft/fighter.h"

typedef struct _ftNessAttributes {
    f32 x0;
    f32 x4;
    f32 x8;
    f32 xC;
    u8 data[0x94 - 0x10];
    f32 unk94;
    u8 data2[0xD9 - 0x98];
} ftNessAttributes;

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
void func_8011B0F8(HSD_GObj* gobj);

typedef struct NessAttr
{
	//Neutral B
	u32 PKFLASH_TIMER1_MINCHARGEFRAMES;
	u32 PKFLASH_TIMER2_LOOPFRAMES;
	u32 FALLING_ACCELERATION_DELAY;
	u32 RELEASE_UNK;
	f32 UNK1;
	f32 FALL_ACCELERATION;
	f32 UNK2;
	f32 LANDING_TOGGLE;//If set to 0, Ness does not enter freefall after aerial PK Flash, but loses his double jump.
	//Side B
	f32 AERIAL_LAUNCH_TRAJECTORY;//Radians
	f32 AERIAL_VELOCITY;
	f32 GROUNDED_LAUNCH_TRAJECTORY;
	f32 GROUNDED_VELOCITY;
	f32 PKFIRE_SPAWN_X;
	f32 PKFIRE_SPAWN_Y;
	f32 LANDING_LAG;
	//Up B - Control
	f32 PK_THUNDER_UNK1;
	u32 LOOP_VARIABLE;
	u32 FRAMES_TO_LOOP_AFTER_HIT;
	u32 FALLING_ACCELERATIO_DELAY;
	f32 PK_THUNDER_UNK2;
	f32 PK_THUNDER_FALLING_ACCELERATION;
	//Up B - PK Thunder 2
	f32 PK_THUNDER_2_MOMENTUM;
	f32 PK_THUNDER_2_UNK1;
	f32 PK_THUNDER_2_DECELERATION_RATE;
	f32 PK_THUNDER_2_KNOCKDOWN_ANGLE;//Angle to determine whether to enter PK Thunder 2 or knockdown state (Ground Only)
	f32 PK_THUNDER_2_WALLHUG_ANGLE;//Surface angle to determine whether PK Thunder 2 wallhugs or bounces
	f32 PK_THUNDER_2_UNK3;
	f32 PK_THUNDER_2_FREEFALL_ANIM_BLEND;
	f32 PK_THUNDER_2_LANDING_LAG;
	//DownB
	f32 COOLDOWN_AFTER_RELEASE;
	f32 PSI_MAGNET_UNK1;//Note: Reminiscent of Fox and Falco's Reflector turn duration attribute?
	f32 PSI_MAGNET_UNK2;//Note: Reminiscent of Fox and Falco's Reflector Unk1 attribute?
	f32 PSI_MAGNET_UNK3;
	f32 PSI_MAGNET_FRAMES_BEFORE_GRAVITY;
	f32 PSI_MAGNET_MOMENTUM_PRESERVATION;
	f32 PSI_MAGNET_FALL_ACCELERATION;
	f32 PSI_MAGNET_UNK6;
	f32 PSI_MAGNET_HEALING_MULTIPLIER;
	f32 PSI_MAGNET_ABSORPTION_BUBBLE_BONE_ID;
	f32 PSI_MAGNET_ABSORPTION_BUBBLE_OFFSET_X;
	f32 PSI_MAGNET_ABSORPTION_BUBBLE_OFFSET_Y;
	f32 PSI_MAGNET_ABSORPTION_BUBBLE_OFFSET_Z;
	f32 PSI_MAGNET_ABSORPTION_BUBBLE_SIZE;
	//Yo-yo - May be able to remove
	f32 SMASH_CHARGE_DURATION;
	f32 SMASH_CHARGE_DAMAGE_MULTIPLIER;
	f32 SMASH_CHARGE_REHIT_RATE;
	//Baseball Bat - May be able to remove
	u32 REFLECTION_BUBBLE_BONE_ID;
	u32 MAXIMUM_DAMAGE_REFLECTABLE;
	f32 REFLECTION_BUBBLE_POSITION_X;
	f32 REFLECTION_BUBBLE_POSITION_Y;
	f32 REFLECTION_BUBBLE_POSITION_Z;
	f32 REFLECTION_BUBBLE_SIZE;
	f32 REFLECTION_DAMAGE_MULTIPLIER;
	f32 REFLECTED_PROJECTILE_SPEED_MULTIPLIER;
	u32 REFLECTOR_BEHAVIOR;
}NessAttr;

#endif
