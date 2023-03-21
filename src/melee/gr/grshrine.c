#include "gr/grshrine.h"

#include "gr/granime.h"
#include "gr/grdisplay.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "lb/lbunknown_001.h"
#include "lb/lbunknown_003.h"

#include <math.h>
#include <dolphin/mtx/types.h>
#include <dolphin/os/os.h>
#include <baselib/gobjgxlink.h>

static void* lbl_804D6A18;

static StageCallbacks lbl_803E50E8[3] = {
    { func_80201E08, func_80201E34, func_80201E3C, func_80201E40, 0 },
    { func_80201E44, func_80201E88, func_80201E90, func_80201E94, 0 },
    { func_80201E9C, func_80201F14, func_80201F1C, func_80201F40,
      (1 << 30) | (1 << 31) },
};

StageData lbl_803E5130 = {
    (1 << 0) | (1 << 1) | (1 << 2),
    lbl_803E50E8,
    "/GrSh.dat",
    func_80201C64,
    func_80201C60,
    func_80201CF0,
    func_80201CF4,
    func_80201D18,
    func_80201F44,
    func_80201F4C,
    (1 << 0),
    NULL,
    0,
};

static void func_80201C60(int arg0) {}

static void func_80201C64(void)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused0[8];
#endif

    lbl_804D6A18 = func_801C49F8();
    func_80201D20(0);
    func_80201D20(1);
    func_80201D20(2);
    func_801C39C0();
    func_801C3BB4();

    {
        Vec3 v = { 0.5F, 0.0F, 0.0F };

        /// @todo Unused stack.
#ifdef MUST_MATCH
        u8 unused1[4];
#endif

        func_80011A50(&v, -1, 0.5f, 0.0f, M_PI / 3, -10000.0f, 10000.0f,
                      10000.0f, -10000.0f);
    }
}

static void func_80201CF0(void) {}

static void func_80201CF4(void)
{
    func_801CAE04(false);
}

static bool func_80201D18(void)
{
    return false;
}

static HSD_GObj* func_80201D20(s32 arg0)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &lbl_803E50E8[arg0];

    gobj = func_801C14D0(arg0);

    if (gobj != NULL) {
        Ground* gp;
        gp = gobj->user_data;
        gp->x8_callback = NULL;
        gp->xC_callback = NULL;
        GObj_SetupGXLink(gobj, func_801C5DB0, 3, 0);
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
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grshrine.c", 205, arg0);
    }
    return gobj;
}

static void func_80201E08(HSD_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    func_801C8138(gobj, gp->map_id, 0);
}

static bool func_80201E34(HSD_GObj* arg0)
{
    return false;
}

static void func_80201E3C(HSD_GObj* arg0) {}

static void func_80201E40(HSD_GObj* arg0) {}

static void func_80201E44(HSD_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    func_801C8138(gobj, gp->map_id, 0);
    gp->x11_flags.b012 = 2;
}

static bool func_80201E88(HSD_GObj* arg0)
{
    return false;
}

static void func_80201E90(HSD_GObj* arg0) {}

static void func_80201E94(HSD_GObj* arg0) {}

static void func_80201E98(HSD_GObj* arg0) {}

static void func_80201E9C(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Ground* gp = gobj->user_data;
    func_801C2ED0(gobj->hsd_obj, gp->map_id);
    func_801C8138(gobj, gp->map_id, 0);
    func_801C10B8(gobj, func_80201E98);
    func_801C2FE0(gobj);
    gp->x10_flags.b5 = true;
}

static bool func_80201F14(HSD_GObj* arg0)
{
    return false;
}

static void func_80201F1C(HSD_GObj* arg0)
{
    func_801C2FE0(arg0);
    func_800115F4();
}

static void func_80201F40(HSD_GObj* arg0) {}

static bool func_80201F44(bool arg0)
{
    return false;
}

static bool func_80201F4C(Vec3* a, int _, HSD_JObj* joint)
{
    Vec3 b;
    func_8000B1CC(joint, 0, &b);

    if (a->y > b.y)
        return true;
    else
        return false;
}
