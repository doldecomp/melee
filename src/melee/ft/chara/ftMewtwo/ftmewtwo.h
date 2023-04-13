#ifndef _ftMewTwo_h_
#define _ftMewTwo_h_

#include <melee/ft/ftcommon.h>
#include <melee/lb/lbvector.h>

#include <melee/ft/fighter.h>
#include <melee/it/item.h>
#include <melee/it/itkind.h>

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

#define CONFUSION_REFLECT_NONE                                                 \
    0 // Effectively a "wait" state for Confusion (i.e. wait until the flag is
      // either 1 or 2 because 0 does nothing).

#define CONFUSION_REFLECT_ON 1 // Toggle reflect bubble on.

#define CONFUSION_REFLECT_OFF 2 // Toggle reflect bubble off.

// Flags used by Mewtwo in Action State Change //

// SpecialN/SpecialAirN //

#define FTMEWTWO_SPECIALN_ACTION_FLAG                                          \
    FtStateChange_SkipUpdateMatAnim | FtStateChange_PreserveSfx |              \
        FtStateChange_UpdateCmd | FtStateChange_SkipUpdateItemVis |            \
        FtStateChange_Unk_19

#define FTMEWTWO_SPECIALN_COLL_FLAG                                            \
    FtStateChange_SkipUpdateMatAnim | FtStateChange_SkipUpdateColAnim |        \
        FtStateChange_UpdateCmd | FtStateChange_SkipUpdateItemVis |            \
        FtStateChange_Unk_19 | FtStateChange_SkipUpdateModelPartVis |          \
        FtStateChange_SkipUpdateModelFlag | FtStateChange_Unk_27

// SpecialS/SpecialAirS //

#define FTMEWTWO_SPECIALS_COLL_FLAG                                            \
    FtStateChange_PreserveGfx | FtStateChange_SkipUpdateMatAnim |              \
        FtStateChange_SkipUpdateColAnim | FtStateChange_UpdateCmd |            \
        FtStateChange_SkipUpdateItemVis | FtStateChange_Unk_19 |               \
        FtStateChange_SkipUpdateModelPartVis |                                 \
        FtStateChange_SkipUpdateModelFlag | FtStateChange_Unk_27

// SpecialHi/SpecialAirHi //

// SpecialLw/SpecialAirLw //

#define FTMEWTWO_SPECIALLW_COLL_FLAG                                           \
    FtStateChange_PreserveGfx | FtStateChange_SkipUpdateMatAnim |              \
        FtStateChange_SkipUpdateColAnim | FtStateChange_UpdateCmd |            \
        FtStateChange_SkipUpdateItemVis | FtStateChange_Unk_19 |               \
        FtStateChange_SkipUpdateModelPartVis |                                 \
        FtStateChange_SkipUpdateModelFlag | FtStateChange_Unk_27

