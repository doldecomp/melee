#include "ftCo_800C7178.h"

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

void ftCo_800C7178(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_MotionState ms;
    if (fp->kind == FTKIND_MARIO) {
        ms = ftCo_MS_WalkSlow;
    } else if (fp->kind == FTKIND_LUIGI) {
        ms = ftCo_MS_WalkSlow;
    } else {
        inlineB2(gobj);
        return;
    }
    Fighter_ChangeMotionState(gobj, ms, 0, 0.0F, 1.0F, 0.0F, NULL);
    fp->x2219_b2 = true;
    fp->x2219_b1 = true;
}

void ftCo_800C7200(Fighter_GObj* gobj)
{
    ft_8008521C(gobj);
}
