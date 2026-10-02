/**
 * @file ftseakspecials.h
 * @brief Header for Sheik's Side-B move: Chain.
 * @details Declarations for grounded and aerial Side-B (Chain) action states,
 * whip animation blending, chain segment hitbox positioning, and hitlag
 * callbacks. Module prefix: ftSk (Fighter: Sheik)
 */

#ifndef GALE01_110490
#define GALE01_110490

#include <Runtime/platform.h>

#include <melee/ft/forward.h>
#include <sysdolphin/baselib/forward.h>

#include <dolphin/mtx.h>

/**
 * @brief Updates chain whip target angle and extension magnitude from control
 * stick.
 * @param fp Fighter pointer
 */
/* 110490 */ void ftSk_SpecialS_80110490(Fighter* fp);

/**
 * @brief Blends upper body and arm joint animation towards chain direction.
 * @param gobj Fighter game object
 * @param anim_id Animation identifier
 * @param blend_weight Blend weight factor
 */
/* 110610 */ void ftSk_SpecialS_80110610(HSD_GObj* gobj, s32 anim_id,
                                         float blend_weight);

/**
 * @brief Plays whip snapping and cracking sound effects based on control stick
 * flicks.
 * @param gobj Fighter game object
 */
/* 110788 */ void ftSk_SpecialS_80110788(HSD_GObj* gobj);

/**
 * @brief Empty accessory callback stub for Side-B.
 * @param gobj Fighter game object
 */
/* 11097C */ void ftSk_SpecialS_8011097C(HSD_GObj* gobj);

/**
 * @brief Updates position for a specific chain segment hitbox.
 * @param gobj Fighter game object
 * @param new_position New 3D position vector
 * @param hitbox_id Hitbox slot index (0-3)
 */
/* 110980 */ void ftSk_SpecialS_UpdateHitboxes(HSD_GObj* gobj,
                                               Vec3* new_position,
                                               s32 hitbox_id);

/**
 * @brief Zeroes out position and previous position vectors for all 4 chain
 * hitboxes.
 * @param gobj Fighter game object
 */
/* 110A80 */ void ftSk_SpecialS_ZeroHitboxPositions(HSD_GObj* gobj);

/**
 * @brief Resets collision status and refreshes all 4 chain hitboxes.
 * @param gobj Fighter game object
 */
/* 110AEC */ void ftSk_SpecialS_80110AEC(HSD_GObj* gobj);

/**
 * @brief Monitors chain segment movement and enables hitboxes when whip speed
 * exceeds threshold.
 * @param gobj Fighter game object
 */
/* 110BCC */ void ftSk_SpecialS_80110BCC(HSD_GObj* gobj);

/**
 * @brief Unlinks chain item and clears fighter callbacks upon state interrupt.
 * @param gobj Fighter game object
 */
/* 110E4C */ void ftSk_SpecialS_80110E4C(HSD_GObj* gobj);

/**
 * @brief Despawns active chain item entity and clears references.
 * @param gobj Fighter game object
 */
/* 110E88 */ void ftSk_SpecialS_CheckAndDestroyChain(HSD_GObj* gobj);

/**
 * @brief Pre-hitlag callback: pauses chain entity during hitlag.
 * @param gobj Fighter game object
 */
/* 110EE8 */ void ftSk_SpecialS_80110EE8(HSD_GObj* gobj);

/**
 * @brief Post-hitlag callback: resumes chain entity after hitlag.
 * @param gobj Fighter game object
 */
/* 110F18 */ void ftSk_SpecialS_ChainSomething(HSD_GObj* gobj);

/**
 * @brief Returns current horizontal control stick input.
 * @param gobj Fighter game object
 * @return float Control stick X position [-1.0, 1.0]
 */
/* 110F58 */ float ftSk_SpecialS_80110F58(HSD_GObj* gobj);

/**
 * @brief Returns current vertical control stick input.
 * @param gobj Fighter game object
 * @return float Control stick Y position [-1.0, 1.0]
 */
/* 110F64 */ float ftSk_SpecialS_80110F64(HSD_GObj* gobj);

