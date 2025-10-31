#include "groldkongo.h"

#include <platform.h>

#include "gr/granime.h"
#include "gr/ground.h"
#include "gr/inlines.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"

void grOldKongo_8020F468(bool arg) {}

/// #grOldKongo_8020F46C

void grOldKongo_8020F4E4(void) {}

/// #grOldKongo_8020F4E8

bool grOldKongo_8020F524(void)
{
    return false;
}

/// #grOldKongo_8020F52C

void grOldKongo_8020F618(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grOldKongo_8020F644(Ground_GObj* gobj)
{
    return false;
}

void grOldKongo_8020F64C(Ground_GObj* arg) {}

void grOldKongo_8020F650(Ground_GObj* arg) {}

/// #grOldKongo_8020F654

bool grOldKongo_8020F6B4(Ground_GObj* gobj)
{
    return false;
}

void grOldKongo_8020F6BC(Ground_GObj* gobj)
{
    Ground_801C2FE0(gobj);
    lb_800115F4();
}

void grOldKongo_8020F6E0(Ground_GObj* arg) {}

/// #grOldKongo_8020F6E4

bool grOldKongo_8020F880(Ground_GObj* gobj)
{
    return false;
}

/// #grOldKongo_8020F888

void grOldKongo_80210058(Ground_GObj* arg) {}

/// #grOldKongo_8021005C

bool grOldKongo_802100F4(Ground_GObj* gobj)
{
    return false;
}

/// #grOldKongo_802100FC

void grOldKongo_80210450(Ground_GObj* arg) {}

/// #fn_80210454

void grOldKongo_802105AC(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    if (gp->gv.inishie2.xC6 == 1) {
        gp->gv.inishie2.xC6 = 2;
    }
}

/// #grOldKongo_802105C8

/// #grOldKongo_80210650

DynamicsDesc* grOldKongo_80210780(enum_t gobj)
{
    return false;
}

bool grOldKongo_80210788(Vec3* a, int arg, HSD_JObj* joint)
{
    Vec3 b;

    lb_8000B1CC(joint, NULL, &b);

    if (a->y > b.y) {
        return true;
    } else {
        return false;
    }
}
