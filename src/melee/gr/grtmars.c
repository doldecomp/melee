#include <melee/gr/grtmars.h>

#include <functions.h>
#include <melee/gr/stage.h>
#include <sysdolphin/baselib/gobjgxlink.h>

extern StageInfo stage_info;

static StageCallbacks lbl_803E8EB0[4] = {
    {
        GrTMars_80222080,
        GrTMars_802220AC,
        GrTMars_802220B4,
        GrTMars_802220B8,
    }, {
        GrTMars_8022214C,
        GrTMars_8022219C,
        GrTMars_802221A4,
        GrTMars_802221C4,
    }, {
        GrTMars_802220BC,
        GrTMars_8022210C,
        GrTMars_80222114,
        GrTMars_80222148,
        0xC0000000,
    }
};

StageData lbl_803E8F0C = {
    0x00000034,
    lbl_803E8EB0,
    "/GrTMs.dat",
    GrTMars_80221EF8,
    GrTMars_80221EF4,
    GrTMars_80221F68,
    GrTMars_80221F6C,
    GrTMars_80221F90,
    GrTMars_802221C8,
    GrTMars_802221D0,
    0x00000001,
};

static void GrTMars_80221EF4(s32)
{
}

static void GrTMars_80221EF8(void)
{
    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 1;
    GrTMars_80221F98(0);
    GrTMars_80221F98(1);
    GrTMars_80221F98(2);
    func_801C39C0();
    func_801C3BB4();
    func_801C4210();
    func_801C42AC();
}

static void GrTMars_80221F68(void)
{
    return;
}

static void GrTMars_80221F6C(void)
{
    func_801CAE04(0);
}

static s32 GrTMars_80221F90(void)
{
    return 0;
}

static HSD_GObj* GrTMars_80221F98(s32 id)
{
    HSD_GObj* gobj;
    Map* gp;
    StageCallbacks* callbacks;

    callbacks = &lbl_803E8EB0[id];
    gobj = func_801C14D0(id);
    if (gobj != NULL) {
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
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grtmars.c", 0xC3, id);
    }
    return gobj;
}

static void GrTMars_80222080(HSD_GObj* gobj)
{
    Map* gp = gobj->user_data;
    func_801C8138(gobj, gp->map_id, 0);
}

static s32 GrTMars_802220AC(void)
{
    return FALSE;
}

static void GrTMars_802220B4(HSD_GObj*)
{
    return;
}

static void GrTMars_802220B8(void)
{
    return;
}

static void GrTMars_802220BC(HSD_GObj* gobj)
{
    Map* gp = gobj->user_data;
    u32 unused[2];
    func_801C2ED0(gobj->hsd_obj, gp->map_id);
    func_801C8138(gobj, gp->map_id, 0);
}

static s32 GrTMars_8022210C(void)
{
    return 0;
}

static void GrTMars_80222114(HSD_GObj* gobj)
{
    func_800115F4();
    func_801C2FE0(gobj);
}

static void GrTMars_80222148(void)
{
}

static void GrTMars_8022214C(HSD_GObj* gobj)
{
    Map* map = gobj->user_data;
    u32 unused[2];
    func_801C2ED0(gobj->hsd_obj, map->map_id);
    func_801C8138(gobj, map->map_id, 0);
}

static s32 GrTMars_8022219C(void)
{
    return 0;
}

static void GrTMars_802221A4(HSD_GObj* gobj)
{
    func_801C2FE0(gobj);
}

static void GrTMars_802221C4(void)
{
}

static BOOL GrTMars_802221C8(s32)
{
    return FALSE;
}

static s32 GrTMars_802221D0(Vec*, s32, struct _HSD_JObj*)
{
    return 1;
}
