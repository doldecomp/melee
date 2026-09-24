#include "mnstagesel.h"

#include <placeholder.h>

#include "forward.h"
#include "inlines.h"
#include "mnmain.h"
#include <melee/gm/gm_unsplit.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lb_013B.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lbdvd.h>
#include <melee/lb/lblanguage.h>
#include <melee/lb/types.h>
#include <sysdolphin/baselib/controller.h>
#include <sysdolphin/baselib/fog.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/gobjplink.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/gobjuserdata.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/lobj.h>
#include <sysdolphin/baselib/memory.h>
#include <sysdolphin/baselib/random.h>

#define MAX_ITER 100000
#define NUM_STAGES 29

static struct StageListInfo {
    /* +00 */ HSD_JObj* x0;
    /* +04 */ int x4;
    /* +08 */ u8 x8;
    /* +09 */ u8 x9;
    /* +0A */ u8 xA;
    /* +0B */ u8 stkind;
    /* +0C */ f32 xC;
    /* +10 */ f32 x10;
    /* +14 */ f32 x14;
    /* +18 */ f32 x18;
} mnStageSel_803F06D0[30] = {
    { 0, 0, 0x2, 0x00, 0x00, 0x04, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x01, 0x0C, 0x0B, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x02, 0x01, 0x05, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x03, 0x0D, 0x0C, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x04, 0x02, 0x0D, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x05, 0x0E, 0x0E, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x08, 0x04, 0x08, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x09, 0x10, 0x10, 2.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x0A, 0x05, 0x02, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x0B, 0x11, 0x11, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x0C, 0x06, 0x07, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x0D, 0x12, 0x16, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x06, 0x03, 0x06, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x07, 0x0F, 0x0F, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x12, 0x09, 0x09, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x13, 0x15, 0x12, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x10, 0x08, 0x0A, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x11, 0x14, 0x18, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x0E, 0x07, 0x03, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x0F, 0x13, 0x17, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x14, 0x0B, 0x13, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x15, 0x16, 0x14, 3.1F, 2.7F, 1.0F, 1.0F },
    { 0, 0, 0x2, 0x16, 0x0A, 0x19, 3.1F, 2.9F, 1.0F, 1.1F },
    { 0, 0, 0x2, 0x17, 0x17, 0x1B, 3.1F, 2.9F, 1.0F, 1.1F },
    { 0, 0, 0x2, 0x18, 0x18, 0x1F, 2.9F, 2.1F, 0.8F, 0.8F },
    { 0, 0, 0x2, 0x19, 0x19, 0x20, 2.9F, 2.1F, 0.8F, 0.8F },
    { 0, 0, 0x2, 0x1A, 0x1A, 0x1C, 2.9F, 2.1F, 0.8F, 0.8F },
    { 0, 0, 0x2, 0x1B, 0x1B, 0x1D, 2.9F, 2.1F, 0.8F, 0.8F },
    { 0, 0, 0x2, 0x1C, 0x1C, 0x1E, 2.9F, 2.1F, 0.8F, 0.8F },
    { 0, 0, 0x2, 0x1D, 0x00, 0x00, 3.6F, 2.7F, 1.2F, 1.0F },
};
ASSERT_SIZE(mnStageSel_803F06D0[0], 0x1C);

typedef struct MnSelectStageModels {
    /* +00 */ StaticModelDesc icon_large;
    /* +10 */ StaticModelDesc icon_random;
    /* +20 */ StaticModelDesc icon_special;
    /* +30 */ StaticModelDesc stage_name;
    /* +40 */ StaticModelDesc icon_stacked;
    /* +50 */ StaticModelDesc menu_border;
    /* +60 */ StaticModelDesc stage_preview;
    /* +70 */ StaticModelDesc icon_hover;
    /* +80 */ StaticModelDesc cursor;
    /* +90 */ StaticModelDesc layout;
    /* +A0 */ StaticModelDesc background;
    /* +B0 */ StaticModelDesc now_loading;
} MnSelectStageModels;

typedef struct MnSelectStageDataTable {
    /* 0x00 */ HSD_CObjDesc* cam;
    /* 0x04 */ HSD_LightDesc* light0;
    /* 0x08 */ HSD_LightDesc* light1;
    /* 0x0C */ HSD_FogDesc* fog;
    /* 0x10 */ MnSelectStageModels models;
} MnSelectStageDataTable;

static s8 mnStageSel_804D50A0 = -1;

static SSSData* sss_data;
static HSD_Archive* mnStageSel_804D6C94;
static MnSelectStageModels* sss_models;
static HSD_GObj* mnStageSel_804D6C9C;
static u32 mnStageSel_804D6CA0;
static u32 mnStageSel_804D6CA4;
static s32 mnStageSel_804D6CA8;
static s8 mnStageSel_804D6CAC;
static s8 mnStageSel_804D6CAD;
static u8 mnStageSel_804D6CAE;
static u8 mnStageSel_804D6CAF;

