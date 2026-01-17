#include "vi/vi0601.h"

#include "cm/camera.h"
#include "ef/efasync.h"
#include "ef/eflib.h"
#include "gm/gm_unsplit.h"
#include "gr/grcorneria.h"
#include "gr/ground.h"
#include "gr/stage.h"
#include "it/item.h"
#include "lb/lb_00F9.h"
#include "lb/lbarchive.h"
#include "lb/lbaudio_ax.h"
#include "mp/mpcoll.h"
#include "pl/player.h"
#include "sc/types.h"
#include "vi/vi.h"

#include <baselib/aobj.h>
#include <baselib/cobj.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>
#include <baselib/lobj.h>
#include <baselib/wobj.h>

static SceneDesc* un_804D6FB0;
static GXColor erase_colors_vi0601;

void vi_8031E6CC_OnFrame(void)
{
    vi_8031CAAC();
}

void vi_8031E6EC(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

static void vi0601_CameraCallback(HSD_GObj* gobj, int unused)
{
    HSD_CObj* cobj;
    cobj = GET_COBJ(gobj);
    if (HSD_CObjSetCurrent(cobj)) {
        HSD_SetEraseColor(erase_colors_vi0601.r, erase_colors_vi0601.g,
                          erase_colors_vi0601.b, erase_colors_vi0601.a);
        cobj = GET_COBJ(gobj);
        HSD_CObjEraseScreen(cobj, 1, 0, 1);
        Camera_800310A0(2);
        gobj->gxlink_prios = 0x9;
        HSD_GObj_80390ED0(gobj, 7);
        Camera_800310A0(1);
        gobj->gxlink_prios = 0x8;
        HSD_GObj_80390ED0(gobj, 7);
        Camera_800310A0(0);
        gobj->gxlink_prios = 0x8;
        HSD_GObj_80390ED0(gobj, 7);
        gobj->gxlink_prios = 0x8A1;
        HSD_GObj_80390ED0(gobj, 7);
        HSD_CObjEndCurrent();
    }
}

void fn_8031E800(HSD_GObj* gobj)
{
    HSD_JObj* jobj;
    HSD_JObj* child;
    f32 scale;

    jobj = GET_JOBJ(gobj);
    if (jobj == NULL) {
        child = NULL;
    } else {
        child = jobj->child;
    }

    scale = 0.65f * HSD_JObjGetScaleX(child);
    HSD_JObjSetScaleX(child, scale);
    HSD_JObjSetScaleY(child, scale);
    HSD_JObjSetScaleZ(child, scale);
}

void un_8031E9B8(void)
{
    HSD_JObj* child;
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    s32 i;
    char pad[8];

    gobj = GObj_Create(0xE, 0xF, 0);
    jobj = HSD_JObjLoadJoint((*un_804D6FB0->models)->joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0xB, 0);
    gm_8016895C(jobj, *un_804D6FB0->models, 0);
    HSD_JObjReqAnimAll(jobj, 0.0f);
    HSD_JObjAnimAll(jobj);
    HSD_GObjProc_8038FD54(gobj, vi_8031E6EC, 0x17);

    i = 0;
    while (un_804D6FB0->models[i] != NULL) {
        if ((u32) (i - 1) <= 2) {
            if ((gobj = grCorneria_801E1BF0())->hsd_obj == NULL) {
                child = NULL;
            } else {
                child = ((HSD_JObj*) gobj->hsd_obj)->child;
            }
            HSD_GObjProc_8038FD54(gobj, fn_8031E800, 2);
            gm_8016895C(child, un_804D6FB0->models[i], 0);
            HSD_JObjReqAnimAll(child, 0.0f);
            HSD_JObjAnimAll(child);
        }
        i++;
    }

    lbAudioAx_80026F2C(0x18);
    lbAudioAx_8002702C(8, (u64) 8 << 32);
    lbAudioAx_80027168();
    lbAudioAx_80027648();
}

void vi0601_RunFrame(HSD_GObj* gobj)
{
    HSD_CObj* cobj;

    cobj = GET_COBJ(gobj);
    HSD_CObjAnim(cobj);

    if (537.0f == cobj->aobj->curr_frame || 559.0f == cobj->aobj->curr_frame ||
        580.0f == cobj->aobj->curr_frame)
    {
        vi_8031C9B4(0x23, 0);
    }
    if (cobj->aobj->curr_frame == cobj->aobj->end_frame) {
        lb_800145F4();
        gm_801A4B60();
    }
}

void un_8031EBBC_OnEnter(void* unused)
{
    HSD_CObj* cobj;
    HSD_GObj* gobj;
    HSD_GObj* gobj2;
    HSD_LObj* lobj;

    lbAudioAx_800236DC();
    efLib_8005B4B8();
    efAsync_8006737C(0);
    lbAudioAx_80023F28(0x57);
    lbAudioAx_80024E50(1);

    lbArchive_LoadSymbols("Vi0601.dat", &un_804D6FB0, "visual0601Scene", NULL);

    gobj = GObj_Create(0x13, 0x14, 0);
    cobj =
        lb_80013B14((HSD_CameraDescPerspective*) un_804D6FB0->cameras->desc);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMax(gobj, vi0601_CameraCallback, 2);
    HSD_CObjAddAnim(cobj, un_804D6FB0->cameras->anims[0]);
    HSD_CObjReqAnim(cobj, 0.0f);
    HSD_CObjAnim(cobj);
    HSD_GObjProc_8038FD54(gobj, vi0601_RunFrame, 0);

    Camera_80028B9C(6);
    lb_8000FCDC();
    mpColl_80041C78();
    Ground_801C0378(0x40);
    Stage_802251E8(7, 0);
    Item_80266FA8();
    Item_80266FCC();
    Stage_8022524C();
    Stage_8022532C(7, 0);

    erase_colors_vi0601 = Camera_80030758();
    un_8031E9B8();

    gobj2 = GObj_Create(0xB, 3, 0);
    lobj = lb_80011AC4(un_804D6FB0->lights);
    HSD_GObjObject_80390A70(gobj2, HSD_GObj_804D784A, lobj);
    GObj_SetupGXLink(gobj2, HSD_GObj_LObjCallback, 0, 0);

    Player_InitAllPlayers();
    lbAudioAx_80024E50(0);
}

void vi_8031ED50_OnFrame(void)
{
    vi_8031CAAC();
}
