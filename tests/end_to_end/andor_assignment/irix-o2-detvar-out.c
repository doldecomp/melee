s32 func_00400090(s32);                             /* static */

s32 test(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp24;
    s32 sp20;
    s32 temp_t3_60;
    s32 temp_t5_82;
    s32 temp_t7_13;
    s32 temp_v0_22;
    s32 temp_v0_47;
    s32 var_s0_12;
    s32 var_t0_19;
    s32 var_v1_34;
    s32 var_v1_42;
    s32 var_v1_88;

    var_s0_12 = arg0 + arg1;
    temp_t7_13 = arg1 + arg2;
    sp20 = temp_t7_13;
    var_t0_19 = temp_t7_13;
    if ((var_s0_12 != 0) || (temp_t7_13 != 0) || (temp_v0_22 = func_00400090(temp_t7_13), var_t0_19 = temp_v0_22, (temp_v0_22 != 0)) || (var_s0_12 = 2, (arg3 != 0))) {
        var_v1_34 = 1;
    } else {
        var_v1_34 = -2;
        if (arg0 != 0) {
            var_v1_34 = -1;
        }
    }
    var_v1_42 = var_v1_34 + arg2;
    if ((var_s0_12 != 0) && (var_t0_19 != 0)) {
        var_s0_12 += var_t0_19;
        sp24 = var_v1_42;
        temp_v0_47 = func_00400090(var_s0_12);
        var_t0_19 = temp_v0_47;
        if ((temp_v0_47 != 0) && (arg3 != 0)) {
            if (var_v1_42 < 5) {
                do {
                    temp_t3_60 = (var_v1_42 + 1) * 2;
                    var_v1_42 = temp_t3_60;
                } while (temp_t3_60 < 5);
            }
            var_v1_42 += 5;
        }
    }
    if ((var_s0_12 != 0) && (var_t0_19 != 0) && (sp24 = var_v1_42, (func_00400090(var_s0_12 + var_t0_19) != 0)) && (arg3 != 0)) {
        if (var_v1_42 < 5) {
            do {
                temp_t5_82 = (var_v1_42 + 1) * 2;
                var_v1_42 = temp_t5_82;
            } while (temp_t5_82 < 5);
        }
        var_v1_88 = var_v1_42 + 5;
    } else {
        var_v1_88 = var_v1_42 + 6;
    }
    return var_v1_88;
}
