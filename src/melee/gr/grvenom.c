#include "grvenom.h"

#include <platform.h>

#include "gr/grcorneria.h"
#include "gr/grdisplay.h"
#include "gr/grmaterial.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "gr/stage.h"
#include "gr/types.h"
#include "if/ifcoget.h"
#include "if/ifstatus.h"
#include "it/items/itarwinglaser.h"
#include "lb/lb_00B0.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbspdisplay.h"
#include "mp/mplib.h"
#include "pl/player.h"

#include <baselib/aobj.h>
#include <baselib/debug.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>
#include <baselib/lobj.h>
#include <baselib/random.h>
#include <baselib/sislib.h>

typedef struct grVe_Data {
    /* +0 */ S16Vec3 joints[5];
    /* +1E */ u16 pad;
    /* +20 */ struct {
        /* +20 */ HSD_GObj* arwing_gobj[3];
        int arwing_type[3];
    } arwing;
} grVe_Data;

static grVe_Data grVe_803E5348 = {
    {
        { 0, 5, 0 },
        { 1, 5, 0 },
        { 2, 9, 0 },
        { 4, 10, 0 },
        { 3, 13, 0 },
    },
};

static int grVe_ArwingGroups[3] = { 0 };

StageCallbacks grVe_803E538C[16] = {
    {
        grVenom_80203F98,
        grVenom_80203FC4,
        grVenom_80203FCC,
        grVenom_80203FD0,
        0,
    },
    {
        grVenom_80206B94,
        grVenom_80206BBC,
        grVenom_80206BC4,
        grVenom_80206BEC,
        0x20000000,
    },
    {
        grVenom_80204F20,
        grVenom_802052D8,
        grVenom_802053B0,
        grVenom_802056AC,
        0,
    },
    {
        grVenom_80205AD4,
        grVenom_80205DF0,
        grVenom_80205F30,
        grVenom_80206870,
        0,
    },
    {
        grVenom_80203FD4,
        grVenom_802040A4,
        grVenom_802040AC,
        grVenom_802040B0,
        0,
    },
    {
        grVenom_802040F0,
        grVenom_8020427C,
        grVenom_80204284,
        grVenom_80204424,
        0xC0000000,
    },
    {
        grVenom_80206874,
        grVenom_80206B68,
        grVenom_80206B70,
        grVenom_80206B90,
        0,
    },
    {
        grVenom_80204428,
        grVenom_80204544,
        grVenom_8020454C,
        grVenom_80204B84,
        0,
    },
    {
        grVenom_80204CE0,
        grVenom_80204CE4,
        grVenom_80204CEC,
        grVenom_80204DB0,
        0,
    },
    {
        grVenom_80204DD4,
        grVenom_80204EF4,
        grVenom_80204EFC,
        grVenom_80204F1C,
        0,
    },
    {
        grVenom_802056B0,
        grVenom_80205750,
        grVenom_80205758,
        grVenom_80205AD0,
        0,
    },
    {
        grVenom_802056B0,
        grVenom_80205750,
        grVenom_80205758,
        grVenom_80205AD0,
        0,
    },
    {
        grVenom_802056B0,
        grVenom_80205750,
        grVenom_80205758,
        grVenom_80205AD0,
        0,
    },
    {
        grVenom_802056B0,
        grVenom_80205750,
        grVenom_80205758,
        grVenom_80205AD0,
        0,
    },
    {
        grVenom_802056B0,
        grVenom_80205750,
        grVenom_80205758,
        grVenom_80205AD0,
        0,
    },
    {
        grVenom_802056B0,
        grVenom_80205750,
        grVenom_80205758,
        grVenom_80205AD0,
        0,
    },
};

StageData grVe_803E54CC = {
    VENOM,
    grVe_803E538C,
    "/GrVe",
    grVenom_80203B18,
    grVenom_80203B14,
    grVenom_80203DD0,
    grVenom_80203E80,
    grVenom_80203EA4,
    grVenom_80206D74,
    grVenom_80206D7C,
    0x00000001,
    grVe_803E5348.joints,
    5,
};

typedef struct grVe_StageData {
    f32 initial_spawn_delay_min;
    f32 initial_spawn_delay_max;
    f32 respawn_delay_min;
    f32 respawn_delay_max;
    f32 group4_chance;
    char x14[0x2C - 0x14];
    f32 maneuver_cooldown;
    char x30[0x34 - 0x30];
    f32 arwing_scale;
    s32 laser_effect_id;
} grVe_StageData;

static grVe_StageData* grVe_StageParams;
static u32 grVe_CurrentArwingSlot;
static s32 grVe_ArwingSpawnTimer;
static s32 grVe_ArwingUpdateDisabled;
static s32 grVe_MultiArwingMode;

typedef struct grVe_Lighting {
    char pad[0xE0];
    u8 xE0;
} grVe_Lighting;

typedef struct grVe_GroundData {
    char pad[0x2C];
    grVe_Lighting* x2C;
} grVe_GroundData;

/// grVenom_8020362C

static inline int* grVe_GetArwingTypes(grVe_Data* data)
{
    return data->arwing.arwing_type;
}

static inline s32 grVe_GetRandomArwingDelay(f32 fmin, f32 fmax)
{
    s32 imin = fmin;
    s32 imax = fmax;
    if (imax > imin) {
        s32 range = imax - imin;
        imax = imin + (range != 0 ? HSD_Randi(range) : 0);
    } else if (imax < imin) {
        s32 range = imin - imax;
        imax += (range != 0 ? HSD_Randi(range) : 0);
    }
    return imax;
}

