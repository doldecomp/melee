/**
 * @file ftsamusspecialhi.h
 * @brief Up-B: Screw Attack declarations for Samus
 * @details Function declarations for Samus's Up-B special move (Screw Attack),
 * including grounded/aerial entry, animation, IASA turnaround, physics, and
 * collision callbacks. Module prefix: ftSs
 */

#ifndef GALE01_12A674
#define GALE01_12A674

#include <sysdolphin/baselib/forward.h>

/**
 * @brief Up-B (Screw Attack): Grounded action state entry callback.
 * @param gobj Samus fighter game object pointer
 */
/* 12A674 */ void ftSs_SpecialHi_Enter(HSD_GObj* gobj);

/**
 * @brief Up-B (Screw Attack): Aerial action state entry callback.
 * @param gobj Samus fighter game object pointer
 */
/* 12A738 */ void ftSs_SpecialAirHi_Enter(HSD_GObj* gobj);

/**
 * @brief Up-B (Screw Attack): Grounded animation callback.
 * @param gobj Samus fighter game object pointer
 */
/* 12A81C */ void ftSs_SpecialHi_Anim(HSD_GObj* gobj);

/**
 * @brief Up-B (Screw Attack): Aerial animation callback.
 * @param gobj Samus fighter game object pointer
 */
/* 12A8C4 */ void ftSs_SpecialAirHi_Anim(HSD_GObj* gobj);

/**
 * @brief Up-B (Screw Attack): Grounded IASA callback (checks B-reverse /
 * turnaround input).
 * @param gobj Samus fighter game object pointer
 */
/* 12A96C */ void ftSs_SpecialHi_IASA(HSD_GObj* gobj);

/**
 * @brief Up-B (Screw Attack): Aerial IASA callback (checks B-reverse /
 * turnaround input).
 * @param gobj Samus fighter game object pointer
 */
/* 12AA3C */ void ftSs_SpecialAirHi_IASA(HSD_GObj* gobj);

/**
 * @brief Up-B (Screw Attack): Grounded physics callback.
 * @param gobj Samus fighter game object pointer
 */
/* 12AB0C */ void ftSs_SpecialHi_Phys(HSD_GObj* gobj);

/**
 * @brief Up-B (Screw Attack): Aerial physics callback.
 * @param gobj Samus fighter game object pointer
 */
/* 12ABB4 */ void ftSs_SpecialAirHi_Phys(HSD_GObj* gobj);

/**
 * @brief Up-B (Screw Attack): Grounded collision callback.
 * @param gobj Samus fighter game object pointer
 */
/* 12AC00 */ void ftSs_SpecialHi_Coll(HSD_GObj* gobj);

/**
 * @brief Up-B (Screw Attack): Aerial collision callback.
 * @param gobj Samus fighter game object pointer
 */
/* 12ACF8 */ void ftSs_SpecialAirHi_Coll(HSD_GObj* gobj);

#endif
