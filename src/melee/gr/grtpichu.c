#include <Runtime/platform.h>

#include <melee/lb/forward.h>
#include <sysdolphin/baselib/forward.h>

#include "ground.h"
#include "grzakogenerator.h"
#include "inlines.h"
#include "types.h"
#include <dolphin/mtx.h>
#include <sysdolphin/baselib/gobjproc.h>

/* 222B98 */ static void grTPichu_80222B98(bool);
/* 222B9C */ static void grTPichu_OnInit(void);
/* 222C0C */ static void grTpichu_UnkStage0_OnLoad(void);
/* 222C10 */ static void grTpichu_UnkStage0_OnStart(void);
/* 222C34 */ static bool grTPichu_80222C34(void);
/* 222C3C */ static HSD_GObj* grTPichu_80222C3C(int gobj_id);
/* 222D24 */ static void stageGObj0_OnInit(Ground_GObj* gobj);
/* 222D50 */ static bool grTPichu_80222D50(Ground_GObj*);
/* 222D58 */ static void grTPichu_80222D58(Ground_GObj*);
/* 222D5C */ static void grTPichu_80222D5C(Ground_GObj*);
/* 222D60 */ static void stageGObj2_OnInit(Ground_GObj* gobj);
/* 222DB0 */ static bool grTPichu_80222DB0(Ground_GObj*);
/* 222DB8 */ static void stageGObj2_GObjProc(Ground_GObj* gobj);
/* 222DEC */ static void grTPichu_80222DEC(Ground_GObj*);
/* 222DF0 */ static void stageGObj1_OnInit(Ground_GObj* gobj);
/* 222E40 */ static bool grTPichu_80222E40(Ground_GObj*);
/* 222E48 */ static void stageGObj1_GObjProc(Ground_GObj*);
/* 222E68 */ static void grTPichu_80222E68(Ground_GObj*);
/* 222E6C */ static DynamicsDesc* grTPichu_80222E6C(enum_t);
/* 222E74 */ static bool grTPichu_80222E74(Vec3*, int, HSD_JObj*);

static StageCallbacks grTPc_StageCallbacks[] = {
    {
        stageGObj0_OnInit,
        grTPichu_80222D50,
        grTPichu_80222D58,
        grTPichu_80222D5C,
        0,
    },
    {
        stageGObj1_OnInit,
        grTPichu_80222E40,
        stageGObj1_GObjProc,
        grTPichu_80222E68,
        0,
    },
    {
        stageGObj2_OnInit,
        grTPichu_80222DB0,
        stageGObj2_GObjProc,
        grTPichu_80222DEC,
        (1 << 30) | (1 << 31),
    },
    { NULL, NULL, NULL, NULL, 0 },
};

StageData grTPc_StageData = {
    Gr_Kind_TPichu,
    grTPc_StageCallbacks,
    "/GrTPc.dat",
    grTPichu_OnInit,
    grTPichu_80222B98,
    grTpichu_UnkStage0_OnLoad,
    grTpichu_UnkStage0_OnStart,
    grTPichu_80222C34,
    grTPichu_80222E6C,
    grTPichu_80222E74,
    0,
    NULL,
    0,
};

static void grTPichu_80222B98(bool arg0) {}

static void grTPichu_OnInit(void)
{
    Ground_InitTargetStage(grTPichu_80222C3C);
}

static void grTpichu_UnkStage0_OnLoad(void) {}

static void grTpichu_UnkStage0_OnStart(void)
{
    grZakoGenerator_801CAE04(NULL);
}

static bool grTPichu_80222C34(void)
{
    return false;
}

static HSD_GObj* grTPichu_80222C3C(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grTPc_StageCallbacks[gobj_id];

    gobj = Ground_GetStageGObj(gobj_id);

    if (gobj != NULL) {
        Ground_SetupStageCallbacks(gobj, callbacks);
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 0xc2, gobj_id);
    }

    return gobj;
}

static void stageGObj0_OnInit(Ground_GObj* gobj)
{
    Ground_StartMapAnim(gobj);
}

static bool grTPichu_80222D50(Ground_GObj* arg0)
{
    return false;
}

static void grTPichu_80222D58(Ground_GObj* arg0) {}

static void grTPichu_80222D5C(Ground_GObj* arg0) {}

static void stageGObj2_OnInit(Ground_GObj* gobj)
{
    Ground_InitMapCollAndAnim(gobj);
}

static bool grTPichu_80222DB0(Ground_GObj* arg0)
{
    return false;
}

static void stageGObj2_GObjProc(Ground_GObj* gobj)
{
    Ground_UpdateWindAndMapColl(gobj);
}

static void grTPichu_80222DEC(Ground_GObj* arg0) {}

static void stageGObj1_OnInit(Ground_GObj* gobj)
{
    Ground_InitMapCollAndAnim(gobj);
}

static bool grTPichu_80222E40(Ground_GObj* arg0)
{
    return false;
}

static void stageGObj1_GObjProc(Ground_GObj* arg0)
{
    Ground_UpdateMapColl(arg0);
}

static void grTPichu_80222E68(Ground_GObj* arg0) {}

static DynamicsDesc* grTPichu_80222E6C(enum_t arg0)
{
    return NULL;
}

static bool grTPichu_80222E74(Vec3* arg0, int arg1, HSD_JObj* arg2)
{
    return true;
}
