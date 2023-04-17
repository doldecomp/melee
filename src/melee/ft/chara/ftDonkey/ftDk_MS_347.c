#include "ft/chara/ftDonkey/ftDk_MS_347.h"

#include "ft/chara/ftDonkey/ftDk_MS_348.h"
#include "ft/chara/ftDonkey/ftdonkey.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"

void ftDk_MS_347_IASA(HSD_GObj* gobj)
{
    s32 result = ft_80094EA4(gobj);
    if (result) {
        return;
    }
}

void ftDk_MS_347_Phys(HSD_GObj* gobj)
{
    ft_80084DB0(gobj);
}

void ftDk_MS_347_Coll(HSD_GObj* gobj)
{
    ft_80082C74(gobj, &ftDk_MS_346_800E05E4);
}

bool ftDk_MS_347_800E0378(HSD_GObj* gobj)
{
    bool result = ft_800CAE80(gobj);

    if (result) {
        ftDk_MS_348_800E04A4(gobj, result);
        return true;
    }

    return false;
}

void ftDk_MS_347_800E03C0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftDonkeyAttributes* donkey_attr;
    ftCommon_8007D5D4(fp);
    donkey_attr = getFtSpecialAttrs2CC(fp);
    Fighter_ChangeMotionState(gobj, donkey_attr->action_state + 7, 0, NULL,
                              0.0f, 1.0, 0.0f);
    ftAnim_SetAnimRate(gobj, 0.0f);
    ft_800CB110(gobj, 1, 1.0f);
}
