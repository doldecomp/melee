#include <Runtime/platform.h>

#include <melee/lb/forward.h>
#include <sysdolphin/baselib/forward.h>

#include "ground.h"
#include "grzakogenerator.h"
#include "inlines.h"
#include "types.h"
#include <dolphin/mtx.h>
#include <sysdolphin/baselib/gobjproc.h>

/* 22050C */ static void grtDrMario_8022050C(bool);
/* 220510 */ static void grtDrMario_OnInit(void);
/* 220580 */ static void grTdrmario_UnkStage0_OnLoad(void);
/* 220584 */ static void grTdrmario_UnkStage0_OnStart(void);
/* 2205A8 */ static bool grtDrMario_802205A8(void);
/* 2205B0 */ static HSD_GObj* grtDrMario_802205B0(int);
/* 220698 */ static void stageGObj0_OnInit(Ground_GObj*);
/* 2206C4 */ static bool grtDrMario_802206C4(Ground_GObj*);
/* 2206CC */ static void grtDrMario_802206CC(Ground_GObj*);
/* 2206D0 */ static void grtDrMario_802206D0(Ground_GObj*);
/* 2206D4 */ static void stageGObj2_OnInit(Ground_GObj*);
/* 220724 */ static bool grtDrMario_80220724(Ground_GObj*);
/* 22072C */ static void stageGObj2_GObjProc(Ground_GObj*);
/* 220760 */ static void grtDrMario_80220760(Ground_GObj*);
/* 220764 */ static void stageGObj1_OnInit(Ground_GObj*);
/* 2207B4 */ static bool grtDrMario_802207B4(Ground_GObj*);
/* 2207BC */ static void stageGObj1_GObjProc(Ground_GObj*);
/* 2207DC */ static void grtDrMario_802207DC(Ground_GObj*);
/* 2207E0 */ static DynamicsDesc* grtDrMario_802207E0(enum_t);
/* 2207E8 */ static bool grtDrMario_802207E8(Vec3*, int, HSD_JObj*);

static StageCallbacks grTDr_StageCallbacks[] = {
    {
        stageGObj0_OnInit,
        grtDrMario_802206C4,
        grtDrMario_802206CC,
        grtDrMario_802206D0,
        0,
    },
    {
        stageGObj1_OnInit,
        grtDrMario_802207B4,
        stageGObj1_GObjProc,
        grtDrMario_802207DC,
        0,
    },
    {
        stageGObj2_OnInit,
        grtDrMario_80220724,
        stageGObj2_GObjProc,
        grtDrMario_80220760,
        (1 << 31) | (1 << 30),
    },
    { 0 },
};

StageData grTDr_StageData = {
    Gr_Kind_TDrmario,
    grTDr_StageCallbacks,
    "/GrTDr.dat",
    grtDrMario_OnInit,
    grtDrMario_8022050C,
    grTdrmario_UnkStage0_OnLoad,
    grTdrmario_UnkStage0_OnStart,
    grtDrMario_802205A8,
    grtDrMario_802207E0,
    grtDrMario_802207E8,
    (1 << 0),
    NULL,
    0,
};

void grtDrMario_8022050C(bool unk0) {}

static void grtDrMario_OnInit(void)
{
    Ground_InitTargetStage(grtDrMario_802205B0);
}

void grTdrmario_UnkStage0_OnLoad(void) {}

void grTdrmario_UnkStage0_OnStart(void)
{
    grZakoGenerator_801CAE04(NULL);
}

bool grtDrMario_802205A8(void)
{
    return false;
}

HSD_GObj* grtDrMario_802205B0(int arg0)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grTDr_StageCallbacks[arg0];

    gobj = Ground_GetStageGObj(arg0);

    if (gobj != NULL) {
        Ground_SetupStageCallbacks(gobj, callbacks);
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 0xCC, arg0);
    }

    return gobj;
}

static void stageGObj0_OnInit(Ground_GObj* gobj)
{
    Ground_StartMapAnim(gobj);
}

bool grtDrMario_802206C4(Ground_GObj* gobj)
{
    return false;
}

void grtDrMario_802206CC(Ground_GObj* gobj) {}

void grtDrMario_802206D0(Ground_GObj* gobj) {}

static void stageGObj2_OnInit(Ground_GObj* gobj)
{
    Ground_InitMapCollAndAnim(gobj);
}

bool grtDrMario_80220724(Ground_GObj* gobj)
{
    return false;
}

static void stageGObj2_GObjProc(Ground_GObj* gobj)
{
    Ground_UpdateWindAndMapColl(gobj);
}

void grtDrMario_80220760(Ground_GObj* gobj) {}

static void stageGObj1_OnInit(Ground_GObj* gobj)
{
    Ground_InitMapCollAndAnim(gobj);
}

bool grtDrMario_802207B4(Ground_GObj* gobj)
{
    return false;
}

static void stageGObj1_GObjProc(Ground_GObj* gobj)
{
    Ground_UpdateMapColl(gobj);
}

void grtDrMario_802207DC(Ground_GObj* gobj) {}

DynamicsDesc* grtDrMario_802207E0(enum_t arg0)
{
    return NULL;
}

bool grtDrMario_802207E8(Vec3* arg0, int arg1, HSD_JObj* arg2)
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
