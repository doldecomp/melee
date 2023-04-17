#ifndef _ftfox_h_
#define _ftfox_h_

#include "it/forward.h"

#include "ft/fighter.h"
#include "ft/ftcommon.h"
#include "it/item.h"
#include "lb/lbvector.h"

#include <common_structs.h>

#define FTFOX_APPEALS_ATTACKID 0x72

typedef enum ftFoxAction {
    MS_FOX_SPECIALN_START = ftCo_MS_Count,
    MS_FOX_SPECIALN_LOOP,
    MS_FOX_SPECIALN_END,
    MS_FOX_SPECIALAIRN_START,
    MS_FOX_SPECIALAIRN_LOOP,
    MS_FOX_SPECIALAIRN_END,
    MS_FOX_SPECIALS_START,
    MS_FOX_SPECIALS,
    MS_FOX_SPECIALS_END,
    MS_FOX_SPECIALAIRS_START,
    MS_FOX_SPECIALAIRS,
    MS_FOX_SPECIALAIRS_END,
    MS_FOX_SPECIALHI_HOLD,
    MS_FOX_SPECIALHI_HOLDAIR,
    MS_FOX_SPECIALHI,
    MS_FOX_SPECIALAIRHI,
    MS_FOX_SPECIALHI_LANDING,
    MS_FOX_SPECIALHI_FALL,
    MS_FOX_SPECIALHI_BOUND,
    MS_FOX_SPECIALLW_START,
    MS_FOX_SPECIALLW_LOOP,
    MS_FOX_SPECIALLW_HIT,
    MS_FOX_SPECIALLW_END,
    MS_FOX_SPECIALLW_TURN,
    MS_FOX_SPECIALAIRLW_START,
    MS_FOX_SPECIALAIRLW_LOOP,
    MS_FOX_SPECIALAIRLW_HIT,
    MS_FOX_SPECIALAIRLW_END,
    MS_FOX_SPECIALAIRLW_TURN,
    MS_FOX_APPEALS_START_R,
    MS_FOX_APPEALS_START_L,
    MS_FOX_APPEALS_R,
    MS_FOX_APPEALS_L,
    MS_FOX_APPEALS_END_R,
    MS_FOX_APPEALS_END_L,

} ftFoxAction;

// Flags used by Fox in Motion State Change

// SpecialHi (Firefox/Firebird)

#define FTFOX_SPECIALHI_COLL_FLAG                                             \
    FtStateChange_PreserveGfx | FtStateChange_SkipUpdateMatAnim |             \
        FtStateChange_UpdateCmd | FtStateChange_SkipUpdateColAnim |           \
        FtStateChange_SkipUpdateItemVis | FtStateChange_Unk_19 |              \
        FtStateChange_SkipUpdateModelPartVis |                                \
        FtStateChange_SkipUpdateModelFlag | FtStateChange_Unk_27

#define FTFOX_SPECIALLW_COLL_FLAG                                             \
    FtStateChange_PreserveGfx | FtStateChange_SkipUpdateMatAnim |             \
        FtStateChange_UpdateCmd | FtStateChange_SkipUpdateColAnim |           \
        FtStateChange_SkipUpdateItemVis | FtStateChange_Unk_19 |              \
        FtStateChange_SkipUpdateModelPartVis |                                \
        FtStateChange_SkipUpdateModelFlag | FtStateChange_Unk_27

#define FTFOX_SPECIALS_COLL_FLAG                                              \
    FtStateChange_SkipUpdateMatAnim | FtStateChange_SkipUpdateRumble |        \
        FtStateChange_UpdateCmd | FtStateChange_SkipUpdateColAnim |           \
        FtStateChange_SkipUpdateItemVis | FtStateChange_Unk_19 |              \
        FtStateChange_SkipUpdateModelPartVis |                                \
        FtStateChange_SkipUpdateModelFlag | FtStateChange_Unk_27

