#include <melee/ft/chara/ftDonkey/ftdonkey9.h>

#include <melee/ft/chara/ftDonkey/ftdonkey.h>
#include <melee/ft/chara/ftDonkey/ftdonkey1.h>
#include <melee/ft/code_80081B38.h>
#include <melee/ft/ft_unknown_006.h>
#include <melee/it/item.h>

void ftDonkey_800E0698(HSD_GObj* fighter_gobj)
{
    ft_80084F3C(fighter_gobj);
}

void ftDonkey_800E06B8(HSD_GObj* fighter_gobj)
{
    ftDonkey_800DFA70(fighter_gobj);
}

static bool ftDonkey_800E0750(HSD_GObj* fighter_gobj);

void ftDonkey_800E06D8(HSD_GObj* fighter_gobj)
{
    Vec3 vec;
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    if (ftDonkey_800E0750(fighter_gobj)) {
        ftDonkey_800E07B0(fighter_gobj);
    } else {
        vec.x = vec.y = vec.z = 0.0f;
        Item_8026ABD8(fp->x1974_heldItem, &vec, 1.0f);
        ft_8008E908(fighter_gobj, 0.0f);
    }
}

bool ftDonkey_800E0750(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    if (ft_8008E984(fp))
        return true;

    if (ft_8008D8E8(ft_ScaleBy154(fp->dmg.x1850_forceApplied)) < 3)
        return true;

    return false;
}

void ftDonkey_800E07B0(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftDonkeyAttributes* donkey_attr = fp->x2CC;
    ft_8008DCE0(fighter_gobj, donkey_attr->action_state + 9, 0.0f);
}

void ftDonkey_800E07E4(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ft_8008F744(fighter_gobj);
    if (!fp->x221C_flag.bits.b6) {
        if (fp->xE0_ground_or_air == GA_Air) {
            ftDonkey_800E0294(fighter_gobj);
        } else {
            ftDonkey_800DF980(fighter_gobj);
        }
    }
}

void ftDonkey_800E0848(HSD_GObj* fighter_gobj)
{
    ft_8008FB18(fighter_gobj);
}

void ftDonkey_800E0868(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    if (fp->xE0_ground_or_air == GA_Ground) {
        if (!ft_80082708(fighter_gobj)) {
            ftCommon_8007D5D4(fp);
        }
    } else if (ft_80081D0C(fighter_gobj)) {
        ftCommon_8007D7FC(fp);
    }
}
