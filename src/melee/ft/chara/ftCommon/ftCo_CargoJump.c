#include <platform.h>

#include "ft/forward.h"
#include <baselib/forward.h>

#include "ftCo_CargoJump.h"

#include "ftCo_CargoFall.h"
#include "ftCo_CargoKneebend.h"
#include "ftCo_CargoThrow.h"
#include "ftCo_Shouldered.h"

#include "ft/fighter.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ftCommon/ftCo_Jump.h"
#include "ftDonkey/types.h"

bool ftCo_8009BB1C(ftCo_GObj* gobj)
{
    ftCo_JumpInput b = ftCo_Jump_GetInput(gobj);
    if (b) {
        ftCo_8009B9C8(gobj, b);
        return true;
    }
    return false;
}

void ftCo_8009BB64(ftCo_GObj* gobj)
{
    u8 _[16] = { 0 };
    ftCo_Fighter* fp = gobj->user_data;
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, fp->x2CC->x4_motion_state + 7, Ft_MF_None,
                              0, 1, 0, NULL);
    ftAnim_SetAnimRate(gobj, 0);
    ftCo_800CB110(gobj, true, 1);
    ftCo_8009C5A4(fp->victim_gobj, ftCo_MS_ShoulderedWait);
}

void ftCo_CargoJump_Anim(HSD_GObj* gobj) {}

void ftCo_CargoJump_IASA(Fighter_GObj* gobj)
{
    RETURN_IF(ftCo_8009BF3C(gobj));
}

void ftCo_CargoJump_Phys(Fighter_GObj* gobj)
{
    ftCo_Jump_Phys_Inner(gobj);
}

void ftCo_CargoJump_Coll(Fighter_GObj* gobj)
{
    ftCo_CargoFall_Coll(gobj);
}
