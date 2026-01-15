#include "vi/vi0402.h"

#include <placeholder.h>

#include "ef/efasync.h"
#include "ef/eflib.h"
#include "gm/gm_unsplit.h"
#include "lb/lb_00F9.h"
#include "lb/lbarchive.h"
#include "lb/lbaudio_ax.h"
#include "pl/player.h"
#include "sc/types.h"
#include "vi/vi.h"

#include <baselib/cobj.h>
#include <baselib/displayfunc.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>

extern SceneDesc* un_804D6F68;

void un_8031D6E4(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

void un_8031D708(void)
{
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    int i;

    for (i = 0; un_804D6F68->models[i] != NULL; i++) {
        gobj = GObj_Create(0xE, 0xF, 0);
        jobj = HSD_JObjLoadJoint(un_804D6F68->models[i]->joint);
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
        GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 3, 0);
        gm_8016895C(jobj, un_804D6F68->models[i], 0);
        HSD_JObjReqAnimAll(jobj, 0.0f);
        HSD_JObjAnimAll(jobj);
        HSD_GObjProc_8038FD54(gobj, un_8031D6E4, 0x17);
    }

    lbAudioAx_80026F2C(0x18);
    lbAudioAx_8002702C(8, 0x10000000000ULL);
    lbAudioAx_80027168();
    lbAudioAx_80027648();
}

void vi_8031D80C(HSD_GObj* gobj)
{
    HSD_AObj* aobj;
    HSD_CObj* cobj = GET_COBJ(gobj);
    HSD_CObjAnim(cobj);
    aobj = cobj->aobj;

    if (aobj->curr_frame == aobj->end_frame) {
        lb_800145F4();
        gm_801A4B60();
    }
}

void un_8031D858_OnEnter(void* arg0)
{
    HSD_GObj* light_gobj;
    HSD_CObj* cobj;
    HSD_GObj* cam_gobj;

    lbAudioAx_800236DC();
    efLib_8005B4B8();
    efAsync_8006737C(0);
    lbAudioAx_80023F28(0x58);
    lbAudioAx_80024E50(1);
    lbArchive_LoadSymbols("Vi0402.dat", &un_804D6F68, "visual0402Scene", NULL);

    light_gobj = GObj_Create(0xB, 0x3, 0);
    HSD_GObjObject_80390A70(light_gobj, HSD_GObj_804D784A,
                            lb_80011AC4(un_804D6F68->lights));
    GObj_SetupGXLink(light_gobj, HSD_GObj_LObjCallback, 0, 0);

    cam_gobj = GObj_Create(0x13, 0x14, 0);
    cobj =
        lb_80013B14((HSD_CameraDescPerspective*) un_804D6F68->cameras[0].desc);
    HSD_GObjObject_80390A70(cam_gobj, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMax(cam_gobj, HSD_GObj_803910D8, 8);
    cam_gobj->gxlink_prios = 0x89;
    HSD_CObjAddAnim(cobj, un_804D6F68->cameras[0].anims[0]);
    HSD_CObjReqAnim(cobj, 0.0f);
    HSD_CObjAnim(cobj);
    HSD_GObjProc_8038FD54(cam_gobj, vi_8031D80C, 0);

    un_8031D708();
    vi_8031C9B4(0x22, 0);
    Player_InitAllPlayers();
    lbAudioAx_80024E50(0);
}
void vi_8031D9C4_OnFrame(void)
{
    vi_8031CAAC();
}

void un_8031D9E4(int arg0, int arg1, int arg2)
{
    un_804D6F84[0] = arg0;
    un_804D6F84[1] = arg1;
    un_804D6F84[3] = arg2;
}
