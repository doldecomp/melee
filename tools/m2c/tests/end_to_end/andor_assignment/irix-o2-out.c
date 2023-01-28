s32 func_00400090(s32);                             /* static */

s32 test(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp24;
    s32 sp20;
    s32 temp_t3;
    s32 temp_t5;
    s32 temp_t7;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_s0;
    s32 var_t0;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;

    var_s0 = arg0 + arg1;
    temp_t7 = arg1 + arg2;
    sp20 = temp_t7;
    var_t0 = temp_t7;
    if ((var_s0 != 0) || (temp_t7 != 0) || (temp_v0 = func_00400090(temp_t7), var_t0 = temp_v0, (temp_v0 != 0)) || (var_s0 = 2, (arg3 != 0))) {
        var_v1_2 = 1;
    } else {
        var_v1_2 = -2;
        if (arg0 != 0) {
            var_v1_2 = -1;
        }
    }
    var_v1_3 = var_v1_2 + arg2;
    if ((var_s0 != 0) && (var_t0 != 0)) {
        var_s0 += var_t0;
        sp24 = var_v1_3;
        temp_v0_2 = func_00400090(var_s0);
        var_t0 = temp_v0_2;
        if ((temp_v0_2 != 0) && (arg3 != 0)) {
            if (var_v1_3 < 5) {
                do {
                    temp_t3 = (var_v1_3 + 1) * 2;
                    var_v1_3 = temp_t3;
                } while (temp_t3 < 5);
            }
            var_v1_3 += 5;
        }
    }
    if ((var_s0 != 0) && (var_t0 != 0) && (sp24 = var_v1_3, (func_00400090(var_s0 + var_t0) != 0)) && (arg3 != 0)) {
        if (var_v1_3 < 5) {
            do {
                temp_t5 = (var_v1_3 + 1) * 2;
                var_v1_3 = temp_t5;
            } while (temp_t5 < 5);
        }
        var_v1 = var_v1_3 + 5;
    } else {
        var_v1 = var_v1_3 + 6;
    }
    return var_v1;
}
