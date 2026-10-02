#ifndef GALE01_11ED38
#define GALE01_11ED38

/**
 * @file ftpopo.h
 * @brief Main declarations for Ice Climbers (Popo) character module
 * @details Declares initialization, item event callbacks, death/damage
 * handlers, motion state table, and asset string tables for Popo. Module
 * prefix: ftPp
 */

#include <Runtime/platform.h>

#include <melee/ft/kinds/ftPopo/forward.h>
#include <sysdolphin/baselib/forward.h>

#include <melee/ft/types.h>

/**
 * @brief Callback when Popo picks up an item
 * @param gobj Fighter game object
 * @param flag Pickup parameter flag
 */
/* 11ED38 */ void ftPp_Init_OnItemPickup(HSD_GObj* gobj, bool flag);

/**
 * @brief Callback when Popo's held item should become invisible
 * @param gobj Fighter game object
 */
/* 11EE18 */ void ftPp_Init_OnItemInvisible(HSD_GObj* gobj);

/**
 * @brief Callback when Popo's held item should become visible
 * @param gobj Fighter game object
 */
/* 11EE60 */ void ftPp_Init_OnItemVisible(HSD_GObj* gobj);

/**
 * @brief Callback when Popo drops an item
 * @param gobj Fighter game object
 * @param flag Drop parameter flag
 */
/* 11EEA8 */ void ftPp_Init_OnItemDrop(HSD_GObj* gobj, bool flag);

/**
 * @brief Main initialization callback for Popo
 * @details Prepares fighter data, pushes attributes, and registers projectile
 * items (Ice Shot, Blizzard, and Belay GumStrings).
 * @param gobj Fighter game object
 */
/* 11EEFC */ void ftPp_Init_OnLoad(HSD_GObj* gobj);

/**
 * @brief Setup Popo attributes when loading partner Nana
 * @param fp Fighter instance data
 */
/* 11EF3C */ void ftPp_Init_OnLoadForNana(Fighter* fp);

/**
 * @brief Callback when Popo dies
 * @details Clears parts rotation, clears partner pointers, and resets
 * variables.
 * @param gobj Fighter game object
 */
/* 11EFE8 */ void ftPp_Init_OnDeath(HSD_GObj* gobj);

/**
 * @brief Special moves cleanup handler on damage or death
 * @details Cleans up Ice Shot ice block, Belay rope, and Blizzard visual
 * effects.
 * @param gobj Fighter game object
 */
/* 11F060 */ void ftPp_Init_8011F060(HSD_GObj* gobj);

/**
 * @brief Reload special move attributes from DAT file
 * @param gobj Fighter game object
 */
/* 11F0A4 */ void ftPp_Init_LoadSpecialAttrs(HSD_GObj* gobj);

/**
 * @brief Callback when Popo enters knockback state
 * @param gobj Fighter game object
 */
/* 11F0E4 */ void ftPp_Init_OnKnockbackEnter(HSD_GObj* gobj);

/**
 * @brief Callback when Popo exits knockback state
 * @param gobj Fighter game object
 */
/* 11F128 */ void ftPp_Init_OnKnockbackExit(HSD_GObj* gobj);

/**
 * @brief Clears Popo's Ice Shot item pointer if matching given item
 * @param gobj Fighter game object
 * @param item_gobj Item game object to verify
 */
/* 11F16C */ void ftPp_Init_8011F16C(HSD_GObj* gobj, Item_GObj* item_gobj);

/// Motion state table containing callbacks for each Popo special move
/* 3CD2D0 */ extern MotionState ftPp_Init_MotionStateTable[ftPp_MS_SelfCount];

/// Popo character archive file name ("PlPp.dat")
/* 3CD610 */ extern char ftPp_Init_DatFilename[];

/// Popo character data symbol name ("ftDataPopo")
/* 3CD61C */ extern char ftPp_Init_DataName[];

/// Popo animation archive file name ("PlPpAJ.dat")
/* 3CD738 */ extern char ftPp_Init_AnimDatFilename[];

/// Demo/result animation file name references for Popo
/* 3CD7B4 */ extern Fighter_DemoStrings ftPp_Init_DemoMotionFilenames;

/// Costume archive and joint symbol strings table
/* 3CD7C4 */ extern Fighter_CostumeStrings ftPp_Init_CostumeStrings[];

/// Costume list descriptors for Popo
/* 459E68 */ extern UnkCostumeStruct ftPp_CostumeList[4];

#endif
