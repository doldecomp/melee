/**
 * @file itgroundcoll.h
 * @brief Item environmental collision and bounce logic
 * @details Handles item ECB (Environment Collision Box) interaction with stages, ground line detection, and bounce physics.
 * Module prefix: it
 */
#ifndef GALE01_ITGROUNDCOLL_H
#define GALE01_ITGROUNDCOLL_H

#include <Runtime/platform.h>

#include <sysdolphin/baselib/forward.h>

#include <dolphin/mtx.h>
#include <melee/it/types.h>

/**
 * @brief Updates ECB and checks for ground collision. If found, updates position and floor line index.
 * @param gobj Item GObj
 * @return true if collided with ground
 */
/* 26D564 */ bool it_8026D564(Item_GObj*);
/**
 * @brief Updates ECB and checks for ground collision without updating item position.
 * @param gobj Item GObj
 * @return true if collided with ground
 */
/* 26D5CC */ bool it_8026D5CC(Item_GObj*);
/**
 * @brief Checks if the item's current floor line index is valid.
 * @param gobj Item GObj
 * @return true if floor line is valid
 */
/* 26D604 */ bool it_8026D604(Item_GObj*);
/**
 * @brief Checks ground collision. If the item loses ground contact, calls the fall callback (air state transition).
 * @param gobj Item GObj
 * @param callback Callback executed if item falls off the edge
 */
/* 26D62C */ void it_8026D62C(Item_GObj*, HSD_GObjEvent);
/**
 * @brief Similar to it_8026D62C but doesn't drop the item explicitly or reset ECB upon losing ground.
 * @param gobj Item GObj
 * @param callback Callback executed if item falls off the edge
 */
/* 26D6F4 */ void it_8026D6F4(Item_GObj*, HSD_GObjEvent);
/**
 * @brief Ground collision check. If lost, executes callback and clears related item ECB flags.
 * @param gobj Item GObj
 * @param callback Callback executed if item falls off the edge
 */
/* 26D78C */ void it_8026D78C(Item_GObj*, HSD_GObjEvent);
/**
 * @brief Checks ground collision and clears ECB flags if ground contact is lost, but without a callback.
 * @param gobj Item GObj
 */
/* 26D82C */ void it_8026D82C(Item_GObj*);
/**
 * @brief Checks ground collision using an alternative mpColl function.
 * @param gobj Item GObj
 * @param callback Callback executed if item falls off the edge
 * @return true if collided with ground
 */
/* 26D8A4 */ bool it_8026D8A4(Item_GObj*, HSD_GObjEvent);
/**
 * @brief Validates the floor line index. If invalid, sets to -1 and triggers the callback.
 * @param gobj Item GObj
 * @param callback Callback to execute if floor is invalid
 */
/* 26D938 */ void it_8026D938(Item_GObj*, HSD_GObjEvent);
/**
 * @brief Evaluates full ECB environmental collision (ground, walls, ceilings) and updates position.
 * @param gobj Item GObj
 * @return true if collision detected
 */
/* 26D9A0 */ bool it_8026D9A0(Item_GObj*);
/**
 * @brief Checks for collision against floor lines.
 * @param gobj Item GObj
 * @return true if collision detected
 */
/* 26DA08 */ bool it_8026DA08(Item_GObj*);
/**
 * @brief Checks for collision against floor lines without updating item position.
 * @param gobj Item GObj
 * @return true if collision detected
 */
/* 26DA70 */ bool it_8026DA70(Item_GObj*);
/**
 * @brief Checks for floor, wall, and ceiling collisions.
 * @param gobj Item GObj
 * @return Bitmask of collisions (0x1 = Floor, 0x4 = Wall, 0x8 = Ceiling)
 */
/* 26DAA8 */ s32 it_8026DAA8(Item_GObj*);
/**
 * @brief Checks for floor and wall collisions.
 * @param gobj Item GObj
 * @return Bitmask of collisions (0x1 = Floor, 0x4 = Wall)
 */
/* 26DB40 */ bool it_8026DB40(Item_GObj*);
/**
 * @brief Top-level check for item bounce/landing logic.
 * @param gobj Item GObj
 * @return true if item successfully landed
 */
/* 26DBC8 */ bool it_8026DBC8(Item_GObj*);
/**
 * @brief Handles bounce physics and impact threshold. Dampens velocity and transitions to landing if velocity is too low.
 * @param gobj Item GObj
 * @return true if the item should land rather than bounce
 */
/* 26DC24 */ bool it_8026DC24(Item_GObj*);
/**
 * @brief Finalizes landing logic, resets land count, and enters the item's ground action state.
 * @param gobj Item GObj
 * @return true on successful landing transition
 */
/* 26DD5C */ bool it_8026DD5C(Item_GObj*);
/**
 * @brief Increments bounce count and handles random item breakage on first impact.
 * @param gobj Item GObj
 * @return false if the item broke, true otherwise
 */
/* 26DDFC */ bool it_8026DDFC(Item_GObj*);
/**
 * @brief Increments bounce count and handles random item breakage on first impact (variant).
 * @param gobj Item GObj
 * @return false if the item broke, true otherwise
 */
