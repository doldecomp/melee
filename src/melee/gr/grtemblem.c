#include "grtemblem.h"

#include <Runtime/platform.h>

#include <melee/lb/forward.h>
#include <sysdolphin/baselib/forward.h>

#include "ground.h"
#include "grzakogenerator.h"
#include "inlines.h"
#include "types.h"
#include <dolphin/mtx.h>
#include <sysdolphin/baselib/gobjproc.h>

static void grTRoy_802243F4(bool);
static void grTRoy_OnInit(void);
static void grTemblem_UnkStage0_OnLoad(void);
static void grTemblem_UnkStage0_OnStart(void);
static bool grTRoy_80224490(void);
static HSD_GObj* grTRoy_80224498(int gobj_id);
static void stageGObj0_OnInit(Ground_GObj* gobj);
static bool grTRoy_802245AC(Ground_GObj*);
static void grTRoy_802245B4(Ground_GObj*);
static void grTRoy_802245B8(Ground_GObj*);
static void stageGObj2_OnInit(Ground_GObj* gobj);
static bool grTRoy_8022460C(Ground_GObj*);
static void stageGObj2_GObjProc(Ground_GObj* gobj);
static void grTRoy_80224648(Ground_GObj*);
static void stageGObj1_OnInit(Ground_GObj* gobj);
static bool grTRoy_8022469C(Ground_GObj*);
static void stageGObj1_GObjProc(Ground_GObj*);
static void grTRoy_802246C4(Ground_GObj*);
static DynamicsDesc* grTRoy_802246C8(enum_t);
static bool grTRoy_802246D0(Vec3*, int, HSD_JObj*);

StageCallbacks grTFe_StageCallbacks[4] = {
    {
        stageGObj0_OnInit,
        grTRoy_802245AC,
        grTRoy_802245B4,
        grTRoy_802245B8,
        0,
    },
    {
        stageGObj1_OnInit,
        grTRoy_8022469C,
        stageGObj1_GObjProc,
        grTRoy_802246C4,
        0,
    },
    {
        stageGObj2_OnInit,
        grTRoy_8022460C,
        stageGObj2_GObjProc,
        grTRoy_80224648,
        (1 << 30) | (1 << 31),
    },
};

StageData grTFe_StageData = {
    Gr_Kind_TEmblem,
    grTFe_StageCallbacks,
    "/GrTFe.dat",
    grTRoy_OnInit,
    grTRoy_802243F4,
    grTemblem_UnkStage0_OnLoad,
    grTemblem_UnkStage0_OnStart,
    grTRoy_80224490,
    grTRoy_802246C8,
    grTRoy_802246D0,
    1,
};

static void grTRoy_802243F4(bool arg0) {}

static void grTRoy_OnInit(void)
{
    Ground_InitTargetStage(grTRoy_80224498);
}

static void grTemblem_UnkStage0_OnLoad(void) {}

static void grTemblem_UnkStage0_OnStart(void)
{
    grZakoGenerator_801CAE04(NULL);
}

static bool grTRoy_80224490(void)
{
    return false;
}

static HSD_GObj* grTRoy_80224498(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grTFe_StageCallbacks[gobj_id];

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
    Ground_StartMapAnim(gobj);
}

static bool grTRoy_802245AC(Ground_GObj* gobj)
{
    return false;
}

static void grTRoy_802245B4(Ground_GObj* gobj) {}

static void grTRoy_802245B8(Ground_GObj* gobj) {}

static void stageGObj2_OnInit(Ground_GObj* gobj)
{
    Ground_InitMapCollAndAnim(gobj);
}

static bool grTRoy_8022460C(Ground_GObj* gobj)
{
    return false;
}

static void stageGObj2_GObjProc(Ground_GObj* gobj)
{
    Ground_UpdateWindAndMapColl(gobj);
}

static void grTRoy_80224648(Ground_GObj* gobj) {}

static void stageGObj1_OnInit(Ground_GObj* gobj)
{
    Ground_InitMapCollAndAnim(gobj);
}

static bool grTRoy_8022469C(Ground_GObj* gobj)
{
    return false;
}

static void stageGObj1_GObjProc(Ground_GObj* gobj)
{
    Ground_UpdateMapColl(gobj);
}

static void grTRoy_802246C4(Ground_GObj* gobj) {}

static DynamicsDesc* grTRoy_802246C8(enum_t arg0)
{
    return NULL;
}

static bool grTRoy_802246D0(Vec3* vec, int arg1, HSD_JObj* jobj)
{
    return true;
}
