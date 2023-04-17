#include "ft/chara/ftDonkey/ftDk_MS_349.h"

#include "ft/chara/ftDonkey/ftDk_MS_341.h"
#include "ft/chara/ftDonkey/ftdonkey.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "it/item.h"

void ftDk_MS_349_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftDk_MS_349_Coll(HSD_GObj* gobj)
{
    ftDk_MS_341_Coll(gobj);
}

static bool ftDk_MS_349_800E0750(HSD_GObj* gobj);

void ftDk_MS_349_800E06D8(HSD_GObj* gobj)
{
    Vec3 vec;
    Fighter* fp = GET_FIGHTER(gobj);
    if (ftDk_MS_349_800E0750(gobj)) {
        ftDk_MS_349_800E07B0(gobj);
    } else {
        vec.x = vec.y = vec.z = 0.0f;
        Item_8026ABD8(fp->x1974_heldItem, &vec, 1.0f);
        ft_8008E908(gobj, 0.0f);
    }
}

bool ftDk_MS_349_800E0750(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ft_8008E984(fp)) {
        return true;
    }

    if (ft_8008D8E8(ft_0877_ScaleBy154(fp->dmg.x1850_forceApplied)) < 3) {
        return true;
    }

    return false;
}

void ftDk_MS_349_800E07B0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftDonkeyAttributes* donkey_attr = fp->x2CC;
    ft_8008DCE0(gobj, donkey_attr->action_state + 9, 0.0f);
}

void ftDk_MS_350_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ft_8008F744(gobj);
    if (!fp->x221C_flag.bits.b6) {
        if (fp->xE0_ground_or_air == GA_Air) {
            ftDk_MS_345_800E0294(gobj);
        } else {
            ftDk_Init_800DF980(gobj);
        }
    }
}

void ftDk_MS_350_Phys(HSD_GObj* gobj)
{
    ftCo_Damage_Phys(gobj);
}

void ftDk_MS_350_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->xE0_ground_or_air == GA_Ground) {
        if (!ft_80082708(gobj)) {
            ftCommon_8007D5D4(fp);
        }
    } else if (ft_80081D0C(gobj)) {
        ftCommon_8007D7FC(fp);
    }
}
