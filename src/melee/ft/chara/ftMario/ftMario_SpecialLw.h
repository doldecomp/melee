#ifndef MELEE_FT_CHARA_FTMARIO_FTMARIO_SPECIALLW_H
#define MELEE_FT_CHARA_FTMARIO_FTMARIO_SPECIALLW_H

#include <baselib/forward.h>

#include <platform.h>

void ftMario_SpecialLw_UpdateRot(HSD_GObj* gobj);
void ftMario_SpecialLw_StartAction(HSD_GObj* gobj);
void ftMario_SpecialAirLw_StartAction(HSD_GObj* gobj);
void ftMario_SpecialLw_Anim(HSD_GObj* gobj);
void ftMario_SpecialAirLw_Anim(HSD_GObj* gobj);
void ftMario_SpecialLw_IASA(HSD_GObj* gobj);
void ftMario_SpecialAirLw_IASA(HSD_GObj* gobj);
void ftMario_SpecialLw_Phys(HSD_GObj* gobj);
void ftMario_SpecialAirLw_Phys(HSD_GObj* gobj);
void ftMario_SpecialLw_Coll(HSD_GObj* gobj);
void ftMario_SpecialAirLw_Coll(HSD_GObj* gobj);

#endif