struct StageSelUserData {
    u16 x0;
    u16 x2;
    int x4;
};

/// @todo .sdata2 order hack
#ifdef MUST_MATCH
static void order_sdata2(void)
{
    (void) S32_TO_F32;
}
#endif

/// Random stage selection
/// Returns an internal stage ID - 2 (since first 2 internal stage IDs are
/// invalid)
int mnStageSel_802599EC(void)
{
    int var_r0;
    int iter;
    bool var_r29 = true;
    int i;

    for (i = 0; i < NUM_STAGES; i++) {
        if (mnStageSel_803F06D0[i].x4 >= 0 &&
            (u8) gm_80164330(mnStageSel_803F06D0[i].xA))
        {
            break;
        }
    }
    if (i == NUM_STAGES) {
        for (i = 0; i < NUM_STAGES; i++) {
            mnStageSel_803F06D0[i].x4 = 0;
        }
    }
    while (var_r29) {
        for (i = 0; i < NUM_STAGES; i++) {
            if (mnStageSel_803F06D0[i].x4 > 0) {
                mnStageSel_803F06D0[i].x4--;
            }
        }
        for (i = 0; i < NUM_STAGES; i++) {
            if (mnStageSel_803F06D0[i].x4 == 0 &&
                (u8) gm_80164330(mnStageSel_803F06D0[i].xA))
            {
                var_r29 = false;
            }
        }
    }
    for (iter = 0; iter < MAX_ITER; iter++) {
        int tmp = HSD_Randi(NUM_STAGES);
        i = tmp;
        if (mnStageSel_803F06D0[i].x4 == 0) {
            if ((u8) gm_80164330(mnStageSel_803F06D0[i].xA)) {
                break;
            }
        }
    }
    if (iter >= MAX_ITER) {
        i = 0;
    }
    mnStageSel_803F06D0[i].x4 = -1;
    if (i < 22) {
        if (i & 1) {
            var_r0 = i - 1;
        } else {
            var_r0 = i + 1;
        }
        if (mnStageSel_803F06D0[var_r0].x4 >= 0) {
            mnStageSel_803F06D0[var_r0].x4 = 3;
        }
    }
    return i;
}

void mnStageSel_80259C28(void)
{
    HSD_JObj* jobj;
    HSD_GObj* gobj;
    u64 _[2];

    if (mnStageSel_804D6CA4 != 0) {
        return;
    }
    switch (mnStageSel_804D6CAE) {
    case 30:
        if (!(mnStageSel_804D6CA0 & 0x1000)) {
            return;
        }
        break;
    case 29:
        if (!(mnStageSel_804D6CA0 & 0x1100)) {
            return;
        }
        break;
    default:
        if (!(mnStageSel_804D6CA0 & 0x1100)) {
            return;
        }
        if (mnStageSel_804D6CAE < 0x1E &&
            mnStageSel_803F06D0[mnStageSel_804D6CAE].x8 >= 2)
        {
            goto skip_randomize;
        }
        lbAudioAx_80024030(3);
        return;
    }
    mnStageSel_804D6CAE = mnStageSel_802599EC();
skip_randomize:

    gobj = GObj_Create(HSD_GOBJ_CLASS_FIGHTER, 5, 0x80);
    jobj = HSD_JObjLoadJoint(sss_models->now_loading.joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_JObjKind, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 4, 0x87);
    HSD_GObj_SetupProc(gobj, mn_8022EAE0, 0);
    HSD_JObjAddAnimAll(jobj, sss_models->now_loading.animjoint,
                       sss_models->now_loading.matanim_joint,
                       sss_models->now_loading.shapeanim_joint);
    HSD_JObjReqAnimAll(gobj->hsd_obj, 0.0F);
    HSD_JObjAnimAll(gobj->hsd_obj);
    mnStageSel_804D6CAF = 1;
    mnStageSel_804D6CA4 = 0x1E;
    sfxForward();
}

void fn_80259D84(HSD_GObj* gobj)
{
    struct StageSelUserData* temp_r31 = HSD_GObjGetUserData(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);

    switch (temp_r31->x2) {
    case 0:
        if (mnStageSel_804D6CAF == 0) {
            mnStageSel_80259C28();
        }
        if (++temp_r31->x4 >= 9U) {
            HSD_ForeachAnim(jobj, JOBJ_TYPE, ALL_TYPE_MASK, HSD_AObjStopAnim,
                            AOBJ_ARG_AOV, 0, 0);
            temp_r31->x2 = 1;
        }
        break;
    case 1:
        if (mnStageSel_804D6CAF == 0) {
            mnStageSel_80259C28();
        }
        if (temp_r31->x0 != mnStageSel_804D6CAE) {
            if (temp_r31->x0 < 0x1E &&
                mnStageSel_803F06D0[temp_r31->x0].x8 >= 2)
            {
                HSD_JObjReqAnimAllByFlags(jobj, 1, 10.0F);
            }
            sfxMove();
            temp_r31->x4 = 0;
            temp_r31->x2 = 2;
            mnStageSel_80259ED8(mnStageSel_804D6CAE);
        }
        break;
    case 2:
        if (++temp_r31->x4 > 0xAU) {
            HSD_GObjFree(gobj);
            temp_r31->x2++;
        }
        break;
    }
}

