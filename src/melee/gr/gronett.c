#include "gronett.h"

#include "types.h"

#include <platform.h>

#include "gr/grdisplay.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "lb/lb_00B0.h"
#include "un/un_2FC9.h"

#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>

StageCallbacks grOt_803E27E0[2] = {
    { NULL, NULL, NULL, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL },
};

static struct {
    int x0;
}* grOt_804D69C0;

void grOnett_801E3734(bool arg) {}

void grOnett_801E3738(void)
{
    grOt_804D69C0 = Ground_801C49F8();
    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = true;
    grOnett_801E37F4(0);
    grOnett_801E37F4(2);
    grOnett_801E37F4(5);
    grOnett_801E37F4(4);
    grOnett_801E37F4(3);
    un_802FD8A0(grOnett_801E56FC());
    un_802FD65C();
    Ground_801C39C0();
    Ground_801C3BB4();
}

void grOnett_801E37C4(void) {}

void grOnett_801E37C8(void)
{
    grZakoGenerator_801CAE04(NULL);
}

bool grOnett_801E37EC(void)
{
    return false;
}

/// #grOnett_801E37F4
HSD_GObj* grOnett_801E37F4(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grOt_803E27E0[gobj_id];

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
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 235, gobj_id);
    }

    return gobj;
}

void grOnett_801E38DC(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x11_flags.b012 = 2;
}

bool grOnett_801E3920(Ground_GObj* gobj)
{
    return false;
}

void grOnett_801E3928(Ground_GObj* gobj) {}

void grOnett_801E392C(Ground_GObj* gobj) {}

/// #grOnett_801E3930

/// #grOnett_801E3A34

bool grOnett_801E3C58(Ground_GObj* gobj)
{
    return false;
}

/// #grOnett_801E3C60

void grOnett_801E3CE0(Ground_GObj* gobj) {}

/// #grOnett_801E3CE4

bool grOnett_801E3D98(Ground_GObj* gobj)
{
    return false;
}

/// #grOnett_801E3DA0

void grOnett_801E40E0(Ground_GObj* gobj) {}

/// #grOnett_801E40E4

void grOnett_801E41B0(HSD_GObj* gobj)
{
    GET_GROUND(gobj)->gv.onett.x0_b0 = false;
}

/// #grOnett_801E41C8

bool grOnett_801E43D8(Ground_GObj* gobj)
{
    return false;
}

/// #grOnett_801E43E0

void grOnett_801E502C(Ground_GObj* gobj) {}

/// #grOnett_801E5030

/// #grOnett_801E5140

/// #grOnett_801E5194

/// #grOnett_801E5214

/// #grOnett_801E54B4

/// #grOnett_801E5538

/// #grOnett_801E56FC

DynamicsDesc* grOnett_801E5760(enum_t arg)
{
    return false;
}

bool grOnett_801E5768(Vec3* a, int b, HSD_JObj* jobj)
{
    Vec3 vec;
    lb_8000B1CC(jobj, NULL, &vec);
    if (a->y > vec.y) {
        return true;
    } else {
        return false;
    }
}
