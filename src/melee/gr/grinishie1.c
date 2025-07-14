
#include <platform.h>

#include "gr/grinishie1.h"

#include "cm/camera.h"
#include "ef/efsync.h"
#include "gm/gm_1601.h"
#include "gr/grdisplay.h"
#include "gr/grlib.h"
#include "gr/grmaterial.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "it/it_266F.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "lb/lbaudio_ax.h"
#include "mp/mplib.h"
#include "sysdolphin/baselib/dobj.h"
#include "sysdolphin/baselib/gobjgxlink.h"
#include "sysdolphin/baselib/gobjproc.h"
#include "sysdolphin/baselib/jobj.h"
#include "sysdolphin/baselib/memory.h"
#include "sysdolphin/baselib/random.h"

#include <baselib/gobj.h>

#define invalid_state(line)                                                   \
    OSReport("%s:%d: oioi...", "grinishie1.c", line);                         \
    while (true) {                                                            \
    }

// these inlines are probably shared in other places
static inline test_random(s32 val)
{
    return ((val != 0) ? HSD_Randi(val) : 0);
}

static inline s32 randi_between(s32 min, s32 max)
{
    if (max > min) {
        return min + test_random(max - min);
    } else if (min > max) {
        return max + test_random(min - max);
    } else {
        return min;
    }
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
    u16 unk1A;
    u32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    Vec3 unk2C[2];
} grInishie1_stuff;

grInishie1_stuff* grI1_804D69F8;
Vec3 grI1_803B8268;

#define DOBJ_LOOP(jobj)                                                       \
    {                                                                         \
        HSD_DObj* dobj = HSD_JObjGetDObj(jobj);                               \
        while (dobj != NULL) {                                                \
            HSD_DObjSetFlags(dobj, 1U);                                       \
            dobj = (dobj != NULL) ? dobj->next : NULL;                        \
        }                                                                     \
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

void grInishie1_801FA908(void) {}

// corresponds with the 3 - 13 - 3 block pattern on the stage
#define BLOCK_COUNT 19

struct block_table_struct {
    s16 idx;
    s16 jobj_idx;
};

struct block_table_struct block_idx_table[BLOCK_COUNT];

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
    grZakoGenerator_801CAE04(0);
}

bool grInishie1_801FA9AC(void)
{
    return false;
}

HSD_GObj* grInishie1_801FA9B4(s32 arg0)
{
    StageCallbacks* cb = &grI1_803E48F4[arg0];
    HSD_GObj* gobj = Ground_801C14D0(arg0);

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
            HSD_GObjProc_8038FD54(gobj, cb->callback2, 4U);
        }
    } else {
        OSReport("%s:%d: couldn't get gobj(id=%d)\n", "grinishie1.c", 0xE7,
                 arg0);
    }

    return gobj;
}

