#include "ftdonkeyheavyfall.h"

#include "ftdonkeyheavyjump.h"
#include "ftdonkeyheavywait1.h"

#include <melee/ft/fighter.h>

#include <melee/ft/forward.h>

#include <melee/ft/ft_081B.h>
#include <melee/ft/ftanim.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/kinds/ftCommon/ftCo_ItemThrow.h>
#include <melee/ft/kinds/ftCommon/ftCo_Jump.h>
#include "types.h"

void ftDk_HeavyFall_IASA(HSD_GObj* gobj)
{
    if (ftCo_80094EA4(gobj)) {
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
    ftCo_JumpInput result = ftCo_Jump_GetInput(gobj);
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
    Fighter_ChangeMotionState(gobj, donkey_attr->motion_state + 7, 0, 0, 1, 0,
                              NULL);
    ftAnim_SetAnimRate(gobj, 0);
    ftCo_800CB110(gobj, true, 1);
}
