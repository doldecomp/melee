#include "ftKb_Init.h"

#include "ft/chara/ftCommon/ftCo_FallSpecial.h"
#include "ft/chara/ftCommon/ftpickupitem.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ftcommon.h"
#include "ftCommon/ftCo_Fall.h"
#include "it/items/itlinkarrow.h"
#include "it/items/itlinkbow.h"
#include "lb/lb_00B0.h"

#include <lb/lbrefract.h>

static inline void ftKb_SpecialN_set_cbs(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->death2_cb = ftKb_Init_800EE74C;
    fp->take_dmg_cb = ftKb_Init_800EE7B8;
}

ftLk_SpecialNIndex ftKb_SpecialNLk800FB394(Fighter_GObj* gobj)
{
    ftLk_SpecialNIndex idx = ftLk_SpecialNIndex_None;
    if (gobj != NULL) {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp != NULL && fp->fv.kb.x78 != 0) {
            switch (fp->fv.kb.hat.kind) {
            case FTKIND_LINK:
                switch (fp->motion_id) {
                case ftKb_MS_LkSpecialNStart:
                case ftKb_MS_LkSpecialNLoop:
                case ftKb_MS_LkSpecialNEnd:
                case ftKb_MS_LkSpecialAirNStart:
                case ftKb_MS_LkSpecialAirNLoop:
                case ftKb_MS_LkSpecialAirNEnd:
                    idx = fp->motion_id - ftKb_MS_LkSpecialNStart;
                }
                break;
            case FTKIND_CLINK:
                switch (fp->motion_id) {
                case ftKb_MS_ClSpecialNStart:
                case ftKb_MS_ClSpecialNLoop:
                case ftKb_MS_ClSpecialNEnd:
                case ftKb_MS_ClSpecialAirNStart:
                case ftKb_MS_ClSpecialAirNLoop:
                case ftKb_MS_ClSpecialAirNEnd:
                    idx = fp->motion_id - ftKb_MS_ClSpecialNStart;
                }
                break;
            }
        }
    }
    return idx;
}

void ftKb_SpecialNLk800FB418(Fighter_GObj* gobj)
{
    if (gobj != NULL) {
        Fighter* ft = GET_FIGHTER(gobj);
        if ((ft != NULL) && (ft->fv.kb.x74 != 0)) {
            ft->fv.kb.x74 = 0;
        }
    }
}

void ftKb_SpecialNLk800FB444(Fighter_GObj* gobj)
{
    if (gobj != NULL) {
        Fighter* ft = GET_FIGHTER(gobj);
        if ((ft != NULL) && (ft->fv.kb.x78 != 0)) {
            ft->fv.kb.x78 = 0;
        }
    }
}

static MotionFlags const ftKb_SpecialNLk_mf =
    Ft_MF_SkipModel | Ft_MF_SkipItemVis;

static MotionFlags const ftKb_SpecialNLk_coll_mf =
    Ft_MF_SkipModel | Ft_MF_SkipMatAnim | Ft_MF_SkipColAnim | Ft_MF_UpdateCmd |
    Ft_MF_SkipItemVis | Ft_MF_Unk19 | Ft_MF_SkipModelPartVis |
    Ft_MF_SkipModelFlags | Ft_MF_Unk27;

static inline void ftKb_SpecialNLk_setCallbacks(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->take_dmg_cb = ftKb_SpecialNLk800FB880;
    fp->death2_cb = ftKb_SpecialNLk800FBA00;
}

static inline float ftKb_SpecialNLk_GetMaxCharge(Fighter* fp)
{
    ftKb_DatAttrs* da = fp->dat_attrs;
    switch (fp->fv.kb.hat.kind) {
    case FTKIND_LINK:
        return da->specialn_lk_max_charge;
    case FTKIND_CLINK:
        return da->specialn_cl_max_charge;
    }
    return 0;
}

static inline float ftKb_SpecialNLk_GetFreefallToggle(Fighter* fp)
{
    ftKb_DatAttrs* da = fp->dat_attrs;
    switch (fp->fv.kb.hat.kind) {
    case FTKIND_LINK:
        return da->specialn_lk_freefall_toggle;
    case FTKIND_CLINK:
        return da->specialn_cl_freefall_toggle;
    }
    return 0;
}