static void do_anim(HSD_JObj* jobj, int frame)
{
    HSD_JObjReqAnimAll(jobj, 0.0F);
    HSD_JObjReqAnimAllByFlags(jobj, 0x10, frame);
    HSD_JObjAnimAll(jobj);
    HSD_ForeachAnim(jobj, JOBJ_TYPE, TOBJ_MASK, HSD_AObjStopAnim, AOBJ_ARG_AOV,
                    0, 0);
}

void mnStageSel_80259ED8(int id)
{
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    struct StageSelUserData* temp_r3_2;
    u8 _[4];

    gobj = GObj_Create(HSD_GOBJ_CLASS_FIGHTER, 5, 0x80);
    jobj = HSD_JObjLoadJoint(sss_models->stage_name.joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_JObjKind, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 4, 0x84);
    HSD_GObj_SetupProc(gobj, mn_8022EAE0, 1);
    HSD_JObjAddAnimAll(jobj, sss_models->stage_name.animjoint,
                       sss_models->stage_name.matanim_joint,
                       sss_models->stage_name.shapeanim_joint);
    jobj = GET_JOBJ(gobj);
    temp_r3_2 = HSD_MemAlloc(sizeof(struct StageSelUserData));
    GObj_InitUserData(gobj, 4, HSD_Free, temp_r3_2);
    HSD_GObj_SetupProc(gobj, fn_80259D84, 1);
    temp_r3_2->x0 = id;
    temp_r3_2->x4 = 0;
    temp_r3_2->x2 = 0;
    if (id < 0x1E && mnStageSel_803F06D0[id].x8 >= 2) {
        do_anim(jobj, 20.0F * mnStageSel_803F06D0[id].x9);
    }
}

void fn_8025A090(HSD_GObj* gobj)
{
    u32 var_r3;
    struct {
        u32 x0;
        u32 x4;
    }* temp_r30;
    HSD_JObj* jobj;

    jobj = GET_JOBJ(gobj);
    temp_r30 = HSD_GObjGetUserData(gobj);
    var_r3 = mnStageSel_804D6CAE;
    if (mnStageSel_803F06D0[mnStageSel_804D6CAE].x8 < 2) {
        var_r3 = 0x1E;
    }
    if (temp_r30->x0 != var_r3) {
        temp_r30->x0 = var_r3;
        temp_r30->x4 = 0;
        if ((s32) var_r3 < 0x1D) {
            HSD_JObjReqAnimAll(jobj, 50.0F * mnStageSel_803F06D0[var_r3].x9);
            HSD_JObjAnimAll(jobj);
            HSD_ForeachAnim(jobj, JOBJ_TYPE, ALL_TYPE_MASK, HSD_AObjStopAnim,
                            AOBJ_ARG_AOV, 0, 0);
            HSD_JObjSetTranslateX(jobj, 0.0F);
        } else {
            HSD_JObjSetTranslateX(jobj, 100.0F);
        }
    }
    if (temp_r30->x4 < 0x5A) {
        temp_r30->x4++;
        if (temp_r30->x4 == 0x14) {
            HSD_JObjReqAnimAll(jobj,
                               50.0F * mnStageSel_803F06D0[temp_r30->x0].x9);
        }
        if (temp_r30->x4 == 0x45) {
            HSD_ForeachAnim(jobj, JOBJ_TYPE, ALL_TYPE_MASK, HSD_AObjStopAnim,
                            AOBJ_ARG_AOV, 0, 0);
        }
    } else if (mnStageSel_804D6CAF) {
        mnStageSel_804D6CAF = 2;
    }
}

