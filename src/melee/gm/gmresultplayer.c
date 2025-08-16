#include "gmresultplayer.h"
#include "baselib/forward.h"
#include "baselib/gobj.h"
#include "cm/camera.h"

#include <melee/gm/types.h>
#include <melee/lb/lb_00B0.h>

/* 46E38C */ static int lbl_8046E38C[4];

void gm_80177724(struct ResultsMatchInfo* arg0)
{
    memzero(arg0, sizeof(*arg0));
}

/// #fn_80177748

/// #fn_80177920

/// #fn_80177B7C

/// #fn_80177DD0

/// #fn_80178050

/// #fn_801785B0

/// #fn_80178BB4

/// #fn_801791E4

/// #fn_80179350

/// #fn_801795D4

/// #fn_801796F0

/// #fn_80179854

/// #fn_80179990

void fn_80179D3C(HSD_GObj* gobj, int arg1)
{
    fn_80179990(gobj, arg1, 0);
}

void fn_80179D60(HSD_GObj* gobj, int arg1)
{
    fn_80179990(gobj, arg1, 1);
}

void fn_80179D84(HSD_GObj* gobj, int arg1)
{
    fn_80179990(gobj, arg1, 2);
}

void fn_80179DA8(HSD_GObj* gobj, int arg1)
{
    fn_80179990(gobj, arg1, 3);
}

void fn_80179DCC(HSD_GObj* gobj, int arg1)
{
    HSD_CObj* cobj = GET_COBJ(gobj);
    if (HSD_CObjSetCurrent(cobj)) {
        Camera_800313E0(gobj, 0);
        gobj->gxlink_prios = 0x80;
        HSD_GObj_80390ED0(gobj, 7U);
        HSD_CObjEndCurrent();
    }
}

void fn_80179E34(HSD_GObj* gobj, int arg1)
{
    HSD_CObj* cobj = GET_COBJ(gobj);
    if (HSD_CObjSetCurrent(cobj)) {
        Camera_800313E0(gobj, 0);
        gobj->gxlink_prios = 0x80;
        HSD_GObj_80390ED0(gobj, 7U);
        HSD_CObjEndCurrent();
    }
}

void fn_80179E9C(HSD_GObj* gobj, int arg1)
{
    HSD_CObj* cobj = GET_COBJ(gobj);
    if (HSD_CObjSetCurrent(cobj)) {
        Camera_800313E0(gobj, 0);
        gobj->gxlink_prios = 0x80;
        HSD_GObj_80390ED0(gobj, 7U);
        HSD_CObjEndCurrent();
    }
}

void fn_80179F04(HSD_GObj* gobj, int arg1)
{
    HSD_CObj* cobj = GET_COBJ(gobj);
    if (HSD_CObjSetCurrent(cobj)) {
        Camera_800313E0(gobj, 0);
        gobj->gxlink_prios = 0x80;
        HSD_GObj_80390ED0(gobj, 7U);
        HSD_CObjEndCurrent();
    }
}

void fn_80179F6C(int idx, int value)
{
    lbl_8046E38C[idx] = value;
}

/// #fn_80179F84

/// #fn_8017A004

/// #fn_8017A078

/// #fn_8017A318

/// #fn_8017A67C

/// #fn_8017A9B4

/// #fn_8017AA78
