#include "gm_1A7A.h"

#include "gm_unsplit.h"

#include "gm/gm_1BA8.h"
#include "gm/gmregtyfall.h"
#include "lb/lb_00B0.h"
#include "lb/lbspdisplay.h"
#include "mn/mnmain.h"
#include "sc/types.h"
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
    HSD_CObj* cobj;
    HSD_LObj* lobj;
    HSD_GObj* gobj;
    HSD_GObj* cam_gobj;
    HSD_JObj* jobj;
    HSD_JObj* child;
    HSD_JObj* target;
    s32 char_idx;
    f32 val;
    f32 scale;
    PAD_STACK(0x30);

    // Light GObj
    gobj = GObj_Create(0xB, 3, 0);
    lobj = lb_80011AC4(gm_804D67A8->lights);
    HSD_GObjObject_80390A70(gobj, (u8) HSD_GObj_804D784A, lobj);
    GObj_SetupGXLink(gobj, HSD_GObj_LObjCallback, 0, 0);

    // Camera GObj
    cam_gobj = GObj_Create(0x13, 0x14, 0);
    cobj =
        lb_80013B14((HSD_CameraDescPerspective*) gm_804D67A8->cameras[0].desc);
    HSD_GObjObject_80390A70(cam_gobj, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMax(cam_gobj, HSD_GObj_803910D8, 8);
    cam_gobj->gxlink_prios = 0x801;
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
    child = jobj == NULL ? NULL : jobj->child;

    val = -Toy_803060BC(char_idx, 0);
    HSD_JObjSetTranslateXWithMtxDirty(child, val);
    val = -Toy_803060BC(char_idx, 1);
    HSD_JObjSetTranslateYWithMtxDirty(child, val);
    val = -Toy_803060BC(char_idx, 2);
    HSD_JObjSetTranslateZWithMtxDirty(child, val);

    val = -(0.017453292f * Toy_803060BC(char_idx, 5));
    HSD_JObjSetRotationYWithMtxDirty(child, val);

    scale = 1.0f / Toy_803060BC(char_idx, 3);
    val = Toy_803060BC(char_idx, 4);
    scale = val * scale;
    HSD_JObjSetScaleXWithMtxDirty(child, scale);
    HSD_JObjSetScaleYWithMtxDirty(child, scale);
    HSD_JObjSetScaleZWithMtxDirty(child, scale);

    HSD_GObj_SetupProc(gobj, fn_801A7A68, 0x17);

    // Walk JObj tree to find constraint target
    target = HSD_JObjGetChild(GET_JOBJ(gm_804D67B0));
    target = HSD_JObjGetChild(target);
    target = HSD_JObjGetChild(target);
    target = HSD_JObjGetChild(target);
    target = HSD_JObjGetChild(target);
    if (target == NULL) {
        target = NULL;
    } else {
        target = target->next;
    }

    lb_8000C1C0((HSD_JObj*) gobj->hsd_obj, target);
    lb_8000C290((HSD_JObj*) gobj->hsd_obj, target);
}