static inline FtMotionId
ftKb_SpecialNLk_GetMsid(Fighter* fp, FtMotionId lk_msid, FtMotionId cl_msid)
{
    switch (fp->fv.kb.hat.kind) {
    case FTKIND_CLINK:
        return cl_msid;
    case FTKIND_LINK:
    default:
        return lk_msid;
    }
}

static inline void ftKb_SpecialNLk_UnsetArrow(Fighter_GObj* gobj)
{
    if (gobj != NULL) {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp != NULL && fp->fv.kb.x74 != 0) {
            fp->fv.kb.x74 = 0;
        }
    }
}

static inline void ftKb_SpecialNLk_UnsetBow(Fighter_GObj* gobj)
{
    if (gobj != NULL) {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp != NULL && fp->fv.kb.x78 != 0) {
            fp->fv.kb.x78 = 0;
        }
    }
}

bool ftKb_SpecialNLk800FB470(Fighter_GObj* gobj)
{
    if (gobj != NULL) {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp != NULL) {
            switch (fp->fv.kb.hat.kind) {
            case FTKIND_LINK:
                switch (fp->motion_id) {
                case ftKb_MS_LkSpecialNStart:
                case ftKb_MS_LkSpecialNLoop:
                case ftKb_MS_LkSpecialNEnd:
                case ftKb_MS_LkSpecialAirNStart:
                case ftKb_MS_LkSpecialAirNLoop:
                case ftKb_MS_LkSpecialAirNEnd:
                    if (!fp->x2070.x2071_b6) {
                        return false;
                    }
                }
                break;
            case FTKIND_CLINK:
                switch (fp->motion_id) {
                case ftKb_MS_ClSpecialNStart:
                case ftKb_MS_ClSpecialNLoop:
                case ftKb_MS_ClSpecialNEnd:
                case ftKb_MS_ClSpecialAirNStart:
                case ftKb_MS_ClSpecialAirNLoop:
                case ftKb_MS_ClSpecialAirNEnd:
                    if (!fp->x2070.x2071_b6) {
                        return false;
                    }
                }
                break;
            }
        }
    }
    return true;
}

bool ftKb_SpecialNLk800FB500(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    if (fp->cmd_vars[0] == 1 && fp->fv.kb.x74 == 0) {
        Vec3 pos;
        s32 loader_id;
        u8 _[4];
        fp->cmd_vars[0] = 0;
        lb_8000B1CC(fp->parts[FtPart_RHandN].joint, NULL, &pos);
        switch (fp->fv.kb.hat.kind) {
        case FTKIND_LINK:
            loader_id = da->specialn_lk_bow_item_loader_id;
            break;
        case FTKIND_CLINK:
            loader_id = da->specialn_cl_bow_item_loader_id;
            break;
        }
        if ((fp->fv.kb.x74 = it_802A83E0(fp->facing_dir, gobj, &pos,
                                         FtPart_RHandN, loader_id)) != NULL)
        {
            ftKb_SpecialN_set_cbs(gobj);
        } else {
            return true;
        }
    }
    return false;
}

bool ftKb_SpecialNLk800FB5F4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    if (fp->fv.kb.x78 == 0) {
        Vec3 pos;
        s32 item_id;
        u8 _[4];
        lb_8000B1CC(fp->parts[FtPart_R3rdNa].joint, NULL, &pos);
        switch (fp->fv.kb.hat.kind) {
        case FTKIND_LINK:
            item_id = da->specialn_lk_bow_item_id;
            break;
        case FTKIND_CLINK:
            item_id = da->specialn_cl_bow_item_id;
            break;
        }
        if ((fp->fv.kb.x78 = it_802AF1A4(fp->facing_dir, gobj, &pos,
                                         FtPart_R3rdNa, item_id)) != NULL)
        {
            ftKb_SpecialN_set_cbs(gobj);
        } else {
            return true;
        }
    } else {
        return true;
    }
    return false;
}

