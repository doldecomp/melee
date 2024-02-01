#include <platform.h>
#include <dolphin/mtx/forward.h>

#include "ftPp_SpecialN.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ft_0C88.h"
#include "ft/ft_0D14.h"
#include "ft/ftanim.h"
#include "ft/types.h"
#include "ftPopo/types.h"
#include "it/items/it_27CF.h"

#include <common_structs.h>
#include <placeholder.h>
#include <baselib/gobj.h>

/* 11F500 */ static void ftPp_SpecialN_8011F500(HSD_GObj* gobj);

void ftPp_SpecialN_Enter(HSD_GObj* gobj)
{
    Fighter* fp = (Fighter*) HSD_GObjGetUserData(gobj);
    fp->throw_flags = 0;
    fp->cmd_vars[0] = 0;
    fp->fv.nn.x222C = 0;

    Fighter_ChangeMotionState(gobj, 341, 0, 0.0f, 1.0f, 0.0f, NULL);

    ftAnim_8006EBA4(gobj);
    fp->accessory4_cb = &ftPp_SpecialN_8011F500;
}

void ftPp_SpecialAirN_Enter(HSD_GObj* gobj)
{
    u8 _[4];

    Fighter* fp = (Fighter*) HSD_GObjGetUserData(gobj);
    ftIceClimberAttributes* icattr = fp->dat_attrs;

    fp->throw_flags = 0;
    fp->cmd_vars[0] = 0;
    fp->fv.nn.x222C = 0;

    if ((s32) fp->fv.nn.x224C == false) {
        fp->self_vel.y = icattr->x4;
        fp->fv.nn.x224C = true;
        fp->fv.nn.x2250 = 0.0f;
    } else {
        fp->fv.nn.x2250 = -10.0;
    }

    Fighter_ChangeMotionState(gobj, 342, 0, 0.0f, 1.0f, 0.0f, NULL);

    ftAnim_8006EBA4(gobj);
    fp->accessory4_cb = &ftPp_SpecialN_8011F500;
}

void ftPp_SpecialN_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftPp_SpecialAirN_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_800CC730(gobj);
    }
}

void ftPp_SpecialN_IASA(HSD_GObj* arg0) {}

void ftPp_SpecialAirN_IASA(HSD_GObj* arg0) {}

void ftPp_SpecialN_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftPp_SpecialAirN_Phys(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftPp_SpecialN_Coll(HSD_GObj* gobj)
{
    if (!ft_80082708(gobj)) {
        Fighter* fp1;
        fp1 = GET_FIGHTER(gobj);
        if (fp1->fv.nn.x222C != 0U) {
            Fighter* fp2;
            it_802C17DC(fp1->fv.nn.x222C);
            fp2 = GET_FIGHTER(gobj);
            if ((u32) fp1->fv.nn.x222C == (u32) fp2->fv.nn.x222C) {
                fp2->fv.nn.x222C = 0U;
                fp2->death2_cb = 0U;
                fp2->take_dmg_cb = 0U;
            }
        }
        ftCo_800CC730(gobj);
    }
}

void ftPp_SpecialAirN_Coll(Fighter_GObj* gobj)
{
    Fighter *fp, *fp1, *fp2;
    ftIceClimberAttributes* da;
    u8 _[16];

    fp = gobj->user_data;
    da = fp->dat_attrs;
    if (ft_80081D0C(gobj) != GA_Ground) {
        fp1 = gobj->user_data;
        if (fp1->fv.pp.x222C != 0) {
            it_802C17DC(fp1->fv.pp.x222C);
            fp2 = gobj->user_data;
            if (fp1->fv.pp.x222C == fp2->fv.pp.x222C) {
                fp2->fv.pp.x222C = 0U;
                fp2->death2_cb = NULL;
                fp2->take_dmg_cb = NULL;
            }
        }
        fp->fv.pp.x224C = 0;
        fp->fv.pp.x2250 = 0.0f;
        ftCo_800D5CB0(gobj, 0, da->x8);
    }
}

static void ftPp_SpecialN_8011F500(HSD_GObj* gobj)
{
    NOT_IMPLEMENTED;
}
