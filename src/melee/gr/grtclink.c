#include "grtclink.h"

#include "gr/grdisplay.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "gr/types.h"
#include "lb/lb_00F9.h"
#include "lb/types.h"

#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>

static StageCallbacks grTCLink_803E86D0[] = {
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
    42,
    grTCLink_803E86D0,
    "/GrTCl.dat",
    grTCLink_8021FF48,
    grTCLink_8021FF44,
    grTCLink_8021FFB8,
    grTCLink_8021FFBC,
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
    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = true;

    grTCLink_8021FFE8(0);
    grTCLink_8021FFE8(1);
    grTCLink_8021FFE8(2);
    Ground_801C39C0();
    Ground_801C3BB4();
    Ground_801C4210();
    Ground_801C42AC();
}

void grTCLink_8021FFB8(void)
{
    return;
}

void grTCLink_8021FFBC(void)
{
    grZakoGenerator_801CAE04(0);
}

bool grTCLink_8021FFE0(void)
{
    return false;
}

HSD_GObj* grTCLink_8021FFE8(int id)
{
    HSD_GObj* gobj;
    StageCallbacks* cb = &grTCLink_803E86D0[id];
    gobj = Ground_801C14D0(id);

    if (gobj != NULL) {
        Ground* gp = (Ground*) HSD_GObjGetUserData(gobj);
        gp->x8_callback = NULL;
        gp->xC_callback = NULL;
        GObj_SetupGXLink(gobj, grDisplay_801C5DB0, 3, 0);

        if (cb->callback3 != NULL) {
            gp->x1C_callback = cb->callback3;
        }

        if (cb->callback0 != NULL) {
            cb->callback0(gobj);
        }

        if (cb->callback2 != NULL) {
            HSD_GObjProc_8038FD54(gobj, cb->callback2, 4);
        }
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grtclink.c", 195, id);
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
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* joint = (HSD_JObj*) gobj->hsd_obj;
    PAD_STACK(8);

    Ground_801C2ED0(joint, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, false);
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
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* joint = (HSD_JObj*) gobj->hsd_obj;
    PAD_STACK(8);

    Ground_801C2ED0(joint, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, false);
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
