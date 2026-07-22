#include "grinishie1.h"

#include "grdisplay.h"
#include "grlib.h"
#include "grmaterial.h"
#include "grzakogenerator.h"
#include "inlines.h"
#include "stage.h"
#include "types.h"

#include <platform.h>

#include "cm/camera.h"
#include "ef/efsync.h"
#include "gm/gm_unsplit.h"
#include "it/it_26B1.h"
#include "it/itdrop.h"
#include "it/itspawn.h"
#include "lb/lb_00B0.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbspdisplay.h"
#include "mp/mplib.h"

#include <baselib/debug.h>
#include <baselib/gobj.h>
#include <sysdolphin/baselib/dobj.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/memory.h>
#include <sysdolphin/baselib/random.h>

/* 1FBEB8 */ static void fn_801FBEB8(void* user_data, int joint_id,
                                     CollData* coll, int coll_x50,
                                     mpLib_GroundEnum ground_kind,
                                     float delta_y);
/* 1FC9AC */ static void fn_801FC9AC(void* user_data, int joint_id,
                                     CollData* coll, int coll_x50,
                                     mpLib_GroundEnum ground_kind,
                                     float delta_y);

/// @todo Emitted only to lay out the .sdata2 literal pool in retail order.
static void sdata2_order(void)
{
    (void) 1.0f;
    (void) 4000.0f;
    (void) 0.0f;
    (void) -1.0f;
    (void) 6.0f;
    (void) 1.20000005f;
    (void) 5.0;
    (void) -1.20000005f;
    (void) 0.0;
    (void) 15.0f;
    (void) 5.0f;
    (void) 0.69999999999999996;
    (void) 100000.0f;
    (void) -30.0f;
    (void) S32_TO_F32;
}

/// these inlines are probably shared in other places
static inline s32 test_random(s32 val)
{
    return ((val != 0) ? HSD_Randi(val) : 0);
}

static inline s32 randi_between(s32 min, s32 max)
{
    if (max > min) {
        max = min + test_random(max - min);
    } else if (max < min) {
        max += test_random(min - max);
    }
    return max;
}

static inline f32 fabsf_inline(f32 x)
{
    return (x < 0.0f) ? -x : x;
}

static inline f32 fclamp0(f32 x)
{
    f32 ret = x;
    if (x < 0.0f) {
        ret = 0.0f;
    }
    return ret;
}

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    s16 unk14;
    s16 unk16;
    u16 unk18;
    s16 unk1A;
    s16 unk1C;
    s16 unk1E;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    Vec3 unk2C[2];
    f32 unk44;
    f32 unk48;
    f32 unk4C;
    f32 unk50;
} grInishie1_stuff;

grInishie1_stuff* grI1_804D69F8;

/// initial velocity for items spawned from hatena blocks
const Vec3 grI1_803B8268 = { 0.0f, 5.0f, 0.0f };

#define DOBJ_LOOP(jobj)                                                       \
    {                                                                         \
        HSD_DObj* dobj = HSD_JObjGetDObj(jobj);                               \
        while (dobj != NULL) {                                                \
            HSD_DObjSetFlags(dobj, 1U);                                       \
            dobj = (dobj != NULL) ? dobj->next : NULL;                        \
        }                                                                     \
    };

#define DOBJ_CLEAR_LOOP(jobj)                                                 \
    {                                                                         \
        HSD_DObj* dobj = HSD_JObjGetDObj(jobj);                               \
        while (dobj != NULL) {                                                \
            HSD_DObjClearFlags(dobj, 1U);                                     \
            dobj = (dobj != NULL) ? dobj->next : NULL;                        \
        }                                                                     \
    }

s16 grI1_803E48C8[22] = {
    13, 3,  3, 14, 3,  14, 15, 3,  15, 16, 3,
    16, 17, 3, 17, 18, 3,  18, 19, 3,  19, 0,
};

StageCallbacks grI1_803E48F4[] = {
    {
        grInishie1_801FAAA0,
        grInishie1_801FAACC,
        grInishie1_801FAAD4,
        grInishie1_801FAAD8,
        0,
    },
    {
        grInishie1_801FABB4,
        grInishie1_801FABF4,
        grInishie1_801FABFC,
        grInishie1_801FAC00,
        0,
    },
    {
        grInishie1_801FAC04,
        grInishie1_801FAC50,
        grInishie1_801FAC58,
        grInishie1_801FAD80,
        0,
    },
    {
        grInishie1_801FAADC,
        grInishie1_801FAB60,
        grInishie1_801FAB68,
        grInishie1_801FABB0,
        0xC0000000,
    },
};

char grI1_803E4944[] = "/GrI1.dat";

typedef struct grInishie1_StageData {
    StageData stage_data;
    char report_fmt_get_gobj[0x24];
} grInishie1_StageData;

