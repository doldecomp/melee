#include <gr/grtpurin.h>

#include <gr/ground.h>
#include <gr/grzakogenerator.h>
#include <gr/inlines.h>
#include <gr/types.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/types.h>
#include <melee/mp/mplib.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/jobj.h>

static void stageGObj2_OnInit(Ground_GObj* gobj);
static void stageGObj1_OnInit(Ground_GObj* gobj);
static void stageGObj1_GObjProc(Ground_GObj* gobj);

StageCallbacks grTPr_StageCallbacks[] = {
    { grTPurin_802232F4, grTPurin_80223320, grTPurin_80223328,
      grTPurin_8022332C, 0 },
    { stageGObj1_OnInit, grTPurin_802234CC, stageGObj1_GObjProc,
      grTPurin_802234F4, 0 },
    { stageGObj2_OnInit, grTPurin_80223380, grTPurin_80223388,
      grTPurin_80223478, 0xC0000000 },
    { NULL, NULL, NULL, NULL, 0 }
};

StageData grTPr_StageData = {
    Gr_Kind_TPurin,
    grTPr_StageCallbacks,
    "/GrTPr.dat",
    grTPurin_80223164,
    grTPurin_80223160,
    grTpurin_UnkStage0_OnLoad,
    grTpurin_UnkStage0_OnStart,
    grTPurin_80223204,
    grTPurin_802234F8,
    grTPurin_80223578,
    (1 << 0),
};

typedef struct grTPrSpecialParams {
    DynamicsDesc* x0;
} grTPrSpecialParams;

static grTPrSpecialParams* yakumono_param;

void grTPurin_80223160(bool unused)
{
    return;
}

void grTPurin_80223164(void)
{
    yakumono_param = Ground_GetYakumonoParam();
    Ground_InitTargetStage(grTPurin_8022320C);
}

void grTpurin_UnkStage0_OnLoad(void)
{
    return;
}

void grTpurin_UnkStage0_OnStart(void)
{
    grZakoGenerator_801CAE04(NULL);
}

bool grTPurin_80223204(void)
{
    return false;
}

HSD_GObj* grTPurin_8022320C(int id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grTPr_StageCallbacks[id];

    gobj = Ground_GetStageGObj(id);

    if (gobj != NULL) {
        Ground_SetupStageCallbacks(gobj, callbacks);
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 203, id);
    }

    return gobj;
}

void grTPurin_802232F4(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grTPurin_80223320(Ground_GObj* gobj)
{
    return false;
}

void grTPurin_80223328(Ground_GObj* gobj)
{
    return;
}

void grTPurin_8022332C(Ground_GObj* gobj)
{
    return;
}

static void stageGObj2_OnInit(Ground_GObj* gobj)
{
    Ground_InitMapCollAndAnim(gobj);
}

bool grTPurin_80223380(Ground_GObj* gobj)
{
    return false;
}

void grTPurin_80223388(Ground_GObj* gobj)
{
    s16* pos;
    HSD_JObj* jobj;
    int res;
    Vec3 vec;
    s16 values[8] = { 0x0037, 0x0039, 0x003B, 0x003D,
                      0x003F, 0x0041, 0x0043, 0xFFFF };
    s32 value;

    for (pos = &values[0]; (value = *pos) != -1; ++pos) {
        res = Ground_801C32D4(2, value);
        if (res != -1) {
            jobj = Ground_801C3FA4(gobj, value);
            if ((jobj != NULL) &&
                (lb_8000B1CC(jobj, NULL, &vec), (vec.x < 130.0f)))
            {
                mpJointListAdd(res);
            } else {
                mpLib_80057BC0(res);
            }
        }
    }
    Ground_UpdateWindAndMapColl(gobj);
}

void grTPurin_80223478(Ground_GObj* gobj)
{
    return;
}

static void stageGObj1_OnInit(Ground_GObj* gobj)
{
    Ground_InitMapCollAndAnim(gobj);
}

bool grTPurin_802234CC(Ground_GObj* gobj)
{
    return false;
}

static void stageGObj1_GObjProc(Ground_GObj* gobj)
{
    Ground_UpdateMapColl(gobj);
}

void grTPurin_802234F4(Ground_GObj* gobj)
{
    return;
}

DynamicsDesc* grTPurin_802234F8(enum_t arg0)
{
    enum_t i;

    if (arg0 != -1) {
        i = mpJointFromLine(arg0);
        if (i != -1) {
            mpLineGetKind(arg0);
            if (i == (0 << 0)) {
                return yakumono_param->x0;
            }
            if (i == (1 << 0)) {
                return yakumono_param->x0;
            }
        }
    }
    return 0;
}

bool grTPurin_80223578(Vec3* vec, int arg1, HSD_JObj* jobj)
{
    return true;
}
