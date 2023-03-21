#ifndef MELEE_FT_CHARA_FTMARIO_FTMARIO_SPECIALS_H
#define MELEE_FT_CHARA_FTMARIO_FTMARIO_SPECIALS_H

#include <baselib/forward.h>
#include <melee/ft/forward.h>
#include <Runtime/platform.h>

bool ftMario_SpecialS_CheckItemCapeRemove(HSD_GObj* gobj);
void ftMario_SpecialAirS_AirToGround(HSD_GObj* gobj);
void ftMario_SpecialAirS_Anim(HSD_GObj* gobj);
void ftMario_SpecialAirS_Coll(HSD_GObj* gobj);
void ftMario_SpecialAirS_IASA(HSD_GObj* gobj);
void ftMario_SpecialAirS_Phys(HSD_GObj* gobj);
void ftMario_SpecialAirS_StartAction(HSD_GObj* gobj);
void ftMario_SpecialS_Anim(HSD_GObj* gobj);
void ftMario_SpecialS_Coll(HSD_GObj* gobj);
void ftMario_SpecialS_CreateCape(HSD_GObj* gobj);
void ftMario_SpecialS_EnterHitlag(HSD_GObj* gobj);
void ftMario_SpecialS_ExitHitlag(HSD_GObj* gobj);
void ftMario_SpecialS_GroundToAir(HSD_GObj* gobj);
void ftMario_SpecialS_IASA(HSD_GObj* gobj);
void ftMario_SpecialS_Phys(HSD_GObj* gobj);
void ftMario_SpecialS_ReflectThink(HSD_GObj* gobj);
void ftMario_SpecialS_RemoveCape(HSD_GObj* gobj);
void ftMario_SpecialS_SetCall(Fighter* fp);
void ftMario_SpecialS_SetNULL(HSD_GObj* gobj);
void ftMario_SpecialS_StartAction(HSD_GObj* gobj);
void ftMario_SpecialS_UpdateVarsColl(HSD_GObj* gobj);

#endif
