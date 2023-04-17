/// @file Side Special - Judgement (SpecialS)
#ifndef MELEE_FT_CHARA_FTGAMEWATCH_FTGAMEWATCH_SPECIALS_H
#define MELEE_FT_CHARA_FTGAMEWATCH_FTGAMEWATCH_SPECIALS_H

#include <platform.h>
#include <baselib/forward.h>

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

#endif
