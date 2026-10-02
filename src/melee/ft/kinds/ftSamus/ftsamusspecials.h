/**
 * @file ftsamusspecials.h
 * @brief Side-B: Missile declarations for Samus
 * @details Function declarations for Samus's Side-B special move (Missile),
 * including grounded/aerial entry, tilt input (Homing Missile), smash input
 * (Super Missile), animation, IASA, physics, and collision callbacks. Module
 * prefix: ftSs
 */

#ifndef GALE01_12A1D8
#define GALE01_12A1D8

#include <sysdolphin/baselib/forward.h>

/**
 * @brief Side-B (Missile): Grounded action state entry callback.
 * @details Determines whether to fire a Homing Missile or Super Missile based
 * on smash input.
 * @param gobj Samus fighter game object pointer
 */
/* 12A1D8 */ void ftSs_SpecialS_Enter(HSD_GObj* gobj);

/**
 * @brief Side-B (Missile): Aerial action state entry callback.
 * @details Determines whether to fire a Homing Missile or Super Missile based
 * on smash input.
 * @param gobj Samus fighter game object pointer
 */
/* 12A2AC */ void ftSs_SpecialAirS_Enter(HSD_GObj* gobj);

/**
 * @brief Side-B (Homing Missile): Grounded animation callback.
 * @param gobj Samus fighter game object pointer
 */
/* 12A380 */ void ftSs_SpecialS_Anim(HSD_GObj* gobj);

/**
 * @brief Side-B (Homing Missile): Aerial animation callback.
 * @param gobj Samus fighter game object pointer
 */
/* 12A3BC */ void ftSs_SpecialAirS_Anim(HSD_GObj* gobj);

/**
 * @brief Side-B (Homing Missile): Grounded IASA callback.
 * @param gobj Samus fighter game object pointer
 */
/* 12A3F8 */ void ftSs_SpecialS_IASA(HSD_GObj* gobj);

/**
 * @brief Side-B (Homing Missile): Aerial IASA callback.
 * @param gobj Samus fighter game object pointer
 */
/* 12A3FC */ void ftSs_SpecialAirS_IASA(HSD_GObj* gobj);

/**
 * @brief Side-B (Homing Missile): Grounded physics callback.
 * @param gobj Samus fighter game object pointer
 */
/* 12A400 */ void ftSs_SpecialS_Phys(HSD_GObj* gobj);

/**
 * @brief Side-B (Homing Missile): Aerial physics callback.
 * @param gobj Samus fighter game object pointer
 */
/* 12A420 */ void ftSs_SpecialAirS_Phys(HSD_GObj* gobj);

/**
 * @brief Side-B (Homing Missile): Grounded collision callback.
 * @param gobj Samus fighter game object pointer
 */
/* 12A468 */ void ftSs_SpecialS_Coll(HSD_GObj* gobj);

/**
 * @brief Side-B (Homing Missile): Aerial collision callback.
 * @param gobj Samus fighter game object pointer
 */
/* 12A4A4 */ void ftSs_SpecialAirS_Coll(HSD_GObj* gobj);

/**
 * @brief Side-B (Super Missile): Grounded animation callback.
 * @param gobj Samus fighter game object pointer
 */
/* 12A4E0 */ void ftSs_SpecialSSmash_Anim(HSD_GObj* gobj);

/**
 * @brief Side-B (Super Missile): Aerial animation callback.
 * @param gobj Samus fighter game object pointer
 */
/* 12A51C */ void ftSs_SpecialAirSSmash_Anim(HSD_GObj* gobj);

/**
 * @brief Side-B (Super Missile): Grounded IASA callback.
 * @param gobj Samus fighter game object pointer
 */
/* 12A558 */ void ftSs_SpecialSSmash_IASA(HSD_GObj* gobj);

/**
 * @brief Side-B (Super Missile): Aerial IASA callback.
 * @param gobj Samus fighter game object pointer
 */
/* 12A55C */ void ftSs_SpecialAirSSmash_IASA(HSD_GObj* gobj);

/**
 * @brief Side-B (Super Missile): Grounded physics callback.
 * @param gobj Samus fighter game object pointer
 */
/* 12A560 */ void ftSs_SpecialSSmash_Phys(HSD_GObj* gobj);

/**
 * @brief Side-B (Super Missile): Aerial physics callback.
 * @param gobj Samus fighter game object pointer
 */
/* 12A580 */ void ftSs_SpecialAirSSmash_Phys(HSD_GObj* gobj);

/**
 * @brief Side-B (Super Missile): Grounded collision callback.
 * @param gobj Samus fighter game object pointer
 */
/* 12A5C8 */ void ftSs_SpecialSSmash_Coll(HSD_GObj* gobj);

/**
 * @brief Side-B (Super Missile): Aerial collision callback.
 * @param gobj Samus fighter game object pointer
 */
/* 12A604 */ void ftSs_SpecialAirSSmash_Coll(HSD_GObj* gobj);

/**
 * @brief Side-B (Missile): Cleans up visual effects and clears active flag.
 * @param gobj Samus fighter game object pointer
 */
/* 12A640 */ void ftSs_SpecialS_8012A640(HSD_GObj* gobj);

#endif
