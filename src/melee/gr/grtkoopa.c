#include <melee/gr/grtkoopa.h>

#include <dolphin/os/os.h>
#include <melee/gr/grdisplay.h>
#include <melee/gr/ground.h>

extern StageInfo stage_info;

static StageCallbacks lbl_803E8C70[4] = {
    { lbl_802217D4, lbl_80221800, lbl_80221808, lbl_8022180C, 0UL },
    { lbl_802218A0, lbl_802218F0, lbl_802218F8, lbl_80221918, 0UL },
    { lbl_80221810, lbl_80221860, lbl_80221868, lbl_8022189C, 0xC0000000 },
    { NULL, NULL, NULL, NULL, 0UL }
};

extern StageData lbl_803E8CCC = { 0x00000031,   lbl_803E8C70,  "/GrTKp.dat",
                                  lbl_8022164C, func_80221648, lbl_802216BC,
                                  lbl_802216C0, lbl_802216E4,  lbl_8022191C,
                                  lbl_80221924, 0x00000001,    NULL,
                                  0UL };

static void func_80221648(long) {}
static void lbl_8022164C(void)
{
    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 1;
    func_802216EC(0);
    func_802216EC(1);
    func_802216EC(2);
    func_801C39C0();
    func_801C3BB4();
    func_801C4210();
    func_801C42AC();
}
static void lbl_802216BC(void) {}
static void lbl_802216C0(void)
{
    func_801CAE04(0);
}
static s32 lbl_802216E4(void)
{
    return 0;
}
static HSD_GObj* func_802216EC(s32 gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &lbl_803E8C70[gobj_id];

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
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grtkoopa.c", 195,
                 gobj_id);
    }

    return gobj;
}
static void lbl_802217D4(HSD_GObj* gobj)
{
    Map* map = gobj->user_data;
    func_801C8138(gobj, map->map_id, 0);
}
static s32 lbl_80221800(void)
{
    return 0;
}
static void lbl_80221808(HSD_GObj*) {}
static void lbl_8022180C(void) {}
static void lbl_80221810(HSD_GObj* gobj)
{
    u32 unused[2];
    Map* map = gobj->user_data;
    func_801C2ED0(gobj->hsd_obj, map->map_id);
    func_801C8138(gobj, map->map_id, 0);
}
static s32 lbl_80221860(void)
{
    return 0;
}
static void lbl_80221868(HSD_GObj* gobj)
{
    func_800115F4();
    func_801C2FE0(gobj);
}
static void lbl_8022189C(void) {}
static void lbl_802218A0(HSD_GObj* gobj)
{
    u32 unused[2];
    Map* map = gobj->user_data;
    func_801C2ED0(gobj->hsd_obj, map->map_id);
    func_801C8138(gobj, map->map_id, 0);
}
static s32 lbl_802218F0(void)
{
    return 0;
}
static void lbl_802218F8(HSD_GObj*)
{
    func_801C2FE0();
}
static void lbl_80221918(void) {}
static bool lbl_8022191C(long)
{
    return 0;
}
static s32 lbl_80221924(Vec3*, long, struct _HSD_JObj*)
{
    return 1;
}
