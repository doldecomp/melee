#ifndef _ftfox_h_
#define _ftfox_h_

#include "melee/ft/ftcommon.h"
#include "melee/lb/lbvector.h"

#include <melee/ft/fighter.h>
#include <melee/it/item.h>
#include <melee/it/itkind.h>
#include <common_structs.h>

#define FTFOX_APPEALS_ATTACKID 0x72

typedef enum ftFoxAction {

    AS_FTCOMMON = 340,
    AS_FOX_SPECIALN_START,
    AS_FOX_SPECIALN_LOOP,
    AS_FOX_SPECIALN_END,
    AS_FOX_SPECIALAIRN_START,
    AS_FOX_SPECIALAIRN_LOOP,
    AS_FOX_SPECIALAIRN_END,
    AS_FOX_SPECIALS_START,
    AS_FOX_SPECIALS,
    AS_FOX_SPECIALS_END,
    AS_FOX_SPECIALAIRS_START,
    AS_FOX_SPECIALAIRS,
    AS_FOX_SPECIALAIRS_END,

} ftFoxAction;

typedef struct _ftFoxAttributes {

    // NEUTRAL SPECIAL - BLASTER //

    f32 x0_FOX_BLASTER_UNK1;
    f32 x4_FOX_BLASTER_UNK2;
    f32 x8_FOX_BLASTER_UNK3;
    f32 xC_FOX_BLASTER_UNK4;
    f32 x10_FOX_BLASTER_ANGLE; // Angle at which Blaster shots are fired
    f32 x14_FOX_BLASTER_VEL; // Velocity at which Blaster shots are fired
    f32 x18_FOX_BLASTER_LANDING_LAG;
    s32 x1C_FOX_BLASTER_SHOT_ITKIND;
    s32 x20_FOX_BLASTER_GUN_ITKIND;

    // SIDE SPECIAL - FOX ILLUSION / FALCO PHANTASM //

    f32 x24_FOX_ILLUSION_GRAVITY_DELAY; // Frames required to pass before gravity is applied
    f32 x28_FOX_ILLUSION_GROUND_VEL_X; // Horizontal velocity?
    f32 x2C_FOX_ILLUSION_UNK1;
    f32 x30_FOX_ILLUSION_UNK2;
    f32 x34_FOX_ILLUSION_UNK3;
    f32 x38_FOX_ILLUSION_GROUND_FRICTION;
    f32 x3C_FOX_ILLUSION_AIR_VEL_X;
    f32 x40_FOX_ILLUSION_AIR_MUL_X;
    f32 x44_FOX_ILLUSION_FALL_ACCEL;
    f32 x48_FOX_ILLUSION_TERMINAL_VELOCITY;
    f32 x4C_FOX_ILLUSION_UNK4;
    f32 x50_FOX_ILLUSION_LANDING_LAG;

    // UP SPECIAL - FIREFOX / FIREBIRD //

    f32 x54_FOX_FIREFOX_GRAVITY_DELAY;
    f32 x58_FOX_FIREFOX_VEL_X; // Initial velocity
    f32 x5C_FOX_FIREFOX_AIR_MOMENTUM_PRESERVE_X; 
    f32 x60_FOX_FIREFOX_FALL_ACCEL;
    f32 x64_FOX_FIREFOX_DIRECTION_STICK_RANGE_MIN; // Minimum control stick range required for direction change
    f32 x68_FOX_FIREFOX_DURATION; // Amount of frames Firefox/Firebird travels
    f32 x6C_FOX_FIREFOX_UNK1;
    f32 x70_FOX_FIREFOX_AIR_MOMENTUM_END;
    f32 x74_FOX_FIREFOX_SPEED;
    f32 x78_FOX_FIREFOX_REVERSE_ACCEL; // ???
    f32 x7C_FOX_FIREFOX_GROUND_MOMENTUM_END;
    f32 x80_FOX_FIREFOX_UNK2;
    f32 x84_FOX_FIREFOX_BOUND_VEL_X; // Horizontal velocity of SpecialHiBound action state
    f32 x88_FOX_FIREFOX_FACING_STICK_RANGE_MIN; // Minimum control stick range required to change character's facing direction
    f32 x8C_FOX_FIREFOX_UNK3;
    f32 x90_FOX_FIREFOX_LANDING_LAG;
    f32 x94_FOX_FIREFOX_BOUND_LANDING_LAG;
    
    // DOWN SPECIAL - REFLECTOR //

    f32 x98_FOX_REFLECTOR_RELEASE_LAG; // Auto lag frames after initializing Reflector if B is not being held. Reflector is immediately released with no lag once these frames have passed.
    f32 x9C_FOX_REFLECTOR_TURN_FRAMES; // Amount of turn frames for changing Reflector direction
    f32 xA0_FOX_REFLECTOR_UNK1;
    s32 xA4_FOX_REFLECTOR_GRAVITY_DELAY;
    f32 xA8_FOX_REFLECTOR_MOMENTUM_PRESERVE_X;
    f32 xAC_FOX_REFLECTOR_FALL_ACCEL;
    ReflectDesc xB0_FOX_REFLECTOR_REFLECTION;

} ftFoxAttributes;

