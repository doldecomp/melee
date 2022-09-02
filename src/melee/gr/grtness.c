#include <melee/gr/grtness.h>

#include <melee/gr/stage.h>

extern StageInfo stage_info;

static StageCallbacks lbl_803E9030[4] = {
    {
        GrTNess_8022275C,
        GrTNess_80222788,
        GrTNess_80222790,
        GrTNess_80222794,
    }, {
        GrTNess_80222828,
        GrTNess_80222878,
        GrTNess_80222880,
        GrTNess_802228A0,
    }, {
        GrTNess_80222798,
        GrTNess_802227E8,
        GrTNess_802227F0,
        GrTNess_80222824,
        0xC0000000,
    },
};

StageData lbl_803E908C = {
    0x00000036,
    lbl_803E9030,
    "/GrTNs.dat",
    GrTNess_802225D4,
    GrTNess_802225D0,
    GrTNess_80222644,
    GrTNess_80222648,
    GrTNess_8022266C,
    GrTNess_802228A4,
    GrTNess_802228AC,
    0x00000001,
};

static void GrTNess_802225D0(s32)
{
    return;
}

static void GrTNess_802225D4(void)
{
    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 1;
    GrTNess_80222674(0);
    GrTNess_80222674(1);
    GrTNess_80222674(2);
    func_801C39C0();
    func_801C3BB4();
    func_801C4210();
    func_801C42AC();
}

static void GrTNess_80222644(void)
{
    return;
}

static void GrTNess_80222648(void)
{
    func_801CAE04(0);
}

static s32 GrTNess_8022266C(void)
{
    return 0;
}

static HSD_GObj* GrTNess_80222674(int id)
{
    HSD_GObj* gobj;
    Map* gp;
    StageCallbacks* cb = &lbl_803E9030[id];
    gobj = func_801C14D0(id);
    if (gobj != NULL) {
        gp = gobj->user_data;
        gp->x8_callback = NULL;
        gp->xC_callback = NULL;
        GObj_SetupGXLink(gobj, func_801C5DB0, 3, 0);
        if (cb->callback3 != 0U) {
            gp->x1C_callback = cb->callback3;
        }
        if (cb->callback0 != 0U) {
            cb->callback0(gobj);
        }
        if (cb->callback2 != 0U) {
            func_8038FD54(gobj, cb->callback2, 4);
        }
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grtness.c", 0xC3, id);
    }
    return gobj;
}

static void GrTNess_8022275C(HSD_GObj* gobj)
{
    Map* gp = gobj->user_data;
    func_801C8138(gobj, gp->map_id, 0);
}

static s32 GrTNess_80222788(void)
{
    return 0;
}

static void GrTNess_80222790(HSD_GObj*)
{
    return;
}

static void GrTNess_80222794(void)
{
    return;
}

static void GrTNess_80222798(HSD_GObj* gobj)
{
    u32 unused[2];
    Map* gp = gobj->user_data;
    func_801C2ED0(gobj->hsd_obj, gp->map_id);
    func_801C8138(gobj, gp->map_id, 0);
}

static s32 GrTNess_802227E8(void)
{
    return 0;
}

static void GrTNess_802227F0(HSD_GObj* gobj)
{
    func_800115F4();
    func_801C2FE0(gobj);
}

static void GrTNess_80222824(void)
{
    return;
}

static void GrTNess_80222828(HSD_GObj* gobj)
{
    u32 unused[2];
    Map* gp = gobj->user_data;
    func_801C2ED0(gobj->hsd_obj, gp->map_id);
    func_801C8138(gobj, gp->map_id, 0);
}

static s32 GrTNess_80222878(void)
{
    return 0;
}

static void GrTNess_80222880(HSD_GObj* gobj)
{
    func_801C2FE0(gobj);
}

static void GrTNess_802228A0(void)
{
    return;
}

static BOOL GrTNess_802228A4(s32)
{
    return FALSE;
}

static s32 GrTNess_802228AC(Vec*, s32, struct _HSD_JObj*)
{
    return TRUE;
}
