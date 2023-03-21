/// @file
/// Neutral Special - Falcon/Warlock Punch (SpecialN)
#ifndef MELEE_FT_CHARA_FTCAPTAIN_FTCAPTAIN_SPECIALN_H
#define MELEE_FT_CHARA_FTCAPTAIN_FTCAPTAIN_SPECIALN_H

#include <platform.h>
#include "ft/forward.h"
#include <baselib/forward.h>

f32 ftCaptain_SpecialN_GetAngleVel(Fighter* fp);
void ftCaptain_SpecialAirN_Anim(HSD_GObj* gobj);
void ftCaptain_SpecialAirN_Coll(HSD_GObj* gobj);
void ftCaptain_SpecialAirN_IASA(HSD_GObj* gobj);
void ftCaptain_SpecialAirN_Phys(HSD_GObj* gobj);
void ftCaptain_SpecialAirN_StartAction(HSD_GObj* gobj);
void ftCaptain_SpecialN_Anim(HSD_GObj* gobj);
void ftCaptain_SpecialN_Coll(HSD_GObj* gobj);
void ftCaptain_SpecialN_CreateWindEffect(HSD_GObj* gobj);
void ftCaptain_SpecialN_IASA(HSD_GObj* gobj);
void ftCaptain_SpecialN_Phys(HSD_GObj* gobj);
void ftCaptain_SpecialN_StartAction(HSD_GObj* gobj);

#endif
