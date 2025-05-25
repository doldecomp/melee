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

/// #mn_80229894

/// #mn_80229938

/// #mn_80229A04

/// #mn_80229A7C

/// #mn_80229B2C

/// #fn_80229BF4

/// #mn_80229DC0

/// #mn_80229F60

/// #mn_8022A440

/// #mn_8022A5D0

/// #mn_8022ADD8

/// #fn_8022AF10

/// #fn_8022AFEC

/// #mn_8022B3A0

/// #mn_8022BA1C

/// #fn_8022BCD4

/// #mn_8022BCF8

/// #mn_8022BD6C

/// #mn_8022BD8C

/// #fn_8022BDB4

/// #mn_8022BE34

/// #mn_8022BEDC

/// #mn_8022BFBC

/// #mn_8022C010

/// #mn_8022C068

/// #fn_8022C128

/// #mn_8022C304

/// #mn_8022C4F4

/// #mn_8022C7CC

/// #mn_8022CA54

/// #mn_8022CC28

/// #mn_8022CE6C

/// #mn_8022D104

/// #mn_8022D34C

/// #mn_8022D594

/// #mn_8022D7F4

/// #mn_8022DB10

/// #mn_8022DD38

/// #mn_8022DDA8

/// #mn_8022E950

/// #mn_8022E978

/// #mn_8022EA08

/// #mn_8022EA78

/// #mn_8022EAE0

/// #mn_8022EB04

/// #mn_8022EB24

/// #mn_8022EB78

/// #mn_8022EBDC

/// #mn_8022EC18

/// #mn_8022ED6C

/// #mn_8022EE84

/// #mn_8022EFD8

/// #mn_8022F0F0

/// #mn_8022F138

/// #mn_8022F1A8

/// #mn_8022F218

/// #mn_8022F268

/// #mn_8022F298

/// #mn_8022F360

/// #mn_8022F3D8

/// #mn_8022F410

/// #mn_8022F470

/// #mn_8022F4CC

/// #fn_8022F538

/// #mn_8022FB88

/// #mn_8022FD18

/// #mn_8022FEC8

/// #mn_80230198

/// #mn_80230274

/// #mn_802307F8

/// #mn_802308F0

/// #fn_802309F0

/// #mn_80230D18

/// #mn_80230E38

int mn_80231634(struct mn_80231634_t* arg0)
{
    if (arg0 == NULL) {
        return 0;
    }
    return arg0->x10;
}

/// #mn_8023164C

/// #mn_80231714

/// #mn_802317E4

/// #mn_80231804

/// #mn_80231F80

/// #fn_8023201C

/// #mn_80232458

/// #mn_802324E4

/// #mn_80232660

/// #mn_802327A4

/// #mn_80232D4C

/// #fn_80232F44

/// #mn_80233218

/// #mn_802339FC