void ftKb_SpecialNLk800FB6DC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    f32 max;
    PAD_STACK(24);

    if (fp->cmd_vars[1] == 1 && fp->fv.kb.x74 != NULL) {
        Vec3 pos1, pos2;
        Item_GObj* saved_item;
        u8 _[12];
        fp->cmd_vars[1] = 0;
        lb_8000B1CC(fp->parts[44].joint, NULL, &pos1);
        lb_8000B1CC(fp->parts[39].joint, NULL, &pos2);
        pos2.z = 0.0f;
        pos1.z = 0.0f;
        saved_item = fp->item_gobj;
        switch (fp->fv.kb.hat.kind) {
        case FTKIND_LINK:
            max = da->specialn_lk_max_charge;
            break;
        case FTKIND_CLINK:
            max = da->specialn_cl_max_charge;
            break;
        }
        itLinkArrow_802A850C(fp->fv.kb.x74, &pos1, &pos2, 0.08726646f,
                             fp->mv.lk.specialn.x0.y, max);
        ftKb_SpecialNLk_UnsetArrow(gobj);
        fp->item_gobj = saved_item;
        ftpickupitem_80094818(gobj, 0);
    }
}

void ftKb_SpecialNLk800FB800(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(8);
    if (fp->fv.kb.x74 != 0) {
        it_802A8A7C((Item_GObj*) fp->fv.kb.x74);
        fp->fv.kb.x74 = 0;
    }
}

void ftKb_SpecialNLk800FB840(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(8);
    if (fp->fv.kb.x78 != 0) {
        it_802AF304((Item_GObj*) fp->fv.kb.x78);
        fp->fv.kb.x78 = 0;
    }
}

void ftKb_SpecialNLk800FB880(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    ftKirby_MotionState msid;
    f32 anim_rate;
    PAD_STACK(24);
    fp->mv.lk.specialn.x0.y = 0.0F;
    fp->mv.lk.specialn.x0.x = 0.0F;
    fp->mv.lk.specialn.unk_timer = 0;
    fp->cmd_vars[3] = 0;
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    ftCommon_8007D7FC(fp);
    msid = ftKb_MS_LkSpecialNStart;
    fp->self_vel.y = 0.0F;
    switch (GET_FIGHTER(gobj)->fv.kb.hat.kind) {
    case FTKIND_LINK:
        break;
    case FTKIND_CLINK:
        msid = ftKb_MS_ClSpecialNStart;
        break;
    }
    Fighter_ChangeMotionState(gobj, msid, 0, 0.0F, 1.0F, 0.0F, NULL);
    ftKb_SpecialN_set_cbs(gobj);
    switch (fp->fv.kb.hat.kind) {
    case FTKIND_LINK:
        anim_rate = da->specialn_lk_arrow_charge_speed;
        break;
    case FTKIND_CLINK:
        anim_rate = da->specialn_cl_arrow_charge_speed;
        break;
    }
    ftAnim_SetAnimRate(gobj, anim_rate);
    ftAnim_8006EBA4(gobj);
    if (ftKb_SpecialNLk800FB5F4(gobj) == true) {
        ftKb_SpecialNLk_UnsetArrow(gobj);
        ftKb_SpecialNLk_UnsetBow(gobj);
        ft_8008A2BC(gobj);
    }
}

void ftKb_SpecialNLk800FBA00(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    ftKirby_MotionState msid = ftKb_MS_LkSpecialAirNStart;
    f32 anim_rate;
    PAD_STACK(24);
    fp->mv.lk.specialn.x0.y = 0.0F;
    fp->mv.lk.specialn.x0.x = 0.0F;
    fp->mv.lk.specialn.unk_timer = 0;
    fp->cmd_vars[3] = 0;
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    switch (GET_FIGHTER(gobj)->fv.kb.hat.kind) {
    case FTKIND_LINK:
        break;
    case FTKIND_CLINK:
        msid = ftKb_MS_ClSpecialAirNStart;
        break;
    }
    Fighter_ChangeMotionState(gobj, msid, 0, 0.0F, 1.0F, 0.0F, NULL);
    ftKb_SpecialN_set_cbs(gobj);
    switch (fp->fv.kb.hat.kind) {
    case FTKIND_LINK:
        anim_rate = da->specialn_lk_arrow_charge_speed;
        break;
    case FTKIND_CLINK:
        anim_rate = da->specialn_cl_arrow_charge_speed;
        break;
    }
    ftAnim_SetAnimRate(gobj, anim_rate);
    ftAnim_8006EBA4(gobj);
    if (ftKb_SpecialNLk800FB5F4(gobj) == true) {
        ftKb_SpecialNLk_UnsetArrow(gobj);
        ftKb_SpecialNLk_UnsetBow(gobj);
        switch (fp->fv.kb.hat.kind) {
        case FTKIND_LINK:
            anim_rate = da->specialn_lk_freefall_toggle;
            break;
        case FTKIND_CLINK:
            anim_rate = da->specialn_cl_freefall_toggle;
            break;
        }
        if (anim_rate == 0.0F) {
            ftCo_Fall_Enter(gobj);
            return;
        }
        ftCo_80096900(gobj, 1, 0, 1, 1.0F, anim_rate);
    }
}

