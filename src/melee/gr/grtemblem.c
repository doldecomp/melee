#include <platform.h>

#include "lb/forward.h"
#include <dolphin/mtx/forward.h>
#include <baselib/forward.h>

#include "gr/grtemblem.h"

#include "gr/granime.h"
#include "gr/grdisplay.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "gr/types.h"
#include "lb/lb_00F9.h"

#include <dolphin/os/OSError.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>

static void grTRoy_802243F4(int);
static void grTRoy_802243F8(void);
static void grTRoy_80224468(void);
static void grTRoy_8022446C(void);
static bool grTRoy_80224490(void);
static HSD_GObj* grTRoy_80224498(s32 gobj_id);
static void grTRoy_80224580(HSD_GObj* gobj);
static bool grTRoy_802245AC(HSD_GObj*);
static void grTRoy_802245B4(HSD_GObj*);
static void grTRoy_802245B8(HSD_GObj*);
static void grTRoy_802245BC(HSD_GObj* gobj);
static bool grTRoy_8022460C(HSD_GObj*);
static void grTRoy_80224614(HSD_GObj* gobj);
static void grTRoy_80224648(HSD_GObj*);
static void grTRoy_8022464C(HSD_GObj* gobj);
static bool grTRoy_8022469C(HSD_GObj*);
static void grTRoy_802246A4(HSD_GObj*);
static void grTRoy_802246C4(HSD_GObj*);
static DynamicsDesc* grTRoy_802246C8(enum_t);
static bool grTRoy_802246D0(Vec3*, int, HSD_JObj*);

StageCallbacks grTFe_803E97C0[4] = {
    {
        grTRoy_80224580,
        grTRoy_802245AC,
        grTRoy_802245B4,
        grTRoy_802245B8,
        0,
    },
    {
        grTRoy_8022464C,
        grTRoy_8022469C,
        grTRoy_802246A4,
        grTRoy_802246C4,
        0,
    },
    {
        grTRoy_802245BC,
        grTRoy_8022460C,
        grTRoy_80224614,
        grTRoy_80224648,
        (1 << 30) | (1 << 31),
    },
};

StageData grTFe_803E981C = {
    64,
    grTFe_803E97C0,
    "/GrTFe.dat",
    grTRoy_802243F8,
    grTRoy_802243F4,
    grTRoy_80224468,
    grTRoy_8022446C,
    grTRoy_80224490,
    grTRoy_802246C8,
    grTRoy_802246D0,
    1,
};

static void grTRoy_802243F4(int arg0) {}

static void grTRoy_802243F8(void)
{
    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 1;
    grTRoy_80224498(0);
    grTRoy_80224498(1);
    grTRoy_80224498(2);
    Ground_801C39C0();
    Ground_801C3BB4();
    Ground_801C4210();
    Ground_801C42AC();
}

static void grTRoy_80224468(void) {}

static void grTRoy_8022446C(void)
{
    grZakoGenerator_801CAE04(0);
}

static bool grTRoy_80224490(void)
{
    return false;
}

static HSD_GObj* grTRoy_80224498(s32 gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* cb;
    Ground* gp;

    cb = &grTFe_803E97C0[gobj_id];
    gobj = Ground_801C14D0(gobj_id);

    if (gobj != NULL) {
        gp = gobj->user_data;
        gp->x8_callback = 0;
        gp->xC_callback = 0;
        GObj_SetupGXLink(gobj, &grDisplay_801C5DB0, 3, 0);
        if (cb->callback3 != NULL) {
            gp->x1C_callback = cb->callback3;
        }
        if (cb->callback0 != NULL) {
            cb->callback0(gobj);
        }
        if (cb->callback2 != NULL) {
            HSD_GObjProc_8038FD54(gobj, cb->callback2, 4);
        }
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grtemblem.c", 0xC3,
                 gobj_id);
    }
    return gobj;
}

static void grTRoy_80224580(HSD_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    grAnime_801C8138(gobj, gp->map_id, 0);
}

static bool grTRoy_802245AC(HSD_GObj* gobj)
{
    return false;
}

static void grTRoy_802245B4(HSD_GObj* gobj) {}

static void grTRoy_802245B8(HSD_GObj* gobj) {}

static void grTRoy_802245BC(HSD_GObj* gobj)
{
    u8 _[8];
    Ground* gp = GET_GROUND(gobj);
    Ground_801C2ED0(gobj->hsd_obj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, false);
}

static bool grTRoy_8022460C(HSD_GObj* gobj)
{
    return false;
}

static void grTRoy_80224614(HSD_GObj* gobj)
{
    lb_800115F4();
    Ground_801C2FE0(gobj);
}

static void grTRoy_80224648(HSD_GObj* gobj) {}

static void grTRoy_8022464C(HSD_GObj* gobj)
{
    u8 _[8];
    Ground* gp = GET_GROUND(gobj);
    Ground_801C2ED0(gobj->hsd_obj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, false);
}

static bool grTRoy_8022469C(HSD_GObj* gobj)
{
    return false;
}

static void grTRoy_802246A4(HSD_GObj* gobj)
{
    Ground_801C2FE0(gobj);
}

static void grTRoy_802246C4(HSD_GObj* gobj) {}

static DynamicsDesc* grTRoy_802246C8(enum_t arg0)
{
    return NULL;
}

static bool grTRoy_802246D0(Vec3* vec, int arg1, HSD_JObj* jobj)
{
    return true;
}
