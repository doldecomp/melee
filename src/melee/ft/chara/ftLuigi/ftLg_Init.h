#ifndef _ftluigi_h_
#define _ftluigi_h_

#include "it/forward.h"

#include "ft/fighter.h"
#include "ft/ftcommon.h"
#include "it/item.h"
#include "lb/lbvector.h"

#include <common_structs.h>

extern MotionState ftLg_Init_MotionStateTable[];
extern MotionState ftLg_Init_UnkMotionStates0[];
extern char ftLg_Init_DatFilename[];
extern char ftLg_Init_DataName[];
extern Fighter_CostumeStrings ftLg_Init_CostumeStrings[];
extern char ftLg_Init_AnimDatFilename[];
extern Fighter_DemoStrings ftLg_Init_DemoMotionFilenames;

// Luigi Functions

// Netural Special - Fireball (SpecialN)

void ftLg_SpecialN_Enter(HSD_GObj* gobj);
void ftLg_SpecialAirN_Enter(HSD_GObj* gobj);
void ftLg_SpecialN_Anim(HSD_GObj* gobj);
void ftLg_SpecialAirN_Anim(HSD_GObj* gobj);
void ftLg_SpecialN_IASA(HSD_GObj* gobj);
void ftLg_SpecialAirN_IASA(HSD_GObj* gobj);
void ftLg_SpecialN_Phys(HSD_GObj* gobj);
void ftLg_SpecialAirN_Phys(HSD_GObj* gobj);
void ftLg_SpecialN_Coll(HSD_GObj* gobj);
void ftLg_SpecialAirN_Coll(HSD_GObj* gobj);
void ftLg_SpecialN_FireSpawn(HSD_GObj* gobj);

// Side Special - Green Missile (SpecialS)

void ftLg_SpecialS_SetGFX(HSD_GObj* gobj);
void ftLg_SpecialS_SetVars(HSD_GObj* gobj);
void ftLg_SpecialS_Enter(HSD_GObj* gobj);
void ftLg_SpecialAirS_Enter(HSD_GObj* gobj);
void ftLg_SpecialS_OnGiveDamage(HSD_GObj* gobj);
void ftLg_SpecialSStart_Anim(HSD_GObj* gobj);
void ftLg_SpecialAirSStart_Anim(HSD_GObj* gobj);
void ftLg_SpecialSStart_IASA(HSD_GObj* gobj);
void ftLg_SpecialAirSStart_IASA(HSD_GObj* gobj);
void ftLg_SpecialSStart_Phys(HSD_GObj* gobj);
void ftLg_SpecialAirSStart_Phys(HSD_GObj* gobj);
void ftLg_SpecialSStart_Coll(HSD_GObj* gobj);
void ftLg_SpecialAirSStart_Coll(HSD_GObj* gobj);
void ftLg_SpecialSStart_GroundToAir(HSD_GObj* gobj);
void ftLg_SpecialAirSStart_AirToGround(HSD_GObj* gobj);
void ftLg_SpecialSHold_Anim(HSD_GObj* gobj);
void ftLg_SpecialAirSHold_Anim(HSD_GObj* gobj);
void ftLg_SpecialSHold_IASA(HSD_GObj* gobj);
void ftLg_SpecialAirSHold_IASA(HSD_GObj* gobj);
void ftLg_SpecialSHold_Phys(HSD_GObj* gobj);
void ftLg_SpecialAirSHold_Phys(HSD_GObj* gobj);
void ftLg_SpecialSHold_Coll(HSD_GObj* gobj);
void ftLg_SpecialAirSHold_Coll(HSD_GObj* gobj);
void ftLg_SpecialSHold_GroundToAir(HSD_GObj* gobj);
void ftLg_SpecialAirSHold_AirToGround(HSD_GObj* gobj);
void ftLg_SpecialSHold_Enter(HSD_GObj* gobj);
void ftLg_SpecialAirSHold_Enter(HSD_GObj* gobj);
void ftLg_SpecialSLaunch_Anim(HSD_GObj* gobj);
void ftLg_SpecialAirSLaunch_Anim(HSD_GObj* gobj);
void ftLg_SpecialSLaunch_IASA(HSD_GObj* gobj);
void ftLg_SpecialAirSLaunch_IASA(HSD_GObj* gobj);
void ftLg_SpecialSLaunch_Phys(HSD_GObj* gobj);
void ftLg_SpecialAirSLaunch_Phys(HSD_GObj* gobj);
void ftLg_SpecialSLaunch_Coll(HSD_GObj* gobj);
void ftLg_SpecialAirSLaunch_Coll(HSD_GObj* gobj);
void ftLg_SpecialSLaunch_GroundToAir(HSD_GObj* gobj);
void ftLg_SpecialAirSLaunch_AirToGround(HSD_GObj* gobj);
void ftLg_SpecialSLaunch_Enter(HSD_GObj* gobj);
void ftLg_SpecialAirSLaunch_Enter(HSD_GObj* gobj);
void ftLg_SpecialSMisfire_Anim(HSD_GObj* gobj);
void ftLg_SpecialAirSMisfire_Anim(HSD_GObj* gobj);
void ftLg_SpecialSMisfire_IASA(HSD_GObj* gobj);
void ftLg_SpecialAirSMisfire_IASA(HSD_GObj* gobj);
void ftLg_SpecialSMisfire_Phys(HSD_GObj* gobj);
void ftLg_SpecialAirSMisfire_Phys(HSD_GObj* gobj);
void ftLg_SpecialSMisfire_Coll(HSD_GObj* gobj);
void ftLg_SpecialAirSMisfire_Coll(HSD_GObj* gobj);
void ftLg_SpecialSMisfire_GroundToAir(HSD_GObj* gobj);
void ftLg_SpecialAirSMisfire_AirToGround(HSD_GObj* gobj);
void ftLg_SpecialSMisfire_Enter(HSD_GObj* gobj);
void ftLg_SpecialAirSMisfire_Enter(HSD_GObj* gobj);
void ftLg_SpecialSFly_Anim(HSD_GObj* gobj);
void ftLg_SpecialAirSFly_Anim(HSD_GObj* gobj);
void ftLg_SpecialSFly_IASA(HSD_GObj* gobj);
void ftLg_SpecialAirSFly_IASA(HSD_GObj* gobj);
void ftLg_SpecialSFly_Phys(HSD_GObj* gobj);
void ftLg_SpecialAirSFly_Phys(HSD_GObj* gobj);
void ftLg_SpecialSFly_Coll(HSD_GObj* gobj);
void ftLg_SpecialAirSFly_Coll(HSD_GObj* gobj);
void ftLg_SpecialSFly_Enter(HSD_GObj* gobj);
void ftLg_SpecialSEnd_Anim(HSD_GObj* gobj);
void ftLg_SpecialAirSEnd_Anim(HSD_GObj* gobj);
void ftLg_SpecialSEnd_IASA(HSD_GObj* gobj);
void ftLg_SpecialAirSEnd_IASA(HSD_GObj* gobj);
void ftLg_SpecialSEnd_Phys(HSD_GObj* gobj);
void ftLg_SpecialAirSEnd_Phys(HSD_GObj* gobj);
void ftLg_SpecialSEnd_Coll(HSD_GObj* gobj);
void ftLg_SpecialAirSEnd_Coll(HSD_GObj* gobj);
void ftLg_SpecialSEnd_Enter(HSD_GObj* gobj);
void ftLg_SpecialAirSEnd_Enter(HSD_GObj* gobj);

