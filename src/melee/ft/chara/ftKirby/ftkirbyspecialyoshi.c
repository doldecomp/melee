#include "ftkirbyspecialdonkey.h"
#include "types.h"

#include <placeholder.h>

#include "ft/chara/ftCommon/ftCo_Throw.h"
#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0892.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Fall.h"

#include "ftKirby/forward.h"

#include "ftKirby/ftkirby.h"
#include "ftKirby/ftkirbycaptureyoshi.h"
#include "it/items/itkirbyyoshispecialn.h"
#include "it/items/ityoshiegglay.h"
#include "lb/lb_00B0.h"

#include <common_structs.h>
#include <stddef.h>
#include <baselib/gobj.h>
#include <baselib/random.h>
#include <MSL/math.h>

/* 1095DC */ static void fn_801095DC(HSD_GObj*);
/* 109680 */ static void fn_80109680(HSD_GObj*);
/* 109714 */ static void fn_80109714(HSD_GObj*);
/* 1097B8 */ static void fn_801097B8(HSD_GObj*);
/* 10AA64 */ static void fn_8010AA64(HSD_GObj* gobj);
/* 10C288 */ static void fn_8010C288(HSD_GObj* gobj);
/* 10C344 */ void fn_8010C344(HSD_GObj* arg0);
/* 10CFB0 */ void fn_8010CFB0(Fighter_GObj* gobj);

void ftKb_SpecialNYs_80109260(Fighter_GObj* gobj, Vec3* vec)
{
    Fighter* ft = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = ft->dat_attrs;
    vec->x = -ft->facing_dir * da->specialn_ys_initial_horizontal_momentum;
    vec->y = da->specialn_ys_initial_vertical_momentum;
    vec->z = 0.0f;
}

float ftKb_SpecialNYs_80109290(Fighter_GObj* gobj)
{
    return GET_FIGHTER(gobj)->facing_dir;
}

f32 ftKb_SpecialNYs_8010929C(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = ft->dat_attrs;
    return da->specialn_ys_damage_multiplier;
}

f32 ftKb_SpecialNYs_801092AC(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = ft->dat_attrs;
    return da->specialn_ys_unk;
}

f32 ftKb_SpecialNYs_801092BC(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = ft->dat_attrs;
    return da->specialn_ys_growth_time;
}

f32 ftKb_SpecialNYs_801092CC(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = ft->dat_attrs;
    return da->specialn_ys_base_duration;
}

f32 ftKb_SpecialNYs_801092DC(void)
{
    ftKb_DatAttrs* ea = gFtDataList[FTKIND_KIRBY]->ext_attr;
    return ea->specialn_ys_egg_breakout_resistance;
}

f32 ftKb_SpecialNYs_801092F4(void)
{
    ftKb_DatAttrs* ea = gFtDataList[FTKIND_KIRBY]->ext_attr;
    return ea->specialn_ys_frames_reduced_per_input;
}

f32 ftKb_SpecialNYs_8010930C(void)
{
    ftKb_DatAttrs* ea = gFtDataList[FTKIND_KIRBY]->ext_attr;
    return ea->specialn_ys_unk1;
}

f32 ftKb_SpecialNYs_80109324(void)
{
    ftKb_DatAttrs* ea = gFtDataList[FTKIND_KIRBY]->ext_attr;
    return ea->specialn_ys_unk2;
}

int ftKb_SpecialNYs_8010933C(void)
{
    ftKb_DatAttrs* ea = gFtDataList[FTKIND_KIRBY]->ext_attr;
    return ea->specialn_ys_iframes_on_release;
}

void ftKb_SpecialNYs_80109354(Vec3* v)
{
    ftKb_DatAttrs* cd = gFtDataList[FTKIND_KIRBY]->ext_attr;
    v->x = cd->specialn_ys_horizontal_velocity_on_breakout;
    v->y = cd->specialn_ys_vertical_velocity_on_breakout;
    v->z = 0.0f;
}

float ftKb_SpecialNYs_80109380(void)
{
    ftKb_DatAttrs* cd = gFtDataList[FTKIND_KIRBY]->ext_attr;
    return cd->specialn_ys_unk3 / cd->specialn_ys_damage_multiplier;
}

