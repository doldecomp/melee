#include "hsd_3982.h"

#include <sysdolphin/baselib/cobj.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/hsd_3924.h>
#include <sysdolphin/baselib/hsd_392A.h>
#include <sysdolphin/baselib/wobj.h>

void fn_803982E4(HSD_GObj* gobj, int unused)
{
    HSD_CObjSetCurrent(gobj->hsd_obj);
    fn_80392934();
    hsd_8039254C();
}

static HSD_WObjDesc lbl_8040BF48 = { NULL, { 0.0f, 0.0f, 1.0f }, NULL };
static HSD_WObjDesc lbl_8040BF5C = { NULL, { 0.0f, 0.0f, 0.0f }, NULL };

/// @todo Ortho camera; typed as the frustum arm of the HSD_CObjDesc union.
static HSD_CameraDescFrustum lbl_8040BF70 = {
    NULL,
    0,
    3,
    { 0, 640, 0, 480 },
    { 0, 640, 0, 480 },
    &lbl_8040BF48,
    &lbl_8040BF5C,
    0.0f,
    NULL,
    0.0f,
    32768.0f,
    -445.0f,
    35.0f,
    -20.0f,
    620.0f,
};

HSD_GObj* hsd_80398310(u16 class_id, u8 p_link, u8 obj_kind, u32 gx_link)
{
    HSD_GObj* gobj;
    HSD_CObj* cobj;

    gobj = GObj_Create(class_id, p_link, obj_kind);
    if (gobj == NULL) {
        return NULL;
    }
    cobj = HSD_CObjLoadDesc((HSD_CObjDesc*) &lbl_8040BF70);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_CameraKind, cobj);
    GObj_SetupGXLinkMax(gobj, fn_803982E4, gx_link);
    hsd_80392528((Event) fn_80392A3C);
    fn_80392A08(4, 1, 0);
    return gobj;
}
