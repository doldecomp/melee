#include "grtclink.h"

#include "gr/grdisplay.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "gr/types.h"
#include "lb/lbspdisplay.h"
#include "lb/types.h"

#include <dolphin/os/OSError.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>

static StageCallbacks grTCLink_StageCallbacks[] = {
    {
        grTCLink_802200D0,
        grTCLink_802200FC,
        grTCLink_80220104,
        grTCLink_80220108,
        0,
    },
    {
        grTCLink_8022019C,
        grTCLink_802201EC,
        grTCLink_802201F4,
        grTCLink_80220214,
        0,
    },
    {
        grTCLink_8022010C,
        grTCLink_8022015C,
        grTCLink_80220164,
        grTCLink_80220198,
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

StageData grTCLink_803E872C = {
    TCLINK,
    grTCLink_StageCallbacks,
    "/GrTCl.dat",
    grTCLink_8021FF48,
    grTCLink_8021FF44,
    grTclink_UnkStage0_OnLoad,
    grTclink_UnkStage0_OnStart,
    grTCLink_8021FFE0,
    grTCLink_80220218,
    grTCLink_80220220,
    (1 << 0),
};

void grTCLink_8021FF44(bool unused)
{
    return;
}

void grTCLink_8021FF48(void)
{
    Ground_InitTargetStage(grTCLink_8021FFE8);
}

void grTclink_UnkStage0_OnLoad(void)
{
    return;
}

void grTclink_UnkStage0_OnStart(void)
{
    grZakoGenerator_801CAE04(NULL);
}

bool grTCLink_8021FFE0(void)
{
    return false;
}

HSD_GObj* grTCLink_8021FFE8(int id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grTCLink_StageCallbacks[id];

    gobj = Ground_GetStageGObj(id);

    if (gobj != NULL) {
        Ground_SetupStageCallbacks(gobj, callbacks);
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 195, id);
    }

    return gobj;
}

void grTCLink_802200D0(Ground_GObj* gobj)
{
    Ground* gp = (Ground*) HSD_GObjGetUserData(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grTCLink_802200FC(Ground_GObj* gobj)
{
    return false;
}

void grTCLink_80220104(Ground_GObj* gobj)
{
    return;
}

void grTCLink_80220108(Ground_GObj* gobj)
{
    return;
}

void grTCLink_8022010C(Ground_GObj* gobj)
{
    Ground_JObjInline1(gobj);
}

bool grTCLink_8022015C(Ground_GObj* gobj)
{
    return false;
}

void grTCLink_80220164(Ground_GObj* gobj)
{
    lb_800115F4();
    Ground_801C2FE0(gobj);
}

void grTCLink_80220198(Ground_GObj* gobj)
{
    return;
}

void grTCLink_8022019C(Ground_GObj* gobj)
{
    Ground_JObjInline1(gobj);
}

bool grTCLink_802201EC(Ground_GObj* gobj)
{
    return false;
}

void grTCLink_802201F4(Ground_GObj* gobj)
{
    Ground_801C2FE0(gobj);
}

void grTCLink_80220214(Ground_GObj* gobj)
{
    return;
}

DynamicsDesc* grTCLink_80220218(enum_t unused)
{
    return NULL;
}

bool grTCLink_80220220(Vec3* vec, int arg1, HSD_JObj* jobj)
{
    return true;
}
