s32 func_00400090(s32);                             /* static */

s32 test(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp2C;
    s32 sp24;
    s32 sp20;
    s32 sp1C;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_t0;
    s32 temp_t5;
    s32 temp_t7;
    s32 temp_t9;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_t1;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;

    temp_t0 = arg0 + arg1;
    temp_t7 = arg1 + arg2;
    sp2C = temp_t0;
    sp1C = temp_t7;
    var_t1 = temp_t7;
    if (temp_t0 == 0) {
        if (temp_t7 == 0) {
            sp20 = temp_t0;
            temp_v0 = func_00400090(temp_t7);
            var_t1 = temp_v0;
            if (temp_v0 == 0) {
                if (arg3 != 0) {
                    goto block_4;
                }
                var_v1_2 = -2;
                if (arg0 != 0) {
                    var_v1_2 = -1;
                }
            } else {
                goto block_4;
            }
        } else {
            goto block_4;
        }
    } else {
block_4:
        var_v1_2 = 1;
    }
    var_v1_3 = var_v1_2 + arg2;
    if (temp_t0 != 0) {
        temp_a0 = temp_t0 + var_t1;
        if (var_t1 != 0) {
            sp2C = temp_a0;
            sp24 = var_v1_3;
            temp_v0_2 = func_00400090(temp_a0);
            var_t1 = temp_v0_2;
            if (temp_v0_2 != 0) {
                if (arg3 != 0) {
                    if (var_v1_3 < 5) {
                        do {
                            temp_t5 = (var_v1_3 + 1) * 2;
                            var_v1_3 = temp_t5;
                        } while (temp_t5 < 5);
                    }
                    var_v1_3 += 5;
                }
            }
        }
    }
    if (sp2C != 0) {
        temp_a0_2 = sp2C + var_t1;
        if (var_t1 != 0) {
            sp2C = temp_a0_2;
            sp24 = var_v1_3;
            if (func_00400090(temp_a0_2) != 0) {
                if (arg3 != 0) {
                    if (var_v1_3 < 5) {
                        do {
                            temp_t9 = (var_v1_3 + 1) * 2;
                            var_v1_3 = temp_t9;
                        } while (temp_t9 < 5);
                    }
                    var_v1 = var_v1_3 + 5;
                } else {
                    goto block_21;
                }
            } else {
                goto block_21;
            }
        } else {
            goto block_21;
        }
    } else {
block_21:
        var_v1 = var_v1_3 + 6;
    }
    return var_v1;
}
