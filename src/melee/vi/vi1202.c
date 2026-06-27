#include "vi/vi1202.h"

#include "vi.h"

#include "baselib/forward.h"

#include "ef/efasync.h"
#include "ef/eflib.h"
#include "gm/gm_1601.h"
#include "gm/gm_unsplit.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "lb/lbarchive.h"
#include "lb/lbaudio_ax.h"
#include "sc/types.h"
#include "ty/toy.h"
#include "ty/tylist.h"

#include <baselib/aobj.h>
#include <baselib/cobj.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>

static SceneDesc* un_804D7040;
static SceneDesc* un_804D7044;
static HSD_Joint* un_804D7048;
static HSD_JObj* un_804D704C;

void un_8032110C(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

void un_80321130(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

void un_80321154(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

static void vi1202_SetupChild(HSD_JObj* child)
{
    f32 scale;

    HSD_JObjSetTranslateXWithMtxDirty(child, -un_803060BC(0x1F, 0));
    HSD_JObjSetTranslateYWithMtxDirty(child, -un_803060BC(0x1F, 1));
    HSD_JObjSetTranslateZWithMtxDirty(child, -un_803060BC(0x1F, 2));
    HSD_JObjSetRotationYWithMtxDirty(child, -un_803060BC(0x1F, 5));

    scale = 0.49f * (un_803060BC(0x1F, 4) * (1.0f / un_803060BC(0x1F, 3)));

    HSD_JObjSetScaleXWithMtxDirty(child, scale);
    HSD_JObjSetScaleYWithMtxDirty(child, scale);
    HSD_JObjSetScaleZWithMtxDirty(child, scale);
}

void un_80321178(void)
{
    s32 i;
    HSD_GObj* gobj;
    HSD_JObj* jobj;

    i = 0;
    while ((un_804D7040->models)[i] != NULL) {
        gobj = GObj_Create(0xE, 0xF, 0);
        jobj = HSD_JObjLoadJoint((un_804D7040->models)[i]->joint);
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
        GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0xB, 0);
        gm_8016895C(jobj, (un_804D7040->models)[i], 0);
        HSD_JObjReqAnimAll(jobj, 0.0f);
        HSD_JObjAnimAll(jobj);
        HSD_GObj_SetupProc(gobj, un_80321154, 0x17);
        lb_80011E24(jobj, &un_804D704C, 2, -1);
        i++;
    }
    lbAudioAx_80026F2C(0x18);
    lbAudioAx_8002702C(8, 0x0020000000000000ULL);
    lbAudioAx_80027168();
    lbAudioAx_80027648();
}

void vi1202_RunFrame(HSD_GObj* gobj)
{
    HSD_CObj* cobj = GET_COBJ(gobj);
    HSD_CObjAnim(cobj);
    if (cobj->aobj->curr_frame == 100.0F) {
        vi_8031C9B4(0xE, 0);
    }
    if (cobj->aobj->curr_frame == cobj->aobj->end_frame) {
        lb_800145F4();
        gm_801A4B60();
    }
}

void vi1202_OnEnter(void* arg)
{
    HSD_LObj* lobj;
    HSD_CObj* cobj;
    HSD_JObj* jobj;
    HSD_JObj* child;
    HSD_GObj *gobj, *cam_gobj;
    PAD_STACK(16);

    lbAudioAx_80023694();
    lbAudioAx_800236DC();
    efLib_Init();
    efAsync_LoadSync(0);
    lbAudioAx_80023F28(0x5A);
    lbAudioAx_80024E50(1);

    lbArchive_LoadSymbols("Vi1202.dat", &un_804D7040, "visual1202Scene", NULL);
    lbArchive_LoadSymbols("TyKoopaR.dat", &un_804D7048,
                          "ToyKoopaRModel_TopN_joint", NULL);
    lbArchive_LoadSymbols("GmRgStnd.dat", &un_804D7044, "standScene", NULL);
    un_803124BC();

    gobj = GObj_Create(0xB, 0x3, 0);
    lobj = lb_80011AC4(un_804D7040->lights);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784A, lobj);
    GObj_SetupGXLink(gobj, HSD_GObj_LObjCallback, 0, 0);

    cam_gobj = GObj_Create(0x13, 0x14, 0);
    cobj =
        lb_80013B14((HSD_CameraDescPerspective*) un_804D7040->cameras->desc);
    HSD_GObjObject_80390A70(cam_gobj, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMax(cam_gobj, HSD_GObj_803910D8, 0x8);
    cam_gobj->gxlink_prios = 0x8A9;
    HSD_CObjAddAnim(cobj, un_804D7040->cameras->anims[0]);
    HSD_CObjReqAnim(cobj, 0.0f);
    HSD_CObjAnim(cobj);
    HSD_GObj_SetupProc(cam_gobj, vi1202_RunFrame, 0);
    un_80321178();

    gobj = GObj_Create(0xE, 0xF, 0);
    jobj = HSD_JObjLoadJoint(un_804D7048);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0xB, 0);

    HSD_JObjSetScaleX(jobj, 0.49f);
    HSD_JObjSetScaleY(jobj, 0.49f);
    HSD_JObjSetScaleZ(jobj, 0.49f);

    lb_8000C1C0(jobj, un_804D704C);
    lb_8000C290(jobj, un_804D704C);
    HSD_GObj_SetupProc(gobj, un_80321130, 0x17);

    gobj = GObj_Create(0xE, 0xF, 0);
    jobj = HSD_JObjLoadJoint(un_804D7044->models[0]->joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0xB, 0);
    HSD_GObj_SetupProc(gobj, un_8032110C, 0x17);

    if (jobj == NULL) {
        child = NULL;
    } else {
        child = jobj->child;
    }

    vi1202_SetupChild(child);

    lb_8000C1C0(jobj, un_804D704C);
    lb_8000C290(jobj, un_804D704C);
    lbAudioAx_80024E50(0);
}

void vi1202_OnFrame(void)
{
    vi_8031CAAC();
}
