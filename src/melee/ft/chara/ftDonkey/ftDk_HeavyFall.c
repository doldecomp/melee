#include "ftDk_HeavyFall.h"

#include "ftDk_HeavyJump.h"
#include "ftDk_HeavyWait1.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"

void ftDk_HeavyFall_IASA(HSD_GObj* gobj)
{
    if (ft_80094EA4(gobj)) {
        return;
    }
}

void ftDk_HeavyFall_Phys(HSD_GObj* gobj)
{
    ft_80084DB0(gobj);
}

void ftDk_HeavyFall_Coll(HSD_GObj* gobj)
{
    ft_80082C74(gobj, ftDk_MS_346_800E05E4);
}

bool ftDk_MS_347_800E0378(HSD_GObj* gobj)
{
    bool result = ft_800CAE80(gobj);
    if (result) {
        ftDk_MS_348_800E04A4(gobj, result);
        return true;
    } else {
        return false;
    }
}

void ftDk_MS_347_800E03C0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftDonkeyAttributes* donkey_attr;
    ftCommon_8007D5D4(fp);
    donkey_attr = getFtSpecialAttrs2CC(fp);
    Fighter_ChangeMotionState(gobj, donkey_attr->motion_state + 7, 0, NULL, 0,
                              1, 0);
    ftAnim_SetAnimRate(gobj, 0);
    ft_800CB110(gobj, 1, 1);
}