void grVenom_8020362C(void)
{
    grVe_Data* data = &grVe_803E5348;
    s32 group_b;
    s32 group_a;
    s32 j;
    s32 idx;
    s32 i;
    s32 mode;
    s32 has_active;
    int* x2c_ptr;
    int* x38_ptr;
    HSD_GObj** x20_ptr;
    HSD_GObj** x20_next;
    PAD_STACK(0x20);

    if (!grVe_MultiArwingMode) {
        if (data->arwing.arwing_gobj[0] == NULL) {
            grVe_ArwingSpawnTimer = grVe_ArwingSpawnTimer - 1;
            if (grVe_ArwingSpawnTimer <= 0) {
                s32 combined;
                Ground* gp = Ground_801C2BA4(7)->user_data;
                group_a =
                    gp->u.venom2.xE0_state.b3 | gp->u.venom2.xE0_state.b4;
                group_b =
                    gp->u.venom2.xE0_state.b0 | gp->u.venom2.xE0_state.b1;
                group_b = group_b | gp->u.venom2.xE0_state.b2;
                group_a |= gp->u.venom2.xE0_state.b5;
                if (group_a) {
                    group_a = 2;
                } else {
                    group_a = 0;
                }
                if (group_b) {
                    group_b = 1;
                } else {
                    group_b = 0;
                }
                combined = group_b | group_a;
                if (combined != 2) {
                    do {
                        if (combined < 2) {
                            if (!combined) {
                                break;
                            }
                            return;
                        }
                        return;
                    } while (false);
                    {
                        int* x2c_base = grVe_GetArwingTypes(data);
                        x2c_ptr = &x2c_base[0];
                    }
                    idx = *x2c_ptr;
                    while (idx == *x2c_ptr) {
                        idx = HSD_Randi(0xB) + 1;
                    }
                    if (*(x38_ptr = &grVe_ArwingGroups[0]) == 4) {
                        mode = 1;
                    } else {
                        mode = (HSD_Randf() > grVe_StageParams->group4_chance)
                                   ? 1
                                   : 4;
                    }
                    grVe_CurrentArwingSlot = 0;
                    *x2c_ptr = idx;
                    *x38_ptr = mode;
                    data->arwing.arwing_gobj[grVe_CurrentArwingSlot] =
                        grVenom_80203EAC(2);
                    return;
                }
                {
                    int* far_x2c_ptr;
                    int* far_x38_ptr;
                    idx = *(far_x2c_ptr = &data->arwing.arwing_type[0]);
                    while (idx == *far_x2c_ptr) {
                        idx = HSD_Randi(4) + 1;
                    }
                    if (*(far_x38_ptr = &grVe_ArwingGroups[0]) == 4) {
                        mode = 1;
                    } else if (HSD_Randf() > grVe_StageParams->group4_chance) {
                        mode = 1;
                    } else {
                        mode = 4;
                    }
                    grVe_CurrentArwingSlot = 0;
                    *far_x2c_ptr = idx;
                    *far_x38_ptr = mode;
                    data->arwing.arwing_gobj[grVe_CurrentArwingSlot] =
                        grVenom_80203EAC(2);
                    return;
                }
            }
        } else {
            grVe_ArwingSpawnTimer =
                grVe_GetRandomArwingDelay(grVe_StageParams->respawn_delay_min,
                                          grVe_StageParams->respawn_delay_max);
        }
    } else {
        x20_ptr = &data->arwing.arwing_gobj[0];
        (void) x20_ptr;
        i = 0;
        if (x20_ptr[0] != NULL) {
            i = 1;
            if (*(x20_next = x20_ptr + 1) != NULL) {
                i = 2;
                if (x20_next[1] != NULL) {
                    i = 3;
                }
            }
        }
        if (i < 3) {
            grVe_ArwingSpawnTimer = grVe_ArwingSpawnTimer - 1;
            if (grVe_ArwingSpawnTimer <= 0) {
                has_active = 0;
                x2c_ptr = &data->arwing.arwing_type[0];
                for (j = 0; j < 3; j++) {
                    if (j != i) {
                        switch (x2c_ptr[j]) {
                        case 1:
                        case 2:
                        case 3:
                        case 4:
                        case 5:
                        case 6:
                        case 7:
                            if (x20_ptr[j] != NULL) {
                                has_active = 1;
                            }
                        }
                    }
                }
                if (!has_active) {
                    idx = data->arwing.arwing_type[i];
                    while (idx == data->arwing.arwing_type[0] ||
                           idx == data->arwing.arwing_type[1] ||
                           idx == data->arwing.arwing_type[2])
                    {
                        idx = HSD_Randi(0xB) + 1;
                    }
                    grVe_CurrentArwingSlot = i;
                    data->arwing.arwing_type[i] = idx;
                    grVe_ArwingGroups[i] = i + 1;
                    data->arwing.arwing_gobj[grVe_CurrentArwingSlot] =
                        grVenom_80203EAC(2);
                } else {
                    Ground* gp = Ground_801C2BA4(7)->user_data;
                    group_a =
                        gp->u.venom2.xE0_state.b3 | gp->u.venom2.xE0_state.b4;
                    group_b =
                        gp->u.venom2.xE0_state.b0 | gp->u.venom2.xE0_state.b1;
                    group_b = group_b | gp->u.venom2.xE0_state.b2;
                    group_a |= gp->u.venom2.xE0_state.b5;
                    if (group_a) {
                        group_a = 2;
                    } else {
                        group_a = 0;
                    }
                    if (group_b) {
                        group_b = 1;
                    } else {
                        group_b = 0;
                    }
                    if (!(group_b | group_a)) {
                        idx = data->arwing.arwing_type[i];
                        while (idx == data->arwing.arwing_type[0] ||
                               idx == data->arwing.arwing_type[1] ||
                               idx == data->arwing.arwing_type[2])
                        {
                            idx = HSD_Randi(4) + 8;
                        }
                        grVe_CurrentArwingSlot = i;
                        data->arwing.arwing_type[i] = idx;
                        grVe_ArwingGroups[i] = i + 1;
                        data->arwing.arwing_gobj[grVe_CurrentArwingSlot] =
                            grVenom_80203EAC(2);
                    }
                }
            }
        } else {
            grVe_ArwingSpawnTimer = 0xA;
        }
    }
}
void grVenom_80203B14(bool arg) {}

static inline void grVe_InitArwingSpawnTimer(void)
{
    int i = grVe_StageParams->initial_spawn_delay_min;
    int j = grVe_StageParams->initial_spawn_delay_max;
    if (j > i) {
        s32 diff = j - i;
        if (diff != 0) {
            diff = HSD_Randi(diff);
        } else {
            diff = 0;
        }
        j = i + diff;
    } else if (j < i) {
        s32 diff = i - j;
        if (diff != 0) {
            diff = HSD_Randi(diff);
        } else {
            diff = 0;
        }
        j = j + diff;
    }
    grVe_ArwingSpawnTimer = j;
}

/// Stage initialization function for Venom
void grVenom_80203B18(void)
{
    PAD_STACK(4);
    {
        Vec3 position;
        Ground_GObj* gobj;
        Ground* gp1;
        s32 flag;

        grVe_StageParams = Ground_801C49F8();
        grVenom_80203EAC(4);
        stage_info.unk8C.b4 = false;
        flag = true;
        stage_info.unk8C.b5 = flag;
        gobj = grVenom_80203EAC(0);
        {
            int i;
            for (i = 0; i < 3; i++) {
                grVe_803E5348.arwing.arwing_gobj[i] = 0;
                grVe_803E5348.arwing.arwing_type[i] = 0;
                grVe_ArwingGroups[i] = 0;
            }
        }
        flag = (Stage_80225194() == 0xE9) ? flag : 0;
        grVe_MultiArwingMode = flag;
        if (flag == 1) {
            grVe_ArwingSpawnTimer = 0x78;
        } else {
            grVe_InitArwingSpawnTimer();
        }
        {
            Ground_GObj* gobj1 = grVenom_80203EAC(5);
            gp1 = GET_GROUND(gobj1);
            gp1->u.venom.target_gobj = gobj;
            grVenom_80203EAC(9);
            gobj1 = grVenom_80203EAC(7);
            grAnime_801C8138(gobj1, 7, 0);
        }
        Ground_801C39C0();
        Ground_801C3BB4();
        {
            float zero;
            position.x = -1.0F;
            position.y = 1.0F;
            position.z = -1.0F;
            zero = 0.0F;
            lb_80011A50(&position, -1, 1.0F, zero, 1.0471976F, -100000.0F,
                        10000.0F, zero, -100000.0F);
        }
        {
            position.x = 1.0F;
            position.y = 1.0F;
            position.z = -1.0F;
            lb_80011A50(&position, -1, 1.0F, 0.0F, 1.0471976F, 0.0F, 10000.0F,
                        100000.0F, -100000.0F);
        }
        mpLib_80057BC0(3);
        mpLib_80057BC0(4);
        { /// @todo shared loop with #grVenom_8020454C
            HSD_GObj* gobj = Ground_801C498C();
            if (gobj != NULL) {
                HSD_LObj* lobj;
                if ((lobj = gobj->hsd_obj) != NULL) {
                    while (lobj != NULL) {
                        if (lobj->aobj != NULL) {
                            HSD_AObjSetFlags(lobj->aobj, AOBJ_LOOP);
                        }
                        if (lobj->position != NULL) {
                            HSD_ForeachAnim(lobj->position, WOBJ_TYPE,
                                            ALL_TYPE_MASK, HSD_AObjSetFlags,
                                            AOBJ_ARG_AU, AOBJ_LOOP);
                        }
                        if (lobj->interest != NULL) {
                            HSD_ForeachAnim(lobj->interest, WOBJ_TYPE,
                                            ALL_TYPE_MASK, HSD_AObjSetFlags,
                                            AOBJ_ARG_AU, AOBJ_LOOP);
                        }
                        lobj = HSD_LObjGetNext(lobj);
                    }
                }
            }
        }
    }
}

