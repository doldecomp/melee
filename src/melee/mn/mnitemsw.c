#include "mnitemsw.h"

#include "mnmain.h"

extern u8 mnItemSw_804D6BEC;
extern s32 HSD_GObj_804D783C;

HSD_GObj* GObj_Create(u16, u8, u8);
void* HSD_GObjProc_8038FD54(HSD_GObj*, void*, s32);
void mnItemSw_802351A0(s32, s32, s32);
void fn_80233E10(HSD_GObj*);

void mnItemSw_802358C0(void) {
    mn_unk1* data;
    u8 prev;
    HSD_GObj* gobj;

    data = &mn_804A04F0;
    prev = data->x0;
    data->x1 = prev;
    data->x0 = 0x10;
    data->x2 = 0;
    mnItemSw_804D6BEC = 1;
    mnItemSw_802351A0(1, 0, 0x10);
    gobj = HSD_GObjProc_8038FD54(GObj_Create(0, 1, 0x80), fn_80233E10, 0);
    {
        s32 val = HSD_GObj_804D783C;
        u8* ptr = (u8*)gobj + 0xD;
        *ptr = (*ptr & ~0x30) | ((val & 3) << 4);
    }
}
