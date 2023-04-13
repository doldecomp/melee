#include <melee/ft/chara/ftDonkey/ftdonkey.h>
#include <melee/ft/chara/ftDonkey/ftdonkey6.h>
#include <melee/ft/chara/ftDonkey/ftdonkey7.h>
#include <melee/ft/ft_unknown_006.h>

void ftDonkey_800E0440(HSD_GObj* fighter_gobj)
{
    s32 result = ft_80094EA4(fighter_gobj);
    if (result) {
        return;
    }
}

void ftDonkey_800E0464(HSD_GObj* fighter_gobj)
{
    ft_800CB438(fighter_gobj);
}

void ftDonkey_800E0484(HSD_GObj* fighter_gobj)
{
    ftDonkey_800E0350(fighter_gobj);
}

void ftDonkey_800E04A4(HSD_GObj* fighter_gobj, s32 arg1)
{
    Fighter* fp = fighter_gobj->user_data;
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs2CC(fp);
    ftDonkeyAttributes* donkey_attr2;
    fp->sv.dk.unk7.x4 = arg1;
    fp->sv.dk.unk7.x0 = 0;
    fp->sv.dk.unk7.x8 = donkey_attr->cargo_hold.x24_JUMP_STARTUP_LAG;
    donkey_attr2 = getFtSpecialAttrs2CC(fp);

    Fighter_ChangeMotionState(fighter_gobj, donkey_attr2->action_state + 5, 0,
                              NULL, 0.0f, 1.0f, 0.0f);
    ftAnim_SetAnimRate(fighter_gobj, 0.0f);
}

void ftDonkey_800E0518(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    if (fp->sv.dk.unk7.x8 <= 0.0f) {
        ftDonkey_800E03C0(fighter_gobj);
    }
    fp->sv.dk.unk7.x8 -= 1.0f;
}
