s32 test(s32 arg0) {
    s32 temp_t1;
    s32 var_a1;
    s32 var_a2;
    s32 var_a2_2;
    s32 var_a3;
    s32 var_a3_2;
    s32 var_t0;
    s32 var_t1;
    s32 var_v0;
    s32 var_v1;

    var_v0 = 0;
    var_v1 = 0;
    if (arg0 > 0) {
        do {
            var_a1 = 0;
            if (arg0 > 0) {
                temp_t1 = arg0 & 3;
                if (temp_t1 != 0) {
                    var_a3 = 1;
                    var_a2 = var_v0 * 0;
                    do {
                        var_a1 = var_a3;
                        var_v1 += var_a2;
                        var_a2 += var_v0;
                        var_a3 += 1;
                    } while (temp_t1 != var_a3);
                    if (var_a1 != arg0) {
                        goto block_6;
                    }
                } else {
block_6:
                    var_a2_2 = var_v0 * var_a1;
                    var_a3_2 = var_v0 * (var_a1 + 1);
                    var_t0 = var_v0 * (var_a1 + 2);
                    var_t1 = var_v0 * (var_a1 + 3);
                    do {
                        var_v1 = var_v1 + var_a2_2 + var_a3_2 + var_t0 + var_t1;
                        var_a1 += 4;
                        var_t1 += var_v0 * 4;
                        var_t0 += var_v0 * 4;
                        var_a3_2 += var_v0 * 4;
                        var_a2_2 += var_v0 * 4;
                    } while (var_a1 != arg0);
                }
            }
            var_v0 += 1;
        } while (var_v0 != arg0);
    }
    return var_v1;
}
