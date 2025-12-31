#include "mnstagesw.h"

#include <platform.h>

extern u8 mnStageSw_803ED4C4[32];

void gm_801641CC(u8);
s32 gm_80164430(void);
void gm_801641E4(u8, u8);

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
