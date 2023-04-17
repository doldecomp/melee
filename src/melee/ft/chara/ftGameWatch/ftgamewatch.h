#ifndef _ftgamewatch_h_
#define _ftgamewatch_h_

#include "ft/fighter.h"
#include "ft/ftcommon.h"
#include "it/item.h"
#include "lb/lbvector.h"

#include <common_structs.h>

// Oil Panic Charge Level Macros //

#define GAMEWATCH_PANIC_EMPTY 0
#define GAMEWATCH_PANIC_LOW 1
#define GAMEWATCH_PANIC_MID 2
#define GAMEWATCH_PANIC_FULL 3

// Mr. Game & Watch Motion State Change Flags //

// Chef (SpecialN/SpecialAirN) //
#define FTGAMEWATCH_SPECIALN_COLL_FLAG                                        \
    FtStateChange_PreserveColAnimHitStatus | FtStateChange_SkipUpdateHit |    \
        FtStateChange_SkipUpdateModel | FtStateChange_SkipUpdateMatAnim |     \
        FtStateChange_SkipUpdateColAnim | FtStateChange_UpdateCmd |           \
        FtStateChange_SkipUpdateItemVis | FtStateChange_Unk_19 |              \
        FtStateChange_SkipUpdateModelPartVis |                                \
        FtStateChange_SkipUpdateModelFlag | FtStateChange_Unk_27

// Judgement (SpecialS/SpecialAirS) //
#define FTGAMEWATCH_SPECIALS_COLL_FLAG                                        \
    FtStateChange_PreserveColAnimHitStatus | FtStateChange_SkipUpdateHit |    \
        FtStateChange_SkipUpdateModel | FtStateChange_SkipUpdateMatAnim |     \
        FtStateChange_SkipUpdateColAnim | FtStateChange_UpdateCmd |           \
        FtStateChange_SkipUpdateItemVis | FtStateChange_Unk_19 |              \
        FtStateChange_SkipUpdateModelPartVis |                                \
        FtStateChange_SkipUpdateModelFlag | FtStateChange_Unk_27

// Oil Panic (SpecialLw/SpecialAirLw) //

// Mr. Game & Watch Motion State IDs //

typedef enum ftGameWatchAction {
    AS_GAMEWATCH_ATTACK11 = ASID_MAX,
    AS_GAMEWATCH_ATTACK100START,
    AS_GAMEWATCH_ATTACK100LOOP,
    AS_GAMEWATCH_ATTACK100END,
    AS_GAMEWATCH_ATTACKLW3,
    AS_GAMEWATCH_ATTACKS4,
    AS_GAMEWATCH_ATTACKAIRN,
    AS_GAMEWATCH_ATTACKAIRB,
    AS_GAMEWATCH_ATTACKAIRHI,
    AS_GAMEWATCH_LANDINGAIRN,
    AS_GAMEWATCH_LANDINGAIRB,
    AS_GAMEWATCH_LANDINGAIRHI,
    AS_GAMEWATCH_SPECIALN,
    AS_GAMEWATCH_SPECIALAIRN,
    AS_GAMEWATCH_SPECIALS1,
    AS_GAMEWATCH_SPECIALS2,
    AS_GAMEWATCH_SPECIALS3,
    AS_GAMEWATCH_SPECIALS4,
    AS_GAMEWATCH_SPECIALS5,
    AS_GAMEWATCH_SPECIALS6,
    AS_GAMEWATCH_SPECIALS7,
    AS_GAMEWATCH_SPECIALS8,
    AS_GAMEWATCH_SPECIALS9,
    AS_GAMEWATCH_SPECIALAIRS1,
    AS_GAMEWATCH_SPECIALAIRS2,
    AS_GAMEWATCH_SPECIALAIRS3,
    AS_GAMEWATCH_SPECIALAIRS4,
    AS_GAMEWATCH_SPECIALAIRS5,
    AS_GAMEWATCH_SPECIALAIRS6,
    AS_GAMEWATCH_SPECIALAIRS7,
    AS_GAMEWATCH_SPECIALAIRS8,
    AS_GAMEWATCH_SPECIALAIRS9,
    AS_GAMEWATCH_SPECIALHI,
    AS_GAMEWATCH_SPECIALAIRHI,
    AS_GAMEWATCH_SPECIALLW,
    AS_GAMEWATCH_SPECIALLW_CATCH,
    AS_GAMEWATCH_SPECIALLW_SHOOT,
    AS_GAMEWATCH_SPECIALAIRLW,
    AS_GAMEWATCH_SPECIALAIRLW_CATCH,
    AS_GAMEWATCH_SPECIALAIRLW_SHOOT,

} ftGameWatchAction;

