#include "ftKb_Init.h"
#include "inlines.h"
#include "types.h"

#include <placeholder.h>

#include "ef/efsync.h"
#include "ft/chara/ftCommon/ftCo_FallSpecial.h"
#include "ft/chara/ftCommon/ftCo_Throw.h"
#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0892.h"
#include "ft/ftcolanim.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/ftCo_Landing.h"

#include "ftKirby/forward.h"

#include "ftKirby/ftkirbyspecialdonkey.h"
#include "it/items/itseakneedleheld.h"
#include "it/items/itseakneedlethrown.h"

#include <common_structs.h>
#include <stddef.h>
#include <baselib/gobj.h>
#include <baselib/random.h>
#include <MSL/math.h>

/* 106DB0 */ static void fn_80106DB0(Fighter_GObj*);
/* 3CB770 */ static float ftKb_Init_803CB770[] = {
    -1.0f, -0.75f, -0.5f, -0.25f, 0.0f, +0.25f, +0.5f, +0.75f, +1.0f,
};

void fn_80105FEC(Fighter_GObj* gobj) {}

bool ftKb_SpecialNSk_80105FF0(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (gobj != NULL) {
        if (ft->fv.kb.xB8 != 0) {
            return false;
        }
        return true;
    }
    return true;
}

s32 ftKb_SpecialNSk_80106020(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (gobj != NULL) {
        return ft->fv.kb.xB4;
    }
    return 0;
}

void ftKb_SpecialNSk_8010603C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;

    if (fp->fv.kb.xB8 != NULL) {
        fp->fv.kb.xB8 = NULL;

        while (fp->fv.kb.xB4 != 0) {
            Vec3 pos = fp->cur_pos;
            PAD_STACK(4);
            {
                f32 y_offset;
                if (fp->ground_or_air == GA_Ground) {
                    y_offset = da->specialn_sk_graphic_y_offset_ground;
                } else {
                    y_offset = da->specialn_sk_graphic_y_offset_air;
                }
                pos.y += fp->x34_scale.y * y_offset;
            }
            pos.z = 0.0f;
            {
                Item_GObj* needle =
                    it_802AFD8C(gobj, &pos, 0x98, fp->facing_dir);
                if (needle != NULL) {
                    it_802AFEA8(needle, gobj, 1);
                }
            }
            fp->fv.kb.xB4 -= 1;
        }
    }

    fp->fv.kb.xB4 = 0;
}

void ftKb_SpecialNSk_8010612C(Fighter_GObj* gobj)
{
    int new_var;
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftKb_MS_SkSpecialNStart, 0, 0.0F, 1.0F,
                              0.0F, NULL);
    fp->throw_flags_b0 = false;
    new_var = 0;
    fp->cmd_vars[3] = new_var;
    fp->cmd_vars[2] = new_var;
    fp->cmd_vars[1] = new_var;
    fp->cmd_vars[new_var] = new_var;
    fp->mv.kb.specialhi.x0 = 0;
    if (fp->fv.kb.xB4 == new_var) {
        fp->fv.kb.xB4 = 1;
    }
    fp->mv.kb.specialhi.x4 = 0;
    fp->mv.kb.specialhi.x8.i = 0;
    ftKb_SpecialN_set_cbs(gobj);
    ftAnim_8006EBA4(gobj);
}

void ftKb_SpecialNSk_801061E4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int new_var2;
    int new_var;
    Fighter_ChangeMotionState(gobj, ftKb_MS_SkSpecialAirNStart, 0, 0.0F, 1.0F,
                              0.0F, NULL);
    fp->throw_flags_b0 = (new_var2 = 0);
    fp->cmd_vars[3] = new_var2;
    fp->cmd_vars[2] = 0;
    new_var = 0;
    fp->cmd_vars[1] = new_var;
    fp->cmd_vars[0] = 0;
    fp->mv.kb.specialhi.x0 = 0;
    if (fp->fv.kb.xB4 == 0) {
        fp->fv.kb.xB4 = 1;
    }
    fp->mv.kb.specialhi.x4 = 0;
    fp->mv.kb.specialhi.x8.i = 0;
    ftKb_SpecialN_set_cbs(gobj);
    ftAnim_8006EBA4(gobj);
}

void ftKb_SkSpecialNStart_Anim(Fighter_GObj* gobj)
{
    /// FAKE MATCH: comma operator required for regalloc
    Fighter* fp = (0, GET_FIGHTER(gobj));
    if (!ftAnim_IsFramesRemaining(gobj)) {
        fp->fv.kb.xB8 =
            it_802B19AC(gobj, &fp->cur_pos, 39, 153, fp->facing_dir);
        Fighter_ChangeMotionState(gobj, ftKb_MS_SkSpecialNLoop, 0, 0, 1, 0,
                                  NULL);
        ftKb_SpecialN_set_cbs(gobj);
    }
}