#pragma dont_inline on
ftDynamics* ftKb_SpecialNYs_801093A0(void)
{
    return ft_80459B88.hats[FTKIND_SAMUS]->hat_dynamics[0];
}
#pragma dont_inline reset

void ftKb_SpecialNYs_801093B4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_JObjAddAnimAll(
        fp->fv.kb.hat.jobj,
        (HSD_AnimJoint*) ft_80459B88.hats[FTKIND_SAMUS]->hat_dynamics[1], 0,
        0);
    HSD_JObjReqAnimAll(fp->fv.kb.hat.jobj, 0.0F);
    HSD_JObjAnimAll(fp->fv.kb.hat.jobj);
    lb_8000BA0C(fp->fv.kb.hat.jobj, 0.0F);
}

void ftKb_SpecialNYs_8010941C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    KirbyHatStruct* ys_hat = ft_80459B88.hats[FTKIND_SAMUS];
    fp->cmd_vars[0] = 0;
    Fighter_ChangeMotionState(gobj, ftKb_MS_YsSpecialN1, 0, 0.0F, 1.0F, 0.0F,
                              NULL);
    ftAnim_8006EBA4(gobj);
    HSD_JObjAddAnimAll(fp->fv.kb.hat.jobj,
                       (HSD_AnimJoint*) ys_hat->hat_dynamics[1], 0, 0);
    HSD_JObjReqAnimAll(fp->fv.kb.hat.jobj, 0.0F);
    HSD_JObjAnimAll(fp->fv.kb.hat.jobj);
    ftCommon_8007E2D0(GET_FIGHTER(gobj), 4, fn_80109680, fn_801095DC,
                      fn_8010A930);
    {
        Fighter* fp2 = GET_FIGHTER(gobj);
        fp2->death2_cb = ftKb_Init_800EE74C;
        fp2->take_dmg_cb = ftKb_Init_800EE7B8;
    }
}

void ftKb_SpecialNYs_801094FC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    KirbyHatStruct* ys_hat = ft_80459B88.hats[FTKIND_SAMUS];
    fp->cmd_vars[0] = 0;
    Fighter_ChangeMotionState(gobj, ftKb_MS_YsSpecialAirNCapture2, 0, 0.0F,
                              1.0F, 0.0F, NULL);
    ftAnim_8006EBA4(gobj);
    HSD_JObjAddAnimAll(fp->fv.kb.hat.jobj,
                       (HSD_AnimJoint*) ys_hat->hat_dynamics[3], 0, 0);
    HSD_JObjReqAnimAll(fp->fv.kb.hat.jobj, 0.0F);
    HSD_JObjAnimAll(fp->fv.kb.hat.jobj);
    ftCommon_8007E2D0(GET_FIGHTER(gobj), 4, fn_801097B8, fn_80109714,
                      fn_8010A930);
    {
        Fighter* fp2 = GET_FIGHTER(gobj);
        fp2->death2_cb = ftKb_Init_800EE74C;
        fp2->take_dmg_cb = ftKb_Init_800EE7B8;
    }
}

static void fn_801095DC(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int new_var;
    HSD_GObj* new_var2;
    it_802F2D98(fp->target_item_gobj, gobj);
    Fighter_ChangeMotionState(gobj, ftKb_MS_YsSpecialNCapture1_1, 0x81092,
                              fp->cur_anim_frame, 1.0f, 0.0f, NULL);
    new_var = 1;
    fp->x2222_b2 = new_var;
    ftCommon_8007E2F4(fp, 0x1FF);
    new_var2 = gobj;
    ftCommon_8007E2FC(gobj);
    fp = new_var2->user_data;
    fp->death2_cb = ftKb_Init_800EE74C;
    fp->take_dmg_cb = ftKb_Init_800EE7B8;
}

