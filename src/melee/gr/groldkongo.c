#include <platform.h>

#include "groldkongo.h"

#include "gr/granime.h"
#include "gr/ground.h"
#include "gr/inlines.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"

void grOldKongo_8020F468(void) {}

/// #grOldKongo_8020F46C

void grOldKongo_8020F4E4(void) {}

/// #grOldKongo_8020F4E8

bool grOldKongo_8020F524(HSD_GObj* gobj)
{
    return false;
}

/// #grOldKongo_8020F52C

void grOldKongo_8020F618(HSD_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grOldKongo_8020F644(HSD_GObj* gobj)
{
    return false;
}

void grOldKongo_8020F64C(void) {}

void grOldKongo_8020F650(void) {}

/// #grOldKongo_8020F654

bool grOldKongo_8020F6B4(HSD_GObj* gobj)
{
    return false;
}

void grOldKongo_8020F6BC(HSD_GObj* gobj)
{
    Ground_801C2FE0(gobj);
    lb_800115F4();
}

void grOldKongo_8020F6E0(void) {}

/// #grOldKongo_8020F6E4

bool grOldKongo_8020F880(HSD_GObj* gobj)
{
    return false;
}

/// #grOldKongo_8020F888

void grOldKongo_80210058(void) {}

/// #grOldKongo_8021005C

bool grOldKongo_802100F4(HSD_GObj* gobj)
{
    return false;
}

/// #grOldKongo_802100FC

void grOldKongo_80210450(void) {}

/// #fn_80210454

/// #grOldKongo_802105AC

/// #grOldKongo_802105C8

/// #grOldKongo_80210650

bool grOldKongo_80210780(HSD_GObj* gobj)
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
