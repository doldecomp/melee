#include "gm_1884.h"

#include "gm_unsplit.h"

#include "dolphin/pad.h"
#include "gm/gm_1601.h"
#include "gm/gm_1A36.h"
#include "gm/gm_1A45.h"
#include "gm/types.h"
#include "gr/stage.h"
#include "if/ifall.h"
#include "if/ifstatus.h"

#include "it/forward.h"

#include "it/itspawn.h"
#include "lb/lb_00B0.h"
#include "lb/lb_0195.h"
#include "lb/lbarchive.h"
#include "lb/lbaudio_ax.h"
#include "lb/lblanguage.h"
#include "lb/lbspdisplay.h"
#include "mn/inlines.h"
#include "mn/types.h"
#include "pl/pl_040D.h"
#include "pl/player.h"
#include "sc/types.h"

#include <sysdolphin/baselib/aobj.h>
#include <sysdolphin/baselib/cobj.h>
#include <sysdolphin/baselib/dobj.h>
#include <sysdolphin/baselib/fog.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/mobj.h>
#include <sysdolphin/baselib/sislib.h>
#include <sysdolphin/baselib/tobj.h>
#include <sysdolphin/baselib/wobj.h>
#include <Runtime/runtime.h>

/// @todo .sdata2 order hack
static inline void gm_1884_sdata2_order(void)
{
    (void) 0.016666668f;
    (void) U32_TO_F32;
    (void) 10.0f;
    (void) 1.0f;
    (void) S32_TO_F32;
    (void) 50.0f;
    (void) 12.0f;
    (void) 9.79882812f;
    (void) 150.0f;
    (void) 0.100000001f;
    (void) 167.0f;
    (void) 16.0f;
    (void) 0.699999988f;
    (void) 0.600000024f;
    (void) 0.0f;
}

typedef struct {
    f32 values[6];
} TrainingSpeedArray;

typedef struct {
    TrainingSpeedArray speeds;
    u8 pad[8];
} TrainingSpeedStack;

DynamicModelDesc** lbl_804D662C;
HSD_Archive* lbl_804D6628;

typedef struct TrainingItemEntry {
    s16 item_id;
    s16 text_id;
} TrainingItemEntry;
ASSERT_SIZE(TrainingItemEntry, 4);

static TrainingItemEntry gmTraining_ItemTable[] = {
    { It_Kind_Foods, 21 },    { It_Kind_Tomato, 11 },
    { It_Kind_Heart, 10 },    { It_Kind_L_Gun, 18 },
    { It_Kind_F_Flower, 35 }, { It_Kind_S_Scope, 25 },
    { It_Kind_StarRod, 26 },  { It_Kind_LipStick, 19 },
    { It_Kind_Sword, 14 },    { It_Kind_Bat, 13 },
    { It_Kind_Harisen, 2 },   { It_Kind_Hammer, 38 },
    { It_Kind_G_Shell, 16 },  { It_Kind_R_Shell, 17 },
    { It_Kind_Flipper, 24 },  { It_Kind_Freeze, 20 },
    { It_Kind_Dosei, 9 },     { It_Kind_M_Ball, 27 },
    { It_Kind_BombHei, 8 },   { It_Kind_MSBomb, 22 },
    { It_Kind_Kinoko, 78 },   { It_Kind_DKinoko, 79 },
    { It_Kind_Star, 12 },     { It_Kind_Parasol, 15 },
    { It_Kind_WStar, 76 },    { It_Kind_MetalB, 81 },
    { It_Kind_RabbitC, 77 },  { It_Kind_ScBall, 80 },
    { It_Kind_TaruCann, 5 },  { It_Kind_Spycloak, 82 },
    { It_Kind_None, 23 },
};

TrainingSpeedArray const lbl_803B7C68 = {
    { 2.0f, 1.5f, 1.0f, 0.666f, 0.5f, 0.25f },
};

static inline TrainingItemEntry* TrainingItemTable_Get(void)
{
    return (TrainingItemEntry*) gmTraining_ItemTable;
}

/* 473700 */ static TrainingModeState lbl_80473700;
/* 473814 */ CssSubStruct gm_80473814;

STATIC_ASSERT(sizeof(lbl_80473700) == 0x114);
STATIC_ASSERT(sizeof(gm_80473814) == 0x204);

