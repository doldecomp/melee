#include "baselib/forward.h"

#include "groldpupupu.h"

#include "gr/granime.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"

#include <baselib/gobj.h>
#include <baselib/jobj.h>

void grOldPupupu_802107DC(void) {}

/// #grOldPupupu_802107E0

void grOldPupupu_80210884(void) {}

void grOldPupupu_80210888(void)
{
    grZakoGenerator_801CAE04(NULL);
}

bool grOldPupupu_802108AC(HSD_GObj* gobj)
{
    return false;
}

/// #grOldPupupu_802108B4

void grOldPupupu_8021099C(HSD_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grOldPupupu_802109C8(HSD_GObj* gobj)
{
    return false;
}

void grOldPupupu_802109D0(void) {}

void grOldPupupu_802109D4(void) {}

/// #grOldPupupu_802109D8

bool grOldPupupu_80210A1C(HSD_GObj* gobj)
{
    return false;
}

/// #grOldPupupu_80210A24

void grOldPupupu_80210B00(void) {}

/// #grOldPupupu_80210B04

bool grOldPupupu_80210B48(HSD_GObj* gobj)
{
    return false;
}

void grOldPupupu_80210B50(void) {}

void grOldPupupu_80210B54(void) {}

/// #grOldPupupu_80210B58

bool grOldPupupu_80210BB8(HSD_GObj* gobj)
{
    return false;
}

void grOldPupupu_80210BC0(HSD_GObj* gobj)
{
    lb_800115F4();
}

void grOldPupupu_80210BE0(void) {}

/// #grOldPupupu_80210BE4

bool grOldPupupu_80210C2C(HSD_GObj* gobj)
{
    return false;
}

void grOldPupupu_80210C34(HSD_GObj* gobj)
{
    PAD_STACK(8);
    if (grAnime_801C83D0(gobj, 0, 7) != 0) {
        Ground_801C4A08(gobj);
    }
}

void grOldPupupu_80210C78(void) {}

/// #grOldPupupu_80210C7C

bool grOldPupupu_80210D08(HSD_GObj* gobj)
{
    return false;
}

/// #grOldPupupu_80210D10

void grOldPupupu_8021110C(void) {}

/// #grOldPupupu_80211110

bool grOldPupupu_8021118C(HSD_GObj* gobj)
{
    return false;
}

void grOldPupupu_80211194(void) {}

void grOldPupupu_80211198(void) {}

/// #grOldPupupu_8021119C

bool grOldPupupu_80211284(HSD_GObj* gobj)
{
    return false;
}

/// #grOldPupupu_8021128C

/// #fn_802112F4

/// #grOldPupupu_802113E0

void grOldPupupu_80211C0C(void) {}

void grOldPupupu_80211C10(void) {}

bool grOldPupupu_80211C14(HSD_GObj* gobj)
{
    return false;
}

/// #grOldPupupu_80211C1C

void grOldPupupu_80211C9C(void) {}

bool grOldPupupu_80211CA0(HSD_GObj* gobj)
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
