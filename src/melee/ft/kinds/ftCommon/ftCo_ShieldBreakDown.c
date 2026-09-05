#include "ftCo_ShieldBreakDown.h"

#include "ftCo_DownAttack.h"
#include "ftCo_DownBound.h"
#include "ftCo_ShieldBreakStand.h"

#include <Runtime/platform.h>

#include <melee/ft/fighter.h>

#include <melee/ft/forward.h>

#include <melee/ft/ft_081B.h>
#include <melee/ft/ft_084E.h>
#include <melee/ft/ftanim.h>
#include <melee/ft/ftcommon.h>

#include <sysdolphin/baselib/forward.h>

void ftCo_80098E3C(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->ground_or_air == GA_Air) {
        ftCommon_8007D7FC(fp);
    }
    {
        FtMotionId msid = ftCo_80097570(gobj) ? ftCo_MS_ShieldBreakDownU
                                              : ftCo_MS_ShieldBreakDownD;
        Fighter_ChangeMotionState(gobj, msid,
                                  Ft_MF_KeepColAnimHitStatus |
                                      Ft_MF_SkipModel | Ft_MF_SkipMatAnim |
                                      Ft_MF_SkipColAnim,
                                  0, 1, 0, NULL);
    }
    ftCo_800978D4(gobj);
}

void ftCo_ShieldBreakDown_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_80098F3C(gobj);
    }
}

void ftCo_ShieldBreakDown_IASA(HSD_GObj* gobj) {}

void ftCo_ShieldBreakDown_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftCo_ShieldBreakDown_Coll(Fighter_GObj* gobj)
{
    ft_80083F88(gobj);
}