int gm_80188454(int idx)
{
    gm_1884_sdata2_order();
    return lbl_80473700.char_data[idx];
}

int fn_8018846C(void)
{
    int result;
    int* ptr = (int*) &lbl_80473700;
    int* p;

    result = pl_8004134C(0);
    p = ptr + Player_GetPlayerCharacter(0) + 2;
    if (*p < result) {
        *p = result;
    }
    if (result != 0) {
        ptr[67] = result;
        ptr[68] = 1;
    }
    if (ptr[68] != 0) {
        return ptr[67];
    }
    return result;
}

int fn_801884F8(void)
{
    int result;
    TrainingModeState* state = &lbl_80473700;

    result = pl_80041300(0);
    if (result != 0) {
        state->result_cache[0] = result;
        state->result_cache[1] = 1;
    }
    if (state->result_cache[1] != 0) {
        result = state->result_cache[0];
    }
    return result;
}

void fn_80188550(int arg0)
{
    int current = lbl_80473700.count;
    int to_remove;
    int j;

    if (arg0 != current) {
        if (arg0 > lbl_80473700.count) {
            int i;
            int skip;
            int remaining;

            skip = lbl_80473700.count;
            remaining = arg0 - current;
            i = 0;
            j = 0;

            for (i = 0; i < 4; i++) {
                if (i != 0) {
                    if (skip == 0) {
                        if (i != 0) {
                            lbl_80473700.players[i].slot_type = 1;
                        } else {
                            lbl_80473700.players[i].slot_type = j;
                        }
                        gm_8016EDDC(i, &lbl_80473700.players[i]);
                        if (--remaining == 0) {
                            break;
                        }
                    } else {
                        skip--;
                    }
                }
            }
        } else {
            to_remove = current - arg0;
            j = 3;
            for (; j >= 0; j--) {
                if (j != 0 && to_remove != 0) {
                    if (current != 3) {
                        fn_8016EF98(to_remove + 1);
                    } else {
                        fn_8016EF98(j);
                    }
                    if (--to_remove == 0) {
                        break;
                    }
                }
            }
        }
        lbl_80473700.count = arg0;
    }
}

#undef PLAYER_AT

void fn_80188644(void)
{
    int i;
    Vec3 sp10;
    int saved_count;

    PAD_STACK(8);

    saved_count = lbl_80473700.count;
    lbl_80473700.count = 1;
    Player_SetFacingDirection(0, 1.0f);
    Player_SetHUDDamage(0, 0);
    Stage_80224E64(0, &sp10);
    Player_800328D4(0, &sp10);
    ifStatus_802F6508(0);

    i = 0;
    do {
        if (i != 0 && i <= saved_count) {
            fn_8016EF98(i);
            if (i == 1) {
                if (i != 0) {
                    lbl_80473700.players[i].slot_type = 1;
                } else {
                    lbl_80473700.players[i].slot_type = 0;
                }
                gm_8016EDDC(i, &lbl_80473700.players[i]);
            }
        }
        i++;
    } while (i < 4);

    gm_80473814.menu_values[0] = 0;
    gm_80473814.menu_values[1] = 0;
    gm_80473814.menu_values[2] = 0;
    gm_80473814.menu_values[3] = 0;
    saved_count = 0;
    gm_80473814.menu_values[4] = saved_count;
    gm_80473814.menu_values[5] = saved_count;
    gm_80473814.menu_values[6] = saved_count;
    gm_80473814.menu_values[saved_count] = 2;
}

void fn_80188738(HSD_JObj* arg0)
{
    HSD_JObj* jobjs[3];
    int i;
    int val;

    if (pl_800412D0(0) > 999) {
        val = 999;
    } else {
        val = pl_800412D0(0);
    }

    jobjs[2] = arg0;
    jobjs[1] = (jobjs[2] == NULL) ? NULL : jobjs[2]->next;
    jobjs[0] = (jobjs[1] == NULL) ? NULL : jobjs[1]->next;

    if ((val / 100) != 0) {
        int temp = val;
        HSD_JObjReqAnimAll(jobjs[0], (f32) (temp / 100));
    } else {
        HSD_JObjReqAnimAll(jobjs[0], 10.0f);
    }

    if ((val / 10) != 0) {
        HSD_JObjReqAnimAll(jobjs[1], (f32) ((val % 100) / 10));
    } else {
        HSD_JObjReqAnimAll(jobjs[1], 10.0f);
    }

    HSD_JObjReqAnimAll(jobjs[2], (f32) (val % 10));

    for (i = 0; i < 3; i++) {
        HSD_JObjAnimAll(jobjs[i]);
    }
}

