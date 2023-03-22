#include "gr/grtyoshi.h"

#include "gr/granime.h"
#include "gr/grdisplay.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "lb/lbunknown_003.h"

#include <dolphin/os/os.h>
#include <baselib/gobjgxlink.h>

static StageCallbacks lbl_803E9578[] = {
    { lbl_80223CD4, lbl_80223D00, lbl_80223D08, lbl_80223D0C, 0 },
    { lbl_80223DA0, lbl_80223DF0, lbl_80223DF8, lbl_80223E18, 0 },
    { lbl_80223D10, lbl_80223D60, lbl_80223D68, lbl_80223D9C,
      (1 << 30) | (1 << 31) },
    { NULL, NULL, NULL, NULL, 0 }
};

StageData lbl_803E95D4 = {
    (1 << 0) | (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5),
    lbl_803E9578,
    "/GrTYs.dat",
    lbl_80223B4C,
    func_80223B48,
    lbl_80223BBC,
    lbl_80223BC0,
    lbl_80223BE4,
    lbl_80223E1C,
    lbl_80223E24,
    (1 << 0),
    NULL,
    0,
};

extern StageInfo stage_info;

static void func_80223B48(int arg0) {}
static void lbl_80223B4C(void)
{
    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 1;
    func_80223BEC(0);
    func_80223BEC(1);
    func_80223BEC(2);
    Ground_801C39C0();
    Ground_801C3BB4();
    Ground_801C4210();
    Ground_801C42AC();
}
static void lbl_80223BBC(void) {}
static void lbl_80223BC0(void)
{
    func_801CAE04(false);
}
static bool lbl_80223BE4(void)
{
    return false;
}
static HSD_GObj* func_80223BEC(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &lbl_803E9578[gobj_id];

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
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grtyoshi.c", 0xc3,
                 gobj_id);
    }

    return gobj;
}
static void lbl_80223CD4(HSD_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    func_801C8138(gobj, gp->map_id, 0);
}

static bool lbl_80223D00(HSD_GObj* arg0)
{
    return false;
}

static void lbl_80223D08(HSD_GObj* arg0) {}

static void lbl_80223D0C(HSD_GObj* arg0) {}

static void lbl_80223D10(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Ground* gp = gobj->user_data;
    Ground_801C2ED0(gobj->hsd_obj, gp->map_id);
    func_801C8138(gobj, gp->map_id, 0);
}

static bool lbl_80223D60(HSD_GObj* arg0)
{
    return false;
}

static void lbl_80223D68(HSD_GObj* gobj)
{
    func_800115F4();
    Ground_801C2FE0(gobj);
}

static void lbl_80223D9C(HSD_GObj* arg0) {}

static void lbl_80223DA0(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Ground* gp = gobj->user_data;
    Ground_801C2ED0(gobj->hsd_obj, gp->map_id);
    func_801C8138(gobj, gp->map_id, 0);
}

static bool lbl_80223DF0(HSD_GObj* arg0)
{
    return false;
}

static void lbl_80223DF8(HSD_GObj* arg0)
{
    Ground_801C2FE0(arg0);
}

static void lbl_80223E18(HSD_GObj* arg0) {}

static bool lbl_80223E1C(int arg0)
{
    return false;
}

static bool lbl_80223E24(Vec3* arg0, int arg1, HSD_JObj* arg2)
{
    return true;
}
