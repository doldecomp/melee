#include <platform.h>

#include "it/forward.h"
#include "lb/forward.h"

#include "gr/grstory.h"

#include "gr/granime.h"
#include "gr/grdisplay.h"
#include "gr/grlib.h"
#include "gr/grmaterial.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/types.h"
#include "it/it_26B1.h"
#include "it/items/itheiho.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"

#include <dolphin/os/OSError.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>
#include <baselib/random.h>

/* 1E302C */ static void grStory_801E302C(bool);
/* 1E36D0 */ static DynamicsDesc* grStory_801E36D0(enum_t);

extern StageInfo stage_info;

static StageCallbacks grSt_803E26F0[4] = {
    { NULL, NULL, NULL, NULL, 0 },
    { grStory_801E31C0, grStory_801E3224, grStory_801E322C, grStory_801E3230,
      0 },
    { grStory_801E3370, grStory_801E33D8, grStory_801E33E0, grStory_801E3414,
      0 },
    { grStory_801E3234, grStory_801E332C, grStory_801E3334, grStory_801E336C,
      (1 << 30) | (1 << 31) },
};

static struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 vars[7];
}* grSt_804D69B8;

StageData grSt_803E274C = {
    (1 << 1) | (1 << 3),
    grSt_803E26F0,
    "/GrSt.dat",
    grStory_801E3030,
    grStory_801E302C,
    grStory_801E30A8,
    grStory_801E30AC,
    grStory_801E30D0,
    grStory_801E36D0,
    grStory_801E36D8,
    (1 << 0),
    NULL,
    0,
};

static void grStory_801E302C(bool _) {}

void grStory_801E3030(void)
{
    grSt_804D69B8 = Ground_801C49F8();
    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = true;
    grStory_801E30D8(0);
    grStory_801E30D8(1);
    grStory_801E30D8(3);
    grStory_801E30D8(2);
    Ground_801C39C0();
    Ground_801C3BB4();
}

void grStory_801E30A8(void) {}

void grStory_801E30AC(void)
{
    grZakoGenerator_801CAE04(false);
}

bool grStory_801E30D0(void)
{
    return false;
}

HSD_GObj* grStory_801E30D8(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grSt_803E26F0[gobj_id];

    gobj = Ground_801C14D0(gobj_id);

    if (gobj != NULL) {
        Ground* gp = gobj->user_data;
        gp->x8_callback = NULL;
        gp->xC_callback = NULL;
        GObj_SetupGXLink(gobj, grDisplay_801C5DB0, 3, 0);
        if (callbacks->callback3 != NULL) {
            gp->x1C_callback = callbacks->callback3;
        }
        // 0x80
        if (callbacks->callback0 != NULL) {
            callbacks->callback0(gobj);
        }
        // 0x94
        if (callbacks->callback2 != NULL) {
            HSD_GObjProc_8038FD54(gobj, callbacks->callback2, 4);
        }
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grstory.c", 220,
                 gobj_id);
    }

    return gobj;
}

void grStory_801E31C0(HSD_GObj* gobj)
{
    u8 _[8];

    Ground* gp = gobj->user_data;
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x11_flags.b012 = 2;
    grMaterial_801C8858(Ground_801C3FA4(gobj, 1), 0x20000000);
}

bool grStory_801E3224(HSD_GObj* arg0)
{
    return false;
}

void grStory_801E322C(HSD_GObj* arg0) {}

void grStory_801E3230(HSD_GObj* arg0) {}

inline s32 randi(s32 max)
{
    return max ? HSD_Randi(max) : 0;
}

/* Initialize shyguys */
void grStory_801E3234(HSD_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    Ground_801C2ED0(gobj->hsd_obj, gp->map_id);
    grAnime_801C7FF8(gobj, 0, 7, 0, 0.0f, 1.0f);
    grAnime_801C7FF8(gobj, 5, 7, 1, 0.0f, 1.0f);

    gp->gv.unk.xC8 = grSt_804D69B8->unk0 + randi(grSt_804D69B8->unk4);
    gp->gv.unk.xC8 = 120;
    gp->x10_flags.b5 = true;
}

bool grStory_801E332C(HSD_GObj* arg0)
{
    return false;
}

