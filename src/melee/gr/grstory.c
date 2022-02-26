#include "grstory.h"

#include <sysdolphin/baselib/random.h>

extern StageInfo stage_info;

struct {
    f32 unk0;
    f32 unk4;
}* lbl_804D69B8;

void func_801E302C(void)
{
}

void func_801E3030(void)
{
    lbl_804D69B8 = func_801C49F8();
    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 1;
    func_801E30D8(0);
    func_801E30D8(1);
    func_801E30D8(3);
    func_801E30D8(2);
    func_801C39C0();
    func_801C3BB4();
}

void lbl_801E30A8(void)
{
}

void lbl_801E30AC(void)
{
    func_801CAE04(0);
}

s32 lbl_801E30D0(void)
{
    return 0;
}

HSD_GObj* func_801E30D8(s32 arg0)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &lbl_803E26F0.callbacks[arg0];

    gobj = func_801C14D0(arg0);
    if (gobj != NULL) {
        Map* map = gobj->user_data;
        map->x8 = 0;
        map->xC = 0;
        GObj_SetupGXLink(gobj, func_801C5DB0, 3, 0);
        if (callbacks->callback3 != NULL) {
            map->x1C_callback = callbacks->callback3;
        }
        // 0x80
        if (callbacks->callback0 != NULL) {
            callbacks->callback0(gobj);
        }
        // 0x94
        if (callbacks->callback2 != NULL) {
            func_8038FD54(gobj, callbacks->callback2, 4);
        }
    } else {
        OSReport(lbl_803E26F0.str1, lbl_803E26F0.str2, 0xDC, arg0);
    }

    return gobj;
}

void lbl_801E31C0(HSD_GObj* gobj)
{
    Map* map = gobj->user_data;
    int unused[2];
    func_801C8138(gobj, map->map_id, 0);
    map->x11_flags.b012 = 2;
    func_801C8858(func_801C3FA4(gobj, 1), 0x20000000);
}

s32 lbl_801E3224(void)
{
    return 0;
}

void lbl_801E322C(void)
{
}

void lbl_801E3230(void)
{
}

inline s32 randi(s32 max)
{
    return max ? HSD_Randi(max) : 0;
}

/* Initialize shyguys */
void lbl_801E3234(HSD_GObj* gobj)
{
    Map* map = gobj->user_data;
    func_801C2ED0(gobj->hsd_obj, map->map_id);
    func_801C7FF8(gobj, 0, 7, 0, 0.0f, 1.0f);
    func_801C7FF8(gobj, 5, 7, 1, 0.0f, 1.0f);

    map->xC8 = lbl_804D69B8->unk0 + randi(lbl_804D69B8->unk4);
    map->xC8 = 120;
    map->x10_flags.b5 = 1;
}

s32 lbl_801E332C(void)
{
    return 0;
}

void lbl_801E3334(HSD_GObj* gobj)
{
    func_801E3418(gobj);
    func_801C2FE0(gobj);
    func_800115F4();
}

void lbl_801E336C()
{
}

void lbl_801E3370(HSD_GObj* gobj)
{
    Map* map = gobj->user_data;
    int unused[2];
    func_801C2ED0(gobj->hsd_obj, map->map_id);
    func_801C8138(gobj, map->map_id, 0);
    map->xC4 = 0;
    map->xC8 = func_801C3FA4(gobj, 1);
}

s32 lbl_801E33D8(void)
{
    return 0;
}

void lbl_801E33E0(HSD_GObj* gobj)
{
    func_801C2FE0(gobj);
    func_801E366C(gobj);
}

void lbl_801E3414(void)
{
}