void fn_8025A310(HSD_GObj* gobj)
{
    Vec3 sp1C;
    Vec3 sp10;
    f32 temp_f1;
    f32 temp_f2;
    int i;
    HSD_JObj* jobj;
    u32 unused;

    jobj = gobj->hsd_obj;
    if (mnStageSel_804D6CAF != 0) {
        HSD_JObjSetFlags(jobj, JOBJ_HIDDEN);
        return;
    }
    HSD_JObjGetTranslation(jobj, &sp1C);
    sp1C.x = 0.03f * mnStageSel_804D6CAC + sp1C.x;
    if (-27.0F > sp1C.x) {
        sp1C.x = -27.0F;
    }
    if (27.0F < sp1C.x) {
        sp1C.x = 27.0F;
    }
    sp1C.y = 0.03f * mnStageSel_804D6CAD + sp1C.y;
    if (-19.0F > sp1C.y) {
        sp1C.y = -19.0F;
    }
    if (19.0F < sp1C.y) {
        sp1C.y = 19.0F;
    }

    HSD_JObjSetTranslate(jobj, &sp1C);
    lb_8000B1CC(jobj, NULL, &sp1C);
    for (i = 0; i < 0x1E; i++) {
        if (mnStageSel_803F06D0[i].x8 != 0) {
            lb_8000B1CC(mnStageSel_803F06D0[i].x0, NULL, &sp10);
            temp_f2 = sp10.x;
            temp_f1 = mnStageSel_803F06D0[i].xC;
            if (temp_f2 - temp_f1 < sp1C.x && temp_f2 + temp_f1 > sp1C.x) {
                if (sp10.y - mnStageSel_803F06D0[i].x10 < sp1C.y &&
                    sp10.y + mnStageSel_803F06D0[i].x10 > sp1C.y)
                {
                    mnStageSel_804D6CAE = i;
                    return;
                }
            }
        }
    }
}

void fn_8025A560(HSD_GObj* gobj)
{
    struct StageSelUserData {
        int x0;
    }* temp_r30;
    Vec3 sp10;
    HSD_JObj* jobj = GET_JOBJ(gobj);
    temp_r30 = HSD_GObjGetUserData(gobj);

    if (mnStageSel_804D6CAE < 0x16 && (mnStageSel_804D6CAE & 1) &&
        mnStageSel_803F06D0[mnStageSel_804D6CAE].x8 == 0)
    {
        HSD_JObjSetTranslateX(jobj, 100.0F);
    } else if (mnStageSel_804D6CAE < 0x1E) {
        lb_8000B1CC(mnStageSel_803F06D0[mnStageSel_804D6CAE].x0, NULL, &sp10);
        HSD_JObjSetTranslateX(jobj, sp10.x);
        HSD_JObjSetTranslateY(jobj, sp10.y);
        HSD_JObjSetScaleX(jobj, mnStageSel_803F06D0[mnStageSel_804D6CAE].x14);
        HSD_JObjSetScaleY(jobj, mnStageSel_803F06D0[mnStageSel_804D6CAE].x18);
    } else {
        HSD_JObjSetTranslateX(jobj, 100.0F);
    }
    if (mnStageSel_804D6CAF != 0) {
        HSD_JObjReqAnimAll(jobj, 0.0F);
        HSD_JObjAnimAll(jobj);
        return;
    }
    if (++temp_r30->x0 >= 10) {
        temp_r30->x0 = 0;
        HSD_JObjReqAnimAll(jobj, 0.0F);
        HSD_JObjAnimAll(jobj);
    }
}

void fn_8025A91C(HSD_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    if (++mnStageSel_804D6CA8 >= 0xFA) {
        mnStageSel_804D6CA8 = 0;
        HSD_JObjReqAnimAll(jobj, 0.0F);
        HSD_JObjAnimAll(jobj);
    }
}

void fn_8025A974(HSD_GObj* gobj, intptr_t unused)
{
    HSD_FogSet(gobj->hsd_obj);
}

static const Vec3 mnStageSel_803B8550 = { 0, -13, 0 };

static inline void make_stage_icon(HSD_JObj** out)
{
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    gobj = GObj_Create(4, 5, 0x80);
    jobj = HSD_JObjLoadJoint(sss_models->icon_stacked.joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_JObjKind, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 4, 0x83);
    HSD_GObj_SetupProc(gobj, mn_8022EAE0, 3);
    HSD_JObjAddAnimAll(jobj, sss_models->icon_stacked.animjoint,
                       sss_models->icon_stacked.matanim_joint,
                       sss_models->icon_stacked.shapeanim_joint);
    *out = GET_JOBJ(gobj);
}

static inline void attach_menu_model(HSD_GObj* gobj)
{
    HSD_JObj* jobj;
    jobj = HSD_JObjLoadJoint(sss_models->background.joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_JObjKind, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 4, 0x80);
    HSD_GObj_SetupProc(gobj, mn_8022EAE0, 0);
    HSD_JObjAddAnimAll(jobj, sss_models->background.animjoint,
                       sss_models->background.matanim_joint,
                       sss_models->background.shapeanim_joint);
}

static inline void make_bg_model(HSD_JObj** out)
{
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    gobj = GObj_Create(4, 5, 0x80);
    jobj = HSD_JObjLoadJoint(sss_models->menu_border.joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_JObjKind, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 4, 0x82);
    HSD_GObj_SetupProc(gobj, mn_8022EAE0, 0);
    HSD_JObjAddAnimAll(jobj, sss_models->menu_border.animjoint,
                       sss_models->menu_border.matanim_joint,
                       sss_models->menu_border.shapeanim_joint);
    *out = gobj->hsd_obj;
}

