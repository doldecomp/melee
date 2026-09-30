/**
 * @file ftcamera.h
 * @brief Handles fighter camera tracking and bounding boxes
 * @details Manages how the camera calculates its bounding box around fighters, tracking player positions, zooming, and panning based on player distance.
 * Module prefix: ft (Fighter)
 */

#ifndef GALE01_076018
#define GALE01_076018

#include <melee/ft/forward.h>
#include <sysdolphin/baselib/forward.h>

/**
 * @brief Scales camera box float arrays by a multiplier
 * @param in Input camera float array
 * @param out Output camera float array
 * @param mul Multiplier to scale by
 */
/* 076018 */ void ftCamera_80076018(UnkFloat6_Camera* in,
                                    UnkFloat6_Camera* out, float mul);

/**
 * @brief Initializes and copies the player position to the camera subject box
 * @param fp Fighter instance data
 */
/* 076064 */ void ftCamera_80076064(Fighter* fp);

/**
 * @brief Updates the camera subject bounding box based on player position and facing direction
 * @param gobj Fighter GObj
 */
/* 0761C8 */ void ftCamera_UpdateCameraBox(HSD_GObj* gobj);

/**
 * @brief Updates the camera bone position for the given fighter
 * @param gobj Fighter GObj
 */
/* 0762F4 */ void ftCamera_800762F4(HSD_GObj* gobj);

/**
 * @brief Updates the camera subject when a fighter hits the upper blast zone (Star KO/Screen KO)
 * @param gobj Fighter GObj
 */
/* 076320 */ void ftCamera_80076320(HSD_GObj* gobj);

#endif
