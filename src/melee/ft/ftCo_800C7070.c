#include "ftCo_800C7070.h"

#include "fighter.h"
#include "kinds/ftCommon/forward.h"
#include "types.h"

void ftCo_800C7070(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftCo_MS_RebirthWait, 0, 0, 1, 0, NULL);
    fp->x2219_b2 = true;
    fp->x2219_b1 = true;
}
