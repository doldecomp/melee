#include <melee/ft/chara/ftDonkey/ftdonkey.h>
#include <melee/ft/chara/ftDonkey/ftdonkey1.h>
#include <melee/ft/chara/ftDonkey/ftdonkey4.h>
#include <melee/ft/chara/ftDonkey/ftdonkey6.h>
#include <melee/ft/code_80081B38.h>
#include <melee/ft/ft_unknown_006.h>
#include <melee/ft/ftcamera.h>

bool ftDonkey_800DF938(HSD_GObj* fighter_gobj)
{
    if (func_8008A1FC(fighter_gobj)) {
        ftDonkey_800DF980(fighter_gobj);
        return true;
    }

    return false;
}

void ftDonkey_800DF980(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftDonkeyAttributes* donkey_attr;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    if (fp->xE0_ground_or_air == GA_Air) {
        func_8007D7FC(fp);
    }
    donkey_attr = getFtSpecialAttrs2CC(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, donkey_attr->action_state,
                                       0, NULL, 0.0f, 1.0f, 0.0f);
}

void ftDonkey_800DF9F0(HSD_GObj* fighter_gobj)
{
    if ((!func_80094EA4(fighter_gobj)) && (!ftDonkey_800E0378(fighter_gobj)) &&
        (!ftDonkey_800E0134(fighter_gobj)))
    {
        s32 result = ftDonkey_800DFA98(fighter_gobj);

        if (result)
            return;
    }
}

void ftDonkey_800DFA50(HSD_GObj* fighter_gobj)
{
    func_80084F3C(fighter_gobj);
}

void ftDonkey_800DFA70(HSD_GObj* fighter_gobj)
{
    func_8008403C(fighter_gobj, &ftDonkey_800E0294);
}
