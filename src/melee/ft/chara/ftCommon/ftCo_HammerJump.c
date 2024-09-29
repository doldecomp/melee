#include <platform.h>

#include "ft/forward.h"

#include "ftCo_HammerJump.h"

#include "ftCo_HammerFall.h"
#include "ftCo_HammerKneeBend.h"
#include "ftCo_HammerWait.h"

#include "ft/fighter.h"
#include "ft/ft_0C88.h"
#include "ft/ftcommon.h"

bool ftCo_800C5A50(ftCo_GObj* gobj)
{
    enum_t e = ftCo_800CAE80(gobj);
    if (e != 0) {
        ftCo_800C5B88(gobj, e);
        return true;
    }
    return false;
}

void ftCo_800C5A98(ftCo_GObj* gobj)
{
    /// @todo Cannot move below @c fp, which suggests an inline
    u32 flags;
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    flags = ftCo_800C54C4(fp);
    Fighter_ChangeMotionState(gobj, ftCo_MS_HammerJump, flags,
                              ftCo_800C548C(fp), 1, 0, NULL);
    ftCo_800CB110(gobj, 0, 1);
    ftCo_800C4E94(fp);
}

void ftCo_HammerJump_Anim(ftCo_GObj* gobj)
{
    ftCo_800C4F64(gobj);
}

void ftCo_HammerJump_IASA(ftCo_GObj* gobj) {}

void ftCo_HammerJump_Phys(ftCo_GObj* gobj)
{
    ftCo_800CB438(gobj);
}

void ftCo_HammerJump_Coll(ftCo_GObj* gobj)
{
    ftCo_HammerFall_Coll(gobj);
}
