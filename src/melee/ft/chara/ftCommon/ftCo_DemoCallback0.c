#include "ftCo_DemoCallback0.h"

#include <platform.h>

#include "ft/fighter.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

/// @@todo #ftCo_800C7070
void ftCo_800C6150(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftCo_MS_Rebirth, Ft_MF_None, 0, 1, 0,
                              NULL);
    fp->x2219_b2 = true;
    fp->x2219_b1 = true;
}
