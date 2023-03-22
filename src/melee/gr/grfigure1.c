#include "gr/grfigure1.h"

#include "gr/granime.h"
#include "gr/grdisplay.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "lb/lb_00F9.h"

#include <dolphin/os/os.h>
#include <baselib/gobjgxlink.h>

static StageCallbacks lbl_803E6278[3] = {
    { lbl_8020E168, lbl_8020E194, lbl_8020E19C, lbl_8020E1A0, 0 },
    { lbl_8020E1A4, lbl_8020E1D0, lbl_8020E1D8, lbl_8020E1FC,
      (1 << 30) | (1 << 31) },
    { lbl_8020E200, lbl_8020E250, lbl_8020E258, lbl_8020E25C, 0 }
};

StageData lbl_803E62C0 = {
    (1 << 2) | (1 << 6),
    lbl_803E6278,
    "/GrEF1.dat",
    lbl_8020DFE0,
    func_8020DFDC,
    lbl_8020E050,
    lbl_8020E054,
    lbl_8020E078,
    lbl_8020E260,
    lbl_8020E268,
    (1 << 0),
    NULL,
    0,
};

unk_t lbl_804D6A70;

extern StageInfo stage_info;

static void func_8020DFDC(int n) {}

static void lbl_8020DFE0(void)
{
    lbl_804D6A70 = Ground_801C49F8();
    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = true;
    func_8020E080(0);
    func_8020E080(2);
    func_8020E080(1);
    Ground_801C39C0();
    Ground_801C3BB4();
}

static void lbl_8020E050(void) {}

static void lbl_8020E054(void)
{
    grZakoGenerator_801CAE04(false);
}

static bool lbl_8020E078(void)
{
    return false;
}

static HSD_GObj* func_8020E080(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &lbl_803E6278[gobj_id];

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
            func_8038FD54(gobj, callbacks->callback2, 4);
        }
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grfigure1.c", 194,
                 gobj_id);
    }

    return gobj;
}

static void lbl_8020E168(HSD_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    grAnime_801C8138(gobj, gp->map_id, 0);
}

static bool lbl_8020E194(HSD_GObj* arg0)
{
    return false;
}

static void lbl_8020E19C(HSD_GObj* gobj) {}

static void lbl_8020E1A0(HSD_GObj* arg0) {}

static void lbl_8020E1A4(HSD_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    Ground_801C2ED0(gobj->hsd_obj, gp->map_id);
}

static bool lbl_8020E1D0(HSD_GObj* arg0)
{
    return false;
}

static void lbl_8020E1D8(HSD_GObj* gobj)
{
    Ground_801C2FE0(gobj);
    func_800115F4();
}

static void lbl_8020E1FC(HSD_GObj* arg0) {}

static void lbl_8020E200(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Ground* gp = gobj->user_data;
    Ground_801C2ED0(gobj->hsd_obj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

static bool lbl_8020E250(HSD_GObj* arg0)
{
    return false;
}

static void lbl_8020E258(HSD_GObj* gobj) {}

static void lbl_8020E25C(HSD_GObj* arg0) {}

static bool lbl_8020E260(int n)
{
    return false;
}

static bool lbl_8020E268(Vec3* v, int n, HSD_JObj* o)
{
    return true;
}

void lbl_8020E270(int n) {}
