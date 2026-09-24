
#include <gr/grtgamewatch.h>

#include <gr/ground.h>
#include <gr/grzakogenerator.h>
#include <gr/inlines.h>
#include <gr/types.h>
#include <melee/lb/types.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjproc.h>

static void grTGameWatch_OnInit(void);
static void stageGObj2_OnInit(Ground_GObj* gobj);
static void stageGObj2_GObjProc(Ground_GObj* gobj);
static void stageGObj1_OnInit(Ground_GObj* gobj);
static void stageGObj1_GObjProc(Ground_GObj* gobj);

StageCallbacks grTGw_StageCallbacks[] = {
    { grTGameWatch_8022429C, grTGameWatch_802242C8, grTGameWatch_802242D0,
      grTGameWatch_802242D4, 0 },
    { stageGObj1_OnInit, grTGameWatch_802243B8, stageGObj1_GObjProc,
      grTGameWatch_802243E0, 0 },
    { stageGObj2_OnInit, grTGameWatch_80224328, stageGObj2_GObjProc,
      grTGameWatch_80224364, 0xC0000000 },
    { NULL, NULL, NULL, NULL, 0 }
};

StageData grTGw_StageData = {
    Gr_Kind_TGamewatch,
    grTGw_StageCallbacks,
    "/GrTGw.dat",
    grTGameWatch_OnInit,
    grTGameWatch_80224110,
    grTgamewatch_UnkStage0_OnLoad,
    grTgamewatch_UnkStage0_OnStart,
    grTGameWatch_802241AC,
    grTGameWatch_802243E4,
    grTGameWatch_802243EC,
    (1 << 0),
};

void grTGameWatch_80224110(bool unused)
{
    return;
}

static void grTGameWatch_OnInit(void)
{
    Ground_InitTargetStage(grTGameWatch_802241B4);
}

void grTgamewatch_UnkStage0_OnLoad(void)
{
    return;
}

void grTgamewatch_UnkStage0_OnStart(void)
{
    grZakoGenerator_801CAE04(NULL);
}

bool grTGameWatch_802241AC(void)
{
    return false;
}

HSD_GObj* grTGameWatch_802241B4(int id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grTGw_StageCallbacks[id];

    gobj = Ground_GetStageGObj(id);

    if (gobj != NULL) {
        Ground_SetupStageCallbacks(gobj, callbacks);
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 195, id);
    }

    return gobj;
}

void grTGameWatch_8022429C(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grTGameWatch_802242C8(Ground_GObj* gobj)
{
    return false;
}

void grTGameWatch_802242D0(Ground_GObj* gobj)
{
    return;
}

void grTGameWatch_802242D4(Ground_GObj* gobj)
{
    return;
}

static void stageGObj2_OnInit(Ground_GObj* gobj)
{
    Ground_InitMapCollAndAnim(gobj);
}

bool grTGameWatch_80224328(Ground_GObj* gobj)
{
    return false;
}

static void stageGObj2_GObjProc(Ground_GObj* gobj)
{
    Ground_UpdateWindAndMapColl(gobj);
}

void grTGameWatch_80224364(Ground_GObj* gobj)
{
    return;
}

static void stageGObj1_OnInit(Ground_GObj* gobj)
{
    Ground_InitMapCollAndAnim(gobj);
}

bool grTGameWatch_802243B8(Ground_GObj* gobj)
{
    return false;
}

static void stageGObj1_GObjProc(Ground_GObj* gobj)
{
    Ground_UpdateMapColl(gobj);
}

void grTGameWatch_802243E0(Ground_GObj* gobj)
{
    return;
}

DynamicsDesc* grTGameWatch_802243E4(enum_t unused)
{
    return NULL;
}

bool grTGameWatch_802243EC(Vec3* vec, int arg1, HSD_JObj* jobj)
{
    return true;
}
