/// @file Up Special - Fire Rescue (SpeciialHi)
#ifndef MELEE_FT_CHARA_FTGAMEWATCH_FTGAMEWATCH_SPECIALHI_H
#define MELEE_FT_CHARA_FTGAMEWATCH_FTGAMEWATCH_SPECIALHI_H

#include <platform.h>
#include <baselib/forward.h>

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

#endif
