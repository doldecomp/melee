#include "grkinokoroute.h"

#include "ground.h"

#include <platform.h>

#include "cm/camera.h"
#include "ft/ftlib.h"
#include "gr/inlines.h"

extern float grNKr_804DB830;

void grKinokoRoute_8020741C(bool arg) {}

/// #grKinokoRoute_80207420

void grKinokoRoute_80207490(void)
{
    Vec3 pos;
    HSD_GObj* gobj = Ground_801C57A4();
    if (gobj != NULL) {
        ftLib_80086644(gobj, &pos);
        Ground_801C38BC(pos.x, grNKr_804DB830 + pos.y);
        Camera_8002F3AC();
    }
}

/// #grKinokoRoute_802074D8

bool grKinokoRoute_80207544(void)
{
    return false;
}

/// #grKinokoRoute_8020754C

/// #grKinokoRoute_80207634

bool grKinokoRoute_802078E8(Ground_GObj* arg)
{
    return false;
}

/// #grKinokoRoute_802078F0

void grKinokoRoute_80207A94(Ground_GObj* arg) {}

void grKinokoRoute_80207A98(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138((HSD_GObj*) gobj, gp->map_id, 0);
    Ground_801C39C0();
    Ground_801C3BB4();
}

bool grKinokoRoute_80207ACC(Ground_GObj* arg)
{
    return false;
}

void grKinokoRoute_80207AD4(Ground_GObj* arg) {}

void grKinokoRoute_80207AD8(Ground_GObj* arg) {}

void grKinokoRoute_80207ADC(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x11_flags.b012 = 2;
}

bool grKinokoRoute_80207B20(Ground_GObj* arg)
{
    return false;
}

void grKinokoRoute_80207B28(Ground_GObj* arg) {}

void grKinokoRoute_80207B2C(Ground_GObj* arg) {}

/// #fn_80207B30

/// #grKinokoRoute_80207B5C

bool grKinokoRoute_80207C80(Ground_GObj* arg)
{
    return false;
}

/// #grKinokoRoute_80207C88

void grKinokoRoute_80208368(Ground_GObj* arg) {}

/// #grKinokoRoute_8020836C

bool fn_80208480(bool arg)
{
    if (arg == 1) {
        Ground_801C5740(arg);
        return 1;
    }
    return 0;
}

/// #fn_802084B4

/// #grKinokoRoute_80208564

/// #fn_80208660

/// #grKinokoRoute_802086EC

DynamicsDesc* grKinokoRoute_80208754(enum_t arg)
{
    return false;
}

/// #grKinokoRoute_8020875C
