/**
 * @file ftcaptain.h
 * @brief Main header for Captain Falcon's core initialization and lifecycle
 * functions
 * @details Declares fighter lifecycle callbacks (load, death, item
 * interaction) and costume/motion state tables for Captain Falcon and
 * Ganondorf. Module prefix: ftCa
 */

#ifndef GALE01_0E2888
#define GALE01_0E2888

#include <Runtime/platform.h>

#include <melee/ft/kinds/ftCaptain/forward.h>
#include <sysdolphin/baselib/forward.h>

#include <melee/ft/types.h>

/**
 * @brief Resets character-specific state flags upon Captain Falcon's death.
 * @param gobj Pointer to Captain Falcon's Fighter GObj
 */
/* 0E2888 */ void ftCa_Init_OnDeath(HSD_GObj* gobj);

/**
 * @brief Callback invoked on taking damage or death to remove Raptor Boost
 * visual effects.
 * @param gobj Pointer to Captain Falcon's Fighter GObj
 */
/* 0E28C8 */ void ftCa_Init_800E28C8(HSD_GObj* gobj);

/**
 * @brief Handles item pickup for Captain Falcon.
 * @param gobj Pointer to Captain Falcon's Fighter GObj
 * @param bool1 Flag passed to standard item pickup handler
 */
/* 0E28E8 */ void ftCa_Init_OnItemPickup(HSD_GObj* gobj, bool bool1);

/**
 * @brief Hides held item when Captain Falcon enters an invisible state.
 * @param gobj Pointer to Captain Falcon's Fighter GObj
 */
/* 0E29C8 */ void ftCa_Init_OnItemInvisible(HSD_GObj* gobj);

/**
 * @brief Shows held item when Captain Falcon returns to visible state.
 * @param gobj Pointer to Captain Falcon's Fighter GObj
 */
/* 0E2A10 */ void ftCa_Init_OnItemVisible(HSD_GObj* gobj);

/**
 * @brief Handles item drop/release for Captain Falcon.
 * @param gobj Pointer to Captain Falcon's Fighter GObj
 * @param bool1 Flag passed to standard item drop handler
 */
/* 0E2A58 */ void ftCa_Init_OnItemDrop(HSD_GObj* gobj, bool bool1);

/**
 * @brief Initializes character attributes for Ganondorf using Captain Falcon's
 * attribute structure.
 * @param fp Pointer to Ganondorf's Fighter data
 */
/* 0E2AAC */ void ftCa_Init_OnLoadForGanon(Fighter* fp);

/**
 * @brief Character initialization callback executed when Captain Falcon is
 * spawned.
 * @param gobj Pointer to Captain Falcon's Fighter GObj
 */
/* 0E2AEC */ void ftCa_Init_OnLoad(HSD_GObj* gobj);

/**
 * @brief Reloads Captain Falcon's special move attributes from the DAT file
 * archive.
 * @param gobj Pointer to Captain Falcon's Fighter GObj
 */
/* 0E2B40 */ void ftCa_Init_LoadSpecialAttrs(HSD_GObj* gobj);

/// Motion state table mapping motion state IDs to submotions, flags, and
/// callback pointers.
/* 3C72B8 */ extern MotionState ftCa_Init_MotionStateTable[ftCa_MS_SelfCount];

/// Filename of Captain Falcon's main data archive on disc ("PlCa.dat").
/* 3C7598 */ extern char ftCa_Init_DatFilename[];

/// Root symbol name in the DAT archive ("ftDataCaptain").
/* 3C75A4 */ extern char ftCa_Init_DataName[];

/// Filename of Captain Falcon's animation data archive ("PlCaAJ.dat").
/* 3C76A0 */ extern char ftCa_Init_AnimDatFilename[];

/// Demo motion file string identifiers for results, intro, ending, and idle
/// screens.
/* 3C772C */ extern Fighter_DemoStrings ftCa_Init_DemoMotionFilenames;

/// Array of costume filenames and joint models for Captain Falcon's color
/// palettes.
/* 3C773C */ extern Fighter_CostumeStrings ftCa_Init_CostumeStrings[];

/// Costume metadata list for Captain Falcon's 6 costume slots.
/* 459A98 */ extern UnkCostumeStruct ftCa_CostumeList[6];

#endif