void grVenom_80203DD0(void)
{
    HSD_GObj* gobj;
    HSD_LObj* lobj;

    gobj = HSD_GObj_Entities->xC;
    while (gobj != NULL) {
        if (HSD_GObjGetClassifier(gobj) == 0xC) {
            lobj = GET_LOBJ(gobj);
            while (lobj != NULL) {
                HSD_ForeachAnim(lobj, LOBJ_TYPE, ALL_TYPE_MASK,
                                HSD_AObjSetFlags, AOBJ_ARG_AU, AOBJ_LOOP);
                lobj = HSD_LObjGetNext(lobj);
            }
            return;
        }
        gobj = HSD_GObjGetNext(gobj);
    }
}

void grVenom_80203E80(void)
{
    grZakoGenerator_801CAE04(NULL);
}

bool grVenom_80203EA4(void)
{
    return false;
}

/// grVenom_80203EAC

Ground_GObj* grVenom_80203EAC(int gobj_id)
{
    Ground_GObj* gobj;
    Ground* gp;
    grVe_Data* base = &grVe_803E5348;
    StageCallbacks* callbacks =
        &((StageCallbacks*) ((char*) base + 0x44))[gobj_id];

    gobj = Ground_GetStageGObj(gobj_id);

    if (gobj != NULL) {
        gp = gobj->user_data;
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
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grvenom.c", 0x23B,
                 gobj_id);
    }

    return gobj;
}

/// Per-state map animation ids, read via the stage data base pointer
/// (`base[state + 0x7A]`, see #grVenom_802053B0); trailing entries are
/// the zero/3/6 words observed in the reference object.
static int grVe_803E5530[53] = {
    -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 0, 0, 0, 0, 0, 0,
    0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0,
    0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  3, 3, 3, 3, 6,
};

