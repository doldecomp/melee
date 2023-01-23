s32 test(s32 arg0) {
    s32 temp_r10;
    s32 var_ctr_2;
    s32 var_r11;
    s32 var_r12;
    s32 var_r29;
    s32 var_r30;
    s32 var_r31;
    s32 var_r4;
    u32 var_ctr;

    temp_r10 = arg0 - 8;
    var_r12 = 0;
    var_r31 = 0;
    var_r30 = 0;
loop_9:
    if (var_r31 < arg0) {
        var_r29 = 0;
        if (arg0 > 0) {
            if (arg0 > 8) {
                var_ctr = (u32) (temp_r10 + 7) >> 3U;
                var_r11 = 0;
                if (temp_r10 > 0) {
                    do {
                        var_r30 = var_r30 + var_r11 + (var_r31 * (var_r29 + 1)) + (var_r31 * (var_r29 + 2)) + (var_r31 * (var_r29 + 3)) + (var_r31 * (var_r29 + 4)) + (var_r31 * (var_r29 + 5)) + (var_r31 * (var_r29 + 6)) + (var_r31 * (var_r29 + 7));
                        var_r11 += var_r12;
                        var_r29 += 8;
                        var_ctr -= 1;
                    } while (var_ctr != 0);
                }
            }
            var_r4 = var_r29 * var_r31;
            var_ctr_2 = arg0 - var_r29;
            if (var_r29 < arg0) {
                do {
                    var_r30 += var_r4;
                    var_r4 += var_r31;
                    var_ctr_2 -= 1;
                } while (var_ctr_2 != 0);
            }
        }
        var_r12 += 8;
        var_r31 += 1;
        goto loop_9;
    }
    return var_r30;
}
