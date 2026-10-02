/**
 * @file ftseakspecialn.h
 * @brief Header for Sheik's Neutral-B move: Needle Storm.
 * @details Declarations for grounded and aerial Neutral-B (Needle Storm)
 * action states, including needle charging, charge loop, shield/dodge
 * cancellation, and needle firing. Module prefix: ftSk (Fighter: Sheik)
 */

#ifndef GALE01_111FBC
#define GALE01_111FBC

#include <melee/ft/forward.h>

/**
 * @brief Cleans up or drops held needles when Sheik takes damage or dies.
 * @param gobj Fighter game object
 */
/* 111FBC */ void ftSk_SpecialN_80111FBC(Fighter_GObj* gobj);

/**
 * @brief Enters grounded Neutral-B (Needle Storm) startup.
 * @param gobj Fighter game object
 */
/* 1120E8 */ void ftSk_SpecialN_Enter(Fighter_GObj* gobj);

/**
 * @brief Enters aerial Neutral-B (Needle Storm) startup.
 * @param gobj Fighter game object
 */
/* 112198 */ void ftSk_SpecialAirN_Enter(Fighter_GObj* gobj);

/**
 * @brief Animation update for grounded Neutral-B startup.
 * @param gobj Fighter game object
 */
/* 112248 */ void ftSk_SpecialNStart_Anim(Fighter_GObj* gobj);

/**
 * @brief Animation update for grounded Neutral-B charge loop (increments
 * needle count).
 * @param gobj Fighter game object
 */
/* 1122D8 */ void ftSk_SpecialNLoop_Anim(Fighter_GObj* gobj);

/**
 * @brief Animation update for grounded Neutral-B shield cancel.
 * @param gobj Fighter game object
 */
/* 112384 */ void ftSk_SpecialNCancel_Anim(Fighter_GObj* gobj);

/**
 * @brief Animation update for grounded Neutral-B needle throwing.
 * @param gobj Fighter game object
 */
/* 1123CC */ void ftSk_SpecialNEnd_Anim(Fighter_GObj* gobj);

/**
 * @brief Animation update for aerial Neutral-B startup.
 * @param gobj Fighter game object
 */
/* 112450 */ void ftSk_SpecialAirNStart_Anim(Fighter_GObj* gobj);

/**
 * @brief Animation update for aerial Neutral-B charge loop (increments needle
 * count).
 * @param gobj Fighter game object
 */
/* 1124E0 */ void ftSk_SpecialAirNLoop_Anim(Fighter_GObj* gobj);

/**
 * @brief Animation update for aerial Neutral-B cancel.
 * @param gobj Fighter game object
 */
/* 11258C */ void ftSk_SpecialAirNCancel_Anim(Fighter_GObj* gobj);

/**
 * @brief Animation update for aerial Neutral-B needle throwing.
 * @param gobj Fighter game object
 */
/* 11260C */ void ftSk_SpecialAirNEnd_Anim(Fighter_GObj* gobj);

/**
 * @brief Interrupt check for grounded Neutral-B startup.
 * @param gobj Fighter game object
 */
/* 1126C8 */ void ftSk_SpecialNStart_IASA(Fighter_GObj* gobj);

/**
 * @brief Interrupt check for grounded Neutral-B loop (handles B release to
 * fire, L/R to cancel).
 * @param gobj Fighter game object
 */
/* 1126CC */ void ftSk_SpecialNLoop_IASA(Fighter_GObj* gobj);

/**
 * @brief Interrupt check for grounded Neutral-B cancel.
 * @param gobj Fighter game object
 */
/* 112798 */ void ftSk_SpecialNCancel_IASA(Fighter_GObj* gobj);

/**
 * @brief Interrupt check for grounded Neutral-B throw.
 * @param gobj Fighter game object
 */
/* 11279C */ void ftSk_SpecialNEnd_IASA(Fighter_GObj* gobj);

/**
 * @brief Interrupt check for aerial Neutral-B startup.
 * @param gobj Fighter game object
 */
/* 1127A0 */ void ftSk_SpecialAirNStart_IASA(Fighter_GObj* gobj);

