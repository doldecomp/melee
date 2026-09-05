#include "mndiagram3.h"

#include <sysdolphin/baselib/debug.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/gobjplink.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/gobjuserdata.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/memory.h>
#include <sysdolphin/baselib/sislib.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lbspdisplay.h>
#include "inlines.h"
#include "mndiagram.h"
#include "mndiagram2.h"
#include "mnmain.h"
#include "mnname.h"
#include "types.h"

typedef struct mnDiagram3_PosTable {
    /* 0x00 */ Vec3 x0;  ///< title_pos (3.3,0.5,0)
    /* 0x0C */ Vec3 xC;  ///< rank_name_pos (-2,0.57,0)
    /* 0x18 */ Vec3 x18; ///< value_pos (8,0.57,0)
} mnDiagram3_PosTable;

typedef struct mnDiagram3_StatTable {
    /* 0x00 */ u16 label_ids[24];      ///< SIS string ids, 0x62..0x79
    /* 0x30 */ u16 unit_glyph_ids[24]; ///< mnDiagram2 unit/icon column entries
} mnDiagram3_StatTable;

typedef struct mnDiagram3_DataTable {
    /* 0x00 */ AnimLoopSettings x0;
    /* 0x0C */ AnimLoopSettings xC;
    /* 0x18 */ mnDiagram3_PosTable positions;
    /* 0x3C */ mnDiagram3_StatTable stats;
} mnDiagram3_DataTable;

/* 3EEC10 */ extern AnimLoopSettings mnDiagram3_803EEC10;
/* 3EEC1C */ extern AnimLoopSettings mnDiagram3_803EEC1C;
/* 3EEC28 */ extern mnDiagram3_PosTable mnDiagram3_803EEC28;
/* 3EEC4C */ extern mnDiagram3_StatTable mnDiagram3_803EEC4C;
/* 4D6C20 */ extern HSD_GObj* mnDiagram3_804D6C20;
/* 4D6C24 */ extern HSD_GObj* mnDiagram3_804D6C24;
/* 4D4B64 */ extern GXColor mn_804D4B64;
/* 4DC008 */ extern const f32 mnDiagram3_804DC008;
/* 4DC00C */ extern const f32 mnDiagram3_804DC00C;
/* 4DC010 */ extern const f32 mnDiagram3_804DC010;
/* 4DC014 */ extern const f32 mnDiagram3_804DC014;
/* 2461BC */ void mnDiagram3_HandleInput(HSD_GObj* gobj);

#ifdef MUST_MATCH
static void sdata2_order(void)
{
    (void) U32_TO_F32;
    (void) 6.5f;
    (void) 240.0f;
    (void) S32_TO_F32;
}
#endif

HSD_GObj* mnDiagram3_804D6C20;

