#include "grbigblueroute.h"

#include <platform.h>

#include "baselib/memory.h"
#include "cm/camera.h"
#include "ft/ftlib.h"
#include "gr/grdisplay.h"
#include "gr/ground.h"
#include "gr/inlines.h"
#include "gr/types.h"

#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>

extern StageCallbacks grBb_Route_803E5E78[];

void grBigBlueRoute_8020B864(bool arg)
{
    HSD_GObj* gobj;
    gobj = Ground_801C2BA4(0x1F);
    if (gobj != NULL) {
        Ground_801C4A08(gobj);
    }
    grBigBlueRoute_8020B9D4(1);
}

/// #grBigBlueRoute_8020B89C

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

/// #grBigBlueRoute_8020B95C

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

/// #grBigBlueRoute_8020BB10

bool grBigBlueRoute_8020BB58(Ground_GObj* arg)
{
    return false;
}

void grBigBlueRoute_8020BB60(Ground_GObj* arg) {}

void grBigBlueRoute_8020BB64(Ground_GObj* arg) {}

/// #grBigBlueRoute_8020BB68

bool grBigBlueRoute_8020BC24(Ground_GObj* arg)
{
    return false;
}

void grBigBlueRoute_8020BC2C(Ground_GObj* arg) {}

void grBigBlueRoute_8020BC30(Ground_GObj* arg) {}

/// #fn_8020BC34

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

/// #grBigBlueRoute_8020DF80