typedef struct ftGameWatchChef {
    s32 sausageCount[5];
} ftGameWatchChef;

typedef struct ftGameWatchJudge {
    s32 rollVar[9];
} ftGameWatchJudge;

typedef struct _ftGameWatchAttributes {
    // MISC. ATTRIBUTES //

    f32 x0_GAMEWATCH_WIDTH;    // Mr. Game & Watch's Z-Axis stretch; 0.01 by
                               // default
    s32 x4_GAMEWATCH_COLOR[4]; // Array of four RGBA values, one for each Mr.
                               // Game & Watch costume color
    s32 x14_GAMEWATCH_OUTLINE; // Outline color of Mr. Game & Watch's model

    // NEUTRAL SPECIAL - CHEF //

    f32 x18_GAMEWATCH_CHEF_LOOPFRAME; // Allow rapid-firing sausages from this
                                      // frame onward
    f32 x1C_GAMEWATCH_CHEF_MAX; // Maximum amount of sausages created per Chef
                                // use

    // SIDE SPECIAL - JUDGEMENT //

    f32 x20_GAMEWATCH_JUDGE_MOMENTUM_PRESERVE; // Horizontal momentum
                                               // preservation value
    f32 x24_GAMEWATCH_JUDGE_MOMENTUM_MUL; // Multiplies momentum preservation
                                          // value
    f32 x28_GAMEWATCH_JUDGE_VEL_Y;
    f32 x2C_GAMEWATCH_JUDGE_FRICTION1;
    f32 x30_GAMEWATCH_JUDGE_FRICTION2;
    s32 x34_GAMEWATCH_JUDGE_ROLL[9]; // Array of BOOLs that toggle respective
                                     // Judgement numbers ON/OFF. If a number
                                     // is OFF, it is excluded from RNG rolls.
                                     // Game panics if less than 2 numbers are
                                     // ON.

    // UP SPECIAL - FIRE RESCUE //

    f32 x58_GAMEWATCH_RESCUE_STICK_RANGE; // Minimum control stick range
                                          // required for directional
                                          // influence? Also affects how far
                                          // Mr. Game & Watch flings
                                          // horizontally (?)
    f32 x5C_GAMEWATCH_RESCUE_ANGLE_UNK; // Radians -- controls how far Mr. Game
                                        // & Watch can angle Fire Rescue?
    f32 x60_GAMEWATCH_RESCUE_LANDING;   // Landing lag / Freefall toggle

    // DOWN SPECIAL - OIL PANIC //

    f32 x64_GAMEWATCH_PANIC_MOMENTUM_PRESERVE; // Horizontal momentum
                                               // preservation value
    f32 x68_GAMEWATCH_PANIC_MOMENTUM_MUL; // Multiplies momentum preservation
                                          // value
    f32 x6C_GAMEWATCH_PANIC_FALL_ACCEL;   // Falling acceleration
    f32 x70_GAMEWATCH_PANIC_VEL_Y_MAX;    // Terminal Y velocity?
    f32 x74_GAMEWATCH_PANIC_DAMAGE_ADD;   // Extra damage added to Oil Panic
                                          // after formula
    f32 x78_GAMEWATCH_PANIC_DAMAGE_MUL;   // Damage multiplier
    f32 x7C_GAMEWATCH_PANIC_TURN_FRAMES;
    AbsorbDesc
        x80_GAMEWATCH_PANIC_ABSORPTION; // Oil Panic absorption attributes

} ftGameWatchAttributes;

extern MotionState ftGw_Init_MotionStateTable[];
extern char ftGw_Init_DatFilename[];
extern char ftGw_Init_DataName[];
extern Fighter_CostumeStrings ftGw_Init_CostumeStrings[];
extern char ftGw_Init_AnimDatFilename[];
extern Fighter_DemoStrings ftGw_Init_DemoMotionFilenames;

