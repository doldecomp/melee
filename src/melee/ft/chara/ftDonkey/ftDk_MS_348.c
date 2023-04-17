#include "ftDk_MS_348.h"

#include "ftDk_MS_347.h"
#include "ftdonkey.h"

#include "ft/ft_0877.h"
#include "ft/inlines.h"

void ftDk_MS_348_IASA(HSD_GObj* gobj)
{
    s32 result = ft_80094EA4(gobj);
    if (result) {
        return;
    }
}

void ftDk_MS_348_Phys(HSD_GObj* gobj)
{
    ft_800CB438(gobj);
}

void ftDk_MS_348_Coll(HSD_GObj* gobj)
{
    ftDk_MS_347_Coll(gobj);
}

void ftDk_MS_348_800E04A4(HSD_GObj* gobj, s32 arg1)
{
    Fighter* fp = gobj->user_data;
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs2CC(fp);
    ftDonkeyAttributes* donkey_attr2;
    fp->mv.dk.unk7.x4 = arg1;
    fp->mv.dk.unk7.x0 = 0;
    fp->mv.dk.unk7.x8 = donkey_attr->cargo_hold.x24_JUMP_STARTUP_LAG;
    donkey_attr2 = getFtSpecialAttrs2CC(fp);

    Fighter_ChangeMotionState(gobj, donkey_attr2->motion_state + 5, 0, NULL,
                              0.0f, 1.0f, 0.0f);
    ftAnim_SetAnimRate(gobj, 0.0f);
}

void ftDk_MS_346_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->mv.dk.unk7.x8 <= 0.0f) {
        ftDk_MS_347_800E03C0(gobj);
    }
    fp->mv.dk.unk7.x8 -= 1.0f;
}
