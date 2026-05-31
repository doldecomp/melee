#include "ftCo_800C7220.h"

#include "ft_0852.h"
#include "ftCo_800C7070.h"

#include <placeholder.h>

#include "ft/fighter.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

static inline void inlineB0(Fighter_GObj* gobj)
{
    ftCo_800C7070(gobj);
}

static inline void inlineB1(Fighter_GObj* gobj)
{
    inlineB0(gobj);
}

static inline void inlineB2(Fighter_GObj* gobj)
{
    inlineB1(gobj);
}

void ftCo_800C7220(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->kind != FTKIND_KIRBY) {
        inlineB2(gobj);
    } else {
        Fighter_ChangeMotionState(gobj, ftCo_MS_Wait, 0, 0, 1, 0, NULL);
        fp->x2219_b2 = true;
        fp->x2219_b1 = true;
    }
}

void ftCo_800C7294(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->kind != FTKIND_KIRBY) {
        inlineB2(gobj);
    } else {
        Fighter_ChangeMotionState(gobj, ftCo_MS_WalkSlow, 0, 0, 1, 0, NULL);
        fp->x2219_b2 = true;
        fp->x2219_b1 = true;
    }
}

void ftCo_800C7308(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->kind != FTKIND_KIRBY) {
        inlineB2(gobj);
    } else {
        Fighter_ChangeMotionState(gobj, ftCo_MS_WalkMiddle, 0, 0, 1, 0, NULL);
        fp->x2219_b2 = true;
        fp->x2219_b1 = true;
    }
}

void ftCo_800C737C(Fighter_GObj* gobj)
{
    ft_8008521C(gobj);
}
