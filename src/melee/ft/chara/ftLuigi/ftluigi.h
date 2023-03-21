#ifndef _ftluigi_h_
#define _ftluigi_h_

#include "ft/fighter.h"
#include "ft/ftcommon.h"
#include "it/forward.h"
#include "it/item.h"
#include "lb/lbvector.h"

#include <common_structs.h>

typedef enum ftLuigiAction {
    AS_LUIGI_SPECIALN = ASID_MAX,
    AS_LUIGI_SPECIALAIRN,
    AS_LUIGI_SPECIALS_START,
    AS_LUIGI_SPECIALS_HOLD,
    AS_LUIGI_SPECIALS_FLY,
    AS_LUIGI_SPECIALS_END,
    AS_LUIGI_SPECIALS_LAUNCH,
    AS_LUIGI_SPECIALS_MISFIRE,
    AS_LUIGI_SPECIALAIRS_START,
    AS_LUIGI_SPECIALAIRS_HOLD,
    AS_LUIGI_SPECIALAIRS_FLY,
    AS_LUIGI_SPECIALAIRS_END,
    AS_LUIGI_SPECIALAIRS_LAUNCH,
    AS_LUIGI_SPECIALAIRS_MISFIRE,
    AS_LUIGI_SPECIALHI,
    AS_LUIGI_SPECIALAIRHI,
    AS_LUIGI_SPECIALLW,
    AS_LUIGI_SPECIALAIRLW,

} ftLuigiAction;

// Flags used by Luigi in Action State Change //

// SpecialN/SpecialAirN (Fireball)

#define FTLUIGI_SPECIALN_COLL_FLAG                                            \
    FtStateChange_UpdateCmd | FtStateChange_SkipUpdateColAnim

// SpecialS/SpecialAirS (Green Missile)

// Misfire

// SpecialLw (Luigi Cyclone)

#define FTLUIGI_SPECIALLW_FLAG                                                \
    FtStateChange_PreserveGfx | FtStateChange_SkipUpdateHit |                 \
        FtStateChange_SkipUpdateMatAnim | FtStateChange_UpdateCmd |           \
        FtStateChange_SkipUpdateColAnim | FtStateChange_SkipUpdateItemVis |   \
        FtStateChange_Unk_19 | FtStateChange_SkipUpdateModelPartVis |         \
        FtStateChange_SkipUpdateModelFlag | FtStateChange_Unk_27

