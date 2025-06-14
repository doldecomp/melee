#include "gm_1A36.h"

#include "gm/gm_1A36.static.h"

#include <baselib/controller.h>

u64 gm_801A3680(u8 idx)
{
    return gm_80479C30[(u8) idx].button;
}

u64 gm_801A36A0(u8 idx)
{
    return gm_80479C30[(u8) idx].trigger;
}

u64 gm_801A36C0(u8 idx)
{
    return gm_80479C30[(u8) idx].unk;
}

void gm_801A36E0(s32 idx, s32 arg1)
{
    if (idx == 4) {
        gm_80479C30[0].x28 = arg1;
        gm_80479C30[1].x28 = arg1;
        gm_80479C30[2].x28 = arg1;
        gm_80479C30[3].x28 = arg1;
        return;
    }
    gm_80479C30[idx].x28 = arg1;
}

void gm_801A3714(s32 idx, u64 arg1, u64 arg2)
{
    if (arg1 & gm_80479C30[idx].button) {
        gm_80479C30[idx].button |= arg2;
    }
    if (arg1 & gm_80479C30[idx].repeat) {
        gm_80479C30[idx].repeat |= arg2;
    }
    if (arg1 & gm_80479C30[idx].trigger) {
        gm_80479C30[idx].trigger |= arg2;
    }
    if (arg1 & gm_80479C30[idx].release) {
        gm_80479C30[idx].release |= arg2;
    }
}

void gm_801A3820(s32 idx, u64 arg1, u64 arg2)
{
    u64 val;
    if (arg1 == (arg1 & gm_80479C30[idx].button)) {
        gm_80479C30[idx].button |= arg2;
    }
    if (arg1 == (arg1 & gm_80479C30[idx].repeat)) {
        gm_80479C30[idx].repeat |= arg2;
    }
    if (arg1 == (arg1 & gm_80479C30[idx].button)) {
        if (arg1 & gm_80479C30[idx].trigger) {
            gm_80479C30[idx].trigger |= arg2;
        }
    }
    if (arg1 == (arg1 & gm_80479C30[idx].button)) {
        if (arg1 & gm_80479C30[idx].release) {
            gm_80479C30[idx].release |= arg2;
        }
    }
}

void fn_801A396C(int idx)
{
    if (gm_80479C30[idx].button || gm_80479C30[idx].release) {
        gm_80479C30[idx].unk = gm_80479C30[idx].button;
        gm_80479C30[idx].x28 = gm_80479D24;
        gm_80479C30[idx].x2C = 0;
    }
    if (gm_80479C30[idx].x2C < gm_80479D24) {
        gm_80479C30[idx].x2C++;
    }
    if (gm_80479C30[idx].x28 != 0) {
        gm_80479C30[idx].x28--;
        gm_80479C30[idx].unk = 0;
    }
}

#pragma push
#pragma dont_inline on
void gm_801A3A74(void)
{
    gm_controller_map* controller = gm_80479C30;
    int i;
    for (i = 0; i < 4; i++) {
        controller->button = HSD_PadCopyStatus[i].button;
        controller->trigger = HSD_PadCopyStatus[i].trigger;
        controller->repeat = HSD_PadCopyStatus[i].repeat;
        controller->release = HSD_PadCopyStatus[i].release;
        gm_801A3714(i, 0x1100, ((u64) 1 << (32 + 0)));
        gm_801A3714(i, 0x200, ((u64) 1 << (32 + 1)));
        gm_801A3820(i, 0x1060, ((u64) 1 << (32 + 2)));
        gm_801A3820(i, 0x1160, ((u64) 1 << (32 + 3)));
        gm_801A3714(i, 0x10008, ((u64) 1 << (32 + 4)));
        gm_801A3714(i, 0x20004, ((u64) 1 << (32 + 5)));
        gm_801A3714(i, 0x40001, ((u64) 1 << (32 + 6)));
        gm_801A3714(i, 0x80002, ((u64) 1 << (32 + 7)));
        gm_80479D20(i);
        controller++;
    }
    controller_union.button = 0;
    controller_union.trigger = 0;
    controller_union.repeat = 0;
    controller_union.release = 0;
    controller_union.unk = 0;
    controller_union.x28 = 0;
    controller_union.x2C = 0;
    for (i = 0; i < 4; i++) {
        controller_union.button |= gm_80479C30[i].button;
        controller_union.trigger |= gm_80479C30[i].trigger;
        controller_union.repeat |= gm_80479C30[i].repeat;
        controller_union.release |= gm_80479C30[i].release;
    }
}
#pragma pop

/// #gm_801A3E88

/// #gm_801A3EF4