extern ftLk_SpecialN_Vec3Group const ftKb_Init_803B7548;

void ftKb_LkSpecialNStart_Anim(Fighter_GObj* gobj)
{
    const ftLk_SpecialN_Vec3Group* vg = &ftKb_Init_803B7548;
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    f32 anim_rate;
    Vec3 c, b, a;
    PAD_STACK(24);
    if (fp->cmd_vars[2] != 0 && fp->mv.lk.specialn.x0.x == 0.0F) {
        fp->mv.lk.specialn.x0.x = 1.0F;
        fp->cmd_vars[2] = 0;
    }
    switch (fp->fv.kb.hat.kind) {
    case FTKIND_LINK:
        anim_rate = da->specialn_lk_arrow_charge_speed;
        break;
    case FTKIND_CLINK:
        anim_rate = da->specialn_cl_arrow_charge_speed;
        break;
    }
    ftAnim_SetAnimRate(gobj, anim_rate);
    if (ftKb_SpecialNLk800FB500(gobj) == false) {
        Fighter* fp2 = GET_FIGHTER(gobj);
        a = vg->a;
        b = vg->b;
        c = vg->c;
        fp2->mv.lk.specialn.x8.y = b.x - c.x;
        fp2->mv.lk.specialn.x8.z = b.y - c.y;
        fp2->mv.lk.specialn.x14 = 0.0F;
        fp2->mv.lk.specialn.x8.x = atan2f(b.y - a.y, b.x - a.x);
        if (fp2->fv.kb.x74 != 0) {
            it_802A8398((Item_GObj*) fp2->fv.kb.x74, &b, &a);
        }
        if (!ftAnim_IsFramesRemaining(gobj)) {
            ftKirby_MotionState msid = ftKb_MS_LkSpecialNLoop;
            switch (GET_FIGHTER(gobj)->fv.kb.hat.kind) {
            case FTKIND_LINK:
                break;
            case FTKIND_CLINK:
                msid = ftKb_MS_ClSpecialNLoop;
                break;
            }
            Fighter_ChangeMotionState(gobj, msid, 0x40010, 0.0F, 1.0F, 0.0F,
                                      NULL);
            ftKb_SpecialN_set_cbs(gobj);
            ftAnim_8006EBA4(gobj);
        }
    } else {
        ftKb_SpecialNLk_UnsetArrow(gobj);
        ftKb_SpecialNLk_UnsetBow(gobj);
        ft_8008A2BC(gobj);
    }
}

extern ftLk_SpecialN_Vec3Group const ftKb_Init_803B7548;

void ftKb_LkSpecialNLoop_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 c, b, a;
    a = ftKb_Init_803B7548.a;
    b = ftKb_Init_803B7548.b;
    c = ftKb_Init_803B7548.c;
    fp->mv.lk.specialn.x8.y = b.x - c.x;
    fp->mv.lk.specialn.x8.z = b.y - c.y;
    fp->mv.lk.specialn.x14 = 0.0F;
    fp->mv.lk.specialn.x8.x = atan2f(b.y - a.y, b.x - a.x);
    if (fp->fv.kb.x74 != 0) {
        it_802A8398((Item_GObj*) fp->fv.kb.x74, &b, &a);
    }
}

void ftKb_LkSpecialNEnd_Anim(Fighter_GObj* gobj)
{
    Fighter_GObj* new_var;
    if (!ftAnim_IsFramesRemaining(gobj)) {
        new_var = gobj;
        ftKb_SpecialNLk_UnsetBow(new_var);
        ft_8008A2BC(gobj);
    }
}

