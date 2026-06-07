#include "ftkirbyspecialdonkey.h"
#include "types.h"

#include <placeholder.h>

#include "ef/efasync.h"
#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/chara/ftCommon/ftCo_Bury.h"
#include "ft/chara/ftCommon/ftCo_Lift.h"
#include "ft/chara/ftCommon/ftCo_Throw.h"
#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0892.h"
#include "ft/ftcolanim.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Attack100.h"
#include "ftCommon/ftCo_Fall.h"

#include "ftKirby/forward.h"

#include "ftKirby/ftkirby.h"
#include "it/items/itgamewatchchef.h"
#include "it/items/itkirbygamewatchchefpan.h"
#include "it/items/itkirbyyoshispecialn.h"
#include "it/items/itpeachtoad.h"
#include "it/items/itpeachtoadspore.h"
#include "it/items/ityoshiegglay.h"
#include "lb/lb_00B0.h"

#include <common_structs.h>
#include <stddef.h>
#include <baselib/gobj.h>
#include <baselib/random.h>
#include <MSL/math.h>

extern f32 ftKb_Init_804D9558;
extern f32 ftKb_Init_804D9570;
extern f32 ftKb_Init_804D9574;
extern f32 ftKb_Init_804D9590;
extern f32 ftKb_Init_804D9594;
extern f32 ftKb_Init_804D9598;
extern f64 ftKb_Init_804D95A0;

/* 1095DC */ static void fn_801095DC(HSD_GObj*);
/* 109680 */ static void fn_80109680(HSD_GObj*);
/* 109714 */ static void fn_80109714(HSD_GObj*);
/* 1097B8 */ static void fn_801097B8(HSD_GObj*);
/* 10A930 */ void fn_8010A930(Fighter_GObj*, Fighter_GObj*);
/* 10AA64 */ static void fn_8010AA64(HSD_GObj* gobj);
/* 10B1F4 */ void fn_8010B1F4(Fighter_GObj* gobj);
/* 10B2E8 */ void fn_8010B2E8(Fighter_GObj* gobj);
/* 10C288 */ static void fn_8010C288(HSD_GObj* gobj);
/* 10C344 */ void fn_8010C344(HSD_GObj* arg0);
/* 10C44C */ static void fn_8010C44C(HSD_GObj* gobj);
/* 10CD88 */ static void fn_8010CD88(HSD_GObj* gobj);
/* 10CE5C */ void fn_8010CE5C(Fighter_GObj* gobj);
/* 10CFB0 */ void fn_8010CFB0(Fighter_GObj* gobj);

void ftKb_SpecialNYs_80109260(Fighter_GObj* gobj, Vec3* vec)
{
    Fighter* ft = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = ft->dat_attrs;
    vec->x = -ft->facing_dir * da->specialn_ys_initial_horizontal_momentum;
    vec->y = da->specialn_ys_initial_vertical_momentum;
    vec->z = ftKb_Init_804D9558;
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
            item_attrs.vel.z = ftKb_Init_804D9558;
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
            item_attrs.vel.z = ftKb_Init_804D9558;
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

void fn_8010A930(Fighter_GObj* gobj, Fighter_GObj* attacker_gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter* attacker_fp = GET_FIGHTER(attacker_gobj);
    ftCommon_8007DB58(gobj);
    ftCo_8009750C(gobj);
    ftCo_800DD168(gobj);
    fp->x1A5C = attacker_gobj;
    fp->victim_gobj = attacker_gobj;
    fp->x221B_b5 = false;
    fp->x221B_b7 = false;
    fp->facing_dir = -attacker_fp->facing_dir;
    ftCo_800DB368(attacker_fp, fp);
    Fighter_ChangeMotionState(gobj, 0x14B, 0, 0.0f, 1.0f, 0.0f, NULL);
    fp->accessory1_cb = ftCo_800DB464;
    ftCommon_8007D5D4(fp);
    ftCommon_8007E2F4(fp, 0x1FF);
    ftAnim_8006EBA4(gobj);
    ftCommon_8007E2FC(gobj);
}

void ftCo_CaptureKirbyYoshi_Anim(Fighter_GObj* gobj) {}

void ftCo_CaptureKirbyYoshi_IASA(Fighter_GObj* gobj) {}

void ftCo_CaptureKirbyYoshi_Phys(Fighter_GObj* gobj) {}

void ftCo_CaptureKirbyYoshi_Coll(Fighter_GObj* gobj) {}

void ftKb_SpecialNYs_8010AA2C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->invisible = true;
    ftColl_8007B62C(gobj, 2);
}

static void fn_8010AA64(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_JObj* jobj = gobj->hsd_obj;
    if (fp->mv.co.yoshiegg.x14 <= 0.0f) {
        Fighter_UpdateModelScale(gobj);
        fp->accessory4_cb = NULL;
        return;
    }
    fp->mv.co.yoshiegg.x14 -= 1.0f;
    {
        Vec3 vec1, vec0;
        f32 temp0 = (fp->mv.co.yoshiegg.x10 - fp->mv.co.yoshiegg.x14) /
                    fp->mv.co.yoshiegg.x10;
        temp0 *= fp->mv.co.yoshiegg.xC;
        {
            f32 temp1 = (1.0f - fp->mv.co.yoshiegg.xC) + temp0;
            vec1.x = vec1.y = vec1.z = temp1;
            vec0 = vec1;
            vec1.x = vec1.x * fp->mv.co.yoshiegg.x18.x;
            vec1.y *= fp->mv.co.yoshiegg.x18.y;
            vec1.z *= fp->mv.co.yoshiegg.x18.z;
            HSD_JObjSetScale(jobj, &vec1);
            vec0.x = vec0.x * fp->mv.co.yoshiegg.scale.x;
            vec0.y *= fp->mv.co.yoshiegg.scale.y;
            vec0.z *= fp->mv.co.yoshiegg.scale.z;
            HSD_JObjSetScale(fp->x20A0_accessory, &vec0);
        }
    }
}

