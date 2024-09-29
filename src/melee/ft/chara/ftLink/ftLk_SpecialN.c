#include <platform.h>

#include "ftLink/forward.h"
#include "it/forward.h"
#include <dolphin/mtx/forward.h>

#include "ftLk_SpecialN.h"

#include "ftLk_Init.h"
#include "math.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ft_0C88.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "ftCommon/ftCo_FallSpecial.h"
#include "ftCommon/ftpickupitem.h"
#include "ftLink/types.h"
#include "it/items/it_27CF.h"
#include "it/items/itlinkarrow.h"
#include "it/items/itlinkbow.h"
#include "lb/lb_00B0.h"
#include "lb/lbrefract.h"

#include <common_structs.h>

static float const ftLk_Init_804D9340 = 0.0;
static float const ftLk_Init_804D9344 = 5 * deg_to_rad;
static double const ftLk_Init_804D9348 = 0.0078125;

typedef enum cmd_var_idx {
    cmd_unk0_bool,
    cmd_unk1_bool,
    cmd_unk2,
    cmd_unk3,
} cmd_var_idx;

ftLk_SpecialNIndex ftLk_SpecialN_GetIndex(ftLk_GObj* gobj)
{
    ftLk_SpecialNIndex result = ftLk_SpecialNIndex_None;
    if (gobj != NULL) {
        ftLk_Fighter* fp = GET_FIGHTER(gobj);
        if (fp != NULL && fp->fv.lk.x14 != NULL) {
            FtMotionId msid = fp->motion_id;
            switch (msid) {
            case ftLk_MS_SpecialNStart:
            case ftLk_MS_SpecialNLoop:
            case ftLk_MS_SpecialNEnd:
            case ftLk_MS_SpecialAirNStart:
            case ftLk_MS_SpecialAirNLoop:
            case ftLk_MS_SpecialAirNEnd:
                result = msid - ftLk_MS_SpecialNStart;
            }
        }
    }
    return result;
}

void ftLk_SpecialN_UnsetArrow(ftLk_GObj* gobj)
{
    if (gobj != NULL) {
        ftLk_Fighter* fp = GET_FIGHTER(gobj);
        if (fp != NULL && fp->fv.lk.arrow_gobj != NULL) {
            fp->fv.lk.arrow_gobj = NULL;
            if (fp->fv.lk.boomerang_gobj == NULL && fp->fv.lk.x14 == NULL) {
                /// @todo Does this actually do anything? Doesn't seem to
                /// return @c bool.
                ftLk_Init_BoomerangExists(gobj);
            }
        }
    }
}

void ftLk_SpecialN_UnsetFv14(ftLk_GObj* gobj)
{
    if (gobj != NULL) {
        ftLk_Fighter* fp = GET_FIGHTER(gobj);
        if (fp != NULL && fp->fv.lk.x14 != NULL) {
            fp->fv.lk.x14 = NULL;
            if (fp->fv.lk.boomerang_gobj == NULL &&
                fp->fv.lk.arrow_gobj == NULL)
            {
                /// @todo Does this actually do anything? Doesn't seem to
                /// return @c bool.
                ftLk_Init_BoomerangExists(gobj);
            }
        }
    }
}

bool ftLk_SpecialN_IsActiveAnd2071b6(ftLk_GObj* gobj)
{
    ftLk_Fighter* fp = GET_FIGHTER(gobj);
    switch (fp->motion_id) {
    case ftLk_MS_SpecialNStart:
    case ftLk_MS_SpecialNLoop:
    case ftLk_MS_SpecialNEnd:
    case ftLk_MS_SpecialAirNStart:
    case ftLk_MS_SpecialAirNLoop:
    case ftLk_MS_SpecialAirNEnd:
        if (!fp->x2070.x2071_b6) {
            return false;
        }
        /// @attention Fall-through.
    default:
        return true;
    }
}

void ftLk_SpecialN_ProcessFv10(ftLk_GObj* gobj)
{
    u8 _[8];
    ftLk_Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.lk.arrow_gobj != NULL) {
        it_802A8A7C(fp->fv.lk.arrow_gobj);
        fp->fv.lk.arrow_gobj = NULL;
        ftLk_Init_BoomerangExists(gobj);
    }
}

