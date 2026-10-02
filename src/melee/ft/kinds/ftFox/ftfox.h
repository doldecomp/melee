/**
 * @file ftfox.h
 * @brief Function declarations for Fox character initialization and lifecycle
 * @details Contains declarations for loading character data, handling item
 * callbacks, death, knockback, and motion state table for Fox (ftFx). Module
 * prefix: ftFx
 */

#ifndef GALE01_0E5534
#define GALE01_0E5534

#include <Runtime/platform.h>

#include <melee/ft/kinds/ftFox/forward.h>
#include <sysdolphin/baselib/forward.h>

#include <melee/ft/types.h>

/**
 * @brief Checks if Fox's Blaster gun item entity exists
 * @param gobj The fighter's game object
 * @return True if blaster GObj exists, false otherwise
 */
/* 0E5534 */ bool ftFx_Init_800E5534(HSD_GObj* gobj);

/**
 * @brief Resets Fox state on death/respawn
 * @param gobj The fighter's game object
 */
/* 0E5554 */ void ftFx_Init_OnDeath(HSD_GObj* gobj);

/**
 * @brief Removes Blaster item on interruption or damage
 * @param gobj The fighter's game object
 */
/* 0E5588 */ void ftFx_Init_800E5588(HSD_GObj* gobj);

/**
 * @brief Item pickup callback for Fox
 * @param gobj The fighter's game object
 * @param flag Item pickup flag
 */
/* 0E55A8 */ void ftFx_Init_OnItemPickup(HSD_GObj* gobj, bool flag);

/**
 * @brief Hides held items during certain moves
 * @param gobj The fighter's game object
 */
/* 0E5688 */ void ftFx_Init_OnItemInvisible(HSD_GObj* gobj);

/**
 * @brief Restores held item visibility
 * @param gobj The fighter's game object
 */
/* 0E56D0 */ void ftFx_Init_OnItemVisible(HSD_GObj* gobj);

/**
 * @brief Item drop callback for Fox
 * @param gobj The fighter's game object
 * @param flag Item drop flag
 */
/* 0E5718 */ void ftFx_Init_OnItemDrop(HSD_GObj* gobj, bool flag);

/**
 * @brief Loads Fox attribute struct for Falco
 * @param fp Pointer to the Fighter data structure
 */
/* 0E576C */ void ftFx_Init_OnLoadForFalco(Fighter* fp);

/**
 * @brief Main character load callback for Fox
 * @param gobj The fighter's game object
 * @details Configures walljump capability, character attributes, and registers
 * item models (Blaster shot, Blaster gun, Fox Illusion ghost entity).
 */
/* 0E57AC */ void ftFx_Init_OnLoad(HSD_GObj* gobj);

/**
 * @brief Reloads special attributes from character data
 * @param gobj The fighter's game object
 */
/* 0E5858 */ void ftFx_Init_LoadSpecialAttrs(HSD_GObj* gobj);

/**
 * @brief Callback when entering knockback; adjusts body part animations
 * @param gobj The fighter's game object
 */
/* 0E5898 */ void ftFx_Init_OnKnockbackEnter(HSD_GObj* gobj);

/**
 * @brief Callback when exiting knockback
 * @param gobj The fighter's game object
 */
/* 0E5904 */ void ftFx_Init_OnKnockbackExit(HSD_GObj* gobj);

/// Fox's motion state table for character-specific actions
/* 3C7788 */ extern MotionState ftFx_Init_MotionStateTable[ftFx_MS_SelfCount];

/// DAT archive file name for Fox ("PlFx.dat")
/* 3C7BE8 */ extern char ftFx_Init_DatFilename[];

/// Data root symbol name ("ftDataFox")
/* 3C7BF4 */ extern char ftFx_Init_DataName[];

/// Animation DAT file name for Fox ("PlFxAJ.dat")
/* 3C7D10 */ extern char ftFx_Init_AnimDatFilename[];

/// Demo motion file names
/* 3C7D8C */ extern Fighter_DemoStrings ftFx_Init_DemoMotionFilenames;

/// Costume strings array for Fox palettes
/* 3C7D9C */ extern Fighter_CostumeStrings ftFx_Init_CostumeStrings[];

/// Costume table for Fox
/* 459B28 */ extern UnkCostumeStruct ftFx_CostumeList[4];

#endif
