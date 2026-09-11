/// @file
/// Side Special - Raptor Boost / Gerudo Dragon (SpecialS)
#ifndef GALE01_0E3278
#define GALE01_0E3278
/**
 * @file
 * Captain Falcon & Ganondorf's Side Special -
 * Raptor Boost / Gerudo Dragon (SpecialS)
 */

#include <sysdolphin/baselib/forward.h>

/// Remove all GFX and set GFX flags to @c false.
/* 0E3278 */ void ftCa_SpecialS_RemoveGFX(HSD_GObj* gobj);
/**
 * Captain Falcon & Ganondorf's aerial Raptor Boost/Gerudo Dragon Start Action
 * State handler.
 */
/* 0E32B0 */ void ftCa_SpecialS_Enter(HSD_GObj* gobj);
/* 0E33E0 */ void ftCa_SpecialAirS_Enter(HSD_GObj* gobj);
/// Captain Falcon & Ganondorf's Raptor Boost / Gerudo Dragon Detect function.
/* 0E350C */ void ftCa_SpecialS_OnDetect(HSD_GObj* gobj);
/**
 * Captain Falcon & Ganondorf's grounded Raptor Boost / Gerudo Dragon Start
 * Animation callback.
 */
/* 0E384C */ void ftCa_SpecialSStart_Anim(HSD_GObj* gobj);
/**
 * Captain Falcon & Ganondorf's grounded Raptor Boost / Gerudo Dragon Hit
 * Animation callback.
 */
/* 0E3888 */ void ftCa_SpecialS_Anim(HSD_GObj* gobj);
/**
 * Captain Falcon & Ganondorf's aerial Raptor Boost / Gerudo Dragon Start
 * Animation callback.
 */
/* 0E3964 */ void ftCa_SpecialAirSStart_Anim(HSD_GObj* gobj);
/**
 * Captain Falcon & Ganondorf's aerial Raptor Boost / Gerudo Dragon Hit
 * Animation callback.
 */
/* 0E39F0 */ void ftCa_SpecialAirS_Anim(HSD_GObj* gobj);
/**
 * Captain Falcon & Ganondorf's grounded Raptor Boost / Gerudo Dragon Start
 * IASA callback.
 */
/* 0E3B0C */ void ftCa_SpecialSStart_IASA(HSD_GObj* gobj);
/**
 * Captain Falcon & Ganondorf's grounded Raptor Boost / Gerudo Dragon Hit IASA
 * callback.
 */
/* 0E3B10 */ void ftCa_SpecialS_IASA(HSD_GObj* gobj);
/**
 * Captain Falcon & Ganondorf's aerial Raptor Boost / Gerudo Dragon Start IASA
 * callback.
 */
/* 0E3B14 */ void ftCa_SpecialAirSStart_IASA(HSD_GObj* gobj);
/**
 * Captain Falcon & Ganondorf's aerial Raptor Boost / Gerudo Dragon Hit IASA
 * callback.
 */
/* 0E3B18 */ void ftCa_SpecialAirS_IASA(HSD_GObj* gobj);
/**
 * Captain Falcon & Ganondorf's grounded Raptor Boost / Gerudo Dragon Start
 * Physics callback.
 */
/* 0E3B1C */ void ftCa_SpecialSStart_Phys(HSD_GObj* gobj);
/**
 * Captain Falcon & Ganondorf's grounded Raptor Boost / Gerudo Dragon Hit
 * Physics callback.
 */
/* 0E3B3C */ void ftCa_SpecialS_Phys(HSD_GObj* gobj);
/**
 * Captain Falcon & Ganondorf's grounded Raptor Boost/Gerudo Dragon Start
 * Motion State handler.
 */
/* 0E3B5C */ void ftCa_SpecialAirSStart_Phys(HSD_GObj* gobj);
/**
 * Captain Falcon & Ganondorf's aerial Raptor Boost / Gerudo Dragon Hit Physics
 * callback
 */
/* 0E3BD0 */ void ftCa_SpecialAirS_Phys(HSD_GObj* gobj);
/* 0E3C38 */ void ftCa_SpecialSStart_Coll(HSD_GObj* gobj);
/**
 * Captain Falcon & Ganondorf's grounded Raptor Boost / Gerudo Dragon Hit
 * Collision callback
 */
/* 0E3D44 */ void ftCa_SpecialS_Coll(HSD_GObj* gobj);
/**
 * Captain Falcon & Ganondorf's aerial Raptor Boost / Gerudo Dragon Start
 * Collision callback
 */
/* 0E3DE4 */ void ftCa_SpecialAirSStart_Coll(HSD_GObj* gobj);
/* 0E3E40 */ void ftCa_SpecialAirS_Coll(HSD_GObj* gobj);

#endif
