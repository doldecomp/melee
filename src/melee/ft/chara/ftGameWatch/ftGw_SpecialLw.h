/// @file Down Special - Oil Panic (SpecialLw)
#ifndef MELEE_FT_CHARA_FTGAMEWATCH_FTGAMEWATCH_SPECIALLW_H
#define MELEE_FT_CHARA_FTGAMEWATCH_FTGAMEWATCH_SPECIALLW_H

#include <platform.h>
#include <baselib/forward.h>

void ftGw_SpecialLw_ItemPanicSetup(HSD_GObj* gobj);
void ftGw_SpecialLw_ItemPanicSetFlag(HSD_GObj* gobj);
void ftGw_SpecialLw_ItemPanicRemove(HSD_GObj* gobj);
void ftGw_SpecialLw_ItemPanicEnterHitlag(HSD_GObj* gobj);
void ftGw_SpecialLw_ItemPanicExitHitlag(HSD_GObj* gobj);
bool ftGw_SpecialLw_ItemCheckPanicRemove(HSD_GObj* gobj);
void ftGw_SpecialLw_UpdateBucketModel(HSD_GObj* gobj);
void ftGw_SpecialLw_Enter(HSD_GObj* gobj);
void ftGw_SpecialAirLw_Enter(HSD_GObj* gobj);
void ftGw_SpecialLw_Anim(HSD_GObj* gobj);
void ftGw_SpecialAirLw_Anim(HSD_GObj* gobj);
void ftGw_SpecialLw_IASA(HSD_GObj* gobj);
void ftGw_SpecialAirLw_IASA(HSD_GObj* gobj);
void ftGw_SpecialLw_Phys(HSD_GObj* gobj);
void ftGw_SpecialAirLw_Phys(HSD_GObj* gobj);
void ftGw_SpecialLw_Coll(HSD_GObj* gobj);
void ftGw_SpecialAirLw_Coll(HSD_GObj* gobj);
void ftGw_SpecialLw_GroundToAir(HSD_GObj* gobj);
void ftGw_SpecialAirLw_AirToGround(HSD_GObj* gobj);
void ftGw_SpecialLw_UpdateAction(HSD_GObj* gobj, f32 animFrame);
void ftGw_SpecialAirLw_UpdateAction(HSD_GObj* gobj, f32 animFrame);
void ftGw_SpecialLwCatch_Anim(HSD_GObj* gobj);
void ftGw_SpecialAirLwCatch_Anim(HSD_GObj* gobj);
void ftGw_SpecialLwCatch_IASA(HSD_GObj* gobj);
void ftGw_SpecialAirLwCatch_IASA(HSD_GObj* gobj);
void ftGw_SpecialLwCatch_Phys(HSD_GObj* gobj);
void ftGw_SpecialAirLwCatch_Phys(HSD_GObj* gobj);
void ftGw_SpecialLwCatch_Coll(HSD_GObj* gobj);
void ftGw_SpecialAirLwCatch_Coll(HSD_GObj* gobj);
void ftGw_SpecialLwCatch_GroundToAir(HSD_GObj* gobj);
void ftGw_SpecialAirLwCatch_AirToGround(HSD_GObj* gobj);
void ftGw_SpecialLw_AbsorbThink_DecideAction(HSD_GObj* gobj);
void ftGw_SpecialLwShoot_Anim(HSD_GObj* gobj);
void ftGw_SpecialAirLwShoot_Anim(HSD_GObj* gobj);
void ftGw_SpecialLwShoot_IASA(HSD_GObj* gobj);
void ftGw_SpecialAirLwShoot_IASA(HSD_GObj* gobj);
void ftGw_SpecialLwShoot_Phys(HSD_GObj* gobj);
void ftGw_SpecialAirLwShoot_Phys(HSD_GObj* gobj);
void ftGw_SpecialLwShoot_Coll(HSD_GObj* gobj);
void ftGw_SpecialAirLwShoot_Coll(HSD_GObj* gobj);
void ftGw_SpecialLwShoot_GroundToAir(HSD_GObj* gobj);
void ftGw_SpecialAirLwShoot_AirToGround(HSD_GObj* gobj);
void ftGw_SpecialLwShoot_ReleaseOil(HSD_GObj* gobj);
void ftGw_SpecialAirLwShoot_ReleaseOil(HSD_GObj* gobj);

#endif
