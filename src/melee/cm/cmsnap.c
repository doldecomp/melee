#include "cm/cmsnap.h"

#include "lb/lbunknown_003.h"

#include <baselib/gobjgxlink.h>

typedef struct {
    int unk0;
    int unk1;
    int _[6];
} _cmsnap_data;
static _cmsnap_data cmsnap_data;

void func_800315C8(void)
{
    if (cmsnap_data.unk0 != 0) {
        __assert("cmsnap.c", 0x55, "_p(status) == CmSnapStatus_Sleep");
    }
    cmsnap_data.unk0 = 1;
}

s32 func_80031618(void)
{
    if (cmsnap_data.unk0 != 5) {
        return 0;
    }
    cmsnap_data.unk0 = 0;
    return cmsnap_data.unk1;
}

void func_80031640(HSD_GObj* arg0, s32 arg1)
{
    switch (cmsnap_data.unk0) {
    case 0:
        break;
    case 1:
        func_800122C8(&cmsnap_data.unk1, 0, 0, 0);
        cmsnap_data.unk0 = 2;
        break;
    case 2:
    case 3:
    case 4:
        cmsnap_data.unk0 += 1;
        break;
    }
}

void func_800316B4(void)
{
    cmsnap_data.unk0 = 0;
    cmsnap_data.unk1 = 0;
    GObj_SetupGXLinkMax(GObj_Create(0x12, 0x12, 0), func_80031640, 4);
    func_800121FC(&cmsnap_data.unk1, 0x280, 0x1E0, 4, 0x7D6);
}
