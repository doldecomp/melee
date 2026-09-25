#include "ifcoget.h"

#include <melee/cm/forward.h>

#include "forward.h"
#include <melee/gm/gm_unsplit.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lbspdisplay.h>
#include <melee/sc/types.h>
#include <sysdolphin/baselib/cobj.h>
#include <sysdolphin/baselib/fog.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/lobj.h>
#include <sysdolphin/baselib/wobj.h>

/* 3F9E08 */ static struct un_803F9E08_t {
    u8 x0_b0 : 1;
    u8 x0_b1 : 1;
    u8 x0_b234 : 3;
    u8 x0_b567 : 3;
    u8 x1;
    u8 x2;
    u8 x3;
    int x4;
    int x8;
    HSD_GObj* xC;
} un_803F9E08 = { 0 };
ASSERT_SIZE(un_803F9E08, 0x10);

/// .sbss
/* 4D6DA0 */ static void* un_804D6DA0;
/* 4D6DA4 */ static SceneDesc* un_804D6DA4;

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
    HSD_CObj* cobj;
    HSD_GObj* gobj_light;
    HSD_LObj* lobj;
    HSD_GObj* gobj_ui;
    HSD_JObj* jobj_ui;

    gobj_camera = GObj_Create(HSD_GOBJ_CLASS_CAMERA, 21, 0);
    cobj = HSD_CObjLoadDesc(un_804D6DA4->cameras[0].desc);
    HSD_GObjObject_80390A70(gobj_camera, HSD_GObj_CameraKind, cobj);
    GObj_SetupGXLinkMax(gobj_camera, HSD_GObj_803910D8, 9);
    gobj_camera->gxlink_prios = 0x8400;
    gobj_light = GObj_Create(HSD_GOBJ_CLASS_LIGHT, 3, 0);
    lobj = lb_80011AC4(un_804D6DA4->lights);
    HSD_GObjObject_80390A70(gobj_light, HSD_GObj_LightKind, lobj);
    GObj_SetupGXLink(gobj_light, HSD_GObj_LObjCallback, 10, 0);
    gobj_ui = GObj_Create(HSD_GOBJ_CLASS_UI, 14, 0);
    jobj_ui = HSD_JObjLoadJoint(un_804D6DA4->models[0]->joint);
    HSD_GObjObject_80390A70(gobj_ui, HSD_GObj_JObjKind, jobj_ui);
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