static int fn_8018846C_noInline(void)
{
    return fn_8018846C();
}

void fn_80188910(HSD_JObj* arg0)
{
    HSD_JObj* jobjs[3];
    int i;
    int val;

    if (fn_8018846C() > 999) {
        val = 999;
    } else {
        val = fn_8018846C_noInline();
    }

    jobjs[2] = arg0;
    jobjs[1] = (jobjs[2] == NULL) ? NULL : jobjs[2]->next;
    jobjs[0] = (jobjs[1] == NULL) ? NULL : jobjs[1]->next;

    if ((val / 100) != 0) {
        int temp = val;
        HSD_JObjReqAnimAll(jobjs[0], (f32) (temp / 100));
    } else {
        HSD_JObjReqAnimAll(jobjs[0], 10.0f);
    }
    if ((val / 10) != 0) {
        HSD_JObjReqAnimAll(jobjs[1], (f32) ((val % 100) / 10));
    } else {
        HSD_JObjReqAnimAll(jobjs[1], 10.0f);
    }
    HSD_JObjReqAnimAll(jobjs[2], (f32) (val % 10));

    for (i = 0; i < 3; i++) {
        HSD_JObjAnimAll(jobjs[i]);
    }
}

static int fn_801884F8_noinline(void)
{
    return fn_801884F8();
}

static int fn_801884F8_noinline_2(void)
{
    return fn_801884F8_noinline();
}

void fn_80188B3C(HSD_JObj* arg0)
{
    HSD_JObj* jobjs[3];
    TrainingModeState* state = &lbl_80473700;
    int i;
    int val;

    val = pl_80041300(0);
    if (val != 0) {
        state->result_cache[0] = val;
        state->result_cache[1] = 1;
    }
    if (state->result_cache[1] != 0) {
        val = state->result_cache[0];
    }

    if (val > 999) {
        val = 999;
    } else {
        val = fn_801884F8_noinline_2();
    }

    jobjs[2] = arg0;
    jobjs[1] = (jobjs[2] == NULL) ? NULL : jobjs[2]->next;
    jobjs[0] = (jobjs[1] == NULL) ? NULL : jobjs[1]->next;

    if ((val / 100) != 0) {
        int temp = val;
        HSD_JObjReqAnimAll(jobjs[0], (f32) (temp / 100));
    } else {
        HSD_JObjReqAnimAll(jobjs[0], 10.0f);
    }
    if ((val / 10) != 0) {
        HSD_JObjReqAnimAll(jobjs[1], (f32) ((val % 100) / 10));
    } else {
        HSD_JObjReqAnimAll(jobjs[1], 10.0f);
    }
    HSD_JObjReqAnimAll(jobjs[2], (f32) (val % 10));

    for (i = 0; i < 3; i++) {
        HSD_JObjAnimAll(jobjs[i]);
    }
}

void fn_80188D3C(HSD_JObj* arg0)
{
    HSD_JObj* jobjs[3];
    int i;
    int val;
    int hundreds;

    val = gm_80473814.menu_values[4];

    jobjs[2] = (arg0 == NULL) ? NULL : arg0->child;
    jobjs[1] = (jobjs[2] == NULL) ? NULL : jobjs[2]->next;
    jobjs[0] = (jobjs[1] == NULL) ? NULL : jobjs[1]->next;

    hundreds = val / 100;
    if (hundreds != 0) {
        HSD_JObjReqAnimAll(jobjs[0], (f32) hundreds);
    } else {
        HSD_JObjReqAnimAll(jobjs[0], 10.0f);
    }

    if ((val / 10) != 0) {
        HSD_JObjReqAnimAll(jobjs[1], (f32) ((val - (hundreds * 100)) / 10));
    } else {
        HSD_JObjReqAnimAll(jobjs[1], 10.0f);
    }

    HSD_JObjReqAnimAll(jobjs[2], (f32) (val % 10));

    for (i = 0; i < 3; i++) {
        HSD_JObjAnimAll(jobjs[i]);
    }
}

