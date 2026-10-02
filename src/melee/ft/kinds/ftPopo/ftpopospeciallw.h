#ifndef GALE01_122904
#define GALE01_122904

/**
 * @file ftpopospeciallw.h
 * @brief Down-B: Blizzard function declarations
 * @details Declarations for grounded and aerial Blizzard state logic for Ice
 * Climbers (Popo/Nana). Module prefix: ftPp
 */

#include <melee/ft/forward.h>

/**
 * @brief Enter grounded Down-B (Blizzard)
 * @param gobj Fighter game object
 */
/* 122904 */ void ftPp_SpecialLw_Enter(Fighter_GObj* gobj);

/**
 * @brief Enter aerial Down-B (Blizzard)
 * @param gobj Fighter game object
 */
/* 122988 */ void ftPp_SpecialAirLw_Enter(Fighter_GObj* gobj);

/**
 * @brief Animation callback for grounded Down-B (Blizzard)
 * @details Cleans up particle effects on animation end and transitions to
 * Wait.
 * @param gobj Fighter game object
 */
/* 122A0C */ void ftPp_SpecialLw_Anim(Fighter_GObj* gobj);

/**
 * @brief Animation callback for aerial Down-B (Blizzard)
 * @details Cleans up particle effects on animation end and transitions to
 * Fall.
 * @param gobj Fighter game object
 */
/* 122A8C */ void ftPp_SpecialAirLw_Anim(Fighter_GObj* gobj);

/**
 * @brief IASA callback for grounded Down-B (Blizzard)
 * @param gobj Fighter game object
 */
/* 122B0C */ void ftPp_SpecialLw_IASA(Fighter_GObj* gobj);

/**
 * @brief IASA callback for aerial Down-B (Blizzard)
 * @param gobj Fighter game object
 */
/* 122B10 */ void ftPp_SpecialAirLw_IASA(Fighter_GObj* gobj);

/**
 * @brief Physics callback for grounded Down-B (Blizzard)
 * @param gobj Fighter game object
 */
/* 122B14 */ void ftPp_SpecialLw_Phys(Fighter_GObj* gobj);

/**
 * @brief Physics callback for aerial Down-B (Blizzard)
 * @param gobj Fighter game object
 */
/* 122B34 */ void ftPp_SpecialAirLw_Phys(Fighter_GObj* gobj);

/**
 * @brief Air-to-ground transition callback for Down-B (Blizzard)
 * @param gobj Fighter game object
 */
/* 122B54 */ void fn_80122B54(Fighter_GObj* gobj);

/**
 * @brief Collision callback for grounded Down-B (Blizzard)
 * @details Adjusts joint rotation to match ground slope angle.
 * @param gobj Fighter game object
 */
/* 122C18 */ void ftPp_SpecialLw_Coll(Fighter_GObj* gobj);

/**
 * @brief Collision callback for aerial Down-B (Blizzard)
 * @param gobj Fighter game object
 */
/* 122D04 */ void ftPp_SpecialAirLw_Coll(Fighter_GObj* gobj);

/**
 * @brief Animation accessory callback for Down-B (Blizzard)
 * @details Spawns periodic blizzard frost breath projectiles and handles sound
 * effects.
 * @param gobj Fighter game object
 */
/* 122D2C */ void fn_80122D2C(Fighter_GObj* gobj);

#endif