typedef struct _ftMewtwoAttributes {
    // NEUTRAL SPECIAL - SHADOW BALL (SpecialN/SpecialAirN) //

    f32 x0_MEWTWO_SHADOWBALL_CHARGE_CYCLES; // Number of frames each iteration
                                            // cycle lasts?
    f32 x4_MEWTWO_SHADOWBALL_GROUND_RECOIL_X;
    f32 x8_MEWTWO_SHADOWBALL_AIR_RECOIL_X;
    s32 xC_MEWTWO_SHADOWBALL_CHARGE_ITERATIONS; // Number of iterations required
                                                // for full charge
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

extern ActionState ftMewtwo_MotionStateTable[];
extern char lbl_803D0D80[];
extern char lbl_803D0D8C[];
extern Fighter_CostumeStrings lbl_803D0F5C[];
extern char lbl_803D0EC4[];
extern Fighter_DemoStrings lbl_803D0F4C;

// Mewtwo functions //

void ftMewtwo_OnDeath(HSD_GObj* fighter_gobj);
void ftMewtwo_OnDeath2(HSD_GObj* fighter_gobj);
void ftMewtwo_OnTakeDamage(HSD_GObj* fighter_gobj);

// Up Special - Teleport (SpecialHi/SpecialAirHi) //

void ftMewtwo_SpecialHi_CreateGFX(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialHi_SetStartGFX(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialHi_SetEndGFX(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialHi_StartMotion(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialAirHi_StartMotion(HSD_GObj* fighter_gobj);
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

// Down Special - Disable (SpecialLw/SpecialAirLw) //

void ftMewtwo_SpecialLw_ClearDisableGObj(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialLw_RemoveDisable(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialLw_StartMotion(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialAirLw_StartMotion(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialLw_Anim(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialAirLw_Anim(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialLw_IASA(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialAirLw_IASA(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialLw_Phys(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialAirLw_Phys(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialLw_GroundToAir(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialAirLw_AirToGround(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialLw_Coll(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialAirLw_Coll(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialLw_CreateDisable(HSD_GObj* fighter_gobj);

// Side Special - Confusion (SpecialS/SpecialAirS) //

void ftMewtwo_SpecialS_SetFlags(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialS_StartMotion(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialAirS_StartMotion(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialS_Anim(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialAirS_Anim(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialS_IASA(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialAirS_IASA(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialS_Phys(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialAirS_Phys(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialS_GroundToAir(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialAirS_AirToGround(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialS_Coll(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialAirS_Coll(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialS_ReflectThink(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialS_OnReflect(HSD_GObj* fighter_gobj);

// Neutral Special - Shadow Ball (SpecialN/SpecialAirN) //

s32 ftMewtwo_SpecialN_GetChargeLevel(HSD_GObj* fighter_gobj, s32* chargeLevel,
                                     s32* chargeCycles);
bool ftMewtwo_SpecialN_CheckShadowBallRemove(HSD_GObj* fighter_gobj);
bool ftMewtwo_SpecialN_CheckShadowBallCancel(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialN_SetNULL(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialN_OnTakeDamage(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialN_OnDeath(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialN_ReleaseShadowBall(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialN_PlayChargeSFX(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialN_StartMotion(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialAirN_StartMotion(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialNStart_Anim(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialNLoop_Anim(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialNFull_Anim(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialNCancel_Anim(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialNEnd_Anim(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialAirNStart_Anim(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialAirNLoop_Anim(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialAirNFull_Anim(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialAirNCancel_Anim(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialAirNEnd_Anim(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialNStart_IASA(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialNLoop_IASA(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialNFull_IASA(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialNCancel_IASA(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialNEnd_IASA(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialAirNStart_IASA(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialAirNLoop_IASA(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialAirNFull_IASA(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialAirNCancel_IASA(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialAirNEnd_IASA(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialNStart_Phys(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialNLoop_Phys(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialNFull_Phys(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialNCancel_Phys(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialNEnd_Phys(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialAirNStart_Phys(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialAirNLoop_Phys(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialAirNFull_Phys(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialAirNCancel_Phys(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialAirNEnd_Phys(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialNStart_Coll(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialNLoop_Coll(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialNFull_Coll(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialNCancel_Coll(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialNEnd_Coll(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialAirNStart_Coll(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialAirNLoop_Coll(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialAirNFull_Coll(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialAirNCancel_Coll(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialAirNEnd_Coll(HSD_GObj* fighter_gobj);
void ftMewtwo_SpecialN_Shoot(HSD_GObj* fighter_gobj);
void ftMewtwo_OnLoad(HSD_GObj* fighter_gobj);
void ftMewTwo_OnItemPickup(HSD_GObj* fighter_gobj, bool bool);
void ftMewTwo_OnItemDrop(HSD_GObj* fighter_gobj, bool bool);
void ftMewTwo_OnItemInvisible(HSD_GObj* fighter_gobj);
void ftMewTwo_OnItemVisible(HSD_GObj* fighter_gobj);
void ftMewTwo_80144F58(HSD_GObj* fighter_gobj);
void ftMewTwo_LoadSpecialAttrs(HSD_GObj* fighter_gobj);
void ftMewTwo_OnKnockbackEnter(HSD_GObj* fighter_gobj);
void ftMewTwo_OnKnockbackExit(HSD_GObj* fighter_gobj);

#endif
