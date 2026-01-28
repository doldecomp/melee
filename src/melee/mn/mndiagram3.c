#include "mndiagram3.h"

#include "ft/ft_0C31.h"
#include "gm/gmmain_lib.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "lb/lbaudio_ax.h"
#include "mn/mndiagram.h"
#include "mn/mndiagram2.h"
#include "mn/mnmain.h"
#include "mn/mnname.h"

#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjplink.h>
#include <baselib/gobjproc.h>
#include <baselib/gobjuserdata.h>
#include <baselib/jobj.h>
#include <baselib/memory.h>
#include <baselib/sislib.h>

HSD_GObj* mnDiagram3_804D6C20;

typedef struct Diagram3Data {
    /* 0x00 */ u8 x0;
    /* 0x01 */ u8 x1;
    /* 0x02 */ char pad2[2];
    /* 0x04 */ u8 x4;
    /* 0x05 */ u8 x5;
    /* 0x06 */ u8 x6;
    /* 0x07 */ char pad7;
    /* 0x08 */ HSD_JObj* x8;
    /* 0x0C */ HSD_JObj* xC;
    /* 0x10 */ HSD_JObj* x10;
    /* 0x14 */ HSD_JObj* x14;
    /* 0x18 */ HSD_JObj* x18;
    /* 0x1C */ HSD_JObj* x1C;
    /* 0x20 */ HSD_JObj* x20;
    /* 0x24 */ HSD_JObj* x24;
    /* 0x28 */ HSD_JObj* x28;
    /* 0x2C */ HSD_JObj* x2C;
    /* 0x30 */ void* x30[10];
    /* 0x58 */ void* x58[7];
    /* 0x74 */ HSD_GObj* x74;
} Diagram3Data;

static inline f32 mnDiagram3_JObjGetTranslationX(HSD_JObj* jobj)
{
    ((jobj) ? ((void) 0)
            : __assert(mnDiagram3_804D4FD8, 0x3E1, mnDiagram3_804D4FE0));
    return jobj->translate.x;
}

static inline f32 mnDiagram3_JObjGetTranslationY(HSD_JObj* jobj)
{
    ((jobj) ? ((void) 0)
            : __assert(mnDiagram3_804D4FD8, 0x3EE, mnDiagram3_804D4FE0));
    return jobj->translate.y;
}

static inline f32 mnDiagram3_JObjGetTranslationZ(HSD_JObj* jobj)
{
    ((jobj) ? ((void) 0)
            : __assert(mnDiagram3_804D4FD8, 0x3FB, mnDiagram3_804D4FE0));
    return jobj->translate.z;
}

static inline void mnDiagram3_JObjSetTranslateX(HSD_JObj* jobj, f32 x)
{
    ((jobj) ? ((void) 0)
            : __assert(mnDiagram3_804D4FD8, 0x3A4, mnDiagram3_804D4FE0));
    jobj->translate.x = x;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        ftCo_800C6AFC(jobj);
    }
}

static inline void mnDiagram3_JObjSetTranslateY(HSD_JObj* jobj, f32 y)
{
    ((jobj) ? ((void) 0)
            : __assert(mnDiagram3_804D4FD8, 0x3B3, mnDiagram3_804D4FE0));
    jobj->translate.y = y;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        ftCo_800C6AFC(jobj);
    }
}

static inline void mnDiagram3_JObjSetTranslateZ(HSD_JObj* jobj, f32 z)
{
    ((jobj) ? ((void) 0)
            : __assert(mnDiagram3_804D4FD8, 0x3C2, mnDiagram3_804D4FE0));
    jobj->translate.z = z;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        ftCo_800C6AFC(jobj);
    }
}

void mnDiagram3_80246D40(HSD_GObj* gobj)
{
    Diagram3Data* data = gobj->user_data;
    HSD_JObj* jobj1 = data->x14;
    HSD_JObj* jobj2;
    int threshold;

    mn_8022ED6C(jobj1, &mnDiagram3_803EEC1C);

    if (data->x6 != 0) {
        threshold = 0x18;
    } else {
        threshold = 0x15;
    }

    if (data->x4 + 0xA < threshold) {
        HSD_JObjClearFlagsAll(jobj1, 0x10);
    } else {
        HSD_JObjSetFlagsAll(jobj1, 0x10);
    }

    jobj2 = data->x18;
    mn_8022ED6C(jobj2, &mnDiagram3_803EEC1C);

    if (data->x4 != 0) {
        HSD_JObjClearFlagsAll(jobj2, 0x10);
    } else {
        HSD_JObjSetFlagsAll(jobj2, 0x10);
    }
}