void grVenom_80203F98(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grVenom_80203FC4(Ground_GObj* arg)
{
    return false;
}

void grVenom_80203FCC(Ground_GObj* arg) {}

void grVenom_80203FD0(Ground_GObj* arg) {}

void grVenom_80203FD4(Ground_GObj* gobj)
{
    HSD_JObj* jobj1;
    HSD_JObj* jobj4;
    HSD_JObj* jobj3;
    HSD_JObj* jobj2;
    HSD_JObj* jobj5;
    HSD_JObj* jobj6;
    Ground* gp = gobj->user_data;
    PAD_STACK(8);

    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x11_flags.b012 = 2;
    jobj6 = Ground_801C3FA4(gobj, 6);
    jobj5 = Ground_801C3FA4(gobj, 5);
    jobj2 = Ground_801C3FA4(gobj, 2);
    jobj3 = Ground_801C3FA4(gobj, 3);
    jobj4 = Ground_801C3FA4(gobj, 4);
    jobj1 = Ground_801C3FA4(gobj, 1);
    Ground_801C4E70(jobj1, jobj4, jobj3, jobj2, jobj5, jobj6);
    gp = gobj->user_data;
    gp->x10_flags.b2 = 0;
}

bool grVenom_802040A4(Ground_GObj* arg)
{
    return false;
}

void grVenom_802040AC(Ground_GObj* arg) {}

void grVenom_802040B0(Ground_GObj* arg) {}

enum_t Stage_80225194(void);

void fn_802040B4(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    if (Stage_80225194() == 0xE4) {
        gp->u.venom.xC8 = 1;
    }
}

/// grVenom_802040F0

void grVenom_802040F0(Ground_GObj* gobj)
{
    Vec3 pos1;
    Vec3 pos2;
    HSD_JObj* temp;
    Ground* new_var;
    Ground* gp = GET_GROUND(gobj);

    Ground_801C2ED0(gobj->hsd_obj, gp->map_id);
    grAnime_801C7FF8(gobj, 0, 7, 0, 0.0F, 1.0F);
    grAnime_801C8098(gobj, 0, 7, 1, 0.0F, 1.0F);
    grAnime_801C7FF8(gobj, 0xB, 7, 2, 0.0F, 1.0F);
    grAnime_801C7FF8(gobj, 0xD, 7, 2, 0.0F, 1.0F);
    grAnime_801C7FF8(gobj, 0xF, 7, 2, 0.0F, 1.0F);
    new_var = gp;
    grAnime_801C7FF8(gobj, 4, 7, 3, 0.0F, 1.0F);
    grAnime_801C7FF8(gobj, 7, 7, 3, 0.0F, 1.0F);
    Ground_801C10B8(gobj, (HSD_GObjEvent) fn_802040B4);
    gp->u.venom.xC8 = -1;
    gp->u.venom.upper_jobj = Ground_801C3FA4(gobj, 2);
    gp->u.venom.lower_jobj = Ground_801C3FA4(gobj, 3);
    lb_8000B1CC(gp->u.venom.upper_jobj, NULL, &pos1);
    lb_8000B1CC(gp->u.venom.lower_jobj, NULL, &pos2);
    if (pos2.y > pos1.y) {
        temp = gp->u.venom.upper_jobj;
        gp->u.venom.upper_jobj = new_var->u.venom.lower_jobj;
        gp->u.venom.lower_jobj = temp;
    }
    gp->x10_flags.b5 = 1;
}

bool grVenom_8020427C(Ground_GObj* arg)
{
    return false;
}

void grVenom_80204284(Ground_GObj* gobj)
{
    Ground* gp;
    Ground* tmp_gp;
    HSD_JObj* src_jobj;
    HSD_JObj* dst_jobj;
    u32 pad2;
    Ground_GObj* other_gobj;
    Vec3 pos;
    s32 timer;
    u32 pad;

    tmp_gp = GET_GROUND(gobj);
    gp = tmp_gp;
    src_jobj = GET_JOBJ(gobj);
    dst_jobj = gp->u.venom.target_gobj->hsd_obj;

    HSD_JObjGetTranslation(src_jobj, &pos);
    HSD_JObjSetTranslate(dst_jobj, &pos);

    Ground_801C39C0();
    Ground_801C3BB4();

    timer = gp->u.venom.xC8;
    if (timer > 0) {
        gp->u.venom.xC8 = timer + 1;
        if (gp->u.venom.xC8 >= 0x3C) {
            if (gp->u.venom.xC8 == 0x3C) {
                ifStatus_802F6898();
                un_802FF570();
                other_gobj = grVenom_80203EAC(1);
                if (other_gobj != NULL) {
                    Ground* other_gp = GET_GROUND(other_gobj);
                    grCorneria_801E25C4(
                        other_gobj,
                        (struct grSmashTaunt_GroundVars*) &other_gp->u.venom
                            .xC4,
                        4, 6, 0x6B6CC);
                }
            } else {
                ifStatus_802F6898();
                un_802FF570();
                if (Ground_801C2BA4(1) == NULL) {
                    ifStatus_802F68F0();
                    un_802FF620();
                    gp->u.venom.xC8 = -1;
                }
            }
        }
    }

    lb_800115F4();
    grVenom_8020362C();
    Ground_801C2FE0(gobj);
}

void grVenom_80204424(Ground_GObj* arg) {}

void grVenom_80204428(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    PAD_STACK(8);

    gp->u.venom2.xC4 = Ground_801C3FA4(gobj, 4);
    gp->u.venom2.xC8 = Ground_801C3FA4(gobj, 0xE);
    gp->u.venom2.xCC = Ground_801C3FA4(gobj, 0x10);
    gp->u.venom2.xD0 = Ground_801C3FA4(gobj, 0x11);
    gp->u.venom2.xD4 = Ground_801C3FA4(gobj, 0x12);
    gp->u.venom2.xD8 = Ground_801C3FA4(gobj, 0x13);
    gp->u.venom2.xDC = Ground_801C3FA4(gobj, 0x15);

    gp->u.venom2.xE0_state.b0 = 0;
    gp->u.venom2.xE0_state.b1 = 0;
    gp->u.venom2.xE0_state.b2 = 0;
    gp->u.venom2.xE0_state.b3 = 0;
    gp->u.venom2.xE0_state.b4 = 0;
    gp->u.venom2.xE0_state.b5 = 0;
    gp->u.venom2.xE0_state.b6 = 0;

    gp->u.venom.xE4 = 0.0F;

    Ground_801C5440(gp, 0, 0x6B6C3);
    mpLib_80057BC0(2);
}

bool grVenom_80204544(Ground_GObj* arg)
{
    return false;
}

void grVenom_8020454C(Ground_GObj* gobj)
{
    PAD_STACK(4);
    {
        Vec3 position;
        bool visible;
        Ground* gp;
        int i = 0;
        Ground* gp_save = (gp = gobj->user_data);
        float lo = 1000.0F;
        float hi = -60000.0F;

        do {
            if (gp->u.venom2.xC4 != NULL) {
                lb_8000B1CC(gp->u.venom2.xC4, NULL, &position);
                visible = true;
                if (!(position.z < lo) && !(position.z > hi)) {
                    visible = false;
                }
                if (HSD_JObjGetFlags(gp->u.venom2.xC4) & JOBJ_HIDDEN) {
                    if (visible) {
                        HSD_JObjClearFlagsAll(gp->u.venom2.xC4, JOBJ_HIDDEN);
                    }
                } else if (!visible) {
                    HSD_JObjSetFlagsAll(gp->u.venom2.xC4, JOBJ_HIDDEN);
                }
            }
            i++;
            gp = (Ground*) (&gp->gobj);
        } while (i < 7);
        gp = gp_save;

        if (grAnime_801C84A4(gobj, 0, 7)) {
            Ground_GObj* lgobj = Ground_801C498C();
            if (lgobj != NULL) {
                HSD_LObj* lobj;
                if ((lobj = lgobj->hsd_obj) != NULL) {
                    while (lobj != NULL) {
                        if (lobj->aobj != NULL) {
                            HSD_AObjReqAnim(lobj->aobj, 0.0F);
                        }
                        if (lobj->position != NULL) {
                            HSD_ForeachAnim(lobj->position, WOBJ_TYPE,
                                            ALL_TYPE_MASK, HSD_AObjReqAnim,
                                            AOBJ_ARG_AF, 0.0);
                        }
                        if (lobj->interest != NULL) {
                            HSD_ForeachAnim(lobj->interest, WOBJ_TYPE,
                                            ALL_TYPE_MASK, HSD_AObjReqAnim,
                                            AOBJ_ARG_AF, 0.0);
                        }
                        lobj = HSD_LObjGetNext(lobj);
                    }
                }
            }
        }

        {
            HSD_AObj* a = grAnime_801C8318(gobj, 0, 7);
            if (a != NULL) {
                float frame = HSD_AObjGetCurrFrame(a);
                if ((gp->u.venom.xE4 < 1033.0F && 1033.0F <= frame) ||
                    (gp->u.venom.xE4 < 1086.0F && 1086.0F <= frame) ||
                    (gp->u.venom.xE4 < 1185.0F && 1185.0F <= frame) ||
                    (gp->u.venom.xE4 < 1238.0F && 1238.0F <= frame))
                {
                    Ground_801C53EC(0x6B6C5);
                }
                if ((gp->u.venom.xE4 < 1063.0F && 1063.0F <= frame) ||
                    (gp->u.venom.xE4 < 1116.0F && 1116.0F <= frame) ||
                    (gp->u.venom.xE4 < 1215.0F && 1215.0F <= frame) ||
                    (gp->u.venom.xE4 < 1268.0F && 1268.0F <= frame))
                {
                    Ground_801C53EC(0x6B6C6);
                }
                if ((gp->u.venom.xE4 < 2460.0F && 2460.0F <= frame) ||
                    (gp->u.venom.xE4 < 6440.0F && 6440.0F <= frame) ||
                    (gp->u.venom.xE4 < 9330.0F && 9330.0F <= frame))
                {
                    gp->u.venom2.xE0_state.b6 = true;
                }
                if ((gp->u.venom.xE4 < 2460.0F && 2460.0F <= frame) ||
                    (gp->u.venom.xE4 < 2747.0F && 2747.0F <= frame) ||
                    (gp->u.venom.xE4 < 3030.0F && 3030.0F <= frame) ||
                    (gp->u.venom.xE4 < 3393.0F && 3393.0F <= frame) ||
                    (gp->u.venom.xE4 < 3727.0F && 3727.0F <= frame) ||
                    (gp->u.venom.xE4 < 6440.0F && 6440.0F <= frame) ||
                    (gp->u.venom.xE4 < 6880.0F && 6880.0F <= frame) ||
                    (gp->u.venom.xE4 < 9330.0F && 9330.0F <= frame) ||
                    (gp->u.venom.xE4 < 9600.0F && 9600.0F <= frame) ||
                    (gp->u.venom.xE4 < 9835.0F && 9835.0F <= frame))
                {
                    Ground_801C53EC(0x6B6C7);
                }
                if ((gp->u.venom.xE4 < 4070.0F && 4070.0F <= frame) ||
                    (gp->u.venom.xE4 < 7220.0F && 7220.0F <= frame) ||
                    (gp->u.venom.xE4 > frame))
                {
                    gp->u.venom2.xE0_state.b6 = false;
                }
                if (gp->u.venom.xE4 < 4200 && 4200 <= frame) {
                    gp->u.venom2.xE0_state.b0 = true;
                }
                if (gp->u.venom.xE4 < 3800 && 3800 <= frame) {
                    gp->u.venom2.xE0_state.b1 = true;
                }
                if (gp->u.venom.xE4 < 4400 && 4400 <= frame) {
                    Ground_801C5440(gp, 0, 0x6B6C4);
                    gp->u.venom2.xE0_state.b2 = true;
                    mpJointListAdd(2);
                }
                if (gp->u.venom.xE4 < 6100 && 6100 <= frame) {
                    Ground_801C5440(gp, 0, 0x6B6C3);
                    gp->u.venom2.xE0_state.b0 = false;
                    gp->u.venom2.xE0_state.b1 = false;
                    gp->u.venom2.xE0_state.b2 = false;
                    mpLib_80057BC0(2);
                }
                if (gp->u.venom.xE4 < 7210 && 7210 <= frame) {
                    gp->u.venom2.xE0_state.b3 = true;
                }
                if (gp->u.venom.xE4 < 6810 && 6810 <= frame) {
                    gp->u.venom2.xE0_state.b4 = true;
                }
                if (gp->u.venom.xE4 < 7410 && 7410 <= frame) {
                    gp->u.venom2.xE0_state.b5 = true;
                }
                if (gp->u.venom.xE4 < 9200 && 9200 <= frame) {
                    gp->u.venom2.xE0_state.b3 = false;
                    gp->u.venom2.xE0_state.b4 = false;
                    gp->u.venom2.xE0_state.b5 = false;
                }
                gp->u.venom.xE4 = frame;
            }
        }

        lbAudioAx_80024D78(!gp->u.venom2.xE0_state.b2 ? 1 : 2);
        grVenom_80204B88(gobj);
    }
}

void grVenom_80204B84(Ground_GObj* arg) {}

/// grVenom_80204B88
/// Updates Venom stage lighting colors based on environment state.

static const GXColor grVe_804DB7D8 = { 0, 0, 0, 0 };
static const GXColor grVe_804DB7DC = { 190, 10, 0, 0 };
static const GXColor grVe_804DB7E0 = { 110, 60, 25, 0 };
static const GXColor grVe_804DB7E4 = { 110, 90, 0, 0 };

void grVenom_80204B88(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    u8 env_flags;
    GXColor color_set1;
    GXColor color_set2;
    GXColor color_neutral1;
    GXColor color_neutral2;

    env_flags = *(u8*) &gp->u.venom2.xE0_state.xE0_state_pad;

    if ((env_flags >> 5) & 1) {
        if (gp->u.venom2.xE0_state.xE0_state_pad.state != 1) {
            color_set1 = grVe_804DB7D8;
            Ground_801C052C(&color_set1);
            Ground_801C05D4(&color_set1);
            Ground_801C0544(&color_set1);
            Ground_801C058C(&color_set1);
            Ground_801C05EC(&color_set1);
            Ground_801C05A4(&color_set1);
            Ground_801C055C(&color_set1);
            Ground_801C05BC(&color_set1);
            Ground_801C0574(&color_set1);
            gp->u.venom2.xE0_state.xE0_state_pad.state = 1;
        }
    } else if ((env_flags >> 1) & 1) {
        if (gp->u.venom2.xE0_state.xE0_state_pad.state != 2) {
            color_set2 = grVe_804DB7DC;
            Ground_801C05BC(&color_set2);
            gp->u.venom2.xE0_state.xE0_state_pad.state = 2;
        }
    } else {
        if (gp->u.venom2.xE0_state.xE0_state_pad.state != 0) {
            color_neutral1 = grVe_804DB7E0;
            color_neutral2 = grVe_804DB7E4;
            Ground_801C052C(&color_neutral1);
            Ground_801C05D4(&color_neutral1);
            Ground_801C0544(&color_neutral1);
            Ground_801C058C(&color_neutral1);
            Ground_801C05EC(&color_neutral1);
            Ground_801C05A4(&color_neutral1);
            Ground_801C055C(&color_neutral2);
            Ground_801C05BC(&color_neutral2);
            Ground_801C0574(&color_neutral2);
            gp->u.venom2.xE0_state.xE0_state_pad.state = 0;
        }
    }
}

void grVenom_80204CE0(Ground_GObj* arg) {}

bool grVenom_80204CE4(Ground_GObj* arg)
{
    return false;
}

void grVenom_80204CEC(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    Ground_UpdateStarFoxSequence(gobj, gp, 1, grVenom_80203EAC);
}

void grVenom_80204DB0(Ground_GObj* gobj)
{
    ifStatus_802F68F0();
    un_802FF620();
}

/// grVenom_80204DD4
/// Unit: main/melee/gr/grvenom

void grVenom_80204DD4(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    HSD_JObj* jobj = gobj->hsd_obj;
    PAD_STACK(8);

    Ground_801C2ED0(jobj, gp->map_id);
    HSD_JObjSetScaleX(jobj, 1.0F);
    HSD_JObjSetScaleY(jobj, 1.0F);
}

bool grVenom_80204EF4(Ground_GObj* arg)
{
    return false;
}

void grVenom_80204EFC(Ground_GObj* arg)
{
    Ground_801C2FE0(arg);
}

void grVenom_80204F1C(Ground_GObj* arg) {}

void grVenom_80204F20(Ground_GObj* arg0)
{
    s32* base = (s32*) &grVe_803E5348;
    Ground* gp = arg0->user_data;
    HSD_JObj* jobj = arg0->hsd_obj;
    HSD_GObj* other;
    f32 scale;
    s32 state;
    PAD_STACK(0x10);

    grVe_803E5348.arwing
        .arwing_gobj[gp->u.starfox_arwing.slot = grVe_CurrentArwingSlot] =
        arg0;

    other = grVenom_80203EAC(base[base[gp->u.starfox_arwing.slot + 14] + 170]);
    if (other != NULL) {
        Ground* other_gp = other->user_data;
        other_gp->x10_flags.b2 = 0;
        other_gp = other->user_data;
        if (other_gp != NULL) {
            other_gp->u.starfox_arwing.slot = gp->u.starfox_arwing.slot;
        } else {
            OSReport("arwin:user data error\n");
        }
    }

    scale = Ground_801C0498();
    state = base[gp->u.starfox_arwing.slot + 11];
    if (state >= 8) {
        goto check_scale_uniform;
    }
    if (state >= 1) {
        goto scale_nonuniform;
    }
    goto done_scale;

check_scale_uniform:
    if (state >= 12) {
        goto done_scale;
    }
    goto scale_uniform;

scale_nonuniform:
    HSD_JObjSetScaleX(jobj, scale);
    HSD_JObjSetScaleY(jobj, scale);
    HSD_JObjSetScaleZ(jobj, scale * grVe_StageParams->arwing_scale);
    goto done_scale;

scale_uniform:
    HSD_JObjSetScaleX(jobj, scale);
    HSD_JObjSetScaleY(jobj, scale);
    HSD_JObjSetScaleZ(jobj, scale);

done_scale:

    gp->u.starfox_arwing.animation_pending = true;
    gp->u.starfox_arwing.sound_state = 0;
}

bool grVenom_802052D8(Ground_GObj* arg)
{
    return false;
}

/// @todo VenomSpawnData struct should be defined in gr/types.h or grvenom.h
typedef struct {
    u8 pad[0x218];
    f32 x;
    f32 y;
    f32 z;
} VenomSpawnData;

void grVenom_GetArwingPosition(Ground_GObj* gobj, Vec3* pos)
{
    u8* new_var2;
    Vec3 jobj_pos;
    s32* spawn_table = (s32*) &grVe_803E5348;
    Ground* gp;
    HSD_JObj* jobj;
    s32* new_var;
    s32* new_var4;
    u32 spawn_idx;
    struct grStarFoxArwing_GroundVars* new_var3;
    s32 data_idx;
    VenomSpawnData* spawn_data;

    if (gobj != NULL) {
        gp = gobj->user_data;
        Ground_801C2BA4(5);
        jobj = Ground_801C3FA4(gobj, 5);
        lb_8000B1CC(jobj, NULL, &jobj_pos);
        new_var = spawn_table;
        new_var4 = spawn_table;
        new_var2 = (u8*) new_var4;
        new_var3 = &gp->u.starfox_arwing;
        spawn_idx = new_var3->slot;
        data_idx = new_var[spawn_idx + 11];
        spawn_data = (VenomSpawnData*) (new_var2 + data_idx * 12);
        pos->x = jobj_pos.x + spawn_data->x;
        pos->y = jobj_pos.y + spawn_data->y;
        pos->z = jobj_pos.z + spawn_data->z;
    } else {
        pos->x = pos->y = pos->z = 0.0F;
    }
}

static inline void grVe_UpdateArwingSounds(Ground* gp, Vec3* pos)
{
    switch (gp->u.starfox_arwing.sound_state) {
    case 0:
        if (!grVenom_IsOutsideBlastZone(pos)) {
            lbAudioAx_800237A8(0x6B6C0, 0x7F, 0x40);
            gp->u.starfox_arwing.sound_state = 1;
        }
        break;
    case 1:
        if (!grVenom_IsOutsideBlastZoneWithMargin(pos)) {
            gp->u.starfox_arwing.sound_state = 2;
        }
        break;
    case 2:
        if (grVenom_IsOutsideBlastZoneWithMargin(pos) == 1) {
            lbAudioAx_800237A8(0x6B6C2, 0x7F, 0x40);
            gp->u.starfox_arwing.sound_state = 3;
        }
        break;
    }
}

void grVenom_802053B0(Ground_GObj* gobj)
{
    Vec3 sp28;
    Vec3 sp1C;
    s32* ptr;
    Ground* gp2;
    s32 state;
    HSD_JObj* jobj;
    s32* base;
    Ground* gp;
    PAD_STACK(0x10);

    gp = gobj->user_data;
    base = (s32*) &grVe_803E5348;
    jobj = gobj->hsd_obj;
    ptr = base + gp->u.starfox_arwing.slot;

    if (grVe_803E5348.arwing.arwing_gobj[gp->u.starfox_arwing.slot] == gobj) {
        if (gp->u.starfox_arwing.animation_pending == true) {
            gp->u.starfox_arwing.animation_pending = false;
            grAnime_801C8138(
                gobj, gp->map_id,
                base[base[gp->u.starfox_arwing.slot + 11] + 0x7A]);
            return;
        }

        state = ptr[11];
        if (state >= 8) {
            goto check_far;
        }
        if (state >= 1) {
            goto near_type;
        }
        goto type_done;

    check_far:
        if (state >= 12) {
            goto type_done;
        }
        goto far_type;

    near_type:
        grVenom_GetArwingPosition(gobj, &sp28);
        grVe_UpdateArwingSounds(gp, &sp28);
        goto type_done;

    far_type:
        HSD_JObjSetRotationY(jobj, 0.0F);

        gp2 = gobj->user_data;
        grVenom_GetArwingPosition(gobj, &sp1C);
        grVe_UpdateArwingSounds(gp2, &sp1C);

    type_done:
        if (grAnime_801C83D0(gobj, 0, 7)) {
            base[gp->u.starfox_arwing.slot + 8] = 0;
            Ground_801C4A08(gobj);
        }
    } else {
        Ground_801C4A08(gobj);
    }
}

void grVenom_802056AC(Ground_GObj* arg) {}

/// Animation index for each randomly selected maneuver and formation variant.
static int grVe_ArwingManeuverAnims[5][2] = {
    { -1, -1 }, { 1, 0 }, { 2, 2 }, { 4, 4 }, { 5, 5 },
};

static int grVe_ArwingLinkedArticleIds[5] = { 0x0A, 0x0A, 0x0B, 0x0C, 0x0D };

static int grVe_ArwingCollisionJointIds[5] = { 4, 4, 4, 4, 3 };

void grVenom_802056B0(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    HSD_JObj* jobj = gobj->hsd_obj;
    int* joint_idx;
    int joint_offset;
    int* joints;
    int joint_id;

    Ground_801C2ED0(jobj, gp->map_id);
    gp->u.starfox_arwing.slot = grVe_CurrentArwingSlot;
    joint_idx = grVe_ArwingGroups;
    joints = grVe_ArwingCollisionJointIds;
    gp->u.starfox_arwing.xD0 = 0;
    gp->u.starfox_arwing.roll_angle = 0.0F;
    gp->u.starfox_arwing.position.z = 0.0F;
    gp->u.starfox_arwing.position.y = 0.0F;
    gp->u.starfox_arwing.position.x = 0.0F;
    joint_offset = joint_idx[gp->u.starfox_arwing.slot];
    joint_id = joints[joint_offset];
    mpJointListAdd(joint_id);

    Ground_801C2ED0(jobj, gp->map_id);
}

bool grVenom_80205750(Ground_GObj* arg)
{
    return false;
}

void grVenom_80205758(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);

    if (grVe_803E5348.arwing.arwing_gobj[gp->u.starfox_arwing.slot] != NULL) {
        Ground_UpdateStarFoxArwingVisibility(gp, jobj, 50.0F);
        {
            f32 scale = Ground_801C0498();
            {
                f32 s = scale * grVe_StageParams->arwing_scale;
                HSD_JObjSetScaleX(jobj, s);
            }
            {
                f32 s = scale * grVe_StageParams->arwing_scale;
                HSD_JObjSetScaleY(jobj, s);
            }
            {
                f32 s = scale * grVe_StageParams->arwing_scale;
                HSD_JObjSetScaleZ(jobj, s);
            }
        }
        Ground_801C2FE0(gobj);
    } else {
        mpLib_80057BC0(grVe_ArwingCollisionJointIds
                           [grVe_ArwingGroups[gp->u.starfox_arwing.slot]]);
        Ground_801C4A08(gobj);
    }
}

