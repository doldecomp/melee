#include "ftdonkey4.h"

#include "ftdonkey.h"

#include "ft/ft_0877.h"
#include "ft/inlines.h"

bool ftDonkey_800E0134(HSD_GObj* gobj)
{
    if (ft_800C97A8(gobj)) {
        ftDonkey_800E017C(gobj);
        return true;
    }

    return false;
}

void ftDonkey_800E017C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs2CC(fp);
    ft_800C9840(gobj, donkey_attr->motion_state + 4, 0, 0.0f,
                donkey_attr->cargo_hold.x20_TURN_SPEED, 0.0f);
}