void grInishie1_801FAAA0(HSD_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grInishie1_801FAACC(HSD_GObj* gobj)
{
    return false;
}

void grInishie1_801FAAD4(HSD_GObj* gobj) {}

void grInishie1_801FAAD8(HSD_GObj* gobj) {}

void grInishie1_801FAADC(HSD_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    Ground_801C2ED0(gobj->hsd_obj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
    grInishie1_801FAD84(gobj);
    grInishie1_801FC018(gobj);
    gp->gv.inishie1.xC4_flags_b0 = 0;
    grMaterial_801C8858(Ground_801C3FA4(gobj, 0x2D), 0x20000000U);
}

bool grInishie1_801FAB60(HSD_GObj* gobj)
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

void grInishie1_801FABB0(HSD_GObj* gobj) {}

void grInishie1_801FABB4(HSD_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x8_callback = NULL;
    gp->xC_callback = NULL;
}

bool grInishie1_801FABF4(HSD_GObj* gobj)
{
    return false;
}

void grInishie1_801FABFC(HSD_GObj* gobj) {}

void grInishie1_801FAC00(HSD_GObj* gobj) {}

void grInishie1_801FAC04(HSD_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->gv.inishie12.xC4 = NULL;
    gp->gv.inishie12.xC8 = grI1_804D69F8->unk16;
    gp->gv.inishie12.xCC = 0;
}

bool grInishie1_801FAC50(HSD_GObj* gobj)
{
    return false;
}

void grInishie1_801FAC58(HSD_GObj* gobj)
{
    Vec3 vec;
    HSD_JObj* jobj;
    HSD_Joint* joint;
    Ground* gp;

    gp = GET_GROUND(gobj);
    jobj = GET_JOBJ(gobj);

    if (gp && jobj) {
        if (gp->gv.inishie12.xCC == 0) {
            if (gp->gv.inishie12.xC8 > 0) {
                if (gp->gv.inishie12.xC8 & 1) {
                    HSD_JObjClearFlagsAll(jobj, 0x10U);
                } else {
                    HSD_JObjSetFlagsAll(jobj, 0x10U);
                }
                gp->gv.inishie12.xC8 -= 1;
            }
        }

        if (gp->gv.inishie12.xC4 != NULL) {
            lb_8000B1CC(gp->gv.inishie12.xC4, NULL, &vec);
            HSD_JObjSetTranslate(jobj, &vec);
        }
    }
}

void grInishie1_801FAD80(HSD_GObj* gobj) {}

void grInishie1_801FAD84(HSD_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    struct grInishie1_GroundVars2* vars = &gp->gv.inishie12;
    int i;

    vars->blocks = (grInishie1_Block*) HSD_MemAlloc(sizeof(grInishie1_Block) *
                                                    BLOCK_COUNT);

    i = 0;
    while (i < BLOCK_COUNT) {
        s16 value;
        int found;
        int j;
        HSD_JObj* jobj;

        if (i < 0 || i > BLOCK_COUNT) {
            invalid_state(0x1F9);
        }
        value = block_idx_table[i].idx;
        found = -1;

        for (j = 0; j < BLOCK_COUNT; j++) {
            if (value == block_idx_table[j].idx) {
                found = j;
                break;
            }
        }

        if (found == -1) {
            invalid_state(0x217);
        }

        jobj = Ground_801C3FA4(gobj, block_idx_table[found].jobj_idx);
        if (jobj == NULL) {
            invalid_state(0x21D);
        }

        {
            grInishie1_Block* slot = &vars->blocks[i];

            slot->x2 = 0;
            slot->x4 = 0;
            slot->jobj2 = jobj;
            slot->hatena_gobj = NULL;
            slot->x8 = HSD_JObjGetTranslationY(jobj);
            slot->xC = 0.0f;
            slot->jobj2 = NULL;
        }

        mpLib_800581A4((s32) value, (s32) gp, (s32) fn_801FBEB8);
        i++;
    }

    for (i = 0; i < BLOCK_COUNT; i++) {
        grInishie1_Block* slot = &vars->blocks[i];

        HSD_GObj* new_gobj =
            grMaterial_801C8CFC(8, 0, gp, slot->jobj, NULL, fn_801FBF6C, NULL);

        if (new_gobj != NULL) {
            grMaterial_801C8DE0(new_gobj, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                                6.0f);
            grMaterial_801C8E08(new_gobj);
            grMaterial_801C8E68(new_gobj, 0);
        }

        slot->item_gobj = new_gobj;
    }

    if (gm_8016AE80() != -1 && gm_8016B238() == 0) {
        int item_kind = It_Common_Start;
        // maybe it_8026D324 returns how many of x item there is or
        // how many have spawned?
        while (item_kind < It_Common_End && it_8026D324(item_kind) == 0) {
            item_kind++;
        }

        if (item_kind != It_Common_End) {
            grInishie1_Block* slot1;
            grInishie1_Block* slot2;
            s16 index1 = HSD_Randi(BLOCK_COUNT);
            s16 index2;

            do {
                index2 = HSD_Randi(BLOCK_COUNT);
            } while (index2 == index1);

            slot1 = &vars->blocks[index1];
            slot2 = &vars->blocks[index2];

            slot1->status = 1;
            grInishie1_801FBAA0(gobj, index1);
            if (slot1->hatena_gobj != NULL) {
                Ground* hatena_gp = GET_GROUND(slot1->hatena_gobj);
                hatena_gp->gv.inishie12.xCC = 1;
            }

            slot2->status = 2;
            grInishie1_801FBAA0(gobj, index2);
            if (slot2->hatena_gobj != NULL) {
                Ground* hatena_gp = GET_GROUND(slot1->hatena_gobj);
                hatena_gp->gv.inishie12.xCC = 1;
            }
        }
    }

    vars->xC6 = 0;
    vars->xC8 = 0;
    vars->xCA = -1;
    vars->xCC = -1;
    vars->xD8 = 0;
}

void grInishie1_801FB0AC(HSD_GObj* gobj, u32 index)
{
    Ground* gp = gobj->user_data;
    if (gp->gv.inishie12.blocks[index].status == 1) {
        grInishie1_801FBA34(gobj, gp->gv.inishie12.blocks[index].jobj);
        gp->gv.inishie12.blocks[index].status = 0;
        grInishie1_801FBC4C(gobj, index);

        gp->gv.inishie12.xC6 =
            randi_between(grI1_804D69F8->unk0, grI1_804D69F8->unk4);
    } else if (gp->gv.inishie12.blocks[index].status == 2) {
        grInishie1_801FBA34(gobj, gp->gv.inishie12.blocks[index].jobj);
        gp->gv.inishie12.blocks[index].status = 0;
        grInishie1_801FBC4C(gobj, index);

        gp->gv.inishie12.xC8 =
            randi_between(grI1_804D69F8->unk8, grI1_804D69F8->unkC);
    } else if (gp->gv.inishie12.blocks[index].status == 3) {
        grInishie1_801FBA34(gobj, gp->gv.inishie12.blocks[index].jobj);
        gp->gv.inishie12.blocks[index].status = 0;
        grInishie1_801FBC4C(gobj, index);

        {
            int i;
            bool match = false;
            for (i = 0; i < 0x13; i++) {
                if (gp->gv.inishie12.blocks[i].status == 3) {
                    match = true;
                    break;
                }
            }
            if (!match) {
                gp->gv.inishie12.xC6 =
                    randi_between(grI1_804D69F8->unk0, grI1_804D69F8->unk4);
                gp->gv.inishie12.xC8 =
                    randi_between(grI1_804D69F8->unk8, grI1_804D69F8->unkC);
            }
        }

        gp->gv.inishie12.xD8 = grI1_804D69F8->unk10;
    } else {
        if (gp->gv.inishie12.blocks[index].hatena_gobj != NULL) {
            __assert("grinishie1.c", 0x29D, "0");
        }
    }
}

inline void grInishie1_801FB3F0_inline(HSD_GObj* gobj, s16* countdown,
                                       s16* last_index, s16 status_val,
                                       grInishie1_Block* blocks)
{
    if (*countdown > 0) {
        (*countdown)--;
        if (*countdown == 0) {
            int attempts = 0;
            s16 index;

            do {
                index = HSD_Randi(0x13);
                attempts++;
            } while ((index == *last_index || blocks[index].status != 0) &&
                     attempts < 0x14);

            if (attempts == 0x14) {
                __assert("grinishie1.c", 0x2D0U, "%s:%d: oioi...");
            }

            *last_index = index;
            blocks[index].status = status_val;
            grInishie1_801FBAA0(gobj, index);
            blocks[index].x20 = 0;
        }
    }
}

void grInishie1_801FB3F0(HSD_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    struct grInishie1_GroundVars* vars = &gp->gv.inishie1;
    HSD_DObj* dobj;
    int i;

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
            vars->blocks[i].status = 3;
            grInishie1_801FBAA0(gobj, i);
            vars->blocks[i].x20 = 0;
        }
    } else {
        grInishie1_801FB3F0_inline(gobj, &vars->xC6, &vars->xCA, 1,
                                   vars->blocks);
        grInishie1_801FB3F0_inline(gobj, &vars->xC8, &vars->xCC, 2,
                                   vars->blocks);
    }

    for (i = 0; i < 0x13; ++i) {
        grInishie1_Block* slot = &vars->blocks[i];

        switch (slot->status) {
        case 2:
            if (slot->x4 > 0) {
                slot->x4--;
            }
            break;

        case 3:
            slot->xC = 1.2f;
            grInishie1_801FB0AC(gobj, i);
            slot->status = 4;
            // fallthrough

        case 4:
            slot->x8 += slot->xC;

            if (slot->x8 > 5.0f) {
                slot->xC = -1.2f;
            } else if (slot->x8 < 0.0f) {
                slot->x8 = 0.0f;
                slot->status = 2;
                slot->x4 = 10;
            }

            // the blocks appear to not move at all, so not
            // sure what this is
            if (slot->jobj != NULL) {
                HSD_JObjSetTranslateY(slot->jobj, slot->x8);
            }
            break;

        case 0:
            if (slot->x20 > 0) {
                slot->x20--;
            } else {
                Vec3 pos;
                lb_8000B1CC(slot->jobj, NULL, &pos);
                if (!grLib_801C9EE8(&pos, 15.0f)) {
                    DOBJ_LOOP(slot->jobj);
                    HSD_JObjClearFlagsAll(slot->jobj, 0x10U);
                    grMaterial_801C8E08(slot->item_gobj);
                    slot->status = 1;
                    slot->x22 = grI1_804D69F8->unk18;
                }
            }

            if (slot->hatena_gobj != NULL) {
                HSD_JObj* sub_jobj = ((HSD_GObj*) slot->hatena_gobj)->hsd_obj;
                if (!(HSD_JObjGetFlags(sub_jobj) & 0x10)) {
                    HSD_JObjSetFlagsAll(sub_jobj, 0x10U);
                }
            }
            break;
        case 1:
            /*
               probably sets the flickering for blocks when they spawn
            */
            if (slot->x22 > 0) {
                HSD_JObjGetDObj(slot->jobj);
                if (slot->hatena_gobj != NULL) {
                    HSD_JObj* target =
                        ((HSD_GObj*) slot->hatena_gobj)->hsd_obj;

                    if (slot->x22 & 1) {
                        HSD_JObjClearFlagsAll(target, 0x10U);
                    } else {
                        HSD_JObjSetFlagsAll(target, 0x10U);
                    }

                    DOBJ_LOOP(slot->jobj);
                } else {
                    if (slot->x22 & 1) {
                        DOBJ_LOOP(slot->jobj);
                    } else {
                        DOBJ_LOOP(slot->jobj);
                    }
                }

                slot->x22--;
            } else {
                slot->status = 2;
                slot->x4 = 0;
            }
            break;
        }
    }
}