void ftKb_SpecialNYs_8010AC78(Fighter_GObj* victim, Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(victim);
    HSD_JObj* jobj = victim->hsd_obj;
    ftHurtboxInit hurt;
    Vec3 scale;
    Fighter* fp2;

    if (fp->ground_or_air == GA_Ground) {
        ftCommon_8007D5D4(fp);
    }
    Fighter_ChangeMotionState(victim, 0x14C, Ft_MF_Unk06, 0.0f, 1.0f, 0.0f,
                              gobj);
    fp->take_dmg_cb = (HSD_GObjEvent) fn_8010B1D4;
    ftCommon_8007E2F4(fp, 0x1FF);
    fp->invisible = true;
    scale.x = scale.y = scale.z = fp->co_attrs.xBC.size;
    ftCommon_SetAccessory(fp, (HSD_Joint*) ftKb_SpecialNYs_801093A0());
    HSD_JObjSetScale(fp->x20A0_accessory, &scale);
    lb_8000C2F8(HSD_JObjGetChild(fp->x20A0_accessory),
                fp->parts[ftParts_GetBoneIndex(fp, FtPart_TransN)].joint);
    fp->mv.co.yoshiegg.scale = scale;
    fp2 = GET_FIGHTER(victim);
    ftColl_8007B0C0(victim, Intangible);
    hurt.bone_idx = ftParts_GetBoneIndex(fp2, FtPart_TransN);
    hurt.height = HurtHeight_Mid;
    hurt.is_grabbable = false;
    hurt.a_offset = fp2->co_attrs.xBC.x4;
    hurt.b_offset = fp2->co_attrs.xBC.x10;
    hurt.scale = fp2->co_attrs.xBC.x1C;
    ftColl_HurtboxInit(fp2, fp2->hurt_capsules, &hurt);
    ftKb_SpecialNYs_80109260(gobj, &fp->self_vel);
    fp->facing_dir = ftKb_SpecialNYs_80109290(gobj);
    fp->dmg.x182c_behavior = ftKb_SpecialNYs_8010929C(gobj);
    fp->mv.ca.specialhi.vel.y = 0.0f;
    fp->mv.co.yoshiegg.x0 = gobj;
    fp->take_dmg_2_cb = (HSD_GObjEvent) fn_8010B16C;
    ftCommon_8007EFC0(fp, 1);
    fp->mv.co.walk.fast_anim_frame = ftKb_SpecialNYs_801092BC(gobj);
    fp->mv.co.common.x14 = fp->mv.co.walk.fast_anim_frame;
    fp->mv.co.common.x4.z = ftKb_SpecialNYs_801092AC(gobj);
    ftCommon_InitGrab(fp, 0, ftKb_SpecialNYs_801092CC(gobj));
    HSD_JObjGetScale(jobj, &fp->mv.co.yoshiegg.x18);
    fp->accessory4_cb = fn_8010AA64;
}

#pragma dont_inline on
void ftCo_KirbyYoshiEgg_Anim(Fighter_GObj* gobj)
{
    f32 temp_ret;
    Fighter* fp = gobj->user_data;
    PAD_STACK(16);
    temp_ret = ftKb_SpecialNYs_801092DC();
    fp->grab_timer -= temp_ret;
    fp->mv.kb.specialhi.x4 = ftCommon_GrabMash(fp, ftKb_SpecialNYs_801092F4());
    if (fp->grab_timer <= 0.0f) {
        Fighter* fp2;
        ftCo_DatAttrs_xBC_t* xBCp;
        ft_PlaySFX(fp, 0x44618, 0x7F, 0x40);
        fp2 = gobj->user_data;
        efAsync_Spawn(gobj, &fp2->x60C, 4, 0x4CF, fp->parts[0].joint,
                      (xBCp = &fp->co_attrs.xBC));
        ftKb_SpecialNYs_80109354(&fp->self_vel);
        ftCommon_8007D5D4(fp);
        ftColl_8007B760(gobj, ftKb_SpecialNYs_8010933C());
        ftCo_Fall_Enter_YoshiEgg_Kirby(gobj);
        return;
    }
    if (fp->mv.kb.specialhi.x8.f) {
        fp->mv.kb.specialhi.x8.f--;
        if (fp->mv.kb.specialhi.x8.f <= 0.0f && fp->mv.kb.specialhi.x4 == 0) {
            ftAnim_SetAnimRate(gobj, 1.0f);
            fp->mv.kb.specialhi.x8.f = 0.0f;
        }
    }
    if (fp->mv.kb.specialhi.x8.f <= 0.0f && fp->mv.kb.specialhi.x4 != 0) {
        fp->mv.kb.specialhi.x8.f = ftKb_SpecialNYs_8010930C();
        ftAnim_SetAnimRate(gobj, ftKb_SpecialNYs_80109324());
    }
}
#pragma dont_inline reset

void ftCo_KirbyYoshiEgg_IASA(Fighter_GObj* gobj) {}

void ftCo_KirbyYoshiEgg_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if ((enum GroundOrAir) fp->ground_or_air == GA_Ground) {
        ft_80084F3C(gobj);
        return;
    }
    ft_80084DB0(gobj);
}

void ftCo_KirbyYoshiEgg_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if ((enum GroundOrAir) fp->ground_or_air == GA_Ground) {
        ft_8008403C(gobj, fn_8010B148);
        return;
    }
    ft_80082C74(gobj, fn_8010B124);
}

void fn_8010B124(Fighter_GObj* gobj)
{
    ftCommon_8007D7FC(GET_FIGHTER(gobj));
}

void fn_8010B148(Fighter_GObj* gobj)
{
    ftCommon_8007D5D4(GET_FIGHTER(gobj));
}

#pragma dont_inline on
void fn_8010B16C(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    fp->grab_timer -= fp->dmg.x1838_percentTemp * ftKb_SpecialNYs_80109380();
    if ((s32) fp->dmg.x18CC == 3 && ftCo_800C0C88(fp->dmg.x18D0) != 0) {
        fp->grab_timer = 0.0f;
    }
    fp->x1828 = 4;
}
#pragma dont_inline reset

void fn_8010B1D4(Fighter_GObj* gobj)
{
    Fighter_UpdateModelScale(gobj);
}

void fn_8010B1F4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!fp->x2219_b0) {
        if ((s32) fp->fv.kb.hat.kind == FTKIND_MARS) {
            if ((s32) fp->ground_or_air == GA_Ground) {
                efSync_Spawn(0x4B4, gobj, fp->parts[FtPart_TopN].joint);
            } else {
                efSync_Spawn(0x4B5, gobj, fp->parts[FtPart_TopN].joint);
            }
        } else {
            if ((s32) fp->ground_or_air == GA_Ground) {
                efSync_Spawn(0x4B8, gobj, fp->parts[FtPart_TopN].joint);
            } else {
                efSync_Spawn(0x4B9, gobj, fp->parts[FtPart_TopN].joint);
            }
        }
        fp->x2219_b0 = true;
    }
    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
    fp->accessory4_cb = NULL;
}

