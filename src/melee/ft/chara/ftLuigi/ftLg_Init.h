#ifndef _ftluigi_h_
#define _ftluigi_h_

#include "it/forward.h"

#include "ft/fighter.h"
#include "ft/ftcommon.h"
#include "it/item.h"
#include "lb/lbvector.h"

#include <common_structs.h>

typedef struct _ftLuigiAttributes {
    // SIDE SPECIAL - GREEN MISSILE

    f32 x0_LUIGI_GREENMISSILE_UNK1;
    f32 x4_LUIGI_GREENMISSILE_SMASH;
    f32 x8_LUIGI_GREENMISSILE_CHARGE_RATE;
    f32 xC_LUIGI_GREENMISSILE_MAX_CHARGE_FRAMES;
    f32 x10_LUIGI_GREENMISSILE_DAMAGE_TILT;
    f32 x14_LUIGI_GREENMISSILE_DAMAGE_SLOPE; // (base damage + charge duration)
                                             // * this value?
    f32 x18_LUIGI_GREENMISSILE_TRACTION;
    f32 x1C_LUIGI_GREENMISSILE_UNK2;
    f32 x20_LUIGI_GREENMISSILE_FALLING_SPEED;
    f32 x24_LUIGI_GREENMISSILE_VEL_X;
    f32 x28_LUIGI_GREENMISSILE_MUL_X;
    f32 x2C_LUIGI_GREENMISSILE_VEL_Y;
    f32 x30_LUIGI_GREENMISSILE_MUL_Y;
    f32 x34_LUIGI_GREENMISSILE_GRAVITY_START;
    f32 x38_LUIGI_GREENMISSILE_FRICTION_END;
    f32 x3C_LUIGI_GREENMISSILE_X_DECEL;
    f32 x40_LUIGI_GREENMISSILE_GRAVITY_MUL;
    f32 x44_LUIGI_GREENMISSILE_MISFIRE_CHANCE; // 1.0f divided by this value
    f32 x48_LUIGI_GREENMISSILE_MISFIRE_VEL_X;
    f32 x4C_LUIGI_GREENMISSILE_MISFIRE_VEL_Y;

    // UP SPECIAL - SUPER JUMP PUNCH

    f32 x50_LUIGI_SUPERJUMP_FREEFALL_MOBILITY; // Multiplies Luigi's max
                                               // horionztal aerial mobility
    f32 x54_LUIGI_SUPERJUMP_LANDING_LAG;
    f32 x58_LUIGI_SUPERJUMP_REVERSE_STICK_RANGE;  // Minimum stick range
                                                  // required for turnaround
    f32 x5C_LUIGI_SUPERJUMP_MOMENTUM_STICK_RANGE; // Minimum stick range
                                                  // required for horionztal
                                                  // momentum?
    f32 x60_LUIGI_SUPERJUMP_ANGLE_DIFF;
    f32 x64_LUIGI_SUPERJUMP_VEL_X;
    f32 x68_LUIGI_SUPERJUMP_GRAVITY_START;
    f32 x6C_LUIGI_SUPERJUMP_VEL_Y;

    // DOWN SPECIAL - LUIGI CYCLONE

    f32 x70_LUIGI_CYCLONE_TAP_MOMENTUM; // Vertical momentum from (first?) B
                                        // button tap
    f32 x74_LUIGI_CYCLONE_MOMENTUM_X_GROUND;
    f32 x78_LUIGI_CYCLONE_MOMENTUM_X_AIR;
    f32 x7C_LUIGI_CYCLONE_MOMENTUM_X_MUL_GROUND;
    f32 x80_LUIGI_CYCLONE_MOMENTUM_X_MUL_AIR;
    f32 x84_LUIGI_CYCLONE_FRICTION_END;
    s32 x88_LUIGI_CYCLONE_UNK;
    f32 x8C_LUIGI_CYCLONE_TAP_Y_VEL_MAX;
    f32 x90_LUIGI_CYCLONE_TAP_GRAVITY;
    s32 x94_LUIGI_CYCLONE_LANDING_LAG;

} ftLuigiAttributes;

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