/// The trailing zero word is present in the reference object.
static int grVe_ArwingModelJointIds[6] = { 1, 1, 1, 1, 1, 0 };

void grVenom_80205AD0(Ground_GObj* arg) {}

void grVenom_80205AD4(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    HSD_JObj* jobj = GET_JOBJ(gobj);
    f32 scale;

    scale = Ground_801C0498();
    gp->u.starfox.arwing_slot = grVe_CurrentArwingSlot;
    Ground_ClearStarFoxArwingGObjs(gp);
    Ground_AnimateStarFoxArwingWithBackground(gobj);

    switch (grVe_803E5348.arwing.arwing_type[gp->u.starfox.arwing_slot]) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7: {
        HSD_GObj* other = grVenom_80203EAC(
            grVe_ArwingLinkedArticleIds
                [grVe_ArwingGroups[gp->u.starfox.arwing_slot]]);
        Ground_LinkStarFoxArwing(gp, other);
        break;
    }
    case 8:
    case 9:
    case 10:
    case 11:
        Ground_AttachStarFoxArwingModel(
            gobj, gp,
            grVe_803E5348.arwing.arwing_gobj[gp->u.starfox.arwing_slot], 5);
        break;
    default:
        Ground_DisableStarFoxArwingGObjs(gp);
        break;
    }
    HSD_JObjSetScaleX(jobj, scale * grVe_StageParams->arwing_scale);
    HSD_JObjSetScaleY(jobj, scale * grVe_StageParams->arwing_scale);
    HSD_JObjSetScaleZ(jobj, scale * grVe_StageParams->arwing_scale);
    Ground_ResetStarFoxArwingState(gp);
    gp->u.starfox.maneuver_cooldown =
        (s32) grVe_StageParams->maneuver_cooldown;
    gp->u.starfox.fire_laser = false;
    gp->u.starfox.laser_joint = HSD_Randi(2);
}

