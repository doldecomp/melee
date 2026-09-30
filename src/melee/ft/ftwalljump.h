/**
 * @file ftwalljump.h
 * @brief Handles wall jump physics and collision checks
 * @details Evaluates controller inputs and collision environments to trigger wall jumps, accommodating for moving walls/platforms.
 * Module prefix: ft (Fighter)
 */

#ifndef GALE01_08169C
#define GALE01_08169C

#include <sysdolphin/baselib/forward.h>

/**
 * @brief Checks and executes a wall jump if conditions are met
 * @param gobj Fighter GObj
 * @return True if a wall jump was started, false otherwise
 */
/* 08169C */ bool ftWallJump_8008169C(HSD_GObj* gobj);

#endif
