s32 foo(s32);                                       /* static */

s32 test(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp14;
    s32 temp_r0;
    s32 var_r30;
    s32 var_r30_2;
    s32 var_r30_3;
    s32 var_r31;
    s32 var_r3;

    temp_r0 = arg0 + arg1;
    var_r3 = arg1 + arg2;
    sp14 = arg3;
    var_r31 = temp_r0;
    if ((temp_r0 != 0) || (var_r3 != 0) || (var_r3 = foo(), ((var_r3 == 0) == 0)) || (var_r31 = 2, ((sp14 == 0) == 0))) {
        var_r30_2 = 1;
    } else if (arg0 != 0) {
        var_r30_2 = -1;
    } else {
        var_r30_2 = -2;
    }
    var_r30_3 = var_r30_2 + arg2;
    if ((var_r31 != 0) && (var_r3 != 0)) {
        var_r31 += var_r3;
        var_r3 = foo(var_r31);
        if ((var_r3 != 0) && (sp14 != 0)) {
loop_14:
            if (var_r30_3 < 5) {
                var_r30_3 = (var_r30_3 + 1) * 2;
                goto loop_14;
            }
            var_r30_3 += 5;
        }
    }
    if ((var_r31 != 0) && (var_r3 != 0) && (foo(var_r31 + var_r3) != 0) && (sp14 != 0)) {
loop_22:
        if (var_r30_3 < 5) {
            var_r30_3 = (var_r30_3 + 1) * 2;
            goto loop_22;
        }
        var_r30 = var_r30_3 + 5;
    } else {
        var_r30 = var_r30_3 + 6;
    }
    return var_r30;
}
