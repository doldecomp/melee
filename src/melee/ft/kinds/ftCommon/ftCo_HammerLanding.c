#include "ftCo_HammerLanding.h"

#include "ftCo_HammerWait.h"
#include "ftCo_Landing.h"
#include "types.h"

#include <melee/ft/fighter.h>
#include <melee/ft/ft_084E.h>
#include <melee/ft/types.h>
#include <Runtime/platform.h>

void ftCo_HammerLanding_Enter(Fighter_GObj* gobj)
{
    /// @todo Cannot move below @c fp, which suggests an inline
    u32 flags;
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.co.hammerlanding.x4 = p_ftCommonData->x6B4;
    flags = ftCo_800C54C4(fp);
    ftCo_Landing_Enter(gobj, ftCo_MS_HammerLanding, Ft_MF_KeepFastFall, flags,
                       ftCo_800C548C(fp), 1.0F);
    ftCo_800C4E94(fp);
}

void ftCo_HammerLanding_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_800C4F64(gobj);
    if (fp->mv.co.hammerlanding.x4 <= 0) {
        ftCo_800C4ED8(gobj);
    }
    --fp->mv.co.hammerlanding.x4;
}

void ftCo_HammerLanding_IASA(Fighter_GObj* gobj) {}

void ftCo_HammerLanding_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftCo_HammerLanding_Coll(Fighter_GObj* gobj)
{
    ftCo_HammerWait_Coll(gobj);
}
