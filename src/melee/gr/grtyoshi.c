#include <platform.h>

#include "gr/granime.h"
#include "gr/grdisplay.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "gr/types.h"

#include "lb/forward.h"

#include "lb/lb_00F9.h"

#include <dolphin/mtx.h>
#include <dolphin/os/OSError.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>

/* 223B48 */ static void grTYoshi_OnDemoInit(bool);
/* 223B4C */ static void grTYoshi_OnInit(void);
/* 223BBC */ static void grTYoshi_OnLoad(void);
/* 223BC0 */ static void grTYoshi_OnStart(void);
/* 223BE4 */ static bool grTYoshi_80223BE4(void);
/* 223BEC */ static HSD_GObj* grTYoshi_80223BEC(int gobj_id);
/* 223CD4 */ static void grTYoshi_80223CD4(Ground_GObj* gobj);
/* 223D00 */ static bool grTYoshi_80223D00(Ground_GObj*);
/* 223D08 */ static void grTYoshi_80223D08(Ground_GObj*);
/* 223D0C */ static void grTYoshi_80223D0C(Ground_GObj*);
/* 223D10 */ static void grTYoshi_80223D10(Ground_GObj* gobj);
/* 223D60 */ static bool grTYoshi_80223D60(Ground_GObj*);
/* 223D68 */ static void grTYoshi_80223D68(Ground_GObj* gobj);
/* 223D9C */ static void grTYoshi_80223D9C(Ground_GObj*);
/* 223DA0 */ static void grTYoshi_80223DA0(Ground_GObj* gobj);
/* 223DF0 */ static bool grTYoshi_80223DF0(Ground_GObj*);
/* 223DF8 */ static void grTYoshi_80223DF8(Ground_GObj*);
/* 223E18 */ static void grTYoshi_80223E18(Ground_GObj*);
/* 223E1C */ static DynamicsDesc* grTYoshi_OnTouchLine(enum_t);
/* 223E24 */ static bool grTYoshi_OnCheckShadowRender(Vec3*, int, HSD_JObj*);

static StageCallbacks grTYs_803E9578[] = {
    {
        grTYoshi_80223CD4,
        grTYoshi_80223D00,
        grTYoshi_80223D08,
        grTYoshi_80223D0C,
        0,
    },
    {
        grTYoshi_80223DA0,
        grTYoshi_80223DF0,
        grTYoshi_80223DF8,
        grTYoshi_80223E18,
        0,
    },
    {
        grTYoshi_80223D10,
        grTYoshi_80223D60,
        grTYoshi_80223D68,
        grTYoshi_80223D9C,
        (1 << 30) | (1 << 31),
    },
    { 0 },
};

StageData grTYs_803E95D4 = {
    TYOSHI,
    grTYs_803E9578,
    "/GrTYs.dat",
    grTYoshi_OnInit,
    grTYoshi_OnDemoInit,
    grTYoshi_OnLoad,
    grTYoshi_OnStart,
    grTYoshi_80223BE4,
    grTYoshi_OnTouchLine,
    grTYoshi_OnCheckShadowRender,
    (1 << 0),
    NULL,
    0,
};

static void grTYoshi_OnDemoInit(bool arg0) {}

static void grTYoshi_OnInit(void)
{
    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 1;
    grTYoshi_80223BEC(0);
    grTYoshi_80223BEC(1);
    grTYoshi_80223BEC(2);
    Ground_801C39C0();
    Ground_801C3BB4();
    Ground_801C4210();
    Ground_801C42AC();
}

static void grTYoshi_OnLoad(void) {}

static void grTYoshi_OnStart(void)
{
    grZakoGenerator_801CAE04(false);
}

static bool grTYoshi_80223BE4(void)
{
    return false;
}

static HSD_GObj* grTYoshi_80223BEC(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grTYs_803E9578[gobj_id];

    gobj = Ground_801C14D0(gobj_id);
    if (gobj != NULL) {
        Ground* gp = gobj->user_data;
        gp->x8_callback = NULL;
        gp->xC_callback = NULL;
        GObj_SetupGXLink(gobj, grDisplay_801C5DB0, 3, 0);
        if (callbacks->callback3 != NULL) {
            gp->x1C_callback = callbacks->callback3;
        }
        if (callbacks->callback0 != NULL) {
            callbacks->callback0(gobj);
        }
        if (callbacks->callback2 != NULL) {
            HSD_GObj_SetupProc(gobj, callbacks->callback2, 4);
        }
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 195, gobj_id);
    }

    return gobj;
}

static void grTYoshi_80223CD4(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

static bool grTYoshi_80223D00(Ground_GObj* arg0)
{
    return false;
}

static void grTYoshi_80223D08(Ground_GObj* arg0) {}

static void grTYoshi_80223D0C(Ground_GObj* arg0) {}

static void grTYoshi_80223D10(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);

    Ground_801C2ED0(jobj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

static bool grTYoshi_80223D60(Ground_GObj* arg0)
{
    return false;
}

static void grTYoshi_80223D68(Ground_GObj* gobj)
{
    lb_800115F4();
    Ground_801C2FE0(gobj);
}

static void grTYoshi_80223D9C(Ground_GObj* arg0) {}

static void grTYoshi_80223DA0(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);

    Ground_801C2ED0(jobj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

static bool grTYoshi_80223DF0(Ground_GObj* arg0)
{
    return false;
}

static void grTYoshi_80223DF8(Ground_GObj* arg0)
{
    Ground_801C2FE0(arg0);
}

static void grTYoshi_80223E18(Ground_GObj* arg0) {}

static DynamicsDesc* grTYoshi_OnTouchLine(enum_t arg0)
{
    return NULL;
}

static bool grTYoshi_OnCheckShadowRender(Vec3* arg0, int arg1, HSD_JObj* arg2)
{
    return true;
}