// Mr. Game & Watch Functions //

// General callbacks //

void ftGw_Init_OnDeath(HSD_GObj* gobj);
void ftGw_Init_OnLoad(HSD_GObj* gobj);
void ftGw_Init_OnDamage(HSD_GObj* gobj);
void ftGw_Init_8014A538(HSD_GObj* gobj);
void ftGw_Init_OnItemPickup(HSD_GObj* gobj, bool arg1);
void ftGw_Init_OnItemInvisible(HSD_GObj* gobj);
void ftGw_Init_OnItemVisible(HSD_GObj* gobj);
void ftGw_Init_OnItemDrop(HSD_GObj* gobj, bool dropItemFlag);
void ftGw_Init_UnkMotionStates4(HSD_GObj* gobj);
void ftGameWatch_CopySpecialAttrs(HSD_GObj* gobj);
void ftGw_Init_8014A7F4(HSD_GObj* gobj, ItemModStruct* item_mod);
void ftGw_Init_8014A814(HSD_GObj* gobj, ItemModStruct* item_mod);
void ftGw_Init_OnAbsorb(HSD_GObj* gobj);

// Item-related callbacks //

void ftGw_ItemTorchSetup(HSD_GObj* gobj);
void ftGw_AttackS4_ItemTorchSetFlag(HSD_GObj* gobj);
void ftGw_AttackS4_ItemTorchOnDamage(HSD_GObj* gobj);
void ftGw_AttackS4_ItemTorchEnterHitlag(HSD_GObj* gobj);
void ftGw_AttackS4_ItemTorchExitHitlag(HSD_GObj* gobj);
bool ftGw_AttackS4_ItemCheckTorchRemove(HSD_GObj* gobj);

// Forward Smash (AttackS4) //

void ftGw_AttackS4_Enter(HSD_GObj* gobj);
void ftGw_AttackS4_Anim(HSD_GObj* gobj);
void ftGw_AttackS4_IASA(HSD_GObj* gobj);
void ftGw_AttackS4_Phys(HSD_GObj* gobj);
void ftGw_AttackS4_Coll(HSD_GObj* gobj);

// Down Tilt (AttackLw3) //

void ftGw_AttackLw3_ItemManholeSetup(HSD_GObj* gobj);
void ftGw_AttackLw3_ItemManholeRemove(HSD_GObj* gobj);
void ftGw_AttackLw3_ItemManholeOnDamage(HSD_GObj* gobj);
bool ftGw_AttackLw3_ItemCheckManholeRemove(HSD_GObj* gobj);
void ftGw_AttackLw3_Enter(HSD_GObj* gobj);
void ftGw_AttackLw3_Anim(HSD_GObj* gobj);
void ftGw_AttackLw3_IASA(HSD_GObj* gobj);
void ftGw_AttackLw3_Phys(HSD_GObj* gobj);
void ftGw_AttackLw3_Coll(HSD_GObj* gobj);

// Aerial Attack Item Setup (AttackAirN) //

void ftGw_AttackAirN_ItemParachuteSetup(HSD_GObj* gobj);
void ftGw_AttackAirN_ItemParachuteOnLand(HSD_GObj* gobj);
void ftGw_AttackAirN_ItemParachuteSetFlag(HSD_GObj* gobj);
void ftGw_AttackAirN_ItemParachuteRemove(HSD_GObj* gobj);
bool ftGw_AttackAirN_ItemCheckParachuteRemove(HSD_GObj* gobj);
void ftGw_AttackAirN_ItemTurtleSetup(HSD_GObj* gobj);
void ftGw_AttackAirN_ItemTurtleSetFlag(HSD_GObj* gobj);
void ftGw_AttackAirN_ItemTurtleRemove(HSD_GObj* gobj);
bool ftGw_AttackAirN_ItemCheckTurtleRemove(HSD_GObj* gobj);
void ftGw_AttackAirN_ItemSparkySetup(HSD_GObj* gobj);
void ftGw_AttackAirN_ItemSparkyOnLand(HSD_GObj* gobj);
void ftGw_AttackAirN_ItemSparkySetFlag(HSD_GObj* gobj);
void ftGw_AttackAirN_ItemSparkyRemove(HSD_GObj* gobj);
void ftGw_AttackAirN_EnterItemHitlag(HSD_GObj* gobj);
bool ftGw_AttackAirN_ItemCheckSparkyRemove(HSD_GObj* gobj);
void ftGw_AttackAirN_DecideAction(HSD_GObj* gobj);

