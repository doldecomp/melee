
#include "grtgamewatch.h"

#include "gr/grdisplay.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "gr/types.h"
#include "lb/lb_00F9.h"
#include "lb/types.h"

#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>

StageCallbacks grTGw_803E96F8[] = {
    { grTGameWatch_8022429C, grTGameWatch_802242C8, grTGameWatch_802242D0,
      grTGameWatch_802242D4, 0 },
    { grTGameWatch_80224368, grTGameWatch_802243B8, grTGameWatch_802243C0,
      grTGameWatch_802243E0, 0 },
    { grTGameWatch_802242D8, grTGameWatch_80224328, grTGameWatch_80224330,
      grTGameWatch_80224364, 0xC0000000 },
    { NULL, NULL, NULL, NULL, 0 }
};

StageData grTGw_803E9754 = {
    63,
    grTGw_803E96F8,
    "/GrTGw.dat",
    grTGameWatch_80224114,
    grTGameWatch_80224110,
    grTgamewatch_UnkStage0_OnLoad,
    grTgamewatch_UnkStage0_OnStart,
    grTGameWatch_802241AC,
    grTGameWatch_802243E4,
    grTGameWatch_802243EC,
    (1 << 0),
};

void grTGameWatch_80224110(bool unused)
{
    return;
}

void grTGameWatch_80224114(void)
{
    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = true;

    grTGameWatch_802241B4(0);
    grTGameWatch_802241B4(1);
    grTGameWatch_802241B4(2);
    Ground_801C39C0();
    Ground_801C3BB4();
    Ground_801C4210();
    Ground_801C42AC();
}

void grTgamewatch_UnkStage0_OnLoad(void)
{
    return;
}

void grTgamewatch_UnkStage0_OnStart(void)
{
    grZakoGenerator_801CAE04(0);
}

bool grTGameWatch_802241AC(void)
{
    return false;
}

HSD_GObj* grTGameWatch_802241B4(int id)
{
    HSD_GObj* gobj;
    StageCallbacks* cb = &grTGw_803E96F8[id];
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
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grtgamewatch.c", 195,
                 id);
    }

    return gobj;
}

void grTGameWatch_8022429C(Ground_GObj* gobj)
{
    Ground* gp = (Ground*) HSD_GObjGetUserData(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grTGameWatch_802242C8(Ground_GObj* gobj)
{
    return false;
}

void grTGameWatch_802242D0(Ground_GObj* gobj)
{
    return;
}

void grTGameWatch_802242D4(Ground_GObj* gobj)
{
    return;
}

void grTGameWatch_802242D8(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* joint = (HSD_JObj*) gobj->hsd_obj;
    PAD_STACK(8);

    Ground_801C2ED0(joint, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, false);
}

bool grTGameWatch_80224328(Ground_GObj* gobj)
{
    return false;
}

void grTGameWatch_80224330(Ground_GObj* gobj)
{
    lb_800115F4();
    Ground_801C2FE0(gobj);
}

void grTGameWatch_80224364(Ground_GObj* gobj)
{
    return;
}

void grTGameWatch_80224368(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* joint = (HSD_JObj*) gobj->hsd_obj;
    PAD_STACK(8);

    Ground_801C2ED0(joint, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, false);
}

bool grTGameWatch_802243B8(Ground_GObj* gobj)
{
    return false;
}

void grTGameWatch_802243C0(Ground_GObj* gobj)
{
    Ground_801C2FE0(gobj);
}

void grTGameWatch_802243E0(Ground_GObj* gobj)
{
    return;
}

DynamicsDesc* grTGameWatch_802243E4(enum_t unused)
{
    return NULL;
}

bool grTGameWatch_802243EC(Vec3* vec, int arg1, HSD_JObj* jobj)
{
    return true;
}
