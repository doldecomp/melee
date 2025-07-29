#include "gm_18A5.h"

#include "gm_18A5.static.h"

#include <sysdolphin/baselib/controller.h>
#include <sysdolphin/baselib/fog.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/jobj.h>
#include <melee/gm/gm_unsplit.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/lb/lb_00F9.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lblanguage.h>
#include <melee/mn/mnmain.h>
#include <melee/mn/mnstagesel.h>

/// #fn_8018A514

void fn_8018A970(int arg0)
{
    int i;
    for (i = 0; i < 0x40; i++) {
        if (lbl_80473AB8[i].x0 != 0) {
            HSD_GObj* gobj = GObj_Create(0xE, 0x1B, 0);
            gobj->user_data = &lbl_80473AB8[i];
            if (i == 0) {
                HSD_GObjProc_8038FD54(gobj, fn_8018B090, 0);
            }
            GObj_SetupGXLink(gobj, fn_8018E46C, 4, 1);
        }
    }

    if (arg0 < 9) {
        if (arg0 == 1) {
            lbl_80473AB8[5].x5E = 1;
        } else if (arg0 == 3) {
            lbl_80473AB8[10].x32 = 1;
            lbl_80473AB8[11].x5E = 1;
        } else if (arg0 == 5) {
            lbl_80473AB8[23].x5E = 1;
        } else if (arg0 == 7) {
            lbl_80473AB8[46].x5E = 1;
            lbl_80473AB8[47].x5E = 1;
        }
    }
}

/// #fn_8018AA74

/// #fn_8018B090

/// #fn_8018C8D4

/// #fn_8018D50C

/// #fn_8018DC18

/// #fn_8018DF68

/// #fn_8018E46C

/// #fn_8018E618

/// #fn_8018E85C

void fn_8018EC48(void)
{
    mn_8022F138(0x19, 0x1C);
    mn_8022F138(0x12, 0x15);
}

void fn_8018EC7C(void)
{
    mn_8022F0F0(0x1B);
    mn_8022F0F0(0x14);
}

/// #fn_8018ECA8

/// #fn_8018F00C

/// #gm_8018F1B0

/// #fn_8018F310

u8 fn_8018F3BC(s32 arg0)
{
    return M2C_FIELD(&lbl_803D9D20.pad_0[arg0], u8*, 0x59);
}

/// #fn_8018F3D0

/// #fn_8018F410

int fn_8018F4A0(void)
{
    int temp_r3 = mnStageSel_8025BBD4();
    if (!gm_80164430(temp_r3)) {
        printf("This is impossible stage num from mnSelStageRandom() -> stage %d \n", temp_r3);
        __assert("gmtoulib.c", 0x53D, "0");
    }
    return temp_r3;
}

/// #fn_8018F508

#pragma push
#pragma dont_inline on
char* fn_8018F5F0(void)
{
    if (lbLang_IsSavedLanguageUS()) {
        return "SdTou.usd";
    } else {
        return "SdTou.dat";
    }
}
#pragma pop

UNK_T fn_8018F62C(HSD_GObj* gobj)
{
    return gobj->user_data;
}

TmData* gm_8018F634(void)
{
    return &gm_804771C4;
}

u32 fn_8018F640(int arg0)
{
    if (arg0 >= 4) {
        arg0 = 4;
    }
    return gm_801A36A0(arg0);
}

u32 fn_8018F674(int arg0)
{
    if (arg0 >= 4) {
        arg0 = 4;
    }
    return gm_801A36C0(arg0);
}

u32 fn_8018F6A8(int arg0)
{
    if (arg0 >= 4) {
        arg0 = 4;
    }
    return gm_801A3680((u8) arg0);
}

int fn_8018F6DC(int arg0)
{
    if (arg0 >= 0x13) {
        if (arg0 == 0x1D) {
            return 5;
        }
        return arg0 - 1;
    }
    return arg0;
}

int fn_8018F6FC(int arg0)
{
    if (arg0 >= 0x13) {
        if (arg0 == 0x1D) {
            return 5;
        }
        return arg0 + 1;
    }
    return arg0;
}

float fn_8018F71C(int arg0, int arg1)
{
    return arg0 + arg1 * 0x1E;
}

int fn_8018F74C(void)
{
    int i;

    for (i = 0; i < 0x40; i++) {
        if (lbl_80473AB8[i].x1 != 0) {
            break;
        }
    }

    return i;
}

