#include "gr/grheal.h"

#include "placeholder.h"

#include <platform.h>

#include "baselib/gobj.h"
#include "baselib/gobjgxlink.h"
#include "baselib/gobjproc.h"
#include "baselib/jobj.h"
#include "dolphin/types.h"
#include "gm/gm_1832.h"

#include "gr/forward.h"

#include "gr/granime.h"
#include "gr/grdisplay.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "gr/stage.h"
#include "if/textlib.h"
#include "it/it_26B1.h"
#include "it/items/itcoin.h"
#include "it/types.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "mp/mplib.h"

typedef struct grHeal_UnkVec4 {
    Vec3 pos;
    s32 unused;
} grHeal_UnkVec4;

typedef struct grHeal_DataBlock {
    s16 player_model_joint_ids[0x1A];
    s32 next_player_character_ids[0x1A];
    StageCallbacks callbacks[5];
    char stage_filename[0xC];
    StageData stage_data;
    char report_fmt_get_gobj[0x24];
    char assert_filename[0xC];
    char report_fmt_not_found_next_player[0x20];
} grHeal_DataBlock;
STATIC_ASSERT(sizeof(grHeal_DataBlock) == 0x190);

typedef struct grHeal_StageData {
    StageData stage_data;
    char report_fmt_get_gobj[0x24];
} grHeal_StageData;
STATIC_ASSERT(sizeof(grHeal_StageData) == 0x58);

const grHeal_UnkVec4 grHeal_803B84A8 = { { 0.0F, 40.0F, 0.0F }, 0 };

s32 grHeal_803E83B8[0x27] = {
    0x1D001E, 0x1F0020, 0x210022, 0x230024, 0x250026, 0x270028, 0x29002A,
    0x2B002C, 0x2D002E, 0x2F0030, 0x310032, 0x330034, 0x350036, 0,
    0x15,     1,        0x16,     0x14,     2,        0x19,     3,
    0xE,      4,        5,        7,        6,        8,        9,
    0xA,      0xB,      0x18,     0xC,      0xD,      0xF,      0x10,
    0x11,     0x12,     0x17,     -1,
};

StageCallbacks grHeal_803E8454[] = {
    {
        grHeal_8021F0D8,
        grHeal_8021F170,
        grHeal_8021F178,
        grHeal_8021F17C,
        0,
    },
    {
        grHeal_8021F180,
        grHeal_8021F41C,
        grHeal_8021F474,
        grHeal_8021F4BC,
        0xC0000000,
    },
    {
        grHeal_8021F5C8,
        grHeal_8021F5CC,
        grHeal_8021F5D4,
        grHeal_8021F5D8,
        0,
    },
    {
        grHeal_8021F5DC,
        grHeal_8021F618,
        grHeal_8021F620,
        grHeal_8021F624,
        0,
    },
    {
        grHeal_8021F6F8,
        grHeal_8021F6FC,
        grHeal_8021F704,
        grHeal_8021F708,
        0,
    },
};

grHeal_StageData grHeal_803E84C4 = {
    {
        HEAL,
        grHeal_803E8454,
        "/GrHe.dat",
        grHeal_8021EF3C,
        grHeal_8021EF38,
        grHeal_8021EFBC,
        grHeal_8021EFC0,
        grHeal_8021EFE4,
        grHeal_8021F830,
        grHeal_8021F838,
        1,
        0,
        0,
    },
    "%s:%d: couldn t get gobj(id=%d)\n",
};

char grHeal_803E851C[0x2C] =
    "grheal.c\0\0\0\0*** Not found Next Player!(%d)\n";

s16 grHeal_804D49D8[4] = { 7, 8, 9, 0 };
SDATA char grHeal_804D49E0[] = "gobj";

grHeal_UnkData* grHeal_804D6AF0[2];

void grHeal_8021EF38(bool arg0) {}

