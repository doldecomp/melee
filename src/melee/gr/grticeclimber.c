#include "grticeclimber.h"

#include "granime.h"
#include "grmaterial.h"
#include "ground.h"
#include "grzakogenerator.h"
#include "inlines.h"
#include "types.h"

#include "cm/camera.h"
#include "ef/efsync.h"
#include "it/inlines.h"
#include "it/types.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "lb/lbspdisplay.h"

#include <baselib/gobj.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>

/* 220F10 */ static void grTIceClimber_80220F10(bool);
/* 220F14 */ static void grTIceClimber_80220F14(void);
/* 220F84 */ static void grTiceclimber_UnkStage0_OnLoad(void);
/* 220F88 */ static void grTiceclimber_UnkStage0_OnStart(void);
/* 220FAC */ static bool grTIceClimber_80220FAC(void);
/* 220FB4 */ static HSD_GObj* setupStageCallbacks(int);
/* 22109C */ static void stageGObj0_OnInit(Ground_GObj*);
/* 2210C8 */ static bool stageGObj0_Callback1(Ground_GObj*);
/* 2210D0 */ static void stageGObj0_GObjProc(Ground_GObj*);
/* 2210D4 */ static void stageGObj0_Callback3(Ground_GObj*);
/* 2210D8 */ static void stageGObj2_OnInit(Ground_GObj*);
/* 22114C */ static bool stageGObj2_Callback1(Ground_GObj*);
/* 221154 */ static void stageGObj2_GObjProc(Ground_GObj*);
/* 221188 */ static void stageGObj2_Callback3(Ground_GObj*);
/* 22118C */ static void stageGObj1_OnInit(Ground_GObj*);
/* 2211DC */ static bool stageGObj1_Callback1(Ground_GObj*);
/* 2211E4 */ static void stageGObj1_GObjProc(Ground_GObj*);
/* 221204 */ static void stageGObj1_Callback3(Ground_GObj*);
/* 221208 */ static void grTIceClimber_80221208(Item_GObj*, Ground*, Vec3*,
                                                HSD_GObj*, f32);
/* 221288 */ static void grTIceClimber_80221288(HSD_GObj*);
/* 221354 */ static DynamicsDesc* grTIceClimber_80221354(enum_t);
/* 22135C */ static bool grTIceClimber_8022135C(Vec3*, int, HSD_JObj*);

static StageCallbacks stage_callbacks[] = {
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

StageData grTIc_StageData = {
    Gr_Kind_TIceclimber,
    stage_callbacks,
    "/GrTIc.dat",
    grTIceClimber_80220F14,
    grTIceClimber_80220F10,
    grTiceclimber_UnkStage0_OnLoad,
    grTiceclimber_UnkStage0_OnStart,
    grTIceClimber_80220FAC,
    grTIceClimber_80221354,
    grTIceClimber_8022135C,
    (1 << 0),
    NULL,
    0,
};

void grTIceClimber_80220F10(bool unused) {}

void grTIceClimber_80220F14(void)
{
    Ground_InitTargetStage(setupStageCallbacks);
}

void grTiceclimber_UnkStage0_OnLoad(void) {}

void grTiceclimber_UnkStage0_OnStart(void)
{
    grZakoGenerator_801CAE04(NULL);
}

bool grTIceClimber_80220FAC(void)
{
    return false;
}

Ground_GObj* setupStageCallbacks(int id)
{
    Ground_GObj* gobj;
    StageCallbacks* callbacks = &stage_callbacks[id];

    gobj = Ground_GetStageGObj(id);

    if (gobj != NULL) {
        Ground_SetupStageCallbacks(gobj, callbacks);
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 202, id);
    }

    return gobj;
}

void stageGObj0_OnInit(Ground_GObj* gobj)
{
    Ground* gp = (Ground*) HSD_GObjGetUserData(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool stageGObj0_Callback1(Ground_GObj* gobj)
{
    return false;
}

void stageGObj0_GObjProc(Ground_GObj* gobj) {}

void stageGObj0_Callback3(Ground_GObj* gobj) {}

void stageGObj2_OnInit(Ground_GObj* gobj)
{
    Ground_JObjInline1(gobj);
    grAnime_801C7FF8(gobj, 69, 2, 1, 0.0F, 1.0F);
    grTIceClimber_80221288(gobj);
}

bool stageGObj2_Callback1(Ground_GObj* gobj)
{
    return false;
}

void stageGObj2_GObjProc(Ground_GObj* gobj)
{
    lb_800115F4();
    Ground_801C2FE0(gobj);
}

void stageGObj2_Callback3(Ground_GObj* gobj) {}

void stageGObj1_OnInit(Ground_GObj* gobj)
{
    Ground_JObjInline1(gobj);
}

bool stageGObj1_Callback1(Ground_GObj* gobj)
{
    return false;
}

void stageGObj1_GObjProc(Ground_GObj* gobj)
{
    Ground_801C2FE0(gobj);
}

void stageGObj1_Callback3(Ground_GObj* gobj) {}

void grTIceClimber_80221208(Item_GObj* gobj, Ground* u1, Vec3* u2,
                            HSD_GObj* u3, f32 u4)
{
    Vec3 pos;
    Item* it = GET_ITEM(gobj);

    HSD_JObjSetFlagsAll(it->xDD4_itemVar.mato.x4, JOBJ_HIDDEN);
    lb_8000B1CC(it->xDD4_itemVar.mato.x4, NULL, &pos);
    efSync_Spawn(0x445, gobj, &pos);
    Camera_80030E44(2, 0);
    Ground_801C53EC(310);
    grMaterial_801C8CDC(gobj);
}

s16 grTIc_803E8B5C[] = {
    0,  1,  2,  3,  4,  5,  6,  8,  9,  10, 11, 12, 13, 14,
    15, 16, 17, 18, 19, 20, 21, 22, 44, 45, 46, 47, 48, 49,
    50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, 0,
};

void grTIceClimber_80221288(HSD_GObj* ground_gobj)
{
    Ground* gp = GET_GROUND(ground_gobj);
    int i;

    for (i = 0; grTIc_803E8B5C[i] != -1; i++) {
        enum_t result_0 = Ground_801C33C0(2, grTIc_803E8B5C[i]);
        if (result_0 != -1) {
            Item_GObj* result_1 = grMaterial_801C8CFC(
                0, 0, gp, Ground_801C3FA4(ground_gobj, result_0), 0,
                grTIceClimber_80221208, 0);

            if (result_1 != NULL) {
                grMaterial_801C8DE0(result_1, -1.0F, 0.0F, 0.0F, 1.0F, 0.0F,
                                    0.0F, 4.0F);
                grMaterial_801C8E08(result_1);
            }
        }
    }
}

DynamicsDesc* grTIceClimber_80221354(enum_t gobj)
{
    return NULL;
}

bool grTIceClimber_8022135C(Vec3* vec, int arg1, HSD_JObj* jobj)
{
    return true;
}