static inline void make_icon_root(HSD_JObj** icons)
{
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    gobj = GObj_Create(4, 5, 0x80);
    jobj = HSD_JObjLoadJoint(sss_models->layout.joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_JObjKind, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 4, 0x82);
    HSD_GObj_SetupProc(gobj, mn_8022EAE0, 4);
    HSD_JObjAddAnimAll(jobj, sss_models->layout.animjoint,
                       sss_models->layout.matanim_joint,
                       sss_models->layout.shapeanim_joint);
    icons[0] = GET_JOBJ(gobj)->child;
    HSD_JObjReqAnimAll(icons[0], 0.0F);
    HSD_JObjAnimAll(icons[0]);
}

static inline HSD_JObj* get_jobj(HSD_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    return jobj;
}

void mnStageSel_Scene_OnEnter(void* arg0)
{
    HSD_JObj* spDC[0x13];
    u8 _[0xDC - 0xD8];
    Vec3 spCC;

    int i;
    MnSelectStageDataTable* sss_data_table;

    PAD_STACK(0xDC - 0x50);

    sss_data = (SSSData*) arg0;

    if (sss_data->force_stage_id < 0) {
        if (lbLang_IsSavedLanguageUS() != 0) {
            mnStageSel_804D6C94 = lbArchive_LoadArchive("MnSlMap.usd");
        } else {
            mnStageSel_804D6C94 = lbArchive_LoadArchive("MnSlMap.dat");
        }
        sss_data_table = HSD_ArchiveGetPublicAddress(mnStageSel_804D6C94,
                                                     "MnSelectStageDataTable");
        MenMain_cam = sss_data_table->cam;
        sss_models = &sss_data_table->models;
        mnStageSel_804D6CAF = 0;
        mnStageSel_804D6CA0 = 0;
        mnStageSel_804D6CAC = 0;
        mnStageSel_804D6CAD = 0;
        mnStageSel_804D6CAE = 0x1E;
        mnStageSel_804D50A0 = sss_data->unk_stage - 1;
        mnStageSel_804D6CA4 = 0x14;

        {
            HSD_GObj* gobj = mnStageSel_804D6C9C = GObj_Create(2, 3, 0x80);
            HSD_CObj* cobj = HSD_CObjLoadDesc(MenMain_cam);
            HSD_GObjObject_80390A70(gobj, HSD_GObj_CameraKind, cobj);
            GObj_SetupGXLinkMax(gobj, HSD_GObj_803910D8, 0);
            gobj->gxlink_prios = 0x11;
            HSD_GObj_SetupProc(gobj, mn_8022BA1C, 5);
        }

        {
            HSD_GObj* gobj;
            HSD_LObj* lobj1;
            HSD_LObj* lobj2;
            gobj = GObj_Create(3, 4, 0x80);
            lobj1 = HSD_LObjLoadDesc(sss_data_table->light0);
            lobj2 = HSD_LObjLoadDesc(sss_data_table->light1);
            HSD_LObjSetNext(lobj1, lobj2);
            HSD_GObjObject_80390A70(gobj, (u8) HSD_GObj_LightKind, lobj1);
            GObj_SetupGXLink(gobj, HSD_GObj_LObjCallback, 0, 0x80);
        }

        {
            HSD_GObj* gobj = GObj_Create(0xE, 0xF, 0);
            HSD_Fog* fog = HSD_FogLoadDesc(sss_data_table->fog);
            HSD_GObjObject_80390A70(gobj, HSD_GObj_FogKind, fog);
            GObj_SetupGXLink(gobj, fn_8025A974, 0, 0x80);
        }

        {
            HSD_JObj* jobj2;
            HSD_GObj* gobj;
            gobj = GObj_Create(4, 5, 0x80);
            attach_menu_model(gobj);
            {
                HSD_GObj* g = gobj;
                jobj2 = GET_JOBJ(g);
                HSD_GObj_SetupProc(g, fn_8025A91C, 0);
                HSD_JObjReqAnimAll(jobj2, 0.0F);
                HSD_JObjAnimAll(jobj2);
            }
        }

        {
            HSD_JObj* temp_r22_4;
            make_bg_model(&temp_r22_4);
            HSD_JObjReqAnimAll(temp_r22_4, 0.0F);
            HSD_JObjAnimAll(temp_r22_4);
        }

        make_icon_root(spDC);

        for (i = 0; i < 0x12; i++) {
            spDC[i + 1] = spDC[i]->next;
            HSD_JObjReqAnimAll(spDC[i + 1], 0.0F);
            HSD_JObjAnimAll(spDC[i + 1]);
        }

        for (i = 0; i < 0x1D; i++) {
            mnStageSel_803F06D0[i].x8 =
                gm_80164430(mnStageSel_803F06D0[i].stkind) ? 2 : 1;
        }

        for (i = 0; i <= 0xA; i++) {
            HSD_JObj* temp_r22_6;
            HSD_JObj* jobj;
            make_stage_icon(&temp_r22_6);
            jobj = temp_r22_6;
            lb_8000C1C0(jobj, spDC[i]);
            mnStageSel_803F06D0[i * 2].x0 = temp_r22_6->child->next;
            switch (mnStageSel_803F06D0[i * 2].x8) {
            case 0:
                HSD_JObjSetFlags(mnStageSel_803F06D0[i * 2].x0, JOBJ_HIDDEN);
                break;
            case 1:
                HSD_JObjReqAnimAllByFlags(mnStageSel_803F06D0[i * 2].x0, 0x10,
                                          1.0F);
                break;
            default:
                HSD_JObjReqAnimAllByFlags(mnStageSel_803F06D0[i * 2].x0, 0x10,
                                          mnStageSel_803F06D0[i * 2].x9 / 2 +
                                              2);
                break;
            }
            mnStageSel_803F06D0[i * 2 + 1].x0 = temp_r22_6->child;
            switch (mnStageSel_803F06D0[i * 2 + 1].x8) {
            case 0:
                HSD_JObjSetFlags(mnStageSel_803F06D0[i * 2 + 1].x0,
                                 JOBJ_HIDDEN);
                break;
            case 1:
                HSD_JObjReqAnimAllByFlags(mnStageSel_803F06D0[i * 2 + 1].x0,
                                          0x10, 1.0F);
                break;
            default:
                HSD_JObjReqAnimAllByFlags(
                    mnStageSel_803F06D0[i * 2 + 1].x0, 0x10,
                    mnStageSel_803F06D0[i * 2 + 1].x9 / 2 + 2);
                break;
            }
            HSD_JObjAnimAll(jobj);
            HSD_ForeachAnim(jobj, JOBJ_TYPE, TOBJ_MASK, HSD_AObjStopAnim,
                            AOBJ_ARG_AOV, 0, 0);
        }

        for (i = 0xB; i <= 0xF; i++) {
            HSD_JObj* jobj;
            HSD_GObj* gobj = GObj_Create(4, 5, 0x80);
            s32 temp_r22_7;
            HSD_JObj* temp_r23_3;
            jobj = HSD_JObjLoadJoint(sss_models->icon_special.joint);
            HSD_GObjObject_80390A70(gobj, HSD_GObj_JObjKind, jobj);
            GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 4, 0x83);
            HSD_GObj_SetupProc(gobj, mn_8022EAE0, 3);
            HSD_JObjAddAnimAll(jobj, sss_models->icon_special.animjoint,
                               sss_models->icon_special.matanim_joint,
                               sss_models->icon_special.shapeanim_joint);
            temp_r23_3 = gobj->hsd_obj;
            lb_8000C1C0(temp_r23_3, spDC[i]);
            mnStageSel_803F06D0[i + 13].x0 = temp_r23_3;
            switch (mnStageSel_803F06D0[i + 13].x8) {
            case 1:
                mnStageSel_803F06D0[i + 13].x8 = 0;
                /* fallthrough */
            case 0:
                HSD_JObjSetFlagsAll(temp_r23_3, JOBJ_HIDDEN);
                break;
            default:
                temp_r22_7 = mnStageSel_803F06D0[i + 13].x9 - 0x16;
                do_anim(temp_r23_3, temp_r22_7);
                break;
            }
        }

        {
            HSD_JObj* jobj;
            HSD_GObj* gobj = GObj_Create(4, 5, 0x80);
            HSD_JObj* temp_r22_8;
            jobj = HSD_JObjLoadJoint(sss_models->icon_random.joint);
            HSD_GObjObject_80390A70(gobj, HSD_GObj_JObjKind, jobj);
            GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 4, 0x83);
            HSD_GObj_SetupProc(gobj, mn_8022EAE0, 3);
            HSD_JObjAddAnimAll(jobj, sss_models->icon_random.animjoint,
                               sss_models->icon_random.matanim_joint,
                               sss_models->icon_random.shapeanim_joint);
            temp_r22_8 = gobj->hsd_obj;
            lb_8000C1C0(temp_r22_8, spDC[0x10]);
            do_anim(temp_r22_8, 2);
            mnStageSel_803F06D0[0x1D].x0 = temp_r22_8;
        }

        for (i = 0x11; i <= 0x12; i++) {
            HSD_JObj* jobj;
            HSD_AnimJoint* animjoint;
            HSD_GObj* gobj = GObj_Create(4, 5, 0x80);
            s32 temp_r22_9;
            HSD_JObj* temp_r23_6;
            jobj = HSD_JObjLoadJoint(sss_models->icon_large.joint);
            HSD_GObjObject_80390A70(gobj, HSD_GObj_JObjKind, jobj);
            GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 4, 0x83);
            HSD_GObj_SetupProc(gobj, mn_8022EAE0, 3);
            animjoint = sss_models->icon_large.animjoint;
            HSD_JObjAddAnimAll(jobj, animjoint,
                               sss_models->icon_large.matanim_joint,
                               sss_models->icon_large.shapeanim_joint);

            temp_r23_6 = gobj->hsd_obj;
            lb_8000C1C0(temp_r23_6, spDC[i]);
            mnStageSel_803F06D0[i + 5].x0 = temp_r23_6;
            switch (mnStageSel_803F06D0[i + 5].x8) {
            case 1:
                mnStageSel_803F06D0[i + 5].x8 = 0;
                /* fallthrough */
            case 0:
                HSD_JObjSetFlagsAll(temp_r23_6, JOBJ_HIDDEN);
                break;
            default:
                temp_r22_9 = mnStageSel_803F06D0[i + 5].x9 - 0x14;
                do_anim(temp_r23_6, temp_r22_9);
                break;
            }
        }

        {
            HSD_JObj* jobj;
            HSD_GObj* gobj;
            gobj = GObj_Create(4, 5, 0x80);
            jobj = HSD_JObjLoadJoint(sss_models->cursor.joint);
            HSD_GObjObject_80390A70(gobj, HSD_GObj_JObjKind, jobj);
            GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 4, 0x86);
            HSD_GObj_SetupProc(gobj, mn_8022EAE0, 2);
            HSD_JObjAddAnimAll(jobj, sss_models->cursor.animjoint,
                               sss_models->cursor.matanim_joint,
                               sss_models->cursor.shapeanim_joint);

            {
                HSD_JObj* jobj2;
                HSD_GObj* g;
                jobj = get_jobj(gobj);
                spCC = mnStageSel_803B8550;
                g = gobj;
                jobj2 = jobj;
                HSD_GObj_SetupProc(g, fn_8025A310, 2);
                do_anim(jobj2, mnStageSel_804D50A0 + 1);
                HSD_JObjSetTranslate(jobj2, &spCC);
            }
        }

        {
            HSD_JObj* jobj;
            HSD_GObj* gobj;
            gobj = GObj_Create(HSD_GOBJ_CLASS_FIGHTER, 5, 0x80);
            jobj = HSD_JObjLoadJoint(sss_models->stage_name.joint);
            HSD_GObjObject_80390A70(gobj, HSD_GObj_JObjKind, jobj);
            GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 4, 0x84);
            HSD_GObj_SetupProc(gobj, mn_8022EAE0, 1);
            HSD_JObjAddAnimAll(jobj, sss_models->stage_name.animjoint,
                               sss_models->stage_name.matanim_joint,
                               sss_models->stage_name.shapeanim_joint);
            {
                struct StageSelUserData* userdata;
                HSD_JObj* jobj = GET_JOBJ(gobj);
                userdata = HSD_MemAlloc(sizeof(struct StageSelUserData));
                GObj_InitUserData(gobj, 4, HSD_Free, userdata);
                HSD_GObj_SetupProc(gobj, fn_80259D84, 1);
                userdata->x0 = 0x1E;
                userdata->x4 = 0;
                userdata->x2 = 0;
            }
        }

        {
            HSD_JObj* jobj;
            HSD_GObj* gobj = GObj_Create(4, 5, 0x80);
            jobj = HSD_JObjLoadJoint(sss_models->stage_preview.joint);
            HSD_GObjObject_80390A70(gobj, HSD_GObj_JObjKind, jobj);
            GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 4, 0x81);
            HSD_GObj_SetupProc(gobj, mn_8022EAE0, 1);
            HSD_JObjAddAnimAll(jobj, sss_models->stage_preview.animjoint,
                               sss_models->stage_preview.matanim_joint,
                               sss_models->stage_preview.shapeanim_joint);

            {
                HSD_GObj* g;
                HSD_JObj* jobj;
                struct foo {
                    int x0, x4;
                }* temp_r3_14;
                g = gobj;
                jobj = GET_JOBJ(g);
                temp_r3_14 = HSD_MemAlloc(sizeof(*temp_r3_14));
                GObj_InitUserData(g, 4, HSD_Free, temp_r3_14);
                HSD_GObj_SetupProc(g, fn_8025A090, 1);
                HSD_JObjReqAnimAll(jobj, 0.0F);
                HSD_JObjAnimAll(jobj);
                HSD_ForeachAnim(jobj, JOBJ_TYPE, ALL_TYPE_MASK,
                                HSD_AObjStopAnim, AOBJ_ARG_AOV, 0, 0);
                HSD_JObjSetTranslateX(jobj, 100.0F);
                temp_r3_14->x0 = 0x1E;
                temp_r3_14->x4 = 0;
            }
        }

        {
            HSD_JObj* jobj;
            HSD_GObj* gobj = GObj_Create(4, 5, 0x80);
            HSD_JObj* temp_r3_15 =
                HSD_JObjLoadJoint(sss_models->icon_hover.joint);
            s32* temp_r3_16;
            HSD_GObjObject_80390A70(gobj, HSD_GObj_JObjKind, temp_r3_15);
            GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 4, 0x85);
            HSD_GObj_SetupProc(gobj, mn_8022EAE0, 1);
            HSD_JObjAddAnimAll(temp_r3_15, sss_models->icon_hover.animjoint,
                               sss_models->icon_hover.matanim_joint,
                               sss_models->icon_hover.shapeanim_joint);
            jobj = gobj->hsd_obj;
            temp_r3_16 = HSD_MemAlloc(sizeof(*temp_r3_16));
            GObj_InitUserData(gobj, 4, HSD_Free, temp_r3_16);
            *temp_r3_16 = 0;
            HSD_GObj_SetupProc(gobj, fn_8025A560, 1);
            HSD_JObjSetTranslateX(jobj, 100.0F);
        }

        lbAudioAx_80023F28(gmMainLib_8015ECB0());
    }
}

