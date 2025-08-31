#include "ftYs_SpecialN.h"

#include "placeholder.h"

#include <placeholder.h>

#include "baselib/forward.h"

#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ftCommon/ftCo_Attack100.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCommon/ftCo_CaptureCut.h"
#include "ftCommon/ftCo_CaptureYoshi.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/ftCo_Throw.h"
#include "ftCommon/ftCo_YoshiEgg.h"
#include "ftYoshi/ftYs_Init.h"
#include "ftYoshi/types.h"
#include "it/items/it_27CF.h"
#include "it/items/it_2F2B.h"
#include "lb/lb_00B0.h"

#include <dolphin/mtx.h>
#include <baselib/gobj.h>

/* 12CEE0 */ static void fn_8012CEE0(Fighter_GObj*);
/* 12CF7C */ static void fn_8012CF7C(Fighter_GObj*);
/* 12DF00 */ static void ftYs_SpecialS_8012DF00(Fighter_GObj*);

Fighter_Part ftYs_SpecialN_GetBoneIndex(Fighter_GObj* gobj)
{
    return ftParts_GetBoneIndex(GET_FIGHTER(gobj), FtPart_TransN2);
}

void ftYs_SpecialN_SetupItemVel(Fighter_GObj* gobj, Vec3* out)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* da = fp->dat_attrs;
    out->x = -fp->facing_dir * da->x10;
    out->y = da->x14;
    out->z = 0.0f;
}

float ftYs_SpecialN_GetFacingDir(HSD_GObj* gobj)
{
    return GET_FIGHTER(gobj)->facing_dir;
}

float ftYs_SpecialN_GetDatAttr18(HSD_GObj* gobj)
{
    ftYoshiAttributes* da = GET_FIGHTER(gobj)->dat_attrs;
    return da->x18;
}

float ftYs_SpecialN_GetDatAttr1C(HSD_GObj* gobj)
{
    ftYoshiAttributes* da = GET_FIGHTER(gobj)->dat_attrs;
    return da->x1C;
}

float ftYs_SpecialN_GetDatAttr20(HSD_GObj* gobj)
{
    ftYoshiAttributes* da = GET_FIGHTER(gobj)->dat_attrs;
    return da->x20;
}

float ftYs_SpecialN_GetDatAttr24(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftYs_DatAttrs* da = fp->dat_attrs;
    return da->x24;
}

float ftYs_SpecialN_GetExtAttr28(Fighter_GObj* gobj)
{
    ftYoshiAttributes* ext_attr = gFtDataList[FTKIND_YOSHI]->ext_attr;
    return ext_attr->x28;
}

float ftYs_SpecialN_GetExtAttr2C(void)
{
    ftYoshiAttributes* ext_attr = gFtDataList[FTKIND_YOSHI]->ext_attr;
    return ext_attr->x2C;
}

float ftYs_SpecialN_8012CD40(void)
{
    ftYoshiAttributes* ext_attr = gFtDataList[FTKIND_YOSHI]->ext_attr;
    return ext_attr->x30;
}

float ftYs_SpecialN_GetExtAttr34(void)
{
    ftYoshiAttributes* ext_attr = gFtDataList[FTKIND_YOSHI]->ext_attr;
    return ext_attr->x34;
}

int ftYs_SpecialN_GetExtAttr38(void)
{
    ftYoshiAttributes* ext_attr = gFtDataList[FTKIND_YOSHI]->ext_attr;
    return ext_attr->x38;
}

void ftYs_SpecialN_8012CD88(Vec3* arg0)
{
    ftYoshiAttributes* ext_attr = gFtDataList[FTKIND_YOSHI]->ext_attr;
    arg0->x = ext_attr->x3C.x;
    arg0->y = ext_attr->x3C.y;
    arg0->z = 0;
}

float ftYs_SpecialN_8012CDB4(void)
{
    ftYoshiAttributes* ea = gFtDataList[FTKIND_YOSHI]->ext_attr;
    return ea->x44 / ea->x18;
}

HSD_Joint* ftYs_SpecialN_8012CDD4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftData* ca = fp->ft_data;
    return ca->x48_items[3];
}