int fn_8018F808(void)
{
    int i;
    int noerrcount = 0;
    for (i = 0; i < 4; i++) {
        if (HSD_PadMasterStatus[(u8) i].err == 0) {
            noerrcount += 1;
        }
    }
    return noerrcount;
}

/// #fn_8018F888

/// #fn_8018FA24

void fn_8018FBD8(void* arg0, s32 arg1)
{
    M2C_FIELD(arg0, s32*, 0x2C) = arg1;
}

/// #fn_8018FBE0

void fn_8018FDC4(HSD_JObj* jobj, float x, float y, float z)
{
    if ((int) x != 666) {
        HSD_JObjSetTranslateX(jobj, x);
    }
    if ((int) y != 666) {
        HSD_JObjSetTranslateY(jobj, y);
    }
    if ((int) z != 666) {
        HSD_JObjSetTranslateZ(jobj, z);
    }
}

void fn_8018FF9C(HSD_JObj* jobj, float x, float y, float z)
{
    if ((int) x != 666) {
        HSD_JObjSetScaleX(jobj, x);
    }
    if ((int) y != 666) {
        HSD_JObjSetScaleY(jobj, y);
    }
    if ((int) z != 666) {
        HSD_JObjSetScaleZ(jobj, z);
    }
}

HSD_GObj* fn_80190174(HSD_CObjDesc* cobjdesc)
{
    HSD_GObj* gobj = GObj_Create(0x13, 0x12, 0);
    HSD_CObj* cobj = HSD_CObjLoadDesc(cobjdesc);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMax(gobj, HSD_GObj_803910D8, 0);
    gobj->gxlink_prios = 7;
    return gobj;
}

HSD_GObj* fn_801901F8(HSD_CObjDesc* cobjdesc)
{
    HSD_GObj* gobj = GObj_Create(0x13, 0x15, 2);
    HSD_CObj* cobj = HSD_CObjLoadDesc(cobjdesc);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMax(gobj, HSD_GObj_803910D8, 2);
    gobj->gxlink_prios = 0xA;
    return gobj;
}

void fn_8019027C(UNK_T lights)
{
    HSD_GObj* gobj = GObj_Create(0xB, 0x1A, 0);
    HSD_LObj* lobj = lb_80011AC4(lights);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784A, lobj);
    GObj_SetupGXLink(gobj, HSD_GObj_LObjCallback, 1, 0);
}

/// #fn_801902F0

HSD_GObj* fn_8019035C(bool arg0, DynamicModelDesc* model, int arg2, int arg3, int arg4, bool arg5, void (*arg6)(HSD_GObj*), f32 arg8)
{
    HSD_GObj* gobj = GObj_Create(0xE, arg3, 0);
    HSD_JObj* jobj = HSD_JObjLoadJoint(model->joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, arg4, 0);
    if (arg6 != NULL) {
        HSD_GObjProc_8038FD54(gobj, arg6, 0);
    }
    if (arg5) {
        gm_8016895C(jobj, model, arg2);
        HSD_JObjReqAnimAll(jobj, arg8);
        HSD_JObjAnimAll(jobj);
        if (arg0) {
            HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        }
    }
    return gobj;
}

void fn_8019044C(HSD_JObj* jobj, float arg1)
{
    HSD_JObjReqAnimAll(jobj, arg1);
    HSD_JObjAnimAll(jobj);
}

void fn_80190480(float arg8)
{
    if ((int) arg8 == 0) {
        HSD_CObjSetFov(lbl_803D9D20.cobj, lbl_803D9D20.xD0);
        return;
    }
    HSD_CObjSetFov(lbl_803D9D20.cobj, arg8);
}

void fn_801904D0(void)
{
    HSD_CObjSetInterest(lbl_803D9D20.cobj, &lbl_803D9D20.interest);
    HSD_CObjSetEyePosition(lbl_803D9D20.cobj, &lbl_803D9D20.eye_position);
}

/// #fn_80190520

/// #gm_801905F0

/// #fn_80190ABC

/// #gm_80190EA4

/// #gm_80190FE4

/// #fn_801910E0

/// #fn_80191154

/// #fn_80191240

/// #fn_801913BC

/// #fn_80191678

/// #fn_8019175C

/// #fn_801918F0

/// #fn_80191A54

/// #fn_80191B5C

/// #fn_80191CA4

/// #fn_80191D38

/// #fn_80191E9C

/// #fn_80191FD4

/// #fn_8019237C

/// #fn_8019249C

