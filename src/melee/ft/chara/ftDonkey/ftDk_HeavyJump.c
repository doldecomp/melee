#include "ftDk_HeavyJump.h"

#include "ftDk_HeavyFall.h"

#include "ft/fighter.h"
#include "ft/ftanim.h"
#include "ft/types.h"
#include "ftCommon/ftCo_ItemThrow.h"
#include "ftCommon/ftCo_Jump.h"
#include "ftDonkey/types.h"

void ftDk_HeavyJump_IASA(HSD_GObj* gobj)
{
    RETURN_IF(ftCo_80094EA4(gobj));
}

void ftDk_HeavyJump_Phys(HSD_GObj* gobj)
{
    ftCo_Jump_Phys_Inner(gobj);
}

void ftDk_HeavyJump_Coll(HSD_GObj* gobj)
{
    ftDk_HeavyFall_Coll(gobj);
}

void ftDk_MS_348_800E04A4(HSD_GObj* gobj, s32 arg1)
{
    /// @todo #GET_FIGHTER
    Fighter* fp = gobj->user_data;
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs2CC(fp);
    ftDonkeyAttributes* donkey_attr2;
    fp->mv.dk.unk7.x4 = arg1;
    fp->mv.dk.unk7.x0 = 0;
    fp->mv.dk.unk7.x8 = donkey_attr->cargo_hold.x24_JUMP_STARTUP_LAG;
    donkey_attr2 = getFtSpecialAttrs2CC(fp);
    Fighter_ChangeMotionState(gobj, donkey_attr2->motion_state + 5, 0, 0, 1, 0,
                              NULL);
    ftAnim_SetAnimRate(gobj, 0);
}

void ftDk_HeavyWait1_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->mv.dk.unk7.x8 <= 0) {
        ftDk_MS_347_800E03C0(gobj);
    }
    fp->mv.dk.unk7.x8 -= 1;
}
