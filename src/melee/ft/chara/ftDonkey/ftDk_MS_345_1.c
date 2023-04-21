#include "ftDk_MS_345_1.h"

#include "ftDk_MS_341.h"
#include "ftDk_MS_347.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"

void ftDk_MS_345_Anim(HSD_GObj* gobj)
{
    ft_800C9924(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftDk_MS_341_800DF980(gobj);
    }
}

void ftDk_MS_345_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->mv.dk.unk5.x0 && !ft_80094EA4(gobj)) {
        if (ftDk_MS_347_800E0378(gobj)) {
            return;
        }
    }
}

void ftDk_MS_345_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftDk_MS_345_Coll(HSD_GObj* gobj)
{
    ftDk_MS_341_Coll(gobj);
}

void ftDk_MS_345_800E0294(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs2CC(fp);
    Fighter_ChangeMotionState(gobj, donkey_attr->motion_state + 6, 1, NULL, 0,
                              1, 0);
    ftAnim_SetAnimRate(gobj, 0);
    if (fp->ground_or_air == GA_Ground) {
        ftCommon_8007D5D4(fp);
    }
}
