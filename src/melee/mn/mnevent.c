#include "mnevent.h"

#include "db/db.h"
#include "gm/gm_1601.h"
#include "gm/gm_1BA8.h"
#include "gm/gmmain_lib.h"
#include "lb/lb_00F9.h"
#include "lb/lbarchive.h"
#include "lb/lbaudio_ax.h"
#include "mn/inlines.h"
#include "mn/mnmain.h"
#include "mn/types.h"

#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjplink.h>
#include <baselib/gobjproc.h>
#include <baselib/gobjuserdata.h>
#include <baselib/jobj.h>
#include <baselib/memory.h>
#include <baselib/sislib.h>

s32 mnEvent_8024CE74(void)
{
    int count = 0;
    int i;
    PAD_STACK(8);

    if (g_debugLevel > 2) {
        return 0x2A;
    }

    count = 0;
    for (i = 0; i < 0x33; i++) {
        if (gmMainLib_8015CEFC(i)) {
            count += 1;
        }
    }

    if (count <= 5) {
        return 1;
    }
    if (count <= 9) {
        return 6;
    }
    if (count <= 0xF) {
        return 0xB;
    }
    if (count <= 0x15) {
        return 0x10;
    }
    if (count <= 0x1A) {
        return 0x14;
    }
    if (count >= 0x32) {
        if (gm_80162EC8()) {
            return 0x2A;
        }
        return 0x29;
    }
    if (gm_80164840(0x14) && gm_80164840(7) && gm_80164840(0xF) &&
        gm_80164840(0x15))
    {
        if (gm_80164840(0xA) && gm_80164840(9) && gm_80164840(3) &&
            gm_80164840(0x18) && gm_80164840(0x19) && gm_80164840(0x16) &&
            gm_80164840(0x17))
        {
            return 0x29;
        }
        return 0x1E;
    }
    return 0x15;
}

static AnimLoopSettings mnEvent_803EF740 = { 0, 0, -0.1f };
static AnimLoopSettings mnEvent_803EF74C = { 0, 0, -0.1f };
static AnimLoopSettings mnEvent_803EF758 = { 0, 199.0f, 0 };

void mnEvent_8024D4E0(HSD_JObj* jobj, Vec3* translate)
{
    HSD_JObjSetTranslate(jobj, translate);
}

void fn_8024E1B4(HSD_GObj* gobj)
{
    int i;
    MnEventData* data = gobj->user_data;
    if (mn_8022EC18(gobj->hsd_obj, &mnEvent_803EF74C, 0x80) >=
        mnEvent_803EF74C.end_frame)
    {
        for (i = 0; i < 9; i++) {
            if (data->gobjs[i] != NULL) {
                HSD_GObjPLink_80390228(data->gobjs[i]);
                data->gobjs[i] = NULL;
            }
            if (data->texts[i] != NULL) {
                HSD_SisLib_803A5CC4(data->texts[i]);
                data->texts[i] = NULL;
            }
            if (data->icons[i] != NULL) {
                HSD_SisLib_803A5CC4(data->icons[i]);
                data->icons[i] = NULL;
            }
        }
        HSD_GObjPLink_80390228(gobj);
    }
}

void fn_8024E2A0(HSD_GObj* gobj)
{
    HSD_GObjProc* proc;
    HSD_JObj* jobj;
    HSD_JObj* tree;
    MnEventData* data = gobj->user_data;
    PAD_STACK(8);

    tree = gobj->hsd_obj;

    if (mn_804A04F0.cur_menu != 7) {
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        proc = HSD_GObj_SetupProc(gobj, fn_8024E1B4, 0);
        proc->flags_3 = HSD_GObj_804D783C;
        HSD_SisLib_803A5CC4(data->desc_text);
        HSD_SisLib_803A5CC4(data->name_text);
    } else {
        lb_80011E24(tree, &jobj, 1, -1);
        mn_8022ED6C(jobj, &mnEvent_803EF758);
    }
}