void ftKb_LkSpecialAirNStart_Anim(Fighter_GObj* gobj)
{
    const ftLk_SpecialN_Vec3Group* vg = &ftKb_Init_803B7548;
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    f32 anim_rate;
    Vec3 c, b, a;
    PAD_STACK(24);
    if (fp->cmd_vars[2] != 0 && fp->mv.lk.specialn.x0.x == 0.0F) {
        fp->mv.lk.specialn.x0.x = 1.0F;
        fp->cmd_vars[2] = 0;
    }
    if (ftKb_SpecialNLk800FB500(gobj) == false) {
        fp = GET_FIGHTER(gobj);
        a = vg->a;
        b = vg->b;
        c = vg->c;
        fp->mv.lk.specialn.x8.y = b.x - c.x;
        fp->mv.lk.specialn.x8.z = b.y - c.y;
        fp->mv.lk.specialn.x14 = 0.0F;
        fp->mv.lk.specialn.x8.x = atan2f(b.y - a.y, b.x - a.x);
        if (fp->fv.kb.x74 != 0) {
            it_802A8398((Item_GObj*) fp->fv.kb.x74, &b, &a);
        }
        if (!ftAnim_IsFramesRemaining(gobj)) {
            ftKirby_MotionState msid = ftKb_MS_LkSpecialAirNLoop;
            switch (GET_FIGHTER(gobj)->fv.kb.hat.kind) {
            case FTKIND_LINK:
                break;
            case FTKIND_CLINK:
                msid = ftKb_MS_ClSpecialAirNLoop;
                break;
            }
            Fighter_ChangeMotionState(gobj, msid, 0x40010, 0.0F, 1.0F, 0.0F,
                                      NULL);
            ftKb_SpecialN_set_cbs(gobj);
            ftAnim_8006EBA4(gobj);
        }
    } else {
        ftKb_SpecialNLk_UnsetArrow(gobj);
        ftKb_SpecialNLk_UnsetBow(gobj);
        switch (fp->fv.kb.hat.kind) {
        case FTKIND_LINK:
            anim_rate = da->specialn_lk_freefall_toggle;
            break;
        case FTKIND_CLINK:
            anim_rate = da->specialn_cl_freefall_toggle;
            break;
        }
        if (anim_rate == 0.0F) {
            ftCo_Fall_Enter(gobj);
            return;
        }
        ftCo_80096900(gobj, 1, 0, 1, 1.0F, anim_rate);
    }
}

void ftKb_LkSpecialAirNLoop_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 c, b, a;
    a = ftKb_Init_803B7548.a;
    b = ftKb_Init_803B7548.b;
    c = ftKb_Init_803B7548.c;
    fp->mv.lk.specialn.x8.y = b.x - c.x;
    fp->mv.lk.specialn.x8.z = b.y - c.y;
    fp->mv.lk.specialn.x14 = 0.0F;
    fp->mv.lk.specialn.x8.x = atan2f(b.y - a.y, b.x - a.x);
    if (fp->fv.kb.x74 != 0) {
        it_802A8398((Item_GObj*) fp->fv.kb.x74, &b, &a);
    }
}

void ftKb_LkSpecialAirNEnd_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftKb_DatAttrs* da = fp->dat_attrs;
    float freefall;
    PAD_STACK(24);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftKb_SpecialNLk_UnsetArrow(gobj);
        ftKb_SpecialNLk_UnsetBow(gobj);
        switch (fp->fv.kb.hat.kind) {
        case FTKIND_LINK:
            freefall = da->specialn_lk_freefall_toggle;
            break;
        case FTKIND_CLINK:
            freefall = da->specialn_cl_freefall_toggle;
            break;
        }
        if (freefall == 0.0f) {
            ftCo_Fall_Enter(gobj);
        } else {
            ftCo_80096900(gobj, 1, 0, true, 1.0f, freefall);
        }
    }
}

void ftKb_LkSpecialNStart_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(8);
    if (fp->mv.lk.specialn.x0.x != 0) {
        f32 max;
        fp->mv.lk.specialn.x0.y += 1.0f;
        switch (fp->fv.kb.hat.kind) {
        case FTKIND_LINK:
            max = da->specialn_lk_max_charge;
            break;
        case FTKIND_CLINK:
            max = da->specialn_cl_max_charge;
            break;
        }
        if (fp->mv.lk.specialn.x0.y > max) {
            fp->mv.lk.specialn.x0.y = max;
        }
        if (!(fp->input.held_inputs & HSD_PAD_B)) {
            s32 msid = ftKb_MS_LkSpecialNEnd;
            switch (GET_FIGHTER(gobj)->fv.kb.hat.kind) {
            case FTKIND_LINK:
                break;
            case FTKIND_CLINK:
                msid = ftKb_MS_ClSpecialNEnd;
                break;
            }
            Fighter_ChangeMotionState(gobj, msid, 0x40010, 0.0f, 1.0f, 0.0f,
                                      NULL);
            ftKb_SpecialN_set_cbs(gobj);
        }
    }
}

