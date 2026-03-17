#include "mnitemsw.h"

#include "mn/inlines.h"
#include "mn/mnmain.h"

#include <baselib/gobj.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>

HSD_JObj* mnItemSw_8023405C(MnItemSwData* data, u8 idx)
{
    HSD_JObj* cur;
    u8 i;

    if (idx >= 16) {
        cur = HSD_JObjGetChild(data->jobjs[6]);
        for (i = 16; i < idx; i++) {
            cur = HSD_JObjGetNext(cur);
        }
    } else {
        if (data->jobjs[4] == NULL) {
            cur = NULL;
        } else {
            cur = data->jobjs[4]->child;
        }
        for (i = 0; i < idx; i++) {
            cur = HSD_JObjGetNext(cur);
        }
    }
    return cur;
}

void mnItemSw_802358C0(void)
{
    HSD_GObjProc* proc;

    mn_804A04F0.prev_menu = mn_804A04F0.cur_menu;
    mn_804A04F0.cur_menu = 0x10;
    mn_804A04F0.hovered_selection = 0;
    mnItemSw_804D6BEC = 1;
    mnItemSw_802351A0(1);

    proc = HSD_GObj_SetupProc(GObj_Create(0, 1, 0x80), fn_80233E10, 0);
    proc->flags_3 = HSD_GObj_804D783C;
}
