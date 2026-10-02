#ifndef GALE01_11F99C
#define GALE01_11F99C

/**
 * @file ftpopospecials.h
 * @brief Side-B: Squall Hammer function declarations
 * @details Declarations for grounded and aerial Squall Hammer move logic (solo
 * and paired) as well as Belay partner coordination helper declarations.
 * Module prefix: ftPp
 */

#include <melee/ft/forward.h>

/**
 * @brief Reset rotation and unlink partner references for Squall Hammer
 * @param gobj Fighter game object
 */
/* 11F68C */ void ftPp_SpecialS_8011F68C(Fighter_GObj* gobj);

/**
 * @brief Check partner's command var state for Squall Hammer
 * @param gobj Fighter game object
 * @return True if partner is valid and finished/available
 */
/* 11F6FC */ bool ftPp_SpecialS_8011F6FC(Fighter_GObj* gobj);

/**
 * @brief Update hammer head joint visibility and ground slope rotation
 * @param gobj Fighter game object
 */
/* 11F720 */ void ftPp_SpecialS_8011F720(Fighter_GObj* gobj);

/**
 * @brief Check if current motion state is a solo vs paired Squall Hammer state
 * @param gobj Fighter game object
 * @return False if paired (SpecialS2 / SpecialAirS2), true otherwise
 */
/* 11F964 */ bool ftPp_SpecialS_8011F964(Fighter_GObj* gobj);

/**
 * @brief Enter grounded Side-B: Squall Hammer
 * @details Checks partner availability; enters solo (SpecialS1) or paired
 * (SpecialS2) state.
 * @param gobj Fighter game object
 */
/* 11F99C */ void ftPp_SpecialS_Enter(Fighter_GObj* gobj);

/**
 * @brief Enter aerial Side-B: Squall Hammer
 * @param gobj Fighter game object
 */
/* 11FB08 */ void ftPp_SpecialAirS_Enter(Fighter_GObj* gobj);

/**
 * @brief Animation callback for grounded solo Squall Hammer
 * @param gobj Fighter game object
 */
/* 11FC78 */ void ftPp_SpecialS1_Anim(Fighter_GObj* gobj);

/**
 * @brief Animation callback for grounded paired Squall Hammer
 * @param gobj Fighter game object
 */
/* 11FCD0 */ void ftPp_SpecialS2_Anim(Fighter_GObj* gobj);

/**
 * @brief Animation callback for aerial solo Squall Hammer
 * @param gobj Fighter game object
 */
/* 11FD9C */ void ftPp_SpecialAirS1_Anim(Fighter_GObj* gobj);

/**
 * @brief Animation callback for aerial paired Squall Hammer
 * @param gobj Fighter game object
 */
/* 11FE48 */ void ftPp_SpecialAirS2_Anim(Fighter_GObj* gobj);

/**
 * @brief IASA steering input callback for grounded solo Squall Hammer
 * @param gobj Fighter game object
 */
/* 11FF40 */ void ftPp_SpecialS1_IASA(Fighter_GObj* gobj);

/**
 * @brief IASA steering input callback for grounded paired Squall Hammer
 * @param gobj Fighter game object
 */
/* 11FF90 */ void ftPp_SpecialS2_IASA(Fighter_GObj* gobj);

/**
 * @brief IASA steering input callback for aerial solo Squall Hammer
 * @param gobj Fighter game object
 */
/* 11FFE0 */ void ftPp_SpecialAirS1_IASA(Fighter_GObj* gobj);

/**
 * @brief IASA steering input callback for aerial paired Squall Hammer
 * @param gobj Fighter game object
 */
/* 120030 */ void ftPp_SpecialAirS2_IASA(Fighter_GObj* gobj);

/**
 * @brief Physics callback for grounded solo Squall Hammer
 * @details Applies horizontal acceleration, ground friction, and B-button mash
 * upward lift.
 * @param gobj Fighter game object
 */
/* 120080 */ void ftPp_SpecialS1_Phys(Fighter_GObj* gobj);

/**
 * @brief Physics callback for grounded paired Squall Hammer
 * @param gobj Fighter game object
 */
/* 120230 */ void ftPp_SpecialS2_Phys(Fighter_GObj* gobj);

/**
 * @brief Physics callback for aerial solo Squall Hammer
 * @details Applies air drift, custom gravity, and B-button mash vertical gain.
 * @param gobj Fighter game object
 */
/* 1203E0 */ void ftPp_SpecialAirS1_Phys(Fighter_GObj* gobj);

/**
 * @brief Physics callback for aerial paired Squall Hammer
 * @param gobj Fighter game object
 */
/* 120520 */ void ftPp_SpecialAirS2_Phys(Fighter_GObj* gobj);

/**
 * @brief Collision callback for grounded solo Squall Hammer
 * @details Checks ground contact and handles wall rebound / bounce reflection.
 * @param gobj Fighter game object
 */
/* 120660 */ void ftPp_SpecialS1_Coll(Fighter_GObj* gobj);

/**
 * @brief Collision callback for grounded paired Squall Hammer
 * @param gobj Fighter game object
 */
/* 120854 */ void ftPp_SpecialS2_Coll(Fighter_GObj* gobj);

/**
 * @brief Collision callback for aerial solo Squall Hammer
 * @details Checks landing, ceiling collision, and wall rebound reflection.
 * @param gobj Fighter game object
 */
/* 120A48 */ void ftPp_SpecialAirS1_Coll(Fighter_GObj* gobj);

/**
 * @brief Collision callback for aerial paired Squall Hammer
 * @param gobj Fighter game object
 */
/* 120C58 */ void ftPp_SpecialAirS2_Coll(Fighter_GObj* gobj);

/**
 * @brief Calculate impulse velocity for Nana towards Popo during Up-B (Belay)
 * @param gobj Fighter game object
 */
/* 120E68 */ void ftPp_SpecialS_80120E68(Fighter_GObj* gobj);

/**
 * @brief Progress Belay rope string event states on animation keyframes
 * @param gobj Fighter game object
 * @return True if rope failed to spawn and state was cancelled
 */
/* 120FE0 */ bool ftPp_SpecialS_80120FE0(Fighter_GObj* gobj);

/**
 * @brief Spawn Belay rope string item entity
 * @param gobj Fighter game object
 */
/* 1210C8 */ void ftPp_SpecialS_801210C8(Fighter_GObj* gobj);

/**
 * @brief Clear Belay rope string reference and callbacks
 * @param gobj Fighter game object
 */
/* 12114C */ void ftPp_SpecialS_8012114C(Fighter_GObj* gobj);

/**
 * @brief Despawn Belay rope string item entity
 * @param gobj Fighter game object
 */
/* 121164 */ void ftPp_SpecialS_80121164(Fighter_GObj* gobj);

#endif
