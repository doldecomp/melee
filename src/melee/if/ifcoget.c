#include "ifcoget.h"

#include "gm/gm_unsplit.h"
#include "if/ifall.h"
#include "if/textdraw.h"
#include "if/textlib.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "lb/lbarchive.h"
#include "lb/lbaudio_ax.h"
#include "sc/types.h"

#include <printf.h>
#include <dolphin/mtx.h>
#include <baselib/cobj.h>
#include <baselib/fog.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjplink.h>
#include <baselib/gobjproc.h>
#include <baselib/gobjuserdata.h>
#include <baselib/jobj.h>
#include <baselib/lobj.h>
#include <baselib/memory.h>
#include <baselib/particle.h>
#include <baselib/sislib.h>
#include <MSL/stdio.h>
#include <MSL/string.h>

/// .data
/* 3F9E08 */ static struct {
    struct {
        unsigned char b0 : 1;
        unsigned char b1 : 1;
        unsigned char b234 : 3;
        unsigned char b567 : 3;
    } x0;
    unsigned char x1;
    unsigned char x2;
    unsigned char x3;
    int x4;
    int x8;
    HSD_GObj* xC;
    char x10[12];
    char x1C[20];
} un_803F9E08 = { {0}, 0, 0, 0, 0, 0, 0, "IfCoGet.dat", "ScInfCgt_scene_data" };
/* 3F9E60 */ static HSD_CObjDesc un_803F9E60 = { 0 };
/* 3F9ED4 */ static HSD_LightDesc un_803F9ED4 = { 0 };

/// .bss
struct un_804A1F58_x8_t {
    HSD_GObj* x0;
    HSD_Text* x4;
    unsigned int x8;
};

// TODO: sizeof(un_804A1F58) should be 0x80, see un_802FF498
// change 0x80 to sizeof(un_804A1F58) when done
/* 4A1F58 */ static struct un_804A1F58_t {
    unsigned int x0;
    unsigned char x4;
    struct un_804A1F58_x8_t x8;
} un_804A1F58[7];

/// .sbss
/* 4D6DA0 */ static void* un_804D6DA0;
/* 4D6DA4 */ static SceneDesc* un_804D6DA4;