void ftKb_LkSpecialNLoop_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(8);
    switch (fp->fv.kb.hat.kind) {
    case FTKIND_LINK:
        fp->mv.lk.specialn.x0.y = da->specialn_lk_max_charge;
        break;
    case FTKIND_CLINK:
        fp->mv.lk.specialn.x0.y = da->specialn_cl_max_charge;
        break;
    }
    if (!(fp->input.held_inputs & HSD_PAD_B)) {
        s32 msid = ftKb_MS_LkSpecialNEnd;
        switch (GET_FIGHTER(gobj)->fv.kb.hat.kind) {
        case FTKIND_LINK:
            break;
        case FTKIND_CLINK:
            msid = ftKb_MS_ClSpecialNEnd;
            break;
        }
        Fighter_ChangeMotionState(gobj, msid, 0x40010, 0.0f, 1.0f, 0.0f, NULL);
        ftKb_SpecialN_set_cbs(gobj);
    }
}

void ftKb_LkSpecialNEnd_IASA(Fighter_GObj* gobj) {}

void ftKb_LkSpecialAirNStart_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(8);
    if (fp->mv.lk.specialn.x0.x != 0) {
        f32 max;
        fp->mv.lk.specialn.x0.y += 1.0f;
        switch (fp->fv.kb.hat.kind) {
        case FTKIND_LINK:
            max = da->specialn_lk_max_charge;
            break;
        case FTKIND_CLINK:
            max = da->specialn_cl_max_charge;
            break;
        }
        if (fp->mv.lk.specialn.x0.y > max) {
            fp->mv.lk.specialn.x0.y = max;
        }
        if (!(fp->input.held_inputs & HSD_PAD_B)) {
            s32 msid = ftKb_MS_LkSpecialAirNEnd;
            switch (GET_FIGHTER(gobj)->fv.kb.hat.kind) {
            case FTKIND_LINK:
                break;
            case FTKIND_CLINK:
                msid = ftKb_MS_ClSpecialAirNEnd;
                break;
            }
            Fighter_ChangeMotionState(gobj, msid, 0x40010, 0.0f, 1.0f, 0.0f,
                                      NULL);
            ftKb_SpecialN_set_cbs(gobj);
        }
    }
}

void ftKb_LkSpecialAirNLoop_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(8);
    switch (fp->fv.kb.hat.kind) {
    case FTKIND_LINK:
        fp->mv.lk.specialn.x0.y = da->specialn_lk_max_charge;
        break;
    case FTKIND_CLINK:
        fp->mv.lk.specialn.x0.y = da->specialn_cl_max_charge;
        break;
    }
    if (!(fp->input.held_inputs & HSD_PAD_B)) {
        s32 msid = ftKb_MS_LkSpecialAirNEnd;
        switch (GET_FIGHTER(gobj)->fv.kb.hat.kind) {
        case FTKIND_LINK:
            break;
        case FTKIND_CLINK:
            msid = ftKb_MS_ClSpecialAirNEnd;
            break;
        }
        Fighter_ChangeMotionState(gobj, msid, 0x40010, 0.0f, 1.0f, 0.0f, NULL);
        ftKb_SpecialN_set_cbs(gobj);
    }
}

void ftKb_LkSpecialAirNEnd_IASA(Fighter_GObj* gobj) {}

void ftKb_LkSpecialNStart_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_LkSpecialNLoop_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_LkSpecialNEnd_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_LkSpecialAirNStart_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_LkSpecialAirNLoop_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_LkSpecialAirNEnd_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_LkSpecialNStart_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(8);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        {
            s32 msid = ftKb_MS_LkSpecialAirNStart;
            f32 anim_frame = fp->cur_anim_frame;
            switch (GET_FIGHTER(gobj)->fv.kb.hat.kind) {
            case FTKIND_LINK:
                break;
            case FTKIND_CLINK:
                msid = ftKb_MS_ClSpecialAirNStart;
                break;
            }
            Fighter_ChangeMotionState(gobj, msid, 0x0C4C5090, anim_frame, 1.0f,
                                      0.0f, NULL);
        }
        ftKb_SpecialN_set_cbs(gobj);
        ftAnim_8006EBA4(gobj);
    }
}

