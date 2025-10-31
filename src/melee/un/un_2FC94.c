#include "un_2FC9.h"

#include "baselib/archive.h"
#include "baselib/dobj.h"

#include "baselib/forward.h"

#include "baselib/jobj.h"
#include "baselib/random.h"
#include "baselib/sislib.h"
#include "gm/gm_unsplit.h"
#include "gm/gmmain_lib.h"
#include "lb/lb_00F9.h"
#include "lb/lbarchive.h"
#include "lb/lbaudio_ax.h"
#include "lb/lblanguage.h"
#include "sc/types.h"
#include "ty/toy.h"
#include "ty/tylist.h"
#include "un/un_2FC9.h"

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
#include <baselib/lobj.h>
#include <baselib/memory.h>
#include <baselib/particle.h>
#include <baselib/sislib.h>
#include <MSL/stdio.h>
#include <MSL/string.h>

// .data
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
struct un_803F9D48 {
    unsigned char x0a : 4;
    unsigned char x0b : 4;
    unsigned char x1;
    char x2;
    unsigned char x3;
    unsigned short x4;
    short x6;
    unsigned char x8;
    unsigned char x9;
    unsigned char xA;
    unsigned char xB;
    int xC;
    char x10[0x28 - 0x10];
    void* x28;
    int x2C;
    int x30;
    int x34;
    int x38;
} un_803F9D48 = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, { 0 }, 0, 0, 0x43, 0x44, 0x45,
};

// .sbss
/* 4D6D98 */ static HSD_Archive* un_804D6D98;
/* 4D6D9C */ static SceneDesc* un_804D6D9C;

// un_802FEBE0_OnEnter will try to inline this otherwise
#pragma push
#pragma dont_inline on
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
#pragma pop

void fn_802FE470(HSD_GObj* gobj)
{
    un_802FE918(0, 0, 0);
    gm_801A36A0(4);
    un_802FE8CC();
    un_802FE918(0, 0, 0);
    HSD_GObjPLink_80390228(0);
    HSD_GObjPLink_80390228(0);
    HSD_GObjPLink_80390228(0);
    lbArchive_80016EFC(0);
    gm_801A4B60();
    HSD_JObjReqAnimAll(0, 0);
    HSD_DObjReqAnimAll(0, 0);
    HSD_DObjReqAnimAll(0, 0);
    HSD_JObjAnimAll(0);
}

void un_802FE6A8(void)
{
    HSD_GObj* gobj_camera;
    HSD_GObj* gobj_light;
    HSD_GObj* gobj_ui;
    HSD_JObj* jobj_ui;
    GXColor color = { 0x5A, 0x5A, 0x5A, 0xFF };
    HSD_Text* text;
    HSD_Text* text2;
    gobj_camera = GObj_Create(HSD_GOBJ_CLASS_CAMERA, 20, 0);
    HSD_GObjObject_80390A70(gobj_camera, HSD_GObj_804D784B,
                            HSD_CObjLoadDesc(un_804D6D9C->cameras[0].desc));
    GObj_SetupGXLinkMax(gobj_camera, HSD_GObj_803910D8, 8);
    gobj_camera->gxlink_prios = 0xC00;
    gobj_light = GObj_Create(HSD_GOBJ_CLASS_LIGHT, 3, 0);
    HSD_GObjObject_80390A70(gobj_light, HSD_GObj_804D784A,
                            lb_80011AC4(un_804D6D9C->lights));
    GObj_SetupGXLink(gobj_light, HSD_GObj_LObjCallback, 10, 0);
    gobj_ui = GObj_Create(HSD_GOBJ_CLASS_UI, 15, 0);
    jobj_ui = HSD_JObjLoadJoint(un_804D6D9C->models[0]->joint);
    HSD_GObjObject_80390A70(gobj_ui, HSD_GObj_804D7849, jobj_ui);
    GObj_SetupGXLink(gobj_ui, HSD_GObj_JObjCallback, 11, 0);
    HSD_GObjProc_8038FD54(gobj_ui, fn_802FE470, 17);
    gm_8016895C(jobj_ui, un_804D6D9C->models[0], 0);
    HSD_JObjReqAnimAll(jobj_ui, 0.0);
    HSD_JObjAnimAll(jobj_ui);
    lb_80011E24(jobj_ui, 0, 2, -1);
    HSD_SisLib_803A611C(2, 0, 9, 20, 0, 14, 0, 18);
    text = HSD_SisLib_803A5ACC(2, 0, 105.0, 202.0, 0.0, 435.0, 75.0);
    text->default_fitting = 1;
    text->default_alignment = 1;
    text2 = HSD_SisLib_803A6754(2, 0);
    text2->default_alignment = 1;
    text2->default_kerning = 1;
    text2->text_color = color;
}

void un_802FE8CC(void)
{
    if (un_803F9D48.x0a && un_803F9D48.x0b) {
        un_803F9D48.x1 = 2;
        HSD_SisLib_803A5F50(2);
    }
}

void un_802FE918(int a, int b, int c)
{
    lbAudioAx_800236DC();
    lbAudioAx_80023F28(0);
    HSD_Randi(2);
    gmMainLib_8015D8B0(0);
    HSD_SisLib_803A6530(0, 0, 0);
    un_803063D4();
    HSD_SisLib_803A660C(0, 0, 0);
    HSD_SisLib_803A660C(0, 0, 0);
    HSD_SisLib_803A6368(0, 0);
    HSD_SisLib_803A6368(0, 0);
    gm_801692E8(0, 0);
    lbLang_IsSavedLanguageUS();
    sprintf(0, 0);
    sprintf(0, 0);
    HSD_SisLib_803A7664(0);
    HSD_SisLib_803A6B98(0, 0, 0, 0);
}

struct un_802FEBE0_OnEnter_arg0 {
    unsigned short x0;
    int x4;
    int x8;
};

void un_802FEBE0_OnEnter(void* arg0_)
{
    struct un_802FEBE0_OnEnter_arg0* arg0 = arg0_;
    struct un_803F9B30* x;
    int i;
    unsigned short arg0x0;
    int arg0x4;

    un_803124BC();
    un_803F9D48.x28 = arg0;
    un_803F9D48.x2C = arg0->x8;
    un_803F9D48.x3 = HSD_Randi(3);
    arg0x4 = arg0->x4;
    arg0x0 = arg0->x0;
    un_803F9D48.x0b = 1;
    i = 0;
    for (x = &un_803F9B30[0]; x->x0 != 66; x++) {
        if (x->x0 == arg0x0) {
            i = un_803F9A00[x->x4];
            goto found;
        }
    }
    i = 0;
found:
    un_803F9D48.x4 = i;
    un_802FE3F8(arg0x0, 2, &un_803F9D48.x6, NULL);
    un_803F9D48.x2 = -1;
    un_803F9D48.x1 = 0;
    un_803F9D48.xC = arg0x4;
    un_803F9D48.x0a = 1;
    un_804D6D98 = lbArchive_80016DBC("IfPrize", &un_804D6D9C,
                                     "ScInfPrize_scene_data", 0);
    if (lbLang_IsSavedLanguageUS()) {
        HSD_SisLib_803A62A0(2, "SdPrize.usd", "SIS_PrizeData");
    } else {
        HSD_SisLib_803A62A0(2, "SdPrize.dat", "SIS_PrizeData");
    }
    un_802FE6A8();
}

void un_802FED10_OnLeave(UNK_T unused) {}
