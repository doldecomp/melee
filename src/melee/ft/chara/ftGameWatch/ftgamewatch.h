#ifndef _ftgamewatch_h_
#define _ftgamewatch_h_

#include <melee/ft/ftcommon.h>
#include <melee/lb/lbvector.h>

#include <melee/ft/fighter.h>
#include <melee/it/item.h>
#include <melee/it/itkind.h>
#include <common_structs.h>

// Oil Panic Charge Level Macros //

#define GAMEWATCH_PANIC_EMPTY 0
#define GAMEWATCH_PANIC_LOW 1
#define GAMEWATCH_PANIC_MID 2
#define GAMEWATCH_PANIC_FULL 3

// Mr. Game & Watch Action State Change Flags //

// Chef (SpecialN/SpecialAirN) //
#define FTGAMEWATCH_SPECIALN_COLL_FLAG FIGHTER_HITSTATUS_COLANIM_PRESERVE | FIGHTER_HIT_NOUPDATE | FIGHTER_MODEL_NOUPDATE | FIGHTER_MATANIM_NOUPDATE | FIGHTER_COLANIM_NOUPDATE | FIGHTER_CMD_UPDATE | FIGHTER_ITEMVIS_NOUPDATE | FIGHTER_SKIP_UNK_0x2222 | FIGHTER_MODELPART_VIS_NOUPDATE | FIGHTER_MODEL_FLAG_NOUPDATE | FIGHTER_UNK_0x2227

// Judgement (SpecialS/SpecialAirS) //
#define FTGAMEWATCH_SPECIALS_COLL_FLAG FIGHTER_HITSTATUS_COLANIM_PRESERVE | FIGHTER_HIT_NOUPDATE | FIGHTER_MODEL_NOUPDATE | FIGHTER_MATANIM_NOUPDATE | FIGHTER_COLANIM_NOUPDATE | FIGHTER_CMD_UPDATE | FIGHTER_ITEMVIS_NOUPDATE | FIGHTER_SKIP_UNK_0x2222 | FIGHTER_MODELPART_VIS_NOUPDATE | FIGHTER_MODEL_FLAG_NOUPDATE | FIGHTER_UNK_0x2227

// Oil Panic (SpecialLw/SpecialAirLw) //
#define FTGAMEWATCH_SPECIALLW_COLL_FLAG FIGHTER_GFX_PRESERVE | FIGHTER_HITSTATUS_COLANIM_PRESERVE | FIGHTER_HIT_NOUPDATE | FIGHTER_MATANIM_NOUPDATE | FIGHTER_COLANIM_NOUPDATE | FIGHTER_CMD_UPDATE | FIGHTER_ITEMVIS_NOUPDATE | FIGHTER_SKIP_UNK_0x2222 | FIGHTER_MODELPART_VIS_NOUPDATE | FIGHTER_MODEL_FLAG_NOUPDATE | FIGHTER_UNK_0x2227

#define FTGAMEWATCH_SPECIALLW_UPDATE_FLAG FIGHTER_GFX_PRESERVE | FIGHTER_HIT_NOUPDATE | FIGHTER_MATANIM_NOUPDATE | FIGHTER_COLANIM_NOUPDATE | FIGHTER_CMD_UPDATE | FIGHTER_ITEMVIS_NOUPDATE | FIGHTER_SKIP_UNK_0x2222 | FIGHTER_MODELPART_VIS_NOUPDATE | FIGHTER_MODEL_FLAG_NOUPDATE | FIGHTER_UNK_0x2227

// Mr. Game & Watch Action State IDs //

