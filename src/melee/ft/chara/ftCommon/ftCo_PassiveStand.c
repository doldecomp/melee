#include <platform.h>

#include "ft/forward.h"
#include <dolphin/mtx/forward.h>

#include "ftCo_PassiveStand.h"

#include "ftCo_DownAttack.h"
#include "math.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0881.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/types.h"
#include "ftCommon/inlines.h"

#include <common_structs.h>

/* 09855C */ static void ftCo_800989D4(ftCo_GObj* gobj, FtMotionId msid);

bool ftCo_80098928(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (ftCo_800986B0(gobj)) {
        if (ABS(fp->input.lstick.x) >= p_ftCommonData->x254) {
            FtMotionId msid = fp->input.lstick.x * fp->facing_dir >= 0
                                  ? ftCo_MS_PassiveStandF
                                  : ftCo_MS_PassiveStandB;
            ftCo_800989D4(gobj, msid);
            return true;
        }
    }
    return false;
}

void ftCo_800989D4(Fighter_GObj* gobj, FtMotionId msid)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->ground_or_air == GA_Air) {
        ftCommon_8007D7FC(fp);
    }
    Fighter_ChangeMotionState(gobj, msid, Ft_MF_None, 0, 1, 0, NULL);
    ft_800881D8(fp, fp->ft_data->x4C_sfx->x24, 127, 64);
    ft_80088148(fp, 3, 127, 64);
    ftCo_SpawnEf(gobj, fp->parts[FtPart_TopN].joint, 1, 1053);
}

void ftCo_PassiveStand_Anim(ftCo_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftCo_PassiveStand_IASA(ftCo_GObj* gobj) {}

void ftCo_PassiveStand_Phys(ftCo_GObj* gobj)
{
    ft_80084FA8(gobj);
}

void ftCo_PassiveStand_Coll(ftCo_GObj* gobj)
{
    ft_80084104(gobj);
}