typedef struct _ftFoxAttributes {
    // NEUTRAL SPECIAL - BLASTER

    f32 x0_FOX_BLASTER_UNK1;
    f32 x4_FOX_BLASTER_UNK2;
    f32 x8_FOX_BLASTER_UNK3;
    f32 xC_FOX_BLASTER_UNK4;
    f32 x10_FOX_BLASTER_ANGLE; // Angle at which Blaster shots are fired
    f32 x14_FOX_BLASTER_VEL;   // Velocity at which Blaster shots are fired
    f32 x18_FOX_BLASTER_LANDING_LAG;
    s32 x1C_FOX_BLASTER_SHOT_ITKIND;
    s32 x20_FOX_BLASTER_GUN_ITKIND;

    // SIDE SPECIAL - FOX ILLUSION / FALCO PHANTASM

    f32 x24_FOX_ILLUSION_GRAVITY_DELAY; // Frames required to pass before
                                        // gravity is applied
    f32 x28_FOX_ILLUSION_GROUND_VEL_X;  // Horizontal velocity?
    f32 x2C_FOX_ILLUSION_UNK1;
    f32 x30_FOX_ILLUSION_UNK2;
    f32 x34_FOX_ILLUSION_GROUND_END_VEL_X;
    f32 x38_FOX_ILLUSION_GROUND_FRICTION;
    f32 x3C_FOX_ILLUSION_AIR_END_VEL_X;
    f32 x40_FOX_ILLUSION_AIR_MUL_X;
    f32 x44_FOX_ILLUSION_FALL_ACCEL;
    f32 x48_FOX_ILLUSION_TERMINAL_VELOCITY;
    f32 x4C_FOX_ILLUSION_FREEFALL_MOBILITY;
    f32 x50_FOX_ILLUSION_LANDING_LAG;

    // UP SPECIAL - FIREFOX / FIREBIRD

    f32 x54_FOX_FIREFOX_GRAVITY_DELAY;
    f32 x58_FOX_FIREFOX_VEL_X; // Initial velocity
    f32 x5C_FOX_FIREFOX_AIR_MOMENTUM_PRESERVE_X;
    f32 x60_FOX_FIREFOX_FALL_ACCEL;
    f32 x64_FOX_FIREFOX_DIRECTION_STICK_RANGE_MIN; // Minimum control stick
                                                   // range required for
                                                   // direction change
    f32 x68_FOX_FIREFOX_DURATION; // Amount of frames Firefox/Firebird travels
    s32 x6C_FOX_FIREFOX_BOUNCE_VAR;
    f32 x70_FOX_FIREFOX_DURATION_END;
    f32 x74_FOX_FIREFOX_SPEED;
    f32 x78_FOX_FIREFOX_REVERSE_ACCEL; // ???
    f32 x7C_FOX_FIREFOX_GROUND_MOMENTUM_END;
    f32 x80_FOX_FIREFOX_UNK2;
    f32 x84_FOX_FIREFOX_BOUND_VEL_X; // Horizontal velocity of SpecialHiBound
                                     // action state
    f32 x88_FOX_FIREFOX_FACING_STICK_RANGE_MIN; // Minimum control stick range
                                                // required to change
                                                // character's facing direction
    f32 x8C_FOX_FIREFOX_FREEFALL_MOBILITY;
    f32 x90_FOX_FIREFOX_LANDING_LAG;
    f32 x94_FOX_FIREFOX_BOUND_ANGLE;

    // DOWN SPECIAL - REFLECTOR

    f32 x98_FOX_REFLECTOR_RELEASE_LAG; // Auto lag frames after initializing
                                       // Reflector if B is not being held.
                                       // Reflector is immediately released
                                       // with no lag once these frames have
                                       // passed.
    f32 x9C_FOX_REFLECTOR_TURN_FRAMES; // Amount of turn frames for changing
                                       // Reflector direction
    f32 xA0_FOX_REFLECTOR_UNK1;
    s32 xA4_FOX_REFLECTOR_GRAVITY_DELAY;
    f32 xA8_FOX_REFLECTOR_MOMENTUM_PRESERVE_X;
    f32 xAC_FOX_REFLECTOR_FALL_ACCEL;
    ReflectDesc xB0_FOX_REFLECTOR_REFLECTION;

} ftFoxAttributes;

