/**
 * @file ftseakspeciallw.h
 * @brief Header for Sheik's Down-B move: Transform.
 * @details Declarations for grounded and aerial Down-B (Transform) action
 * states, controlling Sheik's transition to Zelda and vice versa. Module
 * prefix: ftSk (Fighter: Sheik)
 */

#ifndef GALE01_11108C
#define GALE01_11108C

#include <melee/ft/forward.h>

/**
 * @brief Enters grounded Down-B (Transform) phase 1 (disappearing).
 * @param gobj Fighter game object
 */
/* 114160 */ void ftSk_SpecialLw_Enter(Fighter_GObj* gobj);

/**
 * @brief Enters aerial Down-B (Transform) phase 1 (disappearing).
 * @param gobj Fighter game object
 */
/* 114224 */ void ftSk_SpecialAirLw_Enter(Fighter_GObj* gobj);

/**
 * @brief Animation update for grounded Down-B phase 1.
 * @param gobj Fighter game object
 */
/* 1142E8 */ void ftSk_SpecialLw_Anim(Fighter_GObj* gobj);

/**
 * @brief Animation update for aerial Down-B phase 1.
 * @param gobj Fighter game object
 */
/* 114328 */ void ftSk_SpecialAirLw_Anim(Fighter_GObj* gobj);

/**
 * @brief Interrupt check for grounded Down-B phase 1.
 * @param gobj Fighter game object
 */
/* 114368 */ void ftSk_SpecialLw_IASA(Fighter_GObj* gobj);

/**
 * @brief Interrupt check for aerial Down-B phase 1.
 * @param gobj Fighter game object
 */
/* 11436C */ void ftSk_SpecialAirLw_IASA(Fighter_GObj* gobj);

/**
 * @brief Physics update for grounded Down-B phase 1.
 * @param gobj Fighter game object
 */
/* 114370 */ void ftSk_SpecialLw_Phys(Fighter_GObj* gobj);

/**
 * @brief Physics update for aerial Down-B phase 1 (gravity fall & deaccel).
 * @param gobj Fighter game object
 */
/* 114390 */ void ftSk_SpecialAirLw_Phys(Fighter_GObj* gobj);

/**
 * @brief Collision update for grounded Down-B phase 1.
 * @param gobj Fighter game object
 */
/* 1143D4 */ void ftSk_SpecialLw_Coll(Fighter_GObj* gobj);

/**
 * @brief Collision update for aerial Down-B phase 1.
 * @param gobj Fighter game object
 */
/* 114410 */ void ftSk_SpecialAirLw_Coll(Fighter_GObj* gobj);

/**
 * @brief State transition: Grounded -> Aerial for Down-B phase 1.
 * @param gobj Fighter game object
 */
/* 11444C */ void ftSk_SpecialLw_8011444C(Fighter_GObj* gobj);

/**
 * @brief State transition: Aerial -> Grounded for Down-B phase 1.
 * @param gobj Fighter game object
 */
/* 1144B8 */ void ftSk_SpecialLw_801144B8(Fighter_GObj* gobj);

/**
 * @brief Animation update for grounded Down-B phase 2 (reappearing).
 * @param gobj Fighter game object
 */
/* 114524 */ void ftSk_SpecialLw2_Anim(Fighter_GObj* gobj);

/**
 * @brief Animation update for aerial Down-B phase 2 (reappearing).
 * @param gobj Fighter game object
 */
/* 114560 */ void ftSk_SpecialAirLw2_Anim(Fighter_GObj* gobj);

/**
 * @brief Interrupt check for grounded Down-B phase 2.
 * @param gobj Fighter game object
 */
/* 11459C */ void ftSk_SpecialLw2_IASA(Fighter_GObj* gobj);

/**
 * @brief Interrupt check for aerial Down-B phase 2.
 * @param gobj Fighter game object
 */
/* 1145A0 */ void ftSk_SpecialAirLw2_IASA(Fighter_GObj* gobj);

/**
 * @brief Physics update for grounded Down-B phase 2.
 * @param gobj Fighter game object
 */
/* 1145A4 */ void ftSk_SpecialLw2_Phys(Fighter_GObj* gobj);

/**
 * @brief Physics update for aerial Down-B phase 2.
 * @param gobj Fighter game object
 */
/* 1145C4 */ void ftSk_SpecialAirLw2_Phys(Fighter_GObj* gobj);

/**
 * @brief Collision update for grounded Down-B phase 2.
 * @param gobj Fighter game object
 */
/* 114608 */ void ftSk_SpecialLw2_Coll(Fighter_GObj* gobj);

/**
 * @brief Collision update for aerial Down-B phase 2.
 * @param gobj Fighter game object
 */
/* 114644 */ void ftSk_SpecialAirLw2_Coll(Fighter_GObj* gobj);

/**
 * @brief State transition: Grounded -> Aerial for Down-B phase 2.
 * @param gobj Fighter game object
 */
/* 114680 */ void ftSk_SpecialLw_80114680(Fighter_GObj* gobj);

/**
 * @brief State transition: Aerial -> Grounded for Down-B phase 2.
 * @param gobj Fighter game object
 */
/* 1146EC */ void ftSk_SpecialLw_801146EC(Fighter_GObj* gobj);

/**
 * @brief Enters transformation completion state when switching from Zelda to
 * Sheik.
 * @param gobj Fighter game object
 */
/* 114758 */ void ftSk_SpecialLw_80114758(Fighter_GObj* gobj);

#endif
