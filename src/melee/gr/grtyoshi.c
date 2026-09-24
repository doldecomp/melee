#include <Runtime/platform.h>

#include <melee/lb/forward.h>

#include <gr/ground.h>
#include <gr/grzakogenerator.h>
#include <gr/inlines.h>
#include <gr/types.h>
#include <dolphin/mtx.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/jobj.h>

/* 223B48 */ static void grTYoshi_OnDemoInit(bool);
/* 223B4C */ static void grTYoshi_OnInit(void);
/* 223BBC */ static void grTYoshi_OnLoad(void);
/* 223BC0 */ static void grTYoshi_OnStart(void);
/* 223BE4 */ static bool grTYoshi_80223BE4(void);
/* 223BEC */ static HSD_GObj* grTYoshi_80223BEC(int gobj_id);
/* 223CD4 */ static void stageGObj0_OnInit(Ground_GObj* gobj);
/* 223D00 */ static bool grTYoshi_80223D00(Ground_GObj*);
/* 223D08 */ static void grTYoshi_80223D08(Ground_GObj*);
/* 223D0C */ static void grTYoshi_80223D0C(Ground_GObj*);
/* 223D10 */ static void stageGObj2_OnInit(Ground_GObj* gobj);
/* 223D60 */ static bool grTYoshi_80223D60(Ground_GObj*);
/* 223D68 */ static void stageGObj2_GObjProc(Ground_GObj* gobj);
/* 223D9C */ static void grTYoshi_80223D9C(Ground_GObj*);
/* 223DA0 */ static void stageGObj1_OnInit(Ground_GObj* gobj);
/* 223DF0 */ static bool grTYoshi_80223DF0(Ground_GObj*);
/* 223DF8 */ static void stageGObj1_GObjProc(Ground_GObj*);
/* 223E18 */ static void grTYoshi_80223E18(Ground_GObj*);
/* 223E1C */ static DynamicsDesc* grTYoshi_OnTouchLine(enum_t);
/* 223E24 */ static bool grTYoshi_OnCheckShadowRender(Vec3*, int, HSD_JObj*);

static StageCallbacks grTYs_StageCallbacks[] = {
    {
        stageGObj0_OnInit,
        grTYoshi_80223D00,
        grTYoshi_80223D08,
        grTYoshi_80223D0C,
        0,
    },
    {
        stageGObj1_OnInit,
        grTYoshi_80223DF0,
        stageGObj1_GObjProc,
        grTYoshi_80223E18,
        0,
    },
    {
        stageGObj2_OnInit,
        grTYoshi_80223D60,
        stageGObj2_GObjProc,
        grTYoshi_80223D9C,
        (1 << 30) | (1 << 31),
    },
    { 0 },
};

StageData grTYs_StageData = {
    Gr_Kind_TYoshi,
    grTYs_StageCallbacks,
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
    Ground_InitTargetStage(grTYoshi_80223BEC);
}

static void grTYoshi_OnLoad(void) {}

static void grTYoshi_OnStart(void)
{
    grZakoGenerator_801CAE04(NULL);
}

static bool grTYoshi_80223BE4(void)
{
    return false;
}

static HSD_GObj* grTYoshi_80223BEC(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grTYs_StageCallbacks[gobj_id];

    gobj = Ground_GetStageGObj(gobj_id);

    if (gobj != NULL) {
        Ground_SetupStageCallbacks(gobj, callbacks);
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 195, gobj_id);
    }

    return gobj;
}

static void stageGObj0_OnInit(Ground_GObj* gobj)
{
    Ground_StartMapAnim(gobj);
}

static bool grTYoshi_80223D00(Ground_GObj* arg0)
{
    return false;
}

static void grTYoshi_80223D08(Ground_GObj* arg0) {}

static void grTYoshi_80223D0C(Ground_GObj* arg0) {}

static void stageGObj2_OnInit(Ground_GObj* gobj)
{
    Ground_InitMapCollAndAnim(gobj);
}

static bool grTYoshi_80223D60(Ground_GObj* arg0)
{
    return false;
}

static void stageGObj2_GObjProc(Ground_GObj* gobj)
{
    Ground_UpdateWindAndMapColl(gobj);
}

static void grTYoshi_80223D9C(Ground_GObj* arg0) {}

static void stageGObj1_OnInit(Ground_GObj* gobj)
{
    Ground_InitMapCollAndAnim(gobj);
}

static bool grTYoshi_80223DF0(Ground_GObj* arg0)
{
    return false;
}

static void stageGObj1_GObjProc(Ground_GObj* arg0)
{
    Ground_UpdateMapColl(arg0);
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
