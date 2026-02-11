#include "grshrineroute.h"

#include "ground.h"
#include "types.h"

#include <platform.h>

#include "gr/grdisplay.h"
#include "gr/grmaterial.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "lb/lb_00B0.h"

#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>
#include <baselib/random.h>

StageCallbacks grSh_Route_803E58F0[7] = {
    {
        grShrineRoute_802089AC,
        grShrineRoute_802089D8,
        grShrineRoute_802089E0,
        grShrineRoute_802089E4,
        0,
    },
    {
        grShrineRoute_8020A868,
        grShrineRoute_8020A894,
        grShrineRoute_8020A89C,
        grShrineRoute_8020A8A0,
        0,
    },
    {
        grShrineRoute_802089E8,
        grShrineRoute_80208A28,
        grShrineRoute_80208A30,
        grShrineRoute_80208A34,
        0,
    },
    {
        grShrineRoute_8020A868,
        grShrineRoute_8020A894,
        grShrineRoute_8020A89C,
        grShrineRoute_8020A8A0,
        0,
    },
    {
        grShrineRoute_80208D14,
        grShrineRoute_80208F0C,
        grShrineRoute_80208F70,
        grShrineRoute_80209AEC,
        0xC0000000,
    },
    {
        grShrineRoute_80209AF0,
        grShrineRoute_80209BE4,
        grShrineRoute_80209BEC,
        grShrineRoute_8020A100,
        0,
    },
    {
        grShrineRoute_8020A104,
        grShrineRoute_8020A214,
        grShrineRoute_8020A21C,
        grShrineRoute_8020A864,
        0,
    },
};

StageData grSh_Route_803E5988 = {
    (1 << 4),
    grSh_Route_803E58F0,
    "/GrNSr.dat",
    grShrineRoute_802087BC,
    grShrineRoute_802087B8,
    grShrineRoute_8020882C,
    grShrineRoute_80208850,
    grShrineRoute_802088B8,
    grShrineRoute_8020B104,
    grShrineRoute_8020B10C,
    (1 << 0),
    NULL,
    0,
};

static struct {
    int x0;
    int x4;
    int x8;
    int xC;
    int x10;
    int x14;
    int x18;
    int x1C;
    int x20;
    int x24;
    int x28;
}* grSh_Route_804D6A58;

extern float grNKr_804DB868;

float grShrineRoute_802087B0(void)
{
    return grNKr_804DB868;
}

void grShrineRoute_802087B8(bool arg) {}

void grShrineRoute_802087BC(void)
{
    grSh_Route_804D6A58 = Ground_801C49F8();
    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 0;
    grShrineRoute_802088C0(0);
    grShrineRoute_802088C0(4);
    grShrineRoute_802088C0(2);
    Ground_801C39C0();
    Ground_801C3BB4();
    grShrineRoute_8020B0AC();
}

void grShrineRoute_8020882C(void)
{
    grShrineRoute_802088C0(6);
}

void grShrineRoute_80208850(void)
{
    int val;
    grZakoGenerator_801CAE04(&grSh_Route_804D6A58->x28);
    val = grSh_Route_804D6A58->x24;
    if (val != 0) {
        val = HSD_Randi(grSh_Route_804D6A58->x24);
    } else {
        val = 0;
    }
    if (val == 0) {
        grZakoGenerator_801CAEB0(Ground_801C5840(), Ground_801C5940());
    }
}

bool grShrineRoute_802088B8(void)
{
    return false;
}

HSD_GObj* grShrineRoute_802088C0(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grSh_Route_803E58F0[gobj_id];

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
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 271, gobj_id);
    }

    return gobj;
}

void grShrineRoute_802089AC(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grShrineRoute_802089D8(Ground_GObj* arg)
{
    return false;
}

void grShrineRoute_802089E0(Ground_GObj* arg) {}

void grShrineRoute_802089E4(Ground_GObj* arg) {}

void grShrineRoute_802089E8(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
    grMaterial_801C94D8(jobj);
}

bool grShrineRoute_80208A28(Ground_GObj* arg)
{
    return false;
}

void grShrineRoute_80208A30(Ground_GObj* arg) {}

void grShrineRoute_80208A34(Ground_GObj* arg) {}

/// #fn_80208A38

/// #grShrineRoute_80208D14

bool grShrineRoute_80208F0C(Ground_GObj* arg)
{
    return false;
}

bool grShrineRoute_80208F14(void)
{
    HSD_GObj* gobj;
    Ground* gp;

    gobj = Ground_801C2BA4(4);
    if (gobj != NULL) {
        gp = GET_GROUND(gobj);
        if (gp != NULL) {
            if (gp->gv.shrineroute.xCA != 0) {
                if (gp->gv.shrineroute.xCC != 0) {
                    return true;
                }
            }
        }
    }
    return false;
}

/// #grShrineRoute_80208F70

void grShrineRoute_80209AEC(Ground_GObj* arg) {}

/// #grShrineRoute_80209AF0

bool grShrineRoute_80209BE4(Ground_GObj* arg)
{
    return false;
}

/// #grShrineRoute_80209BEC

void grShrineRoute_8020A100(Ground_GObj* arg) {}

/// #grShrineRoute_8020A104

bool grShrineRoute_8020A214(Ground_GObj* arg)
{
    return false;
}

/// #grShrineRoute_8020A21C

void grShrineRoute_8020A864(Ground_GObj* arg) {}

void grShrineRoute_8020A868(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grShrineRoute_8020A894(Ground_GObj* arg)
{
    return false;
}

void grShrineRoute_8020A89C(Ground_GObj* arg) {}

void grShrineRoute_8020A8A0(Ground_GObj* arg) {}

/// #grShrineRoute_8020A8A4

/// #grShrineRoute_8020AA40

/// #grShrineRoute_8020AB58

/// #grShrineRoute_8020AC44

bool fn_8020AD24(bool arg)
{
    if (arg == 1) {
        Ground_801C5740(arg);
        return 1;
    }
    return 0;
}

/// #fn_8020AD58

/// #fn_8020AE08

/// #grShrineRoute_8020AF38

/// #grShrineRoute_8020B020

/// #grShrineRoute_8020B0AC

DynamicsDesc* grShrineRoute_8020B104(enum_t arg)
{
    return false;
}

bool grShrineRoute_8020B10C(Vec3* a, int b, HSD_JObj* jobj)
{
    Vec3 vec;
    lb_8000B1CC(jobj, NULL, &vec);
    if (a->y > vec.y) {
        return true;
    } else {
        return false;
    }
}
