/// @file Down Special - Oil Panic (SpecialLw)
#ifndef GALE01_14CBF4
#define GALE01_14CBF4

#include <baselib/forward.h>

/* 14CBF4 */ void ftGw_SpecialLw_ItemPanicSetup(HSD_GObj* gobj);
/* 14CC9C */ void ftGw_SpecialLw_ItemPanicSetFlag(HSD_GObj* gobj);
/* 14CCD8 */ void ftGw_SpecialLw_ItemPanicRemove(HSD_GObj* gobj);
/* 14CD38 */ void ftGw_SpecialLw_ItemPanicEnterHitlag(HSD_GObj* gobj);
/* 14CD68 */ void ftGw_SpecialLw_ItemPanicExitHitlag(HSD_GObj* gobj);
/* 14CD98 */ bool ftGw_SpecialLw_ItemCheckPanicRemove(HSD_GObj* gobj);
/* 14CDC0 */ void ftGw_SpecialLw_UpdateBucketModel(HSD_GObj* gobj);
/* 14CEF0 */ void ftGw_SpecialLw_Enter(HSD_GObj* gobj);
/* 14CF78 */ void ftGw_SpecialAirLw_Enter(HSD_GObj* gobj);
/* 14D014 */ void ftGw_SpecialLw_Anim(HSD_GObj* gobj);
/* 14D0E0 */ void ftGw_SpecialAirLw_Anim(HSD_GObj* gobj);
/* 14D1AC */ void ftGw_SpecialLw_IASA(HSD_GObj* gobj);
/* 14D264 */ void ftGw_SpecialAirLw_IASA(HSD_GObj* gobj);
/* 14D31C */ void ftGw_SpecialLw_Phys(HSD_GObj* gobj);
/* 14D350 */ void ftGw_SpecialAirLw_Phys(HSD_GObj* gobj);
/* 14D3B4 */ void ftGw_SpecialLw_Coll(HSD_GObj* gobj);
/* 14D3F0 */ void ftGw_SpecialAirLw_Coll(HSD_GObj* gobj);
/* 14D42C */ void ftGw_SpecialLw_GroundToAir(HSD_GObj* gobj);
/* 14D4DC */ void ftGw_SpecialAirLw_AirToGround(HSD_GObj* gobj);
/* 14D58C */ void ftGw_SpecialLw_UpdateAction(HSD_GObj* gobj, float animFrame);
/* 14D620 */ void ftGw_SpecialAirLw_UpdateAction(HSD_GObj* gobj,
                                                 float animFrame);
/* 14D6B4 */ void ftGw_SpecialLwCatch_Anim(HSD_GObj* gobj);
/* 14D774 */ void ftGw_SpecialAirLwCatch_Anim(HSD_GObj* gobj);
/* 14D834 */ void ftGw_SpecialLwCatch_IASA(HSD_GObj* gobj);
/* 14D838 */ void ftGw_SpecialAirLwCatch_IASA(HSD_GObj* gobj);
/* 14D83C */ void ftGw_SpecialLwCatch_Phys(HSD_GObj* gobj);
/* 14D85C */ void ftGw_SpecialAirLwCatch_Phys(HSD_GObj* gobj);
/* 14D87C */ void ftGw_SpecialLwCatch_Coll(HSD_GObj* gobj);
/* 14D8B8 */ void ftGw_SpecialAirLwCatch_Coll(HSD_GObj* gobj);
/* 14D8F4 */ void ftGw_SpecialLwCatch_GroundToAir(HSD_GObj* gobj);
/* 14D954 */ void ftGw_SpecialAirLwCatch_AirToGround(HSD_GObj* gobj);
/* 14D9B4 */ void ftGw_SpecialLw_AbsorbThink_DecideAction(HSD_GObj* gobj);
/* 14DA60 */ void ftGw_SpecialLwShoot_Anim(HSD_GObj* gobj);
/* 14DAF0 */ void ftGw_SpecialAirLwShoot_Anim(HSD_GObj* gobj);
/* 14DB80 */ void ftGw_SpecialLwShoot_IASA(HSD_GObj* gobj);
/* 14DB84 */ void ftGw_SpecialAirLwShoot_IASA(HSD_GObj* gobj);
/* 14DB88 */ void ftGw_SpecialLwShoot_Phys(HSD_GObj* gobj);
/* 14DBA8 */ void ftGw_SpecialAirLwShoot_Phys(HSD_GObj* gobj);
/* 14DBC8 */ void ftGw_SpecialLwShoot_Coll(HSD_GObj* gobj);
/* 14DC04 */ void ftGw_SpecialAirLwShoot_Coll(HSD_GObj* gobj);
/* 14DC40 */ void ftGw_SpecialLwShoot_GroundToAir(HSD_GObj* gobj);
/* 14DCB4 */ void ftGw_SpecialAirLwShoot_AirToGround(HSD_GObj* gobj);
/* 14DD28 */ void ftGw_SpecialLwShoot_ReleaseOil(HSD_GObj* gobj);
/* 14DE0C */ void ftGw_SpecialAirLwShoot_ReleaseOil(HSD_GObj* gobj);

#endif
