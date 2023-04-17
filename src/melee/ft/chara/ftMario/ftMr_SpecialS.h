#ifndef MELEE_FT_CHARA_FTMARIO_FTMARIO_SPECIALS_H
#define MELEE_FT_CHARA_FTMARIO_FTMARIO_SPECIALS_H

#include <platform.h>
#include "ft/forward.h"
#include <baselib/forward.h>

bool ftMr_SpecialS_CheckItemCapeRemove(HSD_GObj* gobj);
void ftMario_SpecialS_ReflectThink(HSD_GObj* gobj);
void ftMario_SpecialS_SetCall(Fighter* fp);
void ftMario_SpecialS_UpdateVarsColl(HSD_GObj* gobj);
void ftMr_SpecialAirS_AirToGround(HSD_GObj* gobj);
void ftMr_SpecialAirS_Anim(HSD_GObj* gobj);
void ftMr_SpecialAirS_Coll(HSD_GObj* gobj);
void ftMr_SpecialAirS_Enter(HSD_GObj* gobj);
void ftMr_SpecialAirS_IASA(HSD_GObj* gobj);
void ftMr_SpecialAirS_Phys(HSD_GObj* gobj);
void ftMr_SpecialS_Anim(HSD_GObj* gobj);
void ftMr_SpecialS_Coll(HSD_GObj* gobj);
void ftMr_SpecialS_CreateCape(HSD_GObj* gobj);
void ftMr_SpecialS_Enter(HSD_GObj* gobj);
void ftMr_SpecialS_EnterHitlag(HSD_GObj* gobj);
void ftMr_SpecialS_ExitHitlag(HSD_GObj* gobj);
void ftMr_SpecialS_GroundToAir(HSD_GObj* gobj);
void ftMr_SpecialS_IASA(HSD_GObj* gobj);
void ftMr_SpecialS_Phys(HSD_GObj* gobj);
void ftMr_SpecialS_RemoveCape(HSD_GObj* gobj);
void ftMr_SpecialS_SetNULL(HSD_GObj* gobj);

#endif
