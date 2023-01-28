s32 test(s32 arg0) {
    s32 var_r4;

    var_r4 = 0;
loop_4:
    if (var_r4 < arg0) {
        if (var_r4 == 5) {
            var_r4 *= 2;
        } else {
            var_r4 += 4;
        }
        goto loop_4;
    }
    return var_r4;
}
