#include <gr/grtzelda.h>

#include <Runtime/platform.h>

#include <melee/lb/forward.h>
#include <sysdolphin/baselib/forward.h>

#include <gr/ground.h>
#include <gr/grzakogenerator.h>
#include <gr/inlines.h>
#include <gr/types.h>
#include <dolphin/mtx.h>
#include <sysdolphin/baselib/gobjproc.h>

void grTZelda_OnDemoInit(bool);   /* static */
void grTZelda_OnInit(void);       /* static */
void grTZelda_OnLoad(void);       /* static */
void grTZelda_OnStart(void);      /* static */
bool grTZelda_80223EC8(void);     /* static */
HSD_GObj* grTZelda_80223ED0(int); /* static */
static void stageGObj0_OnInit(Ground_GObj*);
bool grTZelda_80223FE4(Ground_GObj*); /* static */
void grTZelda_80223FEC(Ground_GObj*); /* static */
void grTZelda_80223FF0(Ground_GObj*); /* static */
static void stageGObj2_OnInit(Ground_GObj*);
bool grTZelda_80224044(Ground_GObj*); /* static */
static void stageGObj2_GObjProc(Ground_GObj*);
void grTZelda_80224080(Ground_GObj*); /* static */
static void stageGObj1_OnInit(Ground_GObj*);
bool grTZelda_802240D4(Ground_GObj*); /* static */
static void stageGObj1_GObjProc(Ground_GObj*);
void grTZelda_802240FC(Ground_GObj*);                     /* static */
DynamicsDesc* grTZelda_OnTouchLine(enum_t);               /* static */
bool grTZelda_OnCheckShadowRender(Vec3*, int, HSD_JObj*); /* static */

static StageCallbacks grTZd_StageCallbacks[4] = {
    { stageGObj0_OnInit, grTZelda_80223FE4, grTZelda_80223FEC,
      grTZelda_80223FF0, 0 },
    { stageGObj1_OnInit, grTZelda_802240D4, stageGObj1_GObjProc,
      grTZelda_802240FC, 0 },
    { stageGObj2_OnInit, grTZelda_80224044, stageGObj2_GObjProc,
      grTZelda_80224080, (1 << 31) | (1 << 30) },
    { NULL, NULL, NULL, NULL, 0 }
};

StageData grTZd_StageData = {
    Gr_Kind_TZelda,
    grTZd_StageCallbacks,
    "/GrTZd.dat",
    grTZelda_OnInit,
    grTZelda_OnDemoInit,
    grTZelda_OnLoad,
    grTZelda_OnStart,
    grTZelda_80223EC8,
    grTZelda_OnTouchLine,
    grTZelda_OnCheckShadowRender,
    1,
};

void grTZelda_OnDemoInit(int unused) {}

void grTZelda_OnInit(void)
{
    Ground_InitTargetStage(grTZelda_80223ED0);
}

void grTZelda_OnLoad(void) {}

void grTZelda_OnStart(void)
{
    grZakoGenerator_801CAE04(NULL);
}

bool grTZelda_80223EC8(void)
{
    return false;
}

HSD_GObj* grTZelda_80223ED0(int arg0)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grTZd_StageCallbacks[arg0];

    gobj = Ground_GetStageGObj(arg0);

    if (gobj != NULL) {
        Ground_SetupStageCallbacks(gobj, callbacks);
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 0xC3, arg0);
    }

    return gobj;
}

static void stageGObj0_OnInit(Ground_GObj* gobj)
{
    Ground_StartMapAnim(gobj);
}

bool grTZelda_80223FE4(Ground_GObj* gobj)
{
    return false;
}

void grTZelda_80223FEC(Ground_GObj* gobj) {}

void grTZelda_80223FF0(Ground_GObj* gobj) {}

static void stageGObj2_OnInit(Ground_GObj* gobj)
{
    Ground_InitMapCollAndAnim(gobj);
}

bool grTZelda_80224044(Ground_GObj* gobj)
{
    return false;
}

static void stageGObj2_GObjProc(Ground_GObj* gobj)
{
    Ground_UpdateWindAndMapColl(gobj);
}

void grTZelda_80224080(Ground_GObj* gobj) {}

static void stageGObj1_OnInit(Ground_GObj* gobj)
{
    Ground_InitMapCollAndAnim(gobj);
}

bool grTZelda_802240D4(Ground_GObj* gobj)
{
    return false;
}

static void stageGObj1_GObjProc(Ground_GObj* gobj)
{
    Ground_UpdateMapColl(gobj);
}

void grTZelda_802240FC(Ground_GObj* gobj) {}

DynamicsDesc* grTZelda_OnTouchLine(enum_t arg0)
{
    return NULL;
}

bool grTZelda_OnCheckShadowRender(Vec3* arg0, int arg1, HSD_JObj* arg2)
{
    return true;
}

/* Warning: struct HSD_Spline is not defined (only forward-declared) */
/* Warning: struct _HSD_Rvalue is not defined (only forward-declared) */
/* Warning: struct _HSD_RObjDesc is not defined (only forward-declared) */
/* Warning: struct _HSD_ExpDesc is not defined (only forward-declared) */
/* Warning: struct _HSD_ByteCodeExpDesc is not defined (only forward-declared)
 */
/* Warning: struct _HSD_IKHintDesc is not defined (only forward-declared) */
