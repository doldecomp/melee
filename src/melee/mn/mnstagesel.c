#include "mnstagesel.h"

#include "mnstagesel.static.h"

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
#include <melee/gm/gm_unsplit.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lb_00F9.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lbdvd.h>
#include <melee/lb/lblanguage.h>
#include <melee/lb/types.h>
#include <melee/mn/mnmain.h>

// Random stage selection
// Returns an internal stage ID - 2 (since first 2 internal stage IDs are
// invalid)
int mnStageSel_802599EC(void)
{
    int var_r0;
    int iter;
    bool var_r29 = true;
    int i;

    for (i = 0; i < NUM_STAGES; i++) {
        if (mnStageSel_803F06D0[i].x4 >= 0 &&
            gm_80164330(mnStageSel_803F06D0[i].xA))
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
                gm_80164330(mnStageSel_803F06D0[i].xA))
            {
                var_r29 = false;
            }
        }
    }
    for (iter = 0; iter < MAX_ITER; iter++) {
        int tmp = HSD_Randi(NUM_STAGES);
        i = tmp;
        if (mnStageSel_803F06D0[i].x4 == 0) {
            if (gm_80164330(mnStageSel_803F06D0[i].xA)) {
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
    jobj = HSD_JObjLoadJoint(mnStageSel_804D6C98->xB0);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 4, 0x87);
    HSD_GObjProc_8038FD54(gobj, mn_8022EAE0, 0);
    HSD_JObjAddAnimAll(jobj, mnStageSel_804D6C98->xB4,
                       mnStageSel_804D6C98->xB8, mnStageSel_804D6C98->xBC);
    HSD_JObjReqAnimAll(gobj->hsd_obj, 0.0F);
    HSD_JObjAnimAll(gobj->hsd_obj);
    mnStageSel_804D6CAF = 1;
    mnStageSel_804D6CA4 = 0x1E;
    lbAudioAx_80024030(1);
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
            lbAudioAx_80024030(2);
            temp_r31->x4 = 0;
            temp_r31->x2 = 2;
            mnStageSel_80259ED8(mnStageSel_804D6CAE);
        }
        break;
    case 2:
        if (++temp_r31->x4 > 0xAU) {
            HSD_GObjPLink_80390228(gobj);
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
    jobj = HSD_JObjLoadJoint(mnStageSel_804D6C98->x30.joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 4, 0x84);
    HSD_GObjProc_8038FD54(gobj, mn_8022EAE0, 1);
    HSD_JObjAddAnimAll(jobj, mnStageSel_804D6C98->x30.animjoint,
                       mnStageSel_804D6C98->x30.matanim_joint,
                       mnStageSel_804D6C98->x30.shapeanim_joint);
    jobj = GET_JOBJ(gobj);
    temp_r3_2 = HSD_MemAlloc(sizeof(struct StageSelUserData));
    GObj_InitUserData(gobj, 4, HSD_Free, temp_r3_2);
    HSD_GObjProc_8038FD54(gobj, fn_80259D84, 1);
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
        HSD_JObjSetFlags(jobj, 0x10);
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

void fn_8025A974(HSD_GObj* gobj, int unused)
{
    HSD_FogSet(gobj->hsd_obj);
}

// OnLoad
/// #mnStageSel_8025A998_OnEnter

extern HSD_CObjDesc* MenMain_cam;
static const Vec3 mnStageSel_803B8550 = { 0, -13, 0 };

void mnStageSel_8025A998_OnEnter(void* arg0)
{
    HSD_JObj* spDC[0x13];
    u8 _[0xDC - 0xD8];
    Vec3 spCC;

    int i;
    struct {
        HSD_CObjDesc* unk0;
        HSD_LightDesc* unk4;
        HSD_LightDesc* unk8;
        HSD_FogDesc* unkC;
        struct mnStageSel_804D6C98_t x10;
    }* temp_r3;

    PAD_STACK(0xDC - 0x38);

    mnStageSel_804D6C90 = (SSSData*) arg0;

    if (mnStageSel_804D6C90->force_stage_id < 0) {
        if (lbLang_IsSavedLanguageUS() != 0) {
            mnStageSel_804D6C94 = lbArchive_LoadArchive("MnSlMap.usd");
        } else {
            mnStageSel_804D6C94 = lbArchive_LoadArchive("MnSlMap.dat");
        }
        temp_r3 = HSD_ArchiveGetPublicAddress(mnStageSel_804D6C94,
                                              "MnSelectStageDataTable");
        MenMain_cam = temp_r3->unk0;
        mnStageSel_804D6C98 = &temp_r3->x10;
        mnStageSel_804D6CAF = 0;
        mnStageSel_804D6CA0 = 0;
        mnStageSel_804D6CAC = 0;
        mnStageSel_804D6CAD = 0;
        mnStageSel_804D6CAE = 0x1E;
        mnStageSel_804D50A0 = mnStageSel_804D6C90->unk_stage - 1;
        mnStageSel_804D6CA4 = 0x14;

        {
            HSD_GObj* gobj = mnStageSel_804D6C9C = GObj_Create(2, 3, 0x80);
            HSD_CObj* cobj = HSD_CObjLoadDesc(MenMain_cam);
            HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B, cobj);
            GObj_SetupGXLinkMax(gobj, HSD_GObj_803910D8, 0);
            gobj->gxlink_prios = 0x11;
            HSD_GObjProc_8038FD54(gobj, mn_8022BA1C, 5);
        }

        {
            HSD_LObj* lobj1;
            HSD_LObj* lobj2;
            HSD_GObj* gobj;
            gobj = GObj_Create(3, 4, 0x80);
            lobj1 = HSD_LObjLoadDesc(temp_r3->unk4);
            lobj2 = HSD_LObjLoadDesc(temp_r3->unk8);
            if (lobj1 == NULL) {
                __assert("lobj.h", 0x136, "lobj");
            }
            lobj1->next = lobj2;
            HSD_GObjObject_80390A70(gobj, (u8) HSD_GObj_804D784A, lobj1);
            GObj_SetupGXLink(gobj, HSD_GObj_LObjCallback, 0, 0x80);
        }

        {
            HSD_GObj* gobj = GObj_Create(0xE, 0xF, 0);
            HSD_Fog* fog = HSD_FogLoadDesc(temp_r3->unkC);
            HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7848, fog);
            GObj_SetupGXLink(gobj, fn_8025A974, 0, 0x80);
        }

        {
            HSD_JObj* jobj;
            HSD_GObj* gobj = GObj_Create(4, 5, 0x80);
            jobj = HSD_JObjLoadJoint(mnStageSel_804D6C98->xA0.joint);
            HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
            GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 4, 0x80);
            HSD_GObjProc_8038FD54(gobj, mn_8022EAE0, 0);
            HSD_JObjAddAnimAll(jobj, mnStageSel_804D6C98->xA0.animjoint,
                               mnStageSel_804D6C98->xA0.matanim_joint,
                               mnStageSel_804D6C98->xA0.shapeanim_joint);
            {
                HSD_GObj* g = gobj;
                HSD_JObj* jobj = GET_JOBJ(g);
                HSD_GObjProc_8038FD54(g, fn_8025A91C, 0);
                HSD_JObjReqAnimAll(jobj, 0.0F);
                HSD_JObjAnimAll(jobj);
            }
        }

        {
            HSD_JObj* jobj;
            HSD_GObj* gobj = GObj_Create(4, 5, 0x80);
            HSD_JObj* temp_r22_4;
            jobj = HSD_JObjLoadJoint(mnStageSel_804D6C98->x50.joint);
            HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
            GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 4, 0x82);
            HSD_GObjProc_8038FD54(gobj, mn_8022EAE0, 0);
            HSD_JObjAddAnimAll(jobj, mnStageSel_804D6C98->x50.animjoint,
                               mnStageSel_804D6C98->x50.matanim_joint,
                               mnStageSel_804D6C98->x50.shapeanim_joint);
            temp_r22_4 = gobj->hsd_obj;
            HSD_JObjReqAnimAll(temp_r22_4, 0.0F);
            HSD_JObjAnimAll(temp_r22_4);
        }

        {
            HSD_JObj* jobj;
            HSD_GObj* gobj = GObj_Create(4, 5, 0x80);
            jobj = HSD_JObjLoadJoint(mnStageSel_804D6C98->x90.joint);
            HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
            GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 4, 0x82);
            HSD_GObjProc_8038FD54(gobj, mn_8022EAE0, 4);
            HSD_JObjAddAnimAll(jobj, mnStageSel_804D6C98->x90.animjoint,
                               mnStageSel_804D6C98->x90.matanim_joint,
                               mnStageSel_804D6C98->x90.shapeanim_joint);
            spDC[0] = GET_JOBJ(gobj)->child;
            HSD_JObjReqAnimAll(spDC[0], 0.0F);
            HSD_JObjAnimAll(spDC[0]);
        }

        for (i = 0; i < 0x12; i++) {
            spDC[i + 1] = spDC[i]->next;
            HSD_JObjReqAnimAll(spDC[i + 1], 0.0F);
            HSD_JObjAnimAll(spDC[i + 1]);
        }

        for (i = 0; i < 0x1D; i++) {
            mnStageSel_803F06D0[i].x8 =
                gm_80164430(mnStageSel_803F06D0[i].xB) ? 2 : 1;
        }

        for (i = 0; i <= 0xA; i++) {
            HSD_JObj* jobj;
            HSD_GObj* gobj = GObj_Create(4, 5, 0x80);
            HSD_JObj* temp_r22_6;
            jobj = HSD_JObjLoadJoint(mnStageSel_804D6C98->x40.joint);
            HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
            GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 4, 0x83);
            HSD_GObjProc_8038FD54(gobj, mn_8022EAE0, 3);
            HSD_JObjAddAnimAll(jobj, mnStageSel_804D6C98->x40.animjoint,
                               mnStageSel_804D6C98->x40.matanim_joint,
                               mnStageSel_804D6C98->x40.shapeanim_joint);
            temp_r22_6 = GET_JOBJ(gobj);
            lb_8000C1C0(temp_r22_6, spDC[i]);
            mnStageSel_803F06D0[i * 2].x0 = temp_r22_6->child->next;
            switch (mnStageSel_803F06D0[i * 2].x8) {
            case 0:
                HSD_JObjSetFlags(mnStageSel_803F06D0[i * 2].x0, 0x10);
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
                HSD_JObjSetFlags(mnStageSel_803F06D0[i * 2 + 1].x0, 0x10);
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
            HSD_JObjAnimAll(temp_r22_6);
            HSD_ForeachAnim(temp_r22_6, JOBJ_TYPE, TOBJ_MASK, HSD_AObjStopAnim,
                            AOBJ_ARG_AOV, 0, 0);
        }

        for (i = 0xB; i <= 0xF; i++) {
            HSD_JObj* jobj;
            HSD_GObj* gobj = GObj_Create(4, 5, 0x80);
            HSD_JObj* temp_r23_3;
            s32 temp_r22_7;
            jobj = HSD_JObjLoadJoint(mnStageSel_804D6C98->x20.joint);
            HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
            GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 4, 0x83);
            HSD_GObjProc_8038FD54(gobj, mn_8022EAE0, 3);
            HSD_JObjAddAnimAll(jobj, mnStageSel_804D6C98->x20.animjoint,
                               mnStageSel_804D6C98->x20.matanim_joint,
                               mnStageSel_804D6C98->x20.shapeanim_joint);
            temp_r23_3 = gobj->hsd_obj;
            lb_8000C1C0(temp_r23_3, spDC[i]);
            mnStageSel_803F06D0[i + 13].x0 = temp_r23_3;
            switch (mnStageSel_803F06D0[i + 13].x8) {
            case 1:
                mnStageSel_803F06D0[i + 13].x8 = 0;
                /* fallthrough */
            case 0:
                HSD_JObjSetFlagsAll(temp_r23_3, 0x10);
                break;
            default:
                temp_r22_7 = mnStageSel_803F06D0[i + 13].x9 - 0x16;
                HSD_JObjReqAnimAll(temp_r23_3, 0.0F);
                HSD_JObjReqAnimAllByFlags(temp_r23_3, 0x10, temp_r22_7);
                HSD_JObjAnimAll(temp_r23_3);
                HSD_ForeachAnim(temp_r23_3, JOBJ_TYPE, TOBJ_MASK,
                                HSD_AObjStopAnim, AOBJ_ARG_AOV, 0, 0);
                break;
            }
        }

        {
            HSD_JObj* jobj;
            HSD_GObj* gobj = GObj_Create(4, 5, 0x80);
            HSD_JObj* temp_r22_8;
            jobj = HSD_JObjLoadJoint(mnStageSel_804D6C98->x10.joint);
            HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
            GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 4, 0x83);
            HSD_GObjProc_8038FD54(gobj, mn_8022EAE0, 3);
            HSD_JObjAddAnimAll(jobj, mnStageSel_804D6C98->x10.animjoint,
                               mnStageSel_804D6C98->x10.matanim_joint,
                               mnStageSel_804D6C98->x10.shapeanim_joint);
            temp_r22_8 = gobj->hsd_obj;
            lb_8000C1C0(temp_r22_8, spDC[0x10]);
            HSD_JObjReqAnimAll(temp_r22_8, 0.0F);
            HSD_JObjReqAnimAllByFlags(temp_r22_8, 0x10, 2.0F);
            HSD_JObjAnimAll(temp_r22_8);
            HSD_ForeachAnim(temp_r22_8, JOBJ_TYPE, TOBJ_MASK, HSD_AObjStopAnim,
                            AOBJ_ARG_AOV, 0, 0);
            mnStageSel_803F06D0[0x1D].x0 = temp_r22_8;
        }

        for (i = 0x11; i <= 0x12; i++) {
            HSD_JObj* jobj;
            HSD_GObj* gobj = GObj_Create(4, 5, 0x80);
            HSD_JObj* temp_r23_6;
            s32 temp_r22_9;
            jobj = HSD_JObjLoadJoint(mnStageSel_804D6C98->x0.joint);
            HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
            GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 4, 0x83);
            HSD_GObjProc_8038FD54(gobj, mn_8022EAE0, 3);
            HSD_JObjAddAnimAll(jobj, mnStageSel_804D6C98->x0.animjoint,
                               mnStageSel_804D6C98->x0.matanim_joint,
                               mnStageSel_804D6C98->x0.shapeanim_joint);

            temp_r23_6 = gobj->hsd_obj;
            lb_8000C1C0(temp_r23_6, spDC[i]);
            mnStageSel_803F06D0[i + 5].x0 = temp_r23_6;
            switch (mnStageSel_803F06D0[i + 5].x8) {
            case 1:
                mnStageSel_803F06D0[i + 5].x8 = 0;
                /* fallthrough */
            case 0:
                HSD_JObjSetFlagsAll(temp_r23_6, 0x10);
                break;
            default:
                temp_r22_9 = mnStageSel_803F06D0[i + 5].x9 - 0x14;
                HSD_JObjReqAnimAll(temp_r23_6, 0.0F);
                HSD_JObjReqAnimAllByFlags(temp_r23_6, 0x10, temp_r22_9);
                HSD_JObjAnimAll(temp_r23_6);
                HSD_ForeachAnim(temp_r23_6, JOBJ_TYPE, TOBJ_MASK,
                                HSD_AObjStopAnim, AOBJ_ARG_AOV, 0, 0);
                break;
            }
        }

        {
            HSD_JObj* jobj;
            HSD_GObj* gobj;
            gobj = GObj_Create(4, 5, 0x80);
            jobj = HSD_JObjLoadJoint(mnStageSel_804D6C98->x80.joint);
            HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
            GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 4, 0x86);
            HSD_GObjProc_8038FD54(gobj, mn_8022EAE0, 2);
            HSD_JObjAddAnimAll(jobj, mnStageSel_804D6C98->x80.animjoint,
                               mnStageSel_804D6C98->x80.matanim_joint,
                               mnStageSel_804D6C98->x80.shapeanim_joint);

            {
                HSD_JObj* temp_r28 = GET_JOBJ(gobj);
                spCC = mnStageSel_803B8550;
                {
                    s32 temp_r22_10;
                    HSD_GObj* g;
                    HSD_JObj* jobj;
                    g = gobj;
                    jobj = temp_r28;
                    HSD_GObjProc_8038FD54(g, fn_8025A310, 2);
                    temp_r22_10 = mnStageSel_804D50A0 + 1;
                    HSD_JObjReqAnimAll(jobj, 0.0F);
                    HSD_JObjReqAnimAllByFlags(jobj, 0x10, temp_r22_10);
                    HSD_JObjAnimAll(jobj);
                    HSD_ForeachAnim(jobj, JOBJ_TYPE, TOBJ_MASK,
                                    HSD_AObjStopAnim, AOBJ_ARG_AOV, 0, 0);
                }
                HSD_JObjSetTranslate(temp_r28, &spCC);
            }
        }

        {
            HSD_JObj* jobj;
            HSD_GObj* gobj;
            gobj = GObj_Create(HSD_GOBJ_CLASS_FIGHTER, 5, 0x80);
            jobj = HSD_JObjLoadJoint(mnStageSel_804D6C98->x30.joint);
            HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
            GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 4, 0x84);
            HSD_GObjProc_8038FD54(gobj, mn_8022EAE0, 1);
            HSD_JObjAddAnimAll(jobj, mnStageSel_804D6C98->x30.animjoint,
                               mnStageSel_804D6C98->x30.matanim_joint,
                               mnStageSel_804D6C98->x30.shapeanim_joint);
            {
                struct StageSelUserData* userdata;
                HSD_JObj* jobj = GET_JOBJ(gobj);
                userdata = HSD_MemAlloc(sizeof(struct StageSelUserData));
                GObj_InitUserData(gobj, 4, HSD_Free, userdata);
                HSD_GObjProc_8038FD54(gobj, fn_80259D84, 1);
                userdata->x0 = 0x1E;
                userdata->x4 = 0;
                userdata->x2 = 0;
            }
        }

        {
            HSD_JObj* jobj;
            HSD_GObj* gobj = GObj_Create(4, 5, 0x80);
            jobj = HSD_JObjLoadJoint(mnStageSel_804D6C98->x60.joint);
            HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
            GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 4, 0x81);
            HSD_GObjProc_8038FD54(gobj, mn_8022EAE0, 1);
            HSD_JObjAddAnimAll(jobj, mnStageSel_804D6C98->x60.animjoint,
                               mnStageSel_804D6C98->x60.matanim_joint,
                               mnStageSel_804D6C98->x60.shapeanim_joint);

            {
                HSD_GObj* g;
                HSD_JObj* jobj;
                struct foo {
                    int x0, x4;
                }* temp_r3_14;
                g = gobj;
                jobj = GET_JOBJ(g);
                temp_r3_14 = HSD_MemAlloc(8);
                GObj_InitUserData(g, 4, HSD_Free, temp_r3_14);
                HSD_GObjProc_8038FD54(g, fn_8025A090, 1);
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
                HSD_JObjLoadJoint(mnStageSel_804D6C98->x70.joint);
            s32* temp_r3_16;
            HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, temp_r3_15);
            GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 4, 0x85);
            HSD_GObjProc_8038FD54(gobj, mn_8022EAE0, 1);
            HSD_JObjAddAnimAll(temp_r3_15, mnStageSel_804D6C98->x70.animjoint,
                               mnStageSel_804D6C98->x70.matanim_joint,
                               mnStageSel_804D6C98->x70.shapeanim_joint);
            jobj = gobj->hsd_obj;
            temp_r3_16 = HSD_MemAlloc(4);
            GObj_InitUserData(gobj, 4, HSD_Free, temp_r3_16);
            *temp_r3_16 = 0;
            HSD_GObjProc_8038FD54(gobj, fn_8025A560, 1);
            HSD_JObjSetTranslateX(jobj, 100.0F);
        }

        lbAudioAx_80023F28(gmMainLib_8015ECB0());
    }
}

