#include "gr/grfigure1.h"

#include <platform.h>

#include "gr/granime.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "gr/types.h"

#include "lb/forward.h"

#include "lb/lbspdisplay.h"

#include <dolphin/mtx.h>
#include <baselib/gobj.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>

/* 20DFDC */ static void grFigure1_OnDemoInit(int);
/* 20DFE0 */ static void grFigure1_OnInit(void);
/* 20E050 */ static void grFigure1_OnLoad(void);
/* 20E054 */ static void grFigure1_OnStart(void);
/* 20E078 */ static bool grFigure1_8020E078(void);
/* 20E080 */ static HSD_GObj* grFigure1_8020E080(int);
/* 20E168 */ static void grFigure1_8020E168(Ground_GObj*);
/* 20E194 */ static bool grFigure1_8020E194(Ground_GObj*);
/* 20E19C */ static void grFigure1_8020E19C(Ground_GObj*);
/* 20E1A0 */ static void grFigure1_8020E1A0(Ground_GObj*);
/* 20E1A4 */ static void grFigure1_8020E1A4(Ground_GObj*);
/* 20E1D0 */ static bool grFigure1_8020E1D0(Ground_GObj*);
/* 20E1D8 */ static void grFigure1_8020E1D8(Ground_GObj*);
/* 20E1FC */ static void grFigure1_8020E1FC(Ground_GObj*);
/* 20E200 */ static void grFigure1_8020E200(Ground_GObj*);
/* 20E250 */ static bool grFigure1_8020E250(Ground_GObj*);
/* 20E258 */ static void grFigure1_8020E258(Ground_GObj*);
/* 20E25C */ static void grFigure1_8020E25C(Ground_GObj*);
/* 20E260 */ static DynamicsDesc* grFigure1_OnTouchLine(enum_t);
/* 20E268 */ static bool grFigure1_OnCheckShadowRender(Vec3*, int, HSD_JObj*);

static StageCallbacks grEF1_StageCallbacks[3] = {
    { grFigure1_8020E168, grFigure1_8020E194, grFigure1_8020E19C,
      grFigure1_8020E1A0, 0 },
    { grFigure1_8020E1A4, grFigure1_8020E1D0, grFigure1_8020E1D8,
      grFigure1_8020E1FC, (1 << 30) | (1 << 31) },
    { grFigure1_8020E200, grFigure1_8020E250, grFigure1_8020E258,
      grFigure1_8020E25C, 0 }
};

StageData grEF1_803E62C0 = {
    FIGURE1,
    grEF1_StageCallbacks,
    "/GrEF1.dat",
    grFigure1_OnInit,
    grFigure1_OnDemoInit,
    grFigure1_OnLoad,
    grFigure1_OnStart,
    grFigure1_8020E078,
    grFigure1_OnTouchLine,
    grFigure1_OnCheckShadowRender,
    (1 << 0),
    NULL,
    0,
};

static void* yakumono_param;

static void grFigure1_OnDemoInit(int unused) {}

static void grFigure1_OnInit(void)
{
    yakumono_param = Ground_GetYakumonoParam();
    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = true;
    grFigure1_8020E080(0);
    grFigure1_8020E080(2);
    grFigure1_8020E080(1);
    Ground_801C39C0();
    Ground_801C3BB4();
}

static void grFigure1_OnLoad(void) {}

static void grFigure1_OnStart(void)
{
    grZakoGenerator_801CAE04(NULL);
}

static bool grFigure1_8020E078(void)
{
    return false;
}

static HSD_GObj* grFigure1_8020E080(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grEF1_StageCallbacks[gobj_id];

    gobj = Ground_GetStageGObj(gobj_id);

    if (gobj != NULL) {
        Ground_SetupStageCallbacks(gobj, callbacks);
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 194, gobj_id);
    }

    return gobj;
}

static void grFigure1_8020E168(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

static bool grFigure1_8020E194(Ground_GObj* arg0)
{
    return false;
}

static void grFigure1_8020E19C(Ground_GObj* gobj) {}

static void grFigure1_8020E1A0(Ground_GObj* arg0) {}

static void grFigure1_8020E1A4(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);

    Ground_801C2ED0(jobj, gp->map_id);
}

static bool grFigure1_8020E1D0(Ground_GObj* arg0)
{
    return false;
}

static void grFigure1_8020E1D8(Ground_GObj* gobj)
{
    Ground_801C2FE0(gobj);
    lb_800115F4();
}

static void grFigure1_8020E1FC(Ground_GObj* arg0) {}

static void grFigure1_8020E200(Ground_GObj* gobj)
{
    Ground_JObjInline1(gobj);
}

static bool grFigure1_8020E250(Ground_GObj* arg0)
{
    return false;
}

static void grFigure1_8020E258(Ground_GObj* gobj) {}

static void grFigure1_8020E25C(Ground_GObj* arg0) {}

static DynamicsDesc* grFigure1_OnTouchLine(enum_t arg0)
{
    return NULL;
}

static bool grFigure1_OnCheckShadowRender(Vec3* v, int n, HSD_JObj* o)
{
    return true;
}

void grFigure1_8020E270(bool n) {}
