#include "mnstagesw.h"

#include "mnmain.h"

#include <platform.h>
#include <sysdolphin/baselib/gobj.h>

typedef struct {
    u8 pad[0xD];
    u8 x0 : 2;
    u8 render_plink : 2;
    u8 x4 : 4;
} GObjBitfield;

extern u8 mnStageSw_803ED4C4[32];
extern u8 mnStageSw_804D6BF4;
extern s32 HSD_GObj_804D783C;

void gm_801641CC(u8);
s32 gm_80164430(void);
void gm_801641E4(u8, u8);
u16 mnStageSw_80235C58(s32);
HSD_GObj* mnStageSw_80236CBC(s32);
HSD_GObj* HSD_GObjProc_8038FD54(HSD_GObj*, void*, u8);
void fn_80235F80(HSD_GObj*);

void mnStageSw_8023593C(void* gobj) {
    u8* table = mnStageSw_803ED4C4;
    u8* ptr;
    s32 i;
    u8* data;
    s32 dummy[3];
    (void)dummy;

    ptr = table;
    i = 0;
    data = *(u8**)((u8*)gobj + 0x2C);
    do {
        u8* tmp = table + (u8)i;
        gm_801641CC(*tmp);
        if (gm_80164430() != 0) {
            gm_801641E4(*ptr, data[i + 2]);
        }
        i++;
        ptr++;
    } while (i < 0x1D);
}

typedef struct StageSw_Node {
    char x0[8];
    struct StageSw_Node* x8;
    char xC[4];
    struct StageSw_Node* x10;
} StageSw_Node;

typedef struct {
    char x0[0x2C];
    StageSw_Node* x2C;
    char x30[4];
    StageSw_Node* x34;
} StageSw_NodeData;

void* mnStageSw_802364A0(void* arg0, u8 idx) {
    StageSw_NodeData* data = arg0;
    StageSw_Node* current;
    StageSw_Node* result;
    u8 i;

    if (idx >= 15) {
        if (data->x34 == 0) {
            result = 0;
        } else {
            result = data->x34->x10;
        }
        current = result;
        for (i = 15; i < idx; i++) {
            if (current == 0) {
                current = 0;
            } else {
                current = current->x8;
            }
        }
    } else {
        if (data->x2C == 0) {
            current = 0;
        } else {
            current = data->x2C->x10;
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

void mnStageSw_80237410(void) {
    MenuFlow* data;
    u8 prev;
    HSD_GObj* gobj;

    data = &mn_804A04F0;
    prev = data->cur_menu;
    data->prev_menu = prev;
    data->cur_menu = 0x11;
    data->hovered_selection = mnStageSw_80235C58(0);
    mnStageSw_804D6BF4 = 1;
    HSD_GObj_80390CD4(mnStageSw_80236CBC(1));
    gobj = HSD_GObjProc_8038FD54(GObj_Create(0, 1, 0x80), fn_80235F80, 0);
    ((GObjBitfield*)gobj)->render_plink = HSD_GObj_804D783C;
}
