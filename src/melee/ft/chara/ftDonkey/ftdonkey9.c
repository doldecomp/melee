#include "ftdonkey9.h"

#include "ftdonkey.h"
#include "ftdonkey1.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/inlines.h"
#include "it/item.h"

#include <dolphin/mtx/types.h>

void ftDonkey_800E0698(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftDonkey_800E06B8(HSD_GObj* gobj)
{
    ftDonkey_800DFA70(gobj);
}

static bool ftDonkey_800E0750(HSD_GObj* gobj);

void ftDonkey_800E06D8(HSD_GObj* gobj)
{
    Vec3 vec;
    Fighter* fp = GET_FIGHTER(gobj);
    if (ftDonkey_800E0750(gobj)) {
        ftDonkey_800E07B0(gobj);
    } else {
        vec.x = vec.y = vec.z = 0.0f;
        func_8026ABD8(fp->x1974_heldItem, &vec, 1.0f);
        ft_8008E908(gobj, 0.0f);
    }
}

bool ftDonkey_800E0750(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ft_8008E984(fp)) {
        return true;
    }

    if (ft_8008D8E8(ft_ScaleBy154(fp->dmg.x1850_forceApplied)) < 3) {
        return true;
    }

    return false;
}

void ftDonkey_800E07B0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftDonkeyAttributes* donkey_attr = fp->x2CC;
    ft_8008DCE0(gobj, donkey_attr->motion_state + 9, 0.0f);
}

void ftDonkey_800E07E4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ft_8008F744(gobj);
    if (!fp->x221C_flag.bits.b6) {
        if (fp->ground_or_air == GA_Air) {
            ftDonkey_800E0294(gobj);
        } else {
            ftDonkey_800DF980(gobj);
        }
    }
}

void ftDonkey_800E0848(HSD_GObj* gobj)
{
    ft_8008FB18(gobj);
}

void ftDonkey_800E0868(HSD_GObj* gobj)
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
