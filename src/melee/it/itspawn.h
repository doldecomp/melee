/**
 * @file itspawn.h
 * @brief Item spawning system
 * @details Handles spawning item entities into the world, resolving spawn probabilities, stage drops, and container interactions.
 * Module prefix: it (Item)
 */

#ifndef GALE01_ITSPAWN_H
#define GALE01_ITSPAWN_H

#include <Runtime/platform.h>

#include <dolphin/mtx.h>
#include <melee/it/types.h>

/**
 * @brief Constructs a bitfield of active item spawn kinds, used by snapshot functions.
 * @param arg_struct Pointer to the bitfield argument struct
 */
/* 26C47C */ void it_8026C47C(struct it_8026C47C_arg0_t* arg_struct);

/**
 * @brief Randomly selects an item kind from an ItemPickTable based on weighted values.
 * @param table Pointer to the ItemPickTable
 * @return The chosen ItemKind
 */
/* 26C65C */ ItemKind it_8026C65C(ItemPickTable* table);

/**
 * @brief Evaluates if the global item spawn limit or Master Ball restriction is met.
 * @return true if restricted (cannot spawn), false otherwise
 */
/* 26C704 */ bool it_8026C704(void);

/**
 * @brief Selects an item kind to spawn from a table, substituting Master Balls if restricted.
 * @param table Pointer to the ItemPickTable
 * @return The chosen ItemKind
 */
/* 26C75C */ ItemKind it_8026C75C(ItemPickTable* table);

/**
 * @brief Process callback that handles continuous random item spawning during a match.
 * @param gobj The Random Item Spawner GObj
 */
/* 26C88C */ void fn_8026C88C(HSD_GObj* gobj);

/**
 * @brief Sums up total item spawn weights from stage info for a specific item pool.
 * @param alloc Pointer to the ItemPickTable to store the sum
 * @param stage_info Pointer to stage item frequency array
 * @param mask Bitmask of allowed items
 * @param start_idx Index to start summing from
 * @param weight Base weight multiplier
 */
/* 26CA4C */ void it_8026CA4C(ItemPickTable* alloc, s32* stage_info, u64 mask, s32 start_idx, f32 weight);

/**
 * @brief Verifies if a given spawn position is valid (within stage bounds and not colliding).
 * @param vec Pointer to the 3D spawn position vector
 * @return true if the position is valid, false otherwise
 */
/* 26CB3C */ bool it_8026CB3C(Vec3* vec);

/**
 * @brief Builds the common item spawn probability table for random stage drops.
 * @param stage_info Pointer to the stage item counts/frequencies
 * @param allowed_mask Bitmask of allowed items
 * @param weight Base weight multiplier
 */
/* 26CB9C */ void it_8026CB9C(s32* stage_info, u64 allowed_mask, f32 weight);

/**
 * @brief Builds the container item spawn probability table (e.g. for capsules/crates).
 * @param stage_info Pointer to the stage item counts/frequencies
 * @param allowed_mask Bitmask of allowed items
 * @param weight Base weight multiplier
 */
/* 26CD50 */ void it_8026CD50(s32* stage_info, u64 allowed_mask, f32 weight);

/**
 * @brief Builds the monster (Poké Ball Pokémon) spawn probability table.
 */
/* 26CF04 */ void it_8026CF04(void);

/**
 * @brief Initializes the stage's random item spawner and its associated tables.
 */
/* 26D018 */ void it_8026D018(void);

/**
 * @brief Directly spawns an item of a specified kind at a given position.
 * @param pos Pointer to the 3D position vector
 * @param kind The ItemKind to spawn
 * @return true if spawned successfully, false if limits were exceeded
 */
/* 26D258 */ bool it_8026D258(Vec3* pos, ItemKind kind);

/**
 * @brief Checks if a specific item kind is allowed to spawn on the current stage/settings.
 * @param kind The ItemKind to check
 * @return true if allowed, false otherwise
 */
/* 26D324 */ bool it_8026D324(ItemKind kind);

/**
 * @brief Checks if any healing item (Heart Container, Maxim Tomato, Food) is allowed to spawn.
 * @return true if at least one healing item is allowed, false otherwise
 */
/* 26D3CC */ bool it_8026D3CC(void);

#endif
