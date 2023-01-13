#include <melee/gr/grfigure1.h>

#include <dolphin/os/os.h>
#include <melee/gr/grdisplay.h>
#include <melee/gr/ground.h>

static StageCallbacks lbl_803E6278[3] = {
    { lbl_8020E168, lbl_8020E194, lbl_8020E19C, lbl_8020E1A0, 0UL },
    { lbl_8020E1A4, lbl_8020E1D0, lbl_8020E1D8, lbl_8020E1FC, 0xC0000000 },
    { lbl_8020E200, lbl_8020E250, lbl_8020E258, lbl_8020E25C, 0UL }
};

extern StageData lbl_803E62C0 = { 0x00000044,   lbl_803E6278,  "/GrEF1.dat",
                                  lbl_8020DFE0, func_8020DFDC, lbl_8020E050,
                                  lbl_8020E054, lbl_8020E078,  lbl_8020E260,
                                  lbl_8020E268, 0x00000001,    NULL,
                                  0UL };

void* lbl_804D6A70;

extern StageInfo stage_info;

static void func_8020DFDC(s32 n) {}
static void lbl_8020DFE0(void)
{
    lbl_804D6A70 = func_801C49F8();
    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 1;
    func_8020E080(0);
    func_8020E080(2);
    func_8020E080(1);
    func_801C39C0();
    func_801C3BB4();
}
static void lbl_8020E050(void) {}
static void lbl_8020E054(void)
{
    func_801CAE04(0);
}
static s32 lbl_8020E078(void)
{
    return 0;
}
static HSD_GObj* func_8020E080(s32 gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &lbl_803E6278[gobj_id];

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
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grfigure1.c", 194,
                 gobj_id);
    }
    return gobj;
}
static void lbl_8020E168(HSD_GObj* gobj)
{
    Map* map = gobj->user_data;
    func_801C8138(gobj, map->map_id, 0);
}
static s32 lbl_8020E194(void)
{
    return 0;
}
static void lbl_8020E19C(HSD_GObj* gobj) {}
static void lbl_8020E1A0() {}
static void lbl_8020E1A4(HSD_GObj* gobj)
{
    Map* map = gobj->user_data;
    func_801C2ED0(gobj->hsd_obj, map->map_id);
}
static s32 lbl_8020E1D0(void)
{
    return 0;
}
static void lbl_8020E1D8(HSD_GObj* gobj)
{
    func_801C2FE0(gobj);
    func_800115F4();
}
static void lbl_8020E1FC() {}
static void lbl_8020E200(HSD_GObj* gobj)
{
    u32 unused[2];
    Map* map = gobj->user_data;
    func_801C2ED0(gobj->hsd_obj, map->map_id);
    func_801C8138(gobj, map->map_id, 0);
}
static s32 lbl_8020E250(void)
{
    return 0;
}
static void lbl_8020E258(HSD_GObj* gobj) {}
static void lbl_8020E25C() {}
static bool lbl_8020E260(s32 n)
{
    return 0;
}
static s32 lbl_8020E268(Vec3* v, s32 n, struct _HSD_JObj* o)
{
    return 1;
}
void lbl_8020E270(s32 n) {}
