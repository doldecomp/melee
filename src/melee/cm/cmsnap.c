#include "cm/cmsnap.h"

#include "lb/lb_00F9.h"

#include <baselib/gobjgxlink.h>
#include <baselib/tobj.h>

typedef struct {
    int unk0;
    HSD_ImageDesc unk1;
    int unk2;
} _cmsnap_data;
static _cmsnap_data cmsnap_data;

void cmSnap_800315C8(void)
{
    if (cmsnap_data.unk0 != 0) {
        __assert("cmsnap.c", 0x55, "_p(status) == CmSnapStatus_Sleep");
    }
    cmsnap_data.unk0 = 1;
}

void* cmSnap_80031618(void)
{
    if (cmsnap_data.unk0 != 5) {
        return 0;
    }
    cmsnap_data.unk0 = 0;
    return cmsnap_data.unk1.img_ptr;
}

void cmSnap_80031640(HSD_GObj* arg0, int code)
{
    switch (cmsnap_data.unk0) {
    case 0:
        break;
    case 1:
        lb_800122C8(&cmsnap_data.unk1, 0, 0, 0);
        cmsnap_data.unk0 = 2;
        break;
    case 2:
    case 3:
    case 4:
        cmsnap_data.unk0 += 1;
        break;
    }
}

void cmSnap_800316B4(void)
{
    cmsnap_data.unk0 = 0;
    cmsnap_data.unk1.img_ptr = 0;
    GObj_SetupGXLinkMax(GObj_Create(0x12, 0x12, 0), cmSnap_80031640, 4);
    lb_800121FC(&cmsnap_data.unk1, 0x280, 0x1E0, 4, 0x7D6);
}
