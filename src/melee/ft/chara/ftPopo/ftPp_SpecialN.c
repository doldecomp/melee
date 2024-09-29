#include <platform.h>
#include <placeholder.h>

#include "it/forward.h"
#include <dolphin/mtx/forward.h>

#include "ftPp_SpecialN.h"

#include "ftPp_Init.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0881.h"
#include "ft/ft_0892.h"
#include "ft/ft_0C88.h"
#include "ft/ft_0D14.h"
#include "ft/ftanim.h"
#include "ft/types.h"
#include "ftPopo/types.h"
#include "it/items/it_27CF.h"
#include "it/items/itclimbersice.h"
#include "lb/lb_00B0.h"

#include <common_structs.h>
#include <baselib/gobj.h>

/* 11F500 */ static void ftPp_SpecialN_8011F500(Fighter_GObj* gobj);

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

static inline void inlineA0(Fighter_GObj* gobj, Fighter* other_fp)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (other_fp->fv.pp.x222C == fp->fv.pp.x222C) {
        fp->fv.pp.x222C = NULL;
        fp->death2_cb = NULL;
        fp->take_dmg_cb = NULL;
    }
}

static inline void inlineA1(Item_GObj* item_gobj, Fighter* fp) {}

void ftPp_SpecialN_8011F500(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    uint cmd_var0 = fp->cmd_vars[0];

    if (cmd_var0 == 0) {
        return;
    }
    if (cmd_var0 == 1) {
        ftIceClimberAttributes* da = fp->dat_attrs;
        Vec3 pos;
        PAD_STACK(4 * 2);
        lb_8000B1CC(fp->parts[0].joint, NULL, &pos);
        pos.x = da->xC * fp->facing_dir + pos.x;
        pos.y += da->x10 + fp->fv.pp.x2250;
        fp->fv.pp.x222C = it_802C1590(gobj, &pos, 106, fp->facing_dir);
        ft_80088148(fp, 130021, 127, 64);
        if (fp->fv.pp.x222C != NULL) {
            fp->death2_cb = ftPp_Init_8011F060;
            fp->take_dmg_cb = ftPp_Init_8011F060;
        }
        fp->cmd_vars[0] = 0;
    } else if (cmd_var0 == 2) {
        if (fp->fv.pp.x222C != NULL) {
            it_802C16F8(fp->fv.pp.x222C);
            fp->cmd_vars[0] = 0;
            if (fp->kind == FTKIND_POPO) {
                ft_800881D8(fp, 130141, 127, 64);
            } else {
                ft_800881D8(fp, 130090, 127, 64);
            }
            ft_80088148(fp, 130024, 127, 64);
            inlineA0(gobj, fp);
        }
    }
}