// gives item from hatena block upwards velocity, maybe handles spawning it as
// well
void grInishie1_801FBA34(HSD_GObj* gobj, HSD_JObj* jobj)
{
    Vec3 sp1C;
    Vec3 vec;
    lb_8000B1CC(jobj, NULL, &sp1C);
    vec = grI1_803B8268;
    sp1C.y += 5.0f;
    it_8026F7C8(&sp1C, &vec, 0);
}

// creates a hatena block
void grInishie1_801FBAA0(HSD_GObj* gobj, s32 index)
{
    HSD_JObj* hatena_jobj;
    Vec3 position;
    Ground* hatena_gp;
    Ground* gp = gobj->user_data;
    struct grInishie1_GroundVars* vars = &gp->gv.inishie1;
    struct grInishie1_Block* slot = &vars->blocks[index];

    HSD_GObj* hatena = grInishie1_801FA9B4(2);
    if (hatena == NULL) {
        return;
    }

    if (slot->hatena_gobj != NULL) {
        __assert("grinishie1.c", 0x39E, "!mapgp->u.map.block[ix].hatena_gobj");
    }

    slot->hatena_gobj = hatena;

    hatena_jobj = hatena->hsd_obj;
    lb_8000B1CC(slot->jobj, NULL, &position);
    HSD_JObjSetTranslate(hatena_jobj, &position);

    hatena_gp = hatena->user_data;
    hatena_gp->gv.inishie13.xC4 = slot->jobj;

    if (slot->status == 0 || slot->status == 1) {
        hatena_gp->gv.inishie13.xCC = 1;
    }

    DOBJ_LOOP(slot->jobj);
}

