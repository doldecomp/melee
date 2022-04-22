#include "grbattle.h"

#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/random.h>

extern StageInfo stage_info;

struct {
    s32 unk0;
    s32 unk4;
}* lbl_804D6ACC;

static u8 lbl_804D6AC8;

static const int BATTLE_BG_MAX = 3;

static StageCallbacks lbl_803E7DA0[7] = {
    {
        lbl_80219E6C,
        lbl_8021A10C,
        lbl_8021A114,
        lbl_8021A118,
        0,
    },
    {
        lbl_8021A20C,
        lbl_8021A264,
        lbl_8021A26C,
        lbl_8021A270,
        0,
    },
    {
        lbl_8021A274,
        lbl_8021A2CC,
        lbl_8021A2D4,
        lbl_8021A2D8,
        0,
    },
    {
        lbl_8021A344,
        lbl_8021A3B4,
        lbl_8021A3BC,
        lbl_8021A60C,
        0,
    },
    {
        lbl_8021A2DC,
        lbl_8021A334,
        lbl_8021A33C,
        lbl_8021A340,
        0,
    },
    {
        lbl_8021A19C,
        lbl_8021A1FC,
        lbl_8021A204,
        lbl_8021A208,
        0,
    },
    {
        lbl_8021A11C,
        lbl_8021A16C,
        lbl_8021A174,
        lbl_8021A198,
        0xC0000000,
    },
};

StageData lbl_803E7E38 = {
    0x00000024,
    lbl_803E7DA0,
    "/GrNBa.dat",
    lbl_80219CA4,
    func_80219C98,
    lbl_80219D54,
    lbl_80219D58,
    lbl_80219D7C,
    lbl_8021A610,
    lbl_8021A618,
    0x00000001,
};


static void func_80219C98()
{
    lbl_804D6AC8 = 1;
}

static void lbl_80219CA4()
{
    lbl_804D6ACC = func_801C49F8();
    stage_info.unk8C.b4 = 1;
    stage_info.unk8C.b5 = 1;

    func_80219D84(0);
    if (func_8016B3D8() != 0 || Stage_80225194() == 0x111 ||
        Stage_80225194() == 0xF5) {
        func_80219D84(5);
    } else {
        func_80219D84(3);
        func_80219D84(1);
    }
    func_80219D84(6);
    func_801C39C0();
    func_801C3BB4();
    func_801C9A10();
    lbl_804D6AC8 = 0;
}

static void lbl_80219D54()
{
}

static void lbl_80219D58()
{
    func_801CAE04(0);
}

static s32 lbl_80219D7C()
{
    return 0;
}

static HSD_GObj* func_80219D84(s32 arg0)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &lbl_803E7DA0[arg0];

    gobj = func_801C14D0(arg0);
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
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 232, arg0);
    }
    return gobj;
}

static void lbl_80219E6C(HSD_GObj* gobj)
{
    Vec3 v;
    Map* map = gobj->user_data;
    int id = map->map_id;

    func_801C8138(gobj, id, 0);
    if (lbl_804D6AC8 == 0) {
        return;
    }

    func_801C9A70(0, &v);
    HSD_JObjSetTranslate(func_801C2CF4(0), &v);

    func_801C9A70(1, &v);
    HSD_JObjSetTranslate(func_801C2CF4(1), &v);

    func_801C9A70(2, &v);
    HSD_JObjSetTranslate(func_801C2CF4(2), &v);

    func_801C9A70(3, &v);
    HSD_JObjSetTranslate(func_801C2CF4(3), &v);
}

static s32 lbl_8021A10C()
{
    return 0;
}

static void lbl_8021A114()
{
}

static void lbl_8021A118()
{
}

static void lbl_8021A11C(HSD_GObj* gobj)
{
    u32 unused[2];
    Map* map = gobj->user_data;
    func_801C2ED0(gobj->hsd_obj, map->map_id);
    func_801C8138(gobj, map->map_id, 0);
}

static s32 lbl_8021A16C()
{
    return 0;
}

static void lbl_8021A174(HSD_GObj* gobj)
{
    func_801C2FE0(gobj);
    func_800115F4();
}

static void lbl_8021A198()
{
}

static void lbl_8021A19C(HSD_GObj* gobj)
{
    u32 unused[2];
    Map* map = gobj->user_data;
    func_801C2ED0(gobj->hsd_obj, map->map_id);
    func_801C8138(gobj, map->map_id, 0);
    map->x11_flags.b012 = 2;
}

