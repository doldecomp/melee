#include "grtfalco.h"

#include "granime.h"
#include "ground.h"
#include "grzakogenerator.h"
#include "inlines.h"
#include "types.h"

#include <placeholder.h>

#include "lb/lb_00F9.h"

#include "mp/forward.h"

#include "mp/mplib.h"

#include <baselib/gobj.h>
#include <baselib/gobjproc.h>

/* 2207F0 */ static void grTFalco_802207F0(bool);
/* 2207F4 */ static void grTFalco_802207F4(void);
/* 22086C */ static void grTfalco_UnkStage0_OnLoad(void);
/* 220870 */ static void grTfalco_UnkStage0_OnStart(void);
/* 220894 */ static bool grTFalco_80220894(void);
/* 22089C */ static HSD_GObj* setupStageCallbacks(int);
/* 220984 */ static void stageGObj0_OnInit(Ground_GObj*);
/* 2209B0 */ static bool stageGObj0_Callback1(Ground_GObj*);
/* 2209B8 */ static void stageGObj0_GObjProc(Ground_GObj*);
/* 2209BC */ static void stageGObj0_Callback3(Ground_GObj*);
/* 2209C0 */ static void stageGObj2_OnInit(Ground_GObj*);
/* 220A10 */ static bool stageGObj2_Callback1(Ground_GObj*);
/* 220A18 */ static void stageGObj2_GObjProc(Ground_GObj*);
/* 220A4C */ static void stageGObj2_Callback3(Ground_GObj*);
/* 220A50 */ static void stageGObj1_OnInit(Ground_GObj*);
/* 220AA0 */ static bool stageGObj1_Callback1(Ground_GObj*);
/* 220AA8 */ static void stageGObj1_GObjProc(Ground_GObj*);
/* 220AC8 */ static void stageGObj1_Callback3(Ground_GObj*);
/* 220ACC */ static DynamicsDesc* grTFalco_80220ACC(enum_t);
/* 220B78 */ static bool grTFalco_80220B78(Vec3*, int, HSD_JObj*);

StageCallbacks grTFc_803E8918[] = {
    {
        stageGObj0_OnInit,
        stageGObj0_Callback1,
        stageGObj0_GObjProc,
        stageGObj0_Callback3,
        0,
    },
    {
        stageGObj1_OnInit,
        stageGObj1_Callback1,
        stageGObj1_GObjProc,
        stageGObj1_Callback3,
        0,
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

StageData grTFc_StageData = {
    Gr_Kind_TFalco,
    grTFc_803E8918,
    "/GrTFc.dat",
    grTFalco_802207F4,
    grTFalco_802207F0,
    grTfalco_UnkStage0_OnLoad,
    grTfalco_UnkStage0_OnStart,
    grTFalco_80220894,
    grTFalco_80220ACC,
    grTFalco_80220B78,
    (1 << 0),
    NULL,
    0,
};

struct grTFalco_YakumonoParam {
    UNK_T unk_0;
    UNK_T unk_4;
    UNK_T unk_8;
    UNK_T unk_C;
};

static struct grTFalco_YakumonoParam* yakumono_param;

void grTFalco_802207F0(bool arg0) {}

void grTFalco_802207F4(void)
{
    yakumono_param = Ground_GetYakumonoParam();
    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = true;
    setupStageCallbacks(0);
    setupStageCallbacks(1);
    setupStageCallbacks(2);
    Ground_801C39C0();
    Ground_801C3BB4();
    Ground_801C4210();
    Ground_801C42AC();
}

void grTfalco_UnkStage0_OnLoad(void) {}

void grTfalco_UnkStage0_OnStart(void)
{
    grZakoGenerator_801CAE04(NULL);
}

bool grTFalco_80220894(void)
{
    return false;
}

Ground_GObj* setupStageCallbacks(int gobj_id)
{
    Ground_GObj* gobj;
    StageCallbacks* callbacks = &grTFc_803E8918[gobj_id];

    gobj = Ground_GetStageGObj(gobj_id);

    if (gobj != NULL) {
        Ground_SetupStageCallbacks(gobj, callbacks);
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 201, gobj_id);
    }

    return gobj;
}

void stageGObj0_OnInit(Ground_GObj* gobj)
{
    Ground* gp = (Ground*) HSD_GObjGetUserData(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool stageGObj0_Callback1(Ground_GObj* arg0)
{
    return false;
}

void stageGObj0_GObjProc(Ground_GObj* arg0) {}

void stageGObj0_Callback3(Ground_GObj* arg0) {}

void stageGObj2_OnInit(Ground_GObj* gobj)
{
    Ground_JObjInline1(gobj);
}

bool stageGObj2_Callback1(Ground_GObj* arg0)
{
    return false;
}

void stageGObj2_GObjProc(Ground_GObj* arg0)
{
    lb_800115F4();
    Ground_801C2FE0(arg0);
}

void stageGObj2_Callback3(Ground_GObj* arg0) {}

void stageGObj1_OnInit(Ground_GObj* gobj)
{
    Ground_JObjInline1(gobj);
}

bool stageGObj1_Callback1(Ground_GObj* arg0)
{
    return false;
}

void stageGObj1_GObjProc(Ground_GObj* gobj)
{
    Ground_801C2FE0(gobj);
}

void stageGObj1_Callback3(Ground_GObj* arg0) {}

DynamicsDesc* grTFalco_80220ACC(enum_t arg0)
{
    if (arg0 != -1) {
        enum_t i = mpJointFromLine(arg0);

        if (i != -1 && i == 0) {
            i = mpLineGetKind(arg0);

            if (i == CollLine_Floor) {
                return yakumono_param->unk_0;
            }

            if (i == CollLine_Ceiling) {
                return yakumono_param->unk_4;
            }

            if (i == CollLine_RightWall) {
                return yakumono_param->unk_8;
            }

            if (i == CollLine_LeftWall) {
                return yakumono_param->unk_C;
            }

            return NULL;
        }
    }

    return NULL;
}

bool grTFalco_80220B78(Vec3* arg0, int arg1, HSD_JObj* arg2)
{
    return true;
}
