#include <platform.h>

#include "gryorster.h"

#include "gr/grdisplay.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "lb/lb_00F9.h"
#include "mp/mplib.h"

#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>

StageCallbacks grYt_803E5198[2] = {
    { grYorster_80202124, grYorster_80202150, grYorster_80202158,
      grYorster_8020215C, NULL },
    { grYorster_802021AC, grYorster_8020224C, grYorster_80202254,
      grYorster_802022A0, 0xC0000000 }
};

StageData grYt_803E51CC = {
    11,
    grYt_803E5198,
    "/GrYt.dat",
    grYorster_80201FA4,
    grYorster_80201FA0,
    grYorster_8020200C,
    grYorster_80202010,
    grYorster_80202034,
    grYorster_80202B5C,
    grYorster_80202B64,
    (1 << 0),
    NULL,
    0,
};

typedef struct grYt_804D6A20_t {
    void* x0;
} grYt_804D6A20_t;
grYt_804D6A20_t grYt_804D6A20;

void grYorster_80201FA0(int unused)
{
    return;
}

void grYorster_80201FA4(void)
{
    grYt_804D6A20.x0 = Ground_801C49F8();
    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = true;
    grYorster_8020203C(0);
    grYorster_8020203C(1);

    Ground_801C39C0();
    Ground_801C3BB4();
}

void grYorster_8020200C(void)
{
    return;
}

void grYorster_80202010(void)
{
    grZakoGenerator_801CAE04(0);
}

bool grYorster_80202034(void)
{
    return false;
}

HSD_GObj* grYorster_8020203C(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grYt_803E5198[gobj_id];

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
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 221, gobj_id);
    }

    return gobj;
}

void grYorster_80202124(HSD_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grYorster_80202150(HSD_GObj* gobj)
{
    return false;
}

void grYorster_80202158(HSD_GObj* gobj)
{
    return;
}

void grYorster_8020215C(HSD_GObj* gobj)
{
    return;
}

void grYorster_80202160(HSD_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grYorster_802022A4();
    Ground_801C2FE0(gobj);
    mpLib_80058560();
    gp->gv.yorster.xC4 = 0;
}

void grYorster_802021AC(HSD_GObj* gobj)
{
    int _[2];

    Ground* gp = GET_GROUND(gobj);
    Ground_801C2ED0(GET_JOBJ(gobj), gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 4);
    grAnime_801C7FF8(gobj, 23, 7, 3, 0.0f, 1.0f);
    grAnime_801C7FF8(gobj, 26, 7, 3, 0.0f, 1.0f);
    Ground_801C10B8(gobj, grYorster_80202160);
    gp->gv.yorster.xC4 = 1;
}

bool grYorster_8020224C(HSD_GObj* gobj)
{
    return false;
}

void grYorster_80202254(HSD_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    if (gp->gv.yorster.xC4 == 0) {
        grYorster_8020266C(gobj);
    }
    lb_800115F4();
    Ground_801C2FE0(gobj);
}

void grYorster_802022A0(HSD_GObj* gobj) {}

void grYorster_802022A4(void) {}

/// #grYorster_80202428

/// #grYorster_802024F0

/// #grYorster_8020266C

DynamicsDesc* grYorster_80202B5C(enum_t unused)
{
    return NULL;
}

bool grYorster_80202B64(Vec3* a, int _, HSD_JObj* joint)
{
    return true;
}