static inline HSD_PadStatus* get_pad(u8 i)
{
    return &HSD_PadCopyStatus[i];
}

// OnFrame
void mnStageSel_8025B850_OnFrame(void)
{
    if (mnStageSel_804D6C90->force_stage_id >= 0) {
        mnStageSel_804D6CAF = 2;
        mnStageSel_804D6C90->data.data.rules.xE =
            mnStageSel_804D6C90->force_stage_id;
        gm_801A4B60();
        return;
    }
    if (mnStageSel_804D6C90->no_lras == 0 && mn_8022F218()) {
        lbAudioAx_80024030(0);
        lb_800145F4();
        HSD_GObjPLink_80390228(mnStageSel_804D6C9C);
        mn_8022F268();
        gm_801A42F8(1);
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
    if (mnStageSel_804D6C90->x1 == 0 && (mnStageSel_804D6CA0 & 0x200) &&
        mnStageSel_804D6CAF == 0)
    {
        lbAudioAx_80024030(0);
        gm_801A4B60();
    }
    if (mnStageSel_804D6CAF == 2) {
        mnStageSel_804D6C90->data.data.rules.xE =
            mnStageSel_803F06D0[mnStageSel_804D6CAE].xB;
        gm_801A4B60();
    }
}

void mnStageSel_8025BB5C_OnLeave(UNK_T unused)
{
    SSSData* tmp;

    if (mnStageSel_804D6C94 != NULL) {
        lbArchive_80016EFC(mnStageSel_804D6C94);
        mnStageSel_804D6C94 = NULL;
    }
    tmp = mnStageSel_804D6C90;
    tmp->start_game = mnStageSel_804D6CAF == 2 ? true : false;
    if (tmp->start_game) {
        PreloadCacheScene* cache = lbDvd_8001822C();
        cache->game_cache.stage_id = tmp->data.data.rules.xE;
        lbDvd_80018254();
    }
}

int mnStageSel_8025BBD4(void)
{
    return mnStageSel_803F06D0[mnStageSel_802599EC()].xB;
}

int mnStageSel_8025BC08(int idx)
{
    return mnStageSel_803F06D0[idx].xB;
}