void ftKb_LkSpecialNLoop_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(8);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        {
            s32 msid = ftKb_MS_LkSpecialAirNLoop;
            f32 anim_frame = fp->cur_anim_frame;
            switch (GET_FIGHTER(gobj)->fv.kb.hat.kind) {
            case FTKIND_LINK:
                break;
            case FTKIND_CLINK:
                msid = ftKb_MS_ClSpecialAirNLoop;
                break;
            }
            Fighter_ChangeMotionState(gobj, msid, 0x0C4C5090, anim_frame, 1.0f,
                                      0.0f, NULL);
        }
        ftKb_SpecialN_set_cbs(gobj);
        ftAnim_8006EBA4(gobj);
    }
}

void ftKb_LkSpecialNEnd_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(8);
    ftKb_SpecialNLk800FB6DC(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        {
            s32 msid = ftKb_MS_LkSpecialAirNEnd;
            f32 anim_frame = fp->cur_anim_frame;
            switch (GET_FIGHTER(gobj)->fv.kb.hat.kind) {
            case FTKIND_LINK:
                break;
            case FTKIND_CLINK:
                msid = ftKb_MS_ClSpecialAirNEnd;
                break;
            }
            Fighter_ChangeMotionState(gobj, msid, 0x0C4C5090, anim_frame, 1.0f,
                                      0.0f, NULL);
        }
        ftKb_SpecialN_set_cbs(gobj);
        ftAnim_8006EBA4(gobj);
    }
}

void ftKb_LkSpecialAirNStart_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(8);
    if (ft_80081D0C(gobj) == GA_Air) {
        ftCommon_8007D7FC(fp);
        {
            s32 msid = ftKb_MS_LkSpecialNStart;
            f32 anim_frame = fp->cur_anim_frame;
            switch (GET_FIGHTER(gobj)->fv.kb.hat.kind) {
            case FTKIND_LINK:
                break;
            case FTKIND_CLINK:
                msid = ftKb_MS_ClSpecialNStart;
                break;
            }
            Fighter_ChangeMotionState(gobj, msid, 0x0C4C5090, anim_frame, 1.0f,
                                      0.0f, NULL);
        }
        ftKb_SpecialN_set_cbs(gobj);
        ftAnim_8006EBA4(gobj);
    }
}

void ftKb_LkSpecialAirNLoop_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(8);
    if (ft_80081D0C(gobj) == GA_Air) {
        ftCommon_8007D7FC(fp);
        {
            s32 msid = ftKb_MS_LkSpecialNLoop;
            f32 anim_frame = fp->cur_anim_frame;
            switch (GET_FIGHTER(gobj)->fv.kb.hat.kind) {
            case FTKIND_LINK:
                break;
            case FTKIND_CLINK:
                msid = ftKb_MS_ClSpecialNLoop;
                break;
            }
            Fighter_ChangeMotionState(gobj, msid, 0x0C4C5090, anim_frame, 1.0f,
                                      0.0f, NULL);
        }
        ftKb_SpecialN_set_cbs(gobj);
        ftAnim_8006EBA4(gobj);
    }
}

void ftKb_LkSpecialAirNEnd_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(8);
    ftKb_SpecialNLk800FB6DC(gobj);
    if (ft_80081D0C(gobj) == GA_Air) {
        ftCommon_8007D7FC(fp);
        {
            s32 msid = ftKb_MS_LkSpecialNEnd;
            f32 anim_frame = fp->cur_anim_frame;
            switch (GET_FIGHTER(gobj)->fv.kb.hat.kind) {
            case FTKIND_LINK:
                break;
            case FTKIND_CLINK:
                msid = ftKb_MS_ClSpecialNEnd;
                break;
            }
            Fighter_ChangeMotionState(gobj, msid, 0x0C4C5090, anim_frame, 1.0f,
                                      0.0f, NULL);
        }
        ftKb_SpecialN_set_cbs(gobj);
        ftAnim_8006EBA4(gobj);
    }
}