void fn_8010B2E8(Fighter_GObj* gobj)
{
    ftKb_Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[0] = 0;
    fp->mv.kb.specialn_ms.cur_frame = 0;
}

void ftKb_SpecialNMs_8010B2FC(HSD_GObj* gobj)
{
    PAD_STACK(4 * 6);
    {
        ftKb_DatAttrs* da;
        struct ftKb_SpecialNMs_DatAttrs* ms_da;
        Fighter* fp = GET_FIGHTER(gobj);
        da = fp->dat_attrs;

        if (fp->fv.kb.hat.kind == FTKIND_MARS) {
            ms_da = &da->ms;
        } else {
            ms_da = &da->fe;
        }

        // InStateChange callback
        fp->x21EC = fn_8010B2E8;

        fp->gr_vel = fp->gr_vel / ms_da->air_horizontal_momentum_preservation;
    }

    {
        ftKirby_MotionState msid;
        {
            Fighter* fp = GET_FIGHTER(gobj);
            if (fp->fv.kb.hat.kind == FTKIND_MARS) {
                msid = ftKb_MS_MsSpecialNStart;
            } else {
                msid = ftKb_MS_FeSpecialNStart;
            }
        }
        Fighter_ChangeMotionState(gobj, msid, 0, 0, 1, 0, NULL);
    }

    ftAnim_8006EBA4(gobj);

    {
        Fighter* fp = GET_FIGHTER(gobj);
        Vec3 scale;

        if (fp->fv.kb.hat.kind == FTKIND_MARS) {
            ftCommon_SetAccessory(fp, ft_80459B88.x0->x0[FTKIND_MARS].next);
        } else {
            ftCommon_SetAccessory(fp, ft_80459B88.x0->x0[FTKIND_EMBLEM].next);
        }

        scale.x = scale.y = scale.z = ftCommon_GetModelScale(fp);
        HSD_JObjSetScale(fp->x20A0_accessory, &scale);
        lb_8000C2F8(
            fp->x20A0_accessory,
            fp->parts[ftParts_GetBoneIndex(fp, FtPart_RThumbNb)].joint);
    }
}

void ftKb_SpecialNMs_8010B4A0(HSD_GObj* gobj)
{
    PAD_STACK(4 * 6);
    {
        ftKb_DatAttrs* da;
        struct ftKb_SpecialNMs_DatAttrs* ms_da;
        Fighter* fp = GET_FIGHTER(gobj);
        da = fp->dat_attrs;

        if (fp->fv.kb.hat.kind == FTKIND_MARS) {
            ms_da = &da->ms;
        } else {
            ms_da = &da->fe;
        }

        // InStateChange callback
        fp->x21EC = fn_8010B2E8;

        fp->self_vel.x =
            fp->self_vel.x / ms_da->air_horizontal_momentum_preservation;
        if (fp->self_vel.y <= 0.0f) {
            fp->self_vel.y = 0.0f;
        }
    }

    {
        ftKirby_MotionState msid;
        {
            Fighter* fp = GET_FIGHTER(gobj);
            if (fp->fv.kb.hat.kind == FTKIND_MARS) {
                msid = ftKb_MS_MsSpecialAirNStart;
            } else {
                msid = ftKb_MS_FeSpecialAirNStart;
            }
        }
        Fighter_ChangeMotionState(gobj, msid, 0, 0, 1, 0, NULL);
    }

    ftAnim_8006EBA4(gobj);

    {
        Fighter* fp = GET_FIGHTER(gobj);
        Vec3 scale;
        KirbyHatStruct* mars_hat = ft_80459B88.hats[FTKIND_MARS - 1];
        KirbyHatStruct* fe_hat = ft_80459B88.hats[FTKIND_EMBLEM - 1];

        if (fp->fv.kb.hat.kind == FTKIND_MARS) {
            ftCommon_SetAccessory(fp, (HSD_Joint*) mars_hat->hat_dynamics[0]);
        } else {
            ftCommon_SetAccessory(fp, (HSD_Joint*) fe_hat->hat_dynamics[0]);
        }

        scale.x = scale.y = scale.z = ftCommon_GetModelScale(fp);
        HSD_JObjSetScale(fp->x20A0_accessory, &scale);
        lb_8000C2F8(
            fp->x20A0_accessory,
            fp->parts[ftParts_GetBoneIndex(fp, FtPart_RThumbNb)].joint);
    }
}

void ftKb_MsSpecialNStart_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftKb_SpecialNMs_8010BC40(gobj);
        {
            Fighter* fp = GET_FIGHTER(gobj);
            if (fp->fv.kb.hat.kind == FTKIND_MARS) {
                ftCo_800BFFD0(fp, 99, 0);
            } else {
                ftCo_800BFFD0(fp, 100, 0);
            }
        }
    }
}

void ftKb_MsSpecialAirNStart_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftKb_SpecialNMs_8010BC90(gobj);
        {
            Fighter* fp = GET_FIGHTER(gobj);
            if (fp->fv.kb.hat.kind == FTKIND_MARS) {
                ftCo_800BFFD0(fp, 99, 0);
            } else {
                ftCo_800BFFD0(fp, 100, 0);
            }
        }
    }
}

void ftKb_MsSpecialNStart_IASA(Fighter_GObj* gobj) {}

void ftKb_MsSpecialAirNStart_IASA(Fighter_GObj* gobj) {}

void ftKb_MsSpecialNStart_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    struct ftKb_SpecialNMs_DatAttrs* ms_da;
    PAD_STACK(16);
    if (fp->fv.kb.hat.kind == FTKIND_MARS) {
        ms_da = &da->ms;
    } else {
        ms_da = &da->fe;
    }
    ftCommon_ApplyFrictionGround(fp, ms_da->air_horizontal_deceleration_rate);
    ftCommon_ApplyGroundMovement(gobj);
}

void ftKb_MsSpecialAirNStart_Phys(Fighter_GObj* gobj)
{
    struct ftKb_SpecialNMs_DatAttrs* ms_da;
    Fighter* fp = getFighter(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(16);
    if (fp->fv.kb.hat.kind == FTKIND_MARS) {
        ms_da = &da->ms;
    } else {
        ms_da = &da->fe;
    }
    ftCommon_FallBasic(fp);
    ftCommon_ApplyFrictionAir(fp, ms_da->air_horizontal_deceleration_rate);
}

void ftKb_MsSpecialNStart_Coll(Fighter_GObj* gobj)
{
    if (ft_80082708(gobj) == GA_Ground) {
        ftKb_SpecialNMs_8010B868(gobj);
    }
}

void ftKb_MsSpecialAirNStart_Coll(Fighter_GObj* gobj)
{
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftKb_SpecialNMs_8010B8E0(gobj);
    }
}

