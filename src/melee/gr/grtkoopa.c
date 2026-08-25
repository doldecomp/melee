#include "gr/grtkoopa.h"

#include <platform.h>

#include "gr/granime.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "gr/types.h"

#include "lb/forward.h"

#include "lb/lb_00F9.h"

#include <dolphin/mtx.h>
#include <baselib/gobj.h>
#include <baselib/gobjproc.h>

/* 221648 */ static void grTKoopa_80221648(bool);
/* 22164C */ static void grTKoopa_8022164C(void);
/* 2216BC */ static void grTkoopa_UnkStage0_OnLoad(void);
/* 2216C0 */ static void grTkoopa_UnkStage0_OnStart(void);
/* 2216E4 */ static bool grTKoopa_802216E4(void);
/* 2216EC */ static HSD_GObj* grTKoopa_802216EC(int gobj_id);
/* 2217D4 */ static void grTKoopa_802217D4(Ground_GObj* gobj);
/* 221800 */ static bool grTKoopa_80221800(Ground_GObj*);
/* 221808 */ static void grTKoopa_80221808(Ground_GObj*);
/* 22180C */ static void grTKoopa_8022180C(Ground_GObj*);
/* 221810 */ static void grTKoopa_80221810(Ground_GObj* gobj);
/* 221860 */ static bool grTKoopa_80221860(Ground_GObj*);
/* 221868 */ static void grTKoopa_80221868(Ground_GObj* gobj);
/* 22189C */ static void grTKoopa_8022189C(Ground_GObj*);
/* 2218A0 */ static void grTKoopa_802218A0(Ground_GObj* gobj);
/* 2218F0 */ static bool grTKoopa_802218F0(Ground_GObj*);
/* 2218F8 */ static void grTKoopa_802218F8(Ground_GObj*);
/* 221918 */ static void grTKoopa_80221918(Ground_GObj*);
/* 22191C */ static DynamicsDesc* grTKoopa_8022191C(enum_t);
/* 221924 */ static bool grTKoopa_80221924(Vec3*, int, HSD_JObj*);

static StageCallbacks grTKp_StageCallbacks[] = {
    {
        grTKoopa_802217D4,
        grTKoopa_80221800,
        grTKoopa_80221808,
        grTKoopa_8022180C,
        0,
    },
    {
        grTKoopa_802218A0,
        grTKoopa_802218F0,
        grTKoopa_802218F8,
        grTKoopa_80221918,
        0,
    },
    {
        grTKoopa_80221810,
        grTKoopa_80221860,
        grTKoopa_80221868,
        grTKoopa_8022189C,
        (1 << 30) | (1 << 31),
    },
    { 0 },
};

StageData grTKp_StageData = {
    Gr_Kind_TKoopa,
    grTKp_StageCallbacks,
    "/GrTKp.dat",
    grTKoopa_8022164C,
    grTKoopa_80221648,
    grTkoopa_UnkStage0_OnLoad,
    grTkoopa_UnkStage0_OnStart,
    grTKoopa_802216E4,
    grTKoopa_8022191C,
    grTKoopa_80221924,
    (1 << 0),
    NULL,
    0,
};

static void grTKoopa_80221648(bool arg0) {}

static void grTKoopa_8022164C(void)
{
    Ground_InitTargetStage(grTKoopa_802216EC);
}
static void grTkoopa_UnkStage0_OnLoad(void) {}

static void grTkoopa_UnkStage0_OnStart(void)
{
    grZakoGenerator_801CAE04(NULL);
}

static bool grTKoopa_802216E4(void)
{
    return false;
}

static HSD_GObj* grTKoopa_802216EC(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grTKp_StageCallbacks[gobj_id];

    gobj = Ground_GetStageGObj(gobj_id);

    if (gobj != NULL) {
        Ground_SetupStageCallbacks(gobj, callbacks);
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 195, gobj_id);
    }

    return gobj;
}

static void grTKoopa_802217D4(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    grAnime_801C8138(gobj, gp->map_id, 0);
}

static bool grTKoopa_80221800(Ground_GObj* arg0)
{
    return false;
}

static void grTKoopa_80221808(Ground_GObj* arg0) {}
static void grTKoopa_8022180C(Ground_GObj* arg0) {}

static void grTKoopa_80221810(Ground_GObj* gobj)
{
    Ground_JObjInline1(gobj);
}

static bool grTKoopa_80221860(Ground_GObj* arg0)
{
    return false;
}

static void grTKoopa_80221868(Ground_GObj* gobj)
{
    lb_800115F4();
    Ground_801C2FE0(gobj);
}

static void grTKoopa_8022189C(Ground_GObj* arg0) {}

static void grTKoopa_802218A0(Ground_GObj* gobj)
{
    Ground_JObjInline1(gobj);
}

static bool grTKoopa_802218F0(Ground_GObj* arg0)
{
    return false;
}

static void grTKoopa_802218F8(Ground_GObj* arg0)
{
    Ground_801C2FE0(arg0);
}

static void grTKoopa_80221918(Ground_GObj* arg0) {}

static DynamicsDesc* grTKoopa_8022191C(enum_t arg0)
{
    return NULL;
}

static bool grTKoopa_80221924(Vec3* arg0, int arg1, HSD_JObj* arg2)
{
    return true;
}
