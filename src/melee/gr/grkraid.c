#include "grkraid.h"

#include "types.h"

#include <platform.h>

#include "baselib/forward.h"

#include "gr/granime.h"
#include "gr/grdisplay.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"

#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>

S16Vec3 grKr_803E4C78[] = { { 0, 3, 12 }, { 1, 3, 12 }, { 2, 3, 12 },
                            { 3, 3, 12 }, { 4, 3, 12 }, { 5, 3, 12 } };

StageCallbacks grKr_803E4C9C[5] = {
    { grKraid_801FE1B0, grKraid_801FE1DC, grKraid_801FE1E4, grKraid_801FE1E8,
      0 },
    { grKraid_801FE1EC, grKraid_801FE2C8, grKraid_801FE2D0, grKraid_801FE35C,
      0 },
    { grKraid_801FE360, grKraid_801FE3A4, grKraid_801FE3AC, grKraid_801FE3B0,
      0 },
    { grKraid_801FE3B4, grKraid_801FE438, grKraid_801FE440, grKraid_801FE6D4,
      0xC0000000 },
    { grKraid_801FE818, grKraid_801FE9F8, grKraid_801FEA00, grKraid_801FF14C,
      0 }
};

StageData grKr_803E4D0C = {
    (1 << 3),
    grKr_803E4C9C,
    "/GrKr.dat",
    grKraid_801FDFFC,
    grKraid_801FDFF8,
    grKraid_801FE094,
    grKraid_801FE098,
    grKraid_801FE0BC,
    grKraid_801FF154,
    grKraid_801FF15C,
    (1 << 0),
    grKr_803E4C78,
    6,
};

static grKr_804D6A08_t* grKr_804D6A08;

void grKraid_801FDFF8(bool unused)
{
    return;
}

void grKraid_801FDFFC(void)
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

HSD_GObj* grKraid_801FE0C4(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grKr_803E4C9C[gobj_id];

    gobj = Ground_801C14D0(gobj_id);

    if (gobj != NULL) {
        Ground* gp = gobj->user_data;
        gp->x8_callback = NULL;
        gp->xC_callback = NULL;
        GObj_SetupGXLink(gobj, grDisplay_801C5DB0, 3, 0);
        if (callbacks->callback3 != NULL) {
            gp->x1C_callback = callbacks->callback3;
        }
        if (callbacks->callback0 != NULL) {
            callbacks->callback0(gobj);
        }
        if (callbacks->callback2 != NULL) {
            HSD_GObjProc_8038FD54(gobj, callbacks->callback2, 4);
        }
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 223, gobj_id);
    }

    return gobj;
}

void grKraid_801FE1B0(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grKraid_801FE1DC(Ground_GObj* gobj)
{
    return false;
}

void grKraid_801FE1E4(Ground_GObj* gobj)
{
    return;
}

void grKraid_801FE1E8(Ground_GObj* gobj)
{
    return;
}

/// #grKraid_801FE1EC

bool grKraid_801FE2C8(Ground_GObj* gobj)
{
    return false;
}

/// #grKraid_801FE2D0

void grKraid_801FE35C(Ground_GObj* gobj)
{
    return;
}

void grKraid_801FE360(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x11_flags.b012 = 2;
}

bool grKraid_801FE3A4(Ground_GObj* gobj)
{
    return false;
}

void grKraid_801FE3AC(Ground_GObj* gobj)
{
    return;
}

void grKraid_801FE3B0(Ground_GObj* gobj)
{
    return;
}

void grKraid_801FE3B4(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);

    Ground_801C2ED0(jobj, gp->map_id);
    gp->gv.kraid.x0 = 0;
    gp->gv.kraid.x4 = 0.0f;
    gp->gv.kraid.x8 = 0.0f;
    gp->gv.kraid.xC = 0.0f;
    grAnime_801C8138(gobj, gp->map_id, 0);
    grAnime_801C7FF8(gobj, 0xD, 0x7, 0x2, 0.0f, 1.0f);
}

bool grKraid_801FE438(Ground_GObj* gobj)
{
    return false;
}

/// #grKraid_801FE440

void grKraid_801FE6D4(Ground_GObj* gobj)
{
    return;
}

/// #grKraid_801FE6D8

/// #grKraid_801FE818

bool grKraid_801FE9F8(Ground_GObj* gobj)
{
    return false;
}

/// #grKraid_801FEA00

/// #grKraid_801FEE54

void grKraid_801FF068(HSD_GObj* gobj, int val)
{
    int temp;
    Ground* gp = GET_GROUND(gobj);
    PAD_STACK(8);

    gp->gv.kraid.x1 = val;
    grAnime_801C8138(gobj, gp->map_id, gp->gv.kraid.x1);
    temp = gp->gv.kraid.x1;
    gobj = Ground_801C2BA4(1);
    gp = GET_GROUND(gobj);
    gp->gv.kraid.x1 = temp;
    grAnime_801C8138(gobj, gp->map_id, gp->gv.kraid.x1);
    gp->gv.kraid.x0 = 1;
}

/// #grKraid_801FF0E0

void grKraid_801FF14C(Ground_GObj* gobj)
{
    return;
}

void grKraid_801FF150(void) {}

DynamicsDesc* grKraid_801FF154(enum_t unused)
{
    return false;
}

bool grKraid_801FF15C(Vec3* a, int _, HSD_JObj* joint)
{
    return true;
}
