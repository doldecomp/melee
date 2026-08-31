#include "grtlink.h"

#include "granime.h"
#include "ground.h"
#include "grzakogenerator.h"
#include "inlines.h"
#include "types.h"

#include <platform.h>

#include "lb/lb_00F9.h"

#include <baselib/forward.h>

#include <dolphin/mtx.h>
#include <baselib/gobjproc.h>

/* 22192C */ static void grTLink_8022192C(bool);
/* 221930 */ static void grTLink_80221930(void);
/* 2219A0 */ static void grTlink_UnkStage0_OnLoad(void);
/* 2219A4 */ static void grTlink_UnkStage0_OnStart(void);
/* 2219C8 */ static bool grTLink_802219C8(void);
/* 2219D0 */ static HSD_GObj* grTLink_802219D0(int arg0);
/* 221AB8 */ static void grTLink_80221AB8(Ground_GObj*);
/* 221AE4 */ static bool grTLink_80221AE4(Ground_GObj*);
/* 221AEC */ static void grTLink_80221AEC(Ground_GObj*);
/* 221AF0 */ static void grTLink_80221AF0(Ground_GObj*);
/* 221AF4 */ static void grTLink_80221AF4(Ground_GObj*);
/* 221B44 */ static bool grTLink_80221B44(Ground_GObj*);
/* 221B4C */ static void grTLink_80221B4C(Ground_GObj*);
/* 221B80 */ static void grTLink_80221B80(Ground_GObj*);
/* 221B84 */ static void grTLink_80221B84(Ground_GObj*);
/* 221BD4 */ static bool grTLink_80221BD4(Ground_GObj*);
/* 221BDC */ static void grTLink_80221BDC(Ground_GObj*);
/* 221BFC */ static void grTLink_80221BFC(Ground_GObj*);
/* 221C00 */ static DynamicsDesc* grTLink_80221C00(enum_t);
/* 221C08 */ static bool grTLink_80221C08(Vec3*, int, HSD_JObj*);

static StageCallbacks grTLk_StageCallbacks[] = {
    {
        grTLink_80221AB8,
        grTLink_80221AE4,
        grTLink_80221AEC,
        grTLink_80221AF0,
        0,
    },
    {
        grTLink_80221B84,
        grTLink_80221BD4,
        grTLink_80221BDC,
        grTLink_80221BFC,
        0,
    },
    {
        grTLink_80221AF4,
        grTLink_80221B44,
        grTLink_80221B4C,
        grTLink_80221B80,
        (1 << 31) | (1 << 30),
    },
    { 0 },
};

StageData grTLk_StageData = {
    Gr_Kind_TLink,
    grTLk_StageCallbacks,
    "/GrTLk.dat",
    grTLink_80221930,
    grTLink_8022192C,
    grTlink_UnkStage0_OnLoad,
    grTlink_UnkStage0_OnStart,
    grTLink_802219C8,
    grTLink_80221C00,
    grTLink_80221C08,
    (1 << 0),
    NULL,
    0,
};

void grTLink_8022192C(bool unk0) {}

void grTLink_80221930(void)
{
    Ground_InitTargetStage(grTLink_802219D0);
}

void grTlink_UnkStage0_OnLoad(void) {}

void grTlink_UnkStage0_OnStart(void)
{
    grZakoGenerator_801CAE04(NULL);
}

bool grTLink_802219C8(void)
{
    return 0;
}

HSD_GObj* grTLink_802219D0(int arg0)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grTLk_StageCallbacks[arg0];

    gobj = Ground_GetStageGObj(arg0);

    if (gobj != NULL) {
        Ground_SetupStageCallbacks(gobj, callbacks);
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 0xC3, arg0);
    }

    return gobj;
}

void grTLink_80221AB8(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grTLink_80221AE4(Ground_GObj* gobj)
{
    return false;
}

void grTLink_80221AEC(Ground_GObj* gobj) {}

void grTLink_80221AF0(Ground_GObj* gobj) {}

void grTLink_80221AF4(Ground_GObj* gobj)
{
    Ground_JObjInline1(gobj);
}

bool grTLink_80221B44(Ground_GObj* gobj)
{
    return false;
}

void grTLink_80221B4C(Ground_GObj* gobj)
{
    lb_800115F4();
    Ground_801C2FE0(gobj);
}

void grTLink_80221B80(Ground_GObj* gobj) {}

void grTLink_80221B84(Ground_GObj* gobj)
{
    Ground_JObjInline1(gobj);
}

bool grTLink_80221BD4(Ground_GObj* gobj)
{
    return false;
}

void grTLink_80221BDC(Ground_GObj* gobj)
{
    Ground_801C2FE0(gobj);
}

void grTLink_80221BFC(Ground_GObj* gobj) {}

DynamicsDesc* grTLink_80221C00(enum_t arg0)
{
    return NULL;
}

bool grTLink_80221C08(Vec3* arg0, int arg1, HSD_JObj* arg2)
{
    return true;
}
