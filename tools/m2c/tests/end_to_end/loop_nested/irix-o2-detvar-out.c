s32 test(s32 arg0) {
    s32 temp_t1_12;
    s32 var_a1_11;
    s32 var_a2_18;
    s32 var_a2_38;
    s32 var_a3_17;
    s32 var_a3_42;
    s32 var_t0_46;
    s32 var_t1_50;
    s32 var_v0_6;
    s32 var_v1_8;

    var_v0_6 = 0;
    var_v1_8 = 0;
    if (arg0 > 0) {
        do {
            var_a1_11 = 0;
            if (arg0 > 0) {
                temp_t1_12 = arg0 & 3;
                if (temp_t1_12 != 0) {
                    var_a3_17 = 1;
                    var_a2_18 = var_v0_6 * 0;
                    do {
                        var_a1_11 = var_a3_17;
                        var_v1_8 += var_a2_18;
                        var_a2_18 += var_v0_6;
                        var_a3_17 += 1;
                    } while (temp_t1_12 != var_a3_17);
                    if (var_a1_11 != arg0) {
                        goto block_6;
                    }
                } else {
block_6:
                    var_a2_38 = var_v0_6 * var_a1_11;
                    var_a3_42 = var_v0_6 * (var_a1_11 + 1);
                    var_t0_46 = var_v0_6 * (var_a1_11 + 2);
                    var_t1_50 = var_v0_6 * (var_a1_11 + 3);
                    do {
                        var_v1_8 = var_v1_8 + var_a2_38 + var_a3_42 + var_t0_46 + var_t1_50;
                        var_a1_11 += 4;
                        var_t1_50 += var_v0_6 * 4;
                        var_t0_46 += var_v0_6 * 4;
                        var_a3_42 += var_v0_6 * 4;
                        var_a2_38 += var_v0_6 * 4;
                    } while (var_a1_11 != arg0);
                }
            }
            var_v0_6 += 1;
        } while (var_v0_6 != arg0);
    }
    return var_v1_8;
}