inline FtMotionId getAirSpecialMotionId(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.kb.hat.kind == FTKIND_MARS) {
        return ftKb_MS_MsSpecialAirNStart;
    } else {
        return ftKb_MS_FeSpecialAirNStart;
    }
}

void ftKb_SpecialNMs_8010B868(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, getAirSpecialMotionId(gobj), 0x0C4C7084,
                              fp->cur_anim_frame, 1.0f, 0.0f, NULL);
}

inline FtMotionId getGroundSpecialMotionId(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.kb.hat.kind == FTKIND_MARS) {
        return ftKb_MS_MsSpecialNStart;
    } else {
        return ftKb_MS_FeSpecialNStart;
    }
}

void ftKb_SpecialNMs_8010B8E0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, getGroundSpecialMotionId(gobj), 0x0C4C7084,
                              fp->cur_anim_frame, 1.0f, 0.0f, NULL);
}

void ftKb_MsSpecialNLoop_Anim(Fighter_GObj* gobj)
{
    s32* charge;
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    if (fp->fv.kb.hat.kind == FTKIND_MARS) {
        charge = (s32*) &da->ms.charge_iterations;
    } else {
        charge = (s32*) &da->fe.charge_iterations;
    }
    fp->mv.kb.specialn_ms.cur_frame++;
    if (fp->mv.kb.specialn_ms.cur_frame > (*charge * 30)) {
        fp->cmd_vars[0] = 1;
        ftKb_SpecialNPe_8010C148(gobj);
    }
}

void ftKb_MsSpecialAirNLoop_Anim(Fighter_GObj* gobj)
{
    u32* charge;
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    if (fp->fv.kb.hat.kind == FTKIND_MARS) {
        charge = &da->ms.charge_iterations;
    } else {
        charge = &da->fe.charge_iterations;
    }
    fp->mv.kb.specialn_ms.cur_frame++;
    if (fp->mv.kb.specialn_ms.cur_frame > (s32) (*charge * 30)) {
        fp->cmd_vars[0] = 1;
        ftKb_SpecialNPe_8010C1E8(gobj);
    }
}

void ftKb_MsSpecialNLoop_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!(fp->input.held_inputs & HSD_PAD_B)) {
        fp->cmd_vars[0] = 0;
        ftKb_SpecialNPe_8010C148(gobj);
    }
}

void ftKb_MsSpecialAirNLoop_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!(fp->input.held_inputs & HSD_PAD_B)) {
        fp->cmd_vars[0] = 0;
        ftKb_SpecialNPe_8010C1E8(gobj);
    }
}

void ftKb_MsSpecialNLoop_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_MsSpecialAirNLoop_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_MsSpecialNLoop_Coll(Fighter_GObj* gobj)
{
    if (ft_80082708(gobj) == GA_Ground) {
        ftKb_SpecialNMs_8010BB50(gobj);
    }
}

void ftKb_MsSpecialAirNLoop_Coll(Fighter_GObj* gobj)
{
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftKb_SpecialNMs_8010BBC8(gobj);
    }
}

void ftKb_SpecialNMs_8010BB50(Fighter_GObj* gobj)
{
    FtMotionId msid;
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    if ((s32) GET_FIGHTER(gobj)->fv.kb.hat.kind == FTKIND_MARS) {
        msid = ftKb_MS_MsSpecialAirNLoop;
    } else {
        msid = ftKb_MS_FeSpecialAirNLoop;
    }
    Fighter_ChangeMotionState(gobj, msid, 0x0C4C7A86, fp->cur_anim_frame, 1.0f,
                              0.0f, NULL);
}

void ftKb_SpecialNMs_8010BBC8(Fighter_GObj* gobj)
{
    FtMotionId msid;
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    if ((s32) GET_FIGHTER(gobj)->fv.kb.hat.kind == FTKIND_MARS) {
        msid = ftKb_MS_MsSpecialNLoop;
    } else {
        msid = ftKb_MS_FeSpecialNLoop;
    }
    Fighter_ChangeMotionState(gobj, msid, 0x0C4C7A86, fp->cur_anim_frame, 1.0f,
                              0.0f, NULL);
}

void ftKb_SpecialNMs_8010BC40(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 i;

    if ((s32) fp->fv.gw.x2238_panicCharge == 0x12) {
        i = ftKb_MS_MsSpecialNLoop;
    } else {
        i = ftKb_MS_FeSpecialNLoop;
    }

    Fighter_ChangeMotionState(gobj, i, 0x3200U, 0.0f, 1.0f, 0.0f, NULL);
}

void ftKb_SpecialNMs_8010BC90(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 i;

    if ((s32) fp->fv.gw.x2238_panicCharge == 0x12) {
        i = ftKb_MS_MsSpecialAirNLoop;
    } else {
        i = ftKb_MS_FeSpecialAirNLoop;
    }

    Fighter_ChangeMotionState(gobj, i, 0x3200U, 0.0f, 1.0f, 0.0f, NULL);
}

