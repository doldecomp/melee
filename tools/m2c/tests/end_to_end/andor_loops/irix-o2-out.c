s32 test(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 var_v0;
    s32 var_v1;

    var_v1 = 0;
    if ((arg0 != 0) && ((arg1 != 0) || (arg2 != 0))) {
loop_3:
        var_v1 += 1;
        if (arg0 != 0) {
            if ((arg1 != 0) || (arg2 != 0)) {
                goto loop_3;
            }
        }
    }
    if ((arg0 != 0) || ((arg1 != 0) && (arg2 != 0))) {
loop_9:
        var_v1 += 1;
        if (arg0 != 0) {
            goto loop_9;
        }
        if ((arg1 != 0) && (arg2 != 0)) {
            goto loop_9;
        }
    }
    if (arg0 != 0) {
loop_13:
        var_v1 += 1;
        if (((arg1 == 0) || ((arg2 == 0) && (arg3 == 0))) && (var_v1 += 1, (arg1 == 0)) && ((arg2 == 0) || (arg3 == 0))) {
            var_v1 += 1;
            if ((arg1 == 0) || ((arg2 == 0) && (arg3 == 0))) {
                var_v1 += 1;
                if ((arg1 == 0) && ((arg2 == 0) || (arg3 == 0))) {
                    var_v1 += 1;
                    goto block_26;
                }
            }
        } else {
block_26:
            if (arg0 != 0) {
                goto loop_13;
            }
        }
    }
    var_v0 = 0;
    if ((arg0 != 0) || (arg1 != 0)) {
loop_29:
        var_v0 = var_v0 + arg2 + arg3;
        var_v1 += 1;
        if (var_v0 < 0xA) {
            if ((arg0 != 0) || (arg1 != 0)) {
                goto loop_29;
            }
        }
    }
    return var_v1;
}