// Aerial Attacks (AttackAir) //

void ftGw_AttackAirN_Enter(HSD_GObj* gobj);
void ftGw_AttackAirN_Anim(HSD_GObj* gobj);
void ftGw_AttackAirN_IASA(HSD_GObj* gobj);
void ftGw_AttackAirN_Phys(HSD_GObj* gobj);
void ftGw_AttackAirN_Coll(HSD_GObj* gobj);
void ftGw_LandingAirN_Enter(HSD_GObj* gobj);
void ftGw_AttackAirB_Anim(HSD_GObj* gobj);
void ftGw_AttackAirB_IASA(HSD_GObj* gobj);
void ftGw_AttackAirB_Phys(HSD_GObj* gobj);
void ftGw_AttackAirB_Coll(HSD_GObj* gobj);
void ftGw_LandingAirB_Enter(HSD_GObj* gobj);
void ftGw_AttackAirHi_Anim(HSD_GObj* gobj);
void ftGw_AttackAirHi_IASA(HSD_GObj* gobj);
void ftGw_AttackAirHi_Phys(HSD_GObj* gobj);
void ftGw_AttackAirHi_Coll(HSD_GObj* gobj);
void ftGw_LandingAirHi_Enter(HSD_GObj* gobj);
void ftGw_LandingAirN_Anim(HSD_GObj* gobj);
void ftGw_LandingAirN_IASA(HSD_GObj* gobj);
void ftGw_LandingAirN_Phys(HSD_GObj* gobj);
void ftGw_LandingAirN_Coll(HSD_GObj* gobj);
void ftGw_LandingAirB_Init(HSD_GObj* gobj);
void ftGw_LandingAirB_Anim(HSD_GObj* gobj);
void ftGw_LandingAirB_IASA(HSD_GObj* gobj);
void ftGw_LandingAirB_Phys(HSD_GObj* gobj);
void ftGw_LandingAirB_Coll(HSD_GObj* gobj);
void ftGw_LandingAirHi_Init(HSD_GObj* gobj);
void ftGw_LandingAirHi_Anim(HSD_GObj* gobj);
void ftGw_LandingAirHi_IASA(HSD_GObj* gobj);
void ftGw_LandingAirHi_Phys(HSD_GObj* gobj);
void ftGw_LandingAirHi_Coll(HSD_GObj* gobj);

// Neutral Attack - Greenhouse (Attack11, Attack100Start/Loop/End) //

void ftGw_Attack11_ItemGreenhouseSetup(HSD_GObj* gobj);
void ftGw_Attack11_DecideAction(HSD_GObj* gobj);
void ftGw_Attack11_ItemGreenhouseSetFlag(HSD_GObj* gobj);
void ftGw_Attack11_ItemGreenhouseRemove(HSD_GObj* gobj);
void ftGw_Attack11_ItemGreenhouseEnterHitlag(HSD_GObj* gobj);
void ftGw_Attack11_ItemGreenhouseExitHitlag(HSD_GObj* gobj);
bool ftGw_Attack11_ItemGreenhouse_CheckAll(HSD_GObj* gobj);
bool ftGw_Attack11_ItemGreenhouse_CheckAttack11(HSD_GObj* gobj);
void ftGw_Attack11_Enter(HSD_GObj* gobj);
void ftGw_Attack11_Anim(HSD_GObj* gobj);
void ftGw_Attack11_IASA(HSD_GObj* gobj);
void ftGw_Attack11_Phys(HSD_GObj* gobj);
void ftGw_Attack11_Coll(HSD_GObj* gobj);
void ftGw_Attack100Start_Enter(HSD_GObj* gobj);
void ftGw_Attack100Start_Anim(HSD_GObj* gobj);
void ftGw_Attack100Start_IASA(HSD_GObj* gobj);
void ftGw_Attack100Start_Phys(HSD_GObj* gobj);
void ftGw_Attack100Start_Coll(HSD_GObj* gobj);
void ftGw_Attack100Loop_Enter(HSD_GObj* gobj);
void ftGw_Attack100Loop_Anim(HSD_GObj* gobj);
void ftGw_Attack100Loop_IASA(HSD_GObj* gobj);
void ftGw_Attack100Loop_Phys(HSD_GObj* gobj);
void ftGw_Attack100Loop_Coll(HSD_GObj* gobj);
void ftGw_Attack100End_Enter(HSD_GObj* gobj);
void ftGw_Attack100End_Anim(HSD_GObj* gobj);
void ftGw_Attack100End_IASA(HSD_GObj* gobj);
void ftGw_Attack100End_Phys(HSD_GObj* gobj);
void ftGw_Attack100End_Coll(HSD_GObj* gobj);

