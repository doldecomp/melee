/** @file
 * Side Special - Raptor Boost / Gerudo Dragon (SpecialS)
 */
#ifndef MELEE_FT_CHARA_FTCAPTAIN_FTCAPTAIN_SPECIALS_H
#define MELEE_FT_CHARA_FTCAPTAIN_FTCAPTAIN_SPECIALS_H

#include <platform.h>
#include "ft/forward.h"

#include <baselib/gobj.h>

/**
 * Remove all GFX and set GFX flags to @c false.
 */
void ftCa_SpecialS_RemoveGFX(HSD_GObj* gobj);

/**
 * Captain Falcon & Ganondorf's aerial Raptor Boost/Gerudo Dragon Start Action
 * State handler.
 */
void ftCa_SpecialS_StartMotion(HSD_GObj* gobj);

void ftCa_SpecialAirS_StartMotion(HSD_GObj* gobj);

/**
 * Captain Falcon & Ganondorf's Raptor Boost / Gerudo Dragon Detect function.
 */
void ftCa_SpecialS_OnDetect(HSD_GObj* gobj);

/**
 * Captain Falcon & Ganondorf's grounded Raptor Boost / Gerudo Dragon Start
 * Animation callback.
 */
void ftCa_SpecialSStart_Anim(HSD_GObj* gobj);

/**
 * Captain Falcon & Ganondorf's grounded Raptor Boost / Gerudo Dragon Hit
 * Animation callback.
 */
void ftCa_SpecialS_Anim(HSD_GObj* gobj);

/**
 * Captain Falcon & Ganondorf's aerial Raptor Boost / Gerudo Dragon Start
 * Animation callback.
 */
void ftCa_SpecialAirSStart_Anim(HSD_GObj* gobj);

/**
 * Captain Falcon & Ganondorf's aerial Raptor Boost / Gerudo Dragon Hit
 * Animation callback.
 */
void ftCa_SpecialAirS_Anim(HSD_GObj* gobj);

/**
 * Captain Falcon & Ganondorf's grounded Raptor Boost / Gerudo Dragon Start
 * IASA callback.
 */
void ftCa_SpecialSStart_IASA(HSD_GObj* gobj);

/**
 * Captain Falcon & Ganondorf's grounded Raptor Boost / Gerudo Dragon Hit IASA
 * callback.
 */
void ftCa_SpecialS_IASA(HSD_GObj* gobj);

/**
 * Captain Falcon & Ganondorf's aerial Raptor Boost / Gerudo Dragon Start IASA
 * callback.
 */
void ftCa_SpecialAirSStart_IASA(HSD_GObj* gobj);

/**
 * Captain Falcon & Ganondorf's aerial Raptor Boost / Gerudo Dragon Hit IASA
 * callback.
 */
void ftCa_SpecialAirS_IASA(HSD_GObj* gobj);

/**
 * Captain Falcon & Ganondorf's grounded Raptor Boost / Gerudo Dragon Start
 * Physics callback.
 */
void ftCa_SpecialSStart_Phys(HSD_GObj* gobj);

/**
 * Captain Falcon & Ganondorf's grounded Raptor Boost / Gerudo Dragon Hit
 * Physics callback.
 */
void ftCa_SpecialS_Phys(HSD_GObj* gobj);

/**
 * Captain Falcon & Ganondorf's grounded Raptor Boost/Gerudo Dragon Start
 * Motion State handler.
 */
void ftCa_SpecialAirSStart_Phys(HSD_GObj* gobj);

/**
 * Captain Falcon & Ganondorf's aerial Raptor Boost / Gerudo Dragon Hit Physics
 * callback
 */
void ftCa_SpecialAirS_Phys(HSD_GObj* gobj);

void ftCa_SpecialSStart_Coll(HSD_GObj* gobj);

/**
 * Captain Falcon & Ganondorf's grounded Raptor Boost / Gerudo Dragon Hit
 * Collision callback
 */
void ftCa_SpecialS_Coll(HSD_GObj* gobj);

/**
 * Captain Falcon & Ganondorf's aerial Raptor Boost / Gerudo Dragon Start
 * Collision callback
 */
void ftCa_SpecialAirSStart_Coll(HSD_GObj* gobj);

void ftCa_SpecialAirS_Coll(HSD_GObj* gobj);
void ftCa_OnLoadForGanon(Fighter*);

#endif
