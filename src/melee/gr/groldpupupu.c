#include "groldpupupu.h"

#include "baselib/forward.h"
#include "forward.h"

#include "gr/granime.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"

#include <baselib/gobj.h>
#include <baselib/jobj.h>

static struct {
    int x0;
}* grOp_804D6A98;

static void* grOp_804D6A9C;

void grOldPupupu_802107DC(bool arg) {}

void grOldPupupu_802107E0(void)
{
    PAD_STACK(8);

    grOp_804D6A98 = Ground_801C49F8();
    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 1;
    grOldPupupu_802108B4(0);
    grOldPupupu_802108B4(3);
    grOldPupupu_802108B4(7);
    grOldPupupu_802108B4(5);
    grOldPupupu_802108B4(4);
    grOldPupupu_802108B4(6);
    grOldPupupu_802108B4(1);
    grOldPupupu_802108B4(8);
    Ground_801C39C0();
    Ground_801C3BB4();
    grOp_804D6A9C = NULL;
}

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

void grOldPupupu_80210B04(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x10_flags.b5 = 1;
}

bool grOldPupupu_80210B48(Ground_GObj* gobj)
{
    return false;
}

void grOldPupupu_80210B50(Ground_GObj* arg) {}

void grOldPupupu_80210B54(Ground_GObj* arg) {}

void grOldPupupu_80210B58(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);

    Ground_801C2ED0(jobj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x11_flags.b012 = 1;
}

bool grOldPupupu_80210BB8(Ground_GObj* gobj)
{
    return false;
}

void grOldPupupu_80210BC0(Ground_GObj* gobj)
{
    lb_800115F4();
}

void grOldPupupu_80210BE0(Ground_GObj* arg) {}

void grOldPupupu_80210BE4(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObjSetFlagsAll(GET_JOBJ(gobj), JOBJ_HIDDEN);
    gp->x11_flags.b012 = 2;
}

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

bool grOldPupupu_8021128C(Vec* vec, f32 maxX, f32 minX, f32 maxY, f32 minY)
{
    float maxY_actual;
    float maxX_actual;
    if (maxX > minX) {
        maxX_actual = maxX;
    } else {
        maxX_actual = minX;
        minX = maxX;
    }
    if (maxY > minY) {
        maxY_actual = maxY;
    } else {
        maxY_actual = minY;
        minY = maxY;
    }
    if (minX < vec->x && vec->x < maxX_actual) {
        if (minY < vec->y && vec->y < maxY_actual) {
            return true;
        }
    }
    return false;
}

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
