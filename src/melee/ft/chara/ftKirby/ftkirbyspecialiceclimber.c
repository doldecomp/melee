#include "ftkirbyspecialiceclimber.h"

#include "ftkirby.h"
#include "types.h"

#include <placeholder.h>

#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0881.h"
#include "ft/ft_0892.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/ftCo_Landing.h"

#include "ftKirby/forward.h"

#include "ftKirby/ftkirbyspecialdonkey.h"
#include "it/items/itclimbersice.h"
#include "lb/lb_00B0.h"

#include <common_structs.h>
#include <stddef.h>
#include <baselib/gobj.h>
#include <baselib/random.h>
#include <MSL/math.h>

/* 1090D4 */ static void fn_801090D4(Fighter_GObj*);

void ftKb_SpecialNIc_80108CE8(Fighter_GObj* gobj, Item_GObj* it_gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (it_gobj == ft->fv.kb.xC0) {
        ft->fv.kb.xC0 = NULL;
    }
}

void ftKb_SpecialNIc_80108D04(HSD_GObj* gobj)
{
    Fighter* fp = HSD_GObjGetUserData(gobj);
    PAD_STACK(8);
    if (fp->fv.kb.xC0 != NULL) {
        it_802C17DC(fp->fv.kb.xC0);
        {
            Fighter* fp2 = GET_FIGHTER(gobj);
            if (fp->fv.kb.xC0 == fp2->fv.kb.xC0) {
                fp2->fv.kb.xC0 = NULL;
            }
        }
    }
}

void ftKb_SpecialNIc_80108D64(Fighter_GObj* gobj)
{
    int new_var;
    Fighter* fp = GET_FIGHTER(gobj);
    new_var = 0;
    fp->throw_flags = 0;
    fp->cmd_vars[0] = new_var;
    ((Fighter*) fp)->fv.kb.xC0 = NULL;
    Fighter_ChangeMotionState(gobj, ftKb_MS_PpSpecialN, 0, 0.0F, 1.0F, 0.0F,
                              NULL);
    ftAnim_8006EBA4(gobj);
    fp->accessory4_cb = fn_801090D4;
    {
        Fighter* fp2 = GET_FIGHTER(gobj);
        ftCommon_SetAccessory(
            fp2,
            (HSD_Joint*) (&ft_80459B88)->hats[FTKIND_PEACH]->hat_dynamics[1]);
        lb_8000C2F8(
            fp2->x20A0_accessory,
            fp2->parts[ftParts_GetBoneIndex(fp2, FtPart_LThumbNb)].joint);
    }
}

void ftKb_SpecialNIc_80108E14(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    fp->throw_flags = 0;
    fp->cmd_vars[0] = 0;
    fp->fv.kb.xC0 = NULL;
    if ((s32) fp->fv.kb.xC4 == 0) {
        fp->self_vel.y = da->specialn_pp_air_vertical_momentum;
        fp->fv.kb.xC4 = true;
        fp->fv.kb.xC8 = 0.0F;
    } else {
        fp->fv.kb.xC8 = -10.0F;
    }
    Fighter_ChangeMotionState(gobj, ftKb_MS_PpSpecialAirN, 0, 0.0F, 1.0F, 0.0F,
                              NULL);
    ftAnim_8006EBA4(gobj);
    fp->accessory4_cb = fn_801090D4;
    {
        Fighter* fp2 = GET_FIGHTER(gobj);
        ftCommon_SetAccessory(
            fp2, (HSD_Joint*) ft_80459B88.hats[FTKIND_PEACH]->hat_dynamics[1]);
        lb_8000C2F8(
            fp2->x20A0_accessory,
            fp2->parts[ftParts_GetBoneIndex(fp2, FtPart_LThumbNb)].joint);
    }
}

void ftKb_PpSpecialN_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftKb_PpSpecialAirN_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

void ftKb_PpSpecialN_IASA(Fighter_GObj* gobj) {}

void ftKb_PpSpecialAirN_IASA(Fighter_GObj* gobj) {}

void ftKb_PpSpecialN_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_PpSpecialAirN_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_PpSpecialN_Coll(Fighter_GObj* gobj)
{
    if (!ft_80082708(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp->fv.kb.xC0 != NULL) {
            it_802C17DC(fp->fv.kb.xC0);
            {
                Fighter* fp2 = GET_FIGHTER(gobj);
                if (fp->fv.kb.xC0 == fp2->fv.kb.xC0) {
                    fp2->fv.kb.xC0 = NULL;
                }
            }
        }
        ftCo_Fall_Enter(gobj);
    }
}

void ftKb_PpSpecialAirN_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    if (ft_80081D0C(gobj) != GA_Ground) {
        Fighter* fp1 = GET_FIGHTER(gobj);
        if (fp1->fv.kb.xC0 != NULL) {
            it_802C17DC(fp1->fv.kb.xC0);
            {
                Fighter* fp2 = GET_FIGHTER(gobj);
                if (fp1->fv.kb.xC0 == ((0, fp2->fv.kb.xC0))) {
                    fp2->fv.kb.xC0 = NULL;
                }
            }
        }
        fp->fv.kb.xC4 = 0;
        fp->fv.kb.xC8 = 0.0F;
        ftCo_LandingFallSpecial_Enter(gobj, false,
                                      da->specialn_pp_landing_lag);
    }
}

void fn_801090D4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    u32 cmd = fp->cmd_vars[0];
    if (cmd == 0) {
        return;
    }
    if (cmd == 1) {
        ftKb_DatAttrs* da = fp->dat_attrs;
        Vec3 pos;
        PAD_STACK(8);
        lb_8000B1CC(fp->parts[0].joint, NULL, &pos);
        pos.x += da->specialn_pp_x_spawn * fp->facing_dir;
        pos.y += da->specialn_pp_y_spawn + fp->fv.kb.xC8;
        fp->fv.kb.xC0 = it_802C1590(gobj, &pos, 0x85, fp->facing_dir);
        ft_PlaySFX(fp, 0x1FBE5, 127, 64);
        if (fp->fv.kb.xC0 != NULL) {
            fp->death2_cb = (HSD_GObjEvent) ftKb_Init_800EE74C;
            fp->take_dmg_cb = (HSD_GObjEvent) ftKb_Init_800EE7B8;
        }
        fp->cmd_vars[0] = 0;
        return;
    }
    if (cmd == 2) {
        if (fp->fv.kb.xC0 != NULL) {
            it_802C16F8(fp->fv.kb.xC0);
            fp->cmd_vars[0] = 0;
            ft_800881D8(fp, 0x2233B, 127, 64);
            ft_PlaySFX(fp, 0x1FBE8, 127, 64);
            {
                Fighter* fp2 = GET_FIGHTER(gobj);
                if (fp->fv.kb.xC0 == fp2->fv.kb.xC0) {
                    fp2->fv.kb.xC0 = NULL;
                }
            }
        }
    }
}

Fighter_Part ftKb_SpecialNYs_80109238(Fighter_GObj* gobj)
{
    return ftParts_GetBoneIndex(GET_FIGHTER(gobj), FtPart_TransN2);
}
