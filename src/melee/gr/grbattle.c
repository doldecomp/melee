#include <melee/gr/grbattle.h>

#include <dolphin/os/os.h>
#include <melee/gm/code_801601C4.h>
#include <melee/gr/granime.h>
#include <melee/gr/grdisplay.h>
#include <melee/gr/grlib.h>
#include <melee/gr/grmaterial.h>
#include <melee/gr/ground.h>
#include <melee/gr/grzakogenerator.h>
#include <melee/lb/lbunknown_003.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/random.h>

extern StageInfo stage_info;

struct {
    int unk0;
    int unk4;
}* lbl_804D6ACC;

static u8 lbl_804D6AC8;

static const int BATTLE_BG_MAX = 3;

static StageCallbacks lbl_803E7DA0[7] = {
    {
        func_80219E6C,
        func_8021A10C,
        func_8021A114,
        func_8021A118,
        0,
    },
    {
        func_8021A20C,
        func_8021A264,
        func_8021A26C,
        func_8021A270,
        0,
    },
    {
        func_8021A274,
        func_8021A2CC,
        func_8021A2D4,
        func_8021A2D8,
        0,
    },
    {
        func_8021A344,
        func_8021A3B4,
        func_8021A3BC,
        func_8021A60C,
        0,
    },
    {
        func_8021A2DC,
        func_8021A334,
        func_8021A33C,
        func_8021A340,
        0,
    },
    {
        func_8021A19C,
        func_8021A1FC,
        func_8021A204,
        func_8021A208,
        0,
    },
    {
        func_8021A11C,
        func_8021A16C,
        func_8021A174,
        func_8021A198,
        0xC0000000,
    },
};

/// @todo Not ideal @c clang-format behavior.
/// Removing the trailing comma is arguably worse.
StageData lbl_803E7E38 = {
    0x00000024,
    lbl_803E7DA0,
    "/GrNBa.dat",
    func_80219CA4,
    func_80219C98,
    func_80219D54,
    func_80219D58,
    func_80219D7C,
    func_8021A610,
    func_8021A618,
    0x00000001,
    NULL,
    0,
};

static void func_80219C98(void)
{
    lbl_804D6AC8 = 1;
}

