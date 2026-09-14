#include "ftCo_CliffEscape.h"

#include <Runtime/platform.h>

#include "ftCo_CliffClimb.h"
#include "inlines.h"
#include <melee/ft/fighter.h>
#include <melee/ft/ftcliffcommon.h>
#include <melee/ft/types.h>

/// @todo Shared code with #ftCo_8009AEA4.
void ftCo_8009B040(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    FtMotionId msid = fp->dmg.x1830_percent < p_ftCommonData->x488
                          ? ftCo_MS_CliffEscapeQuick
                          : ftCo_MS_CliffEscapeSlow;
    ftCo_Cliff_EnterState(gobj, fp, msid);
    fp->x221D_b5 = true;
    ftCo_CliffCatch_Phys(gobj);
}

void ftCo_CliffEscape_Anim(Fighter_GObj* gobj)
{
    ftCo_CliffClimb_Anim(gobj);
}

void ftCo_CliffEscape_IASA(Fighter_GObj* gobj) {}

void ftCo_CliffEscape_Phys(Fighter_GObj* gobj)
{
    ftCo_CliffClimb_Phys(gobj);
}

void ftCo_CliffEscape_Coll(Fighter_GObj* gobj)
{
    ftCo_CliffClimb_Coll(gobj);
}
