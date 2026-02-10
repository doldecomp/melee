#include "ftCo_HammerKneeBend.h"

#include "ftCo_HammerJump.h"
#include "ftCo_HammerWait.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/types.h"
#include "ftCommon/ftCo_KneeBend.h"
#include "ftCommon/types.h"

void ftCo_800C5B88(Fighter_GObj* gobj, enum_t arg1)
{
    u8 _[8] = { 0 };
    /// @todo Cannot move below @c fp, which suggests an inline
    u32 flags;
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.co.hammerkneebend.x4 = arg1;
    fp->mv.co.hammerkneebend.x0 = 0;
    fp->mv.co.cargokneebend.x8 = fp->co_attrs.jump_startup_time;
    flags = ftCo_800C54C4(fp);
    Fighter_ChangeMotionState(gobj, ftCo_MS_HammerKneeBend, flags,
                              ftCo_800C548C(fp), 1, 0, NULL);
    ftCo_800C4E94(fp);
}

void ftCo_HammerKneeBend_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_800C4F64(gobj);
    if (fp->mv.co.hammerkneebend.x8 <= 0) {
        ftCo_800C5A98(gobj);
    }
    --fp->mv.co.hammerkneebend.x8;
}

void ftCo_HammerKneeBend_IASA(Fighter_GObj* gobj)
{
    ftCo_KneeBend_Check_ShortHop(gobj);
}

void ftCo_HammerKneeBend_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftCo_HammerKneeBend_Coll(Fighter_GObj* gobj)
{
    ftCo_HammerWait_Coll(gobj);
}