void ftLk_SpecialN_ProcessFv14(ftLk_GObj* gobj)
{
    u8 _[8];
    ftLk_Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.lk.x14 != NULL) {
        it_802AF304(fp->fv.lk.x14);
        fp->fv.lk.x14 = NULL;
        ftLk_Init_BoomerangExists(gobj);
    }
}

static inline void setCallbacks(ftLk_GObj* gobj)
{
    ftLk_Fighter* fp = GET_FIGHTER(gobj);
    fp->take_dmg_cb = ftLk_800EAF58;
    fp->death2_cb = ftLk_800EAF58;
}

static inline bool unkCondition(ftLk_GObj* gobj)
{
    ftLk_Fighter* fp = GET_FIGHTER(gobj);
    ftLk_DatAttrs* da = fp->dat_attrs;
    if (fp->fv.lk.x14 == NULL) {
        u8 _[36] = { 0 };
        Vec3 pos;
        lb_8000B1CC(fp->parts[ftParts_8007500C(fp, FtPart_RThumbNb)].joint,
                    NULL, &pos);
        {
            Item_GObj* fv_x14 =
                it_802AF1A4(fp->facing_dir, gobj, &pos,
                            ftParts_8007500C(fp, FtPart_RThumbNb), da->x10);
            fp->fv.lk.x14 = fv_x14;
            if (fv_x14 != NULL) {
                setCallbacks(gobj);
            } else {
                return true;
            }
        }
    } else {
        return true;
    }
    return false;
}

void ftLk_SpecialN_Enter(ftLk_GObj* gobj)
{
    /// @todo #GET_FIGHTER
    ftLk_Fighter* fp = gobj->user_data;
    ftLk_DatAttrs* da = fp->dat_attrs;
    fp->mv.lk.specialn.x0.x = fp->mv.lk.specialn.x0.y = 0;
    fp->mv.lk.specialn.unk_timer = 0;
    fp->cmd_vars[0] = fp->cmd_vars[1] = fp->cmd_vars[2] = fp->cmd_vars[3] = 0;
    ftCommon_8007D7FC(fp);
    fp->self_vel.y = 0;
    Fighter_ChangeMotionState(gobj, ftLk_MS_SpecialNStart, Ft_MF_None, 0, 1, 0,
                              NULL);
    setCallbacks(gobj);
    ftAnim_SetAnimRate(gobj, da->specialn_anim_rate);
    ftAnim_8006EBA4(gobj);
    if (unkCondition(gobj) == true) {
        ftLk_SpecialN_UnsetArrow(gobj);
        ftLk_SpecialN_UnsetFv14(gobj);
        ft_8008A2BC(gobj);
    }
}

/// @todo Share more code with #ftLk_SpecialN_Enter.
void ftLk_SpecialAirN_Enter(ftLk_GObj* gobj)
{
    /// @todo #GET_FIGHTER
    ftLk_Fighter* fp = gobj->user_data;
    ftLk_DatAttrs* da = fp->dat_attrs;
    fp->mv.lk.specialn.x0.x = fp->mv.lk.specialn.x0.y = 0;
    fp->mv.lk.specialn.unk_timer = 0;
    fp->cmd_vars[0] = fp->cmd_vars[1] = fp->cmd_vars[2] = fp->cmd_vars[3] = 0;
    Fighter_ChangeMotionState(gobj, ftLk_MS_SpecialAirNStart, Ft_MF_None, 0, 1,
                              0, NULL);
    setCallbacks(gobj);
    ftAnim_SetAnimRate(gobj, da->specialn_anim_rate);
    ftAnim_8006EBA4(gobj);
    if (unkCondition(gobj) == true) {
        ftLk_SpecialN_UnsetArrow(gobj);
        ftLk_SpecialN_UnsetFv14(gobj);
        if (da->x8 == 0) {
            ftCo_800CC730(gobj);
        } else {
            ftCo_80096900(gobj, 1, 0, 1, 1, da->x8);
        }
    }
}

