#ifndef GALE01_08A698
#define GALE01_08A698

#include <melee/ft/forward.h>

#include <dat_macros.h>

/// One of a fighter's wait animations: @c x is its animation, picked with
/// odds of @c y in 100. Lists of them end in one whose @c x is -1.
typedef struct WaitStruct {
    union WaitStruct_u {
        /// The same words, as #ftCo_8008A7A8 reads the animation.
        struct WaitStruct_u_p {
            int* x;
            int* y;
        } p;
        struct WaitStruct_u_i {
            int x;
            int y;
        } i DAT_IF(true);
    } u;
} WaitStruct;

/* 08A698 */ bool ftCo_8008A698(Fighter* fp);
/* 08A6D8 */ void ftCo_8008A6D8(Fighter_GObj* gobj, s32 anim_id);
/* 08A7A8 */ void ftCo_8008A7A8(Fighter_GObj* gobj, WaitStruct* arg1);
/* 3C54A8 */ extern char ftWaitAnim_803C54A8[];
/* 3C54C4 */ extern char ftWaitAnim_803C54C4[];

#endif
