/**
 * @file ftcaptainspeciallw.h
 * @brief Down Special - Falcon Kick (Captain Falcon) / Wizard's Foot
 * (Ganondorf) (SpecialLw)
 * @details Declarations for state entry, animation, physics, and collision
 * callbacks for Captain Falcon and Ganondorf's grounded and aerial Down
 * Special move (Falcon Kick). Module prefix: ftCa
 */

#ifndef GALE01_0E415C
#define GALE01_0E415C

#include <sysdolphin/baselib/forward.h>

/**
 * @brief Spawns foot flame particle effect on the kicking foot during Falcon
 * Kick.
 * @param gobj Pointer to Fighter GObj
 */
/* 0E3EAC */ void ftCa_SpecialHi_800E3EAC(HSD_GObj* gobj);

/**
 * @brief Grounded Down-B (Falcon Kick) state entry.
 * @param gobj Pointer to Fighter GObj
 */
/* 0E4040 */ void ftCa_SpecialLw_Enter(HSD_GObj* gobj);

/**
 * @brief Aerial Down-B (Aerial Falcon Kick) state entry.
 * @param gobj Pointer to Fighter GObj
 */
/* 0E40D8 */ void ftCa_SpecialAirLw_Enter(HSD_GObj* gobj);

/**
 * @brief Grounded Down-B (Falcon Kick) animation callback.
 * @param gobj Pointer to Fighter GObj
 */
/* 0E415C */ void ftCa_SpecialLw_Anim(HSD_GObj* gobj);

/**
 * @brief Grounded Down-B Ground Recovery (Falcon Kick End) animation callback.
 * @param gobj Pointer to Fighter GObj
 */
/* 0E4268 */ void ftCa_SpecialLwEnd_Anim(HSD_GObj* gobj);

/**
 * @brief Grounded Down-B Edge Slip Air Recovery (Falcon Kick End Air)
 * animation callback.
 * @param gobj Pointer to Fighter GObj
 */
/* 0E42A4 */ void ftCa_SpecialLwEndAir_Anim(HSD_GObj* gobj);

/**
 * @brief Aerial Down-B (Aerial Falcon Kick) animation callback.
 * @param gobj Pointer to Fighter GObj
 */
/* 0E42E0 */ void ftCa_SpecialAirLw_Anim(HSD_GObj* gobj);

/**
 * @brief Aerial Down-B Landing Recovery (Falcon Kick Landing End) animation
 * callback.
 * @param gobj Pointer to Fighter GObj
 */
/* 0E4354 */ void ftCa_SpecialAirLwEnd_Anim(HSD_GObj* gobj);

/**
 * @brief Aerial Down-B Air Recovery (Falcon Kick Air End Air) animation
 * callback.
 * @param gobj Pointer to Fighter GObj
 */
/* 0E4390 */ void ftCa_SpecialAirLwEndAir_Anim(HSD_GObj* gobj);

/**
 * @brief Falcon Kick Wall Rebound (Wall Bonk) animation callback.
 * @param gobj Pointer to Fighter GObj
 */
/* 0E43CC */ void ftCa_SpecialHiThrow1_Anim(HSD_GObj* gobj);

/**
 * @brief Grounded Down-B (Falcon Kick) physics callback.
 * @param gobj Pointer to Fighter GObj
 */
/* 0E4408 */ void ftCa_SpecialLw_Phys(HSD_GObj* gobj);

/**
 * @brief Grounded Down-B Ground Recovery physics callback.
 * @param gobj Pointer to Fighter GObj
 */
/* 0E449C */ void ftCa_SpecialLwEnd_Phys(HSD_GObj* gobj);

/**
 * @brief Grounded Down-B Edge Slip Air Recovery physics callback.
 * @param gobj Pointer to Fighter GObj
 */
/* 0E455C */ void ftCa_SpecialLwEndAir_Phys(HSD_GObj* gobj);

/**
 * @brief Aerial Down-B (Aerial Falcon Kick) physics callback.
 * @param gobj Pointer to Fighter GObj
 */
/* 0E45E4 */ void ftCa_SpecialAirLw_Phys(HSD_GObj* gobj);

/**
 * @brief Aerial Down-B Landing Recovery physics callback.
 * @param gobj Pointer to Fighter GObj
 */
/* 0E4618 */ void ftCa_SpecialAirLwEnd_Phys(HSD_GObj* gobj);

/**
 * @brief Aerial Down-B Air Recovery physics callback.
 * @param gobj Pointer to Fighter GObj
 */
/* 0E4678 */ void ftCa_SpecialAirLwEndAir_Phys(HSD_GObj* gobj);

/**
 * @brief Falcon Kick Wall Rebound physics callback.
 * @param gobj Pointer to Fighter GObj
 */
/* 0E4698 */ void ftCa_SpecialHiThrow1_Phys(HSD_GObj* gobj);

/**
 * @brief Grounded Down-B (Falcon Kick) collision callback.
 * @details Checks ground-to-air transition and wall collisions (triggers wall
 * bonk rebound).
 * @param gobj Pointer to Fighter GObj
 */
/* 0E46B8 */ void ftCa_SpecialLw_Coll(HSD_GObj* gobj);

/**
 * @brief Grounded Down-B Ground Recovery collision callback.
 * @param gobj Pointer to Fighter GObj
 */
/* 0E47B0 */ void ftCa_SpecialLwEnd_Coll(HSD_GObj* gobj);

/**
 * @brief Grounded Down-B Edge Slip Air Recovery collision callback.
 * @param gobj Pointer to Fighter GObj
 */
/* 0E4838 */ void ftCa_SpecialLwEndAir_Coll(HSD_GObj* gobj);

/**
 * @brief Aerial Down-B (Aerial Falcon Kick) collision callback.
 * @details Handles landing on ground into landing lag recovery.
 * @param gobj Pointer to Fighter GObj
 */
/* 0E48BC */ void ftCa_SpecialAirLw_Coll(HSD_GObj* gobj);

/**
 * @brief Aerial Down-B Landing Recovery collision callback.
 * @param gobj Pointer to Fighter GObj
 */
/* 0E493C */ void ftCa_SpecialAirLwEnd_Coll(HSD_GObj* gobj);

/**
 * @brief Aerial Down-B Air Recovery collision callback.
 * @param gobj Pointer to Fighter GObj
 */
/* 0E495C */ void ftCa_SpecialAirLwEndAir_Coll(HSD_GObj* gobj);

#endif