void mnDiagram3_PopulateRankings(HSD_GObj* gobj)
{
    u16* unit_glyph_ids;
    u32 max_time;
    u8 sp58[0x10];
    u8 sp48[0x10];
    u8 fighter_rank[0x10];
    union {
        u8 bytes[0x10];
        struct {
            u8 x0;
            u8 pad_x1[7];
            s32 x8;
            s32 xC;
        } fields;
    } sp28;
    Diagram3* data;
    mnDiagram3_DataTable* table;
    HSD_JObj* row0;
    f32 neg_spacing;
    f32 row_spacing;
    f32 divider;
    f32 icon_x_offset;
    float new_var;
    u8 stat_type;
    u8 aggregate_rank;
    int i;
    HSD_Text* title_text;
    HSD_Text* value_text;
    HSD_JObj* icon;
    s32 entity;
    Vec3 position;
    u32 max_percentage;

    // Keep the stack frame aligned with the original local workspace.
    PAD_STACK(8);

    data = gobj->user_data;
    table = (mnDiagram3_DataTable*) &mnDiagram3_803EEC10;

    {
        u8 offset;
        u8 scroll;
        u8 limit;

        scroll = data->cursor_row;
        offset = data->scroll_offset;
        limit = (data->is_name_mode != 0) ? 0x18 : 0x15;

        {
            int sum = offset + scroll;
            int val = sum;
            if (val >= limit) {
                val = val - limit;
            } else {
                val = (u8) val;
            }
            row0 = data->jobjs[6];
            stat_type = (u8) val;
        }
    }

    {
        divider = HSD_JObjGetTranslationY(row0);
        row_spacing = HSD_JObjGetTranslationY(data->jobjs[7]);

        {
            u32 max_distance;

            unit_glyph_ids = table->stats.unit_glyph_ids;
            icon_x_offset = mnDiagram3_804DC010;
            (void) row_spacing;
            row_spacing = row_spacing - divider;
            max_distance = 0x5F5E0FF;
            max_percentage = 0x98967F;
            divider = mnDiagram3_804DC008;
            max_time = 0x5B8D7F;
            neg_spacing = -row_spacing;

            for (i = 0; i < 5; i++) {
                {
                    if (data->is_name_mode != 0) {
                        if (!mnDiagram2_IsIconOnlyStat(stat_type)) {
                            if (i == 0) {
                                lb_8000B1CC(data->jobjs[6],
                                            &table->positions.xC, &position);
                                title_text = HSD_SisLib_803A6754(0, 1);
                                data->title_text = title_text;
                                title_text->font_size.x = divider;
                                title_text->font_size.y = divider;
                                {
                                    f32 y = position.y;
                                    f32 z = position.z;
                                    title_text->pos_x = position.x;
                                    title_text->pos_y = (new_var = -y);
                                    title_text->pos_z = z;
                                }
                            }

                            entity =
                                mnDiagram2_GetRankedName(stat_type, (u8) i);
                            if (entity == 0x78) {
                                continue;
                            }
                            {
                                char* name_str = GetNameText(entity);
                                f32 f1 = mnDiagram3_804DC00C;
                                f32 offset_y = neg_spacing * (f32) i / divider;
                                HSD_SisLib_803A6B98(title_text, f1, offset_y,
                                                    name_str);
                            }
                        }
                    } else {
                        entity =
                            mnDiagram2_GetRankedFighter(stat_type, (u8) i);
                        icon = mnDiagram_CreateFighterIcon(entity, 0);
                        HSD_JObjSetTranslateY(icon, row_spacing * (f32) i);
                        HSD_JObjAddChild(data->jobjs[6], icon);
                    }
                }

                if (i == 0) {
                    lb_8000B1CC(data->jobjs[6], &table->positions.x18,
                                &position);
                    value_text = HSD_SisLib_803A6754(0, 1);
                    data->value_text = value_text;
                    value_text->font_size.x = divider;
                    value_text->font_size.y = divider;
                    {
                        f32 y = position.y;
                        f32 z = position.z;
                        value_text->pos_x = position.x;
                        value_text->pos_y = (new_var = -y);
                        value_text->pos_z = z;
                    }
                    value_text->default_alignment = 2;
                    value_text->text_color = mn_804D4B64;
                }

                if (mnDiagram2_IsIconOnlyStat(stat_type) &&
                    (aggregate_rank = (u8) i,
                     mnDiagram2_GetAggregatedFighterRank(sp48, stat_type,
                                                         aggregate_rank),
                     sp48[0] != 0x19))
                {
                    {
                        u8 rank = (u16) i;
                        mnDiagram2_GetAggregatedFighterRank(fighter_rank,
                                                            stat_type, rank);
                    }
                    icon = mnDiagram_CreateFighterIcon(fighter_rank[0], 0);
                    HSD_JObjSetTranslateY(icon, row_spacing * (f32) i);
                    HSD_JObjAddChild(data->jobjs[6], icon);

                    {
                        u8 rank = (u8) i;
                        mnDiagram2_GetAggregatedFighterRank(sp28.bytes,
                                                            stat_type, rank);
                    }
                    {
                        int val = sp28.fields.xC;
                        mnDiagram_FormatDecimalNumber((char*) sp58, val, 0);
                    }
                    {
                        f32 f1 = mnDiagram3_804DC00C;
                        f32 offset_y = neg_spacing * (f32) i / divider;
                        HSD_SisLib_803A6B98(value_text, f1, offset_y,
                                            (char*) sp58);
                    }
                } else {
                    if (mnDiagram2_IsTimeStat(stat_type)) {
                        int val = mnDiagram2_GetStatValue(data->is_name_mode,
                                                          stat_type, entity);
                        if ((u32) val > max_time) {
                            val = max_time;
                        }
                        mnDiagram_FormatTime((char*) sp58, val);
                    } else if (mnDiagram2_IsDistanceStat(stat_type)) {
                        u32 val = mnDiagram2_GetStatValue(data->is_name_mode,
                                                          stat_type, entity);
                        val = mnDiagram_ConvertDistanceForDisplay(val);
                        if (val > max_distance) {
                            val = max_distance;
                        }
                        mnDiagram_IntToStr((char*) sp58, val);
                    } else if (mnDiagram2_IsPercentageStat(stat_type)) {
                        u32 val = mnDiagram2_GetStatValue(data->is_name_mode,
                                                          stat_type, entity);
                        if (val > max_percentage) {
                            val = max_percentage;
                        }
                        mnDiagram_FormatDecimalNumber((char*) sp58, val, 2);
                    } else if (mnDiagram2_IsIconOnlyStat(stat_type)) {
                        continue;
                    } else {
                        u32 val = mnDiagram2_GetStatValue(data->is_name_mode,
                                                          stat_type, entity);
                        if (val > max_distance) {
                            val = max_distance;
                        }
                        mnDiagram_FormatDecimalNumber((char*) sp58, val, 0);
                    }

                    {
                        f32 f1 = mnDiagram3_804DC00C;
                        f32 offset_y = neg_spacing * (f32) i / divider;
                        HSD_SisLib_803A6B98(value_text, f1, offset_y,
                                            (char*) sp58);
                    }
                }

                {
                    int icon_id = unit_glyph_ids[stat_type];
                    if (icon_id == 0xFFFF) {
                        continue;
                    }

                    lb_8000B1CC(data->jobjs[6], &table->positions.x18,
                                &position);
                    {
                        HSD_Text* icon_text;
                        f32 negated_y = -position.y;
                        icon_text = HSD_SisLib_803A5ACC(
                            0, 1, icon_x_offset + position.x,
                            neg_spacing * (f32) i + negated_y, position.z,
                            mnDiagram3_804DC014, mnDiagram3_804DC014);
                        data->row_icons[i] = icon_text;
                        icon_text->default_alignment = 1;
                        icon_text->text_color = mn_804D4B64;

                        if (mnDiagram2_IsDistanceStat(stat_type)) {
                            if (mnDiagram_IsDistanceOverflow(
                                    mnDiagram2_GetStatValue(data->is_name_mode,
                                                            stat_type,
                                                            entity)))
                            {
                                HSD_SisLib_803A6368(icon_text, 0x7F);
                                continue;
                            }
                        }
                        HSD_SisLib_803A6368(icon_text, icon_id);
                    }
                }
            }
        }
    }
}

