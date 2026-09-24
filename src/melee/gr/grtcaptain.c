#include <gr/grtcaptain.h>

#include <Runtime/platform.h>

#include <melee/lb/forward.h>
#include <sysdolphin/baselib/forward.h>

#include <gr/ground.h>
#include <gr/grzakogenerator.h>
#include <gr/inlines.h>
#include <gr/types.h>
#include <dolphin/mtx.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjproc.h>

static void grTCaptain_OnDemoInit(int);
static void grTCaptain_OnInit(void);
static void grTCaptain_OnLoad(void);
static void grTCaptain_OnStart(void);
static bool grTCaptain_8021FCFC(void);
static HSD_GObj* grTCaptain_8021FD04(int gobj_id);
static void stageGObj0_OnInit(Ground_GObj* gobj);
static bool grTCaptain_8021FE18(Ground_GObj*);
static void grTCaptain_8021FE20(Ground_GObj*);
static void grTCaptain_8021FE24(Ground_GObj*);
static void stageGObj2_OnInit(Ground_GObj* gobj);
static bool grTCaptain_8021FE78(Ground_GObj*);
static void stageGObj2_GObjProc(Ground_GObj* gobj);
static void grTCaptain_8021FEB4(Ground_GObj*);
static void stageGObj1_OnInit(Ground_GObj* gobj);
static bool grTCaptain_8021FF08(Ground_GObj*);
static void stageGObj1_GObjProc(Ground_GObj*);
static void grTCaptain_8021FF30(Ground_GObj*);
static DynamicsDesc* grTCaptain_OnTouchLine(enum_t);
static bool grTCaptain_OnCheckShadowRender(Vec3*, int, HSD_JObj*);

static StageCallbacks grTCa_StageCallbacks[] = {
    {
        stageGObj0_OnInit,
        grTCaptain_8021FE18,
        grTCaptain_8021FE20,
        grTCaptain_8021FE24,
        0,
    },
    {
        stageGObj1_OnInit,
        grTCaptain_8021FF08,
        stageGObj1_GObjProc,
        grTCaptain_8021FF30,
        0,
    },
    {
        stageGObj2_OnInit,
        grTCaptain_8021FE78,
        stageGObj2_GObjProc,
        grTCaptain_8021FEB4,
        (1 << 30) | (1 << 31),
    },
    { 0 },
};

StageData grTCa_StageData = {
    Gr_Kind_TCaptain,
    grTCa_StageCallbacks,
    "/GrTCa.dat",
    grTCaptain_OnInit,
    grTCaptain_OnDemoInit,
    grTCaptain_OnLoad,
    grTCaptain_OnStart,
    grTCaptain_8021FCFC,
    grTCaptain_OnTouchLine,
    grTCaptain_OnCheckShadowRender,
    (1 << 0),
    NULL,
    0,
};

static void grTCaptain_OnDemoInit(int unused) {}

static void grTCaptain_OnInit(void)
{
    Ground_InitTargetStage(grTCaptain_8021FD04);
}
static void grTCaptain_OnLoad(void) {}

static void grTCaptain_OnStart(void)
{
    grZakoGenerator_801CAE04(NULL);
}

static bool grTCaptain_8021FCFC(void)
{
    return false;
}

static HSD_GObj* grTCaptain_8021FD04(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grTCa_StageCallbacks[gobj_id];

    gobj = Ground_GetStageGObj(gobj_id);

    if (gobj != NULL) {
        Ground_SetupStageCallbacks(gobj, callbacks);
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 215, gobj_id);
    }

    return gobj;
}

static void stageGObj0_OnInit(Ground_GObj* gobj)
{
    Ground_StartMapAnim(gobj);
}

static bool grTCaptain_8021FE18(Ground_GObj* arg0)
{
    return false;
}

static void grTCaptain_8021FE20(Ground_GObj* arg0) {}

static void grTCaptain_8021FE24(Ground_GObj* arg0) {}

static void stageGObj2_OnInit(Ground_GObj* gobj)
{
    Ground_InitMapCollAndAnim(gobj);
}

static bool grTCaptain_8021FE78(Ground_GObj* arg0)
{
    return false;
}

static void stageGObj2_GObjProc(Ground_GObj* gobj)
{
    Ground_UpdateWindAndMapColl(gobj);
}

static void grTCaptain_8021FEB4(Ground_GObj* arg0) {}

static void stageGObj1_OnInit(Ground_GObj* gobj)
{
    Ground_InitMapCollAndAnim(gobj);
}

static bool grTCaptain_8021FF08(Ground_GObj* arg0)
{
    return false;
}

static void stageGObj1_GObjProc(Ground_GObj* arg0)
{
    Ground_UpdateMapColl(arg0);
}

static void grTCaptain_8021FF30(Ground_GObj* argo) {}

static DynamicsDesc* grTCaptain_OnTouchLine(enum_t arg0)
{
    return NULL;
}

static bool grTCaptain_OnCheckShadowRender(Vec3* arg0, int arg1,
                                           HSD_JObj* arg2)
{
    return true;
}
