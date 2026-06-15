#include "ifprize.h"

#include "placeholder.h"

#include "gm/gm_unsplit.h"
#include "gm/gmmain_lib.h"
#include "lb/lb_00F9.h"
#include "lb/lbarchive.h"
#include "lb/lbaudio_ax.h"
#include "lb/lblanguage.h"
#include "sc/types.h"
#include "ty/toy.h"
#include "ty/tylist.h"

#include <printf.h>
#include <dolphin/mtx.h>
#include <baselib/archive.h>
#include <baselib/cobj.h>
#include <baselib/dobj.h>
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
#include <baselib/random.h>
#include <baselib/sislib.h>
#include <MSL/stdio.h>
#include <MSL/string.h>

/// .data
/* 3F9A00 */ static int un_803F9A00[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 3, 2, 2, 5, 5, 4, 6, 6, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 6, 6, 5, 7, 7, 7, 7, 7, 7, 5, 5, 5, 5, 5, 5, 5
};
/* 3F9B30 */ static struct un_803F9B30 {
    int x0;
    unsigned short x4;
} un_803F9B30[67] = {
    { 0, 0 },   { 1, 1 },   { 2, 2 },   { 3, 3 },   { 4, 4 },   { 5, 5 },
    { 6, 6 },   { 7, 7 },   { 8, 8 },   { 9, 9 },   { 10, 10 }, { 11, 11 },
    { 12, 12 }, { 13, 13 }, { 14, 14 }, { 15, 15 }, { 16, 16 }, { 17, 17 },
    { 18, 18 }, { 19, 19 }, { 20, 20 }, { 21, 21 }, { 22, 22 }, { 23, 23 },
    { 24, 24 }, { 25, 25 }, { 26, 26 }, { 27, 27 }, { 28, 28 }, { 29, 29 },
    { 30, 30 }, { 31, 31 }, { 32, 32 }, { 33, 33 }, { 34, 34 }, { 35, 35 },
    { 36, 36 }, { 37, 37 }, { 38, 38 }, { 39, 39 }, { 40, 40 }, { 41, 41 },
    { 42, 42 }, { 43, 43 }, { 44, 44 }, { 45, 45 }, { 46, 46 }, { 47, 47 },
    { 48, 48 }, { 49, 49 }, { 50, 50 }, { 51, 51 }, { 52, 52 }, { 53, 53 },
    { 54, 54 }, { 55, 55 }, { 56, 56 }, { 57, 57 }, { 58, 58 }, { 59, 59 },
    { 60, 60 }, { 61, 61 }, { 62, 63 }, { 63, 67 }, { 64, 68 }, { 65, 62 },
    { 66, 0 }
};
struct un_802FEBE0_OnEnter_arg0 {
    unsigned short x0;
    unsigned short x2;
    int x4;
    struct un_802FEBE0_OnEnter_arg0* x8;
};

struct un_803F9D48 {
    unsigned char x0a : 4;
    unsigned char x0b : 4;
    unsigned char x1;
    char x2;
    unsigned char x3;
    unsigned short x4;
    unsigned short x6;
    unsigned short x8;
    unsigned char xA;
    unsigned char xB;
    int xC;
    HSD_JObj* x10;
    HSD_GObj* x14;
    HSD_GObj* x18;
    HSD_GObj* x1C;
    HSD_Text* x20;
    HSD_Text* x24;
    struct un_802FEBE0_OnEnter_arg0* x28;
    struct un_802FEBE0_OnEnter_arg0* x2C;
    int x30[3];
} un_803F9D48 = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, { 0x43, 0x44, 0x45 },
};
static char lbl_803F9D84[] = "ScInfPrize_scene_data\0\0\0"
                                "SdPrize.usd\0"
                                "SIS_PrizeData\0\0\0"
                                "SdPrize.dat";
/// .sbss
/* 4D6D98 */ static HSD_Archive* un_804D6D98;
/* 4D6D9C */ static SceneDesc* un_804D6D9C;

void un_802FE3F8(int a, int b, short* c, short* d)
{
    struct un_803F9B30* x;
    for (x = &un_803F9B30[0]; x->x0 != 66; x++) {
        if (x->x0 == a) {
            if (a == 0x3E) {
                if (c != NULL) {
                    *c = b + x->x4;
                }
                if (d != NULL) {
                    *d = b + x->x4 + 1;
                }
            } else if (c != NULL) {
                *c = b + x->x4;
            }
        }
    }
}

static inline void un_802FE3F8_inner(int a, int b, short* c, short* d)
{
    un_802FE3F8(a, b, c, d);
}

/// un_802FEBE0_OnEnter will inline un_802FE3F8 otherwise
static inline void un_802FE3F8_noinline(int a, int b, short* c, short* d)
{
    un_802FE3F8_inner(a, b, c, d);
}

