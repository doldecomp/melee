#include "gr/grheal.h"

#include "placeholder.h"

#include <platform.h>

#include "baselib/gobj.h"
#include "baselib/gobjproc.h"
#include "baselib/jobj.h"
#include "dolphin/types.h"
#include "gm/gm_1832.h"

#include "gr/forward.h"

#include "gr/granime.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "gr/stage.h"
#include "it/it_26B1.h"
#include "it/items/itcoin.h"
#include "it/types.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "mp/mplib.h"
#include "ty/toy.h"

typedef struct grHeal_UnkData {
    s32 x0;
    s32 x4;
} grHeal_UnkData;

/* 21EF38 */ static void grHeal_8021EF38(bool);
/* 21EF3C */ static void grHeal_8021EF3C(void);
/* 21EFBC */ static void grHeal_8021EFBC(void);
/* 21EFC0 */ static void grHeal_8021EFC0(void);
/* 21EFE4 */ static bool grHeal_8021EFE4(void);
/* 21EFEC */ static Ground_GObj* grHeal_8021EFEC(u32);
/* 21F0D8 */ static void stageGObj0_OnInit(Ground_GObj*);
/* 21F170 */ static bool stageGObj0_Callback1(Ground_GObj*);
/* 21F178 */ static void stageGObj0_GObjProc(Ground_GObj*);
/* 21F17C */ static void stageGObj0_Callback3(Ground_GObj*);
/* 21F180 */ static void stageGObj1_OnInit(Ground_GObj*);
/* 21F41C */ static bool stageGObj1_Callback1(Ground_GObj*);
/* 21F424 */ static s32 fn_8021F424(void);
/* 21F474 */ static void stageGObj1_GObjProc(Ground_GObj*);
/* 21F4BC */ static void stageGObj1_Callback3(Ground_GObj*);
/* 21F4C0 */ static void onJointCollision(void* user_data, int joint_id,
                                          CollData* coll, int coll_x50,
                                          mpLib_GroundEnum ground_kind,
                                          float delta_y);
/* 21F4E8 */ static void grHeal_8021F4E8(s32, HSD_JObj*);
/* 21F5C8 */ static void stageGObj2_OnInit(Ground_GObj*);
/* 21F5CC */ static bool stageGObj2_Callback1(Ground_GObj*);
/* 21F5D4 */ static void stageGObj2_GObjProc(Ground_GObj*);
/* 21F5D8 */ static void stageGObj2_Callback3(Ground_GObj*);
/* 21F5DC */ static void stageGObj3_OnInit(Ground_GObj*);
/* 21F618 */ static bool stageGObj3_Callback1(Ground_GObj*);
/* 21F620 */ static void stageGObj3_GObjProc(Ground_GObj*);
/* 21F624 */ static void stageGObj3_Callback3(Ground_GObj*);
/* 21F628 */ static void grHeal_8021F628(s32, HSD_JObj*);
/* 21F6F8 */ static void stageGObj4_OnInit(Ground_GObj*);
/* 21F6FC */ static bool stageGObj4_Callback1(Ground_GObj*);
/* 21F704 */ static void stageGObj4_GObjProc(Ground_GObj*);
/* 21F708 */ static void stageGObj4_Callback3(Ground_GObj*);
/* 21F70C */ static int grHeal_8021F70C(enum_t character_id);
/* 21F79C */ static void grHeal_8021F79C(s32, s32, s32);
/* 21F830 */ static DynamicsDesc* grHeal_8021F830(enum_t);
/* 21F838 */ static bool grHeal_8021F838(Vec3*, int, HSD_JObj*);

static Vec3 const grHeal_803B84A8 = { 0.0F, 40.0F, 0.0F };

static size_t const char_id_count = 26;

static s16 grHeal_803E83B8[char_id_count] = {
    29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41,
    42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54,
};

static enum_t frame_to_character_id[char_id_count] = {
    0, 21, 1,  22, 20, 2,  25, 3,  14, 4,  5,  7,  6,
    8, 9,  10, 11, 24, 12, 13, 15, 16, 17, 18, 23, -1,
};

static StageCallbacks stage_callbacks[] = {
    {
        stageGObj0_OnInit,
        stageGObj0_Callback1,
        stageGObj0_GObjProc,
        stageGObj0_Callback3,
        0,
    },
    {
        stageGObj1_OnInit,
        stageGObj1_Callback1,
        stageGObj1_GObjProc,
        stageGObj1_Callback3,
        (1 << 30) | (1 << 31),
    },
    {
        stageGObj2_OnInit,
        stageGObj2_Callback1,
        stageGObj2_GObjProc,
        stageGObj2_Callback3,
        0,
    },
    {
        stageGObj3_OnInit,
        stageGObj3_Callback1,
        stageGObj3_GObjProc,
        stageGObj3_Callback3,
        0,
    },
    {
        stageGObj4_OnInit,
        stageGObj4_Callback1,
        stageGObj4_GObjProc,
        stageGObj4_Callback3,
        0,
    },
};

