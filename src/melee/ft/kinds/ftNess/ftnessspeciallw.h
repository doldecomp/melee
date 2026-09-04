/// @file
/// PSI Magnet callbacks (SpecialLw)
#ifndef GALE01_119E14
#define GALE01_119E14

#include <platform.h>

#include <baselib/forward.h>

/* 119E14 */ void ftNs_SpecialLwStart_Enter(HSD_GObj* gobj);
/* 119E90 */ void ftNs_SpecialAirLwStart_Enter(HSD_GObj* gobj);
/* 119F20 */ void ftNs_SpecialLwStart_Anim(HSD_GObj* gobj);
/* 11A000 */ void ftNs_SpecialAirLwStart_Anim(HSD_GObj* gobj);
/* 11A0E0 */ void ftNs_SpecialLwStart_IASA(HSD_GObj* gobj);
/* 11A0E4 */ void ftNs_SpecialAirLwStart_IASA(HSD_GObj* gobj);
/* 11A0E8 */ void ftNs_SpecialLwStart_Phys(HSD_GObj* gobj);
/* 11A108 */ void ftNs_SpecialAirLwStart_Phys(HSD_GObj* gobj);
/* 11A168 */ void ftNs_SpecialLwStart_Coll(HSD_GObj* gobj);
/* 11A1A4 */ void ftNs_SpecialAirLwStart_Coll(HSD_GObj* gobj);
/* 11A1E0 */ void ftNs_SpecialLwStart_GroundToAir(HSD_GObj* gobj);
/* 11A240 */ void ftNs_SpecialAirLwStart_AirToGround(HSD_GObj* gobj);
/* 11A2A8 */ void ftNs_SpecialLwHold_Anim(HSD_GObj* gobj);
/* 11A370 */ void ftNs_SpecialAirLwHold_Anim(HSD_GObj* gobj);
/* 11A438 */ void ftNs_SpecialLwHold_IASA(HSD_GObj* gobj);
/* 11A43C */ void ftNs_SpecialAirLwHold_IASA(HSD_GObj* gobj);
/* 11A440 */ void ftNs_SpecialLwHold_Phys(HSD_GObj* gobj);
/* 11A474 */ void ftNs_SpecialAirLwHold_Phys(HSD_GObj* gobj);
/* 11A4E8 */ void ftNs_SpecialLwHold_Coll(HSD_GObj* gobj);
/* 11A524 */ void ftNs_SpecialAirLwHold_Coll(HSD_GObj* gobj);
/* 11A560 */ void ftNs_SpecialLwHold_GroundToAir(HSD_GObj* gobj);
/* 11A5D4 */ void ftNs_SpecialAirLwHold_AirToGround(HSD_GObj* gobj);
/* 11A650 */ void ftNs_SpecialLwHold_Enter(HSD_GObj* gobj);
/* 11A6A8 */ void ftNs_SpecialAirLwHold_Enter(HSD_GObj* gobj);
/* 11A700 */ void ftNs_SpecialLwTurn_Anim(HSD_GObj* gobj);
/* 11A810 */ void ftNs_SpecialAirLwTurn_Anim(HSD_GObj* gobj);
/* 11A920 */ void ftNs_SpecialLwTurn_IASA(HSD_GObj* gobj);
/* 11A924 */ void ftNs_SpecialAirLwTurn_IASA(HSD_GObj* gobj);
/* 11A928 */ void ftNs_SpecialLwTurn_Phys(HSD_GObj* gobj);
/* 11A95C */ void ftNs_SpecialAirLwTurn_Phys(HSD_GObj* gobj);
/* 11A9D0 */ void ftNs_SpecialLwTurn_Coll(HSD_GObj* gobj);
/* 11AA0C */ void ftNs_SpecialAirLwTurn_Coll(HSD_GObj* gobj);
/* 11AA48 */ void ftNs_SpecialLwTurn_GroundToAir(HSD_GObj* gobj);
/* 11AAA8 */ void ftNs_SpecialAirLwTurn_AirToGround(HSD_GObj* gobj);
/* 11AB10 */ bool ftNs_SpecialLwHold_GroundOrAir(HSD_GObj* gobj);
/* 11ABF8 */ void ftNs_SpecialLwHit_Anim(HSD_GObj* gobj);
/* 11ADC8 */ void ftNs_SpecialAirLwHit_Anim(HSD_GObj* gobj);
/* 11AEE0 */ void ftNs_SpecialLwHit_IASA(HSD_GObj* gobj);
/* 11AEE4 */ void ftNs_SpecialAirLwHit_IASA(HSD_GObj* gobj);
/* 11AEE8 */ void ftNs_SpecialLwHit_Phys(HSD_GObj* gobj);
/* 11AF1C */ void ftNs_SpecialAirLwHit_Phys(HSD_GObj* gobj);
/* 11AF90 */ void ftNs_SpecialLwHit_Coll(HSD_GObj* gobj);
/* 11AFCC */ void ftNs_SpecialAirLwHit_Coll(HSD_GObj* gobj);
/* 11B008 */ void ftNs_SpecialLwHit_GroundToAir(HSD_GObj* gobj);
/* 11B07C */ void ftNs_SpecialAirLwHit_AirToGround(HSD_GObj* gobj);
/* 11B0F8 */ void ftNs_AbsorbThink_DecideAction(HSD_GObj* gobj);
/* 11B25C */ void ftNs_SpecialLwEnd_Anim(HSD_GObj* gobj);
/* 11B2A0 */ void ftNs_SpecialAirLwEnd_Anim(HSD_GObj* gobj);
/* 11B2E4 */ void ftNs_SpecialLwEnd_IASA(HSD_GObj* gobj);
/* 11B2E8 */ void ftNs_SpecialAirLwEnd_IASA(HSD_GObj* gobj);
/* 11B2EC */ void ftNs_SpecialLwEnd_Phys(HSD_GObj* gobj);
/* 11B30C */ void ftNs_SpecialAirLwEnd_Phys(HSD_GObj* gobj);
/* 11B36C */ void ftNs_SpecialLwEnd_Coll(HSD_GObj* gobj);
/* 11B3A8 */ void ftNs_SpecialAirLwEnd_Coll(HSD_GObj* gobj);
/* 11B3E4 */ void ftNs_SpecialLwEnd_GroundToAir(HSD_GObj* gobj);
/* 11B444 */ void ftNs_SpecialAirLwEnd_AirToGround(HSD_GObj* gobj);
/* 11B4AC */ void ftNs_SpecialLwEnd_Enter(HSD_GObj* gobj);
/* 11B4E4 */ void ftNs_SpecialAirLwEnd_Enter(HSD_GObj* gobj);

#endif