// Fox & Falco Functions //

BOOL func_800E5534(HSD_GObj* gobj);
void ftFox_OnDeath(HSD_GObj* gobj);
void func_800E5588(HSD_GObj* gobj);
void ftFox_OnItemPickup(HSD_GObj* gobj, BOOL arg1);
void ftFox_OnItemInvisible(HSD_GObj* gobj);
void ftFox_OnItemVisible(HSD_GObj* gobj);
void ftFox_OnItemDrop(HSD_GObj* gobj, BOOL arg1);

// Special Taunt (AppealS)

BOOL ftFox_AppealS_CheckIfUsed(Fighter* fp);
BOOL ftFox_AppealS_CheckInput(HSD_GObj* fighter_gobj);
void ftFox_AppealS_Action(HSD_GObj* fighter_gobj);
void ftFox_AppealS_Anim(HSD_GObj* fighter_gobj);
void ftFox_AppealS_IASA(HSD_GObj* fighter_gobj);
void ftFox_AppealS_Phys(HSD_GObj* fighter_gobj);
void ftFox_AppealS_Coll(HSD_GObj* fighter_gobj);
void ftFox_AppealS_OnTakeDamage(HSD_GObj* fighter_gobj);

// Neutral Special - Blaster (SpecialN)

void ftFox_FtGetHoldJoint(HSD_GObj* fighter_gobj, Vec3* pos);
void ftFox_ItGetHoldJoint(HSD_GObj* fighter_gobj, Vec3* pos);
void ftFox_SpecialN_OnChangeAction(HSD_GObj* fighter_gobj);
BOOL ftFox_CheckRemoveBlaster(HSD_GObj* fighter_gobj);
s32 ftFox_GetBlasterAction(HSD_GObj* fighter_gobj);
BOOL ftFox_CheckBlasterAction(HSD_GObj* fighter_gobj);
void ftFox_ClearBlaster(HSD_GObj* fighter_gobj);
void ftFox_RemoveBlaster(HSD_GObj* fighter_gobj);
void ftFox_CreateBlasterShot(HSD_GObj* fighter_gobj);
void ftFox_SpecialN_StartAction(HSD_GObj* fighter_gobj);
void ftFox_SpecialAirN_StartAction(HSD_GObj* fighter_gobj);
void ftFox_SpecialNStart_Anim(HSD_GObj* fighter_gobj);
void ftFox_SpecialNLoop_Anim(HSD_GObj* fighter_gobj);
void ftFox_SpecialNEnd_Anim(HSD_GObj* fighter_gobj);
void ftFox_SpecialAirNStart_Anim(HSD_GObj* fighter_gobj);
void ftFox_SpecialAirNLoop_Anim(HSD_GObj* fighter_gobj);
void ftFox_SpecialAirNEnd_Anim(HSD_GObj* fighter_gobj);
void ftFox_SpecialNStart_IASA(HSD_GObj* fighter_gobj);
void ftFox_SpecialNLoop_IASA(HSD_GObj* fighter_gobj);
void ftFox_SpecialNEnd_IASA(HSD_GObj* fighter_gobj);
void ftFox_SpecialAirNStart_IASA(HSD_GObj* fighter_gobj);
void ftFox_SpecialAirNLoop_IASA(HSD_GObj* fighter_gobj);
void ftFox_SpecialAirNEnd_IASA(HSD_GObj* fighter_gobj);
void ftFox_SpecialNStart_Phys(HSD_GObj* fighter_gobj);
void ftFox_SpecialNLoop_Phys(HSD_GObj* fighter_gobj);
void ftFox_SpecialNEnd_Phys(HSD_GObj* fighter_gobj);
void ftFox_SpecialAirNStart_Phys(HSD_GObj* fighter_gobj);
void ftFox_SpecialAirNLoop_Phys(HSD_GObj* fighter_gobj);
void ftFox_SpecialAirNEnd_Phys(HSD_GObj* fighter_gobj);
void ftFox_SpecialNStart_Coll(HSD_GObj* fighter_gobj);
void ftFox_SpecialNLoop_Coll(HSD_GObj* fighter_gobj);
void ftFox_SpecialNEnd_Coll(HSD_GObj* fighter_gobj);
void ftFox_SpecialAirNStart_Coll(HSD_GObj* fighter_gobj);
void ftFox_SpecialAirNLoop_Coll(HSD_GObj* fighter_gobj);
void ftFox_SpecialAirNEnd_Coll(HSD_GObj* fighter_gobj);

// Throws (ThrowB/ThrowHi/ThrowL) //

void ftFox_Throw_Anim(HSD_GObj* fighter_gobj);

#endif
