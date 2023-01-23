s32 test(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 var_r5;
    s32 var_r7;

    var_r7 = 0;
loop_2:
    if (arg0 != 0) {
        if ((arg1 == 0) && (arg2 == 0)) {

        } else {
            var_r7 += 1;
            goto loop_2;
        }
    }
loop_7:
    if (arg0 != 0) {
block_6:
        var_r7 += 1;
        goto loop_7;
    }
    if (arg1 != 0) {
        if (arg2 == 0) {

        } else {
            goto block_6;
        }
    }
loop_24:
    if (arg0 != 0) {
        var_r7 += 1;
        if (((arg1 == 0) || ((arg2 == 0) && (arg3 == 0))) && (var_r7 += 1, ((arg1 == 0) != 0)) && ((arg2 == 0) || (arg3 == 0))) {
            var_r7 += 1;
            if ((arg1 == 0) || ((arg2 == 0) && (arg3 == 0))) {
                var_r7 += 1;
                if ((arg1 == 0) && ((arg2 == 0) || (arg3 == 0))) {
                    var_r7 += 1;
                    goto loop_24;
                }
            }
        } else {
            goto loop_24;
        }
    }
    var_r5 = 0;
loop_27:
    if ((var_r5 < 0xA) && ((arg0 != 0) || (arg1 != 0))) {
        var_r5 += arg2 + arg3;
        var_r7 += 1;
        goto loop_27;
    }
    return var_r7;
}
