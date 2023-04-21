#include "ft/chara/ftDonkey/ftDk_MS_341.h"

#include "ft/chara/ftDonkey/ftDk_MS_345.h"
#include "ft/chara/ftDonkey/ftDk_MS_347.h"
#include "ft/chara/ftDonkey/ftdonkey.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftcamera.h"

bool ftDk_MS_341_800DF938(HSD_GObj* gobj)
{
    if (ft_8008A1FC(gobj)) {
        ftDk_MS_341_800DF980(gobj);
        return true;
    }

    return false;
}

void ftDk_MS_341_800DF980(HSD_GObj* gobj)
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

void ftDk_MS_341_IASA(HSD_GObj* gobj)
{
    if ((!ft_80094EA4(gobj)) && (!ftDk_MS_347_800E0378(gobj)) &&
        (!ftDk_MS_345_800E0134(gobj)))
    {
        s32 result = ftDk_MS_341_800DFA98(gobj);

        if (result) {
            return;
        }
    }
}

void ftDk_MS_341_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftDk_MS_341_Coll(HSD_GObj* gobj)
{
    ft_8008403C(gobj, &ftDk_MS_345_800E0294);
}