// Up Special - Super Jump Punch (SpecialHi)

void ftLg_SpecialHi_Enter(HSD_GObj* gobj);
void ftLg_SpecialAirHi_Enter(HSD_GObj* gobj);
void ftLg_SpecialHi_Anim(HSD_GObj* gobj);
void ftLg_SpecialAirHi_Anim(HSD_GObj* gobj);
void ftLg_SpecialHi_IASA(HSD_GObj* gobj);
void ftLg_SpecialAirHi_IASA(HSD_GObj* gobj);
void ftLg_SpecialHi_Phys(HSD_GObj* gobj);
void ftLg_SpecialAirHi_Phys(HSD_GObj* gobj);
void ftLg_SpecialHi_CheckLanding(HSD_GObj* gobj);
void ftLg_SpecialHi_Coll(HSD_GObj* gobj);
void ftLg_SpecialAirHi_Coll(HSD_GObj* gobj);

// Down Special - Luigi Cyclone (SpecialLw)

void ftLg_SpecialLw_UpdateRot(HSD_GObj* gobj);
void ftLg_SpecialLw_Enter(HSD_GObj* gobj);
void ftLg_SpecialAirLw_Enter(HSD_GObj* gobj);
void ftLg_SpecialLw_Anim(HSD_GObj* gobj);
void ftLg_SpecialAirLw_Anim(HSD_GObj* gobj);
void ftLg_SpecialLw_IASA(HSD_GObj* gobj);
void ftLg_SpecialAirLw_IASA(HSD_GObj* gobj);
void ftLg_SpecialLw_Phys(HSD_GObj* gobj);
void ftLg_SpecialAirLw_Phys(HSD_GObj* gobj);
void ftLg_SpecialLw_Coll(HSD_GObj* gobj);
void ftLg_SpecialAirLw_Coll(HSD_GObj* gobj);

void ftLg_Init_OnLoad(HSD_GObj* gobj);
void ftLg_Init_OnItemPickup(HSD_GObj* gobj, bool bool);
void ftLg_Init_OnItemInvisible(HSD_GObj* gobj);
void ftLg_Init_OnItemVisible(HSD_GObj* gobj);
void ftLg_Init_OnItemDrop(HSD_GObj* gobj, bool bool1);
void ftLg_Init_LoadSpecialAttrs(HSD_GObj* gobj);
void ftLg_Init_OnKnockbackEnter(HSD_GObj* gobj);
void ftLg_Init_OnKnockbackExit(HSD_GObj* gobj);
void ftLg_Init_UnkDemoCallbacks0(s32 arg0, s32* arg1, s32* arg2);
void ftLg_Init_OnDeath(HSD_GObj* gobj);
char* ftLg_Init_GetMotionFileString(enum_t demoMotionArg);

#endif
