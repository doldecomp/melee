#include "grtdonkey.h"

#include "ground.h"
#include "grzakogenerator.h"
#include "inlines.h"
#include "types.h"
#include <dolphin/mtx.h>
#include <sysdolphin/baselib/gobjproc.h>

/* 220228 */ static void grTDonkey_80220228(bool);
/* 22022C */ static void grTDonkey_OnInit(void);
/* 22029C */ static void grTdonkey_UnkStage0_OnLoad(void);
/* 2202A0 */ static void grTdonkey_UnkStage0_OnStart(void);
/* 2202C4 */ static bool grTDonkey_802202C4(void);
/* 2202CC */ static HSD_GObj* grTDonkey_802202CC(int gobj_id);
/* 2203B4 */ static void stageGObj0_OnInit(Ground_GObj* gobj);
/* 2203E0 */ static bool grTDonkey_802203E0(Ground_GObj*);
/* 2203E8 */ static void grTDonkey_802203E8(Ground_GObj*);
/* 2203EC */ static void grTDonkey_802203EC(Ground_GObj*);
/* 2203F0 */ static void stageGObj2_OnInit(Ground_GObj* gobj);
/* 220440 */ static bool grTDonkey_80220440(Ground_GObj*);
/* 220448 */ static void stageGObj2_GObjProc(Ground_GObj* gobj);
/* 22047C */ static void grTDonkey_8022047C(Ground_GObj*);
/* 220480 */ static void stageGObj1_OnInit(Ground_GObj* gobj);
/* 2204D0 */ static bool grTDonkey_802204D0(Ground_GObj*);
/* 2204D8 */ static void stageGObj1_GObjProc(Ground_GObj*);
/* 2204F8 */ static void grTDonkey_802204F8(Ground_GObj*);
/* 2204FC */ static DynamicsDesc* grTDonkey_802204FC(enum_t);
/* 220504 */ static bool grTDonkey_80220504(Vec3*, int, HSD_JObj*);

static StageCallbacks grTDk_StageCallbacks[] = {
    {
        stageGObj0_OnInit,
        grTDonkey_802203E0,
        grTDonkey_802203E8,
        grTDonkey_802203EC,
        0,
    },
    {
        stageGObj1_OnInit,
        grTDonkey_802204D0,
        stageGObj1_GObjProc,
        grTDonkey_802204F8,
        0,
    },
    {
        stageGObj2_OnInit,
        grTDonkey_80220440,
        stageGObj2_GObjProc,
        grTDonkey_8022047C,
        (1 << 30) | (1 << 31),
    },
    { 0 },
};

StageData grTDk_StageData = {
    Gr_Kind_TDonkey,
    grTDk_StageCallbacks,
    "/GrTDk.dat",
    grTDonkey_OnInit,
    grTDonkey_80220228,
    grTdonkey_UnkStage0_OnLoad,
    grTdonkey_UnkStage0_OnStart,
    grTDonkey_802202C4,
    grTDonkey_802204FC,
    grTDonkey_80220504,
    (1 << 0),
    NULL,
    0,
};

static void grTDonkey_80220228(bool arg0) {}

static void grTDonkey_OnInit(void)
{
    Ground_InitTargetStage(grTDonkey_802202CC);
}

static void grTdonkey_UnkStage0_OnLoad(void) {}

static void grTdonkey_UnkStage0_OnStart(void)
{
    grZakoGenerator_801CAE04(NULL);
}

static bool grTDonkey_802202C4(void)
{
    return false;
}

static HSD_GObj* grTDonkey_802202CC(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grTDk_StageCallbacks[gobj_id];

    gobj = Ground_GetStageGObj(gobj_id);

    if (gobj != NULL) {
        Ground_SetupStageCallbacks(gobj, callbacks);
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 0xc3, gobj_id);
    }

    return gobj;
}
static void stageGObj0_OnInit(Ground_GObj* gobj)
{
    Ground_StartMapAnim(gobj);
}

static bool grTDonkey_802203E0(Ground_GObj* arg0)
{
    return false;
}

static void grTDonkey_802203E8(Ground_GObj* arg0) {}

static void grTDonkey_802203EC(Ground_GObj* arg0) {}

static void stageGObj2_OnInit(Ground_GObj* gobj)
{
    Ground_InitMapCollAndAnim(gobj);
}

static bool grTDonkey_80220440(Ground_GObj* arg0)
{
    return false;
}

static void stageGObj2_GObjProc(Ground_GObj* gobj)
{
    Ground_UpdateWindAndMapColl(gobj);
}

static void grTDonkey_8022047C(Ground_GObj* arg0) {}

static void stageGObj1_OnInit(Ground_GObj* gobj)
{
    Ground_InitMapCollAndAnim(gobj);
}

static bool grTDonkey_802204D0(Ground_GObj* arg0)
{
    return false;
}

static void stageGObj1_GObjProc(Ground_GObj* arg0)
{
    Ground_UpdateMapColl(arg0);
}

static void grTDonkey_802204F8(Ground_GObj* arg0) {}

static DynamicsDesc* grTDonkey_802204FC(enum_t arg0)
{
    return NULL;
}

static bool grTDonkey_80220504(Vec3* arg0, int arg1, HSD_JObj* arg2)
{
    return true;
}
