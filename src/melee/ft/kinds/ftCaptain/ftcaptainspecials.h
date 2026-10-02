/**
 * @file ftcaptainspecials.h
 * @brief Side Special - Raptor Boost (Captain Falcon) / Gerudo Dragon
 * (Ganondorf) (SpecialS)
 * @details Declarations for state entry, animation, IASA, physics, and
 * collision callbacks for Captain Falcon and Ganondorf's grounded and aerial
 * Side Special move. Module prefix: ftCa
 */

#ifndef GALE01_0E3278
#define GALE01_0E3278

#include <sysdolphin/baselib/forward.h>

/**
 * @brief Removes all Raptor Boost / Gerudo Dragon visual effects and resets
 * active flags.
 * @param gobj Pointer to Fighter GObj
 */
/* 0E3278 */ void ftCa_SpecialS_RemoveGFX(HSD_GObj* gobj);

/**
 * @brief Grounded Side-B Startup (Raptor Boost / Gerudo Dragon) state entry.
 * @param gobj Pointer to Fighter GObj
 */
/* 0E32B0 */ void ftCa_SpecialS_Enter(HSD_GObj* gobj);

/**
 * @brief Aerial Side-B Startup (Aerial Raptor Boost / Aerial Gerudo Dragon)
 * state entry.
 * @param gobj Pointer to Fighter GObj
 */
/* 0E33E0 */ void ftCa_SpecialAirS_Enter(HSD_GObj* gobj);

/**
 * @brief Hurtbox detection callback for Raptor Boost / Gerudo Dragon.
 * @details Triggers uppercut (ground) or meteor spike (air) upon contacting an
 * opponent or item.
 * @param gobj Pointer to Fighter GObj
 */
/* 0E350C */ void ftCa_SpecialS_OnDetect(HSD_GObj* gobj);

/**
 * @brief Grounded Side-B Startup (Raptor Boost) animation callback.
 * @param gobj Pointer to Fighter GObj
 */
/* 0E384C */ void ftCa_SpecialSStart_Anim(HSD_GObj* gobj);

/**
 * @brief Grounded Side-B Hit (Raptor Boost Uppercut) animation callback.
 * @param gobj Pointer to Fighter GObj
 */
/* 0E3888 */ void ftCa_SpecialS_Anim(HSD_GObj* gobj);

/**
 * @brief Aerial Side-B Startup (Aerial Raptor Boost) animation callback.
 * @param gobj Pointer to Fighter GObj
 */
/* 0E3964 */ void ftCa_SpecialAirSStart_Anim(HSD_GObj* gobj);

/**
 * @brief Aerial Side-B Hit (Aerial Raptor Boost Meteor Spike) animation
 * callback.
 * @param gobj Pointer to Fighter GObj
 */
/* 0E39F0 */ void ftCa_SpecialAirS_Anim(HSD_GObj* gobj);

/**
 * @brief Grounded Side-B Startup (Raptor Boost) IASA callback (no-op).
 * @param gobj Pointer to Fighter GObj
 */
/* 0E3B0C */ void ftCa_SpecialSStart_IASA(HSD_GObj* gobj);

/**
 * @brief Grounded Side-B Hit (Raptor Boost Uppercut) IASA callback (no-op).
 * @param gobj Pointer to Fighter GObj
 */
/* 0E3B10 */ void ftCa_SpecialS_IASA(HSD_GObj* gobj);

/**
 * @brief Aerial Side-B Startup (Aerial Raptor Boost) IASA callback (no-op).
 * @param gobj Pointer to Fighter GObj
 */
/* 0E3B14 */ void ftCa_SpecialAirSStart_IASA(HSD_GObj* gobj);

/**
 * @brief Aerial Side-B Hit (Aerial Raptor Boost Meteor Spike) IASA callback
 * (no-op).
 * @param gobj Pointer to Fighter GObj
 */
/* 0E3B18 */ void ftCa_SpecialAirS_IASA(HSD_GObj* gobj);

/**
 * @brief Grounded Side-B Startup (Raptor Boost) physics callback.
 * @param gobj Pointer to Fighter GObj
 */
/* 0E3B1C */ void ftCa_SpecialSStart_Phys(HSD_GObj* gobj);

/**
 * @brief Grounded Side-B Hit (Raptor Boost Uppercut) physics callback.
 * @param gobj Pointer to Fighter GObj
 */
/* 0E3B3C */ void ftCa_SpecialS_Phys(HSD_GObj* gobj);

/**
 * @brief Aerial Side-B Startup (Aerial Raptor Boost) physics callback.
 * @param gobj Pointer to Fighter GObj
 */
/* 0E3B5C */ void ftCa_SpecialAirSStart_Phys(HSD_GObj* gobj);

/**
 * @brief Aerial Side-B Hit (Aerial Raptor Boost Meteor Spike) physics
 * callback.
 * @param gobj Pointer to Fighter GObj
 */
/* 0E3BD0 */ void ftCa_SpecialAirS_Phys(HSD_GObj* gobj);

/**
 * @brief Grounded Side-B Startup (Raptor Boost) collision callback.
 * @param gobj Pointer to Fighter GObj
 */
/* 0E3C38 */ void ftCa_SpecialSStart_Coll(HSD_GObj* gobj);

/**
 * @brief Grounded Side-B Hit (Raptor Boost Uppercut) collision callback.
 * @param gobj Pointer to Fighter GObj
 */
/* 0E3D44 */ void ftCa_SpecialS_Coll(HSD_GObj* gobj);

/**
 * @brief Aerial Side-B Startup (Aerial Raptor Boost) collision callback.
 * @param gobj Pointer to Fighter GObj
 */
/* 0E3DE4 */ void ftCa_SpecialAirSStart_Coll(HSD_GObj* gobj);

/**
 * @brief Aerial Side-B Hit (Aerial Raptor Boost Meteor Spike) collision
 * callback.
 * @param gobj Pointer to Fighter GObj
 */
/* 0E3E40 */ void ftCa_SpecialAirS_Coll(HSD_GObj* gobj);

#endif