/**
 * @brief Interrupt check for aerial Neutral-B loop (handles B release to fire,
 * L/R to cancel).
 * @param gobj Fighter game object
 */
/* 1127A4 */ void ftSk_SpecialAirNLoop_IASA(Fighter_GObj* gobj);

/**
 * @brief Interrupt check for aerial Neutral-B cancel.
 * @param gobj Fighter game object
 */
/* 112870 */ void ftSk_SpecialAirNCancel_IASA(Fighter_GObj* gobj);

/**
 * @brief Interrupt check for aerial Neutral-B throw.
 * @param gobj Fighter game object
 */
/* 112874 */ void ftSk_SpecialAirNEnd_IASA(Fighter_GObj* gobj);

/**
 * @brief Physics update for grounded Neutral-B startup.
 * @param gobj Fighter game object
 */
/* 112878 */ void ftSk_SpecialNStart_Phys(Fighter_GObj* gobj);

/**
 * @brief Physics update for grounded Neutral-B loop.
 * @param gobj Fighter game object
 */
/* 112898 */ void ftSk_SpecialNLoop_Phys(Fighter_GObj* gobj);

/**
 * @brief Physics update for grounded Neutral-B cancel.
 * @param gobj Fighter game object
 */
/* 1128B8 */ void ftSk_SpecialNCancel_Phys(Fighter_GObj* gobj);

/**
 * @brief Physics update for grounded Neutral-B throw.
 * @param gobj Fighter game object
 */
/* 1128D8 */ void ftSk_SpecialNEnd_Phys(Fighter_GObj* gobj);

/**
 * @brief Physics update for aerial Neutral-B startup.
 * @param gobj Fighter game object
 */
/* 1128F8 */ void ftSk_SpecialAirNStart_Phys(Fighter_GObj* gobj);

/**
 * @brief Physics update for aerial Neutral-B loop.
 * @param gobj Fighter game object
 */
/* 112918 */ void ftSk_SpecialAirNLoop_Phys(Fighter_GObj* gobj);

/**
 * @brief Physics update for aerial Neutral-B cancel.
 * @param gobj Fighter game object
 */
/* 112938 */ void ftSk_SpecialAirNCancel_Phys(Fighter_GObj* gobj);

/**
 * @brief Physics update for aerial Neutral-B throw.
 * @param gobj Fighter game object
 */
/* 112958 */ void ftSk_SpecialAirNEnd_Phys(Fighter_GObj* gobj);

/**
 * @brief Collision update for grounded Neutral-B startup.
 * @param gobj Fighter game object
 */
/* 112978 */ void ftSk_SpecialNStart_Coll(Fighter_GObj* gobj);

/**
 * @brief Collision update for grounded Neutral-B loop.
 * @param gobj Fighter game object
 */
/* 1129F8 */ void ftSk_SpecialNLoop_Coll(Fighter_GObj* gobj);

/**
 * @brief Collision update for grounded Neutral-B cancel.
 * @param gobj Fighter game object
 */
/* 112A78 */ void ftSk_SpecialNCancel_Coll(Fighter_GObj* gobj);

/**
 * @brief Collision update for grounded Neutral-B throw.
 * @param gobj Fighter game object
 */
/* 112B00 */ void ftSk_SpecialNEnd_Coll(Fighter_GObj* gobj);

/**
 * @brief Collision update for aerial Neutral-B startup.
 * @param gobj Fighter game object
 */
/* 112B98 */ void ftSk_SpecialAirNStart_Coll(Fighter_GObj* gobj);

/**
 * @brief Collision update for aerial Neutral-B loop.
 * @param gobj Fighter game object
 */
/* 112C18 */ void ftSk_SpecialAirNLoop_Coll(Fighter_GObj* gobj);

/**
 * @brief Collision update for aerial Neutral-B cancel.
 * @param gobj Fighter game object
 */
/* 112C98 */ void ftSk_SpecialAirNCancel_Coll(Fighter_GObj* gobj);

/**
 * @brief Collision update for aerial Neutral-B throw.
 * @param gobj Fighter game object
 */
/* 112CE4 */ void ftSk_SpecialAirNEnd_Coll(Fighter_GObj* gobj);

#endif
