#ifndef MELEE_FT_CHARA_FTMARIO_FTMARIO_SPECIALN_H
#define MELEE_FT_CHARA_FTMARIO_FTMARIO_SPECIALN_H

#include <platform.h>
#include "ft/forward.h"

int ftMr_SpecialN_VitaminRandom(HSD_GObj*);
void ftMr_SpecialN_Enter(HSD_GObj*);
void ftMr_SpecialN_Anim(HSD_GObj*);
void ftMr_SpecialN_IASA(HSD_GObj*);
void ftMr_SpecialN_Phys(HSD_GObj*);
void ftMr_SpecialN_Coll(HSD_GObj*);
void ftMr_SpecialN_ItemFireSpawn(HSD_GObj*);
void ftMr_SpecialAirN_Enter(HSD_GObj*);
void ftMr_SpecialAirN_Anim(HSD_GObj*);
void ftMr_SpecialAirN_IASA(HSD_GObj*);
void ftMr_SpecialAirN_Phys(HSD_GObj*);
void ftMr_SpecialAirN_Coll(HSD_GObj*);
void ftMr_SpecialN_GroundToAir(HSD_GObj*);
void ftMr_SpecialAirN_AirToGround(HSD_GObj*);

#endif
