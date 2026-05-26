#include "ftCo_800C7070.h"

#include <placeholder.h>

#include "ft/fighter.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

/// @todo #ftCo_800C6150
void ftCo_800C7070(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftCo_MS_RebirthWait, 0, 0, 1, 0, NULL);
    fp->x2219_b2 = true;
    fp->x2219_b1 = true;
}

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
