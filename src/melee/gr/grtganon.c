#include "grtganon.h"

#include "gr/grdisplay.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "gr/types.h"
#include "lb/lb_00F9.h"
#include "lb/types.h"
#include "mp/mplib.h"

#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>

StageCallbacks grTGn_803E9880[] = {
    { grTGanon_8022486C, grTGanon_80224898, grTGanon_802248A0,
      grTGanon_802248A4, 0 },
    { grTGanon_80224938, grTGanon_80224988, grTGanon_80224990,
      grTGanon_802249B0, 0 },
    { grTGanon_802248A8, grTGanon_802248F8, grTGanon_80224900,
      grTGanon_80224934, 0xC0000000 },
    { NULL, NULL, NULL, NULL, 0 }
};

StageData grTGn_803E98DC = {
    65,
    grTGn_803E9880,
    "/GrTGn.dat",
    grTGanon_802246DC,
    grTGanon_802246D8,
    grTGanon_80224754,
    grTGanon_80224758,
    grTGanon_8022477C,
    grTGanon_802249B4,
    grTGanon_80224A4C,
    (1 << 0),
};

typedef struct grTGnSpecialParams {
    DynamicsDesc* x0;
    DynamicsDesc* x4;
    DynamicsDesc* x8;
} grTGnSpecialParams;

grTGnSpecialParams* grTGn_804D6B18;

void grTGanon_802246D8(bool unused)
{
    return;
}

void grTGanon_802246DC(void)
{
    grTGn_804D6B18 = Ground_801C49F8();
    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = true;

    grTGanon_80224784(0);
    grTGanon_80224784(1);
    grTGanon_80224784(2);
    Ground_801C39C0();
    Ground_801C3BB4();
    Ground_801C4210();
    Ground_801C42AC();
}

void grTGanon_80224754(void)
{
    return;
}

void grTGanon_80224758(void)
{
    grZakoGenerator_801CAE04(0);
}

bool grTGanon_8022477C(void)
{
    return false;
}

HSD_GObj* grTGanon_80224784(int id)
{
    HSD_GObj* gobj;
    StageCallbacks* cb = &grTGn_803E9880[id];
    gobj = Ground_801C14D0(id);

    if (gobj != NULL) {
        Ground* gp = (Ground*) HSD_GObjGetUserData(gobj);
        gp->x8_callback = NULL;
        gp->xC_callback = NULL;
        GObj_SetupGXLink(gobj, grDisplay_801C5DB0, 3, 0);

        if (cb->callback3 != NULL) {
            gp->x1C_callback = cb->callback3;
        }

        if (cb->callback0 != NULL) {
            cb->callback0(gobj);
        }

        if (cb->callback2 != NULL) {
            HSD_GObjProc_8038FD54(gobj, cb->callback2, 4);
        }
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grtganon.c", 201, id);
    }

    return gobj;
}

void grTGanon_8022486C(Ground_GObj* gobj)
{
    Ground* gp = (Ground*) HSD_GObjGetUserData(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grTGanon_80224898(Ground_GObj* gobj)
{
    return false;
}

void grTGanon_802248A0(Ground_GObj* gobj)
{
    return;
}

void grTGanon_802248A4(Ground_GObj* gobj)
{
    return;
}

void grTGanon_802248A8(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* joint = (HSD_JObj*) gobj->hsd_obj;
    PAD_STACK(8);

    Ground_801C2ED0(joint, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, false);
}

bool grTGanon_802248F8(Ground_GObj* gobj)
{
    return false;
}

void grTGanon_80224900(Ground_GObj* gobj)
{
    lb_800115F4();
    Ground_801C2FE0(gobj);
}

void grTGanon_80224934(Ground_GObj* gobj)
{
    return;
}

void grTGanon_80224938(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* joint = (HSD_JObj*) gobj->hsd_obj;
    PAD_STACK(8);

    Ground_801C2ED0(joint, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, false);
}

bool grTGanon_80224988(Ground_GObj* gobj)
{
    return false;
}

void grTGanon_80224990(Ground_GObj* gobj)
{
    Ground_801C2FE0(gobj);
}

void grTGanon_802249B0(Ground_GObj* gobj)
{
    return;
}

DynamicsDesc* grTGanon_802249B4(enum_t arg0)
{
    if (arg0 != -1) {
        enum_t i = mpLib_80056B6C(arg0);

        if (i != -1 && i == 0) {
            i = mpLib_80054C6C(arg0);

            if (i == (1 << 1)) {
                return grTGn_804D6B18->x0;
            }

            if (i == (1 << 2)) {
                return grTGn_804D6B18->x4;
            }

            if (i == (1 << 3)) {
                return grTGn_804D6B18->x8;
            }

            return NULL;
        }
    }

    return NULL;
}

bool grTGanon_80224A4C(Vec3* vec, int arg1, HSD_JObj* jobj)
{
    return true;
}