void grInishie1_801FBC4C(HSD_GObj* gobj, u32 index)
{
    Ground* gp = GET_GROUND(gobj);
    DOBJ_LOOP(gp->gv.inishie1.blocks[index].jobj2);
    Ground_801C4A08(gp->gv.inishie1.blocks[index].hatena_gobj);
    gp->gv.inishie1.blocks[index].hatena_gobj = NULL;
}

void grInishie1_801FBCEC(HSD_GObj* gobj, u32 index)
{
    Ground* gp = gobj->user_data;
    Vec3 effect_pos;
    Vec3 item_spawn_offset;

    gp->gv.inishie1.blocks[index].status = 0;
    gp->gv.inishie1.blocks[index].x20 =
        randi_between(grI1_804D69F8->unk1A, grI1_804D69F8->unk1C);

    HSD_DObjSetFlags(HSD_JObjGetDObj(gp->gv.inishie1.blocks[index].jobj), 1U);

    grMaterial_801C8E28(gp->gv.inishie1.blocks[index].item_gobj);

    if (gp->gv.inishie1.blocks[index].status == 1 ||
        gp->gv.inishie1.blocks[index].status == 2 ||
        gp->gv.inishie1.blocks[index].status == 3)
    {
        Ground_801C4A08(gp->gv.inishie1.blocks[index].hatena_gobj);
        gp->gv.inishie1.blocks[index].hatena_gobj = NULL;

        lb_8000B1CC(gp->gv.inishie1.blocks[index].jobj, NULL,
                    &item_spawn_offset);

        item_spawn_offset.y += 5.0f;

        it_8026F7C8(&item_spawn_offset, &grI1_803B8268, 0);
    }

    HSD_JObjSetFlagsAll(gp->gv.inishie1.blocks[index].jobj, 0x10U);

    it_8026B294(gp->gv.inishie1.blocks[index].item_gobj, &effect_pos);

    efSync_Spawn(0x442, gp->gv.inishie1.blocks[index].item_gobj, &effect_pos);

    Ground_801C5414(0x136, 0xBA);
    Camera_80030E44(2, &effect_pos);
}