void ftKb_SkSpecialNLoop_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    switch (fp->mv.kb.specialhi.x8.i) {
    case 0: {
        Fighter* fp = GET_FIGHTER(gobj);
        ft_PlaySFX(fp, 270134, 127, 64);
    }
    }
    ++fp->mv.kb.specialhi.x8.i;
    if (fp->cur_anim_frame == 0) {
        ++fp->fv.kb.xB4;
        fp->mv.kb.specialhi.x8.i = 0;
        if (fp->fv.kb.xB4 > 6) {
            fp->fv.kb.xB4 = 6;
            fp->mv.kb.specialhi.x8.i = 100;
            ftCo_800BFFD0(fp, 87, 0);
        }
    }
}

void ftKb_SkSpecialNCancel_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->fv.kb.xB8 = 0;
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ft_8008A2BC(gobj);
    }
}

void ftKb_SkSpecialNEnd_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(4 * 8);
    switch (fp->mv.kb.specialhi.x0) {
    case 2:
    case 5:
    case 8:
    case 11:
    case 14:
    case 17:
        fp->mv.kb.specialhi.x4 = 1;
        fp->fv.kb.xB8 = 0;
    }
    ++fp->mv.kb.specialhi.x0;
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftKb_SkSpecialAirNStart_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_GObj* new_var;
    Fighter_GObj* new_var2;
    new_var = gobj;
    if (!ftAnim_IsFramesRemaining(new_var)) {
        if (new_var) {
        }
        fp->fv.kb.xB8 =
            it_802B19AC(new_var, &fp->cur_pos, 39, 153, fp->facing_dir);
        Fighter_ChangeMotionState(gobj, ftKb_MS_SkSpecialAirNLoop, 0, 0, 1, 0,
                                  NULL);
        new_var2 = gobj;
        ftKb_SpecialN_set_cbs(new_var2);
    }
}

void ftKb_SkSpecialAirNLoop_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    switch (fp->mv.kb.specialhi.x8.i) {
    case 0: {
        Fighter* fp = GET_FIGHTER(gobj);
        ft_PlaySFX(fp, 270134, 127, 64);
    }
    }
    ++fp->mv.kb.specialhi.x8.i;
    if (fp->cur_anim_frame == 0) {
        ++fp->fv.kb.xB4;
        fp->mv.kb.specialhi.x8.i = 0;
        if (fp->fv.kb.xB4 > 6) {
            fp->fv.kb.xB4 = 6;
            fp->mv.kb.specialhi.x8.i = 100;
            ftCo_800BFFD0(fp, 87, 0);
        }
    }
}

void ftKb_SkSpecialAirNCancel_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    /// FAKE MATCH: comma operator required for regalloc
    ftKb_DatAttrs* da = (0, fp->dat_attrs);
    ftKb_DatAttrs* new_var;
    new_var = da;
    fp->fv.kb.xB8 = 0;
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (new_var->specialn_sk_freefall_toggle == 0.0F) {
            ftCo_Fall_Enter(gobj);
        } else {
            ftCo_80096900(gobj, 1, 0, 1, 1.0F,
                          da->specialn_sk_freefall_toggle);
        }
    }
}

void ftKb_SkSpecialAirNEnd_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(4 * 8);
    switch (fp->mv.kb.specialhi.x0) {
    case 2:
    case 5:
    case 8:
    case 11:
    case 14:
    case 17:
        fp->mv.kb.specialhi.x4 = 1;
        fp->fv.kb.xB8 = NULL;
    }
    ++fp->mv.kb.specialhi.x0;
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (da->specialn_sk_freefall_toggle == 0.0F) {
            ftCo_Fall_Enter(gobj);
        } else {
            ftCo_80096900(gobj, 1, 0, 1, 1.0F,
                          da->specialn_sk_freefall_toggle);
        }
    }
}

void ftKb_SkSpecialNStart_IASA(Fighter_GObj* gobj) {}

void ftKb_SkSpecialNLoop_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!(fp->input.held_inputs & HSD_PAD_B)) {
        fp->mv.kb.specialhi.x0 = 0;
        Fighter_ChangeMotionState(gobj, ftKb_MS_SkSpecialNEnd, Ft_MF_None,
                                  0.0F, 1.0F, 0.0F, NULL);
        ftKb_SpecialN_set_cbs(gobj);
        fp->accessory4_cb = fn_80106DB0;
    } else if (fp->input.x668 & HSD_PAD_LR) {
        Fighter_ChangeMotionState(gobj, ftKb_MS_SkSpecialNCancel, Ft_MF_None,
                                  0.0F, 1.0F, 0.0F, NULL);
        ftKb_SpecialN_set_cbs(gobj);
    }
}

void ftKb_SkSpecialNCancel_IASA(Fighter_GObj* gobj) {}

void ftKb_SkSpecialNEnd_IASA(Fighter_GObj* gobj) {}

void ftKb_SkSpecialAirNStart_IASA(Fighter_GObj* gobj) {}

