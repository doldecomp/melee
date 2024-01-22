s32 test(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 var_r5;
    s32 var_r7;
    s32 var_r8;

    var_r5 = arg2;
    var_r8 = 0;
    if (((arg0 + arg1) != 0) || (((s32) (arg1 + var_r5) != 0) && ((arg0 * arg1) != 0)) || ((arg3 != 0) && (arg0 != 0))) {
        var_r8 = 1;
    }
    if ((arg0 != 0) && ((arg1 != 0) || (var_r5 != 0)) && ((arg3 != 0) || ((arg0 + 1) != 0))) {
        var_r8 = 2;
    }
    if (((arg0 != 0) && (arg3 != 0)) || (((arg1 != 0) || (var_r5 != 0)) && ((arg0 + 1) != 0))) {
        var_r8 = 3;
    }
    if ((arg0 != 0) && (arg1 != 0) && ((var_r5 != 0) || (arg3 != 0)) && (((arg0 + 1) != 0) || ((arg1 + 1) != 0))) {
        var_r8 = 4;
    }
    if ((((arg0 != 0) || (arg1 != 0)) && (var_r5 != 0)) || ((arg3 != 0) && ((arg0 + 1) != 0)) || ((arg1 + 1) != 0) || ((var_r5 + 1) != 0)) {
        var_r8 = 5;
    }
    if ((((arg0 != 0) && (arg1 != 0)) || ((var_r5 != 0) && (arg3 != 0))) && (((arg0 + 1) != 0) || ((arg1 + 1) != 0))) {
        var_r8 = 6;
    }
    if (arg0 != 0) {
        if (arg1 != 0) {
            var_r7 = var_r5;
        } else {
            var_r7 = arg3;
        }
        if (((s32) (arg0 + 1) == var_r7) && ((arg1 + 1) != 0)) {
            var_r8 = 7;
        }
    }
    if (arg0 == 0) {
        if (arg1 != 0) {

        } else {
            var_r5 = arg3;
        }
        if (((s32) (arg0 + 1) == var_r5) || ((arg1 + 1) != 0)) {
            goto block_53;
        }
    } else {
block_53:
        var_r8 = 8;
    }
    return var_r8;
}
