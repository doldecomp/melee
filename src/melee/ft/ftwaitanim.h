/**
 * @file ftwaitanim.h
 * @brief Fighter idle wait animation logic
 * @details Handles the selection and looping of idle animations when
 * a fighter is standing still.
 * Module prefix: ftCo (Common)
 */
#ifndef GALE01_08A698
#define GALE01_08A698

#include <melee/ft/forward.h>

typedef struct WaitStruct {
    union WaitStruct_u {
        struct WaitStruct_u_p {
            int* x;
            int* y;
        } p;
        struct WaitStruct_u_i {
            int x;
            int y;
        } i;
    } u;
} WaitStruct;

/**
 * @brief Checks if the fighter is currently holding an item with a standard hold style
 * @param fp Fighter state
 * @return true if holding an item (and not hold kind 2), false otherwise
 */
/* 08A698 */ bool ftCo_8008A698(Fighter* fp);

/**
 * @brief Forcibly sets the fighter's idle animation to the specified ID
 * @param gobj Fighter GObj
 * @param anim_id The specific animation ID to play
 */
/* 08A6D8 */ void ftCo_8008A6D8(Fighter_GObj* gobj, s32 anim_id);

/**
 * @brief Updates the fighter's idle animation, randomly selecting a new one from the given list if the current one finished
 * @param gobj Fighter GObj
 * @param wait_data Pointer to the array of potential idle animations and their selection weights
 */
/* 08A7A8 */ void ftCo_8008A7A8(Fighter_GObj* gobj, WaitStruct* wait_data);

/* 3C54A8 */ extern char ftWaitAnim_803C54A8[];
/* 3C54C4 */ extern char ftWaitAnim_803C54C4[];

#endif