void fn_80188EE8(HSD_GObj* gobj)
{
    TrainingModeState* state = &lbl_80473700;
    CssSubStruct* sub = &gm_80473814;
    HSD_JObj* jobj;
    HSD_JObj* cursor_jobj;
    HSD_Text* text;
    s32 val;
    s32* menu_values;
    TrainingItemEntry* item_table;

    PAD_STACK(8);

    if (gm_801A45E8(2) != 0) {
        HSD_SisLib_803A6368(sub->text, 0x1E);
        HSD_JObjSetFlagsAll(sub->jobjs[3], JOBJ_HIDDEN);
    } else {
        HSD_JObjClearFlagsAll(sub->jobjs[3], JOBJ_HIDDEN);
    }

    {
        u32 counter = sub->anim_frames[22];
        if (counter < 10 || (counter >= 20 && counter < 30)) {
            sub->anim_frames[22]++;
            sub->anim_frames[1] = sub->anim_frames[22];
        }
#ifdef MUST_MATCH
        /// @remark Matching tactic: keep counter live through the update block
        /// so MWCC allocates the range-check value to r4.
        (void) sub->anim_frames[counter];
#endif
    }

    HSD_JObjReqAnimAll(sub->jobjs[22], (f32) (u32) sub->anim_frames[22]);
    HSD_JObjAnimAll(sub->jobjs[22]);
    HSD_JObjReqAnimAll(sub->jobjs[1], (f32) (u32) sub->anim_frames[1]);
    HSD_JObjAnimAll(sub->jobjs[1]);

    sub->text->pos_x =
        (12.0f * (9.798828f + HSD_JObjGetTranslationX(jobj = sub->jobjs[1]))) +
        50.0f;
    sub->text->pos_y = 150.0f;

    fn_80188738(sub->jobjs[9]);
    fn_80188910(sub->jobjs[5]);
    fn_80188B3C(sub->jobjs[19]);

    jobj = sub->jobjs[12];
    HSD_JObjReqAnimAll(jobj, (f32) gm_80473814.x03);
    HSD_JObjAnimAll(jobj);

    menu_values = gm_80473814.menu_values;
    jobj = sub->jobjs[13];
    HSD_JObjReqAnimAll(jobj, (f32) (u32) menu_values[0]);
    HSD_JObjAnimAll(jobj);

    jobj = sub->jobjs[23];
    HSD_JObjReqAnimAll(jobj, (f32) gm_80473814.x00);
    HSD_JObjAnimAll(jobj);

    jobj = sub->jobjs[34];
    HSD_JObjReqAnimAll(jobj, (f32) (u32) menu_values[0]);
    HSD_JObjAnimAll(jobj);

    val = gm_80473814.menu_values[1];
    text = gm_80473814.text;
    if (lbLang_IsSettingUS() != 0 && val == 0x13) {
        HSD_SisLib_803A6368(text, 0x17);
    } else {
        item_table = TrainingItemTable_Get();
        HSD_SisLib_803A6368(text, (s32) item_table[val].text_id);
    }

    jobj = sub->jobjs[32];
    HSD_JObjReqAnimAll(jobj, (f32) (u32) (gm_80473814.menu_values[2] + 1));
    HSD_JObjAnimAll(jobj);

    jobj = sub->jobjs[31];
    HSD_JObjReqAnimAll(jobj, (f32) (u32) gm_80473814.menu_values[3]);
    HSD_JObjAnimAll(jobj);

    fn_80188D3C(sub->jobjs[27]);

    HSD_JObjSetFlags(sub->jobjs[25], JOBJ_HIDDEN);

    val = gm_80473814.menu_values[6];
    cursor_jobj = sub->jobjs[26];
    if (val == 2 && state->mode == 3) {
        val = 3;
    }
    HSD_JObjReqAnimAll(cursor_jobj, (f32) val);
    HSD_JObjAnimAll(cursor_jobj);
}

#ifdef MUST_MATCH
#pragma dont_inline off
#endif
static inline u32 gm_801891F4_GetTickRate(void)
{
    return OS_TIMER_CLOCK;
}

static inline s32* gm_801891F4_GetMenuValues(CssSubStruct* sub)
{
    return sub->menu_values;
}

