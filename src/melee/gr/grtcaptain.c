#include <platform.h>

#include "lb/forward.h"
#include <baselib/forward.h>

#include "gr/grtcaptain.h"

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

static void grTCaptain_8021FC60(bool);
static void grTCaptain_8021FC64(void);
static void grTCaptain_8021FCD4(void);
static void grTCaptain_8021FCD8(void);
static bool grTCaptain_8021FCFC(void);
static HSD_GObj* grTCaptain_8021FD04(int gobj_id);
static void grTCaptain_8021FDEC(Ground_GObj* gobj);
static bool grTCaptain_8021FE18(Ground_GObj*);
static void grTCaptain_8021FE20(Ground_GObj*);
static void grTCaptain_8021FE24(Ground_GObj*);
static void grTCaptain_8021FE28(Ground_GObj* gobj);
static bool grTCaptain_8021FE78(Ground_GObj*);
static void grTCaptain_8021FE80(Ground_GObj* gobj);
static void grTCaptain_8021FEB4(Ground_GObj*);
static void grTCaptain_8021FEB8(Ground_GObj* gobj);
static bool grTCaptain_8021FF08(Ground_GObj*);
static void grTCaptain_8021FF10(Ground_GObj*);
static void grTCaptain_8021FF30(Ground_GObj*);
static DynamicsDesc* grTCaptain_8021FF34(enum_t);
static bool grTCaptain_8021FF3C(Vec3*, int, HSD_JObj*);

static StageCallbacks grTCa_803E8608[] = {
    { grTCaptain_8021FDEC, grTCaptain_8021FE18, grTCaptain_8021FE20,
      grTCaptain_8021FE24, 0 },
    { grTCaptain_8021FEB8, grTCaptain_8021FF08, grTCaptain_8021FF10,
      grTCaptain_8021FF30, 0 },
    { grTCaptain_8021FE28, grTCaptain_8021FE78, grTCaptain_8021FE80,
      grTCaptain_8021FEB4, (1 << 30) | (1U << 31) },
    { NULL, NULL, NULL, NULL, 0 }
};

StageData grTCa_803E8664 = {
    41,
    grTCa_803E8608,
    "/GrTCa.dat",
    grTCaptain_8021FC64,
    grTCaptain_8021FC60,
    grTCaptain_8021FCD4,
    grTCaptain_8021FCD8,
    grTCaptain_8021FCFC,
    grTCaptain_8021FF34,
    grTCaptain_8021FF3C,
    (1 << 0),
    NULL,
    0,
};

static void grTCaptain_8021FC60(bool arg0) {}

static void grTCaptain_8021FC64(void)
{
    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = true;
    grTCaptain_8021FD04(0);
    grTCaptain_8021FD04(1);
    grTCaptain_8021FD04(2);
    Ground_801C39C0();
    Ground_801C3BB4();
    Ground_801C4210();
    Ground_801C42AC();
}
static void grTCaptain_8021FCD4(void) {}

static void grTCaptain_8021FCD8(void)
{
    grZakoGenerator_801CAE04(false);
}

static bool grTCaptain_8021FCFC(void)
{
    return false;
}

static HSD_GObj* grTCaptain_8021FD04(int gobj_id)
{
    /// @todo Can't move below @c callbacks.
    HSD_GObj* gobj;

    StageCallbacks* callbacks = &grTCa_803E8608[gobj_id];

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
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grtcaptain.c", 215,
                 gobj_id);
    }

    return gobj;
}

static void grTCaptain_8021FDEC(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

static bool grTCaptain_8021FE18(Ground_GObj* arg0)
{
    return false;
}

static void grTCaptain_8021FE20(Ground_GObj* arg0) {}

static void grTCaptain_8021FE24(Ground_GObj* arg0) {}

static void grTCaptain_8021FE28(Ground_GObj* gobj)
{
    u8 _[8];

    Ground* gp = GET_GROUND(gobj);
    Ground_801C2ED0(gobj->hsd_obj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

static bool grTCaptain_8021FE78(Ground_GObj* arg0)
{
    return false;
}

static void grTCaptain_8021FE80(Ground_GObj* gobj)
{
    lb_800115F4();
    Ground_801C2FE0(gobj);
}

static void grTCaptain_8021FEB4(Ground_GObj* arg0) {}

static void grTCaptain_8021FEB8(Ground_GObj* gobj)
{
    u8 _[8];

    Ground* gp = GET_GROUND(gobj);
    Ground_801C2ED0(gobj->hsd_obj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

static bool grTCaptain_8021FF08(Ground_GObj* arg0)
{
    return false;
}

static void grTCaptain_8021FF10(Ground_GObj* arg0)
{
    Ground_801C2FE0(arg0);
}

static void grTCaptain_8021FF30(Ground_GObj* argo) {}

static DynamicsDesc* grTCaptain_8021FF34(enum_t arg0)
{
    return NULL;
}

static bool grTCaptain_8021FF3C(Vec3* arg0, int arg1, HSD_JObj* arg2)
{
    return true;
}
