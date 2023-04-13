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
void ftCaptain_SpecialS_RemoveGFX(HSD_GObj* fighter_gobj);

/**
 * Captain Falcon & Ganondorf's aerial Raptor Boost/Gerudo Dragon Start Action
 * State handler.
 */
void ftCaptain_SpecialS_StartMotion(HSD_GObj* fighter_gobj);

void ftCaptain_SpecialAirS_StartMotion(HSD_GObj* fighter_gobj);

/**
 * Captain Falcon & Ganondorf's Raptor Boost / Gerudo Dragon Detect function.
 */
void ftCaptain_SpecialS_OnDetect(HSD_GObj* fighter_gobj);

/**
 * Captain Falcon & Ganondorf's grounded Raptor Boost / Gerudo Dragon Start
 * Animation callback.
 */
void ftCaptain_SpecialSStart_Anim(HSD_GObj* fighter_gobj);

/**
 * Captain Falcon & Ganondorf's grounded Raptor Boost / Gerudo Dragon Hit
 * Animation callback.
 */
void ftCaptain_SpecialS_Anim(HSD_GObj* fighter_gobj);

/**
 * Captain Falcon & Ganondorf's aerial Raptor Boost / Gerudo Dragon Start
 * Animation callback.
 */
void ftCaptain_SpecialAirSStart_Anim(HSD_GObj* fighter_gobj);

/**
 * Captain Falcon & Ganondorf's aerial Raptor Boost / Gerudo Dragon Hit
 * Animation callback.
 */
void ftCaptain_SpecialAirS_Anim(HSD_GObj* fighter_gobj);

/**
 * Captain Falcon & Ganondorf's grounded Raptor Boost / Gerudo Dragon Start
 * IASA callback.
 */
void ftCaptain_SpecialSStart_IASA(HSD_GObj* fighter_gobj);

/**
 * Captain Falcon & Ganondorf's grounded Raptor Boost / Gerudo Dragon Hit IASA
 * callback.
 */
void ftCaptain_SpecialS_IASA(HSD_GObj* fighter_gobj);

/**
 * Captain Falcon & Ganondorf's aerial Raptor Boost / Gerudo Dragon Start IASA
 * callback.
 */
void ftCaptain_SpecialAirSStart_IASA(HSD_GObj* fighter_gobj);

/**
 * Captain Falcon & Ganondorf's aerial Raptor Boost / Gerudo Dragon Hit IASA
 * callback.
 */
void ftCaptain_SpecialAirS_IASA(HSD_GObj* fighter_gobj);

/**
 * Captain Falcon & Ganondorf's grounded Raptor Boost / Gerudo Dragon Start
 * Physics callback.
 */
void ftCaptain_SpecialSStart_Phys(HSD_GObj* fighter_gobj);

/**
 * Captain Falcon & Ganondorf's grounded Raptor Boost / Gerudo Dragon Hit
 * Physics callback.
 */
void ftCaptain_SpecialS_Phys(HSD_GObj* fighter_gobj);

/**
 * Captain Falcon & Ganondorf's grounded Raptor Boost/Gerudo Dragon Start
 * Action State handler.
 */
void ftCaptain_SpecialAirSStart_Phys(HSD_GObj* fighter_gobj);

/**
 * Captain Falcon & Ganondorf's aerial Raptor Boost / Gerudo Dragon Hit Physics
 * callback
 */
void ftCaptain_SpecialAirS_Phys(HSD_GObj* fighter_gobj);

void ftCaptain_SpecialSStart_Coll(HSD_GObj* fighter_gobj);

/**
 * Captain Falcon & Ganondorf's grounded Raptor Boost / Gerudo Dragon Hit
 * Collision callback
 */
void ftCaptain_SpecialS_Coll(HSD_GObj* fighter_gobj);

/**
 * Captain Falcon & Ganondorf's aerial Raptor Boost / Gerudo Dragon Start
 * Collision callback
 */
void ftCaptain_SpecialAirSStart_Coll(HSD_GObj* fighter_gobj);

void ftCaptain_SpecialAirS_Coll(HSD_GObj* fighter_gobj);
void ftCaptain_OnLoadForGanon(Fighter*);

#endif
