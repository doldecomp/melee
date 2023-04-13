#include "ft/chara/ftDonkey/ftdonkey8.h"

#include "ft/chara/ftDonkey/ftdonkey.h"
#include "ft/chara/ftDonkey/ftdonkey1.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"

void ftDonkey_800E0568(HSD_GObj* gobj)
{
    if (!ft_80094EA4(gobj)) {
        ft_800CB59C(gobj);
    }
}

void ftDonkey_800E05A4(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftDonkey_800E05C4(HSD_GObj* gobj)
{
    ftDonkey_800DFA70(gobj);
}

void ftDonkey_800E05E4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs2CC(fp);
    fp->sv.dk.unk8.x4 = donkey_attr->cargo_hold.x28_LANDING_LAG;
    donkey_attr = getFtSpecialAttrs2CC(fp);
    ft_800D5AEC(gobj, donkey_attr->action_state + 8, 1, 0, fp, 0.0f, 1.0f);
    ftAnim_SetAnimRate(gobj, 0.0f);
}

void ftDonkey_800E0648(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->sv.dk.unk8.x4 <= 0.0f) {
        ftDonkey_800DF980(gobj);
    }

    fp->sv.dk.unk8.x4 -= 1.0f;
}