AnimLoopSettings mnDiagram3_803EEC10 = { 10.0F, 19.0F, -0.1F };
AnimLoopSettings mnDiagram3_803EEC1C = { 0.0F, 199.0F, 0.0F };

mnDiagram3_PosTable mnDiagram3_803EEC28 = {
    { 3.3F, 0.5F, 0.0F },
    { -2.0F, 0.57F, 0.0F },
    { 8.0F, 0.57F, 0.0F },
};

mnDiagram3_StatTable mnDiagram3_803EEC4C = {
    { 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D,
      0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79 },
    { 0x7A, 0x7A, 0x7A, 0x7C, 0x7C, 0x7C, 0x7C, 0x7C, 0x7A, 0x7A, 0x7A, 0xFFFF,
      0x7C, 0x7B, 0x7E, 0x7E, 0x7E, 0x7E, 0x7D, 0x7D, 0x7D, 0x7B, 0x7B, 0x7B },
};

void mnDiagram3_UpdateScrollArrows(HSD_GObj* gobj)
{
    Diagram3* data;
    HSD_JObj* jobj;
    HSD_JObj* new_var;

    int limit;

    data = gobj->user_data;

    jobj = data->jobjs[3];
    mn_8022ED6C(jobj, &mnDiagram3_803EEC1C);

    if (data->is_name_mode != 0) {
        limit = 0x18;
    } else {
        limit = 0x15;
    }

    if (data->scroll_offset + 10 < limit) {
        HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
    } else {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
    }
    jobj = data->jobjs[4];
    new_var = jobj;
    mn_8022ED6C(new_var, &mnDiagram3_803EEC1C);

    if (data->scroll_offset != 0) {
        HSD_JObjClearFlagsAll(new_var, JOBJ_HIDDEN);
    } else {
        HSD_JObjSetFlagsAll(new_var, JOBJ_HIDDEN);
    }
}