void ftKb_MsSpecialNEnd_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    struct ftKb_SpecialNMs_DatAttrs* ms_da;
    s32 i;
    HitCapsule* hit;
    PAD_STACK(24);
    if ((s32) fp->fv.kb.hat.kind == FTKIND_MARS) {
        ms_da = &da->ms;
    } else {
        ms_da = &da->fe;
    }
    if (fp->cmd_vars[0] == 0U) {
        hit = fp->x914;
        i = 0;
        do {
            if ((s32) hit->state == 1) {
                f32 dmg = (f32) (ms_da->base_damage +
                                 (fp->mv.kb.specialhi.x0 / 30) *
                                     ms_da->additional_damage_per_iteration);
                ftColl_8007ABD0(hit, (u32) dmg, gobj);
            }
            i += 1;
            hit = (HitCapsule*) ((u8*) hit + sizeof(HitCapsule));
        } while (i < 4);
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftKb_MsSpecialAirNEnd_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 i;
    ftKb_DatAttrs* da = fp->dat_attrs;
    struct ftKb_SpecialNMs_DatAttrs* ms_da;
    HitCapsule* hit;
    PAD_STACK(24);
    if ((s32) fp->fv.kb.hat.kind == FTKIND_MARS) {
        ms_da = &da->ms;
    } else {
        ms_da = &da->fe;
    }
    if (fp->cmd_vars[0] == 0U) {
        hit = fp->x914;
        i = 0;
        do {
            if ((s32) hit->state == 1) {
                f32 dmg = (f32) (ms_da->base_damage +
                                 (fp->mv.kb.specialhi.x0 / 30) *
                                     ms_da->additional_damage_per_iteration);
                ftColl_8007ABD0(hit, (u32) dmg, gobj);
            }
            i += 1;
            hit = (HitCapsule*) ((u8*) hit + sizeof(HitCapsule));
        } while (i < 4);
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

void ftKb_MsSpecialNEnd_IASA(Fighter_GObj* gobj) {}

void ftKb_MsSpecialAirNEnd_IASA(Fighter_GObj* gobj) {}

void ftKb_MsSpecialNEnd_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_MsSpecialAirNEnd_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_MsSpecialNEnd_Coll(Fighter_GObj* gobj)
{
    if (ft_80082708(gobj) == GA_Ground) {
        ftKb_SpecialNPe_8010BF90(gobj);
    }
}

void ftKb_MsSpecialAirNEnd_Coll(Fighter_GObj* gobj)
{
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftKb_SpecialNPe_8010C06C(gobj);
    }
}

void ftKb_SpecialNPe_8010BF90(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 msid;
    PAD_STACK(16);
    if (((Fighter*) gobj->user_data)->cmd_vars[0] == 0) {
        msid = (((Fighter*) gobj->user_data)->fv.kb.hat.kind == FTKIND_MARS)
                   ? ftKb_MS_MsSpecialAirNEnd0
                   : ftKb_MS_FeSpecialAirNEnd0;
    } else {
        msid = (((Fighter*) gobj->user_data)->fv.kb.hat.kind == FTKIND_MARS)
                   ? ftKb_MS_MsSpecialAirNEnd0 + 1
                   : ftKb_MS_FeSpecialAirNEnd0 + 1;
    }
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, msid, 0x0C4C708E, fp->cur_anim_frame,
                              ftKb_Init_804D9574, ftKb_Init_804D9570, NULL);
    if (fp->x2219_b0 == true) {
        fp->pre_hitlag_cb = efLib_PauseAll;
        fp->post_hitlag_cb = efLib_ResumeAll;
    }
}

void ftKb_SpecialNPe_8010C06C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 msid;
    PAD_STACK(16);
    if (((Fighter*) gobj->user_data)->cmd_vars[0] == 0) {
        msid = (((Fighter*) gobj->user_data)->fv.kb.hat.kind == FTKIND_MARS)
                   ? ftKb_MS_MsSpecialNEnd0
                   : ftKb_MS_FeSpecialNEnd0;
    } else {
        msid = (((Fighter*) gobj->user_data)->fv.kb.hat.kind == FTKIND_MARS)
                   ? ftKb_MS_MsSpecialNEnd0 + 1
                   : ftKb_MS_FeSpecialNEnd0 + 1;
    }
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, msid, 0x0C4C708E, fp->cur_anim_frame,
                              ftKb_Init_804D9574, ftKb_Init_804D9570, NULL);
    if (fp->x2219_b0 == true) {
        fp->pre_hitlag_cb = efLib_PauseAll;
        fp->post_hitlag_cb = efLib_ResumeAll;
    }
}

void ftKb_SpecialNPe_8010C148(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 msid;
    PAD_STACK(4 * 6);
    if (fp->cmd_vars[0] == 0U) {
        msid = ((s32) fp->fv.kb.hat.kind == FTKIND_MARS)
                   ? ftKb_MS_MsSpecialNEnd0
                   : ftKb_MS_FeSpecialNEnd0;
    } else {
        msid = ((s32) fp->fv.kb.hat.kind == FTKIND_MARS)
                   ? ftKb_MS_MsSpecialNEnd0 + 1
                   : ftKb_MS_FeSpecialNEnd0 + 1;
    }
    Fighter_ChangeMotionState(gobj, msid, 0x2000, 1.0F, 1.0F, 0.0F, NULL);
    GET_FIGHTER(gobj)->accessory4_cb = fn_8010B1F4;
}

void ftKb_SpecialNPe_8010C1E8(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 msid;
    PAD_STACK(4 * 6);
    if (fp->cmd_vars[0] == 0U) {
        msid = ((s32) fp->fv.kb.hat.kind == FTKIND_MARS)
                   ? ftKb_MS_MsSpecialAirNEnd0
                   : ftKb_MS_FeSpecialAirNEnd0;
    } else {
        msid = ((s32) fp->fv.kb.hat.kind == FTKIND_MARS)
                   ? ftKb_MS_MsSpecialAirNEnd0 + 1
                   : ftKb_MS_FeSpecialAirNEnd0 + 1;
    }
    Fighter_ChangeMotionState(gobj, msid, 0x2000, 1.0F, 1.0F, 0.0F, NULL);
    GET_FIGHTER(gobj)->accessory4_cb = fn_8010B1F4;
}

static void fn_8010C288(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!fp->cmd_vars[2]) {
        Vec3 pos;
        fp->cmd_vars[2] = true;
        lb_8000B1CC(fp->parts[FtPart_R3rdNa].joint, 0, &pos);
        fp->fv.kb.xD0 =
            it_802BDE18(gobj, &pos, FtPart_R3rdNa, 134, fp->facing_dir);
        if (fp->fv.kb.xD0 != NULL) {
            fp->death2_cb = &ftKb_Init_800EE74C;
            fp->take_dmg_cb = &ftKb_Init_800EE7B8;
        }
        fp->accessory4_cb = NULL;
        fp->pre_hitlag_cb = fn_8010C44C;
        fp->post_hitlag_cb = ftKb_SpecialNPe_8010C47C;
    }
}

void fn_8010C344(HSD_GObj* arg0)
{
    PAD_STACK(4);
    {
        Fighter* fp = arg0->user_data;
        Vec3 pos;
        PAD_STACK(4 * 2);
        lb_8000B1CC(fp->parts[FtPart_R3rdNa].joint, 0, &pos);
        pos.y += 2.5f;
        pos.z = 0;
        it_802BE214(arg0, &pos, 135, fp->facing_dir);
        fp->accessory4_cb = NULL;
    }
}

void ftKb_SpecialNPe_8010C3C0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_SpecialNPe_8010C47C(gobj);
    fp->fv.kb.xD0 = NULL;
}

void ftKb_SpecialNPe_8010C3F4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.kb.xD0 != NULL) {
        it_802BDF40(fp->fv.kb.xD0);
        ftKb_SpecialNPe_8010C3C0(gobj);
    }
}

