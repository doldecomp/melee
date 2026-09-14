#include <Runtime/platform.h>

#include <melee/lb/forward.h>
#include <sysdolphin/baselib/forward.h>

#include "ground.h"
#include "grzakogenerator.h"
#include "inlines.h"
#include "types.h"
#include <dolphin/mtx.h>
#include <sysdolphin/baselib/gobjproc.h>

/* 223864 */ static void grTSeak_OnDemoInit(bool);
/* 223868 */ static void grTSeak_OnInit(void);
/* 2238D8 */ static void grTseak_OnLoad(void);
/* 2238DC */ static void grTseak_OnStart(void);
/* 223900 */ static bool grTSeak_80223900(void);
/* 223908 */ static HSD_GObj* grTSeak_80223908(int);
/* 2239F0 */ static void stageGObj0_OnInit(Ground_GObj*);
/* 223A1C */ static bool grTSeak_80223A1C(Ground_GObj*);
/* 223A24 */ static void grTSeak_80223A24(Ground_GObj*);
/* 223A28 */ static void grTSeak_80223A28(Ground_GObj*);
/* 223A2C */ static void stageGObj2_OnInit(Ground_GObj*);
/* 223A7C */ static bool grTSeak_80223A7C(Ground_GObj*);
/* 223A84 */ static void stageGObj2_GObjProc(Ground_GObj*);
/* 223AB8 */ static void grTSeak_80223AB8(Ground_GObj*);
/* 223ABC */ static void stageGObj1_OnInit(Ground_GObj*);
/* 223B0C */ static bool grTSeak_80223B0C(Ground_GObj*);
/* 223B14 */ static void stageGObj1_GObjProc(Ground_GObj*);
/* 223B34 */ static void grTSeak_80223B34(Ground_GObj*);
/* 223B38 */ static DynamicsDesc* grTSeak_OnTouchLine(enum_t);
/* 223B40 */ static bool grTSeak_OnCheckShadowRender(Vec3*, int, HSD_JObj*);

static StageCallbacks grTSk_StageCallbacks[] = {
    {
        stageGObj0_OnInit,
        grTSeak_80223A1C,
        grTSeak_80223A24,
        grTSeak_80223A28,
        0,
    },
    {
        stageGObj1_OnInit,
        grTSeak_80223B0C,
        stageGObj1_GObjProc,
        grTSeak_80223B34,
        0,
    },
    {
        stageGObj2_OnInit,
        grTSeak_80223A7C,
        stageGObj2_GObjProc,
        grTSeak_80223AB8,
        (1 << 31) | (1 << 30),
    },
    { 0 },
};

StageData grTSk_StageData = {
    Gr_Kind_TSeak,
    grTSk_StageCallbacks,
    "/GrTSk.dat",
    grTSeak_OnInit,
    grTSeak_OnDemoInit,
    grTseak_OnLoad,
    grTseak_OnStart,
    grTSeak_80223900,
    grTSeak_OnTouchLine,
    grTSeak_OnCheckShadowRender,
    1,
};

void grTSeak_OnDemoInit(bool unk0) {}

void grTSeak_OnInit(void)
{
    Ground_InitTargetStage(grTSeak_80223908);
}

void grTseak_OnLoad(void) {}

void grTseak_OnStart(void)
{
    grZakoGenerator_801CAE04(NULL);
}

bool grTSeak_80223900(void)
{
    return false;
}

HSD_GObj* grTSeak_80223908(int arg0)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grTSk_StageCallbacks[arg0];

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

bool grTSeak_80223A1C(Ground_GObj* gobj)
{
    return false;
}

void grTSeak_80223A24(Ground_GObj* gobj) {}

void grTSeak_80223A28(Ground_GObj* gobj) {}

static void stageGObj2_OnInit(Ground_GObj* gobj)
{
    Ground_InitMapCollAndAnim(gobj);
}

bool grTSeak_80223A7C(Ground_GObj* gobj)
{
    return false;
}

static void stageGObj2_GObjProc(Ground_GObj* gobj)
{
    Ground_UpdateWindAndMapColl(gobj);
}

void grTSeak_80223AB8(Ground_GObj* gobj) {}

static void stageGObj1_OnInit(Ground_GObj* gobj)
{
    Ground_InitMapCollAndAnim(gobj);
}

bool grTSeak_80223B0C(Ground_GObj* gobj)
{
    return false;
}

static void stageGObj1_GObjProc(Ground_GObj* gobj)
{
    Ground_UpdateMapColl(gobj);
}

void grTSeak_80223B34(Ground_GObj* gobj) {}

DynamicsDesc* grTSeak_OnTouchLine(enum_t arg0)
{
    return NULL;
}

bool grTSeak_OnCheckShadowRender(Vec3* arg0, int arg1, HSD_JObj* arg2)
{
    return true;
}
