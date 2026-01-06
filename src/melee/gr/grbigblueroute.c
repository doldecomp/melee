#include "grbigblueroute.h"

#include <platform.h>

#include "baselib/memory.h"
#include "cm/camera.h"
#include "ft/ftlib.h"
#include "gr/inlines.h"

/// #grBigBlueRoute_8020B864

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

/// #grBigBlueRoute_8020B9D4

/// #grBigBlueRoute_8020BABC

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

/// #fn_8020DEAC

/// #grBigBlueRoute_8020DED4

DynamicsDesc* grBigBlueRoute_8020DF78(enum_t arg)
{
    return false;
}

/// #grBigBlueRoute_8020DF80