bool grVenom_80205DF0(Ground_GObj* arg)
{
    return false;
}

s32 grVenom_IsOutsideBlastZone(Vec3* pos)
{
    return Stage_IsOutsideBlastZone(pos);
}

float Stage_GetBlastZoneBottomOffset(void);
float Stage_GetBlastZoneLeftOffset(void);
float Stage_GetBlastZoneRightOffset(void);
float Stage_GetBlastZoneTopOffset(void);

s32 grVenom_IsOutsideBlastZoneWithMargin(Vec3* pos)
{
    return Stage_IsOutsideBlastZoneWithMargin(pos, 20.0F);
}

static const Vec3 grVe_803B82D0 = { 0.0F, 0.0F, 0.0F };
static const Vec3 grVe_803B82DC = { 0.0F, 0.0F, 0.0F };

typedef struct grVe_AnimData {
    u8 pad0[0x2FC];
    s32 maneuver_anims[5][2];
    u8 pad324[0x358 - 0x324];
    s32 model_joints[5];
} grVe_AnimData;

typedef struct grVe_AnimArg {
    u8 pad0[0x2FC];
    s32 value;
} grVe_AnimArg;

/// Steps the anim-arg row/column words on the stage-data base pointer and
/// reads through the struct field so the +0x2FC displacement lands on the
/// load itself. Evidence: the reference object computes the address with
/// two adds on the base register and loads `lwz rD, 0x2FC(rA)`; direct 2D
/// array indexing re-associates to an `lwzx` indexed load instead.
static inline s32 grVe_GetArwingManeuverAnim(s32 formation_variant, Ground* gp,
                                             grVe_AnimData* anim_data)
{
    anim_data =
        (grVe_AnimData*) ((s32*) anim_data + gp->u.starfox.maneuver * 2);
    anim_data = (grVe_AnimData*) ((s32*) anim_data + formation_variant);
    return ((volatile grVe_AnimArg*) anim_data)->value;
}

