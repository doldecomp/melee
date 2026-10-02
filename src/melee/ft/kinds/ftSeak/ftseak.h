/**
 * @file ftseak.h
 * @brief Main header for Sheik (ftSeak) character module.
 * @details Declarations for Sheik character lifecycle callbacks (death, load,
 * item interaction, knockback), motion state tables, and DAT file references.
 * Module prefix: ftSk (Fighter: Sheik)
 */

#ifndef GALE01_110094
#define GALE01_110094

#include <Runtime/platform.h>

#include <melee/ft/kinds/ftSeak/forward.h>
#include <sysdolphin/baselib/forward.h>

#include <melee/ft/types.h>

/**
 * @brief Resets Sheik's character variables upon death.
 * @param gobj Fighter game object
 */
/* 110094 */ void ftSk_Init_OnDeath(HSD_GObj* gobj);

/**
 * @brief Initializes Sheik upon fighter load.
 * @details Enables wall jump, loads DAT attributes, and pre-registers Sheik's
 * items (NeedleThrow, NeedleHeld, Vanish explosion, Chain).
 * @param gobj Fighter game object
 */
/* 1100EC */ void ftSk_Init_OnLoad(HSD_GObj* gobj);

/**
 * @brief Cleans up active special move items (needles, chain) when
 * interrupted.
 * @param gobj Fighter game object
 */
/* 110198 */ void ftSk_Init_80110198(HSD_GObj* gobj);

/**
 * @brief Displays the full-charge visual effect if Sheik has 6 needles stored.
 * @param gobj Fighter game object
 */
/* 1101CC */ void ftSk_Init_UnkMotionStates4(HSD_GObj* gobj);

/**
 * @brief Handles item pickup for Sheik.
 * @param gobj Fighter game object
 * @param flag Item pickup flag
 */
/* 110204 */ void ftSk_Init_OnItemPickup(HSD_GObj* gobj, bool flag);

/**
 * @brief Handles item invisibility for Sheik.
 * @param gobj Fighter game object
 */
/* 1102E4 */ void ftSk_Init_OnItemInvisible(HSD_GObj* gobj);

/**
 * @brief Handles item visibility for Sheik.
 * @param gobj Fighter game object
 */
/* 11032C */ void ftSk_Init_OnItemVisible(HSD_GObj* gobj);

/**
 * @brief Handles item drop for Sheik.
 * @param gobj Fighter game object
 * @param flag Item drop flag
 */
/* 110374 */ void ftSk_Init_OnItemDrop(HSD_GObj* gobj, bool flag);

/**
 * @brief Copies character-specific special attributes from DAT file.
 * @param gobj Fighter game object
 */
/* 1103C8 */ void ftSk_Init_LoadSpecialAttrs(HSD_GObj* gobj);

/**
 * @brief Called when Sheik enters knockback / hitstun.
 * @param gobj Fighter game object
 */
/* 110408 */ void ftSk_Init_OnKnockbackEnter(HSD_GObj* gobj);

/**
 * @brief Called when Sheik exits knockback / hitstun.
 * @param gobj Fighter game object
 */
/* 11044C */ void ftSk_Init_OnKnockbackExit(HSD_GObj* gobj);

/// Motion state table for Sheik's special moves (action states 341-364)
/* 3CC060 */ extern MotionState ftSk_Init_MotionStateTable[ftSk_MS_SelfCount];

/// Main character DAT archive filename ("PlSk.dat")
/* 3CC360 */ extern char ftSk_Init_DatFilename[];

/// Character data symbol name ("ftDataSeak")
/* 3CC36C */ extern char ftSk_Init_DataName[];

/// Animation DAT archive filename ("PlSkAJ.dat")
/* 3CC4CC */ extern char ftSk_Init_AnimDatFilename[];

/// Demo motion animation filenames
/* 3CC548 */ extern Fighter_DemoStrings ftSk_Init_DemoMotionFilenames;

/// Costume strings array for Sheik
/* 3CC558 */ extern Fighter_CostumeStrings ftSk_Init_CostumeStrings[];

/// Costume list definition for Sheik (5 costume colors)
/* 459D18 */ extern UnkCostumeStruct ftSk_CostumeList[5];

#endif
