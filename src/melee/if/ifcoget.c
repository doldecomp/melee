#include "ifcoget.h"

#include "gm/gm_unsplit.h"
#include "lb/lbarchive.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbspdisplay.h"
#include "sc/types.h"

#include <dolphin/mtx.h>
#include <baselib/cobj.h>
#include <baselib/fog.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>
#include <baselib/lobj.h>
#include <baselib/wobj.h>

/* 3F9E08 */ static struct un_803F9E08_t {
    unsigned char x0_b0 : 1;
    unsigned char x0_b1 : 1;
    unsigned char x0_b234 : 3;
    unsigned char x0_b567 : 3;
    unsigned char x1;
    unsigned char x2;
    unsigned char x3;
    int x4;
    int x8;
    HSD_GObj* xC;
} un_803F9E08 = { 0 };
STATIC_ASSERT(sizeof(un_803F9E08) == 0x10);

static void order_data(void)
{
    (void) "IfCoGet.dat";
}

static void order_data_1(void)
{
    (void) "ScInfCgt_scene_data";
}

/// .sbss
/* 4D6DA0 */ static void* un_804D6DA0;
/* 4D6DA4 */ static SceneDesc* un_804D6DA4;

/// .sdata2
/* 4DDC20 */ extern float un_804DDC20;

void fn_802FED14(HSD_GObj* gobj)
{
    HSD_JObj* jobj = HSD_GObjGetHSDObj(gobj);
    if (!un_803F9E08.x0_b1) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        return;
    }
    if (un_803F9E08.x1 <= un_803F9E08.x2) {
        HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
        if (un_803F9E08.x1 < un_803F9E08.x2) {
            if (un_803F9E08.x0_b567) {
                un_803F9E08.x0_b567--;
            }
            if (!un_803F9E08.x0_b567) {
                un_803F9E08.x0_b567 = un_803F9E08.x0_b234;
                un_803F9E08.x1++;
                if (un_803F9E08.x1 && un_803F9E08.x1 % 10 == 0) {
                    lbAudioAx_800237A8(0xB4, 0x7F, 0x40);
                } else {
                    lbAudioAx_800237A8(0xB3, 0x7F, 0x40);
                }
            }
        }
        HSD_JObjSetTranslateX(jobj, un_803F9E08.x4 / 10.9589f - 29.2f);
        HSD_JObjSetTranslateY(jobj, 24.0f + un_803F9E08.x8 / 10.0f);
        HSD_JObjReqAnimAll(jobj, un_803F9E08.x1);
        HSD_JObjAnimAll(jobj);
    }
}

void un_802FEFAC(void)
{
    HSD_GObj* gobj_camera;
    HSD_GObj* gobj_light;
    HSD_GObj* gobj_ui;
    HSD_JObj* jobj_ui;
    gobj_camera = GObj_Create(HSD_GOBJ_CLASS_CAMERA, 21, 0);
    HSD_GObjObject_80390A70(
        gobj_camera, HSD_GObj_804D784B,
        (0, HSD_CObjLoadDesc(un_804D6DA4->cameras[0].desc)));
    GObj_SetupGXLinkMax(gobj_camera, HSD_GObj_803910D8, 9);
    gobj_camera->gxlink_prios = 0x8400;
    gobj_light = GObj_Create(HSD_GOBJ_CLASS_LIGHT, 3, 0);
    HSD_GObjObject_80390A70(gobj_light, HSD_GObj_804D784A,
                            (0, lb_80011AC4(un_804D6DA4->lights)));
    GObj_SetupGXLink(gobj_light, HSD_GObj_LObjCallback, 10, 0);
    gobj_ui = GObj_Create(HSD_GOBJ_CLASS_UI, 14, 0);
    jobj_ui = HSD_JObjLoadJoint(un_804D6DA4->models[0]->joint);
    HSD_GObjObject_80390A70(gobj_ui, HSD_GObj_804D7849, jobj_ui);
    GObj_SetupGXLink(gobj_ui, HSD_GObj_JObjCallback, 15, 0);
    HSD_GObj_SetupProc(gobj_ui, fn_802FED14, 17);
    gm_8016895C(jobj_ui, un_804D6DA4->models[0], 0);
    HSD_JObjSetFlagsAll(jobj_ui, JOBJ_HIDDEN);
    HSD_JObjReqAnimAll(jobj_ui, 0.0f);
    HSD_JObjAnimAll(jobj_ui);
    un_803F9E08.xC = gobj_ui;
}

void un_802FF128(int arg0, int arg1, int arg2, int arg3)
{
    if (arg3 < 1) {
        arg3 = 1;
    }
    un_803F9E08.x0_b1 = 1;
    un_803F9E08.x0_b234 = arg3;
    un_803F9E08.x0_b567 = arg3;
    un_803F9E08.x1 = 0;
    if (arg2 > 100) {
        arg2 = 100;
    }
    un_803F9E08.x2 = arg2;
    un_803F9E08.x4 = arg0;
    un_803F9E08.x8 = -arg1;
}

void un_802FF190(void)
{
    un_803F9E08.x0_b0 = false;
    un_803F9E08.x0_b1 = false;
}

void un_802FF1B4(void)
{
    un_803F9E08.x0_b0 = true;
    un_803F9E08.x0_b1 = false;
    un_804D6DA0 = lbArchive_80016DBC("IfCoGet.dat", &un_804D6DA4,
                                     "ScInfCgt_scene_data", 0);
    un_802FEFAC();
}