void grHeal_8021EF3C(void)
{
    grHeal_804D6AF0[0] = Ground_801C49F8();
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

Ground_GObj* grHeal_8021EFEC(u32 idx)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks =
        (StageCallbacks*) ((char*) grHeal_803E83B8 + 0x9C) + idx;

    gobj = Ground_GetStageGObj(idx);

    if (gobj != NULL) {
        Ground* gp = gobj->user_data;
        gp->x8_callback = NULL;
        gp->xC_callback = NULL;
        GObj_SetupGXLink(gobj, grDisplay_801C5DB0, 3, 0);

        if (callbacks->callback3 != NULL) {
            gp->x1C_callback = callbacks->callback3;
        }

        if (callbacks->callback0 != NULL) {
            callbacks->callback0(gobj);
        }

        if (callbacks->callback2 != NULL) {
            HSD_GObj_SetupProc(gobj, callbacks->callback2, 4);
        }

    } else {
        OSReport(grHeal_803E84C4.report_fmt_get_gobj, grHeal_803E851C, 273,
                 idx);
    }

    return gobj;
}

void grHeal_8021F0D8(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    s32 i;

    grAnime_801C8138(gobj, gp->map_id, 0);

    for (i = 0; i < grHeal_804D6AF0[0]->x0; i++) {
        if ((int) gm_80473A18.x90[i] != 0) {
            grHeal_8021F79C(8, grHeal_804D49D8[i], i);
        }
    }
}

bool grHeal_8021F170(Ground_GObj* gobj)
{
    return false;
}

void grHeal_8021F178(Ground_GObj* gobj) {}

void grHeal_8021F17C(Ground_GObj* gobj) {}

void grHeal_8021F180(Ground_GObj* gobj)
{
    grHeal_UnkVec4 coin_pos;
    u8 next_players[4];
    HSD_JObj* next_jobjs[3];
    UNUSED HSD_JObj* reserved_next_jobj;
    HSD_JObj* player_jobjs[0x1A];
    UNUSED HSD_JObj* reserved_player_jobj;
    s32 next_count;
    s32 line_id;
    s32 next_idx;
    u32 i;
    Ground* gp;

    gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);

    if (gm_80473A18._94[0] % grHeal_804D6AF0[0]->x4 == 0) {
        coin_pos.pos = grHeal_803B84A8.pos;
        Ground_801C2D24(0xDC, &coin_pos.pos);
        line_id = Ground_801C5840();
        if (line_id != -1) {
            it_802F2094(NULL, &coin_pos.pos, line_id, 0);
            un_80304A58(line_id);
        }
    }

    for (next_count = 0; next_count < (s32) gm_80473A18._94[1]; next_count++) {
        next_players[next_count] = gm_80473A18._94[next_count + 2];
    }

    next_jobjs[0] = Ground_801C3FA4(gobj, 0x3A);
    next_jobjs[1] = Ground_801C3FA4(gobj, 0x3B);
    next_jobjs[2] = Ground_801C3FA4(gobj, 0x3C);

    for (next_idx = 0; next_idx < next_count; next_idx++) {
        grHeal_8021F4E8(grHeal_8021F70C(next_players[next_idx]),
                        next_jobjs[next_idx]);
    }

    for (i = 0; i < 0x1A; i++) {
        player_jobjs[i] = Ground_801C3FA4(gobj, ((s16*) grHeal_803E83B8)[i]);
    }

    for (i = 0; i < 0x1A; i++) {
        u32 character_id = gm_80473A18.x76[i];
        if ((s32) character_id != 0x21) {
            grHeal_8021F628(grHeal_8021F70C(character_id), player_jobjs[i]);
        }
    }

    mpJointSetCb1(0, gp, (mpLib_Callback) (Event) fn_8021F4C0);
    gp->gv.flatzone2.xC4 = 0;
}

bool grHeal_8021F41C(Ground_GObj* gobj)
{
    return false;
}

s32 fn_8021F424(void)
{
    Ground_GObj* ground;
    Ground* gp;

    ground = Ground_801C2BA4(1);
    if (ground != NULL) {
        gp = ground->user_data;
        if ((gp != NULL) && (gp->gv.unk.xC4 != 0)) {
            return 1;
        }
    }
    return 0;
}

void grHeal_8021F474(Ground_GObj* ground)
{
    Ground* gp;

    gp = ground->user_data;
    Ground_801C3D44(fn_8021F424, 10.0F, 20.0F);
    lb_800115F4();
    gp->gv.flatzone2.xC4 = 0;
}

