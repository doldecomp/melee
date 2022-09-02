#include <melee/gr/grstory.h>

#include <melee/it/itkind.h>
#include <sysdolphin/baselib/random.h>

extern StageInfo stage_info;

static StageCallbacks lbl_803E26F0[4] = {
    {
        NULL,
        NULL,
        NULL,
        NULL,
    }, {
        func_801E31C0,
        func_801E3224,
        func_801E322C,
        func_801E3230,
    }, {
        func_801E3370,
        func_801E33D8,
        func_801E33E0,
        func_801E3414,
    }, {
        func_801E3234,
        func_801E332C,
        func_801E3334,
        func_801E336C,
        0xC0000000,
    },
};

static struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 vars[7];
}* lbl_804D69B8;

StageData lbl_803E274C = {
    0x0000000A,
    lbl_803E26F0,
    "/GrSt.dat",
    func_801E3030,
    func_801E302C,
    func_801E30A8,
    func_801E30AC,
    func_801E30D0,
    func_801E36D0,
    func_801E36D8,
    0x00000001,
};


static void func_801E302C(s32)
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

void func_801E30A8(void)
{
}

void func_801E30AC(void)
{
    func_801CAE04(0);
}

s32 func_801E30D0(void)
{
    return 0;
}

HSD_GObj* func_801E30D8(s32 arg0)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &lbl_803E26F0[arg0];

    gobj = func_801C14D0(arg0);
    if (gobj != NULL) {
        Map* map = gobj->user_data;
        map->x8_callback = NULL;
        map->xC_callback = NULL;
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
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grstory.c", 220, arg0);
    }

    return gobj;
}

void func_801E31C0(HSD_GObj* gobj)
{
    Map* map = gobj->user_data;
    int unused[2];
    func_801C8138(gobj, map->map_id, 0);
    map->x11_flags.b012 = 2;
    func_801C8858(func_801C3FA4(gobj, 1), 0x20000000);
}

s32 func_801E3224(void)
{
    return 0;
}

void func_801E322C(HSD_GObj*)
{
}

void func_801E3230(void)
{
}

inline s32 randi(s32 max)
{
    return max ? HSD_Randi(max) : 0;
}

/* Initialize shyguys */
void func_801E3234(HSD_GObj* gobj)
{
    Map* map = gobj->user_data;
    func_801C2ED0(gobj->hsd_obj, map->map_id);
    func_801C7FF8(gobj, 0, 7, 0, 0.0f, 1.0f);
    func_801C7FF8(gobj, 5, 7, 1, 0.0f, 1.0f);

    map->xC8 = lbl_804D69B8->unk0 + randi(lbl_804D69B8->unk4);
    map->xC8 = 120;
    map->x10_flags.b5 = 1;
}

s32 func_801E332C(void)
{
    return 0;
}

void func_801E3334(HSD_GObj* gobj)
{
    func_801E3418(gobj);
    func_801C2FE0(gobj);
    func_800115F4();
}

void func_801E336C()
{
}

typedef struct {
    u8 x0_fill[0x14];
    s32 x14;
    u8 x18_fill[0xC4 - 0x18];
    s16 xC4;
    struct _HSD_JObj* xC8;
} UnkUserData;

void func_801E3370(HSD_GObj* gobj)
{
    UnkUserData* data = gobj->user_data;
    int unused[2];
    func_801C2ED0(gobj->hsd_obj, data->x14);
    func_801C8138(gobj, data->x14, 0);
    data->xC4 = 0;
    data->xC8 = func_801C3FA4(gobj, 1);
}

s32 func_801E33D8(void)
{
    return 0;
}

void func_801E33E0(HSD_GObj* gobj)
{
    func_801C2FE0(gobj);
    func_801E366C(gobj);
}

void func_801E3414(void)
{
}

// floating point random number centered at 0
// with an amplitude of 1
inline f32 frand_amp1()
{
    return 2.0f * (HSD_Randf() - 0.5f);
}

typedef struct {
    u8 x0_fill[0xC4];
    s8 xC4;
    s8 xC5;
    s16 xC6;
    s32 xC8;
} UnkUserData2;

// Shy guy spawn timer tick callback
void func_801E3418(HSD_GObj* gobj)
{
    Vec3 pos;
    s32 spawn_pattern;
    s32 i;
    s32 tmp;

    u32 unused[2];

    UnkUserData2* map = gobj->user_data;

    // Don't trigger if any shy guys are still onscreen
    if (func_8026B3C0(It_Kind_Heiho) != 0) {
        return;
    }

    // Wait until the shy guy timer has triggered
    tmp = map->xC8;
    if (tmp != 0) {
        map->xC8 = tmp - 1;
        return;
    }
    // Reset the timer
    map->xC8 = lbl_804D69B8->unk0 + randi(lbl_804D69B8->unk4);
    // This value really is overwritten in the game code.
    // Maybe a leftover hardcoded value from debugging?
    map->xC8 = 120;

    // Pick a random spawn pattern,
    // which must be different from the previous one
    do {
        spawn_pattern = randi(6);
    } while (map->xC5 == spawn_pattern);
    map->xC5 = spawn_pattern;

    // Choose whether they will spawn on the left or the right
    if (spawn_pattern < 3) {
        pos.x = -292.0f;
    } else {
        pos.x = 304.0f;
    }
    pos.y = lbl_804D69B8->vars[spawn_pattern];
    pos.z = 2.0f;

    {
        s32 temp_r29 = randi(3);

        // Spawn either 1, or 3-6 shy guys
        if (randi(lbl_804D69B8->unk8) == 0) {
            map->xC4 = randi(3) + 3;
        } else {
            map->xC4 = 1;
        }
        // Another overwrite, possible debugging?
        if (randi(2) == 0) {
            map->xC4 = randi(3) + 3;
        } else {
            map->xC4 = 1;
        }
        for (i = 0; i < map->xC4; i++) {
            func_802D8618(i, &pos, temp_r29, 25.0f * i);
            // Jitter the vertical position of the each subsequent shy guy
            pos.y = 3.0f * frand_amp1() + lbl_804D69B8->vars[spawn_pattern];
        }
    }
}

void func_801E366C(HSD_GObj* gobj)
{
    UnkUserData* data = gobj->user_data;

    if (data->xC4-- >= 0) {
        return;
    }

    if (data->xC8 != NULL) {
        func_801C97DC(0x2C, 0, data->xC8);
        data->xC4 = HSD_Randi(20) + 10;
    }
}

static BOOL func_801E36D0(s32)
{
    return FALSE;
}

s32 func_801E36D8(Vec3* a, s32 unused, struct _HSD_JObj* joint)
{
    Vec3 b;
    func_8000B1CC(joint, NULL, &b);

    if (a->y + 1.0f > b.y) {
        return TRUE;
    } else {
        return FALSE;
    }
}

static u32 unused[] = {
    0xC3920000,
    0x42D20000,
    0xC3920000,
    0x42960000,
    0xC3920000,
    0x42480000,
    0x43980000,
    0x42DC0000,
    0x43980000,
    0x42B40000,
    0,
    0,
};