static inline bool foo(ftLk_GObj* gobj)
{
    ftLk_Fighter* fp = GET_FIGHTER(gobj);
    ftLk_DatAttrs* da = fp->dat_attrs;
    if (fp->cmd_vars[cmd_unk0_bool] == 1 && fp->fv.lk.arrow_gobj == NULL) {
        fp->cmd_vars[cmd_unk0_bool] = 0;
        {
            Vec3 vec3;
            lb_8000B1CC(fp->parts[ftParts_8007500C(fp, FtPart_LThumbNb)].joint,
                        NULL, &vec3);
            {
                Item_GObj* arrow_gobj =
                    it_802A83E0(fp->facing_dir, gobj, &vec3,
                                ftParts_8007500C(fp, FtPart_LThumbNb), da->xC);
                fp->fv.lk.arrow_gobj = arrow_gobj;
                if (arrow_gobj != NULL) {
                    setCallbacks(gobj);
                    return false;
                }
            }
        }
        return true;
    }
    return false;
}

MotionFlags const mf = Ft_MF_SkipModel | Ft_MF_SkipItemVis;

static inline void bar(ftLk_GObj* gobj)
{
    u8 _[0x20] = { 0 };
    ftLk_Fighter* fp = GET_FIGHTER(gobj);
    ftLk_SpecialN_Vec3Group vecs = ftLk_Init_Vec3Group;
    lb_8000B1CC(fp->parts[ftParts_8007500C(fp, FtPart_LThumbNb)].joint, NULL,
                &vecs.a);
    lb_8000B1CC(fp->parts[ftParts_8007500C(fp, FtPart_RThumbNb)].joint, NULL,
                &vecs.b);
    lb_8000B1CC(fp->parts->joint, NULL, &vecs.c);
    fp->mv.lk.specialn.x8.x = vecs.b.x - vecs.c.x;
    fp->mv.lk.specialn.x8.y = vecs.b.y - vecs.c.y;
    fp->mv.lk.specialn.x8.z = 0;
    fp->mv.lk.specialn.x8.x = atan2f(vecs.b.y - vecs.a.y, vecs.b.x - vecs.a.x);
    if (fp->fv.lk.arrow_gobj != NULL) {
        it_802A8398(fp->fv.lk.arrow_gobj, &vecs.b, &vecs.a);
    }
    if (ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(gobj, ftLk_MS_SpecialNLoop, mf, 0, 1, 0,
                                  NULL);
        setCallbacks(gobj);
        ftAnim_8006EBA4(gobj);
    }
}

static inline void baz(ftLk_GObj* gobj)
{
    ftLk_Fighter* fp = GET_FIGHTER(gobj);
    ftLk_DatAttrs* da = fp->dat_attrs;
    if (fp->cmd_vars[cmd_unk2] && fp->mv.lk.specialn.x0.x == 0) {
        fp->mv.lk.specialn.x0.x = 1;
        fp->cmd_vars[cmd_unk2] = 0;
    }
    ftAnim_SetAnimRate(gobj, da->specialn_anim_rate);
}

void ftLk_SpecialNStart_Anim(ftLk_GObj* gobj)
{
    baz(gobj);
    if (!foo(gobj)) {
        bar(gobj);
    } else {
        ftLk_SpecialN_UnsetArrow(gobj);
        ftLk_SpecialN_UnsetFv14(gobj);
        ft_8008A2BC(gobj);
    }
}

void ftLk_SpecialNLoop_Anim(ftLk_GObj* gobj)
{
    ftLk_Fighter* fp = GET_FIGHTER(gobj);
    ftLk_SpecialN_Vec3Group vecs = ftLk_Init_Vec3Group;
    lb_8000B1CC(fp->parts[ftParts_8007500C(fp, FtPart_LThumbNb)].joint, NULL,
                &vecs.a);
    lb_8000B1CC(fp->parts[ftParts_8007500C(fp, FtPart_RThumbNb)].joint, NULL,
                &vecs.b);
    lb_8000B1CC(fp->parts->joint, NULL, &vecs.c);
    fp->mv.lk.specialn.x8.x = vecs.b.x - vecs.c.x;
    fp->mv.lk.specialn.x8.y = vecs.b.y - vecs.c.y;
    fp->mv.lk.specialn.x8.z = 0;
    fp->mv.lk.specialn.x8.x = atan2f(vecs.b.y - vecs.a.y, vecs.b.x - vecs.a.x);
    if (fp->fv.lk.arrow_gobj != NULL) {
        it_802A8398(fp->fv.lk.arrow_gobj, &vecs.b, &vecs.a);
    }
}