static void fn_80246E04(HSD_GObj* gobj)
{
    Diagram3Data* data;
    char* tbl;
    AnimLoopSettings* table;
    PAD_STACK(4);

    data = gobj->user_data;
    tbl = mnDiagram3_803EEC10;
    table = (AnimLoopSettings*) tbl;
    if (mn_8022ED6C(data->xC, table) >= table->end_frame) {
        HSD_GObjPLink_80390228(gobj);
    }
}

static void fn_80246E64(HSD_GObj* gobj)
{
    u8 cur_menu;
    MenuFlow* flow = &mn_804A04F0;
    Diagram3Data* data = gobj->user_data;
    HSD_GObjProc* proc;
    PAD_STACK(8);

    cur_menu = flow->cur_menu;

    if (cur_menu == 0x1E) {
        if (flow->x10 == 2) {
            goto call_diagram;
        }
    }

    if (cur_menu == 0x1E) {
        HSD_GObjPLink_80390228(gobj);
        return;
    }

    HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
    proc = HSD_GObjProc_8038FD54(gobj, fn_80246E04, 0);
    proc->flags_3 = HSD_GObj_804D783C;
    HSD_JObjSetFlagsAll(data->x10, 0x10);
    return;

call_diagram:
    mnDiagram3_80246D40(gobj);
}

void fn_80246F0C(void* arg0)
{
    HSD_Free(arg0);
}

void mnDiagram3_80246F2C(struct Diagram3Data* data, void* arg1)
{
    int i;
    int zero = 0;
    void** ptr;
    PAD_STACK(8);

    (void) arg1;
    data->x0 = mn_804A04F0.cur_menu;
    data->x1 = (u8) mn_804A04F0.hovered_selection;
    data->x5 = 1;
    data->x4 = zero;
    data->x6 = gmMainLib_8015CC34()->xD;
    data->x30[0] = NULL;
    data->x30[1] = NULL;
    data->x30[2] = NULL;
    data->x30[3] = NULL;
    data->x30[4] = NULL;
    data->x30[5] = NULL;
    data->x30[6] = NULL;
    data->x30[7] = NULL;

    i = 8;
    goto setup;
body: {
    int count = 10 - i;
    if (i >= 10) {
        goto exit;
    }
    do {
        *ptr++ = NULL;
    } while (--count);
}

exit:
    data->x74 = NULL;
    data->x58[0] = NULL;
    data->x58[1] = NULL;
    data->x58[2] = NULL;
    data->x58[3] = NULL;
    data->x58[4] = NULL;
    data->x58[5] = NULL;
    data->x58[6] = NULL;
    return;

setup:
    ptr = &data->x30[i];
    goto body;
}

void mnDiagram3_80247008(void* arg0)
{
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    Diagram3Data* data;
    int i;
    char* errbase = mnDiagram3_803EEC10;
    StaticModelDesc3* desc = &mnDiagram_804A0844;

    gobj = GObj_Create(6, 7, 0x80);
    mnDiagram3_804D6C20 = gobj;
    jobj = HSD_JObjLoadJoint(desc->joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 6, 0x80);
    HSD_JObjAddAnimAll(jobj, desc->animjoint, desc->matanimjoint,
                       desc->shapeanimjoint);
    HSD_JObjReqAnimAll(jobj, mnDiagram3_804DC00C);
    HSD_JObjAnimAll(jobj);

    data = HSD_MemAlloc(sizeof(Diagram3Data));
    if (data == NULL) {
        OSReport(&errbase[0x9C]);
        __assert(&errbase[0xB4], 0x3FC, &errbase[0xC4]);
    }

    mnDiagram3_80246F2C(data, arg0);
    GObj_InitUserData(gobj, 0, fn_80246F0C, data);

    i = 0;
    do {
        lb_80011E24(jobj, (HSD_JObj**) ((u8*) data + (i << 2) + 8), i, -1);
        i++;
    } while (i < 10);

    HSD_GObjProc_8038FD54(gobj, fn_80246E64, 0);
}

