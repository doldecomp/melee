#include "ft/chara/ftDonkey/ftdonkey_walk.h"

#include "ft/chara/ftDonkey/ftdonkey.h"
#include "ft/chara/ftDonkey/ftdonkey1.h"
#include "ft/chara/ftDonkey/ftdonkey6.h"
#include "ft/ft_0877.h"
#include "ft/ftwalkcommon.h"
#include "it/it_27CF.h"

bool ftDonkey_800DFA98(HSD_GObj* gobj)
{
    if (ftWalkCommon_800DFC70(gobj)) {
        ftDonkey_800DFAE4(gobj, 0.0f);
        return true;
    }

    return false;
}

void ftDonkey_800DFAE4(HSD_GObj* gobj, f32 argf)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs2CC(fp);
    ftWalkCommon_800DFCA4(gobj, donkey_attr->action_state + 1, 0, argf,
                          donkey_attr->x8, donkey_attr->xC, donkey_attr->x10,
                          donkey_attr->x14, donkey_attr->x18, donkey_attr->x1C,
                          1.0f);
}

void ftDonkey_800DFB34(HSD_GObj* gobj)
{
    ftWalkCommon_800DFDDC(gobj);
}

void ftDonkey_800DFB54(HSD_GObj* gobj)
{
    if ((!ft_80094EA4(gobj)) && (!ftDonkey_800E0378(gobj)) &&
        (!ftDonkey_800DF938(gobj)))
    {
        ftWalkCommon_800DFEC8(gobj, &ftDonkey_800DFAE4);
    }
}

void ftDonkey_800DFBB8(HSD_GObj* gobj)
{
    ftWalkCommon_800E0060(gobj);
}

void ftDonkey_800DFBD8(HSD_GObj* gobj)
{
    ftDonkey_800DFA70(gobj);
}