void fn_802FE470(HSD_GObj* gobj)
{
    HSD_JObj* jobj;

    if (un_803F9D48.x1 != 4) {
        jobj = HSD_GObjGetHSDObj(gobj);
        switch (un_803F9D48.x1) {
        case 0:
            if (un_803F9D48.x2 < 5) {
                un_803F9D48.x2++;
            } else {
                un_802FE918(un_803F9D48.x28->x0, un_803F9D48.x28->x2,
                            un_803F9D48.x28->x4);
                un_803F9D48.x1 = 1;
            }
            break;
        case 1:
            un_803F9D48.x2 = 0xA;
            if (gm_801A36A0(4) & 0x1100) {
                if (un_803F9D48.x2C == NULL) {
                    un_802FE8CC();
                } else {
                    un_802FE918(un_803F9D48.x2C->x0, un_803F9D48.x2C->x2,
                                un_803F9D48.x2C->x4);
                    un_803F9D48.x2C = un_803F9D48.x2C->x8;
                }
            }
            break;
        case 2:
            if (un_803F9D48.x2 < 0xF) {
                un_803F9D48.x2++;
            } else {
                un_803F9D48.x1 = 3;
            }
            break;
        case 3:
            HSD_GObjPLink_80390228(un_803F9D48.x18);
            HSD_GObjPLink_80390228(un_803F9D48.x1C);
            HSD_GObjPLink_80390228(un_803F9D48.x14);
            lbArchive_80016EFC(un_804D6D98);
            un_803F9D48.x1 = 4;
            un_803F9D48.x0a = 0;
            un_803F9D48.x0b = 0;
            gm_801A4B60();
            return;
        }
        HSD_JObjReqAnimAll(jobj, (f32) (s8) un_803F9D48.x2);
        HSD_DObjReqAnimAll(un_803F9D48.x10->u.dobj, (f32) un_803F9D48.x4);
        HSD_DObjReqAnimAll(HSD_JObjGetChild(un_803F9D48.x10)->u.dobj,
                           (f32) un_803F9D48.x4);
        HSD_JObjAnimAll(jobj);
    }
}

void un_802FE6A8(void)
{
    HSD_GObj* gobj_camera;
    HSD_GObj* gobj_light;
    HSD_GObj* gobj_ui;
    HSD_JObj* jobj_ui;
    gobj_camera = GObj_Create(HSD_GOBJ_CLASS_CAMERA, 20, 0);
    HSD_GObjObject_80390A70(gobj_camera, HSD_GObj_804D784B & 0xFF,
                            HSD_CObjLoadDesc(un_804D6D9C->cameras[0].desc));
    GObj_SetupGXLinkMax(gobj_camera, HSD_GObj_803910D8, 8);
    gobj_camera->gxlink_prios = 0xC00;
    un_803F9D48.x18 = gobj_camera;
    gobj_light = GObj_Create(HSD_GOBJ_CLASS_LIGHT, 3, 0);
    HSD_GObjObject_80390A70(gobj_light, HSD_GObj_804D784A & 0xFF,
                            lb_80011AC4(un_804D6D9C->lights));
    GObj_SetupGXLink(gobj_light, HSD_GObj_LObjCallback, 10, 0);
    un_803F9D48.x1C = gobj_light;
    gobj_ui = GObj_Create(HSD_GOBJ_CLASS_UI, 15, 0);
    jobj_ui = HSD_JObjLoadJoint(un_804D6D9C->models[0]->joint);
    HSD_GObjObject_80390A70(gobj_ui, HSD_GObj_804D7849, jobj_ui);
    GObj_SetupGXLink(gobj_ui, HSD_GObj_JObjCallback, 11, 0);
    HSD_GObj_SetupProc(gobj_ui, fn_802FE470, 17);
    gm_8016895C(jobj_ui, un_804D6D9C->models[0], 0);
    HSD_JObjReqAnimAll(jobj_ui, 0.0);
    HSD_JObjAnimAll(jobj_ui);
    lb_80011E24(jobj_ui, &un_803F9D48.x10, 2, -1);
    un_803F9D48.x14 = gobj_ui;
    {
        GXColor color = { 0x5A, 0x5A, 0x5A, 0xFF };
        PAD_STACK(0x14);

        HSD_SisLib_803A611C(2, 0, 9, 20, 0, 14, 0, 18);
        un_803F9D48.x20 =
            HSD_SisLib_803A5ACC(2, 0, 105.0, 202.0, 0.0, 435.0, 75.0);
        un_803F9D48.x20->default_fitting = 1;
        un_803F9D48.x20->default_alignment = 1;
        un_803F9D48.x24 = HSD_SisLib_803A6754(2, 0);
        un_803F9D48.x24->default_alignment = 1;
        un_803F9D48.x24->default_kerning = 1;
        un_803F9D48.x24->text_color = color;
    }
}

