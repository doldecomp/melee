/// @file
/// PK Thunder callbacks (SpecialHi)
#ifndef GALE01_116D04
#define GALE01_116D04

#include <platform.h>

#include <baselib/forward.h>

/* 116D04 */ void ftNs_SpecialAirS_Enter(HSD_GObj* gobj);
/* 116DB0 */ void ftNs_SpecialAirS_Anim(HSD_GObj* gobj);
/* 116E0C */ void ftNs_SpecialAirS_Phys(HSD_GObj* gobj);
/* 116E68 */ void ftNs_SpecialAirS_Coll(HSD_GObj* gobj);
/* 117034 */ void ftNs_SpecialAirNStart_Enter(HSD_GObj* gobj);
/* 117378 */ void ftNs_SpecialAirNStart_Anim(HSD_GObj* gobj);
/* 117458 */ void ftNs_SpecialAirNRelease_Anim(HSD_GObj* gobj);
/* 11758C */ void ftNs_SpecialAirNEnd_Anim(HSD_GObj* gobj);
/* 1176CC */ void ftNs_SpecialAirNStart_IASA(HSD_GObj* gobj);
/* 1176D0 */ void ftNs_SpecialAirNRelease_IASA(HSD_GObj* gobj);
/* 11774C */ void ftNs_SpecialAirNEnd_IASA(HSD_GObj* gobj);
/* 1177C8 */ void ftNs_SpecialAirNStart_Phys(HSD_GObj* gobj);
/* 117828 */ void ftNs_SpecialAirNRelease_Phys(HSD_GObj* gobj);
/* 117888 */ void ftNs_SpecialAirNEnd_Phys(HSD_GObj* gobj);
/* 117A2C */ void ftNs_SpecialAirNStart_Coll(HSD_GObj* gobj);
/* 117A98 */ void ftNs_SpecialAirNRelease_Coll(HSD_GObj* gobj);
/* 117B04 */ void ftNs_SpecialAirNEnd_Coll(HSD_GObj* gobj);
/* 117B70 */ void ftNs_SpecialHiStopGFX(HSD_GObj* gobj);
/* 117BBC */ bool
ftNs_SpecialHi_ItemPKThunder_CheckNessCollide(HSD_GObj* gobj);
/* 117D9C */ bool ftNs_SpecialHi_CheckSpecialHiHold(HSD_GObj* gobj);
/* 117DD4 */ void ftNs_SpecialHi_ItemPKThunderRemove(HSD_GObj* gobj);
/* 117E60 */ void ftNs_SpecialHi_TakeDamage(HSD_GObj* gobj);
/* 117F00 */ void ftNs_SpecialHi_ItemPKThunderCheckOwn(HSD_GObj* gobj,
                                                       HSD_GObj* thunder_gobj);
/* 118120 */ void ftNs_SpecialHiStart_Enter(HSD_GObj* gobj);
/* 118250 */ void ftNs_SpecialAirHiStart_Enter(HSD_GObj* gobj);
/* 118384 */ void ftNs_SpecialHi_Enter(HSD_GObj* gobj);
/* 118570 */ void ftNs_SpecialAirHi_Enter(HSD_GObj* gobj);
/* 1186B0 */ void ftNs_SpecialHiStart_Anim(HSD_GObj* gobj);
/* 1187A4 */ void ftNs_SpecialHiHold_Anim(HSD_GObj* gobj);
/* 118900 */ void ftNs_SpecialHiEnd_Anim(HSD_GObj* gobj);
/* 11893C */ void ftNs_SpecialHi_Anim(HSD_GObj* gobj);
/* 118A10 */ void ftNs_SpecialAirHiStart_Anim(HSD_GObj* gobj);
/* 118B04 */ void ftNs_SpecialAirHiHold_Anim(HSD_GObj* gobj);
/* 118D60 */ void ftNs_SpecialAirHiEnd_Anim(HSD_GObj* gobj);
/* 118DF8 */ void ftNs_SpecialAirHi_Anim(HSD_GObj* gobj);
/* 118EF0 */ void ftNs_SpecialAirHiRebound_Anim(HSD_GObj* gobj);
/* 118F80 */ void ftNs_SpecialHiStart_IASA(HSD_GObj* gobj);
/* 118F84 */ void ftNs_SpecialHiHold_IASA(HSD_GObj* gobj);
/* 118F88 */ void ftNs_SpecialHiEnd_IASA(HSD_GObj* gobj);
/* 118F8C */ void ftNs_SpecialHi_IASA(HSD_GObj* gobj);
/* 118F90 */ void ftNs_SpecialAirHiStart_IASA(HSD_GObj* gobj);
/* 118F94 */ void ftNs_SpecialAirHiHold_IASA(HSD_GObj* gobj);
/* 118F98 */ void ftNs_SpecialAirHiEnd_IASA(HSD_GObj* gobj);
/* 118F9C */ void ftNs_SpecialAirHi_IASA(HSD_GObj* gobj);
/* 118FA0 */ void ftNs_SpecialAirHiRebound_IASA(HSD_GObj* gobj);
/* 118FA4 */ void ftNs_SpecialHiStart_Phys(HSD_GObj* gobj);
/* 118FDC */ void ftNs_SpecialHiHold_Phys(HSD_GObj* gobj);
/* 118FFC */ void ftNs_SpecialHiEnd_Phys(HSD_GObj* gobj);
/* 11901C */ void ftNs_SpecialHi_Phys(HSD_GObj* gobj);
/* 119134 */ void ftNs_SpecialAirHiStart_Phys(HSD_GObj* gobj);
/* 119194 */ void ftNs_SpecialAirHiHold_Phys(HSD_GObj* gobj);
/* 1191F4 */ void ftNs_SpecialAirHiEnd_Phys(HSD_GObj* gobj);
/* 119254 */ void ftNs_SpecialAirHi_Phys(HSD_GObj* gobj);
/* 119410 */ void ftNs_SpecialAirHiRebound_Phys(HSD_GObj* gobj);
/* 119460 */ void ftNs_SpecialHiStart_Coll(HSD_GObj* gobj);
/* 1194CC */ void ftNs_SpecialHiHold_Coll(HSD_GObj* gobj);
/* 119538 */ void ftNs_SpecialHiEnd_Coll(HSD_GObj* gobj);
/* 1195A4 */ void ftNs_SpecialHi_Coll(HSD_GObj* gobj);
/* 119798 */ void ftNs_SpecialAirHiStart_Coll(HSD_GObj* gobj);
/* 119804 */ void ftNs_SpecialAirHiHold_Coll(HSD_GObj* gobj);
/* 119870 */ void ftNs_SpecialAirHiEnd_Coll(HSD_GObj* gobj);
/* 1198DC */ void ftNs_SpecialAirHi_Coll(HSD_GObj* gobj);
/* 119D58 */ void ftNs_SpecialAirHiRebound_Coll(HSD_GObj* gobj);

#endif
