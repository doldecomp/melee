#ifndef _ftMewTwo_h_
#define _ftMewTwo_h_

#include "ft/fighter.h"
#include "ft/ftcommon.h"
#include "it/item.h"
#include "lb/lbvector.h"

typedef enum ftMewtwoAction {
    AS_MEWTWO_SPECIALN_START = ASID_MAX,
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

// Flag values read during Confusion's reflect think function

#define CONFUSION_REFLECT_NONE                                                \
    0 // Effectively a "wait" state for Confusion (i.e. wait until the flag is
      // either 1 or 2 because 0 does nothing).

#define CONFUSION_REFLECT_ON 1 // Toggle reflect bubble on.

#define CONFUSION_REFLECT_OFF 2 // Toggle reflect bubble off.

// Flags used by Mewtwo in Motion State Change //

// SpecialN/SpecialAirN //

#define FTMEWTWO_SPECIALN_ACTION_FLAG                                         \
    FtStateChange_SkipUpdateMatAnim | FtStateChange_PreserveSfx |             \
        FtStateChange_UpdateCmd | FtStateChange_SkipUpdateItemVis |           \
        FtStateChange_Unk_19

#define FTMEWTWO_SPECIALN_COLL_FLAG                                           \
    FtStateChange_SkipUpdateMatAnim | FtStateChange_SkipUpdateColAnim |       \
        FtStateChange_UpdateCmd | FtStateChange_SkipUpdateItemVis |           \
        FtStateChange_Unk_19 | FtStateChange_SkipUpdateModelPartVis |         \
        FtStateChange_SkipUpdateModelFlag | FtStateChange_Unk_27

// SpecialS/SpecialAirS //

#define FTMEWTWO_SPECIALS_COLL_FLAG                                           \
    FtStateChange_PreserveGfx | FtStateChange_SkipUpdateMatAnim |             \
        FtStateChange_SkipUpdateColAnim | FtStateChange_UpdateCmd |           \
        FtStateChange_SkipUpdateItemVis | FtStateChange_Unk_19 |              \
        FtStateChange_SkipUpdateModelPartVis |                                \
        FtStateChange_SkipUpdateModelFlag | FtStateChange_Unk_27

// SpecialHi/SpecialAirHi //

// SpecialLw/SpecialAirLw //

#define FTMEWTWO_SPECIALLW_COLL_FLAG                                          \
    FtStateChange_PreserveGfx | FtStateChange_SkipUpdateMatAnim |             \
        FtStateChange_SkipUpdateColAnim | FtStateChange_UpdateCmd |           \
        FtStateChange_SkipUpdateItemVis | FtStateChange_Unk_19 |              \
        FtStateChange_SkipUpdateModelPartVis |                                \
        FtStateChange_SkipUpdateModelFlag | FtStateChange_Unk_27

typedef struct _ftMewtwoAttributes {
    // NEUTRAL SPECIAL - SHADOW BALL (SpecialN/SpecialAirN) //

    f32 x0_MEWTWO_SHADOWBALL_CHARGE_CYCLES; // Number of frames each iteration
                                            // cycle lasts?
    f32 x4_MEWTWO_SHADOWBALL_GROUND_RECOIL_X;
    f32 x8_MEWTWO_SHADOWBALL_AIR_RECOIL_X;
    s32 xC_MEWTWO_SHADOWBALL_CHARGE_ITERATIONS; // Number of iterations
                                                // required for full charge
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
    s32 x68_MEWTWO_TELEPORT_ANGLE_CLAMP; // Clamp teleport travel if surface
                                         // angle is greater than this value
    f32 x6C_MEWTWO_TELEPORT_MOMENTUM_END_MUL;
    f32 x70_MEWTWO_TELEPORT_FREEFALL_MOBILITY;
    f32 x74_MEWTWO_TELEPORT_LANDING_LAG;

    // DOWN SPECIAL - DISABLE (SpecialLw/SpecialAirLw) //

    f32 x78_MEWTWO_DISABLE_GRAVITY;
    f32 x7C_MEWTWO_DISABLE_TERMINAL_VELOCITY;
    f32 x80_MEWTWO_DISABLE_OFFSET_X;
    f32 x84_MEWTWO_DISABLE_OFFSET_Y;

} ftMewtwoAttributes;

extern MotionState ftMt_Init_MotionStateTable[];
extern char ftMt_Init_DatFilename[];
extern char ftMt_Init_DataName[];
extern Fighter_CostumeStrings ftMt_Init_CostumeStrings[];
extern char ftMt_Init_AnimDatFilename[];
extern Fighter_DemoStrings ftMt_Init_DemoMotionFilenames;

// Mewtwo functions //

void ftMt_Init_OnDeath(HSD_GObj* gobj);
void ftMt_Init_OnDeath2(HSD_GObj* gobj);
void ftMt_Init_OnTakeDamage(HSD_GObj* gobj);

// Up Special - Teleport (SpecialHi/SpecialAirHi) //

void ftMt_SpecialHi_CreateGFX(HSD_GObj* gobj);
void ftMt_SpecialHi_SetStartGFX(HSD_GObj* gobj);
void ftMt_SpecialHi_SetEndGFX(HSD_GObj* gobj);
void ftMt_SpecialHiStart_Enter(HSD_GObj* gobj);
void ftMt_SpecialAirHiStart_Enter(HSD_GObj* gobj);
void ftMt_SpecialHiStart_Anim(HSD_GObj* gobj);
void ftMt_SpecialAirHiStart_Anim(HSD_GObj* gobj);
void ftMt_SpecialHiStart_IASA(HSD_GObj* gobj);
void ftMt_SpecialAirHiStart_IASA(HSD_GObj* gobj);
void ftMt_SpecialHiStart_Phys(HSD_GObj* gobj);
void ftMt_SpecialAirHiStart_Phys(HSD_GObj* gobj);
void ftMt_SpecialHiStart_Coll(HSD_GObj* gobj);
void ftMt_SpecialAirHiStart_Coll(HSD_GObj* gobj);
void ftMt_SpecialHiStart_GroundToAir(HSD_GObj* gobj);
void ftMt_SpecialAirHiStart_AirToGround(HSD_GObj* gobj);
void ftMt_SpecialHi_Anim(HSD_GObj* gobj);
void ftMt_SpecialAirHi_Anim(HSD_GObj* gobj);
void ftMt_SpecialHi_IASA(HSD_GObj* gobj);
void ftMt_SpecialAirHi_IASA(HSD_GObj* gobj);
void ftMt_SpecialHi_Phys(HSD_GObj* gobj);
void ftMt_SpecialAirHi_Phys(HSD_GObj* gobj);
void ftMt_SpecialHi_Coll(HSD_GObj* gobj);
void ftMt_SpecialAirHi_Coll(HSD_GObj* gobj);
void ftMt_SpecialHi_GroundToAir(HSD_GObj* gobj);
void ftMt_SpecialAirHi_AirToGround(HSD_GObj* gobj);
void ftMt_SpecialHi_Enter(HSD_GObj* gobj);
void ftMt_SpecialAirHi_Enter(HSD_GObj* gobj);
void ftMt_SpecialHiLost_Anim(HSD_GObj* gobj);
void ftMt_SpecialAirHiLost_Anim(HSD_GObj* gobj);
void ftMt_SpecialHiLost_IASA(HSD_GObj* gobj);
void ftMt_SpecialAirHiLost_IASA(HSD_GObj* gobj);
void ftMt_SpecialHiLost_Phys(HSD_GObj* gobj);
void ftMt_SpecialAirHiLost_Phys(HSD_GObj* gobj);
void ftMt_SpecialHiLost_Coll(HSD_GObj* gobj);
void ftMt_SpecialAirHiLost_Coll(HSD_GObj* gobj);
void ftMt_SpecialHiLost_GroundToAir(HSD_GObj* gobj);
void ftMt_SpecialHiLost_Enter(HSD_GObj* gobj);
void ftMt_SpecialAirHiLost_Enter(HSD_GObj* gobj);

// Down Special - Disable (SpecialLw/SpecialAirLw) //

void ftMt_SpecialLw_ClearDisableGObj(HSD_GObj* gobj);
void ftMt_SpecialLw_RemoveDisable(HSD_GObj* gobj);
void ftMt_SpecialLw_Enter(HSD_GObj* gobj);
void ftMt_SpecialAirLw_Enter(HSD_GObj* gobj);
void ftMt_SpecialLw_Anim(HSD_GObj* gobj);
void ftMt_SpecialAirLw_Anim(HSD_GObj* gobj);
void ftMt_SpecialLw_IASA(HSD_GObj* gobj);
void ftMt_SpecialAirLw_IASA(HSD_GObj* gobj);
void ftMt_SpecialLw_Phys(HSD_GObj* gobj);
void ftMt_SpecialAirLw_Phys(HSD_GObj* gobj);
void ftMt_SpecialLw_GroundToAir(HSD_GObj* gobj);
void ftMt_SpecialAirLw_AirToGround(HSD_GObj* gobj);
void ftMt_SpecialLw_Coll(HSD_GObj* gobj);
void ftMt_SpecialAirLw_Coll(HSD_GObj* gobj);
void ftMt_SpecialLw_CreateDisable(HSD_GObj* gobj);

// Side Special - Confusion (SpecialS/SpecialAirS) //

void ftMt_SpecialS_SetFlags(HSD_GObj* gobj);
void ftMt_SpecialS_Enter(HSD_GObj* gobj);
void ftMt_SpecialAirS_Enter(HSD_GObj* gobj);
void ftMt_SpecialS_Anim(HSD_GObj* gobj);
void ftMt_SpecialAirS_Anim(HSD_GObj* gobj);
void ftMt_SpecialS_IASA(HSD_GObj* gobj);
void ftMt_SpecialAirS_IASA(HSD_GObj* gobj);
void ftMt_SpecialS_Phys(HSD_GObj* gobj);
void ftMt_SpecialAirS_Phys(HSD_GObj* gobj);
void ftMt_SpecialS_GroundToAir(HSD_GObj* gobj);
void ftMt_SpecialAirS_AirToGround(HSD_GObj* gobj);
void ftMt_SpecialS_Coll(HSD_GObj* gobj);
void ftMt_SpecialAirS_Coll(HSD_GObj* gobj);
void ftMt_SpecialS_ReflectThink(HSD_GObj* gobj);
void ftMt_SpecialS_OnReflect(HSD_GObj* gobj);

// Neutral Special - Shadow Ball (SpecialN/SpecialAirN) //

s32 ftMt_SpecialN_GetChargeLevel(HSD_GObj* gobj, s32* chargeLevel,
                                     s32* chargeCycles);
bool ftMt_SpecialN_CheckShadowBallRemove(HSD_GObj* gobj);
bool ftMt_SpecialN_CheckShadowBallCancel(HSD_GObj* gobj);
void ftMt_SpecialN_SetNULL(HSD_GObj* gobj);
void ftMt_SpecialN_OnTakeDamage(HSD_GObj* gobj);
void ftMt_SpecialN_OnDeath(HSD_GObj* gobj);
void ftMt_SpecialN_ReleaseShadowBall(HSD_GObj* gobj);
void ftMt_SpecialN_PlayChargeSFX(HSD_GObj* gobj);
void ftMt_SpecialN_Enter(HSD_GObj* gobj);
void ftMt_SpecialAirN_Enter(HSD_GObj* gobj);
void ftMt_SpecialNStart_Anim(HSD_GObj* gobj);
void ftMt_SpecialNLoop_Anim(HSD_GObj* gobj);
void ftMt_SpecialNFull_Anim(HSD_GObj* gobj);
void ftMt_SpecialNCancel_Anim(HSD_GObj* gobj);
void ftMt_SpecialNEnd_Anim(HSD_GObj* gobj);
void ftMt_SpecialAirNStart_Anim(HSD_GObj* gobj);
void ftMt_SpecialAirNLoop_Anim(HSD_GObj* gobj);
void ftMt_SpecialAirNFull_Anim(HSD_GObj* gobj);
void ftMt_SpecialAirNCancel_Anim(HSD_GObj* gobj);
void ftMt_SpecialAirNEnd_Anim(HSD_GObj* gobj);
void ftMt_SpecialNStart_IASA(HSD_GObj* gobj);
void ftMt_SpecialNLoop_IASA(HSD_GObj* gobj);
void ftMt_SpecialNFull_IASA(HSD_GObj* gobj);
void ftMt_SpecialNCancel_IASA(HSD_GObj* gobj);
void ftMt_SpecialNEnd_IASA(HSD_GObj* gobj);
void ftMt_SpecialAirNStart_IASA(HSD_GObj* gobj);
void ftMt_SpecialAirNLoop_IASA(HSD_GObj* gobj);
void ftMt_SpecialAirNFull_IASA(HSD_GObj* gobj);
void ftMt_SpecialAirNCancel_IASA(HSD_GObj* gobj);
void ftMt_SpecialAirNEnd_IASA(HSD_GObj* gobj);
void ftMt_SpecialNStart_Phys(HSD_GObj* gobj);
void ftMt_SpecialNLoop_Phys(HSD_GObj* gobj);
void ftMt_SpecialNFull_Phys(HSD_GObj* gobj);
void ftMt_SpecialNCancel_Phys(HSD_GObj* gobj);
void ftMt_SpecialNEnd_Phys(HSD_GObj* gobj);
void ftMt_SpecialAirNStart_Phys(HSD_GObj* gobj);
void ftMt_SpecialAirNLoop_Phys(HSD_GObj* gobj);
void ftMt_SpecialAirNFull_Phys(HSD_GObj* gobj);
void ftMt_SpecialAirNCancel_Phys(HSD_GObj* gobj);
void ftMt_SpecialAirNEnd_Phys(HSD_GObj* gobj);
void ftMt_SpecialNStart_Coll(HSD_GObj* gobj);
void ftMt_SpecialNLoop_Coll(HSD_GObj* gobj);
void ftMt_SpecialNFull_Coll(HSD_GObj* gobj);
void ftMt_SpecialNCancel_Coll(HSD_GObj* gobj);
void ftMt_SpecialNEnd_Coll(HSD_GObj* gobj);
void ftMt_SpecialAirNStart_Coll(HSD_GObj* gobj);
void ftMt_SpecialAirNLoop_Coll(HSD_GObj* gobj);
void ftMt_SpecialAirNFull_Coll(HSD_GObj* gobj);
void ftMt_SpecialAirNCancel_Coll(HSD_GObj* gobj);
void ftMt_SpecialAirNEnd_Coll(HSD_GObj* gobj);
void ftMt_SpecialN_Shoot(HSD_GObj* gobj);
void ftMt_Init_OnLoad(HSD_GObj* gobj);
void ftMt_Init_OnItemPickup(HSD_GObj* gobj, bool bool);
void ftMt_Init_OnItemDrop(HSD_GObj* gobj, bool bool);
void ftMt_Init_OnItemInvisible(HSD_GObj* gobj);
void ftMt_Init_OnItemVisible(HSD_GObj* gobj);
void ftMt_Init_UnkMotionStates4(HSD_GObj* gobj);
void ftMt_Init_LoadSpecialAttrs(HSD_GObj* gobj);
void ftMt_Init_OnKnockbackEnter(HSD_GObj* gobj);
void ftMt_Init_OnKnockbackExit(HSD_GObj* gobj);

#endif