void fn_8010C44C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.kb.xD0 != NULL) {
        it_802BDFA0(fp->fv.kb.xD0);
    }
}

void ftKb_SpecialNPe_8010C47C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.kb.xD0 != NULL) {
        it_802BDFC0(fp->fv.kb.xD0);
    }
}

bool ftKb_SpecialNPe_8010C4AC(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->motion_id >= ftKb_MS_PeSpecialLw &&
        fp->motion_id <= ftKb_MS_PeSpecialAirLwHit)
    {
        return false;
    }
    return true;
}

static void inlineA0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(4 * 2);
    fp->cmd_vars[0] = fp->cmd_vars[1] = fp->cmd_vars[2] = fp->cmd_vars[3] = 0;
    fp->mv.kb.specialn_pe.facing_dir = fp->facing_dir;
    fp->accessory4_cb = fn_8010C288;
}

static void inlineA1(HSD_GObj* gobj, ftKirby_MotionState msid)
{
    Fighter_ChangeMotionState(gobj, msid, 0, 0, 1, 0, NULL);
    ftAnim_8006EBA4(gobj);
    inlineA0(gobj);
}

void ftKb_SpecialNPe_8010C4D4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(4 * 2);
    fp->self_vel.y = 0;
    inlineA1(gobj, ftKb_MS_PeSpecialLw);
}

void ftKb_SpecialNPe_8010C560(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    struct ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(4 * 2);
    fp->self_vel.x /= da->specialn_pe_friction;
    inlineA1(gobj, ftKb_MS_PeSpecialAirLw);
}

static inline void doPeAnim(HSD_GObj* gobj, HSD_GObjEvent cb)
{
    Fighter* fp = GET_FIGHTER(gobj);
    u32 cmd_var1 = fp->cmd_vars[1];
    struct ftKb_DatAttrs* da = fp->dat_attrs;
    u8 _[4 * 4] = { 0 };

    if (cmd_var1 == 1) {
        fp->cmd_vars[1] = 2;
        ftColl_8007B1B8(gobj, (ShieldDesc*) &da->specialn_pe_absorbdesc,
                        fn_8010CD88);
        fp->x221B_b3 = true;
        fp->shield_unk0 = da->specialn_pe_unk3;
        fp->shield_unk1 = da->specialn_pe_unk3;
    } else if (cmd_var1 == 0) {
        fp->x221B_b0 = false;
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        cb(gobj);
    }
}

void ftKb_PeSpecialLw_Anim(HSD_GObj* gobj)
{
    doPeAnim(gobj, ft_8008A2BC);
}

void ftKb_PeSpecialAirLw_Anim(HSD_GObj* gobj)
{
    doPeAnim(gobj, ftCo_Fall_Enter);
}

void ftKb_PeSpecialLw_IASA(Fighter_GObj* gobj) {}

void ftKb_PeSpecialAirLw_IASA(Fighter_GObj* gobj) {}

void ftKb_PeSpecialLw_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
    ftColl_8007AEE0(gobj);
}

void ftKb_PeSpecialAirLw_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    u32 cmd_var0 = fp->cmd_vars[0];
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(4 * 4);
    if (cmd_var0 >= 1) {
        if (cmd_var0 == 1) {
            fp->cmd_vars[0] = 2;
            if (!fp->fv.kb.xCC) {
                fp->fv.kb.xCC = true;
                fp->self_vel.y = da->specialn_pe_air_initial_vertical_momentum;
            } else {
                fp->self_vel.y = 0;
            }
        }
        ftCommon_Fall(fp, da->specialn_pe_fall_acceleration,
                      da->specialn_pe_unk2);
    } else {
        ftCommon_FallBasic(fp);
    }
    ftCommon_ApplyFrictionAir(
        fp, da->specialn_pe_air_horizontal_momentum_preservation);
    ftColl_8007AEE0(gobj);
}

void ftKb_PeSpecialLw_Coll(HSD_GObj* gobj)
{
    if (!ft_800827A0(gobj)) {
        ftKb_SpecialNPe_8010C8D8(gobj);
    }
}

void ftKb_PeSpecialAirLw_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj)) {
        ftKb_SpecialNPe_8010C9CC(gobj);
    }
}

void ftKb_SpecialNPe_8010C8D8(HSD_GObj* gobj)
{
    /// @todo Flag names.
    static u32 const mf = (1 << 2) | (1 << 3) | (1 << 7) | (1 << 12) |
                          (1 << 14) | (1 << 18) | (1 << 19) | (1 << 22) |
                          (1 << 26) | (1 << 27);
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(4 * 2);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_PeSpecialAirLw, mf,
                              fp->cur_anim_frame, 1, 0, NULL);
    if (fp->cmd_vars[0] == 1) {
        fp->cmd_vars[0] = 2;
    }
    {
        /// @todo @c da can't move below @c fp
        ftKb_DatAttrs* da;
        Fighter* fp = GET_FIGHTER(gobj);
        da = fp->dat_attrs;
        if (fp->fv.kb.xD0 != NULL) {
            fp->death2_cb = ftKb_Init_800EE74C;
            fp->take_dmg_cb = ftKb_Init_800EE7B8;
        }

        fp->accessory4_cb = fn_8010C288;
        fp->pre_hitlag_cb = fn_8010C44C;
        fp->post_hitlag_cb = ftKb_SpecialNPe_8010C47C;

        if (fp->cmd_vars[1] == 2) {
            ftColl_8007B1B8(gobj, (ShieldDesc*) &da->specialn_pe_absorbdesc,
                            fn_8010CD88);
            fp->x221B_b3 = true;
        }
    }
}

void ftKb_SpecialNPe_8010C9CC(HSD_GObj* gobj)
{
    /// @todo Named flags.
    static u32 const mf = (1 << 2) | (1 << 3) | (1 << 7) | (1 << 12) |
                          (1 << 14) | (1 << 18) | (1 << 19) | (1 << 22) |
                          (1 << 26) | (1 << 27);
    Fighter* fp = GET_FIGHTER(gobj);
    fp->fv.kb.xCC = false;
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_PeSpecialLw, mf,
                              fp->cur_anim_frame, 1, 0, NULL);
    {
        /// @todo @c da can't move below @c fp
        ftKb_DatAttrs* da;
        Fighter* fp = GET_FIGHTER(gobj);
        PAD_STACK(4 * 2);
        da = fp->dat_attrs;
        if (fp->fv.kb.xD0 != NULL) {
            fp->death2_cb = ftKb_Init_800EE74C;
            fp->take_dmg_cb = ftKb_Init_800EE7B8;
        }
        fp->accessory4_cb = fn_8010C288;
        fp->pre_hitlag_cb = fn_8010C44C;
        fp->post_hitlag_cb = ftKb_SpecialNPe_8010C47C;

        if (fp->cmd_vars[1] == 2) {
            ftColl_8007B1B8(gobj, (ShieldDesc*) &da->specialn_pe_absorbdesc,
                            fn_8010CD88);
            fp->x221B_b3 = true;
        }
    }
}