StageData grHeal_StageData = {
    Gr_Kind_Heal,
    stage_callbacks,
    "/GrHe.dat",
    grHeal_8021EF3C,
    grHeal_8021EF38,
    grHeal_8021EFBC,
    grHeal_8021EFC0,
    grHeal_8021EFE4,
    grHeal_8021F830,
    grHeal_8021F838,
    (1 << 0),
    NULL,
    0,
};

s16 grHeal_804D49D8[4] = { 7, 8, 9, 0 };

static grHeal_UnkData* grHeal_804D6AF0[2];

void grHeal_8021EF38(bool arg0) {}

void grHeal_8021EF3C(void)
{
    grHeal_804D6AF0[0] = Ground_GetYakumonoParam();
    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = true;

    grHeal_8021EFEC(0);
    grHeal_8021EFEC(1);
    grHeal_8021EFEC(3);
    Ground_801C39C0();
    Ground_801C3BB4();
    Ground_801C3980(2.0F * Stage_GetBlastZoneTopOffset());
}

void grHeal_8021EFBC(void) {}

void grHeal_8021EFC0(void)
{
    grZakoGenerator_801CAE04(NULL);
}

bool grHeal_8021EFE4(void)
{
    return false;
}

Ground_GObj* grHeal_8021EFEC(u32 gobj_id)
{
    Ground_GObj* gobj;
    StageCallbacks* callbacks = &stage_callbacks[gobj_id];
    gobj = Ground_GetStageGObj(gobj_id);

    if (gobj != NULL) {
        /// @todo ::Ground_SetupStageCallbacks
        Ground* gp = GET_GROUND(gobj);
        gp->x8_callback = NULL;
        gp->xC_callback = NULL;
        GObj_SetupGXLink(gobj, grDisplay_801C5DB0, 3, 0);
        if (callbacks->callback3 != NULL) {
            gp->x1C_callback = callbacks->callback3;
        }
        if (callbacks->on_init != NULL) {
            callbacks->on_init(gobj);
        }
        if (callbacks->gobj_proc != NULL) {
            HSD_GObj_SetupProc(gobj, callbacks->gobj_proc, 4);
        }
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 273, gobj_id);
    }

    return gobj;
}

void stageGObj0_OnInit(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    s32 i;

    grAnime_801C8138(gobj, gp->map_id, 0);

    for (i = 0; i < grHeal_804D6AF0[0]->x0; i++) {
        if ((int) gm_80473A18.x90[i] != 0) {
            grHeal_8021F79C(8, grHeal_804D49D8[i], i);
        }
    }
}

bool stageGObj0_Callback1(Ground_GObj* gobj)
{
    return false;
}

void stageGObj0_GObjProc(Ground_GObj* gobj) {}

void stageGObj0_Callback3(Ground_GObj* gobj) {}

void stageGObj1_OnInit(Ground_GObj* gobj)
{
    PAD_STACK(4);
    {
        Vec3 coin_pos;
        u8 next_players[4];
        HSD_JObj* next_jobjs[3];
        UNUSED HSD_JObj* reserved_next_jobj;
        HSD_JObj* player_jobjs[char_id_count];
        UNUSED HSD_JObj* reserved_player_jobj;
        s32 next_count;
        s32 line_id;
        s32 next_idx;
        u32 i;
        Ground* gp;

        gp = GET_GROUND(gobj);
        grAnime_801C8138(gobj, gp->map_id, 0);

        if (gm_80473A18._94[0] % grHeal_804D6AF0[0]->x4 == 0) {
            coin_pos = grHeal_803B84A8;
            Ground_801C2D24(0xDC, &coin_pos);
            line_id = Ground_801C5840();
            if (line_id != -1) {
                it_802F2094(NULL, &coin_pos, line_id, 0);
                Toy_80304A58(line_id);
            }
        }

        for (next_count = 0; next_count < gm_80473A18._94[1]; next_count++) {
            next_players[next_count] = gm_80473A18._94[next_count + 2];
        }

        next_jobjs[0] = Ground_801C3FA4(gobj, 58);
        next_jobjs[1] = Ground_801C3FA4(gobj, 59);
        next_jobjs[2] = Ground_801C3FA4(gobj, 60);

        for (next_idx = 0; next_idx < next_count; next_idx++) {
            grHeal_8021F4E8(grHeal_8021F70C(next_players[next_idx]),
                            next_jobjs[next_idx]);
        }

        for (i = 0; i < ARRAY_SIZE(grHeal_803E83B8); i++) {
            player_jobjs[i] = Ground_801C3FA4(gobj, grHeal_803E83B8[i]);
        }

        for (i = 0; i < ARRAY_SIZE(grHeal_803E83B8); i++) {
            enum_t character_id = gm_80473A18.x76[i];
            if (character_id != 33) {
                grHeal_8021F628(grHeal_8021F70C(character_id),
                                player_jobjs[i]);
            }
        }

        mpJointSetCb1(0, gp, onJointCollision);
        gp->u.flatzone2.xC4 = 0;
    }
}

bool stageGObj1_Callback1(Ground_GObj* gobj)
{
    return false;
}

