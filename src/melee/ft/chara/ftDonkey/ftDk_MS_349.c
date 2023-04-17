#include "ftDk_MS_349.h"

#include "ftDk_MS_341.h"
#include "ftdonkey.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/inlines.h"
#include "it/item.h"

#include <dolphin/mtx/types.h>

void ftDk_MS_349_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftDk_MS_349_Coll(HSD_GObj* gobj)
{
    ftDk_MS_341_Coll(gobj);
}

static bool checkSomething(HSD_GObj* gobj);

void ftDk_MS_349_800E06D8(HSD_GObj* gobj)
{
    Vec3 vec;
    Fighter* fp = GET_FIGHTER(gobj);
    if (checkSomething(gobj)) {
        doSomething(gobj);
    } else {
        vec.x = vec.y = vec.z = 0.0f;
        Item_8026ABD8(fp->x1974_heldItem, &vec, 1.0f);
        ft_8008E908(gobj, 0.0f);
    }
}

bool checkSomething(HSD_GObj* gobj)
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

void doSomething(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftDonkeyAttributes* donkey_attr = fp->x2CC;
    ft_8008DCE0(gobj, donkey_attr->motion_state + 9, 0.0f);
}

void ftDk_MS_350_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ft_8008F744(gobj);
    if (!fp->x221C_flag.bits.b6) {
        if (fp->ground_or_air == GA_Air) {
            ftDk_MS_345_800E0294(gobj);
        } else {
            ftDk_MS_341_800DF980(gobj);
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
    if (fp->ground_or_air == GA_Ground) {
        if (!ft_80082708(gobj)) {
            ftCommon_8007D5D4(fp);
        }
    } else if (ft_80081D0C(gobj)) {
        ftCommon_8007D7FC(fp);
    }
}
