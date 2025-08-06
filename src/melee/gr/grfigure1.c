#include <platform.h>

#include "lb/forward.h"

#include "gr/grfigure1.h"

#include "gr/granime.h"
#include "gr/grdisplay.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/types.h"
#include "lb/lb_00F9.h"

#include <dolphin/mtx.h>
#include <dolphin/os/OSError.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>

static void grFigure1_8020DFDC(bool);
static void grFigure1_8020DFE0(void);
static void grFigure1_8020E050(void);
static void grFigure1_8020E054(void);
static bool grFigure1_8020E078(void);
static HSD_GObj* grFigure1_8020E080(int);
static void grFigure1_8020E168(Ground_GObj*);
static bool grFigure1_8020E194(Ground_GObj*);
static void grFigure1_8020E19C(Ground_GObj*);
static void grFigure1_8020E1A0(Ground_GObj*);
static void grFigure1_8020E1A4(Ground_GObj*);
static bool grFigure1_8020E1D0(Ground_GObj*);
static void grFigure1_8020E1D8(Ground_GObj*);
static void grFigure1_8020E1FC(Ground_GObj*);
static void grFigure1_8020E200(Ground_GObj*);
static bool grFigure1_8020E250(Ground_GObj*);
static void grFigure1_8020E258(Ground_GObj*);
static void grFigure1_8020E25C(Ground_GObj*);
static DynamicsDesc* grFigure1_8020E260(enum_t);
static bool grFigure1_8020E268(Vec3*, int, HSD_JObj*);

static StageCallbacks grEF1_803E6278[3] = {
    { grFigure1_8020E168, grFigure1_8020E194, grFigure1_8020E19C,
      grFigure1_8020E1A0, 0 },
    { grFigure1_8020E1A4, grFigure1_8020E1D0, grFigure1_8020E1D8,
      grFigure1_8020E1FC, (1 << 30) | (1 << 31) },
    { grFigure1_8020E200, grFigure1_8020E250, grFigure1_8020E258,
      grFigure1_8020E25C, 0 }
};

StageData grEF1_803E62C0 = {
    (1 << 2) | (1 << 6),
    grEF1_803E6278,
    "/GrEF1.dat",
    grFigure1_8020DFE0,
    grFigure1_8020DFDC,
    grFigure1_8020E050,
    grFigure1_8020E054,
    grFigure1_8020E078,
    grFigure1_8020E260,
    grFigure1_8020E268,
    (1 << 0),
    NULL,
    0,
};

UNK_T grEF1_804D6A70;

extern StageInfo stage_info;

static void grFigure1_8020DFDC(bool n) {}

static void grFigure1_8020DFE0(void)
{
    grEF1_804D6A70 = Ground_801C49F8();
    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = true;
    grFigure1_8020E080(0);
    grFigure1_8020E080(2);
    grFigure1_8020E080(1);
    Ground_801C39C0();
    Ground_801C3BB4();
}

static void grFigure1_8020E050(void) {}

static void grFigure1_8020E054(void)
{
    grZakoGenerator_801CAE04(false);
}

static bool grFigure1_8020E078(void)
{
    return false;
}

static HSD_GObj* grFigure1_8020E080(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grEF1_803E6278[gobj_id];

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
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grfigure1.c", 194,
                 gobj_id);
    }

    return gobj;
}

static void grFigure1_8020E168(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    grAnime_801C8138(gobj, gp->map_id, 0);
}

static bool grFigure1_8020E194(Ground_GObj* arg0)
{
    return false;
}

static void grFigure1_8020E19C(Ground_GObj* gobj) {}

static void grFigure1_8020E1A0(Ground_GObj* arg0) {}

static void grFigure1_8020E1A4(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    Ground_801C2ED0(gobj->hsd_obj, gp->map_id);
}

static bool grFigure1_8020E1D0(Ground_GObj* arg0)
{
    return false;
}

static void grFigure1_8020E1D8(Ground_GObj* gobj)
{
    Ground_801C2FE0(gobj);
    lb_800115F4();
}

static void grFigure1_8020E1FC(Ground_GObj* arg0) {}

static void grFigure1_8020E200(Ground_GObj* gobj)
{
    u8 _[8];

    Ground* gp = gobj->user_data;
    Ground_801C2ED0(gobj->hsd_obj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

static bool grFigure1_8020E250(Ground_GObj* arg0)
{
    return false;
}

static void grFigure1_8020E258(Ground_GObj* gobj) {}

static void grFigure1_8020E25C(Ground_GObj* arg0) {}

static DynamicsDesc* grFigure1_8020E260(enum_t arg0)
{
    return NULL;
}

static bool grFigure1_8020E268(Vec3* v, int n, HSD_JObj* o)
{
    return true;
}

void grFigure1_8020E270(bool n) {}
