#include <melee/gr/grtpichu.h>

#include <dolphin/os/os.h>
#include <melee/gr/granime.h>
#include <melee/gr/grdisplay.h>
#include <melee/gr/ground.h>
#include <melee/gr/grzakogenerator.h>
#include <melee/lb/lbunknown_003.h>
#include <sysdolphin/baselib/gobjgxlink.h>

static StageCallbacks lbl_803E91B0[] = {
    { lbl_80222D24, lbl_80222D50, lbl_80222D58, lbl_80222D5C, FLAGS_NONE },
    { lbl_80222DF0, lbl_80222E40, lbl_80222E48, lbl_80222E68, FLAGS_NONE },
    { lbl_80222D60, lbl_80222DB0, lbl_80222DB8, lbl_80222DEC,
      (1 << 30) | (1 << 31) },
    { NULL, NULL, NULL, NULL, FLAGS_NONE }
};

StageData lbl_803E920C = {
    (1 << 3) | (1 << 4) | (1 << 5),
    lbl_803E91B0,
    "/GrTPc.dat",
    lbl_80222B9C,
    func_80222B98,
    lbl_80222C0C,
    lbl_80222C10,
    lbl_80222C34,
    lbl_80222E6C,
    lbl_80222E74,
    FLAGS_NONE,
    NULL,
    0,
};

extern StageInfo stage_info;

static void func_80222B98(bool arg0) {}

static void lbl_80222B9C(void)
{
    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = true;
    func_80222C3C(0);
    func_80222C3C(1);
    func_80222C3C(2);
    func_801C39C0();
    func_801C3BB4();
    func_801C4210();
    func_801C42AC();
}

static void lbl_80222C0C(void) {}

static void lbl_80222C10(void)
{
    func_801CAE04(0);
}

static bool lbl_80222C34(void)
{
    return false;
}

static HSD_GObj* func_80222C3C(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &lbl_803E91B0[gobj_id];

    gobj = func_801C14D0(gobj_id);
    if (gobj != NULL) {
        Map* map = gobj->user_data;
        map->x8_callback = NULL;
        map->xC_callback = NULL;
        GObj_SetupGXLink(gobj, func_801C5DB0, 3, 0);
        if (callbacks->callback3 != NULL) {
            map->x1C_callback = callbacks->callback3;
        }
        if (callbacks->callback0 != NULL) {
            callbacks->callback0(gobj);
        }
        if (callbacks->callback2 != NULL) {
            func_8038FD54(gobj, callbacks->callback2, 4);
        }
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grtpichu.c", 0xc2,
                 gobj_id);
    }

    return gobj;
}

static void lbl_80222D24(HSD_GObj* gobj)
{
    Map* map = gobj->user_data;
    func_801C8138(gobj, map->map_id, 0);
}

static bool lbl_80222D50(HSD_GObj* arg0)
{
    return false;
}

static void lbl_80222D58(HSD_GObj* arg0) {}

static void lbl_80222D5C(HSD_GObj* arg0) {}

static void lbl_80222D60(HSD_GObj* gobj)
{
    u32 unused[2];
    Map* map = gobj->user_data;
    func_801C2ED0(gobj->hsd_obj, map->map_id);
    func_801C8138(gobj, map->map_id, 0);
}

static bool lbl_80222DB0(HSD_GObj* arg0)
{
    return false;
}

static void lbl_80222DB8(HSD_GObj* gobj)
{
    func_800115F4();
    func_801C2FE0(gobj);
}

static void lbl_80222DEC(HSD_GObj* arg0) {}
static void lbl_80222DF0(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused[8];
#endif

    Map* map = gobj->user_data;
    func_801C2ED0(gobj->hsd_obj, map->map_id);
    func_801C8138(gobj, map->map_id, 0);
}

static bool lbl_80222E40(HSD_GObj* arg0)
{
    return false;
}

static void lbl_80222E48(HSD_GObj* arg0)
{
    func_801C2FE0(arg0);
}

static void lbl_80222E68(HSD_GObj* arg0) {}

static bool lbl_80222E6C(int arg0)
{
    return false;
}

static bool lbl_80222E74(Vec3* arg0, int arg1, HSD_JObj* arg2)
{
    return true;
}
