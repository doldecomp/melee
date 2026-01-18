#include "groldyoshi.h"

#include "types.h"

#include <platform.h>

#include "forward.h"

#include "gr/grdisplay.h"
#include "gr/grmaterial.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"

#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>

extern StageCallbacks grOy_803E6488[];

static struct {
    int x0;
}* grOy_804D6A88;

void grOldYoshi_8020E798(bool arg) {}

void grOldYoshi_8020E79C(void)
{
    grOy_804D6A88 = Ground_801C49F8();
    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 1;
    grOldYoshi_8020E854(0);
    grOldYoshi_8020E854(1);
    grOldYoshi_8020E854(4);
    grOldYoshi_8020E854(5);
    grOldYoshi_8020E854(2);
    grOldYoshi_8020E854(3);
    Ground_801C39C0();
    Ground_801C3BB4();
}

void grOldYoshi_8020E824(void) {}

void grOldYoshi_8020E828(void)
{
    grZakoGenerator_801CAE04(false);
}

bool grOldYoshi_8020E84C(void)
{
    return false;
}

HSD_GObj* grOldYoshi_8020E854(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grOy_803E6488[gobj_id];

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
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "groldyoshi.c", 206,
                 gobj_id);
    }

    return gobj;
}

void grOldYoshi_8020E93C(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grOldYoshi_8020E968(Ground_GObj* arg)
{
    return false;
}

void grOldYoshi_8020E970(Ground_GObj* arg) {}

void grOldYoshi_8020E974(Ground_GObj* arg) {}

void grOldYoshi_8020E978(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);

    grAnime_801C8138(gobj, gp->map_id, 0);
    grMaterial_801C8858(jobj, JOBJ_UNK_B27);
    grMaterial_801C8858(jobj, JOBJ_ROOT_XLU);
    gp->x11_flags.b012 = 2;
}

bool grOldYoshi_8020E9E0(Ground_GObj* arg)
{
    return false;
}

void grOldYoshi_8020E9E8(Ground_GObj* arg) {}

void grOldYoshi_8020E9EC(Ground_GObj* arg) {}

void grOldYoshi_8020E9F0(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);

    Ground_801C2ED0(jobj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x11_flags.b012 = 1;
    gp->x10_flags.b5 = 1;
}

bool grOldYoshi_8020EA5C(Ground_GObj* arg)
{
    return false;
}

void grOldYoshi_8020EA64(Ground_GObj* arg0)
{
    Ground_801C2FE0(arg0);
    lb_800115F4();
}

void grOldYoshi_8020EA88(Ground_GObj* arg) {}

void grOldYoshi_8020EA8C(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);

    Ground_801C2ED0(jobj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x11_flags.b012 = 1;
}

bool grOldYoshi_8020EAEC(Ground_GObj* arg)
{
    return false;
}

void grOldYoshi_8020EAF4(Ground_GObj* arg) {}

void grOldYoshi_8020EAF8(Ground_GObj* arg) {}

/// #grOldYoshi_8020EAFC

bool grOldYoshi_8020EC08(Ground_GObj* arg)
{
    return false;
}

/// #grOldYoshi_8020EC10

void grOldYoshi_8020EFC8(Ground_GObj* arg) {}

/// #grOldYoshi_8020EFCC

bool grOldYoshi_8020F080(Ground_GObj* arg)
{
    return false;
}

/// #grOldYoshi_8020F088

void grOldYoshi_8020F2A4(Ground_GObj* arg) {}

/// #fn_8020F2A8

/// #grOldYoshi_8020F31C

DynamicsDesc* grOldYoshi_8020F404(enum_t arg)
{
    return NULL;
}

bool grOldYoshi_8020F40C(Vec3* a, int arg, HSD_JObj* joint)
{
    Vec3 b;

    lb_8000B1CC(joint, NULL, &b);

    if (a->y > b.y + -5.0f) {
        return true;
    } else {
        return false;
    }
}