grInishie1_StageData grI1_803E4950 = {
    {
        INISHIE1,
        grI1_803E48F4,
        grI1_803E4944,
        grInishie1_801FA90C,
        grInishie1_801FA908,
        grInishie1_801FA984,
        grInishie1_801FA988,
        grInishie1_801FA9AC,
        grInishie1_801FCBB0,
        grInishie1_801FCBB8,
        1,
        (S16Vec3*) grI1_803E48C8,
        7,
    },
    "%s:%d: couldn t get gobj(id=%d)\n",
};

void grInishie1_801FA908(bool arg) {}

/// corresponds with the 3 - 13 - 3 block pattern on the stage
#define BLOCK_COUNT 19

struct block_table_struct {
    s16 idx;
    s16 jobj_idx;
};

extern struct block_table_struct grI1_803E49B8[BLOCK_COUNT];

void grInishie1_801FA90C(void)
{
    grI1_804D69F8 = Ground_801C49F8();
    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 1;
    grInishie1_801FA9B4(0);
    grInishie1_801FA9B4(3);
    Ground_801C39C0();
    Ground_801C3BB4();
    Camera_800311DC(1.0f);
    Camera_800311CC(4000.0f);
}

void grInishie1_801FA984(void) {}

void grInishie1_801FA988(void)
{
    grZakoGenerator_801CAE04(NULL);
}

bool grInishie1_801FA9AC(void)
{
    return false;
}

HSD_GObj* grInishie1_801FA9B4(s32 arg0)
{
    HSD_GObj* gobj;
    StageCallbacks* cb =
        (StageCallbacks*) ((char*) grI1_803E48C8 + 0x2c) + arg0;

    gobj = Ground_GetStageGObj(arg0);

    if (gobj != NULL) {
        Ground* gp = gobj->user_data;

        gp->x8_callback = NULL;
        gp->xC_callback = NULL;

        GObj_SetupGXLink(gobj, grDisplay_801C5DB0, 3U, 0U);

        if (cb->callback3 != NULL) {
            gp->x1C_callback = cb->callback3;
        }

        if (cb->callback0 != NULL) {
            cb->callback0(gobj);
        }

        if (cb->callback2 != NULL) {
            HSD_GObj_SetupProc(gobj, cb->callback2, 4U);
        }
    } else {
        OSReport(grI1_803E4950.report_fmt_get_gobj, "grinishie1.c", 0xE7,
                 arg0);
    }

    return gobj;
}

struct block_table_struct grI1_803E49B8[BLOCK_COUNT] = {
    { 13, 3 },  { 14, 14 }, { 15, 15 }, { 16, 16 }, { 17, 17 },
    { 18, 18 }, { 19, 19 }, { 11, 20 }, { 12, 21 }, { 1, 4 },
    { 2, 5 },   { 3, 6 },   { 4, 7 },   { 5, 8 },   { 6, 9 },
    { 7, 10 },  { 8, 11 },  { 9, 12 },  { 10, 13 },
};

