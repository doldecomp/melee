/// @file
/// Side Special - Raptor Boost / Gerudo Dragon (SpecialS)
#ifndef MELEE_FT_CHARA_FTCAPTAIN_FTCAPTAIN_SPECIALS_H
#define MELEE_FT_CHARA_FTCAPTAIN_FTCAPTAIN_SPECIALS_H

#include "ft/forward.h"

#include <baselib/gobj.h>
#include <platform.h>

void ftCaptain_SpecialS_RemoveGFX(HSD_GObj* fighter_gobj);
void ftCaptain_SpecialS_StartAction(HSD_GObj* fighter_gobj);
void ftCaptain_SpecialAirS_StartAction(HSD_GObj* fighter_gobj);
void ftCaptain_SpecialS_OnDetect(HSD_GObj* fighter_gobj);
void ftCaptain_SpecialSStart_Anim(HSD_GObj* fighter_gobj);
void ftCaptain_SpecialS_Anim(HSD_GObj* fighter_gobj);
void ftCaptain_SpecialAirSStart_Anim(HSD_GObj* fighter_gobj);
void ftCaptain_SpecialAirS_Anim(HSD_GObj* fighter_gobj);
void ftCaptain_SpecialSStart_IASA(HSD_GObj* fighter_gobj);
void ftCaptain_SpecialS_IASA(HSD_GObj* fighter_gobj);
void ftCaptain_SpecialAirSStart_IASA(HSD_GObj* fighter_gobj);
void ftCaptain_SpecialAirS_IASA(HSD_GObj* fighter_gobj);
void ftCaptain_SpecialSStart_Phys(HSD_GObj* fighter_gobj);
void ftCaptain_SpecialS_Phys(HSD_GObj* fighter_gobj);
void ftCaptain_SpecialAirSStart_Phys(HSD_GObj* fighter_gobj);
void ftCaptain_SpecialAirS_Phys(HSD_GObj* fighter_gobj);
void ftCaptain_SpecialSStart_Coll(HSD_GObj* fighter_gobj);
void ftCaptain_SpecialS_Coll(HSD_GObj* fighter_gobj);
void ftCaptain_SpecialAirSStart_Coll(HSD_GObj* fighter_gobj);
void ftCaptain_SpecialAirS_Coll(HSD_GObj* fighter_gobj);
void ftCaptain_OnLoadForGanon(Fighter*);

#endif
