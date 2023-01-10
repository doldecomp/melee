#include <melee/gr/grtdonkey.h>

#include <dolphin/os/os.h>
#include <melee/gr/grdisplay.h>
#include <melee/gr/ground.h>

static StageCallbacks lbl_803E8790[4] = {
    { lbl_802203B4, lbl_802203E0, lbl_802203E8, lbl_802203EC, 0UL },
    { lbl_80220480, lbl_802204D0, lbl_802204D8, lbl_802204F8, 0UL },
    { lbl_802203F0, lbl_80220440, lbl_80220448, lbl_8022047C, 0xC0000000 },
    { NULL, NULL, NULL, NULL, 0UL }
};

extern StageData lbl_803E87EC = { 0x0000002B,   lbl_803E8790,  "/GrTDk.dat",
                                  lbl_8022022C, func_80220228, lbl_8022029C,
                                  lbl_802202A0, lbl_802202C4,  lbl_802204FC,
                                  lbl_80220504, 0x00000001,    NULL,
                                  0UL };

extern StageInfo stage_info;

static void func_80220228(long) {}
static void lbl_8022022C(void)
{
    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 1;
    func_802202CC(0);
    func_802202CC(1);
    func_802202CC(2);
    func_801C39C0();
    func_801C3BB4();
    func_801C4210();
    func_801C42AC();
}
static void lbl_8022029C(void) {}
static void lbl_802202A0(void)
{
    func_801CAE04(0);
}
static s32 lbl_802202C4(void)
{
    return 0;
}
static HSD_GObj* func_802202CC(s32 gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &lbl_803E8790[gobj_id];

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
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grtdonkey.c", 0xc3,
                 gobj_id);
    }

    return gobj;
}
static void lbl_802203B4(HSD_GObj* gobj)
{
    Map* map = gobj->user_data;
    func_801C8138(gobj, map->map_id, 0);
}
static s32 lbl_802203E0(void)
{
    return 0;
}
static void lbl_802203E8(HSD_GObj*) {}
static void lbl_802203EC(void) {}
static void lbl_802203F0(HSD_GObj* gobj)
{
    u32 unused[2];
    Map* map = gobj->user_data;
    func_801C2ED0(gobj->hsd_obj, map->map_id);
    func_801C8138(gobj, map->map_id, 0);
}
static s32 lbl_80220440(void)
{
    return 0;
}
static void lbl_80220448(HSD_GObj* gobj)
{
    func_800115F4();
    func_801C2FE0(gobj);
}
static void lbl_8022047C(void) {}
static void lbl_80220480(HSD_GObj* gobj)
{
    u32 unused[2];
    Map* map = gobj->user_data;
    func_801C2ED0(gobj->hsd_obj, map->map_id);
    func_801C8138(gobj, map->map_id, 0);
}
static s32 lbl_802204D0(void)
{
    return 0;
}
static void lbl_802204D8(HSD_GObj*)
{
    func_801C2FE0();
}
static void lbl_802204F8(void) {}
static int lbl_802204FC(long)
{
    return 0;
}
static s32 lbl_80220504(Vec*, s32, struct _HSD_JObj*)
{
    return 1;
}
