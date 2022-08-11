#ifndef _ftMewTwo_h_
#define _ftMewTwo_h_

#include <global.h>

#include <dolphin/types.h>

#include "sysdolphin/baselib/gobj.h"

#include "melee/ft/fighter.h"

typedef enum ftMewtwoAction {

    AS_FTCOMMON = 340,
    AS_MEWTWO_SPECIALN_START,
    AS_MEWTWO_SPECIALN_LOOP,
    AS_MEWTWO_SPECIALN_FULL,
    AS_MEWTWO_SPECIALN_CANCEL,
    AS_MEWTWO_SPECIALN_END,
    AS_MEWTWO_SPECIALAIRN_START,
    AS_MEWTWO_SPECIALAIRN_LOOP,
    AS_MEWTWO_SPECIALAIRN_FULL,
    AS_MEWTWO_SPECIALAIRN_CANCEL,
    AS_MEWTWO_SPECIALAIRN_END,
    AS_MEWTWO_SPECIALS,
    AS_MEWTWO_SPECIALAIRS,
    AS_MEWTWO_SPECIALHI_START,
    AS_MEWTWO_SPECIALHI,
    AS_MEWTWO_SPECIALHI_LOST,
    AS_MEWTWO_SPECIALAIRHI_START,
    AS_MEWTWO_SPECIALAIRHI,
    AS_MEWTWO_SPECIALAIRHI_LOST,
    AS_MEWTWO_SPECIALLW,
    AS_MEWTWO_SPECIALAIRLW,

} ftMewtwoAction;

// Flags used by Mewtwo in Action State Change //

// SpecialHi/SpecialAirHi //

#define FTMEWTWO_SPECIALHI_COLL_FLAG FIGHTER_GFX_PRESERVE | FIGHTER_HIT_NOUPDATE | FIGHTER_MATANIM_NOUPDATE | FIGHTER_COLANIM_NOUPDATE | FIGHTER_CMD_UPDATE | FIGHTER_ITEMVIS_NOUPDATE | FIGHTER_SKIP_UNK_0x2222 | FIGHTER_MODELPART_VIS_NOUPDATE | FIGHTER_MODEL_FLAG_NOUPDATE | FIGHTER_UNK_0x2227

typedef struct _ftMewtwoAttributes {

    // NEUTRAL SPECIAL - SHADOW BALL (SpecialN/SpecialAirN) // 

    f32 x0_MEWTWO_SHADOWBALL_CHARGE_CYCLES; // Number of frames each iteration cycle lasts?
    f32 x4_MEWTWO_SHADOWBALL_GROUND_RECOIL_X;
    f32 x8_MEWTWO_SHADOWBALL_AIR_RECOIL_X;
    s32 xC_MEWTWO_SHADOWBALL_CHARGE_ITERATIONS; // Number of iterations required for full charge
    s32 x10_MEWTWO_SHADOWBALL_RELEASE_LAG;
    f32 x14_MEWTWO_SHADOWBALL_LANDING_LAG;

    // SIDE SPECIAL - CONFUSION (SpecialS/SpecialAirS) //

    f32 x18_MEWTWO_CONFUSION_AIR_BOOST;
    ReflectDesc x1C_MEWTWO_CONFUSION_REFLECTION;

    // UP SPECIAL - TELEPORT (SpecialHi/SpecialAirHi) //

    f32 x40_MEWTWO_TELEPORT_VEL_DIV_X;
    f32 x44_MEWTWO_TELEPORT_VEL_DIV_Y;
    f32 x48_MEWTWO_TELEPORT_GRAVITY;
    f32 x4C_MEWTWO_TELEPORT_TERMINAL_VELOCITY;
    s32 x50_MEWTWO_TELEPORT_DURATION;
    f32 x54_MEWTWO_TELEPORT_UNK2;
    f32 x58_MEWTWO_TELEPORT_STICK_RANGE_MIN;
    f32 x5C_MEWTWO_TELEPORT_MOMENTUM;
    f32 x60_MEWTWO_TELEPORT_MOMENTUM_ADD;
    f32 x64_MEWTWO_TELEPORT_DRIFT;
    s32 x68_MEWTWO_TELEPORT_ANGLE_CLAMP; // Clamp teleport travel if surface angle is greater than this valuei88iiiiiiiiii 
    f32 x6C_MEWTWO_TELEPORT_MOMENTUM_END_MUL;
    f32 x70_MEWTWO_TELEPORT_FREEFALL_MOBILITY;
    f32 x74_MEWTWO_TELEPORT_LANDING_LAG;

    // DOWN SPECIAL - DISABLE (SpecialLw/SpecialAirLw) //

    f32 x78_MEWTWO_DISABLE_TERMINAL_VELOCITY;
    f32 x7C_MEWTWO_DISABLE_VEL_Y_MUL;
    f32 x80_MEWTWO_DISABLE_OFFSET_X;
    f32 x84_MEWTWO_DISABLE_OFFSET_Y;

} ftMewtwoAttributes; 

// Mewtwo functions //

void ftMewtwo_OnDeath(HSD_GObj* gobj);

// Up Special - Teleport (SpecialHi/SpecialAirHi) //

void ftMewtwo_SpecialHi_CreateGFX(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialHi_SetStartGFX(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialHi_SetEndGFX(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialHi_StartAction(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialAirHi_StartAction(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialHiStart_Anim(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialAirHiStart_Anim(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialHiStart_IASA(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialAirHiStart_IASA(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialHiStart_Phys(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialAirHiStart_Phys(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialHiStart_Coll(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialAirHiStart_Coll(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialHiStart_GroundToAir(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialAirHiStart_AirToGround(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialHi_Anim(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialAirHi_Anim(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialHi_IASA(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialAirHi_IASA(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialHi_Phys(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialAirHi_Phys(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialHi_Coll(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialAirHi_Coll(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialHi_GroundToAir(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialAirHi_AirToGround(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialHi_Action(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialAirHi_Action(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialHiLost_Anim(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialAirHiLost_Anim(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialHiLost_IASA(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialAirHiLost_IASA(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialHiLost_Phys(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialAirHiLost_Phys(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialHiLost_Coll(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialAirHiLost_Coll(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialHiLost_GroundToAir(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialHiLost_Action(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialAirHiLost_Action(HSD_GObj* fighter_gobj);

#endif
