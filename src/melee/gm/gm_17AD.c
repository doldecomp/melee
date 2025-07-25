#include "gm/forward.h"
#include "gm_17AD.h"
#include "placeholder.h"
#include "gm/gmresult.h"
#include "gm/types.h"

#pragma dont_inline on
s32 fn_8017AD04(s32 arg0, s32 arg1)
{
    s32 temp_r0;

    if (arg0 > arg1) {
        return arg1;
    }
    temp_r0 = -arg1;
    if (arg0 < temp_r0) {
        return temp_r0;
    }
    return arg0;
}
#pragma dont_inline reset

s32 fn_8017AD28(s32 arg0)
{
    if (arg0 > 9999) {
        return 9999;
    }
    if (arg0 < -9999) {
        return -9999;
    }
    return arg0;
}

s32 fn_8017AD48(s32 arg0)
{
    if (arg0 > 9999999) {
        return 9999999;
    }
    if (arg0 < -9999999) {
        return -9999999;
    }
    return arg0;
}

s32 fn_8017AD78(s32 arg0)
{
    if (arg0 > 99999) {
        return 99999;
    }
    if (arg0 < -99999) {
        return -99999;
    }
    return arg0;
}

s32 fn_8017ADA8(s32 arg0)
{
    s32 var_r3;

    var_r3 = fn_80174274()->player_standings[arg0].x1C;
    if (var_r3 > 999999) {
        return 999999;
    }
    else if (var_r3 < -999999) {
        return -999999;
    }
}

s32 fn_8017AE0C(s32 arg0)
{
    s32 var_r3;

    var_r3 = fn_80174274()->player_standings[arg0].x20;
    if (var_r3 > 999999) {
        return 999999;
    }
    if (var_r3 < -999999) {
        var_r3 = -999999;
        return var_r3;
    }
}

s32 fn_8017AE70(s32 arg0)
{
    MatchEnd* me;
    PAD_STACK(8);

    me = fn_80174274();
    if (arg0 == 0) {
        return -1;
    }
    if (me->player_standings[0].slot_type != 3) {
        return fn_8017AD04(me->player_standings[arg0].kills, 999999);
    }
    return -1;
}

s32 fn_8017AED8(s32 arg0)
{
    MatchEnd* me;
    PAD_STACK(8);

    me = fn_80174274();
    if (arg0 == 1) {
        return -1;
    }
    if (me->player_standings[1].slot_type != 3) {
        return fn_8017AD04(me->player_standings[arg0].x12, 999999);
    }
    return -1;
}

s32 fn_8017AF40(s32 arg0)
{
    MatchEnd* me;
    PAD_STACK(8);

    me = fn_80174274();
    if (arg0 == 2) {
        return -1;
    }
    if (me->player_standings[2].slot_type != 3) {
        return fn_8017AD04(me->player_standings[arg0].x14, 999999);
    }
    return -1;
}

s32 fn_8017AFA8(s32 arg0)
{
    MatchEnd* me;
    PAD_STACK(8);

    me = fn_80174274();
    if (arg0 == 3) {
        return -1;
    }
    if (me->player_standings[3].slot_type != 3) {
        return fn_8017AD04(me->player_standings[arg0].x16, 999999);
    }
    return -1;
}

s32 fn_8017B010(s32 arg0)
{
    s32 var_r3;
    MatchEnd* me;

    me = fn_80174274();
    var_r3 = me->player_standings[arg0].x24 - me->player_standings[arg0].self_destructs;
    if (var_r3 > 999999) {
        return 999999;
    }
    if (var_r3 < -999999) {
        return -999999;
    }
}

s32 fn_8017B07C(s32 arg0)
{
    MatchEnd* me;
    PAD_STACK(8);

    me = fn_80174274();
    if (arg0 == 0) {
        return -1;
    }
    if (me->player_standings[0].slot_type != 3) {
        return fn_8017AD04(me->player_standings[0].kills, 999999);
    }
    return -1;
}

s32 fn_8017B0E4(s32 arg0)
{
    MatchEnd* me;
    PAD_STACK(8);

    me = fn_80174274();
    if (arg0 == 1) {
        return -1;
    }
    if (me->player_standings[1].slot_type != 3) {
        return fn_8017AD04(me->player_standings[1].kills, 999999);
    }
    return -1;
}

s32 fn_8017B14C(s32 arg0)
{
    MatchEnd* me;
    PAD_STACK(8);

    me = fn_80174274();
    if (arg0 == 2) {
        return -1;
    }
    if (me->player_standings[2].slot_type != 3) {
        return fn_8017AD04(me->player_standings[2].kills, 999999);
    }
    return -1;
}

s32 fn_8017B1B4(s32 arg0)
{
    MatchEnd* me;
    PAD_STACK(8);

    me = fn_80174274();
    if (arg0 == 3) {
        return -1;
    }
    if ((u8) me->player_standings[3].slot_type != 3) {
        return fn_8017AD04(me->player_standings[3].kills, 999999);
    }
    return -1;
}

s32 fn_8017B21C(s32 arg0)
{
    MatchEnd* me;
    s32 result;

    me = fn_80174274();
    result = me->player_standings[arg0].self_destructs;
    if (result > 999999) {
        return 999999;
    }
    if (result < -999999) {
        return -999999;
    }
}

/// #fn_8017B280

/// #fn_8017B2E4

/// #fn_8017B348

/// #fn_8017B3AC

/// #fn_8017B410

/// #fn_8017B4D0

/// #fn_8017B534

/// #fn_8017B598

/// #fn_8017B5FC

/// #fn_8017B660

/// #fn_8017B6C4

/// #fn_8017B728

/// #fn_8017B78C

/// #fn_8017B7F0

/// #fn_8017B854

/// #fn_8017B8B8

/// #fn_8017B91C

/// #fn_8017B9F4