// Side Special - Judgement (SpecialS) //

void ftGw_SpecialS_ItemJudgementSetup(HSD_GObj* gobj);
void ftGw_SpecialS_ItemJudgementSetFlag(HSD_GObj* gobj);
void ftGw_SpecialS_ItemJudgementRemove(HSD_GObj* gobj);
bool ftGw_SpecialS_ItemCheckJudgementRemove(HSD_GObj* gobj);
int ftGw_SpecialS_GetRandomInt(HSD_GObj* gobj);
void ftGw_SpecialS_Enter(HSD_GObj* gobj);
void ftGw_SpecialAirS_Enter(HSD_GObj* gobj);
void ftGw_SpecialS_Anim(HSD_GObj* gobj);
void ftGw_SpecialAirS_Anim(HSD_GObj* gobj);
void ftGw_SpecialS_IASA(HSD_GObj* gobj);
void ftGw_SpecialAirS_IASA(HSD_GObj* gobj);
void ftGw_SpecialS_Phys(HSD_GObj* gobj);
void ftGw_SpecialAirS_Phys(HSD_GObj* gobj);
void ftGw_SpecialS_Coll(HSD_GObj* gobj);
void ftGw_SpecialAirS_Coll(HSD_GObj* gobj);

// Up Special - Fire Rescue (SpeciialHi) //

void ftGw_SpecialHi_ItemRescueSetup(HSD_GObj* gobj);
bool ftGw_SpecialHi_ItemCheckRescueRemove(HSD_GObj* gobj);
void ftGw_SpecialHi_ItemRescueSetNULL(HSD_GObj* gobj);
void ftGw_SpecialHi_ItemRescueRemove(HSD_GObj* gobj);
void ftGw_SpecialHi_Enter(HSD_GObj* gobj);
void ftGw_SpecialAirHi_Enter(HSD_GObj* gobj);
void ftGw_SpecialHi_Anim(HSD_GObj* gobj);
void ftGw_SpecialAirHi_Anim(HSD_GObj* gobj);
void ftGw_SpecialHi_IASA(HSD_GObj* gobj);
void ftGw_SpecialAirHi_IASA(HSD_GObj* gobj);
void ftGw_SpecialHi_Phys(HSD_GObj* gobj);
void ftGw_SpecialAirHi_Phys(HSD_GObj* gobj);
void ftGw_SpecialHi_Coll(HSD_GObj* gobj);
void ftGw_SpecialAirHi_Coll(HSD_GObj* gobj);

// Down Special - Oil Panic (SpecialLw) //