static void fn_80109680(HSD_GObj* gobj)
{
    int new_var;
    Fighter* new_var2;
    Fighter* fp = GET_FIGHTER(gobj);
    new_var = 1;
    Fighter_ChangeMotionState(gobj, ftKb_MS_YsSpecialNCapture1_0, 0x81092,
                              fp->cur_anim_frame, 1.0f, 0.0f, NULL);
    fp->x2222_b2 = new_var;
    ftCommon_8007E2F4(fp, 0x1FF);
    ftCommon_8007E2FC(gobj);
    fp = (new_var2 = (Fighter*) HSD_GObjGetUserData(gobj));
    new_var2->death2_cb = ftKb_Init_800EE74C;
    fp->take_dmg_cb = ftKb_Init_800EE7B8;
}

static void fn_80109714(HSD_GObj* gobj)
{
    HSD_GObj* new_var2;
    HSD_GObj* new_var;
    Fighter* fp = GET_FIGHTER(gobj);
    it_802F2D98(fp->target_item_gobj, gobj);
    Fighter_ChangeMotionState(gobj, ftKb_MS_YsSpecialAirNCapture1_1, 0x81092,
                              fp->cur_anim_frame, 1.0f, 0.0f,
                              (void*) ((unsigned int) 0));
    fp->x2222_b2 = true;
    ftCommon_8007E2F4(fp, 0x1FF);
    ftCommon_8007E2FC(gobj);
    new_var = gobj;
    new_var2 = new_var;
    fp = new_var2->user_data;
    fp = new_var2->user_data;
    fp->death2_cb = ftKb_Init_800EE74C;
    fp->take_dmg_cb = ftKb_Init_800EE7B8;
}

static void fn_801097B8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int new_var;
    int new_var2;
    new_var2 = ftKb_MS_YsSpecialAirNCapture1_0;
    new_var = 0;
    Fighter_ChangeMotionState(gobj, new_var2, 0x81092, fp->cur_anim_frame,
                              1.0f, 0.0f, (void*) new_var);
    fp->x2222_b2 = true;
    ftCommon_8007E2F4(fp, 0x1FF);
    ftCommon_8007E2FC(gobj);
    fp = GET_FIGHTER(gobj);
    fp->death2_cb = ftKb_Init_800EE74C;
    fp->take_dmg_cb = ftKb_Init_800EE7B8;
}

void fn_8010984C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_YsSpecialAirNCapture2, 0x0C4C509A,
                              fp->cur_anim_frame, 1.0f, 0.0f, NULL);
    ftCommon_8007E2D0(GET_FIGHTER(gobj), 4, fn_801097B8, fn_80109714,
                      fn_8010A930);
    fp = GET_FIGHTER(gobj);
    fp->death2_cb = ftKb_Init_800EE74C;
    fp->take_dmg_cb = ftKb_Init_800EE7B8;
}

void fn_801098EC(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_YsSpecialN1, 0x0C4C509A,
                              fp->cur_anim_frame, 1.0f, 0.0f, NULL);
    ftCommon_8007E2D0(GET_FIGHTER(gobj), 4, fn_80109680, fn_801095DC,
                      fn_8010A930);
    fp = GET_FIGHTER(gobj);
    fp->death2_cb = ftKb_Init_800EE74C;
    fp->take_dmg_cb = ftKb_Init_800EE7B8;
}

void fn_8010998C(HSD_GObj* gobj)
{
    Fighter* new_var;
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_YsSpecialAirNCapture1_1,
                              0x0C4C5092, fp->cur_anim_frame, 1.0f, 0.0f,
                              NULL);
    /// FAKE MATCH: comma operator required for regalloc
    fp = (0, GET_FIGHTER(gobj));
    new_var = fp;
    new_var->death2_cb = ftKb_Init_800EE74C;
    fp->take_dmg_cb = ftKb_Init_800EE7B8;
}

void fn_80109A08(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_YsSpecialAirNCapture1_0,
                              0x0C4C5092, fp->cur_anim_frame, 1.0f, 0.0f,
                              NULL);
    fp = GET_FIGHTER(gobj);
    fp->death2_cb = ftKb_Init_800EE74C;
    fp->take_dmg_cb = ftKb_Init_800EE7B8;
}

