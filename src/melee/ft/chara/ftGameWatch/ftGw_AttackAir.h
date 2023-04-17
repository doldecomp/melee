/// @file Aerial Attacks (AttackAir)
#ifndef MELEE_FT_CHARA_FTGAMEWATCH_FTGAMEWATCH_ATTACKAIR_H
#define MELEE_FT_CHARA_FTGAMEWATCH_FTGAMEWATCH_ATTACKAIR_H

#include <platform.h>
#include <baselib/forward.h>

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

#endif
