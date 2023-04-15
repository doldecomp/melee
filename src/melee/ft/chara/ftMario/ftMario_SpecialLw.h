#ifndef MELEE_FT_CHARA_FTMARIO_FTMARIO_SPECIALLW_H
#define MELEE_FT_CHARA_FTMARIO_FTMARIO_SPECIALLW_H

#include <platform.h>
#include <baselib/forward.h>

void ftMr_SpecialLw_UpdateRot(HSD_GObj* gobj);
void ftMr_SpecialLw_StartMotion(HSD_GObj* gobj);
void ftMr_SpecialAirLw_StartMotion(HSD_GObj* gobj);
void ftMr_SpecialLw_Anim(HSD_GObj* gobj);
void ftMr_SpecialAirLw_Anim(HSD_GObj* gobj);
void ftMr_SpecialLw_IASA(HSD_GObj* gobj);
void ftMr_SpecialAirLw_IASA(HSD_GObj* gobj);
void ftMr_SpecialLw_Phys(HSD_GObj* gobj);
void ftMr_SpecialAirLw_Phys(HSD_GObj* gobj);
void ftMr_SpecialLw_Coll(HSD_GObj* gobj);
void ftMr_SpecialAirLw_Coll(HSD_GObj* gobj);

#endif
