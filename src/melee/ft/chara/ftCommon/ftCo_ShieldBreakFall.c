#include <platform.h>

#include "ft/forward.h"

#include "ftCo_ShieldBreakFall.h"

#include "ftCo_ShieldBreakDown.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ftcommon.h"

void ftCo_80098D90(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    Fighter_ChangeMotionState(gobj, ftCo_MS_ShieldBreakFall,
                              Ft_MF_KeepColAnimHitStatus | Ft_MF_SkipModel |
                                  Ft_MF_Unk06 | Ft_MF_SkipMatAnim |
                                  Ft_MF_SkipColAnim,
                              0, 1, 0, NULL);
    ftCommon_8007D468(fp);
    ftCommon_8007EBAC(fp, 8, 0);
}

void ftCo_ShieldBreakFall_Anim(ftCo_GObj* gobj) {}

void ftCo_ShieldBreakFall_IASA(ftCo_GObj* gobj) {}

void ftCo_ShieldBreakFall_Phys(ftCo_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftCo_ShieldBreakFall_Coll(ftCo_GObj* gobj)
{
    ft_80082C74(gobj, ftCo_80098E3C);
}