extern MotionState ftFx_Init_MotionStateTable[];
extern char ftFx_Init_DatFilename[];
extern char ftFx_Init_DataName[];
extern Fighter_CostumeStrings ftFx_Init_CostumeStrings[];
extern char ftFx_Init_AnimDatFilename[];
extern Fighter_DemoStrings ftFx_Init_DemoMotionFilenames;

// Fox & Falco Functions

bool ftFx_Init_800E5534(HSD_GObj* gobj);
void ftFx_Init_OnDeath(HSD_GObj* gobj);
void ftFx_Init_800E5588(HSD_GObj* gobj);
void ftFx_Init_OnItemPickup(HSD_GObj* gobj, bool arg1);
void ftFx_Init_OnItemInvisible(HSD_GObj* gobj);
void ftFx_Init_OnItemVisible(HSD_GObj* gobj);
void ftFx_Init_OnItemDrop(HSD_GObj* gobj, bool arg1);

// Special Taunt (AppealS)

/// Check if Special Taunt has already been performed
bool ftFx_AppealS_CheckIfUsed(Fighter* fp);

/// Check if Fox/Falco has pressed D-Pad Down
bool ftFx_AppealS_CheckInput(HSD_GObj* gobj);

/// Fox & Falco's Special Taunt Motion State handler
void ftFx_AppealS_Enter(HSD_GObj* gobj);

/// Fox & Falco's Special Taunt Start Animation callback
void ftFx_AppealS_Anim(HSD_GObj* gobj);

/// Fox & Falco's Special Taunt Start IASA callback
void ftFx_AppealS_IASA(HSD_GObj* gobj);

/// Fox & Falco's Special Taunt Physics callback
void ftFx_AppealS_Phys(HSD_GObj* gobj);

/// Fox & Falco's Special Taunt Collision callback
void ftFx_AppealS_Coll(HSD_GObj* gobj);

// Neutral Special - Blaster (SpecialN)

/// Get Fox/Falco's Item Hold Bone Position for Blaster GFX
void ftFx_SpecialN_FtGetHoldJoint(HSD_GObj* gobj, Vec3* pos);

/// Get Fox/Falco's Item Hold Bone Position for Blaster GFX again?
/// @remarks Used in Blaster's item code.
void ftFx_SpecialN_ItGetHoldJoint(HSD_GObj* gobj, Vec3* pos);

void ftFx_SpecialN_OnChangeAction(HSD_GObj* gobj);
bool ftFx_SpecialN_CheckRemoveBlaster(HSD_GObj* gobj);
s32 ftFx_SpecialN_GetBlasterAction(HSD_GObj* gobj);
bool ftFx_SpecialN_CheckBlasterAction(HSD_GObj* gobj);
void ftFx_SpecialN_ClearBlaster(HSD_GObj* gobj);
void ftFx_SpecialN_RemoveBlaster(HSD_GObj* gobj);
void ftFx_SpecialN_CreateBlasterShot(HSD_GObj* gobj);
void ftFx_SpecialN_Enter(HSD_GObj* gobj);
void ftFx_SpecialAirN_Enter(HSD_GObj* gobj);
void ftFx_SpecialNStart_Anim(HSD_GObj* gobj);
void ftFx_SpecialNLoop_Anim(HSD_GObj* gobj);
void ftFx_SpecialNEnd_Anim(HSD_GObj* gobj);
void ftFx_SpecialAirNStart_Anim(HSD_GObj* gobj);
void ftFx_SpecialAirNLoop_Anim(HSD_GObj* gobj);
void ftFx_SpecialAirNEnd_Anim(HSD_GObj* gobj);
void ftFx_SpecialNStart_IASA(HSD_GObj* gobj);
void ftFx_SpecialNLoop_IASA(HSD_GObj* gobj);
void ftFx_SpecialNEnd_IASA(HSD_GObj* gobj);
void ftFx_SpecialAirNStart_IASA(HSD_GObj* gobj);
void ftFx_SpecialAirNLoop_IASA(HSD_GObj* gobj);
void ftFx_SpecialAirNEnd_IASA(HSD_GObj* gobj);
void ftFx_SpecialNStart_Phys(HSD_GObj* gobj);
void ftFx_SpecialNLoop_Phys(HSD_GObj* gobj);
void ftFx_SpecialNEnd_Phys(HSD_GObj* gobj);
void ftFx_SpecialAirNStart_Phys(HSD_GObj* gobj);
void ftFx_SpecialAirNLoop_Phys(HSD_GObj* gobj);
void ftFx_SpecialAirNEnd_Phys(HSD_GObj* gobj);
void ftFx_SpecialNStart_Coll(HSD_GObj* gobj);
void ftFx_SpecialNLoop_Coll(HSD_GObj* gobj);
void ftFx_SpecialNEnd_Coll(HSD_GObj* gobj);
void ftFx_SpecialAirNStart_Coll(HSD_GObj* gobj);
void ftFx_SpecialAirNLoop_Coll(HSD_GObj* gobj);
void ftFx_SpecialAirNEnd_Coll(HSD_GObj* gobj);

