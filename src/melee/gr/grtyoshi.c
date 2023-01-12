#include <melee/gr/grtyoshi.h>

#include <dolphin/os/os.h>
#include <melee/gr/grdisplay.h>
#include <melee/gr/ground.h>

static StageCallbacks lbl_803E9578[4] = {
    { lbl_80223CD4, lbl_80223D00, lbl_80223D08, lbl_80223D0C, 0UL },
    { lbl_80223DA0, lbl_80223DF0, lbl_80223DF8, lbl_80223E18, 0UL },
    { lbl_80223D10, lbl_80223D60, lbl_80223D68, lbl_80223D9C, 0xC0000000 },
    { NULL, NULL, NULL, NULL, 0UL }
};

extern StageData lbl_803E95D4 = { 0x0000003D,   lbl_803E9578,  "/GrTYs.dat",
                                  lbl_80223B4C, func_80223B48, lbl_80223BBC,
                                  lbl_80223BC0, lbl_80223BE4,  lbl_80223E1C,
                                  lbl_80223E24, 0x00000001,    NULL,
                                  0UL };

extern StageInfo stage_info;

static void func_80223B48(long) {}
static void lbl_80223B4C(void)
{
    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 1;
    func_80223BEC(0);
    func_80223BEC(1);
    func_80223BEC(2);
    func_801C39C0();
    func_801C3BB4();
    func_801C4210();
    func_801C42AC();
}
static void lbl_80223BBC(void) {}
static void lbl_80223BC0(void)
{
    func_801CAE04(0);
}
static s32 lbl_80223BE4(void)
{
    return 0;
}
static HSD_GObj* func_80223BEC(s32 gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &lbl_803E9578[gobj_id];

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
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grtyoshi.c", 0xc3,
                 gobj_id);
    }

    return gobj;
}
static void lbl_80223CD4(HSD_GObj* gobj)
{
    Map* map = gobj->user_data;
    func_801C8138(gobj, map->map_id, 0);
}
static s32 lbl_80223D00(void)
{
    return 0;
}
static void lbl_80223D08(HSD_GObj*) {}
static void lbl_80223D0C(void) {}
static void lbl_80223D10(HSD_GObj* gobj)
{
    u32 unused[2];
    Map* map = gobj->user_data;
    func_801C2ED0(gobj->hsd_obj, map->map_id);
    func_801C8138(gobj, map->map_id, 0);
}
static s32 lbl_80223D60(void)
{
    return 0;
}
static void lbl_80223D68(HSD_GObj* gobj)
{
    func_800115F4();
    func_801C2FE0(gobj);
}
static void lbl_80223D9C(void) {}
static void lbl_80223DA0(HSD_GObj* gobj)
{
    u32 unused[2];
    Map* map = gobj->user_data;
    func_801C2ED0(gobj->hsd_obj, map->map_id);
    func_801C8138(gobj, map->map_id, 0);
}
static s32 lbl_80223DF0(void)
{
    return 0;
}
static void lbl_80223DF8(HSD_GObj*)
{
    func_801C2FE0();
}
static void lbl_80223E18(void) {}

static BOOL lbl_80223E1C(long)
{
    return FALSE;
}
static s32 lbl_80223E24(Vec3*, s32, struct _HSD_JObj*)
{
    return TRUE;
}