void grVenom_80205F30(Ground_GObj* gobj)
{
    u64 padA8;
    Vec3 sp94;
    Vec3 sp88;
    u8 pad70[0x18];
    Vec3 sp64;
    u8 pad5C[8];
    Vec3 sp50;
    Ground* gp;
    HSD_JObj* jobj;
    Ground* other_gp;
    HSD_GObj* other;
    HSD_JObj* tmp_jobj;
    s32* base;
    s32* entry;
    s32 state;
    s32 formation_variant;
    s32 slot;
    s32 retries;
    s32 type_idx;
    HSD_JObj* helper;

    base = (s32*) &grVe_803E5348;
    gp = gobj->user_data;
    jobj = gobj->hsd_obj;
    sp94 = grVe_803B82D0;
    sp88 = grVe_803B82DC;
    PAD_STACK(0x18);

    if (grVe_ArwingUpdateDisabled) {
        return;
    }

    entry = base + gp->u.starfox.arwing_slot;
    if (grVe_803E5348.arwing.arwing_gobj[gp->u.starfox.arwing_slot] != NULL) {
        if (entry[14] == 4) {
            tmp_jobj = Ground_801C3FA4(gobj, 1);
            HSD_JObjSetRotationZ(tmp_jobj, 0.0F);
        }

        state = base[gp->u.starfox.arwing_slot + 11];
        switch (state) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            HSD_JObjSetRotationY(jobj, 0.0F);

            {
                s32 maneuver = gp->u.starfox.maneuver;
                if (maneuver == ARWING_MANEUVER_NONE) {
                    goto venom_80205F30_anim_zero;
                }
                if (maneuver < 0) {
                    goto venom_80205F30_anim_done;
                }
                if (maneuver >= (s32) ARRAY_SIZE(grVe_ArwingManeuverAnims)) {
                    goto venom_80205F30_anim_done;
                }
                goto venom_80205F30_check_anim;
            venom_80205F30_anim_zero: {
                if (gp->u.starfox.maneuver_cooldown <= 0) {
                    gp->u.starfox.maneuver =
                        HSD_Randi(ARRAY_SIZE(grVe_ArwingManeuverAnims) - 1) +
                        ARWING_MANEUVER_FIRST;
                    formation_variant = -1;
                    switch (base[GET_GROUND(gobj)->u.starfox.arwing_slot + 14])
                    {
                    case 0:
                        break;
                    case 1:
                    case 2:
                    case 3:
                        formation_variant = 0;
                        break;
                    case 4:
                        formation_variant = 1;
                        break;
                    }
                    {
                        grVe_AnimData* anim_data = (grVe_AnimData*) base;
                        s32 idx0 = base[gp->u.starfox.arwing_slot + 14];
                        s32 maneuver_anim = grVe_GetArwingManeuverAnim(
                            formation_variant, gp, anim_data);
                        s32 model_joint = anim_data->model_joints[idx0];
                        grAnime_801C8098(gobj, model_joint, 7, maneuver_anim,
                                         0.0F, 1.0F);
                    }
                } else {
                    s32 idx0 = base[gp->u.starfox.arwing_slot + 14];
                    s32 model_joint = grVe_ArwingModelJointIds[idx0];
                    tmp_jobj = Ground_801C3FA4(gobj, model_joint);
                    HSD_JObjSetRotationZ(tmp_jobj, 0.0F);
                }
                gp->u.starfox.maneuver_cooldown =
                    gp->u.starfox.maneuver_cooldown - 1;
            }
                goto venom_80205F30_anim_done;
            venom_80205F30_check_anim:
                if (grAnime_801C83D0(gobj, 0, 7)) {
                    gp->u.starfox.maneuver = ARWING_MANEUVER_NONE;
                    gp->u.starfox.maneuver_cooldown =
                        (s32) grVe_StageParams->maneuver_cooldown;
                }
            venom_80205F30_anim_done:;
            }

            if ((other = (HSD_GObj*) base[gp->u.starfox.arwing_slot + 8]) !=
                NULL)
            {
                other_gp = other->user_data;
                Ground_801C2BA4(5);
                lb_8000B1CC(Ground_801C3FA4(other, 5), NULL, &sp64);
                {
                    VenomSpawnData* spawn_data =
                        (VenomSpawnData*) (base +
                                           base[other_gp->u.starfox_arwing
                                                    .slot +
                                                11] *
                                               3);
                    sp94.x = sp64.x + spawn_data->x;
                    sp94.y = sp64.y + spawn_data->y;
                    sp94.z = sp64.z + spawn_data->z;
                }
            } else {
                sp94.x = sp94.y = sp94.z = 0.0F;
            }

            HSD_JObjSetTranslate(jobj, &sp94);

            {
                s32 idx0 = base[gp->u.starfox.arwing_slot + 14];
                s32 model_joint = grVe_ArwingModelJointIds[idx0];
                lb_8000B1CC(Ground_801C3FA4(gobj, model_joint), NULL, &sp94);
            }
            if (gp->u.starfox.linked_gobj != NULL) {
                Ground* sub = gp->u.starfox.linked_gobj->user_data;
                if (sub != NULL) {
                    sub->u.starfox_arwing.position = sp94;
                }
            }

            {
                f32 rot_z;
                s32 idx0 = base[gp->u.starfox.arwing_slot + 14];
                s32 model_joint = grVe_ArwingModelJointIds[idx0];
                helper = Ground_801C3FA4(gobj, model_joint);
                rot_z = HSD_JObjGetRotationZ(helper);
                if (gp->u.starfox.linked_gobj != NULL) {
                    Ground* sub = gp->u.starfox.linked_gobj->user_data;
                    if (sub != NULL) {
                        sub->u.starfox_arwing.roll_angle = rot_z;
                    }
                }
            }
            break;
        case 8:
        case 9:
        case 10:
        case 11:
            if (!(gp->u.starfox.frame_count & 7) && HSD_Randi(8) == 0) {
                gp->u.starfox.fire_laser = false;
                type_idx = base[gp->u.starfox.arwing_slot + 11];
                switch (type_idx) {
                case 8:
                    if (gp->u.starfox.frame_count > 0x3C &&
                        gp->u.starfox.frame_count < 0xE6)
                    {
                        gp->u.starfox.fire_laser = true;
                    }
                    break;
                case 9:
                    if (gp->u.starfox.frame_count > 0x32 &&
                        gp->u.starfox.frame_count < 0xE6)
                    {
                        gp->u.starfox.fire_laser = true;
                    }
                    break;
                case 10:
                    if (gp->u.starfox.frame_count > 0x5A &&
                        gp->u.starfox.frame_count < 0x104)
                    {
                        gp->u.starfox.fire_laser = true;
                    }
                    break;
                case 11:
                    if (gp->u.starfox.frame_count > 0x46 &&
                        gp->u.starfox.frame_count < 0xF0)
                    {
                        gp->u.starfox.fire_laser = true;
                    }
                    break;
                }
            } else {
                gp->u.starfox.fire_laser = false;
            }

            {
                HSD_GObj* far_other;
                Ground* far_other_gp;

                if ((far_other =
                         (HSD_GObj*) base[gp->u.starfox.arwing_slot + 8]) !=
                    NULL)
                {
                    far_other_gp = far_other->user_data;
                    Ground_801C2BA4(5);
                    lb_8000B1CC(Ground_801C3FA4(far_other, 5), NULL, &sp50);
                    {
                        VenomSpawnData* spawn_data =
                            (VenomSpawnData*) (base +
                                               base[far_other_gp->u
                                                        .starfox_arwing.slot +
                                                    11] *
                                                   3);
                        sp94.x = sp50.x + spawn_data->x;
                        sp94.y = sp50.y + spawn_data->y;
                        sp94.z = sp50.z + spawn_data->z;
                    }
                } else {
                    sp94.x = sp94.y = sp94.z = 0.0F;
                }
            }

            if (-100.0F > sp94.z && sp94.z > -2000.0F &&
                gp->u.starfox.fire_laser)
            {
                gp->u.starfox.fire_laser = false;
                slot = HSD_Randi(4);
                retries = 0;
                do {
                    slot = (slot + retries) & 3;
                    if (Player_GetPlayerSlotType(slot) != 3) {
                        break;
                    }
                    retries++;
                } while (retries < 4);

                Player_LoadPlayerCoords(slot, &sp88);
                if ((sp88.x > 0.0F && sp94.x > 0.0F) ||
                    (sp88.x < 0.0F && sp94.x < 0.0F))
                {
                    sp88.y += 5.0F;
                    lbAudioAx_800237A8(0x6B6C9, 0x7F, 0x40);
                    formation_variant = -1;
                    switch (base[GET_GROUND(gobj)->u.starfox.arwing_slot + 14])
                    {
                    case 0:
                        break;
                    case 1:
                    case 2:
                    case 3:
                        formation_variant = 0;
                        break;
                    case 4:
                        formation_variant = 1;
                        break;
                    }
                    if (formation_variant == 1) {
                        it_802E7654(gobj, Ground_801C3FA4(gobj, 7), &sp88, 3,
                                    0, grVe_StageParams->arwing_scale);
                    } else {
                        if (gp->u.starfox.laser_joint != 0) {
                            it_802E7654(gobj, Ground_801C3FA4(gobj, 5), &sp88,
                                        1, 0, grVe_StageParams->arwing_scale);
                        } else {
                            it_802E7654(gobj, Ground_801C3FA4(gobj, 6), &sp88,
                                        1, 0, grVe_StageParams->arwing_scale);
                        }
                        gp->u.starfox.laser_joint =
                            (gp->u.starfox.laser_joint + 1) & 1;
                    }
                    grMaterial_801C9604(gobj,
                                        grVe_StageParams->laser_effect_id, 0);
                }
            }
            break;
        }

        gp->u.starfox.frame_count = gp->u.starfox.frame_count + 1;
    } else {
        if (gp->u.starfox.article_gobjs[0] != NULL) {
            Ground_801C4A08(gp->u.starfox.article_gobjs[0]);
        }
        if (gp->u.starfox.article_gobjs[1] != NULL) {
            Ground_801C4A08(gp->u.starfox.article_gobjs[1]);
        }
        if (gp->u.starfox.article_gobjs[2] != NULL) {
            Ground_801C4A08(gp->u.starfox.article_gobjs[2]);
        }
        if (gp->u.starfox.article_gobjs[3] != NULL) {
            Ground_801C4A08(gp->u.starfox.article_gobjs[3]);
        }
        Ground_801C4A08(gobj);
    }
}

