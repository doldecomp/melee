#include "groldpupupu.h"

#include "baselib/forward.h"

#include "gr/granime.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"

#include <baselib/gobj.h>
#include <baselib/jobj.h>

void grOldPupupu_802107DC(bool arg) {}

/// #grOldPupupu_802107E0

void grOldPupupu_80210884(void) {}

void grOldPupupu_80210888(void)
{
    grZakoGenerator_801CAE04(NULL);
}

bool grOldPupupu_802108AC(void)
{
    return false;
}

/// #grOldPupupu_802108B4

void grOldPupupu_8021099C(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grOldPupupu_802109C8(Ground_GObj* gobj)
{
    return false;
}

void grOldPupupu_802109D0(Ground_GObj* arg) {}

void grOldPupupu_802109D4(Ground_GObj* arg) {}

/// #grOldPupupu_802109D8

bool grOldPupupu_80210A1C(Ground_GObj* gobj)
{
    return false;
}

/// #grOldPupupu_80210A24

void grOldPupupu_80210B00(Ground_GObj* arg) {}

/// #grOldPupupu_80210B04

bool grOldPupupu_80210B48(Ground_GObj* gobj)
{
    return false;
}

void grOldPupupu_80210B50(Ground_GObj* arg) {}

void grOldPupupu_80210B54(Ground_GObj* arg) {}

/// #grOldPupupu_80210B58

bool grOldPupupu_80210BB8(Ground_GObj* gobj)
{
    return false;
}

void grOldPupupu_80210BC0(Ground_GObj* gobj)
{
    lb_800115F4();
}

void grOldPupupu_80210BE0(Ground_GObj* arg) {}

/// #grOldPupupu_80210BE4

bool grOldPupupu_80210C2C(Ground_GObj* gobj)
{
    return false;
}

void grOldPupupu_80210C34(Ground_GObj* gobj)
{
    PAD_STACK(8);
    if (grAnime_801C83D0(gobj, 0, 7) != 0) {
        Ground_801C4A08(gobj);
    }
}

void grOldPupupu_80210C78(Ground_GObj* arg) {}

/// #grOldPupupu_80210C7C

bool grOldPupupu_80210D08(Ground_GObj* gobj)
{
    return false;
}

/// #grOldPupupu_80210D10

void grOldPupupu_8021110C(Ground_GObj* arg) {}

/// #grOldPupupu_80211110

bool grOldPupupu_8021118C(Ground_GObj* gobj)
{
    return false;
}

void grOldPupupu_80211194(Ground_GObj* arg) {}

void grOldPupupu_80211198(Ground_GObj* arg) {}

/// #grOldPupupu_8021119C

bool grOldPupupu_80211284(Ground_GObj* gobj)
{
    return false;
}

/// #grOldPupupu_8021128C

/// #fn_802112F4

/// #grOldPupupu_802113E0

void grOldPupupu_80211C0C(Ground_GObj* arg) {}

void grOldPupupu_80211C10(Ground_GObj* arg) {}

bool grOldPupupu_80211C14(Ground_GObj* gobj)
{
    return false;
}

/// #grOldPupupu_80211C1C

void grOldPupupu_80211C9C(Ground_GObj* arg) {}

DynamicsDesc* grOldPupupu_80211CA0(enum_t gobj)
{
    return false;
}

bool grOldPupupu_80211CA8(Vec3* a, int arg, HSD_JObj* joint)
{
    Vec3 b;

    lb_8000B1CC(joint, NULL, &b);

    if (a->y > b.y) {
        return true;
    } else {
        return false;
    }
}