void grInishie1_801FAAA0(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grInishie1_801FAACC(Ground_GObj* gobj)
{
    return false;
}

void grInishie1_801FAAD4(Ground_GObj* gobj) {}

void grInishie1_801FAAD8(Ground_GObj* gobj) {}

void grInishie1_801FAADC(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);

    Ground_801C2ED0(jobj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
    grInishie1_801FAD84(gobj);
    grInishie1_801FC018(gobj);
    gp->u.inishie1.xC4_flags_b0 = 0;
    grMaterial_801C8858(Ground_801C3FA4(gobj, 0x2D), 0x20000000U);
}

bool grInishie1_801FAB60(Ground_GObj* gobj)
{
    return false;
}

void grInishie1_801FAB68(Ground_GObj* gobj)
{
    grInishie1_801FB3F0(gobj);
    grInishie1_801FC664(gobj);
    grInishie1_801FCB10(gobj);
    lb_800115F4();
    Ground_801C2FE0(gobj);
}

void grInishie1_801FABB0(Ground_GObj* gobj) {}

void grInishie1_801FABB4(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x8_callback = NULL;
    gp->xC_callback = NULL;
}

bool grInishie1_801FABF4(Ground_GObj* gobj)
{
    return false;
}

void grInishie1_801FABFC(Ground_GObj* gobj) {}

void grInishie1_801FAC00(Ground_GObj* gobj) {}

void grInishie1_801FAC04(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->u.inishie12.xC4 = NULL;
    gp->u.inishie12.xC8 = grI1_804D69F8->unk16;
    gp->u.inishie12.xCC = 0;
}

bool grInishie1_801FAC50(Ground_GObj* gobj)
{
    return false;
}

void grInishie1_801FAC58(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = gobj->hsd_obj;
    HSD_JObj* jobj2 = jobj;
    Vec3 vec;

    if (gp && jobj2) {
        if (gp->u.inishie12.xCC == 0) {
            if (gp->u.inishie12.xC8 > 0) {
                if (gp->u.inishie12.xC8 & 1) {
                    HSD_JObjClearFlagsAll(jobj2, JOBJ_HIDDEN);
                } else {
                    HSD_JObjSetFlagsAll(jobj2, JOBJ_HIDDEN);
                }
                gp->u.inishie12.xC8 -= 1;
            }
        }

        if (gp->u.inishie12.xC4 != NULL) {
            lb_8000B1CC(gp->u.inishie12.xC4, NULL, &vec);
            HSD_JObjSetTranslate(jobj2, &vec);
        }
    }
}

void grInishie1_801FAD80(Ground_GObj* gobj) {}

void grInishie1_801FAD84(HSD_GObj* gobj)
{
    /// @todo same layout as #grInishie1_801FB3F0_Vars; the shared
    /// grInishie1_GroundVars/grInishie1_Block structs are likely wrong
    /// (xC4 should be u16, block x4 is s16 and x10 is an f32)
    typedef struct grInishie1_InitBlock {
        s16 status;
        s16 x2;
        s16 x4;
        s16 x6;
        f32 x8;
        f32 xC;
        f32 x10;
        HSD_JObj* jobj;
        HSD_GObj* hatena_gobj;
        Item_GObj* item_gobj;
        s16 x20;
        s16 x22;
    } grInishie1_InitBlock;
    typedef struct grInishie1_InitGround {
        u8 pad[0xC4];
        u16 xC4;
        s16 xC6;
        s16 xC8;
        s16 xCA;
        s16 xCC;
        s16 xCE;
        s32 xD0;
        s32 xD4;
        s32 xD8;
        grInishie1_InitBlock* blocks;
    } grInishie1_InitGround;
    HSD_JObj* jobj;
    struct block_table_struct* block_table;
    u32 j;
    int i;
    s32 value;
    grInishie1_InitGround* gp = gobj->user_data;
    PAD_STACK(8);

    gp->blocks = (grInishie1_InitBlock*) HSD_MemAlloc(
        sizeof(grInishie1_InitBlock) * BLOCK_COUNT);

    block_table = grI1_803E49B8;

    i = 0;
    while ((u32) i < BLOCK_COUNT) {
        if (i < 0 || (u32) i >= BLOCK_COUNT) {
            OSReport("%s:%d: oioi..\n", "grinishie1.c", 0x1F9);
            while (true) {
            }
        }
        {
            s16 check = block_table[i].idx;
            value = check;

            for (j = 0; j < BLOCK_COUNT; j++) {
                if (check == block_table[j].idx) {
                    break;
                }
            }
        }

        if (j == BLOCK_COUNT) {
            OSReport("%s:%d: oioi..\n", "grinishie1.c", 0x217);
            while (true) {
            }
        }

        jobj = Ground_801C3FA4(gobj, grI1_803E49B8[j].jobj_idx);
        if (jobj == NULL) {
            OSReport("%s:%d: oioi..\n", "grinishie1.c", 0x21D);
            while (true) {
            }
        }

        gp->blocks[i].x2 = 2;
        gp->blocks[i].x4 = 0;
        gp->blocks[i].jobj = jobj;
        gp->blocks[i].hatena_gobj = NULL;
        gp->blocks[i].x8 = HSD_JObjGetTranslationY(jobj);
        gp->blocks[i].xC = 0.0f;
        gp->blocks[i].x10 = 0.0f;
        mpJointSetCb2(value, gp, fn_801FBEB8);
        gp->blocks[i].status = 0;
        i++;
    }

    for (i = 0; (u32) i < BLOCK_COUNT; i++) {
        HSD_GObj* new_gobj = grMaterial_801C8CFC(
            8, 0, (Ground*) gp, gp->blocks[i].jobj, NULL, fn_801FBF6C, NULL);

        if (new_gobj != NULL) {
            grMaterial_801C8DE0(new_gobj, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                                6.0f);
            grMaterial_801C8E08(new_gobj);
            grMaterial_801C8E68(new_gobj, 0);
        }

        gp->blocks[i].item_gobj = new_gobj;
    }

    if (gm_8016AE80() != -1 && gm_8016B238() == 0) {
        int item_kind = It_Common_Start;
        do {
            if (it_8026D324(item_kind) != 0) {
                break;
            }
            item_kind++;
        } while (item_kind < It_Common_End);

        if (item_kind != It_Common_End) {
            s32 index1 = HSD_Randi(BLOCK_COUNT);
            s32 index2;
            s32 index1_copy = index1;
            s32 index2_copy;

            do {
                index2 = HSD_Randi(BLOCK_COUNT);
            } while (index1 == (index2_copy = index2));

            gp->blocks[index1].status = 1;
            grInishie1_801FBAA0(gobj, index1_copy);
            GET_GROUND(gp->blocks[index1].hatena_gobj)->u.inishie12.xCC = 1;

            gp->blocks[index2].status = 2;
            grInishie1_801FBAA0(gobj, index2_copy);
            GET_GROUND(gp->blocks[index2].hatena_gobj)->u.inishie12.xCC = 1;
        }
    }

    gp->xC6 = 0;
    gp->xC8 = 0;
    gp->xCA = -1;
    gp->xCC = -1;
    gp->xD8 = 0;
}

void grInishie1_801FB0AC(HSD_GObj* gobj, u32 index)
{
    Ground* gp = gobj->user_data;
    PAD_STACK(8);

    if (gp->u.inishie1.blocks[index].status == 1) {
        grInishie1_801FBA34(gobj, gp->u.inishie1.blocks[index].jobj2);
        gp->u.inishie1.blocks[index].status = 0;
        grInishie1_801FBC4C(gobj, index);

        ((s16*) &gp->u.inishie1.xC4)[1] =
            rand_range(grI1_804D69F8->unk4, grI1_804D69F8->unk0);
    } else if (gp->u.inishie1.blocks[index].status == 2) {
        grInishie1_801FBA34(gobj, gp->u.inishie1.blocks[index].jobj2);
        gp->u.inishie1.blocks[index].status = 0;
        grInishie1_801FBC4C(gobj, index);

        ((s16*) &gp->u.inishie1.xC4)[2] =
            rand_range(grI1_804D69F8->unkC, grI1_804D69F8->unk8);
    } else if (gp->u.inishie1.blocks[index].status == 3) {
        grInishie1_801FBA34(gobj, gp->u.inishie1.blocks[index].jobj2);
        gp->u.inishie1.blocks[index].status = 0;
        grInishie1_801FBC4C(gobj, index);

        {
            u32 i;
            for (i = 0; i < 0x13; i++) {
                if (gp->u.inishie1.blocks[i].status == 3) {
                    break;
                }
            }
            if (i == 0x13) {
                ((s16*) &gp->u.inishie1.xC4)[1] =
                    rand_range(grI1_804D69F8->unk4, grI1_804D69F8->unk0);
                ((s16*) &gp->u.inishie1.xC4)[2] =
                    rand_range(grI1_804D69F8->unkC, grI1_804D69F8->unk8);
            }
        }

        gp->u.inishie1.xD8 = grI1_804D69F8->unk10;
    } else {
        if (gp->u.inishie1.blocks[index].hatena_gobj != NULL) {
            HSD_ASSERT(0x29D, 0);
        }
    }
}

enum {
    HATENA_APPEAR_CHECKLOOP = 0x14
};

#define HATENA_APPEAR_CHECKLOOP(countdown, last_index, status_val, line)      \
    if (countdown > 0) {                                                      \
        countdown--;                                                          \
        if (countdown == 0) {                                                 \
            int i = 0;                                                        \
            s32 index;                                                        \
                                                                              \
            do {                                                              \
                index = HSD_Randi(0x13);                                      \
                if (index != last_index && vars->blocks[index].x0 == 0) {     \
                    break;                                                    \
                }                                                             \
                i++;                                                          \
            } while (i < HATENA_APPEAR_CHECKLOOP);                            \
                                                                              \
            HSD_ASSERT(line, i!=HATENA_APPEAR_CHECKLOOP);                      \
                                                                              \
            last_index = index;                                               \
            vars->blocks[index].x0 = status_val;                              \
            grInishie1_801FBAA0(gobj, index);                                 \
            vars->blocks[index].x20 = 0;                                      \
        }                                                                     \
    }

typedef struct grInishie1_801FB3F0_Block {
    s16 x0;
    s16 x2;
    s16 x4;
    s16 x6;
    f32 x8;
    f32 xC;
    f32 x10;
    HSD_JObj* jobj;
    HSD_GObj* hatena_gobj;
    Item_GObj* item_gobj;
    s16 x20;
    s16 x22;
} grInishie1_801FB3F0_Block;

typedef struct grInishie1_801FB3F0_Vars {
    u8 pad0[0xC6];
    s16 xC6;
    s16 xC8;
    s16 xCA;
    s16 xCC;
    u8 padCE[0xD8 - 0xCE];
    s32 xD8;
    grInishie1_801FB3F0_Block* blocks;
} grInishie1_801FB3F0_Vars;

static inline void
grInishie1_801FB3F0_update_blocks(HSD_GObj* gobj,
                                  grInishie1_801FB3F0_Vars* vars, Vec3* pos)
{
    u32 i;

    for (i = 0; i < 0x13; ++i) {
        switch (vars->blocks[i].x2) {
        case 2:
            if (vars->blocks[i].x4 != 0) {
                vars->blocks[i].x4--;
            }
            break;

        case 3:
            vars->blocks[i].x10 = 1.2f;
            grInishie1_801FB0AC(gobj, i);
            vars->blocks[i].x2 = 4;
            // fallthrough

        case 4:
            vars->blocks[i].xC += vars->blocks[i].x10;

            if (vars->blocks[i].xC > 5.0) {
                vars->blocks[i].x10 = -1.2f;
            } else if (vars->blocks[i].xC < 0.0) {
                vars->blocks[i].xC = 0.0f;
                vars->blocks[i].x2 = 2;
                vars->blocks[i].x4 = 10;
            }

            // the blocks appear to not move at all, so not
            // sure what this is
            {
                f32 y = vars->blocks[i].x8 + vars->blocks[i].xC;
                HSD_JObjSetTranslateY(vars->blocks[i].jobj, y);
            }
            break;

        case 0:
            if (vars->blocks[i].x20 != 0) {
                vars->blocks[i].x20--;
            } else {
                lb_8000B1CC(vars->blocks[i].jobj, NULL, pos);
                if (!grLib_801C9EE8(pos, 15.0f)) {
                    DOBJ_CLEAR_LOOP(vars->blocks[i].jobj);
                    HSD_JObjClearFlagsAll(vars->blocks[i].jobj, JOBJ_HIDDEN);
                    grMaterial_801C8E08(vars->blocks[i].item_gobj);
                    vars->blocks[i].x2 = 1;
                    vars->blocks[i].x22 = grI1_804D69F8->unk18;
                }
            }

            if (vars->blocks[i].hatena_gobj != NULL) {
                HSD_JObj* sub_jobj = vars->blocks[i].hatena_gobj->hsd_obj;
                if (!(HSD_JObjGetFlags(sub_jobj) & 0x10)) {
                    HSD_JObjSetFlagsAll(sub_jobj, JOBJ_HIDDEN);
                }
            }
            break;
        case 1:
            /*
               probably sets the flickering for blocks when they spawn
            */
            if (vars->blocks[i].x22 > 0) {
                HSD_JObjGetDObj(vars->blocks[i].jobj);
                if (vars->blocks[i].hatena_gobj != NULL) {
                    HSD_JObj* target = vars->blocks[i].hatena_gobj->hsd_obj;

                    if (vars->blocks[i].x22 & 1) {
                        HSD_JObjClearFlagsAll(target, JOBJ_HIDDEN);
                    } else {
                        HSD_JObjSetFlagsAll(target, JOBJ_HIDDEN);
                    }

                    DOBJ_CLEAR_LOOP(vars->blocks[i].jobj);
                } else {
                    if (vars->blocks[i].x22 & 1) {
                        DOBJ_CLEAR_LOOP(vars->blocks[i].jobj);
                    } else {
                        DOBJ_LOOP(vars->blocks[i].jobj);
                    }
                }

                vars->blocks[i].x22--;
            } else {
                vars->blocks[i].x2 = 2;
                vars->blocks[i].x4 = 0;
            }
            break;
        }
    }
}

void grInishie1_801FB3F0(HSD_GObj* gobj)
{
    grInishie1_801FB3F0_Vars* vars = gobj->user_data;
    u32 i;
    Vec3 pos;
    PAD_STACK(48);

    if (vars->xD8 > 0) {
        vars->xD8--;
    }

    if (vars->xD8 == 0 && ((vars->xC6 == 1 && vars->xC8 > 0 &&
                            vars->xC8 < grI1_804D69F8->unk14) ||
                           (vars->xC8 == 1 && vars->xC6 > 0 &&
                            vars->xC6 < grI1_804D69F8->unk14)))
    {
        vars->xC8 = 0;
        vars->xC6 = 0;

        // this is likely the rare case mentioned on smashwiki
        // where every block will become a hatena block
        for (i = 0; i < 0x13; ++i) {
            vars->blocks[i].x0 = 3;
            grInishie1_801FBAA0(gobj, i);
            vars->blocks[i].x20 = 0;
        }
    } else {
        HATENA_APPEAR_CHECKLOOP(vars->xC6, vars->xCA, 1, 0x2D0U);
        HATENA_APPEAR_CHECKLOOP(vars->xC8, vars->xCC, 2, 0x2EBU);
    }

    grInishie1_801FB3F0_update_blocks(gobj, vars, &pos);
}

/// gives item from hatena block upwards velocity, maybe handles spawning it as
/// well
void grInishie1_801FBA34(HSD_GObj* gobj, HSD_JObj* jobj)
{
    Vec3 sp1C;
    Vec3 vec;
    lb_8000B1CC(jobj, NULL, &sp1C);
    vec = grI1_803B8268;
    sp1C.y += 5.0f;
    it_8026F7C8(&sp1C, &vec, 0);
}

/// creates a hatena block
static inline Ground* GET_GROUND2(HSD_GObj* gobj)
{
    return gobj->user_data;
}

void grInishie1_801FBAA0(HSD_GObj* gobj, s32 index)
{
    HSD_JObj* hatena_jobj;
    Vec3 position;
    Ground* gp = GET_GROUND2(gobj);
    Ground* hatena_gp;
    HSD_GObj* hatena = grInishie1_801FA9B4(2);
    PAD_STACK(4);

    if (hatena != NULL) {
        hatena_gp = GET_GROUND2(hatena);
        HSD_ASSERTMSG(0x39E, !gp->u.inishie1.blocks[index].hatena_gobj,
                      "!mapgp->u.map.block[ix].hatena_gobj");

        gp->u.inishie1.blocks[index].hatena_gobj = hatena;

        hatena_jobj = hatena->hsd_obj;
        lb_8000B1CC(gp->u.inishie1.blocks[index].jobj2, NULL, &position);
        HSD_JObjSetTranslate(hatena_jobj, &position);

        hatena_gp->u.inishie13.xC4 = gp->u.inishie1.blocks[index].jobj2;

        if (gp->u.inishie1.blocks[index].x2 == 0 ||
            gp->u.inishie1.blocks[index].x2 == 1)
        {
            hatena_gp->u.inishie13.xCC = 1;
        }

        DOBJ_LOOP(gp->u.inishie1.blocks[index].jobj2);
    }
}

void grInishie1_801FBC4C(HSD_GObj* gobj, u32 index)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj2 = gp->u.inishie1.blocks[index].jobj2;
    DOBJ_CLEAR_LOOP(jobj2);
    Ground_801C4A08(gp->u.inishie1.blocks[index].hatena_gobj);
    gp->u.inishie1.blocks[index].hatena_gobj = NULL;
}