void grVenom_80206870(Ground_GObj* arg) {}

void grVenom_80206874(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    HSD_JObj* jobj = gobj->hsd_obj;
    f32 scale;

    scale = Ground_801C0498();
    gp->u.starfox.arwing_slot = grVe_CurrentArwingSlot;
    Ground_ClearStarFoxArwingGObjs(gp);
    Ground_AnimateStarFoxArwing(gobj);

    switch (grVe_803E5348.arwing.arwing_type[gp->u.starfox.arwing_slot]) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7: {
        HSD_GObj* other = grVenom_80203EAC(
            grVe_ArwingLinkedArticleIds
                [grVe_ArwingGroups[gp->u.starfox.arwing_slot]]);
        Ground_LinkStarFoxArwing(gp, other);
        break;
    }
    case 8:
    case 9:
    case 10:
    case 11:
        Ground_AttachStarFoxArwingModel(
            gobj, gp,
            grVe_803E5348.arwing.arwing_gobj[gp->u.starfox.arwing_slot], 5);
        break;
    default:
        Ground_DisableStarFoxArwingGObjs(gp);
        break;
    }

    HSD_JObjSetScaleX(jobj, scale * grVe_StageParams->arwing_scale);
    HSD_JObjSetScaleY(jobj, scale * grVe_StageParams->arwing_scale);
    HSD_JObjSetScaleZ(jobj, scale * grVe_StageParams->arwing_scale);

    Ground_ResetStarFoxArwingState(gp);

    gp->u.starfox.maneuver_cooldown =
        (s32) grVe_StageParams->maneuver_cooldown;
    gp->u.starfox.fire_laser = false;
}

/// #grVenom_80206874

bool grVenom_80206B68(Ground_GObj* arg)
{
    return false;
}

void grVenom_80206B70(Ground_GObj* arg)
{
    grVenom_80205F30(arg);
}

void grVenom_80206B90(Ground_GObj* arg) {}

void grVenom_80206B94(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    smashTaunt_801E2550(gobj, &gp->u.smashtaunt);
}

bool grVenom_80206BBC(Ground_GObj* arg)
{
    return false;
}

void grVenom_80206BC4(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grCorneria_801E277C(gobj, &gp->u.smashtaunt);
}

void grVenom_80206BEC(Ground_GObj* arg) {}

bool grVenom_80206BF0(int arg0)
{
    s32 var_r30;
    Ground_GObj* wgobj;
    Ground* gp;
    PAD_STACK(32);

    if (Ground_801C2BA4(8) != NULL) {
        return 0;
    }
    if (arg0 == 2) {
        var_r30 = HSD_Randi(5) + 8;
    } else if (arg0 == 20) {
        var_r30 = HSD_Randi(5) + 13;
    } else {
        return 0;
    }
    wgobj = grVenom_80203EAC(8);
    HSD_ASSERT(2244, wgobj);
    gp = wgobj->user_data;
    gp->u.venom.xCC = 10;
    gp->u.venom.xC8 = 0;
    gp->u.venom.xC4 = var_r30;
    return 1;
}

void grVenom_80206CB0(s32 arg0)
{
    HSD_GObj* gobj;

    gobj = Ground_801C2BA4(8);
    if (gobj != NULL) {
        if (arg0 != 0) {
            Ground_801C4A08(gobj);
        }
        gobj = Ground_801C2BA4(1);
        if (gobj != NULL) {
            Ground_801C4A08(gobj);
        }
        HSD_SisLib_803A5F50(1);
    }
}

s32 grVenom_80206D10(s32 arg0)
{
    s32 in_range;
    s32 result;
    u32 diff;

    if (stage_info.internal_stage_id == VENOM && arg0 != -1) {
        result = mpJointFromLine(arg0);
        diff = result - 3;
        in_range = 1;
        if (diff > 1U) {
            in_range = 0;
        }
        if (in_range != 0) {
            return 1;
        }
    }
    return 0;
}

DynamicsDesc* grVenom_80206D74(enum_t arg)
{
    return false;
}

bool grVenom_80206D7C(Vec3* pos, int arg1, HSD_JObj* arg2)
{
    Vec3 sp20;
    Vec3 sp14;
    HSD_GObj* gobj;
    Ground* gp;

    lb_8000B1CC(arg2, NULL, &sp20);
    gobj = Ground_801C2BA4(5);
    if (gobj != NULL) {
        gp = gobj->user_data;
        if (gp != NULL && gp->u.venom.lower_jobj == arg2) {
            lb_8000B1CC(gp->u.venom.upper_jobj, NULL, &sp14);
            if (pos->y > sp14.y) {
                return 0;
            }
        }
    }
    if (pos->y > sp20.y) {
        return 1;
    }
    return 0;
}