void ftGw_SpecialLw_ItemPanicSetup(HSD_GObj* gobj);
void ftGw_SpecialLw_ItemPanicSetFlag(HSD_GObj* gobj);
void ftGw_SpecialLw_ItemPanicRemove(HSD_GObj* gobj);
void ftGw_SpecialLw_ItemPanicEnterHitlag(HSD_GObj* gobj);
void ftGw_SpecialLw_ItemPanicExitHitlag(HSD_GObj* gobj);
bool ftGw_SpecialLw_ItemCheckPanicRemove(HSD_GObj* gobj);
void ftGw_SpecialLw_UpdateBucketModel(HSD_GObj* gobj);
void ftGw_SpecialLw_Enter(HSD_GObj* gobj);
void ftGw_SpecialAirLw_Enter(HSD_GObj* gobj);
void ftGw_SpecialLw_Anim(HSD_GObj* gobj);
void ftGw_SpecialAirLw_Anim(HSD_GObj* gobj);
void ftGw_SpecialLw_IASA(HSD_GObj* gobj);
void ftGw_SpecialAirLw_IASA(HSD_GObj* gobj);
void ftGw_SpecialLw_Phys(HSD_GObj* gobj);
void ftGw_SpecialAirLw_Phys(HSD_GObj* gobj);
void ftGw_SpecialLw_Coll(HSD_GObj* gobj);
void ftGw_SpecialAirLw_Coll(HSD_GObj* gobj);
void ftGw_SpecialLw_GroundToAir(HSD_GObj* gobj);
void ftGw_SpecialAirLw_AirToGround(HSD_GObj* gobj);
void ftGw_SpecialLw_UpdateAction(HSD_GObj* gobj, f32 animFrame);
void ftGw_SpecialAirLw_UpdateAction(HSD_GObj* gobj, f32 animFrame);
void ftGw_SpecialLwCatch_Anim(HSD_GObj* gobj);
void ftGw_SpecialAirLwCatch_Anim(HSD_GObj* gobj);
void ftGw_SpecialLwCatch_IASA(HSD_GObj* gobj);
void ftGw_SpecialAirLwCatch_IASA(HSD_GObj* gobj);
void ftGw_SpecialLwCatch_Phys(HSD_GObj* gobj);
void ftGw_SpecialAirLwCatch_Phys(HSD_GObj* gobj);
void ftGw_SpecialLwCatch_Coll(HSD_GObj* gobj);
void ftGw_SpecialAirLwCatch_Coll(HSD_GObj* gobj);
void ftGw_SpecialLwCatch_GroundToAir(HSD_GObj* gobj);
void ftGw_SpecialAirLwCatch_AirToGround(HSD_GObj* gobj);
void ftGw_SpecialLw_AbsorbThink_DecideAction(HSD_GObj* gobj);
void ftGw_SpecialLwShoot_Anim(HSD_GObj* gobj);
void ftGw_SpecialAirLwShoot_Anim(HSD_GObj* gobj);
void ftGw_SpecialLwShoot_IASA(HSD_GObj* gobj);
void ftGw_SpecialAirLwShoot_IASA(HSD_GObj* gobj);
void ftGw_SpecialLwShoot_Phys(HSD_GObj* gobj);
void ftGw_SpecialAirLwShoot_Phys(HSD_GObj* gobj);
void ftGw_SpecialLwShoot_Coll(HSD_GObj* gobj);
void ftGw_SpecialAirLwShoot_Coll(HSD_GObj* gobj);
void ftGw_SpecialLwShoot_GroundToAir(HSD_GObj* gobj);
void ftGw_SpecialAirLwShoot_AirToGround(HSD_GObj* gobj);
void ftGw_SpecialLwShoot_ReleaseOil(HSD_GObj* gobj);
void ftGw_SpecialAirLwShoot_ReleaseOil(HSD_GObj* gobj);

// Neutral Special - Chef (SpecialN/) //

void ftGw_SpecialN_Enter(HSD_GObj* gobj);
void ftGw_SpecialAirN_Enter(HSD_GObj* gobj);
void ftGw_SpecialN_Anim(HSD_GObj* gobj);
void ftGw_SpecialAirN_Anim(HSD_GObj* gobj);
void ftGw_SpecialN_IASA(HSD_GObj* gobj);
void ftGw_SpecialAirN_IASA(HSD_GObj* gobj);
void ftGw_SpecialN_Phys(HSD_GObj* gobj);
void ftGw_SpecialAirN_Phys(HSD_GObj* gobj);
void ftGw_SpecialN_Coll(HSD_GObj* gobj);
void ftGw_SpecialAirN_Coll(HSD_GObj* gobj);
void ftGw_SpecialN_GroundToAir(HSD_GObj* gobj);
void ftGw_SpecialAirN_AirToGround(HSD_GObj* gobj);
void ftGw_SpecialN_Loop(HSD_GObj* gobj, f32 anim_frame);
void ftGw_SpecialAirN_Loop(HSD_GObj* gobj, f32 anim_frame);
void ftGw_Init_LoadSpecialAttrs(HSD_GObj* gobj);

#endif