void grInishie1_801FBCEC(HSD_GObj* gobj, u32 index)
{
    Ground* gp = GET_GROUND2(gobj);
    Vec3 effect_pos;

    gp->u.inishie1.blocks[index].x2 = 0;
    gp->u.inishie1.blocks[index].x20 =
        randi_between(grI1_804D69F8->unk1A, grI1_804D69F8->unk1C);

    HSD_DObjSetFlags(HSD_JObjGetDObj(gp->u.inishie1.blocks[index].jobj2), 1U);

    grMaterial_801C8E28(gp->u.inishie1.blocks[index].item_gobj);

    {
        s16 status = gp->u.inishie1.blocks[index].status;
        if (status == 1 || (u16) (status - 2) <= 1U) {
            Vec3 item_vel;

            Ground_801C4A08(gp->u.inishie1.blocks[index].hatena_gobj);
            gp->u.inishie1.blocks[index].hatena_gobj = NULL;

            lb_8000B1CC(gp->u.inishie1.blocks[index].jobj2, NULL,
                        &item_vel - 1);

            item_vel = grI1_803B8268;
            (&effect_pos - 2)->y += 5.0f;

            it_8026F7C8(&effect_pos - 2, &item_vel, 0);
        }
    }

    HSD_JObjSetFlagsAll(gp->u.inishie1.blocks[index].jobj2, JOBJ_HIDDEN);

    it_8026B294(gp->u.inishie1.blocks[index].item_gobj, &effect_pos);

    efSync_Spawn(0x442, gp->u.inishie1.blocks[index].item_gobj, &effect_pos);

    Ground_801C5414(0x136, 0xBA);
    Camera_80030E44(2, &effect_pos);
}

