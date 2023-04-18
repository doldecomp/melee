#ifndef MELEE_FT_CHARA_FTGAMEWATCH_FTGAMEWATCH_INIT_H
#define MELEE_FT_CHARA_FTGAMEWATCH_FTGAMEWATCH_INIT_H

#include "ft/types.h"

extern MotionState ftGw_Init_MotionStateTable[];
extern char ftGw_Init_DatFilename[];
extern char ftGw_Init_DataName[];
extern Fighter_CostumeStrings ftGw_Init_CostumeStrings[];
extern char ftGw_Init_AnimDatFilename[];
extern Fighter_DemoStrings ftGw_Init_DemoMotionFilenames;

// Mr. Game & Watch Functions

// General callbacks

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

// Item-related callbacks

void ftGw_ItemTorchSetup(HSD_GObj* gobj);
void ftGw_AttackS4_ItemTorchSetFlag(HSD_GObj* gobj);
void ftGw_AttackS4_ItemTorchOnDamage(HSD_GObj* gobj);
void ftGw_AttackS4_ItemTorchEnterHitlag(HSD_GObj* gobj);
void ftGw_AttackS4_ItemTorchExitHitlag(HSD_GObj* gobj);
bool ftGw_AttackS4_ItemCheckTorchRemove(HSD_GObj* gobj);

// Forward Smash (AttackS4)

void ftGw_AttackS4_Enter(HSD_GObj* gobj);
void ftGw_AttackS4_Anim(HSD_GObj* gobj);
void ftGw_AttackS4_IASA(HSD_GObj* gobj);
void ftGw_AttackS4_Phys(HSD_GObj* gobj);
void ftGw_AttackS4_Coll(HSD_GObj* gobj);

// Down Tilt (AttackLw3)

void ftGw_AttackLw3_ItemManholeSetup(HSD_GObj* gobj);
void ftGw_AttackLw3_ItemManholeRemove(HSD_GObj* gobj);
void ftGw_AttackLw3_ItemManholeOnDamage(HSD_GObj* gobj);
bool ftGw_AttackLw3_ItemCheckManholeRemove(HSD_GObj* gobj);
void ftGw_AttackLw3_Enter(HSD_GObj* gobj);
void ftGw_AttackLw3_Anim(HSD_GObj* gobj);
void ftGw_AttackLw3_IASA(HSD_GObj* gobj);
void ftGw_AttackLw3_Phys(HSD_GObj* gobj);
void ftGw_AttackLw3_Coll(HSD_GObj* gobj);

// Aerial Attack Item Setup (AttackAirN)

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

// Aerial Attacks (AttackAir)

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

// Neutral Attack - Greenhouse (Attack11, Attack100Start/Loop/End)

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

// Side Special - Judgement (SpecialS)

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

// Up Special - Fire Rescue (SpeciialHi)

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

// Down Special - Oil Panic (SpecialLw)

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

// Neutral Special - Chef (SpecialN/)

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