void fn_8024E34C(HSD_GObj* gobj)
{
    HSD_GObjProc* proc;
    HSD_JObj* tree = gobj->hsd_obj;
    MnEventData* data = gobj->user_data;
    PAD_STACK(16);

    if (mn_804A04F0.cur_menu != 7) {
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        proc = HSD_GObj_SetupProc(gobj, fn_8024E1B4, 0);
        proc->flags_3 = HSD_GObj_804D783C;
        HSD_SisLib_803A5CC4(data->desc_text);
        HSD_SisLib_803A5CC4(data->name_text);
    } else {
        float frame = mn_8022EC18(tree, &mnEvent_803EF740, 0x80);
        if (frame == mnEvent_803EF740.end_frame) {
            HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
            proc = HSD_GObj_SetupProc(gobj, fn_8024E2A0, 0);
            proc->flags_3 = HSD_GObj_804D783C;
        }
    }
}

void mnEvent_8024D014(HSD_GObj* gobj)
{
    HSD_JObj* jobj;
    MnEventData* data = gobj->user_data;
    HSD_JObj* tree = gobj->hsd_obj;
    PAD_STACK(8);

    lb_80011E24(tree, &jobj, 3, -1);
    if (data->first_event == 0) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
    } else {
        HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
    }

    lb_80011E24(tree, &jobj, 2, -1);
    if (data->first_event == mnEvent_8024CE74()) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
    } else {
        HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
    }
}

void mnEvent_8024D0CC(HSD_GObj* gobj, s32 event)
{
    HSD_JObj* tree = gobj->hsd_obj;
    HSD_JObj* jobj;
    f32 frame;
    FORCE_PAD_STACK_4;

    if (event == 0x21) {
        frame = 25.0f;
    } else {
        frame = gm_80164024(event);
    }

    lb_80011E24(tree, &jobj, 4, -1);
    HSD_JObjReqAnimAll(jobj, frame);
    HSD_JObjAnimAll(jobj);
}

void mnEvent_8024D7E0(HSD_GObj* gobj, s32 idx)
{
    MnEventData* data = gobj->user_data;
    HSD_Text* text;
    s32 sis_idx;
    PAD_STACK(8);

    if (data->desc_text != NULL) {
        HSD_SisLib_803A5CC4(data->desc_text);
    }

    sis_idx = (idx * 2) + 0x155;
    text =
        HSD_SisLib_803A5ACC(0, 1, -9.5f, 8.0f, 17.0f, 364.68332f, 38.38772f);
    data->desc_text = text;
    text->font_size.x = 0.0521f;
    text->font_size.y = 0.0521f;
    HSD_SisLib_803A6368(text, sis_idx);
}

void mnEvent_8024E420(MnEventData* data, s32 event_idx)
{
    s32 max_events;
    int i;

    max_events = mnEvent_8024CE74();

    if (event_idx < max_events) {
        data->first_event = event_idx;
        data->page = 0;
    } else {
        data->first_event = max_events;
        data->page = event_idx - max_events;
    }

    data->desc_text = NULL;
    data->name_text = NULL;

    for (i = 0; i < 9; i++) {
        data->gobjs[i] = NULL;
        data->texts[i] = NULL;
        data->icons[i] = NULL;
    }
}

void mnEvent_8024E838(int event_idx, int first_time)
{
    HSD_GObjProc* proc;
    void** arr = mnEvent_804A08F8;
    char* base = (char*) &mnEvent_803EF740;

    mn_804D6BC8.cooldown = 5;
    mn_804A04F0.prev_menu = mn_804A04F0.cur_menu;
    mn_804A04F0.cur_menu = 7;
    mn_804A04F0.hovered_selection = 0;
    mnEvent_804D6C65 = event_idx;

    if (first_time) {
        mnEvent_804D6C64 = 0x14;
    } else {
        mnEvent_804D6C64 = 0;
    }

    mnEvent_804D6C60 = NULL;
    {
        HSD_Archive* archive = mn_804D6BB8;
        lbArchive_LoadSections(archive, arr, base + 0xA0, arr + 1, base + 0xB8,
                               arr + 2, base + 0xD4, arr + 3, base + 0xF4,
                               arr + 4, base + 0x118, 0);
    }

    if (first_time == 0) {
        mnEvent_8024E524(event_idx);
    }

    proc = HSD_GObj_SetupProc(GObj_Create(0, 1, 0x80), fn_8024D864, 0);
    proc->flags_3 = HSD_GObj_804D783C;
}
