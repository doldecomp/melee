s32 test(s32 arg0, s32 arg1) {
    s32 var_a0;

    var_a0 = arg0;
    if (arg1 != 0) {
        do {
            var_a0 -= 1;
        } while (var_a0 != 0);
    } else {
        var_a0 -= 1;
    }
    return var_a0;
}
