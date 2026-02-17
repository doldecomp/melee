#include "mndiagram3.h"

#include "mndiagram3.static.h"

#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjplink.h>
#include <baselib/gobjproc.h>
#include <baselib/gobjuserdata.h>
#include <baselib/jobj.h>
#include <baselib/memory.h>
#include <baselib/sislib.h>
#include <melee/ft/ft_0C31.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lb_00F9.h>
#include <melee/mn/mndiagram.h>
#include <melee/mn/mndiagram2.h>
#include <melee/mn/mnmain.h>
#include <melee/mn/mnname.h>

void mnDiagram3_80245BA4(HSD_GObj* gobj)
{
    Vec3 sp6C;
    u8 sp58[0x14];
    u8 sp48[0x10];
    u8 sp38[0x10];
    u8 sp28[0x10];
    Diagram3* data;
    char* base;
    u16* table;
    HSD_JObj* row0;
    HSD_JObj* row1;
    f32 neg_spacing;
    f32 row_spacing;
    f32 divider;
    f32 icon_x_offset;
    u8 stat_type;
    int i;
    HSD_Text* title_text;
    HSD_Text* value_text;
    HSD_JObj* icon;
    u8 entity;
    u32 max_distance;
    u32 max_time;
    u32 max_percentage;
    PAD_STACK(8);

    data = gobj->user_data;
    base = (char*) &mnDiagram3_803EEC10;

    {
        u8 is_name_mode = data->is_name_mode;
        u8 scroll = data->saved_selection;
        u8 offset = data->scroll_offset;
        u8 limit;

        if (is_name_mode != 0) {
            limit = 0x18;
        } else {
            limit = 0x15;
        }

        {
            int val = offset + scroll;
            if (val >= limit) {
                val = val - limit;
            } else {
                val = (u8) val;
            }
            row0 = data->jobjs[6];
            stat_type = (u8) val;
        }
    }
    ((row0) ? ((void) 0)
            : __assert(mnDiagram3_804D4FD8, 0x3EE, mnDiagram3_804D4FE0));

    row1 = data->jobjs[7];
    {
        f32 row0_y = row0->translate.y;
        ((row1) ? ((void) 0)
                : __assert(mnDiagram3_804D4FD8, 0x3EE, mnDiagram3_804D4FE0));

        {
            u16* stat_table;
            stat_table = (u16*) (base + ((int) stat_type << 1));
            icon_x_offset = mnDiagram3_804DC010;
            row_spacing = row1->translate.y - row0_y;
            max_distance = 0x5F5E0FF;
            max_percentage = 0x98967F;
            divider = mnDiagram3_804DC008;
            max_time = 0x5C8D7F;
            neg_spacing = -row_spacing;
            stat_table += 0x36;

            for (i = 0; i < 5; i++) {
                if (data->is_name_mode != 0) {
                    if (!mnDiagram2_IsIconOnlyStat(stat_type)) {
                        if (i == 0) {
                            lb_8000B1CC(data->jobjs[6], (Vec3*) (base + 0x24),
                                        &sp6C);
                            title_text = HSD_SisLib_803A6754(0, 1);
                            data->title_text = title_text;
                            title_text->font_size.x = divider;
                            title_text->font_size.y = divider;
                            {
                                f32 y = sp6C.y;
                                f32 z = sp6C.z;
                                title_text->pos_x = sp6C.x;
                                title_text->pos_y = -y;
                                title_text->pos_z = z;
                            }
                        }

                        entity = mnDiagram2_GetRankedName(stat_type, (u8) i);
                        if (entity == 0x78) {
                            goto next;
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
                    entity = mnDiagram2_GetRankedFighter(stat_type, (u8) i);
                    icon = mnDiagram_80242B38(entity, 0);
                    if (icon == NULL) {
                        __assert(mnDiagram3_804D4FD8, 0x3B3,
                                 mnDiagram3_804D4FE0);
                    }
                    icon->translate.y = row_spacing * (f32) i;
                    if (!(icon->flags & (1 << 25))) {
                        HSD_JObjSetMtxDirty(icon);
                    }
                    HSD_JObjAddChild(data->jobjs[6], icon);
                }

                if (i == 0) {
                    lb_8000B1CC(data->jobjs[6], (Vec3*) (base + 0x30), &sp6C);
                    value_text = HSD_SisLib_803A6754(0, 1);
                    data->value_text = value_text;
                    value_text->font_size.x = divider;
                    value_text->font_size.y = divider;
                    {
                        f32 y = sp6C.y;
                        f32 z = sp6C.z;
                        value_text->pos_x = sp6C.x;
                        value_text->pos_y = -y;
                        value_text->pos_z = z;
                    }
                    value_text->default_alignment = 2;
                    value_text->text_color = mn_804D4B64;
                }

                if (mnDiagram2_IsIconOnlyStat(stat_type)) {
                    mnDiagram2_GetAggregatedFighterRank(sp48, stat_type,
                                                        (u8) i);
                    if (sp48[0] == 0x19) {
                        goto next;
                    }
                    mnDiagram2_GetAggregatedFighterRank(sp38, stat_type,
                                                        (u8) i);
                    icon = mnDiagram_80242B38(sp38[0], 0);
                    if (icon == NULL) {
                        __assert(mnDiagram3_804D4FD8, 0x3B3,
                                 mnDiagram3_804D4FE0);
                    }
                    icon->translate.y = row_spacing * (f32) i;
                    if (!(icon->flags & (1 << 25))) {
                        HSD_JObjSetMtxDirty(icon);
                    }
                    HSD_JObjAddChild(data->jobjs[6], icon);

                    mnDiagram2_GetAggregatedFighterRank(sp28, stat_type,
                                                        (u8) i);
                    {
                        int val = *(int*) (sp28 + 0xC);
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
                        goto next;
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
                    u16 icon_id = *stat_table;
                    int r17 = icon_id;
                    if ((u32) icon_id == 0xFFFF) {
                        goto next;
                    }

                    lb_8000B1CC(data->jobjs[6], (Vec3*) (base + 0x30), &sp6C);
                    {
                        HSD_Text* icon_text;
                        f32 negated_y = -sp6C.y;
                        icon_text = HSD_SisLib_803A5ACC(
                            0, 1, icon_x_offset + sp6C.x,
                            neg_spacing * (f32) i + negated_y, sp6C.z,
                            mnDiagram3_804DC014, mnDiagram3_804DC014);
                        data->row_icons[i] = icon_text;
                        icon_text->default_alignment = 1;
                        icon_text->text_color = mn_804D4B64;

                        if (mnDiagram2_IsDistanceStat(stat_type)) {
                            u32 stat_val = mnDiagram2_GetStatValue(
                                data->is_name_mode, stat_type, entity);
                            if (mnDiagram_IsDistanceOverflow(stat_val)) {
                                HSD_SisLib_803A6368(icon_text, 0x7F);
                                goto next;
                            }
                        }
                        HSD_SisLib_803A6368(icon_text, r17);
                    }
                }

            next:
                (void) 0;
            }
        }
    }
}

void mnDiagram3_80246D40(HSD_GObj* gobj)
{
    Diagram3* data;
    HSD_JObj* jobj;
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
        HSD_JObjClearFlagsAll(jobj, 0x10);
    } else {
        HSD_JObjSetFlagsAll(jobj, 0x10);
    }

    jobj = data->jobjs[4];
    mn_8022ED6C(jobj, &mnDiagram3_803EEC1C);

    if (data->scroll_offset != 0) {
        HSD_JObjClearFlagsAll(jobj, 0x10);
    } else {
        HSD_JObjSetFlagsAll(jobj, 0x10);
    }
}

void fn_80246E04(HSD_GObj* gobj)
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

void fn_80246E64(HSD_GObj* gobj)
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
            proc = HSD_GObjProc_8038FD54(gobj, fn_80246E04, 0);
            proc->flags_3 = HSD_GObj_804D783C;
            HSD_JObjSetFlagsAll(data->jobjs[2], 0x10);
        }
    } else {
        mnDiagram3_80246D40(gobj);
    }
}