static void setupCallbacks(Fighter_GObj* gobj, HSD_GObjEvent grab_cb,
                           HSD_GObjEvent arg1,
                           void (*grabbed_cb)(Fighter_GObj* gobj,
                                              Fighter_GObj* attacker_gobj))
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007E2D0(fp, 4, grab_cb, arg1, grabbed_cb);
}

u32 const motion_flags0 = Ft_MF_KeepGfx | Ft_MF_SkipModel | Ft_MF_Unk19;
u32 const motion_flags1 =
    motion_flags0 | Ft_MF_SkipMatAnim | Ft_MF_SkipColAnim;
static u32 const motion_flags2 = motion_flags1 | Ft_MF_KeepGfx |
                                 Ft_MF_SkipModel | Ft_MF_SkipMatAnim |
                                 Ft_MF_SkipColAnim | Ft_MF_Unk19;

static u32 const motion_flags3 = motion_flags2 | Ft_MF_UpdateCmd |
                                 Ft_MF_SkipItemVis | Ft_MF_SkipModelPartVis |
                                 Ft_MF_SkipModelFlags | Ft_MF_Unk27;
static u32 const motion_flags4 = motion_flags3 | Ft_MF_SkipHit;

void ftYs_SpecialN_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[0] = 0;
    Fighter_ChangeMotionState(gobj, ftYs_MS_SpecialN1, Ft_MF_None, 0, 1.0f,
                              0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    setupCallbacks(gobj, fn_8012CF7C, fn_8012CEE0, ftCo_800BBB8C);
}

void ftYs_SpecialAirN_Enter(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[0] = 0;
    Fighter_ChangeMotionState(gobj, ftYs_MS_SpecialAirN1_0, Ft_MF_None, 0.0f,
                              1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    setupCallbacks(gobj, fn_8012D0A0, fn_8012D004, ftCo_800BBB8C);
}

void fn_8012CEE0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    it_802F2BFC(fp->target_item_gobj, gobj);
    Fighter_ChangeMotionState(gobj, ftYs_MS_SpecialN1_1, motion_flags1,
                              fp->cur_anim_frame, 1.0f, 0.0f, NULL);
    fp->x2222_b2 = true;
    fp->mv.ys.specialn.x0_b0 = true;
    ftYs_SpecialS_8012DF00(gobj);
    ftCommon_8007E2F4(fp, 0x1FF);
    ftCommon_8007E2FC(gobj);
}

void fn_8012CF7C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftYs_MS_SpecialN1_0, motion_flags1,
                              fp->cur_anim_frame, 1.0f, 0.0f, NULL);
    fp->x2222_b2 = true;
    fp->mv.ys.specialn.x0_b0 = false;
    ftCommon_8007E2F4(fp, 0x1FF);
    ftCommon_8007E2FC(gobj);
}

void fn_8012D004(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    it_802F2BFC(fp->target_item_gobj, gobj);
    Fighter_ChangeMotionState(gobj, ftYs_MS_SpecialAirN1_2, motion_flags2,
                              fp->cur_anim_frame, 1.0f, 0.0f, NULL);

    fp->x2222_b2 = true;
    fp->mv.ys.specialn.x0_b0 = true;
    ftYs_SpecialS_8012DF00(gobj);
    ftCommon_8007E2F4(fp, 0x1FF);
    ftCommon_8007E2FC(gobj);
}

void fn_8012D0A0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    Fighter_ChangeMotionState(gobj, ftYs_MS_SpecialAirN1_1, motion_flags2,
                              fp->cur_anim_frame, 1.0f, 0.0f, NULL);

    fp->x2222_b2 = true;
    fp->mv.ys.specialn.x0_b0 = false;

    ftCommon_8007E2F4(fp, 0x1FF);
    ftCommon_8007E2FC(gobj);
}

void fn_8012D128(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftYs_MS_SpecialAirN1_0, motion_flags4,
                              fp->cur_anim_frame, 1.0f, 0.0f, NULL);
    setupCallbacks(gobj, fn_8012D0A0, fn_8012D004, ftCo_800BBB8C);
}

void fn_8012D1AC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftYs_MS_SpecialN1, motion_flags4,
                              fp->cur_anim_frame, 1.0f, 0.0f, NULL);
    setupCallbacks(gobj, fn_8012CF7C, fn_8012CEE0, ftCo_800BBB8C);
}

