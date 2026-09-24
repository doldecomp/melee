#include <gr/grtmewtwo.h>

#include <Runtime/platform.h>

#include <melee/lb/forward.h>
#include <melee/mp/forward.h>

#include <gr/ground.h>
#include <gr/grzakogenerator.h>
#include <gr/inlines.h>
#include <gr/types.h>
#include <dolphin/mtx.h>
#include <melee/mp/mplib.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjproc.h>

typedef struct grTMewtwo_UnkStruct {
    DynamicsDesc* x0;
    DynamicsDesc* x4;
    DynamicsDesc* xC;
    DynamicsDesc* x8;
    DynamicsDesc* x10;
    DynamicsDesc* x14;
    DynamicsDesc* x1C;
    DynamicsDesc* x18;
} grTMewtwo_UnkStruct;

/* 2221D8 */ static void grTMewtwo_802221D8(bool arg0);
/* 2221DC */ static void grTMewtwo_802221DC(void);
/* 222254 */ static void grTmewtwo_UnkStage0_OnLoad(void);
/* 222258 */ static void grTmewtwo_UnkStage0_OnStart(void);
/* 22227C */ static bool grTMewtwo_8022227C(void);
/* 222284 */ static Ground_GObj* grTMewtwo_80222284(int index);
/* 22236C */ static void stageGObj0_OnInit(Ground_GObj* gobj);
/* 222398 */ static bool grTMewtwo_80222398(Ground_GObj* gobj);
/* 2223A0 */ static void grTMewtwo_802223A0(Ground_GObj* gobj);
/* 2223A4 */ static void grTMewtwo_802223A4(Ground_GObj* gobj);
/* 2223A8 */ static void stageGObj2_OnInit(Ground_GObj* gobj);
/* 2223F8 */ static bool grTMewtwo_802223F8(Ground_GObj* gobj);
/* 222400 */ static void stageGObj2_GObjProc(Ground_GObj* gobj);
/* 222434 */ static void grTMewtwo_80222434(Ground_GObj* gobj);
/* 222438 */ static void stageGObj1_OnInit(Ground_GObj* gobj);
/* 222488 */ static bool grTMewtwo_80222488(Ground_GObj* gobj);
/* 222490 */ static void stageGObj1_GObjProc(Ground_GObj* gobj);
/* 2224B0 */ static void grTMewtwo_802224B0(Ground_GObj* gobj);
/* 2224B4 */ static DynamicsDesc* grTMewtwo_802224B4(enum_t arg0);
/* 2225C8 */ static bool grTMewtwo_802225C8(Vec3* arg0, int arg1,
                                            HSD_JObj* arg2);
/* 4D6B08 */ static grTMewtwo_UnkStruct* yakumono_param;

static StageCallbacks grTMewtwo_StageCallbacks[4] = {
    {
        stageGObj0_OnInit,
        grTMewtwo_80222398,
        grTMewtwo_802223A0,
        grTMewtwo_802223A4,
        0,
    },
    {
        stageGObj1_OnInit,
        grTMewtwo_80222488,
        stageGObj1_GObjProc,
        grTMewtwo_802224B0,
        0,
    },
    {
        stageGObj2_OnInit,
        grTMewtwo_802223F8,
        stageGObj2_GObjProc,
        grTMewtwo_80222434,
        (1 << 30) | (1 << 31),
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        0,
    },
};

StageData grTMewtwo_StageData = {
    Gr_Kind_TMewtwo,
    grTMewtwo_StageCallbacks,
    "/GrTMt.dat",
    grTMewtwo_802221DC,
    grTMewtwo_802221D8,
    grTmewtwo_UnkStage0_OnLoad,
    grTmewtwo_UnkStage0_OnStart,
    grTMewtwo_8022227C,
    grTMewtwo_802224B4,
    grTMewtwo_802225C8,
    (1 << 0),
    NULL,
};

void grTMewtwo_802221D8(bool arg0) {}

void grTMewtwo_802221DC(void)
{
    yakumono_param = Ground_GetYakumonoParam();
    Ground_InitTargetStage(grTMewtwo_80222284);
}

void grTmewtwo_UnkStage0_OnLoad(void) {}

void grTmewtwo_UnkStage0_OnStart(void)
{
    grZakoGenerator_801CAE04(NULL);
}

bool grTMewtwo_8022227C(void)
{
    return false;
}

Ground_GObj* grTMewtwo_80222284(int index)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grTMewtwo_StageCallbacks[index];

    gobj = Ground_GetStageGObj(index);

    if (gobj != NULL) {
        Ground_SetupStageCallbacks(gobj, callbacks);
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 201, index);
    }

    return gobj;
}

static void stageGObj0_OnInit(Ground_GObj* gobj)
{
    Ground_StartMapAnim(gobj);
}

bool grTMewtwo_80222398(Ground_GObj* gobj)
{
    return false;
}

void grTMewtwo_802223A0(Ground_GObj* gobj) {}

void grTMewtwo_802223A4(Ground_GObj* gobj) {}

static void stageGObj2_OnInit(Ground_GObj* gobj)
{
    Ground_InitMapCollAndAnim(gobj);
}

bool grTMewtwo_802223F8(Ground_GObj* gobj)
{
    return false;
}

static void stageGObj2_GObjProc(Ground_GObj* gobj)
{
    Ground_UpdateWindAndMapColl(gobj);
}

void grTMewtwo_80222434(Ground_GObj* gobj) {}

static void stageGObj1_OnInit(Ground_GObj* gobj)
{
    Ground_InitMapCollAndAnim(gobj);
}

bool grTMewtwo_80222488(Ground_GObj* gobj)
{
    return false;
}

static void stageGObj1_GObjProc(Ground_GObj* gobj)
{
    Ground_UpdateMapColl(gobj);
}

void grTMewtwo_802224B0(Ground_GObj* gobj) {}

static inline DynamicsDesc* inlineA0(int arg0)
{
    int temp = mpLineGetKind(arg0);
    if (temp == CollLine_Floor) {
        return yakumono_param->x0;
    } else if (temp == CollLine_Ceiling) {
        return yakumono_param->x4;
    } else if (temp == CollLine_RightWall) {
        return yakumono_param->x8;
    } else if (temp == CollLine_LeftWall) {
        return yakumono_param->xC;
    } else {
        return NULL;
    }
}

static inline DynamicsDesc* inlineA1(int arg0)
{
    int temp = mpLineGetKind(arg0);
    if (temp == CollLine_Floor) {
        return yakumono_param->x10;
    } else if (temp == CollLine_Ceiling) {
        return yakumono_param->x14;
    } else if (temp == CollLine_RightWall) {
        return yakumono_param->x18;
    } else if (temp == CollLine_LeftWall) {
        return yakumono_param->x1C;
    } else {
        return NULL;
    }
}

DynamicsDesc* grTMewtwo_802224B4(enum_t arg0)
{
    if (arg0 != -1) {
        int temp = mpJointFromLine(arg0);
        if (temp != -1) {
            if (temp == 0) {
                return inlineA0(arg0);
            } else if (temp == 1) {
                return inlineA1(arg0);
            }
        }
    }
    return NULL;
}

bool grTMewtwo_802225C8(Vec3* arg0, int arg1, HSD_JObj* arg2)
{
    return true;
}