void fn_80246F0C(void* arg0)
{
    HSD_Free(arg0);
}

void mnDiagram3_80246F2C(Diagram3* data, int arg1)
{
    u8* src;
    int i;
    PAD_STACK(8);

    src = (u8*) &mn_804A04F0;
    data->saved_menu = src[0];
    data->saved_selection = (u8) * (u16*) (src + 2);
    data->anim_state = 1;
    data->scroll_offset = 0;
    data->is_name_mode = gmMainLib_8015CC34()->xD;

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

void mnDiagram3_80247008(int arg0)
{
    char* base = (char*) &mnDiagram3_803EEC10;
    mnDiagram_ArchiveData* archive = &mnDiagram_804A0844;
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    Diagram3* data;
    int i;

    gobj = GObj_Create(6, 7, 0x80);
    mnDiagram3_804D6C20 = gobj;
    jobj = HSD_JObjLoadJoint(archive->x0);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 6, 0x80);
    HSD_JObjAddAnimAll(jobj, archive->x4, archive->x8, archive->xC);
    HSD_JObjReqAnimAll(jobj, mnDiagram3_804DC00C);
    HSD_JObjAnimAll(jobj);

    data = (Diagram3*) HSD_MemAlloc(0x78);
    if (data == NULL) {
        OSReport(base + 0x9C);
        __assert(base + 0xB4, 0x3FC, base + 0xC4);
    }
    mnDiagram3_80246F2C(data, arg0);
    GObj_InitUserData(gobj, 0, (void (*)(void*)) fn_80246F0C, data);

    for (i = 0; i < 10; i++) {
        lb_80011E24(jobj, (HSD_JObj**) ((u8*) data + (i << 2) + 8), i, -1);
    }

    HSD_GObjProc_8038FD54(gobj, fn_80246E64, 0);
}