void fn_80109A84(HSD_GObj* gobj)
{
    HSD_GObj* new_var;
    volatile unsigned int pad;
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    if (0) {
    }
    Fighter_ChangeMotionState(gobj, ftKb_MS_YsSpecialNCapture1_1, 0x0C4C5092,
                              fp->cur_anim_frame, 1.0f, 0.0f, NULL);
    new_var = gobj;
    fp = new_var->user_data;
    fp->death2_cb = ftKb_Init_800EE74C;
    fp->take_dmg_cb = ftKb_Init_800EE7B8;
}

void fn_80109B00(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_YsSpecialNCapture1_0, 0x0C4C5092,
                              fp->cur_anim_frame, 1.0f, 0.0f, NULL);
    fp = GET_FIGHTER(gobj);
    fp->death2_cb = ftKb_Init_800EE74C;
    fp->take_dmg_cb = ftKb_Init_800EE7B8;
}

void fn_80109B7C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    void* new_var;
    volatile unsigned short pad;
    void* new_var2;
    new_var = (new_var2 = NULL);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_YsSpecialAirN2_1, 0x0C4C5092,
                              fp->cur_anim_frame, 1.0f, 0.0f, new_var);
    fp = GET_FIGHTER(gobj);
    fp->death2_cb = ftKb_Init_800EE74C;
    fp->take_dmg_cb = ftKb_Init_800EE7B8;
}

void fn_80109BF8(HSD_GObj* gobj)
{
    Fighter* new_var;
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_YsSpecialAirN2_0, 0x0C4C5092,
                              fp->cur_anim_frame, 1.0f, 0.0f, NULL);
    fp = (new_var = GET_FIGHTER(gobj));
    fp->death2_cb = ftKb_Init_800EE74C;
    if (gobj) {
    }
    /// FAKE MATCH: comma operator required for regalloc
    new_var->take_dmg_cb = (0, ftKb_Init_800EE7B8);
}

void fn_80109C74(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_YsSpecialNCapture2_1, 0x0C4C5092,
                              fp->cur_anim_frame, 1.0f, 0.0f, NULL);
    fp = GET_FIGHTER(gobj);
    fp->death2_cb = ftKb_Init_800EE74C;
    fp->take_dmg_cb = ftKb_Init_800EE7B8;
}

void fn_80109CF0(HSD_GObj* gobj)
{
    HSD_GObj* new_var;
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_YsSpecialNCapture2_0, 0x0C4C5092,
                              fp->cur_anim_frame, 1.0f, 0.0f, NULL);
    new_var = gobj;
    fp = new_var->user_data;
    /// FAKE MATCH: comma operator required for regalloc
    fp->death2_cb = (0, ftKb_Init_800EE74C);
    fp->take_dmg_cb = ftKb_Init_800EE7B8;
}

void ftKb_YsSpecialN1_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    HSD_JObjAnimAll(fp->fv.kb.hat.jobj);
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ft_8008A2BC(gobj);
    }
}

void ftKb_YsSpecialAirNCapture2_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    HSD_JObjAnimAll(fp->fv.kb.hat.jobj);
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCo_Fall_Enter(gobj);
    }
}

void ftKb_YsSpecialAirNCapture1_Anim(Fighter_GObj* gobj)
{
    KirbyHatStruct* hat;
    Fighter* fp2;
    s32 new_var;
    Fighter* fp = gobj->user_data;
    new_var = 0;
    do {
        UNUSED unsigned char _[8];
    } while (new_var);
    if (fp->cmd_vars[0] != new_var && fp->target_item_gobj != NULL) {
        fp->cmd_vars[0] = new_var;
        fp->cmd_vars[1] = new_var;
        fp2 = GET_FIGHTER(gobj);
        hat = ft_80459B88.hats[0xD];
        Fighter_ChangeMotionState(gobj, ftKb_MS_YsSpecialNCapture2_1, 0x80012,
                                  0.0f, 1.0f, 0.0f, NULL);
        HSD_JObjAddAnimAll(fp2->fv.kb.hat.jobj,
                           (HSD_AnimJoint*) hat->hat_dynamics[2], NULL, NULL);
        HSD_JObjReqAnimAll(fp2->fv.kb.hat.jobj, 0.0f);
        fp2 = GET_FIGHTER(gobj);
        fp2->death2_cb = ftKb_Init_800EE74C;
        fp2->take_dmg_cb = ftKb_Init_800EE7B8;
        ftCommon_8007E2F4(fp, 0x1FF);
    }
}

