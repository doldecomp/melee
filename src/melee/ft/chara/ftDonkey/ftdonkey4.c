#include <melee/ft/chara/ftDonkey/ftdonkey.h>

#include <melee/ft/ft_unknown_006.h>

BOOL ftDonkey_800E0134(HSD_GObj* fighter_gobj)
{
    if (func_800C97A8(fighter_gobj)) {
        ftDonkey_800E017C(fighter_gobj);
        return TRUE;
    }

    return FALSE;
}

void ftDonkey_800E017C(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighterPlus(fighter_gobj);
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs2CC(fp);
    func_800C9840(fighter_gobj, donkey_attr->action_state + 4, 0, 0.0f,
                  donkey_attr->cargo_hold.x20_TURN_SPEED, 0.0f);
}
