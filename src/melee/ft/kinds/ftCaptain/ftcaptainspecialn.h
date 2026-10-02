/**
 * @file ftcaptainspecialn.h
 * @brief Header for Neutral Special move - Falcon Punch / Warlock Punch
 * (SpecialN)
 * @details Declarations for state entry, animation, IASA, physics, and
 * collision callbacks for Captain Falcon and Ganondorf's grounded and aerial
 * Neutral Special move. Module prefix: ftCa
 */

#ifndef GALE01_0E2B80
#define GALE01_0E2B80

#include <sysdolphin/baselib/forward.h>

/**
 * @brief Grounded Neutral-B (Falcon Punch / Warlock Punch) state entry.
 * @param gobj Pointer to Captain Falcon's Fighter GObj
 */
/* 0E2B80 */ void ftCa_SpecialN_Enter(HSD_GObj* gobj);

/**
 * @brief Aerial Neutral-B (Aerial Falcon Punch / Aerial Warlock Punch) state
 * entry.
 * @param gobj Pointer to Captain Falcon's Fighter GObj
 */
/* 0E2C00 */ void ftCa_SpecialAirN_Enter(HSD_GObj* gobj);

/**
 * @brief Grounded Neutral-B (Falcon Punch) animation callback.
 * @param gobj Pointer to Captain Falcon's Fighter GObj
 */
/* 0E2C80 */ void ftCa_SpecialN_Anim(HSD_GObj* gobj);

/**
 * @brief Aerial Neutral-B (Aerial Falcon Punch) animation callback.
 * @param gobj Pointer to Captain Falcon's Fighter GObj
 */
/* 0E2D5C */ void ftCa_SpecialAirN_Anim(HSD_GObj* gobj);

/**
 * @brief Grounded Neutral-B (Falcon Punch) IASA callback (no-op).
 * @param gobj Pointer to Captain Falcon's Fighter GObj
 */
/* 0E2E38 */ void ftCa_SpecialN_IASA(HSD_GObj* gobj);

/**
 * @brief Aerial Neutral-B (Aerial Falcon Punch) IASA callback.
 * @details Computes directional stick angle and applies aerial punch velocity
 * boost.
 * @param gobj Pointer to Captain Falcon's Fighter GObj
 */
/* 0E2E3C */ void ftCa_SpecialAirN_IASA(HSD_GObj* gobj);

/**
 * @brief Grounded Neutral-B (Falcon Punch) physics callback.
 * @details Spawns flame/dark visual effect and applies grounded
 * friction/movement.
 * @param gobj Pointer to Captain Falcon's Fighter GObj
 */
/* 0E2F2C */ void ftCa_SpecialN_Phys(HSD_GObj* gobj);

/**
 * @brief Aerial Neutral-B (Aerial Falcon Punch) physics callback.
 * @details Spawns flame/dark visual effect and applies aerial drag/gravity
 * based on cmd_vars[1].
 * @param gobj Pointer to Captain Falcon's Fighter GObj
 */
/* 0E3018 */ void ftCa_SpecialAirN_Phys(HSD_GObj* gobj);

/**
 * @brief Grounded Neutral-B (Falcon Punch) collision callback.
 * @details Checks if fighter walks off edge; transitions smoothly to aerial
 * Falcon Punch.
 * @param gobj Pointer to Captain Falcon's Fighter GObj
 */
/* 0E3168 */ void ftCa_SpecialN_Coll(HSD_GObj* gobj);

/**
 * @brief Aerial Neutral-B (Aerial Falcon Punch) collision callback.
 * @details Checks for ground contact; transitions smoothly to grounded Falcon
 * Punch.
 * @param gobj Pointer to Captain Falcon's Fighter GObj
 */
/* 0E31F4 */ void ftCa_SpecialAirN_Coll(HSD_GObj* gobj);

#endif
