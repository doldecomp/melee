#include "ftdonkey1.h"

#include "ftdonkey.h"
#include "ftdonkey4.h"
#include "ftdonkey6.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftcamera.h"
#include "ft/inlines.h"

bool ftDk_Init_800DF938(HSD_GObj* gobj)
{
    if (ft_8008A1FC(gobj)) {
        ftDk_Init_800DF980(gobj);
        return true;
    }

    return false;
}

void ftDk_Init_800DF980(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftDonkeyAttributes* donkey_attr;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    if (fp->ground_or_air == GA_Air) {
        ftCommon_8007D7FC(fp);
    }
    donkey_attr = getFtSpecialAttrs2CC(fp);
    Fighter_ChangeMotionState(gobj, donkey_attr->motion_state, 0, NULL, 0.0f,
                              1.0f, 0.0f);
}

void ftDk_Init_800DF9F0(HSD_GObj* gobj)
{
    if ((!ft_80094EA4(gobj)) && (!ftDk_Unk6_800E0378(gobj)) &&
        (!ftDk_Unk4_800E0134(gobj)))
    {
        s32 result = ftDk_Walk_800DFA98(gobj);

        if (result) {
            return;
        }
    }
}

void ftDk_Init_800DFA50(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftDk_Init_800DFA70(HSD_GObj* gobj)
{
    ft_8008403C(gobj, &ftDk_Unk5_800E0294);
}