static void fn_802461BC(HSD_GObj* gobj);
void mnDiagram3_80245BA4(HSD_GObj*);

void mnDiagram3_8024714C(void* arg0)
{
    f32 pos[3];
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    Diagram3Data* data;
    HSD_JObj* jobj28;
    HSD_JObj* jobj2C;
    f32 f30;
    f32 f31;
    f32 f29;
    int i;
    void** ptr;
    StaticModelDesc3* desc;
    HSD_Text* text;
    HSD_GObjProc* proc;
    u8 threshold;
    u8 idx;
    HSD_GObj* gobj2;
    PAD_STACK(12);

    mn_804A04F0.x10 = 2;
    mn_804A04F0.hovered_selection = 0;
    mnDiagram3_80247008(arg0);

    gobj = mnDiagram3_804D6C20;
    desc = &mnDiagram_804A0854;
    data = gobj->user_data;
    gobj2 = GObj_Create(6, 7, 0x80);
    data->x74 = gobj2;
    jobj = HSD_JObjLoadJoint(desc->joint);
    HSD_GObjObject_80390A70(gobj2, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj2, HSD_GObj_JObjCallback, 4, 0x80);
    HSD_JObjAddAnimAll(jobj, desc->animjoint, desc->matanimjoint,
                       desc->shapeanimjoint);
    HSD_JObjReqAnimAll(jobj, mnDiagram3_804DC00C);
    HSD_JObjAnimAll(jobj);

    data = gobj->user_data;
    f30 = mnDiagram3_JObjGetTranslationY(data->x28);
    f30 = mnDiagram3_JObjGetTranslationY(data->x2C) - f30;
    f31 = mnDiagram3_JObjGetTranslationX(data->x28);
    mnDiagram3_JObjSetTranslateX(jobj, f31);
    mnDiagram3_JObjSetTranslateY(
        jobj,
        f30 * mnDiagram3_804DC00C + mnDiagram3_JObjGetTranslationY(data->x28));
    mnDiagram3_JObjSetTranslateZ(jobj,
                                 mnDiagram3_JObjGetTranslationZ(data->x28));

    data = mnDiagram3_804D6C20->user_data;
    idx = data->x4;
    f30 = mnDiagram3_JObjGetTranslationY(data->x28);
    f30 = mnDiagram3_JObjGetTranslationY(data->x2C) - f30;

    lb_8000B1CC(data->x28, &mnDiagram3_803EEC28, (Vec3*) pos);

    f29 = mnDiagram3_804DBFF8;
    ptr = data->x30;
    i = 0;
    do {
        u8 tableIdx;
        text =
            HSD_SisLib_803A5ACC(0, 1, pos[0] - f29, -f30 * (f32) i + -pos[1],
                                pos[2], f29, mnDiagram3_804DBFFC);
        *ptr = text;
        if (data->x6 != 0) {
            threshold = 0x18;
        } else {
            threshold = 0x15;
        }
        if (idx + (u8) i >= threshold) {
            tableIdx = idx + (u8) i - threshold;
        } else {
            tableIdx = idx + (u8) i;
        }
        HSD_SisLib_803A6368(text, mnDiagram3_803EEC4C[tableIdx]);
        i++;
        ptr++;
    } while (i < 10);

    mnDiagram3_80245BA4(mnDiagram3_804D6C20);
    proc = HSD_GObjProc_8038FD54(GObj_Create(0, 1, 0x80), fn_802461BC, 0);
    proc->flags_3 = HSD_GObj_804D783C;
}

