#include "grtclink.h"

#include "ground.h"
#include "grzakogenerator.h"
#include "inlines.h"
#include "types.h"
#include <melee/lb/types.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjproc.h>

static void grTCLink_OnInit(void);
static void stageGObj2_OnInit(Ground_GObj* gobj);
static void stageGObj2_GObjProc(Ground_GObj* gobj);
static void stageGObj1_OnInit(Ground_GObj* gobj);
static void stageGObj1_GObjProc(Ground_GObj* gobj);

static StageCallbacks grTCLink_StageCallbacks[] = {
    {
        grTCLink_802200D0,
        grTCLink_802200FC,
        grTCLink_80220104,
        grTCLink_80220108,
        0,
    },
    {
        stageGObj1_OnInit,
        grTCLink_802201EC,
        stageGObj1_GObjProc,
        grTCLink_80220214,
        0,
    },
    {
        stageGObj2_OnInit,
        grTCLink_8022015C,
        stageGObj2_GObjProc,
        grTCLink_80220198,
        (1 << 30) | (1 << 31),
    },
    { 0 },
};

StageData grTCLink_StageData = {
    Gr_Kind_TClink,
    grTCLink_StageCallbacks,
    "/GrTCl.dat",
    grTCLink_OnInit,
    grTCLink_8021FF44,
    grTclink_UnkStage0_OnLoad,
    grTclink_UnkStage0_OnStart,
    grTCLink_8021FFE0,
    grTCLink_80220218,
    grTCLink_80220220,
    (1 << 0),
    NULL,
    0,
};

void grTCLink_8021FF44(bool unused) {}

static void grTCLink_OnInit(void)
{
    Ground_InitTargetStage(grTCLink_8021FFE8);
}

void grTclink_UnkStage0_OnLoad(void) {}

void grTclink_UnkStage0_OnStart(void)
{
    grZakoGenerator_801CAE04(NULL);
}

bool grTCLink_8021FFE0(void)
{
    return false;
}

HSD_GObj* grTCLink_8021FFE8(int id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grTCLink_StageCallbacks[id];

    gobj = Ground_GetStageGObj(id);

    if (gobj != NULL) {
        Ground_SetupStageCallbacks(gobj, callbacks);
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 195, id);
    }

    return gobj;
}

void grTCLink_802200D0(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grTCLink_802200FC(Ground_GObj* gobj)
{
    return false;
}

void grTCLink_80220104(Ground_GObj* gobj) {}

void grTCLink_80220108(Ground_GObj* gobj) {}

static void stageGObj2_OnInit(Ground_GObj* gobj)
{
    Ground_InitMapCollAndAnim(gobj);
}

bool grTCLink_8022015C(Ground_GObj* gobj)
{
    return false;
}

static void stageGObj2_GObjProc(Ground_GObj* gobj)
{
    Ground_UpdateWindAndMapColl(gobj);
}

void grTCLink_80220198(Ground_GObj* gobj) {}

static void stageGObj1_OnInit(Ground_GObj* gobj)
{
    Ground_InitMapCollAndAnim(gobj);
}

bool grTCLink_802201EC(Ground_GObj* gobj)
{
    return false;
}

static void stageGObj1_GObjProc(Ground_GObj* gobj)
{
    Ground_UpdateMapColl(gobj);
}

void grTCLink_80220214(Ground_GObj* gobj) {}

DynamicsDesc* grTCLink_80220218(enum_t unused)
{
    return NULL;
}

bool grTCLink_80220220(Vec3* vec, int arg1, HSD_JObj* jobj)
{
    return true;
}