void grStory_801E3334(HSD_GObj* gobj)
{
    grStory_801E3418(gobj);
    Ground_801C2FE0(gobj);
    lb_800115F4();
}

void grStory_801E336C(HSD_GObj* arg0) {}

typedef struct {
    u8 x0_fill[0x14];
    s32 x14;
    u8 x18_fill[0xC4 - 0x18];
    s16 xC4;
    HSD_JObj* xC8;
} UnkUserData;

void grStory_801E3370(HSD_GObj* gobj)
{
    UnkUserData* data = gobj->user_data;

    u8 _[8];

    Ground_801C2ED0(gobj->hsd_obj, data->x14);
    grAnime_801C8138(gobj, data->x14, 0);
    data->xC4 = 0;
    data->xC8 = Ground_801C3FA4(gobj, 1);
}

bool grStory_801E33D8(HSD_GObj* arg0)
{
    return false;
}

void grStory_801E33E0(HSD_GObj* gobj)
{
    Ground_801C2FE0(gobj);
    grStory_801E366C(gobj);
}

void grStory_801E3414(HSD_GObj* arg0) {}

// floating point random number centered at 0
// with an amplitude of 1
inline f32 frand_amp1(void)
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
void grStory_801E3418(HSD_GObj* gobj)
{
    Vec3 pos;
    s32 spawn_pattern;
    s32 i;
    s32 tmp;

    u8 _[8];

    UnkUserData2* gp = gobj->user_data;

    // Don't trigger if any shy guys are still onscreen
    if (it_8026B3C0(It_Kind_Heiho) != 0) {
        return;
    }

    // Wait until the shy guy timer has triggered
    tmp = gp->xC8;
    if (tmp != 0) {
        gp->xC8 = tmp - 1;
        return;
    }
    // Reset the timer
    gp->xC8 = grSt_804D69B8->unk0 + randi(grSt_804D69B8->unk4);
    // This value really is overwritten in the game code.
    // Maybe a leftover hardcoded value from debugging?
    gp->xC8 = 120;

    // Pick a random spawn pattern,
    // which must be different from the previous one
    do {
        spawn_pattern = randi(6);
    } while (gp->xC5 == spawn_pattern);
    gp->xC5 = spawn_pattern;

    // Choose whether they will spawn on the left or the right
    if (spawn_pattern < 3) {
        pos.x = -292.0f;
    } else {
        pos.x = 304.0f;
    }
    pos.y = grSt_804D69B8->vars[spawn_pattern];
    pos.z = 2.0f;

    {
        s32 temp_r29 = randi(3);

        // Spawn either 1, or 3-6 shy guys
        if (randi(grSt_804D69B8->unk8) == 0) {
            gp->xC4 = randi(3) + 3;
        } else {
            gp->xC4 = 1;
        }
        // Another overwrite, possible debugging?
        if (randi(2) == 0) {
            gp->xC4 = randi(3) + 3;
        } else {
            gp->xC4 = 1;
        }
        for (i = 0; i < gp->xC4; i++) {
            it_802D8618(i, &pos, temp_r29, 25.0f * i);
            // it_802D8618(i, temp_r29, 0, 0);
            // Jitter the vertical position of the each subsequent shy guy
            pos.y = 3.0f * frand_amp1() + grSt_804D69B8->vars[spawn_pattern];
        }
    }
}

void grStory_801E366C(HSD_GObj* gobj)
{
    UnkUserData* data = gobj->user_data;

    if (data->xC4-- >= 0) {
        return;
    }

    if (data->xC8 != NULL) {
        grLib_801C97DC(0x2C, 0, data->xC8);
        data->xC4 = HSD_Randi(20) + 10;
    }
}

static DynamicsDesc* grStory_801E36D0(enum_t arg0)
{
    return NULL;
}

bool grStory_801E36D8(Vec3* a, int _, HSD_JObj* joint)
{
    Vec3 b;
    lb_8000B1CC(joint, NULL, &b);

    if (a->y + 1.0f > b.y) {
        return true;
    } else {
        return false;
    }
}

#ifndef BUGFIX
static u32 _[] = {
    0xC3920000, 0x42D20000, 0xC3920000, 0x42960000, 0xC3920000, 0x42480000,
    0x43980000, 0x42DC0000, 0x43980000, 0x42B40000, 0,          0,
};
#endif