static void setupParts(ftLk_GObj* gobj, bool arg1)
{
    ftParts_80074A4C(gobj, 2, arg1);
    ftParts_80074B0C(gobj, 2, arg1);
}

static void updateParts(ftLk_GObj* gobj)
{
    ftLk_Fighter* fp = GET_FIGHTER(gobj);
    if (fp->x221E_b3 == true && fp->mv.lk.specialn.unk_timer == 0) {
        ++fp->mv.lk.specialn.unk_timer;
        if (fp->item_gobj != NULL) {
            setupParts(gobj, true);
        } else {
            setupParts(gobj, false);
        }
    }
}

void ftLk_SpecialNEnd_Anim(ftLk_GObj* gobj)
{
    u8 _[8];
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftLk_SpecialN_UnsetFv14(gobj);
        updateParts(gobj);
        ft_8008A2BC(gobj);
    } else {
        updateParts(gobj);
    }
}

void ftLk_SpecialAirNStart_Anim(ftLk_GObj* gobj)
{
    ftLk_Fighter* fp = GET_FIGHTER(gobj);
    ftLk_DatAttrs* da = fp->dat_attrs;
    if (fp->cmd_vars[cmd_unk1_bool] && fp->mv.lk.specialn.x0.x == 0) {
        fp->mv.lk.specialn.x0.x = 0;
        fp->cmd_vars[cmd_unk1_bool] = false;
    }
    if (!unkCondition(gobj)) {
        ftLk_Fighter* fp = GET_FIGHTER(gobj);
        ftLk_SpecialN_Vec3Group vecs = ftLk_Init_Vec3Group;
        lb_8000B1CC(fp->parts[ftParts_8007500C(fp, FtPart_LThumbNb)].joint,
                    NULL, &vecs.a);
        lb_8000B1CC(fp->parts[ftParts_8007500C(fp, FtPart_RThumbNb)].joint,
                    NULL, &vecs.b);
        lb_8000B1CC(fp->parts->joint, NULL, &vecs.c);
        fp->mv.lk.specialn.x8.x = vecs.b.x - vecs.c.x;
        fp->mv.lk.specialn.x8.y = vecs.b.y - vecs.c.y;
        fp->mv.lk.specialn.x8.x =
            atan2f(vecs.b.y - vecs.a.y, vecs.b.x - vecs.a.x);
        if (fp->fv.lk.arrow_gobj != NULL) {
            it_802A8398(fp->fv.lk.arrow_gobj, &vecs.b, &vecs.a);
        }
        if (!ftAnim_IsFramesRemaining(gobj)) {
            Fighter_ChangeMotionState(gobj, ftLk_MS_SpecialAirNLoop, mf, 0, 1,
                                      0, NULL);
            setCallbacks(gobj);
            ftAnim_8006EBA4(gobj);
        }
    } else {
        ftLk_SpecialN_UnsetArrow(gobj);
        ftLk_SpecialN_UnsetFv14(gobj);
        if (da->x8 == 0) {
            ftCo_800CC730(gobj);
        } else {
            ftCo_80096900(gobj, 1, 0, 1, 1, da->x8);
        }
    }
}

void ftLk_SpecialAirNLoop_Anim(ftLk_GObj* gobj)
{
    ftLk_Fighter* fp = GET_FIGHTER(gobj);
    ftLk_SpecialN_Vec3Group vecs = ftLk_Init_Vec3Group;
    lb_8000B1CC(fp->parts[ftParts_8007500C(fp, FtPart_LThumbNb)].joint, NULL,
                &vecs.a);
    lb_8000B1CC(fp->parts[ftParts_8007500C(fp, FtPart_RThumbNb)].joint, NULL,
                &vecs.b);
    lb_8000B1CC(fp->parts->joint, NULL, &vecs.c);
    fp->mv.lk.specialn.x8.x = vecs.b.x - vecs.c.x;
    fp->mv.lk.specialn.x8.y = vecs.b.y - vecs.c.y;
    fp->mv.lk.specialn.x8.x = atan2f(vecs.b.y - vecs.a.y, vecs.b.x - vecs.a.x);
    if (fp->fv.lk.arrow_gobj != NULL) {
        it_802A8398(fp->fv.lk.arrow_gobj, &vecs.b, &vecs.a);
    }
}