inline Item* GET_ITEM2(Item_GObj* arg0)
{
    return arg0->user_data;
}

void fn_801FBF6C(Item_GObj* item_gobj, Ground* gp, Vec3* pos, HSD_GObj* arg3,
                 f32 arg4)
{
    HSD_GObj* new_var;
    s32 i;
    HSD_GObj* map_gobj;
    Item* ip = GET_ITEM2(item_gobj);

    for (i = 0; i < 19; i++) {
        if (gp->u.inishie1.blocks[i].jobj2 ==
            (HSD_JObj*) ip->xDD4_itemVar.it_266F.x4)
        {
            break;
        }
    }

    if ((u32) i == 19) {
        return;
    }

    map_gobj = Ground_801C2BA4(3);
    HSD_ASSERT(0x425, map_gobj);

    new_var = map_gobj;
    grInishie1_801FB0AC(map_gobj, i);
    grInishie1_801FBCEC(new_var, i);
    PAD_STACK(16);
}

void grInishie1_801FC018(HSD_GObj* gobj)
{
    Ground* gp = gobj->user_data;

    gp->u.inishie1.xEE = 0;
    gp->u.inishie1.xE0 = 0.0f;
    gp->u.inishie1.xE4 = 0.0f;
    gp->u.inishie1.xE8 = 0;
    gp->u.inishie1.xEA = 0;
    gp->u.inishie1.xF0 = 0.0f;
    gp->u.inishie1.xF4 = 0.0f;

    gp->u.inishie1.x108 = Ground_801C3FA4(gobj, 0x1a);
    gp->u.inishie1.x10C = Ground_801C3FA4(gobj, 0x1c);

    gp->u.inishie1.xFC = HSD_JObjGetTranslationY(gp->u.inishie1.x108);

    gp->u.inishie1.x100 =
        (gp->u.inishie1.x108 == NULL) ? NULL : gp->u.inishie1.x108->child;
    gp->u.inishie1.x104 =
        (gp->u.inishie1.x10C == NULL) ? NULL : gp->u.inishie1.x10C->child;

    mpJointSetCb1(0x15, gp, fn_801FC9AC);
    mpJointSetCb1(0x14, gp, fn_801FC9AC);
    PAD_STACK(16);
}

