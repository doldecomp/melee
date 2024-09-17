#include <platform.h>

#include "lb/forward.h"
#include <baselib/forward.h>

#include "gr/granime.h"
#include "gr/grdisplay.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "gr/types.h"
#include "lb/lb_00F9.h"

#include <dolphin/mtx.h>
#include <dolphin/os/OSError.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>

/* 223580 */ static void grTSamus_80223580(int);
/* 223584 */ static void grTSamus_80223584(void);
/* 2235F4 */ static void grTSamus_802235F4(void);
/* 2235F8 */ static void grTSamus_802235F8(void);
/* 22361C */ static bool grTSamus_8022361C(void);
/* 223624 */ static HSD_GObj* grTSamus_80223624(s32);
/* 22370C */ static void grTSamus_8022370C(HSD_GObj*);
/* 223738 */ static bool grTSamus_80223738(HSD_GObj*);
/* 223740 */ static void grTSamus_80223740(HSD_GObj*);
/* 223744 */ static void grTSamus_80223744(HSD_GObj*);
/* 223748 */ static void grTSamus_80223748(HSD_GObj*);
/* 223798 */ static bool grTSamus_80223798(HSD_GObj*);
/* 2237A0 */ static void grTSamus_802237A0(HSD_GObj*);
/* 2237D4 */ static void grTSamus_802237D4(HSD_GObj*);
/* 2237D8 */ static void grTSamus_802237D8(HSD_GObj*);
/* 223828 */ static bool grTSamus_80223828(HSD_GObj*);
/* 223830 */ static void grTSamus_80223830(HSD_GObj*);
/* 223850 */ static void grTSamus_80223850(HSD_GObj*);
/* 223854 */ static DynamicsDesc* grTSamus_80223854(enum_t);
/* 22385C */ static bool grTSamus_8022385C(Vec3*, int, HSD_JObj*);

static StageCallbacks grTSs_803E93F8[] = {
    {
        grTSamus_8022370C,
        grTSamus_80223738,
        grTSamus_80223740,
        grTSamus_80223744,
        0,
    },
    {
        grTSamus_802237D8,
        grTSamus_80223828,
        grTSamus_80223830,
        grTSamus_80223850,
        0,
    },
    {
        grTSamus_80223748,
        grTSamus_80223798,
        grTSamus_802237A0,
        grTSamus_802237D4,
        (1 << 31) | (1 << 30),
    },
    { 0 },
};

StageData grTSs_803E9454 = {
    59,
    grTSs_803E93F8,
    "/GrTSs.dat",
    grTSamus_80223584,
    grTSamus_80223580,
    grTSamus_802235F4,
    grTSamus_802235F8,
    grTSamus_8022361C,
    grTSamus_80223854,
    grTSamus_8022385C,
    1,
};

void grTSamus_80223580(int unk0) {}

void grTSamus_80223584(void)
{
    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = true;

    grTSamus_80223624(0);
    grTSamus_80223624(1);
    grTSamus_80223624(2);
    Ground_801C39C0();
    Ground_801C3BB4();
    Ground_801C4210();
    Ground_801C42AC();
}

void grTSamus_802235F4(void) {}

void grTSamus_802235F8(void)
{
    grZakoGenerator_801CAE04(0);
}

bool grTSamus_8022361C(void)
{
    return false;
}

HSD_GObj* grTSamus_80223624(s32 arg0)
{
    HSD_GObj* gobj;
    StageCallbacks* cb;
    Ground* gp;

    cb = &grTSs_803E93F8[arg0];
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
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grtsamus.c", 0xC3,
                 arg0);
    }
    return gobj;
}

void grTSamus_8022370C(HSD_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grTSamus_80223738(HSD_GObj* gobj)
{
    return false;
}

void grTSamus_80223740(HSD_GObj* gobj) {}

void grTSamus_80223744(HSD_GObj* gobj) {}

void grTSamus_80223748(HSD_GObj* gobj)
{
    Ground_JObjInline1(gobj);
}

bool grTSamus_80223798(HSD_GObj* gobj)
{
    return false;
}

void grTSamus_802237A0(HSD_GObj* gobj)
{
    lb_800115F4();
    Ground_801C2FE0(gobj);
}

void grTSamus_802237D4(HSD_GObj* gobj) {}

void grTSamus_802237D8(HSD_GObj* gobj)
{
    Ground_JObjInline1(gobj);
}

bool grTSamus_80223828(HSD_GObj* gobj)
{
    return false;
}

void grTSamus_80223830(HSD_GObj* gobj)
{
    Ground_801C2FE0(gobj);
}

void grTSamus_80223850(HSD_GObj* gobj) {}

DynamicsDesc* grTSamus_80223854(enum_t arg0)
{
    return NULL;
}

bool grTSamus_8022385C(Vec3* arg0, int arg1, HSD_JObj* arg2)
{
    return true;
}
