/**
 * @file ftsamus.h
 * @brief Samus Initialization and General Callbacks
 * @details Core initialization, item event callbacks, attribute scaling,
 * throw grapple beam setup, and bomb jump helper declarations for Samus.
 * Module prefix: ftSs
 */

#ifndef GALE01_12832C
#define GALE01_12832C

#include <Runtime/platform.h>

#include <melee/ft/kinds/ftSamus/forward.h>
#include <sysdolphin/baselib/forward.h>

#include <melee/ft/types.h>

/**
 * @brief Handles cleanup and variable reset when Samus is KO'd / dies.
 * @param gobj Samus fighter game object pointer
 */
/* 12832C */ void ftSs_Init_OnDeath(HSD_GObj* gobj);

/**
 * @brief Initializes Samus-specific attributes and registers character items
 * (Bomb, Charge Shot, Missile, Grapple).
 * @param gobj Samus fighter game object pointer
 */
/* 12837C */ void ftSs_Init_OnLoad(HSD_GObj* gobj);

/**
 * @brief Damage/state cleanup callback to cancel active Charge Shot and
 * missile effects.
 * @param gobj Samus fighter game object pointer
 */
/* 128428 */ void ftSs_Init_80128428(HSD_GObj* gobj);

/**
 * @brief Item pickup event callback for Samus.
 * @param gobj Samus fighter game object pointer
 * @param flag Item pickup flag
 */
/* 128464 */ void ftSs_Init_OnItemPickup(HSD_GObj* gobj, bool flag);

/**
 * @brief Item invisibility event callback for Samus.
 * @param gobj Samus fighter game object pointer
 */
/* 128544 */ void ftSs_Init_OnItemInvisible(HSD_GObj* gobj);

/**
 * @brief Item visibility event callback for Samus.
 * @param gobj Samus fighter game object pointer
 */
/* 12858C */ void ftSs_Init_OnItemVisible(HSD_GObj* gobj);

/**
 * @brief Item drop event callback for Samus.
 * @param gobj Samus fighter game object pointer
 * @param bool1 Drop condition / flag
 */
/* 1285D4 */ void ftSs_Init_OnItemDrop(HSD_GObj* gobj, bool bool1);

/**
 * @brief Checks if Samus's Neutral-B (Charge Shot) is fully charged and
 * triggers full-charge SFX/visuals.
 * @param gobj Samus fighter game object pointer
 */
/* 128628 */ void ftSs_Init_UnkMotionStates4(HSD_GObj* gobj);

/**
 * @brief Copies and scales special attributes (hitboxes, velocity, offsets)
 * based on model scale.
 * @param gobj Samus fighter game object pointer
 */
/* 128684 */ void ftSs_Init_LoadSpecialAttrs(HSD_GObj* gobj);

/**
 * @brief Sets animation playback rate on Grapple Beam animation object if
 * non-looping.
 * @param aobj Grapple beam animation object pointer
 * @param rate Animation playback rate
 */
/* 128770 */ void ftSs_Init_80128770(HSD_AObj* aobj, float rate);

/**
 * @brief Spawns and attaches Grapple Beam accessory to Samus's throw joint for
 * throw animations.
 * @param gobj Samus fighter game object pointer
 * @param motion_state Current throw motion state ID
 * @param anim_speed Animation playback speed
 */
/* 1287C4 */ void ftSs_Init_CreateThrowGrappleBeam(HSD_GObj* gobj,
                                                   s32 motion_state,
                                                   float anim_speed);

/**
 * @brief Down-B (Bomb): Checks if a bomb explosion hit Samus and applies bomb
 * jump knockback.
 * @param gobj Samus fighter game object pointer
 * @param bomb_pos_x World X position of exploding bomb
 * @param bomb_radius Explosion radius / divisor
 */
/* 128944 */ void ftSs_Init_80128944(HSD_GObj* gobj, float bomb_pos_x,
                                     float bomb_radius);

/**
 * @brief Checks collision between an attack capsule and Samus's hurtboxes.
 * @param gobj Samus fighter game object pointer
 * @param attack_capsule Attack capsule data pointer
 * @param hit_radius Hitbox radius offset
 * @return True if collision detected, false otherwise
 */
/* 128A1C */ bool ftSs_Init_80128A1C(HSD_GObj* gobj, UNK_T attack_capsule,
                                     float hit_radius);

/**
 * @brief Down-B (Bomb): Calculates bomb jump trajectory angle based on
 * horizontal offset from bomb.
 * @param gobj Samus fighter game object pointer
 * @param bomb_pos_x World X position of exploding bomb
 * @param bomb_radius Explosion radius / divisor
 * @return Launch angle in radians
 */
/* 128AC8 */ float ftSs_Init_80128AC8(HSD_GObj* gobj, float bomb_pos_x,
                                      float bomb_radius);

/**
 * @brief Down-B (Bomb): Transitions Samus into bomb jump state with given
 * velocity angle.
 * @param gobj Samus fighter game object pointer
 * @param angle Launch angle in radians
 * @param start_frame Starting animation frame
 * @param frame_speed Animation playback speed multiplier
 */
/* 128B1C */ void ftSs_Init_80128B1C(HSD_GObj* gobj, float angle,
                                     float start_frame, float frame_speed);

/* 3CE2D0 */ extern MotionState ftSs_Init_MotionStateTable[ftSs_MS_SelfCount];
/* 3CE510 */ extern char ftSs_Init_DatFilename[];
/* 3CE51C */ extern char ftSs_Init_DataName[];
/* 3CE5EC */ extern char ftSs_Init_AnimDatFilename[];
/* 3CE668 */ extern Fighter_DemoStrings ftSs_Init_DemoMotionFilenames;
/* 3CE678 */ extern Fighter_CostumeStrings ftSs_Init_CostumeStrings[];
/* 459F88 */ extern UnkCostumeStruct ftSs_CostumeList[5];

#endif
