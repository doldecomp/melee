#include "grstory.h"

#include <platform.h>

#include <melee/gr/granime.h>
#include <melee/gr/grdisplay.h>
#include <melee/gr/grlib.h>
#include <melee/gr/grmaterial.h>
#include <melee/gr/ground.h>
#include <melee/gr/grzakogenerator.h>
#include <melee/gr/inlines.h>
#include <melee/gr/types.h>
#include <melee/it/it_26B1.h>
#include <melee/it/items/itheiho.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lb_00F9.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/random.h>

/* 1E302C */ static void grStory_801E302C(bool);
/* 1E36D0 */ static DynamicsDesc* grStory_801E36D0(enum_t);

extern StageInfo stage_info;

static StageCallbacks grSt_803E26F0[] = {
    { NULL, NULL, NULL, NULL, 0 },
    { grStory_801E31C0, grStory_801E3224, grStory_801E322C, grStory_801E3230,
      0 },
    // Randall
    { grStory_801E3370, grStory_801E33D8, grStory_801E33E0, grStory_801E3414,
      0 },
    // Shy Guys
    { grStory_801E3234, grStory_801E332C, grStory_801E3334, grStory_801E336C,
      (1 << 30) | (1 << 31) },
};

static struct {
    float timer_min;
    float timer_rand;
    float spawnmany_rarity;
    float vpos[6];
}* shyguy_vars;

StageData grSt_803E274C = {
    (1 << 1) | (1 << 3),
    grSt_803E26F0,
    "/GrSt.dat",
    grStory_801E3030,
    grStory_801E302C,
    grStory_UnkStage0_OnLoad,
    grStory_UnkStage0_OnStart,
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
    shyguy_vars = Ground_801C49F8();
    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = true;
    grStory_801E30D8(0);
    grStory_801E30D8(1);
    grStory_801E30D8(3);
    grStory_801E30D8(2);
    Ground_801C39C0();
    Ground_801C3BB4();
}

void grStory_UnkStage0_OnLoad(void) {}

void grStory_UnkStage0_OnStart(void)
{
    grZakoGenerator_801CAE04(false);
}

bool grStory_801E30D0(void)
{
    return false;
}

