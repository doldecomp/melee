#include "ft/chara/ftDonkey/ftdonkey6.h"

#include "ft/chara/ftDonkey/ftdonkey.h"
#include "ft/chara/ftDonkey/ftdonkey7.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"

void ftDonkey_800E030C(HSD_GObj* gobj)
{
    s32 result = ft_80094EA4(gobj);
    if (result) {
        return;
    }
}

void ftDonkey_800E0330(HSD_GObj* gobj)
{
    ft_80084DB0(gobj);
}

void ftDonkey_800E0350(HSD_GObj* gobj)
{
    ft_80082C74(gobj, &ftDonkey_800E05E4);
}

bool ftDonkey_800E0378(HSD_GObj* gobj)
{
    bool result = ft_800CAE80(gobj);

    if (result) {
        ftDonkey_800E04A4(gobj, result);
        return true;
    }

    return false;
}

void ftDonkey_800E03C0(HSD_GObj* gobj)
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