void grInishie1_801FC110(HSD_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    f32 dist_lo;
    f32 dist_hi;

    if (gp->u.inishie1.xE0 > 100000.0f || gp->u.inishie1.xE4 > 100000.0f) {
        gp->u.inishie1.xE4 = 100000.0f;
        gp->u.inishie1.xE0 = 100000.0f;
    }

    dist_lo = gp->u.inishie1.xE0 - grI1_804D69F8->unk2C[1].y;
    if (dist_lo < 0.0f) {
        dist_lo = 0.0f;
    }
    dist_hi = gp->u.inishie1.xE4 - grI1_804D69F8->unk2C[1].y;
    if (dist_hi < 0.0f) {
        dist_hi = 0.0f;
    }

    if (dist_lo == 0.0f && dist_hi == 0.0f) {
        if ((gp->u.inishie1.xF0 < 0.0f ? -gp->u.inishie1.xF0
                                       : gp->u.inishie1.xF0) > 0.0f)
        {
            if (gp->u.inishie1.xF0 < 0.0f) {
                gp->u.inishie1.xF0 += grI1_804D69F8->unk2C[1].x;
                if (gp->u.inishie1.xF0 > 0.0f) {
                    gp->u.inishie1.xF0 = 0.0f;
                }
            } else {
                gp->u.inishie1.xF0 -= grI1_804D69F8->unk2C[1].x;
                if (gp->u.inishie1.xF0 < 0.0f) {
                    gp->u.inishie1.xF0 = 0.0f;
                }
            }
        }

        gp->u.inishie1.xF4 = 0.0f;
    } else {
        f32 accel = dist_hi - dist_lo;
        gp->u.inishie1.xF4 = accel * grI1_804D69F8->unk24 + gp->u.inishie1.xF4;

        if (gp->u.inishie1.xF4 > grI1_804D69F8->unk28) {
            gp->u.inishie1.xF4 = grI1_804D69F8->unk28;
        } else if (gp->u.inishie1.xF4 < -grI1_804D69F8->unk28) {
            gp->u.inishie1.xF4 = -grI1_804D69F8->unk28;
        }

        if (dist_lo && dist_hi && gp->u.inishie1.xF4) {
            gp->u.inishie1.xF4 *= grI1_804D69F8->unk2C[0].x;
        } else {
            gp->u.inishie1.xF4 *= grI1_804D69F8->unk2C[0].y;

            if (gp->u.inishie1.xF4 > 0.0f) {
                gp->u.inishie1.xF4 -= grI1_804D69F8->unk2C[0].z;
                if (gp->u.inishie1.xF4 < 0.0f) {
                    gp->u.inishie1.xF4 = 0.0f;
                }
            } else if (gp->u.inishie1.xF4 < 0.0f) {
                gp->u.inishie1.xF4 += grI1_804D69F8->unk2C[0].z;
                if (gp->u.inishie1.xF4 > 0.0f) {
                    gp->u.inishie1.xF4 = 0.0f;
                }
            }
        }

        gp->u.inishie1.xF0 += gp->u.inishie1.xF4;
    }

    {
        if (fabsf_inline(gp->u.inishie1.xF0) > grI1_804D69F8->unk20) {
            if (gp->u.inishie1.xF0 < 0.0f) {
                gp->u.inishie1.xF0 = -grI1_804D69F8->unk20;
            } else {
                gp->u.inishie1.xF0 = grI1_804D69F8->unk20;
            }
            gp->u.inishie1.xEE = 1;
            gp->u.inishie1.xF4 = 0.0f;
        }

        HSD_JObjSetTranslateY(gp->u.inishie1.x108,
                              gp->u.inishie1.xFC + gp->u.inishie1.xF0);
        HSD_JObjSetTranslateY(gp->u.inishie1.x10C,
                              gp->u.inishie1.xFC - gp->u.inishie1.xF0);

        gp->u.inishie1.xE8 = 0;
        gp->u.inishie1.xEA = 0;
        gp->u.inishie1.xE0 = 0.0f;
        gp->u.inishie1.xE4 = 0.0f;
    }
}

