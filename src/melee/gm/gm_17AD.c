#include "gm_17AD.h"

#include <melee/pl/forward.h>

#include <melee/gm/gmresult.h>
#include <melee/gm/types.h>
#include <melee/lb/lblanguage.h>

/// TODO :: figure out how to force the other functions not to inline this
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
    } else if (arg0 < -9999) {
        return -9999;
    }
    return arg0;
}

s32 fn_8017AD48(s32 arg0)
{
    if (arg0 > 9999999) {
        return 9999999;
    } else if (arg0 < -9999999) {
        return -9999999;
    }
    return arg0;
}

s32 fn_8017AD78(s32 arg0)
{
    if (arg0 > 99999) {
        return 99999;
    } else if (arg0 < -99999) {
        return -99999;
    }
    return arg0;
}

s32 fn_8017ADA8(s32 slot)
{
    MatchEnd* me;
    s32 var_r3;

    me = fn_80174274();
    var_r3 = me->player_standings[slot].x1C;
    if (var_r3 > 999999) {
        var_r3 = 999999;
    } else if (var_r3 < -999999) {
        var_r3 = -999999;
    }
    return var_r3;
}

s32 fn_8017AE0C(s32 arg0)
{
    MatchEnd* me;
    s32 var_r3;

    me = fn_80174274();
    var_r3 = me->player_standings[arg0].x20;
    if (var_r3 > 999999) {
        var_r3 = 999999;
    } else if (var_r3 < -999999) {
        var_r3 = -999999;
    }
    return var_r3;
}