static inline void gm_801891F4_SetCpuType(int cpu_type)
{
    int i;
    int count;

    count = lbl_80473700.count;
    gm_80473814.x03 = (u8) cpu_type;
    for (i = 0; i < 4; i++) {
        if (i != 0 && count != 0) {
            Player_SetPlayerAndEntityCpuType(i, cpu_type);
            count--;
            if (count == 0) {
                break;
            }
        }
    }
}

void fn_801891F4(void)
{
    CssSubStruct* sub;
    u64 buttons;
    TrainingSpeedStack speed_stack;
    Vec3 pos;

    buttons = gm_801A36C0((u8) lbl_80473700.mode);
    sub = &gm_80473814;

    if (gm_801A45E8(2) != 0) {
        if (sub->x01 == 0) {
            fn_801651FC(0, 0);
            gm_801891F4_SetCpuType(0);
            sub->anim_frames[22] = 0;
        }
        sub->x01 = 1;

        if (buttons & PAD_ANY_UP) {
            sfxMove();
            if (sub->x00 != 0) {
                sub->x00--;
                if (sub->x00 == 5) {
                    sub->x00 = 4;
                }
            } else {
                sub->x00 = 8;
            }
        }

        if (buttons & PAD_ANY_DOWN) {
            sfxMove();
            if (sub->x00 < 8) {
                sub->x00++;
                if (sub->x00 == 5) {
                    sub->x00 = 6;
                }
            } else {
                sub->x00 = 0;
            }
        }

        switch (sub->x00) {
        case 0:
            if (buttons & PAD_ANY_LEFT) {
                sfxMove();
                if ((u32) sub->menu_values[sub->x00] != 0) {
                    sub->menu_values[sub->x00]--;
                    return;
                }
                sub->menu_values[sub->x00] = 5;
                return;
            }
            if (buttons & PAD_ANY_RIGHT) {
                sfxMove();
                if ((u32) sub->menu_values[sub->x00] < 5) {
                    sub->menu_values[sub->x00]++;
                    return;
                }
                sub->menu_values[sub->x00] = 0;
                return;
            }
            break;
        case 1:
            if (buttons & PAD_ANY_LEFT) {
                sfxMove();
                if ((u32) sub->menu_values[sub->x00] != 0) {
                    sub->menu_values[sub->x00]--;
                } else {
                    sub->menu_values[sub->x00] = 0x1D;
                }
            } else if (buttons & PAD_ANY_RIGHT) {
                sfxMove();
                if ((u32) sub->menu_values[sub->x00] < 0x1D) {
                    sub->menu_values[sub->x00]++;
                } else {
                    sub->menu_values[sub->x00] = 0;
                }
            }
            if (buttons & PAD_BUTTON_A) {
                s16 item;
                HSD_JObj* jobj;
                lbAudioAx_80024030(8);
                item =
                    gmTraining_ItemTable[gm_80473814.menu_values[1]].item_id;
                jobj = Player_GetEntity(0)->hsd_obj;
                HSD_JObjGetTranslation2(jobj, &pos);
                pos.y += 10.0f;
                it_8026D258(&pos, (ItemKind) item);
                return;
            }
            break;
        case 2:
            if (buttons & PAD_ANY_LEFT) {
                sfxMove();
                if ((u32) sub->menu_values[sub->x00] != 0) {
                    sub->menu_values[sub->x00]--;
                    return;
                }
                sub->menu_values[sub->x00] = 2;
                return;
            }
            if (buttons & PAD_ANY_RIGHT) {
                sfxMove();
                if ((u32) sub->menu_values[sub->x00] < 2) {
                    sub->menu_values[sub->x00]++;
                    return;
                }
                sub->menu_values[sub->x00] = 0;
                return;
            }
            break;
        case 3:
            if (buttons & PAD_ANY_LEFT) {
                sfxMove();
                if ((u32) sub->menu_values[sub->x00] != 0) {
                    sub->menu_values[sub->x00]--;
                    return;
                }
                sub->menu_values[sub->x00] = 5;
                return;
            }
            if (buttons & PAD_ANY_RIGHT) {
                sfxMove();
                if ((u32) sub->menu_values[sub->x00] < 5) {
                    sub->menu_values[sub->x00]++;
                    return;
                }
                sub->menu_values[sub->x00] = 0;
                return;
            }
            break;
        case 4:
            if (buttons & PAD_ANY_LEFT) {
                sfxMove();
                if ((u32) sub->menu_values[sub->x00] != 0) {
                    gm_801891F4_GetMenuValues(sub)[sub->x00]--;
                    if ((u32) sub->menu_values[sub->x00] == 0) {
                        gm_801A36E0(0, 0x19);
                        return;
                    }
                } else {
                    sub->menu_values[sub->x00] = 0x3E7;
                    return;
                }
            } else if (buttons & PAD_ANY_RIGHT) {
                sfxMove();
                if ((u32) sub->menu_values[sub->x00] < 0x3E7) {
                    sub->menu_values[sub->x00]++;
                    if ((u32) sub->menu_values[sub->x00] == 0x3E7) {
                        gm_801A36E0(0, 0x19);
                        return;
                    }
                } else {
                    sub->menu_values[sub->x00] = 0;
                    return;
                }
            }
            break;
        case 5:
            if (buttons & PAD_ANY_LEFT) {
                sfxMove();
                sub->menu_values[sub->x00] = 0;
                return;
            }
            if (buttons & PAD_ANY_RIGHT) {
                sfxMove();
                sub->menu_values[sub->x00] = 1;
                return;
            }
            break;
        case 6:
            if (buttons & PAD_ANY_LEFT) {
                sfxMove();
                if ((u32) sub->menu_values[sub->x00] != 0) {
                    sub->menu_values[sub->x00]--;
                } else {
                    sub->menu_values[sub->x00] = 2;
                }
                switch (sub->menu_values[sub->x00]) {
                case 0:
                    fn_801650E8();
                    return;
                case 1:
                    fn_80165190(0, 5);
                    return;
                case 2:
                    if (lbl_80473700.mode == 3) {
                        fn_801652B0(0, 0);
                        return;
                    }
                    fn_801652B0(0, 3);
                    return;
                }
            } else if (buttons & PAD_ANY_RIGHT) {
                sfxMove();
                if ((u32) sub->menu_values[sub->x00] < 2) {
                    sub->menu_values[sub->x00]++;
                } else {
                    sub->menu_values[sub->x00] = 0;
                }
                switch (sub->menu_values[sub->x00]) {
                case 0:
                    fn_801650E8();
                    return;
                case 1:
                    fn_80165190(0, 5);
                    return;
                case 2:
                    if (lbl_80473700.mode == 3) {
                        fn_801652B0(0, 0);
                        return;
                    }
                    fn_801652B0(0, 3);
                    return;
                }
            }
            break;
        case 7:
            if (buttons & PAD_BUTTON_A) {
                sfxForward();
                fn_80188644();
                return;
            }
            break;
        case 8:
            if (buttons & PAD_BUTTON_A) {
                gm_8016B328();
                return;
            }
            break;
        }
    } else {
        if (sub->x01 == 1) {
            PAD_STACK(20);

            speed_stack.speeds = lbl_803B7C68;

            sfxBack();
            sub->anim_frames[22] = 0x14;
            {
                f32 selected_speed =
                    speed_stack.speeds.values[sub->menu_values[0]];
                lb_80019880(
                    __cvt_dbl_usll((f64) (0.016666668f / selected_speed *
                                          (f32) gm_801891F4_GetTickRate())));
            }

            fn_80188550(sub->menu_values[2] + 1);

            gm_801891F4_SetCpuType(sub->menu_values[3]);

            {
                int count;
                int i;
                int damage;

                damage = sub->menu_values[4];
                count = lbl_80473700.count;
                for (i = 0; i < 4; i++) {
                    if (i != 0 && count != 0) {
                        Player_SetHUDDamage(i, damage);
                        count--;
                        if (count == 0) {
                            break;
                        }
                    }
                }
            }

            {
                int i;

                for (i = 1; i < 4; i++) {
                    fn_8016B388(i, sub->menu_values[4]);
                }
            }

            switch (sub->menu_values[6]) {
            case 0:
                fn_801650E8();
                break;
            case 1:
                fn_80165190(0, 5);
                break;
            case 2:
                if (lbl_80473700.mode == 3) {
                    fn_801652B0(0, 0);
                } else {
                    fn_801652B0(0, 3);
                }
                break;
            }
        }
        sub->x01 = 0;
    }
}
#ifdef MUST_MATCH
#pragma dont_inline off
#endif