s32 fn_8021F424(void)
{
    Ground_GObj* ground;
    Ground* gp;

    ground = Ground_GetMapGObj(1);
    if (ground != NULL) {
        gp = ground->user_data;
        if ((gp != NULL) && (gp->u.unk.xC4 != 0)) {
            return 1;
        }
    }
    return 0;
}

void stageGObj1_GObjProc(Ground_GObj* ground)
{
    Ground* gp;

    gp = ground->user_data;
    Ground_801C3D44(fn_8021F424, 10.0F, 20.0F);
    lb_800115F4();
    gp->u.flatzone2.xC4 = 0;
}

void stageGObj1_Callback3(Ground_GObj* gobj) {}

/// @copydoc mpLib_JointCollisionCallback
void onJointCollision(void* user_data, int joint_id, CollData* coll,
                      int coll_x50, mpLib_GroundEnum ground_kind,
                      float delta_y)
{
    Ground* gp = user_data;
    if ((((*(u8*) ((u8*) coll + 0x34) >> 3U) & 0xF) == 1) &&
        ((ground_kind - 1) <= 1U))
    {
        gp->u.unk.xC4 = 1;
    }
}

void grHeal_8021F4E8(s32 arg0, HSD_JObj* parent_jobj)
{
    Ground_GObj* gobj;
    HSD_JObj* jobj;
    HSD_JObj* child;

    gobj = grHeal_8021EFEC(4U);
    HSD_ASSERT(440, gobj);
    grAnime_801C8138(gobj, 4, 0);
    grAnime_801C7FF8(gobj, 0, 7, 0, (f32) arg0, 0.0F);
    jobj = GET_JOBJ(gobj);
    child = HSD_JObjGetChild(jobj);
    HSD_JObjReparent(child, parent_jobj);
    HSD_JObjClearFlagsAll(child, JOBJ_HIDDEN);
    Ground_801C4A08(gobj);
}

void stageGObj2_OnInit(Ground_GObj* gobj) {}

bool stageGObj2_Callback1(Ground_GObj* gobj)
{
    return false;
}

void stageGObj2_GObjProc(Ground_GObj* gobj) {}

void stageGObj2_Callback3(Ground_GObj* gobj) {}

void stageGObj3_OnInit(Ground_GObj* ground)
{
    Ground* gp;

    gp = ground->user_data;
    gp->x10_flags.b2 = false;
    grAnime_801C8138(ground, gp->map_id, 0);
}

bool stageGObj3_Callback1(Ground_GObj* gobj)
{
    return false;
}

void stageGObj3_GObjProc(Ground_GObj* gobj) {}

void stageGObj3_Callback3(Ground_GObj* gobj) {}

void grHeal_8021F628(s32 arg0, HSD_JObj* jobj_parent)
{
    Ground_GObj* gobj;
    HSD_JObj* jobj;
    HSD_JObj* child;

    gobj = grHeal_8021EFEC(2U);
    HSD_ASSERT(513, gobj);
    grAnime_801C8138(gobj, 2, 0);
    grAnime_801C7FF8(gobj, 0, 7, 0, arg0, 0.0F);
    jobj = GET_JOBJ(gobj);
    child = HSD_JObjGetChild(jobj);
    HSD_JObjReparent(child, jobj_parent);
    Ground_801C4A08(gobj);
}

void stageGObj4_OnInit(Ground_GObj* gobj) {}

bool stageGObj4_Callback1(Ground_GObj* gobj)
{
    return false;
}

void stageGObj4_GObjProc(Ground_GObj* gobj) {}

void stageGObj4_Callback3(Ground_GObj* gobj) {}

/// @todo Eliminate gotos, use enum members
int grHeal_8021F70C(enum_t character_id)
{
    int frame = 0;

    if (character_id == 19) {
        character_id = 18;
    }
    goto loop_start;

loop_compare:
    if (character_id != frame_to_character_id[frame]) {
        frame++;
    loop_check:
        if (frame_to_character_id[frame] != -1) {
            goto loop_compare;
        }
    }

    if (frame_to_character_id[frame] == -1) {
        OSReport("*** Not found Next Player!(%d)\n", character_id);
        frame = 0;
    }
    return frame;

loop_start:
    goto loop_check;
}

void grHeal_8021F79C(s32 arg0, s32 idx, s32 arg2)
{
    HSD_GObj* gp;
    HSD_JObj* jobj;
    BobOmbRain bobomb_rain;
    PAD_STACK(4);

    gp = Ground_GetMapGObj(0);
    jobj = Ground_801C3FA4(gp, idx);
    bobomb_rain.x0 = gp;
    bobomb_rain.x4 = NULL;
    bobomb_rain.x14 = arg0;
    bobomb_rain.x18 = arg2;
    bobomb_rain.x1C.b0 = 1;
    lb_8000B1CC(jobj, NULL, &bobomb_rain.x8_vec);
    it_8026BE84(&bobomb_rain);
}

DynamicsDesc* grHeal_8021F830(enum_t arg0)
{
    return false;
}

bool grHeal_8021F838(Vec3* arg0, int arg1, HSD_JObj* jobj)
{
    return true;
}
