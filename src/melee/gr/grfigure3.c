#include <melee/gr/grfigure3.h>

#include <dolphin/os/os.h>
#include <melee/gr/granime.h>
#include <melee/gr/grdisplay.h>
#include <melee/gr/ground.h>
#include <melee/gr/grzakogenerator.h>
#include <melee/lb/lbunknown_003.h>
#include <sysdolphin/baselib/gobjgxlink.h>

static StageCallbacks lbl_803E63D8[3] = {
    { lbl_8020E690, lbl_8020E6BC, lbl_8020E6C4, lbl_8020E6C8, 0UL },
    { lbl_8020E6CC, lbl_8020E6F8, lbl_8020E700, lbl_8020E724, 0xC0000000 },
    { lbl_8020E728, lbl_8020E778, lbl_8020E780, lbl_8020E784, 0UL }
};

extern StageData lbl_803E6420 = { 0x00000046,   lbl_803E63D8,  "/GrEF3.dat",
                                  lbl_8020E508, func_8020E504, lbl_8020E578,
                                  lbl_8020E57C, lbl_8020E5A0,  lbl_8020E788,
                                  lbl_8020E790, 0x00000001,    NULL,
                                  0UL };

void* lbl_804D6A80;

extern StageInfo stage_info;

static void func_8020E504(int number) {}

static void lbl_8020E508(void)
{
    lbl_804D6A80 = func_801C49F8();
    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 1;
    func_8020E5A8(0);
    func_8020E5A8(2);
    func_8020E5A8(1);
    func_801C39C0();
    func_801C3BB4();
}

static void lbl_8020E578(void) {}

static void lbl_8020E57C(void)
{
    func_801CAE04(false);
}

static bool lbl_8020E5A0(void)
{
    return false;
}

static HSD_GObj* func_8020E5A8(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &lbl_803E63D8[gobj_id];

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
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grfigure3.c", 195,
                 gobj_id);
    }

    return gobj;
}

static void lbl_8020E690(HSD_GObj* gobj)
{
    Map* map = gobj->user_data;
    func_801C8138(gobj, map->map_id, 0);
}

static bool lbl_8020E6BC(HSD_GObj*)
{
    return false;
}

static void lbl_8020E6C4(HSD_GObj* gobj) {}

static void lbl_8020E6C8() {}

static void lbl_8020E6CC(HSD_GObj* gobj)
{
    Map* map = gobj->user_data;
    func_801C2ED0(gobj->hsd_obj, map->map_id);
}

static bool lbl_8020E6F8(HSD_GObj*)
{
    return false;
}

static void lbl_8020E700(HSD_GObj* gobj)
{
    func_801C2FE0(gobj);
    func_800115F4();
}

static void lbl_8020E724() {}

static void lbl_8020E728(HSD_GObj* gobj)
{
    u32 unused[2];
    Map* map = gobj->user_data;
    func_801C2ED0(gobj->hsd_obj, map->map_id);
    func_801C8138(gobj, map->map_id, 0);
}

static bool lbl_8020E778(HSD_GObj*)
{
    return false;
}

static void lbl_8020E780(HSD_GObj* gobj) {}

static void lbl_8020E784() {}

static bool lbl_8020E788(int number)
{
    return false;
}

static bool lbl_8020E790(Vec3* vector, int number, struct _HSD_JObj* jobj)
{
    return true;
}