static inline HSD_PadStatus* get_pad(u8 i)
{
    return &HSD_PadCopyStatus[i];
}

/// OnFrame
void mnStageSel_Scene_OnFrame(void)
{
    if (sss_data->force_stage_id >= 0) {
        mnStageSel_804D6CAF = 2;
        sss_data->vs.start.rules.stkind = sss_data->force_stage_id;
        gm_801A4B60();
        return;
    }
    if (sss_data->no_lras == 0 && mn_8022F218()) {
        sfxBack();
        lb_800145F4();
        HSD_GObjFree(mnStageSel_804D6C9C);
        mn_8022F268();
        gm_ChangeGameModeAfterCurrentScene(GM_MENU);
        gm_801A4B60();
        return;
    }
    if (mnStageSel_804D50A0 < 0) {
        mnStageSel_804D6CA0 = 0;
        mnStageSel_804D6CA0 |= HSD_PadCopyStatus[0].trigger;
        mnStageSel_804D6CA0 |= HSD_PadCopyStatus[1].trigger;
        mnStageSel_804D6CA0 |= HSD_PadCopyStatus[2].trigger;
        mnStageSel_804D6CA0 |= HSD_PadCopyStatus[3].trigger;
        {
            int i;
            for (i = 0; i < 4; i++) {
                mnStageSel_804D6CAC = get_pad(i)->stickX;
                mnStageSel_804D6CAD = get_pad(i)->stickY;
                if (get_pad(i)->stickX < -0x1E || get_pad(i)->stickX > +0x1E ||
                    get_pad(i)->stickY < -0x1E || get_pad(i)->stickY > +0x1E)
                {
                    break;
                }
            }
        }
    } else {
        mnStageSel_804D6CA0 = get_pad(mnStageSel_804D50A0)->trigger;
        mnStageSel_804D6CAC = get_pad(mnStageSel_804D50A0)->stickX;
        mnStageSel_804D6CAD = get_pad(mnStageSel_804D50A0)->stickY;
    }
    if (mnStageSel_804D6CAC < -0x1E) {
        mnStageSel_804D6CAC += 0x1E;
    } else if (mnStageSel_804D6CAC > 0x1E) {
        mnStageSel_804D6CAC -= 0x1E;
    } else {
        mnStageSel_804D6CAC = 0;
    }
    if (mnStageSel_804D6CAD < -0x1E) {
        mnStageSel_804D6CAD += 0x1E;
    } else if (mnStageSel_804D6CAD > 0x1E) {
        mnStageSel_804D6CAD -= 0x1E;
    } else {
        mnStageSel_804D6CAD = 0;
    }
    if (mnStageSel_804D6CA4 != 0) {
        mnStageSel_804D6CA4 -= 1;
        return;
    }
    if (sss_data->x1 == 0 && (mnStageSel_804D6CA0 & 0x200) &&
        mnStageSel_804D6CAF == 0)
    {
        sfxBack();
        gm_801A4B60();
    }
    if (mnStageSel_804D6CAF == 2) {
        sss_data->vs.start.rules.stkind =
            mnStageSel_803F06D0[mnStageSel_804D6CAE].stkind;
        gm_801A4B60();
    }
}

void mnStageSel_Scene_OnExit(UNUSED void* exit_data)
{
    if (mnStageSel_804D6C94 != NULL) {
        lbArchive_80016EFC(mnStageSel_804D6C94);
        mnStageSel_804D6C94 = NULL;
    }
    {
        SSSData* sss = sss_data;
        sss->start_game = mnStageSel_804D6CAF == 2 ? true : false;
        if (sss->start_game) {
            PreloadedGameModeState* cache = lbDvd_GetPreloadCacheScene();
            cache->game_cache.stkind = sss->vs.start.rules.stkind;
            lbDvd_80018254();
        }
    }
}

int mnSelStageRandom(void)
{
    return mnStageSel_803F06D0[mnStageSel_802599EC()].stkind;
}

int mnStageSel_8025BC08(int idx)
{
    return mnStageSel_803F06D0[idx].stkind;
}