// Throws (ThrowB/ThrowHi/ThrowL)

void ftFx_Throw_Anim(HSD_GObj* gobj);

// Up Special - Firefox (SpecialHi)

/// Create Firefox/Firebird Launch GFX
void ftFx_SpecialHi_CreateLaunchGFX(HSD_GObj* gobj);

/// Create Firefox/Firebird Charge GFX
void ftFx_SpecialHi_CreateChargeGFX(HSD_GObj* gobj);

/// Fox & Falco's grounded Firefox/Firebird Start Motion State handler
void ftFx_SpecialHi_Enter(HSD_GObj* gobj);

/// Fox & Falco's aerial Firefox/Firebird Start Motion State handler
void ftFx_SpecialAirHiStart_Enter(HSD_GObj* gobj);

void ftFox_SpecialHi_RotateModel(HSD_GObj* gobj);

/// Fox & Falco's grounded Firefox/Firebird Start Animation callback
void ftFx_SpecialHiHold_Anim(HSD_GObj* gobj);

/// Fox & Falco's aerial Firefox/Firebird Start Animation callback
void ftFx_SpecialHiHoldAir_Anim(HSD_GObj* gobj);

/// Fox & Falco's grounded Firefox/Firebird Start IASA callback
void ftFx_SpecialHiHold_IASA(HSD_GObj* gobj);

/// Fox & Falco's aerial Firefox/Firebird Start IASA callback
void ftFx_SpecialHiHoldAir_IASA(HSD_GObj* gobj);

/// Fox & Falco's grorunded Firefox/Firebird Start Physics callback
void ftFx_SpecialHiHold_Phys(HSD_GObj* gobj);

/// Fox & Falco's aerial Firefox/Firebird Start Physics callback
void ftFx_SpecialHiHoldAir_Phys(HSD_GObj* gobj);

/// Fox & Falco's grounded Firerfox/Firebird Start Collision callback
void ftFx_SpecialHiHold_Coll(HSD_GObj* gobj);

/// Fox & Falco's aerial Firefox/Firebird Start Collision callback
void ftFx_SpecialHiHoldAir_Coll(HSD_GObj* gobj);

/// Fox & Falco's ground -> air Firefox/Firebird Start Motion State handler
void ftFx_SpecialHiHold_GroundToAir(HSD_GObj* gobj);

/// Fox & Falco's air -> ground Firefox/Firebird Start Motion State handler
void ftFx_SpecialHiHoldAir_AirToGround(HSD_GObj* gobj);

/// Fox & Falco's grounded Firefox/Firebird Launch Animation callback
void ftFx_SpecialHi_Anim(HSD_GObj* gobj);

/// Fox & Falco's aerial Firefox/Firebird Launch Animation callback
void ftFx_SpecialAirHi_Anim(HSD_GObj* gobj);

/// Fox & Falco's grounded Firefox/Firebird Launch IASA callback
void ftFx_SpecialHi_IASA(HSD_GObj* gobj);

/// Fox & Falco's aerial Firerfox/Firebird Launch IASA callback
void ftFx_SpecialAirHi_IASA(HSD_GObj* gobj);

/// Fox & Falco's grounded Firefox/Firebird Launch Physics callback
void ftFx_SpecialHi_Phys(HSD_GObj* gobj);

/// Fox & Falco's aerial Firefox/Firebird Launch Physics callback
void ftFx_SpecialAirHi_Phys(HSD_GObj* gobj);

