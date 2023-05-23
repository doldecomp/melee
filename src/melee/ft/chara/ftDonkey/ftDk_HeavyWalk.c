#include "ftDk_HeavyWalk.h"

#include "ftDk_HeavyFall.h"
#include "ftDk_HeavyWait0.h"

#include "ft/ft_0877.h"
#include "ft/ft_08A4.h"
#include "ft/ftwalkcommon.h"
#include "ft/inlines.h"
#include "it/it_27CF.h"

bool ftDk_MS_341_800DFA98(HSD_GObj* gobj)
{
    if (ftWalkCommon_800DFC70(gobj)) {
        ftDk_MS_341_800DFAE4(gobj, 0);
        return true;
    } else {
        return false;
    }
}

void ftDk_MS_341_800DFAE4(HSD_GObj* gobj, f32 argf)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs2CC(fp);
    ftWalkCommon_800DFCA4(gobj, donkey_attr->motion_state + 1, 0, argf,
                          donkey_attr->x8, donkey_attr->xC, donkey_attr->x10,
                          donkey_attr->x14, donkey_attr->x18, donkey_attr->x1C,
                          1);
}

void ftDk_HeavyWalk_Anim(HSD_GObj* gobj)
{
    ftWalkCommon_800DFDDC(gobj);
}

void ftDk_HeavyWalk_IASA(HSD_GObj* gobj)
{
    if (!ft_80094EA4(gobj) && !ftDk_MS_347_800E0378(gobj) &&
        !ftDk_MS_341_800DF938(gobj))
    {
        ftWalkCommon_800DFEC8(gobj, ftDk_MS_341_800DFAE4);
    }
}

void ftDk_HeavyWalk_Phys(HSD_GObj* gobj)
{
    ftWalkCommon_800E0060(gobj);
}

void ftDk_HeavyWalk_Coll(HSD_GObj* gobj)
{
    ftDk_HeavyWait0_Coll(gobj);
}
