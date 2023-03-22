#include "ftdonkey5.h"

#include "ftdonkey.h"
#include "ftdonkey1.h"
#include "ftdonkey6.h"

#include "ft/code_80081B38.h"
#include "ft/ft_unknown_006.h"
#include "ft/inlines.h"

void ftDonkey_800E01BC(HSD_GObj* gobj)
{
    func_800C9924(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftDonkey_800DF980(gobj);
    }
}

void ftDonkey_800E0200(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->mv.dk.unk5.x0 && !func_80094EA4(gobj)) {
        bool result = ftDonkey_800E0378(gobj);

        if (result)
            return;
    }
}

void ftDonkey_800E0254(HSD_GObj* gobj)
{
    func_80084F3C(gobj);
}

void ftDonkey_800E0274(HSD_GObj* gobj)
{
    ftDonkey_800DFA70(gobj);
}

void ftDonkey_800E0294(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs2CC(fp);
    Fighter_ChangeMotionState(gobj, donkey_attr->motion_state + 6, 1, NULL,
                              0.0f, 1.0, 0.0f);
    ftAnim_SetAnimRate(gobj, 0.0f);
    if (fp->ground_or_air == GA_Ground) {
        ftCommon_8007D5D4(fp);
    }
}
