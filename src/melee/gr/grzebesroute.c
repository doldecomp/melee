#include "grzebesroute.h"

#include <platform.h>

#include "cm/camera.h"
#include "ft/ftlib.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "lb/lb_00F9.h"
#include "mp/mplib.h"

#include <baselib/gobj.h>
#include <baselib/random.h>

static struct {
    int x0;
    int x4;
}* grZe_Route_804D6A60;

extern Vec3 grZe_Route_803B83A0;

void grZebesRoute_8020B160(bool arg) {}

/// #grZebesRoute_8020B164
void grZebesRoute_8020B164(void)
{
    grZe_Route_804D6A60 = Ground_801C49F8();
    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 1;
    grZebesRoute_8020B260(0);
    grZebesRoute_8020B260(1);
    grZebesRoute_8020B260(2);
    Ground_801C39C0();
    Ground_801C3BB4();
}

void grZebesRoute_8020B1D4(void)
{
    grZebesRoute_8020B548();
}

/// #grZebesRoute_8020B1F4
void grZebesRoute_8020B1F4(void)
{
    int val;
    grZakoGenerator_801CAE04(NULL);
    val = grZe_Route_804D6A60->x4;
    if (val != 0) {
        val = HSD_Randi(grZe_Route_804D6A60->x4);
    } else {
        val = 0;
    }
    if (val == 0) {
        grZakoGenerator_801CAEB0(Ground_801C5840(), Ground_801C5940());
    }
}

bool grZebesRoute_8020B258(void)
{
    return false;
}

/// #grZebesRoute_8020B260

void grZebesRoute_8020B348(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grZebesRoute_8020B374(Ground_GObj* arg)
{
    return false;
}

void grZebesRoute_8020B37C(Ground_GObj* arg) {}

void grZebesRoute_8020B380(Ground_GObj* arg) {}

void grZebesRoute_8020B384(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grZebesRoute_8020B3B0(Ground_GObj* arg)
{
    return false;
}

void grZebesRoute_8020B3B8(Ground_GObj* arg) {}

void grZebesRoute_8020B3BC(Ground_GObj* arg) {}

void grZebesRoute_8020B3C0(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x8_callback = NULL;
    gp->xC_callback = NULL;
    mpJointSetCb1(1, gp, (mpLib_Callback) fn_8020B4D8);
    gp->gv.zebes2.xC4 = (s16) grZe_Route_804D6A60->x0;
}

bool grZebesRoute_8020B424(Ground_GObj* arg)
{
    return false;
}

void grZebesRoute_8020B42C(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    Vec3 pos = grZe_Route_803B83A0;
    HSD_GObj* fighter;
    s32 timer;

    fighter = Ground_801C57A4();
    if (fighter != NULL) {
        ftLib_80086644(fighter, &pos);
        if (pos.y < -50.0f) {
            pos.y = -50.0f;
        }
        pos.x = 0.0f;
        Ground_801C38BC(pos.x, pos.y);
    }

    timer = *(s16*) &gp->gv.zebes2.xC4;
    if (timer > 0) {
        gp->gv.zebes2.xC4 = timer - 1;
    } else {
        Camera_80030E44(1, NULL);
    }

    lb_800115F4();
}

void grZebesRoute_8020B4D4(Ground_GObj* arg) {}

/// #fn_8020B4D8

/// #grZebesRoute_8020B548

DynamicsDesc* grZebesRoute_8020B854(enum_t arg)
{
    return false;
}

bool grZebesRoute_8020B85C(Vec3* arg, int arg0, HSD_JObj* jobj)
{
    return true;
}