static s32 lbl_8021A1FC()
{
    return 0;
}

static void lbl_8021A204()
{
}

static void lbl_8021A208()
{
}

static void lbl_8021A20C(HSD_GObj* gobj)
{
    u32 unused[2];
    Map* map = gobj->user_data;
    void* hsd_obj = gobj->hsd_obj;
    func_801C8138(gobj, map->map_id, 0);
    func_801C94D8(hsd_obj);
    map->x11_flags.b012 = 2;
}

static s32 lbl_8021A264()
{
    return 0;
}

static void lbl_8021A26C()
{
}

static void lbl_8021A270()
{
}

static void lbl_8021A274(HSD_GObj* gobj)
{
    u32 unused[2];
    Map* map = gobj->user_data;
    void* hsd_obj = gobj->hsd_obj;
    func_801C8138(gobj, map->map_id, 0);
    func_801C94D8(hsd_obj);
    map->x11_flags.b012 = 2;
}

static s32 lbl_8021A2CC()
{
    return 0;
}

static void lbl_8021A2D4()
{
}

static void lbl_8021A2D8()
{
}

static void lbl_8021A2DC(HSD_GObj* gobj)
{
    u32 unused[2];
    Map* map = gobj->user_data;
    void* hsd_obj = gobj->hsd_obj;
    func_801C8138(gobj, map->map_id, 0);
    func_801C94D8(hsd_obj);
    gobj;
    map->x11_flags.b012 = 2;
}

static s32 lbl_8021A334()
{
    return 0;
}

static void lbl_8021A33C()
{
}

static void lbl_8021A340()
{
}

static void lbl_8021A344(HSD_GObj* gobj)
{
    u32 unused[6];
    Map* map = gobj->user_data;
    HSD_JObj* jobj = gobj->hsd_obj;
    map->x11_flags.b012 = 2;
    map->xC4 = 0;
    map->xD0 = HSD_Randi(1200) + 2400;
    map->xC8 = -1;
    HSD_JObjSetFlagsAll(jobj, 0x10);
}

static s32 lbl_8021A3B4()
{
    return 0;
}

static void lbl_8021A3BC(HSD_GObj* gobj)
{
    Map* map = gobj->user_data;
    HSD_JObj* jobj = gobj->hsd_obj;
    HSD_GObj* bg_gobj;
    s32 temp_r0_2;
    s16 sp28[BATTLE_BG_MAX] = {1, 2, 4};
    s32 tmp;
    u32 unused[7];

    switch (map->xC4) {
        case 0:
            if (map->xD0-- < 0) {
                map->xC4 = 1;
                func_801C8138(gobj, map->map_id, 0);
            }
            break;
        case 1:
            if (HSD_JObjGetFlags(jobj) & 0x10) {
                HSD_JObjClearFlagsAll(jobj, 0x10);
            }
            if (func_801C83D0(gobj, 0, 7)) {
                if (map->xC8 == -1) {
                    u32 i;
                    for (i = 0; i < BATTLE_BG_MAX; i++) {
                        if (func_801C2BA4(sp28[i])) {
                            map->xC8 = sp28[i];
                            break;
                        }
                    }
                    assert_line(527, i<BATTLE_BG_MAX);
                }
                map->xCC = map->xC8;
                do {
                    temp_r0_2 = sp28[HSD_Randi(BATTLE_BG_MAX)];
                } while ((tmp = map->xCC) == (map->xC8 = temp_r0_2));

                bg_gobj = func_801C2BA4(tmp);
                assert_line(535, bg_gobj);
                func_801C9604(bg_gobj, lbl_804D6ACC->unk4, 0);

                bg_gobj = func_80219D84(map->xC8);
                assert_line(539, bg_gobj);
                func_801C9604(bg_gobj, lbl_804D6ACC->unk0, 0);

                map->xC4 = 2;
            }
            break;
        case 2:
            bg_gobj = func_801C2BA4(map->xCC);
            assert_line(546, bg_gobj);
            if (func_801C96E8(bg_gobj)) {
                func_801C4A08(bg_gobj);
                HSD_JObjSetFlagsAll(jobj, 0x10);
                map->xC4 = 0;
                map->xD0 = HSD_Randi(1200) + 2400;
            }
            break;
    }
}

static void lbl_8021A60C()
{
}

static BOOL lbl_8021A610(s32)
{
    return FALSE;
}

static s32 lbl_8021A618()
{
    return 1;
}