/// Fox & Falco's grounded Firefox/Firebird Launch Collision callback
void ftFx_SpecialHi_Coll(HSD_GObj* gobj);

/// Fox & Falco's aerial Firefox/Firebird Launch Collision callback
void ftFx_SpecialAirHi_Coll(HSD_GObj* gobj);

/// Fox & Falco's Firefox/Firebird Launch ground -> air Motion State handler
void ftFx_SpecialHi_GroundToAir(HSD_GObj* gobj);

/// Fox & Falco's grounded Firefox/Firebird Launch Motion State handler
void ftFx_SpecialAirHi_AirToGround(HSD_GObj* gobj);

void ftFx_SpecialAirHi_Enter(HSD_GObj* gobj);
void ftFx_SpecialHiLanding_Anim(HSD_GObj* gobj);
void ftFx_SpecialHiFall_Anim(HSD_GObj* gobj);
void ftFx_SpecialHiLanding_IASA(HSD_GObj* gobj);
void ftFx_SpecialHiFall_IASA(HSD_GObj* gobj);
void ftFx_SpecialHiLanding_Phys(HSD_GObj* gobj);
void ftFx_SpecialHiFall_Phys(HSD_GObj* gobj);
void ftFx_SpecialHiLanding_Coll(HSD_GObj* gobj);
void ftFx_SpecialHiFall_Coll(HSD_GObj* gobj);
void ftFx_SpecialHiFall_Enter(HSD_GObj* gobj);
void ftFx_SpecialHiFall_AirToGround(HSD_GObj* gobj);
void ftFx_SpecialHiLanding_GroundToAir(HSD_GObj* gobj);
void ftFx_SpecialHiBound_Anim(HSD_GObj* gobj);
void ftFx_SpecialHiBound_IASA(HSD_GObj* gobj);
void ftFx_SpecialHiBound_Phys(HSD_GObj* gobj);
void ftFx_SpecialHiBound_Coll(HSD_GObj* gobj);
void ftFx_SpecialHiBound_Enter(HSD_GObj* gobj);

// Down Special - Reflector (SpecialLw)

/// Create Reflector Loop GFX
void ftFx_SpecialLw_CreateLoopGFX(HSD_GObj* gobj);

void ftFx_SpecialLw_CreateStartGFX(HSD_GObj* gobj);

/// Create Reflector Deflect GFX
void ftFx_SpecialLw_CreateReflectGFX(HSD_GObj* gobj);

/// Fox & Falco's grounded Reflector Start Motion State handler
void ftFx_SpecialLw_Enter(HSD_GObj* gobj);

/// Fox & Falco's aerial Reflector Start Motion State handler
void ftFx_SpecialAirLw_Enter(HSD_GObj* gobj);

void ftFx_SpecialLwStart_Anim(HSD_GObj* gobj);
void ftFx_SpecialAirLwStart_Anim(HSD_GObj* gobj);
void ftFx_SpecialLwStart_IASA(HSD_GObj* gobj);
void ftFx_SpecialAirLwStart_IASA(HSD_GObj* gobj);

/// Check for drop-through platform while in @c SpecialLwStart
bool ftFx_SpecialLwStart_CheckPass(HSD_GObj* gobj);

/// Fox & Falco's Reflector Start Platform Drop Motion State handler
void ftFx_SpecialLwStart_Pass(HSD_GObj* gobj);

/// Fox & Falco's Reflector Start Physics callback
void ftFx_SpecialLwStart_Phys(HSD_GObj* gobj);

/// Fox & Falco's aerial Reflector Start Physics callback
void ftFx_SpecialAirLwStart_Phys(HSD_GObj* gobj);

/// Fox & Falco's grounded Reflector Start Collision callback
void ftFx_SpecialLwStart_Coll(HSD_GObj* gobj);

/// Fox & Falco's aerial Reflector Start Collision callback
void ftFx_SpecialAirLwStart_Coll(HSD_GObj* gobj);

/// Fox & Falco's ground -> air Reflector Start Motion State handler
void ftFx_SpecialLwStart_GroundToAir(HSD_GObj* gobj);

