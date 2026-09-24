#include <gr/grtfox.h>

#include <gr/ground.h>
#include <gr/grzakogenerator.h>
#include <gr/inlines.h>
#include <gr/types.h>
#include <dolphin/mtx.h>
#include <melee/mp/mplib.h>
#include <sysdolphin/baselib/gobjproc.h>

struct grTFox_YakumonoParam {
    UNK_T unk0;
    UNK_T unk4;
    UNK_T unk8;
    UNK_T unkC;
};

static void grTFox_80220B80(bool);
static void grTFox_80220B84(void);
static void grTFox_UnkStage0_OnLoad(void);
static void grTFox_UnkStage0_OnStart(void);
static bool grTFox_80220C24(void);
static HSD_GObj* grTFox_80220C2C(int);
static void stageGObj0_OnInit(Ground_GObj*);
static bool grTFox_80220D40(Ground_GObj*);
static void grTFox_80220D48(Ground_GObj*);
static void grTFox_80220D4C(Ground_GObj*);
static void stageGObj2_OnInit(Ground_GObj*);
static bool grTFox_80220DA0(Ground_GObj*);
static void stageGObj2_GObjProc(Ground_GObj*);
static void grTFox_80220DDC(Ground_GObj*);
static void stageGObj1_OnInit(Ground_GObj*);
static bool grTFox_80220E30(Ground_GObj*);
static void stageGObj1_GObjProc(Ground_GObj*);
static void grTFox_80220E58(Ground_GObj*);
static DynamicsDesc* grTFox_80220E5C(enum_t);
static bool grTFox_80220F08(Vec3*, int, HSD_JObj*);

static struct grTFox_YakumonoParam* yakumono_param;

static StageCallbacks grTFx_StageCallbacks[4] = {
    { stageGObj0_OnInit, grTFox_80220D40, grTFox_80220D48, grTFox_80220D4C,
      0 },
    { stageGObj1_OnInit, grTFox_80220E30, stageGObj1_GObjProc, grTFox_80220E58,
      0 },
    { stageGObj2_OnInit, grTFox_80220DA0, stageGObj2_GObjProc, grTFox_80220DDC,
      (1 << 31) | (1 << 30) },
    { NULL, NULL, NULL, NULL, 0 }
};

StageData grTFx_StageData = {
    Gr_Kind_TFox,
    grTFx_StageCallbacks,
    "/GrTFx.dat",
    grTFox_80220B84,
    grTFox_80220B80,
    grTFox_UnkStage0_OnLoad,
    grTFox_UnkStage0_OnStart,
    grTFox_80220C24,
    grTFox_80220E5C,
    grTFox_80220F08,
    1,
};

void grTFox_80220B80(bool unk) {}

void grTFox_80220B84(void)
{
    yakumono_param = Ground_GetYakumonoParam();
    Ground_InitTargetStage(grTFox_80220C2C);
}

void grTFox_UnkStage0_OnLoad(void) {}

void grTFox_UnkStage0_OnStart(void)
{
    grZakoGenerator_801CAE04(NULL);
}

bool grTFox_80220C24(void)
{
    return false;
}

HSD_GObj* grTFox_80220C2C(int arg0)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grTFx_StageCallbacks[arg0];

    gobj = Ground_GetStageGObj(arg0);

    if (gobj != NULL) {
        Ground_SetupStageCallbacks(gobj, callbacks);
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 0xCB, arg0);
    }

    return gobj;
}

static void stageGObj0_OnInit(Ground_GObj* gobj)
{
    Ground_StartMapAnim(gobj);
}

bool grTFox_80220D40(Ground_GObj* gobj)
{
    return false;
}

void grTFox_80220D48(Ground_GObj* gobj) {}

void grTFox_80220D4C(Ground_GObj* gobj) {}

static void stageGObj2_OnInit(Ground_GObj* gobj)
{
    Ground_InitMapCollAndAnim(gobj);
}

bool grTFox_80220DA0(Ground_GObj* gobj)
{
    return false;
}

static void stageGObj2_GObjProc(Ground_GObj* gobj)
{
    Ground_UpdateWindAndMapColl(gobj);
}

void grTFox_80220DDC(Ground_GObj* gobj) {}

static void stageGObj1_OnInit(Ground_GObj* gobj)
{
    Ground_InitMapCollAndAnim(gobj);
}

bool grTFox_80220E30(Ground_GObj* gobj)
{
    return false;
}

static void stageGObj1_GObjProc(Ground_GObj* gobj)
{
    Ground_UpdateMapColl(gobj);
}

void grTFox_80220E58(Ground_GObj* gobj) {}

DynamicsDesc* grTFox_80220E5C(enum_t arg0)
{
    if (arg0 != -1) {
        enum_t i = mpJointFromLine(arg0);
        if (i != -1 && i == 1) {
            i = mpLineGetKind(arg0);
            if (i == CollLine_Floor) {
                return yakumono_param->unk0;
            }
            if (i == CollLine_Ceiling) {
                return yakumono_param->unk4;
            }
            if (i == CollLine_RightWall) {
                return yakumono_param->unk8;
            }
            if (i == CollLine_LeftWall) {
                return yakumono_param->unkC;
            }
            return NULL;
        }
    }
    return NULL;
}

bool grTFox_80220F08(Vec3* arg0, int arg1, HSD_JObj* arg2)
{
    return true;
}
