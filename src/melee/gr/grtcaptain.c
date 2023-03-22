#include "gr/grtcaptain.h"

#include "gr/granime.h"
#include "gr/grdisplay.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "lb/lb_00F9.h"

#include <dolphin/os/os.h>
#include <baselib/gobjgxlink.h>

static StageCallbacks lbl_803E8608[] = {
    { lbl_8021FDEC, lbl_8021FE18, lbl_8021FE20, lbl_8021FE24, 0 },
    { lbl_8021FEB8, lbl_8021FF08, lbl_8021FF10, lbl_8021FF30, 0 },
    { lbl_8021FE28, lbl_8021FE78, lbl_8021FE80, lbl_8021FEB4,
      (1 << 30) | (1U << 31) },
    { NULL, NULL, NULL, NULL, 0 }
};

StageData lbl_803E8664 = {
    41,
    lbl_803E8608,
    "/GrTCa.dat",
    lbl_8021FC64,
    func_8021FC60,
    lbl_8021FCD4,
    lbl_8021FCD8,
    lbl_8021FCFC,
    lbl_8021FF34,
    lbl_8021FF3C,
    (1 << 0),
    NULL,
    0,
};

static void func_8021FC60(int arg0) {}

static void lbl_8021FC64(void)
{
    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = true;
    func_8021FD04(0);
    func_8021FD04(1);
    func_8021FD04(2);
    Ground_801C39C0();
    Ground_801C3BB4();
    Ground_801C4210();
    Ground_801C42AC();
}
static void lbl_8021FCD4(void) {}

static void lbl_8021FCD8(void)
{
    grZakoGenerator_801CAE04(false);
}

static bool lbl_8021FCFC(void)
{
    return false;
}

static HSD_GObj* func_8021FD04(int gobj_id)
{
    /// @todo Can't move below @c callbacks.
    HSD_GObj* gobj;

    StageCallbacks* callbacks = &lbl_803E8608[gobj_id];

    gobj = Ground_801C14D0(gobj_id);
    if (gobj != NULL) {
        Ground* gp = gobj->user_data;
        gp->x8_callback = NULL;
        gp->xC_callback = NULL;
        GObj_SetupGXLink(gobj, grDisplay_801C5DB0, 3, 0);

        if (callbacks->callback3 != NULL)
            gp->x1C_callback = callbacks->callback3;

        if (callbacks->callback0 != NULL)
            callbacks->callback0(gobj);

        if (callbacks->callback2 != NULL)
            func_8038FD54(gobj, callbacks->callback2, 4);
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grtcaptain.c", 215,
                 gobj_id);
    }

    return gobj;
}

static void lbl_8021FDEC(HSD_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

static bool lbl_8021FE18(HSD_GObj* arg0)
{
    return false;
}

static void lbl_8021FE20(HSD_GObj* arg0) {}

static void lbl_8021FE24(HSD_GObj* arg0) {}

static void lbl_8021FE28(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Ground* gp = GET_GROUND(gobj);
    Ground_801C2ED0(gobj->hsd_obj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

static bool lbl_8021FE78(HSD_GObj* arg0)
{
    return false;
}

static void lbl_8021FE80(HSD_GObj* gobj)
{
    func_800115F4();
    Ground_801C2FE0(gobj);
}

static void lbl_8021FEB4(HSD_GObj* arg0) {}

static void lbl_8021FEB8(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Ground* gp = GET_GROUND(gobj);
    Ground_801C2ED0(gobj->hsd_obj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

static bool lbl_8021FF08(HSD_GObj* arg0)
{
    return false;
}

static void lbl_8021FF10(HSD_GObj* arg0)
{
    Ground_801C2FE0(arg0);
}

static void lbl_8021FF30(HSD_GObj* argo) {}

static bool lbl_8021FF34(int arg0)
{
    return false;
}

static bool lbl_8021FF3C(Vec3* arg0, int arg1, HSD_JObj* arg2)
{
    return true;
}