/// Fox & Falco's air -> ground Reflector Start Motion State handler
void ftFx_SpecialAirLwStart_AirToGround(HSD_GObj* gobj);

/// Fox & Falco's grounded Reflector Loop Animation callback
void ftFx_SpecialLwLoop_Anim(HSD_GObj* gobj);

/// Fox & Falco's aerial Reflector Loop Animation callback
void ftFx_SpecialAirLwLoop_Anim(HSD_GObj* gobj);

/// Fox & Falco's grounded Reflector Loop IASA callback
void ftFx_SpecialLwLoop_IASA(HSD_GObj* gobj);

/// Fox & Falco's aerial Reflector Loop IASA callback
void ftFx_SpecialAirLwLoop_IASA(HSD_GObj* gobj);

/// Fox & Falco's grounded Reflector Loop Physics callback
void ftFx_SpecialLwLoop_Phys(HSD_GObj* gobj);

/// Fox & Falco's aerial Reflector Loop Physics callback
void ftFx_SpecialAirLwLoop_Phys(HSD_GObj* gobj);

/// Fox & Falco's grounded Reflector Loop Collision callback
void ftFx_SpecialLwLoop_Coll(HSD_GObj* gobj);

/// Fox & Falco's aerial Reflector Loop Collision callback
void ftFx_SpecialAirLwLoop_Coll(HSD_GObj* gobj);

/// Fox & Falco's grounded Reflector Turn Animation callback
void ftFx_SpecialLwTurn_Anim(HSD_GObj* gobj);

/// Fox & Falco's aerial Reflector Turn Animation callback
void ftFx_SpecialAirLwTurn_Anim(HSD_GObj* gobj);

void ftFx_SpecialLwTurn_IASA(HSD_GObj* gobj);
void ftFx_SpecialAirLwTurn_IASA(HSD_GObj* gobj);
void ftFx_SpecialLwTurn_Phys(HSD_GObj* gobj);
void ftFx_SpecialAirLwTurn_Phys(HSD_GObj* gobj);
void ftFx_SpecialLwTurn_Coll(HSD_GObj* gobj);
void ftFx_SpecialAirLwTurn_Coll(HSD_GObj* gobj);
void ftFx_SpecialLwTurn_GroundToAir(HSD_GObj* gobj);
void ftFx_SpecialAirLwTurn_GroundToAir(HSD_GObj* gobj);
bool ftFx_SpecialLwTurn_Check(HSD_GObj* gobj);
bool ftFx_SpecialLwHit_Check(HSD_GObj* gobj);
void ftFx_SpecialLwHit_Anim(HSD_GObj* gobj);
void ftFx_SpecialAirLwHit_Anim(HSD_GObj* gobj);
void ftFx_SpecialLwHit_IASA(HSD_GObj* gobj);
void ftFx_SpecialAirLwHit_IASA(HSD_GObj* gobj);
void ftFx_SpecialLwHit_Phys(HSD_GObj* gobj);
void ftFx_SpecialAirLwHit_Phys(HSD_GObj* gobj);
void ftFx_SpecialLwHit_Coll(HSD_GObj* gobj);
void ftFx_SpecialAirLwHit_Coll(HSD_GObj* gobj);
void ftFx_SpecialLwHit_GroundToAir(HSD_GObj* gobj);
void ftFx_SpecialAirLwHit_AirToGround(HSD_GObj* gobj);
void ftFx_SpecialLwHit_SetCall(HSD_GObj* gobj);
void ftFx_SpecialLwHit_Enter(HSD_GObj* gobj);
void ftFx_SpecialLwEnd_Anim(HSD_GObj* gobj);
void ftFx_SpecialAirLwEnd_Anim(HSD_GObj* gobj);
void ftFx_SpecialLwEnd_IASA(HSD_GObj* gobj);
void ftFx_SpecialAirLwEnd_IASA(HSD_GObj* gobj);
void ftFx_SpecialLwEnd_Phys(HSD_GObj* gobj);
void ftFx_SpecialAirLwEnd_Phys(HSD_GObj* gobj);
void ftFx_SpecialLwEnd_Coll(HSD_GObj* gobj);
void ftFx_SpecialAirLwEnd_Coll(HSD_GObj* gobj);
void ftFx_SpecialLwEnd_GroundToAir(HSD_GObj* gobj);
void ftFx_SpecialAirLwEnd_AirToGround(HSD_GObj* gobj);
void ftFx_SpecialLwEnd_Enter(HSD_GObj* gobj);
void ftFx_SpecialAirLwEnd_Enter(HSD_GObj* gobj);

