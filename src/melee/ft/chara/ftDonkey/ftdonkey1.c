#include "ft/chara/ftDonkey/ftdonkey1.h"

#include "ft/chara/ftDonkey/ftdonkey.h"
#include "ft/chara/ftDonkey/ftdonkey4.h"
#include "ft/chara/ftDonkey/ftdonkey6.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftcamera.h"

bool ftDonkey_800DF938(HSD_GObj* gobj)
{
    if (ft_8008A1FC(gobj)) {
        ftDonkey_800DF980(gobj);
        return true;
    }

    return false;
}

void ftDonkey_800DF980(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftDonkeyAttributes* donkey_attr;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    if (fp->xE0_ground_or_air == GA_Air) {
        ftCommon_8007D7FC(fp);
    }
    donkey_attr = getFtSpecialAttrs2CC(fp);
    Fighter_ChangeMotionState(gobj, donkey_attr->action_state, 0, NULL, 0.0f,
                              1.0f, 0.0f);
}

void ftDonkey_800DF9F0(HSD_GObj* gobj)
{
    if ((!ft_80094EA4(gobj)) && (!ftDonkey_800E0378(gobj)) &&
        (!ftDonkey_800E0134(gobj)))
    {
        s32 result = ftDonkey_800DFA98(gobj);

        if (result) {
            return;
        }
    }
}

void ftDonkey_800DFA50(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftDonkey_800DFA70(HSD_GObj* gobj)
{
    ft_8008403C(gobj, &ftDonkey_800E0294);
}
