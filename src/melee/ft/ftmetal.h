/**
 * @file ftmetal.h
 * @brief Fighter metal form effects and shader updates
 * @details Handles the transition, rendering flags, and shader setup when a fighter picks up a Metal Box.
 * Module prefix: ft
 */
#ifndef MELEE_FT_METAL_H
#define MELEE_FT_METAL_H

#include <melee/ft/forward.h>

/**
 * @brief Reverts a fighter's metal effect, resetting the JObj and DObj flags to their original rendering modes.
 * @param fp The fighter
 */
/* 0C8170 */ void ft_800C8170(Fighter* fp);

/**
 * @brief Turns a fighter metal for a specific duration with given health (stamina).
 * @param fighter_gobj The fighter's GObj
 * @param timer How many frames the metal effect lasts
 * @param health Additional stamina/health properties for the metal state
 */
/* 0C8348 */ void ftCo_800C8348(Fighter_GObj* fighter_gobj, int timer, int health);

/**
 * @brief Applies or reapplies the metal state based on the fighter's is_always_metal flag.
 * @param gobj The fighter's GObj
 */
/* 0C8438 */ void ftCo_800C8438(Fighter_GObj* gobj);

/**
 * @brief Clears metal timers and health, removes the metal state, and reverts rendering.
 * @param gobj The fighter's GObj
 */
/* 0C8540 */ void ftCo_800C8540(Fighter_GObj* gobj);

/**
 * @brief Initializes the secondary DObjs / model parts needed for the metal state.
 * @param gobj The fighter's GObj
 */
/* 0C85B8 */ void ft_800C85B8(Fighter_GObj* gobj);

#endif
