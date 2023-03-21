#ifndef MELEE_FT_CHARA_FTMARIO_FTMARIO_SPECIALHI_H
#define MELEE_FT_CHARA_FTMARIO_FTMARIO_SPECIALHI_H

#include <baselib/forward.h>

void ftMario_SpecialHi_StartMotion(HSD_GObj* gobj);
void ftMario_SpecialAirHi_StartMotion(HSD_GObj* gobj);
void ftMario_SpecialHi_Anim(HSD_GObj* gobj);
void ftMario_SpecialAirHi_Anim(HSD_GObj* gobj);
void ftMario_SpecialHi_IASA(HSD_GObj* gobj);
void ftMario_SpecialAirHi_IASA(HSD_GObj* gobj);
void ftMario_SpecialHi_Phys(HSD_GObj* gobj);
void ftMario_SpecialAirHi_Phys(HSD_GObj* gobj);
void ftMario_SpecialHi_CheckLanding(HSD_GObj* gobj);
void ftMario_SpecialHi_Coll(HSD_GObj* gobj);
void ftMario_SpecialAirHi_Coll(HSD_GObj* gobj);

#endif