void fn_802FED14(HSD_GObj* gobj)
{
    HSD_JObj* jobj = HSD_GObjGetHSDObj(gobj);
    if (!un_803F9E08.x0.b1) {
        HSD_JObjSetFlagsAll(jobj, 0x10);
        return;
    }
    if (un_803F9E08.x1 <= un_803F9E08.x2) {
        HSD_JObjClearFlagsAll(jobj, 0x10);
        if (un_803F9E08.x1 < un_803F9E08.x2) {
            if (un_803F9E08.x0.b567) {
                un_803F9E08.x0.b567--;
            }
            if (!un_803F9E08.x0.b567) {
                un_803F9E08.x0.b567 = un_803F9E08.x0.b234;
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
    HSD_GObjObject_80390A70(gobj_camera, HSD_GObj_804D784B,
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
    HSD_GObjProc_8038FD54(gobj_ui, fn_802FED14, 17);
    gm_8016895C(jobj_ui, un_804D6DA4->models[0], 0);
    HSD_JObjSetFlagsAll(jobj_ui, 0x10);
    HSD_JObjReqAnimAll(jobj_ui, 0.0);
    HSD_JObjAnimAll(jobj_ui);
    un_803F9E08.xC = gobj_ui;
}

void un_802FF128(int arg0, int arg1, int arg2, int arg3)
{
    if (arg3 < 1) {
        arg3 = 1;
    }
    un_803F9E08.x0.b1 = 1;
    un_803F9E08.x0.b234 = arg3;
    un_803F9E08.x0.b567 = arg3;
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
    un_803F9E08.x0.b0 = 0;
    un_803F9E08.x0.b1 = 0;
}

void un_802FF1B4(void)
{
    un_803F9E08.x0.b0 = 1;
    un_803F9E08.x0.b1 = 0;
    un_804D6DA0 = lbArchive_80016DBC(un_803F9E08.x10, &un_804D6DA4,
                                     un_803F9E08.x1C, 0);
    un_802FEFAC();
}

void fn_802FF218(HSD_GObj* arg0)
{
    int x;
    int y;
    for (x = 0; x < 6; x++) {
        if (un_804A1F58[x].x8.x0 == arg0) {
            y = x;
            goto _done;
        }
    }
    y = -1;
    _done: 
    if (y >= 0) {
        if (un_804A1F58[y].x0 == 1) {
            HSD_SisLib_803A70A0(un_804A1F58[y].x8.x4,
                                un_804A1F58[y].x8.x8, "");
        } else {
            int s;
            gm_8016B774();
            s = gm_8016C658(y);
            if (s > 9999) {
                s = 9999;
            }
            if (un_804A1F58[y].x0 != s) {
                HSD_SisLib_803A70A0(un_804A1F58[y].x8.x4,
                                    un_804A1F58[y].x8.x8,
                                    "%d", s);
                un_804A1F58[y].x0 = s;
            }
        }
    }
}

void fn_802FF360(void* arg0) {}

void un_802FF364(int slot)
{
    int s;
    Vec3* ifAll;
    struct un_804A1F58_x8_t* thing;
    HSD_GObj* gobj;
    struct un_804A1F58_t* base = un_804A1F58;
    PAD_STACK(0x10);
    thing = &base[slot].x8;
    ifAll = ifAll_802F3424(slot);
    gobj = thing->x0;
    if ((thing && thing) && thing){}
    if (gobj) {
        HSD_GObjPLink_80390228(gobj);
    }
    if (thing->x4) {
        HSD_SisLib_803A5CC4(thing->x4);
    }
    thing->x4 = HSD_SisLib_803A6754(2, base->x0);
    thing->x4->default_alignment = 1;
    thing->x4->default_kerning = 1;
    gm_8016B774();
    s = gm_8016C658(slot);
    if (s > 9999) {
        s = 9999;
    }
    thing->x8 =
        HSD_SisLib_803A6B98(thing->x4, ifAll->x, ifAll->y + 3.2f, "%d", s);
    HSD_SisLib_803A7548(thing->x4, thing->x8, 0.06, 0.06);
    thing->x4->render_callback = fn_802FF360;
    thing->x0 = GObj_Create(HSD_GOBJ_CLASS_UI, 15, 0);
    HSD_GObjProc_8038FD54(thing->x0, fn_802FF218, 17);
}

void un_802FF498(void)
{
    PAD_STACK(8);
    memzero(un_804A1F58, 0x80); // TODO: change to sizeof(un_802FF498) when size fixed
    un_804A1F58->x0 =
        HSD_SisLib_803A611C(2, ifAll_802F3404(), 14, 15, 0, 11, 0, 19);
}

void un_802FF4FC(void)
{
    int i;
    for (i = 0; i < 6; i++) {
        if (un_804A1F58[i].x8.x0) {
            HSD_GObjPLink_80390228(un_804A1F58[i].x8.x0);
        }
        if (un_804A1F58[i].x8.x4) {
            HSD_SisLib_803A5CC4(un_804A1F58[i].x8.x4);
        }
    }
}

void un_802FF570(void)
{
    int i;
    for (i = 0; i < 6; i++) {
        un_804A1F58[i + 1].x4 = 1;
        if (un_804A1F58[i].x8.x4) {
            un_804A1F58[i].x8.x4->hidden = 1;
        }
    }
}

void un_802FF620(void)
{
    int i;
    struct un_804A1F58_t* base = un_804A1F58;
    PAD_STACK(8);
    for (i = 0; i < 6; i++) {
        base[i + 1].x4 = 0;
        if (base[i].x8.x4) {
            un_802FF364(i);
            base[i].x8.x4->hidden = 0;
        }
    }
    base[i].x8 = base[i].x8;
}

void un_802FF6A0(void)
{
    HSD_GObj* gobj = GObj_Create(HSD_GOBJ_CLASS_LIGHT, 3, 0);
    HSD_LObj* new_var;
    new_var = HSD_LObjLoadDesc(&un_803F9ED4);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784A, new_var);
    GObj_SetupGXLink(gobj, HSD_GObj_LObjCallback, 0, 0);
}

void un_802FF710(void)
{
    HSD_CObj* new_var;
    HSD_GObj* gobj = GObj_Create(0x13, 20, 0);
    if (gobj) {
        new_var = HSD_CObjLoadDesc(&un_803F9E60);
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B, new_var);
        GObj_SetupGXLinkMax(gobj, HSD_GObj_803910D8, 11);
        gobj->gxlink_prios = 0x20000;
    }
}

HSD_GObj* un_802FF78C(void)
{
    HSD_GObj* gobj = DevText_Setup(21, 24, 0, 17, 0, 11);
    if (gobj) {
        un_80304138();
    }
    return gobj;
}
