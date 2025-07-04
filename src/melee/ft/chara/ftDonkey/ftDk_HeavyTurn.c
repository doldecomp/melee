#include "ftDk_HeavyTurn.h"

#include "ftDk_HeavyFall.h"
#include "ftDk_HeavyWait0.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/types.h"
#include "ftCommon/ftCo_ItemThrow.h"
#include "ftCommon/ftCo_Turn.h"
#include "ftDonkey/types.h"

#include <common_structs.h>
#include <stddef.h>

void ftDk_HeavyTurn_Anim(HSD_GObj* gobj)
{
    ftCo_Turn_Anim_Inner(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftDk_MS_341_800DF980(gobj);
    }
}

void ftDk_HeavyTurn_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->mv.dk.unk5.x0 && !ftCo_80094EA4(gobj)) {
        if (ftDk_MS_347_800E0378(gobj)) {
            return;
        }
    }
}

void ftDk_HeavyTurn_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftDk_HeavyTurn_Coll(HSD_GObj* gobj)
{
    ftDk_HeavyWait0_Coll(gobj);
}

void ftDk_MS_345_800E0294(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs2CC(fp);
    Fighter_ChangeMotionState(gobj, donkey_attr->motion_state + 6, 1, 0, 1, 0,
                              NULL);
    ftAnim_SetAnimRate(gobj, 0);
    if (fp->ground_or_air == GA_Ground) {
        ftCommon_8007D5D4(fp);
    }
}
