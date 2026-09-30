/**
 * @file item.h
 * @brief Core Item Lifecycle and Management
 * @details Implements the core item pipeline including initialization, updating, 
 * state transitions, physics, collision detection, and memory allocation for all 
 * items in the game.
 * Module prefix: it (Item)
 */
#ifndef GALE01_266F3C
#define GALE01_266F3C
#include <Runtime/platform.h>

#include <melee/it/forward.h>
#include <sysdolphin/baselib/forward.h>

#include <dolphin/mtx.h>
#include <melee/ft/types.h>
#include <sysdolphin/baselib/objalloc.h>

struct ItemStateDesc;

/** @brief Checks if items are enabled globally in the game mode */
/* 266F3C */ bool Item_80266F3C(void);

/** @brief Checks and loads item common data (ItCo.dat / .usd) */
/* 266F70 */ void Item_80266F70(void);

/** @brief Initializes item common data using a default state */
/* 266FA8 */ void Item_80266FA8(void);

/** @brief Initializes memory allocators for Item, DynamicBoneTable, and ItemLink structs */
/* 266FCC */ void Item_80266FCC(void);

/** @brief Removes the associated camera box for an item, stopping it from affecting camera bounds */
/* 267454 */ void Item_80267454(HSD_GObj* gobj);

/** @brief Retrieves and assigns logical pointers (e.g. state tables, item attributes) based on item ID */
/* 267978 */ void Item_80267978(HSD_GObj* gobj);

/** @brief Sets up the item's 3D model (HSD_JObj) tree in the scene graph */
/* 2680CC */ void Item_802680CC(HSD_GObj* gobj);

/** @brief Updates the item's model scale based on its internal properties */
/* 26849C */ void Item_8026849C(HSD_GObj* gobj);

/** @brief Primary spawning routine for airborne items. Allocates GObj, sets initial state, model, physics */
/* 268B18 */ Item_GObj* Item_80268B18(SpawnItem* spawnItem);

/** @brief Primary spawning routine for grounded items. Assigns ground collision state upon spawn */
/* 268B5C */ Item_GObj* Item_80268B5C(SpawnItem* spawnItem);

/** @brief Spawns a grounded item and toggles unknown specific logic flags */
/* 268B9C */ void Item_80268B9C(SpawnItem* spawnItem);

/** @brief Sets up item animation logic (AObj) based on the specified state descriptor */
/* 268D34 */ void Item_80268D34(HSD_GObj* gobj, struct ItemStateDesc* itemStateDesc);

/** @brief Steps the item's animation frames forward */
/* 268DD4 */ void Item_80268DD4(HSD_GObj* gobj, float rate);

/** @brief Copies script data associated with an item's new action state */
/* 268E40 */ void Item_80268E40(Item* item_data, struct ItemStateDesc* itemStateDesc);

/** @brief Executes a state transition for an item, changing behavior/animation per the specified msid */
/* 268E5C */ void Item_80268E5C(HSD_GObj* item_gobj, enum_t msid, Item_StateChangeFlags flags);

/** @brief Refreshes an item's model transformations */
/* 2693E4 */ void Item_802693E4(HSD_GObj* gobj);

/** @brief Advances item animation and associated scripts */
/* 2694CC */ void Item_802694CC(HSD_GObj* gobj);

/** @brief Central think routine for executing item physics calculations */
/* 2697D4 */ void Item_802697D4(HSD_GObj* gobj);

/** @brief Central think routine for executing item collision checks */
/* 269978 */ void Item_80269978(HSD_GObj* gobj);

/** @brief Sets damage taken properties for the item when hit */
/* 269CA0 */ void Item_80269CA0(Item* item_data, s32 damage);

/** @brief Unlinks and removes the item from the player holding it */
/* 26A848 */ void Item_8026A848(HSD_GObj* gobj, HSD_GObj* fgobj);

/** @brief Destroys an item, freeing its GObj and memory */
/* 26A8EC */ void Item_8026A8EC(Item_GObj* gobj);

/** @brief Attaches an item to an owner (player) on a specified bone part */
/* 26AB54 */ void Item_8026AB54(HSD_GObj* gobj, HSD_GObj* owner_gobj, Fighter_Part part);

/** @brief Detaches a held item and assigns it a dropped physical state at a specified position */
/* 26ABD8 */ void Item_8026ABD8(Item_GObj* gobj, Vec3* pos, float drop_speed);

/** @brief Alternative item drop function that takes two position vectors */
/* 26AC74 */ void Item_8026AC74(HSD_GObj* gobj, Vec3* pos1, Vec3* pos2, float rate);

/** @brief Handles logic for when a player throws an item (speed, angle, spin) */
/* 26AD20 */ void Item_8026AD20(HSD_GObj* gobj, Vec3* pos, Vec3* vel, float rate, bool is_smash);

/** @brief Transitions a grounded item into an airborne physical state */
/* 26ADC0 */ void Item_8026ADC0(HSD_GObj* gobj);

/** @brief Free routine for item user data */
/* 26AE10 */ void Item_OnUserDataRemove(void* user_data);

/** @brief Free routine alias */
/* 26AE10 */ void lbl_8026AE10(void* user_data);

/** @brief Returns an unknown item global ID */
/* 26AE60 */ u32 Item_8026AE60(void);

/** @brief Plays an audio sound effect tied to this item */
/* 26AE84 */ void Item_8026AE84(Item* item_data, enum_t sfx, u8 pan, u8 volume);

/** @brief Plays an audio sound effect (variant 2) */
/* 26AF0C */ void Item_8026AF0C(Item* item_data, enum_t sfx, u8 pan, u8 volume);

/** @brief Plays an audio sound effect (variant 3) */
/* 26AFA0 */ void Item_8026AFA0(Item* item_data, enum_t sfx, u8 pan, u8 volume);

/** @brief Stops a currently playing item sound effect */
/* 26B034 */ void Item_8026B034(Item* item_data);

/** @brief Stops a currently playing item sound effect (variant 2) */
/* 26B074 */ void Item_8026B074(Item* item_data);

/** @brief Evaluates whether this item can currently be grabbed by a player */
/* 26B1A4 */ bool Item_IsGrabbable(Item_GObj* gobj);

/* 4A0C38 */ extern HSD_ObjAllocData item_link_alloc_data;
/* 4A0C64 */ extern HSD_ObjAllocUnk Item_804A0C64;
/* 4A0CCC */ extern Item_FtTrack Item_804A0CCC;
/* 4A0E24 */ extern PokemonSelectionState Item_804A0E24;

#endif