// Side Special - Fox Illusion/Falco Phantasm (SpecialS)

void ftFx_SpecialS_CreateGFX(HSD_GObj* gobj);
bool ftFx_SpecialS_CheckGhostRemove(HSD_GObj* gobj);
u32 ftFx_SpecialS_GetCmdVar2(HSD_GObj* gobj);
void ftFx_SpecialS_CopyGhostPosIndexed(HSD_GObj* gobj, s32 index,
                                       Vec3* ghostPos);
f32 ftFx_SpecialS_ReturnFloatVarIndexed(HSD_GObj* gobj, s32 index);
void ftFx_SpecialSStart_Enter(HSD_GObj* gobj);
void ftFx_SpecialAirSStart_Enter(HSD_GObj* gobj);
void ftFx_SpecialSStart_Anim(HSD_GObj* gobj);
void ftFx_SpecialAirSStart_Anim(HSD_GObj* gobj);
void ftFx_SpecialSStart_IASA(HSD_GObj* gobj);
void ftFx_SpecialAirSStart_IASA(HSD_GObj* gobj);
void ftFx_SpecialSStart_Phys(HSD_GObj* gobj);
void ftFx_SpecialAirSStart_Phys(HSD_GObj* gobj);
void ftFx_SpecialSStart_Coll(HSD_GObj* gobj);
void ftFx_SpecialAirSStart_Coll(HSD_GObj* gobj);
void ftFx_SpecialSStart_GroundToAir(HSD_GObj* gobj);
void ftFx_SpecialAirSStart_AirToGround(HSD_GObj* gobj);
void ftFx_SpecialS_Anim(HSD_GObj* gobj);
void ftFx_SpecialAirS_Anim(HSD_GObj* gobj);
void ftFx_SpecialS_IASA(HSD_GObj* gobj);
void ftFx_SpecialAirS_IASA(HSD_GObj* gobj);
void ftFx_SpecialS_Phys(HSD_GObj* gobj);
void ftFx_SpecialAirS_Phys(HSD_GObj* gobj);
void ftFx_SpecialS_Coll(HSD_GObj* gobj);
void ftFx_SpecialAirS_Coll(HSD_GObj* gobj);
void ftFx_SpecialS_GroundToAir(HSD_GObj* gobj);
void ftFx_SpecialAirS_AirToGround(HSD_GObj* gobj);
void ftFx_SpecialS_Enter(HSD_GObj* gobj);
void ftFx_SpecialAirS_Enter(HSD_GObj* gobj);
void ftFx_SpecialSEnd_Anim(HSD_GObj* gobj);
void ftFx_SpecialAirSEnd_Anim(HSD_GObj* gobj);
void ftFx_SpecialSEnd_IASA(HSD_GObj* gobj);
void ftFx_SpecialAirSEnd_IASA(HSD_GObj* gobj);
void ftFx_SpecialSEnd_Phys(HSD_GObj* gobj);
void ftFx_SpecialAirSEnd_Phys(HSD_GObj* gobj);
void ftFx_SpecialSEnd_Coll(HSD_GObj* gobj);
void ftFx_SpecialAirSEnd_Coll(HSD_GObj* gobj);
void ftFx_SpecialSEnd_Enter(HSD_GObj* gobj);
void ftFx_SpecialAirSEnd_Enter(HSD_GObj* gobj);
void ftFx_Init_LoadSpecialAttrs(HSD_GObj*);
void ftFx_Init_OnLoadForFalco(Fighter* fp);

void ftFx_Init_OnLoad(HSD_GObj* gobj);
void ftFx_Init_OnKnockbackEnter(HSD_GObj* gobj);
void ftFx_Init_OnKnockbackExit(HSD_GObj* gobj);

#endif
