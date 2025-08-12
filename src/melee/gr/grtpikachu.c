#include "grtpikachu.h"

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

StageCallbacks grTPk_803E9270[] = {
    { grTPikachu_80223008, grTPikachu_80223034, grTPikachu_8022303C,
      grTPikachu_80223040, 0 },
    { grTPikachu_802230D4, grTPikachu_80223124, grTPikachu_8022312C,
      grTPikachu_8022314C, 0 },
    { grTPikachu_80223044, grTPikachu_80223094, grTPikachu_8022309C,
      grTPikachu_802230D0, 0xC0000000 },
    { NULL, NULL, NULL, NULL, 0 }
};

StageData grTPk_803E92CC = {
    57,
    grTPk_803E9270,
    "/GrTPk.dat",
    grTPikachu_80222E80,
    grTPikachu_80222E7C,
    grTpikachu_UnkStage0_OnLoad,
    grTpikachu_UnkStage0_OnStart,
    grTPikachu_80222F18,
    grTPikachu_80223150,
    grTPikachu_80223158,
    (1 << 0),
};

void grTPikachu_80222E7C(bool unused)
{
    return;
}

void grTPikachu_80222E80(void)
{
    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = true;

    grTPikachu_80222F20(0);
    grTPikachu_80222F20(1);
    grTPikachu_80222F20(2);
    Ground_801C39C0();
    Ground_801C3BB4();
    Ground_801C4210();
    Ground_801C42AC();
}

void grTpikachu_UnkStage0_OnLoad(void)
{
    return;
}

void grTpikachu_UnkStage0_OnStart(void)
{
    grZakoGenerator_801CAE04(0);
}

bool grTPikachu_80222F18(void)
{
    return false;
}

HSD_GObj* grTPikachu_80222F20(int id)
{
    HSD_GObj* gobj;
    StageCallbacks* cb = &grTPk_803E9270[id];
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
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grtpikachu.c", 195, id);
    }

    return gobj;
}

void grTPikachu_80223008(Ground_GObj* gobj)
{
    Ground* gp = (Ground*) HSD_GObjGetUserData(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grTPikachu_80223034(Ground_GObj* gobj)
{
    return false;
}

void grTPikachu_8022303C(Ground_GObj* gobj)
{
    return;
}

void grTPikachu_80223040(Ground_GObj* gobj)
{
    return;
}

void grTPikachu_80223044(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* joint = (HSD_JObj*) gobj->hsd_obj;
    PAD_STACK(8);

    Ground_801C2ED0(joint, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, false);
}

bool grTPikachu_80223094(Ground_GObj* gobj)
{
    return false;
}

void grTPikachu_8022309C(Ground_GObj* gobj)
{
    lb_800115F4();
    Ground_801C2FE0(gobj);
}

void grTPikachu_802230D0(Ground_GObj* gobj)
{
    return;
}

void grTPikachu_802230D4(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* joint = (HSD_JObj*) gobj->hsd_obj;
    PAD_STACK(8);

    Ground_801C2ED0(joint, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, false);
}

bool grTPikachu_80223124(Ground_GObj* gobj)
{
    return false;
}

void grTPikachu_8022312C(Ground_GObj* gobj)
{
    Ground_801C2FE0(gobj);
}

void grTPikachu_8022314C(Ground_GObj* gobj)
{
    return;
}

DynamicsDesc* grTPikachu_80223150(enum_t unused)
{
    return NULL;
}

bool grTPikachu_80223158(Vec3* vec, int arg1, HSD_JObj* jobj)
{
    return true;
}
