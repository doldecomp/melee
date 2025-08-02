#include <platform.h>

#include <baselib/forward.h>

#include "ftCo_Passive.h"

#include "inlines.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0881.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/ftcolanim.h"
#include "ft/ftcommon.h"
#include "ft/types.h"

#include <common_structs.h>

void ftCo_800987D0(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->ground_or_air == GA_Air) {
        ftCommon_8007D7FC(fp);
    }
    Fighter_ChangeMotionState(gobj, 199, Ft_MF_None, 0, 1, 0, NULL);
    ft_800881D8(fp, fp->ft_data->x4C_sfx->x24, 127, 64);
    ft_80088148(fp, 3, 127, 64);
    ftCommon_8007CCE8(fp);
    ftCo_SpawnEf(gobj, fp->parts[FtPart_TopN].joint, 1, 1053);
    ftCo_800BFFD0(fp, 120, 0);
}

void ftCo_Passive_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftCo_Passive_IASA(HSD_GObj* gobj) {}

void ftCo_Passive_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftCo_Passive_Coll(Fighter_GObj* gobj)
{
    ft_80083F88(gobj);
}
