#include "gm_19EF.h"

#include "gm_unsplit.h"
#include "gm_1A36.h"

#include <sysdolphin/baselib/archive.h>
#include <sysdolphin/baselib/cobj.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/jobj.h>
#include <melee/lb/lb_00F9.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lbarchive.h>
#include <melee/sc/types.h>

static HSD_Archive* lbl_804D6698;
static HSD_Archive* lbl_804D66F0;
static HSD_JObj* lbl_804D66F4;
static u32 lbl_804D66F8;

static struct {
    u8 pad0[0x8];
    int x8;
    u8 padC[0x18 - 0xC];
    int x18;
    u8 pad1C[0x22 - 0x1C];
    u16 x22;
} lbl_80479A98;

// seems to handle "Go!" animations, based on .dat filenames

/// #fn_8019F9C4

/// #gm_801A0A10_OnEnter

void gm_801A0B18_OnLeave(void* arg0_)
{
    DebugGameOverData* arg0 = arg0_;
    arg0->x4 = lbl_80479A98.x8;
    arg0->xC = lbl_80479A98.x18;
    arg0->x18 = lbl_80479A98.x22;
    lbAudioAx_800236DC();
    lbArchive_80016EFC(lbl_804D6698);
}

static void fn_801A0B60(HSD_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    HSD_JObjReqAnimAll(jobj, lbl_804D66F8);
    HSD_JObjAnimAll(jobj);
    if (lbl_804D66F8 == 0xBD) {
        if (((u32) gm_801A36A0(4) & 0x1000) || ((u32) gm_801A36A0(4) & 0x100))
        {
            lbl_804D66F8 += 1;
        }
    } else {
        lbl_804D66F8 += 1;
    }
    if ((int) HSD_AObjGetCurrFrame(lbl_804D66F4->aobj) >=
        (int) HSD_AObjGetEndFrame(lbl_804D66F4->aobj))
    {
        gm_801A4B60();
    }
}

void gm_801A0C6C_OnEnter(void* unused)
{
    SceneDesc* sp10;
    HSD_GObj* temp_r30;
    HSD_GObj* temp_r30_2;
    HSD_GObj* temp_r30_3;
    HSD_JObj* temp_r3;
    HSD_CObj* cobj;
    HSD_LObj* lobj;
    PAD_STACK(4);

    lbl_804D66F8 = 0;
    lbl_804D66F0 =
        lbArchive_80016DBC("IfComSn.dat", &sp10, "ScComSoon_scene_data", 0);

    temp_r30 = GObj_Create(0x13, 0x14, 0);
    cobj = HSD_CObjLoadDesc(sp10->cameras[0].desc);
    HSD_GObjObject_80390A70(temp_r30, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMax(temp_r30, HSD_GObj_803910D8, 0);
    temp_r30->gxlink_prios = 0x801;

    temp_r30_2 = GObj_Create(0xB, 0xF, 0);
    lobj = lb_80011AC4(sp10->lights);
    HSD_GObjObject_80390A70(temp_r30_2, HSD_GObj_804D784A, lobj);
    GObj_SetupGXLink(temp_r30_2, HSD_GObj_LObjCallback, 0, 0);
    temp_r30_3 = GObj_Create(0xE, 0xF, 0);
    temp_r3 = HSD_JObjLoadJoint(sp10->models[0]->joint);
    HSD_GObjObject_80390A70(temp_r30_3, HSD_GObj_804D7849, temp_r3);
    GObj_SetupGXLink(temp_r30_3, HSD_GObj_JObjCallback, 0xB, 0);
    HSD_GObjProc_8038FD54(temp_r30_3, fn_801A0B60, 0);
    gm_8016895C(temp_r3, sp10->models[0], 0);
    HSD_JObjReqAnimAll(temp_r3, 0.0f);
    HSD_JObjAnimAll(temp_r3);
    lb_80011E24(temp_r3, &lbl_804D66F4, 1, -1);
}

extern HSD_Archive* lbl_804D66F0;

void gm_801A0E0C_OnLeave(void* unused)
{
    lbArchive_80016EFC(lbl_804D66F0);
    lbAudioAx_800236DC();
}
