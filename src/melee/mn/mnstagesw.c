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

void mnStageSw_80237410(void) {
    mn_unk1* data;
    u8 prev;
    HSD_GObj* gobj;

    data = &mn_804A04F0;
    prev = data->x0;
    data->x1 = prev;
    data->x0 = 0x11;
    data->x2 = mnStageSw_80235C58(0);
    mnStageSw_804D6BF4 = 1;
    HSD_GObj_80390CD4(mnStageSw_80236CBC(1));
    gobj = HSD_GObjProc_8038FD54(GObj_Create(0, 1, 0x80), fn_80235F80, 0);
    ((GObjBitfield*)gobj)->render_plink = HSD_GObj_804D783C;
}
