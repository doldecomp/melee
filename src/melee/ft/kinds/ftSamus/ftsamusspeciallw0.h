/**
 * @file ftsamusspeciallw0.h
 * @brief Down-B: Morph Ball & Bomb Jump declarations for Samus
 * @details Declarations for Samus's Down-B Morph Ball and Bomb Jump states,
 * including animation, IASA, physics, collision, and Charge Shot state
 * queries. Module prefix: ftSs
 */

#ifndef GALE01_128944
#define GALE01_128944

#include <sysdolphin/baselib/forward.h>

/**
 * @brief Down-B (Morph Ball / Bomb Jump): Grounded animation callback.
 * @param gobj Samus fighter game object pointer
 */
/* 128C04 */ void ftSs_SpecialLw_Anim(HSD_GObj* gobj);

/**
 * @brief Down-B (Morph Ball / Bomb Jump): Aerial animation callback.
 * @param gobj Samus fighter game object pointer
 */
/* 128CA0 */ void ftSs_SpecialAirLw_Anim(HSD_GObj* gobj);

/**
 * @brief Down-B (Morph Ball): Grounded IASA callback (uncrouch stick check and
 * attack cancels).
 * @param gobj Samus fighter game object pointer
 */
/* 128D3C */ void ftSs_SpecialLw_IASA(HSD_GObj* gobj);

/**
 * @brief Down-B (Morph Ball): Aerial IASA callback.
 * @param gobj Samus fighter game object pointer
 */
/* 128E68 */ void ftSs_SpecialAirLw_IASA(HSD_GObj* gobj);

/**
 * @brief Down-B (Morph Ball): Grounded physics callback.
 * @param gobj Samus fighter game object pointer
 */
/* 128E88 */ void ftSs_SpecialLw_Phys(HSD_GObj* gobj);

/**
 * @brief Down-B (Morph Ball): Aerial physics callback.
 * @param gobj Samus fighter game object pointer
 */
/* 128EF8 */ void ftSs_SpecialAirLw_Phys(HSD_GObj* gobj);

/**
 * @brief Down-B (Morph Ball): Grounded collision callback.
 * @param gobj Samus fighter game object pointer
 */
/* 128F60 */ void ftSs_SpecialLw_Coll(HSD_GObj* gobj);

/**
 * @brief Down-B (Morph Ball): Aerial collision callback.
 * @param gobj Samus fighter game object pointer
 */
/* 128FD4 */ void ftSs_SpecialAirLw_Coll(HSD_GObj* gobj);

/**
 * @brief Down-B (Morph Ball): Ground-to-air transition.
 * @param gobj Samus fighter game object pointer
 */
/* 129048 */ void ftSs_SpecialLw_80129048(HSD_GObj* gobj);

/**
 * @brief Down-B (Morph Ball): Air-to-ground transition.
 * @param gobj Samus fighter game object pointer
 */
/* 1290A4 */ void ftSs_SpecialLw_801290A4(HSD_GObj* gobj);

/**
 * @brief Queries current and maximum Charge Shot charge levels.
 * @param gobj Samus fighter game object pointer
 * @param[out] out_charge Current charge level pointer
 * @param[out] out_max Maximum charge level pointer
 * @return 0 on success, -1 if no Charge Shot is active
 */
/* 129100 */ int ftSs_SpecialLw_80129100(HSD_GObj* gobj, int* out_charge,
                                         int* out_max);

/**
 * @brief Checks if Samus is currently in Neutral-B charge states with state
 * flag set.
 * @param gobj Samus fighter game object pointer
 * @return Status flag (0 or 1)
 */
/* 129158 */ s32 ftSs_SpecialLw_80129158(HSD_GObj* gobj);

/**
 * @brief Checks if Samus is currently in Neutral-B (Charge Shot) motion
 * states.
 * @param gobj Samus fighter game object pointer
 * @return 0 if charging/firing Charge Shot, 1 otherwise
 */
/* 1291A8 */ s32 ftSs_SpecialN_801291A8(HSD_GObj* gobj);

#endif
