#include "gr/grtluigi.h"

#include "gr/granime.h"
#include "gr/grdisplay.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "gr/types.h"
#include "lb/lb_00F9.h"

#include <dolphin/os/OSError.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>

/* static */ StageCallbacks grTLg_803E8DF0[4] = {
    {
        grTLuigi_80221D9C,
        grTLuigi_80221DC8,
        grTLuigi_80221DD0,
        grTLuigi_80221DD4,
        0,
    },
    {
        grTLuigi_80221E68,
        grTLuigi_80221EB8,
        grTLuigi_80221EC0,
        grTLuigi_80221EE0,
        0,
    },
    {
        grTLuigi_80221DD8,
        grTLuigi_80221E28,
        grTLuigi_80221E30,
        grTLuigi_80221E64,
        (1 << 30) | (1 << 31),
    },
};

StageData grTLg_803E8E4C = {
    51,
    grTLg_803E8DF0,
    "/GrTLg.dat",
    grTLuigi_80221C14,
    grTLuigi_80221C10,
    grTLuigi_80221C84,
    grTLuigi_80221C88,
    grTLuigi_80221CAC,
    grTLuigi_80221EE4,
    grTLuigi_80221EEC,
    1,
};

void grTLuigi_80221C10(bool arg0) {}

void grTLuigi_80221C14(void)
{
    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = true;

    grTLuigi_80221CB4(0);
    grTLuigi_80221CB4(1);
    grTLuigi_80221CB4(2);
    Ground_801C39C0();
    Ground_801C3BB4();
    Ground_801C4210();
    Ground_801C42AC();
}

void grTLuigi_80221C84(void) {}

void grTLuigi_80221C88(void)
{
    grZakoGenerator_801CAE04(0);
}

bool grTLuigi_80221CAC(void)
{
    return false;
}

HSD_GObj* grTLuigi_80221CB4(int arg0)
{
    HSD_GObj* gobj;
    StageCallbacks* cb;
    Ground* gp;

    cb = &grTLg_803E8DF0[arg0];
    gobj = Ground_801C14D0(arg0);
    if (gobj != NULL) {
        gp = gobj->user_data;
        gp->x8_callback = 0;
        gp->xC_callback = 0;
        GObj_SetupGXLink(gobj, &grDisplay_801C5DB0, 3, 0);
        if (cb->callback3 != 0U) {
            gp->x1C_callback = cb->callback3;
        }
        if (cb->callback0 != NULL) {
            cb->callback0(gobj);
        }
        if (cb->callback2 != 0U) {
            HSD_GObjProc_8038FD54(gobj, cb->callback2, 4);
        }
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grtluigi.c", 0xC3,
                 arg0);
    }
    return gobj;
}

void grTLuigi_80221D9C(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grTLuigi_80221DC8(Ground_GObj* arg0)
{
    return false;
}

void grTLuigi_80221DD0(Ground_GObj* arg0) {}

void grTLuigi_80221DD4(Ground_GObj* arg0) {}

void grTLuigi_80221DD8(Ground_GObj* gobj)
{
    Ground_JObjInline1(gobj);
}

bool grTLuigi_80221E28(Ground_GObj* arg0)
{
    return false;
}

void grTLuigi_80221E30(Ground_GObj* arg0)
{
    lb_800115F4();
    Ground_801C2FE0(arg0);
}

void grTLuigi_80221E64(Ground_GObj* arg0) {}

void grTLuigi_80221E68(Ground_GObj* gobj)
{
    Ground_JObjInline1(gobj);
}

bool grTLuigi_80221EB8(Ground_GObj* arg0)
{
    return false;
}

void grTLuigi_80221EC0(Ground_GObj* gobj)
{
    Ground_801C2FE0(gobj);
}

void grTLuigi_80221EE0(Ground_GObj* arg0) {}

DynamicsDesc* grTLuigi_80221EE4(enum_t arg0)
{
    return NULL;
}

bool grTLuigi_80221EEC(Vec3* arg0, int arg1, HSD_JObj* arg2)
{
    return true;
}
