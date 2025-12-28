#include "grrcruise.h"

#include "grzakogenerator.h"

#include <platform.h>

#include "gr/grlib.h"
#include "gr/inlines.h"
#include "lb/lb_00F9.h"

void grRCruise_801FF164(bool arg) {}

/// #grRCruise_801FF168

void grRCruise_801FF298(void) {}

void grRCruise_801FF29C(void)
{
    grZakoGenerator_801CAE04(0);
}

bool grRCruise_801FF2C0(void)
{
    return false;
}

/// #grRCruise_801FF2C8

void grRCruise_801FF3B4(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138((HSD_GObj*) gobj, gp->map_id, 0);
}

bool grRCruise_801FF3E0(Ground_GObj* arg)
{
    return false;
}

void grRCruise_801FF3E8(Ground_GObj* arg) {}

void grRCruise_801FF3EC(Ground_GObj* arg) {}

void grRCruise_801FF3F0(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x11_flags.b012 = 2;
}

bool grRCruise_801FF434(Ground_GObj* arg)
{
    return false;
}

void grRCruise_801FF43C(Ground_GObj* arg) {}

void grRCruise_801FF440(Ground_GObj* arg) {}

/// #fn_801FF444

/// #grRCruise_801FF5B4

bool grRCruise_801FF6CC(Ground_GObj* arg)
{
    return false;
}

void grRCruise_801FF6D4(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    if (*(int*)((u8*)gp + 0xD4) == 0) {
        grRCruise_80201588(gobj);
        grRCruise_8020071C(gobj);
        grRCruise_80200C04(gobj);
    }
    lb_800115F4();
    grRCruise_80201110(gobj);
    Ground_801C2FE0(gobj);
}

void grRCruise_801FF738(Ground_GObj* arg) {}

void grRCruise_801FF73C(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj;
    grAnime_801C8138(gobj, gp->map_id, 0);
    HSD_JObjSetFlagsAll(gobj->hsd_obj, 0x10);
    jobj = Ground_801C3FA4(gobj, 0x1F);
    HSD_JObjClearFlagsAll(jobj, 0x10);
}

bool grRCruise_801FF794(Ground_GObj* arg)
{
    return false;
}

void grRCruise_801FF79C(Ground_GObj* arg) {}

void grRCruise_801FF7A0(Ground_GObj* arg) {}

/// #grRCruise_801FF7A4

bool grRCruise_801FF8DC(Ground_GObj* arg)
{
    return false;
}

void grRCruise_801FF8E4(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grLib_801C9B8C(&gp->gv);
    Ground_801C2FE0(gobj);
}

void grRCruise_801FF920(Ground_GObj* arg) {}

/// #grRCruise_801FF924

bool grRCruise_801FFAD4(Ground_GObj* arg)
{
    return false;
}

/// #grRCruise_801FFADC

void grRCruise_80200070(Ground_GObj* arg) {}

/// #grRCruise_80200074

bool grRCruise_8020014C(Ground_GObj* arg)
{
    return false;
}

/// #grRCruise_80200154

void grRCruise_8020045C(Ground_GObj* arg) {}

/// #fn_80200460

/// #grRCruise_80200540

/// #fn_80200578

/// #grRCruise_8020071C

/// #grRCruise_80200B48

/// #grRCruise_80200C04

/// #fn_802010A4

/// #grRCruise_80201110

/// #grRCruise_80201288

/// #grRCruise_80201410

/// #grRCruise_80201588

/// #grRCruise_80201918

/// #grRCruise_80201988

/// #grRCruise_80201B60

/// #fn_80201BE0

DynamicsDesc* grRCruise_80201C50(enum_t arg)
{
    return false;
}

bool grRCruise_80201C58(Vec3* arg, int arg0, HSD_JObj* jobj)
{
    return true;
}