void ftLk_SpecialAirNEnd_Anim(ftLk_GObj* gobj)
{
    u8 _[16];
    ftLk_Fighter* fp = GET_FIGHTER(gobj);
    ftLk_DatAttrs* da = fp->dat_attrs;
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftLk_SpecialN_UnsetArrow(gobj);
        ftLk_SpecialN_UnsetFv14(gobj);
        updateParts(gobj);
        if (da->x8 == 0) {
            ftCo_800CC730(gobj);
        } else {
            ftCo_80096900(gobj, 1, 0, 1, 1, da->x8);
        }
    } else {
        updateParts(gobj);
    }
}

void ftLk_SpecialNStart_IASA(ftLk_GObj* gobj)
{
    ftLk_Fighter* fp = GET_FIGHTER(gobj);
    ftLk_DatAttrs* da = fp->dat_attrs;
    if (fp->mv.lk.specialn.x0.x != 0) {
        fp->mv.lk.specialn.x0.y += 1;
        if (fp->mv.lk.specialn.x0.y > da->x0) {
            fp->mv.lk.specialn.x0.y = da->x0;
        }
        /// @todo Shared with #ftLk_SpecialNLoop_IASA
        if (!(fp->input.held_inputs & HSD_PAD_B)) {
            Fighter_ChangeMotionState(gobj, ftLk_MS_SpecialNEnd, mf, 0, 1, 0,
                                      NULL);
            setCallbacks(gobj);
        }
    }
}

static void doLoopIASA(ftLk_GObj* gobj, FtMotionId msid)
{
    ftLk_Fighter* fp = GET_FIGHTER(gobj);
    ftLk_DatAttrs* da = fp->dat_attrs;
    fp->mv.lk.specialn.x0.y = da->x0;
    if (!(fp->input.held_inputs & HSD_PAD_B)) {
        Fighter_ChangeMotionState(gobj, msid, mf, 0, 1, 0, NULL);
        setCallbacks(gobj);
    }
}

void ftLk_SpecialNLoop_IASA(ftLk_GObj* gobj)
{
    u8 _[8];
    doLoopIASA(gobj, ftLk_MS_SpecialNEnd);
}

void ftLk_SpecialNEnd_IASA(ftLk_GObj* gobj) {}

void ftLk_SpecialAirNStart_IASA(ftLk_GObj* gobj)
{
    /// @todo Same as #ftLk_SpecialNStart_IASA with different MSID
    ftLk_Fighter* fp = GET_FIGHTER(gobj);
    ftLk_DatAttrs* da = fp->dat_attrs;
    if (fp->mv.lk.specialn.x0.x != 0) {
        fp->mv.lk.specialn.x0.y += 1;
        if (fp->mv.lk.specialn.x0.y > da->x0) {
            fp->mv.lk.specialn.x0.y = da->x0;
        }
        if (!(fp->input.held_inputs & HSD_PAD_B)) {
            Fighter_ChangeMotionState(gobj, ftLk_MS_SpecialAirNEnd, mf, 0, 1,
                                      0, NULL);
            setCallbacks(gobj);
        }
    }
}

void ftLk_SpecialAirNLoop_IASA(ftLk_GObj* gobj)
{
    doLoopIASA(gobj, ftLk_MS_SpecialAirNLoop);
}

void ftLk_SpecialAirNEnd_IASA(ftLk_GObj* gobj) {}