Ground_GObj* grStory_801E30D8(int gobj_id)
{
    Ground_GObj* gobj;
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

void grStory_801E31C0(Ground_GObj* gobj)
{
    u8 _[4];

    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x11_flags.b012 = 2;
    grMaterial_801C8858(Ground_801C3FA4(gobj, 1), 0x20000000);
}

bool grStory_801E3224(Ground_GObj* gobj)
{
    return false;
}

void grStory_801E322C(Ground_GObj* gobj) {}

void grStory_801E3230(Ground_GObj* gobj) {}

inline int randi(int max)
{
    return max ? HSD_Randi(max) : 0;
}

static inline void reset_shyguy_timer(Ground* gp)
{
    // Reset the timer
    gp->u.shyguys.timer = shyguy_vars->timer_min
        + randi(shyguy_vars->timer_rand);

    // This value really is overwritten in the game code.
    // Maybe a leftover hardcoded value from debugging?
    gp->u.shyguys.timer = 120;
}

/**
 * Set the number of Shy Guys to spawn to either 1,
 * or a random integer from 3 to 6.
 *
 * @param rarity Controls the rarity of spawning multiple Shy Guys
 */
static inline void set_shyguy_spawn_count(Ground* gp, int rarity)
{
    if (randi(rarity) == 0) {
        gp->u.shyguys.count = randi(3) + 3;
    } else {
        gp->u.shyguys.count = 1;
    }
}

/**
 * Shy guys initialization function
 */
void grStory_801E3234(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    Ground_801C2ED0(gobj->hsd_obj, gp->map_id);
    grAnime_801C7FF8(gobj, 0, 7, 0, 0.0F, 1.0F);
    grAnime_801C7FF8(gobj, 5, 7, 1, 0.0F, 1.0F);

    reset_shyguy_timer(gp);
    gp->x10_flags.b5 = true;
}

bool grStory_801E332C(Ground_GObj* gobj)
{
    return false;
}

void grStory_801E3334(Ground_GObj* gobj)
{
    grStory_801E3418(gobj);
    Ground_801C2FE0(gobj);
    lb_800115F4();
}

void grStory_801E336C(Ground_GObj* gobj) {}

/**
 * Randall initialization function
 */
void grStory_801E3370(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = gobj->hsd_obj;
    PAD_STACK(4);

    Ground_801C2ED0(jobj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->u.randall.timer = 0;
    gp->u.randall.jobj = Ground_801C3FA4(gobj, 1);
}

bool grStory_801E33D8(Ground_GObj* gobj)
{
    return false;
}

void grStory_801E33E0(Ground_GObj* gobj)
{
    // Update Randall's moving collision box
    Ground_801C2FE0(gobj);
    // Check to spawn Randall puff effect
    grStory_801E366C(gobj);
}

void grStory_801E3414(Ground_GObj* gobj) {}

// floating point random number centered at 0
// with an amplitude of 1
inline f32 frand_amp1(void)
{
    return 2.0F * (HSD_Randf() - 0.5F);
}

/**
 * Shy guy spawn timer frame callback
 */
void grStory_801E3418(Ground_GObj* gobj)
{
    Vec3 pos;
    int spawn_pattern;
    int i;

    Ground* gp = GET_GROUND(gobj);

    // Don't trigger if any shy guys are still onscreen
    if (it_8026B3C0(It_Kind_Heiho) != 0) {
        return;
    }

    // Wait until the shy guy timer has triggered
    if (gp->u.shyguys.timer != 0) {
        gp->u.shyguys.timer--;
        return;
    }

    reset_shyguy_timer(gp);

    // Pick a random spawn pattern,
    // which must be different from the previous one
    do {
        spawn_pattern = randi(ARRAY_SIZE(shyguy_vars->vpos));
    } while (gp->u.shyguys.pattern == spawn_pattern);
    gp->u.shyguys.pattern = spawn_pattern;

    // Choose whether they will spawn on the left or the right
    if (spawn_pattern < 3) {
        pos.x = -292.0F;
    } else {
        pos.x = 304.0F;
    }
    pos.y = shyguy_vars->vpos[spawn_pattern];
    pos.z = 2.0F;

    {
        int temp_r29 = randi(3);

        // Spawn either 1, or 3-6 shy guys
        set_shyguy_spawn_count(gp, shyguy_vars->spawnmany_rarity);

        // Value is overwritten, possible debugging?
        set_shyguy_spawn_count(gp, 2);

        for (i = 0; i < gp->u.shyguys.count; i++) {
            it_802D8618(i, &pos, temp_r29, 25.0F * i);

            // Jitter the vertical position of the each subsequent shy guy
            pos.y = 3.0F * frand_amp1() + shyguy_vars->vpos[spawn_pattern];
        }
    }
}

/**
 * Randall puff timer frame callback
 */
void grStory_801E366C(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);

    // Only create the effect when the timer reaches zero
    if (gp->u.randall.timer-- >= 0) {
        return;
    }

    // Spawn a puff effect at Randall's location,
    // and reset the timer to a random delay
    if (gp->u.randall.jobj != NULL) {
        grLib_801C97DC(0x2C, 0, gp->u.randall.jobj);
        gp->u.randall.timer = HSD_Randi(20) + 10;
    }
}

static DynamicsDesc* grStory_801E36D0(enum_t arg0)
{
    return NULL;
}

bool grStory_801E36D8(Vec3* a, int _, HSD_JObj* jobj)
{
    Vec3 b;
    lb_8000B1CC(jobj, NULL, &b);

    if (a->y + 1.0F > b.y) {
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