void ftKb_YsSpecialNCapture1_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    KirbyHatStruct* hat;
    Fighter* fp2;
    s32 new_var;
    new_var = 0;
    do {
        UNUSED unsigned char _[8];
    } while (new_var);
    HSD_JObjAnimAll(fp->fv.kb.hat.jobj);
    if (fp->cmd_vars[0] != new_var && fp->victim_gobj != NULL) {
        fp->cmd_vars[0] = new_var;
        fp->cmd_vars[1] = new_var;
        fp2 = GET_FIGHTER(gobj);
        hat = ft_80459B88.hats[0xD];
        Fighter_ChangeMotionState(gobj, ftKb_MS_YsSpecialNCapture2_0, 0x80012,
                                  0.0f, 1.0f, 0.0f, NULL);
        HSD_JObjAddAnimAll(fp2->fv.kb.hat.jobj,
                           (HSD_AnimJoint*) hat->hat_dynamics[2], NULL, NULL);
        HSD_JObjReqAnimAll(fp2->fv.kb.hat.jobj, 0.0f);
        fp2 = GET_FIGHTER(gobj);
        fp2->death2_cb = ftKb_Init_800EE74C;
        fp2->take_dmg_cb = ftKb_Init_800EE7B8;
        ftCommon_8007E2F4(fp, 0x1FF);
    }
}

void ftKb_YsSpecialAirCapture2_Anim(Fighter_GObj* gobj)
{
    KirbyHatStruct* hat;
    Fighter* fp2;
    s32 new_var;
    Fighter* fp = gobj->user_data;
    new_var = 0;
    do {
        UNUSED unsigned char _[8];
    } while (new_var);
    if (fp->cmd_vars[0] != new_var && fp->target_item_gobj != NULL) {
        fp->cmd_vars[0] = new_var;
        fp->cmd_vars[1] = new_var;
        fp2 = GET_FIGHTER(gobj);
        hat = ft_80459B88.hats[0xD];
        Fighter_ChangeMotionState(gobj, ftKb_MS_YsSpecialAirN2_1, 0x80012,
                                  0.0f, 1.0f, 0.0f, NULL);
        HSD_JObjAddAnimAll(fp2->fv.kb.hat.jobj,
                           (HSD_AnimJoint*) hat->hat_dynamics[4], NULL, NULL);
        HSD_JObjReqAnimAll(fp2->fv.kb.hat.jobj, 0.0f);
        fp2 = GET_FIGHTER(gobj);
        fp2->death2_cb = ftKb_Init_800EE74C;
        fp2->take_dmg_cb = ftKb_Init_800EE7B8;
        ftCommon_8007E2F4(fp, 0x1FF);
    }
}

void ftKb_YsSpecialAirCapture1_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    KirbyHatStruct* hat;
    Fighter* fp2;
    s32 new_var;
    new_var = 0;
    do {
        UNUSED unsigned char _[8];
    } while (new_var);
    HSD_JObjAnimAll(fp->fv.kb.hat.jobj);
    if (fp->cmd_vars[0] != new_var && fp->victim_gobj != NULL) {
        fp->cmd_vars[0] = new_var;
        fp->cmd_vars[1] = new_var;
        fp2 = GET_FIGHTER(gobj);
        hat = ft_80459B88.hats[0xD];
        Fighter_ChangeMotionState(gobj, ftKb_MS_YsSpecialAirN2_0, 0x80012,
                                  0.0f, 1.0f, 0.0f, NULL);
        HSD_JObjAddAnimAll(fp2->fv.kb.hat.jobj,
                           (HSD_AnimJoint*) hat->hat_dynamics[4], NULL, NULL);
        HSD_JObjReqAnimAll(fp2->fv.kb.hat.jobj, 0.0f);
        fp2 = GET_FIGHTER(gobj);
        fp2->death2_cb = ftKb_Init_800EE74C;
        fp2->take_dmg_cb = ftKb_Init_800EE7B8;
        ftCommon_8007E2F4(fp, 0x1FF);
    }
}

