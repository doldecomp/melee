#ifndef MELEE_FT_CHARA_FTMARIO_FTMARIO_SPECIALS_H
#define MELEE_FT_CHARA_FTMARIO_FTMARIO_SPECIALS_H

#include <platform.h>
#include "ft/forward.h"
#include <baselib/forward.h>

/* 0e1248*/ void ftMr_SpecialS_CreateCape(HSD_GObj* gobj);
/* 0e132c*/ void ftMr_SpecialS_Reset(HSD_GObj* gobj);
/* 0e1368*/ void ftMr_SpecialS_RemoveCape(HSD_GObj* gobj);
/* 0e13c8*/ void ftMr_SpecialS_EnterHitlag(HSD_GObj* gobj);
/* 0e13f8*/ void ftMr_SpecialS_ExitHitlag(HSD_GObj* gobj);
/* 0e1428*/ bool ftMr_SpecialS_CheckItemCapeRemove(HSD_GObj* gobj);
/* 0e1450*/ void ftMr_SpecialS_Enter(HSD_GObj* gobj);
/* 0e14c8*/ void ftMr_SpecialAirS_Enter(HSD_GObj* gobj);
/* 0e1550*/ void ftMr_SpecialS_Anim(HSD_GObj* gobj);
/* 0e158c*/ void ftMr_SpecialAirS_Anim(HSD_GObj* gobj);
/* 0e15c8*/ void ftMr_SpecialS_IASA(HSD_GObj* gobj);
/* 0e15cc*/ void ftMr_SpecialAirS_IASA(HSD_GObj* gobj);
/* 0e15d0*/ void ftMr_SpecialS_Phys(HSD_GObj* gobj);
/* 0e16e0*/ void ftMr_SpecialAirS_Phys(HSD_GObj* gobj);
/* 0e1840*/ void ftMr_SpecialS_Coll(HSD_GObj* gobj);
/* 0e187c*/ void ftMr_SpecialAirS_Coll(HSD_GObj* gobj);
/* 0e18b8*/ void ftMr_SpecialS_GroundToAir(HSD_GObj* gobj);
/* 0e198c*/ void ftMr_SpecialAirS_AirToGround(HSD_GObj* gobj);

#endif
