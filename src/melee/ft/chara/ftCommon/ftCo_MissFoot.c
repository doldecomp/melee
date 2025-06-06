#include <platform.h>

#include "ft/forward.h"

#include "ftCo_MissFoot.h"

#include "ftCo_DamageFall.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"

#include <common_structs.h>
#include <dolphin/mtx.h>

void ftCo_8009F39C(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    fp->x8c_kb_vel.y = 0;
    Fighter_ChangeMotionState(gobj, ftCo_MS_MissFoot, Ft_MF_None, 0, 1, 0,
                              NULL);
    ftCommon_8007D468(fp);
    if (fp->ground_or_air == GA_Ground) {
        ftCommon_8007D5D4(fp);
    }
}

void ftCo_MissFoot_Anim(ftCo_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_80090780(gobj);
    }
}

void ftCo_MissFoot_IASA(ftCo_GObj* gobj) {}

void ftCo_MissFoot_Phys(ftCo_GObj* gobj)
{
    ft_80084DB0(gobj);
}

void ftCo_MissFoot_Coll(ftCo_GObj* gobj)
{
    ft_80082F28(gobj);
}