void ftLk_SpecialNStart_Phys(ftLk_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftLk_SpecialNLoop_Phys(ftLk_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftLk_SpecialNEnd_Phys(ftLk_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftLk_SpecialAirNStart_Phys(ftLk_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftLk_SpecialAirNLoop_Phys(ftLk_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftLk_SpecialAirNEnd_Phys(ftLk_GObj* gobj)
{
    ft_80084EEC(gobj);
}

static MotionFlags const coll_mf =
    Ft_MF_SkipModel | Ft_MF_SkipMatAnim | Ft_MF_SkipColAnim | Ft_MF_UpdateCmd |
    Ft_MF_SkipItemVis | Ft_MF_Unk19 | Ft_MF_SkipModelPartVis |
    Ft_MF_SkipModelFlags | Ft_MF_Unk27;

static void doColl(ftLk_GObj* gobj, FtMotionId msid)
{
    ftLk_Fighter* fp = GET_FIGHTER(gobj);
    if (!ft_80082708(gobj)) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, msid, coll_mf, fp->cur_anim_frame, 1,
                                  0, NULL);
        setCallbacks(gobj);
        ftAnim_8006EBA4(gobj);
    }
}

void ftLk_SpecialNStart_Coll(ftLk_GObj* gobj)
{
    doColl(gobj, ftLk_MS_SpecialAirNStart);
}

void ftLk_SpecialNLoop_Coll(ftLk_GObj* gobj)
{
    doColl(gobj, ftLk_MS_SpecialAirNLoop);
}

static inline void doEndColl(ftLk_GObj* gobj)
{
    u8 _[12] = { 0 };
    ftLk_Fighter* fp = GET_FIGHTER(gobj);
    ftLk_DatAttrs* da = fp->dat_attrs;
    Item_GObj* item_gobj;
    if (fp->cmd_vars[cmd_unk1_bool] == true && fp->fv.lk.arrow_gobj != NULL) {
        fp->cmd_vars[cmd_unk1_bool] = false;
        {
            Vec3 rpos, lpos;
            lb_8000B1CC(fp->parts[ftParts_8007500C(fp, FtPart_RThumbNb)].joint,
                        NULL, &rpos);
            lb_8000B1CC(fp->parts[ftParts_8007500C(fp, FtPart_LThumbNb)].joint,
                        NULL, &lpos);
            rpos.z = lpos.z = 0;
            item_gobj = fp->item_gobj;
            it_802A850C(fp->fv.lk.arrow_gobj, &rpos, &lpos, 5 * deg_to_rad,
                        fp->mv.lk.specialn.x0.y, da->x0);
            ftLk_SpecialN_UnsetArrow(gobj);
            fp->item_gobj = item_gobj;
        }
        ftpickupitem_80094818(gobj, false);
    }
}

void ftLk_SpecialNEnd_Coll(ftLk_GObj* gobj)
{
    ftLk_Fighter* fp = GET_FIGHTER(gobj);
    doEndColl(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftLk_MS_SpecialAirNEnd, coll_mf,
                                  fp->cur_anim_frame, 1, 0, NULL);
        setCallbacks(gobj);
        ftAnim_8006EBA4(gobj);
    }
}

static void doAirColl(ftLk_GObj* gobj, FtMotionId msid)
{
    ftLk_Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) == GA_Air) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, msid, coll_mf, fp->cur_anim_frame, 1,
                                  0, NULL);
        setCallbacks(gobj);
        ftAnim_8006EBA4(gobj);
    }
}

void ftLk_SpecialAirNStart_Coll(ftLk_GObj* gobj)
{
    doAirColl(gobj, ftLk_MS_SpecialNStart);
}

void ftLk_SpecialAirNLoop_Coll(ftLk_GObj* gobj)
{
    doAirColl(gobj, ftLk_MS_SpecialNLoop);
}

/// @todo Combine with #ftLk_SpecialNEnd_Coll.
void ftLk_SpecialAirNEnd_Coll(ftLk_GObj* gobj)
{
    u8 _[8] = { 0 };
    ftLk_Fighter* fp = GET_FIGHTER(gobj);
    doEndColl(gobj);
    if (ft_80081D0C(gobj) == GA_Air) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftLk_MS_SpecialNEnd, coll_mf,
                                  fp->cur_anim_frame, 1, 0, NULL);
        setCallbacks(gobj);
        ftAnim_8006EBA4(gobj);
    }
}