void ftKb_SkSpecialAirNLoop_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!(fp->input.held_inputs & HSD_PAD_B)) {
        fp->mv.kb.specialhi.x0 = 0;
        Fighter_ChangeMotionState(gobj, ftKb_MS_SkSpecialAirNEnd, Ft_MF_None,
                                  0, 1, 0, NULL);
        ftKb_SpecialN_set_cbs(gobj);
        fp->accessory4_cb = fn_80106DB0;
    } else if (fp->input.x668 & HSD_PAD_LR) {
        Fighter_ChangeMotionState(gobj, ftKb_MS_SkSpecialAirNCancel,
                                  Ft_MF_None, 0, 1, 0, NULL);
        ftKb_SpecialN_set_cbs(gobj);
    }
}

void ftKb_SkSpecialAirNCancel_IASA(Fighter_GObj* gobj) {}

void ftKb_SkSpecialAirNEnd_IASA(Fighter_GObj* gobj) {}

void ftKb_SkSpecialNStart_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SkSpecialNLoop_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SkSpecialNCancel_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SkSpecialNEnd_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SkSpecialAirNStart_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_SkSpecialAirNLoop_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_SkSpecialAirNCancel_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_SkSpecialAirNEnd_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_SkSpecialNStart_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_SkSpecialAirNStart,
                                  0x0C4C5080U, fp->cur_anim_frame, 1.0f, 0.0f,
                                  NULL);
        ftKb_SpecialN_set_cbs(gobj);
    }
}

void ftKb_SkSpecialNLoop_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_SkSpecialAirNLoop, 0x0C4C5080U,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
        ftKb_SpecialN_set_cbs(gobj);
    }
}

void ftKb_SkSpecialNCancel_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(8);
    if (ft_80082708(gobj) == GA_Ground) {
        if (da->specialn_sk_freefall_toggle == 0.0F) {
            ftCo_Fall_Enter(gobj);
        } else {
            ftCo_80096900(gobj, 1, 0, 1, 1.0F,
                          da->specialn_sk_freefall_toggle);
        }
    }
}

void ftKb_SkSpecialNEnd_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(16);
    if (ft_80082708(gobj) == GA_Ground) {
        fp->fv.kb.xB4 = 0;
        fp->mv.kb.specialhi.x4 = 0;
        if (da->specialn_sk_freefall_toggle == 0.0F) {
            ftCo_Fall_Enter(gobj);
        } else {
            ftCo_80096900(gobj, 1, 0, 1, 1.0F,
                          da->specialn_sk_freefall_toggle);
        }
    }
}

void ftKb_SkSpecialAirNStart_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_SkSpecialNStart, 0x0C4C5080U,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
        ftKb_SpecialN_set_cbs(gobj);
    }
}

void ftKb_SkSpecialAirNLoop_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_SkSpecialNLoop, 0x0C4C5080U,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
        ftKb_SpecialN_set_cbs(gobj);
    }
}

void ftKb_SkSpecialAirNCancel_Coll(Fighter_GObj* gobj)
{
    FORCE_PAD_STACK_16;

    if (ft_80081D0C(gobj) != GA_Ground) {
        ftCo_Landing_Enter_Basic(gobj);
    }
}

void ftKb_SkSpecialAirNEnd_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(8);
    if (ft_80081D0C(gobj)) {
        fp->fv.kb.xB4 = 0;
        fp->mv.kb.specialhi.x4 = 0;
        ftCo_Landing_Enter_Basic(gobj);
    }
}

// permuter-generated helper, almost certainly fake
static inline s32 perm_randi(int n)
{
    return HSD_Randi(n);
}

void fn_80106DB0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;

    if (fp->mv.kb.specialhi.x4 != 0) {
        fp->mv.kb.specialhi.x4 = 0;
        if (fp->fv.kb.xB4 > 0) {
            Vec3 pos = fp->cur_pos;
            PAD_STACK(4);
            if (fp->ground_or_air == GA_Ground) {
                pos.x +=
                    fp->x34_scale.y *
                    (da->specialn_sk_graphic_x_offset_ground * fp->facing_dir);
                pos.y += fp->x34_scale.y *
                         (da->specialn_sk_graphic_y_offset_ground +
                          ftKb_Init_803CB770[perm_randi(9)]);
            } else {
                pos.x +=
                    fp->x34_scale.y *
                    (da->specialn_sk_graphic_x_offset_air * fp->facing_dir);
                pos.y += fp->x34_scale.y *
                         (2.0f * ftKb_Init_803CB770[perm_randi(9)] +
                          da->specialn_sk_graphic_y_offset_air);
            }
            pos.z = 0.0f;
            {
                Item_GObj* needle =
                    it_802AFD8C(gobj, &pos, 0x98, fp->facing_dir);
                if (needle != NULL) {
                    it_802AFEA8(needle, gobj, 0);
                }
            }
            fp->fv.kb.xB4 -= 1;
            efSync_Spawn(0x503, gobj, &pos);
            ft_PlaySFX(fp, 0x41F3C, 127, 64);
        }
    }
}
