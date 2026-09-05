#include "ftdonkeyheavywait0.h"

#include "ftdonkeyheavyfall.h"
#include "ftdonkeyheavyturn.h"
#include "ftdonkeyms3450.h"

#include <melee/ft/fighter.h>

#include <melee/ft/forward.h>

#include <melee/ft/ft_081B.h>
#include <melee/ft/ft_084E.h>
#include <melee/ft/ft_0892.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/kinds/ftCommon/ftCo_ItemThrow.h>
#include "types.h"

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