void fn_80189B88(void)
{
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    TrainingModeState* state;
    CssSubStruct* sub;
    int i;

    state = &lbl_80473700;
    sub = &gm_80473814;
    sub->x00 = 0;
    sub->x01 = 0;
    HSD_GObj_SetupProc(GObj_Create(0xE, 2, 0), (HSD_GObjEvent) fn_801891F4,
                       0x15);
    gobj = GObj_Create(0xE, 0xF, 0);
    jobj = HSD_JObjLoadJoint((*lbl_804D662C)->joint);
    gm_80473814.gobj = gobj;
    HSD_GObjObject_80390A70(gobj, HSD_GObj_JObjKind, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0xB, 0);
    HSD_GObj_SetupProc(gobj, (HSD_GObjEvent) fn_80188EE8, 0x11);
    gm_8016895C(jobj, *lbl_804D662C, 0);
    HSD_JObjReqAnimAll(jobj, 0.0f);
    HSD_JObjAnimAll(jobj);
    for (i = 0; i < 0x27; i++) {
        sub->anim_frames[i] = 0;
        lb_80011E24(jobj, &sub->jobjs[i], i, -1);
    }
    sub->anim_frames[22] = 0x1E;
    sub->anim_frames[1] = 0x1E;
    sub->menu_values[0] = 0;
    sub->menu_values[1] = 0;
    sub->menu_values[2] = 0;
    sub->menu_values[3] = 0;
    sub->menu_values[4] = 0;
    sub->menu_values[5] = 0;
    sub->menu_values[6] = 0;
    sub->menu_values[0] = 2;
}