/// #fn_801FBF6C

/// #grInishie1_801FC018

void grInishie1_801FC110(HSD_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    struct grInishie1_GroundVars* vars = &gp->gv.inishie1;
    f32 dist_lo;
    f32 dist_hi;

    if (vars->xE0 > 100000.0f || vars->xE4 > 100000.0f) {
        vars->xE0 = 100000.0f;
        vars->xE4 = 100000.0f;
    }

    dist_lo = fclamp0(gp->gv.inishie1.xE0 - grI1_804D69F8->unk2C[1].y);
    dist_hi = fclamp0(gp->gv.inishie1.xE4 - grI1_804D69F8->unk2C[1].y);

    if (dist_lo == 0.0f && dist_hi == 0.0f) {
        if (fabsf_inline(gp->gv.inishie1.xF0) > 0.0f) {
            if (gp->gv.inishie1.xF0 < 0.0f) {
                gp->gv.inishie1.xF0 += grI1_804D69F8->unk2C[1].z;
                if (gp->gv.inishie1.xF0 > 0.0f) {
                    gp->gv.inishie1.xF0 = 0.0f;
                }
            } else {
                gp->gv.inishie1.xF0 -= grI1_804D69F8->unk2C[1].z;
                if (gp->gv.inishie1.xF0 < 0.0f) {
                    gp->gv.inishie1.xF0 = 0.0f;
                }
            }
        }

        gp->gv.inishie1.xF4 = 0.0f;
    } else {
        f32 max_speed;
        gp->gv.inishie1.xF4 += (dist_hi - dist_lo) * grI1_804D69F8->unk24;

        max_speed = grI1_804D69F8->unk28;
        if (gp->gv.inishie1.xF4 > max_speed) {
            gp->gv.inishie1.xF4 = max_speed;
        } else if (gp->gv.inishie1.xF4 < -max_speed) {
            gp->gv.inishie1.xF4 = -max_speed;
        }

        if (dist_lo != 0.0f && dist_hi != 0.0f && gp->gv.inishie1.xF4 != 0.0f)
        {
            gp->gv.inishie1.xF4 *= grI1_804D69F8->unk2C[0].x;
        } else {
            f32 friction;
            gp->gv.inishie1.xF4 *= grI1_804D69F8->unk2C[1].x;

            friction = grI1_804D69F8->unk2C[1].y;
            if (gp->gv.inishie1.xF4 > 0.0f) {
                gp->gv.inishie1.xF4 -= friction;
                if (gp->gv.inishie1.xF4 < 0.0f) {
                    gp->gv.inishie1.xF4 = 0.0f;
                }
            } else if (gp->gv.inishie1.xF4 < 0.0f) {
                gp->gv.inishie1.xF4 += friction;
                if (gp->gv.inishie1.xF4 > 0.0f) {
                    gp->gv.inishie1.xF4 = 0.0f;
                }
            }
        }

        gp->gv.inishie1.xF0 += gp->gv.inishie1.xF4;
    }

    {
        if (fabsf_inline(gp->gv.inishie1.xF0) > grI1_804D69F8->unk20) {
            gp->gv.inishie1.xF0 = fabsf_inline(gp->gv.inishie1.xF0);
            gp->gv.inishie1.xEE = 1;
            gp->gv.inishie1.xF4 = 0.0f;
        }

        HSD_JObjSetTranslateY(gp->gv.inishie1.x108,
                              gp->gv.inishie1.xFC + gp->gv.inishie1.xF0);
        HSD_JObjSetTranslateY(gp->gv.inishie1.x10C,
                              gp->gv.inishie1.xFC - gp->gv.inishie1.xF0);

        gp->gv.inishie1.xE8 = 0;
        gp->gv.inishie1.xEA = 0;
        gp->gv.inishie1.xE0 = 0.0f;
        gp->gv.inishie1.xE4 = 0.0f;
    }
}