void mnDiagram3_OnAnimComplete(HSD_GObj* gobj)
{
    Diagram3* data;
    HSD_JObj* jobj;
    AnimLoopSettings* table;
    int pad;

    data = gobj->user_data;
    jobj = data->jobjs[1];
    table = &mnDiagram3_803EEC10;
    pad = 0;
    if (mn_8022ED6C(jobj, table) >= table->end_frame) {
        HSD_GObjPLink_80390228(gobj);
    }
}

void mnDiagram3_Think(HSD_GObj* gobj)
{
    Diagram3* data;
    u8* src;
    u8 mode;
    PAD_STACK(8);

    src = (u8*) &mn_804A04F0;
    data = gobj->user_data;
    mode = src[0];
    if (mode != 0x1E || src[0x10] != 2) {
        if (mode == 0x1E) {
            HSD_GObjPLink_80390228(gobj);
        } else {
            HSD_GObjProc* proc;

            HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
            proc = HSD_GObj_SetupProc(gobj, mnDiagram3_OnAnimComplete, 0);
            proc->flags_3 = HSD_GObj_804D783C;
            HSD_JObjSetFlagsAll(data->jobjs[2], JOBJ_HIDDEN);
        }
    } else {
        mnDiagram3_UpdateScrollArrows(gobj);
    }
}

void mnDiagram3_FreeUserData(void* arg0)
{
    HSD_Free(arg0);
}

void mnDiagram3_InitUserData(Diagram3* data, int arg1)
{
    u8* src;
    int i;
    PAD_STACK(8);

    src = (u8*) &mn_804A04F0;
    data->saved_menu = src[0];
    data->cursor_row = (u8) * (u16*) (src + 2);
    data->anim_state = 1;
    data->scroll_offset = 0;
    data->is_name_mode = gmMainLib_GetGameRules()->xD;

    for (i = 0; i < 10; i++) {
        data->row_labels[i] = NULL;
    }

    data->popup_gobj = NULL;
    data->title_text = NULL;
    data->value_text = NULL;
    data->row_icons[0] = NULL;
    data->row_icons[1] = NULL;
    data->row_icons[2] = NULL;
    data->row_icons[3] = NULL;
    data->row_icons[4] = NULL;
}

static inline HSD_JObj* mnDiagram3_LoadJoint(mnDiagram_ArchiveData* archive)
{
    return HSD_JObjLoadJoint(archive->x0);
}

void mnDiagram3_Create(int arg0)
{
    mnDiagram_ArchiveData* archive = &mnDiagram_804A0844;
    register HSD_GObj* gobj;
    HSD_JObj* jobj;
    Diagram3* user_data;
    int i;

    gobj = GObj_Create(6, 7, 0x80);
    mnDiagram3_804D6C20 = gobj;
    jobj = mnDiagram3_LoadJoint(archive);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_JObjKind, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 6, 0x80);
    HSD_JObjAddAnimAll(jobj, archive->x4, archive->x8, archive->xC);
    HSD_JObjReqAnimAll(jobj, mnDiagram3_804DC00C);
    HSD_JObjAnimAll(jobj);

    user_data = (Diagram3*) HSD_MemAlloc(sizeof(Diagram3));
    HSD_ASSERTREPORT(0x3FC, user_data, "Can't get user_data.\n");
    mnDiagram3_InitUserData(user_data, arg0);
    GObj_InitUserData(gobj, 0, (void (*)(void*)) mnDiagram3_FreeUserData,
                      user_data);

    for (i = 0; i < 10; i++) {
        lb_80011E24(jobj, &user_data->jobjs[i], i, -1);
    }

    HSD_GObj_SetupProc(gobj, mnDiagram3_Think, 0);
}

