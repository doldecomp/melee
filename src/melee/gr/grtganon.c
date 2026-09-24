#include <gr/grtganon.h>

#include <melee/mp/forward.h>

#include <gr/ground.h>
#include <gr/grzakogenerator.h>
#include <gr/inlines.h>
#include <gr/types.h>
#include <melee/lb/types.h>
#include <melee/mp/mplib.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjproc.h>

static void stageGObj2_OnInit(Ground_GObj* gobj);
static void stageGObj2_GObjProc(Ground_GObj* gobj);
static void stageGObj1_OnInit(Ground_GObj* gobj);
static void stageGObj1_GObjProc(Ground_GObj* gobj);

StageCallbacks grTGn_StageCallbacks[] = {
    { grTGanon_8022486C, grTGanon_80224898, grTGanon_802248A0,
      grTGanon_802248A4, 0 },
    { stageGObj1_OnInit, grTGanon_80224988, stageGObj1_GObjProc,
      grTGanon_802249B0, 0 },
    { stageGObj2_OnInit, grTGanon_802248F8, stageGObj2_GObjProc,
      grTGanon_80224934, 0xC0000000 },
    { NULL, NULL, NULL, NULL, 0 }
};

StageData grTGn_StageData = {
    Gr_Kind_TGanon,
    grTGn_StageCallbacks,
    "/GrTGn.dat",
    grTGanon_802246DC,
    grTGanon_802246D8,
    grTganon_UnkStage0_OnLoad,
    grTganon_UnkStage0_OnStart,
    grTGanon_8022477C,
    grTGanon_802249B4,
    grTGanon_80224A4C,
    (1 << 0),
};

typedef struct grTGn_YakumonoParam {
    DynamicsDesc* x0;
    DynamicsDesc* x4;
    DynamicsDesc* x8;
} grTGn_YakumonoParam;

static grTGn_YakumonoParam* yakumono_param;

void grTGanon_802246D8(bool unused)
{
    return;
}

void grTGanon_802246DC(void)
{
    yakumono_param = Ground_GetYakumonoParam();
    Ground_InitTargetStage(grTGanon_80224784);
}

void grTganon_UnkStage0_OnLoad(void)
{
    return;
}

void grTganon_UnkStage0_OnStart(void)
{
    grZakoGenerator_801CAE04(NULL);
}

bool grTGanon_8022477C(void)
{
    return false;
}

HSD_GObj* grTGanon_80224784(int id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grTGn_StageCallbacks[id];

    gobj = Ground_GetStageGObj(id);

    if (gobj != NULL) {
        Ground_SetupStageCallbacks(gobj, callbacks);
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 201, id);
    }

    return gobj;
}

void grTGanon_8022486C(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grTGanon_80224898(Ground_GObj* gobj)
{
    return false;
}

void grTGanon_802248A0(Ground_GObj* gobj)
{
    return;
}

void grTGanon_802248A4(Ground_GObj* gobj)
{
    return;
}

static void stageGObj2_OnInit(Ground_GObj* gobj)
{
    Ground_InitMapCollAndAnim(gobj);
}

bool grTGanon_802248F8(Ground_GObj* gobj)
{
    return false;
}

static void stageGObj2_GObjProc(Ground_GObj* gobj)
{
    Ground_UpdateWindAndMapColl(gobj);
}

void grTGanon_80224934(Ground_GObj* gobj)
{
    return;
}

static void stageGObj1_OnInit(Ground_GObj* gobj)
{
    Ground_InitMapCollAndAnim(gobj);
}

bool grTGanon_80224988(Ground_GObj* gobj)
{
    return false;
}

static void stageGObj1_GObjProc(Ground_GObj* gobj)
{
    Ground_UpdateMapColl(gobj);
}

void grTGanon_802249B0(Ground_GObj* gobj)
{
    return;
}

DynamicsDesc* grTGanon_802249B4(enum_t arg0)
{
    if (arg0 != -1) {
        enum_t i = mpJointFromLine(arg0);

        if (i != -1 && i == 0) {
            i = mpLineGetKind(arg0);

            if (i == CollLine_Ceiling) {
                return yakumono_param->x0;
            }

            if (i == CollLine_RightWall) {
                return yakumono_param->x4;
            }

            if (i == CollLine_LeftWall) {
                return yakumono_param->x8;
            }

            return NULL;
        }
    }

    return NULL;
}

bool grTGanon_80224A4C(Vec3* vec, int arg1, HSD_JObj* jobj)
{
    return true;
}
