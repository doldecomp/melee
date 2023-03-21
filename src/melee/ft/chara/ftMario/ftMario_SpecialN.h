#ifndef MELEE_FT_CHARA_FTMARIO_FTMARIO_SPECIALN_H
#define MELEE_FT_CHARA_FTMARIO_FTMARIO_SPECIALN_H

#include <platform.h>
#include "ft/forward.h"

int ftMario_SpecialN_VitaminRandom(HSD_GObj*);
void ftMario_SpecialN_StartAction(HSD_GObj*);
void ftMario_SpecialN_Anim(HSD_GObj*);
void ftMario_SpecialN_IASA(HSD_GObj*);
void ftMario_SpecialN_Phys(HSD_GObj*);
void ftMario_SpecialN_Coll(HSD_GObj*);
void ftMario_SpecialN_ItemFireSpawn(HSD_GObj*);
void ftMario_SpecialAirN_StartAction(HSD_GObj*);
void ftMario_SpecialAirN_Anim(HSD_GObj*);
void ftMario_SpecialAirN_IASA(HSD_GObj*);
void ftMario_SpecialAirN_Phys(HSD_GObj*);
void ftMario_SpecialAirN_Coll(HSD_GObj*);
void ftMario_SpecialN_GroundToAir(HSD_GObj*);
void ftMario_SpecialAirN_AirToGround(HSD_GObj*);

#endif
