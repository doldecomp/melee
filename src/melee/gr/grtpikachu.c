#include "grtpikachu.h"

#include "ground.h"
#include "grzakogenerator.h"
#include "inlines.h"
#include "types.h"
#include <melee/lb/types.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjproc.h>

static void grTPikachu_OnInit(void);
static void stageGObj2_OnInit(Ground_GObj* gobj);
static void stageGObj2_GObjProc(Ground_GObj* gobj);
static void stageGObj1_OnInit(Ground_GObj* gobj);
static void stageGObj1_GObjProc(Ground_GObj* gobj);

StageCallbacks grTPk_StageCallbacks[] = {
    { grTPikachu_80223008, grTPikachu_80223034, grTPikachu_8022303C,
      grTPikachu_80223040, 0 },
    { stageGObj1_OnInit, grTPikachu_80223124, stageGObj1_GObjProc,
      grTPikachu_8022314C, 0 },
    { stageGObj2_OnInit, grTPikachu_80223094, stageGObj2_GObjProc,
      grTPikachu_802230D0, 0xC0000000 },
    { NULL, NULL, NULL, NULL, 0 }
};

StageData grTPk_StageData = {
    Gr_Kind_TPikachu,
    grTPk_StageCallbacks,
    "/GrTPk.dat",
    grTPikachu_OnInit,
    grTPikachu_80222E7C,
    grTpikachu_UnkStage0_OnLoad,
    grTpikachu_UnkStage0_OnStart,
    grTPikachu_80222F18,
    grTPikachu_80223150,
    grTPikachu_80223158,
    (1 << 0),
};

void grTPikachu_80222E7C(bool unused)
{
    return;
}

static void grTPikachu_OnInit(void)
{
    Ground_InitTargetStage(grTPikachu_80222F20);
}

void grTpikachu_UnkStage0_OnLoad(void)
{
    return;
}

void grTpikachu_UnkStage0_OnStart(void)
{
    grZakoGenerator_801CAE04(NULL);
}

bool grTPikachu_80222F18(void)
{
    return false;
}

HSD_GObj* grTPikachu_80222F20(int id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grTPk_StageCallbacks[id];

    gobj = Ground_GetStageGObj(id);

    if (gobj != NULL) {
        Ground_SetupStageCallbacks(gobj, callbacks);
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 195, id);
    }

    return gobj;
}

void grTPikachu_80223008(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grTPikachu_80223034(Ground_GObj* gobj)
{
    return false;
}

void grTPikachu_8022303C(Ground_GObj* gobj)
{
    return;
}

void grTPikachu_80223040(Ground_GObj* gobj)
{
    return;
}

static void stageGObj2_OnInit(Ground_GObj* gobj)
{
    Ground_InitMapCollAndAnim(gobj);
}

bool grTPikachu_80223094(Ground_GObj* gobj)
{
    return false;
}

static void stageGObj2_GObjProc(Ground_GObj* gobj)
{
    Ground_UpdateWindAndMapColl(gobj);
}

void grTPikachu_802230D0(Ground_GObj* gobj)
{
    return;
}

static void stageGObj1_OnInit(Ground_GObj* gobj)
{
    Ground_InitMapCollAndAnim(gobj);
}

bool grTPikachu_80223124(Ground_GObj* gobj)
{
    return false;
}

static void stageGObj1_GObjProc(Ground_GObj* gobj)
{
    Ground_UpdateMapColl(gobj);
}

void grTPikachu_8022314C(Ground_GObj* gobj)
{
    return;
}

DynamicsDesc* grTPikachu_80223150(enum_t unused)
{
    return NULL;
}

bool grTPikachu_80223158(Vec3* vec, int arg1, HSD_JObj* jobj)
{
    return true;
}
