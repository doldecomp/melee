#include "ft/chara/ftDonkey/ftdonkey7.h"

#include "ft/chara/ftDonkey/ftdonkey.h"
#include "ft/chara/ftDonkey/ftdonkey6.h"
#include "ft/ft_0877.h"

void ftDonkey_800E0440(HSD_GObj* gobj)
{
    s32 result = ft_80094EA4(gobj);
    if (result) {
        return;
    }
}

void ftDonkey_800E0464(HSD_GObj* gobj)
{
    ft_800CB438(gobj);
}

void ftDonkey_800E0484(HSD_GObj* gobj)
{
    ftDonkey_800E0350(gobj);
}

void ftDonkey_800E04A4(HSD_GObj* gobj, s32 arg1)
{
    Fighter* fp = gobj->user_data;
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs2CC(fp);
    ftDonkeyAttributes* donkey_attr2;
    fp->sv.dk.unk7.x4 = arg1;
    fp->sv.dk.unk7.x0 = 0;
    fp->sv.dk.unk7.x8 = donkey_attr->cargo_hold.x24_JUMP_STARTUP_LAG;
    donkey_attr2 = getFtSpecialAttrs2CC(fp);

    Fighter_ChangeMotionState(gobj, donkey_attr2->action_state + 5, 0, NULL,
                              0.0f, 1.0f, 0.0f);
    ftAnim_SetAnimRate(gobj, 0.0f);
}

void ftDonkey_800E0518(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->sv.dk.unk7.x8 <= 0.0f) {
        ftDonkey_800E03C0(gobj);
    }
    fp->sv.dk.unk7.x8 -= 1.0f;
}
