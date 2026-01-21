#include "vi0801.h"

#include "vi.h"

#include "cm/camera.h"
#include "ef/efasync.h"
#include "ef/eflib.h"
#include "gm/gm_unsplit.h"
#include "gr/grbigblueroute.h"
#include "gr/ground.h"
#include "gr/stage.h"
#include "it/item.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "lb/lbarchive.h"
#include "lb/lbaudio_ax.h"
#include "mp/mpcoll.h"
#include "pl/player.h"
#include "sc/types.h"

#include <baselib/aobj.h>
#include <baselib/cobj.h>
#include <baselib/fog.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjproc.h>
#include <baselib/lobj.h>

static SceneDesc* un_804D6FB8;
static GXColor un_804D6FBC;

/* 4A2EA8 */ extern char un_804A2EA8[];
/* 400128 */ extern s32 un_80400128[][2];

typedef struct vi_GObj {
    u8 pad0[0x20];
    s32 x20;
    s32 x24;
    void* hsd_obj;
} vi_GObj;

static void un_8031ED70(vi_GObj* gobj, int unused)
{
    GXColor* colors;
    s32 zero;
    s32 prio;

    if (HSD_CObjSetCurrent(gobj->hsd_obj) != 0) {
        colors = &un_804D6FBC;
        HSD_SetEraseColor(colors->r, colors->g, colors->b, colors->a);
        HSD_CObjEraseScreen(gobj->hsd_obj, 1, 0, 1);
        Camera_800310A0(2);
        gobj->x24 = 9;
        zero = 0;
        gobj->x20 = zero;
        HSD_GObj_80390ED0((HSD_GObj*) gobj, 7);
        Camera_800310A0(1);
        prio = 8;
        gobj->x24 = prio;
        gobj->x20 = zero;
        HSD_GObj_80390ED0((HSD_GObj*) gobj, 7);
        Camera_800310A0(0);
        gobj->x24 = prio;
        gobj->x20 = zero;
        HSD_GObj_80390ED0((HSD_GObj*) gobj, 7);
        gobj->x24 = 0x8A1;
        gobj->x20 = zero;
        HSD_GObj_80390ED0((HSD_GObj*) gobj, 7);
        HSD_CObjEndCurrent();
    }
}

void un_8031EE60(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

void un_8031EE84(void)
{
    s32 i;
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    s32 j;

    i = 0;
    while (un_804D6FB8->models[i] != NULL) {
        gobj = GObj_Create(0xE, 0xF, 0);
        jobj = HSD_JObjLoadJoint(un_804D6FB8->models[i]->joint);
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
        GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0xB, 0);
        gm_8016895C(jobj, un_804D6FB8->models[i], 0);
        HSD_JObjReqAnimAll(jobj, 0.0F);
        HSD_JObjAnimAll(jobj);
        HSD_GObjProc_8038FD54(gobj, un_8031EE60, 0x17);

        j = 0;
        do {
            if (i == un_80400128[j][0]) {
                lb_80011E24(jobj, (HSD_JObj**) &un_804A2EA8[j * 4],
                            un_80400128[j][1], -1);
            }
            j++;
        } while (j < 0x17);

        i++;
    }

    lbAudioAx_80026F2C(0x18);
    lbAudioAx_8002702C(8, 0x200000000000ULL);
    lbAudioAx_80027168();
    lbAudioAx_80027648();
}

void fn_8031EFE4(HSD_GObj* gobj)
{
    HSD_CObj* cobj = gobj->hsd_obj;
    HSD_CObjAnim(cobj);
    if (cobj->aobj->curr_frame == 75.0F || cobj->aobj->curr_frame == 160.0F) {
        vi_8031C9B4(0xC, 0);
    }
    if (cobj->aobj->curr_frame == 120.0F) {
        vi_8031C9B4(0x10, 0);
    }
    if (cobj->aobj->curr_frame == cobj->aobj->end_frame) {
        lb_800145F4();
        gm_801A4B60();
    }
}

void un_8031F07C_OnEnter(void* unused)
{
    HSD_CObj* cobj;
    HSD_GObj* gobj;
    struct HSD_Fog* fog;
    HSD_LObj* lobj;
    HSD_GObj* gobj2;

    lbAudioAx_800236DC();
    efLib_8005B4B8();
    efAsync_8006737C(0);
    lbAudioAx_80023F28(0x5B);
    lbAudioAx_80024E50(1);

    lbArchive_LoadSymbols("Vi0801.dat", &un_804D6FB8, "visual0801Scene", NULL);

    gobj = GObj_Create(0x13, 0x14, 0);
    cobj =
        lb_80013B14((HSD_CameraDescPerspective*) un_804D6FB8->cameras->desc);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMax(gobj, (void (*)(HSD_GObj*, int)) un_8031ED70, 8);
    HSD_CObjAddAnim(cobj, un_804D6FB8->cameras->anims[0]);
    HSD_CObjReqAnim(cobj, 0.0f);
    HSD_CObjAnim(cobj);
    HSD_GObjProc_8038FD54(gobj, fn_8031EFE4, 0);

    un_8031EE84();

    Camera_80028B9C(6);
    lb_8000FCDC();
    mpColl_80041C78();
    Ground_801C0378(0x40);
    Stage_802251E8(0x49, 0);
    Item_80266FA8();
    Item_80266FCC();
    Stage_8022524C();
    Stage_8022532C(0x49, 0);

    gobj = GObj_Create(0xB, 3, 0);
    fog = (struct HSD_Fog*) HSD_FogLoadDesc(un_804D6FB8->fogs->desc);
    HSD_GObjObject_80390A70(gobj, (u8) HSD_GObj_804D7848, fog);
    GObj_SetupGXLink(gobj, HSD_GObj_FogCallback, 0, 0);
    un_804D6FBC = fog->color;

    gobj2 = GObj_Create(0xB, 3, 0);
    lobj = lb_80011AC4(un_804D6FB8->lights);
    HSD_GObjObject_80390A70(gobj2, (u8) HSD_GObj_804D784A, lobj);
    GObj_SetupGXLink(gobj2, HSD_GObj_LObjCallback, 0, 0);

    grBigBlueRoute_8020DAB4(un_804A2EA8, 0.5f, 0x17);

    Player_InitAllPlayers();
    lbAudioAx_80024E50(0);
}

void un_8031F274_OnFrame(void)
{
    vi_8031CAAC();
}
