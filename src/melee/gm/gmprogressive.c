#include "gmprogressive.h"

#include "gm_unsplit.h"

#include <sysdolphin/baselib/archive.h>
#include <sysdolphin/baselib/cobj.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/sislib.h>
#include <melee/gm/gm_1A36.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/gm/types.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lblanguage.h>
#include <melee/sc/types.h>

static struct {
    HSD_Archive* x0;
    HSD_JObj* x4;
    HSD_Text* x8;
    int xC;
    int x10;
    int x14;
    u32 x18;
    u32 x1C;
    u8 x20;
} gm_80480D70;

static void gm_801AD088(void)
{
    SceneDesc* spC;
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    HSD_CObj* cobj;
    HSD_Text* text;
    PAD_STACK(4);

    gm_80480D70.x0 = lbArchive_80016DBC("NtProge.dat", &spC,
                                        "ScNtcProgressive_scene_data", 0);

    gobj = GObj_Create(0x13, 0x14, 0);
    cobj = HSD_CObjLoadDesc(spC->cameras[0].desc);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMax(gobj, HSD_GObj_803910D8, 0);
    gobj->gxlink_prios = 0x4801;
    gm_80480D70.xC = HSD_SisLib_803A611C(0, 0, 0xE, 0xF, 0, 0xE, 8, 0);
    if (lbLang_IsSavedLanguageUS() != 0) {
        HSD_SisLib_803A62A0(0, "SdProge.usd", "SIS_ProgeData");
    } else {
        HSD_SisLib_803A62A0(0, "SdProge.dat", "SIS_ProgeData");
    }
    gm_80480D70.x8 = HSD_SisLib_803A5ACC(0, gm_80480D70.xC, 0.0F, 0.0F, 0.0F,
                                         640.0F, 480.0F);
    text = gm_80480D70.x8;
    text->font_size.x = 1.0F;
    text->font_size.y = 1.0F;

    gobj = GObj_Create(0xE, 0xF, 0);
    jobj = HSD_JObjLoadJoint(spC->models[0]->joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0xB, 0);
    gm_8016895C(jobj, spC->models[0], 0);
    HSD_JObjReqAnimAll(jobj, 0.0F);
    HSD_JObjAnimAll(jobj);
    gm_80480D70.x4 = jobj;
}

static void gm_801AD254(int arg0)
{
    HSD_JObj* jobj = gm_80480D70.x4;
    PAD_STACK(0x10);

    switch (arg0) {
    case 0:
        gm_80480D70.x8->hidden = 0;
        HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
        HSD_SisLib_803A6368(gm_80480D70.x8, 6);
        HSD_JObjReqAnimAll(jobj, 0.0F);
        HSD_JObjSetTranslateY(jobj, -15.0F);
        break;
    case 4:
        gm_80480D70.x8->hidden = 0;
        HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
        HSD_SisLib_803A6368(gm_80480D70.x8, 5);
        HSD_JObjReqAnimAll(jobj, 0.0F);
        HSD_JObjSetTranslateY(jobj, 0.0F);
        break;
    case 5:
        gm_80480D70.x8->hidden = 0;
        HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
        HSD_SisLib_803A6368(gm_80480D70.x8, 4);
        HSD_JObjReqAnimAll(jobj, 0.0F);
        HSD_JObjSetTranslateY(jobj, 0.0F);
        break;
    case 1:
        gm_80480D70.x8->hidden = 0;
        HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
        HSD_SisLib_803A6368(gm_80480D70.x8, 2);
        HSD_JObjReqAnimAll(jobj, 1.0F);
        HSD_JObjSetTranslateY(jobj, 0.0F);
        break;
    case 2:
        gm_80480D70.x8->hidden = 0;
        HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
        HSD_SisLib_803A6368(gm_80480D70.x8, 3);
        HSD_JObjReqAnimAll(jobj, 2.0F);
        HSD_JObjSetTranslateY(jobj, 0.0F);
        break;
    }
    HSD_JObjAnimAll(jobj);
}

void gm_801AD620_OnFrame(void)
{
    PAD_STACK(0x8);

    if (gm_80480D70.x1C == 0) {
        gm_80480D70.x1C++;
        return;
    }
    if (gm_80480D70.x10 == 3) {
        gm_80480D70.x1C++;
        if (gm_80480D70.x1C == 0xB) {
            gmMainLib_8046B0F0.progressive = true;
            gmMainLib_8015F500();
            OSSetProgressiveMode(1);
        } else if (gm_80480D70.x1C == 0x6E) {
            gm_80480D70.x14 = 1;
            gm_801AD254(4);
            gm_80480D70.x10 = 4;
        }
    } else {
        if ((gm_801A36A0(4) & 0x4000000000) && gm_80480D70.x10 == 2 &&
            gm_80480D70.x14 == 0)
        {
            lbAudioAx_80024030(2);
            gm_80480D70.x10 = 1;
            gm_801AD254(gm_80480D70.x10);
        }
        if ((gm_801A36A0(4) & 0x8000000000) && gm_80480D70.x10 == 1 &&
            gm_80480D70.x14 == 0)
        {
            lbAudioAx_80024030(2);
            gm_80480D70.x10 = 2;
            gm_801AD254(gm_80480D70.x10);
        }
        if ((gm_801A36A0(4) & 0x100000000) && gm_80480D70.x14 == 0) {
            if (gm_80480D70.x10 == 1) {
                lbAudioAx_80024030(1);
                gm_80480D70.x10 = 3;
                gm_80480D70.x8->hidden = 1;
                HSD_JObjSetFlagsAll(gm_80480D70.x4, JOBJ_HIDDEN);
            } else if (gm_80480D70.x10 == 2) {
                lbAudioAx_80024030(1);
                gm_80480D70.x14 = 2;
                gm_801AD254(5);
                OSSetProgressiveMode(0);
            }
        }
        if (gm_80480D70.x10 == 0 || gm_80480D70.x14 != 0) {
            gm_80480D70.x18++;
            gm_80480D70.x20 = 1;
        }
        if (gm_80480D70.x20 != 0 && gm_80480D70.x18 >= 0x12C) {
            gm_801A4B60();
        }
    }
}

void gm_801AD874_OnEnter(UNK_T arg0)
{
    int* dst = arg0;
    int var_r0;

    gm_801AD088();
    gm_801AD254(*dst);
    gm_80480D70.x10 = *dst;
    if (gm_80480D70.x10 != 1) {
        var_r0 = 2;
    } else {
        var_r0 = 0;
    }
    gm_80480D70.x14 = var_r0;
    gm_80480D70.x18 = 0;
    gm_80480D70.x1C = 0;
    gm_80480D70.x20 = 0;
}

void gm_801AD8EC_OnLeave(UNK_T arg0)
{
    int* dst = arg0;
    *dst = gm_80480D70.x14;
    lbArchive_80016EFC(gm_80480D70.x0);
}
