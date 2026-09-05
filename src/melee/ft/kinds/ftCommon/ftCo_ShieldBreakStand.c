#include "ftCo_ShieldBreakStand.h"

#include "ftCo_Furafura.h"

#include <melee/ft/forward.h>

#include <melee/ft/fighter.h>
#include <melee/ft/ft_081B.h>
#include <melee/ft/ft_084E.h>
#include <melee/ft/ftanim.h>
#include <Runtime/platform.h>

void ftCo_80098F3C(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    FtMotionId msid = fp->motion_id == ftCo_MS_ShieldBreakDownU
                          ? ftCo_MS_ShieldBreakStandU
                          : ftCo_MS_ShieldBreakStandD;
    Fighter_ChangeMotionState(gobj, msid,
                              Ft_MF_KeepColAnimHitStatus | Ft_MF_SkipModel |
                                  Ft_MF_SkipMatAnim | Ft_MF_SkipColAnim,
                              0, 1, 0, NULL);
}

void ftCo_ShieldBreakStand_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_80099010(gobj);
    }
}

void ftCo_ShieldBreakStand_IASA(Fighter_GObj* gobj) {}

void ftCo_ShieldBreakStand_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftCo_ShieldBreakStand_Coll(Fighter_GObj* gobj)
{
    ft_80083F88(gobj);
}
