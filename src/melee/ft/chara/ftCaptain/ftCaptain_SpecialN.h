#ifndef MELEE_FT_CHARA_FTCAPTAIN_FTCAPTAIN_SPECIALN_H
#define MELEE_FT_CHARA_FTCAPTAIN_FTCAPTAIN_SPECIALN_H

#include <melee/ft/forward.h>
#include <Runtime/platform.h>
#include <sysdolphin/baselib/forward.h>

void ftCaptain_SpecialN_CreateWindEffect(HSD_GObj* fighter_gobj);
f32 ftCaptain_SpecialN_GetAngleVel(Fighter* fp);
void ftCaptain_SpecialN_StartAction(HSD_GObj* fighter_gobj);
void ftCaptain_SpecialAirN_StartAction(HSD_GObj* fighter_gobj);
void ftCaptain_SpecialN_Anim(HSD_GObj* fighter_gobj);
void ftCaptain_SpecialAirN_Anim(HSD_GObj* fighter_gobj);
void ftCaptain_SpecialN_IASA(HSD_GObj* fighter_gobj);
void ftCaptain_SpecialAirN_IASA(HSD_GObj* fighter_gobj);
void ftCaptain_SpecialN_Phys(HSD_GObj* fighter_gobj);
void ftCaptain_SpecialAirN_Phys(HSD_GObj* fighter_gobj);
void ftCaptain_SpecialN_Coll(HSD_GObj* fighter_gobj);
void ftCaptain_SpecialAirN_Coll(HSD_GObj* fighter_gobj);

#endif