static inline s32 get_block_id(s32 block_id)
{
    int i = BLOCK_COUNT;
    s32 idx = 0;
    while (i != 0) {
        if (block_id == grI1_803E49B8[idx].idx) {
            return idx;
        }
        idx += 1;
        i -= 1;
    }
    OSReport("%s:%d: oioi..\n", "grinishie1.c", 0x1F0);
    while (true) {
    }
    return idx;
}

/// @copydoc mpLib_JointCollisionCallback
void fn_801FBEB8(void* user_data, int joint_id, CollData* coll, int coll_x50,
                 mpLib_GroundEnum ground_kind, float delta_y)
{
    s32 id = get_block_id(joint_id);
    if (fabsf_inline(delta_y) > 0.7) {
        HSD_GObj* gobj = Ground_801C2BA4(3);
        grInishie1_801FB0AC(gobj, id);
        grInishie1_801FBCEC(gobj, id);
    }
}

void grInishie1_801FC4A0(HSD_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    s32 reached = 0;
    f32 zero = 0.0f;

    if (gp->u.inishie1.xF0 != zero) {
        if (gp->u.inishie1.xF0 < zero) {
            gp->u.inishie1.xF0 += grI1_804D69F8->unk50;
            if (gp->u.inishie1.xF0 >= zero) {
                reached = 1;
            }
        } else {
            gp->u.inishie1.xF0 -= grI1_804D69F8->unk50;
            if (gp->u.inishie1.xF0 <= zero) {
                reached = 1;
            }
        }
    }
    if (reached) {
        gp->u.inishie1.xF0 = 0.0f;
        gp->u.inishie1.xF4 = 0.0f;
        gp->u.inishie1.xE0 = 0.0f;
        gp->u.inishie1.xE4 = 0.0f;
        gp->u.inishie1.xEE = 0;
    }
    HSD_JObjSetTranslateY(gp->u.inishie1.x108,
                          gp->u.inishie1.xFC + gp->u.inishie1.xF0);
    HSD_JObjSetTranslateY(gp->u.inishie1.x10C,
                          gp->u.inishie1.xFC - gp->u.inishie1.xF0);
}