static inline void doPeHitAnim(HSD_GObj* gobj, HSD_GObjEvent cb)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->cmd_vars[3]) {
        fp->cmd_vars[3] = false;
        fp->accessory4_cb = fn_8010C344;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        cb(gobj);
    }
}

void ftKb_PeSpecialLwHit_Anim(HSD_GObj* gobj)
{
    doPeHitAnim(gobj, ft_8008A2BC);
}

void ftKb_PeSpecialAirLwHit_Anim(HSD_GObj* gobj)
{
    doPeHitAnim(gobj, ftCo_Fall_Enter);
}

void ftKb_PeSpecialLwHit_IASA(Fighter_GObj* gobj) {}

void ftKb_PeSpecialAirLwHit_IASA(Fighter_GObj* gobj) {}

void ftKb_PeSpecialLwHit_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_PeSpecialAirLwHit_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(4 * 2);
    ftCommon_Fall(fp, da->specialn_pe_fall_acceleration, da->specialn_pe_unk2);
    ftCommon_ApplyFrictionAir(
        fp, da->specialn_pe_air_horizontal_momentum_preservation);
}

void ftKb_PeSpecialLwHit_Coll(HSD_GObj* gobj)
{
    if (!ft_800827A0(gobj)) {
        ftKb_SpecialNGw_8010CC6C(gobj);
    }
}

void ftKb_PeSpecialAirLwHit_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj)) {
        ftKb_SpecialNGw_8010CCD4(gobj);
    }
}

void ftKb_SpecialNGw_8010CC6C(HSD_GObj* gobj)
{
    /// @todo Named flags.
    static u32 const mf = (1 << 2) | (1 << 3) | (1 << 7) | (1 << 12) |
                          (1 << 14) | (1 << 18) | (1 << 19) | (1 << 22) |
                          (1 << 26) | (1 << 27);
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_PeSpecialAirLwHit, mf,
                              fp->cur_anim_frame, 1, 0, NULL);
    ftKb_SpecialNGw_8010CD44(gobj);
}

void ftKb_SpecialNGw_8010CCD4(HSD_GObj* gobj)
{
    /// @todo Named flags.
    static u32 const mf = (1 << 2) | (1 << 3) | (1 << 7) | (1 << 12) |
                          (1 << 14) | (1 << 18) | (1 << 19) | (1 << 22) |
                          (1 << 26) | (1 << 27);
    Fighter* fp = GET_FIGHTER(gobj);
    fp->fv.kb.xCC = false;
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_PeSpecialLwHit, mf,
                              fp->cur_anim_frame, 1, 0, NULL);
    ftKb_SpecialNGw_8010CD44(gobj);
}

void ftKb_SpecialNGw_8010CD44(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.kb.xD0 != NULL) {
        fp->death2_cb = ftKb_Init_800EE74C;
        fp->take_dmg_cb = ftKb_Init_800EE7B8;
    }
    fp->pre_hitlag_cb = fn_8010C44C;
    fp->post_hitlag_cb = ftKb_SpecialNPe_8010C47C;
}

void fn_8010CD88(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.kb.specialn_pe.facing_dir = fp->specialn_facing_dir;
    {
        ftKirby_MotionState msid;
        if (fp->ground_or_air == GA_Ground) {
            msid = ftKb_MS_PeSpecialLwHit;
        } else {
            msid = ftKb_MS_PeSpecialAirLwHit;
        }
        Fighter_ChangeMotionState(gobj, msid, 0, 9, 1, 0, 0);
    }
    ftAnim_8006EBA4(gobj);
    if (fp->fv.kb.xD0 != NULL) {
        it_802BE100(fp->fv.kb.xD0);
    }
    ftKb_SpecialNGw_8010CD44(gobj);
}

void fn_8010CE5C(Fighter_GObj* gobj)
{
    Vec3 vec0;
    Vec3 vec1;

    {
        u8 _[4] = { 0 };
        {
            int sausageCount[6];
            u8 _2[4] = { 0 };
            {
                Fighter* fp;
                {
                    u8 _3[8] = { 0 };
                    Fighter* fp2 = GET_FIGHTER(gobj);
                    ftKb_DatAttrs* da = fp2->dat_attrs;
                    if (fp2->cmd_vars[0] != 0) {
                        int var_r28;
                        fp2->cmd_vars[0] = var_r28 = 0;

                        if ((float) fp2->mv.kb.specialn_gw.maxSausage <
                            da->specialn_gw_max_sausages_per_use)
                        {
                            fp2->mv.kb.specialn_gw.maxSausage++;

                            vec1.x = ftKb_Init_804D9590;
                            vec1.y = ftKb_Init_804D9594;
                            vec1.z = ftKb_Init_804D9598;

                            lb_8000B1CC(fp2->parts[ftParts_GetBoneIndex(
                                                       fp2, FtPart_LThumbNb)]
                                            .joint,
                                        &vec1, &vec0);

                            {
                                int i;
                                int* pSausage;
                                fp = gobj->user_data;
                                pSausage = sausageCount;
                                for (i = 5, i -= 5; i < 5; i++) {
                                    if (i != fp->fv.kb.xD4 &&
                                        i != fp->fv.kb.xD8)
                                    {
                                        *pSausage++ = i;
                                        var_r28++;
                                    }
                                }
                                {
                                    int temp_r5 =
                                        sausageCount[HSD_Randi(var_r28)];
                                    int var_r6;
                                    fp->fv.kb.xD8 = fp->fv.kb.xD4;
                                    var_r6 = temp_r5;
                                    fp->fv.kb.xD4 = temp_r5;
                                    it_802C837C(gobj, &vec0, 0x9B, var_r6,
                                                fp2->facing_dir);
                                }
                            }
                        }
                        fp2->accessory4_cb = NULL;
                    }
                }
            }
        }
    }
}

