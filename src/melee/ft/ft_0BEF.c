#include "ft_0BEF.h"

#include "fighter.h"

#include <platform.h>

#include "ft/types.h"

#include "ftCommon/forward.h"

void ftCo_800BEFD4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftCo_MS_DeadUpFallIce, Ft_MF_None, 0, 1, 0,
                              NULL);
    fp->x2219_b2 = true;
    fp->x2219_b1 = true;
}
