/// @file
/// Down Special - Disable (SpecialLw/SpecialAirLw)
#ifndef GALE01_146198
#define GALE01_146198

#include <baselib/forward.h>

/* 146198 */ void ftMt_SpecialLw_ClearDisableGObj(HSD_GObj* gobj);
/* 1461A8 */ void ftMt_SpecialLw_RemoveDisable(HSD_GObj* gobj);
/* 1461F0 */ void ftMt_SpecialLw_Enter(HSD_GObj* gobj);
/* 146264 */ void ftMt_SpecialAirLw_Enter(HSD_GObj* gobj);
/* 1462DC */ void ftMt_SpecialLw_Anim(HSD_GObj* gobj);
/* 146338 */ void ftMt_SpecialAirLw_Anim(HSD_GObj* gobj);
/* 146394 */ void ftMt_SpecialLw_IASA(HSD_GObj* gobj);
/* 146398 */ void ftMt_SpecialAirLw_IASA(HSD_GObj* gobj);
/* 14639C */ void ftMt_SpecialLw_Phys(HSD_GObj* gobj);
/* 1463BC */ void ftMt_SpecialAirLw_Phys(HSD_GObj* gobj);
/* 146410 */ void ftMt_SpecialLw_GroundToAir(HSD_GObj* gobj);
/* 1464B0 */ void ftMt_SpecialAirLw_AirToGround(HSD_GObj* gobj);
/* 146544 */ void ftMt_SpecialLw_Coll(HSD_GObj* gobj);
/* 14656C */ void ftMt_SpecialAirLw_Coll(HSD_GObj* gobj);
/* 146594 */ void ftMt_SpecialLw_CreateDisable(HSD_GObj* gobj);

#endif
