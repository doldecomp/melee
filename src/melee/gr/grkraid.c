#include <platform.h>

#include "baselib/forward.h"

#include "grkraid.h"

#include "gr/granime.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"

#include <baselib/gobj.h>
#include <baselib/jobj.h>

static grKr_804D6A08_t* grKr_804D6A08;

void grKraid_801FDFF8(void) {}

void grKraid_801FDFFC(grKr_804D6A08_t* arg)
{
    HSD_GObj* gobj;

    grKr_804D6A08 = Ground_801C49F8();
    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = true;
    grKraid_801FE0C4(0);
    grKraid_801FE0C4(2);
    grKraid_801FE0C4(3);
    gobj = grKraid_801FE0C4(4);
    HSD_JObjSetFlagsAll(GET_JOBJ(gobj), 0x10);
    gobj = grKraid_801FE0C4(1);
    HSD_JObjSetFlagsAll(GET_JOBJ(gobj), 0x10);
    Ground_801C39C0();
    Ground_801C3BB4();
}

void grKraid_801FE094(void) {}

void grKraid_801FE098(void)
{
    grZakoGenerator_801CAE04(0);
}

bool grKraid_801FE0BC(void)
{
    return false;
}

/// #grKraid_801FE0C4

/// #grKraid_801FE1B0

bool grKraid_801FE1DC(void)
{
    return false;
}

void grKraid_801FE1E4(void) {}

void grKraid_801FE1E8(void) {}

/// #grKraid_801FE1EC

bool grKraid_801FE2C8(void)
{
    return false;
}

/// #grKraid_801FE2D0

void grKraid_801FE35C(void) {}

void grKraid_801FE360(HSD_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x11_flags.b012 = 2;
}

bool grKraid_801FE3A4(void)
{
    return false;
}

void grKraid_801FE3AC(void) {}

void grKraid_801FE3B0(void) {}

/// #grKraid_801FE3B4

bool grKraid_801FE438(void)
{
    return false;
}

/// #grKraid_801FE440

void grKraid_801FE6D4(void) {}

/// #grKraid_801FE6D8

/// #grKraid_801FE818

bool grKraid_801FE9F8(void)
{
    return false;
}

/// #grKraid_801FEA00

/// #grKraid_801FEE54

/// #grKraid_801FF068

/// #grKraid_801FF0E0

void grKraid_801FF14C(void) {}

void grKraid_801FF150(void) {}

bool grKraid_801FF154(void)
{
    return false;
}

bool grKraid_801FF15C(void)
{
    return true;
}
