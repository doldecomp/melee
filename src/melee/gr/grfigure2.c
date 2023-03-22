#include "gr/grfigure2.h"

#include "gr/granime.h"
#include "gr/grdisplay.h"
#include "gr/grfigure1.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "lb/lbunknown_003.h"

#include <dolphin/os/os.h>
#include <baselib/gobjgxlink.h>

static StageCallbacks lbl_803E6328[3] = {
    { lbl_8020E3FC, lbl_8020E428, lbl_8020E430, lbl_8020E434, 0UL },
    { lbl_8020E438, lbl_8020E464, lbl_8020E46C, lbl_8020E490, 0xC0000000 },
    { lbl_8020E494, lbl_8020E4E4, lbl_8020E4EC, lbl_8020E4F0, 0UL }
};

StageData lbl_803E6370 = {
    0x00000045,   lbl_803E6328, "/GrEF2.dat", func_8020E274, lbl_8020E270,
    lbl_8020E2E4, lbl_8020E2E8, lbl_8020E30C, lbl_8020E4F4,  lbl_8020E4FC,
    0x00000001,   NULL,         0UL
};

void* lbl_804D6A78;

extern StageInfo stage_info;

static void func_8020E274(void)
{
    lbl_804D6A78 = Ground_801C49F8();
    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 1;
    func_8020E314(0);
    func_8020E314(2);
    func_8020E314(1);
    Ground_801C39C0();
    Ground_801C3BB4();
}
static void lbl_8020E2E4(void) {}

static void lbl_8020E2E8(void)
{
    grZakoGenerator_801CAE04(false);
}

static bool lbl_8020E30C(void)
{
    return false;
}

static HSD_GObj* func_8020E314(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &lbl_803E6328[gobj_id];

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
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grfigure2.c", 196,
                 gobj_id);
    }
    return gobj;
}
static void lbl_8020E3FC(HSD_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    grAnime_801C8138(gobj, gp->map_id, 0);
}

static bool lbl_8020E428(HSD_GObj* arg0)
{
    return false;
}

static void lbl_8020E430(HSD_GObj* gobj) {}

static void lbl_8020E434(HSD_GObj* arg0) {}

static void lbl_8020E438(HSD_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    Ground_801C2ED0(gobj->hsd_obj, gp->map_id);
}

static bool lbl_8020E464(HSD_GObj* arg0)
{
    return false;
}

static void lbl_8020E46C(HSD_GObj* gobj)
{
    Ground_801C2FE0(gobj);
    func_800115F4();
}

static void lbl_8020E490(HSD_GObj* arg0) {}

static void lbl_8020E494(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Ground* gp = gobj->user_data;
    Ground_801C2ED0(gobj->hsd_obj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

static bool lbl_8020E4E4(HSD_GObj* arg0)
{
    return false;
}

static void lbl_8020E4EC(HSD_GObj* gobj) {}

static void lbl_8020E4F0(HSD_GObj* arg0) {}

static bool lbl_8020E4F4(int number)
{
    return false;
}

static bool lbl_8020E4FC(Vec3* vector, int number, HSD_JObj* jobj)
{
    return true;
}
