#include <platform.h>

#include "ft/forward.h"
#include "ftCommon/forward.h"

#include "ftCo_HammerJump.h"

#include "ftCo_HammerFall.h"
#include "ftCo_HammerKneeBend.h"
#include "ftCo_HammerWait.h"

#include "ft/fighter.h"
#include "ft/ftcommon.h"
#include "ftCommon/ftCo_Jump.h"

bool ftCo_800C5A50(Fighter_GObj* gobj)
{
    ftCo_JumpInput e = ftCo_Jump_GetInput(gobj);
    if (e != 0) {
        ftCo_800C5B88(gobj, e);
        return true;
    }
    return false;
}

void ftCo_800C5A98(Fighter_GObj* gobj)
{
    /// @todo Cannot move below @c fp, which suggests an inline
    u32 flags;
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    flags = ftCo_800C54C4(fp);
    Fighter_ChangeMotionState(gobj, ftCo_MS_HammerJump, flags,
                              ftCo_800C548C(fp), 1, 0, NULL);
    ftCo_800CB110(gobj, false, 1);
    ftCo_800C4E94(fp);
}

void ftCo_HammerJump_Anim(Fighter_GObj* gobj)
{
    ftCo_800C4F64(gobj);
}

void ftCo_HammerJump_IASA(Fighter_GObj* gobj) {}

void ftCo_HammerJump_Phys(Fighter_GObj* gobj)
{
    ftCo_Jump_Phys_Inner(gobj);
}

void ftCo_HammerJump_Coll(Fighter_GObj* gobj)
{
    ftCo_HammerFall_Coll(gobj);
}
