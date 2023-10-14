#include <platform.h>
#include "ft/forward.h"

#include "ftCo_CargoJump.h"

#include "ftCo_09C4.h"
#include "ftCo_CargoFall.h"
#include "ftCo_CargoKneebend.h"
#include "ftCo_CargoThrow.h"
#include "ftCo_Shouldered.h"

#include "ft/fighter.h"
#include "ft/ft_0C88.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"

bool ftCo_8009BB1C(ftCo_GObj* gobj)
{
    bool b = ftCo_800CAE80(gobj);
    if (b) {
        ftCo_8009B9C8(gobj, b);
        return true;
    }
    return false;
}

void ftCo_8009BB64(ftCo_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16] = { 0 };
#endif
    ftCo_Fighter* fp = gobj->user_data;
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, fp->x2CC->x4_motion_state + 7, Ft_MF_None,
                              0, 1, 0, NULL);
    ftAnim_SetAnimRate(gobj, 0);
    ftCo_800CB110(gobj, 1, 1);
    ftCo_8009C5A4(fp->victim_gobj, ftCo_MS_ShoulderedWait);
}

void ftCo_CargoJump_Anim(HSD_GObj* gobj) {}

void ftCo_CargoJump_IASA(Fighter_GObj* gobj)
{
    RETURN_IF(ftCo_8009BF3C(gobj))
}

void ftCo_CargoJump_Phys(Fighter_GObj* gobj)
{
    ftCo_800CB438(gobj);
}

void ftCo_CargoJump_Coll(Fighter_GObj* gobj)
{
    ftCo_CargoFall_Coll(gobj);
}