void un_802FE8CC(void)
{
    if (un_803F9D48.x0a) {
        if (un_803F9D48.x0b) {
            goto execute;
        }
    }
    return;
execute:
    un_803F9D48.x1 = 2;
    HSD_SisLib_803A5F50(2);
}

static inline void un_802FE918_update_x3(void)
{
    int r;
    int k;
    int new_x3;

    r = HSD_Randi(2);
    for (k = 0; k < 3; k++) {
        if (k == un_803F9D48.x3) {
            r++;
        } else if (r == k) {
            new_x3 = r;
            break;
        }
    }
    un_803F9D48.x3 = new_x3;
}

void un_802FE918(int a, int b, int c)
{
    struct un_803F9B30* x;
    int i;
    char date_text[0x104];
    HSD_Text** text;
    datetime date;

    lbAudioAx_800236DC();
    lbAudioAx_80023F28(un_803F9D48.x30[un_803F9D48.x3]);
    un_802FE918_update_x3();
    gmMainLib_8015D8B0(a);
    for (x = &un_803F9B30[0]; x->x0 != 66; x++) {
        if (x->x0 == a) {
            i = un_803F9A00[x->x4];
            goto found;
        }
    }
    i = 0;
found:
    un_803F9D48.x4 = i;
    if (a == 0x3E) {
        unsigned short v_x6;
        unsigned short v_x8;

        un_802FE3F8(a, 2, (short*) &un_803F9D48.x6, (short*) &un_803F9D48.x8);
        v_x6 = un_803F9D48.x6;
        v_x8 = un_803F9D48.x8;
        HSD_SisLib_803A6530(2, 0x4A, v_x6);
        HSD_SisLib_803A660C(2, 0x4A, un_803063D4(b, 0x4E, 0x174));
        HSD_SisLib_803A660C(2, 0x4A, v_x8);
        HSD_SisLib_803A6368(un_803F9D48.x20, 0x4A);
    } else {
        un_802FE3F8(a, 2, (short*) &un_803F9D48.x6, NULL);
        HSD_SisLib_803A6368(un_803F9D48.x20, un_803F9D48.x6);
    }
    gm_801692E8(c, &date);
    if (lbLang_IsSavedLanguageUS()) {
        sprintf(date_text, "%2d.%2d.%04d  %02d:%02d:%02d", date.month,
                date.day, date.year, date.hour, date.minute, date.second);
    } else {
        sprintf(date_text, "%04d.%2d.%2d  %02d:%02d:%02d", date.year,
                date.month, date.day, date.hour, date.minute, date.second);
    }
    text = &un_803F9D48.x24;
    HSD_SisLib_803A7664(*text);
    HSD_SisLib_803A6B98(*text, 320.0f, 316.0f, date_text);
}

void un_802FEBE0_OnEnter(void* arg0_)
{
    struct un_802FEBE0_OnEnter_arg0* arg0 = arg0_;
    struct un_803F9B30* x;
    int i;
    int arg0x4;
    int arg0x0;

    un_803124BC();
    un_803F9D48.x28 = arg0;
    un_803F9D48.x2C = arg0->x8;
    un_803F9D48.x3 = HSD_Randi(3);
    arg0x4 = arg0->x4;
    i = 0;
    arg0x0 = arg0->x0;
    un_803F9D48.x0b = 1;
    for (x = &un_803F9B30[0]; x->x0 != 66; x++) {
        if (x->x0 == arg0x0) {
            i = un_803F9A00[x->x4];
            goto found;
        }
    }
    i = 0;
found:
    un_803F9D48.x4 = i;
    un_802FE3F8_noinline(arg0x0, 2, (short*) &un_803F9D48.x6, NULL);
    un_803F9D48.x2 = -1;
    un_803F9D48.x1 = 0;
    un_803F9D48.xC = arg0x4;
    un_803F9D48.x0a = 1;
    un_804D6D98 = lbArchive_80016DBC("IfPrize", &un_804D6D9C,
                                     lbl_803F9D84, 0);
    if (lbLang_IsSavedLanguageUS()) {
        HSD_SisLib_803A62A0(2, lbl_803F9D84 + 0x18,
                            lbl_803F9D84 + 0x24);
    } else {
        HSD_SisLib_803A62A0(2, lbl_803F9D84 + 0x34,
                            lbl_803F9D84 + 0x24);
    }
    un_802FE6A8();
}

void un_802FED10_OnLeave(void* unused) {}
