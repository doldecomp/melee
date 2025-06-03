#include <platform.h>

#include "ft/forward.h"
#include <baselib/forward.h>

#include "ftCo_DownStand.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/types.h"

#include <common_structs.h>
#include <dolphin/mtx.h>

bool ftCo_800980BC(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if ((fp->input.lstick.y >= p_ftCommonData->x244 &&
         ftCo_GetLStickAngle(fp) >= p_ftCommonData->x20) ||
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

void ftCo_80098160(ftCo_GObj* gobj, FtMotionId msid)
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

void ftCo_DownStand_Phys(ftCo_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftCo_DownStand_Coll(Fighter_GObj* gobj)
{
    ft_80083F88(gobj);
}
