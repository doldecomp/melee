/// @file Neutral Special - Chef (SpecialN/)
#ifndef MELEE_FT_CHARA_FTGAMEWATCH_FTGAMEWATCH_SPECIALN_H
#define MELEE_FT_CHARA_FTGAMEWATCH_FTGAMEWATCH_SPECIALN_H

#include <platform.h>
#include <baselib/forward.h>

f32 ftGameWatch_SpecialN_SetFloatOrder1(void);
f32 ftGameWatch_SpecialN_SetFloatOrder2(void);
f32 ftGameWatch_SpecialN_SetFloatOrder3(void);
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
