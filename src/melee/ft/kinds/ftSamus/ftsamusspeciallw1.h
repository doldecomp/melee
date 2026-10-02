/**
 * @file ftsamusspeciallw1.h
 * @brief Down-B: Bomb Drop declarations for Samus
 * @details Declarations for Samus's Down-B special move (Bomb Drop),
 * including grounded/aerial entry, bomb spawning accessory callback,
 * morph ball hurtbox reconfiguration, animation, IASA, physics, and collision
 * callbacks. Module prefix: ftSs
 */

#ifndef GALE01_11444C
#define GALE01_11444C

#include <sysdolphin/baselib/forward.h>

/**
 * @brief Down-B (Bomb): Accessory callback that instantiates and spawns the
 * bomb item.
 * @param gobj Samus fighter game object pointer
 */
/* 12ADF0 */ void ftSs_SpecialLw_8012ADF0(HSD_GObj* gobj);

/**
 * @brief Down-B (Bomb): Reconfigures Samus's hurtbox to a single compact
 * sphere (Morph Ball).
 * @param gobj Samus fighter game object pointer
 */
/* 12AEBC */ void ftSs_SpecialLw_8012AEBC(HSD_GObj* gobj);

/**
 * @brief Down-B (Bomb): Restores Samus's default enabled hurtbox capsules.
 * @param gobj Samus fighter game object pointer
 */
/* 12AF38 */ void ftSs_SpecialLw_8012AF38(HSD_GObj* gobj);

/**
 * @brief Down-B (Bomb): Grounded action state entry callback.
 * @param gobj Samus fighter game object pointer
 */
/* 12AF5C */ void ftSs_SpecialLw_Enter(HSD_GObj* gobj);

/**
 * @brief Down-B (Bomb): Aerial action state entry callback.
 * @param gobj Samus fighter game object pointer
 */
/* 12B09C */ void ftSs_SpecialAirLw_Enter(HSD_GObj* gobj);

/**
 * @brief Down-B (Bomb): Grounded bomb release animation callback.
 * @param gobj Samus fighter game object pointer
 */
/* 12B150 */ void ftSs_SpecialLwBomb_Anim(HSD_GObj* gobj);

/**
 * @brief Down-B (Bomb): Aerial bomb release animation callback.
 * @param gobj Samus fighter game object pointer
 */
/* 12B264 */ void ftSs_SpecialAirLwBomb_Anim(HSD_GObj* gobj);

/**
 * @brief Down-B (Bomb): Grounded bomb release IASA callback (checks stick Y to
 * unmorph).
 * @param gobj Samus fighter game object pointer
 */
/* 12B358 */ void ftSs_SpecialLwBomb_IASA(HSD_GObj* gobj);

/**
 * @brief Down-B (Bomb): Aerial bomb release IASA callback.
 * @param gobj Samus fighter game object pointer
 */
/* 12B3A4 */ void ftSs_SpecialAirLwBomb_IASA(HSD_GObj* gobj);

/**
 * @brief Down-B (Bomb): Grounded bomb release physics callback.
 * @param gobj Samus fighter game object pointer
 */
/* 12B3A8 */ void ftSs_SpecialLwBomb_Phys(HSD_GObj* gobj);

/**
 * @brief Down-B (Bomb): Aerial bomb release physics callback.
 * @param gobj Samus fighter game object pointer
 */
/* 12B41C */ void ftSs_SpecialAirLwBomb_Phys(HSD_GObj* gobj);

/**
 * @brief Down-B (Bomb): Grounded bomb release collision callback.
 * @param gobj Samus fighter game object pointer
 */
/* 12B488 */ void ftSs_SpecialLwBomb_Coll(HSD_GObj* gobj);

/**
 * @brief Down-B (Bomb): Aerial bomb release collision callback.
 * @param gobj Samus fighter game object pointer
 */
/* 12B4FC */ void ftSs_SpecialAirLwBomb_Coll(HSD_GObj* gobj);

/**
 * @brief Down-B (Bomb): Ground-to-air transition during bomb drop.
 * @param gobj Samus fighter game object pointer
 */
/* 12B570 */ void ftSs_SpecialLw_8012B570(HSD_GObj* gobj);

/**
 * @brief Down-B (Bomb): Ground-to-air transition with vertical hop during bomb
 * drop.
 * @param gobj Samus fighter game object pointer
 */
/* 12B5F0 */ void ftSs_SpecialLw_8012B5F0(HSD_GObj* gobj);

/**
 * @brief Down-B (Bomb): Air-to-ground transition during bomb drop.
 * @param gobj Samus fighter game object pointer
 */
/* 12B668 */ void ftSs_SpecialLw_8012B668(HSD_GObj* gobj);

#endif