void fn_8012D230(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftYs_MS_SpecialAirN1_2, motion_flags3,
                              fp->cur_anim_frame, 1.0f, 0.0f, NULL);
    ftYs_SpecialS_8012DF00(gobj);
}

void fn_8012D298(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftYs_MS_SpecialAirN1_1, motion_flags3,
                              fp->cur_anim_frame, 1.0f, 0.0f, NULL);
}

void fn_8012D2F8(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftYs_MS_SpecialN1_1, motion_flags3,
                              fp->cur_anim_frame, 1.0f, 0.0f, NULL);
    ftYs_SpecialS_8012DF00(gobj);
}

void fn_8012D360(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftYs_MS_SpecialN1_0, motion_flags3,
                              fp->cur_anim_frame, 1.0f, 0.0f, NULL);
}

void fn_8012D3C0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftYs_MS_SpecialAirN2_1, motion_flags3,
                              fp->cur_anim_frame, 1.0f, 0.0f, NULL);
    ftYs_SpecialS_8012DF00(gobj);
}

void fn_8012D428(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftYs_MS_SpecialAirN2_0, motion_flags3,
                              fp->cur_anim_frame, 1.0f, 0.0f, NULL);
}

void fn_8012D488(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftYs_MS_SpecialN2_1, motion_flags3,
                              fp->cur_anim_frame, 1.0f, 0.0f, NULL);
    ftYs_SpecialS_8012DF00(gobj);
}

void fn_8012D4F0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftYs_MS_SpecialN2_0, motion_flags3,
                              fp->cur_anim_frame, 1.0f, 0.0f, NULL);
}

static void checkAnimEnd(Fighter_GObj* gobj, HSD_GObjEvent cb)
{
    FORCE_PAD_STACK_8;
    if (!ftAnim_IsFramesRemaining(gobj)) {
        cb(gobj);
    }
}

void ftYs_SpecialN1_Anim(Fighter_GObj* gobj)
{
    checkAnimEnd(gobj, ft_8008A2BC);
}

void ftYs_SpecialAirN1_0_Anim(Fighter_GObj* gobj)
{
    checkAnimEnd(gobj, ftCo_Fall_Enter);
}

static void changeMotionState(Fighter_GObj* gobj, enum_t msid,
                              HSD_GObj* (*target_getter)(Fighter* fp),
                              bool arg3)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->cmd_vars[0] && target_getter(fp) != NULL) {
        fp->cmd_vars[0] = 0;
        fp->cmd_vars[1] = 0;
        Fighter_ChangeMotionState(gobj, msid, motion_flags0, 0.0f, 1.0f, 0.0f,
                                  NULL);
        if (arg3) {
            ftYs_SpecialS_8012DF00(gobj);
        }
        ftCommon_8007E2F4(fp, 0x1FF);
    }
}

void ftYs_SpecialN1_1_Anim(Fighter_GObj* gobj)
{
    changeMotionState(gobj, ftYs_MS_SpecialN2_1, getFtTargetItem, true);
}

void ftYs_SpecialN1_0_Anim(Fighter_GObj* gobj)
{
    changeMotionState(gobj, ftYs_MS_SpecialN2_0, getFtVictim, false);
}

void ftYs_SpecialAirN1_2_Anim(Fighter_GObj* gobj)
{
    changeMotionState(gobj, ftYs_MS_SpecialAirN2_1, getFtTargetItem, true);
}

void ftYs_SpecialAirN1_1_Anim(Fighter_GObj* gobj)
{
    changeMotionState(gobj, ftYs_MS_SpecialAirN2_0, getFtVictim, false);
}