void grHeal_8021F4BC(Ground_GObj* gobj) {}

void fn_8021F4C0(Ground* gp, void* arg2, s32 arg4, s32 arg5, s32 arg6)
{
    if ((((*(u8*) ((u8*) arg4 + 0x34) >> 3U) & 0xF) == 1) &&
        ((arg6 - 1) <= 1U))
    {
        gp->gv.unk.xC4 = 1;
    }
}

void grHeal_8021F4E8(s32 arg0, HSD_JObj* parent_jobj)
{
    Ground_GObj* ground;
    HSD_JObj* jobj;
    HSD_JObj* child;

    ground = grHeal_8021EFEC(4U);
    if (ground == NULL) {
        __assert(grHeal_803E851C, 0x1B8U, grHeal_804D49E0);
    }
    grAnime_801C8138(ground, 4, 0);
    grAnime_801C7FF8(ground, 0, 7, 0, (f32) arg0, 0.0F);
    jobj = GET_JOBJ(ground);
    child = HSD_JObjGetChild(jobj);
    HSD_JObjReparent(child, parent_jobj);
    HSD_JObjClearFlagsAll(child, JOBJ_HIDDEN);
    Ground_801C4A08(ground);
}

void grHeal_8021F5C8(Ground_GObj* gobj) {}

bool grHeal_8021F5CC(Ground_GObj* gobj)
{
    return false;
}

void grHeal_8021F5D4(Ground_GObj* gobj) {}

void grHeal_8021F5D8(Ground_GObj* gobj) {}

void grHeal_8021F5DC(Ground_GObj* ground)
{
    Ground* gp;

    gp = ground->user_data;
    gp->x10_flags.b2 = false;
    grAnime_801C8138(ground, gp->map_id, 0);
}

bool grHeal_8021F618(Ground_GObj* gobj)
{
    return false;
}

void grHeal_8021F620(Ground_GObj* gobj) {}

void grHeal_8021F624(Ground_GObj* gobj) {}

void grHeal_8021F628(s32 arg0, HSD_JObj* jobj_parent)
{
    Ground_GObj* ground;
    HSD_JObj* jobj;
    HSD_JObj* child;

    ground = grHeal_8021EFEC(2U);
    if (ground == NULL) {
        __assert(grHeal_803E851C, 0x201U, grHeal_804D49E0);
    }
    grAnime_801C8138(ground, 2, 0);
    grAnime_801C7FF8(ground, 0, 7, 0, (f32) arg0, 0.0F);
    jobj = GET_JOBJ(ground);
    child = HSD_JObjGetChild(jobj);
    HSD_JObjReparent(child, jobj_parent);
    Ground_801C4A08(ground);
}

void grHeal_8021F6F8(Ground_GObj* gobj) {}

bool grHeal_8021F6FC(Ground_GObj* gobj)
{
    return false;
}

void grHeal_8021F704(Ground_GObj* gobj) {}

void grHeal_8021F708(Ground_GObj* gobj) {}

u32 grHeal_8021F70C(u32 character_id)
{
    s32* base;
    s32* entry;
    s32 value;
    int frame;

    base = grHeal_803E83B8;
    frame = 0;

    if ((s32) character_id != 0x13) {
        goto loop_start;
    }
    character_id = 0x12;
    goto loop_start;

loop_compare:
    if ((s32) character_id == value) {
        goto loop_done;
    }
    entry++;
    frame++;
loop_check:
    value = *entry;
    if (value != -1) {
        goto loop_compare;
    }

loop_done:
    if (base[frame + 0xD] == -1) {
        OSReport(((grHeal_DataBlock*) base)->report_fmt_not_found_next_player,
                 character_id);
        frame = 0;
    }
    return frame;

loop_start:
    entry = base + 0xD;
    goto loop_check;
}

void grHeal_8021F79C(s32 arg0, s32 idx, s32 arg2)
{
    HSD_GObj* gp;
    HSD_JObj* jobj;
    BobOmbRain bobomb_rain;
    PAD_STACK(4);

    gp = Ground_801C2BA4(0);
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
