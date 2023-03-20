#include <melee/ft/chara/ftDonkey/ftdonkey.h>
#include <melee/ft/chara/ftDonkey/ftdonkey1.h>
#include <melee/ft/chara/ftDonkey/ftdonkey8.h>
#include <melee/ft/code_80081B38.h>
#include <melee/ft/ft_unknown_006.h>

void ftDonkey_800E0568(HSD_GObj* fighter_gobj)
{
    if (!func_80094EA4(fighter_gobj))
        func_800CB59C(fighter_gobj);
}

void ftDonkey_800E05A4(HSD_GObj* fighter_gobj)
{
    func_80084F3C(fighter_gobj);
}

void ftDonkey_800E05C4(HSD_GObj* fighter_gobj)
{
    ftDonkey_800DFA70(fighter_gobj);
}

void ftDonkey_800E05E4(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs2CC(fp);
    fp->sv.dk.unk8.x4 = donkey_attr->cargo_hold.x28_LANDING_LAG;
    donkey_attr = getFtSpecialAttrs2CC(fp);
    func_800D5AEC(fighter_gobj, donkey_attr->action_state + 8, 1, 0, fp, 0.0f,
                  1.0f);
    ftAnim_SetAnimRate(fighter_gobj, 0.0f);
}

void ftDonkey_800E0648(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    if (fp->sv.dk.unk8.x4 <= 0.0f)
        ftDonkey_800DF980(fighter_gobj);

    fp->sv.dk.unk8.x4 -= 1.0f;
}
