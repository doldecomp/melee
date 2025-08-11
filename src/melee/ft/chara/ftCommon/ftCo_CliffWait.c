#include <platform.h>

#include "ftCo_CliffWait.h"

#include "ftCo_CliffAttack.h"
#include "ftCo_CliffClimb.h"
#include "ftCo_CliffJump.h"
#include "ftCo_DamageFall.h"

#include "ft/fighter.h"
#include "ft/ftcliffcommon.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/types.h"
#include "ftCommon/types.h"

/* 09A9AC */ static bool ftCo_8009A9AC(Fighter_GObj* gobj);

void ftCo_8009A804(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    Fighter_ChangeMotionState(gobj, ftCo_MS_CliffWait, Ft_MF_SkipNametagVis, 0,
                              1, 0, NULL);
    ftCommon_8007E2F4(fp, 511);
    fp->x221D_b7 = true;
    fp->mv.co.cliff.x8 = 0;
    fp->mv.co.cliff.x4 = fp->dmg.x1830_percent < p_ftCommonData->x488
                             ? p_ftCommonData->x48C
                             : p_ftCommonData->x490;
    ftColl_8007B760(gobj, p_ftCommonData->x49C);
    ftCommon_8007E2F4(fp, 511);
}

void ftCo_CliffWait_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->mv.co.cliff.x4 > 0) {
        fp->mv.co.cliff.x4 -= 1;
    }
}

void ftCo_CliffWait_IASA(Fighter_GObj* gobj)
{
    RETURN_IF(ftCo_8009AE38(gobj));
    RETURN_IF(ftCo_8009AFD4(gobj));
    RETURN_IF(ftCo_8009B170(gobj));
    RETURN_IF(ftCo_8009AA0C(gobj));
    RETURN_IF(ftCo_8009A9AC(gobj));
}

void ftCo_CliffWait_Phys(Fighter_GObj* gobj)
{
    ftCo_CliffCatch_Phys(gobj);
}

void ftCo_CliffWait_Coll(Fighter_GObj* gobj)
{
    ftCo_CliffCatch_Coll(gobj);
}

bool ftCo_8009A9AC(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->mv.co.cliff.x4 <= 0) {
        fp->x2064_ledgeCooldown = p_ftCommonData->ledge_cooldown;
        fp->x2227_b1 = true;
        ftCo_80090780(gobj);
        return true;
    }
    return false;
}
