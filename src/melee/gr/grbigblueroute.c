#include "grbigblueroute.h"

#include <platform.h>

#include "baselib/memory.h"
#include "cm/camera.h"
#include "ft/ftlib.h"
#include "gm/gm_16AE.h"
#include "gr/grdisplay.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "gr/types.h"
#include "if/ifhazard.h"
#include "lb/lb_00B0.h"

#include <dolphin/os.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>
#include <baselib/random.h>

extern StageCallbacks grBb_Route_803E5E78[];

static struct {
    int x0;
}* grBb_Route_804D6A68;

void grBigBlueRoute_8020B864(bool arg)
{
    HSD_GObj* gobj;
    gobj = Ground_801C2BA4(0x1F);
    if (gobj != NULL) {
        Ground_801C4A08(gobj);
    }
    grBigBlueRoute_8020B9D4(1);
}

void grBigBlueRoute_8020B89C(void)
{
    grBb_Route_804D6A68 = Ground_801C49F8();
    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 1;
    grBigBlueRoute_8020B9D4(0);
    grBigBlueRoute_8020B9D4(0x20);
    grBigBlueRoute_8020B9D4(0x1F);
    Ground_801C39C0();
    Ground_801C3BB4();
    Camera_80030AE0(true);
    un_802FD8E8(grBigBlueRoute_8020DE48());
    un_802FD65C();
}

void grBigBlueRoute_8020B920(void)
{
    Point3d sp8;
    HSD_GObj* temp_r3;

    temp_r3 = Ground_801C57A4();
    if (temp_r3 != NULL) {
        ftLib_80086644(temp_r3, &sp8);
        grBigBlueRoute_8020DED4(&sp8);
        Camera_8002F3AC();
    }
}

void grBigBlueRoute_8020B95C(void)
{
    int val;
    grZakoGenerator_801CAE04(NULL);
    if (gm_8016B3D8() == false) {
        return;
    }

    val = grBb_Route_804D6A68->x0;
    if (val != 0) {
        val = HSD_Randi(grBb_Route_804D6A68->x0);
    } else {
        val = 0;
    }
    if (val == 0) {
        grZakoGenerator_801CAEB0(Ground_801C5840(), Ground_801C5940());
    }
}

bool grBigBlueRoute_8020B9CC(void)
{
    return false;
}

HSD_GObj* grBigBlueRoute_8020B9D4(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grBb_Route_803E5E78[gobj_id];

    gobj = Ground_801C14D0(gobj_id);

    if (gobj != NULL) {
        Ground* gp = gobj->user_data;
        gp->x8_callback = NULL;
        gp->xC_callback = NULL;
        GObj_SetupGXLink(gobj, grDisplay_801C5DB0, 3, 0);

        if (callbacks->callback3 != NULL) {
            gp->x1C_callback = callbacks->callback3;
        }

        if (callbacks->callback0 != NULL) {
            callbacks->callback0(gobj);
        }

        if (callbacks->callback2 != NULL) {
            HSD_GObjProc_8038FD54(gobj, callbacks->callback2, 4);
        }

    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grbigblueroute.c", 279,
                 gobj_id);
    }

    return gobj;
}

void grBigBlueRoute_8020BABC(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x11_flags.b012 = 2;
}

bool grBigBlueRoute_8020BB00(Ground_GObj* arg)
{
    return false;
}

void grBigBlueRoute_8020BB08(Ground_GObj* arg) {}

void grBigBlueRoute_8020BB0C(Ground_GObj* arg) {}

void grBigBlueRoute_8020BB10(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
    grAnime_801C77FC(gobj, 0, 7);
}

bool grBigBlueRoute_8020BB58(Ground_GObj* arg)
{
    return false;
}

void grBigBlueRoute_8020BB60(Ground_GObj* arg) {}

void grBigBlueRoute_8020BB64(Ground_GObj* arg) {}

void grBigBlueRoute_8020BB68(Ground_GObj* gobj)
{
    HSD_JObj *jobj, *jobj2, *jobj3, *jobj4, *jobj5, *jobj6;

    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
    grAnime_801C77FC(gobj, 0, 7);
    jobj6 = Ground_801C3FA4(gobj, 7);
    jobj5 = Ground_801C3FA4(gobj, 8);
    jobj4 = Ground_801C3FA4(gobj, 4);
    jobj3 = Ground_801C3FA4(gobj, 5);
    jobj2 = Ground_801C3FA4(gobj, 3);
    jobj = Ground_801C3FA4(gobj, 6);
    Ground_801C4E70(jobj, jobj2, jobj3, jobj4, jobj5, jobj6);
}

bool grBigBlueRoute_8020BC24(Ground_GObj* arg)
{
    return false;
}

void grBigBlueRoute_8020BC2C(Ground_GObj* arg) {}

void grBigBlueRoute_8020BC30(Ground_GObj* arg) {}

void grBigBlueRoute_8020BC34(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    gp->gv.bigblueroute.xC4 = grBigBlueRoute_8020B9D4(4);
}

/// #grBigBlueRoute_8020BC68

bool grBigBlueRoute_8020BF30(Ground_GObj* arg)
{
    return false;
}

/// #grBigBlueRoute_8020BF38

void grBigBlueRoute_8020C13C(Ground_GObj* arg) {}

/// #grBigBlueRoute_8020C140

bool grBigBlueRoute_8020C1D4(Ground_GObj* arg)
{
    return false;
}

void grBigBlueRoute_8020C1DC(Ground_GObj* gobj)
{
    grBigBlueRoute_8020C85C();
    grBigBlueRoute_8020CD20(gobj);
}

void grBigBlueRoute_8020C210(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_Free((void*) gp->gv.corneria.xC8);
}

/// #grBigBlueRoute_8020C238

/// #grBigBlueRoute_8020C530

/// #grBigBlueRoute_8020C85C

/// #grBigBlueRoute_8020CD20

int grBigBlueRoute_8020DA9C(struct grBigBlueRoute_8020DA9C_t* arg0)
{
    if (arg0 == NULL) {
        return 0;
    }
    return arg0->x8;
}

/// #grBigBlueRoute_8020DAB4

/// #grBigBlueRoute_8020DD64

/// #grBigBlueRoute_8020DE48

void fn_8020DEAC(void)
{
    Ground_801C53EC(0x77A12);
}

/// #grBigBlueRoute_8020DED4

DynamicsDesc* grBigBlueRoute_8020DF78(enum_t arg)
{
    return false;
}

bool grBigBlueRoute_8020DF80(Vec3* a, int arg, HSD_JObj* joint)
{
    Vec3 b;

    lb_8000B1CC(joint, NULL, &b);

    if (a->y > b.y + -3.0f) {
        return true;
    } else {
        return false;
    }
}
