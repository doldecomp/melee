/// @file
/// Side Special - Confusion (SpecialS/SpecialAirS)
#ifndef GALE01_1466C4
#define GALE01_1466C4

#include <baselib/forward.h>

/* 1466C4 */ void ftMt_SpecialS_Enter(HSD_GObj* gobj);
/* 14677C */ void ftMt_SpecialAirS_Enter(HSD_GObj* gobj);
/* 146858 */ void ftMt_SpecialS_Anim(HSD_GObj* gobj);
/* 1468EC */ void ftMt_SpecialAirS_Anim(HSD_GObj* gobj);
/* 146980 */ void ftMt_SpecialS_IASA(HSD_GObj* gobj);
/* 146984 */ void ftMt_SpecialAirS_IASA(HSD_GObj* gobj);
/* 146988 */ void ftMt_SpecialS_Phys(HSD_GObj* gobj);
/* 1469BC */ void ftMt_SpecialAirS_Phys(HSD_GObj* gobj);
/* 1469F0 */ void ftMt_SpecialS_GroundToAir(HSD_GObj* gobj);
/* 146AD4 */ void ftMt_SpecialAirS_AirToGround(HSD_GObj* gobj);
/* 146BB8 */ void ftMt_SpecialS_Coll(HSD_GObj* gobj);
/* 146BE0 */ void ftMt_SpecialAirS_Coll(HSD_GObj* gobj);
/* 146C08 */ void ftMt_SpecialS_ReflectThink(HSD_GObj* gobj);
/* 146CC8 */ void ftMt_SpecialS_OnReflect(HSD_GObj* gobj);

#endif
