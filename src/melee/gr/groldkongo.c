#include "groldkongo.h"

#include <platform.h>

#include "forward.h"

#include "ft/ftdevice.h"
#include "gr/granime.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"

#include <baselib/gobj.h>

static struct {
    int x0;
}* grOk_804D6A90;

void grOldKongo_8020F468(bool arg) {}

/// #grOldKongo_8020F46C
void grOldKongo_8020F46C(void)
{
    grOk_804D6A90 = Ground_801C49F8();
    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 1;
    grOldKongo_8020F52C(0);
    grOldKongo_8020F52C(3);
    grOldKongo_8020F52C(1);
    grOldKongo_8020F52C(2);
    Ground_801C39C0();
    Ground_801C3BB4();
}

void grOldKongo_8020F4E4(void) {}

/// #grOldKongo_8020F4E8
void grOldKongo_8020F4E8(void)
{
    HSD_GObj* gobj;
    gobj = Ground_801C2BA4(1);
    ftCo_800C0764(gobj, 2, grOldKongo_80210454);
    grZakoGenerator_801CAE04(0);
}

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

void grOldKongo_8020F654(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Ground_801C2ED0(jobj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x10_flags.b5 = 1;
}

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

/// #grOldKongo_80210454

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