void mnDiagram3_80245BA4(HSD_GObj* gobj)
{
    f32 pos[3];
    char str[20];
    u8 sp48[16];
    u8 sp38[16];
    u8 sp28[24];

    HSD_JObj* jobj20;
    HSD_JObj* jobj24;
    u16* idxTable;
    Diagram3Data* ptr;
    char* table;
    HSD_Text* text1;
    u8 charId;
    HSD_Text* text2;
    Diagram3Data* data;
    int i;
    u8 idx;

    u8 threshold;
    f32 f27;
    f32 f28;
    f32 f30;
    f32 f31;
    f64 f29;

    data = gobj->user_data;
    table = mnDiagram3_803EEC10;

    if (data->x6 != 0) {
        threshold = 0x18;
    } else {
        threshold = 0x15;
    }
    if (data->x4 + data->x1 >= threshold) {
        idx = data->x4 + data->x1 - threshold;
    } else {
        idx = data->x4 + data->x1;
    }

    jobj20 = data->x20;
    f27 = mnDiagram3_JObjGetTranslationY(jobj20);
    jobj24 = data->x24;
    f30 = mnDiagram3_JObjGetTranslationY(jobj24) - f27;
    idxTable = (u16*) &table[idx * 2 + 0x6C];
    f28 = mnDiagram3_804DC010;
    f29 = mnDiagram3_804DC000;
    f27 = mnDiagram3_804DC008;
    f31 = -f30;
    ptr = data;

    for (i = 0; i < 5; i++) {
        if (data->x6 != 0) {
            if (mnDiagram2_IsIconOnlyStat(idx) == 0) {
                if (i == 0) {
                    lb_8000B1CC(data->x20, (Vec3*) &table[0x24], (Vec3*) pos);
                    text1 = HSD_SisLib_803A6754(0, 1);
                    data->x58[0] = text1;
                    text1->font_size.x = f27;
                    text1->font_size.y = f27;
                    text1->pos_x = pos[0];
                    text1->pos_y = -pos[1];
                    text1->pos_z = pos[2];
                }
                charId = mnDiagram2_GetRankedName(idx, (u8) i);
                if (charId != 0x78) {
                    HSD_SisLib_803A6B98(text1, mnDiagram3_804DC00C,
                                        (f31 * (f32) i) / f27,
                                        GetNameText(charId));
                }
                goto next_iter;
            }
        } else {
            HSD_JObj* jobj;
            charId = mnDiagram2_GetRankedFighter(idx, (u8) i);
            jobj = mnDiagram_CreateFighterIcon(charId, 0);
            mnDiagram3_JObjSetTranslateY(jobj, f30 * (f32) i);
            HSD_JObjAddChild(data->x20, jobj);
        }

        if (i == 0) {
            lb_8000B1CC(data->x20, (Vec3*) &table[0x30], (Vec3*) pos);
            text2 = HSD_SisLib_803A6754(0, 1);
            data->x58[1] = text2;
            text2->font_size.x = f27;
            text2->font_size.y = f27;
            text2->pos_x = pos[0];
            text2->pos_y = -pos[1];
            text2->pos_z = pos[2];
            text2->default_alignment = 2;
            text2->text_color = *(GXColor*) &mn_804D4B64;
        }

        if (mnDiagram2_IsIconOnlyStat(idx) != 0) {
            mnDiagram2_GetAggregatedFighterRank(sp48, idx, (u8) i);
            if (sp48[0] != 0x19) {
                HSD_JObj* jobj2;
                mnDiagram2_GetAggregatedFighterRank(sp38, idx, (u8) i);
                jobj2 = mnDiagram_CreateFighterIcon(sp38[0], 0);
                mnDiagram3_JObjSetTranslateY(jobj2, f30 * (f32) i);
                HSD_JObjAddChild(data->x20, jobj2);
                mnDiagram2_GetAggregatedFighterRank(sp28, idx, (u8) i);
                mnDiagram_FormatDecimalNumber(str, sp28[6], 0);
                HSD_SisLib_803A6B98(text2, mnDiagram3_804DC00C,
                                    (f31 * (f32) i) / f27, str);
                goto after_stats;
            }
        }

        if (mnDiagram2_IsTimeStat(idx) != 0) {
            u32 val = mnDiagram2_GetStatValue(data->x6, idx, charId);
            if (val > 0x5B8D7F) {
                val = 0x5B8D7F;
            }
            mnDiagram_FormatTime(str, val);
        } else if (mnDiagram2_IsDistanceStat(idx) != 0) {
            u32 val = mnDiagram2_GetStatValue(data->x6, idx, charId);
            val = mnDiagram_ConvertDistanceForDisplay(val);
            if (val > 0x05F5E0FF) {
                val = 0x05F5E0FF;
            }
            mnDiagram_IntToStr(str, val);
        } else if (mnDiagram2_IsPercentageStat(idx) != 0) {
            u32 val = mnDiagram2_GetStatValue(data->x6, idx, charId);
            if (val > 0x98967F) {
                val = 0x98967F;
            }
            mnDiagram_FormatDecimalNumber(str, val, 2);
        } else if (mnDiagram2_IsIconOnlyStat(idx) == 0) {
            u32 val = mnDiagram2_GetStatValue(data->x6, idx, charId);
            if (val > 0x05F5E0FF) {
                val = 0x05F5E0FF;
            }
            mnDiagram_FormatDecimalNumber(str, val, 0);
        }

        HSD_SisLib_803A6B98(text2, mnDiagram3_804DC00C, (f31 * (f32) i) / f27,
                            str);

    after_stats: {
        u16 sisIdx = *idxTable;
        if (sisIdx != 0xFFFF) {
            HSD_Text* text3;
            lb_8000B1CC(data->x20, (Vec3*) &table[0x30], (Vec3*) pos);
            text3 = HSD_SisLib_803A5ACC(
                0, 1, f28 + pos[0], f31 * (f32) i + -pos[1], pos[2],
                mnDiagram3_804DC014, mnDiagram3_804DC014);
            ptr->x58[2] = text3;
            text3->default_alignment = 1;
            text3->text_color = *(GXColor*) &mn_804D4B64;
            if (mnDiagram2_IsDistanceStat(idx) != 0) {
                u32 stat_val = mnDiagram2_GetStatValue(data->x6, idx, charId);
                if (mnDiagram_IsDistanceOverflow(stat_val)) {
                    HSD_SisLib_803A6368(text3, 0x7F);
                } else {
                    HSD_SisLib_803A6368(text3, sisIdx);
                }
            } else {
                HSD_SisLib_803A6368(text3, sisIdx);
            }
        }
    }

    next_iter:
        ptr = (Diagram3Data*) ((u8*) ptr + 4);
    }
}

