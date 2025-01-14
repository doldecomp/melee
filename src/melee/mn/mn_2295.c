#include <platform.h>

#include <baselib/forward.h>

#include "mn/mn_2295.h"

#include "gm/gm_1A36.h"
#include "gm/gmmain_lib.h"
#include "lb/lb_00CE.h"
#include "mn/inlines.h"

u8 mn_802295AC(void)
{
    s32 port_idx = 0;
    while (port_idx < 4) {
        u64 res = gm_801A36A0(port_idx);
        if (res & 0x100000000) {
            return port_idx;
        }
        port_idx += 1;
    }
    return 0;
}

u32 mn_80229624(u32 arg0)
{
    u32 ret = 0;
    u64 inputs_a;
    u64 inputs_b;
    inputs_a = gm_801A36C0(arg0);
    inputs_b = gm_801A36A0(arg0);
    if (mn_804D6BC8.x0 != 0) {
        Menu_DecrementAnimTimer();
        return 0;
    }
    if (inputs_b & 0x100) {
        ret |= MenuEvent_unk4;
    }
    if (inputs_b & 0x1000) {
        ret |= MenuEvent_unk3;
    }
    if (inputs_b & 0x100000000) {
        ret |= MenuEvent_Forward;
    }
    if (inputs_b & 0x200000000) {
        ret |= MenuEvent_Back;
    }
    if (inputs_b & 0x40) {
        ret |= MenuEvent_unk;
    }
    if (inputs_b & 0x20) {
        ret |= MenuEvent_unk2;
    }
    if (inputs_b & 0x400) {
        ret |= MenuEvent_unk5;
    }
    if (inputs_b & 0x800) {
        ret |= MenuEvent_unk6;
    }
    if (inputs_a & 0x1000000000) {
        ret |= MenuEvent_Up;
    }
    if (inputs_a & 0x2000000000) {
        ret |= MenuEvent_Down;
    }
    if (inputs_a & 0x4000000000) {
        ret |= MenuEvent_Left;
    }
    if (inputs_a & 0x8000000000) {
        ret |= MenuEvent_Right;
    }
    return ret;
}

void mn_80229860(s8 arg0)
{
    s8* val = gm_801A4B9C();
    *val = arg0;
    gm_801A4B60();
}

s32 mn_80229938(s32 arg0, s32 arg1)
{
    if (arg0 == 6 && arg1 == 2) {
        if (gmMainLib_8015EDD4()) {
            return 1;
        }
        return 0;
    }
    if (arg0 == 5 && arg1 == 2) {
        if (gmMainLib_8015EE90()) {
            return 1;
        }
        return 0;
    }
    if (arg0 == 4 && arg1 == 3) {
        return 0;
    }
    if (arg0 == 1 && arg1 == 2) {
        return 0;
    }
    if (arg0 == 3) {
        if (arg1 == 2) {
            return 0;
        } else {
            return 1;
        }
    }
    return 1;
}

char null_terminator = '\0';

void mn_8022EA08(char* buf, u32 num)
{
    s32 buf_end = mn_8022EB78(num);
    s32 buf_len = buf_end - 1;
    s32 idx = 0;
    while (idx < buf_end) {
        buf[buf_len - idx] = mn_8022EB24(num, idx) + 0x30;
        idx += 1;
    }
    buf[buf_end] = null_terminator;
}

s32 mn_8022EB24(s32 arg0, s32 arg1)
{
    return (arg0 / powi(0xA, arg1)) % 10;
}

s32 mn_8022EB78(s32 num)
{
    s32 count;
    if (num == 0) {
        return 1;
    }
    count = 0;
    for (;;) {
        if ((num / powi(0xA, count)) != 0) {
            count += 1;
            if (count < 0xB) {
                continue;
            }
        }
        break;
    }
    return count;
}