static inline void mnDiagram3_SetupRows(HSD_JObj* jobj, Diagram3* popup_data,
                                        int count)
{
    f32 spacing;
    f32 row_spacing;
    int i;
    Vec3 pos;
    Diagram3* data;
    int scroll;
    u8 stat_idx;

    HSD_JObjSetTranslateZWithMtxDirty(
        jobj, HSD_JObjGetTranslationZ(popup_data->jobjs[8]));

    data = mnDiagram3_804D6C20->user_data;
    scroll = data->scroll_offset;

    spacing = HSD_JObjGetTranslationY(data->jobjs[9]) -
              HSD_JObjGetTranslationY(data->jobjs[8]);

    lb_8000B1CC(data->jobjs[8], &mnDiagram3_803EEC28.x0, &pos);

    row_spacing = 6.5f;
    i = 0;

    do {
        f32 fi = (f32) i;
        HSD_Text* text = HSD_SisLib_803A5ACC(0, 1, pos.x - row_spacing,
                                             -spacing * fi + -pos.y, pos.z,
                                             row_spacing, 240.0f);

        data->row_labels[i] = text;
        {
            u8 type_idx = (u8) i;
            int val;
            int limit;

            if (data->is_name_mode != 0) {
                limit = 0x18;
            } else {
                limit = 0x15;
            }
            limit = (u8) limit;

            /// @remark Matching tactic: the self-assign keeps type_idx live
            /// for MWCC register allocation.
#ifdef MUST_MATCH
            val = (stat_idx = (u8) scroll) + (type_idx = type_idx);
#else
            val = (stat_idx = (u8) scroll) + type_idx;
#endif
            if (val >= limit) {
                limit = val - limit;
            } else {
                limit = (u8) val;
            }

            {
                u16* entry = &mnDiagram3_803EEC4C.label_ids[(u8) limit];
                HSD_SisLib_803A6368(text, *entry);
            }
        }
        i++;
    } while (i < count);
}

static inline f32 mnDiagram3_GetPopupSpacing(HSD_JObj* popup_row,
                                             Diagram3* data)
{
    return HSD_JObjGetTranslationY(data->jobjs[9]) -
           HSD_JObjGetTranslationY(popup_row);
}

static inline f32 mnDiagram3_GetPopupY(HSD_JObj* popup_row, f32 row_spacing)
{
    return row_spacing * mnDiagram3_804DC00C +
           HSD_JObjGetTranslationY(popup_row);
}

static inline HSD_JObj* mnDiagram3_CreatePopup(Diagram3* data,
                                               mnDiagram_ArchiveData* archive)
{
    HSD_GObj* popup;
    HSD_JObj* popup_jobj;

    popup = GObj_Create(6, 7, 0x80);
    data->popup_gobj = popup;
    popup_jobj = mnDiagram3_LoadJoint(archive);
    HSD_GObjObject_80390A70(popup, HSD_GObj_JObjKind, popup_jobj);
    GObj_SetupGXLink(popup, HSD_GObj_JObjCallback, 4, 0x80);
    HSD_JObjAddAnimAll(popup_jobj, archive->x4, archive->x8, archive->xC);
    HSD_JObjReqAnimAll(popup_jobj, mnDiagram3_804DC00C);
    HSD_JObjAnimAll(popup_jobj);
    return popup_jobj;
}

void mnDiagram3_Init(void* arg0)
{
    void* new_var;
    Diagram3* data;
    HSD_GObj* gobj;
    mnDiagram_ArchiveData* archive;
    f32 row_spacing;

    {
        MenuFlow* flow = &mn_804A04F0;
        /* MenuFlow.x10 is a shared per-menu sub-state slot reused across
         * screens (e.g. mnname.c uses 0/1/2 for a different input mode);
         * within the VS Records flow, 0 = grid, 1 = details, 2 = rankings. */
        flow->x10 = 2;
        flow->hovered_selection = 0;
    }

    mnDiagram3_Create((int) arg0);

    gobj = mnDiagram3_804D6C20;
    archive = &mnDiagram_804A0854;

    {
        HSD_JObj* popup_jobj;

        data = gobj->user_data;
        popup_jobj = mnDiagram3_CreatePopup(data, archive);

        new_var = gobj->user_data;
        data = new_var;
        row_spacing = mnDiagram3_GetPopupSpacing(data->jobjs[8], data);

        HSD_JObjSetTranslateXWithMtxDirty(
            popup_jobj, HSD_JObjGetTranslationX(data->jobjs[8]));

        row_spacing = mnDiagram3_GetPopupY(data->jobjs[8], row_spacing);
        HSD_JObjSetTranslateYWithMtxDirty(popup_jobj, row_spacing);

        mnDiagram3_SetupRows(popup_jobj, data, 10);
    }

    mnDiagram3_PopulateRankings(mnDiagram3_804D6C20);

    {
        HSD_GObjProc* proc;
        proc = HSD_GObj_SetupProc(GObj_Create(0, 1, 0x80),
                                  mnDiagram3_HandleInput, 0);
        proc->flags_3 = HSD_GObj_804D783C;
    }
}

