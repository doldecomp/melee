#include "cm/cmsnap.h"

#include "cm/forward.h"

#include "lb/lbspdisplay.h"

#include <baselib/debug.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/tobj.h>

typedef struct {
    CmSnapStatus status;
    HSD_ImageDesc unk1;
    int unk2;
} _cmsnap_data;
static _cmsnap_data cmsnap_data;
#define _p(x) (cmsnap_data.x)

void cmSnap_800315C8(void)
{
    HSD_ASSERT(0x55, _p(status) == CmSnapStatus_Sleep);
    _p(status) = CmSnapStatus_Unk1;
}

void* cmSnap_80031618(void)
{
    if (_p(status) != CmSnapStatus_Unk5) {
        return 0;
    }
    _p(status) = CmSnapStatus_Sleep;
    return _p(unk1).image_ptr;
}

void cmSnap_80031640(HSD_GObj* arg0, int code)
{
    switch (_p(status)) {
    case CmSnapStatus_Sleep:
        break;
    case CmSnapStatus_Unk1:
        lb_800122C8(&_p(unk1), 0, 0, 0);
        _p(status) = CmSnapStatus_Unk2;
        break;
    case CmSnapStatus_Unk2:
    case CmSnapStatus_Unk3:
    case CmSnapStatus_Unk4:
        _p(status) += 1;
        break;
    }
}

void cmSnap_800316B4(void)
{
    _p(status) = CmSnapStatus_Sleep;
    _p(unk1).image_ptr = NULL;
    GObj_SetupGXLinkMax(GObj_Create(0x12, 0x12, 0), cmSnap_80031640, 4);
    lb_800121FC(&_p(unk1), 0x280, 0x1E0, 4, 0x7D6);
}