void ftKb_YsSpecialNCapture2_0_Anim(Fighter_GObj* gobj)
{
    u8 _pad[8];
    Fighter* fp = GET_FIGHTER(gobj);
    itYoshiEggLay_DatAttrs item_attrs;
    PAD_STACK(82);
    HSD_JObjAnimAll(fp->fv.kb.hat.jobj);
    if (fp->cmd_vars[1] != 0) {
        if (fp->target_item_gobj != NULL) {
            it_802F2E7C(fp->target_item_gobj, false);
            fp->x1A64 = NULL;
            fp->target_item_gobj = NULL;
            fp->cmd_vars[1] = 0;
        }
    }
    if (fp->cmd_vars[0] != 0) {
        ftCommon_8007E2F4(fp, 0);
        {
            Fighter* fp2 = GET_FIGHTER(gobj);
            lb_8000B1CC(
                fp2->parts[ftParts_GetBoneIndex(fp2, FtPart_TransN2)].joint,
                NULL, &item_attrs.pos);
        }
        {
            Fighter* fp2 = GET_FIGHTER(gobj);
            ftKb_DatAttrs* da = fp2->dat_attrs;
            item_attrs.vel.x =
                -fp2->facing_dir * da->specialn_ys_initial_horizontal_momentum;
            item_attrs.vel.y = da->specialn_ys_initial_vertical_momentum;
            item_attrs.vel.z = 0.0f;
        }
        item_attrs.float2 = GET_FIGHTER(gobj)->facing_dir;
        {
            ftKb_DatAttrs* da = GET_FIGHTER(gobj)->dat_attrs;
            item_attrs.lifetime = da->specialn_ys_base_duration;
        }
        {
            ftKb_DatAttrs* da = GET_FIGHTER(gobj)->dat_attrs;
            item_attrs.x24 = da->specialn_ys_damage_multiplier;
        }
        {
            ftKb_DatAttrs* ea = gFtDataList[FTKIND_KIRBY]->ext_attr;
            item_attrs.float3 =
                ea->specialn_ys_unk3 / ea->specialn_ys_damage_multiplier;
        }
        item_attrs.kind = 0x9D;
        it_802F2F34(gobj, &item_attrs);
        fp->cmd_vars[0] = 0;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftKb_YsSpecialNCapture2_1_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_GObj* victim;
    PAD_STACK(8);
    HSD_JObjAnimAll(fp->fv.kb.hat.jobj);
    if (fp->cmd_vars[1] != 0) {
        if (fp->victim_gobj != NULL) {
            ftKb_SpecialNYs_8010AA2C(fp->victim_gobj);
            fp->cmd_vars[1] = 0;
        }
    }
    if (fp->cmd_vars[0] != 0 && (victim = fp->victim_gobj) != NULL) {
        ftCommon_8007E2F4(fp, 0);
        ftCo_800DE2CC(gobj, victim);
        ftKb_SpecialNYs_8010AC78(victim, gobj);
        fp->cmd_vars[0] = 0;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftKb_YsSpecialAirN2_1_Anim(Fighter_GObj* gobj)
{
    u8 _pad[8];
    Fighter* fp = GET_FIGHTER(gobj);
    itYoshiEggLay_DatAttrs item_attrs;
    PAD_STACK(0x54);
    HSD_JObjAnimAll(fp->fv.kb.hat.jobj);
    if (fp->cmd_vars[1] != 0) {
        if (fp->target_item_gobj != NULL) {
            it_802F2E7C(fp->target_item_gobj, false);
            fp->x1A64 = NULL;
            fp->target_item_gobj = NULL;
            fp->cmd_vars[1] = 0;
        }
    }
    if (fp->cmd_vars[0] != 0) {
        ftCommon_8007E2F4(fp, 0);
        {
            Fighter* fp2 = GET_FIGHTER(gobj);
            lb_8000B1CC(
                fp2->parts[ftParts_GetBoneIndex(fp2, FtPart_TransN2)].joint,
                NULL, &item_attrs.pos);
        }
        {
            Fighter* fp2 = GET_FIGHTER(gobj);
            ftKb_DatAttrs* da = fp2->dat_attrs;
            item_attrs.vel.x =
                -fp2->facing_dir * da->specialn_ys_initial_horizontal_momentum;
            item_attrs.vel.y = da->specialn_ys_initial_vertical_momentum;
            item_attrs.vel.z = 0.0f;
        }
        item_attrs.float2 = GET_FIGHTER(gobj)->facing_dir;
        {
            ftKb_DatAttrs* da = GET_FIGHTER(gobj)->dat_attrs;
            item_attrs.lifetime = da->specialn_ys_base_duration;
        }
        {
            ftKb_DatAttrs* da = GET_FIGHTER(gobj)->dat_attrs;
            item_attrs.x24 = da->specialn_ys_damage_multiplier;
        }
        {
            ftKb_DatAttrs* ea = gFtDataList[FTKIND_KIRBY]->ext_attr;
            item_attrs.float3 =
                ea->specialn_ys_unk3 / ea->specialn_ys_damage_multiplier;
        }
        item_attrs.kind = 0x9D;
        it_802F2F34(gobj, &item_attrs);
        fp->cmd_vars[0] = 0;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

void ftKb_YsSpecialAirN2_0_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_GObj* victim;
    PAD_STACK(8);
    HSD_JObjAnimAll(fp->fv.kb.hat.jobj);
    if (fp->cmd_vars[1] != 0) {
        if (fp->victim_gobj != NULL) {
            ftKb_SpecialNYs_8010AA2C(fp->victim_gobj);
            fp->cmd_vars[1] = 0;
        }
    }
    if (fp->cmd_vars[0] != 0 && (victim = fp->victim_gobj) != NULL) {
        ftCommon_8007E2F4(fp, 0);
        ftCo_800DE2CC(gobj, victim);
        ftKb_SpecialNYs_8010AC78(victim, gobj);
        fp->cmd_vars[0] = 0;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

void ftKb_YsSpecialN1_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_YsSpecialAirNCapture2_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_YsSpecialAirNCapture1_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_YsSpecialNCapture1_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_YsSpecialAirCapture1_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_YsSpecialAirCapture2_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_YsSpecialNCapture2_0_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_YsSpecialNCapture2_1_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_YsSpecialAirN2_1_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_YsSpecialAirN2_0_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_YsSpecialN1_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_8010984C);
}

void ftKb_YsSpecialAirNCapture2_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_801098EC);
}

void ftKb_YsSpecialAirNCapture1_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_8010998C);
}

void ftKb_YsSpecialNCapture1_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_80109A08);
}

void ftKb_YsSpecialAirCapture2_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_80109A84);
}

void ftKb_YsSpecialAirCapture1_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_80109B00);
}

void ftKb_YsSpecialNCapture2_0_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_80109B7C);
}

void ftKb_YsSpecialNCapture2_1_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_80109BF8);
}

void ftKb_YsSpecialAirN2_1_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_80109C74);
}

void ftKb_YsSpecialAirN2_0_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_80109CF0);
}

void ftKb_SpecialNYs_8010A8BC(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    bool has_destroy_type;

    if (fp->target_item_gobj != NULL) {
        has_destroy_type = false;
        if (fp->motion_id == ftKb_MS_YsSpecialNCapture1_1 ||
            fp->motion_id == ftKb_MS_YsSpecialNCapture2_1 ||
            fp->motion_id == ftKb_MS_YsSpecialAirNCapture1_1 ||
            fp->motion_id == ftKb_MS_YsSpecialAirN2_1)
        {
            has_destroy_type = true;
        }
        it_802F2E7C(fp->target_item_gobj, has_destroy_type);
        fp->x1A64 = NULL;
        fp->target_item_gobj = NULL;
    }
}
