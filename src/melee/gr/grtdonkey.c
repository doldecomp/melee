#include "gr/grtdonkey.h"

#include "gr/granime.h"
#include "gr/grdisplay.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "lb/lb_00F9.h"

#include <dolphin/os/os.h>
#include <baselib/gobjgxlink.h>

static StageCallbacks lbl_803E8790[] = {
    { lbl_802203B4, lbl_802203E0, lbl_802203E8, lbl_802203EC, 0 },
    { lbl_80220480, lbl_802204D0, lbl_802204D8, lbl_802204F8, 0 },
    { lbl_802203F0, lbl_80220440, lbl_80220448, lbl_8022047C,
      (1 << 30) | (1 << 31) },
    { NULL, NULL, NULL, NULL, 0 },
};

StageData lbl_803E87EC = {
    43,
    lbl_803E8790,
    "/GrTDk.dat",
    lbl_8022022C,
    func_80220228,
    lbl_8022029C,
    lbl_802202A0,
    lbl_802202C4,
    lbl_802204FC,
    lbl_80220504,
    (1 << 0),
    NULL,
    0,
};

extern StageInfo stage_info;

static void func_80220228(int arg0) {}

static void lbl_8022022C(void)
{
    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 1;
    func_802202CC(0);
    func_802202CC(1);
    func_802202CC(2);
    Ground_801C39C0();
    Ground_801C3BB4();
    Ground_801C4210();
    Ground_801C42AC();
}

static void lbl_8022029C(void) {}

static void lbl_802202A0(void)
{
    grZakoGenerator_801CAE04(0);
}

static bool lbl_802202C4(void)
{
    return false;
}

static HSD_GObj* func_802202CC(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &lbl_803E8790[gobj_id];

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
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grtdonkey.c", 0xc3,
                 gobj_id);
    }

    return gobj;
}
static void lbl_802203B4(HSD_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    grAnime_801C8138(gobj, gp->map_id, 0);
}

static bool lbl_802203E0(HSD_GObj* arg0)
{
    return false;
}

static void lbl_802203E8(HSD_GObj* arg0) {}

static void lbl_802203EC(HSD_GObj* arg0) {}

static void lbl_802203F0(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Ground* gp = GET_GROUND(gobj);
    Ground_801C2ED0(gobj->hsd_obj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, false);
}

static bool lbl_80220440(HSD_GObj* arg0)
{
    return false;
}

static void lbl_80220448(HSD_GObj* gobj)
{
    lb_800115F4();
    Ground_801C2FE0(gobj);
}

static void lbl_8022047C(HSD_GObj* arg0) {}

static void lbl_80220480(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Ground* gp = GET_GROUND(gobj);
    Ground_801C2ED0(gobj->hsd_obj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, false);
}

static bool lbl_802204D0(HSD_GObj* arg0)
{
    return false;
}

static void lbl_802204D8(HSD_GObj* arg0)
{
    Ground_801C2FE0(arg0);
}

static void lbl_802204F8(HSD_GObj* arg0) {}

static bool lbl_802204FC(int arg0)
{
    return false;
}

static bool lbl_80220504(Vec3* arg0, int arg1, HSD_JObj* arg2)
{
    return true;
}
