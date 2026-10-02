/**
 * @file ftcaptainspecialhi.h
 * @brief Up Special - Falcon Dive (Captain Falcon) / Dark Dive (Ganondorf)
 * (SpecialHi)
 * @details Declarations for state entry, animation, IASA, physics, and
 * collision callbacks for Captain Falcon and Ganondorf's Up Special command
 * grab move (Falcon Dive). Module prefix: ftCa
 */

#ifndef GALE01_0E4040
#define GALE01_0E4040

#include <sysdolphin/baselib/forward.h>

/**
 * @brief Grounded Up-B (Falcon Dive) animation callback.
 * @details Transitions to FallSpecial (freefall) upon animation completion.
 * @param gobj Pointer to Fighter GObj
 */
/* 0E4354 */ void ftCa_SpecialHi_Anim(HSD_GObj* gobj);

/**
 * @brief Falcon Kick Wall Rebound collision callback.
 * @param gobj Pointer to Fighter GObj
 */
/* 0E49DC */ void ftCa_SpecialHiThrow1_Coll(HSD_GObj* gobj);

/**
 * @brief Grounded Up-B (Falcon Dive) state entry.
 * @details Consumes mid-air jumps, sets catch callbacks, and enters
 * ftCa_MS_SpecialHi.
 * @param gobj Pointer to Fighter GObj
 */
/* 0E4A78 */ void ftCa_SpecialHi_Enter(HSD_GObj* gobj);

/**
 * @brief Grounded Up-B (Falcon Dive) IASA callback.
 * @details Reads analog stick X to reverse facing direction during startup
 * window.
 * @param gobj Pointer to Fighter GObj
 */
/* 0E4B60 */ void ftCa_SpecialHi_IASA(HSD_GObj* gobj);

/**
 * @brief Grounded Up-B (Falcon Dive) physics callback.
 * @details Calculates horizontal air drift and acceleration during the upward
 * leap.
 * @param gobj Pointer to Fighter GObj
 */
/* 0E4BF8 */ void ftCa_SpecialHi_Phys(HSD_GObj* gobj);

/**
 * @brief Aerial Up-B (Aerial Falcon Dive) state entry.
 * @param gobj Pointer to Fighter GObj
 */
/* 0E4CF4 */ void ftCa_SpecialAirHi_Enter(HSD_GObj* gobj);

/**
 * @brief Grounded Up-B (Falcon Dive) collision callback.
 * @param gobj Pointer to Fighter GObj
 */
/* 0E4E1C */ void ftCa_SpecialHi_Coll(HSD_GObj* gobj);

/**
 * @brief Aerial Up-B (Aerial Falcon Dive) animation callback.
 * @details Transitions to FallSpecial (freefall) upon animation completion.
 * @param gobj Pointer to Fighter GObj
 */
/* 0E4EE8 */ void ftCa_SpecialAirHi_Anim(HSD_GObj* gobj);

/**
 * @brief Aerial Up-B (Aerial Falcon Dive) IASA callback.
 * @details Reads analog stick X to reverse facing direction during startup
 * window.
 * @param gobj Pointer to Fighter GObj
 */
/* 0E4F48 */ void ftCa_SpecialAirHi_IASA(HSD_GObj* gobj);

/**
 * @brief Aerial Up-B (Aerial Falcon Dive) physics callback.
 * @param gobj Pointer to Fighter GObj
 */
/* 0E4FDC */ void ftCa_SpecialAirHi_Phys(HSD_GObj* gobj);

/**
 * @brief Aerial Up-B (Aerial Falcon Dive) collision callback.
 * @details Handles ledge grabbing and landing into freefall lag.
 * @param gobj Pointer to Fighter GObj
 */
/* 0E50D8 */ void ftCa_SpecialAirHi_Coll(HSD_GObj* gobj);

/**
 * @brief Up-B Grab Contact (Falcon Dive Catch) animation callback.
 * @details Transitions to the throw explosion state when the catch hold
 * completes.
 * @param gobj Pointer to Fighter GObj
 */
/* 0E51F8 */ void ftCa_SpecialHiCatch_Anim(HSD_GObj* gobj);

/**
 * @brief Up-B Grab Contact (Falcon Dive Catch) IASA callback (no-op).
 * @param gobj Pointer to Fighter GObj
 */
/* 0E5234 */ void ftCa_SpecialHiCatch_IASA(HSD_GObj* gobj);

/**
 * @brief Up-B Grab Contact (Falcon Dive Catch) physics callback (no-op).
 * @param gobj Pointer to Fighter GObj
 */
/* 0E5238 */ void ftCa_SpecialHiCatch_Phys(HSD_GObj* gobj);

/**
 * @brief Up-B Grab Contact (Falcon Dive Catch) collision callback.
 * @param gobj Pointer to Fighter GObj
 */
/* 0E523C */ void ftCa_SpecialHiCatch_Coll(HSD_GObj* gobj);

/**
 * @brief Up-B Explosion Throw (Falcon Dive Release) animation callback.
 * @details On animation completion, transitions to Fall.
 * @param gobj Pointer to Fighter GObj
 */
/* 0E5310 */ void ftCa_SpecialHiThrow0_Anim(HSD_GObj* gobj);

/**
 * @brief Up-B Explosion Throw (Falcon Dive Release) IASA callback (no-op).
 * @param gobj Pointer to Fighter GObj
 */
/* 0E5384 */ void ftCa_SpecialHiThrow0_IASA(HSD_GObj* gobj);

/**
 * @brief Up-B Explosion Throw (Falcon Dive Release) physics callback.
 * @details Applies post-explosion gravity recoil after the explosion release.
 * @param gobj Pointer to Fighter GObj
 */
/* 0E5388 */ void ftCa_SpecialHiThrow0_Phys(HSD_GObj* gobj);

/**
 * @brief Up-B Explosion Throw (Falcon Dive Release) collision callback.
 * @details Enters landing lag if touching the ground during the throw
 * recovery.
 * @param gobj Pointer to Fighter GObj
 */
/* 0E54B8 */ void ftCa_SpecialHiThrow0_Coll(HSD_GObj* gobj);

#endif