static void func_80219CA4(void)
{
    lbl_804D6ACC = func_801C49F8();
    stage_info.unk8C.b4 = 1;
    stage_info.unk8C.b5 = 1;

    func_80219D84(0);
    if (func_8016B3D8() || Stage_80225194() == 0x111 ||
        Stage_80225194() == 0xF5)
    {
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

static void func_80219D54(void) {}

static void func_80219D58(void)
{
    func_801CAE04(false);
}

static bool func_80219D7C(void)
{
    return false;
}

static HSD_GObj* func_80219D84(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &lbl_803E7DA0[gobj_id];

    gobj = func_801C14D0(gobj_id);

    if (gobj != NULL) {
        Map* map = gobj->user_data;
        map->x8_callback = NULL;
        map->xC_callback = NULL;
        GObj_SetupGXLink(gobj, func_801C5DB0, 3, 0);

        if (callbacks->callback3 != NULL)
            map->x1C_callback = callbacks->callback3;

        if (callbacks->callback0 != NULL)
            callbacks->callback0(gobj);

        if (callbacks->callback2 != NULL)
            func_8038FD54(gobj, callbacks->callback2, 4);

    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 232, gobj_id);
    }

    return gobj;
}

static void func_80219E6C(HSD_GObj* gobj)
{
    Vec3 v;
    Map* map = gobj->user_data;
    enum_t id = map->map_id;

    func_801C8138(gobj, id, 0);

    if (lbl_804D6AC8 == 0)
        return;

    func_801C9A70(0, &v);
    HSD_JObjSetTranslate(func_801C2CF4(0), &v);

    func_801C9A70(1, &v);
    HSD_JObjSetTranslate(func_801C2CF4(1), &v);

    func_801C9A70(2, &v);
    HSD_JObjSetTranslate(func_801C2CF4(2), &v);

    func_801C9A70(3, &v);
    HSD_JObjSetTranslate(func_801C2CF4(3), &v);
}

bool func_8021A10C(void)
{
    return false;
}

static void func_8021A114(HSD_GObj* arg0) {}

static void func_8021A118(HSD_GObj* arg0) {}

static void func_8021A11C(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused[8];
#endif

    Map* map = gobj->user_data;
    func_801C2ED0(gobj->hsd_obj, map->map_id);
    func_801C8138(gobj, map->map_id, 0);
}

static bool func_8021A16C(void)
{
    return false;
}

static void func_8021A174(HSD_GObj* gobj)
{
    func_801C2FE0(gobj);
    func_800115F4();
}

static void func_8021A198(HSD_GObj* arg0) {}

static void func_8021A19C(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused[8];
#endif

    Map* map = gobj->user_data;
    func_801C2ED0(gobj->hsd_obj, map->map_id);
    func_801C8138(gobj, map->map_id, 0);
    map->x11_flags.b012 = 2;
}

static bool func_8021A1FC(HSD_GObj* arg0)
{
    return false;
}

static void func_8021A204(HSD_GObj* arg0) {}

static void func_8021A208(HSD_GObj* arg0) {}

static void func_8021A20C(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused[8];
#endif

    Map* map = gobj->user_data;

    /// @todo Missing cast
    unk_t hsd_obj = gobj->hsd_obj;

    func_801C8138(gobj, map->map_id, 0);
    func_801C94D8(hsd_obj);
    map->x11_flags.b012 = 2;
}

static bool func_8021A264(HSD_GObj* arg0)
{
    return false;
}

static void func_8021A26C(HSD_GObj* arg0) {}

static void func_8021A270(HSD_GObj* arg0) {}

static void func_8021A274(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused[8];
#endif

    Map* map = gobj->user_data;
    void* hsd_obj = gobj->hsd_obj;
    func_801C8138(gobj, map->map_id, 0);
    func_801C94D8(hsd_obj);
    map->x11_flags.b012 = 2;
}

static bool func_8021A2CC(HSD_GObj* arg0)
{
    return false;
}

static void func_8021A2D4(HSD_GObj* arg0) {}

static void func_8021A2D8(HSD_GObj* arg0) {}

static void func_8021A2DC(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused[8];
#endif

    Map* map = gobj->user_data;
    void* hsd_obj = gobj->hsd_obj;
    func_801C8138(gobj, map->map_id, 0);
    func_801C94D8(hsd_obj);
    gobj;
    map->x11_flags.b012 = 2;
}

static bool func_8021A334(HSD_GObj* arg0)
{
    return false;
}

static void func_8021A33C(HSD_GObj* arg0) {}

static void func_8021A340(HSD_GObj* arg0) {}

static void func_8021A344(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused[24];
#endif

    Map* map = gobj->user_data;
    HSD_JObj* jobj = gobj->hsd_obj;
    map->x11_flags.b012 = 2;
    map->xC4 = 0;
    map->xD0 = HSD_Randi(1200) + 2400;
    map->xC8 = -1;
    HSD_JObjSetFlagsAll(jobj, 0x10);
}

static bool func_8021A3B4(HSD_GObj* arg0)
{
    return false;
}

static void func_8021A3BC(HSD_GObj* gobj)
{
    Map* map = gobj->user_data;
    HSD_JObj* jobj = gobj->hsd_obj;
    HSD_GObj* bg_gobj;
    s32 temp_r0_2;
    s16 sp28[BATTLE_BG_MAX] = { 1, 2, 4 };
    s32 tmp;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused[28];
#endif

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
                HSD_ASSERT(527, i<BATTLE_BG_MAX);
            }
            map->xCC = map->xC8;
            do {
                temp_r0_2 = sp28[HSD_Randi(BATTLE_BG_MAX)];
            } while ((tmp = map->xCC) == (map->xC8 = temp_r0_2));

            bg_gobj = func_801C2BA4(tmp);
            HSD_ASSERT(535, bg_gobj);
            func_801C9604(bg_gobj, lbl_804D6ACC->unk4, 0);

            bg_gobj = func_80219D84(map->xC8);
            HSD_ASSERT(539, bg_gobj);
            func_801C9604(bg_gobj, lbl_804D6ACC->unk0, 0);

            map->xC4 = 2;
        }
        break;
    case 2:
        bg_gobj = func_801C2BA4(map->xCC);
        HSD_ASSERT(546, bg_gobj);
        if (func_801C96E8(bg_gobj)) {
            func_801C4A08(bg_gobj);
            HSD_JObjSetFlagsAll(jobj, 0x10);
            map->xC4 = 0;
            map->xD0 = HSD_Randi(1200) + 2400;
        }
        break;
    }
}

static void func_8021A60C(HSD_GObj* arg0) {}

static bool func_8021A610(int arg0)
{
    return false;
}

static bool func_8021A618(void)
{
    return true;
}
