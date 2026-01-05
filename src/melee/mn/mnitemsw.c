#include "mnitemsw.h"

#include "mnmain.h"

#include <melee/lb/lblanguage.h>

typedef struct {
    char pad[0x78];
    f32 vals[];
} ItemSwTable;

extern ItemSwTable mnItemSw_803ED340;
extern u8 mnItemSw_804D6BEC;
extern s32 HSD_GObj_804D783C;

HSD_GObj* GObj_Create(u16, u8, u8);
void* HSD_GObjProc_8038FD54(HSD_GObj*, void*, s32);
void mnItemSw_802351A0(s32, s32, s32);
void fn_80233E10(HSD_GObj*);

s32 mnItemSw_80233A98(s32 arg0) {
    ItemSwTable* table = &mnItemSw_803ED340;

    switch (arg0) {
    case 0x12:
        break;
    case 0x13:
        if (lbLang_IsSettingJP()) {
            return (s32)table->vals[arg0];
        }
        return 0x27;
    case 0x11:
        if (lbLang_IsSettingJP()) {
            return (s32)table->vals[arg0];
        }
        return 0x28;
    default:
        break;
    }
    return (s32)table->vals[arg0];
}

typedef struct ItemSwNode {
    char x0[8];
    struct ItemSwNode* x8;
    char xC[4];
    struct ItemSwNode* x10;
} ItemSwNode;

typedef struct {
    char x0[0x34];
    ItemSwNode* x34;
    char x38[4];
    ItemSwNode* x3C;
} ItemSwData;

void* mnItemSw_8023405C(void* arg0, u8 idx) {
    ItemSwData* data = arg0;
    ItemSwNode* current;
    ItemSwNode* result;
    u8 i;

    if (idx >= 16) {
        if (data->x3C == 0) {
            result = 0;
        } else {
            result = data->x3C->x10;
        }
        current = result;
        for (i = 16; i < idx; i++) {
            if (current == 0) {
                current = 0;
            } else {
                current = current->x8;
            }
        }
    } else {
        if (data->x34 == 0) {
            current = 0;
        } else {
            current = data->x34->x10;
        }
        for (i = 0; i < idx; i++) {
            if (current == 0) {
                current = 0;
            } else {
                current = current->x8;
            }
        }
    }
    return current;
}

void mnItemSw_802358C0(void) {
    MenuFlow* data;
    u8 prev;
    HSD_GObj* gobj;

    data = &mn_804A04F0;
    prev = data->cur_menu;
    data->prev_menu = prev;
    data->cur_menu = 0x10;
    data->hovered_selection = 0;
    mnItemSw_804D6BEC = 1;
    mnItemSw_802351A0(1, 0, 0x10);
    gobj = HSD_GObjProc_8038FD54(GObj_Create(0, 1, 0x80), fn_80233E10, 0);
    {
        s32 val = HSD_GObj_804D783C;
        u8* ptr = (u8*)gobj + 0xD;
        *ptr = (*ptr & ~0x30) | ((val & 3) << 4);
    }
}