void fn_802461BC(HSD_GObj* gobj)
{
    f32 pos[3];
    char* table = mnDiagram3_803EEC10;
    Diagram3Data* data = mnDiagram3_804D6C20->user_data;
    u32 buttons;
    int i;
    HSD_JObj* jobj;

    buttons = mn_80229624(4);
    mn_804A04F0.buttons = buttons;

    /* B button - return */
    if (buttons & 0x20) {
        lbAudioAx_80024030(0);
        mn_804A04F0.entering_menu = 0;
        {
            u8 x6 = data->x6;
            GameRules* rules = gmMainLib_8015CC34();
            rules->xD = x6;
        }
        mnDiagram2_ClearDetailView(mnDiagram3_804D6C20);
        HSD_GObjPLink_80390228(data->x74);
        for (i = 0; i < 10; i++) {
            if (data->x30[i] != NULL) {
                HSD_SisLib_803A5CC4(data->x30[i]);
                data->x30[i] = NULL;
            }
        }
        mn_80229894(0x1C, 0, 3);
        return;
    }

    /* L/R + Start - exit */
    if (buttons & 0xC0) {
        lbAudioAx_80024030(1);
        {
            u8 x6 = data->x6;
            GameRules* rules = gmMainLib_8015CC34();
            rules->xD = x6;
        }
        mnDiagram2_ClearDetailView(mnDiagram3_804D6C20);
        HSD_GObjPLink_80390228(data->x74);
        for (i = 0; i < 10; i++) {
            if (data->x30[i] != NULL) {
                HSD_SisLib_803A5CC4(data->x30[i]);
                data->x30[i] = NULL;
            }
        }
        HSD_GObjPLink_80390228(gobj);
        if (buttons & 0x40) {
            mnDiagram2_Init();
            return;
        }
        mnDiagram_Init(0, 0);
        return;
    }

    /* L/R triggers - toggle mode */
    if (buttons & 0xC00) {
        if (GetNameCount() == 0) {
            lbAudioAx_80024030(3);
            return;
        }
        lbAudioAx_80024030(1);
        if (data->x6 == 0) {
            data->x6 = 1;
        } else {
            data->x6 = 0;
        }
        if (data->x6 == 0 && data->x4 + 10 >= 0x15) {
            data->x4 = 0;
        }
        for (i = 0; i < 10; i++) {
            if (data->x30[i] != NULL) {
                HSD_SisLib_803A5CC4(data->x30[i]);
                data->x30[i] = NULL;
            }
        }
        {
            HSD_JObj* jobj28 = data->x28;
            HSD_JObj* jobj2C = data->x2C;
            u8 x4 = data->x4;
            f32 f30;
            f32 f31;
            Diagram3Data* ptr = data;

            if (jobj28 == NULL) {
                __assert(mnDiagram3_804D4FD8, 0x3EE, mnDiagram3_804D4FE0);
            }
            if (jobj2C == NULL) {
                __assert(mnDiagram3_804D4FD8, 0x3EE, mnDiagram3_804D4FE0);
            }
            f30 = jobj2C->translate.y - jobj28->translate.y;
            lb_8000B1CC(jobj28, (Vec3*) &table[0x18], (Vec3*) pos);
            f31 = mnDiagram3_804DBFF8;
            for (i = 0; i < 10; i++) {
                HSD_Text* text;
                u8 threshold = (data->x6 != 0) ? 0x18 : 0x15;
                u8 idx;
                s32 sum = x4 + i;
                if (sum >= threshold) {
                    idx = sum - threshold;
                } else {
                    idx = sum;
                }
                text = HSD_SisLib_803A5ACC(0, 1, pos[0] - f31,
                                           -f30 * (f32) i + -pos[1], pos[2],
                                           f31, mnDiagram3_804DBFFC);
                ptr->x30[0] = text;
                HSD_SisLib_803A6368(text, mnDiagram3_803EEC4C[idx]);
                ptr = (Diagram3Data*) ((u8*) ptr + 4);
            }
        }
        mnDiagram2_ClearDetailView(mnDiagram3_804D6C20);
        mnDiagram3_80245BA4(mnDiagram3_804D6C20);
        return;
    }

    /* D-pad up */
    if (buttons & 1) {
        if (data->x1 != 0) {
            f32 f30;
            lbAudioAx_80024030(2);
            data->x1--;
            jobj = data->x74->hsd_obj;
            f30 = mnDiagram3_JObjGetTranslationY(data->x2C) -
                  mnDiagram3_JObjGetTranslationY(data->x28);
            mnDiagram3_JObjSetTranslateX(
                jobj, mnDiagram3_JObjGetTranslationX(data->x28));
            mnDiagram3_JObjSetTranslateY(
                jobj,
                f30 * data->x1 + mnDiagram3_JObjGetTranslationY(data->x28));
            mnDiagram3_JObjSetTranslateZ(
                jobj, mnDiagram3_JObjGetTranslationZ(data->x28));
            mnDiagram2_ClearDetailView(mnDiagram3_804D6C20);
            mnDiagram3_80245BA4(mnDiagram3_804D6C20);
            return;
        }
        if (data->x4 != 0) {
            lbAudioAx_80024030(2);
            data->x4--;
            for (i = 0; i < 10; i++) {
                if (data->x30[i] != NULL) {
                    HSD_SisLib_803A5CC4(data->x30[i]);
                    data->x30[i] = NULL;
                }
            }
            {
                HSD_JObj* jobj28 = data->x28;
                HSD_JObj* jobj2C = data->x2C;
                u8 x4 = data->x4;
                f32 f30;
                f32 f31;
                Diagram3Data* ptr = data;

                if (jobj28 == NULL) {
                    __assert(mnDiagram3_804D4FD8, 0x3EE, mnDiagram3_804D4FE0);
                }
                if (jobj2C == NULL) {
                    __assert(mnDiagram3_804D4FD8, 0x3EE, mnDiagram3_804D4FE0);
                }
                f30 = jobj2C->translate.y - jobj28->translate.y;
                lb_8000B1CC(jobj28, (Vec3*) &table[0x18], (Vec3*) pos);
                f31 = mnDiagram3_804DBFF8;
                for (i = 0; i < 10; i++) {
                    HSD_Text* text;
                    u8 threshold = (data->x6 != 0) ? 0x18 : 0x15;
                    u8 idx;
                    s32 sum = x4 + i;
                    if (sum >= threshold) {
                        idx = sum - threshold;
                    } else {
                        idx = sum;
                    }
                    text = HSD_SisLib_803A5ACC(
                        0, 1, pos[0] - f31, -f30 * (f32) i + -pos[1], pos[2],
                        f31, mnDiagram3_804DBFFC);
                    ptr->x30[0] = text;
                    HSD_SisLib_803A6368(text, mnDiagram3_803EEC4C[idx]);
                    ptr = (Diagram3Data*) ((u8*) ptr + 4);
                }
            }
            mnDiagram2_ClearDetailView(mnDiagram3_804D6C20);
            mnDiagram3_80245BA4(mnDiagram3_804D6C20);
            return;
        }
    }

    /* D-pad down */
    if (buttons & 2) {
        u8 limit = (data->x6 != 0) ? 0x18 : 0x15;
        u8 maxX1 = (data->x4 + 10 < limit) ? 9 : (limit - 1 - data->x4);
        if (data->x1 < maxX1) {
            lbAudioAx_80024030(2);
            data->x1++;
            jobj = data->x74->hsd_obj;
            {
                f32 f30 = mnDiagram3_JObjGetTranslationY(data->x2C) -
                          mnDiagram3_JObjGetTranslationY(data->x28);
                mnDiagram3_JObjSetTranslateX(
                    jobj, mnDiagram3_JObjGetTranslationX(data->x28));
                mnDiagram3_JObjSetTranslateY(
                    jobj, f30 * data->x1 +
                              mnDiagram3_JObjGetTranslationY(data->x28));
                mnDiagram3_JObjSetTranslateZ(
                    jobj, mnDiagram3_JObjGetTranslationZ(data->x28));
            }
            mnDiagram2_ClearDetailView(mnDiagram3_804D6C20);
            mnDiagram3_80245BA4(mnDiagram3_804D6C20);
            return;
        }
        if (data->x4 + 10 < limit) {
            lbAudioAx_80024030(2);
            data->x4++;
            for (i = 0; i < 10; i++) {
                if (data->x30[i] != NULL) {
                    HSD_SisLib_803A5CC4(data->x30[i]);
                    data->x30[i] = NULL;
                }
            }
            {
                HSD_JObj* jobj28 = data->x28;
                HSD_JObj* jobj2C = data->x2C;
                u8 x4 = data->x4;
                f32 f30;
                f32 f31;
                Diagram3Data* ptr = data;

                if (jobj28 == NULL) {
                    __assert(mnDiagram3_804D4FD8, 0x3EE, mnDiagram3_804D4FE0);
                }
                if (jobj2C == NULL) {
                    __assert(mnDiagram3_804D4FD8, 0x3EE, mnDiagram3_804D4FE0);
                }
                f30 = jobj2C->translate.y - jobj28->translate.y;
                lb_8000B1CC(jobj28, (Vec3*) &table[0x18], (Vec3*) pos);
                f31 = mnDiagram3_804DBFF8;
                for (i = 0; i < 10; i++) {
                    HSD_Text* text;
                    u8 threshold = (data->x6 != 0) ? 0x18 : 0x15;
                    u8 idx;
                    s32 sum = x4 + i;
                    if (sum >= threshold) {
                        idx = sum - threshold;
                    } else {
                        idx = sum;
                    }
                    text = HSD_SisLib_803A5ACC(
                        0, 1, pos[0] - f31, -f30 * (f32) i + -pos[1], pos[2],
                        f31, mnDiagram3_804DBFFC);
                    ptr->x30[0] = text;
                    HSD_SisLib_803A6368(text, mnDiagram3_803EEC4C[idx]);
                    ptr = (Diagram3Data*) ((u8*) ptr + 4);
                }
            }
            mnDiagram2_ClearDetailView(mnDiagram3_804D6C20);
            mnDiagram3_80245BA4(mnDiagram3_804D6C20);
            return;
        }
    }

    /* A button - select */
    if (buttons & 0x100) {
        u8 threshold = (data->x6 != 0) ? 0x18 : 0x15;
        u8 idx;
        s32 sum = data->x4 + data->x1;
        if (sum >= threshold) {
            idx = sum - threshold;
        } else {
            idx = sum;
        }
        lbAudioAx_80024030(0);
        {
            u8 x6 = data->x6;
            GameRules* rules = gmMainLib_8015CC34();
            rules->xD = x6;
        }
        mnDiagram2_ClearDetailView(mnDiagram3_804D6C20);
        HSD_GObjPLink_80390228(data->x74);
        for (i = 0; i < 10; i++) {
            if (data->x30[i] != NULL) {
                HSD_SisLib_803A5CC4(data->x30[i]);
                data->x30[i] = NULL;
            }
        }
        HSD_GObjPLink_80390228(gobj);
        mnDiagram_Init(1, idx);
    }
}
