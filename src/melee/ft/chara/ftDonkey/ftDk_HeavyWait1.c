#include "ftDk_HeavyWait1.h"

#include "ftDk_HeavyWait0.h"

#include "ft/ft_081B.h"
#include "ft/ft_0C88.h"
#include "ft/ft_0D14.h"
#include "ft/ftanim.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCommon/ftCo_ItemThrow.h"
#include "ftDonkey/types.h"

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
    ftCo_800D5AEC(gobj, donkey_attr->motion_state + 8, 1, 0, 0, 1);
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
