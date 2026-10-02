#ifndef GALE01_11F1F8
#define GALE01_11F1F8

/**
 * @file ftpopospecialn.h
 * @brief Neutral-B: Ice Shot function declarations
 * @details Declarations for grounded and aerial Ice Shot state logic for Ice
 * Climbers (Popo). Module prefix: ftPp
 */

#include <sysdolphin/baselib/forward.h>

/**
 * @brief Enter grounded Neutral-B (Ice Shot)
 * @param gobj Fighter game object
 */
/* 11F1F8 */ void ftPp_SpecialN_Enter(HSD_GObj* gobj);

/**
 * @brief Enter aerial Neutral-B (Ice Shot)
 * @details Applies initial vertical hop impulse if first aerial use.
 * @param gobj Fighter game object
 */
/* 11F26C */ void ftPp_SpecialAirN_Enter(HSD_GObj* gobj);

/**
 * @brief Animation callback for grounded Neutral-B (Ice Shot)
 * @param gobj Fighter game object
 */
/* 11F318 */ void ftPp_SpecialN_Anim(HSD_GObj* gobj);

/**
 * @brief Animation callback for aerial Neutral-B (Ice Shot)
 * @param gobj Fighter game object
 */
/* 11F354 */ void ftPp_SpecialAirN_Anim(HSD_GObj* gobj);

/**
 * @brief Interruptible-as-soon-as callback for grounded Neutral-B (Ice Shot)
 * @param gobj Fighter game object
 */
/* 11F390 */ void ftPp_SpecialN_IASA(HSD_GObj* gobj);

/**
 * @brief Interruptible-as-soon-as callback for aerial Neutral-B (Ice Shot)
 * @param gobj Fighter game object
 */
/* 11F394 */ void ftPp_SpecialAirN_IASA(HSD_GObj* gobj);

/**
 * @brief Physics callback for grounded Neutral-B (Ice Shot)
 * @param gobj Fighter game object
 */
/* 11F398 */ void ftPp_SpecialN_Phys(HSD_GObj* gobj);

/**
 * @brief Physics callback for aerial Neutral-B (Ice Shot)
 * @param gobj Fighter game object
 */
/* 11F3B8 */ void ftPp_SpecialAirN_Phys(HSD_GObj* gobj);

/**
 * @brief Collision callback for grounded Neutral-B (Ice Shot)
 * @details Despawns ice block and enters fall if slipping off ledge.
 * @param gobj Fighter game object
 */
/* 11F3D8 */ void ftPp_SpecialN_Coll(HSD_GObj* gobj);

/**
 * @brief Collision callback for aerial Neutral-B (Ice Shot)
 * @details Handles landing detection and transitions to landing lag.
 * @param gobj Fighter game object
 */
/* 11F454 */ void ftPp_SpecialAirN_Coll(HSD_GObj* gobj);

#endif
