#include <placeholder.h>

#include "ft/forward.h"
#include "ftCommon/forward.h"

#include "ft/chara/ftCommon/ftCo_DownSpot.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ftcommon.h"
#include "ft/ftdata.h"
#include "ft/inlines.h"
#include "ftCommon/ftCo_DownBound.h"

void ftCo_DownSpot_Enter(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    FtMotionId msid;

    if (ftData_80085FD4(fp, ftCo_MS_DownSpotU)->x14) {
        msid = ftCo_MS_DownSpotU;
    } else {
        msid = ftCo_MS_DownSpotD;
    }
    Fighter_ChangeMotionState(gobj, msid, Ft_MF_None, 0.0F, 1.0F, 0.0F, NULL);
    ftAnim_8006EBA4(gobj);
    ftCommon_8007E2F4(fp, 0x1FF);
    fp->mv.co.downspot.x4 = 0;
}

void ftCo_DownSpot_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_80097E8C(gobj);
    }
}

void ftCo_DownSpot_IASA(Fighter_GObj* gobj) {}

void ftCo_DownSpot_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftCo_DownSpot_Coll(Fighter_GObj* gobj)
{
    ft_80083F88(gobj);
}
