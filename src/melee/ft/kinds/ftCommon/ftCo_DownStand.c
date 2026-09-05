#include "ftCo_DownStand.h"

#include <melee/ft/forward.h>
#include <sysdolphin/baselib/forward.h>

#include <dolphin/mtx.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ft_081B.h>
#include <melee/ft/ft_084E.h>
#include <melee/ft/ft_0892.h>
#include <melee/ft/ftanim.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/types.h>
#include <Runtime/platform.h>

bool ftCo_800980BC(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if ((fp->input.lstick.y >= p_ftCommonData->x244 &&
         ftCo_GetLStickAngle(fp) >= p_ftCommonData->x20_radians) ||
        fp->input.x668 & HSD_PAD_LR)
    {
        FtMotionId msid;
        if (fp->motion_id == ftCo_MS_DownWaitU) {
            msid = ftCo_MS_DownStandU;
        } else {
            msid = ftCo_MS_DownStandD;
        }
        ftCo_80098160(gobj, msid);
        return true;
    }
    return false;
}

void ftCo_80098160(Fighter_GObj* gobj, FtMotionId msid)
{
    Fighter_ChangeMotionState(gobj, msid, Ft_MF_None, 0, 1, 0, NULL);
}

void ftCo_DownStand_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftCo_DownStand_IASA(HSD_GObj* gobj) {}

void ftCo_DownStand_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftCo_DownStand_Coll(Fighter_GObj* gobj)
{
    ft_80083F88(gobj);
}
