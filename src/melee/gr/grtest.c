#include "gr/grtest.h"

#include <platform.h>

#include "baselib/forward.h"
#include "gr/forward.h"

#include "gr/granime.h"
#include "gr/grdisplay.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "gr/stage.h"
#include "gr/types.h"

#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/jobj.h>
#include <sysdolphin/baselib/controller.h>
#include <sysdolphin/baselib/dobj.h>
#include <sysdolphin/baselib/gobjproc.h>

S16Vec3 grTe_803E56B8[] = {
    { 0, 2, 1 },   { 1, 2, 2 },   { 2, 2, 3 },   { 3, 2, 4 }, { 4, 2, 5 },
    { 5, 2, 6 },   { 6, 2, 7 },   { 7, 2, 8 },   { 8, 2, 9 }, { 9, 2, 10 },
    { 10, 2, 11 }, { 12, 2, 16 }, { 13, 2, 17 },
};

StageCallbacks grTe_803E5708[] = {
    { grTest_80207130, grTest_8020715C, grTest_80207164, grTest_80207168, 0 },
    { grTest_802073D0, grTest_802073FC, grTest_80207404, grTest_80207408, 0 },
    { grTest_8020716C, grTest_802071BC, grTest_802071C4, grTest_802073AC,
      0xC0000000 },
    { 0, 0, 0, 0, 0 }
};
StageData grTe_803E5764 = { 0x01,
                            grTe_803E5708,
                            "/GrTe.dat",
                            grTest_80206E30,
                            grTest_80206E2C,
                            grTest_UnkStage0_OnLoad,
                            grTest_UnkStage0_OnStart,
                            grTest_8020703C,
                            grTest_8020740C,
                            grTest_80207414,
                            1,
                            grTe_803E56B8,
                            13 };

float grTe_804D6A48;

void grTest_80206E2C(bool unused) {}

void grTest_80206E30(void)
{
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    PAD_STACK(8);

    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 1;
    grTest_80207044(0);
    gobj = grTest_80207044(2);
    GET_GROUND(gobj)->x8_callback = grTest_802073B0;
    gobj = grTest_80207044(1);
    jobj = GET_JOBJ(gobj);
    HSD_JObjSetScaleX(jobj, 80.0);
    HSD_JObjSetScaleY(jobj, 80.0);
    HSD_JObjSetScaleZ(jobj, 80.0);
    Ground_801C39C0();
    Ground_801C3BB4();
}

void grTest_UnkStage0_OnLoad(void) {}

void grTest_UnkStage0_OnStart(void)
{
    grZakoGenerator_801CAE04(false);
}

bool grTest_8020703C(void)
{
    return false;
}

HSD_GObj* grTest_80207044(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grTe_803E5708[gobj_id];
    gobj = Ground_801C14D0(gobj_id);
    if (gobj != NULL) {
        Ground* gp = GET_GROUND(gobj);
        gp->x8_callback = 0;
        gp->xC_callback = 0;
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
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grtest.c", 209,
                 gobj_id);
    }
    return gobj;
}

void grTest_80207130(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grTest_8020715C(Ground_GObj* gobj)
{
    return false;
}

void grTest_80207164(Ground_GObj* gobj) {}

void grTest_80207168(Ground_GObj* gobj) {}

void grTest_8020716C(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);

    Ground_801C2ED0(jobj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grTest_802071BC(Ground_GObj* gobj)
{
    return false;
}

void grTest_802071C4(Ground_GObj* gobj)
{
    HSD_JObj* iVar2;
    u32 uVar3;
    HSD_PadStatus* pad;
    PAD_STACK(16);

    if ((HSD_PadMasterStatus[1].trigger & 0x100) != 0) {
        iVar2 = Ground_801C3FA4(gobj, 0x10);
        if (iVar2) {
            if (HSD_JObjGetFlags(iVar2) & 0x10) {
                HSD_JObjClearFlags(iVar2, 0x10);
            } else {
                HSD_JObjSetFlags(iVar2, 0x10);
            }
            grTe_804D6A48 = 0.0f;
        }
    }
    pad = &HSD_PadMasterStatus[2];
    if ((HSD_PadMasterStatus[2].trigger & 0x100) != 0) {
        iVar2 = Ground_801C3FA4(gobj, 0x11);
        if (iVar2) {
            if (HSD_JObjGetFlags(iVar2) & 0x10) {
                HSD_JObjClearFlags(iVar2, 0x10);
            } else {
                HSD_JObjSetFlags(iVar2, 0x10);
            }
            grTe_804D6A48 = 0.0f;
        }
    }
    pad = &HSD_PadMasterStatus[1];
    uVar3 = pad->button;
    if (uVar3 & 0x400) {
        if (grTe_804D6A48 > -1.2217305f) {
            grTe_804D6A48 -= 0.08726646f;
        }
    }
    if (uVar3 & 0x800) {
        if (grTe_804D6A48 < 1.2217305f) {
            grTe_804D6A48 += 0.08726646f;
        }
    }
    iVar2 = Ground_801C3FA4(gobj, 11);
    if (iVar2) {
        HSD_JObjSetRotationZ(iVar2, grTe_804D6A48);
    }
}

void grTest_802073AC(Ground_GObj* gobj) {}

void grTest_802073B0(HSD_GObj* gobj)
{
    Ground_801C2FE0(gobj);
}

void grTest_802073D0(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grTest_802073FC(Ground_GObj* gobj)
{
    return false;
}

void grTest_80207404(Ground_GObj* gobj) {}

void grTest_80207408(Ground_GObj* gobj) {}

struct DynamicsDesc* grTest_8020740C(enum_t unused)
{
    return false;
}

bool grTest_80207414(Vec3* a, int id, HSD_JObj* jobj)
{
    return true;
}