static inline f32 mnDiagram3_GetRowSpacing(Diagram3* data)
{
    return HSD_JObjGetTranslationY(data->jobjs[9]) -
           HSD_JObjGetTranslationY(data->jobjs[8]);
}

static inline void mnDiagram3_ClearRowLabels(Diagram3* data)
{
    int i = 0;
    Diagram3* check_data = data;
    Diagram3* text_data = data;

    do {
        if (check_data->row_labels[i] != NULL) {
            HSD_SisLib_803A5CC4(text_data->row_labels[i]);
            check_data->row_labels[i] = NULL;
        }
    } while (++i < 10);
}

static inline void mnDiagram3_RebuildRowLabels(Diagram3* data, char* base,
                                               Vec3* pos, int count)
{
    f32 spacing;
    int i;
    int base_idx;
    int v;
    HSD_Text* text;
    u8 base_idx_u8;
    u8 i_u8;
    u8 limit;

    base_idx = data->scroll_offset;
    spacing = HSD_JObjGetTranslationY(data->jobjs[9]) -
              HSD_JObjGetTranslationY(data->jobjs[8]);
    lb_8000B1CC(data->jobjs[8], (Vec3*) (base + 0x18), pos);
    base_idx_u8 = base_idx;
    i = 0;
    do {
        text = HSD_SisLib_803A5ACC(0, 1, pos->x - 6.5f,
                                   -spacing * (f32) i + -pos->y, pos->z, 6.5f,
                                   240.0f);
        data->row_labels[i] = text;
        i_u8 = i;
        limit = (data->is_name_mode != 0) ? 0x18 : 0x15;
        v = base_idx_u8 + i_u8;
        if (v >= limit) {
            v -= limit;
        } else {
            v = (u8) v;
        }
        HSD_SisLib_803A6368(text, ((u16*) (base + 0x3C))[(u8) v]);
        i++;
    } while (i < count);
}

static inline void mnDiagram3_RefreshRankings(HSD_GObj* diagram_gobj)
{
    mnDiagram2_ClearDetailView(diagram_gobj);
    mnDiagram3_PopulateRankings(diagram_gobj);
}

