/// @file Neutral Attack - Greenhouse (Attack11)
#ifndef MELEE_FT_CHARA_FTGAMEWATCH_FTGAMEWATCH_ATTACK11_H
#define MELEE_FT_CHARA_FTGAMEWATCH_FTGAMEWATCH_ATTACK11_H

#include <platform.h>
#include <baselib/forward.h>

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

#endif