typedef struct _ftLuigiAttributes {
    // SIDE SPECIAL - GREEN MISSILE //

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

    // UP SPECIAL - SUPER JUMP PUNCH //

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

    // DOWN SPECIAL - LUIGI CYCLONE //

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

extern ActionState as_table_luigi[];
extern ActionState lbl_803D0868[];
extern char lbl_803D08A8[];
extern char lbl_803D08B4[];
extern Fighter_CostumeStrings lbl_803D0AB4[];
extern char lbl_803D09E8[];
extern Fighter_DemoStrings lbl_803D0A64;

// Luigi Functions //

// Netural Special - Fireball (SpecialN) //

void ftLuigi_SpecialN_StartAction(HSD_GObj* gobj);
void ftLuigi_SpecialAirN_StartAction(HSD_GObj* gobj);
void ftLuigi_SpecialN_Anim(HSD_GObj* gobj);
void ftLuigi_SpecialAirN_Anim(HSD_GObj* gobj);
void ftLuigi_SpecialN_IASA(HSD_GObj* gobj);
void ftLuigi_SpecialAirN_IASA(HSD_GObj* gobj);
void ftLuigi_SpecialN_Phys(HSD_GObj* gobj);
void ftLuigi_SpecialAirN_Phys(HSD_GObj* gobj);
void ftLuigi_SpecialN_Coll(HSD_GObj* gobj);
void ftLuigi_SpecialAirN_Coll(HSD_GObj* gobj);
void ftLuigi_SpecialN_FireSpawn(HSD_GObj* gobj);

// Side Special - Green Missile (SpecialS) //

void ftLuigi_SpecialS_SetGFX(HSD_GObj* gobj);
void ftLuigi_SpecialS_SetVars(HSD_GObj* gobj);
void ftLuigi_SpecialS_StartAction(HSD_GObj* gobj);
void ftLuigi_SpecialAirS_StartAction(HSD_GObj* gobj);
void ftLuigi_SpecialS_OnGiveDamage(HSD_GObj* gobj);
void ftLuigi_SpecialSStart_Anim(HSD_GObj* gobj);
void ftLuigi_SpecialAirSStart_Anim(HSD_GObj* gobj);
void ftLuigi_SpecialSStart_IASA(HSD_GObj* gobj);
void ftLuigi_SpecialAirSStart_IASA(HSD_GObj* gobj);
void ftLuigi_SpecialSStart_Phys(HSD_GObj* gobj);
void ftLuigi_SpecialAirSStart_Phys(HSD_GObj* gobj);
void ftLuigi_SpecialSStart_Coll(HSD_GObj* gobj);
void ftLuigi_SpecialAirSStart_Coll(HSD_GObj* gobj);
void ftLuigi_SpecialSStart_GroundToAir(HSD_GObj* gobj);
void ftLuigi_SpecialAirSStart_AirToGround(HSD_GObj* gobj);
void ftLuigi_SpecialSHold_Anim(HSD_GObj* gobj);
void ftLuigi_SpecialAirSHold_Anim(HSD_GObj* gobj);
void ftLuigi_SpecialSHold_IASA(HSD_GObj* gobj);
void ftLuigi_SpecialAirSHold_IASA(HSD_GObj* gobj);
void ftLuigi_SpecialSHold_Phys(HSD_GObj* gobj);
void ftLuigi_SpecialAirSHold_Phys(HSD_GObj* gobj);
void ftLuigi_SpecialSHold_Coll(HSD_GObj* gobj);
void ftLuigi_SpecialAirSHold_Coll(HSD_GObj* gobj);
void ftLuigi_SpecialSHold_GroundToAir(HSD_GObj* gobj);
void ftLuigi_SpecialAirSHold_AirToGround(HSD_GObj* gobj);
void ftLuigi_SpecialSHold_Action(HSD_GObj* gobj);
void ftLuigi_SpecialAirSHold_Action(HSD_GObj* gobj);
void ftLuigi_SpecialSLaunch_Anim(HSD_GObj* gobj);
void ftLuigi_SpecialAirSLaunch_Anim(HSD_GObj* gobj);
void ftLuigi_SpecialSLaunch_IASA(HSD_GObj* gobj);
void ftLuigi_SpecialAirSLaunch_IASA(HSD_GObj* gobj);
void ftLuigi_SpecialSLaunch_Phys(HSD_GObj* gobj);
void ftLuigi_SpecialAirSLaunch_Phys(HSD_GObj* gobj);
void ftLuigi_SpecialSLaunch_Coll(HSD_GObj* gobj);
void ftLuigi_SpecialAirSLaunch_Coll(HSD_GObj* gobj);
void ftLuigi_SpecialSLaunch_GroundToAir(HSD_GObj* gobj);
void ftLuigi_SpecialAirSLaunch_AirToGround(HSD_GObj* gobj);
void ftLuigi_SpecialSLaunch_Action(HSD_GObj* gobj);
void ftLuigi_SpecialAirSLaunch_Action(HSD_GObj* gobj);
void ftLuigi_SpecialSMisfire_Anim(HSD_GObj* gobj);
void ftLuigi_SpecialAirSMisfire_Anim(HSD_GObj* gobj);
void ftLuigi_SpecialSMisfire_IASA(HSD_GObj* gobj);
void ftLuigi_SpecialAirSMisfire_IASA(HSD_GObj* gobj);
void ftLuigi_SpecialSMisfire_Phys(HSD_GObj* gobj);
void ftLuigi_SpecialAirSMisfire_Phys(HSD_GObj* gobj);
void ftLuigi_SpecialSMisfire_Coll(HSD_GObj* gobj);
void ftLuigi_SpecialAirSMisfire_Coll(HSD_GObj* gobj);
void ftLuigi_SpecialSMisfire_GroundToAir(HSD_GObj* gobj);
void ftLuigi_SpecialAirSMisfire_AirToGround(HSD_GObj* gobj);
void ftLuigi_SpecialSMisfire_Action(HSD_GObj* gobj);
void ftLuigi_SpecialAirSMisfire_Action(HSD_GObj* gobj);
void ftLuigi_SpecialSFly_Anim(HSD_GObj* gobj);
void ftLuigi_SpecialAirSFly_Anim(HSD_GObj* gobj);
void ftLuigi_SpecialSFly_IASA(HSD_GObj* gobj);
void ftLuigi_SpecialAirSFly_IASA(HSD_GObj* gobj);
void ftLuigi_SpecialSFly_Phys(HSD_GObj* gobj);
void ftLuigi_SpecialAirSFly_Phys(HSD_GObj* gobj);
void ftLuigi_SpecialSFly_Coll(HSD_GObj* gobj);
void ftLuigi_SpecialAirSFly_Coll(HSD_GObj* gobj);
void ftLuigi_SpecialSFly_Action(HSD_GObj* gobj);
void ftLuigi_SpecialSEnd_Anim(HSD_GObj* gobj);
void ftLuigi_SpecialAirSEnd_Anim(HSD_GObj* gobj);
void ftLuigi_SpecialSEnd_IASA(HSD_GObj* gobj);
void ftLuigi_SpecialAirSEnd_IASA(HSD_GObj* gobj);
void ftLuigi_SpecialSEnd_Phys(HSD_GObj* gobj);
void ftLuigi_SpecialAirSEnd_Phys(HSD_GObj* gobj);
void ftLuigi_SpecialSEnd_Coll(HSD_GObj* gobj);
void ftLuigi_SpecialAirSEnd_Coll(HSD_GObj* gobj);
void ftLuigi_SpecialSEnd_Action(HSD_GObj* gobj);
void ftLuigi_SpecialAirSEnd_Action(HSD_GObj* gobj);

// Up Special - Super Jump Punch (SpecialHi)

void ftLuigi_SpecialHi_StartAction(HSD_GObj* gobj);
void ftLuigi_SpecialAirHi_StartAction(HSD_GObj* gobj);
void ftLuigi_SpecialHi_Anim(HSD_GObj* gobj);
void ftLuigi_SpecialAirHi_Anim(HSD_GObj* gobj);
void ftLuigi_SpecialHi_IASA(HSD_GObj* gobj);
void ftLuigi_SpecialAirHi_IASA(HSD_GObj* gobj);
void ftLuigi_SpecialHi_Phys(HSD_GObj* gobj);
void ftLuigi_SpecialAirHi_Phys(HSD_GObj* gobj);
void ftLuigi_SpecialHi_CheckLanding(HSD_GObj* gobj);
void ftLuigi_SpecialHi_Coll(HSD_GObj* gobj);
void ftLuigi_SpecialAirHi_Coll(HSD_GObj* gobj);

// Down Special - Luigi Cyclone (SpecialLw)

void ftLuigi_SpecialLw_UpdateRot(HSD_GObj* gobj);
void ftLuigi_SpecialLw_StartAction(HSD_GObj* gobj);
void ftLuigi_SpecialAirLw_StartAction(HSD_GObj* gobj);
void ftLuigi_SpecialLw_Anim(HSD_GObj* gobj);
void ftLuigi_SpecialAirLw_Anim(HSD_GObj* gobj);
void ftLuigi_SpecialLw_IASA(HSD_GObj* gobj);
void ftLuigi_SpecialAirLw_IASA(HSD_GObj* gobj);
void ftLuigi_SpecialLw_Phys(HSD_GObj* gobj);
void ftLuigi_SpecialAirLw_Phys(HSD_GObj* gobj);
void ftLuigi_SpecialLw_Coll(HSD_GObj* gobj);
void ftLuigi_SpecialAirLw_Coll(HSD_GObj* gobj);

void ftLuigi_OnLoad(HSD_GObj* gobj);
void ftLuigi_OnItemPickup(HSD_GObj* gobj, bool bool);
void ftLuigi_OnItemInvisible(HSD_GObj* gobj);
void ftLuigi_OnItemVisible(HSD_GObj* gobj);
void ftLuigi_OnItemDrop(HSD_GObj* gobj, bool bool1);
void ftLuigi_LoadSpecialAttrs(HSD_GObj* gobj);
void ftLuigi_OnKnockbackEnter(HSD_GObj* gobj);
void ftLuigi_OnKnockbackExit(HSD_GObj* gobj);
void ftLuigi_8014260C(s32 arg0, s32* arg1, s32* arg2);
void ftLuigi_OnDeath(HSD_GObj* gobj);
char* ftLuigi_GetMotionFileString(enum_t demoMotionArg);

#endif
