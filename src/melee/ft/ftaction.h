/**
 * @file ftaction.h
 * @brief Fighter subaction command script interpreter declarations.
 * @details Declares subaction event handlers and the core script execution loop for
 * fighter action states. Subaction command scripts control frame-by-frame move execution,
 * including hitbox activation, IASA (interruptible) frames, sound triggers, and visual effects.
 * Module prefix: ft (Fighter)
 */

#ifndef GALE01_071028
#define GALE01_071028

#include <melee/ft/forward.h>

/**
 * @brief Subaction opcode 10: Spawns particle graphic effects (GFX).
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
/* 071028 */ void ftAction_80071028(Fighter_GObj* gobj, CommandInfo* cmd);

/**
 * @brief Subaction opcode 10 skip: Skips GFX spawn command payload (5 words).
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
/* 0711DC */ void ftAction_800711DC(Fighter_GObj* gobj, CommandInfo* cmd);

/**
 * @brief Subaction opcode 17: Plays fighter sound effect (SFX) or modifies audio behavior.
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
/* 071B50 */ void ftAction_80071B50(Fighter_GObj* gobj, CommandInfo* cmd);

/**
 * @brief Subaction opcode 17 skip: Skips audio command payload (3 words).
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
/* 071CA4 */ void ftAction_80071CA4(Fighter_GObj* gobj, CommandInfo* cmd);

/**
 * @brief Subaction opcode 57: Configures fighter body collision and shield parameters.
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
/* 0730B8 */ void ftAction_800730B8(Fighter_GObj* gobj, CommandInfo* cmd);

/**
 * @brief Subaction opcode 57 skip: Advances past body parameter command.
 * @param gobj Fighter game object pointer.
 * @param cmd Active subaction command interpreter state.
 */
/* 073108 */ void ftAction_80073108(Fighter_GObj* gobj, CommandInfo* cmd);

/**
 * @brief Main per-frame subaction command script execution interpreter tick.
 * @details Advances the command script timer by animation frame speed multiplier, executes
 * standard control flow commands (opcodes 0-9), and dispatches fighter action events (opcodes 10+)
 * via the normal execution table ftAction_803C06E8.
 * @param gobj Fighter game object pointer.
 */
/* 073240 */ void ftAction_80073240(Fighter_GObj* gobj);

/**
 * @brief Fast-forward subaction script catchup interpreter tick for mid-animation starts.
 * @details Executed when entering an action state with anim_start > 0. Executes persistent
 * state commands (hitbox creation, hurtbox state, flags) via ftAction_803C07AC while skipping
 * one-shot audio and visual effects.
 * @param gobj Fighter game object pointer.
 */
/* 073354 */ void ftAction_80073354(Fighter_GObj* gobj);

/**
 * @brief Fast-forward subaction command skip loop when Ft_MF_UpdateCmd is active.
 * @details Skips event payloads up to the current animation frame using bytecode length
 * table ftAction_803C0870 without executing callbacks.
 * @param gobj Fighter game object pointer.
 */
/* 07349C */ void ftAction_8007349C(Fighter_GObj* gobj);

#endif
