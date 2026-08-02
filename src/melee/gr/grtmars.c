#include "grtmars.h"

#include "granime.h"
#include "ground.h"
#include "grzakogenerator.h"
#include "inlines.h"
#include "types.h"

#include "lb/lb_00F9.h"

#include <dolphin/mtx.h>
#include <baselib/gobj.h>
#include <baselib/gobjproc.h>

/* 221EF4 */ static void grTMars_80221EF4(bool);
/* 221EF8 */ static void grTMars_80221EF8(void);
/* 221F68 */ static void grTmars_UnkStage0_OnLoad(void);
/* 221F6C */ static void grTmars_UnkStage0_OnStart(void);
/* 221F90 */ static bool grTMars_80221F90(void);
/* 221F98 */ static Ground_GObj* setupStageCallbacks(int gobj_id);
/* 222080 */ static void stageGObj0_OnInit(Ground_GObj*);
/* 2220AC */ static bool stageGObj0_Callback1(Ground_GObj*);
/* 2220B4 */ static void stageGObj0_GObjProc(Ground_GObj*);
/* 2220B8 */ static void stageGObj0_Callback3(Ground_GObj*);
/* 2220BC */ static void stageGObj2_OnInit(Ground_GObj*);
/* 22210C */ static bool stageGObj2_Callback1(Ground_GObj*);
/* 222114 */ static void stageGObj2_GObjProc(Ground_GObj*);
/* 222148 */ static void stageGObj2_Callback3(Ground_GObj*);
/* 22214C */ static void stageGObj1_OnInit(Ground_GObj*);
/* 22219C */ static bool stageGObj1_Callback1(Ground_GObj*);
/* 2221A4 */ static void stageGObj1_GObjProc(Ground_GObj*);
/* 2221C4 */ static void stageGObj1_Callback3(Ground_GObj*);
/* 2221C8 */ static DynamicsDesc* grTMars_802221C8(enum_t);
/* 2221D0 */ static bool grTMars_802221D0(Vec3*, int, HSD_JObj*);

static StageCallbacks stage_callbacks[] = {
    {
        stageGObj0_OnInit,
        stageGObj0_Callback1,
        stageGObj0_GObjProc,
        stageGObj0_Callback3,
    },
    {
        stageGObj1_OnInit,
        stageGObj1_Callback1,
        stageGObj1_GObjProc,
        stageGObj1_Callback3,
    },
    {
        stageGObj2_OnInit,
        stageGObj2_Callback1,
        stageGObj2_GObjProc,
        stageGObj2_Callback3,
        (1 << 30) | (1 << 31),
    },
    { 0 },
};

StageData grTMs_StageData = {
    Gr_Kind_TMars,
    stage_callbacks,
    "/GrTMs.dat",
    grTMars_80221EF8,
    grTMars_80221EF4,
    grTmars_UnkStage0_OnLoad,
    grTmars_UnkStage0_OnStart,
    grTMars_80221F90,
    grTMars_802221C8,
    grTMars_802221D0,
    (1 << 0),
    NULL,
    0,
};

static void grTMars_80221EF4(bool arg0) {}

static void grTMars_80221EF8(void)
{
    Ground_InitTargetStage(setupStageCallbacks);
}

static void grTmars_UnkStage0_OnLoad(void) {}

static void grTmars_UnkStage0_OnStart(void)
{
    grZakoGenerator_801CAE04(NULL);
}

static bool grTMars_80221F90(void)
{
    return false;
}

static Ground_GObj* setupStageCallbacks(int gobj_id)
{
    Ground_GObj* gobj;
    StageCallbacks* callbacks = &stage_callbacks[gobj_id];
    gobj = Ground_GetStageGObj(gobj_id);

    if (gobj != NULL) {
        Ground_SetupStageCallbacks(gobj, callbacks);
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 0xC3, gobj_id);
    }

    return gobj;
}

static void stageGObj0_OnInit(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    grAnime_801C8138(gobj, gp->map_id, 0);
}

static bool stageGObj0_Callback1(Ground_GObj* arg0)
{
    return false;
}

static void stageGObj0_GObjProc(Ground_GObj* arg0) {}

static void stageGObj0_Callback3(Ground_GObj* arg0) {}

static void stageGObj2_OnInit(Ground_GObj* gobj)
{
    Ground_JObjInline1(gobj);
}

static bool stageGObj2_Callback1(Ground_GObj* arg0)
{
    return false;
}

static void stageGObj2_GObjProc(Ground_GObj* gobj)
{
    lb_800115F4();
    Ground_801C2FE0(gobj);
}

static void stageGObj2_Callback3(Ground_GObj* arg0) {}

static void stageGObj1_OnInit(Ground_GObj* gobj)
{
    Ground_JObjInline1(gobj);
}

static bool stageGObj1_Callback1(Ground_GObj* arg0)
{
    return false;
}

static void stageGObj1_GObjProc(Ground_GObj* gobj)
{
    Ground_801C2FE0(gobj);
}

static void stageGObj1_Callback3(Ground_GObj* arg0) {}

static DynamicsDesc* grTMars_802221C8(enum_t arg0)
{
    return NULL;
}

static bool grTMars_802221D0(Vec3* arg0, int arg1, HSD_JObj* arg2)
{
    return true;
}