void mnDiagram3_HandleInput(HSD_GObj* gobj)
{
    char* base = (char*) &mnDiagram3_803EEC10;
    Diagram3* data = mnDiagram3_804D6C20->user_data;
    u32 input = Menu_GetAllInputs();
    PAD_STACK(32);

    if (input & MenuInput_Back) {
        sfxBack();
        mn_804A04F0.entering_menu = 0;
        gmMainLib_GetGameRules()->xD =
            ((Diagram3*) mnDiagram3_804D6C20->user_data)->is_name_mode;
        mnDiagram2_ClearDetailView(mnDiagram3_804D6C20);
        HSD_GObjPLink_80390228(data->popup_gobj);
        data = mnDiagram3_804D6C20->user_data;
        mnDiagram3_ClearRowLabels(data);
        mn_80229894(0x1C, 0, 3);
        return;
    }
    if (input & (MenuInput_LTrigger | MenuInput_RTrigger)) {
        sfxForward();
        gmMainLib_GetGameRules()->xD =
            ((Diagram3*) mnDiagram3_804D6C20->user_data)->is_name_mode;
        mnDiagram2_ClearDetailView(mnDiagram3_804D6C20);
        HSD_GObjPLink_80390228(data->popup_gobj);
        data = mnDiagram3_804D6C20->user_data;
        mnDiagram3_ClearRowLabels(data);
        HSD_GObjPLink_80390228(gobj);
        if (input & MenuInput_LTrigger) {
            mnDiagram2_Init();
            return;
        }
        mnDiagram_Init(0, 0);
        return;
    }
    if (input & (MenuInput_XButton | MenuInput_YButton)) {
        Vec3 mode_label_pos;
        PAD_STACK(12);

        if (GetNameCount() == 0) {
            lbAudioAx_80024030(3);
            return;
        }
        sfxForward();
        data->is_name_mode = (data->is_name_mode == 0) ? 1 : 0;
        if ((data->is_name_mode == 0) &&
            ((s32) (data->scroll_offset + 0xA) >= 0x15))
        {
            data->scroll_offset = 0;
        }
        data = mnDiagram3_804D6C20->user_data;
        mnDiagram3_ClearRowLabels(data);
        data = mnDiagram3_804D6C20->user_data;
        mnDiagram3_RebuildRowLabels(data, base, &mode_label_pos, 10);
        mnDiagram3_RefreshRankings(mnDiagram3_804D6C20);
        return;
    }
    if (input & 1) {
        if (data->cursor_row != 0) {
            HSD_JObj* popup;
            Diagram3* cur;
            u8 n;
            f32 spacing;
            sfxMove();
            data->cursor_row = data->cursor_row - 1;
            popup = data->popup_gobj->hsd_obj;
            n = data->cursor_row;
            cur = mnDiagram3_804D6C20->user_data;
            spacing = mnDiagram3_GetRowSpacing(cur);
            HSD_JObjSetTranslateX(popup,
                                  HSD_JObjGetTranslationX(cur->jobjs[8]));
            HSD_JObjSetTranslateY(popup,
                                  spacing * (f32) n +
                                      HSD_JObjGetTranslationY(cur->jobjs[8]));
            HSD_JObjSetTranslateZ(popup,
                                  HSD_JObjGetTranslationZ(cur->jobjs[8]));
            mnDiagram3_RefreshRankings(mnDiagram3_804D6C20);
            return;
        }
        if (data->scroll_offset != 0) {
            Vec3 up_label_pos;
            PAD_STACK(8);

            sfxMove();
            data->scroll_offset = data->scroll_offset - 1;
            data = mnDiagram3_804D6C20->user_data;
            mnDiagram3_ClearRowLabels(data);
            data = mnDiagram3_804D6C20->user_data;
            mnDiagram3_RebuildRowLabels(data, base, &up_label_pos, 10);
            mnDiagram3_RefreshRankings(mnDiagram3_804D6C20);
        }
    } else if (input & 2) {
        u32 down_limit;
        if (data->cursor_row < 9) {
            HSD_JObj* popup;
            Diagram3* cur;
            u8 n;
            f32 spacing;
            sfxMove();
            data->cursor_row = data->cursor_row + 1;
            popup = data->popup_gobj->hsd_obj;
            n = data->cursor_row;
            cur = mnDiagram3_804D6C20->user_data;
            spacing = mnDiagram3_GetRowSpacing(cur);
            HSD_JObjSetTranslateX(popup,
                                  HSD_JObjGetTranslationX(cur->jobjs[8]));
            HSD_JObjSetTranslateY(popup,
                                  spacing * (f32) n +
                                      HSD_JObjGetTranslationY(cur->jobjs[8]));
            HSD_JObjSetTranslateZ(popup,
                                  HSD_JObjGetTranslationZ(cur->jobjs[8]));
            mnDiagram3_RefreshRankings(mnDiagram3_804D6C20);
            return;
        }
        down_limit = (data->is_name_mode != 0) ? 0x18 : 0x15;
        if ((u32) (data->scroll_offset + 0xA) < down_limit) {
            Vec3 down_label_pos;
            PAD_STACK(24);

            sfxMove();
            data->scroll_offset = data->scroll_offset + 1;
            data = mnDiagram3_804D6C20->user_data;
            mnDiagram3_ClearRowLabels(data);
            data = mnDiagram3_804D6C20->user_data;
            mnDiagram3_RebuildRowLabels(data, base, &down_label_pos, 10);
            mnDiagram3_RefreshRankings(mnDiagram3_804D6C20);
        }
    }
}

const f32 mnDiagram3_804DC008 = 0.035f;
const f32 mnDiagram3_804DC00C = 0.0f;
const f32 mnDiagram3_804DC010 = 1.5f;
const f32 mnDiagram3_804DC014 = 1.0f;