void fn_8010CFB0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 pos;
    lb_8000B1CC(fp->parts[ftParts_GetBoneIndex(fp, FtPart_LThumbNb)].joint,
                NULL, &pos);
    fp->fv.kb.xDC = it_802C74D8(
        gobj, &pos, ftParts_GetBoneIndex(fp, FtPart_LThumbNb), fp->facing_dir);
    if (fp->fv.kb.xDC != NULL) {
        fp->death2_cb = ftKb_Init_800EE74C;
        fp->take_dmg_cb = ftKb_Init_800EE7B8;
    }
    fp->pre_hitlag_cb = fn_8010D100;
    fp->post_hitlag_cb = ftKb_SpecialNGw_8010D130;
    fp->accessory4_cb = fn_8010CE5C;
}

void ftKb_SpecialNGw_8010D074(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_SpecialNGw_8010D130(gobj);
    fp->fv.kb.xDC = NULL;
}

void ftKb_SpecialNGw_8010D0A8(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.kb.xDC != NULL) {
        it_802C760C(fp->fv.kb.xDC);
        ftKb_SpecialNGw_8010D074(gobj);
    }
}

void fn_8010D100(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.kb.xDC != NULL) {
        it_802C7658(fp->fv.kb.xDC);
    }
}

void ftKb_SpecialNGw_8010D130(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.kb.xDC != NULL) {
        it_802C7678(fp->fv.kb.xDC);
    }
}

bool ftKb_SpecialNGw_8010D160(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->motion_id >= ftKb_MS_GwSpecialN &&
        fp->motion_id <= ftKb_MS_GwSpecialAirN)
    {
        return false;
    }
    return true;
}

/// #ftGameWatch_SpecialN_SetVars with callback arg
inline void setGwVars(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    fp->cmd_vars[0] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[2] = 0;
    fp->mv.kb.specialn_gw.isChefLoopDisable = false;
    fp->mv.kb.specialn_gw.maxSausage = 0;
    fp->accessory4_cb = fn_8010CFB0;
}

void ftKb_SpecialNGw_8010D188(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->self_vel.y = 0.0F;
    Fighter_ChangeMotionState(gobj, ftKb_MS_GwSpecialN, 0, 0.0F, 1.0F, 0.0F,
                              NULL);
    ftAnim_8006EBA4(gobj);
    setGwVars(gobj);
}

void ftKb_SpecialNGw_8010D204(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->self_vel.y = 0;
    Fighter_ChangeMotionState(gobj, ftKb_MS_GwSpecialAirN, 0, 0, 1, 0, NULL);
    ftAnim_8006EBA4(gobj);
    setGwVars(gobj);
}

void ftKb_GwSpecialN_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(0x20);
    if (fp->cmd_vars[2] != 0) {
        fp->cmd_vars[2] = 0;
        if (fp->mv.kb.specialn_gw.maxSausage <
                da->specialn_gw_max_sausages_per_use &&
            !fp->mv.kb.specialn_gw.isChefLoopDisable)
        {
            ftKb_SpecialNGw_8010D660(gobj, da->specialn_gw_frame_on_repeat);
        }
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftKb_GwSpecialAirN_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(0x20);
    if (fp->cmd_vars[2] != 0) {
        fp->cmd_vars[2] = 0;
        if (!fp->mv.kb.specialn_gw.isChefLoopDisable &&
            fp->mv.kb.specialn_gw.maxSausage <
                da->specialn_gw_max_sausages_per_use)
        {
            ftKb_SpecialNGw_8010D6D0(gobj, da->specialn_gw_frame_on_repeat);
        }
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

void ftKb_GwSpecialN_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(0x8);
    if (!(fp->input.held_inputs & HSD_PAD_B)) {
        fp->mv.kb.specialn_gw.isChefLoopDisable = true;
    }
    if (fp->cmd_vars[1] != 0 && (fp->input.x668 & HSD_PAD_B) &&
        fp->mv.kb.specialn_gw.maxSausage <
            da->specialn_gw_max_sausages_per_use)
    {
        ftKb_SpecialNGw_8010D660(gobj, da->specialn_gw_frame_on_repeat);
    }
}

void ftKb_GwSpecialAirN_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(0x8);
    if (!(fp->input.held_inputs & HSD_PAD_B)) {
        fp->mv.kb.specialn_gw.isChefLoopDisable = true;
    }
    if (fp->cmd_vars[1] != 0 && (fp->input.x668 & HSD_PAD_B) &&
        fp->mv.kb.specialn_gw.maxSausage <
            da->specialn_gw_max_sausages_per_use)
    {
        ftKb_SpecialNGw_8010D6D0(gobj, da->specialn_gw_frame_on_repeat);
    }
}

void ftKb_GwSpecialN_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_GwSpecialAirN_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_GwSpecialN_Coll(Fighter_GObj* gobj)
{
    if (!ft_800827A0(gobj)) {
        ftKb_SpecialNGw_8010D580(gobj);
    }
}

void ftKb_GwSpecialAirN_Coll(Fighter_GObj* gobj)
{
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftKb_SpecialNGw_8010D5F0(gobj);
    }
}

void ftKb_SpecialNGw_8010D580(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_GwSpecialAirN, 0x0C4C508C,
                              fp->cur_anim_frame, 1.0F, 0.0F, NULL);

    fp = GET_FIGHTER(gobj);
    fp->accessory4_cb = fn_8010CE5C;
}

void ftKb_SpecialNGw_8010D5F0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_GwSpecialN, 0x0C4C508C,
                              fp->cur_anim_frame, 1.0F, 0.0F, NULL);

    fp = GET_FIGHTER(gobj);
    fp->accessory4_cb = fn_8010CE5C;
}

static inline void inline1(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[2] = 0;
    fp->mv.kb.specialn_gw.isChefLoopDisable = false;
    fp->accessory4_cb = fn_8010CE5C;
}

void ftKb_SpecialNGw_8010D660(Fighter_GObj* gobj, f32 arg1)
{
    PAD_STACK(8);
    Fighter_ChangeMotionState(gobj, ftKb_MS_GwSpecialN, 0x0C4C508C,
                              arg1 - 1.0F, 1.0F, 0.0F, NULL);
    ftAnim_8006EBA4(gobj);
    inline1(gobj);
}

void ftKb_SpecialNGw_8010D6D0(Fighter_GObj* gobj, f32 arg1)
{
    PAD_STACK(8);
    Fighter_ChangeMotionState(gobj, ftKb_MS_GwSpecialAirN, 0x0C4C508C,
                              arg1 - 1.0F, 1.0F, 0.0F, NULL);
    ftAnim_8006EBA4(gobj);
    inline1(gobj);
}