static inline s32 get_block_id(s32 block_id)
{
    int i = BLOCK_COUNT;
    s32 idx = 0;
    while (i != 0) {
        if (block_id == block_idx_table[i].idx) {
            return idx;
        }
        idx += 1;
        i -= 1;
    }
    invalid_state(0x1F9);
    return idx;
}

void fn_801FBEB8(s32 block_id, f32 dist)
{
    s32 id = get_block_id(block_id);
    if (fabsf_inline(dist) > 0.7f) {
        HSD_GObj* gobj = Ground_801C2BA4(3);
        grInishie1_801FB0AC(gobj, id);
        grInishie1_801FBCEC(gobj, id);
    }
}

/// #grInishie1_801FC4A0

/// #grInishie1_801FC664

/// #fn_801FC9AC

/// #grInishie1_801FCAAC

void grInishie1_801FCB10(HSD_GObj* gobj)
{
    u32 time_remaining;
    s32 var_r3;

    Ground* gp = gobj->user_data;
    if (gp->gv.inishie2.xC4_flags.b0 == 0) {
        if (GetMatchTimer(&time_remaining) != 0) {
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
                gp->gv.inishie2.xC4_flags.b0 = 1;
            }
        } else {
            gp->gv.inishie2.xC4_flags.b0 = 1;
        }
    }
}

bool grInishie1_801FCBB0(void)
{
    return false;
}

bool grInishie1_801FCBB8(void)
{
    return true;
}
