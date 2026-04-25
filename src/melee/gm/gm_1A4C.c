#include "gm_1A4C.h"

#include "gm_unsplit.h"

#include "ft/forward.h"
#include "gm/gm_1BA8.h"
#include "gm/gmregtyfall.h"
#include "if/textlib.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbbgflash.h"
#include "lb/lbmthp.h"
#include "mn/mnmain.h"
#include "ty/tydisplay.h"
#include "ty/toy.h"

#include <sysdolphin/baselib/archive.h>
#include <sysdolphin/baselib/cobj.h>
#include <sysdolphin/baselib/fog.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/gobjplink.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/lobj.h>
#include <sysdolphin/baselib/random.h>
#include <sysdolphin/baselib/sobjlib.h>

#include "gm/gmregtyfall.static.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "sc/types.h"

extern Event gm_804D6724;

void fn_801A7A44(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

void fn_801A7A68(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

static HSD_GObj* gm_804D67B0;
static HSD_GObj* gm_804D67B4;

void fn_801A7A8C(HSD_GObj* gobj)
{
    HSD_CObj* cobj = GET_COBJ(gobj);
    HSD_CObjAnim(cobj);
    if (cobj->aobj->curr_frame == cobj->aobj->end_frame) {
        HSD_GObjPLink_80390228(gm_804D67B0);
        HSD_GObjPLink_80390228(gm_804D67B4);
        mn_8022F0F0(3);
        gm_801A9630();
        HSD_GObjPLink_80390228(gobj);
    }
}

void gm_801A7B00(void)
{
    HSD_GObj* gobj;
    HSD_GObj* cam_gobj;
    HSD_CObj* cobj;
    HSD_JObj* jobj;
    HSD_JObj* child;
    HSD_JObj* target;
    s32 char_idx;
    f32 val;
    f32 scale;
    PAD_STACK(0x30);

    // Light GObj
    gobj = GObj_Create(0xB, 3, 0);
    HSD_GObjObject_80390A70(gobj, (u8) HSD_GObj_804D784A,
                            lb_80011AC4(gm_804D67A8->lights));
    GObj_SetupGXLink(gobj, HSD_GObj_LObjCallback, 0, 0);

    // Camera GObj
    cam_gobj = GObj_Create(0x13, 0x14, 0);
    cobj = lb_80013B14(
        (HSD_CameraDescPerspective*) gm_804D67A8->cameras[0].desc);
    HSD_GObjObject_80390A70(cam_gobj, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMax(cam_gobj, HSD_GObj_803910D8, 8);
    cam_gobj->gxlink_prios = 0x801;
    child = NULL;
    HSD_CObjAddAnim(cobj, gm_804D67A8->cameras[0].anims[0]);
    HSD_CObjReqAnim(cobj, 0.0f);
    HSD_CObjAnim(cobj);
    HSD_GObj_SetupProc(cam_gobj, fn_801A7A8C, 0);

    // Main JObj GObj
    gobj = GObj_Create(0xE, 0xF, 0);
    gm_804D67B0 = gobj;
    jobj = HSD_JObjLoadJoint(gm_804D6798);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0xB, 0);
    gm_8016895C(jobj, gm_804D67A8->models[0], 0);
    HSD_JObjReqAnimAll(jobj, 0.0f);
    HSD_JObjAnimAll(jobj);
    HSD_GObj_SetupProc(gobj, fn_801A7A44, 0x17);

    gm_801A4B90();

    // Character display GObj
    gobj = GObj_Create(0xE, 0xF, 0);
    gm_804D67B4 = gobj;
    jobj = HSD_JObjLoadJoint(gm_804D67AC->models[0]->joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0xB, 0);

    char_idx = gm_801A659C(gm_801BEFB0());
    if (jobj == NULL) {

    } else {
        child = jobj->child;
    }

    val = -un_803060BC(char_idx, 0);
    fake_tyfall_HSD_JObjSetTranslateX(child, val);
    val = -un_803060BC(char_idx, 1);
    fake_tyfall_HSD_JObjSetTranslateY(child, val);
    val = -un_803060BC(char_idx, 2);
    fake_tyfall_HSD_JObjSetTranslateZ(child, val);

    val = -(0.017453292f * un_803060BC(char_idx, 5));
    fake_tyfall_HSD_JObjSetRotationY(child, val);

    scale = 1.0f / un_803060BC(char_idx, 3);
    scale = un_803060BC(char_idx, 4) * scale;
    fake_tyfall_HSD_JObjSetScaleX(child, scale);
    fake_tyfall_HSD_JObjSetScaleY(child, scale);
    fake_tyfall_HSD_JObjSetScaleZ(child, scale);

    HSD_GObj_SetupProc(gobj, fn_801A7A68, 0x17);

    // Walk JObj tree to find constraint target
    target = HSD_JObjGetChild(GET_JOBJ(gm_804D67B0));
    target = HSD_JObjGetChild(target);
    target = HSD_JObjGetChild(target);
    target = HSD_JObjGetChild(target);
    target = HSD_JObjGetChild(target);
    target = HSD_JObjGetNext(target);

    lb_8000C1C0((HSD_JObj*) gobj->hsd_obj, target);
    lb_8000C290((HSD_JObj*) gobj->hsd_obj, target);
}

inline s32 fn_801A7FB4_inline()
{
    s32 i;
    s32 count;
    count = 0;
    for (i = count; i < 0x1A; i++) {
        if (un_803048C0(gm_801A659C(i)) ? true : false) {
            count++;
        }
    }
    return count;
}

inline s32 fn_801A7FB4_inline2()
{
    s32 count;
    s32 i;
    count = 0;
    for (i = count; i < 0x1A; i++) {
        if (un_803048C0(gm_801A659C(i)) ? true : false) {
            count++;
        }
    }
    return count;
}

void fn_801A7FB4(HSD_GObj* gobj)
{
    HSD_Fog* fog = GET_FOG(gobj);
    int count;

    gm_801A4310();
    count = fn_801A7FB4_inline();

    if (count <= 5) {
        if (fog->aobj->curr_frame < 185.0f) {
            HSD_FogInterpretAnim(fog);
        }
        return;
    }

    gm_801A4310();
    count = fn_801A7FB4_inline2();

    if (count <= 0xD) {
        if (fog->aobj->curr_frame < 200.0f) {
            HSD_FogInterpretAnim(fog);
        }
    } else {
        HSD_FogInterpretAnim(fog);
    }
}

void fn_801A80CC(HSD_GObj* gobj)
{
    HSD_LObjAnimAll(GET_LOBJ(gobj));
}

void fn_801A80F0(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

void gm_801A8114(HSD_JObj* arg0, int arg1)
{
    HSD_JObj* transJobj;
    float scale;

    if (arg0 == NULL) {
        transJobj = NULL;
    } else {
        transJobj = arg0->child;
    }

    HSD_JObjSetTranslateX(transJobj, un_803060BC(arg1, 0));
    HSD_JObjSetTranslateY(transJobj, un_803060BC(arg1, 1));
    HSD_JObjSetTranslateZ(transJobj, un_803060BC(arg1, 2));

    HSD_JObjSetRotationY(transJobj, 0.017453292f * un_803060BC(arg1, 5));

    scale = un_803060BC(arg1, 3) * (1.0F / un_803060BC(arg1, 4));
    if (transJobj == NULL) {
        __assert("gmregenddisp.c", 0x16BU, "transJobj");
    }

    HSD_JObjSetScaleX(transJobj, scale);
    HSD_JObjSetScaleY(transJobj, scale);
    HSD_JObjSetScaleZ(transJobj, scale);
}

void fn_801A851C(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
    HSD_JObjSetTranslateZ(GET_JOBJ(gobj), 2.0F);
    if (gm_801A4BA8() == 0x174) {
        lbAudioAx_800237A8(0x7EF41, 0x7F, 0x40);
    }
}

#include <MSL/math.h>

void gm_801A85E4(HSD_JObj* jobj, s32 arg1, s32 arg2)
{
    s32 idx;
    f32 angle;
    f32 x;
    f32 z;
    PAD_STACK(0x20);

    if (arg1 <= 4) {
        arg2 = 4 - arg1;
        idx = arg2 + 2;
        if (idx > 4) {
            arg2 = 4 - idx;
            idx = arg2 + 2;
        }
        angle = 0.017453292f *
                ((45.0f * (f32) idx) + (2.0f * HSD_Randf()) - 1.0f);
        x = 25.0f * cosf(angle);
        HSD_JObjSetTranslateX(jobj, x);
        z = 0.9f * ((25.0f * -sinf(angle)) + -18.0f);
        HSD_JObjSetTranslateZ(jobj, z);
    } else if (arg1 <= 0xC) {
        arg2 = 0xC - arg1;
        idx = arg2 + 8;
        if (idx > 0xC) {
            arg2 = 0xC - idx;
            idx = arg2 + 8;
        }
        angle = 0.017453292f *
                ((25.714285f * (f32) (idx - 5)) + (4.0f * HSD_Randf()) -
                 2.0f);
        x = 50.0f * cosf(angle);
        HSD_JObjSetTranslateX(jobj, x);
        z = 0.9f * ((50.0f * -sinf(angle)) + -18.0f);
        HSD_JObjSetTranslateZ(jobj, z);
    } else if (arg1 <= 0x15) {
        arg2 = 0x15 - arg1;
        idx = arg2 + 0x11;
        if (idx > 0x15) {
            arg2 = 0x15 - idx;
            idx = arg2 + 0x11;
        }
        angle = 0.017453292f *
                ((22.5f * (f32) (idx - 0xD)) + HSD_Randf() - 0.5f);
        x = 75.0f * cosf(angle);
        HSD_JObjSetTranslateX(jobj, x);
        z = 0.8f * ((75.0f * -sinf(angle)) + -18.0f);
        HSD_JObjSetTranslateZ(jobj, z);
    } else if (arg1 == 0x16) {
        HSD_JObjSetTranslateX(jobj, -80.0f);
        HSD_JObjSetTranslateZ(jobj, -70.0f);
    } else if (arg1 == 0x17) {
        HSD_JObjSetTranslateX(jobj, 75.0f);
        HSD_JObjSetTranslateZ(jobj, -75.0f);
    } else {
        HSD_JObjSetTranslateX(jobj, 90.0f);
        HSD_JObjSetTranslateZ(jobj, -55.0f);
    }
}

static HSD_GObj* gm_80480A00[0x34];
static s32 gm_80480AD0[0x1A];

void gm_801A8D54(s32* arg0)
{
    s32 sp84[0x1A];
    int i;
    int j;
    int count;
    s32 temp_i;
    s32 temp_j;
    PAD_STACK(0x68);

    for (i = 0; i < 0x1A; i++) {
        arg0[i] = 0x1A;
        sp84[i] = 0x1A;
    }

    count = 0;
    for (i = 0; i < 0x1A; i++) {
        if ((u32)(i - 0x12) <= 1U) {
            gm_801A4310();
            if ((un_803048C0(gm_801A659C(i)) ? true : false) &&
                gm_801BEFB0() != CKIND_ZELDA &&
                gm_801BEFB0() != CKIND_SEAK)
            {
                sp84[count] = i;
                count++;
            }
        } else {
            gm_801A4310();
            if ((un_803048C0(gm_801A659C(i)) ? true : false) &&
                i != gm_801BEFB0())
            {
                sp84[count] = i;
                count++;
            }
        }
    }

    for (i = 0; i < 0x1A; i++) {
        if (sp84[i] != 0x1A) {
            for (j = i + 1; j < 0x1A; j++) {
                if (0x1A != sp84[j]) {
                    if ((gm_80480AD0[sp84[i]] < gm_80480AD0[sp84[j]] ? 1 : 2) == 2) {
                        temp_i = sp84[i];
                        sp84[i] = sp84[j];
                        sp84[j] = temp_i;
                    }
                }
            }
        }
    }

    for (i = 0; i < 0x1A; i++) {
        arg0[i] = sp84[i];
    }
}

void gm_801A9094(void)
{
    s32 sp8C[0x1A];
    s32 i;
    TyDspEntry* dsp;
    HSD_Joint* joint;
    HSD_MatAnimJoint* matanim;
    HSD_Joint* bg_joint;
    HSD_GObj* gobj;
    HSD_JObj* root;
    HSD_JObj* child;
    PAD_STACK(0x88);

    gm_801A8D54(sp8C);
    i = 0x19;
    do {
        if (sp8C[i] != 0x1A) {
            dsp = un_8031B9DC(gm_801A659C(sp8C[i]));
            joint = HSD_ArchiveGetPublicAddress(
                gm_804D679C, (const char*) un_8031BB34((s8) dsp->x04));
            matanim = HSD_ArchiveGetPublicAddress(
                gm_804D679C, un_8031BB94((s8) dsp->x04));
            bg_joint = HSD_ArchiveGetPublicAddress(
                gm_804D679C, "ToyDspStand_Top_joint");
            gobj = GObj_Create(0xE, 0xF, 0);
            gm_80480A00[sp8C[i]] = gobj;
            root = HSD_JObjAlloc();
            HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, root);
            GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0xB, 0);
            HSD_JObjSetScaleX(root, 1.8f);
            HSD_JObjSetScaleY(root, 1.8f);
            HSD_JObjSetScaleZ(root, 1.8f);
            if (joint == NULL) {
                __assert("jobj.h", 0x2F5U, "joint");
            }
            child = HSD_JObjLoadJoint(joint);
            if (child == NULL) {
                __assert("jobj.h", 0x2F7U, "jobj");
            }
            HSD_JObjAddChild(root, child);
            HSD_JObjAddAnimAll(child, NULL, matanim, NULL);
            HSD_JObjReqAnimAll(child, (f32) dsp->x05);
            HSD_JObjAnimAll(child);
            HSD_JObjSetTranslateX(child, dsp->x08);
            HSD_JObjSetTranslateZ(child, dsp->x0C);
            HSD_JObjAddChild(root, HSD_JObjLoadJoint(bg_joint));
            gm_801A85E4(root, i, sp8C[i]);
        }
        i--;
    } while (i >= 0);
}

void fn_801A9498(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

static s32 gm_804D67C4;

void fn_801A94BC(HSD_GObj* gobj)
{
    int i;
    int var_r31;
    HSD_CObj* cobj;
    PAD_STACK(0x10);

    cobj = GET_COBJ(gobj);
    gm_801A4310();
    var_r31 = 0;
    for (i = 0; i < 0x1A; i++) {
        if (un_803048C0(gm_801A659C(i)) ? true : false) {
            var_r31++;
        }
    }
    if (var_r31 <= 5) {
        if (cobj->aobj->curr_frame < 160.0f) {
            HSD_CObjAnim(cobj);
        } else if (--gm_804D67C4 == 0) {
            gm_801A4B60();
        }
        return;
    }

    gm_801A4310();
    var_r31 = 0;
    for (i = 0; i < 0x1A; i++) {
        if (un_803048C0(gm_801A659C(i)) ? true : false) {
            var_r31++;
        }
    }
    if (var_r31 <= 0xD) {
        if (cobj->aobj->curr_frame < 190.0f) {
            HSD_CObjAnim(cobj);
        } else if (--gm_804D67C4 == 0) {
            gm_801A4B60();
        }
    } else {
        if (cobj->aobj->curr_frame < cobj->aobj->end_frame) {
            HSD_CObjAnim(cobj);
        } else if (--gm_804D67C4 == 0) {
            gm_801A4B60();
        }
    }
}

static HSD_GObj* gm_804D67B8;
static HSD_GObj* gm_804D67BC;
static HSD_GObj* gm_804D67C0;

void gm_801A8114_inline(HSD_JObj* arg0, int arg1);
void gm_801A8114_inline(HSD_JObj* arg0, int arg1) {
    gm_801A8114(arg0, arg1);
}

void gm_801A9630(void)
{
    HSD_GObj* gobj;
    HSD_GObj* cam_gobj;
    HSD_CObj* cobj;
    HSD_Fog* fog;
    HSD_LObj* lobj;
    HSD_JObj* jobj;
    HSD_JObj* child;
    s32 i;
    PAD_STACK(8);

    for (i = 0; i < 0x1A; i++) {
        gm_80480A00[i] = NULL;
    }

    gm_804D67C4 = 0xB4;

    for (i = 0; i < 0x1A; i++) {
        gm_801A4310();
        if (un_803048C0(gm_801A659C(i)) ? true : false) {
            gm_80480AD0[i] = HSD_Randi(0x2710);
        } else {
            gm_80480AD0[i] = 0;
        }
    }

    // Fog GObj
    gobj = GObj_Create(0xE, 3, 0);
    fog = HSD_FogLoadDesc(gm_804D67A4->fogs->desc);
    HSD_GObjObject_80390A70(gobj, (u8) HSD_GObj_804D7848, fog);
    GObj_SetupGXLink(gobj, HSD_GObj_FogCallback, 0, 0);
    HSD_Fog_8037DE7C(fog, gm_804D67A4->fogs->anims[0]->aobjdesc);
    HSD_FogReqAnim(fog, 0.0f);
    HSD_FogInterpretAnim(fog);
    HSD_GObj_SetupProc(gobj, fn_801A7FB4, 0x17);

    // Light GObj
    gobj = GObj_Create(0xB, 3, 0);
    lobj = lb_80011AC4(gm_804D67A4->lights);
    HSD_GObjObject_80390A70(gobj, (u8) HSD_GObj_804D784A, lobj);
    GObj_SetupGXLink(gobj, HSD_GObj_LObjCallback, 0, 0);
    HSD_LObjAddAnimAll(lobj, (*gm_804D67A4->lights)->anims[0]);
    HSD_LObjReqAnimAll(lobj, 0.0f);
    HSD_LObjAnimAll(lobj);
    HSD_GObj_SetupProc(gobj, fn_801A80CC, 0x17);

    // Camera GObj
    cam_gobj = GObj_Create(0x13, 0x14, 0);
    cobj = lb_80013B14(
        (HSD_CameraDescPerspective*) gm_804D67A4->cameras[0].desc);
    HSD_GObjObject_80390A70(cam_gobj, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMax(cam_gobj, HSD_GObj_803910D8, 8);
    cam_gobj->gxlink_prios = 0x801;
    child = NULL;
    HSD_CObjAddAnim(cobj, gm_804D67A4->cameras[0].anims[0]);
    HSD_CObjReqAnim(cobj, 0.0f);
    HSD_CObjAnim(cobj);
    HSD_GObj_SetupProc(cam_gobj, fn_801A94BC, 0);

    // Background JObj GObj 1
    gobj = GObj_Create(0xE, 0xF, 0);
    gm_804D67C0 = gobj;
    jobj = HSD_JObjLoadJoint(gm_804D67A0->models[0]->joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0xB, 0);
    gm_8016895C(jobj, gm_804D67A0->models[0], 0);
    HSD_JObjReqAnimAll(jobj, 0.0f);
    HSD_JObjAnimAll(jobj);
    HSD_GObj_SetupProc(gobj, fn_801A9498, 0x17);

    // Background JObj GObj 2
    gobj = GObj_Create(0xE, 0xF, 0);
    gm_804D67BC = gobj;
    jobj = HSD_JObjLoadJoint(gm_804D67AC->models[0]->joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0xB, 0);
    gm_8016895C(jobj, gm_804D67A4->models[0], 0);
    HSD_JObjReqAnimAll(jobj, 0.0f);
    HSD_JObjAnimAll(jobj);
    HSD_GObj_SetupProc(gobj, fn_801A851C, 0x17);

    // Character display setup
    gm_801A9094();
    gm_801A4B90();

    // Character JObj GObj 3
    gobj = GObj_Create(0xE, 0xF, 0);
    gm_804D67B8 = gobj;
    jobj = HSD_JObjLoadJoint(gm_804D6798);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0xB, 0);
    gm_801A8114_inline(jobj, gm_801A659C(gm_801BEFB0()));

    // Walk JObj tree to find constraint target (3 levels deep)
    child = HSD_JObjGetChild(GET_JOBJ(gm_804D67BC));
    child = HSD_JObjGetChild(child);
    child = HSD_JObjGetChild(child);

    lb_8000C1C0(jobj, child);
    lb_8000C290(jobj, child);
    HSD_GObj_SetupProc(gobj, fn_801A80F0, 0x17);
}

static u8 gm_804D67C8;
static u8 gm_804D67C9;

char* gm_803DB8B8[] = {
    // clang-format off
    "GmRegendSimpleCaptain.thp",
    "GmRegendSimpleDonkey.thp",
    "GmRegendSimpleFox.thp",
    "GmRegendSimpleGamewatch.thp",
    "GmRegendSimpleKirby.thp",
    "GmRegendSimpleKoopa.thp",
    "GmRegendSimpleLink.thp",
    "GmRegendSimpleLuigi.thp",
    "GmRegendSimpleMario.thp",
    "GmRegendSimpleMarth.thp",
    "GmRegendSimpleMewtwo.thp",
    "GmRegendSimpleNess.thp",
    "GmRegendSimplePeach.thp",
    "GmRegendSimplePikachu.thp",
    "GmRegendSimplePoponana.thp",
    "GmRegendSimplePurin.thp",
    "GmRegendSimpleSamus.thp",
    "GmRegendSimpleYoshi.thp",
    "GmRegendSimpleZeldaseak.thp",
    "GmRegendSimpleFalco.thp",
    "GmRegendSimpleClink.thp",
    "GmRegendSimpleDrmario.thp",
    "GmRegendSimpleRoy.thp",
    "GmRegendSimplePichu.thp",
    "GmRegendSimpleGanon.thp",
    // clang-format on
};

char* gm_803DBBF4[] = {
    // clang-format off
    "GmRegendAdventureCaptain.thp",
    "GmRegendAdventureDonkey.thp",
    "GmRegendAdventureFox.thp",
    "GmRegendAdventureGamewatch.thp",
    "GmRegendAdventureKirby.thp",
    "GmRegendAdventureKoopa.thp",
    "GmRegendAdventureLink.thp",
    "GmRegendAdventureLuigi.thp",
    "GmRegendAdventureMario.thp",
    "GmRegendAdventureMarth.thp",
    "GmRegendAdventureMewtwo.thp",
    "GmRegendAdventureNess.thp",
    "GmRegendAdventurePeach.thp",
    "GmRegendAdventurePikachu.thp",
    "GmRegendAdventurePoponana.thp",
    "GmRegendAdventurePurin.thp",
    "GmRegendAdventureSamus.thp",
    "GmRegendAdventureYoshi.thp",
    "GmRegendAdventureZeldaseak.thp",
    "GmRegendAdventureFalco.thp",
    "GmRegendAdventureClink.thp",
    "GmRegendAdventureDrmario.thp",
    "GmRegendAdventureRoy.thp",
    "GmRegendAdventurePichu.thp",
    "GmRegendAdventureGanon.thp",
    // clang-format on
};

char* gm_803DBF10[] = {
    // clang-format off
    "GmRegendAllstarCaptain.thp",
    "GmRegendAllstarDonkey.thp",
    "GmRegendAllstarFox.thp",
    "GmRegendAllstarGamewatch.thp",
    "GmRegendAllstarKirby.thp",
    "GmRegendAllstarKoopa.thp",
    "GmRegendAllstarLink.thp",
    "GmRegendAllstarLuigi.thp",
    "GmRegendAllstarMario.thp",
    "GmRegendAllstarMarth.thp",
    "GmRegendAllstarMewtwo.thp",
    "GmRegendAllstarNess.thp",
    "GmRegendAllstarPeach.thp",
    "GmRegendAllstarPikachu.thp",
    "GmRegendAllstarPoponana.thp",
    "GmRegendAllstarPurin.thp",
    "GmRegendAllstarSamus.thp",
    "GmRegendAllstarYoshi.thp",
    "GmRegendAllstarZeldaseak.thp",
    "GmRegendAllstarFalco.thp",
    "GmRegendAllstarClink.thp",
    "GmRegendAllstarDrmario.thp",
    "GmRegendAllstarRoy.thp",
    "GmRegendAllstarPichu.thp",
    "GmRegendAllstarGanon.thp",
    // clang-format on
};

void gm_801A9B30_OnEnter(UNK_T unused)
{
    struct {
        int x0;
        int x4;
        int x8;
        int xC;
        float x10;
        float x14;
        u8 pad[0x40 - 0x18];
        u32 x40;
    }* temp_r3_3;
    s32 temp_r31;
    HSD_GObj* gobj;
    HSD_GObj* temp_r29;
    const char* thpfile;
    s32 var_r3_3;
    int var_r3;

    gm_804D67C8 = 0x1E;
    gm_804D67C9 = 0;
    temp_r29 = GObj_Create(0x13, 0x14, 0);
    HSD_SObjLib_803A55DC(temp_r29, 0x280, 0x1E0, 8);
    temp_r29->gxlink_prios = 0x800;
    lbAudioAx_80026F2C(0x12);
    lbAudioAx_8002702C(2, 0x10);
    lbAudioAx_80027168();
    lbAudioAx_80027648();
    lbBgFlash_800209F4();
    gobj = GObj_Create(0xE, 0xF, 0);
    HSD_GObjObject_80390A70(gobj, HSD_SObjLib_804D7960, NULL);
    GObj_SetupGXLink(gobj, lbMthp8001F928, 0xB, 0);
    temp_r31 = gm_801BEFB0();
    var_r3 = gm_801A4310();
    if (var_r3 == MJ_DEBUG_GOVER) {
        var_r3 = gm_801BF050();
    }
    switch (var_r3) {
    case MJ_CLASSIC_GOVER:
        thpfile = gm_803DB8B8[temp_r31];
        break;
    case MJ_ADVENTURE_GOVER:
        thpfile = gm_803DBBF4[temp_r31];
        break;
    default:
        thpfile = gm_803DBF10[temp_r31];
        break;
    }
    lbMthp8001FAA0(thpfile, 0x230, 0x1A0);
    temp_r3_3 = lbMthp8001F890(gobj);
    temp_r3_3->x10 = 320.0F;
    temp_r3_3->x14 = 240.0F;
    temp_r3_3->x40 |= 2;
    switch (gm_801A4310()) {
    case MJ_CLASSIC_GOVER:
        var_r3_3 = gm_8017DFF4(1);
        break;
    case MJ_ADVENTURE_GOVER:
        var_r3_3 = gm_8017DFF4(0);
        break;
    default:
        var_r3_3 = gm_8017DFF4(2);
        break;
    }
    if (var_r3_3 == 4) {
        lbAudioAx_800237A8(0x9C45, 0x7F, 0x40);
    } else {
        lbAudioAx_800237A8(0x9C41, 0x7F, 0x40);
    }
}

void gm_801A9D0C_OnFrame(void)
{
    if (gm_804D67C8 != 0) {
        gm_804D67C8--;
    } else if (gm_804D67C9 != 0) {
        gm_804D67C9--;
        if (gm_804D67C9 == 0) {
            if (gm_801A4310() == MJ_DEBUG_GOVER) {
                gm_801A6630(6);
            } else {
                gm_801A6630(1);
            }
        }
    } else {
        if (gm_801A36A0(gm_801BF010()) & 0x1100) {
            lbBgFlash_8002063C(0x3C);
            gm_804D67C9 = 0x3C;
            lbAudioAx_80023694();
            lbAudioAx_80024030(1);
        }
    }
}
