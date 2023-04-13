#include <melee/ft/chara/ftDonkey/ftdonkey.h>
#include <melee/ft/chara/ftDonkey/ftdonkey4.h>
#include <melee/ft/ft_unknown_006.h>

bool ftDonkey_800E0134(HSD_GObj* fighter_gobj)
{
    if (ft_800C97A8(fighter_gobj)) {
        ftDonkey_800E017C(fighter_gobj);
        return true;
    }

    return false;
}

void ftDonkey_800E017C(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs2CC(fp);
    ft_800C9840(fighter_gobj, donkey_attr->action_state + 4, 0, 0.0f,
                donkey_attr->cargo_hold.x20_TURN_SPEED, 0.0f);
}
