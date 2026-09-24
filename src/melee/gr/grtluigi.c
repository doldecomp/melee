#include <gr/grtluigi.h>

#include <gr/ground.h>
#include <gr/grzakogenerator.h>
#include <gr/inlines.h>
#include <gr/types.h>
#include <sysdolphin/baselib/gobjproc.h>

static void grTLuigi_OnInit(void);
static void stageGObj0_OnInit(Ground_GObj* gobj);
static void stageGObj2_OnInit(Ground_GObj* gobj);
static void stageGObj2_GObjProc(Ground_GObj* arg0);
static void stageGObj1_OnInit(Ground_GObj* gobj);
static void stageGObj1_GObjProc(Ground_GObj* gobj);

/* static */ StageCallbacks grTLg_803E8DF0[4] = {
    {
        stageGObj0_OnInit,
        grTLuigi_80221DC8,
        grTLuigi_80221DD0,
        grTLuigi_80221DD4,
        0,
    },
    {
        stageGObj1_OnInit,
        grTLuigi_80221EB8,
        stageGObj1_GObjProc,
        grTLuigi_80221EE0,
        0,
    },
    {
        stageGObj2_OnInit,
        grTLuigi_80221E28,
        stageGObj2_GObjProc,
        grTLuigi_80221E64,
        (1 << 30) | (1 << 31),
    },
};

StageData grTLg_StageData = {
    Gr_Kind_TLuigi,
    grTLg_803E8DF0,
    "/GrTLg.dat",
    grTLuigi_OnInit,
    grTLuigi_80221C10,
    grTluigi_UnkStage0_OnLoad,
    grTluigi_UnkStage0_OnStart,
    grTLuigi_80221CAC,
    grTLuigi_80221EE4,
    grTLuigi_80221EEC,
    1,
};

void grTLuigi_80221C10(bool arg0) {}

static void grTLuigi_OnInit(void)
{
    Ground_InitTargetStage(grTLuigi_80221CB4);
}

void grTluigi_UnkStage0_OnLoad(void) {}

void grTluigi_UnkStage0_OnStart(void)
{
    grZakoGenerator_801CAE04(NULL);
}

bool grTLuigi_80221CAC(void)
{
    return false;
}

HSD_GObj* grTLuigi_80221CB4(int arg0)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grTLg_803E8DF0[arg0];

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

bool grTLuigi_80221DC8(Ground_GObj* arg0)
{
    return false;
}

void grTLuigi_80221DD0(Ground_GObj* arg0) {}

void grTLuigi_80221DD4(Ground_GObj* arg0) {}

static void stageGObj2_OnInit(Ground_GObj* gobj)
{
    Ground_InitMapCollAndAnim(gobj);
}

bool grTLuigi_80221E28(Ground_GObj* arg0)
{
    return false;
}

static void stageGObj2_GObjProc(Ground_GObj* arg0)
{
    Ground_UpdateWindAndMapColl(arg0);
}

void grTLuigi_80221E64(Ground_GObj* arg0) {}

static void stageGObj1_OnInit(Ground_GObj* gobj)
{
    Ground_InitMapCollAndAnim(gobj);
}

bool grTLuigi_80221EB8(Ground_GObj* arg0)
{
    return false;
}

static void stageGObj1_GObjProc(Ground_GObj* gobj)
{
    Ground_UpdateMapColl(gobj);
}

void grTLuigi_80221EE0(Ground_GObj* arg0) {}

DynamicsDesc* grTLuigi_80221EE4(enum_t arg0)
{
    return NULL;
}

bool grTLuigi_80221EEC(Vec3* arg0, int arg1, HSD_JObj* arg2)
{
    return true;
}