void grInishie1_801FC664(HSD_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    f32 t;
    f32 bottom;
    UNUSED u32 unused1;
    Vec3 sp24;
    Vec3 sp18;
    UNUSED u32 unused2;
    UNUSED u32 unused3;
    UNUSED u32 unused4;

    switch (gp->u.inishie1.xEE) {
    case 0:
        grInishie1_801FC110(gobj);
        return;
    case 1:
        gp->u.inishie1.xF4 += grI1_804D69F8->unk44;
        t = grI1_804D69F8->unk48;
        if (gp->u.inishie1.xF4 > t) {
            gp->u.inishie1.xF4 = t;
        }
        HSD_JObjAddTranslationY(gp->u.inishie1.x100, -gp->u.inishie1.xF4);
        HSD_JObjAddTranslationY(gp->u.inishie1.x104, -gp->u.inishie1.xF4);
        bottom = -30.0f + Stage_GetBlastZoneBottomOffset();
        lb_8000B1CC(gp->u.inishie1.x100, NULL, &sp18);
        lb_8000B1CC(gp->u.inishie1.x104, NULL, &sp24);
        if (sp18.y < bottom && sp24.y < bottom) {
            gp->u.inishie1.xEE = 2;
            gp->u.inishie1.xF4 = 0.0f;
            gp->u.inishie1.xEC = grI1_804D69F8->unk4C;
        }
        return;
    case 2:
        gp->u.inishie1.xEC--;
        if (gp->u.inishie1.xEC == 0) {
            gp->u.inishie1.xEE = 3;
            HSD_JObjSetTranslateY(gp->u.inishie1.x100, 0.0f);
            HSD_JObjSetTranslateY(gp->u.inishie1.x104, 0.0f);
            mpLib_80055E9C(0x14);
            mpLib_80055E9C(0x15);
            mpLib_80057424(0x14);
            mpLib_80057424(0x15);
            return;
        }
        break;
    case 3:
        grInishie1_801FC4A0(gobj);
        break;
    }
}

/// @copydoc mpLib_JointCollisionCallback
void fn_801FC9AC(void* user_data, int joint_id, CollData* coll, int coll_x50,
                 mpLib_GroundEnum ground_kind, float delta_y)
{
    Ground* gp = user_data;
    if (joint_id == 0x14) {
        gp->u.inishie1.xE8 += 1;
        if (ground_kind == 1) {
            gp->u.inishie1.xE0 += (f32) coll_x50 * grI1_804D69F8->unk2C[1].z;
        } else {
            gp->u.inishie1.xE0 += (f32) coll_x50;
        }
    } else if (joint_id == 0x15) {
        gp->u.inishie1.xEA += 1;
        if (ground_kind == 1) {
            gp->u.inishie1.xE4 += (f32) coll_x50 * grI1_804D69F8->unk2C[1].z;
        } else {
            gp->u.inishie1.xE4 += (f32) coll_x50;
        }
    }
}

bool grInishie1_801FCAAC(int line_id)
{
    if (stage_info.internal_stage_id == INISHIE1 && line_id != -1) {
        int result;
        u32 joint;

        joint = mpJointFromLine(line_id) - 20;
        result = 1;
        if (joint > 1) {
            result = 0;
        }
        if (result != 0) {
            return true;
        }
    }
    return false;
}

void grInishie1_801FCB10(HSD_GObj* gobj)
{
    Ground* gp;
    u32 time_remaining;
    s32 var_r3;

    gp = GET_GROUND(gobj);
    if (gp->u.inishie2.xC4_flags.b0 == 0) {
        if (GetMatchTimer((int*) &time_remaining) != 0) {
            if (time_remaining < 20) {
                s32 temp_r3 = Ground_801C5A94();
                if (temp_r3 == 0x29) {
                    var_r3 = 0x2A;
                } else if (temp_r3 == 0x2B) {
                    var_r3 = 0x2C;
                } else {
                    var_r3 = -1;
                }
                lbAudioAx_80023F28(var_r3);
                gp->u.inishie2.xC4_flags.b0 = 1;
            }
        } else {
            gp->u.inishie2.xC4_flags.b0 = 1;
        }
    }
}

DynamicsDesc* grInishie1_801FCBB0(enum_t arg)
{
    return false;
}

bool grInishie1_801FCBB8(Vec3* arg, int arg0, HSD_JObj* jobj)
{
    return true;
}
