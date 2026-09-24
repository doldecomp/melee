
#include <Runtime/platform.h>

#include <melee/lb/forward.h>
#include <sysdolphin/baselib/forward.h>

#include <gr/ground.h>
#include <gr/grzakogenerator.h>
#include <gr/inlines.h>
#include <gr/types.h>
#include <dolphin/mtx.h>
#include <sysdolphin/baselib/gobjproc.h>

void grTKirby_80221364(bool); /* static */
static void grTKirby_OnInit(void);
void grTkirby_UnkStage0_OnLoad(void);  /* static */
void grTkirby_UnkStage0_OnStart(void); /* static */
bool grTKirby_80221400(void);          /* static */
HSD_GObj* grTKirby_80221408(int);      /* static */
static void stageGObj0_OnInit(Ground_GObj*);
bool grTKirby_8022151C(Ground_GObj*); /* static */
void grTKirby_80221524(Ground_GObj*); /* static */
void grTKirby_80221528(Ground_GObj*); /* static */
static void stageGObj2_OnInit(Ground_GObj*);
bool grTKirby_8022157C(Ground_GObj*); /* static */
static void stageGObj2_GObjProc(Ground_GObj*);
void grTKirby_802215B8(Ground_GObj*); /* static */
static void stageGObj1_OnInit(Ground_GObj*);
bool grTKirby_8022160C(Ground_GObj*); /* static */
static void stageGObj1_GObjProc(Ground_GObj*);
void grTKirby_80221634(Ground_GObj*);          /* static */
DynamicsDesc* grTKirby_80221638(enum_t);       /* static */
bool grTKirby_80221640(Vec3*, int, HSD_JObj*); /* static */

static StageCallbacks grTKb_StageCallbacks[] = {
    {
        stageGObj0_OnInit,
        grTKirby_8022151C,
        grTKirby_80221524,
        grTKirby_80221528,
        0,
    },
    {
        stageGObj1_OnInit,
        grTKirby_8022160C,
        stageGObj1_GObjProc,
        grTKirby_80221634,
        0,
    },
    {
        stageGObj2_OnInit,
        grTKirby_8022157C,
        stageGObj2_GObjProc,
        grTKirby_802215B8,
        (1 << 31) | (1 << 30),
    },
    { 0 },
};

StageData grTKb_StageData = {
    Gr_Kind_TKirby,
    grTKb_StageCallbacks,
    "/GrTKb.dat",
    grTKirby_OnInit,
    grTKirby_80221364,
    grTkirby_UnkStage0_OnLoad,
    grTkirby_UnkStage0_OnStart,
    grTKirby_80221400,
    grTKirby_80221638,
    grTKirby_80221640,
    (1 << 0),
    NULL,
    0,
};

void grTKirby_80221364(bool unk) {}

static void grTKirby_OnInit(void)
{
    Ground_InitTargetStage(grTKirby_80221408);
}

void grTkirby_UnkStage0_OnLoad(void) {}

void grTkirby_UnkStage0_OnStart(void)
{
    grZakoGenerator_801CAE04(NULL);
}

bool grTKirby_80221400(void)
{
    return false;
}

HSD_GObj* grTKirby_80221408(int arg0)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grTKb_StageCallbacks[arg0];

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

bool grTKirby_8022151C(Ground_GObj* gobj)
{
    return false;
}

void grTKirby_80221524(Ground_GObj* gobj) {}

void grTKirby_80221528(Ground_GObj* gobj) {}

static void stageGObj2_OnInit(Ground_GObj* gobj)
{
    Ground_InitMapCollAndAnim(gobj);
}

bool grTKirby_8022157C(Ground_GObj* gobj)
{
    return false;
}

static void stageGObj2_GObjProc(Ground_GObj* gobj)
{
    Ground_UpdateWindAndMapColl(gobj);
}

void grTKirby_802215B8(Ground_GObj* gobj) {}

static void stageGObj1_OnInit(Ground_GObj* gobj)
{
    Ground_InitMapCollAndAnim(gobj);
}

bool grTKirby_8022160C(Ground_GObj* gobj)
{
    return false;
}

static void stageGObj1_GObjProc(Ground_GObj* gobj)
{
    Ground_UpdateMapColl(gobj);
}

void grTKirby_80221634(Ground_GObj* gobj) {}

DynamicsDesc* grTKirby_80221638(enum_t arg0)
{
    return NULL;
}

bool grTKirby_80221640(Vec3* arg0, int arg1, HSD_JObj* arg2)
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
