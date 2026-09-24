#include <melee/ft/ftCo_800C739C.h>

#include <melee/ft/fighter.h>
#include <melee/ft/ftCo_800C7070.h>
#include <melee/ft/ftdata.h>
#include "kinds/ftCommon/forward.h"
#include <melee/ft/types.h>

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

void ftCo_800C739C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_MotionState ms;
    if (fp->kind == Ft_Kind_Kirby) {
        ms = ftCo_MS_WalkFast;
    } else {
        inlineB2(gobj);
        return;
    }
    Fighter_ChangeMotionState(gobj, ms, Ft_MF_None, 0.0F, 1.0F, 0.0F, NULL);
    fp->x2219_b2 = true;
    fp->x2219_b1 = true;
}

void ftCo_800C7414(Fighter_GObj* gobj)
{
    ft_8008521C(gobj);
}