/**
 * @brief Initializes Side-B motion variables and zeroes chain hitbox tracking.
 * @param gobj Fighter game object
 */
/* 110F70 */ void ftSk_SpecialS_80110F70(HSD_GObj* gobj);

/**
 * @brief Enters grounded Side-B (Chain) startup.
 * @param gobj Fighter game object
 */
/* 111038 */ void ftSk_SpecialS_Enter(HSD_GObj* gobj);

/**
 * @brief Enters aerial Side-B (Chain) startup.
 * @param gobj Fighter game object
 */
/* 11108C */ void ftSk_SpecialAirS_Enter(HSD_GObj* gobj);

/**
 * @brief Handles chain spawn timing during startup.
 * @param gobj Fighter game object
 * @return bool True if startup duration finished and ready for active whip
 * loop
 */
/* 1110E8 */ bool ftSk_SpecialS_CheckInitChain(HSD_GObj* gobj);

/**
 * @brief Animation update for grounded Side-B startup.
 * @param gobj Fighter game object
 */
/* 1112CC */ void ftSk_SpecialSStart_Anim(HSD_GObj* gobj);

/**
 * @brief Animation update for aerial Side-B startup.
 * @param gobj Fighter game object
 */
/* 111308 */ void ftSk_SpecialAirSStart_Anim(HSD_GObj* gobj);

/**
 * @brief Interrupt check for grounded Side-B startup.
 * @param gobj Fighter game object
 */
/* 111344 */ void ftSk_SpecialSStart_IASA(HSD_GObj* gobj);

/**
 * @brief Interrupt check for aerial Side-B startup.
 * @param gobj Fighter game object
 */
/* 111348 */ void ftSk_SpecialAirSStart_IASA(HSD_GObj* gobj);

/**
 * @brief Physics update for grounded Side-B startup.
 * @param gobj Fighter game object
 */
/* 11134C */ void ftSk_SpecialSStart_Phys(HSD_GObj* gobj);

/**
 * @brief Physics update for aerial Side-B startup.
 * @param gobj Fighter game object
 */
/* 11136C */ void ftSk_SpecialAirSStart_Phys(HSD_GObj* gobj);

/**
 * @brief Collision update for grounded Side-B startup.
 * @param gobj Fighter game object
 */
/* 1113C8 */ void ftSk_SpecialSStart_Coll(HSD_GObj* gobj);

/**
 * @brief Collision update for aerial Side-B startup.
 * @param gobj Fighter game object
 */
/* 111404 */ void ftSk_SpecialAirSStart_Coll(HSD_GObj* gobj);

/**
 * @brief State transition: Grounded -> Aerial for Side-B startup.
 * @param gobj Fighter game object
 */
/* 111440 */ void ftSk_SpecialS_80111440(HSD_GObj* gobj);

/**
 * @brief State transition: Aerial -> Grounded for Side-B startup.
 * @param gobj Fighter game object
 */
/* 1114E4 */ void ftSk_SpecialS_801114E4(HSD_GObj* gobj);

/**
 * @brief Animation update for grounded active Side-B loop.
 * @param gobj Fighter game object
 */
/* 111588 */ void ftSk_SpecialS_Anim(HSD_GObj* gobj);

/**
 * @brief Animation update for aerial active Side-B loop.
 * @param gobj Fighter game object
 */
/* 111648 */ void ftSk_SpecialAirS_Anim(HSD_GObj* gobj);

/**
 * @brief Interrupt check for grounded active Side-B loop (handles B button
 * release).
 * @param gobj Fighter game object
 */
/* 111708 */ void ftSk_SpecialS_IASA(HSD_GObj* gobj);

/**
 * @brief Interrupt check for aerial active Side-B loop (handles B button
 * release).
 * @param gobj Fighter game object
 */
/* 111740 */ void ftSk_SpecialAirS_IASA(HSD_GObj* gobj);

/**
 * @brief Physics update for grounded active Side-B loop.
 * @param gobj Fighter game object
 */
/* 111778 */ void ftSk_SpecialS_Phys(HSD_GObj* gobj);

/**
 * @brief Physics update for aerial active Side-B loop.
 * @param gobj Fighter game object
 */