void mnDiagram3_8024714C(void* arg0)
{
    Vec3 sp48;
    Diagram3* data;
    HSD_GObj* gobj;
    HSD_JObj* row0;
    HSD_JObj* row1;
    mnDiagram_ArchiveData* archive;
    f32 row_spacing;
    f32 neg_spacing;
    int i;
    PAD_STACK(56);

    {
        MenuFlow* flow = &mn_804A04F0;
        flow->x10 = 2;
        flow->hovered_selection = 0;
    }

    mnDiagram3_80247008((int) arg0);

    gobj = mnDiagram3_804D6C20;
    archive = &mnDiagram_804A0854;
    data = gobj->user_data;

    {
        HSD_GObj* popup;
        HSD_JObj* popup_jobj;

        popup = GObj_Create(6, 7, 0x80);
        data->popup_gobj = popup;
        popup_jobj = HSD_JObjLoadJoint(archive->x0);
        HSD_GObjObject_80390A70(popup, HSD_GObj_804D7849, popup_jobj);
        GObj_SetupGXLink(popup, HSD_GObj_JObjCallback, 4, 0x80);
        HSD_JObjAddAnimAll(popup_jobj, archive->x4, archive->x8, archive->xC);
        HSD_JObjReqAnimAll(popup_jobj, mnDiagram3_804DC00C);
        HSD_JObjAnimAll(popup_jobj);

        data = gobj->user_data;
        row0 = data->jobjs[8];
        ((row0) ? ((void) 0)
                : __assert(mnDiagram3_804D4FD8, 0x3EE, mnDiagram3_804D4FE0));

        row1 = data->jobjs[9];
        row_spacing = row0->translate.y;
        ((row1) ? ((void) 0)
                : __assert(mnDiagram3_804D4FD8, 0x3EE, mnDiagram3_804D4FE0));
        row_spacing = row1->translate.y - row_spacing;

        row0 = data->jobjs[8];
        ((row0) ? ((void) 0)
                : __assert(mnDiagram3_804D4FD8, 0x3E1, mnDiagram3_804D4FE0));
        {
            f32 tx = row0->translate.x;
            ((popup_jobj)
                 ? ((void) 0)
                 : __assert(mnDiagram3_804D4FD8, 0x3A4, mnDiagram3_804D4FE0));
            popup_jobj->translate.x = tx;
        }
        if (!(popup_jobj->flags & 0x02000000)) {
            ftCo_800C6AFC(popup_jobj);
        }

        row0 = data->jobjs[8];
        ((row0) ? ((void) 0)
                : __assert(mnDiagram3_804D4FD8, 0x3EE, mnDiagram3_804D4FE0));
        {
            f32 ty = row_spacing * mnDiagram3_804DC00C + row0->translate.y;
            ((popup_jobj)
                 ? ((void) 0)
                 : __assert(mnDiagram3_804D4FD8, 0x3B3, mnDiagram3_804D4FE0));
            popup_jobj->translate.y = ty;
        }
        if (!(popup_jobj->flags & 0x02000000)) {
            ftCo_800C6AFC(popup_jobj);
        }

        row0 = data->jobjs[8];
        ((row0) ? ((void) 0)
                : __assert(mnDiagram3_804D4FD8, 0x3FB, mnDiagram3_804D4FE0));
        {
            f32 tz = row0->translate.z;
            ((popup_jobj)
                 ? ((void) 0)
                 : __assert(mnDiagram3_804D4FD8, 0x3C2, mnDiagram3_804D4FE0));
            popup_jobj->translate.z = tz;
        }
        if (!(popup_jobj->flags & 0x02000000)) {
            ftCo_800C6AFC(popup_jobj);
        }
    }

    {
        Diagram3* d;
        u8 scroll;
        u8 stat_idx;
        u16* base;

        gobj = mnDiagram3_804D6C20;
        d = gobj->user_data;
        row0 = d->jobjs[8];
        scroll = d->scroll_offset;
        ((row0) ? ((void) 0)
                : __assert(mnDiagram3_804D4FD8, 0x3EE, mnDiagram3_804D4FE0));

        row1 = d->jobjs[9];
        row_spacing = row0->translate.y;
        ((row1) ? ((void) 0)
                : __assert(mnDiagram3_804D4FD8, 0x3EE, mnDiagram3_804D4FE0));
        row_spacing = row1->translate.y - row_spacing;

        lb_8000B1CC(d->jobjs[8], (Vec3*) &mnDiagram3_803EEC28, &sp48);

        neg_spacing = -row_spacing;
        base = (u16*) &mnDiagram3_803EEC4C;
        row_spacing = mnDiagram3_804DBFF8;
        stat_idx = scroll;
        i = 0;

        do {
            f32 fi = (f32) i;
            HSD_Text* text = HSD_SisLib_803A5ACC(
                0, 1, sp48.x - row_spacing, neg_spacing * fi + -sp48.y, sp48.z,
                mnDiagram3_804DBFFC, mnDiagram3_804DBFFC);

            d->row_labels[i] = text;
            {
                u8 type_idx = (u8) i;
                int val;
                u8 limit;

                if (d->is_name_mode != 0) {
                    limit = 0x18;
                } else {
                    limit = 0x15;
                }

                val = stat_idx + type_idx;
                if (val >= (u8) limit) {
                    val = val - (u8) limit;
                } else {
                    val = (u8) val;
                }

                {
                    u16* entry = &base[(u8) val];
                    HSD_SisLib_803A6368(text, *entry);
                }
            }
            i++;
        } while (i < 10);
    }

    mnDiagram3_80245BA4(mnDiagram3_804D6C20);

    {
        HSD_GObjProc* proc;
        proc = HSD_GObjProc_8038FD54(GObj_Create(0, 1, 0x80), fn_802461BC, 0);
        proc->flags_3 = HSD_GObj_804D783C;
    }
}
