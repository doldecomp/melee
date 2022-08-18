extern s32 glob;

s32 test(s32 arg0) {
    s32 var_r3;
    s32 var_r3_2;

    var_r3 = arg0;
    if (var_r3 != 4) {
        if (var_r3 < 4) {
            if (var_r3 != 2) {
                if (var_r3 < 2) {
                    if (var_r3 < 1) {
                        goto block_14;
                    }
                    return var_r3 * var_r3;
                }
                /* Duplicate return node #11. Try simplifying control flow for better match */
                return var_r3 * 2;
            }
            var_r3 -= 1;
            return var_r3 * 2;
        }
        if (var_r3 < 8) {
            if (var_r3 < 6) {
                goto block_14;
            }
            var_r3_2 = var_r3 * 2;
        } else {
block_14:
            var_r3_2 = var_r3 / 2;
        }
        /* Duplicate return node #15. Try simplifying control flow for better match */
        glob = var_r3_2;
        return 2;
    }
    var_r3_2 = var_r3 + 1;
    glob = var_r3_2;
    return 2;
}
