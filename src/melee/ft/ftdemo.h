/**
 * @file ftdemo.h
 * @brief Fighter Demo / Replay logic
 * @details Handles the initialization and mechanics for fighters during
 * title screen demos and replays (playback of recorded inputs).
 * Module prefix: ftDemo
 */
#ifndef GALE01_0BE7E0
#define GALE01_0BE7E0

#include <melee/ft/forward.h>
#include <melee/pl/forward.h>

/**
 * @brief Creates a fighter specifically for demo/replay playback
 * @param alloc_info Initialization struct with demo parameters
 * @return GObj of the newly created demo fighter
 */
/* 0BE7E0 */ Fighter_GObj* ftDemo_CreateFighter(plAllocInfo2* alloc_info);

/**
 * @brief Initializes the HSD_ObjAlloc memory pools for demo fighters
 */
/* 0BEB28 */ void ftDemo_ObjAllocInit(void);

/**
 * @brief Sets animation archive data pointers for a demo fighter
 * @param pairs_idx Index into the character data table
 * @param archive The loaded archive containing the animations
 * @param arr_idx The specific animation subset index
 */
/* 0BEB60 */ void ftDemo_SetArchiveData(int pairs_idx, HSD_Archive* archive,
                                        int arr_idx);

/**
 * @brief Resolves the motion file symbol string for a character's demo action
 * @param cb_idx Character-specific callback index
 * @param cb_arg Argument passed to the character's filename callback
 * @return String name of the motion file/symbol
 */
/* 0BEC08 */ char* ftDemo_GetMotionFileString(int cb_idx, int cb_arg);

/**
 * @brief Forcibly sets the visual facing direction of a demo fighter
 * @param gobj Fighter GObj
 * @param facing_dir +1.0 for right, -1.0 for left
 */
/* 0BEC74 */ void ftDemo_SetFacingDirection(Fighter_GObj* gobj,
                                            float facing_dir);

/* 3C1364 */ extern MotionState* ftData_UnkMotionStates0[Ft_Kind_Max];

#endif