s32 fn_8017AE70(s32 arg0)
{
    MatchEnd* me;
    PAD_STACK(8);

    me = fn_80174274();
    if (arg0 == 0) {
        return -1;
    }
    if (me->player_standings[0].slot_type != Gm_PKind_NA) {
        return fn_8017AD04(me->player_standings[arg0].kills[0], 999999);
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
    if (me->player_standings[1].slot_type != Gm_PKind_NA) {
        return fn_8017AD04(me->player_standings[arg0].kills[1], 999999);
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
    if (me->player_standings[2].slot_type != Gm_PKind_NA) {
        return fn_8017AD04(me->player_standings[arg0].kills[2], 999999);
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
    if (me->player_standings[3].slot_type != Gm_PKind_NA) {
        return fn_8017AD04(me->player_standings[arg0].kills[3], 999999);
    }
    return -1;
}

s32 fn_8017B010(s32 arg0)
{
    s32 var_r3;
    MatchEnd* me;

    me = fn_80174274();
    var_r3 = me->player_standings[arg0].x24 -
             me->player_standings[arg0].self_destructs;
    if (var_r3 > 999999) {
        var_r3 = 999999;
    } else if (var_r3 < -999999) {
        var_r3 = -999999;
    }
    return var_r3;
}

s32 fn_8017B07C(s32 arg0)
{
    MatchEnd* me;
    s32 var_r3;
    PAD_STACK(8);

    me = fn_80174274();
    if (arg0 == 0) {
        return -1;
    } else if (me->player_standings[0].slot_type != Gm_PKind_NA) {
        var_r3 = fn_8017AD04(me->player_standings[0].kills[arg0], 999999);
        return var_r3;
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
    if (me->player_standings[1].slot_type != Gm_PKind_NA) {
        return fn_8017AD04(me->player_standings[1].kills[arg0], 999999);
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
    if (me->player_standings[2].slot_type != Gm_PKind_NA) {
        return fn_8017AD04(me->player_standings[2].kills[arg0], 999999);
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
    } else if (me->player_standings[3].slot_type != Gm_PKind_NA) {
        return fn_8017AD04(me->player_standings[3].kills[arg0], 999999);
    }
    return -1;
}

s32 fn_8017B21C(s32 arg0)
{
    MatchEnd* me;
    s32 var_r3;

    me = fn_80174274();
    var_r3 = me->player_standings[arg0].self_destructs;
    if (var_r3 > 999999) {
        var_r3 = 999999;
    } else if (var_r3 < -999999) {
        var_r3 = -999999;
    }
    return var_r3;
}

s32 fn_8017B280(s32 arg0)
{
    MatchEnd* me;
    s32 var_r3;

    me = fn_80174274();
    var_r3 = me->player_standings[arg0].x40;
    if (var_r3 > 999999) {
        var_r3 = 999999;
    } else if (var_r3 < -999999) {
        var_r3 = -999999;
    }
    return var_r3;
}

s32 fn_8017B2E4(s32 arg0)
{
    MatchEnd* me;
    s32 var_r3;

    me = fn_80174274();
    var_r3 = me->player_standings[arg0].x44;
    if (var_r3 > 999999) {
        var_r3 = 999999;
    } else if (var_r3 < -999999) {
        var_r3 = -999999;
    }
    return var_r3;
}

s32 fn_8017B348(s32 arg0)
{
    MatchEnd* me;
    s32 var_r3;

    me = fn_80174274();
    var_r3 = me->player_standings[arg0].x48;
    if (var_r3 > 999999) {
        var_r3 = 999999;
    } else if (var_r3 < -999999) {
        var_r3 = -999999;
    }
    return var_r3;
}

s32 fn_8017B3AC(s32 arg0)
{
    MatchEnd* me;
    s32 var_r3;

    me = fn_80174274();
    var_r3 = me->player_standings[arg0].x4C;
    if (var_r3 > 999999) {
        var_r3 = 999999;
    } else if (var_r3 < -999999) {
        var_r3 = -999999;
    }
    return var_r3;
}

s32 fn_8017B410(s32 arg0)
{
    MatchEnd* me;
    s32 var_r3;
    PAD_STACK(24);

    me = fn_80174274();
    if (lbLang_IsSavedLanguageUS() != 0) {
        var_r3 = (u32) (f32) (me->player_standings[arg0].x5C / 30.4788f);
    } else {
        var_r3 = me->player_standings[arg0].x5C / 100;
    }
    if (var_r3 > 999999) {
        var_r3 = 999999;
    } else if (var_r3 < -999999) {
        var_r3 = -999999;
    }
    return var_r3;
}

s32 fn_8017B4D0(s32 arg0)
{
    MatchEnd* me;
    s32 var_r3;

    me = fn_80174274();
    var_r3 = me->player_standings[arg0].x6C;
    if (var_r3 > 999999) {
        var_r3 = 999999;
    } else if (var_r3 < -999999) {
        var_r3 = -999999;
    }
    return var_r3;
}

s32 fn_8017B534(s32 arg0)
{
    MatchEnd* me;
    s32 var_r3;

    me = fn_80174274();
    var_r3 = me->player_standings[arg0].x70;
    if (var_r3 > 999999) {
        var_r3 = 999999;
    } else if (var_r3 < -999999) {
        var_r3 = -999999;
    }
    return var_r3;
}

s32 fn_8017B598(s32 arg0)
{
    MatchEnd* me;
    s32 var_r3;

    me = fn_80174274();
    var_r3 = me->player_standings[arg0].pad_x30[4];
    if (var_r3 > 999999) {
        var_r3 = 999999;
    } else if (var_r3 < -999999) {
        var_r3 = -999999;
    }
    return var_r3;
}

s32 fn_8017B5FC(s32 arg0)
{
    MatchEnd* me;
    s32 var_r3;

    me = fn_80174274();
    var_r3 = me->player_standings[arg0].x74;
    if (var_r3 > 999999) {
        var_r3 = 999999;
    } else if (var_r3 < -999999) {
        var_r3 = -999999;
    }
    return var_r3;
}

s32 fn_8017B660(s32 arg0)
{
    MatchEnd* me;
    s32 var_r3;

    me = fn_80174274();
    var_r3 = me->player_standings[arg0].x78;
    if (var_r3 > 999999) {
        var_r3 = 999999;
    } else if (var_r3 < -999999) {
        var_r3 = -999999;
    }
    return var_r3;
}

s32 fn_8017B6C4(s32 arg0)
{
    MatchEnd* me;
    s32 var_r3;

    me = fn_80174274();
    var_r3 = me->player_standings[arg0].x7C;
    if (var_r3 > 999999) {
        var_r3 = 999999;
    } else if (var_r3 < -999999) {
        var_r3 = -999999;
    }
    return var_r3;
}

s32 fn_8017B728(s32 arg0)
{
    MatchEnd* me;
    s32 var_r3;

    me = fn_80174274();
    var_r3 = me->player_standings[arg0].x84;
    if (var_r3 > 999999) {
        var_r3 = 999999;
    } else if (var_r3 < -999999) {
        var_r3 = -999999;
    }
    return var_r3;
}

s32 fn_8017B78C(s32 arg0)
{
    MatchEnd* me;
    s32 var_r3;

    me = fn_80174274();
    var_r3 = me->player_standings[arg0].x88;
    if (var_r3 > 999999) {
        var_r3 = 999999;
    } else if (var_r3 < -999999) {
        var_r3 = -999999;
    }
    return var_r3;
}

s32 fn_8017B7F0(s32 arg0)
{
    MatchEnd* me;
    s32 var_r3;

    me = fn_80174274();
    var_r3 = me->player_standings[arg0].x8C;
    if (var_r3 > 999999) {
        var_r3 = 999999;
    } else if (var_r3 < -999999) {
        var_r3 = -999999;
    }
    return var_r3;
}

s32 fn_8017B854(s32 arg0)
{
    MatchEnd* me;
    s32 var_r3;

    me = fn_80174274();
    var_r3 = me->player_standings[arg0].x80;
    if (var_r3 > 999999) {
        var_r3 = 999999;
    } else if (var_r3 < -999999) {
        var_r3 = -999999;
    }
    return var_r3;
}

s32 fn_8017B8B8(s32 arg0)
{
    MatchEnd* me;
    s32 var_r3;

    me = fn_80174274();
    var_r3 = me->player_standings[arg0].x90;
    if (var_r3 > 999999) {
        var_r3 = 999999;
    } else if (var_r3 < -999999) {
        var_r3 = -999999;
    }
    return var_r3;
}

s32 fn_8017B91C(s32 arg0)
{
    MatchEnd* me;
    s32 var_r3;
    PAD_STACK(24);

    me = fn_80174274();
    if (lbLang_IsSavedLanguageUS() != 0) {
        var_r3 = (u32) (f32) ((f32) me->player_standings[arg0].x94 / 30.4788);
    } else {
        var_r3 = (u32) ((f32) me->player_standings[arg0].x94 / 100.0f);
    }
    if (var_r3 > 999999) {
        var_r3 = 999999;
    } else if (var_r3 < -999999) {
        var_r3 = -999999;
    }
    return var_r3;
}

s32 fn_8017B9F4(s32 arg0)
{
    MatchEnd* me;
    u32 var_r3;
    PAD_STACK(24);

    me = fn_80174274();
    if (lbLang_IsSavedLanguageUS() != 0) {
        var_r3 = (u32) (f32) ((f32) me->player_standings[arg0].x98 / 30.4788);
    } else {
        var_r3 = (u32) ((f32) me->player_standings[arg0].x98 / 100.0f);
    }
    if ((s32) var_r3 > 999999) {
        return 999999;
    } else if ((s32) var_r3 < -999999) {
        var_r3 = -999999;
    }
    return (s32) var_r3;
}