#pragma push
#pragma dont_inline on
void fn_80192690(HSD_GObj* gobj)
{
    TmData* tmdata = gm_8018F634();
    HSD_JObj* jobj = gobj->hsd_obj;

    if (tmdata->x0 <= 9) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        return;
    }
    HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
    if (tmdata->x0 < 0x11 || tmdata->x0 > 0x12) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        return;
    }
    fn_8018FDC4(jobj, 666.0F, 666.0F, 0.3F);
    fn_8019044C(jobj, tmdata->x0 - 0x11);
}
#pragma pop

/// #fn_80192758

/// #fn_80192938

/// #fn_80192BB0

/// #fn_80192E6C

#pragma push
#pragma dont_inline on
void fn_80193230(void)
{
    HSD_GObj* gobj;
    HSD_Fog* fog;
    PAD_STACK(4);

    fn_8019035C(0, lbl_804D664C->models[5], 0, 0x1A, 2, 1, fn_801910E0, 0.0F);
    fn_8019035C(0, lbl_804D664C->models[4], 0, 0x1A, 2, 1, fn_80191154, 0.0F);
    fn_80192BB0();
    fn_80192E6C();
    gobj = GObj_Create(0xE, 0x1A, 0);
    fog = HSD_FogLoadDesc(lbl_804D664C->fogs[0].desc);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7848, fog);
    GObj_SetupGXLink(gobj, HSD_GObj_FogCallback, 0, 0);
}
#pragma pop

/// #fn_80193308

/// #fn_801935B8

/// #fn_801937C4

/// #fn_80193B58

/// #fn_80193FCC

/// #fn_80194658

/// #fn_801949B4

/// #fn_80194BC4

/// #fn_80194D84

/// #fn_80194F30

/// #fn_801953C8

/// #fn_80195AF0

/// #fn_80195CCC

/// #fn_8019610C

/// #gm_8019628C_OnFrame

extern struct {
    UNK_T x0;
    UNK_T x4;
    UNK_T x8;
} lbl_804771B8;

void gm_801963B4_OnEnter(void* arg0)
{
    const char* filename;
    lbAudioAx_80026F2C(0x12);
    lbAudioAx_8002702C(2, 8);
    lbAudioAx_80027168();
    lbAudioAx_80027648();
    lbl_804D6640 = lbArchive_80016DBC("GmTou1p", &lbl_804D664C, "ScGamTour_scene_data", 0);
    lbl_804D6644 = lbArchive_80016DBC("GmTou2p", &lbl_804D6650, "ScGamTour_scene_data", 0);
    lbl_804D6648 = lbArchive_LoadArchive("MnExtAll");
    filename = "TmBox.dat";
    lbl_804D6638 = lbArchive_80016DBC(filename,
            &lbl_804771B8.x0, "tournament_box2_array",
            &lbl_804771B8.x4, "tournament_box3_array",
            &lbl_804771B8.x8, "tournament_box4_array",
            0);
    HSD_SisLib_803A62A0(0, fn_8018F5F0(), "SIS_TournamentData");
    fn_801935B8();
    lbAudioAx_800237A8(0x7539, 0x7F, 0x40);
    lbAudioAx_80023F28(gmMainLib_8015ECB0());
}

/// #gm_801964A4_OnLeave

/// #fn_80196510

s32 fn_8019655C(void)
{
    return lbl_804D4190;
}

/// #fn_80196564

/// #fn_80196594

/// #fn_801965C4

/// #fn_80196684

/// #fn_801967E0

/// #fn_80196CF8

/// #fn_80196DBC

/// #fn_80196E30

/// #fn_80196EEC

/// #fn_80196FFC

/// #fn_801973F8

/// #fn_801975C8

/// #fn_801976D4

/// #fn_801977AC

/// #fn_80197AF0

/// #fn_80197D4C

/// #fn_80197E18

/// #fn_80197FD8

/// #fn_801981A0

/// #fn_801983E4

/// #fn_80198584

/// #fn_801985D4

/// #fn_80198824

/// #fn_80198BA0

/// #fn_80198C60

/// #fn_80198D18

/// #fn_80198EBC

/// #fn_80199AF0

/// #fn_8019A158

/// #fn_8019A71C

/// #gm_8019A828

/// #fn_8019A86C

/// #fn_8019AF50

/// #gm_8019B2DC_OnFrame

/// #fn_8019B458

/// #fn_8019B81C

/// #fn_8019B860
