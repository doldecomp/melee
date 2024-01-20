s32 test(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 var_t0;
    s32 var_t0_2;
    s32 var_v1;

    var_v1 = 0;
    if (((arg0 + arg1) != 0) || (((arg1 + arg2) != 0) && ((arg0 * arg1) != 0)) || ((arg3 != 0) && (arg0 != 0))) {
        var_v1 = 1;
    }
    if ((arg0 != 0) && ((arg1 != 0) || (arg2 != 0)) && ((arg3 != 0) || ((arg0 + 1) != 0))) {
        var_v1 = 2;
    }
    if (((arg0 != 0) && (arg3 != 0)) || (((arg1 != 0) || (arg2 != 0)) && ((arg0 + 1) != 0))) {
        var_v1 = 3;
    }
    if ((arg0 != 0) && (arg1 != 0) && ((arg2 != 0) || (arg3 != 0)) && (((arg0 + 1) != 0) || ((arg1 + 1) != 0))) {
        var_v1 = 4;
    }
    if ((((arg0 != 0) || (arg1 != 0)) && (arg2 != 0)) || ((arg3 != 0) && ((arg0 + 1) != 0)) || ((arg1 + 1) != 0) || ((arg2 + 1) != 0)) {
        var_v1 = 5;
    }
    if ((((arg0 != 0) && (arg1 != 0)) || ((arg2 != 0) && (arg3 != 0))) && (((arg0 + 1) != 0) || ((arg1 + 1) != 0))) {
        var_v1 = 6;
    }
    if (arg0 != 0) {
        if (arg1 != 0) {
            var_t0 = arg2;
        } else {
            var_t0 = arg3;
        }
        if ((var_t0 == (arg0 + 1)) && ((arg1 + 1) != 0)) {
            var_v1 = 7;
        }
    }
    if (arg0 == 0) {
        if (arg1 != 0) {
            var_t0_2 = arg2;
        } else {
            var_t0_2 = arg3;
        }
        if ((var_t0_2 == (arg0 + 1)) || ((arg1 + 1) != 0)) {
            goto block_53;
        }
    } else {
block_53:
        var_v1 = 8;
    }
    return var_v1;
}
