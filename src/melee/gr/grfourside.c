#include <platform.h>

#include "grfourside.h"

#include "placeholder.h"

#include "gr/granime.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"

#include <dolphin/mtx.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>

static struct {
    int x0;
}* grFs_804D69D8;

void grFourside_801F2D0C(bool arg) {}

void grFourside_801F2D10(void)
{
    grFs_804D69D8 = Ground_801C49F8();
    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = true;
    grFourside_801F2DD0(0);
    grFourside_801F2DD0(4);
    grFourside_801F2DD0(6);
    grFourside_801F2DD0(2);
    grFourside_801F2DD0(1);
    grFourside_801F2DD0(3);
    grFourside_801F2DD0(5);
    Ground_801C39C0();
    Ground_801C3BB4();
}

void grFourside_801F2DA0(void) {}

void grFourside_801F2DA4(void)
{
    grZakoGenerator_801CAE04(0);
}

bool grFourside_801F2DC8(void)
{
    return false;
}

/// #grFourside_801F2DD0

void grFourside_801F2EBC(HSD_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grFourside_801F2EE8(void)
{
    return false;
}

void grFourside_801F2EF0(void) {}

void grFourside_801F2EF4(void) {}

void grFourside_801F2EF8(HSD_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grFourside_801F2F24(void)
{
    return false;
}

void grFourside_801F2F2C(void) {}

void grFourside_801F2F30(void) {}

/// #grFourside_801F2F34

bool grFourside_801F3070(void)
{
    return false;
}

void grFourside_801F3078(HSD_GObj* gobj)
{
    Ground_801C2FE0(gobj);
    lb_800115F4();
}

void grFourside_801F309C(void) {}

/// #fn_801F30A0

void grFourside_801F30F0(HSD_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    PAD_STACK(4);

    gp->x10_flags.b2 = 0;
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x11_flags.b012 = 2;
}

bool grFourside_801F3144(void)
{
    return false;
}

void grFourside_801F314C(void) {}

void grFourside_801F3150(void) {}

/// #grFourside_801F3154

bool grFourside_801F326C(void)
{
    return false;
}

/// #grFourside_801F3274

void grFourside_801F37F8(void) {}

/// #grFourside_801F37FC

bool grFourside_801F388C(void)
{
    return false;
}

/// #grFourside_801F3894

void grFourside_801F3B6C(void) {}

/// #grFourside_801F3B70

/// #grFourside_801F3C40

bool grFourside_801F3CC0(void)
{
    return false;
}

/// #grFourside_801F3CC8

void grFourside_801F3F0C(void) {}

int grFourside_801F3F10(void)
{
    HSD_GObj* gobj = Ground_801C2BA4(3);
    Ground* gp = GET_GROUND(gobj);
    if ((gp->gv.fourside.x0 == 1 && gp->gv.fourside.x1 == 0) ||
        (gp->gv.fourside.x0 == 3 && gp->gv.fourside.x4 <= 700))
    {
        return 1;
    }
    return 0;
}

/// #fn_801F3F74

DynamicsDesc* grFourside_801F41E0(enum_t arg)
{
    return NULL;
}

bool grFourside_801F41E8(Vec3* a, int arg, HSD_JObj* joint)
{
    u8 _[4];
    Vec3 b;

    lb_8000B1CC(joint, NULL, &b);

    if (a->y > b.y) {
        return true;
    } else {
        return false;
    }
}