typedef enum ftGameWatchAction
{
    AS_FTCOMMON = 340,
    AS_GAMEWATCH_ATTACK11,
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

typedef struct ftGameWatchChef
{
    s32 sausageCount[5];
} ftGameWatchChef;

typedef struct ftGameWatchJudge
{
    s32 rollVar[9];
} ftGameWatchJudge;

typedef struct _ftGameWatchAttributes {

    // MISC. ATTRIBUTES //

    f32 x0_GAMEWATCH_WIDTH; // Mr. Game & Watch's Z-Axis stretch; 0.01 by default
    s32 x4_GAMEWATCH_COLOR[4]; // Array of four RGBA values, one for each Mr. Game & Watch costume color
    s32 x14_GAMEWATCH_OUTLINE; // Outline color of Mr. Game & Watch's model

    // NEUTRAL SPECIAL - CHEF //

    f32 x18_GAMEWATCH_CHEF_LOOPFRAME; // Allow rapid-firing sausages from this frame onward
    f32 x1C_GAMEWATCH_CHEF_MAX; // Maximum amount of sausages created per Chef use

    // SIDE SPECIAL - JUDGEMENT //

    f32 x20_GAMEWATCH_JUDGE_MOMENTUM_PRESERVE; // Horizontal momentum preservation value 
    f32 x24_GAMEWATCH_JUDGE_MOMENTUM_MUL; // Multiplies momentum preservation value
    f32 x28_GAMEWATCH_JUDGE_VEL_Y;
    f32 x2C_GAMEWATCH_JUDGE_FRICTION1;
    f32 x30_GAMEWATCH_JUDGE_FRICTION2;
    s32 x34_GAMEWATCH_JUDGE_ROLL[9]; // Array of BOOLs that toggle respective Judgement numbers ON/OFF. If a number is OFF, it is excluded from RNG rolls. Game panics if less than 2 numbers are ON.

    // UP SPECIAL - FIRE RESCUE //

    f32 x58_GAMEWATCH_RESCUE_STICK_RANGE; // Minimum control stick range required for directional influence? Also affects how far Mr. Game & Watch flings horizontally (?)
    f32 x5C_GAMEWATCH_RESCUE_ANGLE_UNK; // Radians -- controls how far Mr. Game & Watch can angle Fire Rescue? 
    f32 x60_GAMEWATCH_RESCUE_LANDING; // Landing lag / Freefall toggle

    // DOWN SPECIAL - OIL PANIC //

    f32 x64_GAMEWATCH_PANIC_MOMENTUM_PRESERVE; // Horizontal momentum preservation value 
    f32 x68_GAMEWATCH_PANIC_MOMENTUM_MUL; // Multiplies momentum preservation value
    f32 x6C_GAMEWATCH_PANIC_FALL_ACCEL; // Falling acceleration
    f32 x70_GAMEWATCH_PANIC_VEL_Y_MAX; // Terminal Y velocity? 
    f32 x74_GAMEWATCH_PANIC_DAMAGE_ADD; // Extra damage added to Oil Panic after formula
    f32 x78_GAMEWATCH_PANIC_DAMAGE_MUL; // Damage multiplier
    f32 x7C_GAMEWATCH_PANIC_TURN_FRAMES;
    AbsorbDesc x80_GAMEWATCH_PANIC_ABSORPTION; // Oil Panic absorption attributes

} ftGameWatchAttributes;


// Mr. Game & Watch Functions //

// General callbacks //

void ftGameWatch_OnDeath(HSD_GObj* fighter_gobj);
void ftGameWatch_OnLoad(HSD_GObj* fighter_gobj);
void ftGameWatch_OnDamage(HSD_GObj* fighter_gobj);
void ftGameWatch_8014A538(HSD_GObj* fighter_gobj);
void ftGameWatch_OnItemPickup(HSD_GObj* gobj, BOOL arg1);
void func_8014A698(HSD_GObj* fighter_gobj);
void func_8014A6E0(HSD_GObj* fighter_gobj);
void ftGameWatch_OnItemDrop(HSD_GObj* fighter_gobj, s32 dropItemFlag);
void ftGameWatch_8014A77C(HSD_GObj* fighter_gobj);
void ftGameWatch_CopySpecialAttrs(HSD_GObj* fighter_gobj);
void ftGameWatch_8014A7F4(HSD_GObj* fighter_gobj, ItemModStruct* item_mod);
void ftGameWatch_8014A814(HSD_GObj* fighter_gobj, ItemModStruct* item_mod);
void ftGameWatch_OnAbsorb(HSD_GObj* fighter_gobj);

// Item-related callbacks //

void ftGameWatch_ItemTorchSetup(HSD_GObj* fighter_gobj);
void ftGameWatch_ItemTorchSetFlag(HSD_GObj* fighter_gobj);
void ftGameWatch_ItemTorchOnDamage(HSD_GObj* fighter_gobj);
void ftGameWatch_ItemTorchEnterHitlag(HSD_GObj* fighter_gobj);
void ftGameWatch_ItemTorchExitHitlag(HSD_GObj* fighter_gobj);
BOOL ftGameWatch_ItemCheckTorchRemove(HSD_GObj* fighter_gobj);

// Forward Smash (AttackS4) //

void ftGameWatch_AttackS4_Action(HSD_GObj* fighter_gobj);
void ftGameWatch_AttackS4_Anim(HSD_GObj* fighter_gobj);
void ftGameWatch_AttackS4_IASA(HSD_GObj* fighter_gobj);
void ftGameWatch_AttackS4_Phys(HSD_GObj* fighter_gobj);
void ftGameWatch_AttackS4_Coll(HSD_GObj* fighter_gobj);

// Down Tilt (AttackLw3) //

void ftGameWatch_ItemManholeSetup(HSD_GObj* fighter_gobj);
void ftGameWatch_ItemManholeRemove(HSD_GObj* fighter_gobj);
void ftGameWatch_ItemManholeOnDamage(HSD_GObj* fighter_gobj);
void ftGameWatch_ItemManholeEnterHitlag(HSD_GObj* fighter_gobj);
void ftGameWatch_ItemManholeExitHitlag(HSD_GObj* fighter_gobj);
BOOL ftGameWatch_ItemCheckManholeRemove(HSD_GObj* fighter_gobj);
void ftGameWatch_AttackLw3_Action(HSD_GObj* fighter_gobj);
void ftGameWatch_AttackLw3_Anim(HSD_GObj* fighter_gobj);
void ftGameWatch_AttackLw3_IASA(HSD_GObj* fighter_gobj);
void ftGameWatch_AttackLw3_Phys(HSD_GObj* fighter_gobj);
void ftGameWatch_AttackLw3_Coll(HSD_GObj* fighter_gobj);

// Aerial Attack Item Setup (AttackAirN) //

void ftGameWatch_ItemParachuteSetup(HSD_GObj* fighter_gobj);
void ftGameWatch_ItemParachuteOnLand(HSD_GObj* fighter_gobj);
void ftGameWatch_ItemParachuteSetFlag(HSD_GObj* fighter_gobj);
void ftGameWatch_ItemParachuteRemove(HSD_GObj* fighter_gobj);
BOOL ftGameWatch_ItemCheckParachuteRemove(HSD_GObj* fighter_gobj);
void ftGameWatch_ItemTurtleSetup(HSD_GObj* fighter_gobj);
void ftGameWatch_ItemTurtleOnLand(HSD_GObj* fighter_gobj);
void ftGameWatch_ItemTurtleSetFlag(HSD_GObj* fighter_gobj);
void ftGameWatch_ItemTurtleRemove(HSD_GObj* fighter_gobj);
BOOL ftGameWatch_ItemCheckTurtleRemove(HSD_GObj* fighter_gobj);
void ftGameWatch_ItemSparkySetup(HSD_GObj* fighter_gobj);
void ftGameWatch_ItemSparkyOnLand(HSD_GObj* fighter_gobj);
void ftGameWatch_ItemSparkySetFlag(HSD_GObj* fighter_gobj);
void ftGameWatch_ItemSparkyRemove(HSD_GObj* fighter_gobj);
void ftGameWatch_AttackAir_EnterItemHitlag(HSD_GObj* fighter_gobj);
void ftGameWatch_AttackAir_ExitItemHitlag(HSD_GObj* fighter_gobj);
BOOL ftGameWatch_ItemCheckSparkyRemove(HSD_GObj* fighter_gobj);
void ftGameWatch_AttackAir_DecideAction(HSD_GObj* fighter_gobj);

// Aerial Attacks (AttackAir) //

void ftGameWatch_AttackAirN_Action(HSD_GObj* fighter_gobj, s32 ASID);
void ftGameWatch_AttackAirN_Anim(HSD_GObj* fighter_gobj);
void ftGameWatch_AttackAirN_IASA(HSD_GObj* fighter_gobj);
void ftGameWatch_AttackAirN_Phys(HSD_GObj* fighter_gobj);
void ftGameWatch_AttackAirN_Coll(HSD_GObj* fighter_gobj);
void ftGameWatch_LandingAirN_Action(HSD_GObj* fighter_gobj);
void ftGameWatch_AttackAirB_Action(HSD_GObj* fighter_gobj, s32 ASID);
void ftGameWatch_AttackAirB_Anim(HSD_GObj* fighter_gobj);
void ftGameWatch_AttackAirB_IASA(HSD_GObj* fighter_gobj);
void ftGameWatch_AttackAirB_Phys(HSD_GObj* fighter_gobj);
void ftGameWatch_AttackAirB_Coll(HSD_GObj* fighter_gobj);
void ftGameWatch_LandingAirB_Action(HSD_GObj* fighter_gobj);
void ftGameWatch_AttackAirHi_Action(HSD_GObj* fighter_gobj, s32 ASID);
void ftGameWatch_AttackAirHi_Anim(HSD_GObj* fighter_gobj);
void ftGameWatch_AttackAirHi_IASA(HSD_GObj* fighter_gobj);
void ftGameWatch_AttackAirHi_Phys(HSD_GObj* fighter_gobj);
void ftGameWatch_AttackAirHi_Coll(HSD_GObj* fighter_gobj);
void ftGameWatch_LandingAirHi_Action(HSD_GObj* fighter_gobj);
void ftGameWatch_LandingAirN_Init(HSD_GObj* fighter_gobj);
void ftGameWatch_LandingAirN_Anim(HSD_GObj* fighter_gobj);
void ftGameWatch_LandingAirN_IASA(HSD_GObj* fighter_gobj);
void ftGameWatch_LandingAirN_Phys(HSD_GObj* fighter_gobj);
void ftGameWatch_LandingAirN_Coll(HSD_GObj* fighter_gobj);
void ftGameWatch_LandingAirB_Init(HSD_GObj* fighter_gobj);
void ftGameWatch_LandingAirB_Anim(HSD_GObj* fighter_gobj);
void ftGameWatch_LandingAirB_IASA(HSD_GObj* fighter_gobj);
void ftGameWatch_LandingAirB_Phys(HSD_GObj* fighter_gobj);
void ftGameWatch_LandingAirB_Coll(HSD_GObj* fighter_gobj);
void ftGameWatch_LandingAirHi_Init(HSD_GObj* fighter_gobj);
void ftGameWatch_LandingAirHi_Anim(HSD_GObj* fighter_gobj);
void ftGameWatch_LandingAirHi_IASA(HSD_GObj* fighter_gobj);
void ftGameWatch_LandingAirHi_Phys(HSD_GObj* fighter_gobj);
void ftGameWatch_LandingAirHi_Coll(HSD_GObj* fighter_gobj);

// Neutral Attack - Greenhouse (Attack11, Attack100Start/Loop/End) //

void ftGameWatch_ItemGreenhouseSetup(HSD_GObj* fighter_gobj);
void ftGameWatch_Attack11_DecideAction(HSD_GObj* fighter_gobj);
void ftGameWatch_ItemGreenhouseSetFlag(HSD_GObj* fighter_gobj);
void ftGameWatch_ItemGreenhouseRemove(HSD_GObj* fighter_gobj);
void ftGameWatch_ItemGreenhouseEnterHitlag(HSD_GObj* fighter_gobj);
void ftGameWatch_ItemGreenhouseExitHitlag(HSD_GObj* fighter_gobj);
BOOL ftGameWatch_ItemGreenhouse_CheckAll(HSD_GObj* fighter_gobj);
BOOL ftGameWatch_ItemGreenhouse_CheckAttack11(HSD_GObj* fighter_gobj);
void ftGameWatch_Attack11_Action(HSD_GObj* fighter_gobj);
void ftGameWatch_Attack11_Anim(HSD_GObj* fighter_gobj);
void ftGameWatch_Attack11_IASA(HSD_GObj* fighter_gobj);
void ftGameWatch_Attack11_Phys(HSD_GObj* fighter_gobj);
void ftGameWatch_Attack11_Coll(HSD_GObj* fighter_gobj);
void ftGameWatch_Attack100Start_Action(HSD_GObj* fighter_gobj);
void ftGameWatch_Attack100Start_Anim(HSD_GObj* fighter_gobj);
void ftGameWatch_Attack100Start_IASA(HSD_GObj* fighter_gobj);
void ftGameWatch_Attack100Start_Phys(HSD_GObj* fighter_gobj);
void ftGameWatch_Attack100Start_Coll(HSD_GObj* fighter_gobj);
void ftGameWatch_Attack100Loop_Action(HSD_GObj* fighter_gobj);
void ftGameWatch_Attack100Loop_Anim(HSD_GObj* fighter_gobj);
void ftGameWatch_Attack100Loop_IASA(HSD_GObj* fighter_gobj);
void ftGameWatch_Attack100Loop_Phys(HSD_GObj* fighter_gobj);
void ftGameWatch_Attack100Loop_Coll(HSD_GObj* fighter_gobj);
void ftGameWatch_Attack100End_Action(HSD_GObj* fighter_gobj);
void ftGameWatch_Attack100End_Anim(HSD_GObj* fighter_gobj);
void ftGameWatch_Attack100End_IASA(HSD_GObj* fighter_gobj);
void ftGameWatch_Attack100End_Phys(HSD_GObj* fighter_gobj);
void ftGameWatch_Attack100End_Coll(HSD_GObj* fighter_gobj);

// Side Special - Judgement (SpecialS) //

void ftGameWatch_ItemJudgementSetup(HSD_GObj* fighter_gobj);
void ftGameWatch_ItemJudgementSetFlag(HSD_GObj* fighter_gobj);
void ftGameWatch_ItemJudgementRemove(HSD_GObj* fighter_gobj);
void ftGameWatch_ItemJudgementEnterHitlag(HSD_GObj* fighter_gobj);
void ftGameWatch_ItemJudgementExitHitlag(HSD_GObj* fighter_gobj);
BOOL ftGameWatch_ItemCheckJudgementRemove(HSD_GObj* fighter_gobj);
s32 ftGameWatch_SpecialS_GetRandomInt(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialS_StartAction(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialAirS_StartAction(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialS_Anim(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialAirS_Anim(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialS_IASA(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialAirS_IASA(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialS_Phys(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialAirS_Phys(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialS_Coll(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialAirS_Coll(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialS_GroundToAir(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialAirS_AirToGround(HSD_GObj* fighter_gobj);

// Up Special - Fire Rescue (SpeciialHi) //

void ftGameWatch_ItemRescueSetup(HSD_GObj* fighter_gobj);
BOOL ftGameWatch_ItemCheckRescueRemove(HSD_GObj* fighter_gobj);
void ftGameWatch_ItemRescueSetNULL(HSD_GObj* fighter_gobj);
void ftGameWatch_ItemRescueRemove(HSD_GObj* fighter_gobj);
void ftGameWatch_ItemRescueEnterHitlag(HSD_GObj* fighter_gobj);
void ftGameWatch_ItemRescueExitHitlag(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialHi_StartAction(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialAirHi_StartAction(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialHi_Anim(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialAirHi_Anim(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialHi_IASA(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialAirHi_IASA(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialHi_Phys(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialAirHi_Phys(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialHi_Coll(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialAirHi_Coll(HSD_GObj* fighter_gobj);

// Down Special - Oil Panic (SpecialLw) //

void ftGameWatch_ItemPanicSetup(HSD_GObj* fighter_gobj);
void ftGameWatch_ItemPanicSetFlag(HSD_GObj* fighter_gobj);
void ftGameWatch_ItemPanicRemove(HSD_GObj* fighter_gobj);
void ftGameWatch_ItemPanicEnterHitlag(HSD_GObj* fighter_gobj);
void ftGameWatch_ItemPanicExitHitlag(HSD_GObj* fighter_gobj);
BOOL ftGameWatch_ItemCheckPanicRemove(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialLw_UpdateBucketModel(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialLw_StartAction(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialAirLw_StartAction(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialLw_Anim(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialAirLw_Anim(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialLw_IASA(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialAirLw_IASA(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialLw_Phys(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialAirLw_Phys(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialLw_Coll(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialAirLw_Coll(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialLw_GroundToAir(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialAirLw_AirToGround(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialLw_UpdateAction(HSD_GObj* fighter_gobj, f32 animFrame);
void ftGameWatch_SpecialAirLw_UpdateAction(HSD_GObj* fighter_gobj, f32 animFrame);
void ftGameWatch_SpecialLwCatch_Anim(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialAirLwCatch_Anim(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialLwCatch_IASA(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialAirLwCatch_IASA(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialLwCatch_Phys(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialAirLwCatch_Phys(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialLwCatch_Coll(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialAirLwCatch_Coll(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialLwCatch_GroundToAir(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialAirLwCatch_AirToGround(HSD_GObj* fighter_gobj);
void ftGameWatch_AbsorbThink_DecideAction(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialLwShoot_Anim(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialAirLwShoot_Anim(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialLwShoot_IASA(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialAirLwShoot_IASA(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialLwShoot_Phys(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialAirLwShoot_Phys(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialLwShoot_Coll(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialAirLwShoot_Coll(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialLwShoot_GroundToAir(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialAirLwShoot_AirToGround(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialLwShoot_ReleaseOil(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialAirLwShoot_ReleaseOil(HSD_GObj* fighter_gobj);

// Neutral Special - Chef (SpecialN/) //
void ftGameWatch_SpecialN_CreateSausage(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialN_StartAction(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialAirN_StartAction(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialN_Anim(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialAirN_Anim(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialN_IASA(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialAirN_IASA(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialN_Phys(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialAirN_Phys(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialN_Coll(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialAirN_Coll(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialN_GroundToAir(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialAirN_AirToGround(HSD_GObj* fighter_gobj);
void ftGameWatch_SpecialN_Loop(HSD_GObj* fighter_gobj, f32 anim_frame);
void ftGameWatch_SpecialAirN_Loop(HSD_GObj* fighter_gobj, f32 anim_frame);

#endif