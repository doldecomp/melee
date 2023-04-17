#ifndef MELEE_FT_CHARA_FTDONKEY_FTDONKEY_SPECIALHI_H
#define MELEE_FT_CHARA_FTDONKEY_FTDONKEY_SPECIALHI_H

#include <baselib/gobj.h>

void ftDk_SpecialHi_DestroyAllEffects_SpecialHi(HSD_GObj* gobj);

void ftDonkey_SetCallbacks_SpecialHi(HSD_GObj* gobj);
void ftDk_SpecialHi_Coll(HSD_GObj* gobj);
void ftDk_SpecialAirHi_Coll(HSD_GObj* gobj);
void ftDk_SpecialHi_DestroyAllEffects_SpecialHi(HSD_GObj* gobj);
void ftDk_SpecialHi_Enter(HSD_GObj* gobj);
void ftDk_SpecialAirHi_Enter(HSD_GObj* gobj);
void ftDk_SpecialHi_Anim(HSD_GObj* gobj);
void ftDk_SpecialAirHi_Anim(HSD_GObj* gobj);
void ftDk_SpecialHi_IASA(HSD_GObj* gobj);
void ftDk_SpecialAirHi_IASA(HSD_GObj* gobj);
void ftDk_SpecialHi_Phys(HSD_GObj* gobj);
void ftDk_SpecialAirHi_Phys(HSD_GObj* gobj);

#endif