/* 26DE98 */ bool it_8026DE98(Item_GObj*);
/**
 * @brief Performs floor collision check and returns boolean result.
 * @param gobj Item GObj
 * @return true if floor collided
 */
/* 26DF34 */ bool it_8026DF34(Item_GObj*);
/**
 * @brief Performs floor, wall, and ceiling collision check and returns boolean result.
 * @param gobj Item GObj
 * @return true if any collision occurred
 */
/* 26DFB0 */ bool it_8026DFB0(Item_GObj*);
/**
 * @brief Performs floor and wall collision check and returns boolean result.
 * @param gobj Item GObj
 * @return true if floor or wall collided
 */
/* 26E058 */ bool it_8026E058(Item_GObj*);
/**
 * @brief Updates position based on full environmental ECB collision.
 * @param gobj Item GObj
 */
/* 26E0F4 */ void it_8026E0F4(Item_GObj*);
/**
 * @brief Evaluates air-to-ground environmental collision, processes bounce velocity, and conditionally transitions to landing state.
 * @param gobj Item GObj
 * @param callback Callback executed upon landing
 */
/* 26E15C */ void it_8026E15C(Item_GObj*, HSD_GObjEvent);
/**
 * @brief Evaluates air-to-ground environmental collision and processes bounce/landing logic (variant).
 * @param gobj Item GObj
 * @param callback Callback executed upon landing
 */
/* 26E248 */ void it_8026E248(Item_GObj*, HSD_GObjEvent);
/**
 * @brief Evaluates air-to-ground environmental collision, returning the collision bitmask.
 * @param gobj Item GObj
 * @param callback Callback executed upon landing
 * @return Collision bitmask
 */
/* 26E32C */ s32 it_8026E32C(Item_GObj*, HSD_GObjEvent);
/**
 * @brief Evaluates air-to-ground collision, forcing an immediate landing upon ground contact (no bounce check).
 * @param gobj Item GObj
 * @param callback Callback executed upon landing
 */
/* 26E414 */ void it_8026E414(Item_GObj*, HSD_GObjEvent);
/**
 * @brief Evaluates air-to-ground collision, forcing landing and resetting item model scale upon ground contact.
 * @param gobj Item GObj
 * @param callback Callback executed upon landing
 */
/* 26E4D0 */ void it_8026E4D0(Item_GObj*, HSD_GObjEvent);
/**
 * @brief Evaluates full environmental collision and conditionally transitions to landing without bounce check.
 * @param gobj Item GObj
 * @param callback Callback executed upon collision
 */
/* 26E5A0 */ void it_8026E5A0(Item_GObj*, HSD_GObjEvent);
/**
 * @brief Evaluates floor and wall collision and conditionally transitions to landing without bounce check.
 * @param gobj Item GObj
 * @param callback Callback executed upon collision
 */
/* 26E664 */ void it_8026E664(Item_GObj*, HSD_GObjEvent);
/**
 * @brief Evaluates full environmental collision with alternate bounce physics callback upon hit.
 * @param gobj Item GObj
 * @param callback Callback executed upon collision
 */
/* 26E71C */ void it_8026E71C(Item_GObj*, HSD_GObjEvent);
/**
 * @brief Evaluates full environmental collision with alternate bounce physics and standard landing check.
 * @param gobj Item GObj
 * @param callback Callback executed upon landing
 */
/* 26E7E0 */ void it_8026E7E0(Item_GObj*, HSD_GObjEvent);
/**
 * @brief Ground to air collision logic with split callbacks for hitting an obstruction or falling off an edge.
 * @param gobj Item GObj
 * @param callback Executed on obstruction
 * @param fall_callback Executed if ground contact is lost
 */
/* 26E8C4 */ void it_8026E8C4(Item_GObj*, HSD_GObjEvent, HSD_GObjEvent);
/**
 * @brief Raycast environment collision check between start and hit positions.
 * @param gobj Item GObj
 * @param start_pos Raycast start vector
 * @param hit_pos Raycast end vector (updated on hit)
 * @param normal Returned surface normal
 * @return true if raycast hit
 */
/* 26E9A4 */ bool it_8026E9A4(HSD_GObj*, Vec3*, Vec3*, Vec3*);
/**
 * @brief Raycast environment collision check that also retrieves the hit line index and material flags.
 * @param gobj Item GObj
 * @param start_pos Raycast start vector
 * @param hit_pos Raycast end vector (updated on hit)
 * @param normal Returned surface normal
 * @param line_idx Pointer to store hit line index
 * @param flags_out Pointer to store material flags
 * @return true if raycast hit
 */
/* 26EA20 */ bool it_8026EA20(HSD_GObj*, Vec3*, Vec3*, Vec3*, int*,
                              u32* flags_out);
/**
 * @brief Raycast environment collision check filtered by specific material flags.
 * @param gobj Item GObj
 * @param start_pos Raycast start vector
 * @param hit_pos Raycast end vector (updated on hit)
 * @param normal Returned surface normal
 * @param line_idx Pointer to store hit line index
 * @param flags_out Pointer to store material flags
 * @param material_flags Material flags to filter against
 * @return true if raycast hit
 */
/* 26EA9C */ bool it_8026EA9C(HSD_GObj*, Vec3*, Vec3*, Vec3*, int*,
                              u32* flags_out, s32);

#endif
