/**
 * @file ftseakspecialhi.h
 * @brief Header for Sheik's Up-B move: Vanish.
 * @details Declarations for grounded and aerial Up-B (Vanish) action states,
 * including startup (explosion attack), invisible teleport travel, and
 * reappearance / landing lag states.
 * Module prefix: ftSk (Fighter: Sheik)
 */

#ifndef GALE01_1130D0
#define GALE01_1130D0

#include <sysdolphin/baselib/forward.h>

/**
 * @brief Enters grounded Up-B (Vanish) startup.
 * @param gobj Fighter game object
 */
/* 1130D0 */ void ftSk_SpecialHi_Enter(HSD_GObj* gobj);

/**
 * @brief Enters aerial Up-B (Vanish) startup.
 * @param gobj Fighter game object
 */
/* 11312C */ void ftSk_SpecialAirHi_Enter(HSD_GObj* gobj);

/**
 * @brief Animation update for grounded Up-B startup (explosion).
 * @param gobj Fighter game object
 */
/* 113194 */ void ftSk_SpecialHiStart_0_Anim(HSD_GObj* gobj);

/**
 * @brief Animation update for aerial Up-B startup (explosion).
 * @param gobj Fighter game object
 */
/* 1131D0 */ void ftSk_SpecialAirHiStart_0_Anim(HSD_GObj* gobj);

/**
 * @brief Interrupt check for grounded Up-B startup.
 * @param gobj Fighter game object
 */
/* 11320C */ void ftSk_SpecialHiStart_0_IASA(HSD_GObj* gobj);

/**
 * @brief Interrupt check for aerial Up-B startup.
 * @param gobj Fighter game object
 */
/* 113210 */ void ftSk_SpecialAirHiStart_0_IASA(HSD_GObj* gobj);

/**
 * @brief Physics update for grounded Up-B startup.
 * @param gobj Fighter game object
 */
/* 113214 */ void ftSk_SpecialHiStart_0_Phys(HSD_GObj* gobj);

/**
 * @brief Physics update for aerial Up-B startup (gravity fall & drift).
 * @param gobj Fighter game object
 */
/* 113234 */ void ftSk_SpecialAirHiStart_0_Phys(HSD_GObj* gobj);

/**
 * @brief Collision update for grounded Up-B startup.
 * @param gobj Fighter game object
 */
/* 113278 */ void ftSk_SpecialHiStart_0_Coll(HSD_GObj* gobj);

/**
 * @brief Collision update for aerial Up-B startup (ground/ledge check).
 * @param gobj Fighter game object
 */
/* 1132B4 */ void ftSk_SpecialAirHiStart_0_Coll(HSD_GObj* gobj);

/**
 * @brief Animation update for grounded Up-B invisible travel phase.
 * @param gobj Fighter game object
 */
/* 1133FC */ void ftSk_SpecialHiStart_1_Anim(HSD_GObj* gobj);

/**
 * @brief Animation update for aerial Up-B invisible travel phase.
 * @param gobj Fighter game object
 */
/* 113438 */ void ftSk_SpecialAirHiStart_1_Anim(HSD_GObj* gobj);

/**
 * @brief Interrupt check for grounded Up-B invisible travel.
 * @param gobj Fighter game object
 */
/* 113474 */ void ftSk_SpecialHiStart_1_IASA(HSD_GObj* gobj);

/**
 * @brief Interrupt check for aerial Up-B invisible travel.
 * @param gobj Fighter game object
 */
/* 113478 */ void ftSk_SpecialAirHiStart_1_IASA(HSD_GObj* gobj);

/**
 * @brief Physics update for grounded Up-B invisible travel.
 * @param gobj Fighter game object
 */
/* 11347C */ void ftSk_SpecialHiStart_1_Phys(HSD_GObj* gobj);

/**
 * @brief Physics update for aerial Up-B invisible travel.
 * @param gobj Fighter game object
 */
/* 11349C */ void ftSk_SpecialAirHiStart_1_Phys(HSD_GObj* gobj);

/**
 * @brief Collision update for grounded Up-B invisible travel.
 * @param gobj Fighter game object
 */
/* 1134A0 */ void ftSk_SpecialHiStart_1_Coll(HSD_GObj* gobj);

/**
 * @brief Collision update for aerial Up-B invisible travel (teleport
 * collision).
 * @param gobj Fighter game object
 */
/* 113540 */ void ftSk_SpecialAirHiStart_1_Coll(HSD_GObj* gobj);

/**
 * @brief Animation update for grounded Up-B reappearance.
 * @param gobj Fighter game object
 */
/* 113C40 */ void ftSk_SpecialHi_Anim(HSD_GObj* gobj);

/**
 * @brief Animation update for aerial Up-B reappearance.
 * @param gobj Fighter game object
 */
/* 113C7C */ void ftSk_SpecialAirHi_Anim(HSD_GObj* gobj);

/**
 * @brief Interrupt check for grounded Up-B reappearance.
 * @param gobj Fighter game object
 */
/* 113CDC */ void ftSk_SpecialHi_IASA(HSD_GObj* gobj);

/**
 * @brief Interrupt check for aerial Up-B reappearance.
 * @param gobj Fighter game object
 */
/* 113CE0 */ void ftSk_SpecialAirHi_IASA(HSD_GObj* gobj);

/**
 * @brief Physics update for grounded Up-B reappearance.
 * @param gobj Fighter game object
 */
/* 113CE4 */ void ftSk_SpecialHi_Phys(HSD_GObj* gobj);

/**
 * @brief Physics update for aerial Up-B reappearance (deceleration/drift).
 * @param gobj Fighter game object
 */
/* 113D04 */ void ftSk_SpecialAirHi_Phys(HSD_GObj* gobj);

/**
 * @brief Collision update for grounded Up-B reappearance.
 * @param gobj Fighter game object
 */
/* 113D80 */ void ftSk_SpecialHi_Coll(HSD_GObj* gobj);

/**
 * @brief Collision update for aerial Up-B reappearance (landing/fall special).
 * @param gobj Fighter game object
 */
/* 113DBC */ void ftSk_SpecialAirHi_Coll(HSD_GObj* gobj);

#endif
