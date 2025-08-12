#include "gr/grtlink.h"

#include <platform.h>

#include "gr/granime.h"
#include "gr/grdisplay.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "gr/types.h"

#include "lb/forward.h"

#include "lb/lb_00F9.h"

#include <baselib/forward.h>

#include <dolphin/mtx.h>
#include <dolphin/os/OSError.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>

void grTLink_8022192C(bool);                  /* static */
void grTLink_80221930(void);                  /* static */
void grTlink_UnkStage0_OnLoad(void);          /* static */
void grTlink_UnkStage0_OnStart(void);         /* static */
bool grTLink_802219C8(void);                  /* static */
HSD_GObj* grTLink_802219D0(s32 arg0);         /* static */
void grTLink_80221AB8(Ground_GObj*);          /* static */
bool grTLink_80221AE4(Ground_GObj*);          /* static */
void grTLink_80221AEC(Ground_GObj*);          /* static */
void grTLink_80221AF0(Ground_GObj*);          /* static */
void grTLink_80221AF4(Ground_GObj*);          /* static */
bool grTLink_80221B44(Ground_GObj*);          /* static */
void grTLink_80221B4C(Ground_GObj*);          /* static */
void grTLink_80221B80(Ground_GObj*);          /* static */
void grTLink_80221B84(Ground_GObj*);          /* static */
bool grTLink_80221BD4(Ground_GObj*);          /* static */
void grTLink_80221BDC(Ground_GObj*);          /* static */
void grTLink_80221BFC(Ground_GObj*);          /* static */
DynamicsDesc* grTLink_80221C00(enum_t);       /* static */
bool grTLink_80221C08(Vec3*, int, HSD_JObj*); /* static */

static StageCallbacks grTLk_803E8D30[4] = {
    { grTLink_80221AB8, grTLink_80221AE4, grTLink_80221AEC, grTLink_80221AF0,
      0 },
    { grTLink_80221B84, grTLink_80221BD4, grTLink_80221BDC, grTLink_80221BFC,
      0 },
    { grTLink_80221AF4, grTLink_80221B44, grTLink_80221B4C, grTLink_80221B80,
      (1 << 31) | (1 << 30) },
    { NULL, NULL, NULL, NULL, 0 }
};

StageData grTLk_803E8D8C = {
    50,
    grTLk_803E8D30,
    "/GrTLk.dat",
    grTLink_80221930,
    grTLink_8022192C,
    grTlink_UnkStage0_OnLoad,
    grTlink_UnkStage0_OnStart,
    grTLink_802219C8,
    grTLink_80221C00,
    grTLink_80221C08,
    1,
};

void grTLink_8022192C(bool unk0) {}

void grTLink_80221930(void)
{
    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = true;

    grTLink_802219D0(0);
    grTLink_802219D0(1);
    grTLink_802219D0(2);
    Ground_801C39C0();
    Ground_801C3BB4();
    Ground_801C4210();
    Ground_801C42AC();
}

void grTlink_UnkStage0_OnLoad(void) {}

void grTlink_UnkStage0_OnStart(void)
{
    grZakoGenerator_801CAE04(0);
}

bool grTLink_802219C8(void)
{
    return 0;
}

HSD_GObj* grTLink_802219D0(s32 arg0)
{
    HSD_GObj* gobj;
    StageCallbacks* cb;
    Ground* gp;

    cb = &grTLk_803E8D30[arg0];
    gobj = Ground_801C14D0(arg0);
    if (gobj != NULL) {
        gp = gobj->user_data;
        gp->x8_callback = 0;
        gp->xC_callback = 0;
        GObj_SetupGXLink(gobj, &grDisplay_801C5DB0, 3, 0);
        if (cb->callback3 != 0U) {
            gp->x1C_callback = cb->callback3;
        }
        if (cb->callback0 != NULL) {
            cb->callback0(gobj);
        }
        if (cb->callback2 != 0U) {
            HSD_GObjProc_8038FD54(gobj, cb->callback2, 4);
        }
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grtlink.c", 0xC3, arg0);
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
