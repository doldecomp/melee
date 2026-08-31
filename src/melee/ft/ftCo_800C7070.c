#include "ftCo_800C7070.h"

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