/* 111798 */ void ftSk_SpecialAirS_Phys(HSD_GObj* gobj);

/**
 * @brief Collision update for grounded active Side-B loop (retracts on ledge
 * slip).
 * @param gobj Fighter game object
 */
/* 1117B8 */ void ftSk_SpecialS_Coll(HSD_GObj* gobj);

/**
 * @brief Collision update for aerial active Side-B loop (retracts on landing).
 * @param gobj Fighter game object
 */
/* 1117F4 */ void ftSk_SpecialAirS_Coll(HSD_GObj* gobj);

/**
 * @brief Enters grounded active Side-B loop (state 350) and checks environment
 * collision.
 * @param gobj Fighter game object
 */
/* 111830 */ void ftSk_SpecialS_80111830(HSD_GObj* gobj);

/**
 * @brief Enters aerial active Side-B loop (state 353).
 * @param gobj Fighter game object
 */
/* 111988 */ void ftSk_SpecialS_80111988(HSD_GObj* gobj);

/**
 * @brief Animation update for grounded Side-B chain retraction.
 * @param gobj Fighter game object
 */
/* 111A48 */ void ftSk_SpecialSEnd_Anim(HSD_GObj* gobj);

/**
 * @brief Animation update for aerial Side-B chain retraction.
 * @param gobj Fighter game object
 */
/* 111B1C */ void ftSk_SpecialAirSEnd_Anim(HSD_GObj* gobj);

/**
 * @brief Interrupt check for grounded Side-B chain retraction.
 * @param gobj Fighter game object
 */
/* 111BF0 */ void ftSk_SpecialSEnd_IASA(HSD_GObj* gobj);

/**
 * @brief Interrupt check for aerial Side-B chain retraction.
 * @param gobj Fighter game object
 */
/* 111BF4 */ void ftSk_SpecialAirSEnd_IASA(HSD_GObj* gobj);

/**
 * @brief Physics update for grounded Side-B chain retraction.
 * @param gobj Fighter game object
 */
/* 111BF8 */ void ftSk_SpecialSEnd_Phys(HSD_GObj* gobj);

/**
 * @brief Physics update for aerial Side-B chain retraction.
 * @param gobj Fighter game object
 */
/* 111C18 */ void ftSk_SpecialAirSEnd_Phys(HSD_GObj* gobj);

/**
 * @brief Collision update for grounded Side-B chain retraction.
 * @param gobj Fighter game object
 */
/* 111C38 */ void ftSk_SpecialSEnd_Coll(HSD_GObj* gobj);

/**
 * @brief Collision update for aerial Side-B chain retraction.
 * @param gobj Fighter game object
 */
/* 111C74 */ void ftSk_SpecialAirSEnd_Coll(HSD_GObj* gobj);

/**
 * @brief State transition: Grounded -> Aerial for Side-B chain retraction.
 * @param gobj Fighter game object
 */
/* 111CB0 */ void ftSk_SpecialS_80111CB0(HSD_GObj* gobj);

/**
 * @brief State transition: Aerial -> Grounded for Side-B chain retraction.
 * @param gobj Fighter game object
 */
/* 111D54 */ void ftSk_SpecialS_80111D54(HSD_GObj* gobj);

/**
 * @brief Enters grounded Side-B chain retraction (state 351).
 * @param gobj Fighter game object
 */
/* 111DF8 */ void ftSk_SpecialS_80111DF8(HSD_GObj* gobj);

/**
 * @brief Enters aerial Side-B chain retraction (state 354).
 * @param gobj Fighter game object
 */
/* 111EB4 */ void ftSk_SpecialS_80111EB4(HSD_GObj* gobj);

/**
 * @brief Checks if Sheik does not currently hold a needle item.
 * @param gobj Fighter game object
 * @return bool True if held needle item is NULL
 */
/* 111F70 */ bool ftSk_SpecialS_80111F70(HSD_GObj* gobj);

/**
 * @brief Returns the number of needles currently charged (0-6).
 * @param gobj Fighter game object
 * @return int Stored needle count
 */
/* 111FA0 */ int ftSk_SpecialS_80111FA0(HSD_GObj* gobj);

#endif
