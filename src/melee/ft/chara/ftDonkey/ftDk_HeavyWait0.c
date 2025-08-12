#include "ftDk_HeavyWait0.h"

#include "ftDk_HeavyFall.h"
#include "ftDk_HeavyTurn.h"
#include "ftDk_MS_345_0.h"

#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ftcommon.h"
#include "ftCommon/ftCo_ItemThrow.h"
#include "ftDonkey/types.h"

#include <common_structs.h>

bool ftDk_MS_341_800DF938(HSD_GObj* gobj)
{
    if (ft_8008A1FC(gobj)) {
        ftDk_MS_341_800DF980(gobj);
        return true;
    } else {
        return false;
    }
}

void ftDk_MS_341_800DF980(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    u8 _[4];
    if (fp->ground_or_air == GA_Air) {
        ftCommon_8007D7FC(fp);
    }
    {
        ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs2CC(fp);
        Fighter_ChangeMotionState(gobj, donkey_attr->motion_state, 0, 0, 1, 0,
                                  NULL);
    }
}

void ftDk_HeavyWait0_IASA(HSD_GObj* gobj)
{
    if (!ftCo_80094EA4(gobj) && !ftDk_MS_347_800E0378(gobj) &&
        !ftDk_MS_345_800E0134(gobj))
    {
        if (ftDk_MS_341_800DFA98(gobj)) {
            return;
        }
    }
}

void ftDk_HeavyWait0_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftDk_HeavyWait0_Coll(HSD_GObj* gobj)
{
    ft_8008403C(gobj, ftDk_MS_345_800E0294);
}