static inline void inlineB0(Fighter_GObj* gobj, HSD_GObjEvent on_anim_end)
{
    Fighter* fp = GET_FIGHTER(gobj);
    FORCE_PAD_STACK_32;
    FORCE_PAD_STACK_16;
    {
        it_27CF_DatAttrs item_attrs;
        FORCE_PAD_STACK_8;
        {
            if (fp->cmd_vars[1]) {
                if (fp->target_item_gobj != NULL) {
                    it_802F2CE0(fp->target_item_gobj, false);
                    fp->target_item_gobj = fp->x1A64 = NULL;
                    fp->cmd_vars[1] = 0;
                }
            }
            if (fp->cmd_vars[0] && fp->mv.ys.specialn.x0_b0) {
                ftCommon_8007E2F4(fp, 0);
                {
                    {
                        Fighter* fp = GET_FIGHTER(gobj);
                        lb_8000B1CC(
                            fp->parts[ftYs_SpecialN_GetBoneIndex(gobj)].joint,
                            NULL, &item_attrs.pos);
                    }
                    ftYs_SpecialN_SetupItemVel(gobj, &item_attrs.vel);
                    item_attrs.float2 = ftYs_SpecialN_GetFacingDir(gobj);
                    item_attrs.lifetime = ftYs_SpecialN_GetDatAttr24(gobj);
                    item_attrs.x24 = ftYs_SpecialN_GetDatAttr18(gobj);
                    item_attrs.float3 = ftYs_SpecialN_8012CDB4();
                    item_attrs.kind = 87;
                    it_802F2F34(gobj, &item_attrs);
                    fp->mv.ys.specialn.x0_b0 = false;
                    fp->cmd_vars[0] = 0;
                }
            }
            if (!ftAnim_IsFramesRemaining(gobj)) {
                on_anim_end(gobj);
            }
        }
    }
}

void ftYs_SpecialN2_1_Anim(Fighter_GObj* gobj)
{
    inlineB0(gobj, ft_8008A2BC);
}

static void inlineA0(Fighter* fp)
{
    Fighter_GObj* victim_gobj = getFtVictim(fp);
    if (victim_gobj != NULL) {
        ftCo_800BBC88(victim_gobj);
        fp->cmd_vars[1] = 0;
    }
}

static void inlineA1(Fighter_GObj* gobj, HSD_GObjEvent anim_end_cb)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->cmd_vars[1]) {
        inlineA0(fp);
    }
    if (fp->cmd_vars[0]) {
        Fighter_GObj* victim_gobj = fp->victim_gobj;
        if (victim_gobj != NULL) {
            ftCommon_8007E2F4(fp, 0);
            ftCo_800DE2CC(gobj, victim_gobj);
            ftCo_800BBED4(victim_gobj, gobj);
            fp->cmd_vars[0] = 0;
        }
    }
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        anim_end_cb(gobj);
    }
}

void ftYs_SpecialN2_0_Anim(Fighter_GObj* gobj)
{
    inlineA1(gobj, ft_8008A2BC);
}

void ftYs_SpecialAirN2_1_Anim(Fighter_GObj* gobj)
{
    inlineB0(gobj, ftCo_Fall_Enter);
}

void ftYs_SpecialAirN2_0_Anim(Fighter_GObj* gobj)
{
    inlineA1(gobj, ftCo_Fall_Enter);
}

void ftYs_SpecialN1_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftYs_SpecialAirN1_0_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftYs_SpecialN1_1_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftYs_SpecialN1_0_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftYs_SpecialAirN1_2_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftYs_SpecialAirN1_1_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftYs_SpecialN2_1_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftYs_SpecialN2_0_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftYs_SpecialAirN2_1_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftYs_SpecialAirN2_0_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftYs_SpecialN1_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_8012D128);
}

void ftYs_SpecialAirN1_0_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_8012D1AC);
}

void ftYs_SpecialN1_1_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_8012D230);
}

void ftYs_SpecialN1_0_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_8012D298);
}

void ftYs_SpecialAirN1_2_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_8012D2F8);
}

void ftYs_SpecialAirN1_1_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_8012D360);
}

void ftYs_SpecialN2_1_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_8012D3C0);
}

void ftYs_SpecialN2_0_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_8012D428);
}

void ftYs_SpecialAirN2_1_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_8012D488);
}

void ftYs_SpecialAirN2_0_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_8012D4F0);
}

void ftYs_SpecialS_8012DF00(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->take_dmg_cb = ftYs_Init_8012BA8C;
    fp->death2_cb = ftYs_Init_8012BA8C;
}