void gm_80189CDC(StartMeleeData* arg0)
{
    TrainingModeState* state = &lbl_80473700;
    s32 i;

    arg0->rules.match_kind = 0;
    arg0->rules.is_teams = 1;
    arg0->rules.xB = -1;
    arg0->rules.x20 = 0xFFFFFFFFFFFFFFFFULL;
    arg0->rules.x5_0 = 1;

    for (i = 0; i < 4; i++) {
        state->players[i] = gm_80473814.saved_players[i] = arg0->players[i];
    }

    state->mode = (s32) (arg0->players[0].slot - 1);
    state->count = 1;

    for (i = 0; 0x1B > i; i++) {
        state->char_data[i] = 0;
    }
}

static inline void resetText(HSD_Text* text)
{
    text->x34.x = 0.7f;
    text->x34.y = 0.6f;
}

HSD_Text* fn_8018A000(void)
{
    TrainingModeState* state;
    u8* data;
    HSD_Text** text_ptr;
    HSD_Text* text;

    PAD_STACK(0x10);
    data = M2C_BITWISE(u8*, gmTraining_ItemTable);
    state = &lbl_80473700;
    memzero(state->result_cache, sizeof(state->result_cache));
    lbl_804D6628 = lbArchive_80016DBC("GmTrain", &lbl_804D662C,
                                      "ScGamTraining_scene_models", 0);
    fn_80189B88();
    ifAll_GetHUDGObj();
    HSD_SisLib_803A611C(0, NULL, 9, 0x14, 0, 0xE, 0, 0x12);
    if (lbLang_IsSavedLanguageUS()) {
        HSD_SisLib_803A62A0(0, "SdTrain.usd", "SIS_TrainingData");
    } else {
        HSD_SisLib_803A62A0(0, "SdTrain.dat", "SIS_TrainingData");
    }

    *(text_ptr = &gm_80473814.text) = HSD_SisLib_803A5ACC(
        0, 0,
        (12.0f * (HSD_JObjGetTranslationX(gm_80473814.jobjs[1]) + 9.798828f)) +
            50.0f,
        150.0f, 0.1f, 167.0f, 16.0f);
    text = *text_ptr;
    lbLang_IsSettingUS();
    HSD_SisLib_803A6368(text, (s32) * (s16*) &data[2]);
    (*text_ptr)->default_fitting = 1;
    resetText(*text_ptr);
    text = *text_ptr;
    (*text_ptr)->default_alignment = 2;
    return text;
}
