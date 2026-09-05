#include "ftdonkeyheavywait1.h"

#include "ftdonkeyheavywait0.h"
#include "types.h"

#include <melee/ft/ft_084E.h>
#include <melee/ft/ftanim.h>
#include <melee/ft/inlines.h>
#include <melee/ft/kinds/ftCommon/ftCo_ItemThrow.h>
#include <melee/ft/kinds/ftCommon/ftCo_KneeBend.h>
#include <melee/ft/kinds/ftCommon/ftCo_Landing.h>
#include <melee/ft/types.h>

void ftDk_HeavyWait1_IASA(HSD_GObj* gobj)
{
    if (!ftCo_80094EA4(gobj)) {
        ftCo_KneeBend_Check_ShortHop(gobj);
    }
}

void ftDk_HeavyWait1_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftDk_HeavyWait1_Coll(HSD_GObj* gobj)
{
    ftDk_HeavyWait0_Coll(gobj);
}

void ftDk_MS_346_800E05E4(HSD_GObj* gobj)
{
    /// @todo #GET_FIGHTER
    Fighter* fp = gobj->user_data;
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs2CC(fp);
    fp->mv.dk.unk8.x4 = donkey_attr->cargo_hold.x28_LANDING_LAG;
    donkey_attr = getFtSpecialAttrs2CC(fp);
    ftCo_Landing_Enter(gobj, donkey_attr->motion_state + 8, true, Ft_MF_None,
                       0.0F, 1.0F);
    ftAnim_SetAnimRate(gobj, 0);
}

void ftDk_HeavyLanding_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->mv.dk.unk8.x4 <= 0) {
        ftDk_MS_341_800DF980(gobj);
    }
    fp->mv.dk.unk8.x4 -= 1;
}
